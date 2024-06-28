// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D12.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d12HPP
#define Winapi_D3d12HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.DxgiType.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.D3DCommon.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "windows.h"
#include "dxgi.h"
#include "d3dcommon.h"
#include "d3d12sdklayers.h"
#include "d3d12.h"
DECLARE_DINTERFACE_TYPE(ID3D12Object);
DECLARE_DINTERFACE_TYPE(ID3D12DeviceChild);
DECLARE_DINTERFACE_TYPE(ID3D12RootSignature);
DECLARE_DINTERFACE_TYPE(ID3D12RootSignatureDeserializer);
DECLARE_DINTERFACE_TYPE(ID3D12Pageable);
DECLARE_DINTERFACE_TYPE(ID3D12Heap);
DECLARE_DINTERFACE_TYPE(ID3D12Resource);
DECLARE_DINTERFACE_TYPE(ID3D12CommandAllocator);
DECLARE_DINTERFACE_TYPE(ID3D12Fence);
DECLARE_DINTERFACE_TYPE(ID3D12PipelineState);
DECLARE_DINTERFACE_TYPE(ID3D12DescriptorHeap);
DECLARE_DINTERFACE_TYPE(ID3D12QueryHeap);
DECLARE_DINTERFACE_TYPE(ID3D12CommandSignature);
DECLARE_DINTERFACE_TYPE(ID3D12CommandList);
DECLARE_DINTERFACE_TYPE(ID3D12GraphicsCommandList);
DECLARE_DINTERFACE_TYPE(ID3D12CommandQueue);
DECLARE_DINTERFACE_TYPE(ID3D12Device);

namespace Winapi
{
namespace D3d12
{
//-- forward type declarations -----------------------------------------------
struct D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT;
struct TD3D12_ROOT_PARAMETER_INNER;
struct TD3D12_INDIRECT_ARGUMENT_DESC_VertexBuffer;
struct TD3D12_INDIRECT_ARGUMENT_DESC_Constant;
struct TD3D12_INDIRECT_ARGUMENT_DESC_ConstantBufferView;
struct TD3D12_INDIRECT_ARGUMENT_DESC_ShaderResourceView;
struct TD3D12_INDIRECT_ARGUMENT_DESC_UnorderedAccessView;
//-- type declarations -------------------------------------------------------
typedef System::StaticArray<float, 4> TFourSingleArray;

typedef System::StaticArray<unsigned, 4> TFourUIntArray;

typedef unsigned __int64 TD3D12GpuVirtualAddress;

typedef D3D12_COMMAND_LIST_TYPE TD3D12CommandListType;

typedef D3D12_COMMAND_QUEUE_FLAGS TD3D12CommandQueueFlags;

typedef D3D12_COMMAND_QUEUE_PRIORITY TD3D12CommandQueuePriority;

typedef D3D12_COMMAND_QUEUE_DESC TD3D12CommandQueueDesc;

typedef D3D12_COMMAND_QUEUE_DESC *PD3D12CommandQueueDesc;

typedef D3D12_PRIMITIVE_TOPOLOGY_TYPE TD3D12PrimitiveTopologyType;

typedef D3D12_INPUT_CLASSIFICATION TD3D12InputClassification;

typedef D3D12_INPUT_ELEMENT_DESC TD3D12InputElementDesc;

typedef D3D12_INPUT_ELEMENT_DESC *PD3D12InputElementDesc;

typedef D3D12_FILL_MODE TD3D12FillMode;

typedef D3D_PRIMITIVE_TOPOLOGY TD3D12PrimitiveTopology;

typedef D3D_PRIMITIVE TD3D12Primitive;

typedef D3D12_CULL_MODE TD3D12CullMode;

typedef D3D12_SO_DECLARATION_ENTRY TD3D12SoDeclarationEntry;

typedef D3D12_SO_DECLARATION_ENTRY *PD3D12SoDeclarationEntry;

typedef D3D12_VIEWPORT TD3D12Viewport;

typedef D3D12_VIEWPORT *PD3D12Viewport;

typedef System::Types::TRect TD3D12Rect;

typedef System::Types::TRect *PD3D12Rect;

typedef D3D12_BOX TD3D12Box;

typedef D3D12_BOX *PD3D12Box;

typedef D3D12_COMPARISON_FUNC TD3D12ComparisonFunc;

typedef D3D12_DEPTH_WRITE_MASK TD3D12DepthWriteMask;

typedef D3D12_STENCIL_OP TD3D12StencilOp;

typedef D3D12_DEPTH_STENCILOP_DESC TD3D12DepthStencilopDesc;

typedef D3D12_DEPTH_STENCILOP_DESC *PD3D12DepthStencilopDesc;

typedef D3D12_DEPTH_STENCIL_DESC TD3D12DepthStencilDesc;

typedef D3D12_DEPTH_STENCIL_DESC *PD3D12DepthStencilDesc;

typedef D3D12_BLEND TD3D12Blend;

typedef D3D12_BLEND_OP TD3D12BlendOp;

typedef D3D12_COLOR_WRITE_ENABLE TD3D12ColorWriteEnable;

typedef D3D12_LOGIC_OP TD3D12LogicOp;

typedef D3D12_RENDER_TARGET_BLEND_DESC TD3D12RenderTargetBlendDesc;

typedef D3D12_RENDER_TARGET_BLEND_DESC *PD3D12RenderTargetBlendDesc;

typedef D3D12_BLEND_DESC TD3D12BlendDesc;

typedef D3D12_BLEND_DESC *PD3D12BlendDesc;

typedef D3D12_CONSERVATIVE_RASTERIZATION_MODE TD3D12ConservativeRasterizationMode;

typedef D3D12_RASTERIZER_DESC TD3D12RasterizerDesc;

typedef D3D12_RASTERIZER_DESC *PD3D12RasterizerDesc;

typedef D3D12_SHADER_BYTECODE TD3D12ShaderBytecode;

typedef D3D12_SHADER_BYTECODE *PD3D12ShaderBytecode;

typedef D3D12_STREAM_OUTPUT_DESC TD3D12StreamOutputDesc;

typedef D3D12_STREAM_OUTPUT_DESC *PD3D12StreamOutputDesc;

typedef D3D12_INPUT_LAYOUT_DESC TD3D12InputLayoutDesc;

typedef D3D12_INPUT_LAYOUT_DESC *PD3D12InputLayoutDesc;

typedef D3D12_INDEX_BUFFER_STRIP_CUT_VALUE TD3D12IndexBufferStripCutValue;

typedef D3D12_INDEX_BUFFER_STRIP_CUT_VALUE *PD3D12IndexBufferStripCutValue;

typedef D3D12_CACHED_PIPELINE_STATE TD3D12CachedPipelineState;

typedef D3D12_CACHED_PIPELINE_STATE *PD3D12CachedPipelineState;

typedef D3D12_PIPELINE_STATE_FLAGS TD3D12PipelineStateFlags;

typedef D3D12_PIPELINE_STATE_FLAGS *PD3D12PipelineStateFlags;

typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC TD3D12GraphicsPipelineStateDesc;

typedef D3D12_GRAPHICS_PIPELINE_STATE_DESC *PD3D12GraphicsPipelineStateDesc;

typedef D3D12_COMPUTE_PIPELINE_STATE_DESC TD3D12ComputePipelineStateDesc;

typedef D3D12_COMPUTE_PIPELINE_STATE_DESC *PD3D12ComputePipelineStateDesc;

typedef D3D12_FEATURE TD3D12Feature;

typedef D3D12_SHADER_MIN_PRECISION_SUPPORT TD3D12ShaderMinPrecisionSupport;

typedef D3D12_TILED_RESOURCES_TIER TD3D12TiledResourcesTier;

typedef D3D12_RESOURCE_BINDING_TIER TD3D12ResourceBindingTier;

typedef D3D12_CONSERVATIVE_RASTERIZATION_TIER TD3D12ConservativeRasterizationTier;

typedef D3D12_FORMAT_SUPPORT1 TD3D12FormatSupport1;

typedef D3D12_FORMAT_SUPPORT2 TD3D12FormatSupport2;

typedef D3D12_MULTISAMPLE_QUALITY_LEVEL_FLAGS TD3D12MultisampleQualityLevelFlags;

typedef D3D12_CROSS_NODE_SHARING_TIER TD3D12CrossNodeSharingTier;

typedef D3D12_RESOURCE_HEAP_TIER TD3D12ResourceHeapTier;

typedef D3D12_FEATURE_DATA_D3D12_OPTIONS TD3D12FeatureDataD3d12Options;

typedef D3D12_FEATURE_DATA_D3D12_OPTIONS *PD3D12FeatureDataD3d12Options;

typedef D3D12_FEATURE_DATA_ARCHITECTURE TD3D12FeatureDataArchitecture;

typedef D3D12_FEATURE_DATA_ARCHITECTURE *PD3D12FeatureDataArchitecture;

typedef D3D12_FEATURE_DATA_FEATURE_LEVELS TD3D12FeatureDataFeatureLevels;

typedef D3D12_FEATURE_DATA_FEATURE_LEVELS *PD3D12FeatureDataFeatureLevels;

typedef D3D12_FEATURE_DATA_FORMAT_SUPPORT TD3D12FeatureDataFormatSupport;

typedef D3D12_FEATURE_DATA_FORMAT_SUPPORT *PD3D12FeatureDataFormatSupport;

typedef D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS TD3D12FeatureDataMultisampleQualityLevels;

typedef D3D12_FEATURE_DATA_MULTISAMPLE_QUALITY_LEVELS *PD3D12FeatureDataMultisampleQualityLevels;

typedef D3D12_FEATURE_DATA_FORMAT_INFO TD3D12FeatureDataFormatInfo;

typedef D3D12_FEATURE_DATA_FORMAT_INFO *PD3D12FeatureDataFormatInfo;

struct DECLSPEC_DRECORD D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT
{
public:
	unsigned MaxGPUVirtualAddressBitsPerResource;
	unsigned MaxGPUVirtualAddressBitsPerProcess;
};


typedef D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT TD3D12FeatureDataGpuVirtualAddressSupport;

typedef D3D12_FEATURE_DATA_GPU_VIRTUAL_ADDRESS_SUPPORT *PD3D12FeatureDataGpuVirtualAddressSupport;

typedef D3D12_RESOURCE_ALLOCATION_INFO TD3D12ResourceAllocationInfo;

typedef D3D12_RESOURCE_ALLOCATION_INFO *PD3D12ResourceAllocationInfo;

typedef D3D12_HEAP_TYPE TD3D12HeapType;

typedef D3D12_CPU_PAGE_PROPERTY TD3D12CpuPageProperty;

typedef D3D12_MEMORY_POOL TD3D12MemoryPool;

typedef D3D12_HEAP_PROPERTIES TD3D12HeapProperties;

typedef D3D12_HEAP_PROPERTIES *PD3D12HeapProperties;

typedef D3D12_HEAP_FLAGS TD3D12HeapFlags;

typedef D3D12_HEAP_FLAGS *PD3D12HeapFlags;

typedef D3D12_HEAP_DESC TD3D12HeapDesc;

typedef D3D12_HEAP_DESC *PD3D12HeapDesc;

typedef D3D12_RESOURCE_DIMENSION TD3D12ResourceDimension;

typedef D3D12_TEXTURE_LAYOUT TD3D12TextureLayout;

typedef D3D12_RESOURCE_FLAGS TD3D12ResourceFlags;

typedef D3D12_RESOURCE_DESC TD3D12ResourceDesc;

typedef D3D12_RESOURCE_DESC *PD3D12ResourceDesc;

typedef D3D12_DEPTH_STENCIL_VALUE TD3D12DepthStencilValue;

typedef D3D12_DEPTH_STENCIL_VALUE *PD3D12DepthStencilValue;

typedef D3D12_CLEAR_VALUE TD3D12ClearValue;

typedef D3D12_CLEAR_VALUE *PD3D12ClearValue;

typedef D3D12_RANGE TD3D12Range;

typedef D3D12_RANGE *PD3D12Range;

typedef D3D12_SUBRESOURCE_INFO TD3D12SubresourceInfo;

typedef D3D12_SUBRESOURCE_INFO *PD3D12SubresourceInfo;

typedef D3D12_TILED_RESOURCE_COORDINATE TD3D12TiledResourceCoordinate;

typedef D3D12_TILED_RESOURCE_COORDINATE *PD3D12TiledResourceCoordinate;

typedef D3D12_TILE_REGION_SIZE TD3D12TileRegionSize;

typedef D3D12_TILE_REGION_SIZE *PD3D12TileRegionSize;

typedef D3D12_TILE_RANGE_FLAGS TD3D12TileRangeFlags;

typedef D3D12_TILE_RANGE_FLAGS *PD3D12TileRangeFlags;

typedef D3D12_SUBRESOURCE_TILING TD3D12SubresourceTiling;

typedef D3D12_SUBRESOURCE_TILING *PD3D12SubresourceTiling;

typedef D3D12_TILE_SHAPE TD3D12TileShape;

typedef D3D12_TILE_SHAPE *PD3D12TileShape;

typedef D3D12_PACKED_MIP_INFO TD3D12PackedMipInfo;

typedef D3D12_PACKED_MIP_INFO *PD3D12PackedMipInfo;

typedef D3D12_TILE_MAPPING_FLAGS TD3D12TileMappingFlags;

typedef D3D12_TILE_MAPPING_FLAGS *PD3D12TileMappingFlags;

typedef D3D12_TILE_COPY_FLAGS TD3D12TileCopyFlags;

typedef D3D12_RESOURCE_STATES TD3D12ResourceStates;

typedef D3D12_RESOURCE_BARRIER_TYPE TD3D12ResourceBarrierType;

typedef D3D12_RESOURCE_TRANSITION_BARRIER TD3D12ResourceTransitionBarrier;

typedef D3D12_RESOURCE_TRANSITION_BARRIER *PD3D12ResourceTransitionBarrier;

typedef D3D12_RESOURCE_ALIASING_BARRIER TD3D12ResourceAliasingBarrier;

typedef D3D12_RESOURCE_ALIASING_BARRIER *PD3D12ResourceAliasingBarrier;

typedef D3D12_RESOURCE_UAV_BARRIER TD3D12ResourceUavBarrier;

typedef D3D12_RESOURCE_UAV_BARRIER *PD3D12ResourceUavBarrier;

typedef D3D12_RESOURCE_BARRIER_FLAGS TD3D12ResourceBarrierFlags;

typedef D3D12_RESOURCE_BARRIER TD3D12ResourceBarrier;

typedef D3D12_RESOURCE_BARRIER *PD3D12ResourceBarrier;

typedef D3D12_SUBRESOURCE_FOOTPRINT TD3D12SubresourceFootprint;

typedef D3D12_SUBRESOURCE_FOOTPRINT *PD3D12SubresourceFootprint;

typedef D3D12_PLACED_SUBRESOURCE_FOOTPRINT TD3D12PlacedSubresourceFootprint;

typedef D3D12_PLACED_SUBRESOURCE_FOOTPRINT *PD3D12PlacedSubresourceFootprint;

typedef D3D12_TEXTURE_COPY_TYPE TD3D12TextureCopyType;

typedef D3D12_TEXTURE_COPY_LOCATION TD3D12TextureCopyLocation;

typedef D3D12_TEXTURE_COPY_LOCATION *PD3D12TextureCopyLocation;

typedef D3D12_SHADER_COMPONENT_MAPPING TD3D12ShaderComponentMapping;

typedef D3D12_BUFFER_SRV_FLAGS TD3D12BufferSrvFlags;

typedef D3D12_BUFFER_SRV TD3D12BufferSrv;

typedef D3D12_BUFFER_SRV *PD3D12BufferSrv;

typedef D3D12_TEX1D_SRV TD3D12Tex1dSrv;

typedef D3D12_TEX1D_SRV *PD3D12Tex1dSrv;

typedef D3D12_TEX1D_ARRAY_SRV TD3D12Tex1dArraySrv;

typedef D3D12_TEX1D_ARRAY_SRV *PD3D12Tex1dArraySrv;

typedef D3D12_TEX2D_SRV TD3D12Tex2dSrv;

typedef D3D12_TEX2D_SRV *PD3D12Tex2dSrv;

typedef D3D12_TEX2D_ARRAY_SRV TD3D12Tex2dArraySrv;

typedef D3D12_TEX2D_ARRAY_SRV *PD3D12Tex2dArraySrv;

typedef D3D12_TEX3D_SRV TD3D12Tex3dSrv;

typedef D3D12_TEX3D_SRV *PD3D12Tex3dSrv;

typedef D3D12_TEXCUBE_SRV TD3D12TexcubeSrv;

typedef D3D12_TEXCUBE_SRV *PD3D12TexcubeSrv;

typedef D3D12_TEXCUBE_ARRAY_SRV TD3D12TexcubeArraySrv;

typedef D3D12_TEXCUBE_ARRAY_SRV *PD3D12TexcubeArraySrv;

typedef D3D12_TEX2DMS_SRV TD3D12Tex2dmsSrv;

typedef D3D12_TEX2DMS_SRV *PD3D12Tex2dmsSrv;

typedef D3D12_TEX2DMS_ARRAY_SRV TD3D12Tex2dmsArraySrv;

typedef D3D12_TEX2DMS_ARRAY_SRV *PD3D12Tex2dmsArraySrv;

typedef D3D12_SRV_DIMENSION TD3D12SrvDimension;

typedef D3D12_SHADER_RESOURCE_VIEW_DESC TD3D12ShaderResourceViewDesc;

typedef D3D12_SHADER_RESOURCE_VIEW_DESC *PD3D12ShaderResourceViewDesc;

typedef D3D12_CONSTANT_BUFFER_VIEW_DESC TD3D12ConstantBufferViewDesc;

typedef D3D12_CONSTANT_BUFFER_VIEW_DESC *PD3D12ConstantBufferViewDesc;

typedef D3D12_FILTER TD3D12Filter;

typedef D3D12_FILTER_TYPE TD3D12FilterType;

typedef D3D12_FILTER_REDUCTION_TYPE TD3D12FilterReductionType;

typedef D3D12_TEXTURE_ADDRESS_MODE TD3D12TextureAddressMode;

typedef D3D12_SAMPLER_DESC TD3D12SamplerDesc;

typedef D3D12_SAMPLER_DESC *PD3D12SamplerDesc;

typedef D3D12_BUFFER_UAV_FLAGS TD3D12BufferUavFlags;

typedef D3D12_BUFFER_UAV TD3D12BufferUav;

typedef D3D12_BUFFER_UAV *PD3D12BufferUav;

typedef D3D12_TEX1D_UAV TD3D12Tex1dUav;

typedef D3D12_TEX1D_UAV *PD3D12Tex1dUav;

typedef D3D12_TEX1D_ARRAY_UAV TD3D12Tex1dArrayUav;

typedef D3D12_TEX1D_ARRAY_UAV *PD3D12Tex1dArrayUav;

typedef D3D12_TEX2D_UAV TD3D12Tex2dUav;

typedef D3D12_TEX2D_UAV *PD3D12Tex2dUav;

typedef D3D12_TEX2D_ARRAY_UAV TD3D12Tex2dArrayUav;

typedef D3D12_TEX2D_ARRAY_UAV *PD3D12Tex2dArrayUav;

typedef D3D12_TEX3D_UAV TD3D12Tex3dUav;

typedef D3D12_TEX3D_UAV *PD3D12Tex3dUav;

typedef D3D12_UAV_DIMENSION TD3D12UavDimension;

typedef D3D12_UNORDERED_ACCESS_VIEW_DESC TD3D12UnorderedAccessViewDesc;

typedef D3D12_UNORDERED_ACCESS_VIEW_DESC *PD3D12UnorderedAccessViewDesc;

typedef D3D12_BUFFER_RTV TD3D12BufferRtv;

typedef D3D12_BUFFER_RTV *PD3D12BufferRtv;

typedef D3D12_TEX1D_RTV TD3D12Tex1dRtv;

typedef D3D12_TEX1D_RTV *PD3D12Tex1dRtv;

typedef D3D12_TEX1D_ARRAY_RTV TD3D12Tex1dArrayRtv;

typedef D3D12_TEX1D_ARRAY_RTV *PD3D12Tex1dArrayRtv;

typedef D3D12_TEX2D_RTV TD3D12Tex2dRtv;

typedef D3D12_TEX2D_RTV *PD3D12Tex2dRtv;

typedef D3D12_TEX2DMS_RTV TD3D12Tex2dmsRtv;

typedef D3D12_TEX2DMS_RTV *PD3D12Tex2dmsRtv;

typedef D3D12_TEX2D_ARRAY_RTV TD3D12Tex2dArrayRtv;

typedef D3D12_TEX2D_ARRAY_RTV *PD3D12Tex2dArrayRtv;

typedef D3D12_TEX2DMS_ARRAY_RTV TD3D12Tex2dmsArrayRtv;

typedef D3D12_TEX2DMS_ARRAY_RTV *PD3D12Tex2dmsArrayRtv;

typedef D3D12_TEX3D_RTV TD3D12Tex3dRtv;

typedef D3D12_TEX3D_RTV *PD3D12Tex3dRtv;

typedef D3D12_RTV_DIMENSION TD3D12RtvDimension;

typedef D3D12_RENDER_TARGET_VIEW_DESC TD3D12RenderTargetViewDesc;

typedef D3D12_RENDER_TARGET_VIEW_DESC *PD3D12RenderTargetViewDesc;

typedef D3D12_TEX1D_DSV TD3D12_TEX1D_DSV;

typedef D3D12_TEX1D_DSV *PD3D12_TEX1D_DSV;

typedef D3D12_TEX1D_ARRAY_DSV TD3D12Tex1dArrayDsv;

typedef D3D12_TEX1D_ARRAY_DSV *PD3D12Tex1dArrayDsv;

typedef D3D12_TEX2D_DSV TD3D12Tex2dDsv;

typedef D3D12_TEX2D_DSV *PD3D12Tex2dDsv;

typedef D3D12_TEX2D_ARRAY_DSV TD3D12Tex2dArrayDsv;

typedef D3D12_TEX2D_ARRAY_DSV *PD3D12Tex2dArrayDsv;

typedef D3D12_TEX2DMS_DSV TD3D12Tex2dmsDsv;

typedef D3D12_TEX2DMS_DSV *PD3D12Tex2dmsDsv;

typedef D3D12_TEX2DMS_ARRAY_DSV TD3D12Tex2dmsArrayDsv;

typedef D3D12_TEX2DMS_ARRAY_DSV *PD3D12Tex2dmsArrayDsv;

typedef D3D12_DSV_FLAGS TD3D12DsvFlags;

typedef D3D12_DSV_DIMENSION TD3D12DsvDimension;

typedef D3D12_DEPTH_STENCIL_VIEW_DESC TD3D12DepthStencilViewDesc;

typedef D3D12_DEPTH_STENCIL_VIEW_DESC *PD3D12DepthStencilViewDesc;

typedef D3D12_CLEAR_FLAGS TD3D12ClearFlags;

typedef D3D12_FENCE_FLAGS TD3D12FenceFlags;

typedef D3D12_DESCRIPTOR_HEAP_TYPE TD3D12DescriptorHeapType;

typedef D3D12_DESCRIPTOR_HEAP_FLAGS TD3D12DescriptorHeapFlags;

typedef D3D12_DESCRIPTOR_HEAP_DESC TD3D12DescriptorHeapDesc;

typedef D3D12_DESCRIPTOR_HEAP_DESC *PD3D12DescriptorHeapDesc;

typedef D3D12_DESCRIPTOR_RANGE_TYPE TD3D12DescriptorRangeType;

typedef D3D12_DESCRIPTOR_RANGE TD3D12DescriptorRange;

typedef D3D12_DESCRIPTOR_RANGE *PD3D12DescriptorRange;

typedef D3D12_ROOT_DESCRIPTOR_TABLE TD3D12RootDescriptorTable;

typedef D3D12_ROOT_DESCRIPTOR_TABLE *PD3D12RootDescriptorTable;

typedef D3D12_ROOT_CONSTANTS TD3D12RootConstants;

typedef D3D12_ROOT_CONSTANTS *PD3D12RootConstants;

typedef D3D12_ROOT_DESCRIPTOR TD3D12RootDescriptor;

typedef D3D12_ROOT_DESCRIPTOR *PD3D12RootDescriptor;

typedef D3D12_SHADER_VISIBILITY TD3D12ShaderVisibility;

typedef D3D12_ROOT_PARAMETER_TYPE TD3D12RootParameterType;

struct DECLSPEC_DRECORD TD3D12_ROOT_PARAMETER_INNER
{
	
public:
	union
	{
		struct 
		{
			D3D12_ROOT_DESCRIPTOR Descriptor;
		};
		struct 
		{
			D3D12_ROOT_CONSTANTS Constants;
		};
		struct 
		{
			D3D12_ROOT_DESCRIPTOR_TABLE DescriptorTable;
		};
		
	};
};


typedef D3D12_ROOT_PARAMETER TD3D12RootParameter;

typedef D3D12_ROOT_PARAMETER *PD3D12RootParameter;

typedef D3D12_ROOT_SIGNATURE_FLAGS TD3D12RootSignatureFlags;

typedef D3D12_STATIC_BORDER_COLOR TD3D12StaticBorderColor;

typedef D3D12_STATIC_SAMPLER_DESC TD3D12_STATIC_SAMPLER_DESC;

typedef D3D12_STATIC_SAMPLER_DESC *PD3D12_STATIC_SAMPLER_DESC;

typedef D3D12_ROOT_SIGNATURE_DESC TD3D12RootSignatureDesc;

typedef D3D12_ROOT_SIGNATURE_DESC *PD3D12RootSignatureDesc;

typedef D3D_ROOT_SIGNATURE_VERSION TD3DRootSignatureVersion;

typedef D3D_ROOT_SIGNATURE_VERSION *PD3DRootSignatureVersion;

typedef D3D12_CPU_DESCRIPTOR_HANDLE TD3D12CpuDescriptorHandle;

typedef D3D12_CPU_DESCRIPTOR_HANDLE *PD3D12CpuDescriptorHandle;

typedef D3D12_GPU_DESCRIPTOR_HANDLE TD3D12GpuDescriptorHandle;

typedef D3D12_GPU_DESCRIPTOR_HANDLE *PD3D12GpuDescriptorHandle;

typedef D3D12_DISCARD_REGION TD3D12DiscardRegion;

typedef D3D12_DISCARD_REGION *PD3D12DiscardRegion;

typedef D3D12_QUERY_HEAP_TYPE TD3D12QueryHeapType;

typedef D3D12_QUERY_HEAP_DESC TD3D12QueryHeapDesc;

typedef D3D12_QUERY_HEAP_DESC *PD3D12QueryHeapDesc;

typedef D3D12_QUERY_TYPE TD3D12QueryType;

typedef D3D12_PREDICATION_OP TD3D12PredicationOp;

typedef D3D12_QUERY_DATA_PIPELINE_STATISTICS TD3D12QueryDataPipelineStatistics;

typedef D3D12_QUERY_DATA_PIPELINE_STATISTICS *PD3D12QueryDataPipelineStatistics;

typedef D3D12_QUERY_DATA_SO_STATISTICS TD3D12QueryDataSoStatistics;

typedef D3D12_QUERY_DATA_SO_STATISTICS *PD3D12QueryDataSoStatistics;

typedef D3D12_STREAM_OUTPUT_BUFFER_VIEW TD3D12StreamOutputBufferView;

typedef D3D12_STREAM_OUTPUT_BUFFER_VIEW *PD3D12StreamOutputBufferView;

typedef D3D12_DRAW_ARGUMENTS TD3D12DrawArguments;

typedef D3D12_DRAW_ARGUMENTS *PD3D12DrawArguments;

typedef D3D12_DRAW_INDEXED_ARGUMENTS TD3D12DrawIndexedArguments;

typedef D3D12_DRAW_INDEXED_ARGUMENTS *PD3D12DrawIndexedArguments;

typedef D3D12_DISPATCH_ARGUMENTS TD3D12DispatchArguments;

typedef D3D12_DISPATCH_ARGUMENTS *PD3D12DispatchArguments;

typedef D3D12_VERTEX_BUFFER_VIEW TD3D12VertexBufferView;

typedef D3D12_VERTEX_BUFFER_VIEW *PD3D12VertexBufferView;

typedef D3D12_INDEX_BUFFER_VIEW TD3D12IndexBufferView;

typedef D3D12_INDEX_BUFFER_VIEW *PD3D12IndexBufferView;

typedef D3D12_INDIRECT_ARGUMENT_TYPE TD3D12IndirectArgumentType;

struct DECLSPEC_DRECORD TD3D12_INDIRECT_ARGUMENT_DESC_VertexBuffer
{
public:
	unsigned Slot;
};


struct DECLSPEC_DRECORD TD3D12_INDIRECT_ARGUMENT_DESC_Constant
{
public:
	unsigned RootParameterIndex;
	unsigned DestOffsetIn32BitValues;
	unsigned Num32BitValuesToSet;
};


struct DECLSPEC_DRECORD TD3D12_INDIRECT_ARGUMENT_DESC_ConstantBufferView
{
public:
	unsigned RootParameterIndex;
};


struct DECLSPEC_DRECORD TD3D12_INDIRECT_ARGUMENT_DESC_ShaderResourceView
{
public:
	unsigned RootParameterIndex;
};


struct DECLSPEC_DRECORD TD3D12_INDIRECT_ARGUMENT_DESC_UnorderedAccessView
{
public:
	unsigned RootParameterIndex;
};


typedef D3D12_INDIRECT_ARGUMENT_DESC TD3D12IndirectArgumentDesc;

typedef D3D12_INDIRECT_ARGUMENT_DESC *PD3D12IndirectArgumentDesc;

typedef D3D12_COMMAND_SIGNATURE_DESC TD3D12CommandSignatureDesc;

typedef D3D12_COMMAND_SIGNATURE_DESC *PD3D12CommandSignatureDesc;

typedef D3D12_SUBRESOURCE_DATA TD3D12SubresourceData;

typedef D3D12_SUBRESOURCE_DATA *PD3D12SubresourceData;

typedef D3D12_MEMCPY_DEST TD3D12MemcpyDest;

typedef D3D12_MEMCPY_DEST *PD3D12MemcpyDest;

//-- var, const, procedure ---------------------------------------------------
#define D3D12dll L"d3d12.dll"
}	/* namespace D3d12 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D12)
using namespace Winapi::D3d12;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d12HPP
