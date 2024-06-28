// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.OleCtl.pas' rev: 34.00 (Windows)

#ifndef Winapi_OlectlHPP
#define Winapi_OlectlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Ole2.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

#include <ocidl.h>
#include <olectl.h>


namespace Winapi
{
namespace Olectl
{
//-- forward type declarations -----------------------------------------------
struct TCAGUID;
struct TCAPOleStr;
struct TCALongint;
//-- type declarations -------------------------------------------------------
typedef Winapi::Windows::PTextMetricW PTextMetricOle;

typedef tagTEXTMETRICW TTextMetricOle;

typedef int TOleColor;

enum DECLSPEC_DENUM OLE_TRISTATE : unsigned int { triUnchecked, triChecked, triGray };

typedef HRESULT __stdcall (*TDLLRegisterServer)();

typedef HRESULT __stdcall (*TDLLUnregisterServer)();

typedef tagPOINTFX *PPointF;

typedef tagPOINTFX TPointF;

typedef tagCONTROLINFO *PControlInfo;

typedef tagCONTROLINFO TControlInfo;

typedef tagCONNECTDATA *PConnectData;

typedef tagCONNECTDATA TConnectData;

typedef tagLICINFO *PLicInfo;

typedef tagLICINFO TLicInfo;

typedef System::StaticArray<Winapi::Ole2::TGUID, 65536> TGUIDList;

typedef TGUIDList *PGUIDList;

typedef TCAGUID *PCAGUID;

struct DECLSPEC_DRECORD TCAGUID
{
public:
	int cElems;
	TGUIDList *pElems;
};


typedef TCAPOleStr *PCAPOleStr;

struct DECLSPEC_DRECORD TCAPOleStr
{
public:
	int cElems;
	Winapi::Ole2::TOleStrList *pElems;
};


typedef System::StaticArray<int, 65536> TLongintList;

typedef TLongintList *PLongintList;

typedef TCALongint *PCALongint;

struct DECLSPEC_DRECORD TCALongint
{
public:
	int cElems;
	TLongintList *pElems;
};


typedef tagOCPFIPARAMS *POCPFIParams;

typedef tagOCPFIPARAMS TOCPFIParams;

typedef tagPROPPAGEINFO *PPropPageInfo;

typedef tagPROPPAGEINFO TPropPageInfo;

typedef tagFONTDESC *PFontDesc;

typedef tagFONTDESC TFontDesc;

typedef tagPICTDESC *PPictDesc;

typedef tagPICTDESC TPictDesc;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_CFontPropPage;
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_CColorPropPage;
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_CPicturePropPage;
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_PersistPropset;
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_ConvertVBX;
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_StdFont;
extern DELPHI_PACKAGE Winapi::Ole2::TGUID CLSID_StdPicture;
}	/* namespace Olectl */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_OLECTL)
using namespace Winapi::Olectl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_OlectlHPP
