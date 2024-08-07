﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Search.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_SearchHPP
#define System_Bindings_SearchHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.EvalProtocol.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Search
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindingSearch;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindingSearch : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	template<typename T> __interface DELPHIINTERFACE TConstProc__1;
	#ifdef __clang__
	template<typename T> using _di_TConstProc__1 = System::DelphiInterface<TConstProc__1<T>>;
	#endif
	// Template declaration generated by Delphi parameterized types is
	// used only for accessing Delphi variables and fields.
	// Don't instantiate with new type parameters in user code.
	template<typename T> __interface TConstProc__1  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const T Arg1) = 0 ;
	};
	
	
private:
	static System::Rtti::TRttiContext FRttiCtx;
	__classmethod void __fastcall DoDepthGetWrappers(const System::Bindings::Evalprotocol::_di_IScopeEnumerable ScopeEnum, System::Bindings::Evalprotocol::TWrapperDictionary* Dict);
	__classmethod System::_di_IInterface __fastcall DoDepthSearchObject(System::TObject* Obj, const System::Bindings::Evalprotocol::_di_IGroup Group);
	__classmethod void __fastcall AddPreparedWrappers(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable, System::TObject* const AList);
	
private:
	// __classmethod void __fastcall Create@();
	
public:
	__classmethod bool __fastcall IsWrapper(const System::_di_IInterface Wrapper);
	__classmethod bool __fastcall IsObjectWrapper(const System::_di_IInterface Wrapper)/* overload */;
	__classmethod bool __fastcall IsObjectWrapper(const System::_di_IInterface Wrapper, System::TObject* Obj)/* overload */;
	__classmethod bool __fastcall IsMemberWrapper(const System::_di_IInterface Wrapper, System::TObject* Obj, const System::UnicodeString MemberName);
	__classmethod bool __fastcall PermitsObjectWrapper(System::TObject* Obj, const System::UnicodeString PropertyName)/* overload */;
	__classmethod bool __fastcall PermitsObjectWrapper(System::Rtti::TRttiMember* const Member)/* overload */;
	__classmethod System::_di_IInterface __fastcall DepthSearchObject(System::TObject* Obj, const System::Bindings::Evalprotocol::_di_IScopeEx Scope)/* overload */;
	__classmethod System::_di_IInterface __fastcall DepthSearchObject(System::TObject* Obj, System::Bindings::Evalprotocol::TWrapperDictionary* Wrappers)/* overload */;
	__classmethod System::_di_IInterface __fastcall DepthSearchProperty(System::TObject* Obj, const System::UnicodeString PropertyName, const System::Bindings::Evalprotocol::_di_IScopeEx Scope)/* overload */;
	__classmethod System::_di_IInterface __fastcall DepthSearchProperty(System::TObject* Obj, const System::UnicodeString PropertyName, System::Bindings::Evalprotocol::TWrapperDictionary* const Wrappers)/* overload */;
	__classmethod System::Bindings::Evalprotocol::TWrapperDictionary* __fastcall DepthGetWrappers(const System::Bindings::Evalprotocol::_di_IScope Scope);
	__classmethod void __fastcall ResetWrappersArguments(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable);
	__classmethod void __fastcall EnumerateResetWrappersArguments(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable, const System::DelphiInterface<TConstProc__1<System::Bindings::Evalprotocol::_di_IArguments> > ACallback);
	__classmethod void __fastcall ReattachWrappers(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable);
	__classmethod void __fastcall EnumerateReattachWrappers(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable, const System::DelphiInterface<TConstProc__1<System::Bindings::Evalprotocol::_di_IPlaceholder> > AReattachCallback, const System::DelphiInterface<TConstProc__1<System::Bindings::Evalprotocol::_di_IRecordPlaceholder> > AReattachRecordCallback);
	__classmethod void __fastcall PrepareWrappersForEvaluation(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable);
	__classmethod void __fastcall EnumeratePrepareWrappersForEvaluation(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable, const System::DelphiInterface<TConstProc__1<System::Bindings::Evalprotocol::_di_IArguments> > AResetCallback, const System::DelphiInterface<TConstProc__1<System::Bindings::Evalprotocol::_di_IPlaceholder> > AReattachCallback, const System::DelphiInterface<TConstProc__1<System::Bindings::Evalprotocol::_di_IRecordPlaceholder> > AReattachRecordCallback);
	__classmethod System::Bindings::Evalprotocol::_di_IPreparedWrappers __fastcall GetPreparedWrappers(const System::Bindings::Evalprotocol::_di_IScopeEnumerable StartScopeEnumerable);
	__classmethod void __fastcall CollectGroupInstWrprs(System::Bindings::Evalprotocol::_di_IGroup Group, System::Bindings::Evalprotocol::TWrapperDictionary* WrprDict);
	__classmethod void __fastcall CopyWrprs(System::Bindings::Evalprotocol::TWrapperDictionary* AFrom, System::Bindings::Evalprotocol::TWrapperDictionary* ATo);
	
private:
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TBindingSearch() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingSearch() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Search */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_SEARCH)
using namespace System::Bindings::Search;
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
#endif	// System_Bindings_SearchHPP
