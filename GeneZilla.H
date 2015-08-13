/****************************************************************
 GeneZilla
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the open-source Gnu General Public License (GPL) version 3
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_GeneZilla_H
#include <math.h>
#include <iostream>
#include <fstream>
#include <typeinfo>
#include "BOOM/CommandLine.H"
#include "BOOM/DnaAlphabet.H"
#include "BOOM/Map.H"
#include "BOOM/Stack.H"
#include "BOOM/Constants.H"
#include "BOOM/Time.H"
#include "BOOM/Array1D.H"
#include "BOOM/GffReader.H"
#include "genezilla.H"
#include "SignalSensor.H"
#include "SignalQueue.H"
#include "SignalTypeProperties.H"
#include "NoncodingQueue.H"
#include "IntronQueue.H"
#include "EmpiricalDistribution.H"
#include "GeometricDistribution.H"
#include "Transitions.H"
#include "IsochoreFile.H"
#include "GffReader.H"
#include "TopologyLoader.H"
#include "Edge.H"
#include "GarbageCollector.H"
#include "EdgeFactory.H"
#include "GffPathFromParseGraph.H"
#include "IsochoreTable.H"
#include "IsochoreInterval.H"


#ifdef EXPLICIT_GRAPHS
#include "ParseGraph.H"
#endif

#ifdef REPORT_MEMORY_USAGE
#include "BOOM/MemoryProfiler.H"
#endif



/****************************************************************
                        class GeneZilla
 ****************************************************************/

class GeneZilla
{
public:

/****************************************************************
                        PUBLIC MEMBERS
 ****************************************************************/

  GeneZilla(const BOOM::String &PROGRAM_NAME,const BOOM::String &VERSION,
	   EdgeFactory &,int &transcriptId);
  virtual ~GeneZilla();
  void sample(int minLength,double gcContent,
	      BOOM::String isochoreFilename,int contigId,
	      BOOM::String outGffFile,BOOM::String outFastaFile);
  void sampleTFBSs(int minLength,ContentSensor *intergenicSensor,
		   SignalSensor *TFBSsensor,int contigId,
		   BOOM::String outGffFile,BOOM::String outFastaFile,
		   int meanIntergenicLen);
  int main(int argc,char *argv[]);
  virtual BOOM::Stack<SignalPtr> * processChunk(const Sequence &seq,
				      const BOOM::String &seqStr,
				      const BOOM::String &isoFilename,
				      const BOOM::String &substrateId);
  void loadIsochoreBoundaries(const BOOM::String &);
  void loadCpGislands(const BOOM::String &);
  int mapPhaseBack(int phase,SignalPtr right,SignalPtr left);
  DiscreteDistribution &getDistribution(ContentType);
  Transitions *getTransitionProbs();
  BOOM::Array1D<double> &getIntergenicSums()      {return intergenicSums;}
  const BOOM::String &getSubstrateId()               {return substrateId;}
  int getSeqLen()                                       {return seqLen;}
  static ContentType exonTypeToContentType(ExonType,Strand);
  ContentSensor &getContentSensor(ContentType);
  SignalSensor &getSignalSensor(SignalType);
  BOOM::StringMap<char> *getStopCodonConsensuses();
  GarbageCollector &getGC()                   {return garbageCollector;}
  double scoreExon(SignalPtr left,SignalPtr right,int phase,
		   ContentType &);

#ifdef EXPLICIT_GRAPHS
  ParseGraph &getParseGraph();
  ParseGraph &parse(const BOOM::String &seqFile,const BOOM::String &isoFile,
		    float &gcContent);
  ParseGraph &parse(const BOOM::String &seqFile,const BOOM::String &isoFile,
		    const Sequence *&,const BOOM::String *&seqString,
		    float &gcContent);
  ParseGraph &parse(const BOOM::String &isoFile,const Sequence &,
		    const BOOM::String &seqString,float &gcContent);
  int numRightTermini() {return rightTermini.size();}
  BOOM::Vector<SignalPtr> *getPathFromGff(BOOM::Vector<
					     BOOM::GffTranscript*> &,
					  Sequence &,
					  const BOOM::String &seqStr,
					  BOOM::Vector<BOOL> &found);
#endif

#ifdef FORCE_SPECIFIC_SIGNALS
  void forceSignalCoords(BOOM::Vector<int> &signalCoords);
#endif

/****************************************************************
                     PRIVATE & PROTECTED MEMBERS
 ****************************************************************/

protected:
#ifdef FORCE_SPECIFIC_SIGNALS
  BOOM::Set<int> forcedSignalCoords;
#endif

#ifdef EXPLICIT_GRAPHS
  BOOM::Vector<SignalPtr> leftTermini, rightTermini;
  ParseGraph parseGraph;

  void buildParseGraph(const Sequence &seq,const BOOM::String &str);
#endif
  
  const Sequence *seq;
  const BOOM::String *seqStr;
  IsochoreTable isochores;
  Isochore *isochore;     // the currently active isochore
  //bool invertSignalProbs; // use P(signal|score), not P(sequence|signal)
  int &transcriptId;
  GarbageCollector garbageCollector;
  EdgeFactory &edgeFactory;
  BOOM::String PROGRAM_NAME, VERSION;
  int seqLen;
  BOOM::String substrateId;
  BOOM::Vector<SignalQueue*> signalQueues;
  BOOM::Vector<SignalQueue*> forwardCodingQueues, reverseCodingQueues;
  BOOM::Map<ContentType,SignalQueue*> contentToQueue;
  bool recentlyEclipsedPhases[3];
  BOOM::Array1D<double> intergenicSums; // for printing exon scores in GFF
  float gcContent;
  bool modelCpGislands;
  BOOM::Map< BOOM::String,BOOM::Vector<IsochoreInterval> > 
    isochoreIntervals;
  IsochoreInterval nextIsochoreInterval;
  int nextIsochoreIndex;
  BOOM::Regex GCregex;

  virtual BOOM::Stack<SignalPtr> * mainAlgorithm(const Sequence &,
					       const BOOM::String &);
  void computeIntergenicSums(const Sequence &,const BOOM::String &,
			     const char *);
  float getGCcontent(const BOOM::String &);
  void instantiateLeftTermini();
  BOOM::Stack<SignalPtr> *instantiateRightTermini(const BOOM::String &,
						int seqLen,
						double &parseScore);
  virtual void updateAccumulators(const Sequence &,const BOOM::String &,
				  int pos,Symbol,char);
  /*inline*/ void linkBack(const BOOM::String &,SignalPtr newSignal);
  inline void selectPredecessors(int newConsPos,SignalQueue &queue,
				 ContentType contentType,Strand strand,
				 double bestScore[3],SignalPtr bestPred[3],
				 SignalType toType,
				 const BOOM::String &substrate,
				 SignalPtr);
  inline void selectIntergenicPred(int newConsPos,SignalQueue &queue,
				   Strand strand,double bestScore[3],
				   SignalPtr bestPred[3],ContentType,
				   SignalType toType,SignalPtr);
  virtual void selectCodingPred(int newConsPos,SignalQueue &queue,
			       Strand strand,double bestScore[3],
			       SignalPtr bestPred[3],ContentType,
			       SignalType toType,SignalPtr);
  inline void selectIntronPred(int newConsPos,SignalQueue &queue,
			       Strand strand,
			       double bestScore[3],SignalPtr bestPred[3],
			       ContentType,SignalType toType,
			       const BOOM::String &substrate,SignalPtr);
  void enqueue(SignalPtr);
  void handleStopCodons(const BOOM::String &,int pos);
  void terminateForwardORFs(int position);
  void terminateReverseORFs(int position);
  void loadTransProbs(const BOOM::String &transFile,float optimism,
		      float intronOptimism);
  BOOM::Stack<SignalPtr> *traceBack(SignalPtr rightTerminus,int phase);
  void generateGff(BOOM::Stack<SignalPtr> *path,int seqLen,
		   double parseScore);
  void generateGff(BOOM::Stack<SignalPtr> *path,int seqLen,
		   double parseScore,BOOM::String outfile,
		   BOOM::String &seqStr);
  double scoreIntronPhases(SignalType predType,SignalType toType,
			   int oldPhase,int newPhase);
  int getPhase(SignalPtr);
  void observeRecentStopCodons(const BOOM::String &,SignalPtr);
  void processIsochoreFile(const BOOM::String &filename,float gcContent);
  void createQueue(ContentType);
  void switchIsochore(float gcContent,int pos);
  void resetAccumulatorPositions();
  void crossIsochoreBoundary(int pos);
  int updatePhase(int phase,ContentType,int contentLen,int nextState,
		  SignalSensor &);
  void adjustContentLen(int &contentLen,SignalType,int &newPhase);
  int getSignalPhase(SignalSensor &sensor,int newPhase);
  void removeStopCodons(BOOM::String &seqStr,int begin,int end,int phase,
			Strand strand);
  void removeStraddlingStops(BOOM::String &seqStr,int phase,int thisPos,
			     int nextPos,Strand strand);
};


#endif
