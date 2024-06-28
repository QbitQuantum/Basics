// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Html.pas' rev: 34.00 (Android)

#ifndef Fmxtee_HtmlHPP
#define Fmxtee_HtmlHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <FMX.Types.hpp>
#include <FMXTee.Canvas.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Html
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


typedef float TCoordinate;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Fmx::Graphics::TBitmap* __fastcall (*GraphicFileExtension)(const System::UnicodeString FileExtension);
extern DELPHI_PACKAGE int __fastcall (*GraphicDownload)(const System::UnicodeString URL, System::Classes::TStream* Stream);
extern DELPHI_PACKAGE int __fastcall HtmlMultiLineTextHeight(Fmxtee::Canvas::TTeeCanvas* const ACanvas, System::UnicodeString S, /* out */ int &NumLines);
extern DELPHI_PACKAGE TSize __fastcall HtmlTextExtent(Fmxtee::Canvas::TTeeCanvas* const ACanvas, const System::UnicodeString Text);
extern DELPHI_PACKAGE void __fastcall HtmlTextOut(Fmxtee::Canvas::TTeeCanvas* const ACanvas, const float x, const float y, System::UnicodeString Text);
}	/* namespace Html */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_HTML)
using namespace Fmxtee::Html;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_HtmlHPP
