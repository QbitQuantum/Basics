// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.Helpers.pas' rev: 34.00 (iOS)

#ifndef Macapi_HelpersHPP
#define Macapi_HelpersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Helpers
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void * __fastcall NSObjectToID(const Iosapi::Foundation::_di_NSObject AObject);
extern DELPHI_PACKAGE int __fastcall GetTimeZone(void);
extern DELPHI_PACKAGE System::TDateTime __fastcall GetGMTDateTime(const System::TDateTime ADateTime);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSDate __fastcall DateTimeToNSDate(const System::TDateTime ADateTime, bool AUseTimeZone = false);
extern DELPHI_PACKAGE System::TDateTime __fastcall NSDateToDateTime(const Iosapi::Foundation::_di_NSDate ADate, bool AUseTimeZone = false);
extern DELPHI_PACKAGE System::TDate __fastcall NSDateToDate(const Iosapi::Foundation::_di_NSDate ADateTime);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall StrToNSStr(const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall NSStrToStr(const Iosapi::Foundation::_di_NSString ASource);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSURL __fastcall StrToNSUrl(const System::UnicodeString AStr);
extern DELPHI_PACKAGE System::UnicodeString __fastcall NSUrlToStr(const Iosapi::Foundation::_di_NSURL AUrl);
extern DELPHI_PACKAGE System::UnicodeString __fastcall CFStringRefToStr(const CFStringRef ASource);
extern DELPHI_PACKAGE void * __fastcall NSStringToID(const Iosapi::Foundation::_di_NSString ASource);
extern DELPHI_PACKAGE void * __fastcall StringToID(const System::UnicodeString ASource);
extern DELPHI_PACKAGE Iosapi::Foundation::NSRect __fastcall CGRectFromRect(const System::Types::TRectF &R);
extern DELPHI_PACKAGE Iosapi::Foundation::NSRect __fastcall RectToNSRect(const System::Types::TRect &R);
extern DELPHI_PACKAGE System::UnicodeString __fastcall CFErrorRefToDescription(const CFErrorRef AError);
}	/* namespace Helpers */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_HELPERS)
using namespace Macapi::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_HelpersHPP
