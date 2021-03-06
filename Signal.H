/****************************************************************
 Signal.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_Signal_H
#define INCL_Signal_H
#include <iostream>
#include "BOOM/List.H"
#include "genezilla.H"
#include "SignalType.H"
class Edge;
class SignalSensor;
class Propagator;
class GarbageCollector;

class Signal : public PointedTo
{
#ifdef EXPLICIT_GRAPHS
  BOOM::Set<Edge*> edgesIn;
  BOOM::Set<Edge*> edgesOut;
  int index; // index into graph's vertex array
#endif

  BOOM::SmartPointer<Signal> predecessors[3]; // optimal predecessors, one in each frame
  int contextWindowPosition;
  Propagator *propagators[2];
  SignalSensor &sensor;
  double signalScore; //score for the entire context window (not just cons.)
  double inductiveScores[3]; // includes signalScore!

  void initializePropagators(double signalScore);
public:
  Signal(int contextWindowPosition,double signalScore,SignalSensor &,
	 GarbageCollector &);
  virtual ~Signal();
  Propagator &getPropagator(ContentType);
  void setPredecessor(int phase,BOOM::SmartPointer<Signal>);
  BOOM::SmartPointer<Signal> getPredecessor(int phase);
  int getContextWindowPosition();
  int getConsensusPosition() const;
  virtual int getContextWindowLength();
  virtual int getConsensusLength();
  int frameOfBaseFollowingConsensus();
  int posOfBaseFollowingConsensus();
  BOOM::Set<ContentType> &belongsInWhichQueues();
  BOOM::Set<ContentType> &linksBackToWhichQueues();
  Strand getStrand();
  SignalType getSignalType() const;
  double contextWindowScore(); // signal score, not the inductive score
  SignalSensor &getSensor();
  double &getInductiveScore(int phase);
  double priorInductiveScore(int phase); // not including signal score
  double posteriorInductiveScore(int phase); // including signal score
  double precedingFeatureScore(int phase); // =content+length+trans scores
  bool isLeftTerminus();
  void printOn(ostream &) const;

#ifdef EXPLICIT_GRAPHS
  bool isRightTerminus();
  void addEdgeIn(Edge *);
  void addEdgeOut(Edge *);
  BOOM::Set<Edge*> &getEdgesIn();
  BOOM::Set<Edge*> &getEdgesOut();
  void dropEdgeIn(Edge*);
  void dropEdgeOut(Edge*);
  inline int getIndex() {return index;}
  inline void setIndex(int x) {index=x;}
  Edge *findEdgeInFrom(BOOM::SmartPointer<Signal> pred);
#endif
};

ostream &operator<<(ostream &,const Signal &);

#endif
