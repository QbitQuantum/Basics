﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxInterbase.pas' rev: 34.00 (Windows)

#ifndef Data_DbxinterbaseHPP
#define Data_DbxinterbaseHPP

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
#include <Data.DBXInterbaseReadOnlyMetaData.hpp>
#include <Data.DBXInterbaseMetaData.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxInterbase"

namespace Data
{
namespace Dbxinterbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXInterBaseProperties;
class DELPHICLASS TDBXInterBaseDriver;
class DELPHICLASS TDBXIBToGoProperties;
class DELPHICLASS TDBXIBToGoDriver;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXInterBaseProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXInterBaseProperties_StrServerCharSet L"ServerCharSet"
	
	System::UnicodeString __fastcall GetDatabase();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	System::UnicodeString __fastcall GetServerCharSet();
	void __fastcall SetServerCharSet(const System::UnicodeString Value);
	void __fastcall SetDatabase(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDBXInterBaseProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property System::UnicodeString Database = {read=GetDatabase, write=SetDatabase};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString ServerCharSet = {read=GetServerCharSet, write=SetServerCharSet};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXInterBaseProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXInterBaseProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXInterBaseDriver : public Data::Dbxdynalinknative::TDBXDynalinkDriverNative
{
	typedef Data::Dbxdynalinknative::TDBXDynalinkDriverNative inherited;
	
public:
	__fastcall virtual TDBXInterBaseDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
public:
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXInterBaseDriver(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DriverClone, DriverHandle, MethodTable) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXInterBaseDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXInterBaseDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader, DriverProps) { }
	
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXInterBaseDriver() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXInterBaseDriver()/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDBXIBToGoProperties : public TDBXInterBaseProperties
{
	typedef TDBXInterBaseProperties inherited;
	
public:
	__fastcall virtual TDBXIBToGoProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXIBToGoProperties()/* overload */ : TDBXInterBaseProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXIBToGoProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIBToGoDriver : public Data::Dbxdynalinknative::TDBXDynalinkDriverNative
{
	typedef Data::Dbxdynalinknative::TDBXDynalinkDriverNative inherited;
	
public:
	__fastcall virtual TDBXIBToGoDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
public:
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXIBToGoDriver(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DriverClone, DriverHandle, MethodTable) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXIBToGoDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXIBToGoDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader, DriverProps) { }
	
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXIBToGoDriver() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXIBToGoDriver()/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxinterbase */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXINTERBASE)
using namespace Data::Dbxinterbase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxinterbaseHPP
