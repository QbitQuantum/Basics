// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IndyPeerImpl.pas' rev: 34.00 (Android)

#ifndef IndypeerimplHPP
#define IndypeerimplHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IPPeerClient.hpp>

//-- user supplied -----------------------------------------------------------
namespace Indypeerimpl
{
  _INIT_UNIT(Indypeerimpl);
}	/* namespace Indypeerimpl */
#if !defined(_NO_PRAGMA_LINK_INDY)
 #ifndef USEPACKAGES
  #pragma link "IndyCore.lib"
  #pragma link "IndyProtocols.lib"
  #pragma link "IndySystem.lib"
 #else
  #pragma link "IndyCore.bpi"
  #pragma link "IndyProtocols.bpi"
  #pragma link "IndySystem.bpi"
 #endif
#endif

namespace Indypeerimpl
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall IPImpId(void);
}	/* namespace Indypeerimpl */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_INDYPEERIMPL)
using namespace Indypeerimpl;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IndypeerimplHPP
