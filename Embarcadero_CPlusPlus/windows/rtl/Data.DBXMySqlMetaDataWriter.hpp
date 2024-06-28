// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMySqlMetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmysqlmetadatawriterHPP
#define Data_DbxmysqlmetadatawriterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXMetaDataWriter.hpp>
#include <Data.DBXPlatform.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmysqlmetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMySqlCustomMetaDataWriter;
class DELPHICLASS TDBXMySqlMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMySqlCustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
protected:
	virtual void __fastcall MakeSqlDataType(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxmetadatareader::TDBXDataTypeDescription* const DataType, Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides)/* overload */;
	virtual bool __fastcall CanCreateIndexAsKey(Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	virtual void __fastcall MakeSqlCreateIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	virtual void __fastcall MakeSqlDropIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
	virtual void __fastcall MakeSqlDropForeignKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const ForeignKey);
	virtual void __fastcall MakeSqlColumnTypeCast(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTable* const Column);
	
private:
	bool __fastcall UnicodeSpecificationRequired(Data::Dbxcommontable::TDBXTableRow* const ColumnRow);
	bool __fastcall HasAutoIncrementColumn(Data::Dbxcommontable::TDBXTableRow* const Index);
	System::UnicodeString __fastcall FindCastType(Data::Dbxcommontable::TDBXTableRow* const Column);
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXMySqlCustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXMySqlCustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  MakeSqlDataType(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString TypeName, Data::Dbxcommontable::TDBXTableRow* const ColumnRow){ Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter::MakeSqlDataType(Buffer, TypeName, ColumnRow); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMySqlMetaDataWriter : public TDBXMySqlCustomMetaDataWriter
{
	typedef TDBXMySqlCustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXMySqlMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
	virtual bool __fastcall IsCatalogsSupported();
	virtual bool __fastcall IsSchemasSupported();
	virtual int __fastcall GetAlterTableSupport();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXMySqlMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmysqlmetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMYSQLMETADATAWRITER)
using namespace Data::Dbxmysqlmetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmysqlmetadatawriterHPP
