/****************************************************************
 DiscreteDistribution.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/

#ifndef INCL_DiscreteDistribution_H
#define INCL_DiscreteDistribution_H

enum DistributionType
  {
    EMPIRICAL_DISTRIBUTION,
    GEOMETRIC_DISTRIBUTION
  };

class DiscreteDistribution
{
public:
  DiscreteDistribution() {}
  virtual ~DiscreteDistribution() {}
  virtual double getLogP(unsigned)=0;
  virtual void useLogLikelihoodRatios()=0;
  virtual int sample()=0;
};


#endif
