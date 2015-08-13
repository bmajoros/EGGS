/****************************************************************
 get-WMM-cutoff.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include <fstream>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/FastaReader.H"
#include "BOOM/Histogram.H"
#include "WMM.H"
#include "MarkovChain.H"
#include "GarbageCollector.H"
using namespace std;
using namespace BOOM;


Alphabet alphabet=DnaAlphabet::global();


enum DecisionType
  {
    FP_RATE,
    FN_RATE,
    MAX_FP_FN
  };


struct Application {
  Application();
  int main(int argc,char *argv[]);
private:
  DecisionType decisionType;
  bool useRatios; // whether to use log-likelihood ratios (LLR) instead of
                  // just raw probabilities
  bool shouldDump; // whether to dump histograms into file
  bool midpointRuleOK; // whether to use the midpoint between histogram
                       // endpoints for fully-separable distributions
  String outfile;
  int numHistBins, order, numSamples, wmmLength;
  double pseudocount, criticalValue;
  GarbageCollector gc;
  WMM *wmm;
  MarkovChain *mc;
  Histogram<double> *buildHist(WMM &);
  Histogram<double> *buildHist(MarkovChain &,WMM &);
  double computeThreshold(Histogram<double> &foreground,
			  Histogram<double> &background);
  void getMinAndMax(Vector<double> &scores,double &min,double &max);
  DecisionType getDecisionType(const String &);
  void dumpHistograms(const Histogram<double> &foreground,
		      const Histogram<double> &background);
};



double max(double a,double b)
{
  return a>b ? a : b;
}



int main(int argc,char *argv[])
  {
    try
      {
	Application app;
	return app.main(argc,argv);
      }
    catch(const String &msg)
      {
	cerr << msg.c_str() << endl;
      }
    catch(const char *p)
      {
	cerr << p << endl;
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
  {
    // ctor
  }



int Application::main(int argc,char *argv[])
  {
    // Process command line
    CommandLine cmd(argc,argv,"Pc:b:B:s:o:d:h:M");
    if(cmd.numArgs()!=3)
      throw String("\n\
get-WMM-cutoff <matrix.wmm> <background.fasta> <critical-value>\n\
\n\
where:\n\
       <critical-value> is the FP rate\n\
       -d X = interpret <critical-value> using decision type X:\n\
               FP = false positive rate (default)\n\
               FN = false negative rate\n\
               MAX = maximum of FP rate and FN rate\n\
       -P   = use raw probabilities instead of LLR ratios\n\
       -c N = use pseudocount N for histogram bins (default=0)\n\
       -b N = use N bins in the histograms (default=30)\n\
       -s N = use N samples when computing histogram (default=1000)\n\
       -o N = order of background model (default=0)\n\
       -h <outfile> = dump histograms to outfile\n\
       -M = do not apply midpoint rule, even for separable distributions\n\
       -B <outfile> = save background model\n\
");
    String matrixFilename=cmd.arg(0);
    String fastaFilename=cmd.arg(1);
    criticalValue=cmd.arg(2).asFloat();
    order=(cmd.option('o') ? cmd.optParm('o').asInt() : 0);
    numHistBins=(cmd.option('b') ? cmd.optParm('b').asInt() : 30);
    numSamples=(cmd.option('s') ? cmd.optParm('s').asInt() : 1000);
    pseudocount=(cmd.option('c') ? cmd.optParm('c').asFloat() : 0.0);
    useRatios=(cmd.option('P') ? false : true);
    decisionType=
      (cmd.option('d') ? getDecisionType(cmd.optParm('d')) : FP_RATE);
    shouldDump=cmd.option('h');
    if(shouldDump) outfile=cmd.optParm('h');
    midpointRuleOK=!cmd.option('M');
    bool wantBackground=cmd.option('B');
    
    // Load the weight matrix
    SignalSensor *sensor=SignalSensor::load(matrixFilename,gc);
    wmm=dynamic_cast<WMM*>(sensor);
    if(!wmm) throw "sensor must be a WMM";
    wmmLength=wmm->getContextWindowLength();

    // Process sequences
    FastaReader fastaReader(fastaFilename);
    String def, seq;
    Vector<TrainingSequence*> seqs;
    while(!fastaReader.eof()) {
      fastaReader.nextSequence(def,seq);
      TrainingSequence *trainingSeq=new TrainingSequence(seq,alphabet);
      trainingSeq->setPhase(0);
      seqs.push_back(trainingSeq);
    }
    fastaReader.close();

    // Train background model
    mc=new MarkovChain(seqs,order,175,0,INTERGENIC);
    
    // Construct histograms
    Histogram<double> *foregroundHist=buildHist(*wmm);
    Histogram<double> *backgroundHist=buildHist(*mc,*wmm);

    // Compute threshold
    double threshold=computeThreshold(*foregroundHist,*backgroundHist);
    cout<<threshold<<endl;

    // Dump histograms into file (if requested)
    if(shouldDump) dumpHistograms(*foregroundHist,*backgroundHist);

    // Dump background model (if requested)
    if(wantBackground) mc->save(cmd.optParm('B'));

    return 0;
  }



void Application::getMinAndMax(Vector<double> &scores,double &min,
			       double &max) 
{
  int n=scores.size();
  min=max=scores[0];
  for(int i=1 ; i<n ; ++i) {
    double s=scores[i];
    if(s<min) min=s;
    else if(s>max) max=s;
  }
}



Histogram<double> *Application::buildHist(WMM &wmm) 
{
  String str;
  Vector<double> scores;
  for(int i=0 ; i<numSamples ; ++i) {
    Sequence seq;
    wmm.sample(seq);
    str=seq(alphabet);
    double logP=wmm.getLogP(seq,str,0);
    if(useRatios)
      logP-=mc->scoreSubsequence(seq,str,0,wmmLength,0);
    scores.push_back(logP);
  }
  double min, max;
  getMinAndMax(scores,min,max);
  Histogram<double> *hist=
    new Histogram<double>(min,max,numHistBins,pseudocount);
  hist->addCounts(scores);
  hist->normalize();
  return hist;
}
			    

			    
Histogram<double> *Application::buildHist(MarkovChain &mc,WMM &wmm)
{
  String str;
  Vector<double> scores;
  for(int i=0 ; i<numSamples ; ++i) {
    Sequence seq;
    mc.sample(seq,wmmLength,0);
    str=seq(alphabet);
    double logP=wmm.getLogP(seq,str,0);
    if(useRatios)
      logP-=mc.scoreSubsequence(seq,str,0,wmmLength,0);
    scores.push_back(logP);
  }
  double min, max;
  getMinAndMax(scores,min,max);
  Histogram<double> *hist=
    new Histogram<double>(min,max,numHistBins,pseudocount);
  hist->addCounts(scores);
  hist->normalize();
  return hist;
}



double Application::computeThreshold(Histogram<double> &foreground,
				   Histogram<double> &background)
{
  if(midpointRuleOK) {
    double b=background.getRightTailThreshold(0.0);
    double f=foreground.getLeftTailThreshold(0.0);
    if(f>b) return (f+b)/2.0; // separable -> return midpoint
  }
  switch(decisionType) 
    {
    case FP_RATE: return background.getRightTailThreshold(criticalValue);
    case FN_RATE: return foreground.getLeftTailThreshold(criticalValue);
    case MAX_FP_FN:
      return max(background.getRightTailThreshold(criticalValue),
		 foreground.getLeftTailThreshold(criticalValue));
    }
  throw "Internal error";
}



void Application::dumpHistograms(const Histogram<double> &foreground,
				 const Histogram<double> &background) 
{
  ofstream os(outfile.c_str());
  if(!os.good()) throw String("Cannot write to file ")+outfile;
  os<<background<<endl<<foreground<<endl;
}



DecisionType Application::getDecisionType(const String &s)
{
  if(s=="FP") return FP_RATE;
  if(s=="FN") return FN_RATE;
  if(s=="MAX") return MAX_FP_FN;
  throw String("Illegal option for -d: ")+s;
}



