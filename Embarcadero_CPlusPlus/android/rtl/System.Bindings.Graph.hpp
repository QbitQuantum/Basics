// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Graph.pas' rev: 34.00 (Android)

#ifndef System_Bindings_GraphHPP
#define System_Bindings_GraphHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.Outputs.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.Expression.hpp>
#include <System.Bindings.Manager.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Graph
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingGraph;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindingGraph : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TDictionary__2<System::Bindings::Expression::TBindingExpression*,int>* TVisitedDict;
	
	typedef __int64 TIteration;
	
	typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,__int64>* TProperties;
	
	typedef System::Generics::Collections::TObjectDictionary__2<System::TObject*,System::Generics::Collections::TDictionary__2<System::UnicodeString,__int64>*>* TObjects;
	
	typedef System::Generics::Collections::TDictionary__2<System::Bindings::Expression::TBindingExpression*,__int64>* TExpressions;
	
	typedef System::Generics::Collections::TPair__2<System::Bindings::Expression::TBindingExpression*,System::Bindings::Evalprotocol::TWrapperDictionary*> TExprWrappersPair;
	
	typedef System::Generics::Collections::TObjectDictionary__2<System::Bindings::Expression::TBindingExpression*,System::Bindings::Evalprotocol::TWrapperDictionary*>* TExprWrappersDict;
	
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,int> TPropertyTopology;
	
	typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,int>* TPropertiesTopology;
	
	typedef System::Generics::Collections::TObjectDictionary__2<System::TObject*,System::Generics::Collections::TDictionary__2<System::UnicodeString,int>*>* TObjectsTopology;
	
	typedef System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* TExpressionsWaitQueue;
	
	typedef void __fastcall (__closure *TObjPropMarkedEvent)(System::TObject* Obj, const System::UnicodeString PropertyName);
	
	typedef void __fastcall (__closure *TExprMarkedEvent)(System::Bindings::Expression::TBindingExpression* Expr);
	
	
private:
	static __int64 FIteration;
	static System::Generics::Collections::TObjectDictionary__2<System::TObject*,System::Generics::Collections::TDictionary__2<System::UnicodeString,__int64>*>* FObjects;
	static System::Generics::Collections::TDictionary__2<System::Bindings::Expression::TBindingExpression*,__int64>* FExpressions;
	static System::Generics::Collections::TObjectDictionary__2<System::TObject*,System::Generics::Collections::TDictionary__2<System::UnicodeString,int>*>* FObjectsTopology;
	static System::Generics::Collections::TDictionary__2<System::Bindings::Expression::TBindingExpression*,int>* FExpressionsTopology;
	static System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* FExpressionsWaitQueue;
	static TObjPropMarkedEvent FOnObjPropMarked;
	static TExprMarkedEvent FOnExprMarked;
	__classmethod void __fastcall DoGetDependentExprs(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Manager::TBindingManager* StartManager, System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* List);
	__classmethod void __fastcall DoScanTopology(System::TObject* Obj, const System::UnicodeString PropertyName, int Level, System::Bindings::Manager::TBindingManager* Manager)/* overload */;
	__classmethod void __fastcall DoScanTopology(System::Bindings::Expression::TBindingExpression* Expr, int Level, System::Bindings::Manager::TBindingManager* Manager)/* overload */;
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
	
public:
	__classmethod void __fastcall MarkIteration(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	__classmethod void __fastcall MarkIteration(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	__classmethod __int64 __fastcall GetIterationMark(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	__classmethod __int64 __fastcall GetIterationMark(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	__classmethod bool __fastcall IsIterationMarked(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	__classmethod bool __fastcall IsIterationMarked(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	__classmethod bool __fastcall AreAllIterationMarked(System::Bindings::Evalprotocol::TWrapperDictionary* Wrappers);
	__classmethod void __fastcall ClearIteration();
	__classmethod bool __fastcall IsInput(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Expression::TBindingExpression* Expr);
	__classmethod bool __fastcall IsOutput(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Expression::TBindingExpression* Expr);
	__classmethod System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* __fastcall GetDependentExprs(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Manager::TBindingManager* Manager);
	__classmethod System::Generics::Collections::TObjectDictionary__2<System::Bindings::Expression::TBindingExpression*,System::Bindings::Evalprotocol::TWrapperDictionary*>* __fastcall GetDependentExprsWrappers(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Manager::TBindingManager* Manager);
	__classmethod void __fastcall MarkTopologic(System::TObject* Obj, const System::UnicodeString PropertyName, int Level)/* overload */;
	__classmethod void __fastcall MarkTopologic(System::Bindings::Expression::TBindingExpression* Expr, int Level)/* overload */;
	__classmethod int __fastcall GetTopologicLevel(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	__classmethod int __fastcall GetTopologicLevel(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	__classmethod bool __fastcall IsTopologicMarked(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	__classmethod bool __fastcall IsTopologicMarked(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	__classmethod void __fastcall ScanTopology(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Manager::TBindingManager* Manager)/* overload */;
	__classmethod void __fastcall ScanTopology(System::Bindings::Expression::TBindingExpression* Expr, System::Bindings::Manager::TBindingManager* Manager)/* overload */;
	__classmethod void __fastcall ClearTopology();
	__classmethod bool __fastcall IsWaiting(System::Bindings::Expression::TBindingExpression* Expr);
	__classmethod bool __fastcall IsWaitQueueEmpty();
	__classmethod void __fastcall EnqueueWait(System::Bindings::Expression::TBindingExpression* Expr);
	__classmethod void __fastcall DequeueWait(System::Bindings::Expression::TBindingExpression* Expr)/* overload */;
	__classmethod System::Bindings::Expression::TBindingExpression* __fastcall DequeueWait()/* overload */;
	__classmethod int __fastcall IncIteration(int Step = 0x1);
	/* static */ __property __int64 Iteration = {read=FIteration, write=FIteration};
	/* static */ __property System::Generics::Collections::TObjectDictionary__2<System::TObject*,System::Generics::Collections::TDictionary__2<System::UnicodeString,__int64>*>* Objects = {read=FObjects};
	/* static */ __property System::Generics::Collections::TDictionary__2<System::Bindings::Expression::TBindingExpression*,__int64>* Expressions = {read=FExpressions};
	/* static */ __property System::Generics::Collections::TObjectDictionary__2<System::TObject*,System::Generics::Collections::TDictionary__2<System::UnicodeString,int>*>* ObjectsTopology = {read=FObjectsTopology};
	/* static */ __property System::Generics::Collections::TDictionary__2<System::Bindings::Expression::TBindingExpression*,int>* ExpressionsTopology = {read=FExpressionsTopology};
	/* static */ __property System::Generics::Collections::TList__1<System::Bindings::Expression::TBindingExpression*>* ExpressionsWaitQueue = {read=FExpressionsWaitQueue};
	/* static */ __property TObjPropMarkedEvent OnObjPropMarked = {read=FOnObjPropMarked, write=FOnObjPropMarked};
	/* static */ __property TExprMarkedEvent OnExprMarked = {read=FOnExprMarked, write=FOnExprMarked};
public:
	/* TObject.Create */ inline __fastcall TBindingGraph() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingGraph() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Graph */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_GRAPH)
using namespace System::Bindings::Graph;
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
#endif	// System_Bindings_GraphHPP
