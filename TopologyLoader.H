/****************************************************************
 TopologyLoader.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/

#ifndef INCL_TopologyLoader_H
#define INCL_TopologyLoader_H
#include "BOOM/Regex.H"
#include "SignalTypeProperties.H"

class TopologyLoader
{
  static BOOM::Regex transitionRegex;      // "GT -> AG : INTRON"
  static BOOM::Regex phaseRegex;           // "GT has phase 0"
  static BOOM::Regex strandRegex;          // "GT strand +"
  static BOOM::Regex consensusCodingRegex; // "ATG consensus coding"
  static BOOM::Regex commentRegex;         // "# comment"
  static BOOM::Regex blankLineRegex;
public:
  static SignalTypeProperties &load(const BOOM::String &filename);
};


#endif
