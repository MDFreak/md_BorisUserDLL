/***************************************************************************
  Diese Datei stellt Umwandlungsfunktionen für Fließpunktzahlen 
  zur Verfügung. 

  10 Byte Fließpunktzahlen <---> 8 Byte Fließpunktzahlen:

  double WFNum2double(WFNum num);
  WFNum  double2WFNum(double d);
  
  Hintergrund:
  Unter dem Simulationssystem BORIS wird immer mit maximaler Genauigkeit
  gerechnet. Der Fließpunktprozessor arbeitet seit dem 8087 intern
  standardmäßig in dem TEMPREAL-Format, das 10 Byte lange Fließpunktzahlen
  bezeichnet. Die IEEE-754 definiert jedoch nur 8 Byte lange, sodass sich
  viele Programmiersprachen hierauf beschränken (was eigentlich auch reicht).
  Wie angedeutet ist BORIS ist in einer Programmiersprache geschrieben,
  die diese 10 Byte langen Fließkommazahlen unterstützt. Und um nun auch in 
  anderen Sprachen User-DLLs schreiben zu können, bieten wir Ihnen diese 
  Bibliothek an.

  Literatur:
  Das Assembler-Buch; Grundlagen und Hochsprachenoptimierung; 
  Trutz Eyke Podschun. Bonn: Addison-Wesley-Longman, 1999
  (Professionelle Programmierung) ISBN 3-8273-1513-1
*****************************************************************************/
#ifndef WFNumber
#define WFNumber WFNumber
#include <float.h>

#pragma pack(1)


#if (LDBL_MANT_DIG == 64 && ! defined __MINGW32__)

#define WFNum long double
#define WFNum2double(a) a
#define double2WFNum(a) a

#else
#define LONG_DOUBLE_PROBLEM

#ifdef _MSC_VER             // Microsoft VC
#  define DEF_INLINE _inline
#  pragma managed(push,off)
#elif  BORLANDC             // Borland C 
#  define DEF_INLINE
#else                       // others
#  define DEF_INLINE
#endif


typedef struct{
	char d[10];
}WFNum;

#ifdef __MINGW32__
typedef union{
  char v[12];
  long double d;
}GCCWFNum;
#endif

DEF_INLINE double WFNum2double(const WFNum mem)
{
  double d;
#ifdef __MINGW32__
  GCCWFNum n;
  int i;
  for(i=0; i<sizeof(WFNum); n.v[i++]=mem.d[i]);
  n.v[10]=0;
  n.v[12]=0;
  d=n.d;
#else
  _asm{
      fld TBYTE PTR mem
      fstp QWORD Ptr d
  }
#endif
  return d;
}

DEF_INLINE WFNum double2WFNum(const double d)
{
  WFNum mem;
#ifdef __MINGW32__
  GCCWFNum n;
  int i;
  n.d=d;
  for(i=0; i<sizeof(WFNum); mem.d[i++]=n.v[i]);
#else
  _asm{
      fld QWORD PTR d
      fstp TBYTE PTR mem
  }
#endif
  return mem;
}
#endif

#ifdef _MSC_VER             // Microsoft VC
#  pragma managed(pop)
#elif  BORLANDC             // Borland C 
#  define DEF_INLINE
#else                       // others
#  define DEF_INLINE
#endif

#pragma pack()

#endif
