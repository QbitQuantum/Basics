// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Phys.DS.pas' rev: 34.00 (Android)

#ifndef Firedac_Phys_DsHPP
#define Firedac_Phys_DsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FireDAC.Phys.TDBXBase.hpp>
#include <FireDAC.Phys.hpp>

//-- user supplied -----------------------------------------------------------
namespace Firedac
{
namespace Phys
{
namespace Ds
{
  _INIT_UNIT(Firedac_Phys_Ds);
}	/* namespace Ds */
}	/* namespace Phys */
}	/* namespace Firedac */

namespace Firedac
{
namespace Phys
{
namespace Ds
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDPhysDSDriverLink;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFDPhysDSDriverLink : public Firedac::Phys::Tdbxbase::TFDPhysTDBXBaseDriverLink
{
	typedef Firedac::Phys::Tdbxbase::TFDPhysTDBXBaseDriverLink inherited;
	
protected:
	virtual System::UnicodeString __fastcall GetBaseDriverID();
public:
	/* TFDPhysDriverLink.Create */ inline __fastcall virtual TFDPhysDSDriverLink(System::Classes::TComponent* AOwner) : Firedac::Phys::Tdbxbase::TFDPhysTDBXBaseDriverLink(AOwner) { }
	/* TFDPhysDriverLink.Destroy */ inline __fastcall virtual ~TFDPhysDSDriverLink() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ds */
}	/* namespace Phys */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_PHYS_DS)
using namespace Firedac::Phys::Ds;
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
#endif	// Firedac_Phys_DsHPP
