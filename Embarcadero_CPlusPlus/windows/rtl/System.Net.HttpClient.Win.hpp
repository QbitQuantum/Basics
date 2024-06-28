// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Net.HttpClient.Win.pas' rev: 34.00 (Windows)

#ifndef System_Net_Httpclient_WinHPP
#define System_Net_Httpclient_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------
#pragma comment(lib, "winhttp")
#pragma comment(lib, "crypt32")

namespace System
{
namespace Net
{
namespace Httpclient
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall ShowSelectCertificateDialog(NativeUInt AParentWnd, const System::UnicodeString ATitle, const System::UnicodeString ADisplayString, void *ACertificate);
}	/* namespace Win */
}	/* namespace Httpclient */
}	/* namespace Net */
}	/* namespace System */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Net_Httpclient_WinHPP
