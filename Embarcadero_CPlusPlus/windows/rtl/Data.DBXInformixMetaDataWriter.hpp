// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXInformixMetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_DbxinformixmetadatawriterHPP
#define Data_DbxinformixmetadatawriterHPP

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
namespace Dbxinformixmetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXInformixCustomMetaDataWriter;
class DELPHICLASS TDBXInformixMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXInformixCustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
protected:
	virtual void __fastcall MakeSqlCreateKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
	virtual void __fastcall MakeSqlCreateForeignKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const ForeignKey, Data::Dbxcommontable::TDBXTable* const ForeignKeyColumns);
	virtual void __fastcall MakeSqlDropSecondaryIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXInformixCustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXInformixCustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXInformixMetaDataWriter : public TDBXInformixCustomMetaDataWriter
{
	typedef TDBXInformixCustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXInformixMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
	virtual bool __fastcall IsSchemasSupported();
	virtual bool __fastcall IsMultipleStatementsSupported();
	virtual bool __fastcall IsDescendingIndexConstraintsSupported();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXInformixMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxinformixmetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXINFORMIXMETADATAWRITER)
using namespace Data::Dbxinformixmetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxinformixmetadatawriterHPP
