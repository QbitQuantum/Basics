// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSProxyObjectiveCiOS.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsproxyobjectiveciosHPP
#define Datasnap_DsproxyobjectiveciosHPP

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
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Datasnap.DSProxyObjectiveCiOS"

namespace Datasnap
{
namespace Dsproxyobjectivecios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSClientProxyWriterObjectiveCiOS;
class DELPHICLASS TDSClientProxyWriterObjectiveCiOS42;
class DELPHICLASS TDSClientProxyWriterObjectiveCiOS71;
class DELPHICLASS TDSClientProxyWriterObjectiveCiOS81;
class DELPHICLASS TDSCustomObjectiveCiOSProxyWriter;
class DELPHICLASS TDSIOSProxyWriter;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFilePart : unsigned char { fpInterface, fpImplementation };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterObjectiveCiOS : public Datasnap::Dsproxywriter::TDSProxyWriter
{
	typedef Datasnap::Dsproxywriter::TDSProxyWriter inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSCustomProxyWriter* __fastcall CreateProxyWriter();
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
	virtual Datasnap::Dsproxywriter::TDSProxyFileDescriptions __fastcall FileDescriptions();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterObjectiveCiOS() : Datasnap::Dsproxywriter::TDSProxyWriter() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterObjectiveCiOS() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterObjectiveCiOS42 : public TDSClientProxyWriterObjectiveCiOS
{
	typedef TDSClientProxyWriterObjectiveCiOS inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterObjectiveCiOS42() : TDSClientProxyWriterObjectiveCiOS() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterObjectiveCiOS42() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterObjectiveCiOS71 : public TDSClientProxyWriterObjectiveCiOS
{
	typedef TDSClientProxyWriterObjectiveCiOS inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterObjectiveCiOS71() : TDSClientProxyWriterObjectiveCiOS() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterObjectiveCiOS71() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TDSClientProxyWriterObjectiveCiOS81 : public TDSClientProxyWriterObjectiveCiOS
{
	typedef TDSClientProxyWriterObjectiveCiOS inherited;
	
public:
	virtual Datasnap::Dsproxywriter::TDSProxyWriterProperties __fastcall Properties();
public:
	/* TFactoryObject.Create */ inline __fastcall virtual TDSClientProxyWriterObjectiveCiOS81() : TDSClientProxyWriterObjectiveCiOS() { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSClientProxyWriterObjectiveCiOS81() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCustomObjectiveCiOSProxyWriter : public Datasnap::Dscustomconnectorproxywriter::TDSCustomConnectorProxyWriter
{
	typedef Datasnap::Dscustomconnectorproxywriter::TDSCustomConnectorProxyWriter inherited;
	
public:
	virtual void __fastcall WriteProxy();
	
protected:
	TFilePart FCurrFilePart;
	virtual System::UnicodeString __fastcall GetCreateDataSetReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual System::UnicodeString __fastcall GetCreateParamsReader(Datasnap::Dscommonproxy::TDSProxyParameter* const Param);
	virtual void __fastcall WriteInterface();
	virtual void __fastcall WriteObjectiveCLine(const System::UnicodeString Line)/* overload */;
	virtual void __fastcall WriteObjectiveCLine()/* overload */;
	virtual void __fastcall WriteImplementation();
	virtual void __fastcall WriteClassImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, System::Classes::TStringList* const ProxyClassNameList);
	virtual void __fastcall WriteClassInterface(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, System::Classes::TStringList* const ProxyClassNameList);
	virtual void __fastcall WriteMethodComment(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual void __fastcall WriteMethodImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual void __fastcall WriteMethodInterface(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	virtual void __fastcall WriteClassInitImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	virtual void __fastcall WriteClassDeallocImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass);
	virtual void __fastcall WriteParamImplementation(Datasnap::Dscommonproxy::TDSProxyClass* const ProxyClass, Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	System::UnicodeString __fastcall GetObjectiveCType(Datasnap::Dscommonproxy::TDSProxyParameter* Param);
	System::UnicodeString __fastcall GetCastType(Datasnap::Dscommonproxy::TDSProxyParameter* Param);
	HIDESBASE bool __fastcall HasOnlyURLParams(Datasnap::Dscommonproxy::TDSProxyMethod* const Method);
	void __fastcall WriteSetterForInputParams(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod);
	void __fastcall WriteGetterForOutputParams(Datasnap::Dscommonproxy::TDSProxyMethod* const ProxyMethod)/* overload */;
	virtual System::UnicodeString __fastcall GetParameterTypePrefix();
	virtual System::UnicodeString __fastcall GetParameterDirectionPrefix();
	
public:
	__property bool GenerateURLFunctions = {read=FGenerateURLFunctions, write=FGenerateURLFunctions, nodefault};
public:
	/* TDSCustomConnectorProxyWriter.Create */ inline __fastcall virtual TDSCustomObjectiveCiOSProxyWriter() : Datasnap::Dscustomconnectorproxywriter::TDSCustomConnectorProxyWriter() { }
	
public:
	/* TDSCustomProxyWriter.Destroy */ inline __fastcall virtual ~TDSCustomObjectiveCiOSProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSIOSProxyWriter : public TDSCustomObjectiveCiOSProxyWriter
{
	typedef TDSCustomObjectiveCiOSProxyWriter inherited;
	
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
	__fastcall virtual ~TDSIOSProxyWriter();
public:
	/* TDSCustomConnectorProxyWriter.Create */ inline __fastcall virtual TDSIOSProxyWriter() : TDSCustomObjectiveCiOSProxyWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
#define sObjectiveCiOS_RESTProxyWriter42 L"Objective-C iOS 4.2 REST"
#define sObjectiveCiOS_RESTProxyWriter71 L"Objective-C iOS 7.1 REST"
#define sObjectiveCiOS_RESTProxyWriter81 L"Objective-C iOS 8.1 REST"
}	/* namespace Dsproxyobjectivecios */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSPROXYOBJECTIVECIOS)
using namespace Datasnap::Dsproxyobjectivecios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsproxyobjectiveciosHPP
