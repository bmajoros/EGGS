/****************************************************************
 GenomeFeature.H
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_GenomeFeature_H
#define INCL_GenomeFeature_H
#include <iostream>
#include "BOOM/Comparator.H"
#include "BOOM/String.H"
#include "BOOM/Sequence.H"
#include "Strand.H"
#include "ContentType.H"
using namespace std;
using namespace BOOM;


class GenomeFeature
{
  int begin, end, phase;
  String featureType;
  Sequence seq;
  Strand strand;
  ContentType contentType;
public:
  GenomeFeature();
  GenomeFeature(int begin,int end,int phase,const String &featureType,
		Strand);
  void initSeq(const Sequence &from);
  void setSeq(const Sequence &);
  int getBegin() const;
  int getEnd() const;
  void changeEnd(int newEnd) {end=newEnd;}
  const String &getFeatureType() const;
  void changeFeatureType(String);
  Sequence &getSeq();
  Strand getStrand() const;
  ContentType getContentType() const;
  int getPhase() const;
  bool isCoding() const;
};


class GenomeFeatureComparator : public Comparator<GenomeFeature*>
{
public:
  virtual bool equal(GenomeFeature *&a,GenomeFeature *&b)
  {return a->getBegin()==b->getBegin();}
  virtual bool greater(GenomeFeature *&a,GenomeFeature *&b)
  {return a->getBegin()>b->getBegin();}
  virtual bool less(GenomeFeature *&a,GenomeFeature *&b)
  {return a->getBegin()<b->getBegin();}
};

#endif

