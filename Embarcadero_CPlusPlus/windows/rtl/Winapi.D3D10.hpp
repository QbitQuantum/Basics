// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D10.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d10HPP
#define Winapi_D3d10HPP

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
#include <Winapi.DxgiType.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3d10_1.h"
#include "D3D10.h"
#include "D3D10Misc.h"
#include "D3D10Shader.h"
DECLARE_DINTERFACE_TYPE(ID3D10DeviceChild);
DECLARE_DINTERFACE_TYPE(ID3D10DepthStencilState);
DECLARE_DINTERFACE_TYPE(ID3D10BlendState);
DECLARE_DINTERFACE_TYPE(ID3D10RasterizerState);
DECLARE_DINTERFACE_TYPE(ID3D10Resource);
DECLARE_DINTERFACE_TYPE(ID3D10Buffer);
DECLARE_DINTERFACE_TYPE(ID3D10Texture1D);
DECLARE_DINTERFACE_TYPE(ID3D10Texture2D);
DECLARE_DINTERFACE_TYPE(ID3D10Texture3D);
DECLARE_DINTERFACE_TYPE(ID3D10View);
DECLARE_DINTERFACE_TYPE(ID3D10ShaderResourceView);
DECLARE_DINTERFACE_TYPE(ID3D10RenderTargetView);
DECLARE_DINTERFACE_TYPE(ID3D10DepthStencilView);
DECLARE_DINTERFACE_TYPE(ID3D10VertexShader);
DECLARE_DINTERFACE_TYPE(ID3D10GeometryShader);
DECLARE_DINTERFACE_TYPE(ID3D10PixelShader);
DECLARE_DINTERFACE_TYPE(ID3D10InputLayout);
DECLARE_DINTERFACE_TYPE(ID3D10SamplerState);
DECLARE_DINTERFACE_TYPE(ID3D10Asynchronous);
DECLARE_DINTERFACE_TYPE(ID3D10Query);
DECLARE_DINTERFACE_TYPE(ID3D10Predicate);
DECLARE_DINTERFACE_TYPE(ID3D10Counter);
DECLARE_DINTERFACE_TYPE(ID3D10Device);
DECLARE_DINTERFACE_TYPE(ID3D10Multithread);
DECLARE_DINTERFACE_TYPE(ID3D10Blob);
DECLARE_DINTERFACE_TYPE(ID3D10ShaderReflection);
DECLARE_DINTERFACE_TYPE(ID3D10StateBlock);
DECLARE_DINTERFACE_TYPE(ID3D10Effect);
DECLARE_DINTERFACE_TYPE(ID3D10EffectPool);

namespace Winapi
{
namespace D3d10
{
//-- forward type declarations -----------------------------------------------
struct D3D10_BUFFER_DESC;
//-- type declarations -------------------------------------------------------
typedef D3D10_INPUT_CLASSIFICATION TD3D10InputClassification;

typedef D3D10_INPUT_ELEMENT_DESC *PD3D10_InputElementDesc;

typedef D3D10_INPUT_ELEMENT_DESC TD3D10_InputElementDesc;

typedef D3D10_FILL_MODE TD3D10_FillMode;

typedef D3D10_PRIMITIVE_TOPOLOGY TD3D10_PrimitiveTopology;

typedef D3D10_PRIMITIVE TD3D10_Primitive;

typedef D3D10_CULL_MODE TD3D10_CullMode;

typedef D3D10_SO_DECLARATION_ENTRY *PD3D10_SO_DeclarationEntry;

typedef D3D10_SO_DECLARATION_ENTRY TD3D10_SO_DeclarationEntry;

typedef D3D10_VIEWPORT *PD3D10_Viewport;

typedef D3D10_VIEWPORT TD3D10_Viewport;

typedef D3D10_RESOURCE_DIMENSION *PD3D10_ResourceDimension;

typedef D3D10_RESOURCE_DIMENSION TD3D10_ResourceDimension;

typedef D3D10_SRV_DIMENSION *PD3D10_SRV_Dimension;

typedef D3D10_SRV_DIMENSION TD3D10_SRV_Dimension;

typedef D3D10_DSV_DIMENSION *PD3D10_DSV_Dimension;

typedef D3D10_DSV_DIMENSION TD3D10_DSV_Dimension;

typedef D3D10_RTV_DIMENSION *PD3D10_RTV_Dimension;

typedef D3D10_RTV_DIMENSION TD3D10_RTV_Dimension;

typedef D3D10_USAGE TD3D10_Usage;

typedef unsigned TD3D10_BindFlag;

typedef unsigned TD3D10_CpuAccessFlag;

typedef unsigned TD3D10_RresourceMiscFlag;

typedef D3D10_MAP TD3D10_Map;

typedef D3D10_MAP_FLAG TD3D10_MapFlag;

typedef D3D10_RAISE_FLAG TD3D10_RaiseFlag;

typedef unsigned TD3D10_ClearFlag;

typedef System::Types::TRect TD3D10_Rect;

typedef System::Types::TRect *PD3D10_Rect;

typedef D3D10_BOX *PD3D10_Box;

typedef D3D10_BOX TD3D10_Box;

typedef unsigned TD3D10_FormatSupport;

typedef _di_ID3D10DeviceChild *PID3D10DeviceChild;

typedef _di_ID3D10DepthStencilState *PID3D10DepthStencilState;

typedef _di_ID3D10BlendState *PID3D10BlendState;

typedef _di_ID3D10RasterizerState *PID3D10RasterizerState;

typedef _di_ID3D10Resource *PID3D10Resource;

typedef _di_ID3D10Buffer *PID3D10Buffer;

typedef _di_ID3D10Texture1D *PID3D10Texture1D;

typedef _di_ID3D10Texture2D *PID3D10Texture2D;

typedef _di_ID3D10Texture3D *PID3D10Texture3D;

typedef _di_ID3D10View *PID3D10View;

typedef _di_ID3D10ShaderResourceView *PID3D10ShaderResourceView;

typedef _di_ID3D10RenderTargetView *PID3D10RenderTargetView;

typedef _di_ID3D10DepthStencilView *PID3D10DepthStencilView;

typedef _di_ID3D10VertexShader *PID3D10VertexShader;

typedef _di_ID3D10GeometryShader *PID3D10GeometryShader;

typedef _di_ID3D10PixelShader *PID3D10PixelShader;

typedef _di_ID3D10InputLayout *PID3D10InputLayout;

typedef _di_ID3D10SamplerState *PID3D10SamplerState;

typedef _di_ID3D10Asynchronous *PID3D10Asynchronous;

typedef _di_ID3D10Query *PID3D10Query;

typedef _di_ID3D10Predicate *PID3D10Predicate;

typedef _di_ID3D10Counter *PID3D10Counter;

typedef _di_ID3D10Device *PID3D10Device;

typedef _di_ID3D10Multithread *PID3D10Multithread;

typedef D3D10_COMPARISON_FUNC TD3D10_ComparisonFunc;

typedef D3D10_DEPTH_WRITE_MASK TD3D10_DepthWriteMask;

typedef D3D10_STENCIL_OP TD3D10_StencilOp;

typedef D3D10_DEPTH_STENCILOP_DESC TD3D10_DepthStencilOpDesc;

typedef D3D10_DEPTH_STENCIL_DESC TD3D10_DepthStencilDesc;

typedef D3D10_BLEND *PD3D10_Blend;

typedef D3D10_BLEND TD3D10_Blend;

typedef D3D10_BLEND_OP TD3D10_BlendOp;

typedef D3D10_COLOR_WRITE_ENABLE TD3D10_ColorWriteEnable;

typedef D3D10_BLEND_DESC TD3D10_BlendDesc;

typedef D3D10_RASTERIZER_DESC TD3D10_RasterizerDesc;

typedef D3D10_SUBRESOURCE_DATA *PD3D10_SubresourceData;

typedef D3D10_SUBRESOURCE_DATA TD3D10_SubresourceData;

struct DECLSPEC_DRECORD D3D10_BUFFER_DESC
{
public:
	unsigned ByteWidth;
	D3D10_USAGE Usage;
	unsigned BindFlags;
	unsigned CPUAccessFlags;
	unsigned MiscFlags;
	__fastcall D3D10_BUFFER_DESC(unsigned byteWidth, unsigned bindFlags, D3D10_USAGE usage, unsigned cpuaccessflags, unsigned miscFlags);
	D3D10_BUFFER_DESC() {}
};


typedef D3D10_BUFFER_DESC TD3D10_BufferDesc;

typedef D3D10_TEXTURE1D_DESC TD3D10_Texture1DDesc;

typedef D3D10_TEXTURE2D_DESC TD3D10_Texture2DDesc;

typedef D3D10_MAPPED_TEXTURE2D TD3D10_MappedTexture2D;

typedef D3D10_TEXTURE3D_DESC TD3D10_Texture3DDesc;

typedef D3D10_MAPPED_TEXTURE3D TD3D10_MappedTexture3D;

typedef D3D10_TEXTURECUBE_FACE TD3D10_TextureCubeFace;

typedef D3D10_BUFFER_SRV TD3D10_Buffer_SRV;

typedef D3D10_TEX1D_SRV TD3D10_Tex1D_SRV;

typedef D3D10_TEX1D_ARRAY_SRV TD3D10_Tex1DArraySRV;

typedef D3D10_TEX2D_SRV TD3D10_Tex2D_SRV;

typedef D3D10_TEX2D_ARRAY_SRV TD3D10_Tex2DArraySRV;

typedef D3D10_TEX3D_SRV TD3D10_Tex3D_SRV;

typedef D3D10_TEXCUBE_SRV TD3D10_TexCube_SRV;

typedef D3D10_TEX2DMS_SRV TD3D10_Tex2DMS_SRV;

typedef D3D10_SHADER_RESOURCE_VIEW_DESC *PD3D10_ShaderResourceViewDesc;

typedef D3D10_SHADER_RESOURCE_VIEW_DESC TD3D10_ShaderResourceViewDesc;

typedef D3D10_BUFFER_RTV TD3D10_Buffer_RTV;

typedef D3D10_TEX1D_RTV TD3D10_Tex1D_RTV;

typedef D3D10_TEX1D_ARRAY_RTV TD3D10_Tex1DArray_RTV;

typedef D3D10_TEX2D_RTV TD3D10_Tex2D_RTV;

typedef D3D10_TEX2DMS_RTV TD3D10_Tex2DMS_RTV;

typedef D3D10_TEX2D_ARRAY_RTV TD3D10_Tex2DArray_RTV;

typedef D3D10_TEX2DMS_ARRAY_RTV TD3D10_Tex2DMSArray_RTV;

typedef D3D10_TEX3D_RTV TD3D10_Tex3D_RTV;

typedef D3D10_RENDER_TARGET_VIEW_DESC *PD3D10_RenderTargetViewDesc;

typedef D3D10_RENDER_TARGET_VIEW_DESC TD3D10_RenderTargetViewDesc;

typedef D3D10_TEX1D_DSV TD3D10_Tex1D_DSV;

typedef D3D10_TEX1D_ARRAY_DSV TD3D10_Tex1DArray_DSV;

typedef D3D10_TEX2D_DSV TD3D10_Tex2D_DSV;

typedef D3D10_TEX2D_ARRAY_DSV TD3D10_Tex2DArray_DSV;

typedef D3D10_TEX2DMS_DSV TD3D10_Tex2DMS_DSV;

typedef D3D10_TEX2DMS_ARRAY_DSV TD3D10_Tex2DMSArray_DSV;

typedef D3D10_DEPTH_STENCIL_VIEW_DESC *PD3D10_DepthStencilViewDesc;

typedef D3D10_DEPTH_STENCIL_VIEW_DESC TD3D10_DepthStencilViewDesc;

typedef D3D10_FILTER TD3D10_Filter;

typedef D3D10_FILTER_TYPE TD3D10_FilterType;

typedef D3D10_TEXTURE_ADDRESS_MODE TD3D10_TextureAddressMode;

typedef D3D10_SAMPLER_DESC TD3D10_SamplerDesc;

typedef D3D10_ASYNC_GETDATA_FLAG TD3D10_AsyncGetDataFlag;

typedef D3D10_QUERY TD3D10_Query;

typedef D3D10_QUERY_MISC_FLAG TD3D10_QueryMiscFlag;

typedef D3D10_QUERY_DESC TD3D10_QueryDesc;

typedef D3D10_QUERY_DATA_TIMESTAMP_DISJOINT TD3D10_QueryData_Timestamp_Disjoint;

typedef D3D10_QUERY_DATA_PIPELINE_STATISTICS TD3D10_QueryData_Pipeline_Statistics;

typedef D3D10_QUERY_DATA_SO_STATISTICS TD3D10_QueryData_SO_Statistics;

typedef D3D10_COUNTER TD3D10_Counter;

typedef D3D10_COUNTER_TYPE TD3D10_CounterType;

typedef D3D10_COUNTER_DESC TD3D10_CounterDesc;

typedef D3D10_COUNTER_INFO TD3D10_CounterInfo;

typedef System::StaticArray<float, 4> TColorArray;

typedef TColorArray *PColorArray;

typedef unsigned *PD3D10_CreateDeviceFlag;

typedef unsigned TD3D10_CreateDeviceFlag;

typedef _di_ID3D10Blob *PID3D10Blob;

typedef _di_ID3D10Blob IID_ID3D10Blob;

typedef D3D10_DRIVER_TYPE *PD3D10DriverType;

typedef D3D10_DRIVER_TYPE TD3D10DriverType;

typedef D3D10_SHADER_MACRO *PD3D10_ShaderMacro;

typedef D3D10_SHADER_MACRO TD3D10_ShaderMacro;

typedef D3D10_SHADER_VARIABLE_CLASS *PD3D10_ShaderVariableClass;

typedef D3D10_SHADER_VARIABLE_CLASS TD3D10_ShaderVariableClass;

typedef D3D10_SHADER_VARIABLE_FLAGS *PD3D10_ShaderVariableFlags;

typedef D3D10_SHADER_VARIABLE_FLAGS TD3D10_ShaderVariableFlags;

typedef D3D10_SHADER_VARIABLE_TYPE *PD3D10_ShaderVariableType;

typedef D3D10_SHADER_VARIABLE_TYPE TD3D10_ShaderVariableType;

typedef D3D10_SHADER_INPUT_FLAGS *PD3D10_ShaderInputFlags;

typedef D3D10_SHADER_INPUT_FLAGS TD3D10_ShaderInputFlags;

typedef D3D10_SHADER_INPUT_TYPE *PD3D10_ShaderInputType;

typedef D3D10_SHADER_INPUT_TYPE TD3D10_ShaderInputType;

typedef D3D10_SHADER_CBUFFER_FLAGS *PD3D10_ShaderCBufferFlags;

typedef D3D10_SHADER_CBUFFER_FLAGS TD3D10_ShaderCBufferFlags;

typedef D3D10_CBUFFER_TYPE *PD3D10_CBufferType;

typedef D3D10_CBUFFER_TYPE TD3D10_CBufferType;

typedef D3D10_NAME *PD3D10_Name;

typedef D3D10_NAME TD3D10_Name;

typedef D3D10_RESOURCE_RETURN_TYPE *PD3D10_ResourceReturnType;

typedef D3D10_RESOURCE_RETURN_TYPE TD3D10_ResourceReturnType;

typedef D3D10_REGISTER_COMPONENT_TYPE *PD3D10_RegisterComponentType;

typedef D3D10_REGISTER_COMPONENT_TYPE TD3D10_RegisterComponentType;

typedef D3D10_INCLUDE_TYPE *PD3D10IncludeType;

typedef D3D10_INCLUDE_TYPE TD3D10IncludeType;

typedef _D3D10_SHADER_DESC *PD3D10_ShaderDesc;

typedef _D3D10_SHADER_DESC TD3D10_ShaderDesc;

typedef _D3D10_SHADER_BUFFER_DESC *PD3D10_ShaderBufferDesc;

typedef _D3D10_SHADER_BUFFER_DESC TD3D10_ShaderBufferDesc;

typedef _D3D10_SHADER_VARIABLE_DESC *PD3D10_ShaderVariableDesc;

typedef _D3D10_SHADER_VARIABLE_DESC TD3D10_ShaderVariableDesc;

typedef _D3D10_SHADER_TYPE_DESC *PD3D10_ShaderTypeDesc;

typedef _D3D10_SHADER_TYPE_DESC TD3D10_ShaderTypeDesc;

typedef _D3D10_SHADER_INPUT_BIND_DESC *PD3D10_ShaderInputBindDesc;

typedef _D3D10_SHADER_INPUT_BIND_DESC TD3D10_ShaderInputBindDesc;

typedef _D3D10_SIGNATURE_PARAMETER_DESC *PD3D10_SignatureParameterDesc;

typedef _D3D10_SIGNATURE_PARAMETER_DESC TD3D10_SignatureParameterDesc;

typedef _D3D10_DEVICE_STATE_TYPES *PD3D10_DeviceStateTypes;

typedef _D3D10_DEVICE_STATE_TYPES TD3D10_DeviceStateTypes;

typedef _D3D10_STATE_BLOCK_MASK *PD3D10_StateBlockMask;

typedef _D3D10_STATE_BLOCK_MASK TD3D10_StateBlockMask;

typedef _D3D10_EFFECT_TYPE_DESC *PD3D10_EffectTypeDesc;

typedef _D3D10_EFFECT_TYPE_DESC TD3D10_EffectTypeDesc;

typedef _D3D10_EFFECT_VARIABLE_DESC *PD3D10_EffectVariableDesc;

typedef _D3D10_EFFECT_VARIABLE_DESC TD3D10_EffectVariableDesc;

typedef _D3D10_EFFECT_SHADER_DESC *PD3D10_EffectShaderDesc;

typedef _D3D10_EFFECT_SHADER_DESC TD3D10_EffectShaderDesc;

typedef _D3D10_PASS_DESC *PD3D10_PassDesc;

typedef _D3D10_PASS_DESC TD3D10_PassDesc;

typedef _D3D10_PASS_SHADER_DESC *PD3D10_PassShaderDesc;

typedef _D3D10_PASS_SHADER_DESC TD3D10_PassShaderDesc;

typedef _D3D10_TECHNIQUE_DESC *PD3D10_TechniqueDesc;

typedef _D3D10_TECHNIQUE_DESC TD3D10_TechniqueDesc;

typedef _D3D10_EFFECT_DESC *PD3D10_EffectDesc;

typedef _D3D10_EFFECT_DESC TD3D10_EffectDesc;

//-- var, const, procedure ---------------------------------------------------
#define D3D10dll L"d3d10.dll"
static const int MAKE_D3D10HRESULT_R = int(-2005336064);
extern DELPHI_PACKAGE unsigned __fastcall D3D10CalcSubresource(unsigned MipSlice, unsigned ArraySlice, unsigned MipLevels);
extern DELPHI_PACKAGE TColorArray __fastcall ColorArray(float a, float b, float c, float d);
}	/* namespace D3d10 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D10)
using namespace Winapi::D3d10;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d10HPP
