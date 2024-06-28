// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D10_1.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d10_1HPP
#define Winapi_D3d10_1HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.DXTypes.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.D3D10.hpp>
#include <Winapi.DxgiFormat.hpp>

//-- user supplied -----------------------------------------------------------
#include "D3D10_1.h"
DECLARE_DINTERFACE_TYPE(ID3D10BlendState1);
DECLARE_DINTERFACE_TYPE(ID3D10ShaderResourceView1);
DECLARE_DINTERFACE_TYPE(ID3D10Device1);
DECLARE_DINTERFACE_TYPE(ID3D10ShaderReflection1);

namespace Winapi
{
namespace D3d10_1
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D10_FEATURE_LEVEL1 *PD3D10_FeatureLevel1;

typedef D3D10_FEATURE_LEVEL1 TD3D10_FeatureLevel1;

typedef D3D10_RENDER_TARGET_BLEND_DESC1 *PD3D10_RenderTargetBlendDesc1;

typedef D3D10_RENDER_TARGET_BLEND_DESC1 TD3D10_RenderTargetBlendDesc1;

typedef D3D10_BLEND_DESC1 *PD3D10_BlendDesc1;

typedef D3D10_BLEND_DESC1 TD3D10_BlendDesc1;

typedef D3D10_TEXCUBE_ARRAY_SRV1 *PD3D10_TexcubeArraySrv1;

typedef D3D10_TEXCUBE_ARRAY_SRV1 TD3D10_TexcubeArraySrv1;

typedef D3D10_SRV_DIMENSION1 *PD3D10SrvDimension1;

typedef D3D10_SRV_DIMENSION1 TD3D10SrvDimension1;

typedef D3D10_SHADER_RESOURCE_VIEW_DESC1 *PD3D10_ShaderResourceViewDesc1;

typedef D3D10_SHADER_RESOURCE_VIEW_DESC1 TD3D10_ShaderResourceViewDesc1;

typedef unsigned *PD3D10_StandardMultisampleQualityLevels;

typedef unsigned TD3D10_StandardMultisampleQualityLevels;

typedef HRESULT __stdcall (*TD3D10_CreateDevice1)(_di_IDXGIAdapter pAdapter, D3D10_DRIVER_TYPE DriverType, NativeUInt Software, unsigned Flags, D3D10_FEATURE_LEVEL1 HardwareLevel, unsigned SDKVersion, /* out */ _di_ID3D10Device1 &ppDevice);

typedef HRESULT __stdcall (*TD3D10CreateDeviceAndSwapChain1)(_di_IDXGIAdapter pAdapter, D3D10_DRIVER_TYPE DriverType, NativeUInt Software, unsigned Flags, D3D10_FEATURE_LEVEL1 HardwareLevel, unsigned SDKVersion, Winapi::Dxgi::PDXGISwapChainDesc pSwapChainDesc, /* out */ _di_IDXGISwapChain &ppSwapChain, /* out */ _di_ID3D10Device1 &ppDevice);

typedef _D3D10_SHADER_DEBUG_REGTYPE *PD3D10_ShaderDebugRegtype;

typedef _D3D10_SHADER_DEBUG_REGTYPE TD3D10_ShaderDebugRegtype;

typedef _D3D10_SHADER_DEBUG_SCOPETYPE *PD3D10_ShaderDebugScopetype;

typedef _D3D10_SHADER_DEBUG_SCOPETYPE TD3D10_ShaderDebugScopetype;

typedef _D3D10_SHADER_DEBUG_VARTYPE *PD3D10_ShaderDebugVartype;

typedef _D3D10_SHADER_DEBUG_VARTYPE TD3D10_ShaderDebugVartype;

typedef _D3D10_SHADER_DEBUG_TOKEN_INFO *PD3D10_ShaderDebugTokenInfo;

typedef _D3D10_SHADER_DEBUG_TOKEN_INFO TD3D10_ShaderDebugTokenInfo;

typedef _D3D10_SHADER_DEBUG_VAR_INFO *PD3D10_ShaderDebugVarInfo;

typedef _D3D10_SHADER_DEBUG_VAR_INFO TD3D10_ShaderDebugVarInfo;

typedef _D3D10_SHADER_DEBUG_INPUT_INFO *PD3D10_ShaderDebugInputInfo;

typedef _D3D10_SHADER_DEBUG_INPUT_INFO TD3D10_ShaderDebugInputInfo;

typedef _D3D10_SHADER_DEBUG_SCOPEVAR_INFO *PD3D10_ShaderDebugScopevarInfo;

typedef _D3D10_SHADER_DEBUG_SCOPEVAR_INFO TD3D10_ShaderDebugScopevarInfo;

typedef _D3D10_SHADER_DEBUG_SCOPE_INFO *PD3D10_ShaderDebugScopeInfo;

typedef _D3D10_SHADER_DEBUG_SCOPE_INFO TD3D10_ShaderDebugScopeInfo;

typedef _D3D10_SHADER_DEBUG_OUTPUTVAR *PD3D10_ShaderDebugOutputvar;

typedef _D3D10_SHADER_DEBUG_OUTPUTVAR TD3D10_ShaderDebugOutputvar;

typedef _D3D10_SHADER_DEBUG_OUTPUTREG_INFO *PD3D10_ShaderDebugOutputregInfo;

typedef _D3D10_SHADER_DEBUG_OUTPUTREG_INFO TD3D10_ShaderDebugOutputregInfo;

typedef _D3D10_SHADER_DEBUG_INST_INFO *PD3D10_ShaderDebugInstInfo;

typedef _D3D10_SHADER_DEBUG_INST_INFO TD3D10_ShaderDebugInstInfo;

typedef _D3D10_SHADER_DEBUG_FILE_INFO *PD3D10_ShaderDebugFileInfo;

typedef _D3D10_SHADER_DEBUG_FILE_INFO TD3D10_ShaderDebugFileInfo;

typedef _D3D10_SHADER_DEBUG_INFO *PD3D10_ShaderDebugInfo;

typedef _D3D10_SHADER_DEBUG_INFO TD3D10_ShaderDebugInfo;

//-- var, const, procedure ---------------------------------------------------
#define D3D10_1_dll L"d3d10_1.dll"
static const unsigned D3D10_STANDARD_MULTISAMPLE_PATTERN = unsigned(0xffffffff);
static const unsigned D3D10_CENTER_MULTISAMPLE_PATTERN = unsigned(0xfffffffe);
}	/* namespace D3d10_1 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D10_1)
using namespace Winapi::D3d10_1;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d10_1HPP
