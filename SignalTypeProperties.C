
// SignalTypeProperties.C

#include "SignalTypeProperties.H"
#include <iostream>


SignalTypeProperties SignalTypeProperties::global;


SignalTypeProperties::SignalTypeProperties()
{
}



SignalTypeProperties &SignalTypeProperties::allowPhase(SignalType t,
						       int phase)
{
  info[t].allowablePhases+=phase;
  return *this;
}



SignalTypeProperties &SignalTypeProperties::belongTo(SignalType t,
						     ContentType queueType)
{
  SignalTypeInfo &record=info[t];
  BOOM::Set<ContentType> &s=record.belongsTo;
  if(!s.isMember(queueType))
  {
    record.propagatorIndexMap[queueType]=s.size();
    s+=queueType;
  }
  return *this;
}



SignalTypeProperties &SignalTypeProperties::linkTo(SignalType t,
						   ContentType queueType)
{
  info[t].linksBackTo+=queueType;
  return *this;
}



void SignalTypeProperties::setStrand(SignalType t,Strand s)
{
  info[t].strand=s;
}



void SignalTypeProperties::setConsensusCoding(SignalType t,bool b)
{
  info[t].codingConsensus=b;
}
