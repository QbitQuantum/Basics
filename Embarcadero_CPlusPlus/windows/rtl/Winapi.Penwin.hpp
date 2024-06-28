// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.PenWin.pas' rev: 34.00 (Windows)

#ifndef Winapi_PenwinHPP
#define Winapi_PenwinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.MMSystem.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "penwin.h"

namespace Winapi
{
namespace Penwin
{
//-- forward type declarations -----------------------------------------------
struct tagOEMPENPACKET;
struct tagSYE;
struct tagRC;
//-- type declarations -------------------------------------------------------
typedef int *PALC;

typedef void * POEM;

typedef int *PSYV;

typedef NativeUInt *PHPENDATA;

typedef ENUMPROC TFNEnumProc;

typedef LPDF *PFNLPDF;

typedef LPDF TFNLPDF;

typedef RCYIELDPROC TFNRCYieldProc;

typedef tagABSTIME *PAbsTime;

typedef tagABSTIME TAbsTime;

typedef tagCTLINITHEDIT *PCtlInitHEdit;

typedef tagCTLINITHEDIT TCtlInitHEdit;

typedef tagBOXLAYOUT *PBoxLayout;

typedef tagBOXLAYOUT TBoxLayout;

typedef tagIMECOLORS *PIMEColors;

typedef tagIMECOLORS TIMEColors;

typedef tagCTLINITBEDIT *PCtlInitBEdit;

typedef tagCTLINITBEDIT TCtlInitBEdit;

typedef tagBOXEDITINFO *PBoxEditInfo;

typedef tagBOXEDITINFO TBoxEditInfo;

typedef tagRECTOFS *PRectOfs;

typedef tagRECTOFS TRectOfs;

typedef tagPENDATAHEADER *PPenDataHeader;

typedef tagPENDATAHEADER TPenDataHeader;

typedef tagSTROKEINFO *PStrokeInfo;

typedef tagSTROKEINFO TStrokeInfo;

typedef tagPENTIP *PPenTip;

typedef tagPENTIP TPenTip;

typedef ANIMATEPROC TFNAnimateProc;

typedef tagANIMATEINFO *PAnimateInfo;

typedef tagANIMATEINFO TAnimateInfo;

typedef tagOEMPENINFO *POEMPenInfo;

typedef tagOEMPENINFO TOEMPenInfo;

typedef tagPENPACKET *PPenPacket;

typedef tagPENPACKET TPenPacket;

typedef tagOEMPENPACKET *POEMPenPacket;

struct DECLSPEC_DRECORD tagOEMPENPACKET
{
public:
	unsigned wTabletX;
	unsigned wTabletY;
	unsigned wPDK;
	System::StaticArray<unsigned, 6> rgwOemData;
	unsigned dwTime;
};


typedef tagOEMPENPACKET TOEMPenPacket;

typedef tagPENINFO *PPenInfo;

typedef tagPENINFO TPenInfo;

typedef tagCALBSTRUCT *PCalbStruct;

typedef tagCALBSTRUCT TCalbStruct;

typedef LPFNRAWHOOK TFNRawHook;

typedef int *PHRC;

typedef int *PHRCRESULT;

typedef int *PHWL;

typedef HRCRESULTHOOKPROC TFNHRCResultHookProc;

typedef tagINTERVAL *PInterval;

typedef tagINTERVAL TInterval;

typedef tagBOXRESULTS *PBoxResults;

typedef tagBOXRESULTS TBoxResults;

typedef tagGUIDE *PGuide;

typedef tagGUIDE TGuide;

typedef tagCTLINITIEDIT *PCtlInitIEdit;

typedef tagCTLINITIEDIT TCtlInitIEdit;

typedef tagPDEVENT *PPDEvent;

typedef tagPDEVENT TPDEvent;

typedef tagSTRKFMT *PStrkFmt;

typedef tagSTRKFMT TStrkFmt;

typedef tagPCMINFO *PPCMInfo;

typedef tagPCMINFO TPCMInfo;

typedef tagINKINGINFO *PInkingInfo;

typedef tagINKINGINFO TInkingInfo;

struct DECLSPEC_DRECORD tagSYE
{
public:
	int syv;
	int lRecogVal;
	int cl;
	int iSyc;
};


typedef tagSYE TSYE;

typedef tagRC *PRC;

struct DECLSPEC_DRECORD tagRC
{
public:
	NativeUInt hrec;
	HWND hwnd;
	unsigned wEventRef;
	unsigned wRcPreferences;
	int lRcOptions;
	RCYIELDPROC lpfnYield;
	System::StaticArray<System::Byte, 32> lpUser;
	unsigned wCountry;
	unsigned wIntlPreferences;
	System::StaticArray<char, 44> lpLanguage;
	System::StaticArray<PFNLPDF, 16> rglpdf;
	unsigned wTryDictionary;
	int clErrorLevel;
	int alc;
	int alcPriority;
	System::StaticArray<System::Byte, 32> rgbfAlc;
	unsigned wResultMode;
	unsigned wTimeOut;
	int lPcm;
	System::Types::TRect rectBound;
	System::Types::TRect rectExclude;
	tagGUIDE guide;
	unsigned wRcOrient;
	unsigned wRcDirect;
	int nInkWidth;
	unsigned rgbInk;
	unsigned dwAppParam;
	unsigned dwDictParam;
	unsigned dwRecognizer;
	System::StaticArray<unsigned, 8> rgwReserved;
};


typedef tagRC TRC;

typedef tagTARGET *PTarget;

typedef tagTARGET TTarget;

typedef tagTARGINFO *PTargInfo;

typedef tagTARGINFO TTargInfo;

typedef tagINPPARAMS *PInpParams;

typedef tagINPPARAMS TInpParams;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Penwin */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_PENWIN)
using namespace Winapi::Penwin;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_PenwinHPP
