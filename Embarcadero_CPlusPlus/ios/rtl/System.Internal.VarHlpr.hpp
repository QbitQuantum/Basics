// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Internal.VarHlpr.pas' rev: 34.00 (iOS)

#ifndef System_Internal_VarhlprHPP
#define System_Internal_VarhlprHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Internal
{
namespace Varhlpr
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall VariantClear(System::Variant &V);
extern DELPHI_PACKAGE void __fastcall VariantCast(const System::Variant &src, System::Variant &dst, int vt);
extern DELPHI_PACKAGE void __fastcall VariantArrayRedim(System::Variant &V, int High);
extern DELPHI_PACKAGE void __fastcall VariantCpy(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantAdd(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantSub(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantMul(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantDiv(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantMod(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantAnd(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantOr(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantXor(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantShl(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE void __fastcall VariantShr(const System::Variant &src, System::Variant &dst);
extern DELPHI_PACKAGE System::Variant __fastcall VariantAdd2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantSub2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantMul2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantDiv2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantMod2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantAnd2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantOr2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantXor2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantShl2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantShr2(const System::Variant &V1, const System::Variant &V2);
extern DELPHI_PACKAGE System::Variant __fastcall VariantNot(const System::Variant &V1);
extern DELPHI_PACKAGE System::Variant __fastcall VariantNeg(const System::Variant &V1);
extern DELPHI_PACKAGE System::Variant __fastcall VariantGetElement(const System::Variant &V, int i1)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VariantGetElement(const System::Variant &V, int i1, int i2)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VariantGetElement(const System::Variant &V, int i1, int i2, int i3)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VariantGetElement(const System::Variant &V, int i1, int i2, int i3, int i4)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VariantGetElement(const System::Variant &V, int i1, int i2, int i3, int i4, int i5)/* overload */;
extern DELPHI_PACKAGE void __fastcall VariantPutElement(System::Variant &V, const System::Variant &data, int i1)/* overload */;
extern DELPHI_PACKAGE void __fastcall VariantPutElement(System::Variant &V, const System::Variant &data, int i1, int i2)/* overload */;
extern DELPHI_PACKAGE void __fastcall VariantPutElement(System::Variant &V, const System::Variant &data, int i1, int i2, int i3)/* overload */;
extern DELPHI_PACKAGE void __fastcall VariantPutElement(System::Variant &V, const System::Variant &data, int i1, int i2, int i3, int i4)/* overload */;
extern DELPHI_PACKAGE void __fastcall VariantPutElement(System::Variant &V, const System::Variant &data, int i1, int i2, int i3, int i4, int i5)/* overload */;
extern DELPHI_PACKAGE void __fastcall VariantFromUnicodeString(System::Variant &V, const System::UnicodeString Str);
extern DELPHI_PACKAGE void __fastcall VariantToUnicodeString(const System::Variant &V, System::UnicodeString &Str);
}	/* namespace Varhlpr */
}	/* namespace Internal */
}	/* namespace System */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Internal_VarhlprHPP
