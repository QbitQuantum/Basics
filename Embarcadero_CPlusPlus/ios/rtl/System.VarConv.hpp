// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.VarConv.pas' rev: 34.00 (iOS)

#ifndef System_VarconvHPP
#define System_VarconvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.ConvUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Varconv
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Variant __fastcall VarConvertCreate(const double AValue, const System::Convutils::TConvType AType)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VarConvertCreate(const System::UnicodeString AValue)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall VarConvert(void);
extern DELPHI_PACKAGE bool __fastcall VarIsConvert(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarAsConvert(const System::Variant &AValue)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VarAsConvert(const System::Variant &AValue, const System::Convutils::TConvType AType)/* overload */;
}	/* namespace Varconv */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_VARCONV)
using namespace System::Varconv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_VarconvHPP
