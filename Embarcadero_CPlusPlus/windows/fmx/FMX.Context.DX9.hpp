// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Context.DX9.pas' rev: 34.00 (Windows)

#ifndef Fmx_Context_Dx9HPP
#define Fmx_Context_Dx9HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Direct3D9.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Math.Vectors.hpp>
#include <System.Math.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Context
{
namespace Dx9
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomDX9Context;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCustomDX9Context : public Fmx::Types3d::TContext3D
{
	typedef Fmx::Types3d::TContext3D inherited;
	
private:
	static _di_IDirect3DDevice9 FSharedDevice;
	static _di_IDirect3D9 FDirect3D9Obj;
	static bool FAllowSample;
	static bool FAllowSample4;
	static _D3DPRESENT_PARAMETERS_ FSharedDevicePresentParams;
	static System::Generics::Collections::TList__1<TCustomDX9Context*>* FContextList;
	static _D3DCAPS9 FCaps;
	static int FSharedBeginSceneCount;
	static _di_IDirect3DVertexBuffer9 FVB;
	static _di_IDirect3DIndexBuffer9 FIB16;
	static _di_IDirect3DIndexBuffer9 FIB32;
	static int FVBLockPos;
	static int FIB16LockPos;
	static int FIB32LockPos;
	static _di_IDirect3DVertexDeclaration9 FVertexDeclaration;
	static _di_IDirect3DDevice9 __fastcall GetSharedDevice();
	static _di_IDirect3D9 __fastcall GetDirect3D9Obj();
	static void __fastcall CreateDirect3D9Obj();
	static void __fastcall CreateSharedDevice();
	
protected:
	virtual Fmx::Types3d::TContext3D::TIndexBufferSupport __fastcall GetIndexBufferSupport();
	
public:
	static void __fastcall DestroySharedDevice();
	__classmethod bool __fastcall HardwareSupported();
	/* static */ __property _di_IDirect3DDevice9 SharedDevice = {read=GetSharedDevice};
	/* static */ __property _di_IDirect3D9 Direct3D9Obj = {read=GetDirect3D9Obj};
	__classmethod virtual Fmx::Types::TPixelFormat __fastcall PixelFormat();
	__classmethod virtual Fmx::Types3d::TContextStyles __fastcall Style();
	__classmethod virtual int __fastcall MaxTextureSize();
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
protected:
	/* TContext3D.CreateFromWindow */ inline __fastcall virtual TCustomDX9Context(Fmx::Types::TWindowHandle* const AParent, const int AWidth, const int AHeight, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(AParent, AWidth, AHeight, AMultisample, ADepthStencil) { }
	/* TContext3D.CreateFromTexture */ inline __fastcall virtual TCustomDX9Context(Fmx::Types3d::TTexture* const ATexture, const Fmx::Types3d::TMultisample AMultisample, const bool ADepthStencil) : Fmx::Types3d::TContext3D(ATexture, AMultisample, ADepthStencil) { }
	
public:
	/* TContext3D.Destroy */ inline __fastcall virtual ~TCustomDX9Context() { }
	
public:
	/* TObject.Create */ inline __fastcall TCustomDX9Context() : Fmx::Types3d::TContext3D() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterContextClasses(void);
extern DELPHI_PACKAGE void __fastcall UnregisterContextClasses(void);
}	/* namespace Dx9 */
}	/* namespace Context */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CONTEXT_DX9)
using namespace Fmx::Context::Dx9;
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
#endif	// Fmx_Context_Dx9HPP
