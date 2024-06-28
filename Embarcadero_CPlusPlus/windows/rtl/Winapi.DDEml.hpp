// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DDEml.pas' rev: 34.00 (Windows)

#ifndef Winapi_DdemlHPP
#define Winapi_DdemlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <ddeml.h>

namespace Winapi
{
namespace Ddeml
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef NativeUInt HConvList;

typedef NativeUInt HConv;

typedef NativeUInt HSZ;

typedef NativeUInt HDDEData;

typedef tagHSZPAIR *PHSZPair;

typedef tagHSZPAIR THSZPair;

typedef tagCONVCONTEXT *PConvContext;

typedef tagCONVCONTEXT TConvContext;

typedef tagCONVINFO *PConvInfo;

typedef tagCONVINFO TConvInfo;

typedef PFNCALLBACK TFNCallback;

typedef tagDDEML_MSG_HOOK_DATA TDdemlMsgHookData;

typedef tagMONMSGSTRUCT TMonMsgStruct;

typedef tagMONCBSTRUCT TMonCBStruct;

typedef tagMONHSZSTRUCTA TMonHSZStructA;

typedef tagMONHSZSTRUCTW TMonHSZStructW;

typedef tagMONHSZSTRUCTA TMonHSZStruct;

typedef tagMONERRSTRUCT *PMonErrStruct;

typedef tagMONERRSTRUCT TMonErrStruct;

typedef tagMONLINKSTRUCT *PMonLinkStruct;

typedef tagMONLINKSTRUCT TMonLinkStruct;

typedef tagMONCONVSTRUCT *PMonConvStruct;

typedef tagMONCONVSTRUCT TMonConvStruct;

//-- var, const, procedure ---------------------------------------------------
#define ddelib L"user32.dll"
}	/* namespace Ddeml */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DDEML)
using namespace Winapi::Ddeml;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DdemlHPP
