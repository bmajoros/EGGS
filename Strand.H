/**************************************************************
 Strand.H
 Bill Majoros - bmajoros@duke.edu / martiandna@gmail.com

 This software is governed by the Gnu General Public License (GPL) version 3 
 (see www.opensource.org).
***************************************************************/

#ifndef INCL_strand_H
#define INCL_strand_H

typedef char Strand;
inline Strand complement(Strand s) {return s=='-' ? '+' : '-';}

#define PLUS_STRAND '+'
#define MINUS_STRAND '-'
#define FORWARD_STRAND PLUS_STRAND
#define REVERSE_STRAND MINUS_STRAND
#define EITHER_STRAND '.'
#define NO_STRAND '.'

#endif

