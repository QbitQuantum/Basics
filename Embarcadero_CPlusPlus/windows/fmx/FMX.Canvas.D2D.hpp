// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Canvas.D2D.pas' rev: 34.00 (Windows)

#ifndef Fmx_Canvas_D2dHPP
#define Fmx_Canvas_D2dHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.D3D10.hpp>
#include <Winapi.D2D1.hpp>
#include <Winapi.Wincodec.hpp>
#include <FMX.Graphics.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Canvas
{
namespace D2d
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomBitmapCodecWIC;
class DELPHICLASS TCustomCanvasD2D;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomBitmapCodecWIC : public Fmx::Graphics::TCustomBitmapCodec
{
	typedef Fmx::Graphics::TCustomBitmapCodec inherited;
	
private:
	static _di_IWICImagingFactory FImagingFactory;
	
private:
	// __classmethod void __fastcall DestroySharedResources@();
	
private:
	static _di_IWICImagingFactory __fastcall GetImagingFactory();
	
public:
	/* static */ __property _di_IWICImagingFactory ImagingFactory = {read=GetImagingFactory};
	
private:
	// __classmethod void __fastcall Create@();
public:
	/* TObject.Create */ inline __fastcall TCustomBitmapCodecWIC() : Fmx::Graphics::TCustomBitmapCodec() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCustomBitmapCodecWIC() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomCanvasD2D : public Fmx::Graphics::TCanvas
{
	typedef Fmx::Graphics::TCanvas inherited;
	
	
public:
	enum class DECLSPEC_DENUM TDirect3DLevel : unsigned char { Undetermined, Unsupported, Direct3D10, Direct3D10_1 };
	
	enum class DECLSPEC_DENUM TDirect3DSupport : unsigned char { Undetermined, Direct3D10Legacy, Direct3D10, Direct3D10_1 };
	
	
private:
	static _di_ID3D10Device FSharedDevice;
	static _di_IDXGIFactory FSharedDXGIFactory;
	static Winapi::D2d1::_di_ID2D1Factory FSharedFactory;
	static Winapi::D2d1::_di_IDWriteFactory FSharedDWriteFactory;
	static TDirect3DLevel FDirect3DLevel;
	static TDirect3DSupport FDirect3DSupport;
	static bool FDirect3DHardware;
	static void __fastcall UpdateDirect3DLevel();
	static bool __fastcall TryCreateDirect3DDevice();
	static void __fastcall CreateDirect3DDevice();
	static void __fastcall DestroyDirect3DDevice();
	static void __fastcall AcquireDXGIFactory();
	static void __fastcall CreateDirect2DFactory();
	static TDirect3DLevel __fastcall GetDirect3DLevel();
	static _di_ID3D10Device __fastcall GetSharedDevice();
	static _di_IDXGIFactory __fastcall GetSharedDXGIFactory();
	static Winapi::D2d1::_di_IDWriteFactory __fastcall GetSharedDWriteFactory();
	static Winapi::D2d1::_di_ID2D1Factory __fastcall GetSharedFactory();
	
protected:
	__classmethod virtual void __fastcall CreateSharedResources();
	__classmethod virtual void __fastcall DestroySharedResources();
	
public:
	/* static */ __property TDirect3DLevel Direct3DLevel = {read=GetDirect3DLevel, nodefault};
	/* static */ __property TDirect3DSupport Direct3DSupport = {read=FDirect3DSupport, nodefault};
	/* static */ __property bool Direct3DHardware = {read=FDirect3DHardware, nodefault};
	/* static */ __property _di_ID3D10Device SharedDevice = {read=GetSharedDevice};
	/* static */ __property _di_IDXGIFactory SharedDXGIFactory = {read=GetSharedDXGIFactory};
	/* static */ __property Winapi::D2d1::_di_ID2D1Factory SharedFactory = {read=GetSharedFactory};
	/* static */ __property Winapi::D2d1::_di_IDWriteFactory SharedDWriteFactory = {read=GetSharedDWriteFactory};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
protected:
	/* TCanvas.CreateFromWindow */ inline __fastcall virtual TCustomCanvasD2D(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Graphics::TCanvasQuality AQuality) : Fmx::Graphics::TCanvas(AParent, AWidth, AHeight, AQuality) { }
	/* TCanvas.CreateFromBitmap */ inline __fastcall virtual TCustomCanvasD2D(Fmx::Graphics::TBitmap* const ABitmap, const Fmx::Graphics::TCanvasQuality AQuality) : Fmx::Graphics::TCanvas(ABitmap, AQuality) { }
	/* TCanvas.CreateFromPrinter */ inline __fastcall virtual TCustomCanvasD2D(Fmx::Graphics::TAbstractPrinter* const APrinter) : Fmx::Graphics::TCanvas(APrinter) { }
	
public:
	/* TCanvas.Destroy */ inline __fastcall virtual ~TCustomCanvasD2D() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomCanvasD2D() : Fmx::Graphics::TCanvas() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterCanvasClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterCanvasClasses(void);
}	/* namespace D2d */
}	/* namespace Canvas */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CANVAS_D2D)
using namespace Fmx::Canvas::D2d;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CANVAS)
using namespace Fmx::Canvas;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Canvas_D2dHPP
