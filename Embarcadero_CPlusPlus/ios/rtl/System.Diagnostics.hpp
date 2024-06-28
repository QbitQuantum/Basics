// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Diagnostics.pas' rev: 34.00 (iOS)

#ifndef System_DiagnosticsHPP
#define System_DiagnosticsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.TimeSpan.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Diagnostics
{
//-- forward type declarations -----------------------------------------------
struct TStopwatch;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TStopwatch
{
private:
	static __int64 FFrequency;
	static bool FIsHighResolution;
	static double TickFrequency;
	__int64 FElapsed;
	bool FRunning;
	__int64 FStartTimeStamp;
	System::Timespan::TTimeSpan __fastcall GetElapsed();
	__int64 __fastcall GetElapsedDateTimeTicks();
	__int64 __fastcall GetElapsedMilliseconds();
	__int64 __fastcall GetElapsedTicks();
	static void __fastcall InitStopwatchType();
	
public:
	static TStopwatch __fastcall Create();
	static __int64 __fastcall GetTimeStamp();
	void __fastcall Reset();
	void __fastcall Start();
	static TStopwatch __fastcall StartNew();
	void __fastcall Stop();
	__property System::Timespan::TTimeSpan Elapsed = {read=GetElapsed};
	__property __int64 ElapsedMilliseconds = {read=GetElapsedMilliseconds};
	__property __int64 ElapsedTicks = {read=GetElapsedTicks};
	/* static */ __property __int64 Frequency = {read=FFrequency};
	/* static */ __property bool IsHighResolution = {read=FIsHighResolution};
	__property bool IsRunning = {read=FRunning};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Diagnostics */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_DIAGNOSTICS)
using namespace System::Diagnostics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_DiagnosticsHPP
