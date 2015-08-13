
#include "SignalType.H"
#include "BOOM/Map.H"
#include "BOOM/String.H"

static BOOM::Map<BOOM::String,SignalType> typeNames;
TypeNamesInitializer TypeNamesInitializer::initializer;


TypeNamesInitializer::TypeNamesInitializer()
{
  typeNames["ATG"]=ATG;
  typeNames["TAG"]=TAG;
  typeNames["GT"]=GT;
  typeNames["AG"]=AG;
  typeNames["PROMOTER"]=PROM;
  typeNames["POLYA"]=POLYA;
  typeNames["-ATG"]=NEG_ATG;
  typeNames["-TAG"]=NEG_TAG;
  typeNames["-GT"]=NEG_GT;
  typeNames["-AG"]=NEG_AG;
  typeNames["-PROMOTER"]=NEG_PROM;
  typeNames["-POLYA"]=NEG_POLYA;

  typeNames["GT0"]=GT0;
  typeNames["GT1"]=GT1;
  typeNames["GT2"]=GT2;
  typeNames["AG0"]=AG0;
  typeNames["AG1"]=AG1;
  typeNames["AG2"]=AG2;
  typeNames["-GT0"]=NEG_GT0;
  typeNames["-GT1"]=NEG_GT1;
  typeNames["-GT2"]=NEG_GT2;
  typeNames["-AG0"]=NEG_AG0;
  typeNames["-AG1"]=NEG_AG1;
  typeNames["-AG2"]=NEG_AG2;
}



SignalType stringToSignalType(const BOOM::String &s)
{
  if(!typeNames.isDefined(s))
    throw BOOM::String("undefined SignalType: ")+s;
  return typeNames[s];
}



BOOM::String signalTypeToString(SignalType t)
{
  switch(t)
    {
    case ATG:         return "ATG";
    case TAG:         return "TAG";
    case GT:          return "GT"; 
    case AG:          return "AG"; 
    case PROM:        return "PROMOTER";
    case POLYA:       return "POLYA";   
    case NEG_ATG:     return "-ATG";    
    case NEG_TAG:     return "-TAG";    
    case NEG_GT:      return "-GT";     
    case NEG_AG:      return "-AG";     
    case NEG_PROM:    return "-PROMOTER";
    case NEG_POLYA:   return "-POLYA";  
    }
  throw "signalTypeToString()";
}



BOOM::String signalTypeToName(SignalType t)
{
  switch(t)
    {
    case ATG:         return "start-codon";
    case TAG:         return "stop-codon";
    case GT:          return "donor"; 
    case AG:          return "acceptor"; 
    case PROM:        return "promoter";
    case POLYA:       return "poly-A";   
    case NEG_ATG:     return "start-codon";    
    case NEG_TAG:     return "stop-codon";    
    case NEG_GT:      return "donor";     
    case NEG_AG:      return "acceptor";     
    case NEG_PROM:    return "promoter";
    case NEG_POLYA:   return "poly-A";  
    }
  throw "signalTypeToName()";
}



ostream &operator<<(ostream &os,SignalType t)
{
  switch(t)
    {
    case ATG:         os << "ATG";          break;
    case TAG:         os << "TAG";          break;
    case GT:          os << "GT";           break;
    case AG:          os << "AG";           break;
    case PROM:        os << "PROMOTER";     break;
    case POLYA:       os << "POLYA";        break;
    case NEG_ATG:     os << "-ATG";         break;
    case NEG_TAG:     os << "-TAG";         break;
    case NEG_GT:      os << "-GT";          break;
    case NEG_AG:      os << "-AG";          break;
    case NEG_PROM:    os << "-PROMOTER";    break;
    case NEG_POLYA:   os << "-POLYA";       break;
    default: throw BOOM::String("INVALID SIGNAL TYPE: ")+int(t);
    }
  return os;
}



istream &operator>>(istream &is,SignalType &t)
{
  BOOM::String buf;
  is >> buf;
  if(!typeNames.isDefined(buf)) 
    throw BOOM::String(" undefined SignalType: ")+buf;
  t=typeNames[buf];
  return is;
}



SignalType reverseComplement(SignalType t)
{
  switch(t)
    {
    case ATG:         return NEG_ATG;
    case TAG:         return NEG_TAG;
    case GT:          return NEG_GT;
    case AG:          return NEG_AG;
    case PROM:        return NEG_PROM;
    case POLYA:       return NEG_POLYA;
    case NEG_ATG:     return ATG;
    case NEG_TAG:     return TAG;
    case NEG_GT:      return GT;
    case NEG_AG:      return AG;
    case NEG_PROM:    return PROM;
    case NEG_POLYA:   return POLYA;
    }
}



Strand getStrand(SignalType t)
{
  switch(t)
    {
    case ATG:         return FORWARD_STRAND;
    case TAG:         return FORWARD_STRAND;
    case GT:          return FORWARD_STRAND;
    case AG:          return FORWARD_STRAND;
    case PROM:        return FORWARD_STRAND;
    case POLYA:       return FORWARD_STRAND;
    case NEG_ATG:     return REVERSE_STRAND;
    case NEG_TAG:     return REVERSE_STRAND;
    case NEG_GT:      return REVERSE_STRAND;
    case NEG_AG:      return REVERSE_STRAND;
    case NEG_PROM:    return REVERSE_STRAND;
    case NEG_POLYA:   return REVERSE_STRAND;
    }
}



bool endsCoding(SignalType t)
{
  switch(t)
    {
    case TAG:
    case GT:
    case NEG_ATG:
    case NEG_AG: 
      return true;
    }
  return false;
}


bool beginsCoding(SignalType t)
{
  switch(t)
    {
    case ATG: 
    case AG:
    case NEG_TAG:
    case NEG_GT:
      return true;
    }
  return false;
}


bool beginsIntron(SignalType t)
{
  switch(t)
    {
    case GT:
    case NEG_AG: 
      return true;
    }
  return false;
}


