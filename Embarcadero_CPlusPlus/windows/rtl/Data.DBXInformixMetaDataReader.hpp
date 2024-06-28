// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXInformixMetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_DbxinformixmetadatareaderHPP
#define Data_DbxinformixmetadatareaderHPP

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
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxinformixmetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXInformixCustomMetaDataReader;
class DELPHICLASS TDBXInformixMetaDataReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXInformixCustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
	
public:
	class DELPHICLASS TDBXInformixColumnsCursor;
	class PASCALIMPLEMENTATION TDBXInformixColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXInformixColumnsCursor();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXInformixColumnsCursor(TDBXInformixCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		void __fastcall ReadTypeInformation();
		System::UnicodeString __fastcall ComputeTypeName();
		int __fastcall ComputePrecision();
		bool __fastcall HasScale();
		int __fastcall ComputeScale();
		bool __fastcall ComputeNullable();
		bool __fastcall ComputeAutoIncrement();
		System::UnicodeString __fastcall ComputeDefaultValue();
		System::UnicodeString __fastcall ComputeTypeQualifier();
		System::UnicodeString __fastcall GetQualifier(const int FieldQualifier);
		System::UnicodeString __fastcall ComputeLiteralValue();
		TDBXInformixCustomMetaDataReader* FReader;
		short FColType;
		short FColLength;
		System::UnicodeString FDefaultType;
		System::UnicodeString FDefaultValue;
		System::UnicodeString FExtendedName;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 ColumnsCatalogName = System::Int8(0x0);
		
		static const System::Int8 ColumnsSchemaName = System::Int8(0x1);
		
		static const System::Int8 ColumnsTableName = System::Int8(0x2);
		
		static const System::Int8 ColumnsColumnName = System::Int8(0x3);
		
		static const System::Int8 ColumnsColtype = System::Int8(0x4);
		
		static const System::Int8 ColumnsXname = System::Int8(0x5);
		
		static const System::Int8 ColumnsCollength = System::Int8(0x6);
		
		static const System::Int8 ColumnsOrdinal = System::Int8(0x7);
		
		static const System::Int8 ColumnsDefaultType = System::Int8(0x8);
		
		static const System::Int8 ColumnsDefaultValue = System::Int8(0x9);
		
	};
	
	
	class DELPHICLASS TDBXInformixIndexColumnsCursor;
	class PASCALIMPLEMENTATION TDBXInformixIndexColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXInformixIndexColumnsCursor();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXInformixIndexColumnsCursor(TDBXInformixCustomMetaDataReader* const Provider, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		int __fastcall IndexOfColumnName(const int KeyIndex);
		int FKeyIndex;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 KeyCount = System::Int8(0x10);
		
		static const System::Word DefaultColumnSize = System::Word(0x100);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TDBXInformixForeignKeyColumnsCursor;
	class PASCALIMPLEMENTATION TDBXInformixForeignKeyColumnsCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall virtual ~TDBXInformixForeignKeyColumnsCursor();
		virtual bool __fastcall Next();
		
	protected:
		__fastcall TDBXInformixForeignKeyColumnsCursor(TDBXInformixCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
		virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		int __fastcall IndexOfForeignKeyColumnName(const int KeyIndex);
		int __fastcall IndexOfPrimaryKeyColumnName(const int KeyIndex);
		
	public:
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		
	private:
		int FKeyIndex;
		static const System::Int8 KeyCount = System::Int8(0x10);
		
		static const System::Word DefaultColumnSize = System::Word(0x100);
		
	/* Hoisted overloads: */
		
	protected:
		inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
		
	};
	
	
	class DELPHICLASS TInformixParameter;
	class PASCALIMPLEMENTATION TInformixParameter : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		System::UnicodeString FName;
		System::UnicodeString FTypeName;
		System::UnicodeString FMode;
		Data::Dbxmetadatareader::TDBXDataTypeDescription* FDataType;
		int FOrdinal;
		int FPrecision;
		int FScale;
		bool FPrecisionParsed;
	public:
		/* TObject.Create */ inline __fastcall TInformixParameter() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TInformixParameter() { }
		
	};
	
	
	class DELPHICLASS TDBXInformixProcedureParametersCursor;
	class PASCALIMPLEMENTATION TDBXInformixProcedureParametersCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
	{
		typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
		
	public:
		__fastcall TDBXInformixProcedureParametersCursor(TDBXInformixCustomMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, const System::UnicodeString Parameter, Data::Dbxcommontable::TDBXTable* const Cursor);
		__fastcall virtual ~TDBXInformixProcedureParametersCursor();
		virtual void __fastcall Close();
		virtual bool __fastcall Next();
		
	protected:
		virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
		
	private:
		HIDESBASE void __fastcall SetValues();
		void __fastcall ComputeParams();
		TDBXInformixCustomMetaDataReader* FReader;
		System::UnicodeString FParameterName;
		int FParameterIndex;
		Data::Dbxplatform::TDBXArrayList* FParams;
		TDBXInformixCustomMetaDataReader::TInformixParameter* FParameter;
		Data::Dbxcommontable::TDBXTable* FCursor;
		System::Sysutils::TStringBuilder* FBuffer;
		bool FBeforeEnd;
		bool FBeforeFirst;
		System::UnicodeString FProcedureType;
		bool FIsCatalogNameNull;
		bool FIsSchemaNameNull;
		bool FIsProcedureNameNull;
		System::UnicodeString FCatalogName;
		System::UnicodeString FSchemaName;
		System::UnicodeString FProcedureName;
		Data::Dbxcommontable::TDBXSingleValueRow* FRow;
		static const System::Int8 LineNumberOrdinal = System::Int8(0x6);
		
	};
	
	
	
public:
	__fastcall virtual ~TDBXInformixCustomMetaDataReader();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString Index);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeyColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString ForeignKeyName, const System::UnicodeString PrimaryCatalog, const System::UnicodeString PrimarySchema, const System::UnicodeString PrimaryTable, const System::UnicodeString PrimaryKeyName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc, const System::UnicodeString Parameter);
	
protected:
	virtual void __fastcall SetContext(Data::Dbxmetadatareader::TDBXProviderContext* const Context);
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteChar();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetAllDataTypes();
	
private:
	HIDESBASE void __fastcall InitScanner();
	void __fastcall ParseProcedure(const System::UnicodeString Definition, const System::UnicodeString aType, Data::Dbxplatform::TDBXArrayList* const Params);
	int __fastcall ParseType(const int InToken, TInformixParameter* const Param);
	int __fastcall ParsePrecision(TInformixParameter* const Param);
	int __fastcall ToInt(const System::UnicodeString Value);
	
protected:
	Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
	
private:
	Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray FAlltypes;
	System::UnicodeString FQuoteChar;
	__property Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray AllDataTypes = {read=GetAllDataTypes};
	static const System::Int8 CharType = System::Int8(0x0);
	
	static const System::Int8 SmallintType = System::Int8(0x1);
	
	static const System::Int8 IntegerType = System::Int8(0x2);
	
	static const System::Int8 FloatType = System::Int8(0x3);
	
	static const System::Int8 SmallfloatType = System::Int8(0x4);
	
	static const System::Int8 DecimalType = System::Int8(0x5);
	
	static const System::Int8 SerialType = System::Int8(0x6);
	
	static const System::Int8 DateType = System::Int8(0x7);
	
	static const System::Int8 MoneyType = System::Int8(0x8);
	
	static const System::Int8 DatetimeType = System::Int8(0xa);
	
	static const System::Int8 ByteType = System::Int8(0xb);
	
	static const System::Int8 TextType = System::Int8(0xc);
	
	static const System::Int8 VarcharType = System::Int8(0xd);
	
	static const System::Int8 IntervalType = System::Int8(0xe);
	
	static const System::Int8 NcharType = System::Int8(0xf);
	
	static const System::Int8 NvarcharType = System::Int8(0x10);
	
	static const System::Int8 Int8_Type = System::Int8(0x11);
	
	static const System::Int8 Serial8_Type = System::Int8(0x12);
	
	static const System::Int8 LvarcharType = System::Int8(0x13);
	
	static const System::Int8 BooleanType = System::Int8(0x14);
	
	static const System::Int8 TypesCount = System::Int8(0x15);
	
	static const System::Int8 NullType = System::Int8(0x9);
	
	static const System::Int8 SetType = System::Int8(0x13);
	
	static const System::Int8 MultisetType = System::Int8(0x14);
	
	static const System::Int8 ListType = System::Int8(0x15);
	
	static const System::Int8 UnnamedRowType = System::Int8(0x16);
	
	static const System::Int8 VarOpaqueType = System::Int8(0x28);
	
	static const System::Int8 FixedOpaqueType = System::Int8(0x29);
	
	static const System::Word NullTypeFlag = System::Word(0x100);
	
	#define TDBXInformixCustomMetaDataReader_CharTypename L"CHAR"
	
	#define TDBXInformixCustomMetaDataReader_VarcharTypename L"VARCHAR"
	
	#define TDBXInformixCustomMetaDataReader_LvarcharTypename L"LVARCHAR"
	
	#define TDBXInformixCustomMetaDataReader_NcharTypename L"NCHAR"
	
	#define TDBXInformixCustomMetaDataReader_NvarcharTypename L"NVARCHAR"
	
	#define TDBXInformixCustomMetaDataReader_SmallintTypename L"SMALLINT"
	
	#define TDBXInformixCustomMetaDataReader_IntegerTypename L"INTEGER"
	
	#define TDBXInformixCustomMetaDataReader_Int8_Typename L"INT8"
	
	#define TDBXInformixCustomMetaDataReader_FloatTypename L"FLOAT"
	
	#define TDBXInformixCustomMetaDataReader_SmallfloatTypename L"SMALLFLOAT"
	
	#define TDBXInformixCustomMetaDataReader_DecimalTypename L"DECIMAL"
	
	#define TDBXInformixCustomMetaDataReader_SerialTypename L"SERIAL"
	
	#define TDBXInformixCustomMetaDataReader_Serial8_Typename L"SERIAL8"
	
	#define TDBXInformixCustomMetaDataReader_DateTypename L"DATE"
	
	#define TDBXInformixCustomMetaDataReader_DatetimeTypename L"DATETIME"
	
	#define TDBXInformixCustomMetaDataReader_IntervalTypename L"INTERVAL"
	
	#define TDBXInformixCustomMetaDataReader_MoneyTypename L"MONEY"
	
	#define TDBXInformixCustomMetaDataReader_ByteTypename L"BYTE"
	
	#define TDBXInformixCustomMetaDataReader_TextTypename L"TEXT"
	
	#define TDBXInformixCustomMetaDataReader_BooleanTypename L"BOOLEAN"
	
	#define TDBXInformixCustomMetaDataReader_Create L"CREATE"
	
	#define TDBXInformixCustomMetaDataReader_Returning L"RETURNING"
	
	#define TDBXInformixCustomMetaDataReader_cIn L"IN"
	
	#define TDBXInformixCustomMetaDataReader_cOut L"OUT"
	
	#define TDBXInformixCustomMetaDataReader_Inout L"INOUT"
	
	#define TDBXInformixCustomMetaDataReader_Like L"LIKE"
	
	#define TDBXInformixCustomMetaDataReader_References L"REFERENCES"
	
	#define TDBXInformixCustomMetaDataReader_IntType L"INT"
	
	#define TDBXInformixCustomMetaDataReader_DecType L"DEC"
	
	#define TDBXInformixCustomMetaDataReader_BigintType L"BIGINT"
	
	#define TDBXInformixCustomMetaDataReader_Character L"CHARACTER"
	
	#define TDBXInformixCustomMetaDataReader_Varying L"VARYING"
	
	#define TDBXInformixCustomMetaDataReader_RealType L"REAL"
	
	#define TDBXInformixCustomMetaDataReader_DoubleType L"DOUBLE"
	
	#define TDBXInformixCustomMetaDataReader_Precision L"PRECISION"
	
	#define TDBXInformixCustomMetaDataReader_Numeric L"NUMERIC"
	
	#define TDBXInformixCustomMetaDataReader_Default L"DEFAULT"
	
	#define TDBXInformixCustomMetaDataReader_QuoteCharacterEnabled L"QuoteCharEnabled"
	
	static const System::Int8 TokenCreate = System::Int8(0x33);
	
	static const System::Int8 TokenProcedure = System::Int8(0x34);
	
	static const System::Int8 TokenFunction = System::Int8(0x35);
	
	static const System::Int8 TokenReturning = System::Int8(0x36);
	
	static const System::Int8 TokenOut = System::Int8(0x37);
	
	static const System::Int8 TokenInout = System::Int8(0x38);
	
	static const System::Int8 TokenLike = System::Int8(0x39);
	
	static const System::Int8 TokenReferences = System::Int8(0x3a);
	
	static const System::Int8 TokenInt = System::Int8(0x3b);
	
	static const System::Int8 TokenDec = System::Int8(0x3c);
	
	static const System::Int8 TokenBigint = System::Int8(0x3d);
	
	static const System::Int8 TokenCharacter = System::Int8(0x3e);
	
	static const System::Int8 TokenVarying = System::Int8(0x3f);
	
	static const System::Int8 TokenReal = System::Int8(0x40);
	
	static const System::Int8 TokenDouble = System::Int8(0x41);
	
	static const System::Int8 TokenPrecision = System::Int8(0x42);
	
	static const System::Int8 TokenNumeric = System::Int8(0x43);
	
	static const System::Int8 TokenDefault = System::Int8(0x44);
	
public:
	/* TObject.Create */ inline __fastcall TDBXInformixCustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXInformixMetaDataReader : public TDBXInformixCustomMetaDataReader
{
	typedef TDBXInformixCustomMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
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
	virtual System::UnicodeString __fastcall GetSynonymType();
	virtual bool __fastcall IsLowerCaseIdentifiersSupported();
	virtual bool __fastcall IsUpperCaseIdentifiersSupported();
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
	virtual System::UnicodeString __fastcall GetSqlForUsers();
	virtual System::UnicodeString __fastcall GetSqlForRoles();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXInformixCustomMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXInformixMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXInformixMetaDataReader() : TDBXInformixCustomMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxinformixmetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXINFORMIXMETADATAREADER)
using namespace Data::Dbxinformixmetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxinformixmetadatareaderHPP
