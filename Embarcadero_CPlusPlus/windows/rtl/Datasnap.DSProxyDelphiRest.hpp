// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyDelphiRest.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproxydelphirestHPP
#define Datasnap_DsproxydelphirestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSProxyDelphi.hpp>
#include <Datasnap.DSProxyWriter.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Datasnap.DSProxyDelphiRest"

namespace Datasnap
{
namespace Dsproxydelphirest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterDelphi;
class DELPHICLASS TDSCustomNativeRestProxyWriter;
class DELPHICLASS TDSCustomDelphiRestProxyWriter;
class DELPHICLASS TDSDelphiRestProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterDelphi : public Datasnap::Dsproxywriter::TDSProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSProxyWriter inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSCustomProxyWriter* __fastcall CreateProxyWriter();
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
	virtual Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterDelphi() : Datasnap::Dsproxywriter::TDSProxyWriter() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterDelphi() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TNativeRestProxyWriterOption : unsigned char { optCacheParameters };

typedef System::Set<TNativeRestProxyWriterOption, TNativeRestProxyWriterOption::optCacheParameters, TNativeRestProxyWriterOption::optCacheParameters> TNativeRestProxyWriterOptions;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomNativeRestProxyWriter : public Datasnap::Dsproxydelphi::TDSCustomExtendedProxyWriter
{
	typedef Datasnap::Dsproxydelphi::TDSCustomExtendedProxyWriter inherited;
	
private:
	System::Generics::Collections::TList__1<int>* FSupportedTypes;
	bool __fastcall ExtendedIncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	System::Generics::Collections::TList__1<int>* __fastcall GetSupportedTypes();
	bool __fastcall ExtendedIncludeCacheMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	
protected:
	virtual bool __fastcall CanMarshal();
	System::UnicodeString __fastcall GetAncestor(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	virtual bool __fastcall IncludeClass(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	virtual bool __fastcall IncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	bool __fastcall IncludeCacheMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	bool __fastcall SupportsRequestFilter(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	bool __fastcall IsCachableParameter(Datasnap::Dscommonproxy::TDSProxyParameter* const ProxyParameter, /* out */ System::UnicodeString &ACachedValueClassName)/* overload */;
	bool __fastcall IsCachableParameter(Datasnap::Dscommonproxy::TDSProxyParameter* const ProxyParameter, /* out */ System::UnicodeString &ACachedValueClassName, /* out */ bool &AIsCustomType)/* overload */;
	__property System::Generics::Collections::TList__1<int>* SupportedTypes = {read=GetSupportedTypes};
	bool __fastcall EnumClasses(System::DelphiInterface<System::Sysutils::TFunc__2<Datasnap::Dscommonproxy::TDSProxyClass*,bool> > ACallback);
	bool __fastcall EnumMethods(Datasnap::Dscommonproxy::TDSProxyClass* AClass, System::DelphiInterface<System::Sysutils::TFunc__2<Datasnap::Dscommonproxy::TDSProxyMethod*,bool> > ACallback);
	bool __fastcall EnumParams(Datasnap::Dscommonproxy::TDSProxyMethod* AMethod, System::DelphiInterface<System::Sysutils::TFunc__2<Datasnap::Dscommonproxy::TDSProxyParameter*,bool> > ACallback);
	
public:
	__fastcall TDSCustomNativeRestProxyWriter();
	__fastcall virtual ~TDSCustomNativeRestProxyWriter();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomDelphiRestProxyWriter : public TDSCustomNativeRestProxyWriter
{
	typedef TDSCustomNativeRestProxyWriter inherited;
	
public:
	__fastcall TDSCustomDelphiRestProxyWriter();
	virtual void __fastcall WriteProxy();
	
protected:
	System::UnicodeString FUnitName;
	virtual void __fastcall WriteInterface();
	virtual void __fastcall WriteImplementation();
	virtual System::UnicodeString __fastcall GetAssignmentString();
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	
private:
	void __fastcall WriteInterfaceUses();
	void __fastcall WriteMethodSignature(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method, const bool IsInterface, TNativeRestProxyWriterOptions AOptions);
	void __fastcall WriteClassInterface(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, TNativeRestProxyWriterOptions AOptions = TNativeRestProxyWriterOptions() );
	void __fastcall WriteOutgoingParameter(const System::UnicodeString Lhs, const System::UnicodeString InRhs, Datasnap::Dscommonproxy::TDSProxyParameter* const Param, const System::UnicodeString CommandName, const System::UnicodeString ParamName);
	void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	void __fastcall WriteTDSRestParameterMetaData();
	void __fastcall WriteClassTDSRestParameterMetaData(Datasnap::Dscommonproxy::TDSProxyClass* ProxyClass);
	void __fastcall WriteMethodTDSRestParameterMetaData(Datasnap::Dscommonproxy::TDSProxyClass* ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* Method, TNativeRestProxyWriterOptions AOptions = TNativeRestProxyWriterOptions() );
	System::UnicodeString __fastcall MakeTDSRestParameterMetaDataTypeName(Datasnap::Dscommonproxy::TDSProxyClass* ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* Method, TNativeRestProxyWriterOptions AOptions = TNativeRestProxyWriterOptions() );
	void __fastcall GetHTTPMethodAndPrefix(Datasnap::Dscommonproxy::TDSProxyMethod* Method, /* out */ System::UnicodeString &AServerMethodPrefix, /* out */ System::UnicodeString &AHTTPMethodName);
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* __fastcall GetCachedObjectTypes();
	void __fastcall WriteCachedObjectTypes(System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* List, const bool Forwards);
public:
	/* TDSCustomNativeRestProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomDelphiRestProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSDelphiRestProxyWriter : public TDSCustomDelphiRestProxyWriter
{
	typedef TDSCustomDelphiRestProxyWriter inherited;
	
private:
	System::Classes::TStreamWriter* FStreamWriter;
	
protected:
	virtual void __fastcall DerivedWrite(const System::UnicodeString Line);
	virtual void __fastcall DerivedWriteLine();
	
public:
	__property System::Classes::TStreamWriter* StreamWriter = {read=FStreamWriter, write=FStreamWriter};
	__fastcall virtual ~TDSDelphiRestProxyWriter();
public:
	/* TDSCustomDelphiRestProxyWriter.Create */ inline __fastcall TDSDelphiRestProxyWriter() : TDSCustomDelphiRestProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sDelphiRestProxyWriter L"Delphi REST"
#define sObjectPascalRestProxyWriter L"Object Pascal REST"
#define sDSRestCached L"DSRestCached"
}	/* namespace Dsproxydelphirest */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYDELPHIREST)
using namespace Datasnap::Dsproxydelphirest;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxydelphirestHPP
