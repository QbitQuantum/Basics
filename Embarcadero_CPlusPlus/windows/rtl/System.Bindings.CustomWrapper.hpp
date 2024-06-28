// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.CustomWrapper.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_CustomwrapperHPP
#define System_Bindings_CustomwrapperHPP

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
#include <System.RTLConsts.hpp>
#include <System.Bindings.EvalProtocol.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Customwrapper
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ECustomWrapperError;
class DELPHICLASS TCustomWrapper;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ECustomWrapperError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECustomWrapperError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECustomWrapperError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECustomWrapperError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECustomWrapperError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECustomWrapperError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECustomWrapperError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECustomWrapperError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECustomWrapperError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECustomWrapperError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECustomWrapperError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECustomWrapperError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECustomWrapperError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECustomWrapperError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TCustomWrapper : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Bindings::Evalprotocol::TCustomWrapperType FWrapperType;
	System::Bindings::Evalprotocol::_di_TCustomWrapperGetterCallback FGetterCallback;
	System::TObject* FParent;
	System::TClass FMetaClass;
	System::UnicodeString FMemberName;
#ifndef _WIN64
	System::DynamicArray<System::Rtti::TValue> FArgs;
#else /* _WIN64 */
	System::TArray__1<System::Rtti::TValue> FArgs;
#endif /* _WIN64 */
	System::Rtti::TValue FValue;
	
public:
	__fastcall TCustomWrapper(System::TObject* Parent, System::TClass MetaClass, const System::UnicodeString MemberName, System::Bindings::Evalprotocol::TCustomWrapperType WrapperType, const System::Bindings::Evalprotocol::_di_TCustomWrapperGetterCallback GetterCallback);
	HIDESBASE HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	System::Bindings::Evalprotocol::TCustomWrapperType __fastcall GetWrapperType();
	System::Bindings::Evalprotocol::_di_TCustomWrapperGetterCallback __fastcall GetGetterCallback();
	void __fastcall SetGetterCallback(const System::Bindings::Evalprotocol::_di_TCustomWrapperGetterCallback Callback);
	__property System::Bindings::Evalprotocol::TCustomWrapperType WrapperType = {read=GetWrapperType, nodefault};
	__property System::Bindings::Evalprotocol::_di_TCustomWrapperGetterCallback GetterCallback = {read=GetGetterCallback, write=SetGetterCallback};
	System::Typinfo::PTypeInfo __fastcall GetType();
	System::Rtti::TValue __fastcall GetValue();
#ifndef _WIN64
	System::Bindings::Evalprotocol::_di_IValue __fastcall Invoke(const System::DynamicArray<System::Bindings::Evalprotocol::_di_IValue> Args);
	System::DynamicArray<System::Rtti::TValue> __fastcall GetArgs();
	void __fastcall SetArgs(const System::DynamicArray<System::Rtti::TValue> Args);
	__property System::DynamicArray<System::Rtti::TValue> Args = {read=GetArgs, write=SetArgs};
#else /* _WIN64 */
	System::Bindings::Evalprotocol::_di_IValue __fastcall Invoke(const System::TArray__1<System::Bindings::Evalprotocol::_di_IValue> Args);
	System::TArray__1<System::Rtti::TValue> __fastcall GetArgs();
	void __fastcall SetArgs(const System::TArray__1<System::Rtti::TValue> Args);
	__property System::TArray__1<System::Rtti::TValue> Args = {read=GetArgs, write=SetArgs};
#endif /* _WIN64 */
	System::TObject* __fastcall GetParent();
	System::UnicodeString __fastcall GetMemberName();
	__property System::TObject* Parent = {read=GetParent};
	__property System::UnicodeString MemberName = {read=GetMemberName};
	System::TObject* __fastcall GetAttachment();
	System::TClass __fastcall GetMetaClass();
	bool __fastcall GetAttached();
	bool __fastcall GetEvalTimeOnly();
	void __fastcall Attach(System::TObject* Obj);
	void __fastcall Detach();
	__property System::TObject* Attachment = {read=GetAttachment};
	__property System::TClass MetaClass = {read=GetMetaClass};
	__property bool Attached = {read=GetAttached, nodefault};
	__property bool EvalTimeOnly = {read=GetEvalTimeOnly, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomWrapper() { }
	
private:
	void *__IPlaceholder;	// System::Bindings::Evalprotocol::IPlaceholder 
	void *__IChild;	// System::Bindings::Evalprotocol::IChild 
	void *__IArguments;	// System::Bindings::Evalprotocol::IArguments 
	void *__IInvokable;	// System::Bindings::Evalprotocol::IInvokable 
	void *__IValue;	// System::Bindings::Evalprotocol::IValue 
	void *__ICustomWrapper;	// System::Bindings::Evalprotocol::ICustomWrapper 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {4F76D2FA-BED9-476B-AA29-B6399F234DA1}
	operator System::Bindings::Evalprotocol::_di_IPlaceholder()
	{
		System::Bindings::Evalprotocol::_di_IPlaceholder intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IPlaceholder*(void) { return (System::Bindings::Evalprotocol::IPlaceholder*)&__IPlaceholder; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D4DD0F18-4076-4A9B-B87A-F9BA1BC69E26}
	operator System::Bindings::Evalprotocol::_di_IChild()
	{
		System::Bindings::Evalprotocol::_di_IChild intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IChild*(void) { return (System::Bindings::Evalprotocol::IChild*)&__IChild; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79D93B44-2F1B-4F53-B44D-91913FE68581}
	operator System::Bindings::Evalprotocol::_di_IArguments()
	{
		System::Bindings::Evalprotocol::_di_IArguments intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IArguments*(void) { return (System::Bindings::Evalprotocol::IArguments*)&__IArguments; }
	#endif
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
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A495F901-72F5-4384-BA50-EC3B4B42F6C2}
	operator System::Bindings::Evalprotocol::_di_IValue()
	{
		System::Bindings::Evalprotocol::_di_IValue intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::IValue*(void) { return (System::Bindings::Evalprotocol::IValue*)&__IValue; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {45963846-9D75-4219-8A5D-1CDEECAEA7CD}
	operator System::Bindings::Evalprotocol::_di_ICustomWrapper()
	{
		System::Bindings::Evalprotocol::_di_ICustomWrapper intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Bindings::Evalprotocol::ICustomWrapper*(void) { return (System::Bindings::Evalprotocol::ICustomWrapper*)&__ICustomWrapper; }
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
	operator System::IInterface*(void) { return (System::IInterface*)&__IPlaceholder; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Customwrapper */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_CUSTOMWRAPPER)
using namespace System::Bindings::Customwrapper;
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
#endif	// System_Bindings_CustomwrapperHPP
