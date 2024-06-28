// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Cor.pas' rev: 34.00 (Windows)

#ifndef Winapi_CorHPP
#define Winapi_CorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.CorError.hpp>
#include <Winapi.CorHdr.hpp>

//-- user supplied -----------------------------------------------------------
#include <cor.h>

namespace Winapi
{
namespace Cor
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef tagCOINITCOR TCoInitICor;

typedef tagCOINITEE TCoInitIEE;

typedef OSINFO *POSINFO;

typedef ASSEMBLYMETADATA *PASSEMBLYMETADATA;

typedef CorRegFlags TCorRegFlags;

typedef GUID TCVID;

typedef CVStruct TCVStruct;

typedef CeeSectionAttr TCeeSectionAttr;

typedef CeeSectionRelocType TCeeSectionRelocType;

typedef CeeSectionRelocExtra TCeeSectionRelocExtra;

typedef ICorModuleInitializeFlags TICorModuleInitializeFlags;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Cor */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_COR)
using namespace Winapi::Cor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_CorHPP
