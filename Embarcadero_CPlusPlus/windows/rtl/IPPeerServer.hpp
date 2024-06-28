// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IPPeerServer.pas' rev: 34.00 (Windows)

#ifndef IppeerserverHPP
#define IppeerserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <IdIOHandlerSocket.hpp>
#include <IdIOHandler.hpp>
#include <IdStack.hpp>
#include <IdHTTP.hpp>
#include <IdHTTPHeaderInfo.hpp>
#include <IdServerIOHandler.hpp>
#include <IdContext.hpp>
#include <IdSchedulerOfThreadPool.hpp>
#include <IdScheduler.hpp>
#include <IdSSLOpenSSL.hpp>
#include <IdGlobalProtocols.hpp>
#include <IdHeaderList.hpp>
#include <IdSocketHandle.hpp>
#include <IdTCPServer.hpp>
#include <IdUDPServer.hpp>
#include <IdHTTPServer.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdTCPConnection.hpp>
#include <IdStackConsts.hpp>
#include <IdGlobal.hpp>
#include <IdIPMCastServer.hpp>
#include <IPPeerCommon.hpp>
#include <IPPeerResStrs.hpp>
#include <IPPeerAPI.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "IPPeerServer"
#if !defined(_NO_PRAGMA_LINK_INDY)
 #ifndef USEPACKAGES
#ifndef _WIN64
  #pragma link "IndyCore.lib"
  #pragma link "IndyProtocols.lib"
  #pragma link "IndySystem.lib"
#else /* _WIN64 */
  #pragma link "IndyCore.a"
  #pragma link "IndyProtocols.a"
  #pragma link "IndySystem.a"
#endif /* _WIN64 */
 #else
  #pragma link "IndyCore.bpi"
  #pragma link "IndyProtocols.bpi"
  #pragma link "IndySystem.bpi"
 #endif
#endif

namespace Ippeerserver
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString __fastcall IPImpId();
}	/* namespace Ippeerserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IPPEERSERVER)
using namespace Ippeerserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IppeerserverHPP
