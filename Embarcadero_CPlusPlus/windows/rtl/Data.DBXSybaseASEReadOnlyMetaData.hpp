﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSybaseASEReadOnlyMetaData.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseasereadonlymetadataHPP
#define Data_DbxsybaseasereadonlymetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXMetaDataReader.hpp>
#include <Data.DBXMetaDataCommandFactory.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Data.DBXSybaseASEReadOnlyMetaData"

namespace Data
{
namespace Dbxsybaseasereadonlymetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASEMetaDataCommandFactory;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASEMetaDataCommandFactory : public Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory
{
	typedef Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory inherited;
	
public:
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader();
public:
	/* TObject.Create */ inline __fastcall TDBXSybaseASEMetaDataCommandFactory() : Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSybaseASEMetaDataCommandFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybaseasereadonlymetadata */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASEREADONLYMETADATA)
using namespace Data::Dbxsybaseasereadonlymetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseasereadonlymetadataHPP
