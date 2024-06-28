// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Materials.Canvas.pas' rev: 34.00 (Windows)

#ifndef Fmx_Materials_CanvasHPP
#define Fmx_Materials_CanvasHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Materials.hpp>
#include <FMX.Graphics.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Materials
{
namespace Canvas
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCanvasSolidMaterial;
class DELPHICLASS TCanvasTextureMaterial;
class DELPHICLASS TCanvasGradientMaterial;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCanvasSolidMaterial : public Fmx::Materials::TCustomMaterial
{
	typedef Fmx::Materials::TCustomMaterial inherited;
	
protected:
	virtual void __fastcall DoInitialize();
	
public:
	__fastcall virtual TCanvasSolidMaterial();
public:
	/* TMaterial.Destroy */ inline __fastcall virtual ~TCanvasSolidMaterial() { }
	
};


class PASCALIMPLEMENTATION TCanvasTextureMaterial : public Fmx::Materials::TCustomMaterial
{
	typedef Fmx::Materials::TCustomMaterial inherited;
	
private:
	Fmx::Types3d::TTexture* FTexture;
	void __fastcall SetTexture(Fmx::Types3d::TTexture* const Value);
	
protected:
	virtual void __fastcall DoApply(Fmx::Types3d::TContext3D* const Context);
	virtual void __fastcall DoReset(Fmx::Types3d::TContext3D* const Context);
	virtual void __fastcall DoInitialize();
	
public:
	__property Fmx::Types3d::TTexture* Texture = {read=FTexture, write=SetTexture};
public:
	/* TMaterial.Create */ inline __fastcall virtual TCanvasTextureMaterial() : Fmx::Materials::TCustomMaterial() { }
	/* TMaterial.Destroy */ inline __fastcall virtual ~TCanvasTextureMaterial() { }
	
};


class PASCALIMPLEMENTATION TCanvasGradientMaterial : public Fmx::Materials::TCustomMaterial
{
	typedef Fmx::Materials::TCustomMaterial inherited;
	
private:
	Fmx::Graphics::TGradient* FGradient;
	Fmx::Types3d::TContextShader* FLinear2PS;
	Fmx::Types3d::TContextShader* FLinear3PS;
	Fmx::Types3d::TContextShader* FLinear4PS;
	Fmx::Types3d::TContextShader* FRadial2PS;
	Fmx::Types3d::TContextShader* FRadial3PS;
	Fmx::Types3d::TContextShader* FRadial4PS;
	void __fastcall SetGradient(Fmx::Graphics::TGradient* const Value);
	
protected:
	virtual void __fastcall DoInitialize();
	virtual void __fastcall DoApply(Fmx::Types3d::TContext3D* const Context);
	
public:
	__fastcall virtual TCanvasGradientMaterial();
	__fastcall virtual ~TCanvasGradientMaterial();
	__property Fmx::Graphics::TGradient* Gradient = {read=FGradient, write=SetGradient};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Canvas */
}	/* namespace Materials */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MATERIALS_CANVAS)
using namespace Fmx::Materials::Canvas;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MATERIALS)
using namespace Fmx::Materials;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Materials_CanvasHPP
