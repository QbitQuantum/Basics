// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSybaseASAReadOnlyMetaData.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsybaseasareadonlymetadataHPP
#define Data_DbxsybaseasareadonlymetadataHPP

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
#pragma link "Data.DBXSybaseASAReadOnlyMetaData"

namespace Data
{
namespace Dbxsybaseasareadonlymetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSybaseASAMetaDataCommandFactory;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSybaseASAMetaDataCommandFactory : public Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory
{
	typedef Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory inherited;
	
public:
	virtual Data::Dbxmetadatareader::TDBXMetaDataReader* __fastcall CreateMetaDataReader();
public:
	/* TObject.Create */ inline __fastcall TDBXSybaseASAMetaDataCommandFactory() : Data::Dbxmetadatacommandfactory::TDBXMetaDataCommandFactory() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXSybaseASAMetaDataCommandFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsybaseasareadonlymetadata */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSYBASEASAREADONLYMETADATA)
using namespace Data::Dbxsybaseasareadonlymetadata;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsybaseasareadonlymetadataHPP
