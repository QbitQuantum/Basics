// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.ShareMem.pas' rev: 34.00 (Windows)

#ifndef System_SharememHPP
#define System_SharememHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Sharemem
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void * __fastcall SysGetMem(NativeInt Size);
extern DELPHI_PACKAGE int __fastcall SysFreeMem(void * P);
extern DELPHI_PACKAGE void * __fastcall SysReallocMem(void * P, NativeInt Size);
extern "C" System::THeapStatus __fastcall GetHeapStatus();
extern "C" int __fastcall GetAllocMemCount();
extern "C" int __fastcall GetAllocMemSize();
extern "C" void __fastcall DumpBlocks();
extern DELPHI_PACKAGE void __fastcall HeapAddRef();
extern DELPHI_PACKAGE void __fastcall HeapRelease();
extern DELPHI_PACKAGE void * __fastcall SysAllocMem(NativeInt Size);
extern DELPHI_PACKAGE bool __fastcall SysRegisterExpectedMemoryLeak(void * P);
extern DELPHI_PACKAGE bool __fastcall SysUnregisterExpectedMemoryLeak(void * P);
}	/* namespace Sharemem */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_SHAREMEM)
using namespace System::Sharemem;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_SharememHPP
