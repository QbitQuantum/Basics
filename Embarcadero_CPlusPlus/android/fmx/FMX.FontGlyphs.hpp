// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.FontGlyphs.pas' rev: 34.00 (Android)

#ifndef Fmx_FontglyphsHPP
#define Fmx_FontglyphsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Surfaces.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Fontglyphs
{
//-- forward type declarations -----------------------------------------------
struct TFontSettings;
class DELPHICLASS TFontGlyph;
class DELPHICLASS ETFontGlyphManagerException;
struct TFontGlyphSettingHelper /* Helper for enum 'TFontGlyphSetting' */;
class DELPHICLASS TFontGlyphManager;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TFontGlyphStyle : unsigned char { NoGlyph, HasPath, ColorGlyph };

typedef System::Set<TFontGlyphStyle, _DELPHI_SET_ENUMERATOR(TFontGlyphStyle::NoGlyph), _DELPHI_SET_ENUMERATOR(TFontGlyphStyle::ColorGlyph)> TFontGlyphStyles;

struct DECLSPEC_DRECORD TFontSettings
{
public:
	System::UnicodeString Family;
	Fmx::Graphics::TFontStyleExt Style;
	float Size;
	float Scale;
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFontGlyph : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Fmx::Surfaces::TBitmapSurface* FBitmap;
	Fmx::Graphics::TPathData* FPath;
	System::Types::TPoint FOrigin;
	float FAdvance;
	float FVerticalAvance;
	TFontGlyphStyles FStyle;
	
public:
	__fastcall TFontGlyph(const System::Types::TPoint &AOrigin, const float AAdvance, const float AVertAdvance, const TFontGlyphStyles AStyle);
	__fastcall virtual ~TFontGlyph();
	__property Fmx::Surfaces::TBitmapSurface* Bitmap = {read=FBitmap};
	__property Fmx::Graphics::TPathData* Path = {read=FPath};
	__property System::Types::TPoint Origin = {read=FOrigin};
	__property float Advance = {read=FAdvance};
	__property float VerticalAdvance = {read=FVerticalAvance};
	__property TFontGlyphStyles Style = {read=FStyle, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ETFontGlyphManagerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETFontGlyphManagerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETFontGlyphManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETFontGlyphManagerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETFontGlyphManagerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETFontGlyphManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETFontGlyphManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETFontGlyphManagerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETFontGlyphManagerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETFontGlyphManagerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETFontGlyphManagerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETFontGlyphManagerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETFontGlyphManagerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETFontGlyphManagerException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum class DECLSPEC_DENUM TFontGlyphSetting : unsigned char { Bitmap, PremultipliedAlpha, Path, gsBitmap _DEPRECATED_ATTRIBUTE3("Use TFontGlyphSetting.Bitmap")  = 0x0, gsPremultipliedAlpha _DEPRECATED_ATTRIBUTE3("Use TFontGlyphSetting.PremultipliedAlpha")  = 0x1, gsPath _DEPRECATED_ATTRIBUTE3("Use TFontGlyphSetting.Path")  = 0x2 };

typedef System::Set<TFontGlyphSetting, _DELPHI_SET_ENUMERATOR(TFontGlyphSetting::Bitmap), _DELPHI_SET_ENUMERATOR(TFontGlyphSetting::Path)> TFontGlyphSettings;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFontGlyphManager : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef bool __fastcall (*TCharacterHandleFunction)(const System::UCS4String Character);
	
	
private:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TMethodDescriptor
	{
	public:
		TFontGlyphManager::TCharacterHandleFunction Method;
		bool OverrideValue;
		static TFontGlyphManager::TMethodDescriptor __fastcall Create(TFontGlyphManager::TCharacterHandleFunction AMethod, bool AOverrideValue);
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
private:
	static TFontGlyphManager* FCurrentManager;
	static TFontGlyphManager* __fastcall InternalGetFontGlyphManager();
	TFontSettings FCurrentSettings;
	
protected:
	bool __fastcall HasGlyph(const System::UCS4String ACharacter);
	virtual void __fastcall LoadResource() = 0 ;
	virtual void __fastcall FreeResource() = 0 ;
	virtual TFontGlyph* __fastcall DoGetGlyph(const System::UCS4String ACharacter, const TFontGlyphSettings Settings, const bool UseColorfulPalette) = 0 ;
	virtual float __fastcall DoGetBaseline() = 0 ;
	__property TFontSettings CurrentSettings = {read=FCurrentSettings};
	
public:
	__fastcall virtual ~TFontGlyphManager();
	__classmethod void __fastcall UnInitialize();
	TFontGlyph* __fastcall GetGlyph(const System::UCS4String ACharacter, Fmx::Graphics::TFont* const Font, const float Scale, const TFontGlyphSettings Settings);
	float __fastcall GetBaseline(Fmx::Graphics::TFont* const Font, const float Scale);
	/* static */ __property TFontGlyphManager* Current = {read=InternalGetFontGlyphManager};
	
private:
	static System::Generics::Collections::TList__1<TMethodDescriptor>* FMethods;
	
protected:
	virtual bool __fastcall IsColorfulCharacter(const System::UCS4String ACharacter);
	
public:
	static void __fastcall RegisterCharacterHandleMethod(const TCharacterHandleFunction Method, const bool OverrideValue = false);
	static void __fastcall UnRegisterCharacterHandleMethod(const TCharacterHandleFunction Method);
public:
	/* TObject.Create */ inline __fastcall TFontGlyphManager() : System::TObject() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::StaticArray<int, 1311> EmojiCodes120;
extern DELPHI_PACKAGE System::StaticArray<int, 218> UnqualifiedEmoji;
extern DELPHI_PACKAGE bool __fastcall IsEmojiPresentation(const System::UCS4String ACharacter);
}	/* namespace Fontglyphs */
}	/* namespace Fmx */
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
#endif	// Fmx_FontglyphsHPP
