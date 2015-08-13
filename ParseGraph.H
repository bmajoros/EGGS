/****************************************************************
 ParseGraph.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_ParseGraph_H
#define INCL_ParseGraph_H
#include <iostream>
#include "BOOM/Stack.H"
#include "BOOM/Array1D.H"
#include "Signal.H"
#include "genezilla.H"

class GeneZilla;

#ifdef EXPLICIT_GRAPHS
class ParseGraph
{
  BOOM::Vector<SignalPtr> *vertices;
  BOOM::Set<Edge*> &getEdgesOut();
  GeneZilla &genezilla;
public:
  ParseGraph(GeneZilla &);
  virtual ~ParseGraph();
  void addVertex(SignalPtr);
  int numVertices();
  SignalPtr getIthVertex(int);
  BOOM::Stack<SignalPtr> *findOptimalPath(double &parseScore);
  void deleteVertices(BOOM::Array1D<bool> &deleteIfTrue);
  void setVertexIndices();
  int findSignal(SignalType,int consensusPos); // -1 if not found
  int findFirstSignalAfter(int pos); // -1 if no signals follow pos
  int countLeftTermini();
  int countRightTermini();
  void toGFF(ostream &) const;
  int countEdges() const;
};

ostream &operator<<(const ParseGraph &,ostream &);

#endif

#endif
