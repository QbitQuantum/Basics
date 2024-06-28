// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.PsAPI.pas' rev: 34.00 (Windows)

#ifndef Winapi_PsapiHPP
#define Winapi_PsapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <psapi.h>

namespace Winapi
{
namespace Psapi
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void * *PPointer;

typedef System::LongBool __stdcall (*TEnumProcesses)(unsigned* lpidProcess, unsigned cb, unsigned &cbNeeded);

typedef System::LongBool __stdcall (*TEnumProcessModules)(NativeUInt hProcess, Winapi::Windows::PHMODULE lphModule, unsigned cb, unsigned &lpcbNeeded);

typedef unsigned __stdcall (*TGetModuleBaseNameA)(NativeUInt hProcess, NativeUInt hModule, char * lpBaseName, unsigned nSize);

typedef unsigned __stdcall (*TGetModuleBaseNameW)(NativeUInt hProcess, NativeUInt hModule, System::WideChar * lpBaseName, unsigned nSize);

typedef TGetModuleBaseNameW TGetModuleBaseName;

typedef unsigned __stdcall (*TGetModuleFileNameExA)(NativeUInt hProcess, NativeUInt hModule, char * lpFilename, unsigned nSize);

typedef unsigned __stdcall (*TGetModuleFileNameExW)(NativeUInt hProcess, NativeUInt hModule, System::WideChar * lpFilename, unsigned nSize);

typedef TGetModuleFileNameExW TGetModuleFileNameEx;

typedef _MODULEINFO TModuleInfo;

typedef LPMODULEINFO PModuleInfo;

typedef System::LongBool __stdcall (*TGetModuleInformation)(NativeUInt hProcess, NativeUInt hModule, LPMODULEINFO lpmodinfo, unsigned cb);

typedef System::LongBool __stdcall (*TEmptyWorkingSet)(NativeUInt hProcess);

typedef System::LongBool __stdcall (*TQueryWorkingSet)(NativeUInt hProcess, void * pv, unsigned cb);

typedef System::LongBool __stdcall (*TInitializeProcessForWsWatch)(NativeUInt hProcess);

typedef _PSAPI_WS_WATCH_INFORMATION TPSAPIWsWatchInformation;

typedef PPSAPI_WS_WATCH_INFORMATION PPSAPIWsWatchInformation;

typedef System::LongBool __stdcall (*TGetWsChanges)(NativeUInt hProcess, PPSAPI_WS_WATCH_INFORMATION lpWatchInfo, unsigned cb);

typedef unsigned __stdcall (*TGetMappedFileNameA)(NativeUInt hProcess, void * lpv, char * lpFilename, unsigned nSize);

typedef unsigned __stdcall (*TGetMappedFileNameW)(NativeUInt hProcess, void * lpv, System::WideChar * lpFilename, unsigned nSize);

typedef TGetMappedFileNameW TGetMappedFileName;

typedef unsigned __stdcall (*TGetDeviceDriverBaseNameA)(void * ImageBase, char * lpBaseName, unsigned nSize);

typedef unsigned __stdcall (*TGetDeviceDriverBaseNameW)(void * ImageBase, System::WideChar * lpBaseName, unsigned nSize);

typedef TGetDeviceDriverBaseNameW TGetDeviceDriverBaseName;

typedef unsigned __stdcall (*TGetDeviceDriverFileNameA)(void * ImageBase, char * lpFileName, unsigned nSize);

typedef unsigned __stdcall (*TGetDeviceDriverFileNameW)(void * ImageBase, System::WideChar * lpFileName, unsigned nSize);

typedef TGetDeviceDriverFileNameW TGetDeviceDriverFileName;

typedef System::LongBool __stdcall (*TEnumDeviceDrivers)(PPointer lpImageBase, unsigned cb, unsigned &lpcbNeeded);

typedef _PROCESS_MEMORY_COUNTERS TProcessMemoryCounters;

typedef _PROCESS_MEMORY_COUNTERS *PProcessMemoryCounters;

typedef _PROCESS_MEMORY_COUNTERS_EX TProcessMemoryCountersEx;

typedef _PROCESS_MEMORY_COUNTERS_EX *PProcessMemoryCountersEx;

typedef System::LongBool __stdcall (*TGetProcessMemoryInfo)(NativeUInt Process, PPROCESS_MEMORY_COUNTERS ppsmemCounters, unsigned cb);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Psapi */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_PSAPI)
using namespace Winapi::Psapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_PsapiHPP
