// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdUriUtils.pas' rev: 34.00 (iOS)

#ifndef IduriutilsHPP
#define IduriutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdGlobal.hpp>
#include <System.Character.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iduriutils
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall CalcUTF16CharLength(const System::UnicodeString AStr, const int AIndex);
extern DELPHI_PACKAGE bool __fastcall WideCharIsInSet(const System::UnicodeString ASet, const System::WideChar AChar);
extern DELPHI_PACKAGE int __fastcall GetUTF16Codepoint(const System::UnicodeString AStr, const int AIndex);
}	/* namespace Iduriutils */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDURIUTILS)
using namespace Iduriutils;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IduriutilsHPP
