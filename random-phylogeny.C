/****************************************************************
 random-phylogeny.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include "BOOM/String.H"
#include "BOOM/CommandLine.H"
#include "BOOM/Vector.H"
#include "BOOM/Random.H"
#include "../PhyLib/Phylogeny.H"
using namespace std;
using namespace BOOM;


class Application
{
public:
  Application();
  int main(int argc,char *argv[]);
private:
  Phylogeny *generate(int numLeaves);
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
    if(cmd.numArgs()!=1)
      throw String("random-phylogeny <num-leaves>");
    int numLeaves=cmd.arg(0).asInt();

    randomize();
    Phylogeny *phylogeny=generate(numLeaves);
    cout<<*phylogeny<<endl;

    return 0;
  }



Phylogeny *Application::generate(int numLeaves)
{
  Vector<PhylogenyNode*> pool;

  // Generate the initial pool, which constists entirely of leaves
  for(int i=0 ; i<numLeaves ; ++i)
    {
      String name=String("species_")+(i+1);
      LeafNode *node=new LeafNode;
      node->setName(name);
      pool.push_back(node);
    }

  // Iteratively combine random pairs of nodes from the pool, until
  // only one node remains (the root)
  int nodeNum=1;
  while(pool.size()>1)
    {
      String name=String("ancestor_")+(nodeNum++);
      int n=pool.size();
      int i=RandomNumber(n), j=RandomNumber(n);
      if(j==i) j=(j+1)%n;
      InternalNode *node=new InternalNode(pool[i],pool[j]);
      node->setName(name);
      node->setLeftDistance(Random0to1());
      node->setRightDistance(Random0to1());
      pool.cut(i);
      if(j>i) --j;
      pool.cut(j);
      pool.push_back(node);
    }

  // Create a phylogeny object
  PhylogenyNode *root=pool[0];
  Phylogeny *phylogeny=new Phylogeny(root);
  return phylogeny;
}


