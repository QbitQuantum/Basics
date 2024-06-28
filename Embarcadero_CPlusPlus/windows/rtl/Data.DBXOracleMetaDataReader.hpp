// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXOracleMetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_DbxoraclemetadatareaderHPP
#define Data_DbxoraclemetadatareaderHPP

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
namespace Dbxoraclemetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXOracleCustomMetaDataReader;
class DELPHICLASS TDBXOracleMetaDataReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOracleCustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
	
public:
	class DELPHICLASS TDBXOracleColumnsCursor;
	class PASCALIMPLEMENTATION TDBXOracleColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXOracleColumnsCursor();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXOracleColumnsCursor(TDBXOracleCustomMetaDataReader* const Provider, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	public:
		Data::Dbxcommon::TDBXWritableValue* FDefaultValue;
	};
	
	
	class DELPHICLASS TDBXOracleIndexColumnsCursor;
	class PASCALIMPLEMENTATION TDBXOracleIndexColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXOracleIndexColumnsCursor();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXOracleIndexColumnsCursor(TDBXOracleCustomMetaDataReader* const Provider, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		System::UnicodeString __fastcall ComputeColumnName();
		Data::Dbxcommon::TDBXWritableValue* FNameValue;
		static const System::Int8 ColumnExpressionOrdinal = System::Int8(0x7);
		
		static const System::Int8 ColumnExpressionNullOrdinal = System::Int8(0x8);
		
	};
	
	
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString Index);
	
protected:
	virtual void __fastcall PopulateDataTypes(Data::Dbxplatform::TDBXObjectStore* const Hash, Data::Dbxplatform::TDBXArrayList* const Types, const Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray Descr);
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
public:
	/* TDBXBaseMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXOracleCustomMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXOracleCustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOracleMetaDataReader : public TDBXOracleCustomMetaDataReader
{
	typedef TDBXOracleCustomMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	
protected:
	virtual bool __fastcall AreSchemasSupported();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual bool __fastcall IsNestedTransactionsSupported();
	virtual bool __fastcall IsSetRowSizeSupported();
	virtual System::UnicodeString __fastcall GetSqlForSchemas();
	virtual System::UnicodeString __fastcall GetSqlForTables();
	virtual System::UnicodeString __fastcall GetSqlForViews();
	virtual System::UnicodeString __fastcall GetSqlForColumns();
	virtual System::UnicodeString __fastcall GetSqlForIndexes();
	virtual System::UnicodeString __fastcall GetSqlForIndexColumns();
	virtual System::UnicodeString __fastcall GetSqlForForeignKeys();
	virtual System::UnicodeString __fastcall GetSqlForForeignKeyColumns();
	virtual System::UnicodeString __fastcall GetSqlForSynonyms();
	virtual System::UnicodeString __fastcall GetSqlForProcedures();
	virtual System::UnicodeString __fastcall GetSqlForProcedureSources();
	virtual System::UnicodeString __fastcall GetSqlForProcedureParameters();
	virtual System::UnicodeString __fastcall GetSqlForPackages();
	virtual System::UnicodeString __fastcall GetSqlForPackageSources();
	virtual System::UnicodeString __fastcall GetSqlForPackageProcedures();
	virtual System::UnicodeString __fastcall GetSqlForPackageProcedureParameters();
	virtual System::UnicodeString __fastcall GetSqlForUsers();
	virtual System::UnicodeString __fastcall GetSqlForRoles();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXBaseMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXOracleMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXOracleMetaDataReader() : TDBXOracleCustomMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxoraclemetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXORACLEMETADATAREADER)
using namespace Data::Dbxoraclemetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxoraclemetadatareaderHPP
