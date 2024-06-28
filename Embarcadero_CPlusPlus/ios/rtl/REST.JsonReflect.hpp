// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.JsonReflect.pas' rev: 34.00 (iOS)

#ifndef Rest_JsonreflectHPP
#define Rest_JsonreflectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.StrUtils.hpp>
#include <System.JSON.hpp>
#include <System.Generics.Collections.hpp>
#include <System.TypInfo.hpp>
#include <System.Rtti.hpp>
#include <System.Classes.hpp>
#include <REST.Json.Types.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Jsonreflect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EConversionError;
template<typename TSerial> class DELPHICLASS TConverter__1;
__interface DELPHIINTERFACE TObjectsConverter;
typedef System::DelphiInterface<TObjectsConverter> _di_TObjectsConverter;
__interface DELPHIINTERFACE TStringsConverter;
typedef System::DelphiInterface<TStringsConverter> _di_TStringsConverter;
__interface DELPHIINTERFACE TTypeObjectsConverter;
typedef System::DelphiInterface<TTypeObjectsConverter> _di_TTypeObjectsConverter;
__interface DELPHIINTERFACE TTypeStringsConverter;
typedef System::DelphiInterface<TTypeStringsConverter> _di_TTypeStringsConverter;
__interface DELPHIINTERFACE TObjectConverter;
typedef System::DelphiInterface<TObjectConverter> _di_TObjectConverter;
__interface DELPHIINTERFACE TStringConverter;
typedef System::DelphiInterface<TStringConverter> _di_TStringConverter;
__interface DELPHIINTERFACE TTypeObjectConverter;
typedef System::DelphiInterface<TTypeObjectConverter> _di_TTypeObjectConverter;
__interface DELPHIINTERFACE TTypeStringConverter;
typedef System::DelphiInterface<TTypeStringConverter> _di_TTypeStringConverter;
__interface DELPHIINTERFACE TObjectsReverter;
typedef System::DelphiInterface<TObjectsReverter> _di_TObjectsReverter;
__interface DELPHIINTERFACE TStringsReverter;
typedef System::DelphiInterface<TStringsReverter> _di_TStringsReverter;
__interface DELPHIINTERFACE TTypeObjectsReverter;
typedef System::DelphiInterface<TTypeObjectsReverter> _di_TTypeObjectsReverter;
__interface DELPHIINTERFACE TTypeStringsReverter;
typedef System::DelphiInterface<TTypeStringsReverter> _di_TTypeStringsReverter;
__interface DELPHIINTERFACE TObjectReverter;
typedef System::DelphiInterface<TObjectReverter> _di_TObjectReverter;
__interface DELPHIINTERFACE TStringReverter;
typedef System::DelphiInterface<TStringReverter> _di_TStringReverter;
__interface DELPHIINTERFACE TTypeObjectReverter;
typedef System::DelphiInterface<TTypeObjectReverter> _di_TTypeObjectReverter;
__interface DELPHIINTERFACE TTypeStringReverter;
typedef System::DelphiInterface<TTypeStringReverter> _di_TTypeStringReverter;
class DELPHICLASS TConverterEvent;
class DELPHICLASS TReverterEvent;
class DELPHICLASS TJSONPopulationCustomizer;
class DELPHICLASS TJSONInterceptor;
class DELPHICLASS JsonReflectAttribute;
class DELPHICLASS TMarshalUnmarshalBase;
template<typename TSerial> class DELPHICLASS TTypeMarshaller__1;
class DELPHICLASS TJSONConverter;
class DELPHICLASS TJSONMarshal;
class DELPHICLASS TJSONUnMarshal;
class DELPHICLASS TSerStringItem;
class DELPHICLASS TSerStringList;
class DELPHICLASS TStringListInterceptor;
class DELPHICLASS TJSONConverters;
class DELPHICLASS TInternalJSONPopulationCustomizer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EConversionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EConversionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EConversionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EConversionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EConversionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EConversionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EConversionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EConversionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EConversionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EConversionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EConversionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EConversionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EConversionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EConversionError() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TSerial> class PASCALIMPLEMENTATION TConverter__1 : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Rest::Json::Types::TJsonIdentCase FIdentCase;
	
protected:
	virtual TSerial __fastcall GetSerializedData() = 0 ;
	
public:
	__fastcall virtual TConverter__1();
	virtual void __fastcall Clear() = 0 ;
	virtual void __fastcall OnRefType(System::UnicodeString TypeName, int id) = 0 ;
	virtual void __fastcall OnTypeStart(System::UnicodeString TypeName) = 0 ;
	virtual void __fastcall OnTypeEnd(System::UnicodeString TypeName) = 0 ;
	virtual void __fastcall OnFieldStart(System::Rtti::TRttiField* Field) = 0 ;
	virtual void __fastcall OnFieldEnd(System::Rtti::TRttiField* Field) = 0 ;
	virtual void __fastcall OnListStart() = 0 ;
	virtual void __fastcall OnListEnd() = 0 ;
	virtual void __fastcall OnString(System::UnicodeString Data) = 0 ;
	virtual void __fastcall OnNumber(System::UnicodeString Data) = 0 ;
	virtual void __fastcall OnBoolean(bool Data) = 0 ;
	virtual void __fastcall OnNull() = 0 ;
	virtual bool __fastcall IsConsistent() = 0 ;
	virtual void __fastcall SetCurrentValue(TSerial Data) = 0 ;
	__property TSerial SerializedData = {read=GetSerializedData};
	__property Rest::Json::Types::TJsonIdentCase IdentCase = {read=FIdentCase, write=FIdentCase, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TConverter__1() { }
	
};


typedef System::DynamicArray<System::TObject*> TListOfObjects;

typedef System::DynamicArray<System::UnicodeString> TListOfStrings;

__interface TObjectsConverter  : public System::IInterface 
{
	virtual TListOfObjects __fastcall Invoke(System::TObject* Data, System::UnicodeString Field) = 0 ;
};

__interface TStringsConverter  : public System::IInterface 
{
	virtual TListOfStrings __fastcall Invoke(System::TObject* Data, System::UnicodeString Field) = 0 ;
};

__interface TTypeObjectsConverter  : public System::IInterface 
{
	virtual TListOfObjects __fastcall Invoke(System::TObject* Data) = 0 ;
};

__interface TTypeStringsConverter  : public System::IInterface 
{
	virtual TListOfStrings __fastcall Invoke(System::TObject* Data) = 0 ;
};

__interface TObjectConverter  : public System::IInterface 
{
	virtual System::TObject* __fastcall Invoke(System::TObject* Data, System::UnicodeString Field) = 0 ;
};

__interface TStringConverter  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall Invoke(System::TObject* Data, System::UnicodeString Field) = 0 ;
};

__interface TTypeObjectConverter  : public System::IInterface 
{
	virtual System::TObject* __fastcall Invoke(System::TObject* Data) = 0 ;
};

__interface TTypeStringConverter  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall Invoke(System::TObject* Data) = 0 ;
};

enum DECLSPEC_DENUM TConverterType : unsigned char { ctObjects, ctStrings, ctTypeObjects, ctTypeStrings, ctObject, ctString, ctTypeObject, ctTypeString };

__interface TObjectsReverter  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* Data, System::UnicodeString Field, TListOfObjects Args) = 0 ;
};

__interface TStringsReverter  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* Data, System::UnicodeString Field, TListOfStrings Args) = 0 ;
};

__interface TTypeObjectsReverter  : public System::IInterface 
{
	virtual System::TObject* __fastcall Invoke(TListOfObjects Data) = 0 ;
};

__interface TTypeStringsReverter  : public System::IInterface 
{
	virtual System::TObject* __fastcall Invoke(TListOfStrings Data) = 0 ;
};

__interface TObjectReverter  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* Data, System::UnicodeString Field, System::TObject* Arg) = 0 ;
};

__interface TStringReverter  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* Data, System::UnicodeString Field, System::UnicodeString Arg) = 0 ;
};

__interface TTypeObjectReverter  : public System::IInterface 
{
	virtual System::TObject* __fastcall Invoke(System::TObject* Data) = 0 ;
};

__interface TTypeStringReverter  : public System::IInterface 
{
	virtual System::TObject* __fastcall Invoke(System::UnicodeString Data) = 0 ;
};

enum DECLSPEC_DENUM TReverterType : unsigned char { rtObjects, rtStrings, rtTypeObjects, rtTypeStrings, rtObject, rtString, rtTypeObject, rtTypeString };

class PASCALIMPLEMENTATION TConverterEvent : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TClass FFieldClassType;
	System::UnicodeString FFieldName;
	TConverterType FConverterType;
	_di_TObjectsConverter FObjectsConverter;
	_di_TStringsConverter FStringsConverter;
	_di_TTypeObjectsConverter FTypeObjectsConverter;
	_di_TTypeStringsConverter FTypeStringsConverter;
	_di_TObjectConverter FObjectConverter;
	_di_TStringConverter FStringConverter;
	_di_TTypeObjectConverter FTypeObjectConverter;
	_di_TTypeStringConverter FTypeStringConverter;
	
protected:
	void __fastcall SetObjectsConverter(_di_TObjectsConverter Converter);
	void __fastcall SetStringsConverter(_di_TStringsConverter Converter);
	void __fastcall SetTypeObjectsConverter(_di_TTypeObjectsConverter Converter);
	void __fastcall SetTypeStringsConverter(_di_TTypeStringsConverter Converter);
	void __fastcall SetObjectConverter(_di_TObjectConverter Converter);
	void __fastcall SetStringConverter(_di_TStringConverter Converter);
	void __fastcall SetTypeObjectConverter(_di_TTypeObjectConverter Converter);
	void __fastcall SetTypeStringConverter(_di_TTypeStringConverter Converter);
	
public:
	__fastcall TConverterEvent()/* overload */;
	__fastcall TConverterEvent(System::TClass AFieldClassType, System::UnicodeString AFieldName)/* overload */;
	bool __fastcall IsTypeConverter();
	__property TConverterType ConverterType = {read=FConverterType, nodefault};
	__property _di_TObjectsConverter ObjectsConverter = {read=FObjectsConverter, write=SetObjectsConverter};
	__property _di_TStringsConverter StringsConverter = {read=FStringsConverter, write=SetStringsConverter};
	__property _di_TTypeObjectsConverter TypeObjectsConverter = {read=FTypeObjectsConverter, write=SetTypeObjectsConverter};
	__property _di_TTypeStringsConverter TypeStringsConverter = {read=FTypeStringsConverter, write=SetTypeStringsConverter};
	__property _di_TObjectConverter ObjectConverter = {read=FObjectConverter, write=SetObjectConverter};
	__property _di_TStringConverter StringConverter = {read=FStringConverter, write=SetStringConverter};
	__property _di_TTypeObjectConverter TypeObjectConverter = {read=FTypeObjectConverter, write=SetTypeObjectConverter};
	__property _di_TTypeStringConverter TypeStringConverter = {read=FTypeStringConverter, write=SetTypeStringConverter};
	__property System::TClass FieldClassType = {read=FFieldClassType};
	__property System::UnicodeString FieldName = {read=FFieldName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TConverterEvent() { }
	
};


class PASCALIMPLEMENTATION TReverterEvent : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::TClass FFieldClassType;
	System::UnicodeString FFieldName;
	TReverterType FReverterType;
	_di_TObjectsReverter FObjectsReverter;
	_di_TStringsReverter FStringsReverter;
	_di_TTypeObjectsReverter FTypeObjectsReverter;
	_di_TTypeStringsReverter FTypeStringsReverter;
	_di_TObjectReverter FObjectReverter;
	_di_TStringReverter FStringReverter;
	_di_TTypeObjectReverter FTypeObjectReverter;
	_di_TTypeStringReverter FTypeStringReverter;
	
protected:
	void __fastcall SetObjectsReverter(_di_TObjectsReverter Reverter);
	void __fastcall SetStringsReverter(_di_TStringsReverter Reverter);
	void __fastcall SetTypeObjectsReverter(_di_TTypeObjectsReverter Reverter);
	void __fastcall SetTypeStringsReverter(_di_TTypeStringsReverter Reverter);
	void __fastcall SetObjectReverter(_di_TObjectReverter Reverter);
	void __fastcall SetStringReverter(_di_TStringReverter Reverter);
	void __fastcall SetTypeObjectReverter(_di_TTypeObjectReverter Reverter);
	void __fastcall SetTypeStringReverter(_di_TTypeStringReverter Reverter);
	
public:
	__fastcall TReverterEvent()/* overload */;
	__fastcall TReverterEvent(System::TClass AFieldClassType, System::UnicodeString AFieldName)/* overload */;
	bool __fastcall IsTypeReverter();
	__property TReverterType ReverterType = {read=FReverterType, nodefault};
	__property _di_TObjectsReverter ObjectsReverter = {read=FObjectsReverter, write=SetObjectsReverter};
	__property _di_TStringsReverter StringsReverter = {read=FStringsReverter, write=SetStringsReverter};
	__property _di_TTypeObjectsReverter TypeObjectsReverter = {read=FTypeObjectsReverter, write=SetTypeObjectsReverter};
	__property _di_TTypeStringsReverter TypeStringsReverter = {read=FTypeStringsReverter, write=SetTypeStringsReverter};
	__property _di_TObjectReverter ObjectReverter = {read=FObjectReverter, write=SetObjectReverter};
	__property _di_TStringReverter StringReverter = {read=FStringReverter, write=SetStringReverter};
	__property _di_TTypeObjectReverter TypeObjectReverter = {read=FTypeObjectReverter, write=SetTypeObjectReverter};
	__property _di_TTypeStringReverter TypeStringReverter = {read=FTypeStringReverter, write=SetTypeStringReverter};
	__property System::TClass FieldClassType = {read=FFieldClassType};
	__property System::UnicodeString FieldName = {read=FFieldName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TReverterEvent() { }
	
};


typedef System::DelphiInterface<System::Sysutils::TFunc__3<System::TObject*,System::Rtti::TRttiField*,bool> > TJSONCanPopulateProc;

class PASCALIMPLEMENTATION TJSONPopulationCustomizer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::DelphiInterface<System::Sysutils::TFunc__3<System::TObject*,System::Rtti::TRttiField*,bool> > FCanPopulate;
	
protected:
	virtual bool __fastcall CanPopulate(System::TObject* Data, System::Rtti::TRttiField* rttiField);
	virtual void __fastcall PrePopulateObjField(System::TObject* Data, System::Rtti::TRttiField* rttiField);
	virtual void __fastcall DoFieldPopulated(System::TObject* Data, System::Rtti::TRttiField* rttiField);
	
public:
	__fastcall TJSONPopulationCustomizer(System::DelphiInterface<System::Sysutils::TFunc__3<System::TObject*,System::Rtti::TRttiField*,bool> > ACanPopulate);
	virtual void __fastcall PrePopulate(System::TObject* Data, const System::Rtti::TRttiContext &rttiContext);
	virtual void __fastcall PostPopulate(System::TObject* Data);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONPopulationCustomizer() { }
	
};


class PASCALIMPLEMENTATION TJSONInterceptor : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TConverterType FConverterType;
	TReverterType FReverterType;
	System::TClass FObjectType;
	bool FMarshalOwner;
	
public:
	virtual TListOfObjects __fastcall ObjectsConverter(System::TObject* Data, System::UnicodeString Field);
	virtual TListOfStrings __fastcall StringsConverter(System::TObject* Data, System::UnicodeString Field);
	virtual TListOfObjects __fastcall TypeObjectsConverter(System::TObject* Data);
	virtual TListOfStrings __fastcall TypeStringsConverter(System::TObject* Data);
	virtual System::TObject* __fastcall ObjectConverter(System::TObject* Data, System::UnicodeString Field);
	virtual System::UnicodeString __fastcall StringConverter(System::TObject* Data, System::UnicodeString Field);
	virtual System::TObject* __fastcall TypeObjectConverter(System::TObject* Data);
	virtual System::UnicodeString __fastcall TypeStringConverter(System::TObject* Data);
	virtual void __fastcall ObjectsReverter(System::TObject* Data, System::UnicodeString Field, TListOfObjects Args);
	virtual void __fastcall StringsReverter(System::TObject* Data, System::UnicodeString Field, TListOfStrings Args);
	virtual System::TObject* __fastcall TypeObjectsReverter(TListOfObjects Data);
	virtual System::TObject* __fastcall TypeStringsReverter(TListOfStrings Data);
	virtual void __fastcall ObjectReverter(System::TObject* Data, System::UnicodeString Field, System::TObject* Arg);
	virtual void __fastcall StringReverter(System::TObject* Data, System::UnicodeString Field, System::UnicodeString Arg);
	virtual System::TObject* __fastcall TypeObjectReverter(System::TObject* Data);
	virtual System::TObject* __fastcall TypeStringReverter(System::UnicodeString Data);
	bool __fastcall IsTypeConverter();
	bool __fastcall IsTypeReverter();
	__property TConverterType ConverterType = {read=FConverterType, write=FConverterType, nodefault};
	__property TReverterType ReverterType = {read=FReverterType, write=FReverterType, nodefault};
	__property bool MarshalOwner = {read=FMarshalOwner, write=FMarshalOwner, nodefault};
	__property System::TClass ObjectType = {read=FObjectType, write=FObjectType};
public:
	/* TObject.Create */ inline __fastcall TJSONInterceptor() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONInterceptor() { }
	
};


class PASCALIMPLEMENTATION JsonReflectAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	bool FMarshalOwner;
	TConverterType FConverterType;
	TReverterType FReverterType;
	System::TClass FInterceptor;
	System::TClass FPopulationCustomizer;
	
public:
	__fastcall JsonReflectAttribute(bool IsMarshalOwned)/* overload */;
	__fastcall JsonReflectAttribute(TConverterType ConverterType, TReverterType ReverterType, System::TClass InterceptorType, System::TClass PopulationCustomizerType, bool IsMarshalOwned)/* overload */;
	TJSONInterceptor* __fastcall JSONInterceptor();
	TJSONPopulationCustomizer* __fastcall JSONPopulationCustomizer();
	__property bool MarshalOwner = {read=FMarshalOwner, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JsonReflectAttribute() { }
	
};


class PASCALIMPLEMENTATION TMarshalUnmarshalBase : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,bool>* FMarshalled;
	Rest::Json::Types::TJsonDateFormat FDateFormat;
	bool FDateTimeIsUTC;
	Rest::Json::Types::TJsonBytesFormat FBytesFormat;
	void __fastcall RegisterJSONMarshalled(System::UnicodeString AComposeKey, bool Marshal)/* overload */;
	
public:
	__classmethod System::UnicodeString __fastcall ComposeKey(System::TClass clazz, System::UnicodeString Field)/* overload */;
	void __fastcall RegisterJSONMarshalled(System::TClass clazz, System::UnicodeString Field, bool Marshal)/* overload */;
	void __fastcall UnregisterJSONMarshalled(System::TClass clazz, System::UnicodeString Field);
	bool __fastcall ShouldMarshal(System::TObject* Data, System::Rtti::TRttiField* rttiField);
	__fastcall TMarshalUnmarshalBase();
	__fastcall virtual ~TMarshalUnmarshalBase();
	__property Rest::Json::Types::TJsonDateFormat DateFormat = {read=FDateFormat, write=FDateFormat, default=0};
	__property bool DateTimeIsUTC = {read=FDateTimeIsUTC, write=FDateTimeIsUTC, default=1};
	__property Rest::Json::Types::TJsonBytesFormat BytesFormat = {read=FBytesFormat, write=FBytesFormat, default=0};
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TSerial> class PASCALIMPLEMENTATION TTypeMarshaller__1 : public TMarshalUnmarshalBase
{
	typedef TMarshalUnmarshalBase inherited;
	
private:
	TConverter__1<TSerial>* FConverter;
	bool FOwnConverter;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TConverterEvent*>* FConverters;
	bool FShareConverters;
	System::Rtti::TRttiContext FRTTICtx;
	bool __fastcall MarshalSimpleField(System::Rtti::TRttiField* rttiField, void * Data);
	void __fastcall ReleaseConvertedObj(System::TObject* AObj, TJSONInterceptor* AConverterEvent);
	void __fastcall MarshalVarValue(const System::Rtti::TValue &Value, System::Rtti::TRttiField* fieldRTTI);
	
protected:
	__classmethod System::UnicodeString __fastcall ComposeTypeName(System::TObject* Data);
	__classmethod void __fastcall DecomposeTypeName(System::UnicodeString TypeName, /* out */ System::UnicodeString &UnitName, /* out */ System::UnicodeString &ClassName);
	TConverterEvent* __fastcall Converter(System::TClass clazz, System::UnicodeString Field);
	bool __fastcall HasConverter(System::TClass clazz, System::UnicodeString Field);
	TJSONInterceptor* __fastcall GetTypeConverter(System::TClass clazz)/* overload */;
	TJSONInterceptor* __fastcall GetTypeConverter(System::Rtti::TRttiType* rttiType)/* overload */;
	TJSONInterceptor* __fastcall GetTypeConverter(System::Rtti::TRttiField* rttiField)/* overload */;
	bool __fastcall HasInterceptor(System::Rtti::TRttiField* rttiField);
	void __fastcall MarshalData(System::TObject* Data);
	void __fastcall MarshalValue(const System::Rtti::TValue &Value, System::Rtti::TRttiField* fieldRTTI = (System::Rtti::TRttiField*)(0x0));
	void __fastcall MarshalConverter(System::TObject* Data, System::UnicodeString Field)/* overload */;
	void __fastcall MarshalConverter(System::TObject* Data, System::UnicodeString Field, TConverterEvent* ConverterEvent)/* overload */;
	void __fastcall MarshalConverter(System::TObject* Data, System::UnicodeString Field, TJSONInterceptor* ConverterEvent)/* overload */;
	void __fastcall MarshalTypeConverter(System::TObject* Data, System::UnicodeString Field, TConverterEvent* ConverterEvent)/* overload */;
	void __fastcall MarshalTypeConverter(System::TObject* Data, System::UnicodeString Field, TJSONInterceptor* ConverterEvent)/* overload */;
	System::Rtti::TRttiField* __fastcall GetFieldType(System::TObject* Data, System::UnicodeString Field);
	
public:
	__fastcall virtual TTypeMarshaller__1(TConverter__1<TSerial>* Converter, bool OwnConverter)/* overload */;
	__fastcall virtual TTypeMarshaller__1(TConverter__1<TSerial>* Converter, bool OwnConverter, System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TConverterEvent*>* Converters)/* overload */;
	__fastcall virtual ~TTypeMarshaller__1();
	virtual TSerial __fastcall Marshal(System::TObject* Data);
	void __fastcall RegisterConverter(System::TClass clazz, System::UnicodeString Field, TConverterEvent* Converter)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, System::UnicodeString Field, _di_TObjectsConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, System::UnicodeString Field, _di_TObjectConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, System::UnicodeString Field, _di_TStringsConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, System::UnicodeString Field, _di_TStringConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, _di_TTypeObjectsConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, _di_TTypeObjectConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, _di_TTypeStringsConverter func)/* overload */;
	void __fastcall RegisterConverter(System::TClass clazz, _di_TTypeStringConverter func)/* overload */;
};


class PASCALIMPLEMENTATION TJSONConverter : public TConverter__1<System::Json::TJSONValue*>
{
	typedef TConverter__1<System::Json::TJSONValue*> inherited;
	
private:
	System::Json::TJSONValue* FRoot;
	System::Generics::Collections::TStack__1<System::Json::TJSONAncestor*>* FStack;
	
protected:
	virtual System::Json::TJSONValue* __fastcall GetSerializedData();
	virtual void __fastcall ProcessData(System::Json::TJSONAncestor* Data);
	System::Json::TJSONAncestor* __fastcall GetCurrent();
	__property System::Json::TJSONAncestor* Current = {read=GetCurrent};
	
public:
	__fastcall virtual TJSONConverter();
	__fastcall virtual ~TJSONConverter();
	virtual void __fastcall Clear();
	System::UnicodeString __fastcall ConvertFieldNameToJson(System::Rtti::TRttiField* const AField)/* overload */;
	System::UnicodeString __fastcall ConvertFieldNameToJson(System::TObject* AObject, const System::UnicodeString AFieldName)/* overload */;
	virtual void __fastcall OnRefType(System::UnicodeString TypeName, int id);
	virtual void __fastcall OnTypeStart(System::UnicodeString TypeName);
	virtual void __fastcall OnTypeEnd(System::UnicodeString TypeName);
	virtual void __fastcall OnFieldStart(System::Rtti::TRttiField* Field);
	virtual void __fastcall OnFieldEnd(System::Rtti::TRttiField* Field);
	virtual void __fastcall OnListStart();
	virtual void __fastcall OnListEnd();
	virtual void __fastcall OnString(System::UnicodeString Data);
	virtual void __fastcall OnNumber(System::UnicodeString Data);
	virtual void __fastcall OnBoolean(bool Data);
	virtual void __fastcall OnNull();
	virtual bool __fastcall IsConsistent();
	virtual void __fastcall SetCurrentValue(System::Json::TJSONValue* Data);
};


class PASCALIMPLEMENTATION TJSONMarshal : public TTypeMarshaller__1<System::Json::TJSONValue*>
{
	typedef TTypeMarshaller__1<System::Json::TJSONValue*> inherited;
	
public:
	__fastcall TJSONMarshal()/* overload */;
	__fastcall virtual TJSONMarshal(TConverter__1<System::Json::TJSONValue*>* Converter, bool OwnConverter)/* overload */;
	__fastcall virtual TJSONMarshal(TConverter__1<System::Json::TJSONValue*>* Converter, bool OwnConverter, System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TConverterEvent*>* Converters)/* overload */;
public:
	/* {REST_JsonReflect}TTypeMarshaller<System_JSON_TJSONValue>.Destroy */ inline __fastcall virtual ~TJSONMarshal() { }
	
};


class PASCALIMPLEMENTATION TJSONUnMarshal : public TMarshalUnmarshalBase
{
	typedef TMarshalUnmarshalBase inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TObject*>* FObjectHash;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TReverterEvent*>* FReverters;
	System::Rtti::TRttiContext FRTTICtx;
	bool FShareReverters;
	__classmethod System::Rtti::TRttiType* __fastcall ObjectType(const System::Rtti::TRttiContext &Ctx, System::UnicodeString TypeName);
	System::UnicodeString __fastcall ConvertFieldNameFromJson(System::TObject* AObject, const System::UnicodeString AFieldName);
	System::Rtti::TValue __fastcall JSONToVarTValue(System::Json::TJSONValue* JsonValue);
	
public:
	__classmethod System::TObject* __fastcall ObjectInstance(const System::Rtti::TRttiContext &Ctx, System::UnicodeString TypeName);
	
protected:
	bool __fastcall HasReverter(System::UnicodeString key);
	TJSONInterceptor* __fastcall FieldReverter(System::Rtti::TRttiField* Field)/* overload */;
	TJSONInterceptor* __fastcall FieldReverter(System::TObject* Data, System::UnicodeString Field)/* overload */;
	TJSONInterceptor* __fastcall FieldTypeReverter(System::Rtti::TRttiType* ctxType)/* overload */;
	TJSONInterceptor* __fastcall FieldTypeReverter(System::TObject* Data, System::UnicodeString Field)/* overload */;
	TReverterEvent* __fastcall Reverter(System::UnicodeString key);
	System::TClass __fastcall ClassTypeOf(System::TObject* Data, System::UnicodeString Field, bool AConvertName = true);
	bool __fastcall HasObject(System::UnicodeString ObjId);
	System::TObject* __fastcall GetObject(System::UnicodeString ObjId);
	System::Rtti::TRttiField* __fastcall GetFieldType(System::TObject* Data, System::UnicodeString Field);
	void __fastcall PopulateFields(System::Json::TJSONObject* JsonFields, System::TObject* Data, TJSONPopulationCustomizer* JsonCustomizer);
	TListOfObjects __fastcall GetArgObjects(System::TClass AClass, System::Json::TJSONArray* JsonArray);
	TListOfStrings __fastcall GetArgStrings(System::Json::TJSONArray* JsonArray);
	System::Rtti::TValue __fastcall JSONToTValue(System::Json::TJSONValue* JsonValue, System::Rtti::TRttiType* rttiType);
	System::Rtti::TValue __fastcall StringToTValue(System::UnicodeString Value, System::Typinfo::PTypeInfo typeInfo);
	void __fastcall RevertType(System::Rtti::TRttiField* recField, void * Instance, TReverterEvent* revEv, System::Json::TJSONValue* jsonFieldVal)/* overload */;
	void __fastcall RevertType(System::Rtti::TRttiField* recField, void * Instance, TJSONInterceptor* revEv, System::Json::TJSONValue* jsonFieldVal)/* overload */;
	
public:
	__fastcall virtual TJSONUnMarshal()/* overload */;
	__fastcall virtual TJSONUnMarshal(System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TReverterEvent*>* Reverters)/* overload */;
	__fastcall virtual ~TJSONUnMarshal();
	System::TObject* __fastcall CreateObject(System::TClass AClass, System::Json::TJSONObject* JsonObj, System::TObject* AObject = (System::TObject*)(0x0));
	bool __fastcall TryCreateObject(System::TClass AClass, System::Json::TJSONObject* JsonObj, /* out */ System::TObject* &AObject);
	void __fastcall RegisterReverter(System::TClass clazz, System::UnicodeString Field, TReverterEvent* Reverter)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, System::UnicodeString Field, _di_TObjectsReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, System::UnicodeString Field, _di_TObjectReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, System::UnicodeString Field, _di_TStringsReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, System::UnicodeString Field, _di_TStringReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, _di_TTypeObjectsReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, _di_TTypeObjectReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, _di_TTypeStringsReverter func)/* overload */;
	void __fastcall RegisterReverter(System::TClass clazz, _di_TTypeStringReverter func)/* overload */;
	void __fastcall SetField(System::TObject* Data, System::UnicodeString Field, System::UnicodeString Value, bool IsNum)/* overload */;
	void __fastcall SetField(System::TObject* Data, System::UnicodeString Field, bool Value)/* overload */;
	void __fastcall SetField(System::TObject* Data, System::UnicodeString Field, System::TObject* Value)/* overload */;
	void __fastcall SetFieldArray(System::TObject* Data, System::UnicodeString Field, System::Json::TJSONArray* Value);
	void __fastcall SetFieldNull(System::TObject* Data, System::UnicodeString Field);
	__classmethod virtual System::Json::TJSONValue* __fastcall TValueToJson(const System::Rtti::TValue &JsonValue);
};


class PASCALIMPLEMENTATION TSerStringItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FString;
	System::TObject* FObject;
	
public:
	__fastcall TSerStringItem(System::UnicodeString AString, System::TObject* AObject);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TSerStringItem() { }
	
};


class PASCALIMPLEMENTATION TSerStringList : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<TSerStringItem*> _TSerStringList__1;
	
	
private:
	_TSerStringList__1 FSerStringItemList;
	bool FSorted;
	System::Types::TDuplicates FDuplicates;
	bool FCaseSensitive;
	
public:
	__fastcall TSerStringList(System::Classes::TStringList* Source);
	__fastcall virtual ~TSerStringList();
	System::Classes::TStringList* __fastcall AsStringList();
};


class PASCALIMPLEMENTATION TStringListInterceptor : public TJSONInterceptor
{
	typedef TJSONInterceptor inherited;
	
public:
	virtual System::TObject* __fastcall TypeObjectConverter(System::TObject* Data);
	virtual System::TObject* __fastcall TypeObjectReverter(System::TObject* Data);
public:
	/* TObject.Create */ inline __fastcall TStringListInterceptor() : TJSONInterceptor() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TStringListInterceptor() { }
	
};


class PASCALIMPLEMENTATION TJSONConverters : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TConverterEvent*>* CFRegConverters;
	static System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TReverterEvent*>* CFRegReverters;
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,bool>* CFRegMarshal;
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod TJSONMarshal* __fastcall GetJSONMarshaler();
	__classmethod TJSONUnMarshal* __fastcall GetJSONUnMarshaler();
	__classmethod void __fastcall AddConverter(TConverterEvent* event);
	__classmethod void __fastcall AddReverter(TReverterEvent* event);
	__classmethod void __fastcall AddMarshalFlag(System::TClass AClass, System::UnicodeString AField, bool Marshal);
	__classmethod void __fastcall ClearMarshalFlag(System::TClass AClass, System::UnicodeString AField);
public:
	/* TObject.Create */ inline __fastcall TJSONConverters() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSONConverters() { }
	
};


class PASCALIMPLEMENTATION TInternalJSONPopulationCustomizer : public TJSONPopulationCustomizer
{
	typedef TJSONPopulationCustomizer inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::Rtti::TRttiField*,System::TObject*>* FBackupCache;
	void __fastcall Cleanup();
	
protected:
	virtual void __fastcall PrePopulateObjField(System::TObject* Data, System::Rtti::TRttiField* rttiField);
	virtual void __fastcall DoFieldPopulated(System::TObject* Data, System::Rtti::TRttiField* rttiField);
	
public:
	__fastcall TInternalJSONPopulationCustomizer(System::DelphiInterface<System::Sysutils::TFunc__3<System::TObject*,System::Rtti::TRttiField*,bool> > ACanPopulate);
	__fastcall virtual ~TInternalJSONPopulationCustomizer();
	virtual void __fastcall PostPopulate(System::TObject* Data);
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TListOfObjects __fastcall JSONObjectPairListConverter(System::TObject* Data, System::UnicodeString Field);
extern DELPHI_PACKAGE TListOfObjects __fastcall JSONArrayElementsConverter(System::TObject* Data, System::UnicodeString Field);
extern DELPHI_PACKAGE void __fastcall JSONObjectPairListReverter(System::TObject* Data, System::UnicodeString Field, TListOfObjects Args);
extern DELPHI_PACKAGE void __fastcall JSONArrayElementsReverter(System::TObject* Data, System::UnicodeString Field, TListOfObjects Args);
extern DELPHI_PACKAGE System::TObject* __fastcall StringListConverter(System::TObject* Data);
extern DELPHI_PACKAGE System::TObject* __fastcall StringListReverter(System::TObject* Ser);
extern DELPHI_PACKAGE bool __fastcall JSONBooleanAttributeValue(System::Rtti::TRttiNamedObject* rttiObject, System::TClass AttributeClass, bool DefaultValue = false);
}	/* namespace Jsonreflect */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_JSONREFLECT)
using namespace Rest::Jsonreflect;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_JsonreflectHPP
