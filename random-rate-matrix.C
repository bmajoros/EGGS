/****************************************************************
 random-rate-matrix.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include <fstream>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/DnaAlphabet.H"
#include "BOOM/GSL/Matrix.H"
#include "BOOM/GSL/Vector.H"
#include "BOOM/Random.H"
#include "BOOM/FastaReader.H"
#include "BOOM/Sequence.H"
#include "../PhyLib/RateMatrixType.H"
#include "../PhyLib/NthOrdRateMatrix.H"
using namespace std;
using namespace BOOM;


class Application
{
    void processRefGenome(const String &refGenomeFile,
                          Array1D<double> &equilibriumFreqs);
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
    CommandLine cmd(argc,argv,"r");
    if(cmd.numArgs()!=4)
      throw String(
"random-rate-matrix <order> <type> <out.matrix> <reference-genome.fasta>\n\
\n\
where <type> is one of {JC,FEL,KIM,HKY,REV}\n\
      -r = generate random equilibrium frequencies\n\
\n");
    int order=cmd.arg(0).asInt();
    String matrixTypeStr=cmd.arg(1);
    String outfile=cmd.arg(2);
    String refGenomeFile=cmd.arg(3);
    RateMatrixType matrixType=rateMatrixTypeFromString(matrixTypeStr);
    MolecularSequenceType seqType=DNA; // ###

    // Generate nucleotide equilibrium frequencies
    randomize();
    Array1D<double> equilibriumFreqs(5);
    if(cmd.option('r'))
    {
        double sum=0;
        for(int i=0 ; i<4 ; ++i) 
            sum+=(equilibriumFreqs[i]=RandomFloat(0.3,0.7));
        for(int i=0 ; i<4 ; ++i) equilibriumFreqs[i]/=sum;
        equilibriumFreqs[4]=equilibriumFreqs[3];
        equilibriumFreqs[3]=0;
    }
    else processRefGenome(refGenomeFile,equilibriumFreqs);
    if(matrixType!=MT_JC && matrixType!=MT_KIM)
    {
        cout<<"Equilibrium frequencies: ";
        for(int i=0 ; i<5 ; ++i) 
            if(i!=3)
                cout<<equilibriumFreqs[i]<<"  ";
        cout<<endl;
    }
    
    // Construct rate matrix
    NthOrdRateMatrix *M=
        NthOrdRateMatrix::random(seqType,order,matrixType,equilibriumFreqs);
    
    // Store rate matrix in outfile
    M->save(outfile);

    return 0;
  }



void Application::processRefGenome(const String &refGenomeFile,
                                   Array1D<double> &equilibriumFreqs)
{
    equilibriumFreqs.setAllTo(0.0);
    FastaReader reader(refGenomeFile);
    String defline, sequence;
    while(reader.nextSequence(defline,sequence))
    {
        Sequence seq(sequence,DnaAlphabet::global);
        int len=seq.getLength();
        for(int i=0 ; i<len ; ++i)
            ++equilibriumFreqs[seq[i]];
    }
    double sum=0.0;
    Symbol N=DnaAlphabet::global.lookup('N');
    for(Symbol s=0 ; s<5 ; ++s)
        if(s!=N)
            sum+=equilibriumFreqs[s];
    for(Symbol s=0 ; s<5 ; ++s)
        if(s==N)
            equilibriumFreqs[s]=0;
        else
            equilibriumFreqs[s]/=sum;
}


