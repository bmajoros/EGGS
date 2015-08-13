/****************************************************************
 chunk-maf.C
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
    void chunk(Vector<MultiAlignment*> &,int maxChunkSize,
               const String &filename);
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
  {
    // ctor
  }



int Application::main(int argc,char *argv[])
  {
    // Process command line
    CommandLine cmd(argc,argv,"");
    if(cmd.numArgs()!=3)
      throw String("chunk-maf <in.maf> <max-chunk-size> <out.maf>");
    String inMafName=cmd.arg(0);
    int maxChunkSize=cmd.arg(1).asInt();
    String outMafName=cmd.arg(2);

    // Initialization
    alphabet=DnaAlphabet::global;

    // Load the alignments
    Vector<MultiAlignment*> alignments;
    MultiAlignment::loadMAF(inMafName,alignments);
    //alignment->toupper();

    // Break into chunks
    chunk(alignments,maxChunkSize,outMafName);

    return 0;
  }



void Application::chunk(Vector<MultiAlignment*> &alignments,int maxChunkSize,
                        const String &filename)
{
    ofstream os(filename.c_str());
    os<<"##maf"<<endl;
    int n=alignments.size();
    for(int i=0 ; i<n ; ++i)
    {
        MultiAlignment &alignment=*alignments[i];
        int L=alignment.getLength();
        alignment.printSlice(os,0,L,maxChunkSize);
    }
}


