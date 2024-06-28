// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataReader.pas' rev: 34.00 (Android)

#ifndef Data_DbxmetadatareaderHPP
#define Data_DbxmetadatareaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXSqlScanner.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXColumnsTableCursor;
class DELPHICLASS TDBXCustomMetaDataTable;
class DELPHICLASS TDBXDataTypeCursor;
class DELPHICLASS TDBXDataTypeDescription;
class DELPHICLASS TDBXEmptyTableCursor;
class DELPHICLASS TDBXFilterProps;
class DELPHICLASS TDBXMetaDataCollectionColumns;
class DELPHICLASS TDBXMetaDataCommandParseResult;
class DELPHICLASS TDBXMetaDataReader;
class DELPHICLASS TDBXBaseMetaDataReader;
class DELPHICLASS TDBXParameterName;
class DELPHICLASS TDBXPlatformTypeNames;
class DELPHICLASS TDBXProcedureType;
class DELPHICLASS TDBXProviderContext;
class DELPHICLASS TDBXReservedWordsCursor;
class DELPHICLASS TDBXSourceTableCursor;
class DELPHICLASS TDBXTableType;
class DELPHICLASS TDBXTableTypeFlag;
class DELPHICLASS TDBXTableTypeParser;
class DELPHICLASS TDBXTypeFlag;
class DELPHICLASS TDBXVersion;
class DELPHICLASS TDBXMetaDataError;
//-- type declarations -------------------------------------------------------
typedef System::DynamicArray<TDBXDataTypeDescription*> TDBXDataTypeDescriptionArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXColumnsTableCursor : public Data::Dbxcommontable::TDBXDelegateTable
{
	typedef Data::Dbxcommontable::TDBXDelegateTable inherited;
	
public:
	__fastcall TDBXColumnsTableCursor()/* overload */;
	__fastcall TDBXColumnsTableCursor(TDBXBaseMetaDataReader* const Reader, const bool CheckBase, Data::Dbxcommontable::TDBXTable* const Cursor)/* overload */;
	__fastcall virtual ~TDBXColumnsTableCursor();
	virtual bool __fastcall Next();
	
protected:
	int FOrdinalOffset;
	int FOrdinalTypeName;
	TDBXBaseMetaDataReader* FReader;
	Data::Dbxplatform::TDBXObjectStore* FDataTypeHash;
	TDBXDataTypeDescription* FDataType;
	bool FCheckBase;
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
private:
	Data::Dbxcommontable::TDBXSingleValueRow* FDataTypesRow;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXCustomMetaDataTable : public Data::Dbxcommontable::TDBXRowTable
{
	typedef Data::Dbxcommontable::TDBXRowTable inherited;
	
public:
	__fastcall TDBXCustomMetaDataTable(TDBXPlatformTypeNames* const TypeNames, const System::UnicodeString MetaDataCollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor);
	__fastcall virtual ~TDBXCustomMetaDataTable();
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual bool __fastcall InBounds();
	virtual void __fastcall Close();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	
protected:
	virtual System::TObject* __fastcall GetCommand();
	virtual int __fastcall FindStringSize(const int Ordinal, const Data::Dbxcommon::TDBXValueTypeArray SourceColumns)/* overload */;
	virtual int __fastcall FindStringSize(Data::Dbxcommon::TDBXValueType* const Column)/* overload */;
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual void __fastcall CheckColumn(const int Ordinal);
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	virtual int __fastcall GetInt32(Data::Dbxcommontable::TDBXTable* const Cursor, const int Ordinal, const int DefaultValue);
	virtual __int64 __fastcall GetInt64(Data::Dbxcommontable::TDBXTable* const Cursor, const int Ordinal, const __int64 DefaultValue);
	virtual System::UnicodeString __fastcall GetAsString(Data::Dbxcommontable::TDBXTable* const Cursor, const int Ordinal, const System::UnicodeString DefaultValue);
	virtual bool __fastcall GetBoolean(Data::Dbxcommontable::TDBXTable* const Cursor, const int Ordinal, const bool DefaultValue);
	
private:
	void __fastcall AdjustColumnSize();
	
protected:
	TDBXPlatformTypeNames* FTypeNames;
	System::UnicodeString FMetaDataCollectionName;
	Data::Dbxcommontable::TDBXTable* FCursor;
	Data::Dbxcommon::TDBXValueTypeArray FColumns;
	
private:
	bool FColumnsSizeAdjusted;
	bool FHasIndexColumn;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXDataTypeCursor : public Data::Dbxcommontable::TDBXRowTable
{
	typedef Data::Dbxcommontable::TDBXRowTable inherited;
	
public:
	__fastcall TDBXDataTypeCursor(TDBXBaseMetaDataReader* const Reader, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxplatform::TDBXArrayList* const Types);
	__fastcall virtual ~TDBXDataTypeCursor();
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name)/* overload */;
	virtual void __fastcall Close();
	virtual bool __fastcall First();
	virtual bool __fastcall InBounds();
	virtual bool __fastcall Next();
	
protected:
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	TDBXBaseMetaDataReader* FReader;
	Data::Dbxplatform::TDBXArrayList* FTypes;
	TDBXDataTypeDescription* FCurrent;
	int FRowIndex;
	
private:
	Data::Dbxcommontable::TDBXSingleValueRow* FTypeRow;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

class PASCALIMPLEMENTATION TDBXDataTypeDescription : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXDataTypeDescription(const System::UnicodeString TypeName, const int DataType, const __int64 ColumnSize, const System::UnicodeString CreateFormat, const System::UnicodeString CreateParams, const int MaxScale, const int MinScale, const System::UnicodeString LiteralPrefix, const System::UnicodeString LiteralSuffix, const System::UnicodeString MaxVersion, const System::UnicodeString MinVersion, const int Flags)/* overload */;
	__fastcall TDBXDataTypeDescription(TDBXDataTypeDescription* const Original)/* overload */;
	System::UnicodeString __fastcall GetDataType(TDBXPlatformTypeNames* const TypeNames);
	
protected:
	bool __fastcall IsAutoIncrementable();
	bool __fastcall IsBestMatch();
	bool __fastcall IsCaseSensitive();
	bool __fastcall IsFixedLength();
	bool __fastcall IsFixedPrecisionScale();
	bool __fastcall IsLong();
	bool __fastcall IsNullable();
	bool __fastcall IsSearchable();
	bool __fastcall IsSearchableWithLike();
	bool __fastcall IsUnsigned();
	bool __fastcall IsUnicode();
	bool __fastcall IsUnicodeOptionSupported();
	void __fastcall SetUnicodeOptionSupported(const bool Supported);
	bool __fastcall IsUnsignedOptionSupported();
	bool __fastcall IsStringOptionSupported();
	bool __fastcall IsLongOptionSupported();
	short __fastcall GetMaximumScale();
	short __fastcall GetMinimumScale();
	bool __fastcall IsConcurrencyType();
	bool __fastcall IsLiteralSupported();
	
private:
	bool __fastcall IsFlagSet(const int Flag);
	void __fastcall SetFlag(const bool bOn, const int Flag);
	System::UnicodeString FTypeName;
	int FDataType;
	__int64 FColumnSize;
	int FFlags;
	System::UnicodeString FMaxVersion;
	System::UnicodeString FMinVersion;
	System::UnicodeString FCreateFormat;
	System::UnicodeString FCreateParams;
	System::UnicodeString FLiteralPrefix;
	System::UnicodeString FLiteralSuffix;
	int FMaxScale;
	int FMinScale;
	
public:
	__property System::UnicodeString TypeName = {read=FTypeName};
	__property int DbxDataType = {read=FDataType, nodefault};
	__property __int64 ColumnSize = {read=FColumnSize};
	__property System::UnicodeString CreateFormat = {read=FCreateFormat};
	__property System::UnicodeString CreateParameters = {read=FCreateParams};
	__property bool AutoIncrementable = {read=IsAutoIncrementable, nodefault};
	__property bool BestMatch = {read=IsBestMatch, nodefault};
	__property bool CaseSensitive = {read=IsCaseSensitive, nodefault};
	__property bool FixedLength = {read=IsFixedLength, nodefault};
	__property bool FixedPrecisionScale = {read=IsFixedPrecisionScale, nodefault};
	__property bool Long = {read=IsLong, nodefault};
	__property bool Nullable = {read=IsNullable, nodefault};
	__property bool Searchable = {read=IsSearchable, nodefault};
	__property bool SearchableWithLike = {read=IsSearchableWithLike, nodefault};
	__property bool Unsigned = {read=IsUnsigned, nodefault};
	__property bool Unicode = {read=IsUnicode, nodefault};
	__property bool UnicodeOptionSupported = {read=IsUnicodeOptionSupported, write=SetUnicodeOptionSupported, nodefault};
	__property bool UnsignedOptionSupported = {read=IsUnsignedOptionSupported, nodefault};
	__property bool StringOptionSupported = {read=IsStringOptionSupported, nodefault};
	__property bool LongOptionSupported = {read=IsLongOptionSupported, nodefault};
	__property short MaximumScale = {read=GetMaximumScale, nodefault};
	__property short MinimumScale = {read=GetMinimumScale, nodefault};
	__property bool ConcurrencyType = {read=IsConcurrencyType, nodefault};
	__property System::UnicodeString MaximumVersion = {read=FMaxVersion};
	__property System::UnicodeString MinimumVersion = {read=FMinVersion};
	__property bool LiteralSupported = {read=IsLiteralSupported, nodefault};
	__property System::UnicodeString LiteralPrefix = {read=FLiteralPrefix};
	__property System::UnicodeString LiteralSuffix = {read=FLiteralSuffix};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataTypeDescription() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXEmptyTableCursor : public Data::Dbxcommontable::TDBXTable
{
	typedef Data::Dbxcommontable::TDBXTable inherited;
	
public:
	__fastcall TDBXEmptyTableCursor(const System::UnicodeString MetaDataCollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns);
	__fastcall virtual ~TDBXEmptyTableCursor();
	virtual int __fastcall GetOrdinal(const System::UnicodeString ColumnName)/* overload */;
	virtual bool __fastcall First();
	virtual bool __fastcall InBounds();
	virtual bool __fastcall Next();
	virtual void __fastcall Close();
	
protected:
	virtual bool __fastcall IsUpdateable();
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	
public:
	Data::Dbxcommon::TDBXValueTypeArray FColumns;
	
private:
	System::UnicodeString FMetaDataCollectionName;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXFilterProps : public Data::Dbxcommon::TDBXProperties
{
	typedef Data::Dbxcommon::TDBXProperties inherited;
	
private:
	static constexpr __int64 FSerialVersionUID = -0x297bd397b94c735cLL;
	
public:
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXFilterProps(Data::Dbxcommon::TDBXContext* DBXContext)/* overload */ : Data::Dbxcommon::TDBXProperties(DBXContext) { }
	/* TDBXProperties.Create */ inline __fastcall virtual TDBXFilterProps()/* overload */ : Data::Dbxcommon::TDBXProperties() { }
	/* TDBXProperties.Destroy */ inline __fastcall virtual ~TDBXFilterProps() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataCollectionColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateDataTypesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateCatalogsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateSchemasColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateTablesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateViewsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateSynonymsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateColumnsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateColumnConstraintsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateIndexesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateIndexColumnsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateForeignKeysColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateForeignKeyColumnsColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateProceduresColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateProcedureSourcesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateProcedureParametersColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreatePackagesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreatePackageProceduresColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreatePackageProcedureParametersColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreatePackageSourcesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateUsersColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateRolesColumns();
	static Data::Dbxcommon::TDBXValueTypeArray __fastcall CreateReservedWordsColumns();
	static Data::Dbxcommon::TDBXValueType* __fastcall CreateValueType(const System::UnicodeString ColumnName, const System::UnicodeString ColumnCaption, const int ColumnType)/* overload */;
	static Data::Dbxcommon::TDBXValueType* __fastcall CreateValueType(const System::UnicodeString ColumnName, const System::UnicodeString ColumnCaption, const int ColumnType, const bool Hidden)/* overload */;
	static int __fastcall DefaultDataSize(const int ColumnType);
	
private:
	static constexpr System::Byte DefaultAnsiDataSize = System::Byte(0x80);
	
	static constexpr System::Word DefaultWideDataSize = System::Word(0x100);
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCollectionColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCollectionColumns() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataCommandParseResult : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXMetaDataCommandParseResult(const int CommandToken, const Data::Dbxplatform::TDBXStringArray Parameters);
	
private:
	int FCommandToken;
	Data::Dbxplatform::TDBXStringArray FParameters;
	
public:
	__property int CommandToken = {read=FCommandToken, nodefault};
	__property Data::Dbxplatform::TDBXStringArray Parameters = {read=FParameters};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCommandParseResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataReader : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCollection(const System::UnicodeString MetaDataCommand) = 0 ;
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCollectionWithStorage(const System::UnicodeString MetaDataCommand) = 0 ;
	
protected:
	virtual void __fastcall SetContext(TDBXProviderContext* const Context) = 0 ;
	virtual TDBXProviderContext* __fastcall GetContext() = 0 ;
	virtual System::UnicodeString __fastcall GetProductName() = 0 ;
	virtual System::UnicodeString __fastcall GetVersion() = 0 ;
	virtual void __fastcall SetVersion(const System::UnicodeString Version) = 0 ;
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix() = 0 ;
	virtual bool __fastcall IsLowerCaseIdentifiersSupported() = 0 ;
	virtual bool __fastcall IsUpperCaseIdentifiersSupported() = 0 ;
	virtual bool __fastcall IsQuotedIdentifiersSupported() = 0 ;
	virtual bool __fastcall IsDescendingIndexSupported() = 0 ;
	virtual bool __fastcall IsDescendingIndexColumnsSupported() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteChar() = 0 ;
	virtual System::UnicodeString __fastcall GetSqlProcedureQuoteChar() = 0 ;
	virtual bool __fastcall IsMultipleCommandsSupported() = 0 ;
	virtual bool __fastcall IsTransactionsSupported() = 0 ;
	virtual bool __fastcall IsNestedTransactionsSupported() = 0 ;
	virtual bool __fastcall IsSetRowSizeSupported() = 0 ;
	virtual bool __fastcall IsSPReturnCodeSupported() = 0 ;
	virtual bool __fastcall IsParameterMetadataSupported() = 0 ;
	virtual bool __fastcall AreCatalogFunctionsSupported() = 0 ;
	virtual bool __fastcall AreCatalogsSupported() = 0 ;
	virtual bool __fastcall AreSchemasSupported() = 0 ;
	
public:
	__property TDBXProviderContext* Context = {read=GetContext, write=SetContext};
	__property System::UnicodeString ProductName = {read=GetProductName};
	__property System::UnicodeString Version = {read=GetVersion, write=SetVersion};
	__property System::UnicodeString SqlIdentifierQuotePrefix = {read=GetSqlIdentifierQuotePrefix};
	__property System::UnicodeString SqlIdentifierQuoteSuffix = {read=GetSqlIdentifierQuoteSuffix};
	__property bool LowerCaseIdentifiersSupported = {read=IsLowerCaseIdentifiersSupported, nodefault};
	__property bool UpperCaseIdentifiersSupported = {read=IsUpperCaseIdentifiersSupported, nodefault};
	__property bool QuotedIdentifiersSupported = {read=IsQuotedIdentifiersSupported, nodefault};
	__property bool DescendingIndexSupported = {read=IsDescendingIndexSupported, nodefault};
	__property bool DescendingIndexColumnsSupported = {read=IsDescendingIndexColumnsSupported, nodefault};
	__property System::UnicodeString SqlIdentifierQuoteChar = {read=GetSqlIdentifierQuoteChar};
	__property System::UnicodeString SqlProcedureQuoteChar = {read=GetSqlProcedureQuoteChar};
	__property bool MultipleCommandsSupported = {read=IsMultipleCommandsSupported, nodefault};
	__property bool TransactionsSupported = {read=IsTransactionsSupported, nodefault};
	__property bool NestedTransactionsSupported = {read=IsNestedTransactionsSupported, nodefault};
	__property bool SetRowSizeSupported = {read=IsSetRowSizeSupported, nodefault};
	__property bool SPReturnCodeSupported = {read=IsSPReturnCodeSupported, nodefault};
	__property bool ParameterMetadataSupported = {read=IsParameterMetadataSupported, nodefault};
	__property bool CatalogFunctionsSupported = {read=AreCatalogFunctionsSupported, nodefault};
	__property bool CatalogsSupported = {read=AreCatalogsSupported, nodefault};
	__property bool SchemasSupported = {read=AreSchemasSupported, nodefault};
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataReader() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXBaseMetaDataReader : public TDBXMetaDataReader
{
	typedef TDBXMetaDataReader inherited;
	
public:
	__fastcall virtual ~TDBXBaseMetaDataReader();
	virtual int __fastcall CompareVersion(const System::UnicodeString OtherVersion);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCollection(const System::UnicodeString MetaDataCommand);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall MakeStorage(Data::Dbxcommontable::TDBXTable* &Cursor);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCollectionWithStorage(const System::UnicodeString MetaDataCommand);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchDataTypes();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSchemas(const System::UnicodeString Catalog);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchTables(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString TableName, const System::UnicodeString TableType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchViews(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString View);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexes(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchIndexColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString Index);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeys(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchForeignKeyColumns(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Table, const System::UnicodeString ForeignKeyName, const System::UnicodeString PrimaryCatalog, const System::UnicodeString PrimarySchema, const System::UnicodeString PrimaryTable, const System::UnicodeString PrimaryKeyName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchSynonyms(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Synonym);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedures(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureSources(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString Proc, const System::UnicodeString Parameter);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString Catalog, const System::UnicodeString Schema, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchUsers();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchRoles();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchReservedWords();
	
protected:
	virtual void __fastcall SetContext(TDBXProviderContext* const Context);
	virtual TDBXProviderContext* __fastcall GetContext();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetVersion();
	virtual void __fastcall SetVersion(const System::UnicodeString Version);
	virtual System::UnicodeString __fastcall GetSqlDefaultParameterMarker();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuotePrefix();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteSuffix();
	virtual bool __fastcall IsQuotedIdentifiersSupported();
	virtual bool __fastcall IsLowerCaseIdentifiersSupported();
	virtual bool __fastcall IsUpperCaseIdentifiersSupported();
	virtual bool __fastcall IsDescendingIndexSupported();
	virtual bool __fastcall IsDescendingIndexColumnsSupported();
	virtual bool __fastcall IsSPReturnCodeSupported();
	virtual bool __fastcall IsParameterMetadataSupported();
	virtual bool __fastcall AreCatalogFunctionsSupported();
	virtual bool __fastcall AreCatalogsSupported();
	virtual bool __fastcall AreSchemasSupported();
	virtual System::UnicodeString __fastcall GetSqlIdentifierQuoteChar();
	virtual System::UnicodeString __fastcall GetSqlProcedureQuoteChar();
	virtual bool __fastcall IsMultipleCommandsSupported();
	virtual bool __fastcall IsTransactionsSupported();
	virtual bool __fastcall IsNestedTransactionsSupported();
	virtual bool __fastcall IsSetRowSizeSupported();
	virtual System::UnicodeString __fastcall GetTableType();
	virtual System::UnicodeString __fastcall GetViewType();
	virtual System::UnicodeString __fastcall GetSystemTableType();
	virtual System::UnicodeString __fastcall GetSystemViewType();
	virtual System::UnicodeString __fastcall GetSynonymType();
	System::UnicodeString __fastcall MakeTableTypeString(const int InTableTypeCode, const int Flags);
	Data::Dbxplatform::TDBXObjectStore* __fastcall GetDataTypeHash();
	Data::Dbxplatform::TDBXArrayList* __fastcall GetDataTypes();
	virtual void __fastcall PopulateDataTypes(Data::Dbxplatform::TDBXObjectStore* const Hash, Data::Dbxplatform::TDBXArrayList* const Types, const TDBXDataTypeDescriptionArray Descr);
	virtual TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
	virtual System::UnicodeString __fastcall GetSqlForDataTypes();
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
	virtual System::UnicodeString __fastcall GetSqlForPackages();
	virtual System::UnicodeString __fastcall GetSqlForPackageProcedures();
	virtual System::UnicodeString __fastcall GetSqlForPackageProcedureParameters();
	virtual System::UnicodeString __fastcall GetSqlForPackageSources();
	virtual System::UnicodeString __fastcall GetSqlForUsers();
	virtual System::UnicodeString __fastcall GetSqlForRoles();
	virtual System::UnicodeString __fastcall GetSqlForReservedWords();
	
private:
	int __fastcall CountDigits(const System::UnicodeString Version, const int FromIndex);
	void __fastcall AppendVersionSection(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString Version, const int InStart, const int EndIndex, const int ExpectedLength, const bool AddDot);
	System::UnicodeString __fastcall MakeStandardVersionFormat(const System::UnicodeString Version);
	int __fastcall FindSourceLineColumn(Data::Dbxcommontable::TDBXTable* const Cursor, const int ExpectedColumns);
	void __fastcall InitScanner();
	TDBXMetaDataCommandParseResult* __fastcall ParseMetaDataCommand(const System::UnicodeString MetaDataCommand);
	System::UnicodeString __fastcall ParseId();
	void __fastcall ParseSqlObjectName(const Data::Dbxplatform::TDBXStringArray Parameters, const int MaxIds);
	TDBXMetaDataCommandParseResult* __fastcall ParseParameter(const int CommandToken, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseGetObjectName(const int CommandToken, const int MaxIds, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseGetTables(const int CommandToken, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseForeignKeyColumns(const int CommandToken, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseIndexColumns(const int CommandToken, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseProcedures(const int CommandToken, const int MaxIds, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseProcedureParameters(const int CommandToken, const int MaxIds, const System::UnicodeString Command);
	TDBXMetaDataCommandParseResult* __fastcall ParseDone(const int CommandToken, const System::UnicodeString Command, const Data::Dbxplatform::TDBXStringArray Parameters);
	TDBXProviderContext* FContext;
	Data::Dbxplatform::TDBXObjectStore* FDataTypeHash;
	Data::Dbxsqlscanner::TDBXSqlScanner* FScanner;
	System::UnicodeString FVersion;
	Data::Dbxplatform::TDBXArrayList* FTypes;
	
public:
	__property System::UnicodeString SqlDefaultParameterMarker = {read=GetSqlDefaultParameterMarker};
	__property System::UnicodeString TableType = {read=GetTableType};
	__property System::UnicodeString ViewType = {read=GetViewType};
	__property System::UnicodeString SystemTableType = {read=GetSystemTableType};
	__property System::UnicodeString SystemViewType = {read=GetSystemViewType};
	__property System::UnicodeString SynonymType = {read=GetSynonymType};
	__property Data::Dbxplatform::TDBXObjectStore* DataTypeHash = {read=GetDataTypeHash};
	__property Data::Dbxplatform::TDBXArrayList* DataTypes = {read=GetDataTypes};
	
protected:
	__property TDBXDataTypeDescriptionArray DataTypeDescriptions = {read=GetDataTypeDescriptions};
	__property Data::Dbxplatform::TDBXStringArray ReservedWords = {read=GetReservedWords};
	__property System::UnicodeString SqlForDataTypes = {read=GetSqlForDataTypes};
	__property System::UnicodeString SqlForCatalogs = {read=GetSqlForCatalogs};
	__property System::UnicodeString SqlForSchemas = {read=GetSqlForSchemas};
	__property System::UnicodeString SqlForTables = {read=GetSqlForTables};
	__property System::UnicodeString SqlForViews = {read=GetSqlForViews};
	__property System::UnicodeString SqlForColumns = {read=GetSqlForColumns};
	__property System::UnicodeString SqlForColumnConstraints = {read=GetSqlForColumnConstraints};
	__property System::UnicodeString SqlForIndexes = {read=GetSqlForIndexes};
	__property System::UnicodeString SqlForIndexColumns = {read=GetSqlForIndexColumns};
	__property System::UnicodeString SqlForForeignKeys = {read=GetSqlForForeignKeys};
	__property System::UnicodeString SqlForForeignKeyColumns = {read=GetSqlForForeignKeyColumns};
	__property System::UnicodeString SqlForSynonyms = {read=GetSqlForSynonyms};
	__property System::UnicodeString SqlForProcedures = {read=GetSqlForProcedures};
	__property System::UnicodeString SqlForProcedureSources = {read=GetSqlForProcedureSources};
	__property System::UnicodeString SqlForProcedureParameters = {read=GetSqlForProcedureParameters};
	__property System::UnicodeString SqlForPackages = {read=GetSqlForPackages};
	__property System::UnicodeString SqlForPackageProcedures = {read=GetSqlForPackageProcedures};
	__property System::UnicodeString SqlForPackageProcedureParameters = {read=GetSqlForPackageProcedureParameters};
	__property System::UnicodeString SqlForPackageSources = {read=GetSqlForPackageSources};
	__property System::UnicodeString SqlForUsers = {read=GetSqlForUsers};
	__property System::UnicodeString SqlForRoles = {read=GetSqlForRoles};
	__property System::UnicodeString SqlForReservedWords = {read=GetSqlForReservedWords};
	
private:
	#define TDBXBaseMetaDataReader_SourceLineNumber u"SOURCE_LINE_NUMBER"
	
	static constexpr System::WideChar Colon = (System::WideChar)(0x3a);
	
	static constexpr System::WideChar Dot = (System::WideChar)(0x2e);
	
	static constexpr System::WideChar DoubleQuote = (System::WideChar)(0x22);
	
	static constexpr System::Word TokenDatabase = System::Word(0x1f4);
	
	static constexpr System::Word TokenTable = System::Word(0x1f5);
	
	static constexpr System::Word TokenView = System::Word(0x1f6);
	
	static constexpr System::Word TokenSystemTable = System::Word(0x1f7);
	
	static constexpr System::Word TokenSystemView = System::Word(0x1f8);
	
	static constexpr System::Word TokenSynonym = System::Word(0x1f9);
	
	static constexpr System::Word TokenProcedureType = System::Word(0x1fa);
	
	static constexpr System::Word TokenFunctionType = System::Word(0x1fb);
	
	static constexpr System::Word TokenPrimaryKey = System::Word(0x1fc);
	
	static constexpr System::Word TokenForeignKey = System::Word(0x1fd);
	
public:
	/* TObject.Create */ inline __fastcall TDBXBaseMetaDataReader() : TDBXMetaDataReader() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXParameterName : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::WideChar DefaultMarker = (System::WideChar)(0x3a);
	
	#define TDBXParameterName_CatalogName u"CATALOG_NAME"
	
	#define TDBXParameterName_SchemaName u"SCHEMA_NAME"
	
	#define TDBXParameterName_TableName u"TABLE_NAME"
	
	#define TDBXParameterName_NewSchemaName u"NEW_SCHEMA_NAME"
	
	#define TDBXParameterName_NewTableName u"NEW_TABLE_NAME"
	
	#define TDBXParameterName_Tables u"TABLES"
	
	#define TDBXParameterName_Views u"VIEWS"
	
	#define TDBXParameterName_SystemTables u"SYSTEM_TABLES"
	
	#define TDBXParameterName_SystemViews u"SYSTEM_VIEWS"
	
	#define TDBXParameterName_Synonyms u"SYNONYMS"
	
	#define TDBXParameterName_ViewName u"VIEW_NAME"
	
	#define TDBXParameterName_IndexName u"INDEX_NAME"
	
	#define TDBXParameterName_ForeignKeyName u"FOREIGN_KEY_NAME"
	
	#define TDBXParameterName_PrimaryCatalogName u"PRIMARY_CATALOG_NAME"
	
	#define TDBXParameterName_PrimarySchemaName u"PRIMARY_SCHEMA_NAME"
	
	#define TDBXParameterName_PrimaryTableName u"PRIMARY_TABLE_NAME"
	
	#define TDBXParameterName_PrimaryKeyName u"PRIMARY_KEY_NAME"
	
	#define TDBXParameterName_SynonymName u"SYNONYM_NAME"
	
	#define TDBXParameterName_ProcedureType u"PROCEDURE_TYPE"
	
	#define TDBXParameterName_ProcedureName u"PROCEDURE_NAME"
	
	#define TDBXParameterName_PackageName u"PACKAGE_NAME"
	
	#define TDBXParameterName_ParameterName u"PARAMETER_NAME"
	
public:
	/* TObject.Create */ inline __fastcall TDBXParameterName() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXParameterName() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXPlatformTypeNames : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall GetPlatformTypeName(const int DataType, const bool IsUnsigned) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TDBXPlatformTypeNames() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPlatformTypeNames() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXProcedureType : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProcedureType_ProcedureType u"PROCEDURE"
	
	#define TDBXProcedureType_FunctionType u"FUNCTION"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureType() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXProviderContext : public TDBXPlatformTypeNames
{
	typedef TDBXPlatformTypeNames inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall ExecuteQuery(const System::UnicodeString Sql, const Data::Dbxplatform::TDBXStringArray ParameterNames, const Data::Dbxplatform::TDBXStringArray ParameterValues) = 0 ;
	virtual Data::Dbxcommontable::TDBXTable* __fastcall CreateTableStorage(const System::UnicodeString MetaDataCollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns) = 0 ;
	virtual Data::Dbxcommontable::TDBXTableRow* __fastcall CreateRowStorage(const System::UnicodeString MetaDataCollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns) = 0 ;
	virtual void __fastcall StartSerializedTransaction() = 0 ;
	virtual void __fastcall StartTransaction() = 0 ;
	virtual void __fastcall Commit() = 0 ;
	virtual void __fastcall Rollback() = 0 ;
	virtual System::UnicodeString __fastcall GetVendorProperty(const System::UnicodeString Name) = 0 ;
	static bool __fastcall UseAnsiString(const System::UnicodeString ProductName);
public:
	/* TObject.Create */ inline __fastcall TDBXProviderContext() : TDBXPlatformTypeNames() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProviderContext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXReservedWordsCursor : public Data::Dbxcommontable::TDBXTable
{
	typedef Data::Dbxcommontable::TDBXTable inherited;
	
public:
	__fastcall TDBXReservedWordsCursor(TDBXPlatformTypeNames* const TypeNames, const Data::Dbxcommon::TDBXValueTypeArray Columns, const Data::Dbxplatform::TDBXStringArray Keywords);
	virtual int __fastcall GetOrdinal(const System::UnicodeString Name)/* overload */;
	__fastcall virtual ~TDBXReservedWordsCursor();
	virtual bool __fastcall First();
	virtual bool __fastcall Next();
	virtual bool __fastcall InBounds();
	virtual void __fastcall Close();
	
protected:
	virtual System::UnicodeString __fastcall GetDBXTableName();
	virtual Data::Dbxcommon::TDBXValueTypeArray __fastcall GetColumns();
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	TDBXPlatformTypeNames* FTypeNames;
	Data::Dbxplatform::TDBXStringArray FKeywords;
	int FRowIndex;
	
private:
	Data::Dbxcommontable::TDBXSingleValueRow* FReservedRow;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXSourceTableCursor : public TDBXCustomMetaDataTable
{
	typedef TDBXCustomMetaDataTable inherited;
	
public:
	__fastcall TDBXSourceTableCursor(TDBXProviderContext* const Context, const System::UnicodeString MetaDataCollectionName, const Data::Dbxcommon::TDBXValueTypeArray Columns, Data::Dbxcommontable::TDBXTable* const Cursor, const int OrdinalDefinition, const int OrdinalLineNumber);
	__fastcall virtual ~TDBXSourceTableCursor();
	virtual bool __fastcall Next();
	
protected:
	virtual Data::Dbxcommon::TDBXWritableValue* __fastcall GetWritableValue(const int Ordinal);
	
private:
	Data::Dbxcommontable::TDBXSingleValueRow* FRowStorage;
	System::Sysutils::TStringBuilder* FBuffer;
	int FOrdinalLineNumber;
	int FOrdinalDefinition;
	bool FBeforeEnd;
	bool FBeforeFirst;
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTableType : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXTableType_Table u"TABLE"
	
	#define TDBXTableType_View u"VIEW"
	
	#define TDBXTableType_Synonym u"SYNONYM"
	
	#define TDBXTableType_SystemTable u"SYSTEM TABLE"
	
	#define TDBXTableType_SystemView u"SYSTEM VIEW"
	
public:
	/* TObject.Create */ inline __fastcall TDBXTableType() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTableType() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTableTypeFlag : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 Table = System::Int8(0x1);
	
	static constexpr System::Int8 View = System::Int8(0x2);
	
	static constexpr System::Int8 SystemTable = System::Int8(0x4);
	
	static constexpr System::Int8 SystemView = System::Int8(0x8);
	
	static constexpr System::Int8 Synonym = System::Int8(0x10);
	
	static constexpr System::Int8 All = System::Int8(0x1f);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTableTypeFlag() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTableTypeFlag() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTableTypeParser : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static int __fastcall ParseTableTypes(const System::UnicodeString TableTypes);
public:
	/* TObject.Create */ inline __fastcall TDBXTableTypeParser() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTableTypeParser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXTypeFlag : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 AutoIncrementable = System::Int8(0x1);
	
	static constexpr System::Int8 BestMatch = System::Int8(0x2);
	
	static constexpr System::Int8 FixedLength = System::Int8(0x4);
	
	static constexpr System::Int8 CaseSensitive = System::Int8(0x8);
	
	static constexpr System::Int8 FixedPrecisionScale = System::Int8(0x10);
	
	static constexpr System::Int8 Long = System::Int8(0x20);
	
	static constexpr System::Int8 Nullable = System::Int8(0x40);
	
	static constexpr System::Byte Searchable = System::Byte(0x80);
	
	static constexpr System::Word SearchableWithLike = System::Word(0x100);
	
	static constexpr System::Word Unsigned = System::Word(0x200);
	
	static constexpr System::Word ConcurrencyType = System::Word(0x400);
	
	static constexpr System::Word LiteralSupported = System::Word(0x800);
	
	static constexpr System::Word Unicode = System::Word(0x1000);
	
	static constexpr System::Word UnicodeOption = System::Word(0x2000);
	
	static constexpr System::Word UnsignedOption = System::Word(0x4000);
	
	static constexpr System::Word StringOption = System::Word(0x8000);
	
	static constexpr int LongOption = int(0x10000);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTypeFlag() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTypeFlag() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXVersion : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXVersion_FMySQL4_1 u"04.01.0000"
	
	#define TDBXVersion_FMySQL5 u"05.00.0000"
	
	#define TDBXVersion_FMySQL5_0_6 u"05.00.0006"
	
	#define TDBXVersion_FVersion10 u"10.00.0000"
	
public:
	/* TObject.Create */ inline __fastcall TDBXVersion() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXVersion() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXMetaDataError : public Data::Dbxcommon::TDBXError
{
	typedef Data::Dbxcommon::TDBXError inherited;
	
public:
	__fastcall TDBXMetaDataError(const System::UnicodeString Message);
public:
	/* Exception.CreateFmt */ inline __fastcall TDBXMetaDataError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Data::Dbxcommon::TDBXError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDBXMetaDataError(NativeUInt Ident)/* overload */ : Data::Dbxcommon::TDBXError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDBXMetaDataError(System::PResStringRec ResStringRec)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXMetaDataError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Dbxcommon::TDBXError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDBXMetaDataError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDBXMetaDataError(const System::UnicodeString Msg, int AHelpContext) : Data::Dbxcommon::TDBXError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDBXMetaDataError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Data::Dbxcommon::TDBXError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXMetaDataError(NativeUInt Ident, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDBXMetaDataError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXMetaDataError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDBXMetaDataError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Data::Dbxcommon::TDBXError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDBXMetaDataError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATAREADER)
using namespace Data::Dbxmetadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatareaderHPP
