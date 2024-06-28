// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysTypes.pas' rev: 34.00 (Android)

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
typedef void * *Ptimer_t;

#ifndef __aarch64__
typedef unsigned *Pblkcnt_t;
#else /* __aarch64__ */
typedef unsigned long *Pblkcnt_t;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef unsigned *Pblksize_t;
#else /* __aarch64__ */
typedef unsigned long *Pblksize_t;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef int *Pclock_t;
#else /* __aarch64__ */
typedef long *Pclock_t;
#endif /* __aarch64__ */

typedef int *Pclockid_t;

#ifndef __aarch64__
typedef unsigned *Pdev_t;
#else /* __aarch64__ */
typedef unsigned long *Pdev_t;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef unsigned *Pfsblkcnt_t;
#else /* __aarch64__ */
typedef unsigned long *Pfsblkcnt_t;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef unsigned *Pfsfilcnt_t;
#else /* __aarch64__ */
typedef unsigned long *Pfsfilcnt_t;
#endif /* __aarch64__ */

typedef unsigned *Pgid_t;

typedef unsigned *_Pid_t;

#ifndef __aarch64__
typedef unsigned *Pino_t;
#else /* __aarch64__ */
typedef unsigned long *Pino_t;
#endif /* __aarch64__ */

typedef int *Pkey_t;

#ifndef __aarch64__
typedef System::Word *Pmode_t;
#else /* __aarch64__ */
typedef unsigned *Pmode_t;
#endif /* __aarch64__ */

typedef unsigned *Pnlink_t;

#ifndef __aarch64__
typedef int *Poff_t;
#else /* __aarch64__ */
typedef long *Poff_t;
#endif /* __aarch64__ */

typedef __int64 *Poff64_t;

typedef int *Ppid_t;

#ifndef __aarch64__
typedef int *Pssize_t;
#else /* __aarch64__ */
typedef long *Pssize_t;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef System::Word *Puid_t;
#else /* __aarch64__ */
typedef unsigned *Puid_t;
#endif /* __aarch64__ */

typedef NativeInt *Psuseconds_t;

typedef pthread_attr_t *Ppthread_attr_t;

typedef NativeInt *Ppthread_condattr_t;

typedef NativeInt *Ppthread_rwlockattr_t;

typedef NativeInt *Ppthread_mutexattr_t;

typedef NativeInt *Ptime_t;

typedef unsigned *Puseconds_t;

using Posix::Stddef::Psize_t;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Systypes */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SystypesHPP
