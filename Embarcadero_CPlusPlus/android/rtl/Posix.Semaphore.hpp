// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Semaphore.pas' rev: 34.00 (Android)

#ifndef Posix_SemaphoreHPP
#define Posix_SemaphoreHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.Time.hpp>
#include <Posix.SysTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Posix
{
namespace Semaphore
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef sem_t *Psem_t;

//-- var, const, procedure ---------------------------------------------------
extern "C" int __cdecl sem_timedwait(sem_t &sem, timespec &abs_timeout);
}	/* namespace Semaphore */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SemaphoreHPP
