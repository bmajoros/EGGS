/****************************************************************
 Accumulator.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/

#ifndef INCL_Accumulator_H
#define INCL_Accumulator_H

#include "Propagator.H"

class Accumulator : public Propagator
{
public:
  inline Accumulator(int position);
};


inline Accumulator::Accumulator(int position) 
  : Propagator(position) 
{
  double *sc=scores;
  *sc=*(sc+1)=*(sc+2)=0;
}


#endif
