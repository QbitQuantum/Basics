// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMSSQLMetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_DbxmssqlmetadatawriterHPP
#define Data_DbxmssqlmetadatawriterHPP

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
namespace Dbxmssqlmetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXMsSqlCustomMetaDataWriter;
class DELPHICLASS TDBXMsSqlMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMsSqlCustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
protected:
	virtual void __fastcall MakeSqlDropSecondaryIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXMsSqlCustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXMsSqlCustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXMsSqlMetaDataWriter : public TDBXMsSqlCustomMetaDataWriter
{
	typedef TDBXMsSqlCustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXMsSqlMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual bool __fastcall IsSerializedIsolationSupported();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementInserts();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
	virtual bool __fastcall IsCatalogsSupported();
	virtual bool __fastcall IsSchemasSupported();
	virtual bool __fastcall IsMultipleStatementsSupported();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXMsSqlMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmssqlmetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMSSQLMETADATAWRITER)
using namespace Data::Dbxmssqlmetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmssqlmetadatawriterHPP
