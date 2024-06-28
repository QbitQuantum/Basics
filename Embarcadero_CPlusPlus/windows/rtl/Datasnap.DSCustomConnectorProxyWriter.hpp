// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSCustomConnectorProxyWriter.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DscustomconnectorproxywriterHPP
#define Datasnap_DscustomconnectorproxywriterHPP

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
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dscustomconnectorproxywriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSCustomConnectorProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomConnectorProxyWriter : public Datasnap::Dsproxywriter::TDSCustomProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSCustomProxyWriter inherited;
	
public:
	__fastcall virtual TDSCustomConnectorProxyWriter();
	
protected:
	System::UnicodeString Get;
	System::UnicodeString Post;
	System::UnicodeString Put;
	System::UnicodeString Delete;
	System::UnicodeString FPostPrefix;
	System::UnicodeString FPutPrefix;
	System::UnicodeString FDeletePrefix;
	bool FGenerateURLFunctions;
	Data::Dbxplatform::TDBXInt32s FSupportedTypes;
	Data::Dbxplatform::TDBXInt32s FNonURLTypes;
	virtual System::UnicodeString __fastcall GetMethodRequestType(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	bool __fastcall Contains(const Data::Dbxplatform::TDBXInt32s Arr, const int Value);
	bool __fastcall ExtendedIncludeClass(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	bool __fastcall ExtendedIncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	void __fastcall ForEachInputParameter(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, System::DelphiInterface<System::Sysutils::TProc__1<Datasnap::Dscommonproxy::TDSProxyParameter*> > Callback);
	void __fastcall ForEachOutputParameter(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, System::DelphiInterface<System::Sysutils::TProc__1<Datasnap::Dscommonproxy::TDSProxyParameter*> > Callback);
	void __fastcall ForEachParameter(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod, System::DelphiInterface<System::Sysutils::TProc__1<Datasnap::Dscommonproxy::TDSProxyParameter*> > Callback);
	Datasnap::Dscommonproxy::TDSProxyClass* __fastcall GetFirstClass();
	bool __fastcall IsOutputParameter(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	bool __fastcall IsInputParameter(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual Data::Dbxplatform::TDBXInt32s __fastcall GetNonURLTypes();
	virtual Data::Dbxplatform::TDBXInt32s __fastcall GetSupportedTypes();
	virtual bool __fastcall IsPrimitiveJSONType(System::UnicodeString ClassName) _FINAL_ATTRIBUTE;
	virtual System::UnicodeString __fastcall GetAssignmentString();
	HIDESBASE virtual System::UnicodeString __fastcall GetSetter(Datasnap::Dscommonproxy::TDSProxyParameter* Param);
	HIDESBASE virtual System::UnicodeString __fastcall GetGetter(Datasnap::Dscommonproxy::TDSProxyParameter* Param);
	bool __fastcall IsDBXValueTypeParameter(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetParameterDirection(int Direction);
	virtual System::UnicodeString __fastcall GetParameterDirectionPrefix();
	virtual int __fastcall GetOutputParametersCount(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	bool __fastcall HasOnlyURLParams(Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	bool __fastcall IsProcedure(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	Datasnap::Dscommonproxy::TDSProxyParameter* __fastcall GetReturnParam(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual System::UnicodeString __fastcall GetMethodRequestName(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	virtual System::UnicodeString __fastcall GetParameterType(int ParameterType);
	virtual System::UnicodeString __fastcall GetParameterTypePrefix();
	__property Data::Dbxplatform::TDBXInt32s SupportedTypes = {read=GetSupportedTypes};
	__property Data::Dbxplatform::TDBXInt32s NonURLTypes = {read=GetNonURLTypes};
	__property Datasnap::Dscommonproxy::TDSProxyClass* FirstClass = {read=GetFirstClass};
public:
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomConnectorProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dscustomconnectorproxywriter */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCUSTOMCONNECTORPROXYWRITER)
using namespace Datasnap::Dscustomconnectorproxywriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DscustomconnectorproxywriterHPP
