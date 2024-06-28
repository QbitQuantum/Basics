// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXInterbaseReadOnlyMetaData.pas' rev: 34.00 (iOS)

#ifndef Data_DbxinterbasereadonlymetadataHPP
#define Data_DbxinterbasereadonlymetadataHPP

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
namespace Data
{
namespace Dbxinterbasereadonlymetadata
{
  _INIT_UNIT(Data_Dbxinterbasereadonlymetadata);
}	/* namespace Dbxinterbasereadonlymetadata */
}	/* namespace Data */

namespace Data
{
namespace Dbxinterbasereadonlymetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXInterbaseMetaDataCommandFactory;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXInterbaseMetaDataCommandFactory : public Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory
{
	typedef Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory inherited;
	
public:
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader();
public:
	/* TObject.Create */ inline __fastcall TDBXInterbaseMetaDataCommandFactory() : Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXInterbaseMetaDataCommandFactory() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxinterbasereadonlymetadata */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXINTERBASEREADONLYMETADATA)
using namespace Data::Dbxinterbasereadonlymetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxinterbasereadonlymetadataHPP
