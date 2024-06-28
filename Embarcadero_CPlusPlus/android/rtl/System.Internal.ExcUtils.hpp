// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Internal.ExcUtils.pas' rev: 34.00 (Android)

#ifndef System_Internal_ExcutilsHPP
#define System_Internal_ExcutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.SysConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Internal
{
namespace Excutils
{
//-- forward type declarations -----------------------------------------------
struct TExceptRec;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TExceptType : unsigned char { etDivByZero, etRangeError, etIntOverflow, etInvalidOp, etZeroDivide, etOverflow, etUnderflow, etInvalidCast, etAccessViolation, etPrivilege, etControlC, etStackOverflow, etVariantError, etAssertionFailed, etExternalException, etIntfCastError, etSafeCallException, etMonitorLockException, etNoMonitorSupportException, etQuit, etCodesetConversion, etNotImplemented, etObjectDisposed };

struct DECLSPEC_DRECORD TExceptRec
{
public:
	TExceptType EClass;
	System::UnicodeString EIdent;
};


typedef System::StaticArray<TExceptRec, 28> System_Internal_Excutils__1;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::StaticArray<System::Sysutils::ExceptClass, 23> ExceptTypes;
extern DELPHI_PACKAGE System_Internal_Excutils__1 ExceptMap;
#ifndef __aarch64__
extern DELPHI_PACKAGE System::Sysutils::Exception* __fastcall GetExceptionObject(NativeUInt ExceptionAddress, NativeUInt AccessAddress, unsigned ErrorCode);
#else /* __aarch64__ */
extern DELPHI_PACKAGE System::Sysutils::Exception* __fastcall GetExceptionObject(NativeUInt ExceptionAddress, NativeUInt AccessAddress, unsigned long ErrorCode);
#endif /* __aarch64__ */
extern DELPHI_PACKAGE void __fastcall SignalConverter(NativeUInt ExceptionEIP, NativeUInt FaultAddr, NativeUInt ErrorCode);
#ifndef __aarch64__
extern DELPHI_PACKAGE unsigned __fastcall CalcThumbInstructionSize(const unsigned InstPtr);
#endif /* not __aarch64__ */
extern DELPHI_PACKAGE System::Sysutils::TSignalState __fastcall InquireSignal(int RtlSigNum);
extern DELPHI_PACKAGE void __fastcall AbandonSignalHandler(int RtlSigNum);
extern DELPHI_PACKAGE void __fastcall HookSignal(int RtlSigNum);
extern DELPHI_PACKAGE void __fastcall UnhookSignal(int RtlSigNum, bool OnlyIfHooked = true);
extern DELPHI_PACKAGE void __fastcall UnhookOSExceptions(void);
extern DELPHI_PACKAGE void __fastcall HookOSExceptions(void);
#ifndef __aarch64__
extern DELPHI_PACKAGE unsigned __fastcall MapSignal(int SigNum, NativeInt Context);
#else /* __aarch64__ */
extern DELPHI_PACKAGE unsigned long __fastcall MapSignal(int SigNum, NativeInt Context);
#endif /* __aarch64__ */
}	/* namespace Excutils */
}	/* namespace Internal */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_INTERNAL_EXCUTILS)
using namespace System::Internal::Excutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_INTERNAL)
using namespace System::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Internal_ExcutilsHPP
