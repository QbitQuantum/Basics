// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3DCommon.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3dcommonHPP
#define Winapi_D3dcommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <d3dcommon.h>
namespace Winapi
{
namespace D3dcommon
{
DECLARE_DINTERFACE_TYPE(ID3D10Blob);
}	/* namespace D3dcommon */
}	/* namespace Winapi */

namespace Winapi
{
namespace D3dcommon
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D_DRIVER_TYPE TD3D_DRIVER_TYPE;

typedef unsigned TD3D_FEATURE_LEVEL;

typedef unsigned *PD3D_FEATURE_LEVEL;

typedef D3D_PRIMITIVE_TOPOLOGY TD3D_PRIMITIVE_TOPOLOGY;

typedef D3D_PRIMITIVE TD3D_PRIMITIVE;

typedef D3D_SRV_DIMENSION TD3D_SRV_DIMENSION;

typedef _D3D_SHADER_MACRO TD3D_SHADER_MACRO;

typedef _di_ID3D10Blob *PID3D10Blob;

typedef _di_ID3D10Blob PID3DBlob;

typedef _D3D_INCLUDE_TYPE TD3D_INCLUDE_TYPE;

typedef void * *PLPCVOID;

typedef _D3D_SHADER_VARIABLE_CLASS TD3D_SHADER_VARIABLE_CLASS;

typedef _D3D_SHADER_VARIABLE_FLAGS TD3D_SHADER_VARIABLE_FLAGS;

typedef _D3D_SHADER_VARIABLE_TYPE TD3D_SHADER_VARIABLE_TYPE;

typedef _D3D_SHADER_INPUT_FLAGS TD3D_SHADER_INPUT_FLAGS;

typedef _D3D_SHADER_INPUT_TYPE TD3D_SHADER_INPUT_TYPE;

typedef _D3D_SHADER_CBUFFER_FLAGS TD3D_SHADER_CBUFFER_FLAGS;

typedef _D3D_CBUFFER_TYPE TD3D_CBUFFER_TYPE;

typedef D3D_NAME TD3D_NAME;

typedef D3D_RESOURCE_RETURN_TYPE TD3D_RESOURCE_RETURN_TYPE;

typedef D3D_REGISTER_COMPONENT_TYPE TD3D_REGISTER_COMPONENT_TYPE;

typedef D3D_TESSELLATOR_DOMAIN TD3D_TESSELLATOR_DOMAIN;

typedef D3D_TESSELLATOR_PARTITIONING TD3D_TESSELLATOR_PARTITIONING;

typedef D3D_TESSELLATOR_OUTPUT_PRIMITIVE TD3D_TESSELLATOR_OUTPUT_PRIMITIVE;

typedef D3D_MIN_PRECISION TD3D_MIN_PRECISION;

typedef D3D_INTERPOLATION_MODE TD3D_INTERPOLATION_MODE;

typedef _D3D_PARAMETER_FLAGS TD3D_PARAMETER_FLAGS;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3dcommon */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3DCOMMON)
using namespace Winapi::D3dcommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3dcommonHPP
