// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyJavaScript.pas' rev: 34.00 (iOS)

#ifndef Datasnap_DsproxyjavascriptHPP
#define Datasnap_DsproxyjavascriptHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSProxyWriter.hpp>

//-- user supplied -----------------------------------------------------------
namespace Datasnap
{
namespace Dsproxyjavascript
{
  _INIT_UNIT(Datasnap_Dsproxyjavascript);
}	/* namespace Dsproxyjavascript */
}	/* namespace Datasnap */

namespace Datasnap
{
namespace Dsproxyjavascript
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterJavaScript;
class DELPHICLASS TDSCustomJavaScriptProxyWriter;
class DELPHICLASS TDSJavaScriptProxyWriter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterJavaScript : public Datasnap::Dsproxywriter::TDSProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSProxyWriter inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSCustomProxyWriter* __fastcall CreateProxyWriter();
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
	virtual Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterJavaScript() : Datasnap::Dsproxywriter::TDSProxyWriter() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterJavaScript() { }
	
};


class PASCALIMPLEMENTATION TDSCustomJavaScriptProxyWriter : public Datasnap::Dsproxywriter::TDSCustomProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSCustomProxyWriter inherited;
	
public:
	__fastcall TDSCustomJavaScriptProxyWriter();
	
protected:
	bool __fastcall IsPrimitiveJSONType(System::UnicodeString ClassName);
	virtual Data::Dbxplatform::TDBXInt32s __fastcall GetSupportedTypes();
	virtual Data::Dbxplatform::TDBXInt32s __fastcall GetNonURLTypes();
	virtual System::UnicodeString __fastcall GetAssignmentString();
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual void __fastcall WriteInterface();
	virtual void __fastcall WriteJSLine(const System::UnicodeString Line)/* overload */;
	virtual void __fastcall WriteJSLine()/* overload */;
	virtual bool __fastcall ExtendedIncludeClass(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	virtual bool __fastcall Contains(const Data::Dbxplatform::TDBXInt32s Arr, const int Value);
	virtual bool __fastcall ExtendedIncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual Datasnap::Dscommonproxy::TDSProxyClass* __fastcall GetFirstClass();
	virtual void __fastcall WriteImplementation();
	virtual void __fastcall WriteProxyClassList(System::Classes::TStringList* const ProxyClassNameList);
	virtual void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, System::Classes::TStringList* const ProxyClassNameList);
	virtual System::UnicodeString __fastcall GetMethodRequestType(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	virtual System::UnicodeString __fastcall GetMethodRequestName(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	virtual void __fastcall WriteMethodComment(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	
private:
	bool __fastcall HasOnlyURLParams(Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	
protected:
	Data::Dbxplatform::TDBXInt32s FSupportedTypes;
	Data::Dbxplatform::TDBXInt32s FNonURLTypes;
	System::UnicodeString Get;
	System::UnicodeString Post;
	System::UnicodeString Put;
	System::UnicodeString Delete;
	System::UnicodeString FPostPrefix;
	System::UnicodeString FPutPrefix;
	System::UnicodeString FDeletePrefix;
	bool FGenerateURLFunctions;
	
public:
	__property bool GenerateURLFunctions = {read=FGenerateURLFunctions, write=FGenerateURLFunctions, nodefault};
	
protected:
	__property Data::Dbxplatform::TDBXInt32s SupportedTypes = {read=GetSupportedTypes};
	__property Data::Dbxplatform::TDBXInt32s NonURLTypes = {read=GetNonURLTypes};
	__property Datasnap::Dscommonproxy::TDSProxyClass* FirstClass = {read=GetFirstClass};
public:
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomJavaScriptProxyWriter() { }
	
};


class PASCALIMPLEMENTATION TDSJavaScriptProxyWriter : public TDSCustomJavaScriptProxyWriter
{
	typedef TDSCustomJavaScriptProxyWriter inherited;
	
private:
	System::Classes::TStreamWriter* FStreamWriter;
	System::UnicodeString FTargetUnitName;
	Data::Dbxplatform::TDBXStringArray FIncludeClasses;
	Data::Dbxplatform::TDBXStringArray FExcludeClasses;
	Data::Dbxplatform::TDBXStringArray FIncludeMethods;
	Data::Dbxplatform::TDBXStringArray FExcludeMethods;
	System::UnicodeString __fastcall GetFileName(System::UnicodeString OutputFile);
	
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
	void __fastcall generateJS(Data::Dbxcommon::TDBXConnection* AConnection, System::Classes::TStream* AStream);
	void __fastcall UpdateJSProxyFile(Data::Dbxcommon::TDBXConnection* AConnection, const System::UnicodeString AFileName);
	__fastcall virtual ~TDSJavaScriptProxyWriter();
public:
	/* TDSCustomJavaScriptProxyWriter.Create */ inline __fastcall TDSJavaScriptProxyWriter() : TDSCustomJavaScriptProxyWriter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define sJavaScriptRESTProxyWriter u"Java Script REST"
}	/* namespace Dsproxyjavascript */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYJAVASCRIPT)
using namespace Datasnap::Dsproxyjavascript;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxyjavascriptHPP
