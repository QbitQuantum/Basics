// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.ShLwApi.pas' rev: 34.00 (Windows)

#ifndef Winapi_ShlwapiHPP
#define Winapi_ShlwapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.ShlObj.hpp>

//-- user supplied -----------------------------------------------------------

#if !defined(_INC_SHLWAPI)
 #include <shlwapi.h>
 #if defined(StrToInt) && !defined(NO_UNDEF_StrToInt)
  #undef StrToInt // Conflicts /w System::Sysutils::StrToInt
 #endif
#endif


namespace Winapi
{
namespace Shlwapi
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned TUrlIs;

typedef unsigned TSHRegDelFlags;

typedef unsigned TSHRegEnumFlags;

typedef _DLLVERSIONINFO *PDllVersionInfo;

typedef _DLLVERSIONINFO TDllVersionInfo;

typedef _DLLVERSIONINFO2 *PDllVersionInfo2;

typedef _DLLVERSIONINFO2 TDllVersionInfo2;

//-- var, const, procedure ---------------------------------------------------
#define SID_IQueryAssociations L"{c46ca590-3c3f-11d2-bee6-0000f805ca57}"
}	/* namespace Shlwapi */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_SHLWAPI)
using namespace Winapi::Shlwapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_ShlwapiHPP
