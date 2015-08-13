/**************************************************************
ModelBuilder.H
Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

Open source under the Gnu General Public License (GPL) version 3.
***************************************************************/

#ifndef INCL_ModelBuilder_H
#define INCL_ModelBuilder_H

#include "BOOM/String.H"
#include "BOOM/Map.H"
#include "BOOM/Vector.H"
#include "BOOM/Alphabet.H"
#include "BOOM/Sequence.H"
#include "SignalSensor.H"
#include "ContentSensor.H"
#include "ModelType.H"
#include "SignalType.H"
#include "TrainingSequence.H"

class ModelBuilder
{
  Alphabet &alphabet;
  int minSampleSize, order, windowSize;
  int branchContextLength; // only for branch point models
  int branchOrder;         // only for branch point models
  GarbageCollector &gc;
public:
  ModelBuilder(GarbageCollector &,Alphabet &,int minSampleSize=175,
	       int order=5,int windowSize=5);
  SignalSensor *buildSignalSensor(ModelType,BOOM::Vector<TrainingSequence*> &,
				  SignalType,int consensusOffset,
				  int consensusLength,float pseudocount=0.0);
  ContentSensor *buildContentSensor(ModelType,
				    BOOM::Vector<TrainingSequence*> &,
				    ContentType);
  void changeOrder(int order);
  void changeWindowSize(int windowSize);
  void changeMinSampleSize(int minSampleSize);
  void changeBranchContextLength(int);
  void changeBranchOrder(int);
};


#endif

