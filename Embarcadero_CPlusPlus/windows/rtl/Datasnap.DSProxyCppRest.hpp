// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyCppRest.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproxycpprestHPP
#define Datasnap_DsproxycpprestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DSProxyWriter.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSProxyDelphiRest.hpp>
#include <Data.DBXPlatform.hpp>
#include <Datasnap.DSProxyDelphi.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Datasnap.DSProxyCppRest"

namespace Datasnap
{
namespace Dsproxycpprest
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterCppRest;
class DELPHICLASS TDSCustomCppRestProxyWriter;
class DELPHICLASS TDSCppRestProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterCppRest : public Datasnap::Dsproxywriter::TDSProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSProxyWriter inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSCustomProxyWriter* __fastcall CreateProxyWriter();
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
	virtual Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterCppRest() : Datasnap::Dsproxywriter::TDSProxyWriter() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterCppRest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomCppRestProxyWriter : public Datasnap::Dsproxydelphirest::TDSCustomNativeRestProxyWriter
{
	typedef Datasnap::Dsproxydelphirest::TDSCustomNativeRestProxyWriter inherited;
	
public:
	__fastcall TDSCustomCppRestProxyWriter();
	virtual void __fastcall WriteProxy();
	
protected:
	System::UnicodeString FUnitName;
	virtual bool __fastcall CanMarshal();
	virtual void __fastcall StartCppHeader() = 0 ;
	virtual void __fastcall EndCppHeader() = 0 ;
	virtual void __fastcall WriteFileHeader();
	virtual System::UnicodeString __fastcall GetDelphiTypeName(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual void __fastcall WriteInterface();
	virtual void __fastcall WriteImplementation();
	virtual System::UnicodeString __fastcall GetAssignmentString();
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual bool __fastcall IncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	
private:
	void __fastcall WriteHeaderUses();
	void __fastcall WriteMethodSignature(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method, const bool IsInterface, Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions AOptions);
	void __fastcall WriteClassInterface(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions AOptions = Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions() );
	void __fastcall WriteOutgoingParameter(const System::UnicodeString Lhs, const System::UnicodeString InRhs, Datasnap::Dscommonproxy::TDSProxyParameter* const Param, const System::UnicodeString CommandName, const System::UnicodeString ParamName);
	void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	void __fastcall WriteTDSRestParameterMetaData();
	void __fastcall WriteClassTDSRestParameterMetaData(Datasnap::Dscommonproxy::TDSProxyClass* ProxyClass);
	void __fastcall WriteMethodTDSRestParameterMetaData(Datasnap::Dscommonproxy::TDSProxyClass* ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* Method, Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions AOptions = Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions() );
	System::UnicodeString __fastcall MakeTDSRestParameterMetaDataTypeName(Datasnap::Dscommonproxy::TDSProxyClass* ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* Method, Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions AOptions = Datasnap::Dsproxydelphirest::TNativeRestProxyWriterOptions() );
	void __fastcall GetHTTPMethodAndPrefix(Datasnap::Dscommonproxy::TDSProxyMethod* Method, /* out */ System::UnicodeString &AServerMethodPrefix, /* out */ System::UnicodeString &AHTTPMethodName);
	System::UnicodeString __fastcall GetCacheValueInterfaceTypeName(const System::UnicodeString ACachedValueClassName);
public:
	/* TDSCustomNativeRestProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomCppRestProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCppRestProxyWriter : public TDSCustomCppRestProxyWriter
{
	typedef TDSCustomCppRestProxyWriter inherited;
	
private:
	System::Classes::TStreamWriter* FStreamWriter;
	System::Classes::TStreamWriter* FHeaderStreamWriter;
	bool FWritingHeader;
	
protected:
	virtual void __fastcall DerivedWrite(const System::UnicodeString Line);
	virtual void __fastcall DerivedWriteLine();
	virtual void __fastcall StartCppHeader();
	virtual void __fastcall EndCppHeader();
	
public:
	__property System::Classes::TStreamWriter* StreamWriter = {read=FStreamWriter, write=FStreamWriter};
	__property System::Classes::TStreamWriter* HeaderStreamWriter = {read=FHeaderStreamWriter, write=FHeaderStreamWriter};
	__fastcall virtual ~TDSCppRestProxyWriter();
public:
	/* TDSCustomCppRestProxyWriter.Create */ inline __fastcall TDSCppRestProxyWriter() : TDSCustomCppRestProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sCPlusPlusBuilderRestProxyWriter L"C++Builder REST"
}	/* namespace Dsproxycpprest */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYCPPREST)
using namespace Datasnap::Dsproxycpprest;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxycpprestHPP
