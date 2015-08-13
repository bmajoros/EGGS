/****************************************************************
 GenomeFeature.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include "GenomeFeature.H"
using namespace std;
using namespace BOOM;


GenomeFeature::GenomeFeature()
{
}



GenomeFeature::GenomeFeature(int begin,int end,int phase,
			     const String &featureType,Strand strand)
  : begin(begin),
    end(end),
    phase(phase),
    featureType(featureType),
    strand(strand)
{
  String s=featureType;
  s.toupper();
  if(s=="INTRON" && strand==REVERSE_STRAND) s="NEG-INTRON";
  else if(s=="TFBS" && strand==REVERSE_STRAND) s="NEG-TFBS";
  contentType=strToContentType(s,strand);
  if(strand==REVERSE_STRAND) contentType=::reverseComplement(contentType);
}



void GenomeFeature::initSeq(const Sequence &from)
{
  from.getSubsequence(begin,end-begin,seq);
}



int GenomeFeature::getBegin() const
{
  return begin;
}



int GenomeFeature::getEnd() const
{
  return end;
}



const String &GenomeFeature::getFeatureType() const
{
  return featureType;
}



Sequence &GenomeFeature::getSeq()
{
  return seq;
}



void GenomeFeature::setSeq(const Sequence &s)
{
  seq=s;
}



Strand GenomeFeature::getStrand() const
{
  return strand;
}



ContentType GenomeFeature::getContentType() const
{
  return contentType;
}



int GenomeFeature::getPhase() const
{
  return phase;
}



bool GenomeFeature::isCoding() const
{
  return ::isCoding(contentType);
}



void GenomeFeature::changeFeatureType(String f)
{
  featureType=f;
  f.toupper();
  if(f=="INTRON" && strand==REVERSE_STRAND) f="NEG-INTRON";
  else if(f=="TFBS" && strand==REVERSE_STRAND) f="NEG-TFBS";
  contentType=strToContentType(f,strand);
  if(strand==REVERSE_STRAND) contentType=::reverseComplement(contentType);
}

