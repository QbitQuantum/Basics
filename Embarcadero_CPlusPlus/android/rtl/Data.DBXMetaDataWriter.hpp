// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataWriter.pas' rev: 34.00 (Android)

#ifndef Data_DbxmetadatawriterHPP
#define Data_DbxmetadatawriterHPP

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
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXAlterTableOperation;
class DELPHICLASS TDBXMetaDataWriter;
class DELPHICLASS TDBXBaseMetaDataWriter;
class DELPHICLASS TDBXSQL;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXAlterTableOperation : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 NoSupport = System::Int8(0x0);
	
	static constexpr System::Int8 RenameTable = System::Int8(0x1);
	
	static constexpr System::Int8 RenameTableTo = System::Int8(0x2);
	
	static constexpr System::Int8 DropColumn = System::Int8(0x4);
	
	static constexpr System::Int8 AddColumn = System::Int8(0x8);
	
	static constexpr System::Int8 AddColumnWithPosition = System::Int8(0x10);
	
	static constexpr System::Int8 ChangeDefaultValue = System::Int8(0x20);
	
	static constexpr System::Int8 DropDefaultValue = System::Int8(0x40);
	
	static constexpr System::Byte SetNullable = System::Byte(0x80);
	
	static constexpr System::Word DropNullable = System::Word(0x100);
	
	static constexpr System::Word ChangeColumnType = System::Word(0x200);
	
	static constexpr System::Word AddAutoincrement = System::Word(0x400);
	
	static constexpr System::Word DropAutoincrement = System::Word(0x800);
	
	static constexpr System::Word ChangeColumnPosition = System::Word(0x1000);
	
	static constexpr System::Word RenameColumn = System::Word(0x2000);
	
	static constexpr System::Word FullAlterSupport = System::Word(0x3fff);
	
public:
	/* TObject.Create */ inline __fastcall TDBXAlterTableOperation() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXAlterTableOperation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataWriter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall Open() = 0 ;
	virtual void __fastcall MakeSqlCreate(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item, Data::Dbxcommontable::TDBXTable* const Parts) = 0 /* overload */;
	virtual void __fastcall MakeSqlCreate(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const TableItem, Data::Dbxcommontable::TDBXTable* const TableParts, Data::Dbxcommontable::TDBXTableRow* const ViewItem, Data::Dbxcommontable::TDBXTable* const ViewParts, Data::Dbxcommontable::TDBXTableRow* const SynonymItem, Data::Dbxcommontable::TDBXTable* const SynonymParts, Data::Dbxcommontable::TDBXTableRow* const IndexesItem, Data::Dbxcommontable::TDBXTable* const IndexesParts, Data::Dbxcommontable::TDBXTableRow* const ForeignKeysItem, Data::Dbxcommontable::TDBXTable* const ForeignKeysParts) = 0 /* overload */;
	virtual void __fastcall MakeSqlAlter(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item, Data::Dbxcommontable::TDBXTable* const Parts) = 0 ;
	virtual void __fastcall MakeSqlDrop(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item) = 0 ;
	virtual void __fastcall MakeSqlIdentifier(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString Identifier) = 0 ;
	virtual bool __fastcall CheckColumnSupported(Data::Dbxcommontable::TDBXTableRow* const Column) = 0 ;
	virtual System::UnicodeString __fastcall GetSqlQuotedIdentifier(const System::UnicodeString UnquotedIdentifier) = 0 ;
	virtual System::UnicodeString __fastcall GetSqlUnQuotedIdentifier(const System::UnicodeString QuotedIdentifier) = 0 ;
	
protected:
	virtual void __fastcall SetContext(Data::Dbxmetadatareader::TDBXProviderContext* const Context) = 0 ;
	virtual Data::Dbxmetadatareader::TDBXProviderContext* __fastcall GetContext() = 0 ;
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall GetMetaDataReader() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlRenameTable() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementInserts() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlKeyGeneratedIndexName() = 0 ;
	virtual int __fastcall GetAlterTableSupport() = 0 ;
	virtual bool __fastcall IsCatalogsSupported() = 0 ;
	virtual bool __fastcall IsSchemasSupported() = 0 ;
	virtual bool __fastcall IsMultipleStatementsSupported() = 0 ;
	virtual bool __fastcall IsIndexNamesGlobal() = 0 ;
	virtual bool __fastcall IsDescendingIndexConstraintsSupported() = 0 ;
	virtual bool __fastcall IsSerializedIsolationSupported() = 0 ;
	virtual bool __fastcall IsDDLTransactionsSupported() = 0 ;
	virtual bool __fastcall IsMixed_DDL_DML_Supported() = 0 ;
	
public:
	__property Data::Dbxmetadatareader::TDBXProviderContext* Context = {read=GetContext, write=SetContext};
	__property Data::Dbxmetadatareader::TDBXMetaDataReader* MetaDataReader = {read=GetMetaDataReader};
	__property System::UnicodeString SqlRenameTable = {read=GetSqlRenameTable};
	__property System::UnicodeString SqlAutoIncrementInserts = {read=GetSqlAutoIncrementInserts};
	__property System::UnicodeString SqlAutoIncrementKeyword = {read=GetSqlAutoIncrementKeyword};
	__property System::UnicodeString SqlKeyGeneratedIndexName = {read=GetSqlKeyGeneratedIndexName};
	__property int AlterTableSupport = {read=GetAlterTableSupport, nodefault};
	__property bool CatalogsSupported = {read=IsCatalogsSupported, nodefault};
	__property bool SchemasSupported = {read=IsSchemasSupported, nodefault};
	__property bool MultipleStatementsSupported = {read=IsMultipleStatementsSupported, nodefault};
	__property bool IndexNamesGlobal = {read=IsIndexNamesGlobal, nodefault};
	__property bool DescendingIndexConstraintsSupported = {read=IsDescendingIndexConstraintsSupported, nodefault};
	__property bool SerializedIsolationSupported = {read=IsSerializedIsolationSupported, nodefault};
	__property bool DDLTransactionsSupported = {read=IsDDLTransactionsSupported, nodefault};
	__property bool Mixed_DDL_DML_Supported = {read=IsMixed_DDL_DML_Supported, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataWriter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXBaseMetaDataWriter : public TDBXMetaDataWriter
{
	typedef TDBXMetaDataWriter inherited;
	
public:
	virtual void __fastcall Open();
	__fastcall virtual ~TDBXBaseMetaDataWriter();
	virtual void __fastcall MakeSqlCreate(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item, Data::Dbxcommontable::TDBXTable* const Parts)/* overload */;
	virtual void __fastcall MakeSqlCreate(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const TableItem, Data::Dbxcommontable::TDBXTable* const TableParts, Data::Dbxcommontable::TDBXTableRow* const ViewItem, Data::Dbxcommontable::TDBXTable* const ViewParts, Data::Dbxcommontable::TDBXTableRow* const SynonymItem, Data::Dbxcommontable::TDBXTable* const SynonymParts, Data::Dbxcommontable::TDBXTableRow* const IndexesItem, Data::Dbxcommontable::TDBXTable* const IndexesParts, Data::Dbxcommontable::TDBXTableRow* const ForeignKeysItem, Data::Dbxcommontable::TDBXTable* const ForeignKeysParts)/* overload */;
	virtual void __fastcall MakeSqlAlter(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item, Data::Dbxcommontable::TDBXTable* const Parts);
	virtual void __fastcall MakeSqlDrop(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item);
	virtual bool __fastcall CheckColumnSupported(Data::Dbxcommontable::TDBXTableRow* const Column);
	virtual System::UnicodeString __fastcall GetSqlQuotedIdentifier(const System::UnicodeString UnquotedIdentifier);
	virtual System::UnicodeString __fastcall GetSqlUnQuotedIdentifier(const System::UnicodeString QuotedIdentifier);
	virtual void __fastcall MakeSqlIdentifier(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString Identifier);
	
protected:
	virtual void __fastcall SetContext(Data::Dbxmetadatareader::TDBXProviderContext* const Context);
	virtual Data::Dbxmetadatareader::TDBXProviderContext* __fastcall GetContext();
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall GetMetaDataReader();
	virtual bool __fastcall IsCatalogsSupported();
	virtual bool __fastcall IsSchemasSupported();
	virtual bool __fastcall IsMultipleStatementsSupported();
	virtual bool __fastcall IsIndexNamesGlobal();
	virtual bool __fastcall IsDescendingIndexConstraintsSupported();
	virtual bool __fastcall IsSerializedIsolationSupported();
	virtual bool __fastcall IsDDLTransactionsSupported();
	virtual bool __fastcall IsMixed_DDL_DML_Supported();
	virtual int __fastcall GetAlterTableSupport();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
	virtual System::UnicodeString __fastcall GetSqlKeyGeneratedIndexName();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementInserts();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
	virtual void __fastcall MakeSqlObjectName(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString ObjectName);
	virtual void __fastcall MakeSqlNullable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Column);
	virtual void __fastcall MakeSqlDataType(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString TypeName, Data::Dbxcommontable::TDBXTableRow* const ColumnRow)/* overload */;
	virtual void __fastcall MakeSqlDataType(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxmetadatareader::TDBXDataTypeDescription* const DataType, Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides)/* overload */;
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescription* __fastcall FindDataType(const System::UnicodeString InTypeName, Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides);
	virtual System::UnicodeString __fastcall FindTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindSimpleColumnTypeMatch(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindBooleanTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindStringOrBinaryTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindIntegerTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindDecimalTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindFloatTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides, const bool FailIfNotFound);
	virtual System::UnicodeString __fastcall FindDateTimeTypeName(Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const bool FailIfNotFound);
	virtual void __fastcall MakeSqlColumnTypeCast(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTable* const Column);
	virtual bool __fastcall CanCreateIndexAsKey(Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	virtual void __fastcall MakeSqlCreateIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	virtual void __fastcall MakeSqlDropIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
	virtual void __fastcall MakeSqlCreateKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	void __fastcall MakeSqlConstraintName(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Constraint);
	virtual void __fastcall MakeSqlAlterTablePrefix(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item);
	virtual void __fastcall MakeSqlCreateIndexColumnList(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	virtual void __fastcall MakeSqlDropSecondaryIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
	void __fastcall MakeSqlForeignKeySyntax(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const ForeignKey, Data::Dbxcommontable::TDBXTable* const ForeignKeyColumns);
	virtual void __fastcall MakeSqlCreateForeignKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const ForeignKey, Data::Dbxcommontable::TDBXTable* const ForeignKeyColumns);
	virtual void __fastcall MakeSqlDropForeignKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const ForeignKey);
	
private:
	void __fastcall MakeSqlCreateTable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns);
	void __fastcall MakeSqlCreateTableWithIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	void __fastcall MakeSqlAlterTable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns);
	bool __fastcall SupportedTableAlteration(const int Operation);
	bool __fastcall MakeSqlFullAlterTable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns);
	bool __fastcall MakeSqlTableRename(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName, const System::UnicodeString OldCatalogName, const System::UnicodeString OldSchemaName, const System::UnicodeString OldTableName)/* overload */;
	bool __fastcall MakeSqlColumnRename(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString ColumnName, const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName, const System::UnicodeString OldColumnName);
	void __fastcall MakeSqlColumnDefinition(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Column);
	void __fastcall MakeSqlDefaultValue(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString DefaultValue, const System::UnicodeString TypeName);
	System::UnicodeString __fastcall RemoveMarkersForNullValues(const System::UnicodeString InFormat, const Data::Dbxplatform::TDBXStringArray Values);
	System::Sysutils::Exception* __fastcall ErrorTypeNameNotFound(Data::Dbxcommontable::TDBXTableRow* const ColumnRow);
	int __fastcall CalcPrecisionColumnType(const int ColumnType, const bool UnsignedOption);
	int __fastcall CalcDecimalPrecision(const int ColumnType);
	int __fastcall CalcBinaryPrecision(const int ColumnType);
	bool __fastcall IsSignedInteger(const int ColumnType);
	int __fastcall GetDefaultFloatPrecision(const int ColumnType);
	System::Sysutils::TStringBuilder* __fastcall AddToExternalStatements(System::Sysutils::TStringBuilder* const InExternalStatements, System::Sysutils::TStringBuilder* const Buffer, const int StartPosition);
	bool __fastcall IsValidSqlIdentifier(const System::UnicodeString Identifier);
	bool __fastcall IsReservedWord(const System::UnicodeString Identifier);
	bool __fastcall IsLetter(const System::WideChar Ch, const bool UpperOK, const bool LowerOK);
	bool __fastcall IsDigit(const System::WideChar Ch);
	void __fastcall MakeSqlTableReplacement(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns);
	Data::Dbxcommontable::TDBXTable* __fastcall CopyColumns(Data::Dbxcommontable::TDBXTable* const ColumnTable);
	Data::Dbxcommontable::TDBXTable* __fastcall CopyTable(Data::Dbxcommontable::TDBXTableRow* const Table, const System::UnicodeString TempTableName);
	Data::Dbxcommon::TDBXProperties* __fastcall ComputeColumnMap(Data::Dbxcommontable::TDBXTable* const Columns);
	Data::Dbxcommontable::TDBXTable* __fastcall GetDefaults(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	Data::Dbxcommontable::TDBXTable* __fastcall GetIndexes(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	Data::Dbxcommontable::TDBXTable* __fastcall GetIndexColumns(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	Data::Dbxcommontable::TDBXTable* __fastcall GetForeignKeyColumns(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	void __fastcall RemoveForeignKeyGeneratedIndexes(Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Indexes, Data::Dbxcommontable::TDBXTable* const IndexColumns, Data::Dbxcommontable::TDBXTable* const ForeignKeyColumns);
	void __fastcall DropAllConstraints(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTable* const Defaults, Data::Dbxcommontable::TDBXTable* const Indexes, Data::Dbxcommontable::TDBXTable* const ForeignKeys);
	void __fastcall CreateTempOutputTable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns, const System::UnicodeString TempTableName);
	void __fastcall SetIdentityInsert(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName, const bool bOn);
	bool __fastcall CheckForAutoIncrement(Data::Dbxcommontable::TDBXTable* const Columns);
	void __fastcall InsertValuesFromOldTable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Columns, const System::UnicodeString TempTableName);
	void __fastcall MakeSqlDropTable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table);
	void __fastcall ReplaceParameter(System::Sysutils::TStringBuilder* const Buffer, const int Start, const System::UnicodeString InParameter, const System::UnicodeString Replacement);
	void __fastcall MakeSqlTableRename(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName, const System::UnicodeString NewTableName)/* overload */;
	void __fastcall CopyRow(Data::Dbxcommontable::TDBXTableRow* const Source, Data::Dbxcommontable::TDBXTable* const Target, const int Columns);
	bool __fastcall Compare(Data::Dbxcommontable::TDBXTable* const Table, const int InStart, Data::Dbxcommontable::TDBXTableRow* const Row, const int InRowStart, const int Columns);
	bool __fastcall SameConstraint(Data::Dbxcommontable::TDBXTable* const Table, Data::Dbxcommontable::TDBXTableRow* const Row, const int Columns);
	void __fastcall MapTable(Data::Dbxcommontable::TDBXTable* const Item, Data::Dbxcommontable::TDBXTableRow* const Table);
	System::UnicodeString __fastcall MapColumn(Data::Dbxcommontable::TDBXTable* const Parts, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommon::TDBXProperties* const ColumnMap, const int ColIndex, const int IdColumns, const System::UnicodeString DroppedColumn);
	void __fastcall CreateConstraints(System::Sysutils::TStringBuilder* const Buffer, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Constraints, Data::Dbxcommontable::TDBXTable* const ConstraintColumns, const System::UnicodeString CollectionName, const int IdColumns, const int ItemColumns, const int PartColumns, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommon::TDBXProperties* const ColumnMap, const int ColIndex1, const int ColIndex2);
	void __fastcall CreateIndices(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const Indexes, Data::Dbxcommontable::TDBXTable* const IndexColumns, Data::Dbxcommon::TDBXProperties* const ColumnMap);
	void __fastcall CreateForeignKeys(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Table, Data::Dbxcommontable::TDBXTable* const ForeignKeyColumns, Data::Dbxcommon::TDBXProperties* const ColumnMap);
	void __fastcall MakeSqlCreateSecondaryIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	void __fastcall MakeSqlCreateConstraint(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Constraint);
	void __fastcall MakeSqlDropConstraint(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Constraint);
	void __fastcall MakeSqlCreateView(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const View, Data::Dbxcommontable::TDBXTable* const Columns);
	void __fastcall MakeSqlAlterView(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const View, Data::Dbxcommontable::TDBXTable* const Columns);
	void __fastcall MakeSqlDropView(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const View);
	void __fastcall MakeSqlCreateSynonym(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Synonym, Data::Dbxcommontable::TDBXTable* const Columns);
	void __fastcall MakeSqlAlterSynonym(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Synonym, Data::Dbxcommontable::TDBXTable* const Columns);
	void __fastcall MakeSqlDropSynonym(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Synonym);
	
protected:
	Data::Dbxmetadatareader::TDBXProviderContext* FContext;
	Data::Dbxmetadatareader::TDBXBaseMetaDataReader* FReader;
	Data::Dbxcommontable::TDBXTable* FReservedWords;
	
private:
	static constexpr System::Word Requirement = System::Word(0x3e8);
	
	static constexpr System::Int8 Desireable = System::Int8(0x64);
	
	static constexpr System::Int8 TieBreaker1 = System::Int8(0x1);
	
	static constexpr System::Int8 TieBreaker2 = System::Int8(0x2);
	
	static constexpr System::Int8 TieBreaker3 = System::Int8(0x4);
	
	static constexpr System::Int8 TieBreaker4 = System::Int8(0x8);
	
	static constexpr System::Int8 TieBreaker5 = System::Int8(0x10);
	
	static constexpr System::Int8 TieBreaker6 = System::Int8(0x20);
	
public:
	/* TObject.Create */ inline __fastcall TDBXBaseMetaDataWriter() : TDBXMetaDataWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXSQL : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXSQL_Add u"ADD"
	
	#define TDBXSQL_Alter u"ALTER"
	
	#define TDBXSQL_cAs u"AS"
	
	#define TDBXSQL_Binary u"BINARY"
	
	#define TDBXSQL_Cast u"CAST"
	
	#define TDBXSQL_Char u"CHAR"
	
	static constexpr System::WideChar CloseBrace = (System::WideChar)(0x7d);
	
	static constexpr System::WideChar CloseParen = (System::WideChar)(0x29);
	
	static constexpr System::WideChar Colon = (System::WideChar)(0x3a);
	
	#define TDBXSQL_Column u"COLUMN"
	
	static constexpr System::WideChar Comma = (System::WideChar)(0x2c);
	
	#define TDBXSQL_Constraint u"CONSTRAINT"
	
	#define TDBXSQL_Convert u"CONVERT"
	
	#define TDBXSQL_Create u"CREATE"
	
	#define TDBXSQL_CurrentTimestamp u"CURRENT_TIMESTAMP"
	
	#define TDBXSQL_Date u"DATE"
	
	#define TDBXSQL_Datetime u"DATETIME"
	
	#define TDBXSQL_Decimal u"DECIMAL"
	
	#define TDBXSQL_Default u"DEFAULT"
	
	#define TDBXSQL_Descending u"DESC"
	
	static constexpr System::WideChar Dot = (System::WideChar)(0x2e);
	
	static constexpr System::WideChar DoubleQuote = (System::WideChar)(0x22);
	
	#define TDBXSQL_Drop u"DROP"
	
	#define TDBXSQL_Empty u""
	
	#define TDBXSQL_cFor u"FOR"
	
	#define TDBXSQL_Foreign u"FOREIGN"
	
	#define TDBXSQL_From u"FROM"
	
	#define TDBXSQL_cFunction u"FUNCTION"
	
	#define TDBXSQL_Index u"INDEX"
	
	#define TDBXSQL_Insert u"INSERT"
	
	#define TDBXSQL_Into u"INTO"
	
	#define TDBXSQL_Key u"KEY"
	
	#define TDBXSQL_LineComment u"//"
	
	#define TDBXSQL_Makedate u"MAKEDATE"
	
	static constexpr System::WideChar Nl = (System::WideChar)(0xa);
	
	#define TDBXSQL_cNot u"NOT"
	
	#define TDBXSQL_Nullable u"NULL"
	
	#define TDBXSQL_Off u"OFF"
	
	#define TDBXSQL_cOn u"ON"
	
	static constexpr System::WideChar OpenBrace = (System::WideChar)(0x7b);
	
	static constexpr System::WideChar OpenParen = (System::WideChar)(0x28);
	
	#define TDBXSQL_Position u"POSITION"
	
	#define TDBXSQL_Primary u"PRIMARY"
	
	#define TDBXSQL_Proc u"PROCEDURE"
	
	static constexpr System::WideChar Quote = (System::WideChar)(0x27);
	
	#define TDBXSQL_References u"REFERENCES"
	
	#define TDBXSQL_Rename u"RENAME"
	
	#define TDBXSQL_Result u"RESULT"
	
	#define TDBXSQL_Returns u"RETURNS"
	
	#define TDBXSQL_Select u"SELECT"
	
	static constexpr System::WideChar Semicolon = (System::WideChar)(0x3b);
	
	#define TDBXSQL_cSet u"SET"
	
	#define TDBXSQL_Signed u"SIGNED"
	
	static constexpr System::WideChar Space = (System::WideChar)(0x20);
	
	#define TDBXSQL_Spacing u"  "
	
	#define TDBXSQL_Synonym u"SYNONYM"
	
	#define TDBXSQL_Table u"TABLE"
	
	#define TDBXSQL_Temp u"TEMP_"
	
	#define TDBXSQL_Time u"TIME"
	
	#define TDBXSQL_cTo u"TO"
	
	#define TDBXSQL_cType u"TYPE"
	
	#define TDBXSQL_FYear u"year"
	
	#define TDBXSQL_Unique u"UNIQUE"
	
	#define TDBXSQL_View u"VIEW"
	
public:
	/* TObject.Create */ inline __fastcall TDBXSQL() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSQL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATAWRITER)
using namespace Data::Dbxmetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatawriterHPP
