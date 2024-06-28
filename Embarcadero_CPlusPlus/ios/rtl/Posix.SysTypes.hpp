// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysTypes.pas' rev: 34.00 (iOS)

#ifndef Posix_SystypesHPP
#define Posix_SystypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------
#include <pthread.h>

namespace Posix
{
namespace Systypes
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef long *Ptime_t;

typedef unsigned long *Pclock_t;

typedef __int64 *Pblkcnt_t;

typedef int *Pblksize_t;

typedef int *Pdev_t;

typedef unsigned *Pfsblkcnt_t;

typedef unsigned *Pfsfilcnt_t;

typedef unsigned *Pgid_t;

typedef unsigned *_Pid_t;

typedef __int64 *Pino_t;

typedef System::Word *Pmode_t;

typedef System::Word *Pnlink_t;

typedef __int64 *Poff_t;

typedef int *Ppid_t;

typedef long *Pssize_t;

typedef unsigned *Puid_t;

typedef unsigned long *Puseconds_t;

typedef int *Psuseconds_t;

typedef pthread_mutexattr_t *Ppthread_mutexattr_t;

typedef pthread_condattr_t *Ppthread_condattr_t;

typedef pthread_rwlockattr_t *Ppthread_rwlockattr_t;

typedef pthread_attr_t *Ppthread_attr_t;

using Posix::Stddef::Psize_t;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Systypes */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SystypesHPP
