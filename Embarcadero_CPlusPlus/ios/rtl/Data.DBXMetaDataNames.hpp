// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetaDataNames.pas' rev: 34.00 (iOS)

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
class PASCALIMPLEMENTATION TDBXCatalogsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXCatalogsColumns_CatalogName u"CatalogName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXCatalogsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCatalogsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXCatalogsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXCatalogsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXCatalogsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXColumnConstraintsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXColumnConstraintsColumns_CatalogName u"CatalogName"
	
	#define TDBXColumnConstraintsColumns_SchemaName u"SchemaName"
	
	#define TDBXColumnConstraintsColumns_TableName u"TableName"
	
	#define TDBXColumnConstraintsColumns_ConstraintName u"ConstraintName"
	
	#define TDBXColumnConstraintsColumns_ColumnName u"ColumnName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnConstraintsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnConstraintsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXColumnConstraintsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 ConstraintName = System::Int8(0x3);
	
	static constexpr System::Int8 ColumnName = System::Int8(0x4);
	
	static constexpr System::Int8 Last = System::Int8(0x4);
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnConstraintsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnConstraintsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXColumnsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXColumnsColumns_CatalogName u"CatalogName"
	
	#define TDBXColumnsColumns_SchemaName u"SchemaName"
	
	#define TDBXColumnsColumns_TableName u"TableName"
	
	#define TDBXColumnsColumns_ColumnName u"ColumnName"
	
	#define TDBXColumnsColumns_TypeName u"TypeName"
	
	#define TDBXColumnsColumns_Precision u"Precision"
	
	#define TDBXColumnsColumns_Scale u"Scale"
	
	#define TDBXColumnsColumns_Ordinal u"Ordinal"
	
	#define TDBXColumnsColumns_DefaultValue u"DefaultValue"
	
	#define TDBXColumnsColumns_IsNullable u"IsNullable"
	
	#define TDBXColumnsColumns_IsAutoIncrement u"IsAutoIncrement"
	
	#define TDBXColumnsColumns_MaxInline u"MaxInline"
	
	#define TDBXColumnsColumns_DbxDataType u"DbxDataType"
	
	#define TDBXColumnsColumns_IsFixedLength u"IsFixedLength"
	
	#define TDBXColumnsColumns_IsUnicode u"IsUnicode"
	
	#define TDBXColumnsColumns_IsLong u"IsLong"
	
	#define TDBXColumnsColumns_IsUnsigned u"IsUnsigned"
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 ColumnName = System::Int8(0x3);
	
	static constexpr System::Int8 TypeName = System::Int8(0x4);
	
	static constexpr System::Int8 Precision = System::Int8(0x5);
	
	static constexpr System::Int8 Scale = System::Int8(0x6);
	
	static constexpr System::Int8 Ordinal = System::Int8(0x7);
	
	static constexpr System::Int8 DefaultValue = System::Int8(0x8);
	
	static constexpr System::Int8 IsNullable = System::Int8(0x9);
	
	static constexpr System::Int8 IsAutoIncrement = System::Int8(0xa);
	
	static constexpr System::Int8 MaxInline = System::Int8(0xb);
	
	static constexpr System::Int8 DbxDataType = System::Int8(0xc);
	
	static constexpr System::Int8 IsFixedLength = System::Int8(0xd);
	
	static constexpr System::Int8 IsUnicode = System::Int8(0xe);
	
	static constexpr System::Int8 IsLong = System::Int8(0xf);
	
	static constexpr System::Int8 IsUnsigned = System::Int8(0x10);
	
	static constexpr System::Int8 Last = System::Int8(0x10);
	
public:
	/* TObject.Create */ inline __fastcall TDBXColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXColumnsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXDataTypesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXDataTypesColumns_TypeName u"TypeName"
	
	#define TDBXDataTypesColumns_DbxDataType u"DbxDataType"
	
	#define TDBXDataTypesColumns_ColumnSize u"ColumnSize"
	
	#define TDBXDataTypesColumns_CreateFormat u"CreateFormat"
	
	#define TDBXDataTypesColumns_CreateParameters u"CreateParameters"
	
	#define TDBXDataTypesColumns_DataType u"DataType"
	
	#define TDBXDataTypesColumns_IsAutoIncrementable u"IsAutoIncrementable"
	
	#define TDBXDataTypesColumns_IsBestMatch u"IsBestMatch"
	
	#define TDBXDataTypesColumns_IsCaseSensitive u"IsCaseSensitive"
	
	#define TDBXDataTypesColumns_IsFixedLength u"IsFixedLength"
	
	#define TDBXDataTypesColumns_IsFixedPrecisionScale u"IsFixedPrecisionScale"
	
	#define TDBXDataTypesColumns_IsLong u"IsLong"
	
	#define TDBXDataTypesColumns_IsNullable u"IsNullable"
	
	#define TDBXDataTypesColumns_IsSearchable u"IsSearchable"
	
	#define TDBXDataTypesColumns_IsSearchableWithLike u"IsSearchableWithLike"
	
	#define TDBXDataTypesColumns_IsUnsigned u"IsUnsigned"
	
	#define TDBXDataTypesColumns_MaximumScale u"MaximumScale"
	
	#define TDBXDataTypesColumns_MinimumScale u"MinimumScale"
	
	#define TDBXDataTypesColumns_IsConcurrencyType u"IsConcurrencyType"
	
	#define TDBXDataTypesColumns_MaximumVersion u"MaximumVersion"
	
	#define TDBXDataTypesColumns_MinimumVersion u"MinimumVersion"
	
	#define TDBXDataTypesColumns_IsLiteralSupported u"IsLiteralSupported"
	
	#define TDBXDataTypesColumns_LiteralPrefix u"LiteralPrefix"
	
	#define TDBXDataTypesColumns_LiteralSuffix u"LiteralSuffix"
	
	#define TDBXDataTypesColumns_IsUnicode u"IsUnicode"
	
	#define TDBXDataTypesColumns_ProviderDbType u"ProviderDbType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXDataTypesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataTypesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXDataTypesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 TypeName = System::Int8(0x0);
	
	static constexpr System::Int8 DbxDataType = System::Int8(0x1);
	
	static constexpr System::Int8 ColumnSize = System::Int8(0x2);
	
	static constexpr System::Int8 CreateFormat = System::Int8(0x3);
	
	static constexpr System::Int8 CreateParameters = System::Int8(0x4);
	
	static constexpr System::Int8 DataType = System::Int8(0x5);
	
	static constexpr System::Int8 IsAutoIncrementable = System::Int8(0x6);
	
	static constexpr System::Int8 IsBestMatch = System::Int8(0x7);
	
	static constexpr System::Int8 IsCaseSensitive = System::Int8(0x8);
	
	static constexpr System::Int8 IsFixedLength = System::Int8(0x9);
	
	static constexpr System::Int8 IsFixedPrecisionScale = System::Int8(0xa);
	
	static constexpr System::Int8 IsLong = System::Int8(0xb);
	
	static constexpr System::Int8 IsNullable = System::Int8(0xc);
	
	static constexpr System::Int8 IsSearchable = System::Int8(0xd);
	
	static constexpr System::Int8 IsSearchableWithLike = System::Int8(0xe);
	
	static constexpr System::Int8 IsUnsigned = System::Int8(0xf);
	
	static constexpr System::Int8 MaximumScale = System::Int8(0x10);
	
	static constexpr System::Int8 MinimumScale = System::Int8(0x11);
	
	static constexpr System::Int8 IsConcurrencyType = System::Int8(0x12);
	
	static constexpr System::Int8 MaximumVersion = System::Int8(0x13);
	
	static constexpr System::Int8 MinimumVersion = System::Int8(0x14);
	
	static constexpr System::Int8 IsLiteralSupported = System::Int8(0x15);
	
	static constexpr System::Int8 LiteralPrefix = System::Int8(0x16);
	
	static constexpr System::Int8 LiteralSuffix = System::Int8(0x17);
	
	static constexpr System::Int8 IsUnicode = System::Int8(0x18);
	
	static constexpr System::Int8 ProviderDbType = System::Int8(0x19);
	
	static constexpr System::Int8 Last = System::Int8(0x19);
	
public:
	/* TObject.Create */ inline __fastcall TDBXDataTypesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDataTypesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXForeignKeyColumnsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXForeignKeyColumnsColumns_CatalogName u"CatalogName"
	
	#define TDBXForeignKeyColumnsColumns_SchemaName u"SchemaName"
	
	#define TDBXForeignKeyColumnsColumns_TableName u"TableName"
	
	#define TDBXForeignKeyColumnsColumns_ForeignKeyName u"ForeignKeyName"
	
	#define TDBXForeignKeyColumnsColumns_ColumnName u"ColumnName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryCatalogName u"PrimaryCatalogName"
	
	#define TDBXForeignKeyColumnsColumns_PrimarySchemaName u"PrimarySchemaName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryTableName u"PrimaryTableName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryKeyName u"PrimaryKeyName"
	
	#define TDBXForeignKeyColumnsColumns_PrimaryColumnName u"PrimaryColumnName"
	
	#define TDBXForeignKeyColumnsColumns_Ordinal u"Ordinal"
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeyColumnsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeyColumnsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXForeignKeyColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 ForeignKeyName = System::Int8(0x3);
	
	static constexpr System::Int8 ColumnName = System::Int8(0x4);
	
	static constexpr System::Int8 PrimaryCatalogName = System::Int8(0x5);
	
	static constexpr System::Int8 PrimarySchemaName = System::Int8(0x6);
	
	static constexpr System::Int8 PrimaryTableName = System::Int8(0x7);
	
	static constexpr System::Int8 PrimaryKeyName = System::Int8(0x8);
	
	static constexpr System::Int8 PrimaryColumnName = System::Int8(0x9);
	
	static constexpr System::Int8 Ordinal = System::Int8(0xa);
	
	static constexpr System::Int8 Last = System::Int8(0xa);
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeyColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeyColumnsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXForeignKeysColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXForeignKeysColumns_CatalogName u"CatalogName"
	
	#define TDBXForeignKeysColumns_SchemaName u"SchemaName"
	
	#define TDBXForeignKeysColumns_TableName u"TableName"
	
	#define TDBXForeignKeysColumns_ForeignKeyName u"ForeignKeyName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeysColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeysColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXForeignKeysIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 ForeignKeyName = System::Int8(0x3);
	
	static constexpr System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXForeignKeysIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXForeignKeysIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXIndexColumnsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXIndexColumnsColumns_CatalogName u"CatalogName"
	
	#define TDBXIndexColumnsColumns_SchemaName u"SchemaName"
	
	#define TDBXIndexColumnsColumns_TableName u"TableName"
	
	#define TDBXIndexColumnsColumns_IndexName u"IndexName"
	
	#define TDBXIndexColumnsColumns_ColumnName u"ColumnName"
	
	#define TDBXIndexColumnsColumns_Ordinal u"Ordinal"
	
	#define TDBXIndexColumnsColumns_IsAscending u"IsAscending"
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexColumnsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexColumnsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXIndexColumnsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 IndexName = System::Int8(0x3);
	
	static constexpr System::Int8 ColumnName = System::Int8(0x4);
	
	static constexpr System::Int8 Ordinal = System::Int8(0x5);
	
	static constexpr System::Int8 IsAscending = System::Int8(0x6);
	
	static constexpr System::Int8 Last = System::Int8(0x6);
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexColumnsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexColumnsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXIndexesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXIndexesColumns_CatalogName u"CatalogName"
	
	#define TDBXIndexesColumns_SchemaName u"SchemaName"
	
	#define TDBXIndexesColumns_TableName u"TableName"
	
	#define TDBXIndexesColumns_IndexName u"IndexName"
	
	#define TDBXIndexesColumns_ConstraintName u"ConstraintName"
	
	#define TDBXIndexesColumns_IsPrimary u"IsPrimary"
	
	#define TDBXIndexesColumns_IsUnique u"IsUnique"
	
	#define TDBXIndexesColumns_IsAscending u"IsAscending"
	
	#define TDBXIndexesColumns_IndexQualifier u"IndexQualifier"
	
	#define TDBXIndexesColumns_TypeName u"Type"
	
	#define TDBXIndexesColumns_OrdinalPosition u"OrdinalPosition"
	
	#define TDBXIndexesColumns_ColumnName u"ColumnName"
	
	#define TDBXIndexesColumns_AscDesc u"AscDesc"
	
	#define TDBXIndexesColumns_Cardinality u"Cardinality"
	
	#define TDBXIndexesColumns_Pages u"Pages"
	
	#define TDBXIndexesColumns_FilterCondition u"FilterCondition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXIndexesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 IndexName = System::Int8(0x3);
	
	static constexpr System::Int8 ConstraintName = System::Int8(0x4);
	
	static constexpr System::Int8 IsPrimary = System::Int8(0x5);
	
	static constexpr System::Int8 IsUnique = System::Int8(0x6);
	
	static constexpr System::Int8 IsAscending = System::Int8(0x7);
	
	static constexpr System::Int8 Last = System::Int8(0x7);
	
public:
	/* TObject.Create */ inline __fastcall TDBXIndexesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXIndexesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXMetaDataCollectionIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 DataTypes = System::Int8(0x1);
	
	static constexpr System::Int8 Catalogs = System::Int8(0x2);
	
	static constexpr System::Int8 Schemas = System::Int8(0x3);
	
	static constexpr System::Int8 Tables = System::Int8(0x4);
	
	static constexpr System::Int8 Views = System::Int8(0x5);
	
	static constexpr System::Int8 Synonyms = System::Int8(0x6);
	
	static constexpr System::Int8 Columns = System::Int8(0x7);
	
	static constexpr System::Int8 ColumnConstraints = System::Int8(0x8);
	
	static constexpr System::Int8 Indexes = System::Int8(0x9);
	
	static constexpr System::Int8 IndexColumns = System::Int8(0xa);
	
	static constexpr System::Int8 ForeignKeys = System::Int8(0xb);
	
	static constexpr System::Int8 ForeignKeyColumns = System::Int8(0xc);
	
	static constexpr System::Int8 Procedures = System::Int8(0xd);
	
	static constexpr System::Int8 ProcedureSources = System::Int8(0xe);
	
	static constexpr System::Int8 ProcedureParameters = System::Int8(0xf);
	
	static constexpr System::Int8 Packages = System::Int8(0x10);
	
	static constexpr System::Int8 PackageProcedures = System::Int8(0x11);
	
	static constexpr System::Int8 PackageProcedureParameters = System::Int8(0x12);
	
	static constexpr System::Int8 PackageSources = System::Int8(0x13);
	
	static constexpr System::Int8 Users = System::Int8(0x14);
	
	static constexpr System::Int8 Roles = System::Int8(0x15);
	
	static constexpr System::Int8 ReservedWords = System::Int8(0x16);
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCollectionIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCollectionIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXMetaDataCollectionName : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXMetaDataCollectionName_DataTypes u"DataTypes"
	
	#define TDBXMetaDataCollectionName_Catalogs u"Catalogs"
	
	#define TDBXMetaDataCollectionName_Schemas u"Schemas"
	
	#define TDBXMetaDataCollectionName_Tables u"Tables"
	
	#define TDBXMetaDataCollectionName_Views u"Views"
	
	#define TDBXMetaDataCollectionName_Synonyms u"Synonyms"
	
	#define TDBXMetaDataCollectionName_Columns u"Columns"
	
	#define TDBXMetaDataCollectionName_ColumnConstraints u"ColumnConstraints"
	
	#define TDBXMetaDataCollectionName_Indexes u"Indexes"
	
	#define TDBXMetaDataCollectionName_IndexColumns u"IndexColumns"
	
	#define TDBXMetaDataCollectionName_ForeignKeys u"ForeignKeys"
	
	#define TDBXMetaDataCollectionName_ForeignKeyColumns u"ForeignKeyColumns"
	
	#define TDBXMetaDataCollectionName_Procedures u"Procedures"
	
	#define TDBXMetaDataCollectionName_ProcedureSources u"ProcedureSources"
	
	#define TDBXMetaDataCollectionName_ProcedureParameters u"ProcedureParameters"
	
	#define TDBXMetaDataCollectionName_Packages u"Packages"
	
	#define TDBXMetaDataCollectionName_PackageProcedures u"PackageProcedures"
	
	#define TDBXMetaDataCollectionName_PackageProcedureParameters u"PackageProcedureParameters"
	
	#define TDBXMetaDataCollectionName_PackageSources u"PackageSources"
	
	#define TDBXMetaDataCollectionName_Users u"Users"
	
	#define TDBXMetaDataCollectionName_Roles u"Roles"
	
	#define TDBXMetaDataCollectionName_ReservedWords u"ReservedWords"
	
