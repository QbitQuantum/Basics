// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.EvalSys.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_EvalsysHPP
#define System_Bindings_EvalsysHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.SyncObjs.hpp>
#include <System.TypInfo.hpp>
#include <System.Rtti.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Evalsys
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCollectionInterfacesTracker;
class DELPHICLASS TPairScope;
class DELPHICLASS TObjectMemberGroupScope;
class DELPHICLASS TDictionaryScope;
class DELPHICLASS TNestedScope;
class DELPHICLASS TNamespaceScope;
class DELPHICLASS TValueConverter;
class DELPHICLASS TOverload;
class DELPHICLASS TOverloadGroup;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCollectionInterfacesTracker : public System::Generics::Collections::TList__1<GUID>
{
	typedef System::Generics::Collections::TList__1<GUID> inherited;
	
private:
	void __fastcall ItemChanged(System::TObject* Sender, const System::_di_IInterface Item, System::Generics::Collections::TCollectionNotification Action);
	
public:
	bool __fastcall GetSupported(const GUID *IIDs, const int IIDs_High);
public:
	/* {System_Generics_Collections}TList<System_TGUID>.Create */ inline __fastcall TCollectionInterfacesTracker()/* overload */ : System::Generics::Collections::TList__1<GUID>() { }
	/* {System_Generics_Collections}TList<System_TGUID>.Create */ inline __fastcall TCollectionInterfacesTracker(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<GUID> > AComparer)/* overload */ : System::Generics::Collections::TList__1<GUID>(AComparer) { }
	/* {System_Generics_Collections}TList<System_TGUID>.Create */ inline __fastcall TCollectionInterfacesTracker(System::Generics::Collections::TEnumerable__1<GUID>* const Collection)/* overload */ : System::Generics::Collections::TList__1<GUID>(Collection) { }
	/* {System_Generics_Collections}TList<System_TGUID>.Destroy */ inline __fastcall virtual ~TCollectionInterfacesTracker() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPairScope : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Generics::Collections::TPair__2<System::UnicodeString,System::Bindings::Evalprotocol::_di_IInvokable> FPair;
	
public:
	__fastcall TPairScope(const System::UnicodeString MethodName, const System::Bindings::Evalprotocol::_di_IInvokable MethodInvokable);
	System::_di_IInterface __fastcall Lookup(const System::UnicodeString Name)/* overload */;
	System::_di_IInterface __fastcall Lookup(System::TObject* Obj)/* overload */;
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TPairScope() { }
	
private:
	void *__IScopeEx;	// System::Bindings::Evalprotocol::IScopeEx 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B757805E-E2B1-473D-A201-99BF6E1134FF}
	operator System::Bindings::Evalprotocol::_di_IScopeEx()
	{
		System::Bindings::Evalprotocol::_di_IScopeEx intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEx*(void) { return (System::Bindings::Evalprotocol::IScopeEx*)&__IScopeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DAFE2455-3DB6-40CC-B1D6-1EAC0A29ABEC}
	operator System::Bindings::Evalprotocol::_di_IScope()
	{
		System::Bindings::Evalprotocol::_di_IScope intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScope*(void) { return (System::Bindings::Evalprotocol::IScope*)&__IScopeEx; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TObjectMemberGroupScope : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	typedef System::Generics::Collections::TList__1<System::_di_IInterface>* TWrappers;
	
	class DELPHICLASS TWrappersEnumerator;
	class PASCALIMPLEMENTATION TWrappersEnumerator : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		TObjectMemberGroupScope* FScope;
		typename System::Generics::Collections::TList__1<System::_di_IInterface>::TEnumerator* FListEnumerator;
		
	public:
		__fastcall TWrappersEnumerator(TObjectMemberGroupScope* Scope);
		__fastcall virtual ~TWrappersEnumerator();
		System::_di_IInterface __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property System::_di_IInterface Current = {read=GetCurrent};
private:
		void *__IScopeEnumerator;	// System::Bindings::Evalprotocol::IScopeEnumerator 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {AD60BFF2-4A13-4183-A6A9-20FE60FF035D}
		operator System::Bindings::Evalprotocol::_di_IScopeEnumerator()
		{
			System::Bindings::Evalprotocol::_di_IScopeEnumerator intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator System::Bindings::Evalprotocol::IScopeEnumerator*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerator*)&__IScopeEnumerator; }
		#endif
		
	};
	
	
	
private:
	System::Generics::Collections::TList__1<System::_di_IInterface>* FWrappers;
	TCollectionInterfacesTracker* FSupportedIntfs;
	
public:
	__fastcall TObjectMemberGroupScope();
	__fastcall virtual ~TObjectMemberGroupScope();
	__property System::Generics::Collections::TList__1<System::_di_IInterface>* Wrappers = {read=FWrappers};
	System::Bindings::Evalprotocol::_di_IScopeEnumerator __fastcall GetEnumerator();
	bool __fastcall HasItemsSupporting(const GUID *IIDs, const int IIDs_High);
private:
	void *__IScopeEnumerable;	// System::Bindings::Evalprotocol::IScopeEnumerable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59DE173C-954A-4DBA-BAC1-5D1B9551B85A}
	operator System::Bindings::Evalprotocol::_di_IScopeEnumerable()
	{
		System::Bindings::Evalprotocol::_di_IScopeEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEnumerable*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerable*)&__IScopeEnumerable; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDictionaryScope : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,System::_di_IInterface>* TMap;
	
	class DELPHICLASS TWrappersEnumerator;
	class PASCALIMPLEMENTATION TWrappersEnumerator : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		TDictionaryScope* FScope;
		typename System::Generics::Collections::TDictionary__2<System::UnicodeString,System::_di_IInterface>::TValueEnumerator* FMapEnumerator;
		
	public:
		__fastcall TWrappersEnumerator(TDictionaryScope* Scope);
		__fastcall virtual ~TWrappersEnumerator();
		System::_di_IInterface __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property System::_di_IInterface Current = {read=GetCurrent};
private:
		void *__IScopeEnumerator;	// System::Bindings::Evalprotocol::IScopeEnumerator 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {AD60BFF2-4A13-4183-A6A9-20FE60FF035D}
		operator System::Bindings::Evalprotocol::_di_IScopeEnumerator()
		{
			System::Bindings::Evalprotocol::_di_IScopeEnumerator intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator System::Bindings::Evalprotocol::IScopeEnumerator*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerator*)&__IScopeEnumerator; }
		#endif
		
	};
	
	
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::_di_IInterface>* FMap;
	TCollectionInterfacesTracker* FSupportedIntfs;
	
