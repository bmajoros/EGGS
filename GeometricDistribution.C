/****************************************************************
 GeometricDistribution.C
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include "BOOM/Random.H"
#include "GeometricDistribution.H"
#include <iostream>
#include <math.h>
using namespace std;

GeometricDistribution::GeometricDistribution(int meanLength)
  : usingRatios(false)
{
  double q=1.0/meanLength;
  logQ=log(q);
  logOneMinusQ=log(1-q);
  logMean=getLogP(meanLength);
}



double GeometricDistribution::getLogP(unsigned len)
{
  // log[ (1-q)^(len-1) * q ] == (len-1)*log(1-q)+log(q)

  return (len-1)*logOneMinusQ+logQ;//-(usingRatios ? logMean : 0);
}



void GeometricDistribution::useLogLikelihoodRatios()
{
  usingRatios=true;
}



int GeometricDistribution::sample()
{
  double P=BOOM::Random0to1();
  double len=-log(1-P)/exp(logQ);
  return int(len+5.0/9);
}


