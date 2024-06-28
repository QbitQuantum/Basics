// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.TlHelp32.pas' rev: 34.00 (Windows)

#ifndef Winapi_Tlhelp32HPP
#define Winapi_Tlhelp32HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <tlhelp32.h>

namespace Winapi
{
namespace Tlhelp32
{
//-- forward type declarations -----------------------------------------------
struct tagPROCESSENTRY32A;
struct tagMODULEENTRY32A;
//-- type declarations -------------------------------------------------------
typedef NativeUInt __stdcall (*TCreateToolhelp32Snapshot)(unsigned dwFlags, unsigned th32ProcessID);

typedef tagHEAPLIST32 THeapList32;

typedef System::LongBool __stdcall (*THeap32ListFirst)(NativeUInt hSnapshot, tagHEAPLIST32 &lphl);

typedef System::LongBool __stdcall (*THeap32ListNext)(NativeUInt hSnapshot, tagHEAPLIST32 &lphl);

typedef tagHEAPENTRY32 THeapEntry32;

typedef System::LongBool __stdcall (*THeap32First)(tagHEAPENTRY32 &lphe, unsigned th32ProcessID, NativeUInt th32HeapID);

typedef System::LongBool __stdcall (*THeap32Next)(tagHEAPENTRY32 &lphe);

typedef System::LongBool __stdcall (*TToolhelp32ReadProcessMemory)(unsigned th32ProcessID, void * lpBaseAddress, void *lpBuffer, NativeUInt cbRead, NativeUInt &lpNumberOfBytesRead);

struct DECLSPEC_DRECORD tagPROCESSENTRY32A
{
public:
	unsigned dwSize;
	unsigned cntUsage;
	unsigned th32ProcessID;
	NativeUInt th32DefaultHeapID;
	unsigned th32ModuleID;
	unsigned cntThreads;
	unsigned th32ParentProcessID;
	int pcPriClassBase;
	unsigned dwFlags;
	System::StaticArray<char, 260> szExeFile;
};


typedef tagPROCESSENTRY32A PROCESSENTRY32A;

typedef tagPROCESSENTRY32A *PPROCESSENTRY32A;

typedef tagPROCESSENTRY32A *LPPROCESSENTRY32A;

typedef tagPROCESSENTRY32A TProcessEntry32A;

typedef System::LongBool __stdcall (*TProcess32FirstA)(NativeUInt hSnapshot, tagPROCESSENTRY32A &lppe);

typedef System::LongBool __stdcall (*TProcess32NextA)(NativeUInt hSnapshot, tagPROCESSENTRY32A &lppe);

typedef tagPROCESSENTRY32W TProcessEntry32W;

typedef System::LongBool __stdcall (*TProcess32FirstW)(NativeUInt hSnapshot, tagPROCESSENTRY32W &lppe);

typedef System::LongBool __stdcall (*TProcess32NextW)(NativeUInt hSnapshot, tagPROCESSENTRY32W &lppe);

typedef tagPROCESSENTRY32W PROCESSENTRY32;

typedef tagPROCESSENTRY32W TProcessEntry32;

typedef TProcess32FirstW TProcess32First;

typedef TProcess32NextW TProcess32Next;

typedef tagTHREADENTRY32 TThreadEntry32;

typedef System::LongBool __stdcall (*TThread32First)(NativeUInt hSnapshot, tagTHREADENTRY32 &lpte);

typedef System::LongBool __stdcall (*TThread32Next)(NativeUInt hSnapshot, tagTHREADENTRY32 &lpte);

struct DECLSPEC_DRECORD tagMODULEENTRY32A
{
public:
	unsigned dwSize;
	unsigned th32ModuleID;
	unsigned th32ProcessID;
	unsigned GlblcntUsage;
	unsigned ProccntUsage;
	System::Byte *modBaseAddr;
	unsigned modBaseSize;
	NativeUInt hModule;
	System::StaticArray<char, 256> szModule;
	System::StaticArray<char, 260> szExePath;
};


typedef tagMODULEENTRY32A MODULEENTRY32A;

typedef tagMODULEENTRY32A *PMODULEENTRY32A;

typedef tagMODULEENTRY32A *LPMODULEENTRY32A;

typedef tagMODULEENTRY32A TModuleEntry32A;

typedef System::LongBool __stdcall (*TModule32FirstA)(NativeUInt hSnapshot, tagMODULEENTRY32A &lpme);

typedef System::LongBool __stdcall (*TModule32NextA)(NativeUInt hSnapshot, tagMODULEENTRY32A &lpme);

typedef tagMODULEENTRY32W MODULEENTRY32W;

typedef tagMODULEENTRY32W *PMODULEENTRY32W;

typedef tagMODULEENTRY32W *LPMODULEENTRY32W;

typedef tagMODULEENTRY32W TModuleEntry32W;

typedef System::LongBool __stdcall (*TModule32FirstW)(NativeUInt hSnapshot, tagMODULEENTRY32W &lpme);

typedef System::LongBool __stdcall (*TModule32NextW)(NativeUInt hSnapshot, tagMODULEENTRY32W &lpme);

typedef tagMODULEENTRY32W TModuleEntry32;

typedef TModule32FirstW TModule32First;

typedef TModule32NextW TModule32Next;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::LongBool __fastcall Process32FirstA(NativeUInt hSnapshot, tagPROCESSENTRY32A &lppe);
extern DELPHI_PACKAGE System::LongBool __fastcall Process32NextA(NativeUInt hSnapshot, tagPROCESSENTRY32A &lppe);
extern DELPHI_PACKAGE System::LongBool __fastcall Module32FirstA(NativeUInt hSnapshot, tagMODULEENTRY32A &lpme);
extern DELPHI_PACKAGE System::LongBool __fastcall Module32NextA(NativeUInt hSnapshot, tagMODULEENTRY32A &lpme);
}	/* namespace Tlhelp32 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_TLHELP32)
using namespace Winapi::Tlhelp32;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Tlhelp32HPP
