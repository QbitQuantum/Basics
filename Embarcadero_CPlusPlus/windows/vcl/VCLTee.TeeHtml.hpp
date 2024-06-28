// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeHtml.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeehtmlHPP
#define Vcltee_TeehtmlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teehtml
{
//-- forward type declarations -----------------------------------------------
struct TSize;
//-- type declarations -------------------------------------------------------
#pragma pack(push,1)
struct DECLSPEC_DRECORD TSize
{
public:
	int Width;
	int Height;
};
#pragma pack(pop)


typedef int TCoordinate;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Vcl::Graphics::TGraphic* __fastcall (*GraphicFileExtension)(const System::UnicodeString FileExtension);
extern DELPHI_PACKAGE int __fastcall (*GraphicDownload)(const System::UnicodeString URL, System::Classes::TStream* Stream);
extern DELPHI_PACKAGE int __fastcall HtmlMultiLineTextHeight(Vcltee::Tecanvas::TTeeCanvas* const ACanvas, System::UnicodeString S, /* out */ int &NumLines);
extern DELPHI_PACKAGE TSize __fastcall HtmlTextExtent(Vcltee::Tecanvas::TTeeCanvas* const ACanvas, const System::UnicodeString Text);
extern DELPHI_PACKAGE void __fastcall HtmlTextOut(Vcltee::Tecanvas::TTeeCanvas* const ACanvas, const int x, const int y, System::UnicodeString Text);
}	/* namespace Teehtml */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEHTML)
using namespace Vcltee::Teehtml;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeehtmlHPP
