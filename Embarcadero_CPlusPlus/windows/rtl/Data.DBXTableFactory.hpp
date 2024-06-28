// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXTableFactory.pas' rev: 34.00 (Windows)

#ifndef Data_DbxtablefactoryHPP
#define Data_DbxtablefactoryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXCommonTable.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxtablefactory
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXTableFactory;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTableFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static Data::Dbxcommontable::TDBXTable* __fastcall CreateDBXTable();
public:
	/* TObject.Create */ inline __fastcall TDBXTableFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTableFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxtablefactory */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXTABLEFACTORY)
using namespace Data::Dbxtablefactory;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxtablefactoryHPP
