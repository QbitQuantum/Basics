// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Stan.Expr.pas' rev: 34.00 (Android)

#ifndef Firedac_Stan_ExprHPP
#define Firedac_Stan_ExprHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Stan.Intf.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Stan
{
namespace Expr
{
  _INIT_UNIT(Firedac_Stan_Expr);
}	/* namespace Expr */
}	/* namespace Stan */
}	/* namespace Firedac */

namespace Firedac
{
namespace Stan
{
namespace Expr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDExpressionFunctionDesc;
class DELPHICLASS TFDExpressionCollation;
class DELPHICLASS TFDExpressionManager;
//-- type declarations -------------------------------------------------------
typedef System::Variant __fastcall (*TFDExpressionFunction)(const System::Variant *AArgs, const int AArgs_High);

typedef System::Variant __fastcall (*TFDExpressionFieldFunction)(const System::Variant *AArgs, const int AArgs_High, Firedac::Stan::Intf::_di_IFDStanExpressionEvaluator AExpr);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDExpressionFunctionDesc : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	Firedac::Stan::Intf::TFDExpressionScopeKind FScopeKind;
	int FScopeKindArg;
	Firedac::Stan::Intf::TFDDataType FDataType;
	int FDataTypeArg;
	int FArgMin;
	int FArgMax;
	System::UnicodeString FArgTypeFamiles;
	void *FCall;
	
public:
	__property System::UnicodeString Name = {read=FName};
	__property Firedac::Stan::Intf::TFDExpressionScopeKind ScopeKind = {read=FScopeKind, nodefault};
	__property int ScopeKindArg = {read=FScopeKindArg, nodefault};
	__property Firedac::Stan::Intf::TFDDataType DataType = {read=FDataType, nodefault};
	__property int DataTypeArg = {read=FDataTypeArg, nodefault};
	__property int ArgMin = {read=FArgMin, nodefault};
	__property int ArgMax = {read=FArgMax, nodefault};
	__property System::UnicodeString ArgTypeFamiles = {read=FArgTypeFamiles};
	__property void * Call = {read=FCall};
public:
	/* TObject.Create */ inline __fastcall TFDExpressionFunctionDesc() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDExpressionFunctionDesc() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef int __fastcall (*TFDExpressionCompare)(void * AStr1, int ALen1, void * AStr2, int ALen2, bool ANoCase);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDExpressionCollation : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	System::StaticArray<TFDExpressionCompare, 3> FCalls;
	TFDExpressionCompare __fastcall GetCall(Firedac::Stan::Intf::TFDEncoding AEncoding);
	
public:
	__property System::UnicodeString Name = {read=FName};
	__property TFDExpressionCompare Calls[Firedac::Stan::Intf::TFDEncoding AEncoding] = {read=GetCall};
public:
	/* TObject.Create */ inline __fastcall TFDExpressionCollation() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TFDExpressionCollation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDExpressionManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStringList* FFunctions;
	System::Classes::TStringList* FCollations;
	int __fastcall GetFunctionCount();
	TFDExpressionFunctionDesc* __fastcall GetFunctions(int AIndex);
	int __fastcall GetCollationCount();
	TFDExpressionCollation* __fastcall GetCollations(int AIndex);
	
public:
	__fastcall TFDExpressionManager();
	__fastcall virtual ~TFDExpressionManager();
	void __fastcall AddSynonym(const System::UnicodeString AName, const System::UnicodeString ASynonym);
	void __fastcall AddFunction(const System::UnicodeString AName, Firedac::Stan::Intf::TFDExpressionScopeKind AScopeKind, int AScopeKindArg, Firedac::Stan::Intf::TFDDataType ADataType, int ADataTypeArg, int AArgMin, int AArgMax, const System::UnicodeString AArgTypeFamiles, void * ACall);
	void __fastcall RemoveFunction(const System::UnicodeString AName);
	void __fastcall AddCollation(const System::UnicodeString AName, Firedac::Stan::Intf::TFDEncoding AEncoding, TFDExpressionCompare ACall);
	void __fastcall RemoveCollation(const System::UnicodeString AName, Firedac::Stan::Intf::TFDEncoding AEncoding);
	int __fastcall FindFunction(const System::UnicodeString AName);
	int __fastcall FindCollation(const System::UnicodeString AName, Firedac::Stan::Intf::TFDEncoding AEncoding);
	__property int FunctionCount = {read=GetFunctionCount, nodefault};
	__property TFDExpressionFunctionDesc* Functions[int AIndex] = {read=GetFunctions};
	__property int CollationCount = {read=GetCollationCount, nodefault};
	__property TFDExpressionCollation* Collations[int AIndex] = {read=GetCollations};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::WideChar C_FD_FAny = (System::WideChar)(0x2a);
static constexpr System::WideChar C_FD_FAnsi = (System::WideChar)(0x61);
static constexpr System::WideChar C_FD_FUni = (System::WideChar)(0x75);
static constexpr System::WideChar C_FD_FStr = (System::WideChar)(0x73);
static constexpr System::WideChar C_FD_FDate = (System::WideChar)(0x64);
static constexpr System::WideChar C_FD_FInt = (System::WideChar)(0x69);
static constexpr System::WideChar C_FD_FFloat = (System::WideChar)(0x66);
static constexpr System::WideChar C_FD_FNum = (System::WideChar)(0x6e);
static constexpr System::WideChar C_FD_FBool = (System::WideChar)(0x62);
extern DELPHI_PACKAGE bool __fastcall FDStrIsNull(const System::Variant &V);
extern DELPHI_PACKAGE System::Variant __fastcall FDStrToVar(const System::UnicodeString S);
extern DELPHI_PACKAGE TFDExpressionManager* __fastcall FDExpressionManager(void);
}	/* namespace Expr */
}	/* namespace Stan */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN_EXPR)
using namespace Firedac::Stan::Expr;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_STAN)
using namespace Firedac::Stan;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Stan_ExprHPP
