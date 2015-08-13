/****************************************************************
 convert-from-JASPAR.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include <fstream>
#include <math.h>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/File.H"
#include "BOOM/Array2D.H"
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
    if(cmd.numArgs()!=3)
      throw String(
"convert-from-JASPAR <JASPAR-matrix> <pseudocount> <out.wmm>");
    String infile=cmd.arg(0);
    double pseudocount=cmd.arg(1).asFloat();
    
    // Load JASPAR matrix
    File file(infile);
    Array2D<float> matrix;
    bool first=true;
    int nucIndex=0, L=0;
    while(!file.eof()) {
      String line=file.readLine();
      Vector<String> &fields=*line.getFields();
      int n=fields.size();
      if(n>0) {
	if(first) { matrix.resize(4,n); L=n; first=false; }
	for(int i=0 ; i<n ; ++i) 
	  matrix[nucIndex][i]=fields[i].asFloat()+pseudocount;
	++nucIndex;
      }
      delete &fields;
    }

    // Convert to WMM
    double sum=0.0;
    for(int i=0 ; i<4 ; ++i) sum+=matrix[i][0];
    for(int i=0 ; i<4 ; ++i)
      for(int j=0 ; j<L ; ++j) matrix[i][j]/=sum;
    
    // Produce output
    ofstream os(cmd.arg(2).c_str());
    os<<"WMM\nPROMOTER\n0 "<<L<<" 4"<<endl;
    os<<L<<" 0 0 +"<<endl;
    double totalBits=0.0, maxH=log2(4), maxBits=0.0;
    for(int j=0 ; j<L ; ++j) {
      double H=0.0;
      for(int i=0 ; i<4 ; ++i) {
	double P=matrix[i][j];
	if(P>0)	H-=P*log2(P);
	os<<log(P)<<"\t";
      }
      double IC=maxH-H;
      totalBits+=IC;
      maxBits+=maxH;
      os<<endl;
    }
    cout<<totalBits<<" bits (max="<<maxBits<<" bits over "<<L
	<<" positions)"<<endl;

    return 0;
  }

