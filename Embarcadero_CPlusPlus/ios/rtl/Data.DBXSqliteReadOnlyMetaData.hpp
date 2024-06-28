// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSqliteReadOnlyMetaData.pas' rev: 34.00 (iOS)

#ifndef Data_DbxsqlitereadonlymetadataHPP
#define Data_DbxsqlitereadonlymetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXMetaDataCommandFactory.hpp>
#include <Data.DBXMetaDataReader.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Dbxsqlitereadonlymetadata
{
  _INIT_UNIT(Data_Dbxsqlitereadonlymetadata);
}	/* namespace Dbxsqlitereadonlymetadata */
}	/* namespace Data */

namespace Data
{
namespace Dbxsqlitereadonlymetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSqliteMetaDataCommandFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXSqliteMetaDataCommandFactory : public Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory
{
	typedef Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory inherited;
	
public:
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader();
public:
	/* TObject.Create */ inline __fastcall TDBXSqliteMetaDataCommandFactory() : Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSqliteMetaDataCommandFactory() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsqlitereadonlymetadata */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSQLITEREADONLYMETADATA)
using namespace Data::Dbxsqlitereadonlymetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsqlitereadonlymetadataHPP
