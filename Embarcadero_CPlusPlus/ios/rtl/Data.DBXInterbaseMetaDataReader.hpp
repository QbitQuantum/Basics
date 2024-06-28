// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXInterbaseMetaDataReader.pas' rev: 34.00 (iOS)

#ifndef Data_DbxinterbasemetadatareaderHPP
#define Data_DbxinterbasemetadatareaderHPP

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
namespace Dbxinterbasemetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXInterbaseCustomMetaDataReader;
class DELPHICLASS TDBXInterbaseMetaDataReader;
class DELPHICLASS TDBXInterbaseTypeFilterCursor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXInterbaseCustomMetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
public:
	__fastcall virtual ~TDBXInterbaseCustomMetaDataReader();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc, const System::UnicodeString Parameter);
	
protected:
	virtual void __fastcall SetContext(Data::Dbxmetadatareader::TDBXProviderContext* const Context);
	virtual bool __fastcall IsDefaultCharSetUnicode();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteChar();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetAllDataTypes();
	
public:
	bool FDefaultCharSetIsUnicode;
	
private:
	Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray FAlltypes;
	System::UnicodeString FQuoteChar;
	
public:
	__property bool DefaultCharSetUnicode = {read=IsDefaultCharSetUnicode, nodefault};
	__property Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray AllDataTypes = {read=GetAllDataTypes};
	static constexpr System::Int8 CharType = System::Int8(0x0);
	
	static constexpr System::Int8 VarcharType = System::Int8(0x1);
	
	static constexpr System::Int8 IntegerType = System::Int8(0x2);
	
	static constexpr System::Int8 SmallintType = System::Int8(0x3);
	
	static constexpr System::Int8 FloatType = System::Int8(0x4);
	
	static constexpr System::Int8 DoubleType = System::Int8(0x5);
	
	static constexpr System::Int8 NumericType = System::Int8(0x6);
	
	static constexpr System::Int8 DecimalType = System::Int8(0x7);
	
	static constexpr System::Int8 DateType = System::Int8(0x8);
	
	static constexpr System::Int8 TimeType = System::Int8(0x9);
	
	static constexpr System::Int8 TimestampType = System::Int8(0xa);
	
	static constexpr System::Int8 BlobType = System::Int8(0xb);
	
	static constexpr System::Int8 BooleanType = System::Int8(0xc);
	
	static constexpr System::Int8 DefaultCharset = System::Int8(0x0);
	
	static constexpr System::Int8 CharsetUnicodeFss = System::Int8(0x3);
	
	static constexpr System::Int8 CharsetSjis208 = System::Int8(0x5);
	
	static constexpr System::Int8 CharsetEucj208 = System::Int8(0x6);
	
	
private:
	static constexpr System::Int8 TypesCount = System::Int8(0xd);
	
	#define TDBXInterbaseCustomMetaDataReader_DefaultStringStart u"DEFAULT "
	
	#define TDBXInterbaseCustomMetaDataReader_DefaultCharsetIsUnicode u"UnicodeEncoding"
	
	#define TDBXInterbaseCustomMetaDataReader_QuoteCharacterEnabled u"QuoteCharEnabled"
	
	static constexpr System::Int8 ColumnsFieldType = System::Int8(0x4);
	
	static constexpr System::Int8 ColumnsSubtype = System::Int8(0xc);
	
	static constexpr System::Int8 ParametersFieldType = System::Int8(0x5);
	
	static constexpr System::Int8 ParametersSubtype = System::Int8(0xa);
	
public:
	/* TObject.Create */ inline __fastcall TDBXInterbaseCustomMetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};


class PASCALIMPLEMENTATION TDBXInterbaseMetaDataReader : public TDBXInterbaseCustomMetaDataReader
{
	typedef TDBXInterbaseCustomMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSchemas(const System::UnicodeString CatalogName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSynonyms(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString SynonymName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	
protected:
	virtual System::UnicodeString __fastcall GetProductName();
	virtual bool __fastcall IsDescendingIndexSupported();
	virtual bool __fastcall IsDescendingIndexColumnsSupported();
	virtual bool __fastcall IsNestedTransactionsSupported();
	virtual bool __fastcall IsParameterMetadataSupported();
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
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXInterbaseCustomMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXInterbaseMetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXInterbaseMetaDataReader() : TDBXInterbaseCustomMetaDataReader() { }
	
};


class PASCALIMPLEMENTATION TDBXInterbaseTypeFilterCursor : public Data::Dbxmetadatareader::TDBXCustomMetaDataTable
{
	typedef Data::Dbxmetadatareader::TDBXCustomMetaDataTable inherited;
	
	
public:
	class DELPHICLASS Tibase_const;
	class PASCALIMPLEMENTATION Tibase_const : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		static constexpr System::Int8 FBlr_text = System::Int8(0xe);
		
		static constexpr System::Int8 FBlr_text2 = System::Int8(0xf);
		
		static constexpr System::Int8 FBlr_short = System::Int8(0x7);
		
		static constexpr System::Int8 FBlr_long = System::Int8(0x8);
		
		static constexpr System::Int8 FBlr_quad = System::Int8(0x9);
		
		static constexpr System::Int8 FBlr_int64 = System::Int8(0x10);
		
		static constexpr System::Int8 FBlr_float = System::Int8(0xa);
		
		static constexpr System::Int8 FBlr_double = System::Int8(0x1b);
		
		static constexpr System::Int8 FBlr_d_float = System::Int8(0xb);
		
		static constexpr System::Int8 FBlr_timestamp = System::Int8(0x23);
		
		static constexpr System::Int8 FBlr_varying = System::Int8(0x25);
		
		static constexpr System::Int8 FBlr_varying2 = System::Int8(0x26);
		
		static constexpr System::Word FBlr_blob = System::Word(0x105);
		
		static constexpr System::Int8 FBlr_cstring = System::Int8(0x28);
		
		static constexpr System::Int8 FBlr_cstring2 = System::Int8(0x29);
		
		static constexpr System::Int8 FBlr_blob_id = System::Int8(0x2d);
		
		static constexpr System::Int8 FBlr_sql_date = System::Int8(0xc);
		
		static constexpr System::Int8 FBlr_sql_time = System::Int8(0xd);
		
		static constexpr System::Int8 FBlr_boolean_dtype = System::Int8(0x11);
		
	public:
		/* TObject.Create */ inline __fastcall Tibase_const() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~Tibase_const() { }
		
	};
	
	
	
public:
	__fastcall virtual ~TDBXInterbaseTypeFilterCursor();
	virtual bool __fastcall Next();
	
protected:
	__fastcall TDBXInterbaseTypeFilterCursor(TDBXInterbaseCustomMetaDataReader* const Provider, const System::UnicodeString MetadataCollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor, const int OrdinalTypeName, const int OrdinalFieldType, const int OrdinalSubType, const int OrdinalScale, const int OrdinalDefaultValue);
	virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
private:
	void __fastcall ComputeDataType();
	System::UnicodeString __fastcall ComputeTypeName();
	bool __fastcall ComputeUnicode();
	System::UnicodeString __fastcall ComputeDefaultValue();
	int __fastcall GetIBType(const short FieldType, const short FieldSubType, const short FieldScale);
	TDBXInterbaseCustomMetaDataReader* FCustomProvider;
	int FOrdinalTypeName;
	int FOrdinalFieldType;
	int FOrdinalSubType;
	int FOrdinalCharSet;
	int FOrdinalScale;
	int FOrdinalDefaultValue;
	Data::Dbxmetadatareader::TDBXDataTypeDescription* FDataType;
	Data::Dbxcommontable::TDBXSingleValueRow* FRow;
	#define TDBXInterbaseTypeFilterCursor_DefaultStringStart u"DEFAULT "
	
	/* Hoisted overloads: */
	
protected:
	inline int __fastcall  FindStringSize(Data::Dbxcommon::TDBXValueType* const Column){ return Data::Dbxmetadatareader::TDBXCustomMetaDataTable::FindStringSize(Column); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxinterbasemetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXINTERBASEMETADATAREADER)
using namespace Data::Dbxinterbasemetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxinterbasemetadatareaderHPP
