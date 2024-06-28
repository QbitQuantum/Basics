// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.Serializers.pas' rev: 34.00 (Windows)

#ifndef System_Json_SerializersHPP
#define System_Json_SerializersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <System.Rtti.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.Readers.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
namespace Serializers
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EJsonSerializationException;
class DELPHICLASS JsonConverterAttribute;
class DELPHICLASS JsonIgnoreAttribute;
class DELPHICLASS JsonNameAttribute;
class DELPHICLASS JsonInAttribute;
class DELPHICLASS JsonObjectHandlingAttribute;
class DELPHICLASS JsonObjectOwnership;
class DELPHICLASS JsonSerializeAttribute;
class DELPHICLASS TJsonConverter;
__interface DELPHIINTERFACE IJsonCreator;
typedef System::DelphiInterface<IJsonCreator> _di_IJsonCreator;
class DELPHICLASS TJsonObjectCreator;
class DELPHICLASS TJsonRecordCreator;
__interface DELPHIINTERFACE IJsonAttributeProvider;
typedef System::DelphiInterface<IJsonAttributeProvider> _di_IJsonAttributeProvider;
class DELPHICLASS TJsonInlineAttributes;
class DELPHICLASS TJsonDynamicAttributes;
class DELPHICLASS TJsonInlineAttributeProvider;
class DELPHICLASS TJsonDynamicAttributeProvider;
__interface DELPHIINTERFACE IJsonValueProvider;
typedef System::DelphiInterface<IJsonValueProvider> _di_IJsonValueProvider;
class DELPHICLASS TJsonValueProvider;
class DELPHICLASS TJsonFieldValueProvider;
class DELPHICLASS TJsonPropertyValueProvider;
class DELPHICLASS TJsonContract;
class DELPHICLASS TJsonPrimitiveContract;
class DELPHICLASS TJsonObjectContract;
class DELPHICLASS TJsonArrayContract;
class DELPHICLASS TJsonClassContract;
class DELPHICLASS TJsonConverterContract;
class DELPHICLASS TJsonProperty;
__interface DELPHIINTERFACE IJsonContractResolver;
typedef System::DelphiInterface<IJsonContractResolver> _di_IJsonContractResolver;
class DELPHICLASS TJsonDefaultContractResolver;
class DELPHICLASS TJsonDynamicContractResolver;
__interface DELPHIINTERFACE IJsonTypeResolver;
typedef System::DelphiInterface<IJsonTypeResolver> _di_IJsonTypeResolver;
class DELPHICLASS TJsonDefaultTypeResolver;
class DELPHICLASS TJsonSerializer;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EJsonSerializationException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJsonSerializationException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJsonSerializationException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJsonSerializationException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJsonSerializationException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJsonSerializationException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJsonSerializationException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJsonSerializationException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJsonSerializationException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJsonSerializationException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJsonSerializationException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJsonSerializationException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJsonSerializationException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJsonSerializationException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TJsonMemberSerialization : unsigned char { Fields, Public, In };

enum class DECLSPEC_DENUM TJsonObjectHandling : unsigned char { Auto, Reuse, Replace };

enum class DECLSPEC_DENUM TJsonObjectOwnership : unsigned char { Auto, Owned, NotOwned };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonConverterAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::TClass FValue;
	
public:
	__fastcall JsonConverterAttribute(const System::TClass AValue);
	__property System::TClass Value = {read=FValue};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JsonConverterAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonIgnoreAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
public:
	/* TObject.Create */ inline __fastcall JsonIgnoreAttribute() : System::TCustomAttribute() { }
	/* TObject.Destroy */ inline __fastcall virtual ~JsonIgnoreAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonNameAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::UnicodeString FValue;
	
public:
	__fastcall JsonNameAttribute(const System::UnicodeString AValue);
	__property System::UnicodeString Value = {read=FValue};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JsonNameAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonInAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
public:
	/* TObject.Create */ inline __fastcall JsonInAttribute() : System::TCustomAttribute() { }
	/* TObject.Destroy */ inline __fastcall virtual ~JsonInAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonObjectHandlingAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	TJsonObjectHandling FValue;
	
public:
	__fastcall JsonObjectHandlingAttribute(const TJsonObjectHandling AValue);
	__property TJsonObjectHandling Value = {read=FValue, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JsonObjectHandlingAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonObjectOwnership : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	TJsonObjectOwnership FValue;
	
public:
	__fastcall JsonObjectOwnership(const TJsonObjectOwnership AValue);
	__property TJsonObjectOwnership Value = {read=FValue, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JsonObjectOwnership() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION JsonSerializeAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	TJsonMemberSerialization FValue;
	
public:
	__fastcall JsonSerializeAttribute(TJsonMemberSerialization AValue);
	__property TJsonMemberSerialization Value = {read=FValue, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JsonSerializeAttribute() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonConverter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual bool __fastcall CanConvert(System::Typinfo::PTypeInfo ATypeInf) = 0 ;
	virtual bool __fastcall CanRead();
	virtual bool __fastcall CanWrite();
	virtual System::Rtti::TValue __fastcall ReadJson(System::Json::Readers::TJsonReader* const AReader, System::Typinfo::PTypeInfo ATypeInf, const System::Rtti::TValue &AExistingValue, TJsonSerializer* const ASerializer) = 0 ;
	virtual void __fastcall WriteJson(System::Json::Writers::TJsonWriter* const AWriter, const System::Rtti::TValue &AValue, TJsonSerializer* const ASerializer) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TJsonConverter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonConverter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IJsonCreator  : public System::IInterface 
{
	virtual System::Rtti::TValue __fastcall Invoke(const System::Rtti::TValue *Params, const int Params_High) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonObjectCreator : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::TClass FMetaClass;
	System::Rtti::TRttiMethod* FConstructor;
	
public:
	__fastcall TJsonObjectCreator(const System::TClass AMetaClass, System::Rtti::TRttiMethod* const AConstructor);
	System::Rtti::TValue __fastcall Invoke(const System::Rtti::TValue *Params, const int Params_High);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonObjectCreator() { }
	
private:
	void *__IJsonCreator;	// IJsonCreator 
	
public:
	operator IJsonCreator*(void) { return (IJsonCreator*)&__IJsonCreator; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonRecordCreator : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Typinfo::TTypeInfo *FTypeInf;
	System::Rtti::TRttiMethod* FParametrizedConstructor;
	
public:
	__fastcall TJsonRecordCreator(System::Typinfo::PTypeInfo ATypeInf, System::Rtti::TRttiMethod* const AParametrizedConstructor);
	System::Rtti::TValue __fastcall Invoke(const System::Rtti::TValue *Params, const int Params_High);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonRecordCreator() { }
	
private:
	void *__IJsonCreator;	// IJsonCreator 
	
public:
	operator IJsonCreator*(void) { return (IJsonCreator*)&__IJsonCreator; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IJsonAttributeProvider  : public System::IInterface 
{
	virtual System::TCustomAttribute* __fastcall GetAttribute(const System::TClass AAttributeClass, bool AInherit = false) = 0 ;
};

typedef System::Generics::Collections::TPair__2<System::Rtti::TRttiObject*,System::TClass> TAttrKey;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonInlineAttributes : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::Rtti::TRttiObject*,bool>* FCachedObjects;
	static System::Generics::Collections::TDictionary__2<System::Generics::Collections::TPair__2<System::Rtti::TRttiObject*,System::TClass>,System::TCustomAttribute*>* FAttributes;
	static void __fastcall LoadAttributes(System::Rtti::TRttiObject* const ARttiObject);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	static System::TCustomAttribute* __fastcall GetAttribute(System::Rtti::TRttiObject* const ARttiObject, const System::TClass AAttributeClass, bool AInherit = false);
public:
	/* TObject.Create */ inline __fastcall TJsonInlineAttributes() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonInlineAttributes() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonDynamicAttributes : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TObjectDictionary__2<System::Generics::Collections::TPair__2<System::Rtti::TRttiObject*,System::TClass>,System::TCustomAttribute*>* FAttributes;
	
public:
	__fastcall TJsonDynamicAttributes();
	__fastcall virtual ~TJsonDynamicAttributes();
	void __fastcall Clear();
	void __fastcall AddAttribute(System::Rtti::TRttiObject* const ARttiObject, System::TCustomAttribute* const AAttribute);
	System::TCustomAttribute* __fastcall GetAttribute(System::Rtti::TRttiObject* const ARttiObject, const System::TClass AAttributeClass, bool AInherit = false);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonInlineAttributeProvider : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Rtti::TRttiObject* FRttiObject;
	
public:
	__fastcall TJsonInlineAttributeProvider(System::Rtti::TRttiObject* const ARttiObject);
	System::TCustomAttribute* __fastcall GetAttribute(const System::TClass AAttributeClass, bool AInherit);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonInlineAttributeProvider() { }
	
private:
	void *__IJsonAttributeProvider;	// IJsonAttributeProvider 
	
public:
	operator IJsonAttributeProvider*(void) { return (IJsonAttributeProvider*)&__IJsonAttributeProvider; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonDynamicAttributeProvider : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Rtti::TRttiObject* FRttiObject;
	TJsonDynamicAttributes* FDynamicAttributes;
	
public:
	__fastcall TJsonDynamicAttributeProvider(System::Rtti::TRttiObject* const ARttiObject, TJsonDynamicAttributes* const ADynamicAttributes);
	System::TCustomAttribute* __fastcall GetAttribute(const System::TClass AttrClass, bool AInherit = false);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonDynamicAttributeProvider() { }
	
private:
	void *__IJsonAttributeProvider;	// IJsonAttributeProvider 
	
public:
	operator IJsonAttributeProvider*(void) { return (IJsonAttributeProvider*)&__IJsonAttributeProvider; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IJsonValueProvider  : public System::IInterface 
{
	virtual System::Rtti::TValue __fastcall GetValue(const System::Rtti::TValue &AInstance) = 0 ;
	virtual void __fastcall SetValue(const System::Rtti::TValue &AInstance, const System::Rtti::TValue &Value) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonValueProvider : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	virtual System::Rtti::TValue __fastcall InternalGetValue(const void * AInstance) = 0 ;
	virtual void __fastcall InternalSetValue(const void * AInstance, const System::Rtti::TValue &AValue) = 0 ;
	
public:
	System::Rtti::TValue __fastcall GetValue(const System::Rtti::TValue &AInstance);
	void __fastcall SetValue(const System::Rtti::TValue &AInstance, const System::Rtti::TValue &AValue);
public:
	/* TObject.Create */ inline __fastcall TJsonValueProvider() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonValueProvider() { }
	
private:
	void *__IJsonValueProvider;	// IJsonValueProvider 
	
public:
	operator IJsonValueProvider*(void) { return (IJsonValueProvider*)&__IJsonValueProvider; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonFieldValueProvider : public TJsonValueProvider
{
	typedef TJsonValueProvider inherited;
	
private:
	System::Rtti::TRttiField* FRttiField;
	virtual System::Rtti::TValue __fastcall InternalGetValue(const void * AInstance);
	virtual void __fastcall InternalSetValue(const void * AInstance, const System::Rtti::TValue &AValue);
	
public:
	__fastcall TJsonFieldValueProvider(System::Rtti::TRttiField* const ARttiField);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonFieldValueProvider() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonPropertyValueProvider : public TJsonValueProvider
{
	typedef TJsonValueProvider inherited;
	
private:
	System::Rtti::TRttiProperty* FRttiProperty;
	virtual System::Rtti::TValue __fastcall InternalGetValue(const void * AInstance);
	virtual void __fastcall InternalSetValue(const void * AInstance, const System::Rtti::TValue &AValue);
	
public:
	__fastcall TJsonPropertyValueProvider(System::Rtti::TRttiProperty* const ARttiProperty);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonPropertyValueProvider() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TJsonContractType : unsigned char { Object, Class, Array, Primitive, Converter };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonContract : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TJsonConverter* FConverter;
	System::Typinfo::TTypeInfo *FTypeInf;
	bool FIgnored;
	bool FIsReference;
	TJsonContractType FContractType;
	_di_IJsonAttributeProvider FAttributeProvider;
	bool FSealed;
	
public:
	__fastcall TJsonContract(System::Typinfo::PTypeInfo ATypeInf);
	__property TJsonConverter* Converter = {read=FConverter, write=FConverter};
	__property TJsonContractType ContractType = {read=FContractType, nodefault};
	__property bool Ignored = {read=FIgnored, write=FIgnored, nodefault};
	__property bool IsReference = {read=FIsReference, write=FIsReference, nodefault};
	__property System::Typinfo::PTypeInfo TypeInf = {read=FTypeInf};
	__property _di_IJsonAttributeProvider AttributeProvider = {read=FAttributeProvider, write=FAttributeProvider};
	__property bool Sealed = {read=FSealed, write=FSealed, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonContract() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TJsonPrimitiveKind : unsigned char { Int8, UInt8, Int16, UInt16, Int32, UInt32, Int64, UInt64, Single, Double, Extended, Comp, Currency, String, Char, Boolean, Enumeration, Set, DateTime };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonPrimitiveContract : public TJsonContract
{
	typedef TJsonContract inherited;
	
private:
	TJsonPrimitiveKind FKind;
	
public:
	__fastcall TJsonPrimitiveContract(System::Typinfo::PTypeInfo ATypeInf, TJsonPrimitiveKind AKind);
	__property TJsonPrimitiveKind Kind = {read=FKind, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonPrimitiveContract() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonObjectContract : public TJsonContract
{
	typedef TJsonContract inherited;
	
private:
	System::Generics::Collections::TObjectList__1<TJsonProperty*>* FProperties;
	TJsonMemberSerialization FMemberSerialization;
	_di_IJsonCreator FDefaultCreator;
	
public:
	__fastcall TJsonObjectContract(System::Typinfo::PTypeInfo ATypeInf);
	__fastcall virtual ~TJsonObjectContract();
	TJsonProperty* __fastcall GetClosestMatchProperty(const System::UnicodeString AName);
	__property System::Generics::Collections::TObjectList__1<TJsonProperty*>* Properties = {read=FProperties};
	__property TJsonMemberSerialization MemberSerialization = {read=FMemberSerialization, write=FMemberSerialization, nodefault};
	__property _di_IJsonCreator DefaultCreator = {read=FDefaultCreator, write=FDefaultCreator};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonArrayContract : public TJsonContract
{
	typedef TJsonContract inherited;
	
private:
	TJsonContract* FItemContract;
	System::Typinfo::PTypeInfo __fastcall GetArrayType();
	
public:
	__fastcall TJsonArrayContract(System::Typinfo::PTypeInfo ATypeInf);
	__property System::Typinfo::PTypeInfo ArrayType = {read=GetArrayType};
	__property TJsonContract* ItemContract = {read=FItemContract, write=FItemContract};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonArrayContract() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonClassContract : public TJsonContract
{
	typedef TJsonContract inherited;
	
public:
	__fastcall TJsonClassContract(System::Typinfo::PTypeInfo ATypeInf);
	System::TClass __fastcall ResolveClassByName(const System::UnicodeString Name);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonClassContract() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonConverterContract : public TJsonContract
{
	typedef TJsonContract inherited;
	
public:
	__fastcall TJsonConverterContract(System::Typinfo::PTypeInfo ATypeInf);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonConverterContract() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonProperty : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TJsonContract* FContract;
	TJsonConverter* FConverter;
	bool FIgnored;
	System::UnicodeString FName;
	System::Typinfo::TTypeInfo *FParentType;
	bool FReadable;
	System::Typinfo::TTypeInfo *FTypeInf;
	bool FWritable;
	_di_IJsonValueProvider FValueProvider;
	_di_IJsonAttributeProvider FAttributeProvider;
	TJsonObjectHandling FObjectHandling;
	TJsonObjectOwnership FObjectOwnership;
	System::UnicodeString FUnderlyingName;
	
public:
	__property System::Typinfo::PTypeInfo TypeInf = {read=FTypeInf, write=FTypeInf};
	__property TJsonContract* Contract = {read=FContract, write=FContract};
	__property TJsonConverter* Converter = {read=FConverter, write=FConverter};
	__property bool Ignored = {read=FIgnored, write=FIgnored, nodefault};
	__property System::UnicodeString Name = {read=FName, write=FName};
	__property System::Typinfo::PTypeInfo ParentType = {read=FParentType, write=FParentType};
	__property bool Readable = {read=FReadable, write=FReadable, nodefault};
	__property bool Writable = {read=FWritable, write=FWritable, nodefault};
	__property _di_IJsonValueProvider ValueProvider = {read=FValueProvider, write=FValueProvider};
	__property _di_IJsonAttributeProvider AttributeProvider = {read=FAttributeProvider, write=FAttributeProvider};
	__property TJsonObjectHandling ObjectHandling = {read=FObjectHandling, write=FObjectHandling, nodefault};
	__property TJsonObjectOwnership ObjectOwnership = {read=FObjectOwnership, write=FObjectOwnership, nodefault};
	__property System::UnicodeString UnderlyingName = {read=FUnderlyingName, write=FUnderlyingName};
public:
	/* TObject.Create */ inline __fastcall TJsonProperty() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonProperty() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IJsonContractResolver  : public System::IInterface 
{
	virtual TJsonContract* __fastcall ResolveContract(System::Typinfo::PTypeInfo ATypeInf) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonDefaultContractResolver : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	TJsonMemberSerialization FDefaultMemberSerialization;
	System::Generics::Collections::TDictionary__2<System::TClass,TJsonConverter*>* FCachedAttributeConverters;
	System::Generics::Collections::TObjectDictionary__2<System::Typinfo::PTypeInfo,TJsonContract*>* FCachedContracts;
	TJsonConverter* FListHelperConverter;
	virtual TJsonArrayContract* __fastcall CreateArrayContract(System::Typinfo::PTypeInfo ATypeInf);
	virtual TJsonClassContract* __fastcall CreateClassContract(System::Typinfo::PTypeInfo ATypeInf);
	virtual TJsonContract* __fastcall CreateContract(System::Typinfo::PTypeInfo ATypeInf);
	virtual TJsonConverterContract* __fastcall CreateConverterContract(System::Typinfo::PTypeInfo ATypeInf);
	virtual TJsonObjectContract* __fastcall CreateObjectContract(System::Typinfo::PTypeInfo ATypeInf);
	virtual TJsonPrimitiveContract* __fastcall CreatePrimitiveContract(System::Typinfo::PTypeInfo ATypeInf);
	virtual TJsonProperty* __fastcall CreateProperty(System::Rtti::TRttiMember* const ARttiMember, TJsonMemberSerialization AMemberSerialization);
	virtual void __fastcall CreateProperties(System::Typinfo::PTypeInfo ATypeInf, TJsonMemberSerialization AMemberSerialization, System::Generics::Collections::TObjectList__1<TJsonProperty*>* const AOutProperties);
	virtual void __fastcall GetSerializableMembers(System::Typinfo::PTypeInfo ATypeInf, System::Generics::Collections::TList__1<System::Rtti::TRttiMember*>* const AMembers);
	virtual bool __fastcall ShouldIncludeMember(System::Rtti::TRttiMember* const AMember, TJsonMemberSerialization AMemberSerialization);
	TJsonConverter* __fastcall GetConverterFromAttribute(JsonConverterAttribute* const AConverterAttribute);
	virtual void __fastcall InitializeContract(TJsonContract* const AJsonContract, System::Rtti::TRttiType* const ARttiType);
	virtual void __fastcall SetPropertySettingsFromAttributes(TJsonProperty* const AProperty, System::Rtti::TRttiMember* const ARttiMember, TJsonMemberSerialization AMemberSerialization);
	virtual _di_IJsonValueProvider __fastcall CreateValueProvider(System::Rtti::TRttiMember* const ARttiMember);
	virtual _di_IJsonAttributeProvider __fastcall CreateAttributeProvider(System::Rtti::TRttiObject* const ARttiObject);
	virtual System::UnicodeString __fastcall ResolvePropertyName(const System::UnicodeString AName);
	
public:
	__fastcall TJsonDefaultContractResolver(TJsonMemberSerialization ADefaultMemberSerialization);
	__fastcall virtual ~TJsonDefaultContractResolver();
	virtual void __fastcall ClearCache();
	TJsonContract* __fastcall ResolveContract(System::Typinfo::PTypeInfo ATypeInf);
private:
	void *__IJsonContractResolver;	// IJsonContractResolver 
	
public:
	operator IJsonContractResolver*(void) { return (IJsonContractResolver*)&__IJsonContractResolver; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonDynamicContractResolver : public TJsonDefaultContractResolver
{
	typedef TJsonDefaultContractResolver inherited;
	
private:
	TJsonDynamicAttributes* FDynamicAttributes;
	System::Rtti::TRttiType* __fastcall GetRttiType(System::Typinfo::PTypeInfo ATypeInf);
	System::Rtti::TRttiMember* __fastcall GetRttiField(System::Rtti::TRttiType* const ARttiType, System::UnicodeString AFieldName);
	System::Rtti::TRttiMember* __fastcall GetRttiProperty(System::Rtti::TRttiType* const ARttiType, System::UnicodeString APropertyName);
	
protected:
	virtual _di_IJsonAttributeProvider __fastcall CreateAttributeProvider(System::Rtti::TRttiObject* const ARttiObject);
	
public:
	__fastcall TJsonDynamicContractResolver(TJsonMemberSerialization ADefaultMemberSerialization);
	void __fastcall ClearAttributes();
	void __fastcall SetFieldConverter(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString FieldName, const System::TClass AConverterClass);
	void __fastcall SetFieldName(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString AFieldName, System::UnicodeString ResolvedName);
	void __fastcall SetFieldsIgnored(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString *AFieldNames, const int AFieldNames_High);
	void __fastcall SetFieldsIn(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString *AFieldNames, const int AFieldNames_High);
	void __fastcall SetPropertiesIgnored(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString *APropertyNames, const int APropertyNames_High);
	void __fastcall SetPropertiesIn(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString *APropertyNames, const int APropertyNames_High);
	void __fastcall SetPropertyConverter(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString APropertyName, const System::TClass AConverterClass);
	void __fastcall SetPropertyName(System::Typinfo::PTypeInfo ATypeInf, System::UnicodeString APropertyName, System::UnicodeString AResolvedName);
	void __fastcall SetTypeConverter(System::Typinfo::PTypeInfo ATypeInf, const System::TClass AConverterClass);
	void __fastcall SetTypeMemberSerialization(System::Typinfo::PTypeInfo ATypeInf, TJsonMemberSerialization AMemberSerialization);
	void __fastcall SetTypeIgnored(System::Typinfo::PTypeInfo ATypeInf);
public:
	/* TJsonDefaultContractResolver.Destroy */ inline __fastcall virtual ~TJsonDynamicContractResolver() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface IJsonTypeResolver  : public System::IInterface 
{
	virtual System::Typinfo::PTypeInfo __fastcall ResolveType(const System::UnicodeString ATypeName) = 0 ;
	virtual System::UnicodeString __fastcall ResolveName(const System::Typinfo::PTypeInfo ATypeInf) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonDefaultTypeResolver : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	virtual System::Typinfo::PTypeInfo __fastcall ResolveType(const System::UnicodeString ATypeName);
	virtual System::UnicodeString __fastcall ResolveName(const System::Typinfo::PTypeInfo ATypeInf);
public:
	/* TObject.Create */ inline __fastcall TJsonDefaultTypeResolver() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonDefaultTypeResolver() { }
	
private:
	void *__IJsonTypeResolver;	// IJsonTypeResolver 
	
public:
	operator IJsonTypeResolver*(void) { return (IJsonTypeResolver*)&__IJsonTypeResolver; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonSerializer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	_di_IJsonContractResolver FContractResolver;
	System::Generics::Collections::TList__1<TJsonConverter*>* FConverters;
	System::Json::Types::TJsonDateFormatHandling FDateFormatHandling;
	System::Json::Types::TJsonDateParseHandling FDateParseHandling;
	System::Json::Types::TJsonDateTimeZoneHandling FDateTimeZoneHandling;
	System::Json::Types::TJsonFloatFormatHandling FFloatFormatHandling;
	System::Json::Types::TJsonFormatting FFormatting;
	int FMaxDepth;
	TJsonObjectHandling FObjectHandling;
	TJsonObjectOwnership FObjectOwnership;
	System::Json::Types::TJsonStringEscapeHandling FStringEscapeHandling;
	_di_IJsonTypeResolver FTypeResolver;
	
protected:
	virtual _di_IJsonContractResolver __fastcall GetContractResolver();
	virtual System::Generics::Collections::TList__1<TJsonConverter*>* __fastcall GetConverters();
	virtual System::Json::Types::TJsonDateFormatHandling __fastcall GetDateFormatHandling();
	virtual System::Json::Types::TJsonDateParseHandling __fastcall GetDateParseHandling();
	virtual System::Json::Types::TJsonDateTimeZoneHandling __fastcall GetDateTimeZoneHandling();
	virtual System::Json::Types::TJsonFloatFormatHandling __fastcall GetFloatFormatHandling();
	virtual System::Json::Types::TJsonFormatting __fastcall GetFormatting();
	virtual int __fastcall GetMaxDepth();
	virtual TJsonObjectHandling __fastcall GetObjectHandling();
	virtual TJsonObjectOwnership __fastcall GetObjectOwnership();
	virtual System::Json::Types::TJsonStringEscapeHandling __fastcall GetStringEscapeHandling();
	virtual _di_IJsonTypeResolver __fastcall GetTypeResolver();
	virtual void __fastcall SetContractResolver(const _di_IJsonContractResolver AValue);
	virtual void __fastcall SetDateFormatHandling(System::Json::Types::TJsonDateFormatHandling AValue);
	virtual void __fastcall SetDateParseHandling(System::Json::Types::TJsonDateParseHandling AValue);
	virtual void __fastcall SetDateTimeZoneHandling(System::Json::Types::TJsonDateTimeZoneHandling AValue);
	virtual void __fastcall SetFloatFormatHandling(System::Json::Types::TJsonFloatFormatHandling AValue);
	virtual void __fastcall SetFormatting(System::Json::Types::TJsonFormatting AValue);
	virtual void __fastcall SetMaxDepth(int AValue);
	virtual void __fastcall SetObjectHandling(const TJsonObjectHandling AValue);
	virtual void __fastcall SetObjectOwnership(const TJsonObjectOwnership AValue);
	virtual void __fastcall SetStringEscapeHandling(System::Json::Types::TJsonStringEscapeHandling AValue);
	virtual void __fastcall SetTypeResolver(const _di_IJsonTypeResolver AValue);
	virtual void __fastcall InternalSerialize(System::Json::Writers::TJsonWriter* const AWriter, const System::Rtti::TValue &AValue);
	virtual System::Rtti::TValue __fastcall InternalDeserialize(System::Json::Readers::TJsonReader* const AReader, System::Typinfo::PTypeInfo ATypeInf);
	virtual void __fastcall InternalPopulate(System::Json::Readers::TJsonReader* const Reader, System::Rtti::TValue &AValue);
	
public:
	__fastcall TJsonSerializer();
	__fastcall virtual ~TJsonSerializer();
	template<typename T> System::UnicodeString __fastcall Serialize(const T AValue)/* overload */;
	template<typename T> void __fastcall Serialize(System::Classes::TTextWriter* const AWriter, const T AValue)/* overload */;
	template<typename T> void __fastcall Serialize(System::Json::Writers::TJsonWriter* const AWriter, const T AValue)/* overload */;
	void __fastcall Serialize(System::Json::Writers::TJsonWriter* const AWriter, const System::Rtti::TValue &AValue)/* overload */;
	template<typename T> T __fastcall Deserialize(const System::UnicodeString AJson)/* overload */;
	template<typename T> T __fastcall Deserialize(System::Classes::TTextReader* const AReader)/* overload */;
	template<typename T> T __fastcall Deserialize(System::Json::Readers::TJsonReader* const AReader)/* overload */;
	template<typename T> void __fastcall Populate(const System::UnicodeString AJson, T &AValue)/* overload */;
	template<typename T> void __fastcall Populate(System::Classes::TTextReader* const AReader, T &AValue)/* overload */;
	template<typename T> void __fastcall Populate(System::Json::Readers::TJsonReader* const AReader, T &AValue)/* overload */;
	void __fastcall Populate(System::Json::Readers::TJsonReader* const AReader, System::Rtti::TValue &AValue)/* overload */;
	static TJsonConverter* __fastcall MatchConverter(System::Generics::Collections::TList__1<TJsonConverter*>* const AConverters, System::Typinfo::PTypeInfo ATypeInf);
	__property _di_IJsonContractResolver ContractResolver = {read=GetContractResolver, write=SetContractResolver};
	__property System::Generics::Collections::TList__1<TJsonConverter*>* Converters = {read=GetConverters};
	__property System::Json::Types::TJsonDateFormatHandling DateFormatHandling = {read=GetDateFormatHandling, write=SetDateFormatHandling, nodefault};
	__property System::Json::Types::TJsonDateParseHandling DateParseHandling = {read=GetDateParseHandling, write=SetDateParseHandling, nodefault};
	__property System::Json::Types::TJsonDateTimeZoneHandling DateTimeZoneHandling = {read=GetDateTimeZoneHandling, write=SetDateTimeZoneHandling, nodefault};
	__property System::Json::Types::TJsonFloatFormatHandling FloatFormatHandling = {read=GetFloatFormatHandling, write=SetFloatFormatHandling, nodefault};
	__property System::Json::Types::TJsonFormatting Formatting = {read=GetFormatting, write=SetFormatting, nodefault};
	__property int MaxDepth = {read=GetMaxDepth, write=SetMaxDepth, nodefault};
	__property TJsonObjectHandling ObjectHandling = {read=GetObjectHandling, write=SetObjectHandling, nodefault};
	__property TJsonObjectOwnership ObjectOwnership = {read=GetObjectOwnership, write=SetObjectOwnership, nodefault};
	__property System::Json::Types::TJsonStringEscapeHandling StringEscapeHandling = {read=GetStringEscapeHandling, write=SetStringEscapeHandling, nodefault};
	__property _di_IJsonTypeResolver TypeResolver = {read=GetTypeResolver, write=SetTypeResolver};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Serializers */
}	/* namespace Json */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON_SERIALIZERS)
using namespace System::Json::Serializers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON)
using namespace System::Json;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif

//-- user supplied -----------------------------------------------------------
#include <SystemJSONSerializers.h>

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Json_SerializersHPP
