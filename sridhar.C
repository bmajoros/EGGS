
// sridhar.C

#include <iostream>
#include <math.h>
#include "BOOM/CommandLine.H"
#include "BOOM/FastaReader.H"
#include "BOOM/DnaAlphabet.H"
#include "ContentSensor.H"
using namespace std;

Alphabet alphabet; 

class Application
{
public:
  int main(int argc,char *argv[]);
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



int Application::main(int argc,char *argv[])
  {
    // Process command line
    BOOM::CommandLine cmd(argc,argv,"");
    if(cmd.numArgs()!=3)
      throw string("sridhar <model1> <model2> <*.fasta>");
    BOOM::String modelName1=cmd.arg(0);
    BOOM::String modelName2=cmd.arg(1);
    BOOM::String fastaFile=cmd.arg(2);

    // Load models
    ContentSensor *model1=ContentSensor::load(modelName1);
    ContentSensor *model2=ContentSensor::load(modelName2);

    // Process all sequences in multi-fasta file
    const int phase=0;
    alphabet=DnaAlphabet::global;
    BOOM::FastaReader reader(fastaFile,alphabet);
    BOOM::String defline, seqString, id, remainder;
    while(reader.nextSequence(defline,seqString))
      {
	BOOM::FastaReader::parseDefline(defline,id,remainder);
	cout<<id<<": ";

	Sequence seq(seqString,alphabet);
	int length=seq.getLength();
	double score1=model1->scoreSubsequence(seq,seqString,0,length,phase);
	double score2=model2->scoreSubsequence(seq,seqString,0,length,phase);
	double ratio=score1-score2;
	
	cout<<" score1: "<<score1<<" score2: "<<score2;
	cout<<" log(s1/s2): "<<ratio<<endl;
      }

    return 0;
  }

