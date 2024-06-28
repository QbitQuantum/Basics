// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyWriter.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproxywriterHPP
#define Datasnap_DsproxywriterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Masks.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsproxywriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSProxyWriterFactory;
struct TDSProxyWriterProperties;
struct TDSProxyFileDescription;
class DELPHICLASS TDSProxyWriter;
struct TDSProxyParamAccess;
class DELPHICLASS TDSCustomProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSProxyWriterFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static TDSProxyWriterFactory* __fastcall Instance();
	static void __fastcall RegisterWriter(const System::UnicodeString Id, const Data::Dbxplatform::TObjectClass WriterClass);
	static void __fastcall UnregisterWriter(const System::UnicodeString Id);
	__classmethod bool __fastcall HasWriter(const System::UnicodeString Id);
	static TDSProxyWriter* __fastcall GetWriter(const System::UnicodeString Id);
	static Data::Dbxplatform::TDBXStringArray __fastcall RegisteredWritersList();
	__fastcall TDSProxyWriterFactory();
	__fastcall virtual ~TDSProxyWriterFactory();
	
private:
	static TDSProxyWriterFactory* FSingleton;
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,Data::Dbxplatform::TObjectClass>* FRegisteredWriters;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TDSProxyWriteFeature : unsigned char { feConnectsWithDSRestConnection, feConnectsWithDBXConnection, feRESTClient, feDBXClient };

typedef System::Set<TDSProxyWriteFeature, TDSProxyWriteFeature::feConnectsWithDSRestConnection, TDSProxyWriteFeature::feDBXClient> TDSProxyWriteFeatures;

struct DECLSPEC_DRECORD TDSProxyWriterProperties
{
public:
	System::UnicodeString UsesUnits;
	System::UnicodeString DefaultExcludeClasses;
	System::UnicodeString DefaultExcludeMethods;
	System::Sysutils::TEncoding* DefaultEncoding;
	System::UnicodeString Author;
	System::UnicodeString Comment;
	System::UnicodeString Language;
	TDSProxyWriteFeatures Features;
};


struct DECLSPEC_DRECORD TDSProxyFileDescription
{
public:
	System::UnicodeString ID;
	System::UnicodeString DefaultFileExt;
};


typedef System::DynamicArray<TDSProxyFileDescription> TDSProxyFileDescriptions;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSProxyWriter : public Data::Dbxplatform::TFactoryObject
{
	typedef Data::Dbxplatform::TFactoryObject inherited;
	
public:
	virtual TDSCustomProxyWriter* __fastcall CreateProxyWriter() = 0 ;
	virtual TDSProxyWriterProperties __fastcall Properties() = 0 ;
	virtual TDSProxyFileDescriptions __fastcall FileDescriptions() = 0 ;
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSProxyWriter() : Data::Dbxplatform::TFactoryObject() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TDSProxyParamAccess
{
public:
	System::UnicodeString TypeIdentifier;
	System::UnicodeString Getter;
	System::UnicodeString Setter;
	System::UnicodeString TypeUnit;
	__fastcall TDSProxyParamAccess(const System::UnicodeString ATypeId, const System::UnicodeString AGetter, const System::UnicodeString ASetter, const System::UnicodeString ATypeUnit);
	TDSProxyParamAccess() {}
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomProxyWriter : public System::TObject
{
	typedef System::TObject inherited;
	
	
protected:
	typedef System::Generics::Collections::TPair__2<int,int> TCustomTypeMapPair;
	
	
public:
	__fastcall TDSCustomProxyWriter();
	__fastcall virtual ~TDSCustomProxyWriter();
	virtual void __fastcall WriteProxy();
	
protected:
	virtual void __fastcall WriteImplementation() = 0 ;
	virtual void __fastcall WriteInterface() = 0 ;
	virtual void __fastcall WriteFileHeader();
	virtual System::UnicodeString __fastcall GetTimeStamp();
	virtual void __fastcall DerivedWrite(const System::UnicodeString Line) = 0 ;
	virtual void __fastcall DerivedWriteLine() = 0 ;
	virtual System::UnicodeString __fastcall GetAssignmentString() = 0 ;
	bool __fastcall IncludeClassName(const System::UnicodeString ClassName);
	bool __fastcall IncludeMethodName(const System::UnicodeString MethodName);
	virtual bool __fastcall IncludeClass(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	virtual bool __fastcall IncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	void __fastcall WriteLine(const System::UnicodeString Line)/* overload */;
	void __fastcall Indent();
	void __fastcall Outdent();
	void __fastcall WriteLine()/* overload */;
	virtual bool __fastcall IsKnownTableTypeName(const System::UnicodeString Name);
	virtual bool __fastcall IsKnownDBXValueTypeName(const System::UnicodeString Name);
	virtual bool __fastcall IsKnownJSONTypeName(const System::UnicodeString Name);
	virtual System::UnicodeString __fastcall GetDelphiTypeName(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetDelphiUnitName(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	System::UnicodeString __fastcall GetGetter(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	System::UnicodeString __fastcall GetSetter(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param) = 0 ;
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param) = 0 ;
	
private:
	Datasnap::Dscommonproxy::TDSProxyMetadata* FMetadata;
	bool FOwnsMetaData;
	System::Generics::Collections::TDictionary__2<System::Generics::Collections::TPair__2<int,int>,TDSProxyParamAccess>* FCustomTypeMap;
	
private:
	void __fastcall ClearMasks();
	bool __fastcall InclusionTest(const Data::Dbxplatform::TDBXStringArray Includes, const Data::Dbxplatform::TDBXStringArray Excludes, const System::UnicodeString Name);
	void __fastcall SetMetaDataLoader(const Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader Value);
	
protected:
	System::UnicodeString FUnitFileName;
	System::UnicodeString FIndentString;
	int FIndentIncrement;
	Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader FMetaDataLoader;
	void __fastcall AddCustomTypeMap(const int ADbxDataType, const TDSProxyParamAccess &AProxyParamRec)/* overload */;
	void __fastcall AddCustomTypeMap(const int ADbxDataType, const int ADbxSubDataType, const TDSProxyParamAccess &AProxyParamRec)/* overload */;
	void __fastcall RemoveCustomTypeMap(const int ADbxDataType);
	
private:
	int FIndentSpaces;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Masks::TMask*>* FMasks;
	Data::Dbxplatform::TDBXStringArray FIncludeClasses;
	Data::Dbxplatform::TDBXStringArray FExcludeClasses;
	Data::Dbxplatform::TDBXStringArray FIncludeMethods;
	Data::Dbxplatform::TDBXStringArray FExcludeMethods;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Datasnap::Dscommonproxy::_di_IDSProxyWriter>* FProxyWriters;
	Datasnap::Dscommonproxy::TDSProxyMetadata* __fastcall GetMetadata();
	void __fastcall SetExcludeClasses(const Data::Dbxplatform::TDBXStringArray Value);
	void __fastcall SetExcludeMethods(const Data::Dbxplatform::TDBXStringArray Value);
	void __fastcall SetIncludeClasses(const Data::Dbxplatform::TDBXStringArray Value);
	void __fastcall SetIncludeMethods(const Data::Dbxplatform::TDBXStringArray Value);
	
public:
	__property Datasnap::Dscommonproxy::TDSProxyMetadata* Metadata = {read=GetMetadata};
	__property Datasnap::Dscommonproxy::_di_IDSProxyMetaDataLoader MetaDataLoader = {read=FMetaDataLoader, write=SetMetaDataLoader};
	__property System::Generics::Collections::TDictionary__2<System::UnicodeString,Datasnap::Dscommonproxy::_di_IDSProxyWriter>* ProxyWriters = {read=FProxyWriters};
	__property System::UnicodeString UnitFileName = {read=FUnitFileName, write=FUnitFileName};
	__property Data::Dbxplatform::TDBXStringArray IncludeClasses = {read=FIncludeClasses, write=SetIncludeClasses};
	__property Data::Dbxplatform::TDBXStringArray ExcludeClasses = {read=FExcludeClasses, write=SetExcludeClasses};
	__property Data::Dbxplatform::TDBXStringArray IncludeMethods = {read=FIncludeMethods, write=SetIncludeMethods};
	__property Data::Dbxplatform::TDBXStringArray ExcludeMethods = {read=FExcludeMethods, write=SetExcludeMethods};
	
protected:
	__property System::UnicodeString AssignmentString = {read=GetAssignmentString};
	__property System::Generics::Collections::TDictionary__2<System::Generics::Collections::TPair__2<int,int>,TDSProxyParamAccess>* CustomTypeMap = {read=FCustomTypeMap};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sDSProxyDelphiLanguage L"Delphi"
#define sDSProxyCppLanguage L"C++"
#define sDSProxyJavaScriptLanguage L"Java Script"
}	/* namespace Dsproxywriter */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYWRITER)
using namespace Datasnap::Dsproxywriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxywriterHPP
