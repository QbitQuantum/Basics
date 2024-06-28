// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Context.DX11.pas' rev: 34.00 (Windows)

#ifndef Fmx_Context_Dx11HPP
#define Fmx_Context_Dx11HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.D3D11.hpp>
#include <Winapi.D3DCommon.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Math.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Context
{
namespace Dx11
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomDX11Context;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomDX11Context : public Fmx::Types3d::TContext3D
{
	typedef Fmx::Types3d::TContext3D inherited;
	
private:
	static D3D_DRIVER_TYPE FDriverType;
	static unsigned FFeatureLevel;
	static bool FDriverSupportTested;
	static _di_ID3D11Device FSharedDevice;
	static _di_ID3D11DeviceContext FSharedContext;
	static _di_IDXGIFactory FDXGIFactory;
	static _di_ID3D11Buffer FVB;
	static _di_ID3D11Buffer FIB;
	static int FVBLockPos;
	static int FIBLockPos;
	static _di_ID3D11Texture2D FBlankTexture;
	static _di_ID3D11Device __fastcall GetSharedDevice();
	static void __fastcall CreateSharedDevice();
	static _di_IDXGIFactory __fastcall GetDXGIFactory();
	static void __fastcall CreateBlankTexture();
	static _di_ID3D11Texture2D __fastcall GetBlankTexture();
	static _di_ID3D11DeviceContext __fastcall GetSharedContext();
	static unsigned __fastcall GetFeatureLevel();
	
protected:
	virtual Fmx::Types3d::TContext3D::TIndexBufferSupport __fastcall GetIndexBufferSupport();
	
public:
	static void __fastcall DestroySharedDevice();
	__classmethod void __fastcall TestDriverSupport(/* out */ D3D_DRIVER_TYPE &DriverType, /* out */ unsigned &FeatureLevel);
	/* static */ __property unsigned FeatureLevel = {read=GetFeatureLevel, nodefault};
	/* static */ __property _di_ID3D11Device SharedDevice = {read=GetSharedDevice};
	/* static */ __property _di_ID3D11DeviceContext SharedContext = {read=GetSharedContext};
	/* static */ __property _di_IDXGIFactory DXGIFactory = {read=GetDXGIFactory};
	/* static */ __property _di_ID3D11Texture2D BlankTexture = {read=GetBlankTexture};
	__classmethod virtual Fmx::Types::TPixelFormat __fastcall PixelFormat();
	__classmethod virtual int __fastcall MaxTextureSize();
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
protected:
	/* TContext3D.CreateFromWindow */ inline __fastcall virtual TCustomDX11Context(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(AParent, AWidth, AHeight, AMultisample, ADepthStencil) { }
	/* TContext3D.CreateFromTexture */ inline __fastcall virtual TCustomDX11Context(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(ATexture, AMultisample, ADepthStencil) { }
	
public:
	/* TContext3D.Destroy */ inline __fastcall virtual ~TCustomDX11Context() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomDX11Context() : Fmx::Types3d::TContext3D() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterContextClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterContextClasses(void);
}	/* namespace Dx11 */
}	/* namespace Context */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_DX11)
using namespace Fmx::Context::Dx11;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT)
using namespace Fmx::Context;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Context_Dx11HPP
