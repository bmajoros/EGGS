/****************************************************************
 Genome.H
 william.majoros@duke.edu

 This is open-source software, governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_Genome_H
#define INCL_Genome_H
#include <iostream>
#include "BOOM/String.H"
#include "BOOM/Vector.H"
#include "BOOM/Set.H"
#include "GenomeFeature.H"
using namespace std;
using namespace BOOM;


class Genome
{
    Vector<GenomeFeature*> features;
    void load(const String &gffFile,const Sequence &substrate,
              const Set<String> &keepFeatureTypes);
    void fillGaps(const Sequence &);
public:
    Genome();
    Genome(const String &gffFile,const String &fastaFile,
           const Set<String> &keepFeatureTypes);
    Genome(const String &gffFile,const Sequence &,
           const Set<String> &keepFeatureTypes);
    virtual ~Genome();
    void addFeature(GenomeFeature *);
    int numFeatures();
    GenomeFeature *getIthFeature(int i);
    void sortFeatures();
    int getLength();
};

#endif

