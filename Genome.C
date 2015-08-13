/****************************************************************
 Genome.C
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include <iostream>
#include "Genome.H"
#include "BOOM/DnaAlphabet.H"
#include "BOOM/GffReader.H"
#include "BOOM/FastaReader.H"
#include "BOOM/VectorSorter.H"
using namespace std;
using namespace BOOM;


Genome::Genome()
{
}



Genome::Genome(const String &gffFile,const String &fastaFile,
	       const Set<String> &keepFeatureTypes)
{
  FastaReader reader(fastaFile);
  String defline, seqStr;
  reader.nextSequence(defline,seqStr);
  Sequence seq(seqStr,DnaAlphabet::global);
  reader.close();
  load(gffFile,seq,keepFeatureTypes);
}



Genome::Genome(const String &gffFile,const Sequence &seq,
	       const Set<String> &keepFeatureTypes)
{
  load(gffFile,seq,keepFeatureTypes);
}



Genome::~Genome()
{
  int n=features.size();
  for(int i=0 ; i<n ; ++i)
    delete features[i];
}



void Genome::addFeature(GenomeFeature *feature)
{
  features.push_back(feature);
}



int Genome::numFeatures()
{
  return features.size();
}



GenomeFeature *Genome::getIthFeature(int i)
{
  return features[i];
}



void Genome::sortFeatures()
{
  GenomeFeatureComparator cmp;
  VectorSorter<GenomeFeature*> sorter(features,cmp);
  sorter.sortAscendInPlace();
}



void Genome::load(const String &gffFile,const Sequence &substrate,
		  const Set<String> &keepFeatureTypes)
{
  int L=substrate.getLength();
  GffReader reader(gffFile);
  GffFeature *feature;
  while(feature=reader.nextFeature())
    {
      String type=feature->getFeatureType();
      if(keepFeatureTypes.isMember(type))
	{
	  int begin=feature->getBegin();
	  int end=feature->getEnd();
	  int phase=feature->getFrame();
	  Strand strand=feature->getStrand();
	  GenomeFeature *feature=new GenomeFeature(begin,end,phase,type,
						   strand);
	  feature->initSeq(substrate);
	  features.push_back(feature);
	}

      delete feature;
    }
  fillGaps(substrate);
  sortFeatures();
}



void Genome::fillGaps(const Sequence &substrate)
{
  int L=substrate.getLength();
  int n=features.size();
  //if(n==0) throw "No features were retained!  Check your *.config file";
  GenomeFeature *f;
  if(n==0)
  {
      f=new GenomeFeature(0,L,0,"intergenic",EITHER_STRAND);
      features.insertByIndex(f,0);
      f->initSeq(substrate);
      return;
  }
  for(int i=0 ; i<n-1 ; ++i)
    {
      GenomeFeature &left=*features[i], &right=*features[i+1];
      int begin=left.getEnd(), end=right.getBegin();
      if(begin>=end) continue;
      switch(left.getContentType())
	{
	case INITIAL_EXON:
	case INTERNAL_EXON:
	  f=new GenomeFeature(begin,end,0,"intron",FORWARD_STRAND);
	  features.insertByIndex(f,i+1);
	  f->initSeq(substrate);
	  ++n;
	  break;
	case NEG_FINAL_EXON:
	case NEG_INTERNAL_EXON:
	  f=new GenomeFeature(begin,end,0,"intron",REVERSE_STRAND);
	  features.insertByIndex(f,i+1);
	  f->initSeq(substrate);
	  ++n;
	  break;
	case INTRON:
	case NEG_INTRON:
	case INTERGENIC:
	  break;
	case TFBS:
	case NEG_TFBS:
	default:
	  f=new GenomeFeature(begin,end,0,"intergenic",EITHER_STRAND);
	  features.insertByIndex(f,i+1);
	  f->initSeq(substrate);
	  ++n;
	  break;
	}
    }
  GenomeFeature *left=features[0];
  int end=left->getBegin();
  if(end>0)
    {
      f=new GenomeFeature(0,end,0,"intergenic",EITHER_STRAND);
      features.insertByIndex(f,0);
      f->initSeq(substrate);
    }
  GenomeFeature *right=features[features.size()-1];
  int begin=right->getEnd();
  if(begin<L)
    {
      f=new GenomeFeature(begin,L,0,"intergenic",EITHER_STRAND);
      features.push_back(f);
      f->initSeq(substrate);
    }
}



int Genome::getLength()
{
    int len=0;
    int n=features.size();
    for(int i=0 ; i<n ; ++i)
        len+=features[i]->getSeq().getLength();
    return len;
}

