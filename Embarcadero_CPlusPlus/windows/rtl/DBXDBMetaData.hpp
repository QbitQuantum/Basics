// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DBXDBMetaData.pas' rev: 34.00 (Windows)

#ifndef DbxdbmetadataHPP
#define DbxdbmetadataHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXMetaDataProvider.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>

//-- user supplied -----------------------------------------------------------

namespace Dbxdbmetadata
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXDBMetaData;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXDBMetaData : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static Data::Db::TFieldType __fastcall ToFieldType(int DataType);
	
public:
	static void __fastcall AddParams(Data::Db::TParams* Params, Data::Dbxmetadataprovider::TDBXMetaDataTable* MetaDataTable);
	static void __fastcall AddClientDataSetFields(Datasnap::Dbclient::TClientDataSet* ClientDataSet, Data::Dbxmetadataprovider::TDBXMetaDataTable* MetaDataTable);
public:
	/* TObject.Create */ inline __fastcall TDBXDBMetaData() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXDBMetaData() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxdbmetadata */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DBXDBMETADATA)
using namespace Dbxdbmetadata;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DbxdbmetadataHPP
