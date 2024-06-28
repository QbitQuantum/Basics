// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Canvas.GPU.pas' rev: 34.00 (Android)

#ifndef Fmx_Canvas_GpuHPP
#define Fmx_Canvas_GpuHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Canvas.GPU.Helpers.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Canvas
{
namespace Gpu
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBitmapCtx;
class DELPHICLASS TCustomCanvasGpu;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBitmapCtx : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCustomCanvasGpu* FCanvas;
	Fmx::Types3d::TTexture* FTexture;
	Fmx::Types3d::TTexture* FRenderTarget;
	Fmx::Graphics::TMapAccess FAccess;
	void *FData;
	int FWidth;
	int FHeight;
	float FBitmapScale;
	int FBytesPerLine;
	Fmx::Types::TPixelFormat FPixelFormat;
	Fmx::Types3d::TTexture* __fastcall GetTexture();
	Fmx::Types3d::TTexture* __fastcall GetRenderTarget();
	Fmx::Types3d::TTexture* __fastcall GetPaintingTexture();
	void __fastcall CreateBuffer();
	void __fastcall FreeBuffer();
	
public:
	__fastcall TBitmapCtx(const int AWidth, const int AHeight, const float AScale, const Fmx::Types::TPixelFormat APixelFormat);
	__fastcall virtual ~TBitmapCtx();
	__property Fmx::Graphics::TMapAccess Access = {read=FAccess, write=FAccess, nodefault};
	__property TCustomCanvasGpu* Canvas = {read=FCanvas, write=FCanvas};
	__property Fmx::Types3d::TTexture* Texture = {read=GetTexture};
	__property int BytesPerLine = {read=FBytesPerLine, nodefault};
	__property Fmx::Types3d::TTexture* RenderTarget = {read=GetRenderTarget};
	__property Fmx::Types3d::TTexture* PaintingTexture = {read=GetPaintingTexture};
	__property Fmx::Types::TPixelFormat PixelFormat = {read=FPixelFormat, nodefault};
	__property int Height = {read=FHeight, nodefault};
	__property int Width = {read=FWidth, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomCanvasGpu : public Fmx::Graphics::TCanvas
{
	typedef Fmx::Graphics::TCanvas inherited;
	
private:
	static System::Uitypes::TAlphaColor FModulateColor;
	static bool FAlignToPixels;
	static int FFlushCountPerFrame;
	static int FPrimitiveCountPerFrame;
	
protected:
	Fmx::Types3d::TContext3D* FContext;
	
public:
	virtual void __fastcall DrawTexture(const System::Types::TRectF &ARect, const System::Types::TRectF &ATexRect, const System::Uitypes::TAlphaColor AColor, Fmx::Types3d::TTexture* const ATexture) = 0 ;
	/* static */ __property System::Uitypes::TAlphaColor ModulateColor = {read=FModulateColor, write=FModulateColor, nodefault};
	/* static */ __property bool AlignToPixels = {read=FAlignToPixels, write=FAlignToPixels, nodefault};
	/* static */ __property int FlushCountPerFrame = {read=FFlushCountPerFrame, nodefault};
	/* static */ __property int PrimitiveCountPerFrame = {read=FPrimitiveCountPerFrame, nodefault};
	__property Fmx::Types3d::TContext3D* Context = {read=FContext};
protected:
	/* TCanvas.CreateFromWindow */ inline __fastcall virtual TCustomCanvasGpu(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Graphics::TCanvasQuality AQuality) : Fmx::Graphics::TCanvas(AParent, AWidth, AHeight, AQuality) { }
	/* TCanvas.CreateFromBitmap */ inline __fastcall virtual TCustomCanvasGpu(Fmx::Graphics::TBitmap* const ABitmap, const Fmx::Graphics::TCanvasQuality AQuality) : Fmx::Graphics::TCanvas(ABitmap, AQuality) { }
	/* TCanvas.CreateFromPrinter */ inline __fastcall virtual TCustomCanvasGpu(Fmx::Graphics::TAbstractPrinter* const APrinter) : Fmx::Graphics::TCanvas(APrinter) { }
	
public:
	/* TCanvas.Destroy */ inline __fastcall virtual ~TCustomCanvasGpu() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomCanvasGpu() : Fmx::Graphics::TCanvas() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterCanvasClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterCanvasClasses(void);
}	/* namespace Gpu */
}	/* namespace Canvas */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CANVAS_GPU)
using namespace Fmx::Canvas::Gpu;
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
#endif	// Fmx_Canvas_GpuHPP
