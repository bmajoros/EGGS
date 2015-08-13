/****************************************************************
 Transitions.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/

#ifndef INCL_Transitions_H
#define INCL_Transitions_H

#include <iostream>
#include "BOOM/String.H"
#include "BOOM/Array2D.H"
#include "SignalType.H"

class Transitions
{
  BOOM::Array2D<double> matrix;
  void load(istream &);
  float optimism, intronOptimism;
public:
  /*Transitions(int numSignalTypes,const BOOM::String &filename,
    float optimism,float intronOptimism);*/
  Transitions(int numSignalTypes,istream &,float optimism,
	      float intronOptimism);
  double getLogP(SignalType from,SignalType to);
  SignalType sample(SignalType);
};


#endif
