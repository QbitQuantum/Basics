// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxSybaseASE.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseaseHPP
#define Data_DbxsybaseaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXDynalink.hpp>
#include <Data.DBXDynalinkNative.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXSybaseASEReadOnlyMetaData.hpp>
#include <Data.DBXSybaseASEMetaData.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxSybaseASE"

namespace Data
{
namespace Dbxsybasease
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASEProperties;
class DELPHICLASS TDBXSybaseASEDriver;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXSybaseASEProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXSybaseASEProperties_StrASETransIsolation L"ASE TransIsolation"
	
	#define TDBXSybaseASEProperties_StrTDSPacketSize L"TDS Packet Size"
	
	#define TDBXSybaseASEProperties_StrClientHostName L"Client HostName"
	
	#define TDBXSybaseASEProperties_StrClientAppName L"Client AppName"
	
	System::UnicodeString __fastcall GetHostName();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	int __fastcall GetBlobSize();
	System::UnicodeString __fastcall GetDatabase();
	int __fastcall GetTDSPacketSize();
	System::UnicodeString __fastcall GetSybaseASETransIsolation();
	System::UnicodeString __fastcall GetClientAppName();
	System::UnicodeString __fastcall GetClientHostName();
	void __fastcall SetClientAppName(const System::UnicodeString Value);
	void __fastcall SetClientHostName(const System::UnicodeString Value);
	void __fastcall SetTDSPacketSize(const int Value);
	void __fastcall SetBlobSize(const int Value);
	void __fastcall SetDatabase(const System::UnicodeString Value);
	void __fastcall SetSybaseASETransIsolation(const System::UnicodeString Value);
	void __fastcall SetHostName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDBXSybaseASEProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property System::UnicodeString HostName = {read=GetHostName, write=SetHostName};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString Database = {read=GetDatabase, write=SetDatabase};
	__property int BlobSize = {read=GetBlobSize, write=SetBlobSize, nodefault};
	__property System::UnicodeString SybaseASETransIsolation = {read=GetSybaseASETransIsolation, write=SetSybaseASETransIsolation};
	__property int TDSPacketSize = {read=GetTDSPacketSize, write=SetTDSPacketSize, nodefault};
	__property System::UnicodeString ClientHostName = {read=GetClientHostName, write=SetClientHostName};
	__property System::UnicodeString ClientAppName = {read=GetClientAppName, write=SetClientAppName};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXSybaseASEProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXSybaseASEProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASEDriver : public Data::Dbxdynalinknative::TDBXDynalinkDriverNative
{
	typedef Data::Dbxdynalinknative::TDBXDynalinkDriverNative inherited;
	
public:
	__fastcall virtual TDBXSybaseASEDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
public:
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXSybaseASEDriver(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DriverClone, DriverHandle, MethodTable) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXSybaseASEDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXSybaseASEDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader, DriverProps) { }
	
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXSybaseASEDriver() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXSybaseASEDriver()/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybasease */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASE)
using namespace Data::Dbxsybasease;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseaseHPP
