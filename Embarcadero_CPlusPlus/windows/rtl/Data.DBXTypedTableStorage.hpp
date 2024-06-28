// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXTypedTableStorage.pas' rev: 34.00 (Windows)

#ifndef Data_DbxtypedtablestorageHPP
#define Data_DbxtypedtablestorageHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXCommonTable.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxtypedtablestorage
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMemoryDelegateTable;
class DELPHICLASS TDBXCatalogsTableStorage;
class DELPHICLASS TDBXColumnConstraintsTableStorage;
class DELPHICLASS TDBXColumnsTableStorage;
class DELPHICLASS TDBXDataTypesTableStorage;
class DELPHICLASS TDBXForeignKeyColumnsTableStorage;
class DELPHICLASS TDBXForeignKeysTableStorage;
class DELPHICLASS TDBXIndexColumnsTableStorage;
class DELPHICLASS TDBXIndexesTableStorage;
class DELPHICLASS TDBXPackageProcedureParametersTableStorage;
class DELPHICLASS TDBXPackageProceduresTableStorage;
class DELPHICLASS TDBXPackageSourcesTableStorage;
class DELPHICLASS TDBXPackagesTableStorage;
class DELPHICLASS TDBXProcedureParametersTableStorage;
class DELPHICLASS TDBXProcedureSourcesTableStorage;
class DELPHICLASS TDBXProceduresTableStorage;
class DELPHICLASS TDBXReservedWordsTableStorage;
class DELPHICLASS TDBXRolesTableStorage;
class DELPHICLASS TDBXSchemasTableStorage;
class DELPHICLASS TDBXSynonymsTableStorage;
class DELPHICLASS TDBXTablesTableStorage;
class DELPHICLASS TDBXUsersTableStorage;
class DELPHICLASS TDBXViewsTableStorage;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMemoryDelegateTable : public Data::Dbxcommontable::TDBXDelegateTable
{
	typedef Data::Dbxcommontable::TDBXDelegateTable inherited;
	
public:
	HIDESBASE void __fastcall Insert(const int AIndex)/* overload */;
	HIDESBASE void __fastcall DeleteRow(const int AIndex)/* overload */;
	Data::Dbxcommon::TDBXWritableValueArray __fastcall GetRow(const int AIndex);
public:
	/* TDBXDelegateTable.Create */ inline __fastcall TDBXMemoryDelegateTable() : Data::Dbxcommontable::TDBXDelegateTable() { }
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXMemoryDelegateTable() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXCatalogsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXCatalogsTableStorage()/* overload */;
	__fastcall TDBXCatalogsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXCatalogsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnConstraintsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXColumnConstraintsTableStorage()/* overload */;
	__fastcall TDBXColumnConstraintsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetConstraintName();
	void __fastcall SetConstraintName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetColumnName();
	void __fastcall SetColumnName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString ConstraintName = {read=GetConstraintName, write=SetConstraintName};
	__property System::UnicodeString ColumnName = {read=GetColumnName, write=SetColumnName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXColumnConstraintsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXColumnsTableStorage()/* overload */;
	__fastcall TDBXColumnsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetColumnName();
	void __fastcall SetColumnName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTypeName();
	void __fastcall SetTypeName(const System::UnicodeString Value);
	__int64 __fastcall GetPrecision();
	void __fastcall SetPrecision(const __int64 Value);
	int __fastcall GetScale();
	void __fastcall SetScale(const int Value);
	int __fastcall GetColumnOrdinal();
	void __fastcall SetColumnOrdinal(const int Value);
	System::UnicodeString __fastcall GetDefaultValue();
	void __fastcall SetDefaultValue(const System::UnicodeString Value);
	bool __fastcall IsNullable();
	void __fastcall SetNullable(const bool Value);
	bool __fastcall IsAutoIncrement();
	void __fastcall SetAutoIncrement(const bool Value);
	int __fastcall GetMaxInline();
	void __fastcall SetMaxInline(const int Value);
	int __fastcall GetDbxDataType();
	void __fastcall SetDbxDataType(const int Value);
	bool __fastcall IsFixedLength();
	void __fastcall SetFixedLength(const bool Value);
	bool __fastcall IsUnicode();
	void __fastcall SetUnicode(const bool Value);
	bool __fastcall IsLong();
	void __fastcall SetLong(const bool Value);
	bool __fastcall IsUnsigned();
	void __fastcall SetUnsigned(const bool Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString ColumnName = {read=GetColumnName, write=SetColumnName};
	__property System::UnicodeString TypeName = {read=GetTypeName, write=SetTypeName};
	__property __int64 Precision = {read=GetPrecision, write=SetPrecision};
	__property int Scale = {read=GetScale, write=SetScale, nodefault};
	__property int ColumnOrdinal = {read=GetColumnOrdinal, write=SetColumnOrdinal, nodefault};
	__property System::UnicodeString DefaultValue = {read=GetDefaultValue, write=SetDefaultValue};
	__property bool Nullable = {read=IsNullable, write=SetNullable, nodefault};
	__property bool AutoIncrement = {read=IsAutoIncrement, write=SetAutoIncrement, nodefault};
	__property int MaxInline = {read=GetMaxInline, write=SetMaxInline, nodefault};
	__property int DbxDataType = {read=GetDbxDataType, write=SetDbxDataType, nodefault};
	__property bool FixedLength = {read=IsFixedLength, write=SetFixedLength, nodefault};
	__property bool Unicode = {read=IsUnicode, write=SetUnicode, nodefault};
	__property bool Long = {read=IsLong, write=SetLong, nodefault};
	__property bool Unsigned = {read=IsUnsigned, write=SetUnsigned, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXColumnsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataTypesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXDataTypesTableStorage()/* overload */;
	__fastcall TDBXDataTypesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetTypeName();
	void __fastcall SetTypeName(const System::UnicodeString Value);
	int __fastcall GetDbxDataType();
	void __fastcall SetDbxDataType(const int Value);
	__int64 __fastcall GetColumnSize();
	void __fastcall SetColumnSize(const __int64 Value);
	System::UnicodeString __fastcall GetCreateFormat();
	void __fastcall SetCreateFormat(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetCreateParameters();
	void __fastcall SetCreateParameters(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetDataType();
	void __fastcall SetDataType(const System::UnicodeString Value);
	bool __fastcall IsAutoIncrementable();
	void __fastcall SetAutoIncrementable(const bool Value);
	bool __fastcall IsBestMatch();
	void __fastcall SetBestMatch(const bool Value);
	bool __fastcall IsCaseSensitive();
	void __fastcall SetCaseSensitive(const bool Value);
	bool __fastcall IsFixedLength();
	void __fastcall SetFixedLength(const bool Value);
	bool __fastcall IsFixedPrecisionScale();
	void __fastcall SetFixedPrecisionScale(const bool Value);
	bool __fastcall IsLong();
	void __fastcall SetLong(const bool Value);
	bool __fastcall IsNullable();
	void __fastcall SetNullable(const bool Value);
	bool __fastcall IsSearchable();
	void __fastcall SetSearchable(const bool Value);
	bool __fastcall IsSearchableWithLike();
	void __fastcall SetSearchableWithLike(const bool Value);
	bool __fastcall IsUnsigned();
	void __fastcall SetUnsigned(const bool Value);
	short __fastcall GetMaximumScale();
	void __fastcall SetMaximumScale(const short Value);
	short __fastcall GetMinimumScale();
	void __fastcall SetMinimumScale(const short Value);
	bool __fastcall IsConcurrencyType();
	void __fastcall SetConcurrencyType(const bool Value);
	System::UnicodeString __fastcall GetMaximumVersion();
	void __fastcall SetMaximumVersion(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetMinimumVersion();
	void __fastcall SetMinimumVersion(const System::UnicodeString Value);
	bool __fastcall IsLiteralSupported();
	void __fastcall SetLiteralSupported(const bool Value);
	System::UnicodeString __fastcall GetLiteralPrefix();
	void __fastcall SetLiteralPrefix(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetLiteralSuffix();
	void __fastcall SetLiteralSuffix(const System::UnicodeString Value);
	bool __fastcall IsUnicode();
	void __fastcall SetUnicode(const bool Value);
	int __fastcall GetProviderDbType();
	void __fastcall SetProviderDbType(const int Value);
	
public:
	__property System::UnicodeString TypeName = {read=GetTypeName, write=SetTypeName};
	__property int DbxDataType = {read=GetDbxDataType, write=SetDbxDataType, nodefault};
	__property __int64 ColumnSize = {read=GetColumnSize, write=SetColumnSize};
	__property System::UnicodeString CreateFormat = {read=GetCreateFormat, write=SetCreateFormat};
	__property System::UnicodeString CreateParameters = {read=GetCreateParameters, write=SetCreateParameters};
	__property System::UnicodeString DataType = {read=GetDataType, write=SetDataType};
	__property bool AutoIncrementable = {read=IsAutoIncrementable, write=SetAutoIncrementable, nodefault};
	__property bool BestMatch = {read=IsBestMatch, write=SetBestMatch, nodefault};
	__property bool CaseSensitive = {read=IsCaseSensitive, write=SetCaseSensitive, nodefault};
	__property bool FixedLength = {read=IsFixedLength, write=SetFixedLength, nodefault};
	__property bool FixedPrecisionScale = {read=IsFixedPrecisionScale, write=SetFixedPrecisionScale, nodefault};
	__property bool Long = {read=IsLong, write=SetLong, nodefault};
	__property bool Nullable = {read=IsNullable, write=SetNullable, nodefault};
	__property bool Searchable = {read=IsSearchable, write=SetSearchable, nodefault};
	__property bool SearchableWithLike = {read=IsSearchableWithLike, write=SetSearchableWithLike, nodefault};
	__property bool Unsigned = {read=IsUnsigned, write=SetUnsigned, nodefault};
	__property short MaximumScale = {read=GetMaximumScale, write=SetMaximumScale, nodefault};
	__property short MinimumScale = {read=GetMinimumScale, write=SetMinimumScale, nodefault};
	__property bool ConcurrencyType = {read=IsConcurrencyType, write=SetConcurrencyType, nodefault};
	__property System::UnicodeString MaximumVersion = {read=GetMaximumVersion, write=SetMaximumVersion};
	__property System::UnicodeString MinimumVersion = {read=GetMinimumVersion, write=SetMinimumVersion};
	__property bool LiteralSupported = {read=IsLiteralSupported, write=SetLiteralSupported, nodefault};
	__property System::UnicodeString LiteralPrefix = {read=GetLiteralPrefix, write=SetLiteralPrefix};
	__property System::UnicodeString LiteralSuffix = {read=GetLiteralSuffix, write=SetLiteralSuffix};
	__property bool Unicode = {read=IsUnicode, write=SetUnicode, nodefault};
	__property int ProviderDbType = {read=GetProviderDbType, write=SetProviderDbType, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXDataTypesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXForeignKeyColumnsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXForeignKeyColumnsTableStorage()/* overload */;
	__fastcall TDBXForeignKeyColumnsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetForeignKeyName();
	void __fastcall SetForeignKeyName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetColumnName();
	void __fastcall SetColumnName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPrimaryCatalogName();
	void __fastcall SetPrimaryCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPrimarySchemaName();
	void __fastcall SetPrimarySchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPrimaryTableName();
	void __fastcall SetPrimaryTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPrimaryKeyName();
	void __fastcall SetPrimaryKeyName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPrimaryColumnName();
	void __fastcall SetPrimaryColumnName(const System::UnicodeString Value);
	int __fastcall GetColumnOrdinal();
	void __fastcall SetColumnOrdinal(const int Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString ForeignKeyName = {read=GetForeignKeyName, write=SetForeignKeyName};
	__property System::UnicodeString ColumnName = {read=GetColumnName, write=SetColumnName};
	__property System::UnicodeString PrimaryCatalogName = {read=GetPrimaryCatalogName, write=SetPrimaryCatalogName};
	__property System::UnicodeString PrimarySchemaName = {read=GetPrimarySchemaName, write=SetPrimarySchemaName};
	__property System::UnicodeString PrimaryTableName = {read=GetPrimaryTableName, write=SetPrimaryTableName};
	__property System::UnicodeString PrimaryKeyName = {read=GetPrimaryKeyName, write=SetPrimaryKeyName};
	__property System::UnicodeString PrimaryColumnName = {read=GetPrimaryColumnName, write=SetPrimaryColumnName};
	__property int ColumnOrdinal = {read=GetColumnOrdinal, write=SetColumnOrdinal, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXForeignKeyColumnsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXForeignKeysTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXForeignKeysTableStorage()/* overload */;
	__fastcall TDBXForeignKeysTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetForeignKeyName();
	void __fastcall SetForeignKeyName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString ForeignKeyName = {read=GetForeignKeyName, write=SetForeignKeyName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXForeignKeysTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIndexColumnsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXIndexColumnsTableStorage()/* overload */;
	__fastcall TDBXIndexColumnsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetIndexName();
	void __fastcall SetIndexName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetColumnName();
	void __fastcall SetColumnName(const System::UnicodeString Value);
	int __fastcall GetColumnOrdinal();
	void __fastcall SetColumnOrdinal(const int Value);
	bool __fastcall IsAscending();
	void __fastcall SetAscending(const bool Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString IndexName = {read=GetIndexName, write=SetIndexName};
	__property System::UnicodeString ColumnName = {read=GetColumnName, write=SetColumnName};
	__property int ColumnOrdinal = {read=GetColumnOrdinal, write=SetColumnOrdinal, nodefault};
	__property bool Ascending = {read=IsAscending, write=SetAscending, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXIndexColumnsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIndexesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXIndexesTableStorage()/* overload */;
	__fastcall TDBXIndexesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetIndexName();
	void __fastcall SetIndexName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetConstraintName();
	void __fastcall SetConstraintName(const System::UnicodeString Value);
	bool __fastcall IsPrimary();
	void __fastcall SetPrimary(const bool Value);
	bool __fastcall IsUnique();
	void __fastcall SetUnique(const bool Value);
	bool __fastcall IsAscending();
	void __fastcall SetAscending(const bool Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString IndexName = {read=GetIndexName, write=SetIndexName};
	__property System::UnicodeString ConstraintName = {read=GetConstraintName, write=SetConstraintName};
	__property bool Primary = {read=IsPrimary, write=SetPrimary, nodefault};
	__property bool Unique = {read=IsUnique, write=SetUnique, nodefault};
	__property bool Ascending = {read=IsAscending, write=SetAscending, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXIndexesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageProcedureParametersTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXPackageProcedureParametersTableStorage()/* overload */;
	__fastcall TDBXPackageProcedureParametersTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPackageName();
	void __fastcall SetPackageName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProcedureName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetParameterName();
	void __fastcall SetParameterName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetParameterMode();
	void __fastcall SetParameterMode(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTypeName();
	void __fastcall SetTypeName(const System::UnicodeString Value);
	__int64 __fastcall GetPrecision();
	void __fastcall SetPrecision(const __int64 Value);
	int __fastcall GetScale();
	void __fastcall SetScale(const int Value);
	int __fastcall GetColumnOrdinal();
	void __fastcall SetColumnOrdinal(const int Value);
	bool __fastcall IsNullable();
	void __fastcall SetNullable(const bool Value);
	int __fastcall GetDbxDataType();
	void __fastcall SetDbxDataType(const int Value);
	bool __fastcall IsFixedLength();
	void __fastcall SetFixedLength(const bool Value);
	bool __fastcall IsUnicode();
	void __fastcall SetUnicode(const bool Value);
	bool __fastcall IsLong();
	void __fastcall SetLong(const bool Value);
	bool __fastcall IsUnsigned();
	void __fastcall SetUnsigned(const bool Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString PackageName = {read=GetPackageName, write=SetPackageName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName, write=SetProcedureName};
	__property System::UnicodeString ParameterName = {read=GetParameterName, write=SetParameterName};
	__property System::UnicodeString ParameterMode = {read=GetParameterMode, write=SetParameterMode};
	__property System::UnicodeString TypeName = {read=GetTypeName, write=SetTypeName};
	__property __int64 Precision = {read=GetPrecision, write=SetPrecision};
	__property int Scale = {read=GetScale, write=SetScale, nodefault};
	__property int ColumnOrdinal = {read=GetColumnOrdinal, write=SetColumnOrdinal, nodefault};
	__property bool Nullable = {read=IsNullable, write=SetNullable, nodefault};
	__property int DbxDataType = {read=GetDbxDataType, write=SetDbxDataType, nodefault};
	__property bool FixedLength = {read=IsFixedLength, write=SetFixedLength, nodefault};
	__property bool Unicode = {read=IsUnicode, write=SetUnicode, nodefault};
	__property bool Long = {read=IsLong, write=SetLong, nodefault};
	__property bool Unsigned = {read=IsUnsigned, write=SetUnsigned, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXPackageProcedureParametersTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageProceduresTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXPackageProceduresTableStorage()/* overload */;
	__fastcall TDBXPackageProceduresTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPackageName();
	void __fastcall SetPackageName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProcedureName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureType();
	void __fastcall SetProcedureType(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString PackageName = {read=GetPackageName, write=SetPackageName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName, write=SetProcedureName};
	__property System::UnicodeString ProcedureType = {read=GetProcedureType, write=SetProcedureType};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXPackageProceduresTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageSourcesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXPackageSourcesTableStorage()/* overload */;
	__fastcall TDBXPackageSourcesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPackageName();
	void __fastcall SetPackageName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetDefinition();
	void __fastcall SetDefinition(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString PackageName = {read=GetPackageName, write=SetPackageName};
	__property System::UnicodeString Definition = {read=GetDefinition, write=SetDefinition};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXPackageSourcesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackagesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXPackagesTableStorage()/* overload */;
	__fastcall TDBXPackagesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetPackageName();
	void __fastcall SetPackageName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString PackageName = {read=GetPackageName, write=SetPackageName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXPackagesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProcedureParametersTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXProcedureParametersTableStorage()/* overload */;
	__fastcall TDBXProcedureParametersTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProcedureName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetParameterName();
	void __fastcall SetParameterName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetParameterMode();
	void __fastcall SetParameterMode(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTypeName();
	void __fastcall SetTypeName(const System::UnicodeString Value);
	__int64 __fastcall GetPrecision();
	void __fastcall SetPrecision(const __int64 Value);
	int __fastcall GetScale();
	void __fastcall SetScale(const int Value);
	int __fastcall GetColumnOrdinal();
	void __fastcall SetColumnOrdinal(const int Value);
	bool __fastcall IsNullable();
	void __fastcall SetNullable(const bool Value);
	int __fastcall GetDbxDataType();
	void __fastcall SetDbxDataType(const int Value);
	bool __fastcall IsFixedLength();
	void __fastcall SetFixedLength(const bool Value);
	bool __fastcall IsUnicode();
	void __fastcall SetUnicode(const bool Value);
	bool __fastcall IsLong();
	void __fastcall SetLong(const bool Value);
	bool __fastcall IsUnsigned();
	void __fastcall SetUnsigned(const bool Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName, write=SetProcedureName};
	__property System::UnicodeString ParameterName = {read=GetParameterName, write=SetParameterName};
	__property System::UnicodeString ParameterMode = {read=GetParameterMode, write=SetParameterMode};
	__property System::UnicodeString TypeName = {read=GetTypeName, write=SetTypeName};
	__property __int64 Precision = {read=GetPrecision, write=SetPrecision};
	__property int Scale = {read=GetScale, write=SetScale, nodefault};
	__property int ColumnOrdinal = {read=GetColumnOrdinal, write=SetColumnOrdinal, nodefault};
	__property bool Nullable = {read=IsNullable, write=SetNullable, nodefault};
	__property int DbxDataType = {read=GetDbxDataType, write=SetDbxDataType, nodefault};
	__property bool FixedLength = {read=IsFixedLength, write=SetFixedLength, nodefault};
	__property bool Unicode = {read=IsUnicode, write=SetUnicode, nodefault};
	__property bool Long = {read=IsLong, write=SetLong, nodefault};
	__property bool Unsigned = {read=IsUnsigned, write=SetUnsigned, nodefault};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXProcedureParametersTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProcedureSourcesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXProcedureSourcesTableStorage()/* overload */;
	__fastcall TDBXProcedureSourcesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProcedureName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureType();
	void __fastcall SetProcedureType(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetDefinition();
	void __fastcall SetDefinition(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetExternalDefinition();
	void __fastcall SetExternalDefinition(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName, write=SetProcedureName};
	__property System::UnicodeString ProcedureType = {read=GetProcedureType, write=SetProcedureType};
	__property System::UnicodeString Definition = {read=GetDefinition, write=SetDefinition};
	__property System::UnicodeString ExternalDefinition = {read=GetExternalDefinition, write=SetExternalDefinition};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXProcedureSourcesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProceduresTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXProceduresTableStorage()/* overload */;
	__fastcall TDBXProceduresTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureName();
	void __fastcall SetProcedureName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetProcedureType();
	void __fastcall SetProcedureType(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString ProcedureName = {read=GetProcedureName, write=SetProcedureName};
	__property System::UnicodeString ProcedureType = {read=GetProcedureType, write=SetProcedureType};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXProceduresTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXReservedWordsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXReservedWordsTableStorage()/* overload */;
	__fastcall TDBXReservedWordsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetReservedWord();
	void __fastcall SetReservedWord(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString ReservedWord = {read=GetReservedWord, write=SetReservedWord};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXReservedWordsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXRolesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXRolesTableStorage()/* overload */;
	__fastcall TDBXRolesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetRoleName();
	void __fastcall SetRoleName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString RoleName = {read=GetRoleName, write=SetRoleName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXRolesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSchemasTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXSchemasTableStorage()/* overload */;
	__fastcall TDBXSchemasTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXSchemasTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSynonymsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXSynonymsTableStorage()/* overload */;
	__fastcall TDBXSynonymsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSynonymName();
	void __fastcall SetSynonymName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableCatalogName();
	void __fastcall SetTableCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableSchemaName();
	void __fastcall SetTableSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString SynonymName = {read=GetSynonymName, write=SetSynonymName};
	__property System::UnicodeString TableCatalogName = {read=GetTableCatalogName, write=SetTableCatalogName};
	__property System::UnicodeString TableSchemaName = {read=GetTableSchemaName, write=SetTableSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXSynonymsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTablesTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXTablesTableStorage()/* overload */;
	__fastcall TDBXTablesTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableName();
	void __fastcall SetTableName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetTableType();
	void __fastcall SetTableType(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString TableName = {read=GetTableName, write=SetTableName};
	__property System::UnicodeString TableType = {read=GetTableType, write=SetTableType};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXTablesTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXUsersTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXUsersTableStorage()/* overload */;
	__fastcall TDBXUsersTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetUserName();
	void __fastcall SetUserName(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXUsersTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXViewsTableStorage : public TDBXMemoryDelegateTable
{
	typedef TDBXMemoryDelegateTable inherited;
	
public:
	__fastcall TDBXViewsTableStorage()/* overload */;
	__fastcall TDBXViewsTableStorage(Data::Dbxcommontable::TDBXTable* const TableStore)/* overload */;
	
protected:
	System::UnicodeString __fastcall GetCatalogName();
	void __fastcall SetCatalogName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSchemaName();
	void __fastcall SetSchemaName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetViewName();
	void __fastcall SetViewName(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetDefinition();
	void __fastcall SetDefinition(const System::UnicodeString Value);
	
public:
	__property System::UnicodeString CatalogName = {read=GetCatalogName, write=SetCatalogName};
	__property System::UnicodeString SchemaName = {read=GetSchemaName, write=SetSchemaName};
	__property System::UnicodeString ViewName = {read=GetViewName, write=SetViewName};
	__property System::UnicodeString Definition = {read=GetDefinition, write=SetDefinition};
public:
	/* TDBXDelegateTable.Destroy */ inline __fastcall virtual ~TDBXViewsTableStorage() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxtypedtablestorage */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXTYPEDTABLESTORAGE)
using namespace Data::Dbxtypedtablestorage;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxtypedtablestorageHPP
