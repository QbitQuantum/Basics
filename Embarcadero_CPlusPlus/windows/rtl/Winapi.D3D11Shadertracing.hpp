// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D11Shadertracing.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d11shadertracingHPP
#define Winapi_D3d11shadertracingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.D3D11.hpp>
#include <Winapi.D3DCommon.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3d11ShaderTracing.h"
DECLARE_DINTERFACE_TYPE(ID3D11ShaderTrace);
DECLARE_DINTERFACE_TYPE(ID3D11ShaderTraceFactory);

namespace Winapi
{
namespace D3d11shadertracing
{
//-- forward type declarations -----------------------------------------------
struct TTRACE_REGISTER_INDEX;
//-- type declarations -------------------------------------------------------
typedef D3D11_SHADER_TYPE TD3D11ShaderType;

typedef D3D11_VERTEX_SHADER_TRACE_DESC TD3D11_VERTEX_SHADER_TRACE_DESC;

typedef D3D11_HULL_SHADER_TRACE_DESC TD3D11HullShaderTraceDesc;

typedef D3D11_DOMAIN_SHADER_TRACE_DESC TD3D11DomainShaderTraceDesc;

typedef D3D11_GEOMETRY_SHADER_TRACE_DESC TD3D11GeometryShaderTraceDesc;

typedef D3D11_PIXEL_SHADER_TRACE_DESC TD3D11PixelShaderTraceDesc;

typedef D3D11_COMPUTE_SHADER_TRACE_DESC TD3D11ComputeShaderTraceDesc;

typedef D3D11_SHADER_TRACE_DESC TD3D11ShaderTraceDesc;

typedef D3D11_SHADER_TRACE_DESC *PD3D11ShaderTraceDesc;

typedef D3D11_TRACE_GS_INPUT_PRIMITIVE TD3D11TraceGsInputPrimitive;

typedef D3D11_TRACE_STATS TD3D11TraceStats;

typedef D3D11_TRACE_VALUE TD3D11TraceValue;

typedef D3D11_TRACE_REGISTER_TYPE TD3D11TraceRegisterType;

struct DECLSPEC_DRECORD TTRACE_REGISTER_INDEX
{
	
public:
	union
	{
		struct 
		{
			System::StaticArray<System::Word, 2> Index2D;
		};
		struct 
		{
			System::Word Index1D;
		};
		
	};
};


typedef D3D11_TRACE_REGISTER TD3D11TraceRegister;

typedef D3D11_TRACE_REGISTER *PD3D11TraceRegister;

typedef D3D11_TRACE_STEP TD3D11TraceStep;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d11shadertracing */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D11SHADERTRACING)
using namespace Winapi::D3d11shadertracing;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d11shadertracingHPP
