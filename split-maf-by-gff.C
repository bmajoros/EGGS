/****************************************************************
 split-maf-by-gff.C
 william.majoros@duke.edu

 Breaks a big MAF (multi-alignment format) file into chunks so it
 can be more easily viewed with the UNIX less and more commands.

 This is open-source software, governed by the Gnu General Public License (GPL) version 3
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include <fstream>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/Constants.H"
#include "BOOM/Sequence.H"
#include "BOOM/DnaAlphabet.H"
#include "BOOM/AlphabetMap.H"
#include "BOOM/MultiAlignment.H"
#include "BOOM/GffReader.H"
#include "../PhyLib/SubstitutionMatrix.H"
#include "../PhyLib/Phylogeny.H"
using namespace std;
using namespace BOOM;

Alphabet alphabet;


class Application
{
public:
    Application();
    int main(int argc,char *argv[]);
private:
    MultiAlignment *alignment;
    int nextCodingChunk, nextNoncodingChunk;
    void split(Vector<MultiAlignment*> &,Vector<GffFeature*> &,
               AlignmentTrack &targetTrack,const String &codingDir,
               const String &noncodingDir);
    void advance(AlignmentTrack &targetTrack,int alignLen,
                 int &alignPos,int &seqPos,int advanceTo);
    bool isCoding(const String &featureType);
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
    : nextCodingChunk(1), nextNoncodingChunk(1)
  {
    // ctor
  }



int Application::main(int argc,char *argv[])
  {
      // Process command line
      CommandLine cmd(argc,argv,"");
      if(cmd.numArgs()!=6)
          throw String(
"split-maf-by-gff <*.maf> <*.gff> <target-species> <coding-dir> <noncoding-dir> <max-noncoding-feature-length>");
      String mafFile=cmd.arg(0);
      String gffFile=cmd.arg(1);
      String targetSpecies=cmd.arg(2);
      String codingDir=cmd.arg(3);
      String noncodingDir=cmd.arg(4);
      int maxNoncodingLength=cmd.arg(5).asInt();

      // Initialization
      alphabet=DnaAlphabet::global;
      if(codingDir.lastChar()=='/') codingDir.chop();
      if(noncodingDir.lastChar()=='/') noncodingDir.chop();
      
      // Load the alignments
      cerr<<"loading alignments..."<<endl;
      Vector<MultiAlignment*> alignments;
      MultiAlignment::loadMAF(mafFile,alignments);
      cerr<<"combining alignments..."<<endl;
      alignment=MultiAlignment::combine(alignments,true);
      alignment->toupper();
      AlignmentTrack &targetTrack=alignment->getTrackByName(targetSpecies);
      cerr<<"getting nongap length..."<<endl;
      int targetSeqLen=targetTrack.getNonGapLength();

      // Load GFF
      cerr<<"loading gff..."<<endl;
      GffReader reader(gffFile);
      Vector<GffFeature*> *features=reader.loadFeatures();
      String substrate="dummy_substrate";
      cerr<<"filtering..."<<endl;
      GffReader::filterBySource(*features,targetSpecies);
      cerr<<"adding noncoding features..."<<endl;
      GffReader::addNoncodingFeatures(*features,targetSeqLen,substrate,
                                      targetSpecies,maxNoncodingLength);
      
      // Break into chunks
      cerr<<"breaking into chunks..."<<endl;
      split(alignments,*features,targetTrack,codingDir,noncodingDir);

      cout<<"done."<<endl;
      return 0;
  }



void Application::split(Vector<MultiAlignment*> &alignments,
                        Vector<GffFeature*> &features,
                        AlignmentTrack &targetTrack,
                        const String &codingDir,
                        const String &noncodingDir)
{
    const int LINE_LEN=50000;
    int numFeatures=features.size();
    int alignLen=alignment->getLength();
    int alignPos=-1, seqPos=-1;
    cout<<"numFeatures="<<numFeatures<<", alignLen="<<alignLen<<endl;
    for(int featureIndex=0 ; featureIndex<numFeatures ; ++featureIndex)
    {
        GffFeature *feature=features[featureIndex];
        advance(targetTrack,alignLen,alignPos,seqPos,feature->getBegin());
        int sliceBegin=alignPos;
        advance(targetTrack,alignLen,alignPos,seqPos,feature->getEnd());
        int sliceEnd=alignPos;
        int sliceLen=sliceEnd-sliceBegin;
        String filename;
        String featureType=feature->getFeatureType();
        if(isCoding(featureType))
        {
            filename=codingDir+String("/")+nextCodingChunk+String(".maf");
            ++nextCodingChunk;
        }
        else
        {
            filename=noncodingDir+String("/")+nextNoncodingChunk+String(".maf");
            ++nextNoncodingChunk;
        }
        //cout<<filename<<endl;
        ofstream os(filename.c_str());
        alignment->printSlice(os,sliceBegin,sliceLen,feature->getStrand(),
                              LINE_LEN);
        //cout<<"printSlice("<<sliceBegin<<","<<sliceLen<<","<<LINE_LEN<<")"<<endl;
    }
}



void Application::advance(AlignmentTrack &targetTrack,int alignLen,
                          int &alignPos,int &seqPos,int advanceTo)
{
    if(seqPos>advanceTo) throw String("ERROR: ")+seqPos+">"+advanceTo;
    while(seqPos<advanceTo)
    {
        ++alignPos;
        if(targetTrack[alignPos]!='-') ++seqPos;
    }
}



bool Application::isCoding(const String &featureType)
{
    return featureType.contains("exon") || featureType.contains("CDS");
}


