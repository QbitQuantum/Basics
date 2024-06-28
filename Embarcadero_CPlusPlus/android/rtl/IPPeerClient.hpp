// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IPPeerClient.pas' rev: 34.00 (Android)

#ifndef IppeerclientHPP
#define IppeerclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandler.hpp>
#include <IdHTTP.hpp>
#include <IdAuthentication.hpp>
#include <IdURI.hpp>
#include <IdHTTPHeaderInfo.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdTCPClient.hpp>
#include <IdStack.hpp>
#include <IdGlobal.hpp>
#include <IdHashMessageDigest.hpp>
#include <IdCookieManager.hpp>
#include <IdIPMCastClient.hpp>
#include <IdSocketHandle.hpp>
#include <IPPeerCommon.hpp>
#include <IPPeerResStrs.hpp>
#include <IPPeerAPI.hpp>

//-- user supplied -----------------------------------------------------------
namespace Ippeerclient
{
  _INIT_UNIT(Ippeerclient);
}	/* namespace Ippeerclient */
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

namespace Ippeerclient
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall IPImpId(void);
}	/* namespace Ippeerclient */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IPPEERCLIENT)
using namespace Ippeerclient;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IppeerclientHPP
