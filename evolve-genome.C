/****************************************************************
 evolve-genome.C
 william.majoros@duke.edu

 Simulation program for evolving a root genome along the branches
 of a given phylogeny, using a given rate matrix for each feature
 type.  Useful for debugging phylogenetic inference software.

 This is open-source software, governed by the Gnu General Public License (GPL) version 3
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include <fstream>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/Constants.H"
#include "BOOM/FastaReader.H"
#include "BOOM/FastaWriter.H"
#include "BOOM/Sequence.H"
#include "BOOM/Alphabet.H"
#include "BOOM/Map.H"
#include "BOOM/Set.H"
#include "BOOM/RouletteWheel.H"
#include "BOOM/Random.H"
#include "BOOM/ConfigFile.H"
#include "BOOM/GffReader.H"
#include "BOOM/Regex.H"
#include "../PhyLib/NthOrdRateMatrix.H"
#include "../PhyLib/Phylogeny.H"
#include "../PhyLib/GapPattern.H"
#include "../PhyLib/IndelHistory.H"
#include "Genome.H"
#include "genezilla.H"
#include "GarbageCollector.H"
#include "SignalSensor.H"
using namespace std;
using namespace BOOM;

Alphabet alphabet;


class Application
{
public:
    Application();
    int main(int argc,char *argv[]);
private:
    Genome *rootGenome;
    GenomeFeature *rootFeature;
    Sequence *rootSeq;
    Map<String,NthOrdRateMatrix*> matrices; // feature type -> matrix
    Map<String,float> insertionProbs; // feature type -> insertion prob
    Map<String,float> deletionProbs;  // feature type -> deletion prob
    Map<String,float> branchFactors;  // feature type -> branchLen multiplier
    Set<String> codingTypes;
    Set<String> keepFeatureTypes;
    Regex matrixFilenameRegex, branchLenRegex;
    Regex insertionRegex, deletionRegex;
    ostream *osGFF, *osFASTA;
    ostream *osGapPatterns;
    FastaWriter fastaWriter;
    Symbol A, C, G, T, N;
    Sequence TAG, TGA, TAA, CTA, TCA, TTA;
    GarbageIgnorer garbageCollector;
    SignalSensor *tfbsSensor;
    bool wantAlignments, dualContexts;
    
    void evolve(Genome *,PhylogenyNode *);
    void inferGaps(Phylogeny &);
    void performSubstitutions(const Sequence &from,Sequence &to,
                              NthOrdSubstMatrix &);
    void substDual(const Sequence &parent,Sequence &S,NthOrdSubstMatrix &);
    GapPattern *inferencePhase1(PhylogenyNode *);
    void inferencePhase2(PhylogenyNode *,GapPattern *);
    void emit(PhylogenyNode &,GapPattern &);
    GapPattern *propagateDown(GapPattern &,IndelHistory &);
    Sequence *mutateNoncoding(Sequence &,NthOrdSubstMatrix &,
                              const String &featureType,IndelHistory &);
    Sequence *mutateCoding(Sequence &,NthOrdSubstMatrix &,
                           const String &featureType,IndelHistory &);
    void processConfigFile(String filename);
    void generateOutput(Genome *,PhylogenyNode *);
    Genome *evolveDist(Genome *,float branchLength,IndelHistory &);
    void unclobberSignals(Sequence &,ContentType);
    void installStopCodon(Sequence &seq,int index,Strand strand);
    void performIndels(Sequence &S,const String &featureType,IndelHistory &);
    void performCodingIndels(Sequence &S,const String &featureType,
                             IndelHistory &);
    int propagatePhase(int &phase,int length,bool isCoding,Strand,
                       ContentType);
    void emitFeatureGFF(GenomeFeature &,PhylogenyNode &);
    void removePrematureStops(Sequence &seq,Genome *genome,int phase,
                              Strand strand);
    void checkTFBS(Genome *child,GenomeFeature *feature);
    void findNewTFBSs(SignalSensor *sensor,Genome *genome,
                      GenomeFeature *feature,Sequence &seq,String &seqStr,
                      Strand);
};


int main(int argc,char *argv[])
  {
    try
      {
	Application app;
	return app.main(argc,argv);
      }
    catch(const char *p)
      {
	cerr << p << endl;
      }
    catch(const BOOM::String &msg)
      {
	cerr << msg.c_str() << endl;
      }
    catch(const string &msg)
      {
	cerr << msg.c_str() << endl;
      }
    catch(const exception &e)
      {
	cerr << "STL exception caught in main:\n" << e.what() << endl;
      }
    catch(...)
      {
	cerr << "Unknown exception caught in main" << endl;
      }
    return -1;
  }



Application::Application()
  : matrixFilenameRegex("matrix\\[(.+)\\]"),
    insertionRegex("insertion\\((\\S+)\\)"),
    deletionRegex("deletion\\((\\S+)\\)"),
    branchLenRegex("branch_factor\\[(.+)\\]"),
    tfbsSensor(NULL),
    wantAlignments(false),
    dualContexts(false)
  {
    // ctor

    codingTypes.insert("exon");
    codingTypes.insert("initial-exon");
    codingTypes.insert("internal-exon");
    codingTypes.insert("final-exon");
    codingTypes.insert("single-exon");
    codingTypes.insert("CDS");
  }



int Application::main(int argc,char *argv[])
  {
    // Process command line
    CommandLine cmd(argc,argv,"a:s:d");
    if(cmd.numArgs()!=6)
      throw String(
"evolve-genome [options] <in.fasta> <in.gff> <*.phylogeny> <*.config>\n\
                        <out.fasta> <out.gff>\n\
where:\n\
        -a <filestem> : emits feature alignments\n\
        -s <N> : use N to seed random number generator\n\
        -d : use dual contexts\n\
\n");
    String inFasta=cmd.arg(0);
    String inGff=cmd.arg(1);
    String phyloFile=cmd.arg(2);
    String configFilename=cmd.arg(3);
    String outFasta=cmd.arg(4);
    String outGff=cmd.arg(5);
    if(cmd.option('a'))
    {
        wantAlignments=true;
        String filestem=cmd.optParm('a');
        osGapPatterns=new ofstream((filestem+".gaps").c_str());
    }
    if(cmd.option('s'))
        SeedRandomizer(cmd.optParm('s').asInt());
    else
        randomize();
    if(cmd.option('d')) dualContexts=true;

    // Load the root sequence
    alphabet=DnaAlphabet::global;
    FastaReader fastaReader(inFasta,alphabet);
    String seqStr, def;
    fastaReader.nextSequence(def,seqStr);
    rootSeq=new Sequence(seqStr,alphabet);
    fastaReader.close();

    // Some initialization
    A=alphabet.lookup('A');
    C=alphabet.lookup('C');
    G=alphabet.lookup('G');
    T=alphabet.lookup('T');
    N=alphabet.lookup('N');
    TAG=Sequence("TAG",alphabet);
    TGA=Sequence("TGA",alphabet);
    TAA=Sequence("TAA",alphabet);
    CTA=Sequence("CTA",alphabet);
    TCA=Sequence("TCA",alphabet);
    TTA=Sequence("TTA",alphabet);

    // Process the config file
    processConfigFile(configFilename);

    // Load the root annotations
    rootGenome=new Genome(inGff,*rootSeq,keepFeatureTypes);

    // Load the phylogeny
    Phylogeny phylogeny(phyloFile);

    // Prepare output files
    osGFF=new ofstream(outGff.c_str());
    osFASTA=new ofstream(outFasta.c_str());

    // Perform evolution
    cerr<<"performing evolution..."<<endl;
    evolve(rootGenome,phylogeny.getRoot());

    // Emit alignments if desired
    if(wantAlignments)
    {
        cerr<<"Reconstructing gap patterns..."<<endl;
        inferGaps(phylogeny);
    }
    
    // Clean up
    cerr<<"cleaning up..."<<endl;
    delete osGFF;
    delete osFASTA;
    if(wantAlignments) delete osGapPatterns;
    cerr<<"done."<<endl;
    return 0;
  }



void Application::evolve(Genome *genome,PhylogenyNode *node)
{
    if(wantAlignments)
        node->getIndelHistory().topOff(genome->getLength());
    
    // Proceed with evolution below this point
    switch(node->getNodeType())
    {
        case LEAF_NODE:
            generateOutput(genome,node);
            delete genome;
            break;
        case INTERNAL_NODE:
        {
            InternalNode *intNode=(InternalNode*) node;
            PhylogenyNode *leftChild=intNode->getLeft();
            PhylogenyNode *rightChild=intNode->getRight();
            float leftLen=intNode->getLeftDistance();
            float rightLen=intNode->getRightDistance();
            IndelHistory &leftHistory=leftChild->getIndelHistory();
            IndelHistory &rightHistory=rightChild->getIndelHistory();
            Genome *leftGenome=evolveDist(genome,leftLen,leftHistory);
            Genome *rightGenome=evolveDist(genome,rightLen,rightHistory);
            generateOutput(genome,node);
            delete genome;
            evolve(leftGenome,leftChild);
            evolve(rightGenome,rightChild);
        }
        break;
        case ROOT_NODE:
        {
            RootNode *root=(RootNode*) node;
            PhylogenyNode *child=root->getChild();
            float branchLen=root->getBranchLength();
            IndelHistory &history=child->getIndelHistory();
            Genome *childGenome=evolveDist(genome,branchLen,history);
            generateOutput(genome,node);
            //delete genome; // can't do this if using TRCO!
            evolve(childGenome,child);
        }
        break;
    }
}



Sequence *Application::mutateNoncoding(Sequence &S,NthOrdSubstMatrix &Pt,
				       const String &featureType,
                                       IndelHistory &indelHistory)
{
    Sequence *newS=new Sequence(N,S.getLength());
    performSubstitutions(S,*newS,Pt);
    performIndels(*newS,featureType,indelHistory);
    return newS;
}



Sequence *Application::mutateCoding(Sequence &S,NthOrdSubstMatrix &Pt,
				    const String &featureType,
                                    IndelHistory &indelHistory)
{
    Sequence *newS=new Sequence(N,S.getLength());
    performSubstitutions(S,*newS,Pt);
    performCodingIndels(*newS,featureType,indelHistory);
    return newS;
}



void Application::substDual(const Sequence &parent,Sequence &S,
                            NthOrdSubstMatrix &Pt) {
    // same as performSubstitutions(), but using dual contexts

    int order=Pt.getOrder()/2;
    int L=S.getLength();
    for(int i=0 ; i<L ; ++i)
    {
        Symbol sym=parent[i];
        int contextBegin=i-order;
        if(contextBegin<0) contextBegin=0;
        int contextLen=i-contextBegin;
        Sequence fullContext, childContext;
        parent.getSubsequence(contextBegin,contextLen,fullContext);
        S.getSubsequence(contextBegin,contextLen,childContext);
        fullContext.append(childContext);
        Symbol newSym=Pt.mutate(sym,fullContext,0,2*contextLen);
        if(newSym==N) ++newSym;
        S[i]=newSym;
    }
}



void Application::performSubstitutions(const Sequence &parent,
                                       Sequence &S,NthOrdSubstMatrix &Pt)
{
    if(dualContexts) {substDual(parent,S,Pt); return;}
    
    // Mutate sequence
    int order=Pt.getOrder();
    int L=parent.getLength();
    for(int i=L-1 ; i>=0 ; --i)
    {
        Symbol sym=parent[i];
        int contextBegin=i-order;
        if(contextBegin<0) contextBegin=0;
        int contextLen=i-contextBegin;
        const Sequence &context=parent; // ACO
        //Sequence &context=rootFeature->getSeq(); // TRCO
        Symbol newSym=Pt.mutate(sym,context,contextBegin,contextLen);
        if(newSym==N) ++newSym;
        S[i]=newSym;
    }
}



void Application::processConfigFile(String filename)
{
  double tfbsThreshold=NEGATIVE_INFINITY;
  ConfigFile configFile(filename);
  Map<String,String> entries=configFile.peek();
  Map<String,String>::iterator cur=entries.begin(), end=entries.end();
  for(; cur!=end ; ++cur)
    {
      pair<const String,String> &p=*cur;
      const String &key=p.first;
      if(matrixFilenameRegex.search(key))
	{
	  String featureType=matrixFilenameRegex[1];
	  String matrixFile=p.second;
	  NthOrdRateMatrix *Q=NthOrdRateMatrix::load(matrixFile);
	  matrices[featureType]=Q;
	  keepFeatureTypes.insert(featureType);
	}

      else if(branchLenRegex.search(key))
	{
	  String featureType=branchLenRegex[1];
	  branchFactors[featureType]=p.second.asFloat();
	}

      else if(insertionRegex.match(key))
	insertionProbs[insertionRegex[1]]=p.second.asFloat();

      else if(deletionRegex.match(key))
	deletionProbs[deletionRegex[1]]=p.second.asFloat();

      else if(key=="TFBS_model")
	{
	  tfbsSensor=SignalSensor::load(p.second,garbageCollector);
	  tfbsSensor->noConsensus();
	  if(tfbsThreshold==NEGATIVE_INFINITY)
	    tfbsThreshold=tfbsSensor->getCutoff();
	}

      else if(key=="TFBS_threshold")
	tfbsThreshold=p.second.asFloat();

      //...process other config file entries here...
    }
  if(tfbsSensor) tfbsSensor->setCutoff(tfbsThreshold);
}



Genome *Application::evolveDist(Genome *parent,float branchLength,
                                IndelHistory &indelHistory)
{
  Genome *child=new Genome;
  int numFeatures=parent->numFeatures();
  int length=0, phase=0;
  for(int i=0 ; i<numFeatures ; ++i)
    {
      GenomeFeature *feature=parent->getIthFeature(i);
      rootFeature=rootGenome->getIthFeature(i); // for TRCO
      String featureType=feature->getFeatureType();
      ContentType contentType=feature->getContentType();
      Strand strand=feature->getStrand();
      NthOrdRateMatrix *Q=matrices[featureType];
      float branchLenMultiplier=1.0;
      if(branchFactors.isDefined(featureType))
	branchLenMultiplier=branchFactors[featureType];
      NthOrdSubstMatrix *Pt=
	Q->instantiate(branchLength*branchLenMultiplier);
      Pt->initGenerators();
      bool isCoding=::isCoding(contentType);
      Sequence *childSeq=
	isCoding ? 
          mutateCoding(feature->getSeq(),*Pt,featureType,indelHistory) :
          mutateNoncoding(feature->getSeq(),*Pt,featureType,indelHistory);
      delete Pt;
      int begin=length;
      length+=childSeq->getLength();
      int end=length;
      GenomeFeature *childFeature=
	new GenomeFeature(begin,end,phase,featureType,strand);
      if(isCoding)
	removePrematureStops(*childSeq,child,phase,strand);
      unclobberSignals(*childSeq,contentType);
      phase=propagatePhase(phase,length,isCoding,strand,contentType);
      childFeature->setSeq(*childSeq);
      delete childSeq;
      child->addFeature(childFeature);
    }
  if(tfbsSensor)
    for(int i=0 ; i<numFeatures ; ++i)
      checkTFBS(child,child->getIthFeature(i));
  return child;
}



void Application::checkTFBS(Genome *child,GenomeFeature *feature)
{
  String featureType=feature->getFeatureType();
  ContentType contentType=feature->getContentType();
  Strand strand=feature->getStrand();
  Sequence &seq=feature->getSeq();
  String *str=seq.toString(DnaAlphabet::global);
  if(contentType==TFBS || contentType==NEG_TFBS)
    {
      SignalSensor *sensor=
	contentType==TFBS ? tfbsSensor : tfbsSensor->reverseComplement();
      SignalPtr signal=sensor->detect(seq,*str,0);
      if(!signal) 
	{
	  feature->changeFeatureType("intergenic");
	}
    }
  else if(contentType==INTERGENIC)
    {
      findNewTFBSs(tfbsSensor,child,feature,seq,*str,FORWARD_STRAND);
      findNewTFBSs(tfbsSensor->reverseComplement(),child,feature,seq,*str,
		   REVERSE_STRAND);
    }

  delete str;
}



void Application::findNewTFBSs(SignalSensor *sensor,Genome *genome,
			       GenomeFeature *feature,Sequence &seq,
			       String &seqStr,Strand strand)
{
  int L=seq.getLength();
  int wLen=sensor->getContextWindowLength();
  int end=L-wLen+1;
  for(int i=0 ; i<end ; ++i)
    {
      SignalPtr p=sensor->detect(seq,seqStr,i);
      if(p)
	{
	  GenomeFeature *newTFBS=new GenomeFeature(i,i+wLen,0,"TFBS",
						   strand);
	  newTFBS->initSeq(seq);
	  Sequence tmp=seq;
	  if(i+wLen<L)
	    {
	      GenomeFeature *right=new GenomeFeature(i+wLen,L,0,
						 feature->getFeatureType(),
						 feature->getStrand());
	      right->initSeq(seq);
	      genome->addFeature(right);
	    }
	  feature->changeEnd(i);
	  feature->initSeq(tmp);
	  genome->addFeature(newTFBS);
	  break;
	}
    }
}
		       


void Application::performIndels(Sequence &S,const String &featureType,
                                IndelHistory &indelHistory)
{
    float iP=(insertionProbs.isDefined(featureType) ?
              insertionProbs[featureType] : 0);
    float dP=(deletionProbs.isDefined(featureType) ?
              deletionProbs[featureType] : 0);
    int L=S.getLength();
    for(int i=0 ; i<L ; ++i)
    {
        float r=Random0to1();
        if(r<iP)
        {
            Symbol s=RandomNumber(4);
            if(s==N) ++s;
            S.insert(s,i);
            ++L;
            if(wantAlignments)
                indelHistory.append(IndelOperation::INSERTION);
        }
        else
        {
            r=Random0to1();
            if(r<dP)
            {
                S.cut(i,1);
                --L;
                --i;
                if(wantAlignments)
                    indelHistory.append(IndelOperation::DELETION);
            }
            else if(wantAlignments)
                indelHistory.append(IndelOperation::SUBSTITUTION);
        }
    }
}



void Application::performCodingIndels(Sequence &S,
				      const String &featureType,
                                      IndelHistory &indelHistory)
{
    float iP=insertionProbs.isDefined(featureType) ?
        insertionProbs[featureType] : 0;
    float dP=deletionProbs.isDefined(featureType) ?
        deletionProbs[featureType] : 0;
    int L=S.getLength();
    for(int i=3 ; i<L-3 ; i+=3) // ### 7/18/06 : changed 0->3 and L->L-3
    {
        float r=Random0to1();
        if(r<iP)
        {
            for(int j=0 ; j<3 ; ++j)
            {
                Symbol s=RandomNumber(4);
                if(s==N) ++s;
                S.insert(s,i);
                ++L;
            }
            if(wantAlignments)
                indelHistory.append(IndelOperation::INSERTION,3);
        }
        else if(wantAlignments)
            indelHistory.append(IndelOperation::SUBSTITUTION,3);

        r=Random0to1();
        if(r<dP && L>3)
        {
            S.cut(i,3);
            L-=3;
            i-=3;
            if(wantAlignments)
                indelHistory.append(IndelOperation::DELETION,3);
        }
        else if(wantAlignments)
            indelHistory.append(IndelOperation::SUBSTITUTION,3);
    }
}



int Application::propagatePhase(int &phase,int length,bool isCoding,
				 Strand strand,ContentType contentType)
{
  switch(contentType)
    {
    case UNKNOWN_CONTENT_FORWARD: return 0;
    case UNKNOWN_CONTENT_REVERSE: return 2;
    case INITIAL_EXON: return (phase+length)%3;
    case INTERNAL_EXON: return (phase+length)%3;
    case FINAL_EXON: return 0;
    case SINGLE_EXON: return 0;
    case INTRON: return phase;
    case INTERGENIC: return 0;
    case FIVE_PRIME_UTR: return 0;
    case THREE_PRIME_UTR: return 0;
    case NEG_INITIAL_EXON: return 2;
    case NEG_INTERNAL_EXON: return posmod(phase-length);
    case NEG_FINAL_EXON: return posmod(phase-length);
    case NEG_SINGLE_EXON: return 2;
    case NEG_INTRON: return phase;
    case NEG_FIVE_PRIME_UTR: return 2;
    case NEG_THREE_PRIME_UTR: return 2;
    case TFBS: return 0;
    case NEG_TFBS: return 0;
    }
}



void Application::generateOutput(Genome *genome,PhylogenyNode *node)
{
  genome->sortFeatures();
  Alphabet &alphabet=DnaAlphabet::global;
  int n=genome->numFeatures();
  Sequence genomeSeq;
  for(int i=0 ; i<n ; ++i)
    {
      GenomeFeature *feature=genome->getIthFeature(i);
      genomeSeq.append(feature->getSeq());
      if(feature->isCoding() || feature->getFeatureType()=="TFBS")
	emitFeatureGFF(*feature,*node);
    }

  String defline=String(">")+node->getID()+" /name="+node->getName();
  switch(node->getNodeType())
    {
    case INTERNAL_NODE: defline+=" /type=ancestor"; break;
    case LEAF_NODE:     defline+=" /type=leaf";     break;
    case ROOT_NODE:     defline+=" /type=root";     break;
    }
  String *str=genomeSeq.toString(alphabet);
  fastaWriter.addToFasta(defline,*str,*osFASTA);
}



void Application::emitFeatureGFF(GenomeFeature &feature,PhylogenyNode &node)
{
  String substrateID=node.getID();
  String species=node.getName();
  if(species=="") species="species_"+node.getID();
  *osGFF<<node.getID()<<"\t"<<species<<"\t"<<feature.getFeatureType()
	<<"\t"<<feature.getBegin()+1<<"\t"<<feature.getEnd()
	<<"\t"<<"."<<"\t"<<feature.getStrand()<<"\t"
	<<feature.getPhase()<<endl;
}



void Application::removePrematureStops(Sequence &seq,Genome *genome,
				       int phase,Strand strand)
{
  // INVARIANT: The caller first checks that this is a coding feature!

  // First, check for complete stop codons in frame
  int begin;
  if(strand==FORWARD_STRAND) begin=(3-phase)%3;
  else begin=(phase+1)%3;
  int end=seq.getLength();
  for(int pos=begin ; pos<end ; pos+=3)
    {
      if(seq.subsequenceOccursAt(TAG,pos) ||
	 seq.subsequenceOccursAt(TGA,pos) ||
	 seq.subsequenceOccursAt(TAA,pos))
	{
	  int r=RandomNumber(3);
	  if(strand==FORWARD_STRAND) 
	    seq[pos]=
	      (r==0 ? A : (r==1 ? C : G));
	  else
	    seq[pos+2]=
	      (r==0 ? T : (r==1 ? C : G));
	}
    }

  // Also check for stops straddling an immediately preceding intron
  int n=genome->numFeatures();
  if(n<2) return;
  if(!isIntron(genome->getIthFeature(n-1)->getContentType())) return;
  GenomeFeature *prevExon=genome->getIthFeature(n-2);
  Sequence &prevSeq=prevExon->getSeq();
  int prevLen=prevSeq.getLength();
  Sequence codon("NNN",DnaAlphabet::global);
  if(strand==FORWARD_STRAND)
    {
      if(phase==1)
	{
	  codon[0]=prevSeq[prevLen-1];
	  codon[1]=seq[0];
	  codon[2]=seq[1];
	  if(codon==TAG || codon==TGA || codon==TAA)
	    {
	      prevSeq[prevLen-1]=codon[2]; 
	      seq[1]=codon[0];
	    }
	}
      else if(phase==2)
	{
	  codon[0]=prevSeq[prevLen-2];
	  codon[1]=prevSeq[prevLen-1];
	  codon[2]=seq[0];
	  if(codon==TAG || codon==TGA || codon==TAA)
	    {
	      prevSeq[prevLen-2]=codon[2];
	      seq[0]=codon[0];
	    }
	}
    }
  else // strand==REVERSE_STRAND
    {
      if(phase==0)
	{
	  codon[0]=prevSeq[prevLen-2];
	  codon[1]=prevSeq[prevLen-1];
	  codon[2]=seq[0];
	  if(codon==CTA || codon==TCA || codon==TTA)
	    {
	      prevSeq[prevLen-2]=codon[2];
	      seq[0]=codon[0];
	    }
	}
      else if(phase==1)
	{
	  codon[0]=prevSeq[prevLen-1];
	  codon[1]=seq[0];
	  codon[2]=seq[1];
	  if(codon==CTA || codon==TCA || codon==TTA)
	    {
	      prevSeq[prevLen-1]=codon[2];
	      seq[1]=codon[0];
	    }
	}
    }
}



void Application::unclobberSignals(Sequence &seq,ContentType contentType)
{
    int L=seq.getLength();
    switch(contentType)
    {
        case INITIAL_EXON:
            seq[0]=A; seq[1]=T; seq[2]=G;
            break;
        case FINAL_EXON:
            installStopCodon(seq,L-3,FORWARD_STRAND);
            break;
        case SINGLE_EXON:
            seq[0]=A; seq[1]=T; seq[2]=G;
            installStopCodon(seq,L-3,FORWARD_STRAND);
            break;
        case INTRON:
            seq[0]=G; seq[1]=T; seq[L-2]=A; seq[L-1]=G;
            break;
        case NEG_INITIAL_EXON:
            seq[L-1]=T; seq[L-2]=A; seq[L-3]=C;
            break;
        case NEG_FINAL_EXON:
            installStopCodon(seq,0,REVERSE_STRAND);
            break;
        case NEG_SINGLE_EXON:
            seq[L-1]=T; seq[L-2]=A; seq[L-3]=C;
            installStopCodon(seq,0,REVERSE_STRAND);
            break;
        case NEG_INTRON:
            seq[0]=C; seq[1]=T; seq[L-2]=A; seq[L-1]=C;
            break;
    }
}



void Application::installStopCodon(Sequence &seq,int index,Strand strand)
{
    // Install a stop codon at the indicate position, while minimizing the
    // number of changes to the sequence

    int r;
    Sequence codon("NNN",alphabet);
    switch(strand)
    {
        case FORWARD_STRAND:
            seq.getSubsequence(index,3,codon);
            if(codon==TAG || codon==TGA || codon==TAA) break;
            if(seq[index]!=T) seq[index]=T;
            if(seq[index+1]==G) {seq[index+2]=A; break;}
            r=RandomNumber(3);
            if(r==0) {seq[index+1]=G; seq[index+2]=A; break;}
            seq[index+1]=A;
            if(seq[index+2]==A || seq[index+2]==G) break;
            seq[index+2]=(r==1 ? A : G);
            break;
        case REVERSE_STRAND:
            seq.getSubsequence(index,3,codon);
            if(codon==CTA || codon==TCA || codon==TTA) break;
            if(seq[index+2]!=A) seq[index+2]=A;
            if(seq[index+1]==C) {seq[index]=T; break;}
            r=RandomNumber(3);
            if(r==0) {seq[index+1]=C; seq[index]=T; break;}
            seq[index+1]=T;
            if(seq[index]==T || seq[index]==C) break;
            seq[index]=(r==1 ? T : C);
            break;
        default: throw __FILE__;
    }
}



void Application::inferGaps(Phylogeny &phylogeny)
{
    // Phase I : synthesize initial gap patterns up from the leaves to
    // the root
    PhylogenyNode *root=phylogeny.getRoot();
    GapPattern *rootPattern=inferencePhase1(root);
    
    // Phase II : propagate final gap patterns down from the root to the
    // leaves
    inferencePhase2(root,rootPattern);
}



GapPattern *Application::inferencePhase1(PhylogenyNode *node)
{
    switch(node->getNodeType())
    {
        case ROOT_NODE:
        {
            RootNode *root=(RootNode*) node;
            return inferencePhase1(root->getChild());
        }
        case LEAF_NODE:
        {
            GapPattern empty;
            return empty.propagateUp(node->getIndelHistory(),node->getID());
        }
        case INTERNAL_NODE:
        {
            InternalNode *intNode=(InternalNode*) node;
            GapPattern *left=inferencePhase1(intNode->getLeft());
            GapPattern *right=inferencePhase1(intNode->getRight());
            left->subsume(*right);
            GapPattern *combined=left->propagateUp(node->getIndelHistory(),
                                                   node->getID());
            delete left;
            delete right;
            return combined;
        }
        default: throw String(__FILE__)+__LINE__;
    }
}



void Application::inferencePhase2(PhylogenyNode *node,
                                  GapPattern *gapPattern)
{
    emit(*node,*gapPattern);
    switch(node->getNodeType())
    {
        case ROOT_NODE:
        {
            RootNode *root=(RootNode*) node;
            PhylogenyNode *child=root->getChild();
            IndelHistory &H=child->getIndelHistory();
            gapPattern->appendGap(H.getParentSeqLength(),0);
            GapPattern *childPattern=propagateDown(*gapPattern,H);
            inferencePhase2(child,childPattern);
            break;
        }
        case LEAF_NODE:
        {
            // do nothing
            break;
        }
        case INTERNAL_NODE:
        {
            InternalNode *intNode=(InternalNode*) node;
            PhylogenyNode *left=intNode->getLeft();
            PhylogenyNode *right=intNode->getRight();
            IndelHistory &leftH=left->getIndelHistory();
            IndelHistory &rightH=right->getIndelHistory();
            gapPattern->appendGap(leftH.getParentSeqLength(),0);
            GapPattern *childPattern=propagateDown(*gapPattern,leftH);
            inferencePhase2(left,childPattern);
            childPattern=propagateDown(*gapPattern,rightH);
            inferencePhase2(right,childPattern);
            break;
        }
        default: throw String(__FILE__)+":"+__LINE__;
    }
    delete gapPattern;
}



void Application::emit(PhylogenyNode &node,GapPattern &pattern)
{
    (*osGapPatterns)<<node.getName()<<endl<<pattern<<endl;
}



GapPattern *Application::propagateDown(GapPattern &G,
                                       IndelHistory &h)
{
    IndelHistory H=h;
    GapPattern &newPattern=*new GapPattern;
    int nH=H.getLength(), nG=G.numGaps();
    int parentPos=0, childPos=0;
    for(int iH=0, iG=0 ; iG<nG ; ++iG)
    {
        Gap oldGap=G[iG];
        int newGapPos;
        for( ; iH<nH ; ++iH)
        {
            IndelOperation &op=H[iH];
            int nextParentPos, nextChildPos, opLen=op.getLength();
            switch(op.getType()) {
                case IndelOperation::SUBSTITUTION:
                    nextParentPos=parentPos+opLen;
                    nextChildPos=childPos+opLen;
                    if(parentPos<=oldGap.pos && nextParentPos>oldGap.pos) {
                        newGapPos=childPos+oldGap.pos-parentPos;
                        goto APPEND;
                    }
                    break;
                case IndelOperation::INSERTION:
                    if(oldGap.insertion==&h[iH]) { // "annihilate"
                        childPos+=oldGap.len;
                        op.changeLength(opLen-oldGap.len);
                        goto NO_APPEND;
                    }
                    nextParentPos=parentPos;
                    nextChildPos=childPos+opLen;
                    if(parentPos==oldGap.pos) {
                        newGapPos=childPos;
                        goto APPEND;
                    }
                    break;
                case IndelOperation::DELETION:
                    nextParentPos=parentPos+opLen;
                    nextChildPos=childPos;
                    if(parentPos<=oldGap.pos && nextParentPos>oldGap.pos) {
                        int leftPart=oldGap.pos-parentPos;
                        int rightPart=opLen-leftPart;
                        if(leftPart>0) newPattern.appendGap(childPos,leftPart);
                        newPattern.appendGap(childPos,oldGap.len,
                                             oldGap.insertion);
                        op.changeLength(opLen-leftPart);
                        parentPos+=leftPart;
                        goto NO_APPEND;
                    }
                    else newPattern.appendGap(childPos,opLen);
                    break;
            }
            parentPos=nextParentPos;
            childPos=nextChildPos;
        }
      APPEND:
        if(iH==nH) newGapPos=childPos;
        if(oldGap.len>0)
            newPattern.appendGap(newGapPos,oldGap.len,oldGap.insertion);
      NO_APPEND:
        ;
    }
    return &newPattern;
}