public:
	/* TObject.Create */ inline __fastcall TDBXMetaDataCollectionName() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXMetaDataCollectionName() { }
	
};


class PASCALIMPLEMENTATION TDBXPackageProcedureParametersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackageProcedureParametersColumns_CatalogName u"CatalogName"
	
	#define TDBXPackageProcedureParametersColumns_SchemaName u"SchemaName"
	
	#define TDBXPackageProcedureParametersColumns_PackageName u"PackageName"
	
	#define TDBXPackageProcedureParametersColumns_ProcedureName u"ProcedureName"
	
	#define TDBXPackageProcedureParametersColumns_ParameterName u"ParameterName"
	
	#define TDBXPackageProcedureParametersColumns_ParameterMode u"ParameterMode"
	
	#define TDBXPackageProcedureParametersColumns_TypeName u"TypeName"
	
	#define TDBXPackageProcedureParametersColumns_Precision u"Precision"
	
	#define TDBXPackageProcedureParametersColumns_Scale u"Scale"
	
	#define TDBXPackageProcedureParametersColumns_Ordinal u"Ordinal"
	
	#define TDBXPackageProcedureParametersColumns_IsNullable u"IsNullable"
	
	#define TDBXPackageProcedureParametersColumns_DbxDataType u"DbxDataType"
	
	#define TDBXPackageProcedureParametersColumns_IsFixedLength u"IsFixedLength"
	
	#define TDBXPackageProcedureParametersColumns_IsUnicode u"IsUnicode"
	
	#define TDBXPackageProcedureParametersColumns_IsLong u"IsLong"
	
	#define TDBXPackageProcedureParametersColumns_IsUnsigned u"IsUnsigned"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProcedureParametersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProcedureParametersColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXPackageProcedureParametersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 PackageName = System::Int8(0x2);
	
	static constexpr System::Int8 ProcedureName = System::Int8(0x3);
	
	static constexpr System::Int8 ParameterName = System::Int8(0x4);
	
	static constexpr System::Int8 ParameterMode = System::Int8(0x5);
	
	static constexpr System::Int8 TypeName = System::Int8(0x6);
	
	static constexpr System::Int8 Precision = System::Int8(0x7);
	
	static constexpr System::Int8 Scale = System::Int8(0x8);
	
	static constexpr System::Int8 Ordinal = System::Int8(0x9);
	
	static constexpr System::Int8 IsNullable = System::Int8(0xa);
	
	static constexpr System::Int8 DbxDataType = System::Int8(0xb);
	
	static constexpr System::Int8 IsFixedLength = System::Int8(0xc);
	
	static constexpr System::Int8 IsUnicode = System::Int8(0xd);
	
	static constexpr System::Int8 IsLong = System::Int8(0xe);
	
	static constexpr System::Int8 IsUnsigned = System::Int8(0xf);
	
	static constexpr System::Int8 Last = System::Int8(0xf);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProcedureParametersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProcedureParametersIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXPackageProceduresColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackageProceduresColumns_CatalogName u"CatalogName"
	
	#define TDBXPackageProceduresColumns_SchemaName u"SchemaName"
	
	#define TDBXPackageProceduresColumns_PackageName u"PackageName"
	
	#define TDBXPackageProceduresColumns_ProcedureName u"ProcedureName"
	
	#define TDBXPackageProceduresColumns_ProcedureType u"ProcedureType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProceduresColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProceduresColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXPackageProceduresIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 PackageName = System::Int8(0x2);
	
	static constexpr System::Int8 ProcedureName = System::Int8(0x3);
	
	static constexpr System::Int8 ProcedureType = System::Int8(0x4);
	
	static constexpr System::Int8 Last = System::Int8(0x4);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageProceduresIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageProceduresIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXPackagesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackagesColumns_CatalogName u"CatalogName"
	
	#define TDBXPackagesColumns_SchemaName u"SchemaName"
	
	#define TDBXPackagesColumns_PackageName u"PackageName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackagesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackagesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXPackagesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 PackageName = System::Int8(0x2);
	
	static constexpr System::Int8 Last = System::Int8(0x2);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackagesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackagesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXPackageSourcesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXPackageSourcesColumns_CatalogName u"CatalogName"
	
	#define TDBXPackageSourcesColumns_SchemaName u"SchemaName"
	
	#define TDBXPackageSourcesColumns_PackageName u"PackageName"
	
	#define TDBXPackageSourcesColumns_Definition u"Definition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageSourcesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageSourcesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXPackageSourcesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 PackageName = System::Int8(0x2);
	
	static constexpr System::Int8 Definition = System::Int8(0x3);
	
	static constexpr System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXPackageSourcesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPackageSourcesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXProcedureParametersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProcedureParametersColumns_CatalogName u"CatalogName"
	
	#define TDBXProcedureParametersColumns_SchemaName u"SchemaName"
	
	#define TDBXProcedureParametersColumns_ProcedureName u"ProcedureName"
	
	#define TDBXProcedureParametersColumns_ParameterName u"ParameterName"
	
	#define TDBXProcedureParametersColumns_ParameterMode u"ParameterMode"
	
	#define TDBXProcedureParametersColumns_TypeName u"TypeName"
	
	#define TDBXProcedureParametersColumns_Precision u"Precision"
	
	#define TDBXProcedureParametersColumns_Scale u"Scale"
	
	#define TDBXProcedureParametersColumns_Ordinal u"Ordinal"
	
	#define TDBXProcedureParametersColumns_IsNullable u"IsNullable"
	
	#define TDBXProcedureParametersColumns_DbxDataType u"DbxDataType"
	
	#define TDBXProcedureParametersColumns_IsFixedLength u"IsFixedLength"
	
	#define TDBXProcedureParametersColumns_IsUnicode u"IsUnicode"
	
	#define TDBXProcedureParametersColumns_IsLong u"IsLong"
	
	#define TDBXProcedureParametersColumns_IsUnsigned u"IsUnsigned"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureParametersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureParametersColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXProcedureParametersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 ProcedureName = System::Int8(0x2);
	
	static constexpr System::Int8 ParameterName = System::Int8(0x3);
	
	static constexpr System::Int8 ParameterMode = System::Int8(0x4);
	
	static constexpr System::Int8 TypeName = System::Int8(0x5);
	
	static constexpr System::Int8 Precision = System::Int8(0x6);
	
	static constexpr System::Int8 Scale = System::Int8(0x7);
	
	static constexpr System::Int8 Ordinal = System::Int8(0x8);
	
	static constexpr System::Int8 IsNullable = System::Int8(0x9);
	
	static constexpr System::Int8 DbxDataType = System::Int8(0xa);
	
	static constexpr System::Int8 IsFixedLength = System::Int8(0xb);
	
	static constexpr System::Int8 IsUnicode = System::Int8(0xc);
	
	static constexpr System::Int8 IsLong = System::Int8(0xd);
	
	static constexpr System::Int8 IsUnsigned = System::Int8(0xe);
	
	static constexpr System::Int8 Last = System::Int8(0xe);
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureParametersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureParametersIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXProceduresColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProceduresColumns_CatalogName u"CatalogName"
	
	#define TDBXProceduresColumns_SchemaName u"SchemaName"
	
	#define TDBXProceduresColumns_ProcedureName u"ProcedureName"
	
	#define TDBXProceduresColumns_ProcedureType u"ProcedureType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProceduresColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProceduresColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXProceduresIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 ProcedureName = System::Int8(0x2);
	
	static constexpr System::Int8 ProcedureType = System::Int8(0x3);
	
	static constexpr System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXProceduresIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProceduresIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXProcedureSourcesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXProcedureSourcesColumns_CatalogName u"CatalogName"
	
	#define TDBXProcedureSourcesColumns_SchemaName u"SchemaName"
	
	#define TDBXProcedureSourcesColumns_ProcedureName u"ProcedureName"
	
	#define TDBXProcedureSourcesColumns_ProcedureType u"ProcedureType"
	
	#define TDBXProcedureSourcesColumns_Definition u"Definition"
	
	#define TDBXProcedureSourcesColumns_ExternalDefinition u"ExternalDefinition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureSourcesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureSourcesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXProcedureSourcesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 ProcedureName = System::Int8(0x2);
	
	static constexpr System::Int8 ProcedureType = System::Int8(0x3);
	
	static constexpr System::Int8 Definition = System::Int8(0x4);
	
	static constexpr System::Int8 ExternalDefinition = System::Int8(0x5);
	
	static constexpr System::Int8 Last = System::Int8(0x5);
	
public:
	/* TObject.Create */ inline __fastcall TDBXProcedureSourcesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXProcedureSourcesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXReservedWordsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXReservedWordsColumns_ReservedWord u"ReservedWord"
	
public:
	/* TObject.Create */ inline __fastcall TDBXReservedWordsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXReservedWordsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXReservedWordsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 ReservedWord = System::Int8(0x0);
	
	static constexpr System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXReservedWordsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXReservedWordsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXRolesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXRolesColumns_RoleName u"RoleName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXRolesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXRolesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXRolesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 RoleName = System::Int8(0x0);
	
	static constexpr System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXRolesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXRolesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXSchemasColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXSchemasColumns_CatalogName u"CatalogName"
	
	#define TDBXSchemasColumns_SchemaName u"SchemaName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXSchemasColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSchemasColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXSchemasIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 Last = System::Int8(0x1);
	
public:
	/* TObject.Create */ inline __fastcall TDBXSchemasIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSchemasIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXSynonymsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXSynonymsColumns_CatalogName u"CatalogName"
	
	#define TDBXSynonymsColumns_SchemaName u"SchemaName"
	
	#define TDBXSynonymsColumns_SynonymName u"SynonymName"
	
	#define TDBXSynonymsColumns_TableCatalogName u"TableCatalogName"
	
	#define TDBXSynonymsColumns_TableSchemaName u"TableSchemaName"
	
	#define TDBXSynonymsColumns_TableName u"TableName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXSynonymsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSynonymsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXSynonymsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 SynonymName = System::Int8(0x2);
	
	static constexpr System::Int8 TableCatalogName = System::Int8(0x3);
	
	static constexpr System::Int8 TableSchemaName = System::Int8(0x4);
	
	static constexpr System::Int8 TableName = System::Int8(0x5);
	
	static constexpr System::Int8 Last = System::Int8(0x5);
	
public:
	/* TObject.Create */ inline __fastcall TDBXSynonymsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSynonymsIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXTablesColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXTablesColumns_CatalogName u"CatalogName"
	
	#define TDBXTablesColumns_SchemaName u"SchemaName"
	
	#define TDBXTablesColumns_TableName u"TableName"
	
	#define TDBXTablesColumns_TableType u"TableType"
	
public:
	/* TObject.Create */ inline __fastcall TDBXTablesColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTablesColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXTablesIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 TableName = System::Int8(0x2);
	
	static constexpr System::Int8 TableType = System::Int8(0x3);
	
	static constexpr System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXTablesIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTablesIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXUsersColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXUsersColumns_UserName u"UserName"
	
public:
	/* TObject.Create */ inline __fastcall TDBXUsersColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUsersColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXUsersIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 UserName = System::Int8(0x0);
	
	static constexpr System::Int8 Last = System::Int8(0x0);
	
public:
	/* TObject.Create */ inline __fastcall TDBXUsersIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXUsersIndex() { }
	
};


class PASCALIMPLEMENTATION TDBXViewsColumns : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDBXViewsColumns_CatalogName u"CatalogName"
	
	#define TDBXViewsColumns_SchemaName u"SchemaName"
	
	#define TDBXViewsColumns_ViewName u"ViewName"
	
	#define TDBXViewsColumns_Definition u"Definition"
	
public:
	/* TObject.Create */ inline __fastcall TDBXViewsColumns() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXViewsColumns() { }
	
};


class PASCALIMPLEMENTATION TDBXViewsIndex : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 CatalogName = System::Int8(0x0);
	
	static constexpr System::Int8 SchemaName = System::Int8(0x1);
	
	static constexpr System::Int8 ViewName = System::Int8(0x2);
	
	static constexpr System::Int8 Definition = System::Int8(0x3);
	
	static constexpr System::Int8 Last = System::Int8(0x3);
	
public:
	/* TObject.Create */ inline __fastcall TDBXViewsIndex() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXViewsIndex() { }
	
};


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
