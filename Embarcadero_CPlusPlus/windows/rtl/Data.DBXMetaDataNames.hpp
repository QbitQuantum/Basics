// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataNames.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmetadatanamesHPP
#define Data_DbxmetadatanamesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatanames
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXCatalogsColumns;
class DELPHICLASS TDBXCatalogsIndex;
class DELPHICLASS TDBXColumnConstraintsColumns;
class DELPHICLASS TDBXColumnConstraintsIndex;
class DELPHICLASS TDBXColumnsColumns;
class DELPHICLASS TDBXColumnsIndex;
class DELPHICLASS TDBXDataTypesColumns;
class DELPHICLASS TDBXDataTypesIndex;
class DELPHICLASS TDBXForeignKeyColumnsColumns;
class DELPHICLASS TDBXForeignKeyColumnsIndex;
class DELPHICLASS TDBXForeignKeysColumns;
class DELPHICLASS TDBXForeignKeysIndex;
class DELPHICLASS TDBXIndexColumnsColumns;
class DELPHICLASS TDBXIndexColumnsIndex;
class DELPHICLASS TDBXIndexesColumns;
class DELPHICLASS TDBXIndexesIndex;
class DELPHICLASS TDBXMetaDataCollectionIndex;
class DELPHICLASS TDBXMetaDataCollectionName;
class DELPHICLASS TDBXPackageProcedureParametersColumns;
class DELPHICLASS TDBXPackageProcedureParametersIndex;
class DELPHICLASS TDBXPackageProceduresColumns;
class DELPHICLASS TDBXPackageProceduresIndex;
class DELPHICLASS TDBXPackagesColumns;
class DELPHICLASS TDBXPackagesIndex;
class DELPHICLASS TDBXPackageSourcesColumns;
class DELPHICLASS TDBXPackageSourcesIndex;
class DELPHICLASS TDBXProcedureParametersColumns;
class DELPHICLASS TDBXProcedureParametersIndex;
class DELPHICLASS TDBXProceduresColumns;
class DELPHICLASS TDBXProceduresIndex;
class DELPHICLASS TDBXProcedureSourcesColumns;
class DELPHICLASS TDBXProcedureSourcesIndex;
class DELPHICLASS TDBXReservedWordsColumns;
class DELPHICLASS TDBXReservedWordsIndex;
class DELPHICLASS TDBXRolesColumns;
class DELPHICLASS TDBXRolesIndex;
class DELPHICLASS TDBXSchemasColumns;
class DELPHICLASS TDBXSchemasIndex;
class DELPHICLASS TDBXSynonymsColumns;
class DELPHICLASS TDBXSynonymsIndex;
class DELPHICLASS TDBXTablesColumns;
class DELPHICLASS TDBXTablesIndex;
class DELPHICLASS TDBXUsersColumns;
class DELPHICLASS TDBXUsersIndex;
class DELPHICLASS TDBXViewsColumns;
class DELPHICLASS TDBXViewsIndex;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXCatalogsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXCatalogsColumns_CatalogName L"CatalogName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXCatalogsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCatalogsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXCatalogsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXCatalogsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCatalogsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnConstraintsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXColumnConstraintsColumns_CatalogName L"CatalogName"
	
	#define TDBXColumnConstraintsColumns_SchemaName L"SchemaName"
	
	#define TDBXColumnConstraintsColumns_TableName L"TableName"
	
	#define TDBXColumnConstraintsColumns_ConstraintName L"ConstraintName"
	
	#define TDBXColumnConstraintsColumns_ColumnName L"ColumnName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnConstraintsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnConstraintsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnConstraintsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 ConstraintName = System::Int8(0x3);
	
	static const System::Int8 ColumnName = System::Int8(0x4);
	
	static const System::Int8 Last = System::Int8(0x4);
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnConstraintsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnConstraintsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXColumnsColumns_CatalogName L"CatalogName"
	
	#define TDBXColumnsColumns_SchemaName L"SchemaName"
	
	#define TDBXColumnsColumns_TableName L"TableName"
	
	#define TDBXColumnsColumns_ColumnName L"ColumnName"
	
	#define TDBXColumnsColumns_TypeName L"TypeName"
	
	#define TDBXColumnsColumns_Precision L"Precision"
	
	#define TDBXColumnsColumns_Scale L"Scale"
	
	#define TDBXColumnsColumns_Ordinal L"Ordinal"
	
	#define TDBXColumnsColumns_DefaultValue L"DefaultValue"
	
	#define TDBXColumnsColumns_IsNullable L"IsNullable"
	
	#define TDBXColumnsColumns_IsAutoIncrement L"IsAutoIncrement"
	
	#define TDBXColumnsColumns_MaxInline L"MaxInline"
	
	#define TDBXColumnsColumns_DbxDataType L"DbxDataType"
	
	#define TDBXColumnsColumns_IsFixedLength L"IsFixedLength"
	
	#define TDBXColumnsColumns_IsUnicode L"IsUnicode"
	
	#define TDBXColumnsColumns_IsLong L"IsLong"
	
	#define TDBXColumnsColumns_IsUnsigned L"IsUnsigned"
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 ColumnName = System::Int8(0x3);
	
	static const System::Int8 TypeName = System::Int8(0x4);
	
	static const System::Int8 Precision = System::Int8(0x5);
	
	static const System::Int8 Scale = System::Int8(0x6);
	
	static const System::Int8 Ordinal = System::Int8(0x7);
	
	static const System::Int8 DefaultValue = System::Int8(0x8);
	
	static const System::Int8 IsNullable = System::Int8(0x9);
	
	static const System::Int8 IsAutoIncrement = System::Int8(0xa);
	
	static const System::Int8 MaxInline = System::Int8(0xb);
	
	static const System::Int8 DbxDataType = System::Int8(0xc);
	
	static const System::Int8 IsFixedLength = System::Int8(0xd);
	
	static const System::Int8 IsUnicode = System::Int8(0xe);
	
	static const System::Int8 IsLong = System::Int8(0xf);
	
	static const System::Int8 IsUnsigned = System::Int8(0x10);
	
	static const System::Int8 Last = System::Int8(0x10);
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataTypesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXDataTypesColumns_TypeName L"TypeName"
	
	#define TDBXDataTypesColumns_DbxDataType L"DbxDataType"
	
	#define TDBXDataTypesColumns_ColumnSize L"ColumnSize"
	
	#define TDBXDataTypesColumns_CreateFormat L"CreateFormat"
	
	#define TDBXDataTypesColumns_CreateParameters L"CreateParameters"
	
	#define TDBXDataTypesColumns_DataType L"DataType"
	
	#define TDBXDataTypesColumns_IsAutoIncrementable L"IsAutoIncrementable"
	
	#define TDBXDataTypesColumns_IsBestMatch L"IsBestMatch"
	
	#define TDBXDataTypesColumns_IsCaseSensitive L"IsCaseSensitive"
	
	#define TDBXDataTypesColumns_IsFixedLength L"IsFixedLength"
	
	#define TDBXDataTypesColumns_IsFixedPrecisionScale L"IsFixedPrecisionScale"
	
	#define TDBXDataTypesColumns_IsLong L"IsLong"
	
	#define TDBXDataTypesColumns_IsNullable L"IsNullable"
	
	#define TDBXDataTypesColumns_IsSearchable L"IsSearchable"
	
	#define TDBXDataTypesColumns_IsSearchableWithLike L"IsSearchableWithLike"
	
	#define TDBXDataTypesColumns_IsUnsigned L"IsUnsigned"
	
	#define TDBXDataTypesColumns_MaximumScale L"MaximumScale"
	
	#define TDBXDataTypesColumns_MinimumScale L"MinimumScale"
	
	#define TDBXDataTypesColumns_IsConcurrencyType L"IsConcurrencyType"
	
	#define TDBXDataTypesColumns_MaximumVersion L"MaximumVersion"
	
	#define TDBXDataTypesColumns_MinimumVersion L"MinimumVersion"
	
	#define TDBXDataTypesColumns_IsLiteralSupported L"IsLiteralSupported"
	
	#define TDBXDataTypesColumns_LiteralPrefix L"LiteralPrefix"
	
	#define TDBXDataTypesColumns_LiteralSuffix L"LiteralSuffix"
	
	#define TDBXDataTypesColumns_IsUnicode L"IsUnicode"
	
	#define TDBXDataTypesColumns_ProviderDbType L"ProviderDbType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXDataTypesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataTypesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDataTypesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 TypeName = System::Int8(0x0);
	
	static const System::Int8 DbxDataType = System::Int8(0x1);
	
	static const System::Int8 ColumnSize = System::Int8(0x2);
	
	static const System::Int8 CreateFormat = System::Int8(0x3);
	
	static const System::Int8 CreateParameters = System::Int8(0x4);
	
	static const System::Int8 DataType = System::Int8(0x5);
	
	static const System::Int8 IsAutoIncrementable = System::Int8(0x6);
	
	static const System::Int8 IsBestMatch = System::Int8(0x7);
	
	static const System::Int8 IsCaseSensitive = System::Int8(0x8);
	
	static const System::Int8 IsFixedLength = System::Int8(0x9);
	
	static const System::Int8 IsFixedPrecisionScale = System::Int8(0xa);
	
	static const System::Int8 IsLong = System::Int8(0xb);
	
	static const System::Int8 IsNullable = System::Int8(0xc);
	
	static const System::Int8 IsSearchable = System::Int8(0xd);
	
	static const System::Int8 IsSearchableWithLike = System::Int8(0xe);
	
	static const System::Int8 IsUnsigned = System::Int8(0xf);
	
	static const System::Int8 MaximumScale = System::Int8(0x10);
	
	static const System::Int8 MinimumScale = System::Int8(0x11);
	
	static const System::Int8 IsConcurrencyType = System::Int8(0x12);
	
	static const System::Int8 MaximumVersion = System::Int8(0x13);
	
	static const System::Int8 MinimumVersion = System::Int8(0x14);
	
	static const System::Int8 IsLiteralSupported = System::Int8(0x15);
	
	static const System::Int8 LiteralPrefix = System::Int8(0x16);
	
	static const System::Int8 LiteralSuffix = System::Int8(0x17);
	
	static const System::Int8 IsUnicode = System::Int8(0x18);
	
	static const System::Int8 ProviderDbType = System::Int8(0x19);
	
	static const System::Int8 Last = System::Int8(0x19);
	
public:
	/* TObject.Create */ inline __fastcall TDBXDataTypesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataTypesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXForeignKeyColumnsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXForeignKeyColumnsColumns_CatalogName L"CatalogName"
	
	#define TDBXForeignKeyColumnsColumns_SchemaName L"SchemaName"
	
	#define TDBXForeignKeyColumnsColumns_TableName L"TableName"
	
	#define TDBXForeignKeyColumnsColumns_ForeignKeyName L"ForeignKeyName"
	
	#define TDBXForeignKeyColumnsColumns_ColumnName L"ColumnName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryCatalogName L"PrimaryCatalogName"
	
	#define TDBXForeignKeyColumnsColumns_PrimarySchemaName L"PrimarySchemaName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryTableName L"PrimaryTableName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryKeyName L"PrimaryKeyName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryColumnName L"PrimaryColumnName"
	
	#define TDBXForeignKeyColumnsColumns_Ordinal L"Ordinal"
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeyColumnsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeyColumnsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXForeignKeyColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 ForeignKeyName = System::Int8(0x3);
	
	static const System::Int8 ColumnName = System::Int8(0x4);
	
	static const System::Int8 PrimaryCatalogName = System::Int8(0x5);
	
	static const System::Int8 PrimarySchemaName = System::Int8(0x6);
	
	static const System::Int8 PrimaryTableName = System::Int8(0x7);
	
	static const System::Int8 PrimaryKeyName = System::Int8(0x8);
	
	static const System::Int8 PrimaryColumnName = System::Int8(0x9);
	
	static const System::Int8 Ordinal = System::Int8(0xa);
	
	static const System::Int8 Last = System::Int8(0xa);
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeyColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeyColumnsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXForeignKeysColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXForeignKeysColumns_CatalogName L"CatalogName"
	
	#define TDBXForeignKeysColumns_SchemaName L"SchemaName"
	
	#define TDBXForeignKeysColumns_TableName L"TableName"
	
	#define TDBXForeignKeysColumns_ForeignKeyName L"ForeignKeyName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeysColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeysColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXForeignKeysIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 ForeignKeyName = System::Int8(0x3);
	
	static const System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeysIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeysIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIndexColumnsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXIndexColumnsColumns_CatalogName L"CatalogName"
	
	#define TDBXIndexColumnsColumns_SchemaName L"SchemaName"
	
	#define TDBXIndexColumnsColumns_TableName L"TableName"
	
	#define TDBXIndexColumnsColumns_IndexName L"IndexName"
	
	#define TDBXIndexColumnsColumns_ColumnName L"ColumnName"
	
	#define TDBXIndexColumnsColumns_Ordinal L"Ordinal"
	
	#define TDBXIndexColumnsColumns_IsAscending L"IsAscending"
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexColumnsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexColumnsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIndexColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 IndexName = System::Int8(0x3);
	
	static const System::Int8 ColumnName = System::Int8(0x4);
	
	static const System::Int8 Ordinal = System::Int8(0x5);
	
	static const System::Int8 IsAscending = System::Int8(0x6);
	
	static const System::Int8 Last = System::Int8(0x6);
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexColumnsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIndexesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXIndexesColumns_CatalogName L"CatalogName"
	
	#define TDBXIndexesColumns_SchemaName L"SchemaName"
	
	#define TDBXIndexesColumns_TableName L"TableName"
	
	#define TDBXIndexesColumns_IndexName L"IndexName"
	
	#define TDBXIndexesColumns_ConstraintName L"ConstraintName"
	
	#define TDBXIndexesColumns_IsPrimary L"IsPrimary"
	
	#define TDBXIndexesColumns_IsUnique L"IsUnique"
	
	#define TDBXIndexesColumns_IsAscending L"IsAscending"
	
	#define TDBXIndexesColumns_IndexQualifier L"IndexQualifier"
	
	#define TDBXIndexesColumns_TypeName L"Type"
	
	#define TDBXIndexesColumns_OrdinalPosition L"OrdinalPosition"
	
	#define TDBXIndexesColumns_ColumnName L"ColumnName"
	
	#define TDBXIndexesColumns_AscDesc L"AscDesc"
	
	#define TDBXIndexesColumns_Cardinality L"Cardinality"
	
	#define TDBXIndexesColumns_Pages L"Pages"
	
	#define TDBXIndexesColumns_FilterCondition L"FilterCondition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXIndexesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 IndexName = System::Int8(0x3);
	
	static const System::Int8 ConstraintName = System::Int8(0x4);
	
	static const System::Int8 IsPrimary = System::Int8(0x5);
	
	static const System::Int8 IsUnique = System::Int8(0x6);
	
	static const System::Int8 IsAscending = System::Int8(0x7);
	
	static const System::Int8 Last = System::Int8(0x7);
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMetaDataCollectionIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 DataTypes = System::Int8(0x1);
	
	static const System::Int8 Catalogs = System::Int8(0x2);
	
	static const System::Int8 Schemas = System::Int8(0x3);
	
	static const System::Int8 Tables = System::Int8(0x4);
	
	static const System::Int8 Views = System::Int8(0x5);
	
	static const System::Int8 Synonyms = System::Int8(0x6);
	
	static const System::Int8 Columns = System::Int8(0x7);
	
	static const System::Int8 ColumnConstraints = System::Int8(0x8);
	
	static const System::Int8 Indexes = System::Int8(0x9);
	
	static const System::Int8 IndexColumns = System::Int8(0xa);
	
	static const System::Int8 ForeignKeys = System::Int8(0xb);
	
	static const System::Int8 ForeignKeyColumns = System::Int8(0xc);
	
	static const System::Int8 Procedures = System::Int8(0xd);
	
	static const System::Int8 ProcedureSources = System::Int8(0xe);
	
	static const System::Int8 ProcedureParameters = System::Int8(0xf);
	
	static const System::Int8 Packages = System::Int8(0x10);
	
	static const System::Int8 PackageProcedures = System::Int8(0x11);
	
	static const System::Int8 PackageProcedureParameters = System::Int8(0x12);
	
	static const System::Int8 PackageSources = System::Int8(0x13);
	
	static const System::Int8 Users = System::Int8(0x14);
	
	static const System::Int8 Roles = System::Int8(0x15);
	
	static const System::Int8 ReservedWords = System::Int8(0x16);
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCollectionIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCollectionIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMetaDataCollectionName : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDataCollectionName_DataTypes L"DataTypes"
	
	#define TDBXMetaDataCollectionName_Catalogs L"Catalogs"
	
	#define TDBXMetaDataCollectionName_Schemas L"Schemas"
	
	#define TDBXMetaDataCollectionName_Tables L"Tables"
	
	#define TDBXMetaDataCollectionName_Views L"Views"
	
	#define TDBXMetaDataCollectionName_Synonyms L"Synonyms"
	
	#define TDBXMetaDataCollectionName_Columns L"Columns"
	
	#define TDBXMetaDataCollectionName_ColumnConstraints L"ColumnConstraints"
	
	#define TDBXMetaDataCollectionName_Indexes L"Indexes"
	
	#define TDBXMetaDataCollectionName_IndexColumns L"IndexColumns"
	
	#define TDBXMetaDataCollectionName_ForeignKeys L"ForeignKeys"
	
	#define TDBXMetaDataCollectionName_ForeignKeyColumns L"ForeignKeyColumns"
	
	#define TDBXMetaDataCollectionName_Procedures L"Procedures"
	
	#define TDBXMetaDataCollectionName_ProcedureSources L"ProcedureSources"
	
	#define TDBXMetaDataCollectionName_ProcedureParameters L"ProcedureParameters"
	
	#define TDBXMetaDataCollectionName_Packages L"Packages"
	
	#define TDBXMetaDataCollectionName_PackageProcedures L"PackageProcedures"
	
	#define TDBXMetaDataCollectionName_PackageProcedureParameters L"PackageProcedureParameters"
	
	#define TDBXMetaDataCollectionName_PackageSources L"PackageSources"
	
	#define TDBXMetaDataCollectionName_Users L"Users"
	
	#define TDBXMetaDataCollectionName_Roles L"Roles"
	
	#define TDBXMetaDataCollectionName_ReservedWords L"ReservedWords"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCollectionName() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCollectionName() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageProcedureParametersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackageProcedureParametersColumns_CatalogName L"CatalogName"
	
	#define TDBXPackageProcedureParametersColumns_SchemaName L"SchemaName"
	
	#define TDBXPackageProcedureParametersColumns_PackageName L"PackageName"
	
	#define TDBXPackageProcedureParametersColumns_ProcedureName L"ProcedureName"
	
	#define TDBXPackageProcedureParametersColumns_ParameterName L"ParameterName"
	
	#define TDBXPackageProcedureParametersColumns_ParameterMode L"ParameterMode"
	
	#define TDBXPackageProcedureParametersColumns_TypeName L"TypeName"
	
	#define TDBXPackageProcedureParametersColumns_Precision L"Precision"
	
	#define TDBXPackageProcedureParametersColumns_Scale L"Scale"
	
	#define TDBXPackageProcedureParametersColumns_Ordinal L"Ordinal"
	
	#define TDBXPackageProcedureParametersColumns_IsNullable L"IsNullable"
	
	#define TDBXPackageProcedureParametersColumns_DbxDataType L"DbxDataType"
	
	#define TDBXPackageProcedureParametersColumns_IsFixedLength L"IsFixedLength"
	
	#define TDBXPackageProcedureParametersColumns_IsUnicode L"IsUnicode"
	
	#define TDBXPackageProcedureParametersColumns_IsLong L"IsLong"
	
	#define TDBXPackageProcedureParametersColumns_IsUnsigned L"IsUnsigned"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProcedureParametersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProcedureParametersColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageProcedureParametersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 PackageName = System::Int8(0x2);
	
	static const System::Int8 ProcedureName = System::Int8(0x3);
	
	static const System::Int8 ParameterName = System::Int8(0x4);
	
	static const System::Int8 ParameterMode = System::Int8(0x5);
	
	static const System::Int8 TypeName = System::Int8(0x6);
	
	static const System::Int8 Precision = System::Int8(0x7);
	
	static const System::Int8 Scale = System::Int8(0x8);
	
	static const System::Int8 Ordinal = System::Int8(0x9);
	
	static const System::Int8 IsNullable = System::Int8(0xa);
	
	static const System::Int8 DbxDataType = System::Int8(0xb);
	
	static const System::Int8 IsFixedLength = System::Int8(0xc);
	
	static const System::Int8 IsUnicode = System::Int8(0xd);
	
	static const System::Int8 IsLong = System::Int8(0xe);
	
	static const System::Int8 IsUnsigned = System::Int8(0xf);
	
	static const System::Int8 Last = System::Int8(0xf);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProcedureParametersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProcedureParametersIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageProceduresColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackageProceduresColumns_CatalogName L"CatalogName"
	
	#define TDBXPackageProceduresColumns_SchemaName L"SchemaName"
	
	#define TDBXPackageProceduresColumns_PackageName L"PackageName"
	
	#define TDBXPackageProceduresColumns_ProcedureName L"ProcedureName"
	
	#define TDBXPackageProceduresColumns_ProcedureType L"ProcedureType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProceduresColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProceduresColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageProceduresIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 PackageName = System::Int8(0x2);
	
	static const System::Int8 ProcedureName = System::Int8(0x3);
	
	static const System::Int8 ProcedureType = System::Int8(0x4);
	
	static const System::Int8 Last = System::Int8(0x4);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProceduresIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProceduresIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackagesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackagesColumns_CatalogName L"CatalogName"
	
	#define TDBXPackagesColumns_SchemaName L"SchemaName"
	
	#define TDBXPackagesColumns_PackageName L"PackageName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackagesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackagesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackagesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 PackageName = System::Int8(0x2);
	
	static const System::Int8 Last = System::Int8(0x2);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackagesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackagesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageSourcesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackageSourcesColumns_CatalogName L"CatalogName"
	
	#define TDBXPackageSourcesColumns_SchemaName L"SchemaName"
	
	#define TDBXPackageSourcesColumns_PackageName L"PackageName"
	
	#define TDBXPackageSourcesColumns_Definition L"Definition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageSourcesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageSourcesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPackageSourcesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 PackageName = System::Int8(0x2);
	
	static const System::Int8 Definition = System::Int8(0x3);
	
	static const System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageSourcesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageSourcesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProcedureParametersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProcedureParametersColumns_CatalogName L"CatalogName"
	
	#define TDBXProcedureParametersColumns_SchemaName L"SchemaName"
	
	#define TDBXProcedureParametersColumns_ProcedureName L"ProcedureName"
	
	#define TDBXProcedureParametersColumns_ParameterName L"ParameterName"
	
	#define TDBXProcedureParametersColumns_ParameterMode L"ParameterMode"
	
	#define TDBXProcedureParametersColumns_TypeName L"TypeName"
	
	#define TDBXProcedureParametersColumns_Precision L"Precision"
	
	#define TDBXProcedureParametersColumns_Scale L"Scale"
	
	#define TDBXProcedureParametersColumns_Ordinal L"Ordinal"
	
	#define TDBXProcedureParametersColumns_IsNullable L"IsNullable"
	
	#define TDBXProcedureParametersColumns_DbxDataType L"DbxDataType"
	
	#define TDBXProcedureParametersColumns_IsFixedLength L"IsFixedLength"
	
	#define TDBXProcedureParametersColumns_IsUnicode L"IsUnicode"
	
	#define TDBXProcedureParametersColumns_IsLong L"IsLong"
	
	#define TDBXProcedureParametersColumns_IsUnsigned L"IsUnsigned"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureParametersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureParametersColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProcedureParametersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 ProcedureName = System::Int8(0x2);
	
	static const System::Int8 ParameterName = System::Int8(0x3);
	
	static const System::Int8 ParameterMode = System::Int8(0x4);
	
	static const System::Int8 TypeName = System::Int8(0x5);
	
	static const System::Int8 Precision = System::Int8(0x6);
	
	static const System::Int8 Scale = System::Int8(0x7);
	
	static const System::Int8 Ordinal = System::Int8(0x8);
	
	static const System::Int8 IsNullable = System::Int8(0x9);
	
	static const System::Int8 DbxDataType = System::Int8(0xa);
	
	static const System::Int8 IsFixedLength = System::Int8(0xb);
	
	static const System::Int8 IsUnicode = System::Int8(0xc);
	
	static const System::Int8 IsLong = System::Int8(0xd);
	
	static const System::Int8 IsUnsigned = System::Int8(0xe);
	
	static const System::Int8 Last = System::Int8(0xe);
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureParametersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureParametersIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProceduresColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProceduresColumns_CatalogName L"CatalogName"
	
	#define TDBXProceduresColumns_SchemaName L"SchemaName"
	
	#define TDBXProceduresColumns_ProcedureName L"ProcedureName"
	
	#define TDBXProceduresColumns_ProcedureType L"ProcedureType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProceduresColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProceduresColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProceduresIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 ProcedureName = System::Int8(0x2);
	
	static const System::Int8 ProcedureType = System::Int8(0x3);
	
	static const System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXProceduresIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProceduresIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProcedureSourcesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProcedureSourcesColumns_CatalogName L"CatalogName"
	
	#define TDBXProcedureSourcesColumns_SchemaName L"SchemaName"
	
	#define TDBXProcedureSourcesColumns_ProcedureName L"ProcedureName"
	
	#define TDBXProcedureSourcesColumns_ProcedureType L"ProcedureType"
	
	#define TDBXProcedureSourcesColumns_Definition L"Definition"
	
	#define TDBXProcedureSourcesColumns_ExternalDefinition L"ExternalDefinition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureSourcesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureSourcesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXProcedureSourcesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 ProcedureName = System::Int8(0x2);
	
	static const System::Int8 ProcedureType = System::Int8(0x3);
	
	static const System::Int8 Definition = System::Int8(0x4);
	
	static const System::Int8 ExternalDefinition = System::Int8(0x5);
	
	static const System::Int8 Last = System::Int8(0x5);
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureSourcesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureSourcesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXReservedWordsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXReservedWordsColumns_ReservedWord L"ReservedWord"
	
public:
	/* TObject.Create */ inline __fastcall TDBXReservedWordsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXReservedWordsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXReservedWordsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 ReservedWord = System::Int8(0x0);
	
	static const System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXReservedWordsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXReservedWordsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXRolesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXRolesColumns_RoleName L"RoleName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXRolesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXRolesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXRolesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 RoleName = System::Int8(0x0);
	
	static const System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXRolesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXRolesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSchemasColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXSchemasColumns_CatalogName L"CatalogName"
	
	#define TDBXSchemasColumns_SchemaName L"SchemaName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXSchemasColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSchemasColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSchemasIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 Last = System::Int8(0x1);
	
public:
	/* TObject.Create */ inline __fastcall TDBXSchemasIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSchemasIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSynonymsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXSynonymsColumns_CatalogName L"CatalogName"
	
	#define TDBXSynonymsColumns_SchemaName L"SchemaName"
	
	#define TDBXSynonymsColumns_SynonymName L"SynonymName"
	
	#define TDBXSynonymsColumns_TableCatalogName L"TableCatalogName"
	
	#define TDBXSynonymsColumns_TableSchemaName L"TableSchemaName"
	
	#define TDBXSynonymsColumns_TableName L"TableName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXSynonymsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSynonymsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSynonymsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 SynonymName = System::Int8(0x2);
	
	static const System::Int8 TableCatalogName = System::Int8(0x3);
	
	static const System::Int8 TableSchemaName = System::Int8(0x4);
	
	static const System::Int8 TableName = System::Int8(0x5);
	
	static const System::Int8 Last = System::Int8(0x5);
	
public:
	/* TObject.Create */ inline __fastcall TDBXSynonymsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSynonymsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTablesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXTablesColumns_CatalogName L"CatalogName"
	
	#define TDBXTablesColumns_SchemaName L"SchemaName"
	
	#define TDBXTablesColumns_TableName L"TableName"
	
	#define TDBXTablesColumns_TableType L"TableType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXTablesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTablesColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTablesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 TableName = System::Int8(0x2);
	
	static const System::Int8 TableType = System::Int8(0x3);
	
	static const System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTablesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTablesIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXUsersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXUsersColumns_UserName L"UserName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXUsersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUsersColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXUsersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 UserName = System::Int8(0x0);
	
	static const System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXUsersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUsersIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXViewsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXViewsColumns_CatalogName L"CatalogName"
	
	#define TDBXViewsColumns_SchemaName L"SchemaName"
	
	#define TDBXViewsColumns_ViewName L"ViewName"
	
	#define TDBXViewsColumns_Definition L"Definition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXViewsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXViewsColumns() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXViewsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Int8 CatalogName = System::Int8(0x0);
	
	static const System::Int8 SchemaName = System::Int8(0x1);
	
	static const System::Int8 ViewName = System::Int8(0x2);
	
	static const System::Int8 Definition = System::Int8(0x3);
	
	static const System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXViewsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXViewsIndex() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadatanames */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATANAMES)
using namespace Data::Dbxmetadatanames;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatanamesHPP
