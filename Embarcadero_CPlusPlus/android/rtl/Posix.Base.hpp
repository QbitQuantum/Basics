// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Base.pas' rev: 34.00 (Android)

#ifndef Posix_BaseHPP
#define Posix_BaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace Posix
{
namespace Base
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
#ifndef __aarch64__
#define libc u"/system/lib/libc.so"
#define libpthread u"/system/lib/libc.so"
#define libdl u"/system/lib/libdl.so"
#else /* __aarch64__ */
#define libc u"/system/lib64/libc.so"
#define libpthread u"/system/lib64/libc.so"
#define libdl u"/system/lib64/libdl.so"
#endif /* __aarch64__ */
#define _INODE_SUFFIX u""
}	/* namespace Base */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_BaseHPP
