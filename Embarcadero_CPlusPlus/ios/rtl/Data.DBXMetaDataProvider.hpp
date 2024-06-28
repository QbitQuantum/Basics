// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataProvider.pas' rev: 34.00 (iOS)

#ifndef Data_DbxmetadataproviderHPP
#define Data_DbxmetadataproviderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXMetaDataWriter.hpp>
#include <Data.DBXTypedTableStorage.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadataprovider
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMetaDataColumn;
class DELPHICLASS TDBXInt8Column;
class DELPHICLASS TDBXInt64Column;
class DELPHICLASS TDBXInt32Column;
class DELPHICLASS TDBXInt16Column;
class DELPHICLASS TDBXDoubleColumn;
class DELPHICLASS TDBXDecimalColumn;
class DELPHICLASS TDBXDateColumn;
class DELPHICLASS TDBXBooleanColumn;
class DELPHICLASS TDBXBinaryLongColumn;
class DELPHICLASS TDBXBinaryColumn;
class DELPHICLASS TDBXAnsiVarCharColumn;
class DELPHICLASS TDBXAnsiLongColumn;
class DELPHICLASS TDBXAnsiCharColumn;
class DELPHICLASS TDBXMetaDataForeignKey;
class DELPHICLASS TDBXMetaDataIndex;
class DELPHICLASS TDBXMetaDataProvider;
class DELPHICLASS TDBXMetaDataTable;
class DELPHICLASS TDBXObjectColumn;
class DELPHICLASS TDBXProductNames;
class DELPHICLASS TDBXSingleColumn;
class DELPHICLASS TDBXSqlExecution;
class DELPHICLASS TDBXTimeColumn;
class DELPHICLASS TDBXTimestampColumn;
class DELPHICLASS TDBXUInt16Column;
class DELPHICLASS TDBXUInt32Column;
class DELPHICLASS TDBXUInt64Column;
class DELPHICLASS TDBXUInt8Column;
class DELPHICLASS TDBXUnicodeCharColumn;
class DELPHICLASS TDBXUnicodeLongColumn;
class DELPHICLASS TDBXUnicodeVarCharColumn;
class DELPHICLASS TDBXVarBinaryColumn;
class DELPHICLASS TDBXWideVarCharColumn;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<TDBXMetaDataColumn*> TDBXMetaDataColumnArray;

class PASCALIMPLEMENTATION TDBXMetaDataColumn : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FColumnIndex;
	System::UnicodeString FColumnName;
	System::UnicodeString FDefaultValue;
	int FDataType;
	__int64 FPrecision;
	int FScale;
	int FMaxInline;
	bool FUnsigned;
	bool FAutoIncrement;
	bool FNullable;
	bool FFixedLength;
	bool FUnicodeString;
	bool FBlob;
	Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* FColumnStorage;
	System::UnicodeString FTypeName;
	void __fastcall SetAutoIncrement(const bool Value);
	void __fastcall SetBlob(const bool Value);
	void __fastcall SetColumnName(const System::UnicodeString Value);
	void __fastcall SetDefaultValue(const System::UnicodeString Value);
	void __fastcall SetFixedLength(const bool Value);
	void __fastcall SetMaxInline(const int Value);
	void __fastcall SetNullable(const bool Value);
	void __fastcall SetDataType(const int Value);
	void __fastcall SetPrecision(const __int64 Value);
	void __fastcall SetScale(const int Value);
	void __fastcall SetUnicodeString(const bool Value);
	void __fastcall SetUnsigned(const bool Value);
	void __fastcall SetTypeName(const System::UnicodeString Value);
	
public:
	__fastcall TDBXMetaDataColumn()/* overload */;
	__fastcall TDBXMetaDataColumn(TDBXMetaDataColumn* const Column)/* overload */;
	void __fastcall CopyColumnPropertyToTableStorage(const int AColumnIndex, const System::Variant &ANewValue);
	void __fastcall CopyColumnToTableStorage(Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* const Columns);
	__property System::UnicodeString TypeName = {read=FTypeName, write=SetTypeName};
	__property bool AutoIncrement = {read=FAutoIncrement, write=SetAutoIncrement, nodefault};
	__property System::UnicodeString ColumnName = {read=FColumnName, write=SetColumnName};
	__property System::UnicodeString DefaultValue = {read=FDefaultValue, write=SetDefaultValue};
	__property bool FixedLength = {read=FFixedLength, write=SetFixedLength, nodefault};
	__property int MaxInline = {read=FMaxInline, write=SetMaxInline, nodefault};
	__property bool Nullable = {read=FNullable, write=SetNullable, nodefault};
	__property bool Long = {read=FBlob, write=SetBlob, nodefault};
	__property __int64 Precision = {read=FPrecision, write=SetPrecision};
	__property int Scale = {read=FScale, write=SetScale, nodefault};
	__property int DataType = {read=FDataType, write=SetDataType, nodefault};
	__property bool UnicodeString = {read=FUnicodeString, write=SetUnicodeString, nodefault};
	__property bool Unsigned = {read=FUnsigned, write=SetUnsigned, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXInt8Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXInt8Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXInt8Column() { }
	
};


class PASCALIMPLEMENTATION TDBXInt64Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXInt64Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXInt64Column() { }
	
};


class PASCALIMPLEMENTATION TDBXInt32Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXInt32Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXInt32Column() { }
	
};


class PASCALIMPLEMENTATION TDBXInt16Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXInt16Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXInt16Column() { }
	
};


class PASCALIMPLEMENTATION TDBXDoubleColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXDoubleColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDoubleColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXDecimalColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXDecimalColumn(const System::UnicodeString InName, const int InPrecision, const int InScale);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDecimalColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXDateColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXDateColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDateColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXBooleanColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXBooleanColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXBooleanColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXBinaryLongColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXBinaryLongColumn(const System::UnicodeString Name);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXBinaryLongColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXBinaryColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXBinaryColumn(const System::UnicodeString InName, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXBinaryColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXAnsiVarCharColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXAnsiVarCharColumn(const System::UnicodeString Name, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXAnsiVarCharColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXAnsiLongColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXAnsiLongColumn(const System::UnicodeString Name);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXAnsiLongColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXAnsiCharColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXAnsiCharColumn(const System::UnicodeString Name, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXAnsiCharColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXMetaDataForeignKey : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxtypedtablestorage::TDBXForeignKeysTableStorage* FForeignkey;
	Data::Dbxtypedtablestorage::TDBXForeignKeyColumnsTableStorage* FColumns;
	System::UnicodeString FPrimaryCatalogName;
	System::UnicodeString FPrimarySchemaName;
	System::UnicodeString FPrimaryTableName;
	int FColumnCount;
	
protected:
	Data::Dbxtypedtablestorage::TDBXForeignKeyColumnsTableStorage* __fastcall GetForeignKeyColumnsStorage();
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString CatalogName);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString SchemaName);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString TableName);
	System::UnicodeString __fastcall GetForeignKeyName();
	void __fastcall SetForeignKeyName(const System::UnicodeString ForeignKeyName);
	
public:
	__fastcall TDBXMetaDataForeignKey()/* overload */;
	__fastcall virtual ~TDBXMetaDataForeignKey();
	__fastcall TDBXMetaDataForeignKey(const System::UnicodeString InForeignTableName, const System::UnicodeString InPrimaryTableName, const System::UnicodeString InForeignKeyName, System::UnicodeString *References, const int References_High)/* overload */;
	void __fastcall AddReference(const System::UnicodeString ColumnName, const System::UnicodeString ColumnNameInPrimaryTable);
	__property Data::Dbxtypedtablestorage::TDBXForeignKeysTableStorage* ForeignKeysStorage = {read=FForeignkey};
	__property Data::Dbxtypedtablestorage::TDBXForeignKeyColumnsTableStorage* ForeignKeyColumnsStorage = {read=GetForeignKeyColumnsStorage};
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString ForeignKeyName = {read=GetForeignKeyName, write=SetForeignKeyName};
	__property System::UnicodeString PrimaryCatalogName = {read=FPrimaryCatalogName, write=FPrimaryCatalogName};
	__property System::UnicodeString PrimarySchemaName = {read=FPrimarySchemaName, write=FPrimarySchemaName};
	__property System::UnicodeString PrimaryTableName = {read=FPrimaryTableName, write=FPrimaryTableName};
};


class PASCALIMPLEMENTATION TDBXMetaDataIndex : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxtypedtablestorage::TDBXIndexesTableStorage* FIndexes;
	Data::Dbxtypedtablestorage::TDBXIndexColumnsTableStorage* FColumns;
	int FColumnCount;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString CatalogName);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString SchemaName);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString TableName);
	System::UnicodeString __fastcall GetIndexName();
	void __fastcall SetIndexName(const System::UnicodeString IndexName);
	bool __fastcall IsUnique();
	void __fastcall SetUnique(const bool Unique);
	
public:
	__fastcall TDBXMetaDataIndex()/* overload */;
	__fastcall virtual ~TDBXMetaDataIndex();
	__fastcall TDBXMetaDataIndex(const System::UnicodeString InTableName, const System::UnicodeString InIndexName, System::UnicodeString *Columns, const int Columns_High)/* overload */;
	void __fastcall AddColumn(const System::UnicodeString ColumnName)/* overload */;
	void __fastcall AddColumn(const System::UnicodeString ColumnName, const bool Ascending)/* overload */;
	__property Data::Dbxtypedtablestorage::TDBXIndexesTableStorage* IndexesStorage = {read=FIndexes};
	__property Data::Dbxtypedtablestorage::TDBXIndexColumnsTableStorage* IndexColumnsStorage = {read=FColumns};
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString IndexName = {read=GetIndexName, write=SetIndexName};
	__property bool Unique = {read=IsUnique, write=SetUnique, nodefault};
};


class PASCALIMPLEMENTATION TDBXMetaDataProvider : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxmetadatawriter::TDBXMetaDataWriter* FWriter;
	TDBXSqlExecution* FExecuter;
	
protected:
	virtual void __fastcall SetWriter(Data::Dbxmetadatawriter::TDBXMetaDataWriter* const Writer);
	virtual Data::Dbxmetadatawriter::TDBXMetaDataWriter* __fastcall GetWriter();
	System::UnicodeString __fastcall GetVendor();
	System::UnicodeString __fastcall GetDatabaseProduct();
	System::UnicodeString __fastcall GetDatabaseVersion();
	System::UnicodeString __fastcall GetIdentifierQuotePrefix();
	System::UnicodeString __fastcall GetIdentifierQuoteSuffix();
	
public:
	__fastcall TDBXMetaDataProvider();
	__fastcall virtual ~TDBXMetaDataProvider();
	void __fastcall AlterTable(TDBXMetaDataTable* const Table);
	bool __fastcall CheckColumnSupported(TDBXMetaDataColumn* const Column);
	void __fastcall Execute(const System::UnicodeString Sql);
	void __fastcall CreateTable(TDBXMetaDataTable* const Table);
	void __fastcall CreateTableWithIndex(TDBXMetaDataTable* const Table, TDBXMetaDataIndex* const Index);
	bool __fastcall DropTable(const System::UnicodeString SchemaName, const System::UnicodeString TableName)/* overload */;
	bool __fastcall DropTable(const System::UnicodeString TableName)/* overload */;
	void __fastcall CreatePrimaryKey(TDBXMetaDataIndex* const Index);
	void __fastcall CreateUniqueIndex(TDBXMetaDataIndex* const Index);
	void __fastcall CreateIndex(TDBXMetaDataIndex* const Index);
	bool __fastcall DropIndex(const System::UnicodeString TableName, const System::UnicodeString IndexName)/* overload */;
	bool __fastcall DropIndex(const System::UnicodeString SchemaName, const System::UnicodeString TableName, const System::UnicodeString IndexName)/* overload */;
	void __fastcall CreateForeignKey(TDBXMetaDataForeignKey* const Foreignkey);
	bool __fastcall DropForeignKey(const System::UnicodeString TableName, const System::UnicodeString ForeignKey)/* overload */;
	bool __fastcall DropForeignKey(const System::UnicodeString SchemaName, const System::UnicodeString TableName, const System::UnicodeString ForeignKey)/* overload */;
	System::UnicodeString __fastcall QuoteIdentifierIfNeeded(const System::UnicodeString Identifier);
	Data::Dbxcommontable::TDBXTable* __fastcall GetCollection(const System::UnicodeString MetaDataCommand);
	void __fastcall ToMemoryStorage(Data::Dbxcommontable::TDBXDelegateTable* const Table);
	System::UnicodeString __fastcall MakeCreateTableSql(Data::Dbxtypedtablestorage::TDBXTablesTableStorage* const Table, Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* const Columns);
	System::UnicodeString __fastcall MakeCreateTableSqlWithIndex(Data::Dbxtypedtablestorage::TDBXTablesTableStorage* const Table, Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* const Columns, Data::Dbxtypedtablestorage::TDBXIndexesTableStorage* const Indexes, Data::Dbxtypedtablestorage::TDBXIndexColumnsTableStorage* const IndexColumns);
	System::UnicodeString __fastcall MakeAlterTableSql(Data::Dbxtypedtablestorage::TDBXTablesTableStorage* const Table, Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* const Columns)/* overload */;
	System::UnicodeString __fastcall MakeDropTableSql(Data::Dbxtypedtablestorage::TDBXTablesTableStorage* const Table);
	System::UnicodeString __fastcall MakeCreateIndexSql(Data::Dbxtypedtablestorage::TDBXIndexesTableStorage* const Indexes, Data::Dbxtypedtablestorage::TDBXIndexColumnsTableStorage* const Columns);
	System::UnicodeString __fastcall MakeDropIndexSql(Data::Dbxtypedtablestorage::TDBXIndexesTableStorage* const Indexes);
	System::UnicodeString __fastcall MakeCreateForeignKeySql(Data::Dbxtypedtablestorage::TDBXForeignKeysTableStorage* const ForeignKeys, Data::Dbxtypedtablestorage::TDBXForeignKeyColumnsTableStorage* const Columns);
	System::UnicodeString __fastcall MakeDropForeignKeySql(Data::Dbxtypedtablestorage::TDBXForeignKeysTableStorage* const ForeignKey);
	System::UnicodeString __fastcall MakeAlterTableSql(Data::Dbxtypedtablestorage::TDBXIndexesTableStorage* const Indexes, Data::Dbxtypedtablestorage::TDBXIndexColumnsTableStorage* const Columns)/* overload */;
	bool __fastcall IsCatalogsSupported();
	bool __fastcall IsSchemasSupported();
	bool __fastcall IsMultipleStatementsSupported();
	bool __fastcall IsDescendingIndexSupported();
	bool __fastcall IsDescendingIndexColumnsSupported();
	bool __fastcall IsMixedDDLAndDMLSupported();
	bool __fastcall IsDDLTransactionsSupported();
	__property System::UnicodeString Vendor = {read=GetVendor};
	__property System::UnicodeString DatabaseProduct = {read=GetDatabaseProduct};
	__property System::UnicodeString DatabaseVersion = {read=GetDatabaseVersion};
	__property System::UnicodeString IdentifierQuotePrefix = {read=GetIdentifierQuotePrefix};
	__property System::UnicodeString IdentifierQuoteSuffix = {read=GetIdentifierQuoteSuffix};
	__property Data::Dbxmetadatawriter::TDBXMetaDataWriter* Writer = {read=GetWriter};
};


class PASCALIMPLEMENTATION TDBXMetaDataTable : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxtypedtablestorage::TDBXTablesTableStorage* FTable;
	Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* FColumns;
	int FColumnCount;
	System::Generics::Collections::TObjectList__1<TDBXMetaDataColumn*>* FMetaDataColumns;
	void __fastcall UpdateColumnOrdinals();
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString CatalogName);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString SchemaName);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString TableName);
	
public:
	__fastcall TDBXMetaDataTable()/* overload */;
	__fastcall TDBXMetaDataTable(Data::Dbxcommon::TDBXReader* const AReader)/* overload */;
	__fastcall virtual ~TDBXMetaDataTable();
	void __fastcall AddColumn(TDBXMetaDataColumn* const Column);
	void __fastcall InsertColumn(TDBXMetaDataColumn* const Column, const int Ordinal);
	void __fastcall RemoveColumn(TDBXMetaDataColumn* const Column);
	TDBXMetaDataColumn* __fastcall GetColumn(const int Ordinal);
	__property Data::Dbxtypedtablestorage::TDBXTablesTableStorage* TableStorage = {read=FTable};
	__property Data::Dbxtypedtablestorage::TDBXColumnsTableStorage* ColumnsStorage = {read=FColumns};
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
};


class PASCALIMPLEMENTATION TDBXObjectColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXObjectColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXObjectColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXProductNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProductNames_DatasnapProduct u"Datasnap"
	
	#define TDBXProductNames_Db2_Product u"Db2"
	
	#define TDBXProductNames_FirebirdProduct u"Firebird"
	
	#define TDBXProductNames_InformixProduct u"Informix Dynamic Server"
	
	#define TDBXProductNames_InterbaseProduct u"InterBase"
	
	#define TDBXProductNames_MsSqlProduct u"Microsoft SQL Server"
	
	#define TDBXProductNames_MySqlProduct u"MySQL"
	
	#define TDBXProductNames_OdbcProduct u"Odbc"
	
	#define TDBXProductNames_OracleProduct u"Oracle"
	
	#define TDBXProductNames_SqliteProduct u"Sqlite"
	
	#define TDBXProductNames_SybaseAsaProduct u"Adaptive Server Anywhere"
	
	#define TDBXProductNames_SybaseAseProduct u"Sybase SQL Server"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProductNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProductNames() { }
	
};


class PASCALIMPLEMENTATION TDBXSingleColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXSingleColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSingleColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXSqlExecution : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxmetadatareader::TDBXProviderContext* FContext;
	
public:
	__fastcall TDBXSqlExecution(Data::Dbxmetadatawriter::TDBXMetaDataWriter* const Writer);
	virtual void __fastcall Execute(const System::UnicodeString Sql);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSqlExecution() { }
	
};


class PASCALIMPLEMENTATION TDBXTimeColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXTimeColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTimeColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXTimestampColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXTimestampColumn(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTimestampColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXUInt16Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUInt16Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUInt16Column() { }
	
};


class PASCALIMPLEMENTATION TDBXUInt32Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUInt32Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUInt32Column() { }
	
};


class PASCALIMPLEMENTATION TDBXUInt64Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUInt64Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUInt64Column() { }
	
};


class PASCALIMPLEMENTATION TDBXUInt8Column : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUInt8Column(const System::UnicodeString InName);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUInt8Column() { }
	
};


class PASCALIMPLEMENTATION TDBXUnicodeCharColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUnicodeCharColumn(const System::UnicodeString Name, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUnicodeCharColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXUnicodeLongColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUnicodeLongColumn(const System::UnicodeString Name);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUnicodeLongColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXUnicodeVarCharColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXUnicodeVarCharColumn(const System::UnicodeString InName, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUnicodeVarCharColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXVarBinaryColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXVarBinaryColumn(const System::UnicodeString InName, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXVarBinaryColumn() { }
	
};


class PASCALIMPLEMENTATION TDBXWideVarCharColumn : public TDBXMetaDataColumn
{
	typedef TDBXMetaDataColumn inherited;
	
public:
	__fastcall TDBXWideVarCharColumn(const System::UnicodeString Name, const int InPrecision);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXWideVarCharColumn() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadataprovider */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATAPROVIDER)
using namespace Data::Dbxmetadataprovider;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadataproviderHPP
