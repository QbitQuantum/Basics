// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMSSQLMetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmssqlmetadatareaderHPP
#define Data_DbxmssqlmetadatareaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXSqlScanner.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmssqlmetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMsSqlCustomMetaDataReader;
class DELPHICLASS TDBXMsSqlMetaDataReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMsSqlCustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
	
public:
	class DELPHICLASS TDBXMsSqlSynonymTableCursor;
	class PASCALIMPLEMENTATION TDBXMsSqlSynonymTableCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall TDBXMsSqlSynonymTableCursor(Data::Dbxmetadatareader::TDBXProviderContext* const Context, Data::Dbxsqlscanner::TDBXSqlScanner* const Scanner, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		__fastcall virtual ~TDBXMsSqlSynonymTableCursor();
		virtual bool __fastcall Next();
		
	protected:
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		void __fastcall ParseBaseObject();
		Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
		System::UnicodeString FCatalog;
		System::UnicodeString FSchema;
		System::UnicodeString FTable;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	
public:
	__fastcall virtual ~TDBXMsSqlCustomMetaDataReader();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSynonyms(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Synonym);
	
protected:
	virtual bool __fastcall IsSPReturnCodeSupported();
	
private:
	Data::Dbxsqlscanner::TDBXSqlScanner* __fastcall CreateScanner();
	Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
public:
	/* TObject.Create */ inline __fastcall TDBXMsSqlCustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMsSqlMetaDataReader : public TDBXMsSqlCustomMetaDataReader
{
	typedef TDBXMsSqlCustomMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	
protected:
	virtual bool __fastcall AreCatalogsSupported();
	virtual bool __fastcall AreSchemasSupported();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix();
	virtual System::UnicodeString __fastcall GetTableType();
	virtual System::UnicodeString __fastcall GetViewType();
	virtual System::UnicodeString __fastcall GetSystemTableType();
	virtual System::UnicodeString __fastcall GetSystemViewType();
	virtual System::UnicodeString __fastcall GetSynonymType();
	virtual bool __fastcall IsLowerCaseIdentifiersSupported();
	virtual bool __fastcall IsParameterMetadataSupported();
	virtual System::UnicodeString __fastcall GetSqlForCatalogs();
	virtual System::UnicodeString __fastcall GetSqlForSchemas();
	virtual System::UnicodeString __fastcall GetSqlForTables();
	virtual System::UnicodeString __fastcall GetSqlForViews();
	virtual System::UnicodeString __fastcall GetSqlForColumns();
	virtual System::UnicodeString __fastcall GetSqlForColumnConstraints();
	virtual System::UnicodeString __fastcall GetSqlForIndexes();
	virtual System::UnicodeString __fastcall GetSqlForIndexColumns();
	virtual System::UnicodeString __fastcall GetSqlForForeignKeys();
	virtual System::UnicodeString __fastcall GetSqlForForeignKeyColumns();
	virtual System::UnicodeString __fastcall GetSqlForSynonyms();
	virtual System::UnicodeString __fastcall GetSqlForProcedures();
	virtual System::UnicodeString __fastcall GetSqlForProcedureSources();
	virtual System::UnicodeString __fastcall GetSqlForProcedureParameters();
	virtual System::UnicodeString __fastcall GetSqlForUsers();
	virtual System::UnicodeString __fastcall GetSqlForRoles();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXMsSqlCustomMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXMsSqlMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXMsSqlMetaDataReader() : TDBXMsSqlCustomMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmssqlmetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMSSQLMETADATAREADER)
using namespace Data::Dbxmssqlmetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmssqlmetadatareaderHPP
