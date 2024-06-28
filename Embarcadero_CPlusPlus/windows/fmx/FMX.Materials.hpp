// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Materials.pas' rev: 34.00 (Windows)

#ifndef Fmx_MaterialsHPP
#define Fmx_MaterialsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types3D.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Materials
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomMaterial;
class DELPHICLASS TColorMaterial;
class DELPHICLASS TTextureMaterial;
class DELPHICLASS TLightMaterial;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomMaterial : public Fmx::Types3d::TMaterial
{
	typedef Fmx::Types3d::TMaterial inherited;
	
protected:
	Fmx::Types3d::TContextShader* FVertexShader;
	Fmx::Types3d::TContextShader* FPixelShader;
	virtual void __fastcall DoApply(Fmx::Types3d::TContext3D* const Context);
	__classmethod virtual System::UnicodeString __fastcall DoGetMaterialProperty(const Fmx::Types3d::TMaterial::TProperty Prop);
public:
	/* TMaterial.Create */ inline __fastcall virtual TCustomMaterial() : Fmx::Types3d::TMaterial() { }
	/* TMaterial.Destroy */ inline __fastcall virtual ~TCustomMaterial() { }
	
};


class PASCALIMPLEMENTATION TColorMaterial : public TCustomMaterial
{
	typedef TCustomMaterial inherited;
	
private:
	System::Uitypes::TAlphaColor FColor;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	
protected:
	virtual void __fastcall DoApply(Fmx::Types3d::TContext3D* const Context);
	virtual void __fastcall DoInitialize();
	
public:
	__fastcall virtual TColorMaterial();
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, nodefault};
public:
	/* TMaterial.Destroy */ inline __fastcall virtual ~TColorMaterial() { }
	
};


class PASCALIMPLEMENTATION TTextureMaterial : public TCustomMaterial
{
	typedef TCustomMaterial inherited;
	
private:
	Fmx::Types3d::TTexture* FTexture;
	Fmx::Types3d::TContextShader* FPixelShaderFlip;
	void __fastcall SetTexture(Fmx::Types3d::TTexture* const Value);
	
protected:
	virtual void __fastcall DoApply(Fmx::Types3d::TContext3D* const Context);
	virtual void __fastcall DoInitialize();
	
public:
	__fastcall virtual TTextureMaterial();
	__fastcall virtual ~TTextureMaterial();
	__property Fmx::Types3d::TTexture* Texture = {read=FTexture, write=SetTexture};
};


class PASCALIMPLEMENTATION TLightMaterial : public TCustomMaterial
{
	typedef TCustomMaterial inherited;
	
private:
	System::Uitypes::TAlphaColor FDiffuse;
	int FShininess;
	System::Uitypes::TAlphaColor FAmbient;
	System::Uitypes::TAlphaColor FSpecular;
	System::Uitypes::TAlphaColor FEmissive;
	Fmx::Types3d::TTexture* FTexture;
	Fmx::Types3d::TContextShader* F2LightsVS;
	Fmx::Types3d::TContextShader* F4LightsVS;
	Fmx::Types3d::TContextShader* F8LightsVS;
	Fmx::Types3d::TContextShader* FNoLightsVS;
	Fmx::Types3d::TContextShader* FPixelShaderFlip;
	
protected:
	virtual void __fastcall DoApply(Fmx::Types3d::TContext3D* const Context);
	virtual void __fastcall DoInitialize();
	__classmethod virtual System::UnicodeString __fastcall DoGetMaterialProperty(const Fmx::Types3d::TMaterial::TProperty Prop);
	
public:
	__fastcall virtual TLightMaterial();
	__fastcall virtual ~TLightMaterial();
	__property System::Uitypes::TAlphaColor Diffuse = {read=FDiffuse, write=FDiffuse, nodefault};
	__property System::Uitypes::TAlphaColor Ambient = {read=FAmbient, write=FAmbient, nodefault};
	__property System::Uitypes::TAlphaColor Emissive = {read=FEmissive, write=FEmissive, nodefault};
	__property System::Uitypes::TAlphaColor Specular = {read=FSpecular, write=FSpecular, nodefault};
	__property Fmx::Types3d::TTexture* Texture = {read=FTexture, write=FTexture};
	__property int Shininess = {read=FShininess, write=FShininess, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Materials */
}	/* namespace Fmx */
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
#endif	// Fmx_MaterialsHPP
