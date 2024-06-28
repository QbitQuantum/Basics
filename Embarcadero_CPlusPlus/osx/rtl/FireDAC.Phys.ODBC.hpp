// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.ODBC.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Phys_OdbcHPP
#define Firedac_Phys_OdbcHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Phys.hpp>
#include <FireDAC.Phys.ODBCBase.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.ODBC"

namespace Firedac
{
namespace Phys
{
namespace Odbc
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysODBCDriverLink;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysODBCDriverLink : public Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink
{
	typedef Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysODBCDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Odbcbase::TFDPhysODBCBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysODBCDriverLink() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Odbc */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_ODBC)
using namespace Firedac::Phys::Odbc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS)
using namespace Firedac::Phys;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Phys_OdbcHPP
