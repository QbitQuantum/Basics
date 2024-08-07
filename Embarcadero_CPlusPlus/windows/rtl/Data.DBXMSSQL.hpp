﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxMSSQL.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmssqlHPP
#define Data_DbxmssqlHPP

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
#include <Data.DBXMSSQLReadOnlyMetaData.hpp>
#include <Data.DBXMSSQLMetaData.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxMSSQL"

namespace Data
{
namespace Dbxmssql
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMSSQLProperties;
class DELPHICLASS TDBXMSSQLDriver;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXMSSQLProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXMSSQLProperties_StrOSAuthentication L"OS Authentication"
	
	#define TDBXMSSQLProperties_StrPrepareSQL L"Prepare SQL"
	
	#define TDBXMSSQLProperties_StrMSSQLTransIsolation L"MSSQL TransIsolation"
	
	int __fastcall GetBlobSize();
	System::UnicodeString __fastcall GetMSSQLTransIsolation();
	bool __fastcall GetOSAuthentication();
	bool __fastcall GetPrepareSql();
	System::UnicodeString __fastcall GetSchemaOverride();
	System::UnicodeString __fastcall GetDatabase();
	void __fastcall SetDatabase(const System::UnicodeString Value);
	void __fastcall SetBlobSize(const int Value);
	void __fastcall SetMSSQLTransIsolation(const System::UnicodeString Value);
	void __fastcall SetOSAuthentication(const bool Value);
	void __fastcall SetPrepareSql(const bool Value);
	void __fastcall SetSchemaOverride(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetHostName();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	void __fastcall SetHostName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDBXMSSQLProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property System::UnicodeString HostName = {read=GetHostName, write=SetHostName};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString SchemaOverride = {read=GetSchemaOverride, write=SetSchemaOverride};
	__property int BlobSize = {read=GetBlobSize, write=SetBlobSize, nodefault};
	__property System::UnicodeString MSSQLTransIsolation = {read=GetMSSQLTransIsolation, write=SetMSSQLTransIsolation};
	__property bool OSAuthentication = {read=GetOSAuthentication, write=SetOSAuthentication, nodefault};
	__property bool PrepareSQL = {read=GetPrepareSql, write=SetPrepareSql, nodefault};
	__property System::UnicodeString Database = {read=GetDatabase, write=SetDatabase};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXMSSQLProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXMSSQLProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMSSQLDriver : public Data::Dbxdynalinknative::TDBXDynalinkDriverNative
{
	typedef Data::Dbxdynalinknative::TDBXDynalinkDriverNative inherited;
	
public:
	__fastcall virtual TDBXMSSQLDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
public:
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXMSSQLDriver(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DriverClone, DriverHandle, MethodTable) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXMSSQLDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXMSSQLDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader, DriverProps) { }
	
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXMSSQLDriver() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXMSSQLDriver()/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmssql */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMSSQL)
using namespace Data::Dbxmssql;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmssqlHPP
