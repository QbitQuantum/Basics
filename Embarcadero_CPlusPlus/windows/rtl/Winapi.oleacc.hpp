// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.oleacc.pas' rev: 34.00 (Windows)

#ifndef Winapi_OleaccHPP
#define Winapi_OleaccHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------
#include <oleacc.h>
DECLARE_DINTERFACE_TYPE(IAccessible)
DECLARE_DINTERFACE_TYPE(IAccessibleHandler)
DECLARE_DINTERFACE_TYPE(IAccIdentity)
DECLARE_DINTERFACE_TYPE(IAccPropServer)
DECLARE_DINTERFACE_TYPE(IAccPropServices)
#if !defined(_VCL_ALIAS_RECORDS)
 #if !defined(_WIN64)
  #pragma link "oleacc.lib"
 #endif
#endif

namespace Winapi
{
namespace Oleacc
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::Byte *PByte1;

typedef GUID *PUserType1;

//-- var, const, procedure ---------------------------------------------------
static const System::Int8 AccessibilityMajorVersion = System::Int8(0x1);
static const System::Int8 AccessibilityMinorVersion = System::Int8(0x1);
}	/* namespace Oleacc */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_OLEACC)
using namespace Winapi::Oleacc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_OleaccHPP
