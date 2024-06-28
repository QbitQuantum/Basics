// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyJavaAndroid.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproxyjavaandroidHPP
#define Datasnap_DsproxyjavaandroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSProxyWriter.hpp>
#include <Datasnap.DSCustomConnectorProxyWriter.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Datasnap.DSProxyJavaAndroid"

namespace Datasnap
{
namespace Dsproxyjavaandroid
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterJavaAndroid;
class DELPHICLASS TDSCustomJavaAndroidProxyWriter;
class DELPHICLASS TDSJavaAndroidProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterJavaAndroid : public Datasnap::Dsproxywriter::TDSProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSProxyWriter inherited;
	
private:
	System::Sysutils::TEncoding* FUTF8Encoding;
	System::Sysutils::TEncoding* __fastcall GetEncoding();
	
public:
	virtual Datasnap::Dsproxywriter::TDSCustomProxyWriter* __fastcall CreateProxyWriter();
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
	virtual Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
	__fastcall virtual ~TDSClientProxyWriterJavaAndroid();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterJavaAndroid() : Datasnap::Dsproxywriter::TDSProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomJavaAndroidProxyWriter : public Datasnap::Dscustomconnectorproxywriter::TDSCustomConnectorProxyWriter
{
	typedef Datasnap::Dscustomconnectorproxywriter::TDSCustomConnectorProxyWriter inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual void __fastcall WriteInterface();
	virtual void __fastcall WriteJavaLine(const System::UnicodeString Line)/* overload */;
	virtual void __fastcall WriteJavaLine()/* overload */;
	virtual void __fastcall WriteImplementation();
	virtual void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, System::Classes::TStringList* const ProxyClassNameList);
	virtual void __fastcall WriteMethodComment(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual void __fastcall WriteMethodParametersMetadata(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, /* out */ System::UnicodeString &MetadataGetterName);
	virtual void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, const System::UnicodeString MetadataGetterName);
	System::UnicodeString __fastcall GetJavaType(Datasnap::Dscommonproxy::TDSProxyParameter* Param);
	System::UnicodeString __fastcall GetCastType(Datasnap::Dscommonproxy::TDSProxyParameter* Param);
	virtual void __fastcall WriteResultObjectClass(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, /* out */ System::UnicodeString &ResultObjectClassName);
	
private:
	void __fastcall WriteSetterForInputParams(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	void __fastcall WriteGetterForOutputParams(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod)/* overload */;
	void __fastcall WriteGetterForOutputParams(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, const System::UnicodeString ResultObjectClassName)/* overload */;
public:
	/* TDSCustomConnectorProxyWriter.Create */ inline __fastcall virtual TDSCustomJavaAndroidProxyWriter() : Datasnap::Dscustomconnectorproxywriter::TDSCustomConnectorProxyWriter() { }
	
public:
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomJavaAndroidProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSJavaAndroidProxyWriter : public TDSCustomJavaAndroidProxyWriter
{
	typedef TDSCustomJavaAndroidProxyWriter inherited;
	
private:
	System::Classes::TStreamWriter* FStreamWriter;
	System::UnicodeString FTargetUnitName;
	Data::Dbxplatform::TDBXStringArray FIncludeClasses;
	Data::Dbxplatform::TDBXStringArray FExcludeClasses;
	Data::Dbxplatform::TDBXStringArray FIncludeMethods;
	Data::Dbxplatform::TDBXStringArray FExcludeMethods;
	
protected:
	virtual void __fastcall DerivedWrite(const System::UnicodeString Line);
	virtual void __fastcall DerivedWriteLine();
	
public:
	__property System::Classes::TStreamWriter* StreamWriter = {read=FStreamWriter, write=FStreamWriter};
	__property System::UnicodeString TargetUnitName = {read=FTargetUnitName, write=FTargetUnitName};
	__property Data::Dbxplatform::TDBXStringArray IncludeClasses = {read=FIncludeClasses, write=FIncludeClasses};
	__property Data::Dbxplatform::TDBXStringArray ExcludeClasses = {read=FExcludeClasses, write=FExcludeClasses};
	__property Data::Dbxplatform::TDBXStringArray IncludeMethods = {read=FIncludeMethods, write=FIncludeMethods};
	__property Data::Dbxplatform::TDBXStringArray ExcludeMethods = {read=FExcludeMethods, write=FExcludeMethods};
	__fastcall virtual ~TDSJavaAndroidProxyWriter();
public:
	/* TDSCustomConnectorProxyWriter.Create */ inline __fastcall virtual TDSJavaAndroidProxyWriter() : TDSCustomJavaAndroidProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sJavaAndroidRESTProxyWriter L"Java (Android) REST"
}	/* namespace Dsproxyjavaandroid */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYJAVAANDROID)
using namespace Datasnap::Dsproxyjavaandroid;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxyjavaandroidHPP
