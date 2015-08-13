/**************************************************************************
 WWAM.H : Windowed Weight Array Matrix (WAM w/probabilities averaged over
                                        a small window)
 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_WWAM_H
#define INCL_WWAM_H
#include "BOOM/String.H"
#include "BOOM/Vector.H"
#include "MarkovChain.H"
#include "SignalSensor.H"
#include "TrainingSequence.H"
#include "GarbageCollector.H"

class WWAM : public SignalSensor
{
  BOOM::Vector<MarkovChain *> matrix;

  void load(istream &);
public:
  WWAM(GarbageCollector &,const WWAM &, bool reverseComplement=false);
  WWAM(GarbageCollector &,BOOM::String &filename);
  WWAM(GarbageCollector &,istream &);
  WWAM(GarbageCollector &,BOOM::Vector<TrainingSequence*> &, int order, 
       int minSampleSize,SignalType,int consensusOffset,
       int consensusLength); 
       // training constructor
  virtual ~WWAM();
  virtual bool save(const BOOM::String &filename);
  virtual bool save(ostream &os);
  double getLogP(const Sequence &,const BOOM::String &,int begin);
  virtual SignalSensor *reverseComplement();
  virtual void useLogOdds(SignalSensor &nullModel);
  virtual void useLogOdds_anonymous(ContentSensor &nullModel);
  virtual void sample(Sequence &appendToThis);
};

#endif
