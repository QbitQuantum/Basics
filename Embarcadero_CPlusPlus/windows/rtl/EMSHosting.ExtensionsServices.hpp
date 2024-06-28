// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.ExtensionsServices.pas' rev: 34.00 (Windows)

#ifndef Emshosting_ExtensionsservicesHPP
#define Emshosting_ExtensionsservicesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "EMSHosting.ExtensionsServices"

namespace Emshosting
{
namespace Extensionsservices
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall AddService(const System::_di_IInterface Handler);
extern DELPHI_PACKAGE void __fastcall RemoveService(int Index);
}	/* namespace Extensionsservices */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EXTENSIONSSERVICES)
using namespace Emshosting::Extensionsservices;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_ExtensionsservicesHPP
