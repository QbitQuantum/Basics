// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Manager.pas' rev: 34.00 (iOS)

#ifndef System_Bindings_ManagerHPP
#define System_Bindings_ManagerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Manager
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBindingManager : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	typedef System::Generics::Collections::TList__1<TBindingManager*>* TManagerList;
	
	typedef System::Generics::Collections::TObjectList__1<System::Bindings::Expression::TBindingExpression*>* TExprList;
	
	
private:
	System::Generics::Collections::TList__1<TBindingManager*>* FManagers;
	System::Generics::Collections::TObjectList__1<System::Bindings::Expression::TBindingExpression*>* FExpressions;
	TBindingManager* FOwner;
	int __fastcall GetExprCount();
	System::Bindings::Expression::TBindingExpression* __fastcall GetExpressions(int Index);
	int __fastcall GetManagerCount();
	TBindingManager* __fastcall GetManagers(int Index);
	
protected:
	__property System::Generics::Collections::TList__1<TBindingManager*>* ManagerList = {read=FManagers};
	__property System::Generics::Collections::TObjectList__1<System::Bindings::Expression::TBindingExpression*>* ExprList = {read=FExpressions};
	
public:
	__fastcall TBindingManager(TBindingManager* Owner);
	__fastcall virtual ~TBindingManager();
	int __fastcall Add(const System::UnicodeString Expr);
	System::Bindings::Expression::TBindingExpression* __fastcall AddExpr(const System::UnicodeString Expr);
	void __fastcall Delete(int Index);
	int __fastcall Remove(System::Bindings::Expression::TBindingExpression* Expr);
	int __fastcall IndexOf(System::Bindings::Expression::TBindingExpression* Expr);
	void __fastcall Clear();
	System::Bindings::Expression::TBindingExpression* __fastcall Extract(System::Bindings::Expression::TBindingExpression* Expr);
	__property TBindingManager* Owner = {read=FOwner};
	__property TBindingManager* Managers[int Index] = {read=GetManagers};
	__property int ManagerCount = {read=GetManagerCount, nodefault};
	__property System::Bindings::Expression::TBindingExpression* Expressions[int Index] = {read=GetExpressions};
	__property int ExprCount = {read=GetExprCount, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Manager */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_MANAGER)
using namespace System::Bindings::Manager;
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
#endif	// System_Bindings_ManagerHPP
