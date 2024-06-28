// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Graphics.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Graphics_AndroidHPP
#define Fmx_Graphics_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <FMX.Surfaces.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Platform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Graphics
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBitmapCodecAndroid;
class DELPHICLASS TAndroidGraphicsServices;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBitmapCodecAndroid : public Fmx::Graphics::TCustomBitmapCodec
{
	typedef Fmx::Graphics::TCustomBitmapCodec inherited;
	
private:
	static constexpr System::Int8 DefaultSaveQuality = System::Int8(0x4b);
	
	__classmethod System::Types::TPoint __fastcall GetMovieSize(const System::UnicodeString FileName)/* overload */;
	__classmethod System::Types::TPoint __fastcall GetMovieSize(System::Classes::TStream* const Stream)/* overload */;
	__classmethod bool __fastcall IsGIFStream(System::Classes::TStream* const Stream);
	bool __fastcall LoadMovieFromStream(System::Classes::TStream* const Stream, Fmx::Surfaces::TBitmapSurface* const Surface);
	bool __fastcall LoadMovieFromFile(const System::UnicodeString FileName, Fmx::Surfaces::TBitmapSurface* const Surface);
	bool __fastcall LoadMovieFromFileScaled(const System::UnicodeString FileName, Fmx::Surfaces::TBitmapSurface* const Surface, const System::Types::TPoint &FitSize);
	bool __fastcall StretchIfNeed(const Androidapi::Jni::Graphicscontentviewtext::_di_JBitmap SrcBitmap, Fmx::Surfaces::TBitmapSurface* const Bitmap, const Androidapi::Jni::Graphicscontentviewtext::_di_JBitmapFactory_Options LoadOptions, const unsigned MaxSizeLimit);
	
public:
	__classmethod virtual System::Types::TPointF __fastcall GetImageSize(const System::UnicodeString AFileName);
	__classmethod virtual bool __fastcall IsValid(System::Classes::TStream* const AStream);
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const Bitmap, const unsigned MaxSizeLimit);
	virtual bool __fastcall LoadThumbnailFromFile(const System::UnicodeString AFileName, const float AFitWidth, const float AFitHeight, const bool UseEmbedded, Fmx::Surfaces::TBitmapSurface* const Bitmap);
	virtual bool __fastcall SaveToFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const Bitmap, const Fmx::Graphics::PBitmapCodecSaveParams SaveParams);
	virtual bool __fastcall LoadFromStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const Bitmap, const unsigned MaxSizeLimit);
	virtual bool __fastcall SaveToStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const Bitmap, const System::UnicodeString Extension, const Fmx::Graphics::PBitmapCodecSaveParams SaveParams);
public:
	/* TObject.Create */ inline __fastcall TBitmapCodecAndroid() : Fmx::Graphics::TCustomBitmapCodec() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBitmapCodecAndroid() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidGraphicsServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	void __fastcall RegisterServices();
	void __fastcall UnregisterServices();
	
public:
	__fastcall TAndroidGraphicsServices();
	__fastcall virtual ~TAndroidGraphicsServices();
	void __fastcall RegisterContextClasses();
	void __fastcall UnregisterContextClasses();
	void __fastcall RegisterCanvasClasses();
	void __fastcall UnregisterCanvasClasses();
private:
	void *__IFMXCanvasService;	// Fmx::Platform::IFMXCanvasService 
	void *__IFMXContextService;	// Fmx::Platform::IFMXContextService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {476E5E53-A77A-4ADA-93E3-CA66A8956059}
	operator Fmx::Platform::_di_IFMXCanvasService()
	{
		Fmx::Platform::_di_IFMXCanvasService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXCanvasService*(void) { return (Fmx::Platform::IFMXCanvasService*)&__IFMXCanvasService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EB6C9074-48B9-4A99-ABF4-BFB6FCF9C385}
	operator Fmx::Platform::_di_IFMXContextService()
	{
		Fmx::Platform::_di_IFMXContextService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXContextService*(void) { return (Fmx::Platform::IFMXContextService*)&__IFMXContextService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Graphics */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRAPHICS_ANDROID)
using namespace Fmx::Graphics::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRAPHICS)
using namespace Fmx::Graphics;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Graphics_AndroidHPP
