// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.EvalProtocol.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_EvalprotocolHPP
#define System_Bindings_EvalprotocolHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.TypInfo.hpp>
#include <System.Rtti.hpp>
#include <System.RTLConsts.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Bindings
{
namespace Evalprotocol
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EWrapperError;
class DELPHICLASS EPlaceholderError;
class DELPHICLASS EEvaluatorError;
__interface DELPHIINTERFACE IWrapper;
typedef System::DelphiInterface<IWrapper> _di_IWrapper;
__interface DELPHIINTERFACE IValue;
typedef System::DelphiInterface<IValue> _di_IValue;
__interface DELPHIINTERFACE ILocation;
typedef System::DelphiInterface<ILocation> _di_ILocation;
__interface DELPHIINTERFACE IChild;
typedef System::DelphiInterface<IChild> _di_IChild;
__interface DELPHIINTERFACE IRttiChild;
typedef System::DelphiInterface<IRttiChild> _di_IRttiChild;
__interface DELPHIINTERFACE IRecordChild;
typedef System::DelphiInterface<IRecordChild> _di_IRecordChild;
__interface DELPHIINTERFACE IPlaceholder;
typedef System::DelphiInterface<IPlaceholder> _di_IPlaceholder;
__interface DELPHIINTERFACE IRecordPlaceholder;
typedef System::DelphiInterface<IRecordPlaceholder> _di_IRecordPlaceholder;
__interface DELPHIINTERFACE IArguments;
typedef System::DelphiInterface<IArguments> _di_IArguments;
__interface DELPHIINTERFACE IInvokable;
typedef System::DelphiInterface<IInvokable> _di_IInvokable;
__interface DELPHIINTERFACE IGroup;
typedef System::DelphiInterface<IGroup> _di_IGroup;
__interface DELPHIINTERFACE IDynamicGroup;
typedef System::DelphiInterface<IDynamicGroup> _di_IDynamicGroup;
__interface DELPHIINTERFACE IDynamicInstance;
typedef System::DelphiInterface<IDynamicInstance> _di_IDynamicInstance;
__interface DELPHIINTERFACE ISubscription;
typedef System::DelphiInterface<ISubscription> _di_ISubscription;
__interface DELPHIINTERFACE TSubscriptionNotification;
typedef System::DelphiInterface<TSubscriptionNotification> _di_TSubscriptionNotification;
__interface DELPHIINTERFACE ISubscribable;
typedef System::DelphiInterface<ISubscribable> _di_ISubscribable;
__interface DELPHIINTERFACE IScopeSelf;
typedef System::DelphiInterface<IScopeSelf> _di_IScopeSelf;
__interface DELPHIINTERFACE IScope;
typedef System::DelphiInterface<IScope> _di_IScope;
__interface DELPHIINTERFACE IScopeEx;
typedef System::DelphiInterface<IScopeEx> _di_IScopeEx;
__interface DELPHIINTERFACE ICustomScope;
typedef System::DelphiInterface<ICustomScope> _di_ICustomScope;
__interface DELPHIINTERFACE IScopeEnumerator;
typedef System::DelphiInterface<IScopeEnumerator> _di_IScopeEnumerator;
__interface DELPHIINTERFACE IScopeEnumerable;
typedef System::DelphiInterface<IScopeEnumerable> _di_IScopeEnumerable;
__interface DELPHIINTERFACE IScopeSymbols;
typedef System::DelphiInterface<IScopeSymbols> _di_IScopeSymbols;
__interface DELPHIINTERFACE TCustomWrapperGetterCallback;
typedef System::DelphiInterface<TCustomWrapperGetterCallback> _di_TCustomWrapperGetterCallback;
__interface DELPHIINTERFACE ICustomWrapper;
typedef System::DelphiInterface<ICustomWrapper> _di_ICustomWrapper;
__interface DELPHIINTERFACE IPreparedWrappers;
typedef System::DelphiInterface<IPreparedWrappers> _di_IPreparedWrappers;
__interface DELPHIINTERFACE ICompiledBinding;
typedef System::DelphiInterface<ICompiledBinding> _di_ICompiledBinding;
class DELPHICLASS TWrapperDictionary;
__interface DELPHIINTERFACE ICompiledBindingWrappers;
typedef System::DelphiInterface<ICompiledBindingWrappers> _di_ICompiledBindingWrappers;
__interface DELPHIINTERFACE IWrapperBinding;
typedef System::DelphiInterface<IWrapperBinding> _di_IWrapperBinding;
__interface DELPHIINTERFACE IDebugBinding;
typedef System::DelphiInterface<IDebugBinding> _di_IDebugBinding;
class DELPHICLASS TValueWrapper;
class DELPHICLASS TLocationWrapper;
class DELPHICLASS TScopeSymbols;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EWrapperError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EWrapperError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EWrapperError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EWrapperError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EWrapperError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrapperError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EWrapperError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EWrapperError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EWrapperError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrapperError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EWrapperError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrapperError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EWrapperError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EWrapperError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EPlaceholderError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EPlaceholderError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EPlaceholderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EPlaceholderError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EPlaceholderError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EPlaceholderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EPlaceholderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EPlaceholderError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EPlaceholderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPlaceholderError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EPlaceholderError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPlaceholderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EPlaceholderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EPlaceholderError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEvaluatorError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEvaluatorError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEvaluatorError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEvaluatorError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEvaluatorError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEvaluatorError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEvaluatorError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEvaluatorError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEvaluatorError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEvaluatorError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEvaluatorError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEvaluatorError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEvaluatorError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEvaluatorError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{743F6B0A-931A-4EF7-9637-8DF639ABA4A9}") IWrapper  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{A495F901-72F5-4384-BA50-EC3B4B42F6C2}") IValue  : public System::IInterface 
{
	virtual System::Typinfo::PTypeInfo __fastcall GetType() = 0 ;
	virtual System::Rtti::TValue __fastcall GetValue() = 0 ;
};

__interface  INTERFACE_UUID("{861746E3-740A-4799-BB14-217066C629A8}") ILocation  : public IValue 
{
	virtual void __fastcall SetValue(const System::Rtti::TValue &AValue) = 0 ;
};

__interface  INTERFACE_UUID("{D4DD0F18-4076-4A9B-B87A-F9BA1BC69E26}") IChild  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetParent() = 0 ;
	virtual System::UnicodeString __fastcall GetMemberName() = 0 ;
	__property System::TObject* Parent = {read=GetParent};
	__property System::UnicodeString MemberName = {read=GetMemberName};
};

__interface  INTERFACE_UUID("{D4DD0F18-4076-4A9B-B87A-F9BA1BC69E26}") IRttiChild  : public IChild 
{
	virtual System::Rtti::TRttiMember* __fastcall GetMember() = 0 ;
	__property System::Rtti::TRttiMember* Member = {read=GetMember};
};

__interface  INTERFACE_UUID("{0F19D037-D3D4-410D-9E83-4C7013128DD3}") IRecordChild  : public System::IInterface 
{
	virtual System::Rtti::TValue __fastcall GetParent() = 0 ;
	virtual System::Rtti::TRttiMember* __fastcall GetMember() = 0 ;
	__property System::Rtti::TValue Parent = {read=GetParent};
	__property System::Rtti::TRttiMember* Member = {read=GetMember};
};

__interface  INTERFACE_UUID("{4F76D2FA-BED9-476B-AA29-B6399F234DA1}") IPlaceholder  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetAttachment() = 0 ;
	virtual System::TClass __fastcall GetMetaClass() = 0 ;
	virtual bool __fastcall GetAttached() = 0 ;
	virtual bool __fastcall GetEvalTimeOnly() = 0 ;
	virtual void __fastcall Attach(System::TObject* Obj) = 0 ;
	virtual void __fastcall Detach() = 0 ;
	__property System::TObject* Attachment = {read=GetAttachment};
	__property System::TClass MetaClass = {read=GetMetaClass};
	__property bool Attached = {read=GetAttached};
	__property bool EvalTimeOnly = {read=GetEvalTimeOnly};
};

__interface  INTERFACE_UUID("{EA75D719-9962-4A60-AAC1-11E9EE820EED}") IRecordPlaceholder  : public System::IInterface 
{
	virtual System::Rtti::TValue __fastcall GetAttachment() = 0 ;
	virtual bool __fastcall GetAttached() = 0 ;
	virtual bool __fastcall GetEvalTimeOnly() = 0 ;
	virtual void __fastcall Attach(const System::Rtti::TValue &Rec) = 0 ;
	virtual void __fastcall Detach() = 0 ;
	__property System::Rtti::TValue Attachment = {read=GetAttachment};
	__property bool Attached = {read=GetAttached};
	__property bool EvalTimeOnly = {read=GetEvalTimeOnly};
};

__interface  INTERFACE_UUID("{79D93B44-2F1B-4F53-B44D-91913FE68581}") IArguments  : public System::IInterface 
{
#ifndef _WIN64
	virtual System::DynamicArray<System::Rtti::TValue> __fastcall GetArgs() = 0 ;
	virtual void __fastcall SetArgs(const System::DynamicArray<System::Rtti::TValue> Args) = 0 ;
	__property System::DynamicArray<System::Rtti::TValue> Args = {read=GetArgs, write=SetArgs};
#else /* _WIN64 */
	virtual System::TArray__1<System::Rtti::TValue> __fastcall GetArgs() = 0 ;
	virtual void __fastcall SetArgs(const System::TArray__1<System::Rtti::TValue> Args) = 0 ;
	__property System::TArray__1<System::Rtti::TValue> Args = {read=GetArgs, write=SetArgs};
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{0BB8361C-AAC7-42DB-B970-5275797DF41F}") IInvokable  : public System::IInterface 
{
#ifndef _WIN64
	virtual _di_IValue __fastcall Invoke(const System::DynamicArray<_di_IValue> Args) = 0 ;
#else /* _WIN64 */
	virtual _di_IValue __fastcall Invoke(const System::TArray__1<_di_IValue> Args) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{D6945DB4-6EFB-47A0-A91E-975522DAB28A}") IGroup  : public System::IInterface 
{
	virtual System::_di_IInterface __fastcall GetWrappers(int Index) = 0 ;
	virtual int __fastcall GetWrapperCount() = 0 ;
	virtual int __fastcall Add() = 0 /* overload */;
	virtual int __fastcall Add(/* out */ System::_di_IInterface &Wrapper) = 0 /* overload */;
	virtual void __fastcall Clear() = 0 ;
	__property System::_di_IInterface Wrappers[int Index] = {read=GetWrappers};
	__property int WrapperCount = {read=GetWrapperCount};
};

__interface  INTERFACE_UUID("{9F4AA978-B053-4137-87EE-A1C66C53FB25}") IDynamicGroup  : public IGroup 
{
	virtual _di_IGroup __fastcall GetFixedGroup() = 0 ;
	virtual void __fastcall SetFixedGroup(const _di_IGroup Group) = 0 ;
	__property _di_IGroup FixedGroup = {read=GetFixedGroup, write=SetFixedGroup};
};

__interface  INTERFACE_UUID("{50F20CB5-22A2-4FF7-A1BD-9D61B463D078}") IDynamicInstance  : public System::IInterface 
{
	virtual System::_di_IInterface __fastcall GetFixedInstance() = 0 ;
	virtual void __fastcall SetFixedInstance(const System::_di_IInterface Instance) = 0 ;
	__property System::_di_IInterface FixedInstance = {read=GetFixedInstance, write=SetFixedInstance};
};

__interface  INTERFACE_UUID("{3AD2F70A-3AAE-4A09-8982-12DE494E8D6A}") ISubscription  : public System::IInterface 
{
	virtual void __fastcall Unsubscribe() = 0 ;
};

__interface TSubscriptionNotification  : public System::IInterface 
{
	virtual void __fastcall Invoke(const _di_ISubscription ASubscription) = 0 ;
};

__interface  INTERFACE_UUID("{CFDD03F1-FB50-4B39-99B8-842D5604A14A}") ISubscribable  : public System::IInterface 
{
	virtual _di_ISubscription __fastcall Subscribe(const _di_TSubscriptionNotification ANotification) = 0 ;
};

__interface  INTERFACE_UUID("{FAD875D9-7EDE-438C-A477-F7BCEF135147}") IScopeSelf  : public System::IInterface 
{
	virtual System::_di_IInterface __fastcall GetSelf() = 0 ;
};

__interface  INTERFACE_UUID("{DAFE2455-3DB6-40CC-B1D6-1EAC0A29ABEC}") IScope  : public System::IInterface 
{
	virtual System::_di_IInterface __fastcall Lookup(const System::UnicodeString Name) = 0 ;
};

__interface  INTERFACE_UUID("{B757805E-E2B1-473D-A201-99BF6E1134FF}") IScopeEx  : public IScope 
{
	HIDESBASE virtual System::_di_IInterface __fastcall Lookup(System::TObject* Obj) = 0 /* overload */;
};

__interface ICustomScope  : public IScope 
{
	virtual System::TObject* __fastcall GetMappedObject() = 0 ;
	virtual System::TClass __fastcall GetMetaClass() = 0 ;
	virtual void __fastcall SetMappedObject(System::TObject* const Value) = 0 ;
	__property System::TObject* MappedObject = {read=GetMappedObject, write=SetMappedObject};
	__property System::TClass MetaClass = {read=GetMetaClass};
};

__interface  INTERFACE_UUID("{AD60BFF2-4A13-4183-A6A9-20FE60FF035D}") IScopeEnumerator  : public System::IInterface 
{
	virtual System::_di_IInterface __fastcall GetCurrent() = 0 ;
	virtual bool __fastcall MoveNext() = 0 ;
	__property System::_di_IInterface Current = {read=GetCurrent};
};

__interface  INTERFACE_UUID("{59DE173C-954A-4DBA-BAC1-5D1B9551B85A}") IScopeEnumerable  : public System::IInterface 
{
	virtual _di_IScopeEnumerator __fastcall GetEnumerator() = 0 ;
	virtual bool __fastcall HasItemsSupporting(const GUID *IIDs, const int IIDs_High) = 0 ;
};

__interface  INTERFACE_UUID("{1FF4BA45-C177-4847-ABFF-5D74D06400B1}") IScopeSymbols  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetSymbols(int Index) = 0 ;
	virtual void __fastcall SetSymbols(int Index, const System::UnicodeString Value) = 0 ;
	virtual int __fastcall GetSymbolCount() = 0 ;
	virtual void __fastcall Add(const System::UnicodeString Symbol) = 0 ;
	virtual void __fastcall Remove(const System::UnicodeString Symbol) = 0 ;
	virtual bool __fastcall Contains(const System::UnicodeString Symbol) = 0 ;
	virtual void __fastcall Clear() = 0 ;
	__property System::UnicodeString Symbols[int Index] = {read=GetSymbols, write=SetSymbols};
	__property int SymbolCount = {read=GetSymbolCount};
};

enum DECLSPEC_DENUM TCustomWrapperType : unsigned char { cwtProperty, cwtMethod, cwtIndexedProperty };

__interface TCustomWrapperGetterCallback  : public System::IInterface 
{
#ifndef _WIN64
	virtual System::Rtti::TValue __fastcall Invoke(System::TObject* ParentObject, const System::UnicodeString MemberName, System::DynamicArray<System::Rtti::TValue> Args) = 0 ;
#else /* _WIN64 */
	virtual System::Rtti::TValue __fastcall Invoke(System::TObject* ParentObject, const System::UnicodeString MemberName, System::TArray__1<System::Rtti::TValue> Args) = 0 ;
#endif /* _WIN64 */
};

__interface  INTERFACE_UUID("{45963846-9D75-4219-8A5D-1CDEECAEA7CD}") ICustomWrapper  : public System::IInterface 
{
	virtual TCustomWrapperType __fastcall GetWrapperType() = 0 ;
	virtual _di_TCustomWrapperGetterCallback __fastcall GetGetterCallback() = 0 ;
	virtual void __fastcall SetGetterCallback(const _di_TCustomWrapperGetterCallback Callback) = 0 ;
	__property TCustomWrapperType WrapperType = {read=GetWrapperType};
	__property _di_TCustomWrapperGetterCallback GetterCallback = {read=GetGetterCallback, write=SetGetterCallback};
};

__interface IPreparedWrappers  : public System::IInterface 
{
	virtual void __fastcall BeforeEvaluate() = 0 ;
	virtual void __fastcall AfterEvaluate() = 0 ;
};

enum DECLSPEC_DENUM TCompiledBindingPhaseType : unsigned char { cbpEmpty, cbpPrepareCompilation, cbpCompiling, cbpCompiled, cbpPrepareEvaluation, cbpEvaluating, cbpEvaluated, cbpEvaluationError };

__interface  INTERFACE_UUID("{42B9D178-5460-45F8-8CBF-5F8310A4C713}") ICompiledBinding  : public System::IInterface 
{
	virtual TCompiledBindingPhaseType __fastcall GetPhase() = 0 ;
	virtual _di_IValue __fastcall Evaluate(const _di_IScope ARoot, const _di_TSubscriptionNotification ASubscriptionCallback, System::Generics::Collections::TList__1<_di_ISubscription>* Subscriptions) = 0 /* overload */;
	virtual _di_IValue __fastcall Evaluate(const _di_IScope ARoot, const _di_TSubscriptionNotification ASubscriptionCallback, System::Generics::Collections::TList__1<_di_ISubscription>* Subscriptions, _di_IPreparedWrappers &APreparedWrapper) = 0 /* overload */;
	__property TCompiledBindingPhaseType Phase = {read=GetPhase};
};

class PASCALIMPLEMENTATION TWrapperDictionary : public System::Generics::Collections::TDictionary__2<System::_di_IInterface,void *>
{
	typedef System::Generics::Collections::TDictionary__2<System::_di_IInterface,void *> inherited;
	
public:
	__fastcall TWrapperDictionary();
public:
	/* {System_Generics_Collections}TDictionary<System_IInterface,System_Pointer>.Destroy */ inline __fastcall virtual ~TWrapperDictionary() { }
	
};


__interface  INTERFACE_UUID("{CAEEF849-A88F-4D4D-8980-395042DD56FA}") ICompiledBindingWrappers  : public System::IInterface 
{
	virtual TWrapperDictionary* __fastcall GetWrappers() = 0 ;
	__property TWrapperDictionary* Wrappers = {read=GetWrappers};
};

__interface  INTERFACE_UUID("{8B5BF98B-DD68-4013-BBBB-4819CB8DD2AB}") IWrapperBinding  : public System::IInterface 
{
	virtual _di_ICompiledBinding __fastcall GetBinding() = 0 ;
	virtual void __fastcall SetBinding(const _di_ICompiledBinding Binding) = 0 ;
	__property _di_ICompiledBinding Binding = {read=GetBinding, write=SetBinding};
};

__interface  INTERFACE_UUID("{1BC1935C-3E46-4DB4-A56E-C1F15460CE8E}") IDebugBinding  : public System::IInterface 
{
	virtual void __fastcall Dump(const System::DelphiInterface<System::Sysutils::TProc__1<System::UnicodeString> > W) = 0 ;
};

class PASCALIMPLEMENTATION TValueWrapper : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Rtti::TValue FValue;
	
public:
	__fastcall TValueWrapper(const System::Rtti::TValue &AValue);
	System::Rtti::TValue __fastcall GetValue();
	System::Typinfo::PTypeInfo __fastcall GetType();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TValueWrapper() { }
	
private:
	void *__IValue;	// IValue 
	void *__IWrapper;	// IWrapper 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A495F901-72F5-4384-BA50-EC3B4B42F6C2}
	operator _di_IValue()
	{
		_di_IValue intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IValue*(void) { return (IValue*)&__IValue; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {743F6B0A-931A-4EF7-9637-8DF639ABA4A9}
	operator _di_IWrapper()
	{
		_di_IWrapper intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWrapper*(void) { return (IWrapper*)&__IWrapper; }
	#endif
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TLocationWrapper : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	__interface DELPHIINTERFACE TValueGetter;
	typedef System::DelphiInterface<TValueGetter> _di_TValueGetter;
	__interface TValueGetter  : public System::IInterface 
	{
		virtual System::Rtti::TValue __fastcall Invoke() = 0 ;
	};
	
	__interface DELPHIINTERFACE TValueSetter;
	typedef System::DelphiInterface<TValueSetter> _di_TValueSetter;
	__interface TValueSetter  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const System::Rtti::TValue &AValue) = 0 ;
	};
	
	
private:
	enum DECLSPEC_DENUM TWorkMode : unsigned char { wmObjectProperty, wmGetterSetter };
	
	
private:
	System::Rtti::TRttiProperty* FProperty;
	System::Rtti::TRttiIndexedProperty* FIndexedProperty;
	TWorkMode FWorkMode;
	System::TObject* FObject;
#ifndef _WIN64
	System::DynamicArray<System::Rtti::TValue> FArgs;
#else /* _WIN64 */
	System::TArray__1<System::Rtti::TValue> FArgs;
#endif /* _WIN64 */
	System::Typinfo::TTypeInfo *FType;
	_di_TValueGetter FGetter;
	_di_TValueSetter FSetter;
	
public:
	__fastcall TLocationWrapper(System::Typinfo::PTypeInfo AType, const _di_TValueGetter AGetter, const _di_TValueSetter ASetter)/* overload */;
	__fastcall TLocationWrapper(System::TObject* AObject, const System::UnicodeString PropertyName)/* overload */;
#ifndef _WIN64
	__fastcall TLocationWrapper(System::TObject* AObject, const System::UnicodeString PropertyName, const System::DynamicArray<System::Rtti::TValue> Args)/* overload */;
#else /* _WIN64 */
	__fastcall TLocationWrapper(System::TObject* AObject, const System::UnicodeString PropertyName, const System::TArray__1<System::Rtti::TValue> Args)/* overload */;
#endif /* _WIN64 */
	HIDESBASE HRESULT __stdcall QueryInterface(const GUID &IID, /* out */ void *Obj);
	System::Typinfo::PTypeInfo __fastcall GetType();
	System::Rtti::TValue __fastcall GetValue();
	void __fastcall SetValue(const System::Rtti::TValue &AValue);
#ifndef _WIN64
	System::DynamicArray<System::Rtti::TValue> __fastcall GetArgs();
	void __fastcall SetArgs(const System::DynamicArray<System::Rtti::TValue> Args);
#else /* _WIN64 */
	System::TArray__1<System::Rtti::TValue> __fastcall GetArgs();
	void __fastcall SetArgs(const System::TArray__1<System::Rtti::TValue> Args);
#endif /* _WIN64 */
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TLocationWrapper() { }
	
private:
	void *__IArguments;	// IArguments 
	void *__ILocation;	// ILocation 
	void *__IWrapper;	// IWrapper 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {79D93B44-2F1B-4F53-B44D-91913FE68581}
	operator _di_IArguments()
	{
		_di_IArguments intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IArguments*(void) { return (IArguments*)&__IArguments; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {861746E3-740A-4799-BB14-217066C629A8}
	operator _di_ILocation()
	{
		_di_ILocation intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ILocation*(void) { return (ILocation*)&__ILocation; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A495F901-72F5-4384-BA50-EC3B4B42F6C2}
	operator _di_IValue()
	{
		_di_IValue intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IValue*(void) { return (IValue*)&__ILocation; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {743F6B0A-931A-4EF7-9637-8DF639ABA4A9}
	operator _di_IWrapper()
	{
		_di_IWrapper intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IWrapper*(void) { return (IWrapper*)&__IWrapper; }
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
	operator System::IInterface*(void) { return (System::IInterface*)&__IArguments; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TScopeSymbols : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Generics::Collections::TList__1<System::UnicodeString>* FSymbols;
	
protected:
	System::UnicodeString __fastcall GetSymbols(int Index);
	void __fastcall SetSymbols(int Index, const System::UnicodeString Value);
	int __fastcall GetSymbolCount();
	
public:
	__fastcall TScopeSymbols();
	__fastcall virtual ~TScopeSymbols();
	void __fastcall Add(const System::UnicodeString Symbol);
	void __fastcall Remove(const System::UnicodeString Symbol);
	bool __fastcall Contains(const System::UnicodeString Symbol);
	void __fastcall Clear();
	__property System::UnicodeString Symbols[int Index] = {read=GetSymbols, write=SetSymbols};
	__property int SymbolCount = {read=GetSymbolCount, nodefault};
private:
	void *__IScopeSymbols;	// IScopeSymbols 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1FF4BA45-C177-4847-ABFF-5D74D06400B1}
	operator _di_IScopeSymbols()
	{
		_di_IScopeSymbols intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IScopeSymbols*(void) { return (IScopeSymbols*)&__IScopeSymbols; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#ifndef _WIN64
extern DELPHI_PACKAGE System::DynamicArray<System::Rtti::TValue> __fastcall AdaptArguments(const System::DynamicArray<_di_IValue> Source);
#else /* _WIN64 */
extern DELPHI_PACKAGE System::TArray__1<System::Rtti::TValue> __fastcall AdaptArguments(const System::TArray__1<_di_IValue> Source);
#endif /* _WIN64 */
}	/* namespace Evalprotocol */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_EVALPROTOCOL)
using namespace System::Bindings::Evalprotocol;
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
#endif	// System_Bindings_EvalprotocolHPP
