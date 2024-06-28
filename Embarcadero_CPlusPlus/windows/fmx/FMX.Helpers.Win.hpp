// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Helpers.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Helpers_WinHPP
#define Fmx_Helpers_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <System.Math.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.ImgList.hpp>
#include <FMX.Surfaces.hpp>
#include <Winapi.D2D1.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Helpers
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TImeModeHelper;
class DELPHICLASS TWow64Redirection;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TImeModeHelper : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	#define TImeModeHelper_Imm32ModName L"imm32.dll"
	
	static NativeUInt Imm32Dll;
	static System::Classes::TStrings* FIMEs;
	static System::UnicodeString FDefaultIme;
	static HKL FDefaultKbLayout;
	__classmethod bool __fastcall Win32NLSEnableIME(HWND hWnd, bool Enable);
	static System::Classes::TStrings* __fastcall GetIMEs();
	static System::UnicodeString __fastcall GetDefaultIME();
	__classmethod void __fastcall SetImeMode(HWND Handle, Fmx::Types::TImeMode Mode);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__classmethod void __fastcall SetIme(HWND Handle, Fmx::Types::TImeMode Mode);
	__classmethod void __fastcall ResetIme(HWND Handle, Fmx::Types::TImeMode Mode);
	/* static */ __property System::UnicodeString DefaultIme = {read=GetDefaultIME};
#ifndef _WIN64
	/* static */ __property HKL DefaultKbLayout = {read=FDefaultKbLayout, nodefault};
#else /* _WIN64 */
	/* static */ __property HKL DefaultKbLayout = {read=FDefaultKbLayout};
#endif /* _WIN64 */
	/* static */ __property System::Classes::TStrings* IMEs = {read=GetIMEs};
public:
	/* TObject.Create */ inline __fastcall TImeModeHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TImeModeHelper() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWow64Redirection : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::LongBool __stdcall (*TWow64DisableWow64FsRedirection)(/* out */ System::LongBool &Wow64FsEnableRedirection);
	
	typedef System::LongBool __stdcall (*TWow64RevertWow64FsRedirection)(System::LongBool &Wow64FsEnableRedirection);
	
	typedef System::LongBool __stdcall (*TWow64EnableWow64FsRedirection)(const System::LongBool Wow64FsEnableRedirection);
	
	
private:
	static System::LongBool FOldValue;
	static int FDisableCount;
	static TWow64Redirection* FCurrent;
	static bool FRedirectLoaded;
	static TWow64DisableWow64FsRedirection Wow64DisableWow64FsRedirection;
	static TWow64RevertWow64FsRedirection Wow64RevertWow64FsRedirection;
	static TWow64EnableWow64FsRedirection Wow64EnableWow64FsRedirection;
	static bool __fastcall RedirectLoad();
	static TWow64Redirection* __fastcall GetCurrent();
	
public:
	/* static */ __property TWow64Redirection* Current = {read=GetCurrent};
	bool __fastcall Disable();
	bool __fastcall Restore();
	bool __fastcall SetEnable(const bool Value);
public:
	/* TObject.Create */ inline __fastcall TWow64Redirection() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWow64Redirection() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
static const System::Word CN_BASE = System::Word(0x1000);
static const System::Word CN_CTLCOLORMSGBOX = System::Word(0x1132);
static const System::Word CN_CTLCOLOREDIT = System::Word(0x1133);
static const System::Word CN_CTLCOLORLISTBOX = System::Word(0x1134);
static const System::Word CN_CTLCOLORBTN = System::Word(0x1135);
static const System::Word CN_CTLCOLORDLG = System::Word(0x1136);
static const System::Word CN_CTLCOLORSCROLLBAR = System::Word(0x1137);
static const System::Word CN_CTLCOLORSTATIC = System::Word(0x1138);
static const System::Word WM_ADDUPDATERECT = System::Word(0x47b);
static const System::Word WM_RELEASEFORM = System::Word(0x47d);
static const System::Word WM_NCADDUPDATERECT = System::Word(0x47e);
static const System::Word WM_CLOSEMENU = System::Word(0x47f);
static const System::Int8 StandardDpi = System::Int8(0x60);
extern DELPHI_PACKAGE HBITMAP __fastcall BitmapToWinBitmap(Fmx::Graphics::TBitmap* const Bitmap, const bool RemoveBlackPixel)/* overload */;
extern DELPHI_PACKAGE HBITMAP __fastcall BitmapToWinBitmap(Fmx::Graphics::TBitmap* const Bitmap, const System::Uitypes::TAlphaColor Background)/* overload */;
extern DELPHI_PACKAGE HBITMAP __fastcall BitmapToMenuBitmap(const bool TopLevel, Fmx::Graphics::TBitmap* const Bitmap);
extern DELPHI_PACKAGE HBITMAP __fastcall ImageListToMenuBitmap(const bool TopLevel, Fmx::Imglist::TCustomImageList* const Images, const int Index);
extern DELPHI_PACKAGE HICON __fastcall BitmapToIcon(Fmx::Graphics::TBitmap* const Bitmap);
extern DELPHI_PACKAGE Fmx::Surfaces::TBitmapSurface* __fastcall DIBDataToBitmapSurface(void * DataPtr);
extern DELPHI_PACKAGE System::Classes::TShiftState __fastcall KeysToShiftState(int Keys);
extern DELPHI_PACKAGE System::Classes::TShiftState __fastcall MouseToShiftState(int Keys);
extern DELPHI_PACKAGE System::Classes::TShiftState __fastcall KeyDataToShiftState(int KeyData);
extern DELPHI_PACKAGE void __fastcall ShortCutToKey(const System::Classes::TShortCut ShortCut, System::Word &Key, System::Classes::TShiftState &Shift);
extern DELPHI_PACKAGE System::UnicodeString __fastcall ShortCutToText(const System::Classes::TShortCut ShortCut);
extern DELPHI_PACKAGE int __fastcall TextToShortCut(System::UnicodeString Text);
extern DELPHI_PACKAGE void __fastcall CheckWinapiResult(const bool AResult, const System::UnicodeString AdditionalInfo = System::UnicodeString())/* overload */;
extern DELPHI_PACKAGE NativeUInt __fastcall CheckWinapiHandle(const NativeUInt AHandle, const System::UnicodeString AdditionalInfo = System::UnicodeString());
extern DELPHI_PACKAGE void __fastcall EnableTaskWindows(void * WindowList);
extern DELPHI_PACKAGE HWND __fastcall FindTopMostWindow(HWND ActiveWindow);
extern DELPHI_PACKAGE void * __fastcall DisableTaskWindows(HWND ActiveWindow);
extern DELPHI_PACKAGE unsigned __fastcall NewUniqueMenuCommand(void);
extern DELPHI_PACKAGE void __fastcall FreeUniqueMenuCommand(unsigned Id);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetHWNDText(const HWND AWnd);
extern DELPHI_PACKAGE float __fastcall GetDCScale(const HDC DC);
extern DELPHI_PACKAGE float __fastcall GetWndScale(const HWND Wnd);
extern DELPHI_PACKAGE DWRITE_FONT_WEIGHT __fastcall FontWeightToDWrite(const Fmx::Graphics::TFontWeight AWeight);
extern DELPHI_PACKAGE Fmx::Graphics::TFontWeight __fastcall DWriteFontWeightToWeight(const DWRITE_FONT_WEIGHT AWeight);
extern DELPHI_PACKAGE unsigned __fastcall FontWeightToWinapi(const Fmx::Graphics::TFontWeight AWeight);
extern DELPHI_PACKAGE Fmx::Graphics::TFontWeight __fastcall WinapiWeightToFontWeight(const unsigned AWeight);
extern DELPHI_PACKAGE DWRITE_FONT_STRETCH __fastcall FontStretchToDWrite(const Fmx::Graphics::TFontStretch AStretch);
extern DELPHI_PACKAGE Fmx::Graphics::TFontStretch __fastcall DWriteFontStretchToStretch(const DWRITE_FONT_STRETCH AStretch);
extern DELPHI_PACKAGE DWRITE_FONT_STYLE __fastcall FontSlantToDWrite(const Fmx::Graphics::TFontSlant ASlant);
extern DELPHI_PACKAGE Fmx::Graphics::TFontSlant __fastcall DWriteFontStyleToSlant(const DWRITE_FONT_STYLE ASlant);
}	/* namespace Win */
}	/* namespace Helpers */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_HELPERS_WIN)
using namespace Fmx::Helpers::Win;
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
#endif	// Fmx_Helpers_WinHPP
