// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXMetadataCommon.pas' rev: 34.00 (iOS)

#ifndef Data_DbxmetadatacommonHPP
#define Data_DbxmetadatacommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxmetadatacommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TInvocationMetadataDelegate;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TInvocationMetadataDelegate : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static void __fastcall StoreMetadata(System::Json::TJSONObject* &MetaData);
	static void __fastcall WriteMetadata(System::TObject* const ConnectionHandler);
	static void __fastcall ClearMetadata(System::TObject* const ConnectionHandler);
public:
	/* TObject.Create */ inline __fastcall TInvocationMetadataDelegate() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TInvocationMetadataDelegate() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxmetadatacommon */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXMETADATACOMMON)
using namespace Data::Dbxmetadatacommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxmetadatacommonHPP
