/****************************************************************
 IsochoreFile.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com
 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#ifndef INCL_IsochoreFile_H
#define INCL_IsochoreFile_H
#include "genezilla.H"
#include "BOOM/Regex.H"
#include "BOOM/ConfigFile.H"

class IsochoreFile
{
  static BOOM::Regex lineRegex;
public:
  static BOOM::ConfigFile *parse(const BOOM::String &filename,
				 double gcContent,
				 BOOM::String &gffMessage);
};


#endif
