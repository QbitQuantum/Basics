// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSybaseASAMetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseasametadatawriterHPP
#define Data_DbxsybaseasametadatawriterHPP

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
namespace Dbxsybaseasametadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASACustomMetaDataWriter;
class DELPHICLASS TDBXSybaseASAMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASACustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
protected:
	virtual void __fastcall MakeSqlNullable(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Column);
	virtual void __fastcall MakeSqlDropSecondaryIndex(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index);
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXSybaseASACustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXSybaseASACustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASAMetaDataWriter : public TDBXSybaseASACustomMetaDataWriter
{
	typedef TDBXSybaseASACustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXSybaseASAMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual bool __fastcall IsCatalogsSupported();
	virtual bool __fastcall IsSchemasSupported();
	virtual bool __fastcall IsSerializedIsolationSupported();
	virtual bool __fastcall IsMultipleStatementsSupported();
	virtual bool __fastcall IsDDLTransactionsSupported();
	virtual bool __fastcall IsDescendingIndexConstraintsSupported();
	virtual System::UnicodeString __fastcall GetSqlAutoIncrementKeyword();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXSybaseASAMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybaseasametadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASAMETADATAWRITER)
using namespace Data::Dbxsybaseasametadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseasametadatawriterHPP
