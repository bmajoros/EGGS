/****************************************************************
 subset-maf-tracks.C
 william.majoros@duke.edu

 Drops unwanted tracks from a multi-alignment in MAF format.

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
    CommandLine cmd(argc,argv,"z");
    if(cmd.numArgs()!=3)
      throw String("\nsubset-maf-tracks [z] <in.maf> <track1,track2,track3,...> <out.maf>\n   where -z = keep the zeroth track also, regardless of its name\n");
    String inMafName=cmd.arg(0);
    String trackList=cmd.arg(1);
    String outMafName=cmd.arg(2);
    bool keepZeroth=cmd.option('z');

    alphabet=DnaAlphabet::global();
    Vector<String> &trackNames=*trackList.getFields(",");
    int n=trackNames.size();
    ifstream is(inMafName.c_str());
    ofstream os(outMafName.c_str());
    if(!os.good()) throw String("can't write to file ")+outMafName;
    if(!is.good()) throw String("Can't open file ")+inMafName;
    while(!is.eof())
    {
      MultiAlignment *oldMAF=MultiAlignment::nextAlignmentFromMAF(is);
      if(!oldMAF) break;
      MultiAlignment newMAF;
      bool keptZeroth=false;
      if(keepZeroth) {
	AlignmentTrack &track=oldMAF->getIthTrack(0);
	oldMAF->releaseTrack(0);
	newMAF.addTrack(&track);
	keptZeroth=true;
      }
      for(int i=0 ; i<n ; ++i)
        {
	  const String &name=trackNames[i];
	  AlignmentTrack &track=oldMAF->findOrCreateTrack(name);//oldMAF->getTrackByName(name);
	  if(track.getID()==0 && keptZeroth) continue;
	  oldMAF->releaseTrack(track.getID());
	  newMAF.addTrack(&track);
        }
      delete oldMAF;
      newMAF.ensureAllSameLength();
      os<<newMAF<<endl;
    }
    os.close();
    
    return 0;
  }



