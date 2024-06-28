// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.Timer.pas' rev: 34.00 (Android)

#ifndef Androidapi_TimerHPP
#define Androidapi_TimerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Timer
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TAndroidTimerNotify)(int TimerId);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall AndroidTimerSetHandler(TAndroidTimerNotify OnTimer);
extern DELPHI_PACKAGE int __fastcall AndroidTimerCreate(void);
extern DELPHI_PACKAGE void __fastcall AndroidTimerSetInterval(int TimerHandle, int Interval);
extern DELPHI_PACKAGE void __fastcall AndroidTimerDestroy(int TimerHandle);
}	/* namespace Timer */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_TIMER)
using namespace Androidapi::Timer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_TimerHPP
