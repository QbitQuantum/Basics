// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.FontGlyphs.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Fontglyphs_IosHPP
#define Fmx_Fontglyphs_IosHPP

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
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreText.hpp>
#include <iOSapi.UIKit.hpp>
#include <FMX.Types.hpp>
#include <FMX.Surfaces.hpp>
#include <FMX.FontGlyphs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Fontglyphs
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIOSFontGlyphManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIOSFontGlyphManager : public Fmx::Fontglyphs::TFontGlyphManager
{
	typedef Fmx::Fontglyphs::TFontGlyphManager inherited;
	
public:
	static constexpr System::Word BoundsLimit = System::Word(0xffff);
	
	
private:
	void *FColorSpace;
	void *FFontRef;
	void *FColoredEmojiFontRef;
	float FDefaultBaseline;
	float FDefaultVerticalAdvance;
	void __fastcall GetDefaultBaseline();
	void * __fastcall GetFontDescriptor();
	void * __fastcall CGColorCreate(const System::Uitypes::TAlphaColor AColor);
	void * __fastcall CTFrameCreate(const void * APath, const System::UnicodeString ACharacter);
	
protected:
	virtual void __fastcall LoadResource();
	virtual void __fastcall FreeResource();
	virtual Fmx::Fontglyphs::TFontGlyph* __fastcall DoGetGlyph(const System::UCS4String ACharacter, const Fmx::Fontglyphs::TFontGlyphSettings Settings, const bool UseColorfulPalette);
	virtual float __fastcall DoGetBaseline();
	virtual bool __fastcall IsColorfulCharacter(const System::UCS4String ACharacter);
	
public:
	__fastcall TIOSFontGlyphManager();
	__fastcall virtual ~TIOSFontGlyphManager();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Fontglyphs */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FONTGLYPHS_IOS)
using namespace Fmx::Fontglyphs::Ios;
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
#endif	// Fmx_Fontglyphs_IosHPP
