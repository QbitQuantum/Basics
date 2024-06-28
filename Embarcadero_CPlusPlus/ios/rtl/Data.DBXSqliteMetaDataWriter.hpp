// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSqliteMetaDataWriter.pas' rev: 34.00 (iOS)

#ifndef Data_DbxsqlitemetadatawriterHPP
#define Data_DbxsqlitemetadatawriterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>
#include <Data.DBXMetaDataWriter.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxsqlitemetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSqliteCustomMetaDataWriter;
class DELPHICLASS TDBXSqliteMetaDataWriter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXSqliteCustomMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
protected:
	virtual bool __fastcall IsSchemasSupported();
	virtual void __fastcall MakeSqlCreateKey(System::Sysutils::TStringBuilder* const Buffer, Data::Dbxcommontable::TDBXTableRow* const Index, Data::Dbxcommontable::TDBXTable* const IndexColumns);
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXSqliteCustomMetaDataWriter() { }
	
public:
	/* TObject.Create */ inline __fastcall TDBXSqliteCustomMetaDataWriter() : Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter() { }
	
};


class PASCALIMPLEMENTATION TDBXSqliteMetaDataWriter : public TDBXSqliteCustomMetaDataWriter
{
	typedef TDBXSqliteCustomMetaDataWriter inherited;
	
public:
	__fastcall TDBXSqliteMetaDataWriter();
	virtual void __fastcall Open();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXSqliteMetaDataWriter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsqlitemetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSQLITEMETADATAWRITER)
using namespace Data::Dbxsqlitemetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsqlitemetadatawriterHPP
