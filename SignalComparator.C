/****************************************************************
 SignalComparator.C
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com
 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include "SignalComparator.H"
#include "Propagator.H"
#include <iostream>
using namespace std;


//==============================================================
//               SinglePhaseComparator methods
//==============================================================

SinglePhaseComparator::SinglePhaseComparator(int phase,
					     ContentType contentType,
					     DiscreteDistribution &distr)
  : phase(phase),
    contentType(contentType),
    distr(distr)
{
}



double SinglePhaseComparator::getLengthPenalty(SignalPtr signal,
					       int position)
{
  int length=position-signal->posOfBaseFollowingConsensus();
  double lengthPenalty=distr.getLogP(length);
  return lengthPenalty;
}



void SinglePhaseComparator::getScores(SignalPtr a,SignalPtr b,
				      double &scoreA,double &scoreB)
{
  Propagator &propA=a->getPropagator(contentType);
  Propagator &propB=b->getPropagator(contentType);

  int pos=max(propA.getPosition(),propB.getPosition())+1;

  scoreA=propA[phase]+getLengthPenalty(a,pos);
  scoreB=propB[phase]+getLengthPenalty(b,pos);
}



bool SinglePhaseComparator::equal(SignalPtr &a,SignalPtr &b)
{
  double scoreA, scoreB;
  getScores(a,b,scoreA,scoreB);
  return scoreA==scoreB;
}



bool SinglePhaseComparator::greater(SignalPtr &a,SignalPtr &b)
{
  double scoreA, scoreB;
  getScores(a,b,scoreA,scoreB);
  return scoreA>scoreB;
}



bool SinglePhaseComparator::less(SignalPtr &a,SignalPtr &b)
{
  double scoreA, scoreB;
  getScores(a,b,scoreA,scoreB);
  return scoreA<scoreB;
}




//=================================================================
//                  NoncodingComparator methods
//=================================================================

NoncodingComparator::NoncodingComparator(ContentType contentType,
					 DiscreteDistribution &distr)
  : SinglePhaseComparator(-1,contentType,distr)
{
}



void NoncodingComparator::getScores(SignalPtr a,SignalPtr b,
				    double &scoreA,
				    double &scoreB)
{
  Propagator &propA=a->getPropagator(contentType);
  Propagator &propB=b->getPropagator(contentType);

  int pos=propA.getPosition()+1;
    // both propagators are at the same position!

  int phaseA=(a->getStrand()==FORWARD_STRAND ? 0 : 2);
  int phaseB=(b->getStrand()==FORWARD_STRAND ? 0 : 2);

  scoreA=propA[phaseA]+getLengthPenalty(a,pos);
  scoreB=propB[phaseB]+getLengthPenalty(b,pos);
}

