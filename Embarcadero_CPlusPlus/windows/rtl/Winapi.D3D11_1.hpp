// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D11_1.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d11_1HPP
#define Winapi_D3d11_1HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.D3D11.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.D3DCommon.hpp>

//-- user supplied -----------------------------------------------------------
#define D3D11_VIDEO_NO_HELPERS
#include "d3d11_1.h"
DECLARE_DINTERFACE_TYPE(ID3D11BlendState1);
DECLARE_DINTERFACE_TYPE(ID3D11RasterizerState1);
DECLARE_DINTERFACE_TYPE(ID3DDeviceContextState);
DECLARE_DINTERFACE_TYPE(ID3D11DeviceContext1);
DECLARE_DINTERFACE_TYPE(ID3D11Device1);
DECLARE_DINTERFACE_TYPE(ID3DUserDefinedAnnotation);

namespace Winapi
{
namespace D3d11_1
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D11_COPY_FLAGS TD3D11CopyFlags;

typedef D3D11_LOGIC_OP TD3D11LogicOp;

typedef D3D11_RENDER_TARGET_BLEND_DESC1 TD3D11RenderTargetBlendDesc1;

typedef D3D11_RENDER_TARGET_BLEND_DESC1 *PD3D11RenderTargetBlendDesc1;

typedef D3D11_BLEND_DESC1 TD3D11BlendDesc1;

typedef D3D11_BLEND_DESC1 *PD3D11BlendDesc1;

typedef D3D11_RASTERIZER_DESC1 TD3D11RasterizerDesc1;

typedef D3D11_RASTERIZER_DESC1 *PD3D11RasterizerDesc1;

typedef D3D11_1_CREATE_DEVICE_CONTEXT_STATE_FLAG TD3D111CreateDeviceContextStateFlag;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d11_1 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D11_1)
using namespace Winapi::D3d11_1;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d11_1HPP
