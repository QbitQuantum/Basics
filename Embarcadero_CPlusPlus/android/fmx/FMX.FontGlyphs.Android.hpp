// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.FontGlyphs.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Fontglyphs_AndroidHPP
#define Fmx_Fontglyphs_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.FontGlyphs.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Fontglyphs
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidFontGlyphManager;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidFontGlyphManager : public Fmx::Fontglyphs::TFontGlyphManager
{
	typedef Fmx::Fontglyphs::TFontGlyphManager inherited;
	
private:
	Androidapi::Jni::Graphicscontentviewtext::_di_JPaint FPaint;
	int FTop;
	int FAscent;
	int FDescent;
	int FBottom;
	int FLeading;
	
protected:
	virtual void __fastcall LoadResource();
	virtual void __fastcall FreeResource();
	virtual Fmx::Fontglyphs::TFontGlyph* __fastcall DoGetGlyph(const System::UCS4String ACharacter, const Fmx::Fontglyphs::TFontGlyphSettings Settings, const bool UseColorfulPalette);
	virtual float __fastcall DoGetBaseline();
	virtual bool __fastcall IsColorfulCharacter(const System::UCS4String ACharacter);
	
public:
	__fastcall TAndroidFontGlyphManager();
	__fastcall virtual ~TAndroidFontGlyphManager();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Fontglyphs */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FONTGLYPHS_ANDROID)
using namespace Fmx::Fontglyphs::Android;
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
#endif	// Fmx_Fontglyphs_AndroidHPP
