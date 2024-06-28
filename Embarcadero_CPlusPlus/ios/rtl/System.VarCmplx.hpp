// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.VarCmplx.pas' rev: 34.00 (iOS)

#ifndef System_VarcmplxHPP
#define System_VarcmplxHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Varcmplx
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString ComplexNumberSymbol;
extern DELPHI_PACKAGE bool ComplexNumberSymbolBeforeImaginary;
extern DELPHI_PACKAGE bool ComplexNumberDefuzzAtZero;
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCreate(void)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCreate(const double AReal)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCreate(const double AReal, const double AImaginary)/* overload */;
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCreate(const System::UnicodeString AText)/* overload */;
extern DELPHI_PACKAGE System::Word __fastcall VarComplex(void);
extern DELPHI_PACKAGE bool __fastcall VarIsComplex(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarAsComplex(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSimplify(const System::Variant &AValue);
extern DELPHI_PACKAGE double __fastcall VarComplexAbsSqr(const System::Variant &AValue);
extern DELPHI_PACKAGE double __fastcall VarComplexAbs(const System::Variant &AValue);
extern DELPHI_PACKAGE double __fastcall VarComplexAngle(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSign(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexConjugate(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexInverse(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexExp(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexLn(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexLog10(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexLog2(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexLogN(const System::Variant &AValue, const double X);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSqr(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSqrt(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexTimesPosI(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexTimesNegI(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexTimesImaginary(const System::Variant &AValue, const double AFactor);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexTimesReal(const System::Variant &AValue, const double AFactor);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexPower(const System::Variant &AValue, const System::Variant &APower);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCos(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSin(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexTan(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCot(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSec(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCsc(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcCos(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcSin(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcTan(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcCot(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcSec(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcCsc(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCosH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSinH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexTanH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCotH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexSecH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexCscH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcCosH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcSinH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcTanH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcCotH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcSecH(const System::Variant &AValue);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexArcCscH(const System::Variant &AValue);
extern DELPHI_PACKAGE void __fastcall VarComplexToPolar(const System::Variant &AValue, double &ARadius, double &ATheta, bool AFixTheta = true);
extern DELPHI_PACKAGE System::Variant __fastcall VarComplexFromPolar(const double ARadius, const double ATheta);
}	/* namespace Varcmplx */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_VARCMPLX)
using namespace System::Varcmplx;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_VarcmplxHPP
