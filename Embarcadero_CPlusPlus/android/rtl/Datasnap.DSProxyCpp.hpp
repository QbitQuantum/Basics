﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyCpp.pas' rev: 34.00 (Android)

#ifndef Datasnap_DsproxycppHPP
#define Datasnap_DsproxycppHPP

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
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------
namespace Datasnap
{
namespace Dsproxycpp
{
  _INIT_UNIT(Datasnap_Dsproxycpp);
}	/* namespace Dsproxycpp */
}	/* namespace Datasnap */

namespace Datasnap
{
namespace Dsproxycpp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterCpp;
class DELPHICLASS TDSCustomCppProxyWriter;
class DELPHICLASS TDSCppProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterCpp : public Datasnap::Dsproxywriter::TDSProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSProxyWriter inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSCustomProxyWriter* __fastcall CreateProxyWriter();
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
	virtual Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterCpp() : Datasnap::Dsproxywriter::TDSProxyWriter() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterCpp() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCustomCppProxyWriter : public Datasnap::Dsproxydelphi::TDSCustomExtendedProxyWriter
{
	typedef Datasnap::Dsproxydelphi::TDSCustomExtendedProxyWriter inherited;
	
public:
	__fastcall TDSCustomCppProxyWriter();
	virtual void __fastcall WriteProxy();
	
protected:
	System::UnicodeString FUnitName;
	virtual void __fastcall StartCppHeader() = 0 ;
	virtual void __fastcall EndCppHeader() = 0 ;
	virtual void __fastcall WriteFileHeader();
	virtual System::UnicodeString __fastcall GetDelphiTypeName(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual void __fastcall WriteInterface();
	virtual void __fastcall WriteImplementation();
	virtual System::UnicodeString __fastcall GetAssignmentString();
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	
private:
	void __fastcall WriteHeaderUses();
	void __fastcall WriteMethodSignature(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method, const bool IsInterface);
	void __fastcall WriteClassInterface(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	void __fastcall WriteOutgoingParameter(const System::UnicodeString Lhs, const System::UnicodeString InRhs, Datasnap::Dscommonproxy::TDSProxyParameter* const Param, const System::UnicodeString CommandName, const System::UnicodeString ParamName);
	void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
public:
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomCppProxyWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCppProxyWriter : public TDSCustomCppProxyWriter
{
	typedef TDSCustomCppProxyWriter inherited;
	
private:
	System::Classes::TStreamWriter* FStreamWriter;
	System::Classes::TStreamWriter* FHeaderStreamWriter;
	bool FWritingHeader;
	
protected:
	virtual bool __fastcall IncludeMethod(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual void __fastcall DerivedWrite(const System::UnicodeString Line);
	virtual void __fastcall DerivedWriteLine();
	virtual void __fastcall StartCppHeader();
	virtual void __fastcall EndCppHeader();
	
public:
	__property System::Classes::TStreamWriter* StreamWriter = {read=FStreamWriter, write=FStreamWriter};
	__property System::Classes::TStreamWriter* HeaderStreamWriter = {read=FHeaderStreamWriter, write=FHeaderStreamWriter};
	__fastcall virtual ~TDSCppProxyWriter();
public:
	/* TDSCustomCppProxyWriter.Create */ inline __fastcall TDSCppProxyWriter() : TDSCustomCppProxyWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define sCPlusPlusBuilderDBXProxyWriter u"C++Builder DBX"
}	/* namespace Dsproxycpp */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYCPP)
using namespace Datasnap::Dsproxycpp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxycppHPP
