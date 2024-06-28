// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D11_3.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d11_3HPP
#define Winapi_D3d11_3HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.D3D11_2.hpp>
#include <Winapi.D3D11_1.hpp>
#include <Winapi.D3D11.hpp>
#include <Winapi.D3DCommon.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.DxgiType.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3d11_3.h"
DECLARE_DINTERFACE_TYPE(ID3D11Texture2D1);
DECLARE_DINTERFACE_TYPE(ID3D11Texture3D1);
DECLARE_DINTERFACE_TYPE(ID3D11RasterizerState2);
DECLARE_DINTERFACE_TYPE(ID3D11ShaderResourceView1);
DECLARE_DINTERFACE_TYPE(ID3D11RenderTargetView1);
DECLARE_DINTERFACE_TYPE(ID3D11UnorderedAccessView1);
DECLARE_DINTERFACE_TYPE(ID3D11Query1);
DECLARE_DINTERFACE_TYPE(ID3D11DeviceContext3);
DECLARE_DINTERFACE_TYPE(ID3D11Device3);

namespace Winapi
{
namespace D3d11_3
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D11_CONTEXT_TYPE TD3D11ContextType;

typedef D3D11_TEXTURE_LAYOUT TD3D11TextureLayout;

typedef D3D11_TEXTURE2D_DESC1 TD3D11Texture2dDesc1;

typedef D3D11_TEXTURE2D_DESC1 *PD3D11Texture2dDesc1;

typedef _di_ID3D11Texture2D1 IID_ID3D11Texture2D1;

typedef D3D11_TEXTURE3D_DESC1 TD3D11Texture3dDesc1;

typedef D3D11_TEXTURE3D_DESC1 *PD3D11Texture3dDesc1;

typedef _di_ID3D11Texture3D1 IID_ID3D11Texture3D1;

typedef D3D11_CONSERVATIVE_RASTERIZATION_MODE TD3D11ConservativeRasterizationMode;

typedef D3D11_RASTERIZER_DESC2 TD3D11RasterizerDesc2;

typedef D3D11_RASTERIZER_DESC2 *PD3D11RasterizerDesc2;

typedef _di_ID3D11RasterizerState2 IID_ID3D11RasterizerState2;

typedef D3D11_TEX2D_SRV1 TD3D11Tex2dSrv1;

typedef D3D11_TEX2D_SRV1 *PD3D11Tex2dSrv1;

typedef D3D11_TEX2D_ARRAY_SRV1 TD3D11Tex2dArraySrv1;

typedef D3D11_TEX2D_ARRAY_SRV1 *PD3D11Tex2dArraySrv1;

typedef D3D11_SHADER_RESOURCE_VIEW_DESC1 TD3D11ShaderResourceViewDesc1;

typedef D3D11_SHADER_RESOURCE_VIEW_DESC1 *PD3D11ShaderResourceViewDesc1;

typedef _di_ID3D11ShaderResourceView1 IID_ID3D11ShaderResourceView1;

typedef D3D11_TEX2D_RTV1 TD3D11Tex2dRtv1;

typedef D3D11_TEX2D_RTV1 *PD3D11Tex2dRtv1;

typedef D3D11_TEX2D_ARRAY_RTV1 TD3D11Tex2dArrayRtv1;

typedef D3D11_TEX2D_ARRAY_RTV1 *PD3D11Tex2dArrayRtv1;

typedef D3D11_RENDER_TARGET_VIEW_DESC1 TD3D11RenderTargetViewDesc1;

typedef D3D11_RENDER_TARGET_VIEW_DESC1 *PD3D11RenderTargetViewDesc1;

typedef _di_ID3D11RenderTargetView1 IID_ID3D11RenderTargetView1;

typedef D3D11_TEX2D_UAV1 TD3D11Tex2dUav1;

typedef D3D11_TEX2D_UAV1 *PD3D11Tex2dUav1;

typedef D3D11_TEX2D_ARRAY_UAV1 TD3D11Tex2dArrayUav1;

typedef D3D11_TEX2D_ARRAY_UAV1 *PD3D11Tex2dArrayUav1;

typedef D3D11_UNORDERED_ACCESS_VIEW_DESC1 TD3D11UnorderedAccessViewDesc1;

typedef D3D11_UNORDERED_ACCESS_VIEW_DESC1 *PD3D11UnorderedAccessViewDesc1;

typedef _di_ID3D11UnorderedAccessView1 IID_ID3D11UnorderedAccessView1;

typedef D3D11_QUERY_DESC1 TD3D11QueryDesc1;

typedef D3D11_QUERY_DESC1 *PD3D11QueryDesc1;

typedef _di_ID3D11Query1 IID_ID3D11Query1;

typedef _di_ID3D11DeviceContext3 IID_ID3D11DeviceContext3;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d11_3 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D11_3)
using namespace Winapi::D3d11_3;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d11_3HPP
