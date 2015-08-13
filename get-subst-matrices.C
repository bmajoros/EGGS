/****************************************************************
 get-subst-matrices.C
 william.majoros@duke.edu

 Infers substitution (not rate) matrices for each of the branches
 in a phylogeny, from a multiple alignment.

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
    Phylogeny *phylogeny;

    void inferMatrices();
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
    if(cmd.numArgs()!=2)
      throw String("get-subst-matrices <*.maf> <*.phylogeny>");
    String mafFilename=cmd.arg(0);
    String phyloFilename=cmd.arg(1);

    // Initialization
    alphabet=DnaAlphabet::global;

   // Load the alignments
    Vector<MultiAlignment*> alignments;
    MultiAlignment::loadMAF(mafFilename,alignments);
    alignment=MultiAlignment::combine(alignments,true);
    alignment->toupper();

    // Load the phylogeny
    phylogeny=new Phylogeny(phyloFilename);
    phylogeny->attachAlignment(*alignment);

    // Infer the matrices
    inferMatrices();

    return 0;
  }



struct SMVisitor : public TreeVisitor
{
public:
    MultiAlignment &A;
    int numNodes, numAlpha;
    Alphabet &alpha;
    AlphabetMap &am;
    Symbol N;
    
    SMVisitor(int numNodes,int numAlpha,Alphabet &alpha,AlphabetMap &am,
              MultiAlignment &A)
        : A(A), numNodes(numNodes), numAlpha(numAlpha), alpha(alpha),
          N(alpha.lookup('N')), am(am) {}
    virtual void processNode(LeafNode &u) {}
    virtual void processNode(InternalNode &u) 
        {
            processBranch(u,*u.getLeft());
            processBranch(u,*u.getRight());
        }
    virtual void processNode(RootNode &u)
        {
            processBranch(u,*u.getChild());
        }
    void processBranch(PhylogenyNode &parent,PhylogenyNode &child)
        {
            SubstitutionMatrix M(alpha,am);
            M.peek().setAllTo(0.0);
            int parentID=parent.getID(), childID=child.getID();
            AlignmentTrack &parentTrack=A.getIthTrack(parentID);
            AlignmentTrack &childTrack=A.getIthTrack(childID);
            const String &parentSeq=parentTrack.getSeq();
            const String &childSeq=childTrack.getSeq();
            int L=parentSeq.length();
            for(int i=0 ; i<L ; ++i)
            {
                char parentChar=parentSeq[i], childChar=childSeq[i];
                if(!alpha.isDefined(parentChar) || !alpha.isDefined(childChar))
                    continue;
                Symbol parentSymbol=alphabet.lookup(parentChar);
                Symbol childSymbol=alphabet.lookup(childChar);
                if(parentSymbol==N || childSymbol==N) continue;
                ++M(parentSymbol,childSymbol);
            }
            for(Symbol s=0 ; s<numAlpha ; ++s)
            {
                if(s==N) continue;
                double sum=0.0;
                for(Symbol t=0 ; t<numAlpha ; ++t)
                    if(t!=N)
                        sum+=M(s,t);
                for(Symbol t=0 ; t<numAlpha ; ++t)
                    if(t!=N)
                        M(s,t)/=sum;
            }
            cout<<parent.getName()<<"->"<<child.getName()<<":"<<endl;
            cout<<M<<endl;
        }
};



void Application::inferMatrices()
{
    int numNodes=phylogeny->getNumNodes();
    int numAlpha=alphabet.size();
    DropNMapping alphabetMap;
    SMVisitor visitor(numNodes,numAlpha,alphabet,alphabetMap,*alignment);
    phylogeny->postorderTraversal(visitor);
}

