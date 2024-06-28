// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXInterbaseMetaDataWriter.pas' rev: 34.00 (Android)

#ifndef Data_DbxinterbasemetadatawriterHPP
#define Data_DbxinterbasemetadatawriterHPP

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
namespace Dbxinterbasemetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXInterbaseCustomMetaDataWriter;
class DELPHICLASS TDBXInterbaseMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXInterbaseCustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
protected:
	virtual void __fastcall MakeSqlDataType(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxmetadatareader::TDBXDataTypeDescription* const DataType, Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides)/* overload */;
	
private:
	void __fastcall FormatStringType(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxmetadatareader::TDBXDataTypeDescription* const DataType, Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides);
	void __fastcall FormatBlobType(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxmetadatareader::TDBXDataTypeDescription* const DataType, Data::Dbxcommontable::TDBXTableRow* const ColumnRow, const Data::Dbxplatform::TDBXInt32s Overrides);
	bool __fastcall UnicodeSpecificationRequired(Data::Dbxcommontable::TDBXTableRow* const ColumnRow);
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXInterbaseCustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXInterbaseCustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  MakeSqlDataType(System::Sysutils::TStringBuilder* const Buffer, const System::UnicodeString TypeName, Data::Dbxcommontable::TDBXTableRow* const ColumnRow){ Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter::MakeSqlDataType(Buffer, TypeName, ColumnRow); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TDBXInterbaseMetaDataWriter : public TDBXInterbaseCustomMetaDataWriter
{
	typedef TDBXInterbaseCustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXInterbaseMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual bool __fastcall IsIndexNamesGlobal();
	virtual bool __fastcall IsSerializedIsolationSupported();
	virtual bool __fastcall IsMixed_DDL_DML_Supported();
	virtual int __fastcall GetAlterTableSupport();
	virtual System::UnicodeString __fastcall GetSqlKeyGeneratedIndexName();
	virtual bool __fastcall IsSchemasSupported();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXInterbaseMetaDataWriter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxinterbasemetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXINTERBASEMETADATAWRITER)
using namespace Data::Dbxinterbasemetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxinterbasemetadatawriterHPP
