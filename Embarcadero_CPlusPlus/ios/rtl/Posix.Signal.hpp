// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Signal.pas' rev: 34.00 (iOS)

#ifndef Posix_SignalHPP
#define Posix_SignalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>

//-- user supplied -----------------------------------------------------------
#include <signal.h>
typedef struct sigaction sigaction_t;
typedef struct __darwin_i386_exception_state exception_state;
typedef struct __darwin_i386_thread_state thread_state;
typedef struct __darwin_mmst_reg mmst_reg;
typedef struct __darwin_xmm_reg xmm_reg;
typedef struct __darwin_i386_float_state float_state;

namespace Posix
{
namespace Signal
{
//-- forward type declarations -----------------------------------------------
struct UInt128;
struct _sigaltstack;
//-- type declarations -------------------------------------------------------
typedef int *Psig_atomic_t;

typedef unsigned *Psigset_t;

typedef void __cdecl (*TSignalEventStartProc)(sigval param);

typedef sigevent *Psigevent;

struct DECLSPEC_DRECORD _DRECORD_ALIGNAS(16) UInt128
{
public:
	unsigned __int64 __high;
	unsigned __int64 __low;
};


struct DECLSPEC_DRECORD _sigaltstack
{
public:
	void *ss_sp;
	long ss_size;
	int ss_flags;
};


typedef _sigaltstack *Pstack_t;

typedef ucontext_t *Pucontext_t;

typedef siginfo_t *Psiginfo_t;

typedef void __cdecl (*TSignalHandler)(int SigNum);

typedef void __cdecl (*TSigActionHandler)(int SigNum, Psiginfo_t SigInfo, void * Context);

typedef sigaction_t *Psigaction_t;

//-- var, const, procedure ---------------------------------------------------
extern "C" int __cdecl __raise(int signal);
}	/* namespace Signal */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SignalHPP
