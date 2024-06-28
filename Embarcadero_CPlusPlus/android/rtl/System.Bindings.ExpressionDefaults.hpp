// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.ExpressionDefaults.pas' rev: 34.00 (Android)

#ifndef System_Bindings_ExpressiondefaultsHPP
#define System_Bindings_ExpressiondefaultsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.EvalSys.hpp>
#include <System.Bindings.Evaluator.hpp>
#include <System.Bindings.ObjEval.hpp>
#include <System.Bindings.NotifierContracts.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Bindings.Manager.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Expressiondefaults
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingExpressionDefault;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBindingExpressionDefault : public System::Bindings::Expression::TBindingExpression
{
	typedef System::Bindings::Expression::TBindingExpression inherited;
	
private:
	System::Bindings::Evalprotocol::_di_ICompiledBinding FBinding;
	System::Bindings::Evalprotocol::_di_IScope FRootScope;
	bool FCompiled;
	System::Bindings::Manager::TBindingManager* FManager;
	System::Bindings::Evalprotocol::_di_IScopeSymbols FScopeSymbols;
	System::Bindings::Evalprotocol::_di_ICompiledBinding FCompiledBinding;
	System::Bindings::Evalprotocol::_di_IPreparedWrappers FPreparedWrappers;
	System::Bindings::Evalprotocol::_di_IScopeEx __fastcall GetRootScopeEx();
	System::Bindings::Evalprotocol::_di_IScopeEnumerator __fastcall GetRootScopeEnumerator();
	System::Bindings::Evalprotocol::_di_ICompiledBindingWrappers __fastcall GetBindingWrappers();
	void __fastcall SetBinding(const System::Bindings::Evalprotocol::_di_ICompiledBinding ABinding);
	
protected:
	virtual bool __fastcall GetCompiled();
	System::Bindings::Evalprotocol::_di_IScope __fastcall CreateScope(System::Generics::Collections::TDictionary__2<System::TObject*,System::UnicodeString>* const Assocs);
	virtual void __fastcall Compile()/* overload */;
	virtual bool __fastcall GetIsManaged();
	__property System::Bindings::Evalprotocol::_di_IScope RootScope = {read=FRootScope};
	__property System::Bindings::Evalprotocol::_di_IScopeEx RootScopeEx = {read=GetRootScopeEx};
	__property System::Bindings::Evalprotocol::_di_IScopeEnumerator RootScopeEnumerator = {read=GetRootScopeEnumerator};
	__property System::Bindings::Evalprotocol::_di_IScopeSymbols ScopeSymbols = {read=FScopeSymbols};
	__property System::Bindings::Evalprotocol::_di_ICompiledBinding Binding = {read=FCompiledBinding};
	__property System::Bindings::Evalprotocol::_di_ICompiledBindingWrappers BindingWrappers = {read=GetBindingWrappers};
	
public:
	__fastcall TBindingExpressionDefault(System::Bindings::Manager::TBindingManager* Manager);
	__fastcall virtual ~TBindingExpressionDefault();
	__property System::Bindings::Manager::TBindingManager* Manager = {read=FManager};
	virtual System::Bindings::Evalprotocol::_di_IValue __fastcall Evaluate();
	virtual void __fastcall EvaluateOutputs();
	virtual void __fastcall Clear();
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Compile(System::Classes::TComponent* const *Objects, const int Objects_High){ System::Bindings::Expression::TBindingExpression::Compile(Objects, Objects_High); }
	inline void __fastcall  Compile(const System::Bindings::Expression::TBindingAssociation *Assocs, const int Assocs_High){ System::Bindings::Expression::TBindingExpression::Compile(Assocs, Assocs_High); }
	inline void __fastcall  Compile(const System::Bindings::Evalprotocol::_di_IScope AScope){ System::Bindings::Expression::TBindingExpression::Compile(AScope); }
	inline void __fastcall  Compile(const System::Bindings::Evalprotocol::_di_IScope *AScopes, const int AScopes_High){ System::Bindings::Expression::TBindingExpression::Compile(AScopes, AScopes_High); }
	inline void __fastcall  Compile(System::Classes::TComponent* const *Objects, const int Objects_High, const System::Bindings::Expression::TBindingAssociation *Assocs, const int Assocs_High, const System::Bindings::Evalprotocol::_di_IScope *Scopes, const int Scopes_High){ System::Bindings::Expression::TBindingExpression::Compile(Objects, Objects_High, Assocs, Assocs_High, Scopes, Scopes_High); }
	
private:
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CAEEF849-A88F-4D4D-8980-395042DD56FA}
	operator System::Bindings::Evalprotocol::_di_ICompiledBindingWrappers() { return BindingWrappers; }
	#else
	operator System::Bindings::Evalprotocol::ICompiledBindingWrappers*(void) { return (System::Bindings::Evalprotocol::ICompiledBindingWrappers*)BindingWrappers; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {42B9D178-5460-45F8-8CBF-5F8310A4C713}
	operator System::Bindings::Evalprotocol::_di_ICompiledBinding() { return Binding; }
	#else
	operator System::Bindings::Evalprotocol::ICompiledBinding*(void) { return (System::Bindings::Evalprotocol::ICompiledBinding*)Binding; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1FF4BA45-C177-4847-ABFF-5D74D06400B1}
	operator System::Bindings::Evalprotocol::_di_IScopeSymbols() { return ScopeSymbols; }
	#else
	operator System::Bindings::Evalprotocol::IScopeSymbols*(void) { return (System::Bindings::Evalprotocol::IScopeSymbols*)ScopeSymbols; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AD60BFF2-4A13-4183-A6A9-20FE60FF035D}
	operator System::Bindings::Evalprotocol::_di_IScopeEnumerator() { return RootScopeEnumerator; }
	#else
	operator System::Bindings::Evalprotocol::IScopeEnumerator*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerator*)RootScopeEnumerator; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B757805E-E2B1-473D-A201-99BF6E1134FF}
	operator System::Bindings::Evalprotocol::_di_IScopeEx() { return RootScopeEx; }
	#else
	operator System::Bindings::Evalprotocol::IScopeEx*(void) { return (System::Bindings::Evalprotocol::IScopeEx*)RootScopeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DAFE2455-3DB6-40CC-B1D6-1EAC0A29ABEC}
	operator System::Bindings::Evalprotocol::_di_IScope() { return RootScope; }
	#else
	operator System::Bindings::Evalprotocol::IScope*(void) { return (System::Bindings::Evalprotocol::IScope*)RootScope; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Expressiondefaults */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_EXPRESSIONDEFAULTS)
using namespace System::Bindings::Expressiondefaults;
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
#endif	// System_Bindings_ExpressiondefaultsHPP
