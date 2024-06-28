// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXOdbcReadOnlyMetaData.pas' rev: 34.00 (Windows)

#ifndef Data_DbxodbcreadonlymetadataHPP
#define Data_DbxodbcreadonlymetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DbxOdbc.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXMetaDataCommandFactory.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DBXOdbcReadOnlyMetaData"

namespace Data
{
namespace Dbxodbcreadonlymetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXOdbcMetaDataCommandFactory;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXOdbcMetaDataCommandFactory : public Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory
{
	typedef Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory inherited;
	
public:
	virtual Data::Dbxcommon::TDBXCommand* __fastcall CreateCommand(Data::Dbxcommon::TDBXContext* DbxContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader()/* overload */;
	HIDESBASE Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader(Data::Dbxodbc::TDBXOdbcConnection* OdbcConnection)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDBXOdbcMetaDataCommandFactory() : Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXOdbcMetaDataCommandFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxodbcreadonlymetadata */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXODBCREADONLYMETADATA)
using namespace Data::Dbxodbcreadonlymetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxodbcreadonlymetadataHPP
