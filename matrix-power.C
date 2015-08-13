/****************************************************************
 matrix-power.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/GSL/Matrix.H"
using namespace std;
using namespace BOOM;


class Application
{
public:
  Application();
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



Application::Application()
  {
    // ctor
  }



int Application::main(int argc,char *argv[])
  {
    // Process command line
    CommandLine cmd(argc,argv,"");
    if(cmd.numArgs()!=2)
      throw String("matrix-power <*.matrix> <N>");
    String filename=cmd.arg(0);
    int N=cmd.arg(1).asInt();

    // Load matrix
    GSL::Matrix M(filename);
    if(M.getNumRows()!=M.getNumColumns())
        throw "Error: matrix is not square!";

    // Compute matrix power
    GSL::Matrix M_N;
    M.power(N,M_N);

    // Produce output
    cout<<M_N<<endl;

    return 0;
  }

