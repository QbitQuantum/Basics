// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Graphics.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Graphics_IosHPP
#define Fmx_Graphics_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <FMX.Surfaces.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Platform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Graphics
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBitmapCodecQuartz;
class DELPHICLASS TCocoaTouchGraphicServices;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBitmapCodecQuartz : public Fmx::Graphics::TCustomBitmapCodec
{
	typedef Fmx::Graphics::TCustomBitmapCodec inherited;
	
private:
	static void *FColorSpace;
	
private:
	// __classmethod void __fastcall ReleaseColorSpace@();
	
private:
	bool __fastcall ImageToSurface(const void * Img, Fmx::Surfaces::TBitmapSurface* const Bitmap, const unsigned MaxSizeLimit);
	bool __fastcall SurfaceToCGBitmap(Fmx::Surfaces::TBitmapSurface* const ABitmap, /* out */ void * &ABitmapCtx);
	
protected:
	static void * __fastcall ColorSpace();
	
public:
	__classmethod virtual System::Types::TPointF __fastcall GetImageSize(const System::UnicodeString AFileName);
	__classmethod virtual bool __fastcall IsValid(System::Classes::TStream* const AStream);
	virtual bool __fastcall LoadFromFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const Bitmap, const unsigned MaxSizeLimit);
	virtual bool __fastcall LoadThumbnailFromFile(const System::UnicodeString AFileName, const float AFitWidth, const float AFitHeight, const bool UseEmbedded, Fmx::Surfaces::TBitmapSurface* const Bitmap);
	virtual bool __fastcall SaveToFile(const System::UnicodeString AFileName, Fmx::Surfaces::TBitmapSurface* const Bitmap, const Fmx::Graphics::PBitmapCodecSaveParams SaveParams);
	virtual bool __fastcall LoadFromStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const Bitmap, const unsigned MaxSizeLimit);
	virtual bool __fastcall SaveToStream(System::Classes::TStream* const AStream, Fmx::Surfaces::TBitmapSurface* const Bitmap, const System::UnicodeString Extension, const Fmx::Graphics::PBitmapCodecSaveParams SaveParams);
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TBitmapCodecQuartz() : Fmx::Graphics::TCustomBitmapCodec() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBitmapCodecQuartz() { }
	
};


class PASCALIMPLEMENTATION TCocoaTouchGraphicServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	void __fastcall RegisterServices();
	void __fastcall UnregisterServices();
	
public:
	__fastcall TCocoaTouchGraphicServices();
	__fastcall virtual ~TCocoaTouchGraphicServices();
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Graphics */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_GRAPHICS_IOS)
using namespace Fmx::Graphics::Ios;
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
#endif	// Fmx_Graphics_IosHPP
