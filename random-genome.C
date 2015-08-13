/****************************************************************
 random-genome.C
 bmajoros@duke.edu

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include "GeneZilla.H"
#include "genezilla.H"
#include "EdgeFactory.H"
#include "BOOM/FastaReader.H"
#include "BOOM/Constants.H"
#include "BOOM/Random.H"
using namespace std;

#ifdef EXPLICIT_GRAPHS
//#error Please edit the file genezilla.H, comment out the definition of EXPLICIT_GRAPHS, issue a "make clean", and recompile this project
#endif

#ifdef FORCE_SPECIFIC_SIGNALS
#error Please edit the file genezilla.H, comment out the definition of FORCE_SPECIFIC_SIGNALS, issue a "make clean", and recompile this project
#endif

static const char *PROGRAM_NAME="random-genome";
static const char *VERSION="1.0";
Alphabet alphabet;
int frame; // ### CAUTION: this is required by older code; to be removed

void AppMain(int argc,char *argv[]);

int main(int argc,char *argv[])
  {
    try
      {
	AppMain(argc,argv);
      }
    catch(const char *p)
      {
	cerr << p << endl;
	return -1;
      }
    catch(const string &msg)
      {
	cerr << msg.c_str() << endl;
	return -1;
      }
    catch(const exception &e)
      {
	cerr << "STL exception caught in main:\n" << e.what() << endl;
	return -1;
      }
    catch(...)
      {
	cerr << "Unknown exception caught in main" << endl;
	return -1;
      }
    return 0;
  }



void AppMain(int argc,char *argv[])
{
  // Process command line
  BOOM::CommandLine cmd(argc,argv,"");
  if(cmd.numArgs()!=6)
    throw BOOM::String(
     "\nrandom-genome <*.iso> <length> <out.gff> <out.fasta> <ID> <GC%>\n");
  BOOM::String isochoreFilename=cmd.arg(0);
  int minLength=cmd.arg(1).asInt();
  BOOM::String outGffFile=cmd.arg(2);
  BOOM::String outFastaFile=cmd.arg(3);
  int contigId=cmd.arg(4).asInt();
  float gcContent=cmd.arg(5).asFloat();
  if(gcContent<0 || gcContent>1) throw "GC% must be between 0 and 1";
  alphabet=DnaAlphabet::global;

  // Generate the sequence
  randomize();
  int transcriptId=-1;
  EdgeFactory edgeFactory;
  GeneZilla genezilla(PROGRAM_NAME,VERSION,edgeFactory,transcriptId);
  genezilla.sample(minLength,gcContent,isochoreFilename,contigId,outGffFile,
		   outFastaFile);
}



