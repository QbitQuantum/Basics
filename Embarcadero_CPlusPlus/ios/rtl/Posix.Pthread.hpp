// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Pthread.pas' rev: 34.00 (iOS)

#ifndef Posix_PthreadHPP
#define Posix_PthreadHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.Mach.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.Time.hpp>
#include <Posix.Sched.hpp>

//-- user supplied -----------------------------------------------------------

namespace Posix
{
namespace Pthread
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void __cdecl (*TInitOnceProc)(void);

typedef void __cdecl (*TKeyValueDestructor)(void * ValueInKey);

typedef void * __cdecl (*TPThreadFunc)(void * Parameter);

//-- var, const, procedure ---------------------------------------------------
extern "C" NativeUInt __cdecl GetCurrentThreadID(void);
extern DELPHI_PACKAGE int __fastcall pthread_mutex_timedlock(pthread_mutex_t &Mutex, const timespec &AbsTime);
}	/* namespace Pthread */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_PthreadHPP
