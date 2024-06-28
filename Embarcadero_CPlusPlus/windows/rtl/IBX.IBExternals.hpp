// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IBX.IBExternals.pas' rev: 34.00 (Windows)

#ifndef Ibx_IbexternalsHPP
#define Ibx_IbexternalsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ibx
{
namespace Ibexternals
{
//-- forward type declarations -----------------------------------------------
struct TCTimeStructure;
struct TISC_VARYING;
struct TBlob;
//-- type declarations -------------------------------------------------------
typedef int Int;

typedef unsigned UInt;

typedef int Long;

typedef unsigned ULong;

typedef short Short;

typedef System::Word UShort;

typedef float Float;

typedef System::Byte UChar;

typedef int ISC_LONG;

typedef unsigned UISC_LONG;

typedef __int64 ISC_INT64;

typedef short ISC_BOOLEAN;

typedef NativeInt ISC_STATUS;

typedef NativeUInt UISC_STATUS;

typedef void * Void;

typedef void * *ISC_BLOB_HANDLE;

typedef System::PByte *PPByte;

typedef short *PSmallInt;

typedef int *PInt;

typedef int *PInteger;

typedef short *PShort;

typedef System::Word *PUShort;

typedef int *PLong;

typedef unsigned *PULong;

typedef float *PFloat;

typedef System::Byte *PUChar;

typedef void * *PVoid;

typedef double *PDouble;

typedef int *PISC_LONG;

typedef unsigned *PUISC_LONG;

typedef NativeInt *PISC_STATUS;

typedef PISC_STATUS *PPISC_STATUS;

typedef NativeUInt *PUISC_STATUS;

struct DECLSPEC_DRECORD TCTimeStructure
{
public:
	int tm_sec;
	int tm_min;
	int tm_hour;
	int tm_mday;
	int tm_mon;
	int tm_year;
	int tm_wday;
	int tm_yday;
	int tm_isdst;
};


typedef TCTimeStructure *PCTimeStructure;

typedef TCTimeStructure TM;

typedef TCTimeStructure *PTM;

struct DECLSPEC_DRECORD TISC_VARYING
{
public:
	short strlen;
	System::StaticArray<System::Byte, 1> str;
};


typedef short __cdecl (*TISC_BlobGetSegment)(ISC_BLOB_HANDLE BlobHandle, System::PByte Buffer, System::Word BufferSize, System::Word &ResultLength);

typedef void __cdecl (*TISC_BlobPutSegment)(ISC_BLOB_HANDLE BlobHandle, System::PByte Buffer, System::Word BufferLength);

struct DECLSPEC_DRECORD TBlob
{
public:
	TISC_BlobGetSegment GetSegment;
	void * *BlobHandle;
	int SegmentCount;
	int MaxSegmentLength;
	int TotalSize;
	TISC_BlobPutSegment PutSegment;
};


typedef TBlob *PBlob;

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 dSun = System::Int8(0x1);
static const System::Int8 dMon = System::Int8(0x2);
static const System::Int8 dTue = System::Int8(0x3);
static const System::Int8 dWed = System::Int8(0x4);
static const System::Int8 dThu = System::Int8(0x5);
static const System::Int8 dFri = System::Int8(0x6);
static const System::Int8 dSat = System::Int8(0x7);
static const System::Int8 dJan = System::Int8(0x1);
static const System::Int8 dFeb = System::Int8(0x2);
static const System::Int8 dMar = System::Int8(0x3);
static const System::Int8 dApr = System::Int8(0x4);
static const System::Int8 dMay = System::Int8(0x5);
static const System::Int8 dJun = System::Int8(0x6);
static const System::Int8 dJul = System::Int8(0x7);
static const System::Int8 dAug = System::Int8(0x8);
static const System::Int8 dSep = System::Int8(0x9);
static const System::Int8 dOct = System::Int8(0xa);
static const System::Int8 dNov = System::Int8(0xb);
static const System::Int8 dDec = System::Int8(0xc);
static const System::Word cYearOffset = System::Word(0x76c);
static const System::Int8 cSun = System::Int8(0x0);
static const System::Int8 cMon = System::Int8(0x1);
static const System::Int8 cTue = System::Int8(0x2);
static const System::Int8 cWed = System::Int8(0x3);
static const System::Int8 cThu = System::Int8(0x4);
static const System::Int8 cFri = System::Int8(0x5);
static const System::Int8 cSat = System::Int8(0x6);
static const System::Int8 cJan = System::Int8(0x0);
static const System::Int8 cFeb = System::Int8(0x1);
static const System::Int8 cMar = System::Int8(0x2);
static const System::Int8 cApr = System::Int8(0x3);
static const System::Int8 cMay = System::Int8(0x4);
static const System::Int8 cJun = System::Int8(0x5);
static const System::Int8 cJul = System::Int8(0x6);
static const System::Int8 cAug = System::Int8(0x7);
static const System::Int8 cSep = System::Int8(0x8);
static const System::Int8 cOct = System::Int8(0x9);
static const System::Int8 cNov = System::Int8(0xa);
static const System::Int8 cDec = System::Int8(0xb);
extern DELPHI_PACKAGE void __fastcall InitializeTCTimeStructure(TCTimeStructure &tm_record);
}	/* namespace Ibexternals */
}	/* namespace Ibx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX_IBEXTERNALS)
using namespace Ibx::Ibexternals;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IBX)
using namespace Ibx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Ibx_IbexternalsHPP
