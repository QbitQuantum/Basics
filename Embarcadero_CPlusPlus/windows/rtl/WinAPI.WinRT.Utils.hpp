// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'WinAPI.WinRT.Utils.pas' rev: 34.00 (Windows)

#ifndef Winapi_Winrt_UtilsHPP
#define Winapi_Winrt_UtilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Winrt
{
namespace Utils
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TApplicationProcessMessagesProc)(void);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall Await(const System::_di_IInterface asyncInfo, const TApplicationProcessMessagesProc AApplicationProcessMessage);
extern DELPHI_PACKAGE System::TDateTime __fastcall DateTimeToTDateTime(const Winapi::Commontypes::DateTime &ADateTime);
extern DELPHI_PACKAGE Winapi::Commontypes::DateTime __fastcall TDateTimeToDateTime(const System::TDateTime ADateTime);
}	/* namespace Utils */
}	/* namespace Winrt */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WINRT_UTILS)
using namespace Winapi::Winrt::Utils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WINRT)
using namespace Winapi::Winrt;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Winrt_UtilsHPP
