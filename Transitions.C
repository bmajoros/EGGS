/****************************************************************
 Transitions.C
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 
 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
 ****************************************************************/
#include "Transitions.H"
#include <math.h>
#include <iostream>
#include <fstream>
#include "BOOM/Constants.H"
#include "BOOM/Random.H"
#include "genezilla.H"


Transitions::Transitions(int numSignalTypes,istream &is,float optimism,
			 float intronOptimism)
  : matrix(numSignalTypes,numSignalTypes), optimism(optimism),
    intronOptimism(intronOptimism)
{
  matrix.setAllTo(NEGATIVE_INFINITY);
  load(is);
}



void Transitions::load(istream &is)
{
  while(!is.eof())
    {
      BOOM::String line;
      getline(is,line);
      BOOM::Vector<BOOM::String> &fields=*line.getFields(" \t");
      if(fields.size()==5)
	{
	  SignalType from=stringToSignalType(fields[0]);
	  SignalType to=stringToSignalType(fields[2]);
	  double P=fields[4].asDouble();
	  matrix[from][to]=log(P);
	}
      else if(fields.size()>0)
	throw BOOM::String("syntax error in transition file: ")+line;
      delete &fields;
    }
}



double Transitions::getLogP(SignalType from,SignalType to)
{
  if(beginsCoding(to)) 
    return 
      optimism +
      matrix[static_cast<int>(from)][static_cast<int>(to)];
  else if(beginsIntron(to))
    return 
      intronOptimism +
      matrix[static_cast<int>(from)][static_cast<int>(to)];    
  else
    return 
      matrix[static_cast<int>(from)][static_cast<int>(to)];
}



SignalType Transitions::sample(SignalType from)
{
  double P=Random0to1();
  int N=numSignalTypes(), to;
  for(to=0 ; to<N ; ++to)
    {
      double logP=matrix[static_cast<int>(from)][to];  
      P-=exp(logP);
      if(P<=0 || to==N-1) break;
    }
  return SignalType(to);
}



