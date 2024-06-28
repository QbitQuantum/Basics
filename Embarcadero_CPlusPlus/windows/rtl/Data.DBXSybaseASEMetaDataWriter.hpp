// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSybaseASEMetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseasemetadatawriterHPP
#define Data_DbxsybaseasemetadatawriterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataWriter.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxsybaseasemetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASECustomMetaDataWriter;
class DELPHICLASS TDBXSybaseASEMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASECustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
public:
	virtual void __fastcall MakeSqlCreate(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item, Data::Dbxcommontable::TDBXTable* const Parts)/* overload */;
	virtual void __fastcall MakeSqlAlter(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item, Data::Dbxcommontable::TDBXTable* const Parts);
	virtual void __fastcall MakeSqlDrop(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Item);
	
protected:
	virtual void __fastcall MakeSqlColumnTypeCast(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTable* const Column);
	virtual void __fastcall MakeSqlDropSecondaryIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
	
private:
	#define TDBXSybaseASECustomMetaDataWriter_SetQuotedIdentifiersOn L"SET QUOTED_IDENTIFIER ON;\n"
	
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXSybaseASECustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXSybaseASECustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  MakeSqlCreate(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const TableItem, Data::Dbxcommontable::TDBXTable* const TableParts, Data::Dbxcommontable::TDBXTableRow* const ViewItem, Data::Dbxcommontable::TDBXTable* const ViewParts, Data::Dbxcommontable::TDBXTableRow* const SynonymItem, Data::Dbxcommontable::TDBXTable* const SynonymParts, Data::Dbxcommontable::TDBXTableRow* const IndexesItem, Data::Dbxcommontable::TDBXTable* const IndexesParts, Data::Dbxcommontable::TDBXTableRow* const ForeignKeysItem, Data::Dbxcommontable::TDBXTable* const ForeignKeysParts){ Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter::MakeSqlCreate(Buffer, TableItem, TableParts, ViewItem, ViewParts, SynonymItem, SynonymParts, IndexesItem, IndexesParts, ForeignKeysItem, ForeignKeysParts); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASEMetaDataWriter : public TDBXSybaseASECustomMetaDataWriter
{
	typedef TDBXSybaseASECustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXSybaseASEMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementInserts();
	virtual bool __fastcall IsCatalogsSupported();
	virtual bool __fastcall IsSchemasSupported();
	virtual bool __fastcall IsSerializedIsolationSupported();
	virtual bool __fastcall IsMultipleStatementsSupported();
	virtual bool __fastcall IsDDLTransactionsSupported();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXSybaseASEMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybaseasemetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASEMETADATAWRITER)
using namespace Data::Dbxsybaseasemetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseasemetadatawriterHPP
