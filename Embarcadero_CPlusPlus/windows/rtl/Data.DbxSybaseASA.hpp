// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxSybaseASA.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseasaHPP
#define Data_DbxsybaseasaHPP

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
#include <Data.DBXSybaseASAReadOnlyMetaData.hpp>
#include <Data.DBXSybaseASAMetaData.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxSybaseASA"

namespace Data
{
namespace Dbxsybaseasa
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASAProperties;
class DELPHICLASS TDBXSybaseASADriver;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXSybaseASAProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXSybaseASAProperties_StrASATransIsolation L"ASA TransIsolation"
	
	System::UnicodeString __fastcall GetHostName();
	System::UnicodeString __fastcall GetDBHostName();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	int __fastcall GetBlobSize();
	System::UnicodeString __fastcall GetSybaseASATransIsolation();
	void __fastcall SetBlobSize(const int Value);
	void __fastcall SetSybaseASATransIsolation(const System::UnicodeString Value);
	void __fastcall SetHostName(const System::UnicodeString Value);
	void __fastcall SetDBHostName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDBXSybaseASAProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property System::UnicodeString HostName = {read=GetHostName, write=SetHostName};
	__property System::UnicodeString DBHostName = {read=GetDBHostName, write=SetDBHostName};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property int BlobSize = {read=GetBlobSize, write=SetBlobSize, nodefault};
	__property System::UnicodeString SybaseASATransIsolation = {read=GetSybaseASATransIsolation, write=SetSybaseASATransIsolation};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXSybaseASAProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXSybaseASAProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASADriver : public Data::Dbxdynalinknative::TDBXDynalinkDriverNative
{
	typedef Data::Dbxdynalinknative::TDBXDynalinkDriverNative inherited;
	
public:
	__fastcall virtual TDBXSybaseASADriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
public:
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXSybaseASADriver(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DriverClone, DriverHandle, MethodTable) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXSybaseASADriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXSybaseASADriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader, DriverProps) { }
	
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXSybaseASADriver() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXSybaseASADriver()/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybaseasa */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASA)
using namespace Data::Dbxsybaseasa;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseasaHPP
