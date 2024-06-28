// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXOracleMetaDataWriter.pas' rev: 34.00 (Windows)

#ifndef Data_DbxoraclemetadatawriterHPP
#define Data_DbxoraclemetadatawriterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXMetaDataWriter.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxoraclemetadatawriter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXOracleMetaDataWriter;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOracleMetaDataWriter : public Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter
{
	typedef Data::Dbxmetadatawriter::TDBXBaseMetaDataWriter inherited;
	
public:
	__fastcall TDBXOracleMetaDataWriter();
	virtual void __fastcall Open();
	
protected:
	virtual bool __fastcall IsCatalogsSupported();
	virtual bool __fastcall IsSchemasSupported();
	virtual bool __fastcall IsMultipleStatementsSupported();
	virtual bool __fastcall IsDescendingIndexConstraintsSupported();
	virtual bool __fastcall IsIndexNamesGlobal();
	virtual System::UnicodeString __fastcall GetSqlRenameTable();
public:
	/* TDBXBaseMetaDataWriter.Destroy */ inline __fastcall virtual ~TDBXOracleMetaDataWriter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxoraclemetadatawriter */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXORACLEMETADATAWRITER)
using namespace Data::Dbxoraclemetadatawriter;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxoraclemetadatawriterHPP
