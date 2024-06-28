// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.MongoDB.pas' rev: 34.00 (Windows)

#ifndef Firedac_Phys_MongodbHPP
#define Firedac_Phys_MongodbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Phys.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "FireDAC.Phys.MongoDB"

namespace Firedac
{
namespace Phys
{
namespace Mongodb
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysMongoDriverLink;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDPhysMongoDriverLink : public Firedac::Phys::TFDPhysDriverLink
{
	typedef Firedac::Phys::TFDPhysDriverLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysMongoDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::TFDPhysDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysMongoDriverLink() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mongodb */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_MONGODB)
using namespace Firedac::Phys::Mongodb;
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
#endif	// Firedac_Phys_MongodbHPP
