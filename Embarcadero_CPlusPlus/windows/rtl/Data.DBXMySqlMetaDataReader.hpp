// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMySqlMetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmysqlmetadatareaderHPP
#define Data_DbxmysqlmetadatareaderHPP

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
#include <Data.DBXSqlScanner.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmysqlmetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMySqlCustomMetaDataReader;
class DELPHICLASS TDBXMySqlMetaDataReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMySqlCustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
	
public:
	class DELPHICLASS TMySqlColumnType;
	class PASCALIMPLEMENTATION TMySqlColumnType : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		System::UnicodeString FDataType;
		int FPrecision;
		int FScale;
		bool FUnsigned;
		bool FUnicode;
		bool FNotnull;
	public:
		/* TObject.Create */ inline __fastcall TMySqlColumnType() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TMySqlColumnType() { }
		
	};
	
	
	class DELPHICLASS TMySqlParameter;
	class PASCALIMPLEMENTATION TMySqlParameter : public TDBXMySqlCustomMetaDataReader::TMySqlColumnType
	{
		typedef TDBXMySqlCustomMetaDataReader::TMySqlColumnType inherited;
		
	public:
		System::UnicodeString FName;
		System::UnicodeString FMode;
		int FOrdinal;
	public:
		/* TObject.Create */ inline __fastcall TMySqlParameter() : TDBXMySqlCustomMetaDataReader::TMySqlColumnType() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TMySqlParameter() { }
		
	};
	
	
	class DELPHICLASS TMySqlForeignKey;
	class PASCALIMPLEMENTATION TMySqlForeignKey : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		__fastcall TMySqlForeignKey();
		__fastcall virtual ~TMySqlForeignKey();
		virtual void __fastcall Reset();
		System::UnicodeString FConstraintName;
		System::Classes::TStringList* FKeyColumns;
		System::UnicodeString FReferencedTableName;
		System::Classes::TStringList* FReferencedColumns;
	};
	
	
	class DELPHICLASS TDBXMySql4TablesCursor;
	class PASCALIMPLEMENTATION TDBXMySql4TablesCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySql4TablesCursor();
		
	protected:
		__fastcall TDBXMySql4TablesCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	public:
		Data::Dbxcommon::TDBXWritableValue* FTableValue;
		Data::Dbxcommon::TDBXWritableValue* FNullValue;
		
	private:
		static const System::Int8 ShowTablesTableNameOrdinal = System::Int8(0x0);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySqlColumnsTableCursor;
	class PASCALIMPLEMENTATION TDBXMySqlColumnsTableCursor : public Data::Dbxmetadatareader::TDBXColumnsTableCursor
	{
		typedef Data::Dbxmetadatareader::TDBXColumnsTableCursor inherited;
		
	public:
		__fastcall TDBXMySqlColumnsTableCursor(TDBXMySqlCustomMetaDataReader* const Reader, const bool Version5, Data::Dbxcommontable::TDBXTable* const Original, Data::Dbxcommontable::TDBXTable* const Sanitized);
		__fastcall virtual ~TDBXMySqlColumnsTableCursor();
		virtual bool __fastcall Next();
		
	protected:
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	public:
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		
	private:
		Data::Dbxcommontable::TDBXTable* FOriginal;
		bool FVersion5;
		static const System::Int8 MysqlIsUnicode = System::Int8(0xc);
		
		static const System::Int8 MysqlIsUnsigned = System::Int8(0xd);
		
	};
	
	
	class DELPHICLASS TDBXMySql4ColumnsCursor;
	class PASCALIMPLEMENTATION TDBXMySql4ColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySql4ColumnsCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySql4ColumnsCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString TableName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		System::UnicodeString __fastcall ComputeDefaultValue();
		bool __fastcall ComputeAutoIncrement();
		bool __fastcall ComputeNullable();
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FTables;
		int FTableIndex;
		System::UnicodeString FSql;
		System::UnicodeString FTableName;
		int FColumnNumber;
		TDBXMySqlCustomMetaDataReader::TMySqlColumnType* FColumnType;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ShowColumnsFieldOrdinal = System::Int8(0x0);
		
		static const System::Int8 ShowColumnsTypeOrdinal = System::Int8(0x1);
		
		static const System::Int8 ShowColumnsNullOrdinal = System::Int8(0x2);
		
		static const System::Int8 ShowColumnsKeyOrdinal = System::Int8(0x3);
		
		static const System::Int8 ShowColumnsDefaultOrdinal = System::Int8(0x4);
		
		static const System::Int8 ShowColumnsExtraOrdinal = System::Int8(0x5);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySql4IndexesCursor;
	class PASCALIMPLEMENTATION TDBXMySql4IndexesCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySql4IndexesCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySql4IndexesCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString TableName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		System::UnicodeString __fastcall ComputeConstraintName();
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FTables;
		int FTableIndex;
		System::UnicodeString FSql;
		System::UnicodeString FTableName;
		bool FUniqueIndex;
		System::UnicodeString FIndexName;
		System::UnicodeString FPrevIndexName;
		System::UnicodeString FPrevTableName;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ShowIndexTableOrdinal = System::Int8(0x0);
		
		static const System::Int8 ShowIndexNonUniqueOrdinal = System::Int8(0x1);
		
		static const System::Int8 ShowIndexKeyNameOrdinal = System::Int8(0x2);
		
		static const System::Int8 ShowIndexSeqInIndexOrdinal = System::Int8(0x3);
		
		static const System::Int8 ShowIndexColumnNameOrdinal = System::Int8(0x4);
		
		static const System::Int8 ShowIndexCollationOrdinal = System::Int8(0x5);
		
		static const System::Int8 ShowIndexCardinalityOrdinal = System::Int8(0x6);
		
		static const System::Int8 ShowIndexSubPartOrdinal = System::Int8(0x7);
		
		static const System::Int8 ShowIndexPackedOrdinal = System::Int8(0x8);
		
		static const System::Int8 ShowIndexNullOrdinal = System::Int8(0x9);
		
		static const System::Int8 ShowIndexIndexTypeOrdinal = System::Int8(0xa);
		
		static const System::Int8 ShowIndexCommentOrdinal = System::Int8(0xb);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySql4IndexColumnsCursor;
	class PASCALIMPLEMENTATION TDBXMySql4IndexColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySql4IndexColumnsCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySql4IndexColumnsCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString TableName, const System::UnicodeString IndexName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FTables;
		int FTableIndex;
		System::UnicodeString FSql;
		System::UnicodeString FWantedIndexName;
		System::UnicodeString FTableName;
		System::UnicodeString FIndexName;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ShowIndexTableOrdinal = System::Int8(0x0);
		
		static const System::Int8 ShowIndexNonUniqueOrdinal = System::Int8(0x1);
		
		static const System::Int8 ShowIndexKeyNameOrdinal = System::Int8(0x2);
		
		static const System::Int8 ShowIndexSeqInIndexOrdinal = System::Int8(0x3);
		
		static const System::Int8 ShowIndexColumnNameOrdinal = System::Int8(0x4);
		
		static const System::Int8 ShowIndexCollationOrdinal = System::Int8(0x5);
		
		static const System::Int8 ShowIndexCardinalityOrdinal = System::Int8(0x6);
		
		static const System::Int8 ShowIndexSubPartOrdinal = System::Int8(0x7);
		
		static const System::Int8 ShowIndexPackedOrdinal = System::Int8(0x8);
		
		static const System::Int8 ShowIndexNullOrdinal = System::Int8(0x9);
		
		static const System::Int8 ShowIndexIndexTypeOrdinal = System::Int8(0xa);
		
		static const System::Int8 ShowIndexCommentOrdinal = System::Int8(0xb);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySql4ForeignKeyCursor;
	class PASCALIMPLEMENTATION TDBXMySql4ForeignKeyCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySql4ForeignKeyCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySql4ForeignKeyCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString TableName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		
	public:
		TDBXMySqlCustomMetaDataReader::TMySqlForeignKey* FKey;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		
	private:
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FTables;
		int FTableIndex;
		System::UnicodeString FSql;
		System::UnicodeString FTableName;
		System::UnicodeString FSqlCreateTable;
		int FParseIndex;
		static const System::Int8 ShowCreateTableSqlOrdinal = System::Int8(0x1);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySql4ForeignKeyColumnsCursor;
	class PASCALIMPLEMENTATION TDBXMySql4ForeignKeyColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySql4ForeignKeyColumnsCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySql4ForeignKeyColumnsCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString TableName, const System::UnicodeString ForeignKeyName, const System::UnicodeString PrimaryTableName, const System::UnicodeString PrimaryKeyName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		HIDESBASE void __fastcall SetValues();
		
	public:
		TDBXMySqlCustomMetaDataReader::TMySqlForeignKey* FKey;
		
	private:
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FTables;
		int FTableIndex;
		System::UnicodeString FSql;
		System::UnicodeString FTableName;
		System::UnicodeString FForeignKeyName;
		System::UnicodeString FPrimaryTableName;
		System::UnicodeString FPrimaryKeyName;
		System::UnicodeString FSqlCreateTable;
		int FParseIndex;
		int FKeyIndex;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ShowCreateTableSqlOrdinal = System::Int8(0x1);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySqlProcedureSourcesCursor;
	class PASCALIMPLEMENTATION TDBXMySqlProcedureSourcesCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySqlProcedureSourcesCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySqlProcedureSourcesCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString SchemaName, const System::UnicodeString ProcedureName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		System::UnicodeString __fastcall ComputeDefinition();
		System::UnicodeString __fastcall ComputeDefiner();
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FProcedures;
		System::Classes::TStringList* FProcedureTypes;
		int FProcedureIndex;
		System::UnicodeString FSql;
		System::UnicodeString FProcedureName;
		System::UnicodeString FProcedureType;
		System::UnicodeString FDefiner;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ShowCreateProcedureSqlOrdinal = System::Int8(0x2);
		
		#define TDBXMySqlCustomMetaDataReader_TDBXMySqlProcedureSourcesCursor_DefinerString L"DEFINER="
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXMySqlProcedureParametersCursor;
	class PASCALIMPLEMENTATION TDBXMySqlProcedureParametersCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXMySqlProcedureParametersCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXMySqlProcedureParametersCursor(TDBXMySqlCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Sql, const System::UnicodeString SchemaName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		bool __fastcall InitNextCursor();
		HIDESBASE void __fastcall SetValues();
		void __fastcall ComputeParams();
		TDBXMySqlCustomMetaDataReader* FReader;
		System::Classes::TStringList* FProcedures;
		System::Classes::TStringList* FProcedureTypes;
		int FProcedureIndex;
		int FParameterIndex;
		System::UnicodeString FSql;
		System::UnicodeString FProcedureName;
		System::UnicodeString FParameterName;
		System::UnicodeString FProcedureType;
		System::UnicodeString FDefiner;
		Data::Dbxplatform::TDBXArrayList* FParams;
		TDBXMySqlCustomMetaDataReader::TMySqlParameter* FParameter;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ShowCreateProcedureSqlOrdinal = System::Int8(0x2);
		
		#define TDBXMySqlCustomMetaDataReader_TDBXMySqlProcedureParametersCursor_DefinerString L"DEFINER="
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	
public:
	__fastcall virtual ~TDBXMySqlCustomMetaDataReader();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSchemas(const System::UnicodeString Catalog);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchTables(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString TableName, const System::UnicodeString TableType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchViews(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString View);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexes(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString Index);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeys(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeyColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString ForeignKeyName, const System::UnicodeString PrimaryCatalog, const System::UnicodeString PrimarySchema, const System::UnicodeString PrimaryTable, const System::UnicodeString PrimaryKeyName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedures(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString ProcedureName, const System::UnicodeString ProcType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureSources(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc, const System::UnicodeString Parameter);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchUsers();
	
protected:
	virtual void __fastcall SetContext(Data::Dbxmetadatareader::TDBXProviderContext* const Context);
	virtual bool __fastcall IsDefaultCharSetUnicode();
	virtual void __fastcall PopulateDataTypes(Data::Dbxplatform::TDBXObjectStore* const Hash, Data::Dbxplatform::TDBXArrayList* const Types, const Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray Descr);
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	System::Classes::TStringList* __fastcall GetTables();
	virtual int __fastcall FindDataType(const System::UnicodeString TypeName);
	
private:
	HIDESBASE void __fastcall InitScanner();
	void __fastcall GetProcedures(const System::UnicodeString SchemaName, const System::UnicodeString ProcedureName, System::Classes::TStringList* const Procedures, System::Classes::TStringList* const ProcedureTypes);
	System::UnicodeString __fastcall ParseProcedureDefiner(const System::UnicodeString Definition);
	void __fastcall ParseProcedure(const System::UnicodeString Definition, const System::UnicodeString aType, Data::Dbxplatform::TDBXArrayList* const Params);
	int __fastcall ParseType(const System::UnicodeString Definition, TMySqlColumnType* const aType);
	System::UnicodeString __fastcall ReplaceIdentifier(const System::UnicodeString Sql, const System::UnicodeString ParameterName, const System::UnicodeString ActualValue, const bool MakeQuotes);
	int __fastcall ToInt(const System::UnicodeString Value);
	bool __fastcall ParseIdList(Data::Dbxsqlscanner::TDBXSqlScanner* const Scanner, System::Classes::TStringList* const List);
	bool __fastcall ParseForeignKey(Data::Dbxsqlscanner::TDBXSqlScanner* const Scanner, TMySqlForeignKey* const ForeignKey);
	int __fastcall ParseCreateTableForNextForeignKey(const System::UnicodeString Sql, const int InStartIndex, TMySqlForeignKey* const Key);
	
protected:
	Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
	
private:
	bool FDefaultCharSetIsUnicode;
	
public:
	__property bool DefaultCharSetUnicode = {read=IsDefaultCharSetUnicode, nodefault};
	
private:
	__property System::Classes::TStringList* Tables = {read=GetTables};
	#define TDBXMySqlCustomMetaDataReader_DefaultCharsetIsUnicode L"UnicodeEncoding"
	
	static const System::WideChar YForYes = (System::WideChar)(0x59);
	
	static const System::WideChar AForAscending = (System::WideChar)(0x41);
	
	#define TDBXMySqlCustomMetaDataReader_FAuto_increment L"auto_increment"
	
	#define TDBXMySqlCustomMetaDataReader_IntegerType L"integer"
	
	#define TDBXMySqlCustomMetaDataReader_IntType L"int"
	
	#define TDBXMySqlCustomMetaDataReader_DecimalType L"decimal"
	
	#define TDBXMySqlCustomMetaDataReader_DecType L"dec"
	
	#define TDBXMySqlCustomMetaDataReader_Table L"TABLE"
	
	#define TDBXMySqlCustomMetaDataReader_Constraint L"CONSTRAINT"
	
	#define TDBXMySqlCustomMetaDataReader_Foreign L"FOREIGN"
	
	#define TDBXMySqlCustomMetaDataReader_Key L"KEY"
	
	#define TDBXMySqlCustomMetaDataReader_References L"REFERENCES"
	
	static const System::WideChar Quote = (System::WideChar)(0x27);
	
	#define TDBXMySqlCustomMetaDataReader_FYear L"year"
	
	#define TDBXMySqlCustomMetaDataReader_CurrentTimestamp L"CURRENT_TIMESTAMP"
	
	#define TDBXMySqlCustomMetaDataReader_Primary L"PRIMARY"
	
	#define TDBXMySqlCustomMetaDataReader_Proc L"PROCEDURE"
	
	#define TDBXMySqlCustomMetaDataReader_cFunction L"FUNCTION"
	
	#define TDBXMySqlCustomMetaDataReader_cBegin L"BEGIN"
	
	#define TDBXMySqlCustomMetaDataReader_cCreate L"CREATE"
	
	#define TDBXMySqlCustomMetaDataReader_Definer L"DEFINER"
	
	#define TDBXMySqlCustomMetaDataReader_Returns L"RETURNS"
	
	#define TDBXMySqlCustomMetaDataReader_Character L"CHARACTER"
	
	#define TDBXMySqlCustomMetaDataReader_cSet L"SET"
	
	#define TDBXMySqlCustomMetaDataReader_Utf8 L"utf8"
	
	#define TDBXMySqlCustomMetaDataReader_cIn L"IN"
	
	#define TDBXMySqlCustomMetaDataReader_cOut L"OUT"
	
	#define TDBXMySqlCustomMetaDataReader_Inout L"INOUT"
	
	#define TDBXMySqlCustomMetaDataReader_Unsigned L"UNSIGNED"
	
	#define TDBXMySqlCustomMetaDataReader_cNot L"NOT"
	
	#define TDBXMySqlCustomMetaDataReader_NullSpec L"NULL"
	
	#define TDBXMySqlCustomMetaDataReader_Binary L"BINARY"
	
	#define TDBXMySqlCustomMetaDataReader_Varbinary L"VARBINARY"
	
	static const System::Byte DefaultVarcharPrecision = System::Byte(0x80);
	
	static const System::Int8 TokenProcedure = System::Int8(0x1);
	
	static const System::Int8 TokenFunction = System::Int8(0x2);
	
	static const System::Int8 TokenReturns = System::Int8(0x3);
	
	static const System::Int8 TokenBegin = System::Int8(0x4);
	
	static const System::Int8 TokenIn = System::Int8(0x5);
	
	static const System::Int8 TokenOut = System::Int8(0x6);
	
	static const System::Int8 TokenInout = System::Int8(0x7);
	
	static const System::Int8 TokenCharacter = System::Int8(0x8);
	
	static const System::Int8 TokenSet = System::Int8(0x9);
	
	static const System::Int8 TokenUtf8 = System::Int8(0xa);
	
	static const System::Int8 TokenUnsigned = System::Int8(0xb);
	
	static const System::Int8 TokenCreate = System::Int8(0xc);
	
	static const System::Int8 TokenDefiner = System::Int8(0xd);
	
	static const System::Int8 TokenNot = System::Int8(0xe);
	
	static const System::Int8 TokenNull = System::Int8(0xf);
	
	static const System::Int8 TokenBinary = System::Int8(0x10);
	
public:
	/* TObject.Create */ inline __fastcall TDBXMySqlCustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMySqlMetaDataReader : public TDBXMySqlCustomMetaDataReader
{
	typedef TDBXMySqlCustomMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSchemas(const System::UnicodeString CatalogName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSynonyms(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString SynonymName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchRoles();
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteChar();
	virtual System::UnicodeString __fastcall GetTableType();
	virtual bool __fastcall IsDescendingIndexColumnsSupported();
	virtual bool __fastcall IsLowerCaseIdentifiersSupported();
	virtual bool __fastcall IsUpperCaseIdentifiersSupported();
	virtual bool __fastcall IsMultipleCommandsSupported();
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
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXMySqlCustomMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXMySqlMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXMySqlMetaDataReader() : TDBXMySqlCustomMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmysqlmetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMYSQLMETADATAREADER)
using namespace Data::Dbxmysqlmetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmysqlmetadatareaderHPP
