// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Bindings.Outputs.pas' rev: 34.00 (Windows)

#ifndef System_Bindings_OutputsHPP
#define System_Bindings_OutputsHPP

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
#include <System.Classes.hpp>
#include <System.StrUtils.hpp>
#include <System.Bindings.Evaluator.hpp>
#include <System.Bindings.ObjEval.hpp>
#include <System.Bindings.EvalProtocol.hpp>
#include <System.Bindings.EvalSys.hpp>
#include <System.Bindings.Consts.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "System.Bindings.Outputs"

namespace System
{
namespace Bindings
{
namespace Outputs
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBindOutputError;
class DELPHICLASS EBindOutputCallbackError;
class DELPHICLASS EBindConverterError;
class DELPHICLASS TBindingCallbackFactory;
__interface DELPHIINTERFACE TConvertProc;
typedef System::DelphiInterface<TConvertProc> _di_TConvertProc;
__interface DELPHIINTERFACE TConvertProc2;
typedef System::DelphiInterface<TConvertProc2> _di_TConvertProc2;
__interface DELPHIINTERFACE TConvertProc3;
typedef System::DelphiInterface<TConvertProc3> _di_TConvertProc3;
struct TConvertPair;
struct TConverterDescription;
__interface DELPHIINTERFACE IValueRefConverter;
typedef System::DelphiInterface<IValueRefConverter> _di_IValueRefConverter;
class DELPHICLASS TValueRefConverter;
class DELPHICLASS TValueRefConverterFactory;
struct TBindingAssignValueRec;
class DELPHICLASS TBindingOutput;
class DELPHICLASS TConverterUtils;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBindOutputError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindOutputError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindOutputError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindOutputError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindOutputError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindOutputError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindOutputError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindOutputError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindOutputError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindOutputError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindOutputError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindOutputError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindOutputError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindOutputError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBindOutputCallbackError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindOutputCallbackError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindOutputCallbackError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindOutputCallbackError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindOutputCallbackError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindOutputCallbackError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindOutputCallbackError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindOutputCallbackError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindOutputCallbackError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindOutputCallbackError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindOutputCallbackError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindOutputCallbackError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindOutputCallbackError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindOutputCallbackError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBindConverterError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindConverterError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindConverterError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindConverterError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindConverterError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindConverterError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindConverterError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindConverterError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindConverterError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindConverterError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindConverterError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindConverterError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindConverterError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindConverterError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBindingCallbackFactory : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE TBindingCallback;
	typedef System::DelphiInterface<TBindingCallback> _di_TBindingCallback;
	__interface TBindingCallback  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(System::TObject* const Obj, const System::Rtti::TValue &Val) = 0 ;
	};
	
	
private:
	typedef System::Generics::Collections::TList__1<_di_TBindingCallback>* TBindingCallbacksList;
	
	typedef System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TList__1<_di_TBindingCallback>*>* TBindingCallbacks;
	
	
private:
	static System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TList__1<_di_TBindingCallback>*>* FCallbacks;
	__classmethod System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TList__1<_di_TBindingCallback>*>* __fastcall Instance();
	__classmethod System::UnicodeString __fastcall GetPair(const System::UnicodeString ClassType, const System::UnicodeString PropertyName);
	
private:
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void __fastcall RegisterCallback(const System::UnicodeString *ClassTypes, const int ClassTypes_High, const System::UnicodeString *Properties, const int Properties_High, const _di_TBindingCallback PropCallback);
	__classmethod bool __fastcall GetCallback(const System::UnicodeString ClassType, const System::UnicodeString PropertyName, System::Generics::Collections::TList__1<_di_TBindingCallback>* &PropCallbacks);
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TBindingCallbackFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBindingCallbackFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface TConvertProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(const System::Rtti::TValue &InValue, System::Rtti::TValue &OutValue) = 0 ;
};

__interface TConvertProc2  : public System::IInterface 
{
	virtual void __fastcall Invoke(const System::Rtti::TValue &InValue, System::Typinfo::PTypeInfo ATo, System::Rtti::TValue &OutValue) = 0 ;
};

__interface TConvertProc3  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::Rtti::TValue &OutValue) = 0 ;
};

struct DECLSPEC_DRECORD TConvertPair
{
public:
	System::Typinfo::TTypeInfo *FromType;
	System::Typinfo::TTypeInfo *ToType;
	__fastcall TConvertPair(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo);
	TConvertPair() {}
};


struct DECLSPEC_DRECORD TConverterDescription
{
private:
	_di_TConvertProc FConvertProc;
	_di_TConvertProc2 FConvertProc2;
	_di_TConvertProc3 FConvertProc3;
	
private:
	System::UnicodeString FID;
	System::UnicodeString FDisplayName;
	System::UnicodeString FUnitName;
	bool FDefaultEnabled;
	System::Classes::TPersistentClass FFrameworkClass;
	System::UnicodeString FDescription;
	
public:
	__fastcall TConverterDescription(_di_TConvertProc AConvertProc, const System::UnicodeString AID, const System::UnicodeString ADisplayName, const System::UnicodeString AUnitName, bool ADefaultEnabled, const System::UnicodeString ADescription, System::Classes::TPersistentClass AFrameworkClass)/* overload */;
	__fastcall TConverterDescription(_di_TConvertProc2 AConvertProc2, const System::UnicodeString AID, const System::UnicodeString ADisplayName, const System::UnicodeString AUnitName, bool ADefaultEnabled, const System::UnicodeString ADescription, System::Classes::TPersistentClass AFrameworkClass)/* overload */;
	__fastcall TConverterDescription(_di_TConvertProc3 AConvertProc3, const System::UnicodeString AID, const System::UnicodeString ADisplayName, const System::UnicodeString AUnitName, bool ADefaultEnabled, const System::UnicodeString ADescription, System::Classes::TPersistentClass AFrameworkClass)/* overload */;
	__property System::UnicodeString ID = {read=FID};
	__property System::UnicodeString DisplayName = {read=FDisplayName};
	__property System::UnicodeString UnitName = {read=FUnitName};
	__property bool DefaultEnabled = {read=FDefaultEnabled};
	__property System::Classes::TPersistentClass FrameWorkClass = {read=FFrameworkClass};
	__property System::UnicodeString Description = {read=FDescription};
	TConverterDescription() {}
};


__interface IValueRefConverter  : public System::IInterface 
{
	virtual bool __fastcall CanConvert(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo) = 0 ;
	virtual void __fastcall Convert(const System::Rtti::TValue &InValue, System::Typinfo::PTypeInfo ATo, System::Rtti::TValue &OutValue) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TValueRefConverter : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	typedef System::Generics::Collections::TDictionary__2<TConvertPair,TConverterDescription>* TValueConvDict;
	
	
private:
	System::Generics::Collections::TDictionary__2<TConvertPair,TConverterDescription>* FConversions;
	System::Sysutils::TStringBuilder* FDuplicates;
	
public:
	__fastcall TValueRefConverter();
	__fastcall virtual ~TValueRefConverter();
	__property System::Generics::Collections::TDictionary__2<TConvertPair,TConverterDescription>* Converters = {read=FConversions};
	void __fastcall AddConversion(const TConvertPair &ConvPair, const TConverterDescription &AConverter)/* overload */;
#ifndef _WIN64
	void __fastcall AddConversion(System::DynamicArray<TConvertPair> ConvPairs, const TConverterDescription &AConverter)/* overload */;
#else /* _WIN64 */
	void __fastcall AddConversion(System::TArray__1<TConvertPair> ConvPairs, const TConverterDescription &AConverter)/* overload */;
#endif /* _WIN64 */
	void __fastcall ClearConverters();
	bool __fastcall CanConvert(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo);
	_di_TConvertProc2 __fastcall GetConverter(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo, bool FindBestMatch = true);
	void __fastcall Convert(const System::Rtti::TValue &InValue, System::Typinfo::PTypeInfo ATo, System::Rtti::TValue &OutValue);
private:
	void *__IValueRefConverter;	// IValueRefConverter 
	
public:
	operator IValueRefConverter*(void) { return (IValueRefConverter*)&__IValueRefConverter; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TValueRefConverterFactory : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::Generics::Collections::TPair__2<System::Generics::Collections::TList__1<TConvertPair>*,TConverterDescription> TConverterValuePair;
	
	typedef System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Generics::Collections::TPair__2<System::Generics::Collections::TList__1<TConvertPair>*,TConverterDescription> >* TNamedOutputConverters;
	
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Generics::Collections::TPair__2<System::Generics::Collections::TList__1<TConvertPair>*,TConverterDescription> >* FRegisteredConversions;
	static System::Generics::Collections::TObjectList__1<System::TObject*>* FFreeList;
	static _di_IValueRefConverter FOutputConverter;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void __fastcall RegisterConversion(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo, const TConverterDescription &AConverter)/* overload */;
	__classmethod void __fastcall UnRegisterConversion(const System::UnicodeString ConverterID)/* overload */;
	__classmethod void __fastcall UnRegisterConversion(System::Typinfo::PTypeInfo AFrom, System::Typinfo::PTypeInfo ATo)/* overload */;
	__classmethod bool __fastcall HasConverter(const System::UnicodeString ConverterID);
	__classmethod void __fastcall RegisterConversion(System::Typinfo::PTypeInfo *AFrom, const int AFrom_High, System::Typinfo::PTypeInfo *ATo, const int ATo_High, const TConverterDescription &AConverter)/* overload */;
#ifndef _WIN64
	__classmethod void __fastcall RegisterConversion(System::DynamicArray<System::Typinfo::PTypeInfo> AFrom, System::DynamicArray<System::Typinfo::PTypeInfo> ATo, const TConverterDescription &AConverter)/* overload */;
#else /* _WIN64 */
	__classmethod void __fastcall RegisterConversion(System::TArray__1<System::Typinfo::PTypeInfo> AFrom, System::TArray__1<System::Typinfo::PTypeInfo> ATo, const TConverterDescription &AConverter)/* overload */;
#endif /* _WIN64 */
	__classmethod void __fastcall UnRegisterConversion(System::Typinfo::PTypeInfo *AFrom, const int AFrom_High, System::Typinfo::PTypeInfo *ATo, const int ATo_High)/* overload */;
#ifndef _WIN64
	__classmethod void __fastcall UnRegisterConversion(System::DynamicArray<System::Typinfo::PTypeInfo> AFrom, System::DynamicArray<System::Typinfo::PTypeInfo> ATo)/* overload */;
#else /* _WIN64 */
	__classmethod void __fastcall UnRegisterConversion(System::TArray__1<System::Typinfo::PTypeInfo> AFrom, System::TArray__1<System::Typinfo::PTypeInfo> ATo)/* overload */;
#endif /* _WIN64 */
	__classmethod void __fastcall ClearRegisteredConverters();
#ifndef _WIN64
	__classmethod TValueRefConverter* __fastcall GetConverter(System::DynamicArray<System::UnicodeString> ConverterIDs);
	__classmethod System::DynamicArray<TConverterDescription> __fastcall GetConverterDescriptions();
#else /* _WIN64 */
	__classmethod TValueRefConverter* __fastcall GetConverter(System::TArray__1<System::UnicodeString> ConverterIDs);
	__classmethod System::TArray__1<TConverterDescription> __fastcall GetConverterDescriptions();
#endif /* _WIN64 */
	__classmethod System::UnicodeString __fastcall GetConverterUnitName(const System::UnicodeString ConverterID);
	__classmethod System::Classes::TPersistentClass __fastcall GetConverterFrameworkClass(const System::UnicodeString ConverterID);
	__classmethod _di_IValueRefConverter __fastcall GetOutputConverter();
public:
	/* TObject.Create */ inline __fastcall TValueRefConverterFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TValueRefConverterFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DelphiInterface<System::Sysutils::TProc__1<System::Rtti::TValue> > TBindingSetValueEvent;

struct DECLSPEC_DRECORD TBindingAssignValueRec
{
public:
	System::TObject* Expression;
	System::TObject* OutObj;
	System::UnicodeString OutProp;
	__fastcall TBindingAssignValueRec(System::TObject* Expr, System::TObject* Obj, System::UnicodeString Prop);
	TBindingAssignValueRec() {}
};


typedef void __fastcall (__closure *TBindingAssigningValueEvent)(const TBindingAssignValueRec &AssignValueRec, System::Rtti::TValue &Value, bool &Handled);

typedef void __fastcall (__closure *TBindingAssignedValueEvent)(const TBindingAssignValueRec &AssignValueRec, const System::Rtti::TValue &Value);

typedef void __fastcall (__closure *TBindingEvalErrorEvent)(System::Sysutils::Exception* AException);

typedef void __fastcall (__closure *TBindingLocationUpdatedEvent)(System::Bindings::Evalprotocol::_di_ILocation AOldLocation, System::Bindings::Evalprotocol::_di_ILocation ANewLocation);

typedef System::DelphiInterface<System::Sysutils::TFunc__1<System::Bindings::Evalprotocol::_di_IValue> > TBindOutValueFunc;

class PASCALIMPLEMENTATION TBindingOutput : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef System::Generics::Collections::TPair__2<System::TObject*,System::UnicodeString> TOutputPair;
	
	struct DECLSPEC_DRECORD TLocationRec
	{
	public:
		System::Bindings::Evalprotocol::_di_ILocation Location;
		bool IsExpression;
		System::_di_IInterface Notifier;
		System::Bindings::Evalprotocol::_di_ICompiledBinding CompiledBinding;
		System::Bindings::Evalprotocol::_di_IScope Scope;
		__fastcall TLocationRec(const System::Bindings::Evalprotocol::_di_ILocation ALocation, const System::_di_IInterface ANotifier, const System::Bindings::Evalprotocol::_di_ICompiledBinding ACompiledBinding, const System::Bindings::Evalprotocol::_di_IScope AScope, const bool AIsExpression);
		TLocationRec() {}
	};
	
	
	typedef System::Generics::Collections::TList__1<TLocationRec>* TLocations;
	
	typedef System::Generics::Collections::TPair__2<System::Bindings::Evalprotocol::_di_ILocation,System::Generics::Collections::TPair__2<System::TObject*,System::UnicodeString> > TDestinationPair;
	
	typedef System::Generics::Collections::TDictionary__2<System::Bindings::Evalprotocol::_di_ILocation,System::Generics::Collections::TPair__2<System::TObject*,System::UnicodeString> >* TDestinations;
	
	typedef System::Generics::Collections::TList__1<System::DelphiInterface<System::Sysutils::TProc__1<System::Rtti::TValue> > >* TOutputProcs;
	
	enum DECLSPEC_DENUM TOption : unsigned char { opNotify };
	
	typedef System::Set<TOption, TOption::opNotify, TOption::opNotify> TOptions;
	
	
private:
	System::TObject* FOwner;
	System::Generics::Collections::TDictionary__2<System::Bindings::Evalprotocol::_di_ILocation,System::Generics::Collections::TPair__2<System::TObject*,System::UnicodeString> >* FOutputs;
	System::Generics::Collections::TList__1<TLocationRec>* FLocations;
	System::Generics::Collections::TList__1<System::DelphiInterface<System::Sysutils::TProc__1<System::Rtti::TValue> > >* FOutputProcs;
	TBindingAssigningValueEvent FAssigningValueEvent;
	TBindingAssignedValueEvent FAssignedValueEvent;
	TBindingEvalErrorEvent FEvalErrorEvent;
	TBindingLocationUpdatedEvent FLocationUpdatedEvent;
	_di_IValueRefConverter FValueConverter;
	System::Generics::Collections::TList__1<System::UnicodeString>* FOutputConverterIDs;
	bool FNotify;
	System::Bindings::Evalprotocol::_di_IPreparedWrappers FPreparedWrappers;
	
protected:
	TLocationRec __fastcall MakeLocation(System::TObject* AObject, const System::UnicodeString PropertyName)/* overload */;
	bool __fastcall MakeLocation(System::Bindings::Evalprotocol::_di_IScope Scope, const System::UnicodeString Expr, /* out */ TLocationRec &LocationRec)/* overload */;
	bool __fastcall UpdateOutputLocation(TLocationRec &LocationRec);
	System::Bindings::Evalprotocol::_di_IScope __fastcall MakeObjScope(System::TObject* const Obj);
	
public:
	__fastcall TBindingOutput(System::TObject* AOwner, TOptions AOptions);
	__fastcall virtual ~TBindingOutput();
	void __fastcall AddProc(System::DelphiInterface<System::Sysutils::TProc__1<System::Rtti::TValue> > AProc);
	void __fastcall Add(System::Bindings::Evalprotocol::_di_IScope AScope, const System::UnicodeString Expression)/* overload */;
	void __fastcall Add(System::TObject* AObject, const System::UnicodeString PropertyName)/* overload */;
	void __fastcall SetValue(System::TObject* AExpression, const System::DelphiInterface<System::Sysutils::TFunc__1<System::Bindings::Evalprotocol::_di_IValue> > ValueFunc);
	void __fastcall AddConverter(const System::UnicodeString ConverterID);
	bool __fastcall GetLocationRec(const System::Bindings::Evalprotocol::_di_ILocation Location, /* out */ TLocationRec &LocationRec);
	__property System::TObject* Owner = {read=FOwner};
	__property System::Generics::Collections::TDictionary__2<System::Bindings::Evalprotocol::_di_ILocation,System::Generics::Collections::TPair__2<System::TObject*,System::UnicodeString> >* Destinations = {read=FOutputs};
	__property System::Generics::Collections::TList__1<System::DelphiInterface<System::Sysutils::TProc__1<System::Rtti::TValue> > >* Procs = {read=FOutputProcs};
	__property _di_IValueRefConverter ValueConverter = {read=FValueConverter, write=FValueConverter};
	__property bool Notify = {read=FNotify, write=FNotify, nodefault};
	__property TBindingAssignedValueEvent OnAssignedValue = {read=FAssignedValueEvent, write=FAssignedValueEvent};
	__property TBindingAssigningValueEvent OnAssigningValue = {read=FAssigningValueEvent, write=FAssigningValueEvent};
	__property TBindingEvalErrorEvent OnEvalErrorEvent = {read=FEvalErrorEvent, write=FEvalErrorEvent};
	__property TBindingLocationUpdatedEvent OnLocationUpdated = {read=FLocationUpdatedEvent, write=FLocationUpdatedEvent};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TConverterUtils : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static void __fastcall AnsiStringToAnsiChar(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToAnsiChar(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall BoolToString(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall BoolToVariant(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall BoolToInteger(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall BoolToFloat(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall DateTimeToString(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall FloatToInteger(const System::Rtti::TValue &I, System::Typinfo::PTypeInfo ATo, System::Rtti::TValue &O);
	static void __fastcall FloatToString(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall FloatToVariant(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall FloatToBool(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall IntegerToString(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall IntToVariant(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall IntegerToBool(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall NilToBoolean(System::Rtti::TValue &O);
	static void __fastcall NilToDateTime(System::Rtti::TValue &O);
	static void __fastcall NilToNumber(System::Rtti::TValue &O);
	static void __fastcall NilToString(System::Rtti::TValue &O);
	static void __fastcall NilToTStrings(System::Rtti::TValue &O);
	static void __fastcall NilToVariant(System::Rtti::TValue &O);
	static void __fastcall PersistentToPersistent(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall PersistentToString(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringsToString(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToBool(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToChar(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToDate(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToDateTime(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToFloat(const System::Rtti::TValue &I, System::Typinfo::PTypeInfo ATo, System::Rtti::TValue &O);
	static void __fastcall StringToInteger(const System::Rtti::TValue &I, System::Typinfo::PTypeInfo ATo, System::Rtti::TValue &O);
	static void __fastcall StringToStrings(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToTime(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall StringToVariant(const System::Rtti::TValue &I, System::Rtti::TValue &O);
	static void __fastcall VariantToBool(const System::Rtti::TValue &I, System::Rtti::TValue &O);
public:
	/* TObject.Create */ inline __fastcall TConverterUtils() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TConverterUtils() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool GCollectAllDups;
}	/* namespace Outputs */
}	/* namespace Bindings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_BINDINGS_OUTPUTS)
using namespace System::Bindings::Outputs;
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
#endif	// System_Bindings_OutputsHPP
