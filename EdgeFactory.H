/****************************************************************
 EdgeFactory.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com
 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_EdgeFactory_H
#define INCL_EdgeFactory_H
#include "Edge.H"

class EdgeFactory
{
public:
  virtual ~EdgeFactory() {}
  virtual PhasedEdge *newPhasedEdge(double scorePhase0,double scorePhase1,
				    double scorePhase2,SignalPtr left,
				    SignalPtr right);
  virtual NonPhasedEdge *newNonPhasedEdge(double score,SignalPtr left,
					  SignalPtr right);
};


#endif
