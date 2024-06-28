// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Evaluator.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_EvaluatorHPP
#define System_Bindings_EvaluatorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.Character.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Evaluator
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TBuiltinOp : unsigned char { boAdd, boSubtract, boMultiply, boDivide, boNegate, boEqualTo, boNotEqual, boLessThan, boLessEqual, boGreaterThan, boGreaterEqual };

typedef System::StaticArray<System::UnicodeString, 11> System_Bindings_Evaluator__1;

typedef System::StaticArray<System::UnicodeString, 4> System_Bindings_Evaluator__2;

//-- var, const, procedure ---------------------------------------------------
static const TBuiltinOp boAnd = (TBuiltinOp)(11);
static const TBuiltinOp boOr = (TBuiltinOp)(12);
static const TBuiltinOp boXor = (TBuiltinOp)(13);
static const TBuiltinOp boNot = (TBuiltinOp)(14);
extern DELPHI_PACKAGE System_Bindings_Evaluator__1 BuiltinOpName;
extern DELPHI_PACKAGE System_Bindings_Evaluator__2 BuiltinOpNameExt;
extern DELPHI_PACKAGE System::Sysutils::TFormatSettings EvalFormatSettings;
extern DELPHI_PACKAGE System::Bindings::Evalprotocol::_di_ICompiledBinding __fastcall Compile(const System::UnicodeString Source, const System::Bindings::Evalprotocol::_di_IScope RootScope = System::Bindings::Evalprotocol::_di_IScope());
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetBuiltinOpName(TBuiltinOp AOp);
}	/* namespace Evaluator */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_EVALUATOR)
using namespace System::Bindings::Evaluator;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS)
using namespace System::Bindings;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Bindings_EvaluatorHPP
