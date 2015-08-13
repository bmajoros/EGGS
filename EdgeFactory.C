/****************************************************************
 EdgeFactory.C
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com
 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include "EdgeFactory.H"
#include <iostream>
#include "Signal.H"


PhasedEdge *EdgeFactory::newPhasedEdge(double scorePhase0,double scorePhase1,
				       double scorePhase2,SignalPtr left,
				       SignalPtr right)
{
  return new PhasedEdge(scorePhase0,scorePhase1,scorePhase2,left,right);
}



NonPhasedEdge *EdgeFactory::newNonPhasedEdge(double score,SignalPtr left,
					     SignalPtr right)
{
  return new NonPhasedEdge(score,left,right);
}