public:
	__fastcall TDictionaryScope();
	__fastcall virtual ~TDictionaryScope();
	__property System::Generics::Collections::TDictionary__2<System::UnicodeString,System::_di_IInterface>* Map = {read=FMap};
	System::_di_IInterface __fastcall Lookup(const System::UnicodeString Name)/* overload */;
	System::_di_IInterface __fastcall Lookup(System::TObject* Obj)/* overload */;
	System::Bindings::Evalprotocol::_di_IScopeEnumerator __fastcall GetEnumerator();
	bool __fastcall HasItemsSupporting(const GUID *IIDs, const int IIDs_High);
private:
	void *__IScopeEnumerable;	// System::Bindings::Evalprotocol::IScopeEnumerable 
	void *__IScopeEx;	// System::Bindings::Evalprotocol::IScopeEx 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59DE173C-954A-4DBA-BAC1-5D1B9551B85A}
	operator System::Bindings::Evalprotocol::_di_IScopeEnumerable()
	{
		System::Bindings::Evalprotocol::_di_IScopeEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEnumerable*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerable*)&__IScopeEnumerable; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B757805E-E2B1-473D-A201-99BF6E1134FF}
	operator System::Bindings::Evalprotocol::_di_IScopeEx()
	{
		System::Bindings::Evalprotocol::_di_IScopeEx intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEx*(void) { return (System::Bindings::Evalprotocol::IScopeEx*)&__IScopeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DAFE2455-3DB6-40CC-B1D6-1EAC0A29ABEC}
	operator System::Bindings::Evalprotocol::_di_IScope()
	{
		System::Bindings::Evalprotocol::_di_IScope intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScope*(void) { return (System::Bindings::Evalprotocol::IScope*)&__IScopeEx; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNestedScope : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	class DELPHICLASS TWrapperEnumerator;
	class PASCALIMPLEMENTATION TWrapperEnumerator : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
		
	protected:
		typedef System::DynamicArray<System::_di_IInterface> TWrappers;
		
		
	private:
		TNestedScope* FScope;
		TWrappers FWrappers;
		int FIndex;
		
	public:
		__fastcall TWrapperEnumerator(TNestedScope* const Scope);
		System::_di_IInterface __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property System::_di_IInterface Current = {read=GetCurrent};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TWrapperEnumerator() { }
		
private:
		void *__IScopeEnumerator;	// System::Bindings::Evalprotocol::IScopeEnumerator 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {AD60BFF2-4A13-4183-A6A9-20FE60FF035D}
		operator System::Bindings::Evalprotocol::_di_IScopeEnumerator()
		{
			System::Bindings::Evalprotocol::_di_IScopeEnumerator intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator System::Bindings::Evalprotocol::IScopeEnumerator*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerator*)&__IScopeEnumerator; }
		#endif
		
	};
	
	
	
private:
	System::Bindings::Evalprotocol::_di_IScope FOuter;
	System::Bindings::Evalprotocol::_di_IScope FInner;
	
public:
	__fastcall TNestedScope(const System::Bindings::Evalprotocol::_di_IScope AOuter, const System::Bindings::Evalprotocol::_di_IScope AInner);
	__property System::Bindings::Evalprotocol::_di_IScope Inner = {read=FInner};
	__property System::Bindings::Evalprotocol::_di_IScope Outer = {read=FOuter};
	HIDESBASE HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	System::_di_IInterface __fastcall GetSelf();
	System::_di_IInterface __fastcall Lookup(const System::UnicodeString Name)/* overload */;
	System::_di_IInterface __fastcall Lookup(System::TObject* Obj)/* overload */;
	System::Bindings::Evalprotocol::_di_IScopeEnumerator __fastcall GetEnumerator();
	bool __fastcall HasItemsSupporting(const GUID *IIDs, const int IIDs_High);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TNestedScope() { }
	
private:
	void *__IScopeSelf;	// System::Bindings::Evalprotocol::IScopeSelf 
	void *__IScopeEnumerable;	// System::Bindings::Evalprotocol::IScopeEnumerable 
	void *__IScopeEx;	// System::Bindings::Evalprotocol::IScopeEx 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FAD875D9-7EDE-438C-A477-F7BCEF135147}
	operator System::Bindings::Evalprotocol::_di_IScopeSelf()
	{
		System::Bindings::Evalprotocol::_di_IScopeSelf intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeSelf*(void) { return (System::Bindings::Evalprotocol::IScopeSelf*)&__IScopeSelf; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59DE173C-954A-4DBA-BAC1-5D1B9551B85A}
	operator System::Bindings::Evalprotocol::_di_IScopeEnumerable()
	{
		System::Bindings::Evalprotocol::_di_IScopeEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEnumerable*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerable*)&__IScopeEnumerable; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B757805E-E2B1-473D-A201-99BF6E1134FF}
	operator System::Bindings::Evalprotocol::_di_IScopeEx()
	{
		System::Bindings::Evalprotocol::_di_IScopeEx intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEx*(void) { return (System::Bindings::Evalprotocol::IScopeEx*)&__IScopeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DAFE2455-3DB6-40CC-B1D6-1EAC0A29ABEC}
	operator System::Bindings::Evalprotocol::_di_IScope()
	{
		System::Bindings::Evalprotocol::_di_IScope intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScope*(void) { return (System::Bindings::Evalprotocol::IScope*)&__IScopeEx; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IScopeSelf; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TNamespaceScope : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	class DELPHICLASS TWrapperEnumerator;
	class PASCALIMPLEMENTATION TWrapperEnumerator : public System::TInterfacedObject
	{
		typedef System::TInterfacedObject inherited;
		
	private:
		TNamespaceScope* FScope;
		bool FEnumerated;
		
	public:
		__fastcall TWrapperEnumerator(TNamespaceScope* const Scope);
		System::_di_IInterface __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property System::_di_IInterface Current = {read=GetCurrent};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TWrapperEnumerator() { }
		
private:
		void *__IScopeEnumerator;	// System::Bindings::Evalprotocol::IScopeEnumerator 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {AD60BFF2-4A13-4183-A6A9-20FE60FF035D}
		operator System::Bindings::Evalprotocol::_di_IScopeEnumerator()
		{
			System::Bindings::Evalprotocol::_di_IScopeEnumerator intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator System::Bindings::Evalprotocol::IScopeEnumerator*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerator*)&__IScopeEnumerator; }
		#endif
		
	};
	
	
	
private:
	System::UnicodeString FName;
	System::Bindings::Evalprotocol::_di_IScope FScope;
	
public:
	__fastcall TNamespaceScope(const System::UnicodeString Name, const System::Bindings::Evalprotocol::_di_IScope Scope);
	System::_di_IInterface __fastcall Lookup(const System::UnicodeString Name);
	System::Bindings::Evalprotocol::_di_IScopeEnumerator __fastcall GetEnumerator();
	bool __fastcall HasItemsSupporting(const GUID *IIDs, const int IIDs_High);
	__property System::UnicodeString Name = {read=FName};
	__property System::Bindings::Evalprotocol::_di_IScope Scope = {read=FScope};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TNamespaceScope() { }
	
private:
	void *__IScopeEnumerable;	// System::Bindings::Evalprotocol::IScopeEnumerable 
	void *__IScope;	// System::Bindings::Evalprotocol::IScope 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {59DE173C-954A-4DBA-BAC1-5D1B9551B85A}
	operator System::Bindings::Evalprotocol::_di_IScopeEnumerable()
	{
		System::Bindings::Evalprotocol::_di_IScopeEnumerable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScopeEnumerable*(void) { return (System::Bindings::Evalprotocol::IScopeEnumerable*)&__IScopeEnumerable; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DAFE2455-3DB6-40CC-B1D6-1EAC0A29ABEC}
	operator System::Bindings::Evalprotocol::_di_IScope()
	{
		System::Bindings::Evalprotocol::_di_IScope intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IScope*(void) { return (System::Bindings::Evalprotocol::IScope*)&__IScope; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TValueConverter : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TConvPair
	{
	public:
		System::Typinfo::TTypeInfo *FromType;
		System::Typinfo::TTypeInfo *ToType;
		__fastcall TConvPair(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo);
		TConvPair() {}
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	System::Generics::Collections::TDictionary__2<TConvPair,System::DelphiInterface<System::Sysutils::TFunc__2<System::Rtti::TValue,System::Rtti::TValue> > >* FConversions;
	
public:
	__fastcall TValueConverter();
	__fastcall virtual ~TValueConverter();
	void __fastcall AddConversion(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo, const System::DelphiInterface<System::Sysutils::TFunc__2<System::Rtti::TValue,System::Rtti::TValue> > AFunc);
	bool __fastcall CanConvert(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo);
	System::Rtti::TValue __fastcall Convert(const System::Rtti::TValue &AValue, System::Typinfo::PTypeInfo ATo);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOverload : public System::TObject
{
	typedef System::TObject inherited;
	
private:
#ifndef _WIN64
	System::DynamicArray<System::Typinfo::PTypeInfo> FParamTypes;
	System::DelphiInterface<System::Sysutils::TFunc__2<System::DynamicArray<System::Rtti::TValue>,System::Rtti::TValue> > FBody;
#else /* _WIN64 */
	System::TArray__1<System::Typinfo::PTypeInfo> FParamTypes;
	System::DelphiInterface<System::Sysutils::TFunc__2<System::TArray__1<System::Rtti::TValue>,System::Rtti::TValue> > FBody;
#endif /* _WIN64 */
	
public:
#ifndef _WIN64
	__fastcall TOverload(System::Typinfo::PTypeInfo const *ParamTypes, const int ParamTypes_High, const System::DelphiInterface<System::Sysutils::TFunc__2<System::DynamicArray<System::Rtti::TValue>,System::Rtti::TValue> > Body);
#else /* _WIN64 */
	__fastcall TOverload(System::Typinfo::PTypeInfo const *ParamTypes, const int ParamTypes_High, const System::DelphiInterface<System::Sysutils::TFunc__2<System::TArray__1<System::Rtti::TValue>,System::Rtti::TValue> > Body);
#endif /* _WIN64 */
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TOverload() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TOverloadGroup : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FName;
	TValueConverter* FConverter;
	int FArity;
	System::Generics::Collections::TList__1<TOverload*>* FList;
	
public:
	__fastcall TOverloadGroup(TValueConverter* AConverter, const System::UnicodeString AName);
	__fastcall virtual ~TOverloadGroup();
	void __fastcall AddOverload(TOverload* AOverload);
	__property System::UnicodeString Name = {read=FName};
#ifndef _WIN64
	System::Bindings::Evalprotocol::_di_IValue __fastcall Invoke(const System::DynamicArray<System::Bindings::Evalprotocol::_di_IValue> Args);
#else /* _WIN64 */
	System::Bindings::Evalprotocol::_di_IValue __fastcall Invoke(const System::TArray__1<System::Bindings::Evalprotocol::_di_IValue> Args);
#endif /* _WIN64 */
private:
	void *__IInvokable;	// System::Bindings::Evalprotocol::IInvokable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0BB8361C-AAC7-42DB-B970-5275797DF41F}
	operator System::Bindings::Evalprotocol::_di_IInvokable()
	{
		System::Bindings::Evalprotocol::_di_IInvokable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IInvokable*(void) { return (System::Bindings::Evalprotocol::IInvokable*)&__IInvokable; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Bindings::Evalprotocol::_di_IScope __fastcall BasicOperators(void);
extern DELPHI_PACKAGE System::Bindings::Evalprotocol::_di_IScope __fastcall BasicConstants(void);
}	/* namespace Evalsys */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_EVALSYS)
using namespace System::Bindings::Evalsys;
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
#endif	// System_Bindings_EvalsysHPP
