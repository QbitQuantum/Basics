// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D11Shader.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d11shaderHPP
#define Winapi_D3d11shaderHPP

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
DECLARE_DINTERFACE_TYPE(ID3D11ShaderReflectionType);
DECLARE_DINTERFACE_TYPE(ID3D11ShaderReflectionVariable);
DECLARE_DINTERFACE_TYPE(ID3D11ShaderReflectionConstantBuffer);
DECLARE_DINTERFACE_TYPE(ID3D11ShaderReflection);

namespace Winapi
{
namespace D3d11shader
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD D3D11_TESSELLATOR_DOMAIN
{
};


struct DECLSPEC_DRECORD D3D11_TESSELLATOR_PARTITIONING
{
};


struct DECLSPEC_DRECORD D3D11_TESSELLATOR_OUTPUT_PRIMITIVE
{
};


__interface DELPHIINTERFACE ID3D11FunctionLinkingGraph;
typedef System::DelphiInterface<ID3D11FunctionLinkingGraph> _di_ID3D11FunctionLinkingGraph;
//-- type declarations -------------------------------------------------------
typedef D3D11_SHADER_VERSION_TYPE TD3D11ShaderVersionType;

typedef _D3D11_SIGNATURE_PARAMETER_DESC TD3D11SignatureParameterDesc;

typedef _D3D11_SHADER_BUFFER_DESC *PD3D11ShaderBufferDesc;

typedef _D3D11_SHADER_BUFFER_DESC TD3D11ShaderBufferDesc;

typedef _D3D11_SHADER_VARIABLE_DESC TD3D11ShaderVariableDesc;

typedef _D3D11_SHADER_TYPE_DESC *PD3D11ShaderTypeDesc;

typedef _D3D11_SHADER_TYPE_DESC TD3D11ShaderTypeDesc;

typedef _D3D11_SHADER_DESC TD3D11ShaderDesc;

typedef _D3D11_SHADER_INPUT_BIND_DESC TD3D11ShaderInputBindDesc;

typedef _D3D11_LIBRARY_DESC TD3D11LibraryDesc;

typedef _D3D11_LIBRARY_DESC *PD3D11LibraryDesc;

typedef _D3D11_FUNCTION_DESC TD3D11FunctionDesc;

typedef _D3D11_FUNCTION_DESC *PD3D11FunctionDesc;

typedef _D3D11_PARAMETER_DESC TD3D11ParameterDesc;

typedef _D3D11_PARAMETER_DESC *PD3D11ParameterDesc;

typedef _di_ID3D11ShaderReflectionType *PD3D11SHADERREFLECTIONTYPE;

typedef _di_ID3D11ShaderReflectionVariable *PID3D11ShaderReflectionVariable;

typedef _di_ID3D11ShaderReflectionConstantBuffer *PID3D11ShaderReflectionConstantBuffer;

typedef _di_ID3D11ShaderReflection *PIDD3D11SHADERREFLECTION;

typedef _di_ID3D11FunctionReflection *PID3D11FUNCTIONREFLECTION;

typedef _di_ID3D11FunctionParameterReflection *PID3D11FUNCTIONPARAMETERREFLECTION;

typedef _di_ID3D11ShaderReflectionType *PID3D11ShaderReflectionType;

typedef _di_ID3D11ShaderReflectionVariable TID3D11ShaderReflectionVariable;

typedef _di_ID3D11ShaderReflectionConstantBuffer TID3D11ShaderReflectionConstantBuffer;

typedef _di_ID3D11ShaderReflection TID3D11ShaderReflection;

__interface  INTERFACE_UUID("{54133220-1CE8-43D3-8236-9855C5CEECFF}") ID3D11FunctionLinkingGraph  : public System::IInterface 
{
	virtual HRESULT __stdcall CreateModuleInstance(/* out */ _di_ID3D11ModuleInstance &ppModuleInstance, /* out */ _di_ID3D10Blob &ppErrorBuffer) = 0 ;
	virtual HRESULT __stdcall SetInputSignature(const PD3D11ParameterDesc pInputParameters, unsigned cInputParameters, /* out */ _di_ID3D11LinkingNode &ppInputNode) = 0 ;
	virtual HRESULT __stdcall SetOutputSignature(const PD3D11ParameterDesc pOutputParameters, unsigned cOutputParameters, /* out */ _di_ID3D11LinkingNode &ppOutputNode) = 0 ;
	virtual HRESULT __stdcall CallFunction(char * pModuleInstanceNamespace, _di_ID3D11Module pModuleWithFunctionPrototype, char * pFunctionName, /* out */ _di_ID3D11LinkingNode &ppCallNode) = 0 ;
	virtual HRESULT __stdcall PassValue(_di_ID3D11LinkingNode pSrcNode, int SrcParameterIndex, _di_ID3D11LinkingNode pDstNode, int DstParameterIndex) = 0 ;
	virtual HRESULT __stdcall PassValueWithSwizzle(_di_ID3D11LinkingNode pSrcNode, int SrcParameterIndex, char * pSrcSwizzle, _di_ID3D11LinkingNode pDstNode, int DstParameterIndex, char * pDstSwizzle) = 0 ;
	virtual HRESULT __stdcall GetLastError(/* out */ _di_ID3D10Blob &ppErrorBuffer) = 0 ;
	virtual HRESULT __stdcall GenerateHlsl(unsigned uFlags, /* out */ _di_ID3D10Blob &ppBuffer) = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d11shader */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D11SHADER)
using namespace Winapi::D3d11shader;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d11shaderHPP
