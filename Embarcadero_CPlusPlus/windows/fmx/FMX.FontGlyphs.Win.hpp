// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.FontGlyphs.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Fontglyphs_WinHPP
#define Fmx_Fontglyphs_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <Winapi.Windows.hpp>
#include <FMX.Types.hpp>
#include <FMX.Surfaces.hpp>
#include <FMX.FontGlyphs.hpp>
#include <FMX.Utils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Fontglyphs
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinFontGlyphManager;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWinFontGlyphManager : public Fmx::Fontglyphs::TFontGlyphManager
{
	typedef Fmx::Fontglyphs::TFontGlyphManager inherited;
	
	
private:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TWinBitmap
	{
	public:
		tagBITMAPINFO BitmapInfo;
		HDC DC;
		HBITMAP Bitmap;
		Fmx::Utils::TAlphaColorRecArray *Bits;
		int Width;
		int Height;
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	HFONT FFont;
	TWinBitmap FMeasureBitmap;
	int FBaseline;
	TWinBitmap __fastcall CreateBitmap(const int Width, const int Height);
	void __fastcall DestroyBitmap(TWinBitmap &Bitmap);
	
protected:
	virtual void __fastcall LoadResource();
	virtual void __fastcall FreeResource();
	virtual Fmx::Fontglyphs::TFontGlyph* __fastcall DoGetGlyph(const System::UCS4String ACharacter, const Fmx::Fontglyphs::TFontGlyphSettings Settings, const bool UseColorfulPalette);
	virtual float __fastcall DoGetBaseline();
	
public:
	__fastcall TWinFontGlyphManager();
	__fastcall virtual ~TWinFontGlyphManager();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Fontglyphs */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FONTGLYPHS_WIN)
using namespace Fmx::Fontglyphs::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FONTGLYPHS)
using namespace Fmx::Fontglyphs;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Fontglyphs_WinHPP
