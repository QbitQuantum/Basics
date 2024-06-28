// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Signal.pas' rev: 34.00 (Android)

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
typedef struct sigcontext sigcontext_t;

namespace Posix
{
namespace Signal
{
//-- forward type declarations -----------------------------------------------
struct sigev_thread_t;
struct ucontext_t;
//-- type declarations -------------------------------------------------------
typedef int *Psig_atomic_t;

#ifndef __aarch64__
typedef unsigned *Psigset_t;
#else /* __aarch64__ */
typedef unsigned long *Psigset_t;
#endif /* __aarch64__ */

typedef sigval sigval_t;

typedef sigval *Psigval;

typedef void __cdecl (*TSignalEventStartProc)(sigval param);

struct DECLSPEC_DRECORD sigev_thread_t
{
public:
	TSignalEventStartProc _function;
	void *_attribute;
};


typedef sigevent *Psigevent;

typedef siginfo_t *Psiginfo_t;

typedef void __cdecl (*TSignalHandler)(int SigNum);

typedef void __cdecl (*TRestoreHandler)(void);

typedef void __cdecl (*TSigActionHandler)(int SigNum, Psiginfo_t SigInfo, void * Context);

typedef sigaction_t *Psigaction_t;

typedef stack_t *Pstack_t;

typedef sigcontext_t *Psigcontext_t;

typedef ucontext_t *Pucontext_t;

struct DECLSPEC_DRECORD ucontext_t
{
public:
	unsigned uc_flags;
	ucontext_t *uc_link;
	stack_t uc_stack;
#ifdef __aarch64__
	unsigned long uc_sigmask;
	System::StaticArray<System::Byte, 121> __padding;
#endif /* __aarch64__ */
	sigcontext_t uc_mcontext;
#ifndef __aarch64__
	unsigned uc_sigmask;
	unsigned __padding_rt_sigset;
#endif /* not __aarch64__ */
};


//-- var, const, procedure ---------------------------------------------------
extern "C" int __cdecl __raise(int signal);
}	/* namespace Signal */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SignalHPP
