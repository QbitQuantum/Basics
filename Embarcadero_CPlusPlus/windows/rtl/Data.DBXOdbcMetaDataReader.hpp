// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXOdbcMetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_DbxodbcmetadatareaderHPP
#define Data_DbxodbcmetadatareaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataNames.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DbxOdbc.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxodbcmetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXOdbcCustomMetaDataReader;
class DELPHICLASS TDBXOdbcMetaDataReader;
class DELPHICLASS TDBXOdbcColumnsTableCursor;
class DELPHICLASS TDBXOdbcProcedureParametersIndex;
class DELPHICLASS TDBXOdbcColumnsIndex;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcCustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
private:
	Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray FAlltypes;
	
public:
	__fastcall virtual ~TDBXOdbcCustomMetaDataReader();
public:
	/* TObject.Create */ inline __fastcall TDBXOdbcCustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcMetaDataReader : public TDBXOdbcCustomMetaDataReader
{
	typedef TDBXOdbcCustomMetaDataReader inherited;
	
private:
	void *FConnectionHandle;
	Data::Dbxodbc::TDBXOdbcConnection* FOdbcConnection;
	Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray FDataTypeDescriptions;
	System::Word FIndexKeyword;
	System::Word FMaxConcurrentActivities;
	System::Classes::TStrings* FReservedWords;
	bool FCatalogsSupported;
	bool FSchemasSupported;
	bool FSupportsMultipleTransactions;
	System::UnicodeString FSqlIdentifierQuoteChar;
	System::Word FSqlIdentifierCase;
	bool FSupportsParameterMetaData;
	System::Word FTransactionCapable;
	bool FInitialized;
	void __fastcall CheckInitialized();
	void __fastcall CheckResult(short ReturnValue);
	void __fastcall Init();
	void __fastcall SetDataTypeDescriptions();
#ifndef _WIN64
	void __fastcall SetReservedWords(System::DynamicArray<System::Byte> Buffer);
#else /* _WIN64 */
	void __fastcall SetReservedWords(System::TArray__1<System::Byte> Buffer);
#endif /* _WIN64 */
	Data::Dbxcommontable::TDBXTable* __fastcall SqlTablesInvocation(System::UnicodeString CommandText, System::UnicodeString Catalog, System::UnicodeString Schema, System::UnicodeString TableName, System::UnicodeString TableType);
	
protected:
	virtual bool __fastcall AreCatalogFunctionsSupported();
	virtual bool __fastcall AreCatalogsSupported();
	virtual bool __fastcall AreSchemasSupported();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteChar();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix();
	virtual System::UnicodeString __fastcall GetSqlProcedureQuoteChar();
	virtual bool __fastcall IsDescendingIndexSupported();
	virtual bool __fastcall IsLowerCaseIdentifiersSupported();
	virtual bool __fastcall IsMultipleCommandsSupported();
	virtual bool __fastcall IsNestedTransactionsSupported();
	virtual bool __fastcall IsParameterMetadataSupported();
	virtual bool __fastcall IsQuotedIdentifiersSupported();
	virtual bool __fastcall IsSetRowSizeSupported();
	virtual bool __fastcall IsTransactionsSupported();
	virtual bool __fastcall IsUpperCaseIdentifiersSupported();
	virtual void __fastcall PopulateDataTypes(Data::Dbxplatform::TDBXObjectStore* const Hash, Data::Dbxplatform::TDBXArrayList* const Types, const Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray Descr);
	
public:
	__fastcall TDBXOdbcMetaDataReader()/* overload */;
	__fastcall TDBXOdbcMetaDataReader(Data::Dbxodbc::TDBXOdbcConnection* OdbcConnection)/* overload */;
	__fastcall virtual ~TDBXOdbcMetaDataReader();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeyColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString ForeignKeyName, const System::UnicodeString PrimaryCatalog, const System::UnicodeString PrimarySchema, const System::UnicodeString PrimaryTable, const System::UnicodeString PrimaryKeyName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeys(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString Index);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexes(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedures(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc, const System::UnicodeString Parameter);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureSources(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchRoles();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSchemas(const System::UnicodeString Catalog);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSynonyms(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Synonym);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchTables(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString TableName, const System::UnicodeString TableType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchUsers();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchViews(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString View);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcColumnsTableCursor : public Data::Dbxmetadatareader::TDBXColumnsTableCursor
{
	typedef Data::Dbxmetadatareader::TDBXColumnsTableCursor inherited;
	
private:
	Data::Dbxcommontable::TDBXSingleValueRow* FDataTypesRow;
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
public:
	__fastcall TDBXOdbcColumnsTableCursor(Data::Dbxmetadatareader::TDBXBaseMetaDataReader* const Reader, const bool CheckBase, Data::Dbxcommontable::TDBXTable* const Cursor);
	__fastcall virtual ~TDBXOdbcColumnsTableCursor();
	virtual bool __fastcall Next();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcProcedureParametersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 ColumnName = System::Int8(0x3);
	
	static const System::Int8 Mode = System::Int8(0x4);
	
	static const System::Int8 SqlDataType = System::Int8(0x5);
	
	static const System::Int8 TypeName = System::Int8(0x6);
	
	static const System::Int8 ColumnSize = System::Int8(0x7);
	
	static const System::Int8 BufferLength = System::Int8(0x8);
	
	static const System::Int8 Scale = System::Int8(0x9);
	
	static const System::Int8 NumPrecRadix = System::Int8(0xa);
	
	static const System::Int8 IsNullable = System::Int8(0xb);
	
	static const System::Int8 Remarks = System::Int8(0xc);
	
	static const System::Int8 ColumnDef = System::Int8(0xd);
	
	static const System::Int8 DescSqlDataType = System::Int8(0xe);
	
	static const System::Int8 SqlDatetimeSub = System::Int8(0xf);
	
	static const System::Int8 CharOctetLength = System::Int8(0x10);
	
	static const System::Int8 Ordinal = System::Int8(0x11);
	
	static const System::Int8 IsNullableChar = System::Int8(0x12);
	
	static const System::Int8 DbxDataType = System::Int8(0x13);
	
	static const System::Int8 ParameterMode = System::Int8(0x14);
	
	static const System::Int8 IsFixedLength = System::Int8(0x15);
	
	static const System::Int8 Last = System::Int8(0x15);
	
public:
	/* TObject.Create */ inline __fastcall TDBXOdbcProcedureParametersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXOdbcProcedureParametersIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 ColumnName = System::Int8(0x3);
	
	static const System::Int8 SqlDataType = System::Int8(0x4);
	
	static const System::Int8 TypeName = System::Int8(0x5);
	
	static const System::Int8 ColumnSize = System::Int8(0x6);
	
	static const System::Int8 BufferLength = System::Int8(0x7);
	
	static const System::Int8 Scale = System::Int8(0x8);
	
	static const System::Int8 NumPrecRadix = System::Int8(0x9);
	
	static const System::Int8 IsNullable = System::Int8(0xa);
	
	static const System::Int8 Remarks = System::Int8(0xb);
	
	static const System::Int8 ColumnDef = System::Int8(0xc);
	
	static const System::Int8 DescSqlDataType = System::Int8(0xd);
	
	static const System::Int8 SqlDatetimeSub = System::Int8(0xe);
	
	static const System::Int8 CharOctetLength = System::Int8(0xf);
	
	static const System::Int8 Ordinal = System::Int8(0x10);
	
	static const System::Int8 IsNullableChar = System::Int8(0x11);
	
	static const System::Int8 Last = System::Int8(0x11);
	
public:
	/* TObject.Create */ inline __fastcall TDBXOdbcColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXOdbcColumnsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxodbcmetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXODBCMETADATAREADER)
using namespace Data::Dbxodbcmetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxodbcmetadatareaderHPP
