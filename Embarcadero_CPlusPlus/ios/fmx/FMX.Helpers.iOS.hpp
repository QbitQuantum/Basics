// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Helpers.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Helpers_IosHPP
#define Fmx_Helpers_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreText.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Surfaces.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Helpers
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIApplication __fastcall SharedApplication(void);
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIScreen __fastcall MainScreen(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSNotificationCenter __fastcall DefaultNotificationCenter(void);
extern DELPHI_PACKAGE bool __fastcall IsPhone(void);
extern DELPHI_PACKAGE bool __fastcall IsPad(void);
extern DELPHI_PACKAGE Fmx::Graphics::TBitmap* __fastcall UIImageToBitmap(const Iosapi::Uikit::_di_UIImage AImage, const float ARotate, const System::Types::TSize &AMaxSize);
extern DELPHI_PACKAGE Fmx::Surfaces::TBitmapSurface* __fastcall UIImageToBitmapSurface(const Iosapi::Uikit::_di_UIImage AImage);
extern DELPHI_PACKAGE bool __fastcall NativeViewToSurface(const Iosapi::Uikit::_di_UIView ANativeView, Fmx::Surfaces::TBitmapSurface* const ASurface);
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIImage __fastcall UIViewToUIImage(const Iosapi::Uikit::_di_UIView AView);
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIImage __fastcall BitmapToUIImage(Fmx::Graphics::TBitmap* const Bitmap);
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIImage __fastcall BitmapSurfaceToUIImage(Fmx::Surfaces::TBitmapSurface* const BitmapSurface);
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIColor __fastcall AlphaColorToUIColor(const System::Uitypes::TAlphaColor Color);
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor __fastcall UIColorToAlphaColor(const Iosapi::Uikit::_di_UIColor Color);
extern DELPHI_PACKAGE long __fastcall TextAlignToUITextAlignment(const Fmx::Types::TTextAlign ATextAlignment);
extern DELPHI_PACKAGE long __fastcall VirtualKeyboardTypeToUIKeyboardType(const Fmx::Types::TVirtualKeyboardType AVirtualKeyboardType);
extern DELPHI_PACKAGE long __fastcall ReturnKeyTypeToUIReturnKeyType(const Fmx::Types::TReturnKeyType AReturnKeyType);
extern DELPHI_PACKAGE Iosapi::Uikit::_di_UIFont __fastcall FontToUIFont(Fmx::Graphics::TFont* const AFont);
extern DELPHI_PACKAGE void * __fastcall FontToCTFontRef(Fmx::Graphics::TFont* const AFont);
extern DELPHI_PACKAGE long __fastcall ScreenOrientationToUIInterfaceOrientation(const Fmx::Types::TScreenOrientations ASource);
extern DELPHI_PACKAGE long __fastcall GetUserInterfaceStyle(void);
}	/* namespace Ios */
}	/* namespace Helpers */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS_IOS)
using namespace Fmx::Helpers::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS)
using namespace Fmx::Helpers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Helpers_IosHPP
