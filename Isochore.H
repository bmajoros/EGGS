/****************************************************************
 Isochore.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_Isochore_H
#define INCL_Isochore_H
#include "BOOM/Vector.H"
#include "BOOM/Map.H"
#include "BOOM/ConfigFile.H"
#include "BOOM/String.H"
#include "Transitions.H"
#include "SignalSensor.H"
#include "ContentSensor.H"
#include "SignalType.H"
#include "ContentType.H"
#include "DiscreteDistribution.H"
#include "EmpiricalDistribution.H"
#include "SignalComparator.H"

/****************************************************************
 This class encapsulates everything about the gene finder that
 could be isochore-specific (i.e., all models and parameters that
 can depend on local GC-content).
 ****************************************************************/
struct Isochore
{
  float maximumGC;
  bool useSignalThresholds;
  double signalThresholdMultiplier;
  double pI, pN, pF, pT;
  double threePrimeOptimism, fivePrimeOptimism;
  BOOM::String name;
  BOOM::Vector<SignalSensor*> signalSensors;
  BOOM::Vector<ContentSensor*> contentSensors;
  Transitions *transitionProbs;
  BOOM::Map<ContentType,ContentSensor*> contentToSensor;
  BOOM::Map<SignalType,SignalSensor*> signalTypeToSensor;
  BOOM::Map<ContentType,DiscreteDistribution*> contentToDistribution;
  SignalSensor *stopCodonSensor, *negStopCodonSensor;
  BOOM::Map<ContentType,BOOM::Array1D<SinglePhaseComparator*>*> 
    intronComparators;
  BOOM::Map<ContentType,NoncodingComparator*> noncodingComparators;
  bool interpolateHistograms;

  // temporary:
  BOOM::Map<BOOM::String,ContentSensor*> uniqContentSensors;//by filename
  BOOM::Map<BOOM::String,EmpiricalDistribution*> uniqDistributions;// ditto
};


#endif
