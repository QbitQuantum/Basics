// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'SysInit.pas' rev: 34.00 (iOS)

#ifndef SysinitHPP
#define SysinitHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>

//-- user supplied -----------------------------------------------------------

namespace Sysinit
{
//-- forward type declarations -----------------------------------------------
struct TMachEHData;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TMachEHData
{
public:
	System::StaticArray<unsigned, 16> eh_port_masks;
	System::StaticArray<unsigned, 16> eh_ports;
	System::StaticArray<int, 16> eh_behaviors;
	System::StaticArray<int, 16> eh_flavors;
	unsigned eh_portcnt;
	int __fastcall Get(unsigned task, unsigned mask);
	void __fastcall Apply(unsigned task);
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 MAX_EXCEPTION_PORTS = System::Int8(0x10);
extern DELPHI_PACKAGE NativeInt TlsStart;
extern DELPHI_PACKAGE bool ModuleIsLib;
extern DELPHI_PACKAGE bool ModuleIsPackage;
extern DELPHI_PACKAGE bool ModuleIsCpp;
extern DELPHI_PACKAGE unsigned long TlsIndex;
extern DELPHI_PACKAGE System::Byte TlsLast;
extern DELPHI_PACKAGE NativeUInt HInstance;
extern DELPHI_PACKAGE System::TDLLProc DllProc;
extern DELPHI_PACKAGE System::TDLLProcEx DllProcEx;
extern DELPHI_PACKAGE int DataMark;
extern DELPHI_PACKAGE System::StaticArray<char, 129> CoverageLibraryName;
extern DELPHI_PACKAGE void *dbkFCallWrapperAddr;
extern DELPHI_PACKAGE int dbk_RTL_initialized;
extern DELPHI_PACKAGE unsigned __int64 ExcThreadPort;
extern DELPHI_PACKAGE unsigned RTLExceptionPort;
extern DELPHI_PACKAGE TMachEHData OrigEHData;
extern DELPHI_PACKAGE System::StaticArray<unsigned, 3> _GLOBAL_OFFSET_TABLE_;
extern DELPHI_PACKAGE void *PtrToNil;
extern DELPHI_PACKAGE void *ThreadInitProc;
extern DELPHI_PACKAGE NativeUInt __fastcall GetThisModuleHandle();
extern DELPHI_PACKAGE void __cdecl VclInit(bool isDLL, bool isPkg, NativeUInt hInst, bool isGui);
extern DELPHI_PACKAGE void __cdecl VclExit();
extern DELPHI_PACKAGE void __fastcall lldb_invoke_except_handler(System::UnicodeString ExcType);
}	/* namespace Sysinit */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSINIT)
using namespace Sysinit;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// SysinitHPP
