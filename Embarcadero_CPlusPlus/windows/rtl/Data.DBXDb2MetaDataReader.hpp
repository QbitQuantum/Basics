// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXDb2MetaDataReader.pas' rev: 34.00 (Windows)

#ifndef Data_Dbxdb2metadatareaderHPP
#define Data_Dbxdb2metadatareaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxdb2metadatareader
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDb2MetaDataReader;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDb2MetaDataReader : public Data::Dbxmetadatareader::TDBXBaseMetaDataReader
{
	typedef Data::Dbxmetadatareader::TDBXBaseMetaDataReader inherited;
	
public:
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchCatalogs();
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchColumnConstraints(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString TableName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackages(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedures(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ProcedureType);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageProcedureParameters(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName, const System::UnicodeString ProcedureName, const System::UnicodeString ParameterName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchPackageSources(const System::UnicodeString CatalogName, const System::UnicodeString SchemaName, const System::UnicodeString PackageName);
	virtual Data::Dbxcommontable::TDBXTable* __fastcall FetchUsers();
	
protected:
	virtual bool __fastcall AreSchemasSupported();
	virtual System::UnicodeString __fastcall GetProductName();
	virtual System::UnicodeString __fastcall GetTableType();
	virtual System::UnicodeString __fastcall GetViewType();
	virtual System::UnicodeString __fastcall GetSystemTableType();
	virtual System::UnicodeString __fastcall GetSqlProcedureQuoteChar();
	virtual bool __fastcall IsSetRowSizeSupported();
	virtual bool __fastcall IsParameterMetadataSupported();
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
	virtual System::UnicodeString __fastcall GetSqlForProcedureParameters();
	virtual System::UnicodeString __fastcall GetSqlForRoles();
	virtual System::UnicodeString __fastcall GetVersion();
	virtual Data::Dbxmetadatareader::TDBXDataTypeDescriptionArray __fastcall GetDataTypeDescriptions();
	virtual Data::Dbxplatform::TDBXStringArray __fastcall GetReservedWords();
public:
	/* TDBXBaseMetaDataReader.Destroy */ inline __fastcall virtual ~TDBXDb2MetaDataReader() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXDb2MetaDataReader() : Data::Dbxmetadatareader::TDBXBaseMetaDataReader() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdb2metadatareader */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXDB2METADATAREADER)
using namespace Data::Dbxdb2metadatareader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Dbxdb2metadatareaderHPP
