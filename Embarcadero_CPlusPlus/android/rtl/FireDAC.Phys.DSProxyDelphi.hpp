// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.DSProxyDelphi.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_DsproxydelphiHPP
#define Firedac_Phys_DsproxydelphiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSProxyWriter.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Phys
{
namespace Dsproxydelphi
{
  _INIT_UNIT(Firedac_Phys_Dsproxydelphi);
}	/* namespace Dsproxydelphi */
}	/* namespace Phys */
}	/* namespace Firedac */

namespace Firedac
{
namespace Phys
{
namespace Dsproxydelphi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterDelphi;
class DELPHICLASS TDSCustomExtendedProxyWriter;
class DELPHICLASS TDSCustomDelphiProxyWriter;
class DELPHICLASS TDSDelphiProxyWriter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
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

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCustomExtendedProxyWriter : public Datasnap::Dsproxywriter::TDSCustomProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSCustomProxyWriter inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetClassNameSuffix();
	
public:
	virtual System::TArray__1<System::UnicodeString> __fastcall GetProxyClassNames();
public:
	/* TDSCustomProxyWriter.Create */ inline __fastcall TDSCustomExtendedProxyWriter() : Datasnap::Dsproxywriter::TDSCustomProxyWriter() { }
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomExtendedProxyWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSCustomDelphiProxyWriter : public TDSCustomExtendedProxyWriter
{
	typedef TDSCustomExtendedProxyWriter inherited;
	
public:
	__fastcall TDSCustomDelphiProxyWriter();
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
	void __fastcall WriteMethodSignature(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const Method, const bool IsInterface);
	void __fastcall WriteClassInterface(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	void __fastcall WriteOutgoingParameter(const System::UnicodeString Lhs, const System::UnicodeString InRhs, Datasnap::Dscommonproxy::TDSProxyParameter* const Param, const System::UnicodeString CommandName, const System::UnicodeString ParamName);
	void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
public:
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomDelphiProxyWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDSDelphiProxyWriter : public TDSCustomDelphiProxyWriter
{
	typedef TDSCustomDelphiProxyWriter inherited;
	
private:
	System::Classes::TStreamWriter* FStreamWriter;
	
protected:
	virtual void __fastcall DerivedWrite(const System::UnicodeString Line);
	virtual void __fastcall DerivedWriteLine();
	
public:
	__property System::Classes::TStreamWriter* StreamWriter = {read=FStreamWriter, write=FStreamWriter};
	__fastcall virtual ~TDSDelphiProxyWriter();
public:
	/* TDSCustomDelphiProxyWriter.Create */ inline __fastcall TDSDelphiProxyWriter() : TDSCustomDelphiProxyWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define sDelphiFireDACProxyWriter u"Delphi FireDAC"
}	/* namespace Dsproxydelphi */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_DSPROXYDELPHI)
using namespace Firedac::Phys::Dsproxydelphi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_DsproxydelphiHPP
