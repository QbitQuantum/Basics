// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DbxOracle.pas' rev: 34.00 (Windows)

#ifndef Data_DbxoracleHPP
#define Data_DbxoracleHPP

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
#include <Data.DBXOracleReadOnlyMetaData.hpp>
#include <Data.DBXOracleMetaData.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DbxOracle"

namespace Data
{
namespace Dbxoracle
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXOracleProperties;
class DELPHICLASS TDBXOracleDriver;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXOracleProperties : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	#define TDBXOracleProperties_StrOSAuthentication L"OS Authentication"
	
	#define TDBXOracleProperties_StrOracleTransIsolation L"Oracle TransIsolation"
	
	#define TDBXOracleProperties_StrDecimalSeparator L"Decimal Separator"
	
	#define TDBXOracleProperties_StrTrimChar L"Trim Char"
	
	#define TDBXOracleProperties_StrMultipleTransaction L"Multiple Transaction"
	
	#define TDBXOracleProperties_StrRowsetSize L"RowsetSize"
	
	System::UnicodeString __fastcall GetHostName();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	int __fastcall GetBlobSize();
	System::UnicodeString __fastcall GetDatabase();
	System::UnicodeString __fastcall GetOracleTransIsolation();
	System::UnicodeString __fastcall GetDecimalSeparator();
	bool __fastcall GetTrimChar();
	int __fastcall GetRowsetSize();
	bool __fastcall GetOSAuthentication();
	bool __fastcall GetMultipleTransaction();
	void __fastcall SetMultipleTransaction(const bool Value);
	void __fastcall SetOSAuthentication(const bool Value);
	void __fastcall SetRowsetSize(const int Value);
	void __fastcall SetBlobSize(const int Value);
	void __fastcall SetDatabase(const System::UnicodeString Value);
	void __fastcall SetOracleTransIsolation(const System::UnicodeString Value);
	void __fastcall SetDecimalSeparator(const System::UnicodeString Value);
	void __fastcall SetTrimChar(const bool Value);
	void __fastcall SetHostName(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDBXOracleProperties(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */;
	
__published:
	__property System::UnicodeString HostName = {read=GetHostName, write=SetHostName};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString Database = {read=GetDatabase, write=SetDatabase};
	__property int BlobSize = {read=GetBlobSize, write=SetBlobSize, nodefault};
	__property System::UnicodeString OracleTransIsolation = {read=GetOracleTransIsolation, write=SetOracleTransIsolation};
	__property System::UnicodeString DecimalSeparator = {read=GetDecimalSeparator, write=SetDecimalSeparator};
	__property bool OSAuthentication = {read=GetOSAuthentication, write=SetOSAuthentication, nodefault};
	__property bool TrimChar = {read=GetTrimChar, write=SetTrimChar, nodefault};
	__property int RowsetSize = {read=GetRowsetSize, write=SetRowsetSize, nodefault};
	__property bool MultipleTransaction = {read=GetMultipleTransaction, write=SetMultipleTransaction, nodefault};
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXOracleProperties()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXOracleProperties() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOracleDriver : public Data::Dbxdynalinknative::TDBXDynalinkDriverNative
{
	typedef Data::Dbxdynalinknative::TDBXDynalinkDriverNative inherited;
	
public:
	__fastcall virtual TDBXOracleDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
public:
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXOracleDriver(Data::Dbxcommon::TDBXDriver* DriverClone, void * DriverHandle, Data::Dbxdynalink::TDBXMethodTable* MethodTable)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DriverClone, DriverHandle, MethodTable) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXOracleDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader) { }
	/* TDBXDynalinkDriverNative.Create */ inline __fastcall TDBXOracleDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef, Data::Dbxdynalink::TDBXDynalinkDriverCommonLoaderClass DBXDriverLoader, Data::Dbxcommon::TDBXProperties* DriverProps)/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative(DBXDriverDef, DBXDriverLoader, DriverProps) { }
	
public:
	/* TDBXDynalinkDriver.Destroy */ inline __fastcall virtual ~TDBXOracleDriver() { }
	
public:
	/* TDBXDriver.Create */ inline __fastcall TDBXOracleDriver()/* overload */ : Data::Dbxdynalinknative::TDBXDynalinkDriverNative() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxoracle */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXORACLE)
using namespace Data::Dbxoracle;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxoracleHPP
