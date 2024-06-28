// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D12Shader.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d12shaderHPP
#define Winapi_D3d12shaderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.D3DCommon.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3dcommon.h"
#include "D3D12Shader.h"
DECLARE_DINTERFACE_TYPE(ID3D12ShaderReflectionType);
DECLARE_DINTERFACE_TYPE(ID3D12ShaderReflectionVariable);
DECLARE_DINTERFACE_TYPE(ID3D12ShaderReflectionConstantBuffer);
DECLARE_DINTERFACE_TYPE(ID3D12ShaderReflection);
DECLARE_DINTERFACE_TYPE(ID3D12LibraryReflection);
DECLARE_DINTERFACE_TYPE(ID3D12FunctionReflection);
DECLARE_DINTERFACE_TYPE(ID3D12FunctionParameterReflection);

namespace Winapi
{
namespace D3d12shader
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D12_SHADER_VERSION_TYPE TD3D12ShaderVersionType;

typedef D3D12_SHADER_VERSION_TYPE *PD3D12ShaderVersionType;

typedef _D3D12_SIGNATURE_PARAMETER_DESC TD3D12_SIGNATURE_PARAMETER_DESC;

typedef _D3D12_SIGNATURE_PARAMETER_DESC *PD3D12_SIGNATURE_PARAMETER_DESC;

typedef _D3D12_SHADER_BUFFER_DESC TD3D12ShaderBufferDesc;

typedef _D3D12_SHADER_BUFFER_DESC *PD3D12ShaderBufferDesc;

typedef _D3D12_SHADER_VARIABLE_DESC TD3D12ShaderVariableDesc;

typedef _D3D12_SHADER_VARIABLE_DESC *PD3D12ShaderVariableDesc;

typedef _D3D12_SHADER_TYPE_DESC TD3D12ShaderTypeDesc;

typedef _D3D12_SHADER_TYPE_DESC *PD3D12ShaderTypeDesc;

typedef _D3D12_SHADER_DESC TD3D12ShaderDesc;

typedef _D3D12_SHADER_DESC *PD3D12ShaderDesc;

typedef _D3D12_SHADER_INPUT_BIND_DESC TD3D12ShaderInputBindDesc;

typedef _D3D12_SHADER_INPUT_BIND_DESC *PD3D12ShaderInputBindDesc;

typedef _D3D12_LIBRARY_DESC TD3D12LibraryDesc;

typedef _D3D12_LIBRARY_DESC *PD3D12LibraryDesc;

typedef _D3D12_FUNCTION_DESC TD3D12FunctionDesc;

typedef _D3D12_FUNCTION_DESC *PD3D12FunctionDesc;

typedef _D3D12_PARAMETER_DESC TD3D12ParameterDesc;

typedef _D3D12_PARAMETER_DESC *PD3D12ParameterDesc;

typedef _di_ID3D12ShaderReflectionType *PID3D12ShaderReflectionType;

typedef _di_ID3D12ShaderReflectionVariable *PID3D12ShaderReflectionVariable;

typedef _di_ID3D12ShaderReflectionConstantBuffer *PID3D12ShaderReflectionConstantBuffer;

typedef _di_ID3D12ShaderReflection *PID3D12ShaderReflection;

typedef _di_ID3D12LibraryReflection *PID3D12LibraryReflection;

typedef _di_ID3D12FunctionReflection *PID3D12FunctionReflection;

typedef _di_ID3D12FunctionParameterReflection *PID3D12FunctionParameterReflection;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d12shader */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D12SHADER)
using namespace Winapi::D3d12shader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d12shaderHPP
