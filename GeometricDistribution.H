/****************************************************************
 GeometricDistribution.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/

#ifndef INCL_GeometricDistribution_H
#define INCL_GeometricDistribution_H

#include "DiscreteDistribution.H"

class GeometricDistribution : public DiscreteDistribution
{
  double logQ, logOneMinusQ, logMean;
  bool usingRatios;
public:
  GeometricDistribution(int meanLength);
  virtual double getLogP(unsigned);
  virtual void useLogLikelihoodRatios();
  virtual int sample();
};


#endif
