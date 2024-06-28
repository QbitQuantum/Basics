// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSybaseASAMetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseasametadatareaderHPP
#define Data_DbxsybaseasametadatareaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataNames.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxsybaseasametadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASACustomMetaDataReader;
class DELPHICLASS TDBXSybaseASAMetaDataReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASACustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
	
public:
	class DELPHICLASS TDBXSybaseASAForeignKeyColumnsCursor;
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	class PASCALIMPLEMENTATION TDBXSybaseASAForeignKeyColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXSybaseASAForeignKeyColumnsCursor();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXSybaseASAForeignKeyColumnsCursor(TDBXSybaseASACustomMetaDataReader* const Provider, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		System::UnicodeString FSchemaName;
		System::UnicodeString FPrevSchemaName;
		System::UnicodeString FTableName;
		System::UnicodeString FPrevTableName;
		__int64 FIndexId;
		__int64 FPrevIndexId;
		int FRunningOrdinal;
		Data::Dbxcommon::TDBXWritableValue* FOrdinalValue;
		static const System::Int8 ForeignkeyColumnIndexIndicator = System::Int8(0xb);
		
		static const System::Int8 NullIndexId = System::Int8(-1);
		
	};
	
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeyColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString ForeignKeyName, const System::UnicodeString PrimaryCatalog, const System::UnicodeString PrimarySchema, const System::UnicodeString PrimaryTable, const System::UnicodeString PrimaryKeyName);
	
protected:
	virtual void __fastcall SetContext(Data::Dbxmetadatareader::TDBXProviderContext* const Context);
	
private:
	System::UnicodeString FVendorLibPath;
	bool FSupportsNLSDataType;
	bool FIsServerCharsetUTF8;
	bool FIsCharUnicode;
	
public:
	__property System::UnicodeString VendorLibPath = {read=FVendorLibPath};
	__property bool SupportsNLSDataType = {read=FSupportsNLSDataType, nodefault};
	__property bool IsServerCharsetUTF8 = {read=FIsServerCharsetUTF8, nodefault};
	__property bool IsCharUnicode = {read=FIsCharUnicode, nodefault};
	__property bool DefaultCharSetUnicode = {read=FIsServerCharsetUTF8, nodefault};
	
private:
	#define TDBXSybaseASACustomMetaDataReader_VendorLibPathPropertyName L"VendorLibPath"
	
	#define TDBXSybaseASACustomMetaDataReader_SupportsNLSDataTypePropertyName L"SupportsNLSDataType"
	
	#define TDBXSybaseASACustomMetaDataReader_IsServerCharsetUTF8PropertyName L"IsServerCharsetUTF8"
	
	#define TDBXSybaseASACustomMetaDataReader_IsCharUnicodePropertyName L"IsCharUnicode"
	
	#define TDBXSybaseASACustomMetaDataReader_UnicodeEncodingPropertyName L"UnicodeEncoding"
	
public:
	/* TDBXBaseMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXSybaseASACustomMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXSybaseASACustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASAMetaDataReader : public TDBXSybaseASACustomMetaDataReader
{
	typedef TDBXSybaseASACustomMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSynonyms(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString SynonymName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	
protected:
	virtual bool __fastcall AreSchemasSupported();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetTableType();
	virtual System::UnicodeString __fastcall GetViewType();
	virtual System::UnicodeString __fastcall GetSystemTableType();
	virtual System::UnicodeString __fastcall GetSystemViewType();
	virtual bool __fastcall IsLowerCaseIdentifiersSupported();
	virtual bool __fastcall IsSetRowSizeSupported();
	virtual bool __fastcall IsUpperCaseIdentifiersSupported();
	virtual System::UnicodeString __fastcall GetSqlForSchemas();
	virtual System::UnicodeString __fastcall GetSqlForTables();
	virtual System::UnicodeString __fastcall GetSqlForViews();
	virtual System::UnicodeString __fastcall GetSqlForColumns();
	virtual System::UnicodeString __fastcall GetSqlForIndexes();
	virtual System::UnicodeString __fastcall GetSqlForIndexColumns();
	virtual System::UnicodeString __fastcall GetSqlForForeignKeys();
	virtual System::UnicodeString __fastcall GetSqlForForeignKeyColumns();
	virtual System::UnicodeString __fastcall GetSqlForProcedures();
	virtual System::UnicodeString __fastcall GetSqlForProcedureSources();
	virtual System::UnicodeString __fastcall GetSqlForProcedureParameters();
	virtual System::UnicodeString __fastcall GetSqlForUsers();
	virtual System::UnicodeString __fastcall GetSqlForRoles();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXBaseMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXSybaseASAMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXSybaseASAMetaDataReader() : TDBXSybaseASACustomMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybaseasametadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASAMETADATAREADER)
using namespace Data::Dbxsybaseasametadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseasametadatareaderHPP
