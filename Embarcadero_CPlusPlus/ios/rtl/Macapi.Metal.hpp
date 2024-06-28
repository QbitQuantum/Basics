// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.Metal.pas' rev: 34.00 (iOS)

#ifndef Macapi_MetalHPP
#define Macapi_MetalHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <Macapi.CoreServices.hpp>
#include <Macapi.Dispatch.hpp>
#include <Macapi.Mach.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Macapi
{
namespace Metal
{
//-- forward type declarations -----------------------------------------------
struct MTLOrigin;
struct MTLSize;
struct MTLRegion;
struct MTLSamplePosition;
__interface DELPHIINTERFACE MTLArgument;
typedef System::DelphiInterface<MTLArgument> _di_MTLArgument;
struct MTLSizeAndAlign;
__interface DELPHIINTERFACE MTLRenderPipelineReflection;
typedef System::DelphiInterface<MTLRenderPipelineReflection> _di_MTLRenderPipelineReflection;
__interface DELPHIINTERFACE MTLComputePipelineReflection;
typedef System::DelphiInterface<MTLComputePipelineReflection> _di_MTLComputePipelineReflection;
struct MTLDispatchThreadgroupsIndirectArguments;
struct MTLStageInRegionIndirectArguments;
struct MTLClearColor;
struct MTLScissorRect;
struct MTLViewport;
struct MTLDrawPrimitivesIndirectArguments;
struct MTLDrawIndexedPrimitivesIndirectArguments;
struct MTLDrawPatchIndirectArguments;
struct MTLQuadTessellationFactorsHalf;
struct MTLTriangleTessellationFactorsHalf;
__interface DELPHIINTERFACE MTLTextureDescriptorClass;
typedef System::DelphiInterface<MTLTextureDescriptorClass> _di_MTLTextureDescriptorClass;
__interface DELPHIINTERFACE MTLTextureDescriptor;
typedef System::DelphiInterface<MTLTextureDescriptor> _di_MTLTextureDescriptor;
class DELPHICLASS TMTLTextureDescriptor;
__interface DELPHIINTERFACE MTLArgumentClass;
typedef System::DelphiInterface<MTLArgumentClass> _di_MTLArgumentClass;
class DELPHICLASS TMTLArgument;
__interface DELPHIINTERFACE MTLTypeClass;
typedef System::DelphiInterface<MTLTypeClass> _di_MTLTypeClass;
__interface DELPHIINTERFACE MTLType;
typedef System::DelphiInterface<MTLType> _di_MTLType;
class DELPHICLASS TMTLType;
__interface DELPHIINTERFACE MTLStructTypeClass;
typedef System::DelphiInterface<MTLStructTypeClass> _di_MTLStructTypeClass;
__interface DELPHIINTERFACE MTLStructType;
typedef System::DelphiInterface<MTLStructType> _di_MTLStructType;
class DELPHICLASS TMTLStructType;
__interface DELPHIINTERFACE MTLArrayTypeClass;
typedef System::DelphiInterface<MTLArrayTypeClass> _di_MTLArrayTypeClass;
__interface DELPHIINTERFACE MTLArrayType;
typedef System::DelphiInterface<MTLArrayType> _di_MTLArrayType;
class DELPHICLASS TMTLArrayType;
__interface DELPHIINTERFACE MTLTextureReferenceTypeClass;
typedef System::DelphiInterface<MTLTextureReferenceTypeClass> _di_MTLTextureReferenceTypeClass;
__interface DELPHIINTERFACE MTLTextureReferenceType;
typedef System::DelphiInterface<MTLTextureReferenceType> _di_MTLTextureReferenceType;
class DELPHICLASS TMTLTextureReferenceType;
__interface DELPHIINTERFACE MTLPointerTypeClass;
typedef System::DelphiInterface<MTLPointerTypeClass> _di_MTLPointerTypeClass;
__interface DELPHIINTERFACE MTLPointerType;
typedef System::DelphiInterface<MTLPointerType> _di_MTLPointerType;
class DELPHICLASS TMTLPointerType;
__interface DELPHIINTERFACE MTLStructMemberClass;
typedef System::DelphiInterface<MTLStructMemberClass> _di_MTLStructMemberClass;
__interface DELPHIINTERFACE MTLStructMember;
typedef System::DelphiInterface<MTLStructMember> _di_MTLStructMember;
class DELPHICLASS TMTLStructMember;
__interface DELPHIINTERFACE MTLCompileOptionsClass;
typedef System::DelphiInterface<MTLCompileOptionsClass> _di_MTLCompileOptionsClass;
__interface DELPHIINTERFACE MTLCompileOptions;
typedef System::DelphiInterface<MTLCompileOptions> _di_MTLCompileOptions;
class DELPHICLASS TMTLCompileOptions;
__interface DELPHIINTERFACE MTLFunctionConstantValuesClass;
typedef System::DelphiInterface<MTLFunctionConstantValuesClass> _di_MTLFunctionConstantValuesClass;
__interface DELPHIINTERFACE MTLFunctionConstantValues;
typedef System::DelphiInterface<MTLFunctionConstantValues> _di_MTLFunctionConstantValues;
class DELPHICLASS TMTLFunctionConstantValues;
__interface DELPHIINTERFACE MTLVertexAttributeClass;
typedef System::DelphiInterface<MTLVertexAttributeClass> _di_MTLVertexAttributeClass;
__interface DELPHIINTERFACE MTLVertexAttribute;
typedef System::DelphiInterface<MTLVertexAttribute> _di_MTLVertexAttribute;
class DELPHICLASS TMTLVertexAttribute;
__interface DELPHIINTERFACE MTLAttributeClass;
typedef System::DelphiInterface<MTLAttributeClass> _di_MTLAttributeClass;
__interface DELPHIINTERFACE MTLAttribute;
typedef System::DelphiInterface<MTLAttribute> _di_MTLAttribute;
class DELPHICLASS TMTLAttribute;
__interface DELPHIINTERFACE MTLFunctionConstantClass;
typedef System::DelphiInterface<MTLFunctionConstantClass> _di_MTLFunctionConstantClass;
__interface DELPHIINTERFACE MTLFunctionConstant;
typedef System::DelphiInterface<MTLFunctionConstant> _di_MTLFunctionConstant;
class DELPHICLASS TMTLFunctionConstant;
__interface DELPHIINTERFACE MTLTileRenderPipelineDescriptorClass;
typedef System::DelphiInterface<MTLTileRenderPipelineDescriptorClass> _di_MTLTileRenderPipelineDescriptorClass;
__interface DELPHIINTERFACE MTLTileRenderPipelineDescriptor;
typedef System::DelphiInterface<MTLTileRenderPipelineDescriptor> _di_MTLTileRenderPipelineDescriptor;
class DELPHICLASS TMTLTileRenderPipelineDescriptor;
__interface DELPHIINTERFACE MTLSamplerDescriptorClass;
typedef System::DelphiInterface<MTLSamplerDescriptorClass> _di_MTLSamplerDescriptorClass;
__interface DELPHIINTERFACE MTLSamplerDescriptor;
typedef System::DelphiInterface<MTLSamplerDescriptor> _di_MTLSamplerDescriptor;
class DELPHICLASS TMTLSamplerDescriptor;
__interface DELPHIINTERFACE MTLRenderPipelineColorAttachmentDescriptorClass;
typedef System::DelphiInterface<MTLRenderPipelineColorAttachmentDescriptorClass> _di_MTLRenderPipelineColorAttachmentDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPipelineColorAttachmentDescriptor;
typedef System::DelphiInterface<MTLRenderPipelineColorAttachmentDescriptor> _di_MTLRenderPipelineColorAttachmentDescriptor;
class DELPHICLASS TMTLRenderPipelineColorAttachmentDescriptor;
__interface DELPHIINTERFACE MTLDepthStencilDescriptorClass;
typedef System::DelphiInterface<MTLDepthStencilDescriptorClass> _di_MTLDepthStencilDescriptorClass;
__interface DELPHIINTERFACE MTLDepthStencilDescriptor;
typedef System::DelphiInterface<MTLDepthStencilDescriptor> _di_MTLDepthStencilDescriptor;
class DELPHICLASS TMTLDepthStencilDescriptor;
__interface DELPHIINTERFACE MTLRenderPipelineDescriptorClass;
typedef System::DelphiInterface<MTLRenderPipelineDescriptorClass> _di_MTLRenderPipelineDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPipelineDescriptor;
typedef System::DelphiInterface<MTLRenderPipelineDescriptor> _di_MTLRenderPipelineDescriptor;
class DELPHICLASS TMTLRenderPipelineDescriptor;
__interface DELPHIINTERFACE MTLRenderPassDescriptorClass;
typedef System::DelphiInterface<MTLRenderPassDescriptorClass> _di_MTLRenderPassDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPassDescriptor;
typedef System::DelphiInterface<MTLRenderPassDescriptor> _di_MTLRenderPassDescriptor;
class DELPHICLASS TMTLRenderPassDescriptor;
__interface DELPHIINTERFACE MTLRenderPipelineReflectionClass;
typedef System::DelphiInterface<MTLRenderPipelineReflectionClass> _di_MTLRenderPipelineReflectionClass;
class DELPHICLASS TMTLRenderPipelineReflection;
__interface DELPHIINTERFACE MTLComputePipelineDescriptorClass;
typedef System::DelphiInterface<MTLComputePipelineDescriptorClass> _di_MTLComputePipelineDescriptorClass;
__interface DELPHIINTERFACE MTLComputePipelineDescriptor;
typedef System::DelphiInterface<MTLComputePipelineDescriptor> _di_MTLComputePipelineDescriptor;
class DELPHICLASS TMTLComputePipelineDescriptor;
__interface DELPHIINTERFACE MTLComputePipelineReflectionClass;
typedef System::DelphiInterface<MTLComputePipelineReflectionClass> _di_MTLComputePipelineReflectionClass;
class DELPHICLASS TMTLComputePipelineReflection;
__interface DELPHIINTERFACE MTLHeapDescriptorClass;
typedef System::DelphiInterface<MTLHeapDescriptorClass> _di_MTLHeapDescriptorClass;
__interface DELPHIINTERFACE MTLHeapDescriptor;
typedef System::DelphiInterface<MTLHeapDescriptor> _di_MTLHeapDescriptor;
class DELPHICLASS TMTLHeapDescriptor;
__interface DELPHIINTERFACE MTLIndirectCommandBufferDescriptorClass;
typedef System::DelphiInterface<MTLIndirectCommandBufferDescriptorClass> _di_MTLIndirectCommandBufferDescriptorClass;
__interface DELPHIINTERFACE MTLIndirectCommandBufferDescriptor;
typedef System::DelphiInterface<MTLIndirectCommandBufferDescriptor> _di_MTLIndirectCommandBufferDescriptor;
class DELPHICLASS TMTLIndirectCommandBufferDescriptor;
__interface DELPHIINTERFACE MTLSharedEventHandleClass;
typedef System::DelphiInterface<MTLSharedEventHandleClass> _di_MTLSharedEventHandleClass;
__interface DELPHIINTERFACE MTLSharedEventHandle;
typedef System::DelphiInterface<MTLSharedEventHandle> _di_MTLSharedEventHandle;
class DELPHICLASS TMTLSharedEventHandle;
__interface DELPHIINTERFACE MTLArgumentDescriptorClass;
typedef System::DelphiInterface<MTLArgumentDescriptorClass> _di_MTLArgumentDescriptorClass;
__interface DELPHIINTERFACE MTLArgumentDescriptor;
typedef System::DelphiInterface<MTLArgumentDescriptor> _di_MTLArgumentDescriptor;
class DELPHICLASS TMTLArgumentDescriptor;
__interface DELPHIINTERFACE MTLStencilDescriptorClass;
typedef System::DelphiInterface<MTLStencilDescriptorClass> _di_MTLStencilDescriptorClass;
__interface DELPHIINTERFACE MTLStencilDescriptor;
typedef System::DelphiInterface<MTLStencilDescriptor> _di_MTLStencilDescriptor;
class DELPHICLASS TMTLStencilDescriptor;
__interface DELPHIINTERFACE MTLRenderPassAttachmentDescriptorClass;
typedef System::DelphiInterface<MTLRenderPassAttachmentDescriptorClass> _di_MTLRenderPassAttachmentDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPassAttachmentDescriptor;
typedef System::DelphiInterface<MTLRenderPassAttachmentDescriptor> _di_MTLRenderPassAttachmentDescriptor;
class DELPHICLASS TMTLRenderPassAttachmentDescriptor;
__interface DELPHIINTERFACE MTLRenderPassColorAttachmentDescriptorClass;
typedef System::DelphiInterface<MTLRenderPassColorAttachmentDescriptorClass> _di_MTLRenderPassColorAttachmentDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPassColorAttachmentDescriptor;
typedef System::DelphiInterface<MTLRenderPassColorAttachmentDescriptor> _di_MTLRenderPassColorAttachmentDescriptor;
class DELPHICLASS TMTLRenderPassColorAttachmentDescriptor;
__interface DELPHIINTERFACE MTLRenderPassDepthAttachmentDescriptorClass;
typedef System::DelphiInterface<MTLRenderPassDepthAttachmentDescriptorClass> _di_MTLRenderPassDepthAttachmentDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPassDepthAttachmentDescriptor;
typedef System::DelphiInterface<MTLRenderPassDepthAttachmentDescriptor> _di_MTLRenderPassDepthAttachmentDescriptor;
class DELPHICLASS TMTLRenderPassDepthAttachmentDescriptor;
__interface DELPHIINTERFACE MTLRenderPassStencilAttachmentDescriptorClass;
typedef System::DelphiInterface<MTLRenderPassStencilAttachmentDescriptorClass> _di_MTLRenderPassStencilAttachmentDescriptorClass;
__interface DELPHIINTERFACE MTLRenderPassStencilAttachmentDescriptor;
typedef System::DelphiInterface<MTLRenderPassStencilAttachmentDescriptor> _di_MTLRenderPassStencilAttachmentDescriptor;
class DELPHICLASS TMTLRenderPassStencilAttachmentDescriptor;
__interface DELPHIINTERFACE MTLRenderPassColorAttachmentDescriptorArrayClass;
typedef System::DelphiInterface<MTLRenderPassColorAttachmentDescriptorArrayClass> _di_MTLRenderPassColorAttachmentDescriptorArrayClass;
__interface DELPHIINTERFACE MTLRenderPassColorAttachmentDescriptorArray;
typedef System::DelphiInterface<MTLRenderPassColorAttachmentDescriptorArray> _di_MTLRenderPassColorAttachmentDescriptorArray;
class DELPHICLASS TMTLRenderPassColorAttachmentDescriptorArray;
__interface DELPHIINTERFACE MTLBufferLayoutDescriptorClass;
typedef System::DelphiInterface<MTLBufferLayoutDescriptorClass> _di_MTLBufferLayoutDescriptorClass;
__interface DELPHIINTERFACE MTLBufferLayoutDescriptor;
typedef System::DelphiInterface<MTLBufferLayoutDescriptor> _di_MTLBufferLayoutDescriptor;
class DELPHICLASS TMTLBufferLayoutDescriptor;
__interface DELPHIINTERFACE MTLBufferLayoutDescriptorArrayClass;
typedef System::DelphiInterface<MTLBufferLayoutDescriptorArrayClass> _di_MTLBufferLayoutDescriptorArrayClass;
__interface DELPHIINTERFACE MTLBufferLayoutDescriptorArray;
typedef System::DelphiInterface<MTLBufferLayoutDescriptorArray> _di_MTLBufferLayoutDescriptorArray;
class DELPHICLASS TMTLBufferLayoutDescriptorArray;
__interface DELPHIINTERFACE MTLAttributeDescriptorClass;
typedef System::DelphiInterface<MTLAttributeDescriptorClass> _di_MTLAttributeDescriptorClass;
__interface DELPHIINTERFACE MTLAttributeDescriptor;
typedef System::DelphiInterface<MTLAttributeDescriptor> _di_MTLAttributeDescriptor;
class DELPHICLASS TMTLAttributeDescriptor;
__interface DELPHIINTERFACE MTLAttributeDescriptorArrayClass;
typedef System::DelphiInterface<MTLAttributeDescriptorArrayClass> _di_MTLAttributeDescriptorArrayClass;
__interface DELPHIINTERFACE MTLAttributeDescriptorArray;
typedef System::DelphiInterface<MTLAttributeDescriptorArray> _di_MTLAttributeDescriptorArray;
class DELPHICLASS TMTLAttributeDescriptorArray;
__interface DELPHIINTERFACE MTLStageInputOutputDescriptorClass;
typedef System::DelphiInterface<MTLStageInputOutputDescriptorClass> _di_MTLStageInputOutputDescriptorClass;
__interface DELPHIINTERFACE MTLStageInputOutputDescriptor;
typedef System::DelphiInterface<MTLStageInputOutputDescriptor> _di_MTLStageInputOutputDescriptor;
class DELPHICLASS TMTLStageInputOutputDescriptor;
__interface DELPHIINTERFACE MTLPipelineBufferDescriptorClass;
typedef System::DelphiInterface<MTLPipelineBufferDescriptorClass> _di_MTLPipelineBufferDescriptorClass;
__interface DELPHIINTERFACE MTLPipelineBufferDescriptor;
typedef System::DelphiInterface<MTLPipelineBufferDescriptor> _di_MTLPipelineBufferDescriptor;
class DELPHICLASS TMTLPipelineBufferDescriptor;
__interface DELPHIINTERFACE MTLPipelineBufferDescriptorArrayClass;
typedef System::DelphiInterface<MTLPipelineBufferDescriptorArrayClass> _di_MTLPipelineBufferDescriptorArrayClass;
__interface DELPHIINTERFACE MTLPipelineBufferDescriptorArray;
typedef System::DelphiInterface<MTLPipelineBufferDescriptorArray> _di_MTLPipelineBufferDescriptorArray;
class DELPHICLASS TMTLPipelineBufferDescriptorArray;
__interface DELPHIINTERFACE MTLVertexDescriptorClass;
typedef System::DelphiInterface<MTLVertexDescriptorClass> _di_MTLVertexDescriptorClass;
__interface DELPHIINTERFACE MTLVertexDescriptor;
typedef System::DelphiInterface<MTLVertexDescriptor> _di_MTLVertexDescriptor;
class DELPHICLASS TMTLVertexDescriptor;
__interface DELPHIINTERFACE MTLRenderPipelineColorAttachmentDescriptorArrayClass;
typedef System::DelphiInterface<MTLRenderPipelineColorAttachmentDescriptorArrayClass> _di_MTLRenderPipelineColorAttachmentDescriptorArrayClass;
__interface DELPHIINTERFACE MTLRenderPipelineColorAttachmentDescriptorArray;
typedef System::DelphiInterface<MTLRenderPipelineColorAttachmentDescriptorArray> _di_MTLRenderPipelineColorAttachmentDescriptorArray;
class DELPHICLASS TMTLRenderPipelineColorAttachmentDescriptorArray;
__interface DELPHIINTERFACE MTLTileRenderPipelineColorAttachmentDescriptorClass;
typedef System::DelphiInterface<MTLTileRenderPipelineColorAttachmentDescriptorClass> _di_MTLTileRenderPipelineColorAttachmentDescriptorClass;
__interface DELPHIINTERFACE MTLTileRenderPipelineColorAttachmentDescriptor;
typedef System::DelphiInterface<MTLTileRenderPipelineColorAttachmentDescriptor> _di_MTLTileRenderPipelineColorAttachmentDescriptor;
class DELPHICLASS TMTLTileRenderPipelineColorAttachmentDescriptor;
__interface DELPHIINTERFACE MTLTileRenderPipelineColorAttachmentDescriptorArrayClass;
typedef System::DelphiInterface<MTLTileRenderPipelineColorAttachmentDescriptorArrayClass> _di_MTLTileRenderPipelineColorAttachmentDescriptorArrayClass;
__interface DELPHIINTERFACE MTLTileRenderPipelineColorAttachmentDescriptorArray;
typedef System::DelphiInterface<MTLTileRenderPipelineColorAttachmentDescriptorArray> _di_MTLTileRenderPipelineColorAttachmentDescriptorArray;
class DELPHICLASS TMTLTileRenderPipelineColorAttachmentDescriptorArray;
__interface DELPHIINTERFACE MTLVertexBufferLayoutDescriptorClass;
typedef System::DelphiInterface<MTLVertexBufferLayoutDescriptorClass> _di_MTLVertexBufferLayoutDescriptorClass;
__interface DELPHIINTERFACE MTLVertexBufferLayoutDescriptor;
typedef System::DelphiInterface<MTLVertexBufferLayoutDescriptor> _di_MTLVertexBufferLayoutDescriptor;
class DELPHICLASS TMTLVertexBufferLayoutDescriptor;
__interface DELPHIINTERFACE MTLVertexBufferLayoutDescriptorArrayClass;
typedef System::DelphiInterface<MTLVertexBufferLayoutDescriptorArrayClass> _di_MTLVertexBufferLayoutDescriptorArrayClass;
__interface DELPHIINTERFACE MTLVertexBufferLayoutDescriptorArray;
typedef System::DelphiInterface<MTLVertexBufferLayoutDescriptorArray> _di_MTLVertexBufferLayoutDescriptorArray;
class DELPHICLASS TMTLVertexBufferLayoutDescriptorArray;
__interface DELPHIINTERFACE MTLVertexAttributeDescriptorClass;
typedef System::DelphiInterface<MTLVertexAttributeDescriptorClass> _di_MTLVertexAttributeDescriptorClass;
__interface DELPHIINTERFACE MTLVertexAttributeDescriptor;
typedef System::DelphiInterface<MTLVertexAttributeDescriptor> _di_MTLVertexAttributeDescriptor;
class DELPHICLASS TMTLVertexAttributeDescriptor;
__interface DELPHIINTERFACE MTLVertexAttributeDescriptorArrayClass;
typedef System::DelphiInterface<MTLVertexAttributeDescriptorArrayClass> _di_MTLVertexAttributeDescriptorArrayClass;
__interface DELPHIINTERFACE MTLVertexAttributeDescriptorArray;
typedef System::DelphiInterface<MTLVertexAttributeDescriptorArray> _di_MTLVertexAttributeDescriptorArray;
class DELPHICLASS TMTLVertexAttributeDescriptorArray;
__interface DELPHIINTERFACE MTLCaptureManagerClass;
typedef System::DelphiInterface<MTLCaptureManagerClass> _di_MTLCaptureManagerClass;
__interface DELPHIINTERFACE MTLCaptureManager;
typedef System::DelphiInterface<MTLCaptureManager> _di_MTLCaptureManager;
class DELPHICLASS TMTLCaptureManager;
__interface DELPHIINTERFACE MTLSharedEventListenerClass;
typedef System::DelphiInterface<MTLSharedEventListenerClass> _di_MTLSharedEventListenerClass;
__interface DELPHIINTERFACE MTLSharedEventListener;
typedef System::DelphiInterface<MTLSharedEventListener> _di_MTLSharedEventListener;
class DELPHICLASS TMTLSharedEventListener;
__interface DELPHIINTERFACE MTLDeviceClass;
typedef System::DelphiInterface<MTLDeviceClass> _di_MTLDeviceClass;
__interface DELPHIINTERFACE MTLDevice;
typedef System::DelphiInterface<MTLDevice> _di_MTLDevice;
class DELPHICLASS TMTLDevice;
__interface DELPHIINTERFACE MTLCommandEncoder;
typedef System::DelphiInterface<MTLCommandEncoder> _di_MTLCommandEncoder;
__interface DELPHIINTERFACE MTLHeap;
typedef System::DelphiInterface<MTLHeap> _di_MTLHeap;
__interface DELPHIINTERFACE MTLResource;
typedef System::DelphiInterface<MTLResource> _di_MTLResource;
__interface DELPHIINTERFACE MTLTextureClass;
typedef System::DelphiInterface<MTLTextureClass> _di_MTLTextureClass;
__interface DELPHIINTERFACE MTLTexture;
typedef System::DelphiInterface<MTLTexture> _di_MTLTexture;
class DELPHICLASS TMTLTexture;
__interface DELPHIINTERFACE MTLBuffer;
typedef System::DelphiInterface<MTLBuffer> _di_MTLBuffer;
__interface DELPHIINTERFACE MTLFunction;
typedef System::DelphiInterface<MTLFunction> _di_MTLFunction;
__interface DELPHIINTERFACE MTLLibrary;
typedef System::DelphiInterface<MTLLibrary> _di_MTLLibrary;
__interface DELPHIINTERFACE MTLArgumentEncoder;
typedef System::DelphiInterface<MTLArgumentEncoder> _di_MTLArgumentEncoder;
__interface DELPHIINTERFACE MTLCommandQueue;
typedef System::DelphiInterface<MTLCommandQueue> _di_MTLCommandQueue;
__interface DELPHIINTERFACE MTLDepthStencilState;
typedef System::DelphiInterface<MTLDepthStencilState> _di_MTLDepthStencilState;
__interface DELPHIINTERFACE MTLSamplerState;
typedef System::DelphiInterface<MTLSamplerState> _di_MTLSamplerState;
__interface DELPHIINTERFACE MTLRenderPipelineState;
typedef System::DelphiInterface<MTLRenderPipelineState> _di_MTLRenderPipelineState;
__interface DELPHIINTERFACE MTLComputePipelineState;
typedef System::DelphiInterface<MTLComputePipelineState> _di_MTLComputePipelineState;
__interface DELPHIINTERFACE MTLFence;
typedef System::DelphiInterface<MTLFence> _di_MTLFence;
__interface DELPHIINTERFACE MTLIndirectRenderCommandEncoder;
typedef System::DelphiInterface<MTLIndirectRenderCommandEncoder> _di_MTLIndirectRenderCommandEncoder;
__interface DELPHIINTERFACE MTLIndirectComputeCommandEncoder;
typedef System::DelphiInterface<MTLIndirectComputeCommandEncoder> _di_MTLIndirectComputeCommandEncoder;
__interface DELPHIINTERFACE MTLIndirectCommandBuffer;
typedef System::DelphiInterface<MTLIndirectCommandBuffer> _di_MTLIndirectCommandBuffer;
__interface DELPHIINTERFACE MTLEvent;
typedef System::DelphiInterface<MTLEvent> _di_MTLEvent;
__interface DELPHIINTERFACE MTLSharedEvent;
typedef System::DelphiInterface<MTLSharedEvent> _di_MTLSharedEvent;
__interface DELPHIINTERFACE MTLBlitCommandEncoder;
typedef System::DelphiInterface<MTLBlitCommandEncoder> _di_MTLBlitCommandEncoder;
__interface DELPHIINTERFACE MTLRenderCommandEncoder;
typedef System::DelphiInterface<MTLRenderCommandEncoder> _di_MTLRenderCommandEncoder;
__interface DELPHIINTERFACE MTLParallelRenderCommandEncoder;
typedef System::DelphiInterface<MTLParallelRenderCommandEncoder> _di_MTLParallelRenderCommandEncoder;
__interface DELPHIINTERFACE MTLComputeCommandEncoder;
typedef System::DelphiInterface<MTLComputeCommandEncoder> _di_MTLComputeCommandEncoder;
__interface DELPHIINTERFACE MTLDrawable;
typedef System::DelphiInterface<MTLDrawable> _di_MTLDrawable;
__interface DELPHIINTERFACE MTLCommandBuffer;
typedef System::DelphiInterface<MTLCommandBuffer> _di_MTLCommandBuffer;
__interface DELPHIINTERFACE MTLCaptureScope;
typedef System::DelphiInterface<MTLCaptureScope> _di_MTLCaptureScope;
__interface DELPHIINTERFACE MTLIndirectRenderCommand;
typedef System::DelphiInterface<MTLIndirectRenderCommand> _di_MTLIndirectRenderCommand;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD MTLOrigin
{
public:
	unsigned long x;
	unsigned long y;
	unsigned long z;
};


typedef MTLOrigin *PMTLOrigin;

struct DECLSPEC_DRECORD MTLSize
{
public:
	unsigned long width;
	unsigned long height;
	unsigned long depth;
};


typedef MTLSize *PMTLSize;

struct DECLSPEC_DRECORD MTLRegion
{
public:
	MTLOrigin origin;
	MTLSize size;
};


typedef MTLRegion *PMTLRegion;

struct DECLSPEC_DRECORD MTLSamplePosition
{
public:
	float x;
	float y;
};


typedef MTLSamplePosition *PMTLSamplePosition;

typedef unsigned long MTLResourceUsage;

typedef unsigned long MTLBarrierScope;

typedef unsigned long MTLPixelFormat;

typedef unsigned long MTLPurgeableState;

typedef unsigned long MTLCPUCacheMode;

typedef unsigned long MTLStorageMode;

typedef unsigned long MTLResourceOptions;

typedef unsigned long MTLTextureType;

typedef unsigned long MTLTextureUsage;

typedef void * IOSurfaceRef;

typedef void * *PIOSurfaceRef;

typedef unsigned long MTLDataType;

typedef unsigned long MTLArgumentType;

typedef unsigned long MTLArgumentAccess;

typedef _di_MTLArgument MTLAutoreleasedArgument;

typedef _di_MTLArgument *PMTLAutoreleasedArgument;

typedef unsigned long MTLPatchType;

typedef unsigned long MTLFunctionType;

typedef unsigned long MTLLanguageVersion;

typedef unsigned long MTLLibraryError;

typedef void __fastcall (__closure *TMTLLibraryNewFunctionWithNameConstantValuesCompletionHandler)(_di_MTLFunction function, Iosapi::Foundation::_di_NSError error);

typedef unsigned long MTLFeatureSet;

typedef unsigned long MTLPipelineOption;

typedef unsigned long MTLReadWriteTextureTier;

typedef unsigned long MTLArgumentBuffersTier;

struct DECLSPEC_DRECORD MTLSizeAndAlign
{
public:
	unsigned long size;
	unsigned long align;
};


typedef MTLSizeAndAlign *PMTLSizeAndAlign;

typedef _di_MTLRenderPipelineReflection MTLAutoreleasedRenderPipelineReflection;

typedef _di_MTLRenderPipelineReflection *PMTLAutoreleasedRenderPipelineReflection;

typedef _di_MTLComputePipelineReflection MTLAutoreleasedComputePipelineReflection;

typedef _di_MTLComputePipelineReflection *PMTLAutoreleasedComputePipelineReflection;

typedef void __fastcall (__closure *MTLNewLibraryCompletionHandler)(_di_MTLLibrary library, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *MTLNewRenderPipelineStateCompletionHandler)(_di_MTLRenderPipelineState renderPipelineState, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *MTLNewRenderPipelineStateWithReflectionCompletionHandler)(_di_MTLRenderPipelineState renderPipelineState, _di_MTLRenderPipelineReflection reflection, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *MTLNewComputePipelineStateCompletionHandler)(_di_MTLComputePipelineState computePipelineState, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *MTLNewComputePipelineStateWithReflectionCompletionHandler)(_di_MTLComputePipelineState computePipelineState, _di_MTLComputePipelineReflection reflection, Iosapi::Foundation::_di_NSError error);

typedef void __fastcall (__closure *TMTLDeviceNewBufferWithBytesNoCopyDeallocator)(void * pointer, unsigned long length);

typedef void * dispatch_data_t;

typedef void * *Pdispatch_data_t;

typedef unsigned long MTLBlitOption;

typedef unsigned long MTLCommandBufferStatus;

typedef unsigned long MTLCommandBufferError;

typedef void __fastcall (__closure *MTLCommandBufferHandler)(_di_MTLCommandBuffer commandBuffer);

typedef unsigned long MTLDispatchType;

struct DECLSPEC_DRECORD MTLDispatchThreadgroupsIndirectArguments
{
public:
	System::StaticArray<unsigned long, 3> threadgroupsPerGrid;
};


typedef MTLDispatchThreadgroupsIndirectArguments *PMTLDispatchThreadgroupsIndirectArguments;

struct DECLSPEC_DRECORD MTLStageInRegionIndirectArguments
{
public:
	System::StaticArray<unsigned long, 3> stageInOrigin;
	System::StaticArray<unsigned long, 3> stageInSize;
};


typedef MTLStageInRegionIndirectArguments *PMTLStageInRegionIndirectArguments;

typedef unsigned long MTLCompareFunction;

typedef unsigned long MTLStencilOperation;

typedef void __fastcall (__closure *MTLDrawablePresentedHandler)(_di_MTLDrawable drawable);

typedef unsigned long MTLLoadAction;

typedef unsigned long MTLStoreAction;

typedef unsigned long MTLStoreActionOptions;

struct DECLSPEC_DRECORD MTLClearColor
{
public:
	double red;
	double green;
	double blue;
	double alpha;
};


typedef MTLClearColor *PMTLClearColor;

typedef unsigned long MTLMultisampleDepthResolveFilter;

typedef unsigned long MTLMultisampleStencilResolveFilter;

typedef unsigned long MTLAttributeFormat;

typedef unsigned long MTLIndexType;

typedef unsigned long MTLStepFunction;

typedef unsigned long MTLMutability;

typedef unsigned long MTLPrimitiveType;

typedef unsigned long MTLVisibilityResultMode;

struct DECLSPEC_DRECORD MTLScissorRect
{
public:
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
};


typedef MTLScissorRect *PMTLScissorRect;

struct DECLSPEC_DRECORD MTLViewport
{
public:
	double originX;
	double originY;
	double width;
	double height;
	double znear;
	double zfar;
};


typedef MTLViewport *PMTLViewport;

typedef unsigned long MTLCullMode;

typedef unsigned long MTLWinding;

typedef unsigned long MTLDepthClipMode;

typedef unsigned long MTLTriangleFillMode;

struct DECLSPEC_DRECORD MTLDrawPrimitivesIndirectArguments
{
public:
	unsigned long vertexCount;
	unsigned long instanceCount;
	unsigned long vertexStart;
	unsigned long baseInstance;
};


typedef MTLDrawPrimitivesIndirectArguments *PMTLDrawPrimitivesIndirectArguments;

struct DECLSPEC_DRECORD MTLDrawIndexedPrimitivesIndirectArguments
{
public:
	unsigned long indexCount;
	unsigned long instanceCount;
	unsigned long indexStart;
	int baseVertex;
	unsigned long baseInstance;
};


typedef MTLDrawIndexedPrimitivesIndirectArguments *PMTLDrawIndexedPrimitivesIndirectArguments;

struct DECLSPEC_DRECORD MTLDrawPatchIndirectArguments
{
public:
	unsigned long patchCount;
	unsigned long instanceCount;
	unsigned long patchStart;
	unsigned long baseInstance;
};


typedef MTLDrawPatchIndirectArguments *PMTLDrawPatchIndirectArguments;

struct DECLSPEC_DRECORD MTLQuadTessellationFactorsHalf
{
public:
	System::StaticArray<System::Word, 4> edgeTessellationFactor;
	System::StaticArray<System::Word, 2> insideTessellationFactor;
};


typedef MTLQuadTessellationFactorsHalf *PMTLQuadTessellationFactorsHalf;

struct DECLSPEC_DRECORD MTLTriangleTessellationFactorsHalf
{
public:
	System::StaticArray<System::Word, 3> edgeTessellationFactor;
	System::Word insideTessellationFactor;
};


typedef MTLTriangleTessellationFactorsHalf *PMTLTriangleTessellationFactorsHalf;

typedef unsigned long MTLRenderStages;

typedef unsigned long MTLBlendFactor;

typedef unsigned long MTLBlendOperation;

typedef unsigned long MTLColorWriteMask;

typedef unsigned long MTLPrimitiveTopologyClass;

typedef unsigned long MTLTessellationPartitionMode;

typedef unsigned long MTLTessellationFactorStepFunction;

typedef unsigned long MTLTessellationFactorFormat;

typedef unsigned long MTLTessellationControlPointIndexType;

typedef unsigned long MTLVertexFormat;

typedef unsigned long MTLVertexStepFunction;

typedef unsigned long MTLSamplerMinMagFilter;

typedef unsigned long MTLSamplerMipFilter;

typedef unsigned long MTLSamplerAddressMode;

typedef unsigned long MTLSamplerBorderColor;

typedef unsigned long MTLIndirectCommandType;

typedef void __fastcall (__closure *MTLSharedEventNotificationBlock)(_di_MTLSharedEvent sharedEvent, unsigned __int64 value);

__interface  INTERFACE_UUID("{AB8548A2-66BF-4CDD-B72F-C4E574C7632A}") MTLTextureDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MTLTextureDescriptor __cdecl texture2DDescriptorWithPixelFormat(unsigned long pixelFormat, unsigned long width, unsigned long height, bool mipmapped) = 0 ;
	virtual _di_MTLTextureDescriptor __cdecl textureCubeDescriptorWithPixelFormat(unsigned long pixelFormat, unsigned long size, bool mipmapped) = 0 ;
	virtual _di_MTLTextureDescriptor __cdecl textureBufferDescriptorWithPixelFormat(unsigned long pixelFormat, unsigned long width, unsigned long resourceOptions, unsigned long usage) = 0 ;
};

__interface  INTERFACE_UUID("{9E0D3B5F-C43D-4A37-9341-CD93A6E47D81}") MTLTextureDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setTextureType(unsigned long textureType) = 0 ;
	virtual unsigned long __cdecl textureType() = 0 ;
	virtual void __cdecl setPixelFormat(unsigned long pixelFormat) = 0 ;
	virtual unsigned long __cdecl pixelFormat() = 0 ;
	virtual void __cdecl setWidth(unsigned long width) = 0 ;
	virtual unsigned long __cdecl width() = 0 ;
	virtual void __cdecl setHeight(unsigned long height) = 0 ;
	virtual unsigned long __cdecl height() = 0 ;
	virtual void __cdecl setDepth(unsigned long depth) = 0 ;
	virtual unsigned long __cdecl depth() = 0 ;
	virtual void __cdecl setMipmapLevelCount(unsigned long mipmapLevelCount) = 0 ;
	virtual unsigned long __cdecl mipmapLevelCount() = 0 ;
	virtual void __cdecl setSampleCount(unsigned long sampleCount) = 0 ;
	virtual unsigned long __cdecl sampleCount() = 0 ;
	virtual void __cdecl setArrayLength(unsigned long arrayLength) = 0 ;
	virtual unsigned long __cdecl arrayLength() = 0 ;
	virtual void __cdecl setResourceOptions(unsigned long resourceOptions) = 0 ;
	virtual unsigned long __cdecl resourceOptions() = 0 ;
	virtual void __cdecl setCpuCacheMode(unsigned long cpuCacheMode) = 0 ;
	virtual unsigned long __cdecl cpuCacheMode() = 0 ;
	virtual void __cdecl setStorageMode(unsigned long storageMode) = 0 ;
	virtual unsigned long __cdecl storageMode() = 0 ;
	virtual void __cdecl setUsage(unsigned long usage) = 0 ;
	virtual unsigned long __cdecl usage() = 0 ;
	virtual void __cdecl setAllowGPUOptimizedContents(bool allowGPUOptimizedContents) = 0 ;
	virtual bool __cdecl allowGPUOptimizedContents() = 0 ;
};

class PASCALIMPLEMENTATION TMTLTextureDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureDescriptorClass,_di_MTLTextureDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureDescriptorClass,_di_MTLTextureDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLTextureDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureDescriptorClass,_di_MTLTextureDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLTextureDescriptor() { }
	
};


typedef void * PMTLTextureDescriptor;

__interface  INTERFACE_UUID("{FED43758-4F5D-4E52-B96A-EAA5237C415D}") MTLArgumentClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{444C2B50-9E66-4C28-91BC-4028F67999BF}") MTLArgument  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual unsigned long __cdecl type() = 0 ;
	virtual unsigned long __cdecl access() = 0 ;
	virtual unsigned long __cdecl index() = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual unsigned long __cdecl bufferAlignment() = 0 ;
	virtual unsigned long __cdecl bufferDataSize() = 0 ;
	virtual unsigned long __cdecl bufferDataType() = 0 ;
	virtual _di_MTLStructType __cdecl bufferStructType() = 0 ;
	virtual _di_MTLPointerType __cdecl bufferPointerType() = 0 ;
	virtual unsigned long __cdecl threadgroupMemoryAlignment() = 0 ;
	virtual unsigned long __cdecl threadgroupMemoryDataSize() = 0 ;
	virtual unsigned long __cdecl textureType() = 0 ;
	virtual unsigned long __cdecl textureDataType() = 0 ;
	virtual bool __cdecl isDepthTexture() = 0 ;
	virtual unsigned long __cdecl arrayLength() = 0 ;
};

class PASCALIMPLEMENTATION TMTLArgument : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLArgumentClass,_di_MTLArgument>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLArgumentClass,_di_MTLArgument> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLArgument(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLArgumentClass,_di_MTLArgument>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLArgument() { }
	
};


typedef void * PMTLArgument;

__interface  INTERFACE_UUID("{3FD45DDD-637A-417D-849E-B4B7820FDA76}") MTLTypeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E5A1BD9D-F2DB-4500-A874-85EFDDE5F076}") MTLType  : public Iosapi::Foundation::NSObject 
{
	virtual unsigned long __cdecl dataType() = 0 ;
};

class PASCALIMPLEMENTATION TMTLType : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTypeClass,_di_MTLType>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTypeClass,_di_MTLType> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLType(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTypeClass,_di_MTLType>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLType() { }
	
};


typedef void * PMTLType;

__interface  INTERFACE_UUID("{7499FAE1-96EC-41D3-91A8-F8A5023D7FAE}") MTLStructTypeClass  : public MTLTypeClass 
{
	
};

__interface  INTERFACE_UUID("{82D158CC-947E-4355-B79A-A2E3DE92C67A}") MTLStructType  : public MTLType 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl members() = 0 ;
	virtual _di_MTLStructMember __cdecl memberByName(Iosapi::Foundation::_di_NSString name) = 0 ;
};

class PASCALIMPLEMENTATION TMTLStructType : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLStructTypeClass,_di_MTLStructType>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLStructTypeClass,_di_MTLStructType> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLStructType(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLStructTypeClass,_di_MTLStructType>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLStructType() { }
	
};


typedef void * PMTLStructType;

__interface  INTERFACE_UUID("{A40CB0C5-2698-4206-8CF4-3250E5273776}") MTLArrayTypeClass  : public MTLTypeClass 
{
	
};

__interface  INTERFACE_UUID("{19124D0B-C332-4B91-A327-516C97E7F883}") MTLArrayType  : public MTLType 
{
	virtual unsigned long __cdecl elementType() = 0 ;
	virtual unsigned long __cdecl arrayLength() = 0 ;
	virtual unsigned long __cdecl stride() = 0 ;
	virtual unsigned long __cdecl argumentIndexStride() = 0 ;
	virtual _di_MTLStructType __cdecl elementStructType() = 0 ;
	virtual _di_MTLArrayType __cdecl elementArrayType() = 0 ;
	virtual _di_MTLTextureReferenceType __cdecl elementTextureReferenceType() = 0 ;
	virtual _di_MTLPointerType __cdecl elementPointerType() = 0 ;
};

class PASCALIMPLEMENTATION TMTLArrayType : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLArrayTypeClass,_di_MTLArrayType>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLArrayTypeClass,_di_MTLArrayType> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLArrayType(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLArrayTypeClass,_di_MTLArrayType>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLArrayType() { }
	
};


typedef void * PMTLArrayType;

__interface  INTERFACE_UUID("{0D001BF2-F086-473F-9736-D88C19EE6069}") MTLTextureReferenceTypeClass  : public MTLTypeClass 
{
	
};

__interface  INTERFACE_UUID("{12ACF7BD-A5B8-4BD1-9796-8AD98E7E71C7}") MTLTextureReferenceType  : public MTLType 
{
	virtual unsigned long __cdecl textureDataType() = 0 ;
	virtual unsigned long __cdecl textureType() = 0 ;
	virtual unsigned long __cdecl access() = 0 ;
	virtual bool __cdecl isDepthTexture() = 0 ;
};

class PASCALIMPLEMENTATION TMTLTextureReferenceType : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureReferenceTypeClass,_di_MTLTextureReferenceType>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureReferenceTypeClass,_di_MTLTextureReferenceType> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLTextureReferenceType(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureReferenceTypeClass,_di_MTLTextureReferenceType>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLTextureReferenceType() { }
	
};


typedef void * PMTLTextureReferenceType;

__interface  INTERFACE_UUID("{8CCBCACE-C3D1-4CDF-BA52-0D7E57AC9FF1}") MTLPointerTypeClass  : public MTLTypeClass 
{
	
};

__interface  INTERFACE_UUID("{197CDF9A-FC7B-4572-8113-432944E41477}") MTLPointerType  : public MTLType 
{
	virtual unsigned long __cdecl elementType() = 0 ;
	virtual unsigned long __cdecl access() = 0 ;
	virtual unsigned long __cdecl alignment() = 0 ;
	virtual unsigned long __cdecl dataSize() = 0 ;
	virtual bool __cdecl elementIsArgumentBuffer() = 0 ;
	virtual _di_MTLStructType __cdecl elementStructType() = 0 ;
	virtual _di_MTLArrayType __cdecl elementArrayType() = 0 ;
};

class PASCALIMPLEMENTATION TMTLPointerType : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLPointerTypeClass,_di_MTLPointerType>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLPointerTypeClass,_di_MTLPointerType> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLPointerType(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLPointerTypeClass,_di_MTLPointerType>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLPointerType() { }
	
};


typedef void * PMTLPointerType;

__interface  INTERFACE_UUID("{260FE9F5-A55E-4A81-9B57-91162D522B9F}") MTLStructMemberClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{C1C73EA9-36D6-4D3B-892D-342A8F2C77C5}") MTLStructMember  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual unsigned long __cdecl offset() = 0 ;
	virtual unsigned long __cdecl dataType() = 0 ;
	virtual _di_MTLStructType __cdecl structType() = 0 ;
	virtual _di_MTLArrayType __cdecl arrayType() = 0 ;
	virtual _di_MTLTextureReferenceType __cdecl textureReferenceType() = 0 ;
	virtual _di_MTLPointerType __cdecl pointerType() = 0 ;
	virtual unsigned long __cdecl argumentIndex() = 0 ;
};

class PASCALIMPLEMENTATION TMTLStructMember : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLStructMemberClass,_di_MTLStructMember>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLStructMemberClass,_di_MTLStructMember> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLStructMember(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLStructMemberClass,_di_MTLStructMember>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLStructMember() { }
	
};


typedef void * PMTLStructMember;

__interface  INTERFACE_UUID("{794A8BDE-4634-41C4-9A1D-B4FBDBA563C9}") MTLCompileOptionsClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3FCEA625-354F-4485-82B7-C2672BE8CB0C}") MTLCompileOptions  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setPreprocessorMacros(Iosapi::Foundation::_di_NSDictionary preprocessorMacros) = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl preprocessorMacros() = 0 ;
	virtual void __cdecl setFastMathEnabled(bool fastMathEnabled) = 0 ;
	virtual bool __cdecl fastMathEnabled() = 0 ;
	virtual void __cdecl setLanguageVersion(unsigned long languageVersion) = 0 ;
	virtual unsigned long __cdecl languageVersion() = 0 ;
};

class PASCALIMPLEMENTATION TMTLCompileOptions : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLCompileOptionsClass,_di_MTLCompileOptions>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLCompileOptionsClass,_di_MTLCompileOptions> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLCompileOptions(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLCompileOptionsClass,_di_MTLCompileOptions>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLCompileOptions() { }
	
};


typedef void * PMTLCompileOptions;

__interface  INTERFACE_UUID("{3467F290-C092-4040-A63D-A8599892BE45}") MTLFunctionConstantValuesClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{85BA7F72-44D6-44BD-BAC0-FFE735A6E2F5}") MTLFunctionConstantValues  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setConstantValueTypeAtIndex(void * value, unsigned long type, unsigned long atIndex) = 0 ;
	virtual void __cdecl setConstantValues(void * values, unsigned long type, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setConstantValueTypeWithName(void * value, unsigned long type, Iosapi::Foundation::_di_NSString withName) = 0 ;
	virtual void __cdecl reset() = 0 ;
};

class PASCALIMPLEMENTATION TMTLFunctionConstantValues : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLFunctionConstantValuesClass,_di_MTLFunctionConstantValues>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLFunctionConstantValuesClass,_di_MTLFunctionConstantValues> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLFunctionConstantValues(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLFunctionConstantValuesClass,_di_MTLFunctionConstantValues>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLFunctionConstantValues() { }
	
};


typedef void * PMTLFunctionConstantValues;

__interface  INTERFACE_UUID("{028B0A42-68CA-459A-9331-EA9ADCA2C6B3}") MTLVertexAttributeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{A389D726-24C8-41EF-9C85-CDF74C0C07D2}") MTLVertexAttribute  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual unsigned long __cdecl attributeIndex() = 0 ;
	virtual unsigned long __cdecl attributeType() = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual bool __cdecl isPatchData() = 0 ;
	virtual bool __cdecl isPatchControlPointData() = 0 ;
};

class PASCALIMPLEMENTATION TMTLVertexAttribute : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeClass,_di_MTLVertexAttribute>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeClass,_di_MTLVertexAttribute> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLVertexAttribute(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeClass,_di_MTLVertexAttribute>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLVertexAttribute() { }
	
};


typedef void * PMTLVertexAttribute;

__interface  INTERFACE_UUID("{B78CF324-DCCC-46C5-AF06-4AB024912F7B}") MTLAttributeClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0C742290-5A77-4DB6-B557-32BE3DF4A2F7}") MTLAttribute  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual unsigned long __cdecl attributeIndex() = 0 ;
	virtual unsigned long __cdecl attributeType() = 0 ;
	virtual bool __cdecl isActive() = 0 ;
	virtual bool __cdecl isPatchData() = 0 ;
	virtual bool __cdecl isPatchControlPointData() = 0 ;
};

class PASCALIMPLEMENTATION TMTLAttribute : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeClass,_di_MTLAttribute>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeClass,_di_MTLAttribute> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLAttribute(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeClass,_di_MTLAttribute>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLAttribute() { }
	
};


typedef void * PMTLAttribute;

__interface  INTERFACE_UUID("{46F8DD00-5A8C-4D48-9C4A-B7946F3643A5}") MTLFunctionConstantClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E7E4C9B1-69D3-4877-A0E1-4CAA7E6EC70C}") MTLFunctionConstant  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual unsigned long __cdecl type() = 0 ;
	virtual unsigned long __cdecl index() = 0 ;
	virtual bool __cdecl required() = 0 ;
};

class PASCALIMPLEMENTATION TMTLFunctionConstant : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLFunctionConstantClass,_di_MTLFunctionConstant>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLFunctionConstantClass,_di_MTLFunctionConstant> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLFunctionConstant(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLFunctionConstantClass,_di_MTLFunctionConstant>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLFunctionConstant() { }
	
};


typedef void * PMTLFunctionConstant;

__interface  INTERFACE_UUID("{00BF2FE1-F704-4538-99D7-AD852276F01A}") MTLTileRenderPipelineDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{20FE634C-458D-4126-BD90-E4119BA2E9FE}") MTLTileRenderPipelineDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual void __cdecl setTileFunction(_di_MTLFunction tileFunction) = 0 ;
	virtual _di_MTLFunction __cdecl tileFunction() = 0 ;
	virtual void __cdecl setRasterSampleCount(unsigned long rasterSampleCount) = 0 ;
	virtual unsigned long __cdecl rasterSampleCount() = 0 ;
	virtual _di_MTLTileRenderPipelineColorAttachmentDescriptorArray __cdecl colorAttachments() = 0 ;
	virtual void __cdecl setThreadgroupSizeMatchesTileSize(bool threadgroupSizeMatchesTileSize) = 0 ;
	virtual bool __cdecl threadgroupSizeMatchesTileSize() = 0 ;
	virtual _di_MTLPipelineBufferDescriptorArray __cdecl tileBuffers() = 0 ;
	virtual void __cdecl setMaxTotalThreadsPerThreadgroup(unsigned long maxTotalThreadsPerThreadgroup) = 0 ;
	virtual unsigned long __cdecl maxTotalThreadsPerThreadgroup() = 0 ;
	virtual void __cdecl reset() = 0 ;
};

class PASCALIMPLEMENTATION TMTLTileRenderPipelineDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineDescriptorClass,_di_MTLTileRenderPipelineDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineDescriptorClass,_di_MTLTileRenderPipelineDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLTileRenderPipelineDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineDescriptorClass,_di_MTLTileRenderPipelineDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLTileRenderPipelineDescriptor() { }
	
};


typedef void * PMTLTileRenderPipelineDescriptor;

__interface  INTERFACE_UUID("{5310941F-E1F3-445E-A85C-E50979B96996}") MTLSamplerDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{7DED2ECB-3BAC-4177-99BA-793C67EBE96F}") MTLSamplerDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setMinFilter(unsigned long minFilter) = 0 ;
	virtual unsigned long __cdecl minFilter() = 0 ;
	virtual void __cdecl setMagFilter(unsigned long magFilter) = 0 ;
	virtual unsigned long __cdecl magFilter() = 0 ;
	virtual void __cdecl setMipFilter(unsigned long mipFilter) = 0 ;
	virtual unsigned long __cdecl mipFilter() = 0 ;
	virtual void __cdecl setMaxAnisotropy(unsigned long maxAnisotropy) = 0 ;
	virtual unsigned long __cdecl maxAnisotropy() = 0 ;
	virtual void __cdecl setSAddressMode(unsigned long sAddressMode) = 0 ;
	virtual unsigned long __cdecl sAddressMode() = 0 ;
	virtual void __cdecl setTAddressMode(unsigned long tAddressMode) = 0 ;
	virtual unsigned long __cdecl tAddressMode() = 0 ;
	virtual void __cdecl setRAddressMode(unsigned long rAddressMode) = 0 ;
	virtual unsigned long __cdecl rAddressMode() = 0 ;
	virtual void __cdecl setBorderColor(unsigned long borderColor) = 0 ;
	virtual unsigned long __cdecl borderColor() = 0 ;
	virtual void __cdecl setNormalizedCoordinates(bool normalizedCoordinates) = 0 ;
	virtual bool __cdecl normalizedCoordinates() = 0 ;
	virtual void __cdecl setLodMinClamp(float lodMinClamp) = 0 ;
	virtual float __cdecl lodMinClamp() = 0 ;
	virtual void __cdecl setLodMaxClamp(float lodMaxClamp) = 0 ;
	virtual float __cdecl lodMaxClamp() = 0 ;
	virtual void __cdecl setLodAverage(bool lodAverage) = 0 ;
	virtual bool __cdecl lodAverage() = 0 ;
	virtual void __cdecl setCompareFunction(unsigned long compareFunction) = 0 ;
	virtual unsigned long __cdecl compareFunction() = 0 ;
	virtual void __cdecl setSupportArgumentBuffers(bool supportArgumentBuffers) = 0 ;
	virtual bool __cdecl supportArgumentBuffers() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
};

class PASCALIMPLEMENTATION TMTLSamplerDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLSamplerDescriptorClass,_di_MTLSamplerDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLSamplerDescriptorClass,_di_MTLSamplerDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLSamplerDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLSamplerDescriptorClass,_di_MTLSamplerDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLSamplerDescriptor() { }
	
};


typedef void * PMTLSamplerDescriptor;

__interface  INTERFACE_UUID("{9AA354FA-0E2E-411D-B6B8-2F404A65605E}") MTLRenderPipelineColorAttachmentDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{AA55F953-CD08-45EA-8776-9173A195E8FA}") MTLRenderPipelineColorAttachmentDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setPixelFormat(unsigned long pixelFormat) = 0 ;
	virtual unsigned long __cdecl pixelFormat() = 0 ;
	virtual void __cdecl setBlendingEnabled(bool blendingEnabled) = 0 ;
	virtual bool __cdecl isBlendingEnabled() = 0 ;
	virtual void __cdecl setSourceRGBBlendFactor(unsigned long sourceRGBBlendFactor) = 0 ;
	virtual unsigned long __cdecl sourceRGBBlendFactor() = 0 ;
	virtual void __cdecl setDestinationRGBBlendFactor(unsigned long destinationRGBBlendFactor) = 0 ;
	virtual unsigned long __cdecl destinationRGBBlendFactor() = 0 ;
	virtual void __cdecl setRgbBlendOperation(unsigned long rgbBlendOperation) = 0 ;
	virtual unsigned long __cdecl rgbBlendOperation() = 0 ;
	virtual void __cdecl setSourceAlphaBlendFactor(unsigned long sourceAlphaBlendFactor) = 0 ;
	virtual unsigned long __cdecl sourceAlphaBlendFactor() = 0 ;
	virtual void __cdecl setDestinationAlphaBlendFactor(unsigned long destinationAlphaBlendFactor) = 0 ;
	virtual unsigned long __cdecl destinationAlphaBlendFactor() = 0 ;
	virtual void __cdecl setAlphaBlendOperation(unsigned long alphaBlendOperation) = 0 ;
	virtual unsigned long __cdecl alphaBlendOperation() = 0 ;
	virtual void __cdecl setWriteMask(unsigned long writeMask) = 0 ;
	virtual unsigned long __cdecl writeMask() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPipelineColorAttachmentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineColorAttachmentDescriptorClass,_di_MTLRenderPipelineColorAttachmentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineColorAttachmentDescriptorClass,_di_MTLRenderPipelineColorAttachmentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPipelineColorAttachmentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineColorAttachmentDescriptorClass,_di_MTLRenderPipelineColorAttachmentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPipelineColorAttachmentDescriptor() { }
	
};


typedef void * PMTLRenderPipelineColorAttachmentDescriptor;

__interface  INTERFACE_UUID("{B158E71C-C6B6-4782-8FB1-6A8FA665F081}") MTLDepthStencilDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E0D887A3-E13B-44F3-B1A9-F67543C8F596}") MTLDepthStencilDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setDepthCompareFunction(unsigned long depthCompareFunction) = 0 ;
	virtual unsigned long __cdecl depthCompareFunction() = 0 ;
	virtual void __cdecl setDepthWriteEnabled(bool depthWriteEnabled) = 0 ;
	virtual bool __cdecl isDepthWriteEnabled() = 0 ;
	virtual void __cdecl setFrontFaceStencil(_di_MTLStencilDescriptor frontFaceStencil) = 0 ;
	virtual _di_MTLStencilDescriptor __cdecl frontFaceStencil() = 0 ;
	virtual void __cdecl setBackFaceStencil(_di_MTLStencilDescriptor backFaceStencil) = 0 ;
	virtual _di_MTLStencilDescriptor __cdecl backFaceStencil() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
};

class PASCALIMPLEMENTATION TMTLDepthStencilDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLDepthStencilDescriptorClass,_di_MTLDepthStencilDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLDepthStencilDescriptorClass,_di_MTLDepthStencilDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLDepthStencilDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLDepthStencilDescriptorClass,_di_MTLDepthStencilDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLDepthStencilDescriptor() { }
	
};


typedef void * PMTLDepthStencilDescriptor;

__interface  INTERFACE_UUID("{2F9903CE-78B8-43B2-ABFB-74014E51E7FA}") MTLRenderPipelineDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{07059857-3A96-4B72-B8BC-081F7CCA88A3}") MTLRenderPipelineDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual void __cdecl setVertexFunction(_di_MTLFunction vertexFunction) = 0 ;
	virtual _di_MTLFunction __cdecl vertexFunction() = 0 ;
	virtual void __cdecl setFragmentFunction(_di_MTLFunction fragmentFunction) = 0 ;
	virtual _di_MTLFunction __cdecl fragmentFunction() = 0 ;
	virtual void __cdecl setVertexDescriptor(_di_MTLVertexDescriptor vertexDescriptor) = 0 ;
	virtual _di_MTLVertexDescriptor __cdecl vertexDescriptor() = 0 ;
	virtual void __cdecl setSampleCount(unsigned long sampleCount) = 0 ;
	virtual unsigned long __cdecl sampleCount() = 0 ;
	virtual void __cdecl setRasterSampleCount(unsigned long rasterSampleCount) = 0 ;
	virtual unsigned long __cdecl rasterSampleCount() = 0 ;
	virtual void __cdecl setAlphaToCoverageEnabled(bool alphaToCoverageEnabled) = 0 ;
	virtual bool __cdecl isAlphaToCoverageEnabled() = 0 ;
	virtual void __cdecl setAlphaToOneEnabled(bool alphaToOneEnabled) = 0 ;
	virtual bool __cdecl isAlphaToOneEnabled() = 0 ;
	virtual void __cdecl setRasterizationEnabled(bool rasterizationEnabled) = 0 ;
	virtual bool __cdecl isRasterizationEnabled() = 0 ;
	virtual _di_MTLRenderPipelineColorAttachmentDescriptorArray __cdecl colorAttachments() = 0 ;
	virtual void __cdecl setDepthAttachmentPixelFormat(unsigned long depthAttachmentPixelFormat) = 0 ;
	virtual unsigned long __cdecl depthAttachmentPixelFormat() = 0 ;
	virtual void __cdecl setStencilAttachmentPixelFormat(unsigned long stencilAttachmentPixelFormat) = 0 ;
	virtual unsigned long __cdecl stencilAttachmentPixelFormat() = 0 ;
	virtual void __cdecl setInputPrimitiveTopology(unsigned long inputPrimitiveTopology) = 0 ;
	virtual unsigned long __cdecl inputPrimitiveTopology() = 0 ;
	virtual void __cdecl setTessellationPartitionMode(unsigned long tessellationPartitionMode) = 0 ;
	virtual unsigned long __cdecl tessellationPartitionMode() = 0 ;
	virtual void __cdecl setMaxTessellationFactor(unsigned long maxTessellationFactor) = 0 ;
	virtual unsigned long __cdecl maxTessellationFactor() = 0 ;
	virtual void __cdecl setTessellationFactorScaleEnabled(bool tessellationFactorScaleEnabled) = 0 ;
	virtual bool __cdecl isTessellationFactorScaleEnabled() = 0 ;
	virtual void __cdecl setTessellationFactorFormat(unsigned long tessellationFactorFormat) = 0 ;
	virtual unsigned long __cdecl tessellationFactorFormat() = 0 ;
	virtual void __cdecl setTessellationControlPointIndexType(unsigned long tessellationControlPointIndexType) = 0 ;
	virtual unsigned long __cdecl tessellationControlPointIndexType() = 0 ;
	virtual void __cdecl setTessellationFactorStepFunction(unsigned long tessellationFactorStepFunction) = 0 ;
	virtual unsigned long __cdecl tessellationFactorStepFunction() = 0 ;
	virtual void __cdecl setTessellationOutputWindingOrder(unsigned long tessellationOutputWindingOrder) = 0 ;
	virtual unsigned long __cdecl tessellationOutputWindingOrder() = 0 ;
	virtual _di_MTLPipelineBufferDescriptorArray __cdecl vertexBuffers() = 0 ;
	virtual _di_MTLPipelineBufferDescriptorArray __cdecl fragmentBuffers() = 0 ;
	virtual void __cdecl setSupportIndirectCommandBuffers(bool supportIndirectCommandBuffers) = 0 ;
	virtual bool __cdecl supportIndirectCommandBuffers() = 0 ;
	virtual void __cdecl reset() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPipelineDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineDescriptorClass,_di_MTLRenderPipelineDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineDescriptorClass,_di_MTLRenderPipelineDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPipelineDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineDescriptorClass,_di_MTLRenderPipelineDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPipelineDescriptor() { }
	
};


typedef void * PMTLRenderPipelineDescriptor;

__interface  INTERFACE_UUID("{9FD99F4F-E419-4F3B-B211-254FCA348F8A}") MTLRenderPassDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MTLRenderPassDescriptor __cdecl renderPassDescriptor() = 0 ;
};

__interface  INTERFACE_UUID("{252DD6A8-244D-413A-8F3C-31FB32BB67F2}") MTLRenderPassDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLRenderPassColorAttachmentDescriptorArray __cdecl colorAttachments() = 0 ;
	virtual void __cdecl setDepthAttachment(_di_MTLRenderPassDepthAttachmentDescriptor depthAttachment) = 0 ;
	virtual _di_MTLRenderPassDepthAttachmentDescriptor __cdecl depthAttachment() = 0 ;
	virtual void __cdecl setStencilAttachment(_di_MTLRenderPassStencilAttachmentDescriptor stencilAttachment) = 0 ;
	virtual _di_MTLRenderPassStencilAttachmentDescriptor __cdecl stencilAttachment() = 0 ;
	virtual void __cdecl setVisibilityResultBuffer(_di_MTLBuffer visibilityResultBuffer) = 0 ;
	virtual _di_MTLBuffer __cdecl visibilityResultBuffer() = 0 ;
	virtual void __cdecl setRenderTargetArrayLength(unsigned long renderTargetArrayLength) = 0 ;
	virtual unsigned long __cdecl renderTargetArrayLength() = 0 ;
	virtual void __cdecl setImageblockSampleLength(unsigned long imageblockSampleLength) = 0 ;
	virtual unsigned long __cdecl imageblockSampleLength() = 0 ;
	virtual void __cdecl setThreadgroupMemoryLength(unsigned long threadgroupMemoryLength) = 0 ;
	virtual unsigned long __cdecl threadgroupMemoryLength() = 0 ;
	virtual void __cdecl setTileWidth(unsigned long tileWidth) = 0 ;
	virtual unsigned long __cdecl tileWidth() = 0 ;
	virtual void __cdecl setTileHeight(unsigned long tileHeight) = 0 ;
	virtual unsigned long __cdecl tileHeight() = 0 ;
	virtual void __cdecl setDefaultRasterSampleCount(unsigned long defaultRasterSampleCount) = 0 ;
	virtual unsigned long __cdecl defaultRasterSampleCount() = 0 ;
	virtual void __cdecl setRenderTargetWidth(unsigned long renderTargetWidth) = 0 ;
	virtual unsigned long __cdecl renderTargetWidth() = 0 ;
	virtual void __cdecl setRenderTargetHeight(unsigned long renderTargetHeight) = 0 ;
	virtual unsigned long __cdecl renderTargetHeight() = 0 ;
	virtual void __cdecl setSamplePositions(PMTLSamplePosition positions, unsigned long count) = 0 ;
	virtual unsigned long __cdecl getSamplePositions(PMTLSamplePosition positions, unsigned long count) = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPassDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassDescriptorClass,_di_MTLRenderPassDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassDescriptorClass,_di_MTLRenderPassDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPassDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassDescriptorClass,_di_MTLRenderPassDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPassDescriptor() { }
	
};


typedef void * PMTLRenderPassDescriptor;

__interface  INTERFACE_UUID("{3D0B4500-CCC1-44E6-9674-F7955D3113F5}") MTLRenderPipelineReflectionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{ADBA1021-90B3-4410-AAE5-30261781F995}") MTLRenderPipelineReflection  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl vertexArguments() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl fragmentArguments() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl tileArguments() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPipelineReflection : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineReflectionClass,_di_MTLRenderPipelineReflection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineReflectionClass,_di_MTLRenderPipelineReflection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPipelineReflection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineReflectionClass,_di_MTLRenderPipelineReflection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPipelineReflection() { }
	
};


typedef void * PMTLRenderPipelineReflection;

__interface  INTERFACE_UUID("{3664FB32-790A-47C2-8CC9-540731012A84}") MTLComputePipelineDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B9EBC808-71E3-45B4-8FF9-1AA4E4287E69}") MTLComputePipelineDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual void __cdecl setComputeFunction(_di_MTLFunction computeFunction) = 0 ;
	virtual _di_MTLFunction __cdecl computeFunction() = 0 ;
	virtual void __cdecl setThreadGroupSizeIsMultipleOfThreadExecutionWidth(bool threadGroupSizeIsMultipleOfThreadExecutionWidth) = 0 ;
	virtual bool __cdecl threadGroupSizeIsMultipleOfThreadExecutionWidth() = 0 ;
	virtual void __cdecl setMaxTotalThreadsPerThreadgroup(unsigned long maxTotalThreadsPerThreadgroup) = 0 ;
	virtual unsigned long __cdecl maxTotalThreadsPerThreadgroup() = 0 ;
	virtual void __cdecl setStageInputDescriptor(_di_MTLStageInputOutputDescriptor stageInputDescriptor) = 0 ;
	virtual _di_MTLStageInputOutputDescriptor __cdecl stageInputDescriptor() = 0 ;
	virtual _di_MTLPipelineBufferDescriptorArray __cdecl buffers() = 0 ;
	virtual void __cdecl reset() = 0 ;
};

class PASCALIMPLEMENTATION TMTLComputePipelineDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLComputePipelineDescriptorClass,_di_MTLComputePipelineDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLComputePipelineDescriptorClass,_di_MTLComputePipelineDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLComputePipelineDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLComputePipelineDescriptorClass,_di_MTLComputePipelineDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLComputePipelineDescriptor() { }
	
};


typedef void * PMTLComputePipelineDescriptor;

__interface  INTERFACE_UUID("{B8868236-A376-47B1-BDF1-9969F75EBBFA}") MTLComputePipelineReflectionClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F9F607DE-8F16-47DD-9CFE-2DC272043F7D}") MTLComputePipelineReflection  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSArray __cdecl arguments() = 0 ;
};

class PASCALIMPLEMENTATION TMTLComputePipelineReflection : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLComputePipelineReflectionClass,_di_MTLComputePipelineReflection>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLComputePipelineReflectionClass,_di_MTLComputePipelineReflection> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLComputePipelineReflection(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLComputePipelineReflectionClass,_di_MTLComputePipelineReflection>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLComputePipelineReflection() { }
	
};


typedef void * PMTLComputePipelineReflection;

__interface  INTERFACE_UUID("{3D79443D-A1A9-4F3D-B66C-B7AD60FA842F}") MTLHeapDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{8C29FD29-E9F5-4499-B0D3-21A0331FA407}") MTLHeapDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setSize(unsigned long size) = 0 ;
	virtual unsigned long __cdecl size() = 0 ;
	virtual void __cdecl setStorageMode(unsigned long storageMode) = 0 ;
	virtual unsigned long __cdecl storageMode() = 0 ;
	virtual void __cdecl setCpuCacheMode(unsigned long cpuCacheMode) = 0 ;
	virtual unsigned long __cdecl cpuCacheMode() = 0 ;
};

class PASCALIMPLEMENTATION TMTLHeapDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLHeapDescriptorClass,_di_MTLHeapDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLHeapDescriptorClass,_di_MTLHeapDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLHeapDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLHeapDescriptorClass,_di_MTLHeapDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLHeapDescriptor() { }
	
};


typedef void * PMTLHeapDescriptor;

__interface  INTERFACE_UUID("{3CDEF6D5-23D8-4DD7-A28E-9F96721EC4E5}") MTLIndirectCommandBufferDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{74A6FD5F-1654-40F0-A35C-000731973CF3}") MTLIndirectCommandBufferDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setCommandTypes(unsigned long commandTypes) = 0 ;
	virtual unsigned long __cdecl commandTypes() = 0 ;
	virtual void __cdecl setInheritPipelineState(bool inheritPipelineState) = 0 ;
	virtual bool __cdecl inheritPipelineState() = 0 ;
	virtual void __cdecl setInheritBuffers(bool inheritBuffers) = 0 ;
	virtual bool __cdecl inheritBuffers() = 0 ;
	virtual void __cdecl setMaxVertexBufferBindCount(unsigned long maxVertexBufferBindCount) = 0 ;
	virtual unsigned long __cdecl maxVertexBufferBindCount() = 0 ;
	virtual void __cdecl setMaxFragmentBufferBindCount(unsigned long maxFragmentBufferBindCount) = 0 ;
	virtual unsigned long __cdecl maxFragmentBufferBindCount() = 0 ;
};

class PASCALIMPLEMENTATION TMTLIndirectCommandBufferDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLIndirectCommandBufferDescriptorClass,_di_MTLIndirectCommandBufferDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLIndirectCommandBufferDescriptorClass,_di_MTLIndirectCommandBufferDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLIndirectCommandBufferDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLIndirectCommandBufferDescriptorClass,_di_MTLIndirectCommandBufferDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLIndirectCommandBufferDescriptor() { }
	
};


typedef void * PMTLIndirectCommandBufferDescriptor;

__interface  INTERFACE_UUID("{E6DAEF1E-8B5D-48DB-901E-5F0B3C1442DF}") MTLSharedEventHandleClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{197A608C-95C0-4266-865B-F8277A86A036}") MTLSharedEventHandle  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
};

class PASCALIMPLEMENTATION TMTLSharedEventHandle : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLSharedEventHandleClass,_di_MTLSharedEventHandle>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLSharedEventHandleClass,_di_MTLSharedEventHandle> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLSharedEventHandle(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLSharedEventHandleClass,_di_MTLSharedEventHandle>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLSharedEventHandle() { }
	
};


typedef void * PMTLSharedEventHandle;

__interface  INTERFACE_UUID("{B74B2404-15BD-483B-894D-4925AC00FB8A}") MTLArgumentDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MTLArgumentDescriptor __cdecl argumentDescriptor() = 0 ;
};

__interface  INTERFACE_UUID("{5BA99F6B-5057-45A5-B717-0540133E97B7}") MTLArgumentDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setDataType(unsigned long dataType) = 0 ;
	virtual unsigned long __cdecl dataType() = 0 ;
	virtual void __cdecl setIndex(unsigned long index) = 0 ;
	virtual unsigned long __cdecl index() = 0 ;
	virtual void __cdecl setArrayLength(unsigned long arrayLength) = 0 ;
	virtual unsigned long __cdecl arrayLength() = 0 ;
	virtual void __cdecl setAccess(unsigned long access) = 0 ;
	virtual unsigned long __cdecl access() = 0 ;
	virtual void __cdecl setTextureType(unsigned long textureType) = 0 ;
	virtual unsigned long __cdecl textureType() = 0 ;
	virtual void __cdecl setConstantBlockAlignment(unsigned long constantBlockAlignment) = 0 ;
	virtual unsigned long __cdecl constantBlockAlignment() = 0 ;
};

class PASCALIMPLEMENTATION TMTLArgumentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLArgumentDescriptorClass,_di_MTLArgumentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLArgumentDescriptorClass,_di_MTLArgumentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLArgumentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLArgumentDescriptorClass,_di_MTLArgumentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLArgumentDescriptor() { }
	
};


typedef void * PMTLArgumentDescriptor;

__interface  INTERFACE_UUID("{18256F3A-E36F-4C7E-8171-F300B0C4D45B}") MTLStencilDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F4732280-D5F0-44D8-8D43-8BB62287A04C}") MTLStencilDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setStencilCompareFunction(unsigned long stencilCompareFunction) = 0 ;
	virtual unsigned long __cdecl stencilCompareFunction() = 0 ;
	virtual void __cdecl setStencilFailureOperation(unsigned long stencilFailureOperation) = 0 ;
	virtual unsigned long __cdecl stencilFailureOperation() = 0 ;
	virtual void __cdecl setDepthFailureOperation(unsigned long depthFailureOperation) = 0 ;
	virtual unsigned long __cdecl depthFailureOperation() = 0 ;
	virtual void __cdecl setDepthStencilPassOperation(unsigned long depthStencilPassOperation) = 0 ;
	virtual unsigned long __cdecl depthStencilPassOperation() = 0 ;
	virtual void __cdecl setReadMask(unsigned long readMask) = 0 ;
	virtual unsigned long __cdecl readMask() = 0 ;
	virtual void __cdecl setWriteMask(unsigned long writeMask) = 0 ;
	virtual unsigned long __cdecl writeMask() = 0 ;
};

class PASCALIMPLEMENTATION TMTLStencilDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLStencilDescriptorClass,_di_MTLStencilDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLStencilDescriptorClass,_di_MTLStencilDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLStencilDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLStencilDescriptorClass,_di_MTLStencilDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLStencilDescriptor() { }
	
};


typedef void * PMTLStencilDescriptor;

__interface  INTERFACE_UUID("{33E4B62A-C49C-41FA-AD49-FBA534DF7159}") MTLRenderPassAttachmentDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{F0B9B352-4066-448C-AB84-DD788FC9BAF4}") MTLRenderPassAttachmentDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setTexture(_di_MTLTexture texture) = 0 ;
	virtual _di_MTLTexture __cdecl texture() = 0 ;
	virtual void __cdecl setLevel(unsigned long level) = 0 ;
	virtual unsigned long __cdecl level() = 0 ;
	virtual void __cdecl setSlice(unsigned long slice) = 0 ;
	virtual unsigned long __cdecl slice() = 0 ;
	virtual void __cdecl setDepthPlane(unsigned long depthPlane) = 0 ;
	virtual unsigned long __cdecl depthPlane() = 0 ;
	virtual void __cdecl setResolveTexture(_di_MTLTexture resolveTexture) = 0 ;
	virtual _di_MTLTexture __cdecl resolveTexture() = 0 ;
	virtual void __cdecl setResolveLevel(unsigned long resolveLevel) = 0 ;
	virtual unsigned long __cdecl resolveLevel() = 0 ;
	virtual void __cdecl setResolveSlice(unsigned long resolveSlice) = 0 ;
	virtual unsigned long __cdecl resolveSlice() = 0 ;
	virtual void __cdecl setResolveDepthPlane(unsigned long resolveDepthPlane) = 0 ;
	virtual unsigned long __cdecl resolveDepthPlane() = 0 ;
	virtual void __cdecl setLoadAction(unsigned long loadAction) = 0 ;
	virtual unsigned long __cdecl loadAction() = 0 ;
	virtual void __cdecl setStoreAction(unsigned long storeAction) = 0 ;
	virtual unsigned long __cdecl storeAction() = 0 ;
	virtual void __cdecl setStoreActionOptions(unsigned long storeActionOptions) = 0 ;
	virtual unsigned long __cdecl storeActionOptions() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPassAttachmentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassAttachmentDescriptorClass,_di_MTLRenderPassAttachmentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassAttachmentDescriptorClass,_di_MTLRenderPassAttachmentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPassAttachmentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassAttachmentDescriptorClass,_di_MTLRenderPassAttachmentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPassAttachmentDescriptor() { }
	
};


typedef void * PMTLRenderPassAttachmentDescriptor;

__interface  INTERFACE_UUID("{86D11781-62AA-4EDD-B360-1DC227FDA98F}") MTLRenderPassColorAttachmentDescriptorClass  : public MTLRenderPassAttachmentDescriptorClass 
{
	
};

__interface  INTERFACE_UUID("{52C1BB69-00F2-4D27-8DA6-00C7DCEB3680}") MTLRenderPassColorAttachmentDescriptor  : public MTLRenderPassAttachmentDescriptor 
{
	virtual void __cdecl setClearColor(MTLClearColor clearColor) = 0 ;
	virtual MTLClearColor __cdecl clearColor() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPassColorAttachmentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassColorAttachmentDescriptorClass,_di_MTLRenderPassColorAttachmentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassColorAttachmentDescriptorClass,_di_MTLRenderPassColorAttachmentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPassColorAttachmentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassColorAttachmentDescriptorClass,_di_MTLRenderPassColorAttachmentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPassColorAttachmentDescriptor() { }
	
};


typedef void * PMTLRenderPassColorAttachmentDescriptor;

__interface  INTERFACE_UUID("{F1B447AB-EF74-4393-A55B-E8B078AD9F28}") MTLRenderPassDepthAttachmentDescriptorClass  : public MTLRenderPassAttachmentDescriptorClass 
{
	
};

__interface  INTERFACE_UUID("{9D6029A1-F934-4B52-A28C-04DAEB78F428}") MTLRenderPassDepthAttachmentDescriptor  : public MTLRenderPassAttachmentDescriptor 
{
	virtual void __cdecl setClearDepth(double clearDepth) = 0 ;
	virtual double __cdecl clearDepth() = 0 ;
	virtual void __cdecl setDepthResolveFilter(unsigned long depthResolveFilter) = 0 ;
	virtual unsigned long __cdecl depthResolveFilter() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPassDepthAttachmentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassDepthAttachmentDescriptorClass,_di_MTLRenderPassDepthAttachmentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassDepthAttachmentDescriptorClass,_di_MTLRenderPassDepthAttachmentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPassDepthAttachmentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassDepthAttachmentDescriptorClass,_di_MTLRenderPassDepthAttachmentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPassDepthAttachmentDescriptor() { }
	
};


typedef void * PMTLRenderPassDepthAttachmentDescriptor;

__interface  INTERFACE_UUID("{AB7DF324-CEB8-4ACF-AAFE-544723894389}") MTLRenderPassStencilAttachmentDescriptorClass  : public MTLRenderPassAttachmentDescriptorClass 
{
	
};

__interface  INTERFACE_UUID("{2EDC01F7-62B7-4C85-AA90-2DC20E9D8506}") MTLRenderPassStencilAttachmentDescriptor  : public MTLRenderPassAttachmentDescriptor 
{
	virtual void __cdecl setClearStencil(unsigned long clearStencil) = 0 ;
	virtual unsigned long __cdecl clearStencil() = 0 ;
	virtual void __cdecl setStencilResolveFilter(unsigned long stencilResolveFilter) = 0 ;
	virtual unsigned long __cdecl stencilResolveFilter() = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPassStencilAttachmentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassStencilAttachmentDescriptorClass,_di_MTLRenderPassStencilAttachmentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassStencilAttachmentDescriptorClass,_di_MTLRenderPassStencilAttachmentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPassStencilAttachmentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassStencilAttachmentDescriptorClass,_di_MTLRenderPassStencilAttachmentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPassStencilAttachmentDescriptor() { }
	
};


typedef void * PMTLRenderPassStencilAttachmentDescriptor;

__interface  INTERFACE_UUID("{E7A039D2-4D74-4311-9508-C8DAA63E1DE3}") MTLRenderPassColorAttachmentDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{0611EEC2-9D06-436F-BA99-44B224646FEF}") MTLRenderPassColorAttachmentDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLRenderPassColorAttachmentDescriptor __cdecl objectAtIndexedSubscript(unsigned long attachmentIndex) = 0 ;
	virtual void __cdecl setObject(_di_MTLRenderPassColorAttachmentDescriptor attachment, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPassColorAttachmentDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassColorAttachmentDescriptorArrayClass,_di_MTLRenderPassColorAttachmentDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassColorAttachmentDescriptorArrayClass,_di_MTLRenderPassColorAttachmentDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPassColorAttachmentDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPassColorAttachmentDescriptorArrayClass,_di_MTLRenderPassColorAttachmentDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPassColorAttachmentDescriptorArray() { }
	
};


typedef void * PMTLRenderPassColorAttachmentDescriptorArray;

__interface  INTERFACE_UUID("{4A5B8CC7-CA94-4A54-9717-5439F45A6045}") MTLBufferLayoutDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{95DDE8E2-8099-4FAF-8903-EB5E7A4E619C}") MTLBufferLayoutDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setStride(unsigned long stride) = 0 ;
	virtual unsigned long __cdecl stride() = 0 ;
	virtual void __cdecl setStepFunction(unsigned long stepFunction) = 0 ;
	virtual unsigned long __cdecl stepFunction() = 0 ;
	virtual void __cdecl setStepRate(unsigned long stepRate) = 0 ;
	virtual unsigned long __cdecl stepRate() = 0 ;
};

class PASCALIMPLEMENTATION TMTLBufferLayoutDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLBufferLayoutDescriptorClass,_di_MTLBufferLayoutDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLBufferLayoutDescriptorClass,_di_MTLBufferLayoutDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLBufferLayoutDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLBufferLayoutDescriptorClass,_di_MTLBufferLayoutDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLBufferLayoutDescriptor() { }
	
};


typedef void * PMTLBufferLayoutDescriptor;

__interface  INTERFACE_UUID("{27F56753-8CC6-4971-AEB7-83959537248D}") MTLBufferLayoutDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{4AD6AA7E-CD94-44BC-9A09-E15C11476980}") MTLBufferLayoutDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLBufferLayoutDescriptor __cdecl objectAtIndexedSubscript(unsigned long index) = 0 ;
	virtual void __cdecl setObject(_di_MTLBufferLayoutDescriptor bufferDesc, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLBufferLayoutDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLBufferLayoutDescriptorArrayClass,_di_MTLBufferLayoutDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLBufferLayoutDescriptorArrayClass,_di_MTLBufferLayoutDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLBufferLayoutDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLBufferLayoutDescriptorArrayClass,_di_MTLBufferLayoutDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLBufferLayoutDescriptorArray() { }
	
};


typedef void * PMTLBufferLayoutDescriptorArray;

__interface  INTERFACE_UUID("{7E6137DE-10CB-42A9-83D5-C7A97E311D05}") MTLAttributeDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{90EB98E3-F320-44C0-BCAB-CE73F832373C}") MTLAttributeDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setFormat(unsigned long format) = 0 ;
	virtual unsigned long __cdecl format() = 0 ;
	virtual void __cdecl setOffset(unsigned long offset) = 0 ;
	virtual unsigned long __cdecl offset() = 0 ;
	virtual void __cdecl setBufferIndex(unsigned long bufferIndex) = 0 ;
	virtual unsigned long __cdecl bufferIndex() = 0 ;
};

class PASCALIMPLEMENTATION TMTLAttributeDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeDescriptorClass,_di_MTLAttributeDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeDescriptorClass,_di_MTLAttributeDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLAttributeDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeDescriptorClass,_di_MTLAttributeDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLAttributeDescriptor() { }
	
};


typedef void * PMTLAttributeDescriptor;

__interface  INTERFACE_UUID("{B738EA13-064B-4016-923C-022985BBFB84}") MTLAttributeDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D80EBC85-BA1D-4917-B0AB-809F59202FAD}") MTLAttributeDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLAttributeDescriptor __cdecl objectAtIndexedSubscript(unsigned long index) = 0 ;
	virtual void __cdecl setObject(_di_MTLAttributeDescriptor attributeDesc, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLAttributeDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeDescriptorArrayClass,_di_MTLAttributeDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeDescriptorArrayClass,_di_MTLAttributeDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLAttributeDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLAttributeDescriptorArrayClass,_di_MTLAttributeDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLAttributeDescriptorArray() { }
	
};


typedef void * PMTLAttributeDescriptorArray;

__interface  INTERFACE_UUID("{3C5B8E60-D888-4091-B451-EBC09A1CDA03}") MTLStageInputOutputDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MTLStageInputOutputDescriptor __cdecl stageInputOutputDescriptor() = 0 ;
};

__interface  INTERFACE_UUID("{A78D73EC-0D62-4BDC-9137-B9A668F551D4}") MTLStageInputOutputDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLBufferLayoutDescriptorArray __cdecl layouts() = 0 ;
	virtual _di_MTLAttributeDescriptorArray __cdecl attributes() = 0 ;
	virtual void __cdecl setIndexType(unsigned long indexType) = 0 ;
	virtual unsigned long __cdecl indexType() = 0 ;
	virtual void __cdecl setIndexBufferIndex(unsigned long indexBufferIndex) = 0 ;
	virtual unsigned long __cdecl indexBufferIndex() = 0 ;
	virtual void __cdecl reset() = 0 ;
};

class PASCALIMPLEMENTATION TMTLStageInputOutputDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLStageInputOutputDescriptorClass,_di_MTLStageInputOutputDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLStageInputOutputDescriptorClass,_di_MTLStageInputOutputDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLStageInputOutputDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLStageInputOutputDescriptorClass,_di_MTLStageInputOutputDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLStageInputOutputDescriptor() { }
	
};


typedef void * PMTLStageInputOutputDescriptor;

__interface  INTERFACE_UUID("{DB6D1469-34DD-4F1A-A21C-3E4600C1934A}") MTLPipelineBufferDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{3C8CEAC8-422A-42DB-977B-725B8E515A2C}") MTLPipelineBufferDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setMutability(unsigned long mutability) = 0 ;
	virtual unsigned long __cdecl mutability() = 0 ;
};

class PASCALIMPLEMENTATION TMTLPipelineBufferDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLPipelineBufferDescriptorClass,_di_MTLPipelineBufferDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLPipelineBufferDescriptorClass,_di_MTLPipelineBufferDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLPipelineBufferDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLPipelineBufferDescriptorClass,_di_MTLPipelineBufferDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLPipelineBufferDescriptor() { }
	
};


typedef void * PMTLPipelineBufferDescriptor;

__interface  INTERFACE_UUID("{7F447EB3-D369-48A2-9439-8DD671DF20D1}") MTLPipelineBufferDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{1B975261-ED33-47BE-A60A-775A4A3747A1}") MTLPipelineBufferDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLPipelineBufferDescriptor __cdecl objectAtIndexedSubscript(unsigned long bufferIndex) = 0 ;
	virtual void __cdecl setObject(_di_MTLPipelineBufferDescriptor buffer, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLPipelineBufferDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLPipelineBufferDescriptorArrayClass,_di_MTLPipelineBufferDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLPipelineBufferDescriptorArrayClass,_di_MTLPipelineBufferDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLPipelineBufferDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLPipelineBufferDescriptorArrayClass,_di_MTLPipelineBufferDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLPipelineBufferDescriptorArray() { }
	
};


typedef void * PMTLPipelineBufferDescriptorArray;

__interface  INTERFACE_UUID("{B92E5B5F-607F-496C-BDCB-53BD8DC32014}") MTLVertexDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MTLVertexDescriptor __cdecl vertexDescriptor() = 0 ;
};

__interface  INTERFACE_UUID("{451A2F29-F42E-42CC-9947-FEB887888ABF}") MTLVertexDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLVertexBufferLayoutDescriptorArray __cdecl layouts() = 0 ;
	virtual _di_MTLVertexAttributeDescriptorArray __cdecl attributes() = 0 ;
	virtual void __cdecl reset() = 0 ;
};

class PASCALIMPLEMENTATION TMTLVertexDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexDescriptorClass,_di_MTLVertexDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexDescriptorClass,_di_MTLVertexDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLVertexDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexDescriptorClass,_di_MTLVertexDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLVertexDescriptor() { }
	
};


typedef void * PMTLVertexDescriptor;

__interface  INTERFACE_UUID("{D350C8EF-C946-4E41-9CC9-1589E0B66AD9}") MTLRenderPipelineColorAttachmentDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{E7CFF0F0-DE3D-456A-B54E-B3A5D9B44D60}") MTLRenderPipelineColorAttachmentDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLRenderPipelineColorAttachmentDescriptor __cdecl objectAtIndexedSubscript(unsigned long attachmentIndex) = 0 ;
	virtual void __cdecl setObject(_di_MTLRenderPipelineColorAttachmentDescriptor attachment, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLRenderPipelineColorAttachmentDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineColorAttachmentDescriptorArrayClass,_di_MTLRenderPipelineColorAttachmentDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineColorAttachmentDescriptorArrayClass,_di_MTLRenderPipelineColorAttachmentDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLRenderPipelineColorAttachmentDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLRenderPipelineColorAttachmentDescriptorArrayClass,_di_MTLRenderPipelineColorAttachmentDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLRenderPipelineColorAttachmentDescriptorArray() { }
	
};


typedef void * PMTLRenderPipelineColorAttachmentDescriptorArray;

__interface  INTERFACE_UUID("{C4D9BC48-E9B2-4510-B0E1-F530EF4015CF}") MTLTileRenderPipelineColorAttachmentDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{45D3F6E6-E697-4CCD-955E-2B925D421FFB}") MTLTileRenderPipelineColorAttachmentDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setPixelFormat(unsigned long pixelFormat) = 0 ;
	virtual unsigned long __cdecl pixelFormat() = 0 ;
};

class PASCALIMPLEMENTATION TMTLTileRenderPipelineColorAttachmentDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineColorAttachmentDescriptorClass,_di_MTLTileRenderPipelineColorAttachmentDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineColorAttachmentDescriptorClass,_di_MTLTileRenderPipelineColorAttachmentDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLTileRenderPipelineColorAttachmentDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineColorAttachmentDescriptorClass,_di_MTLTileRenderPipelineColorAttachmentDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLTileRenderPipelineColorAttachmentDescriptor() { }
	
};


typedef void * PMTLTileRenderPipelineColorAttachmentDescriptor;

__interface  INTERFACE_UUID("{B10769A1-7923-4972-AA47-2B38AEA85C81}") MTLTileRenderPipelineColorAttachmentDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{2A7741A2-CF64-4CF0-A138-6DB3514CB559}") MTLTileRenderPipelineColorAttachmentDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLTileRenderPipelineColorAttachmentDescriptor __cdecl objectAtIndexedSubscript(unsigned long attachmentIndex) = 0 ;
	virtual void __cdecl setObject(_di_MTLTileRenderPipelineColorAttachmentDescriptor attachment, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLTileRenderPipelineColorAttachmentDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineColorAttachmentDescriptorArrayClass,_di_MTLTileRenderPipelineColorAttachmentDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineColorAttachmentDescriptorArrayClass,_di_MTLTileRenderPipelineColorAttachmentDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLTileRenderPipelineColorAttachmentDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTileRenderPipelineColorAttachmentDescriptorArrayClass,_di_MTLTileRenderPipelineColorAttachmentDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLTileRenderPipelineColorAttachmentDescriptorArray() { }
	
};


typedef void * PMTLTileRenderPipelineColorAttachmentDescriptorArray;

__interface  INTERFACE_UUID("{F24A040C-99F4-4676-A45E-E03E3AFB00E7}") MTLVertexBufferLayoutDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{93CEA6E8-9D0A-4674-A0F8-184650144AC8}") MTLVertexBufferLayoutDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setStride(unsigned long stride) = 0 ;
	virtual unsigned long __cdecl stride() = 0 ;
	virtual void __cdecl setStepFunction(unsigned long stepFunction) = 0 ;
	virtual unsigned long __cdecl stepFunction() = 0 ;
	virtual void __cdecl setStepRate(unsigned long stepRate) = 0 ;
	virtual unsigned long __cdecl stepRate() = 0 ;
};

class PASCALIMPLEMENTATION TMTLVertexBufferLayoutDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexBufferLayoutDescriptorClass,_di_MTLVertexBufferLayoutDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexBufferLayoutDescriptorClass,_di_MTLVertexBufferLayoutDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLVertexBufferLayoutDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexBufferLayoutDescriptorClass,_di_MTLVertexBufferLayoutDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLVertexBufferLayoutDescriptor() { }
	
};


typedef void * PMTLVertexBufferLayoutDescriptor;

__interface  INTERFACE_UUID("{5A9C23AE-E651-4BA0-AC7A-934093C5B2BA}") MTLVertexBufferLayoutDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{43B7FCDC-7CEB-48E3-B981-189D678B1A6D}") MTLVertexBufferLayoutDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLVertexBufferLayoutDescriptor __cdecl objectAtIndexedSubscript(unsigned long index) = 0 ;
	virtual void __cdecl setObject(_di_MTLVertexBufferLayoutDescriptor bufferDesc, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLVertexBufferLayoutDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexBufferLayoutDescriptorArrayClass,_di_MTLVertexBufferLayoutDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexBufferLayoutDescriptorArrayClass,_di_MTLVertexBufferLayoutDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLVertexBufferLayoutDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexBufferLayoutDescriptorArrayClass,_di_MTLVertexBufferLayoutDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLVertexBufferLayoutDescriptorArray() { }
	
};


typedef void * PMTLVertexBufferLayoutDescriptorArray;

__interface  INTERFACE_UUID("{434116A4-1676-4FA2-ADD1-7C9D2FF3EFF8}") MTLVertexAttributeDescriptorClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{DF91A57D-499D-47CE-A796-142243F5C9DA}") MTLVertexAttributeDescriptor  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setFormat(unsigned long format) = 0 ;
	virtual unsigned long __cdecl format() = 0 ;
	virtual void __cdecl setOffset(unsigned long offset) = 0 ;
	virtual unsigned long __cdecl offset() = 0 ;
	virtual void __cdecl setBufferIndex(unsigned long bufferIndex) = 0 ;
	virtual unsigned long __cdecl bufferIndex() = 0 ;
};

class PASCALIMPLEMENTATION TMTLVertexAttributeDescriptor : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeDescriptorClass,_di_MTLVertexAttributeDescriptor>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeDescriptorClass,_di_MTLVertexAttributeDescriptor> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLVertexAttributeDescriptor(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeDescriptorClass,_di_MTLVertexAttributeDescriptor>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLVertexAttributeDescriptor() { }
	
};


typedef void * PMTLVertexAttributeDescriptor;

__interface  INTERFACE_UUID("{6C6659D3-59B9-4F7D-AB1E-6EA8411A6BDB}") MTLVertexAttributeDescriptorArrayClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EACEC432-C463-4EC1-B115-C31E09C7CD82}") MTLVertexAttributeDescriptorArray  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLVertexAttributeDescriptor __cdecl objectAtIndexedSubscript(unsigned long index) = 0 ;
	virtual void __cdecl setObject(_di_MTLVertexAttributeDescriptor attributeDesc, unsigned long atIndexedSubscript) = 0 ;
};

class PASCALIMPLEMENTATION TMTLVertexAttributeDescriptorArray : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeDescriptorArrayClass,_di_MTLVertexAttributeDescriptorArray>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeDescriptorArrayClass,_di_MTLVertexAttributeDescriptorArray> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLVertexAttributeDescriptorArray(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLVertexAttributeDescriptorArrayClass,_di_MTLVertexAttributeDescriptorArray>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLVertexAttributeDescriptorArray() { }
	
};


typedef void * PMTLVertexAttributeDescriptorArray;

__interface  INTERFACE_UUID("{31DAC14E-AA71-47A3-994A-6301ADEE584D}") MTLCaptureManagerClass  : public Iosapi::Foundation::NSObjectClass 
{
	virtual _di_MTLCaptureManager __cdecl sharedCaptureManager() = 0 ;
};

__interface  INTERFACE_UUID("{5FD0485A-242F-420E-B478-798A81EBBFBF}") MTLCaptureManager  : public Iosapi::Foundation::NSObject 
{
	HIDESBASE virtual _di_MTLCaptureManager __cdecl init() = 0 ;
	virtual _di_MTLCaptureScope __cdecl newCaptureScopeWithDevice(_di_MTLDevice device) = 0 ;
	virtual _di_MTLCaptureScope __cdecl newCaptureScopeWithCommandQueue(_di_MTLCommandQueue commandQueue) = 0 ;
	virtual void __cdecl startCaptureWithDevice(_di_MTLDevice device) = 0 ;
	virtual void __cdecl startCaptureWithCommandQueue(_di_MTLCommandQueue commandQueue) = 0 ;
	virtual void __cdecl startCaptureWithScope(_di_MTLCaptureScope captureScope) = 0 ;
	virtual void __cdecl stopCapture() = 0 ;
	virtual void __cdecl setDefaultCaptureScope(_di_MTLCaptureScope defaultCaptureScope) = 0 ;
	virtual _di_MTLCaptureScope __cdecl defaultCaptureScope() = 0 ;
	virtual bool __cdecl isCapturing() = 0 ;
};

class PASCALIMPLEMENTATION TMTLCaptureManager : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLCaptureManagerClass,_di_MTLCaptureManager>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLCaptureManagerClass,_di_MTLCaptureManager> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLCaptureManager(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLCaptureManagerClass,_di_MTLCaptureManager>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLCaptureManager() { }
	
};


typedef void * PMTLCaptureManager;

__interface  INTERFACE_UUID("{F01F4932-B60C-420A-9E52-35F2C004DCA8}") MTLSharedEventListenerClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{B419F971-D043-4A32-BF5D-034DD54B1171}") MTLSharedEventListener  : public Iosapi::Foundation::NSObject 
{
	HIDESBASE virtual _di_MTLSharedEventListener __cdecl init() = 0 ;
	virtual _di_MTLSharedEventListener __cdecl initWithDispatchQueue(NativeInt dispatchQueue) = 0 ;
	virtual NativeInt __cdecl dispatchQueue() = 0 ;
};

class PASCALIMPLEMENTATION TMTLSharedEventListener : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLSharedEventListenerClass,_di_MTLSharedEventListener>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLSharedEventListenerClass,_di_MTLSharedEventListener> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLSharedEventListener(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLSharedEventListenerClass,_di_MTLSharedEventListener>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLSharedEventListener() { }
	
};


typedef void * PMTLSharedEventListener;

__interface  INTERFACE_UUID("{13D44692-0C22-4731-BA10-34B77942DA9E}") MTLDeviceClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{D5740836-B1B6-426C-935B-D0E614083878}") MTLDevice  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual unsigned __int64 __cdecl registryID() = 0 ;
	virtual MTLSize __cdecl maxThreadsPerThreadgroup() = 0 ;
	virtual bool __cdecl isLowPower() = 0 ;
	virtual bool __cdecl isHeadless() = 0 ;
	virtual bool __cdecl isRemovable() = 0 ;
	virtual unsigned __int64 __cdecl recommendedMaxWorkingSetSize() = 0 ;
	virtual bool __cdecl isDepth24Stencil8PixelFormatSupported() = 0 ;
	virtual unsigned long __cdecl readWriteTextureSupport() = 0 ;
	virtual unsigned long __cdecl argumentBuffersSupport() = 0 ;
	virtual bool __cdecl areRasterOrderGroupsSupported() = 0 ;
	virtual unsigned long __cdecl currentAllocatedSize() = 0 ;
	virtual _di_MTLCommandQueue __cdecl newCommandQueue() = 0 ;
	virtual _di_MTLCommandQueue __cdecl newCommandQueueWithMaxCommandBufferCount(unsigned long maxCommandBufferCount) = 0 ;
	virtual MTLSizeAndAlign __cdecl heapTextureSizeAndAlignWithDescriptor(_di_MTLTextureDescriptor desc) = 0 ;
	virtual MTLSizeAndAlign __cdecl heapBufferSizeAndAlignWithLength(unsigned long length, unsigned long options) = 0 ;
	virtual _di_MTLHeap __cdecl newHeapWithDescriptor(_di_MTLHeapDescriptor descriptor) = 0 ;
	virtual _di_MTLBuffer __cdecl newBufferWithLength(unsigned long length, unsigned long options) = 0 ;
	virtual _di_MTLBuffer __cdecl newBufferWithBytes(void * pointer, unsigned long length, unsigned long options) = 0 ;
	virtual _di_MTLBuffer __cdecl newBufferWithBytesNoCopy(void * pointer, unsigned long length, unsigned long options, TMTLDeviceNewBufferWithBytesNoCopyDeallocator deallocator) = 0 ;
	virtual _di_MTLDepthStencilState __cdecl newDepthStencilStateWithDescriptor(_di_MTLDepthStencilDescriptor descriptor) = 0 ;
	virtual _di_MTLTexture __cdecl newTextureWithDescriptor(_di_MTLTextureDescriptor descriptor) = 0 ;
	virtual _di_MTLTexture __cdecl newTextureWithDescriptorIosurfacePlane(_di_MTLTextureDescriptor descriptor, void * iosurface, unsigned long plane) = 0 ;
	virtual _di_MTLSamplerState __cdecl newSamplerStateWithDescriptor(_di_MTLSamplerDescriptor descriptor) = 0 ;
	virtual _di_MTLLibrary __cdecl newDefaultLibrary() = 0 ;
	virtual _di_MTLLibrary __cdecl newDefaultLibraryWithBundle(Iosapi::Foundation::_di_NSBundle bundle, System::PPointer error) = 0 ;
	virtual _di_MTLLibrary __cdecl newLibraryWithFile(Iosapi::Foundation::_di_NSString filepath, System::PPointer error) = 0 ;
	virtual _di_MTLLibrary __cdecl newLibraryWithURL(Iosapi::Foundation::_di_NSURL url, System::PPointer error) = 0 ;
	virtual _di_MTLLibrary __cdecl newLibraryWithData(void * data, System::PPointer error) = 0 ;
	virtual _di_MTLLibrary __cdecl newLibraryWithSourceOptionsError(Iosapi::Foundation::_di_NSString source, _di_MTLCompileOptions options, System::PPointer error) = 0 ;
	virtual void __cdecl newLibraryWithSourceOptionsCompletionHandler(Iosapi::Foundation::_di_NSString source, _di_MTLCompileOptions options, MTLNewLibraryCompletionHandler completionHandler) = 0 ;
	virtual _di_MTLRenderPipelineState __cdecl newRenderPipelineStateWithDescriptorError(_di_MTLRenderPipelineDescriptor descriptor, System::PPointer error) = 0 ;
	virtual _di_MTLRenderPipelineState __cdecl newRenderPipelineStateWithDescriptorOptionsReflectionError(_di_MTLRenderPipelineDescriptor descriptor, unsigned long options, PMTLAutoreleasedRenderPipelineReflection reflection, System::PPointer error) = 0 ;
	virtual void __cdecl newRenderPipelineStateWithDescriptorCompletionHandler(_di_MTLRenderPipelineDescriptor descriptor, MTLNewRenderPipelineStateCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl newRenderPipelineStateWithDescriptorOptionsCompletionHandler(_di_MTLRenderPipelineDescriptor descriptor, unsigned long options, MTLNewRenderPipelineStateWithReflectionCompletionHandler completionHandler) = 0 ;
	virtual _di_MTLComputePipelineState __cdecl newComputePipelineStateWithFunctionError(_di_MTLFunction computeFunction, System::PPointer error) = 0 ;
	virtual _di_MTLComputePipelineState __cdecl newComputePipelineStateWithFunctionOptionsReflectionError(_di_MTLFunction computeFunction, unsigned long options, PMTLAutoreleasedComputePipelineReflection reflection, System::PPointer error) = 0 ;
	virtual void __cdecl newComputePipelineStateWithFunctionCompletionHandler(_di_MTLFunction computeFunction, MTLNewComputePipelineStateCompletionHandler completionHandler) = 0 ;
	virtual void __cdecl newComputePipelineStateWithFunctionOptionsCompletionHandler(_di_MTLFunction computeFunction, unsigned long options, MTLNewComputePipelineStateWithReflectionCompletionHandler completionHandler) = 0 ;
	virtual _di_MTLComputePipelineState __cdecl newComputePipelineStateWithDescriptorOptionsReflectionError(_di_MTLComputePipelineDescriptor descriptor, unsigned long options, PMTLAutoreleasedComputePipelineReflection reflection, System::PPointer error) = 0 ;
	virtual void __cdecl newComputePipelineStateWithDescriptorOptionsCompletionHandler(_di_MTLComputePipelineDescriptor descriptor, unsigned long options, MTLNewComputePipelineStateWithReflectionCompletionHandler completionHandler) = 0 ;
	virtual _di_MTLFence __cdecl newFence() = 0 ;
	virtual bool __cdecl supportsFeatureSet(unsigned long featureSet) = 0 ;
	virtual bool __cdecl supportsTextureSampleCount(unsigned long sampleCount) = 0 ;
	virtual unsigned long __cdecl minimumLinearTextureAlignmentForPixelFormat(unsigned long format) = 0 ;
	virtual unsigned long __cdecl minimumTextureBufferAlignmentForPixelFormat(unsigned long format) = 0 ;
	virtual _di_MTLRenderPipelineState __cdecl newRenderPipelineStateWithTileDescriptorOptionsReflectionError(_di_MTLTileRenderPipelineDescriptor descriptor, unsigned long options, PMTLAutoreleasedRenderPipelineReflection reflection, System::PPointer error) = 0 ;
	virtual void __cdecl newRenderPipelineStateWithTileDescriptorOptionsCompletionHandler(_di_MTLTileRenderPipelineDescriptor descriptor, unsigned long options, MTLNewRenderPipelineStateWithReflectionCompletionHandler completionHandler) = 0 ;
	virtual unsigned long __cdecl maxThreadgroupMemoryLength() = 0 ;
	virtual unsigned long __cdecl maxArgumentBufferSamplerCount() = 0 ;
	virtual bool __cdecl areProgrammableSamplePositionsSupported() = 0 ;
	virtual void __cdecl getDefaultSamplePositions(PMTLSamplePosition positions, unsigned long count) = 0 ;
	virtual _di_MTLArgumentEncoder __cdecl newArgumentEncoderWithArguments(Iosapi::Foundation::_di_NSArray arguments) = 0 ;
	virtual _di_MTLIndirectCommandBuffer __cdecl newIndirectCommandBufferWithDescriptor(_di_MTLIndirectCommandBufferDescriptor descriptor, unsigned long maxCommandCount, unsigned long options) = 0 ;
	virtual _di_MTLEvent __cdecl newEvent() = 0 ;
	virtual _di_MTLSharedEvent __cdecl newSharedEvent() = 0 ;
	virtual _di_MTLSharedEvent __cdecl newSharedEventWithHandle(_di_MTLSharedEventHandle sharedEventHandle) = 0 ;
	virtual unsigned long __cdecl maxBufferLength() = 0 ;
};

class PASCALIMPLEMENTATION TMTLDevice : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLDeviceClass,_di_MTLDevice>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLDeviceClass,_di_MTLDevice> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLDevice(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLDeviceClass,_di_MTLDevice>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLDevice() { }
	
};


typedef void * PMTLDevice;

__interface  INTERFACE_UUID("{6FC08DBA-1CC1-44D2-BCD0-429314107B98}") MTLCommandEncoder  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual void __cdecl endEncoding() = 0 ;
	virtual void __cdecl insertDebugSignpost(Iosapi::Foundation::_di_NSString string) = 0 ;
	virtual void __cdecl pushDebugGroup(Iosapi::Foundation::_di_NSString string) = 0 ;
	virtual void __cdecl popDebugGroup() = 0 ;
};

__interface  INTERFACE_UUID("{6B62994A-7182-47DC-8F99-AE1C6D82769C}") MTLHeap  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual unsigned long __cdecl storageMode() = 0 ;
	virtual unsigned long __cdecl cpuCacheMode() = 0 ;
	virtual unsigned long __cdecl size() = 0 ;
	virtual unsigned long __cdecl usedSize() = 0 ;
	virtual unsigned long __cdecl currentAllocatedSize() = 0 ;
	virtual unsigned long __cdecl maxAvailableSizeWithAlignment(unsigned long alignment) = 0 ;
	virtual _di_MTLBuffer __cdecl newBufferWithLength(unsigned long length, unsigned long options) = 0 ;
	virtual _di_MTLTexture __cdecl newTextureWithDescriptor(_di_MTLTextureDescriptor desc) = 0 ;
	virtual unsigned long __cdecl setPurgeableState(unsigned long state) = 0 ;
};

__interface  INTERFACE_UUID("{52FD0811-9354-4285-855F-C764403D9704}") MTLResource  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual unsigned long __cdecl cpuCacheMode() = 0 ;
	virtual unsigned long __cdecl storageMode() = 0 ;
	virtual unsigned long __cdecl setPurgeableState(unsigned long state) = 0 ;
	virtual _di_MTLHeap __cdecl heap() = 0 ;
	virtual unsigned long __cdecl allocatedSize() = 0 ;
	virtual void __cdecl makeAliasable() = 0 ;
	virtual bool __cdecl isAliasable() = 0 ;
};

__interface  INTERFACE_UUID("{53787C08-9CA3-4595-BE99-6BC14C4FB440}") MTLTextureClass  : public Iosapi::Foundation::NSObjectClass 
{
	
};

__interface  INTERFACE_UUID("{EE934D5D-96DD-4B80-9CC7-4B0D2CF0B969}") MTLTexture  : public MTLResource 
{
	virtual _di_MTLResource __cdecl rootResource() = 0 ;
	virtual _di_MTLTexture __cdecl parentTexture() = 0 ;
	virtual unsigned long __cdecl parentRelativeLevel() = 0 ;
	virtual unsigned long __cdecl parentRelativeSlice() = 0 ;
	virtual _di_MTLBuffer __cdecl buffer() = 0 ;
	virtual unsigned long __cdecl bufferOffset() = 0 ;
	virtual unsigned long __cdecl bufferBytesPerRow() = 0 ;
	virtual void * __cdecl iosurface() = 0 ;
	virtual unsigned long __cdecl iosurfacePlane() = 0 ;
	virtual unsigned long __cdecl textureType() = 0 ;
	virtual unsigned long __cdecl pixelFormat() = 0 ;
	virtual unsigned long __cdecl width() = 0 ;
	virtual unsigned long __cdecl height() = 0 ;
	virtual unsigned long __cdecl depth() = 0 ;
	virtual unsigned long __cdecl mipmapLevelCount() = 0 ;
	virtual unsigned long __cdecl sampleCount() = 0 ;
	virtual unsigned long __cdecl arrayLength() = 0 ;
	virtual unsigned long __cdecl usage() = 0 ;
	virtual bool __cdecl isFramebufferOnly() = 0 ;
	virtual bool __cdecl allowGPUOptimizedContents() = 0 ;
	virtual void __cdecl getBytesBytesPerRowBytesPerImageFromRegionMipmapLevelSlice(void * pixelBytes, unsigned long bytesPerRow, unsigned long bytesPerImage, MTLRegion fromRegion, unsigned long mipmapLevel, unsigned long slice) = 0 ;
	virtual void __cdecl replaceRegionMipmapLevelSliceWithBytesBytesPerRowBytesPerImage(MTLRegion region, unsigned long mipmapLevel, unsigned long slice, void * withBytes, unsigned long bytesPerRow, unsigned long bytesPerImage) = 0 ;
	virtual void __cdecl getBytesBytesPerRowFromRegionMipmapLevel(void * pixelBytes, unsigned long bytesPerRow, MTLRegion fromRegion, unsigned long mipmapLevel) = 0 ;
	virtual void __cdecl replaceRegionMipmapLevelWithBytesBytesPerRow(MTLRegion region, unsigned long mipmapLevel, void * withBytes, unsigned long bytesPerRow) = 0 ;
	virtual _di_MTLTexture __cdecl newTextureViewWithPixelFormat(unsigned long pixelFormat) = 0 ;
	virtual _di_MTLTexture __cdecl newTextureViewWithPixelFormatTextureTypeLevelsSlices(unsigned long pixelFormat, unsigned long textureType, Iosapi::Foundation::NSRange levels, Iosapi::Foundation::NSRange slices) = 0 ;
};

class PASCALIMPLEMENTATION TMTLTexture : public Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureClass,_di_MTLTexture>
{
	typedef Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureClass,_di_MTLTexture> inherited;
	
public:
	/* TOCImport.Create */ inline __fastcall TMTLTexture(void * ID, void * ClsID, Macapi::Objectivec::TOCVTable* VTable) : Macapi::Objectivec::TOCGenericImport__2<_di_MTLTextureClass,_di_MTLTexture>(ID, ClsID, VTable) { }
	/* TOCImport.Destroy */ inline __fastcall virtual ~TMTLTexture() { }
	
};


typedef void * PMTLTexture;

__interface  INTERFACE_UUID("{B7DF13D0-4BFC-4383-9675-86792216DACD}") MTLBuffer  : public MTLResource 
{
	virtual unsigned long __cdecl length() = 0 ;
	virtual void * __cdecl contents() = 0 ;
	virtual void __cdecl didModifyRange(Iosapi::Foundation::NSRange range) = 0 ;
	virtual _di_MTLTexture __cdecl newTextureWithDescriptor(_di_MTLTextureDescriptor descriptor, unsigned long offset, unsigned long bytesPerRow) = 0 ;
	virtual void __cdecl addDebugMarker(Iosapi::Foundation::_di_NSString marker, Iosapi::Foundation::NSRange range) = 0 ;
	virtual void __cdecl removeAllDebugMarkers() = 0 ;
};

__interface  INTERFACE_UUID("{515A016D-22F1-4CAF-B8C4-0410C0113741}") MTLFunction  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual unsigned long __cdecl functionType() = 0 ;
	virtual unsigned long __cdecl patchType() = 0 ;
	virtual long __cdecl patchControlPointCount() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl vertexAttributes() = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl stageInputAttributes() = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl name() = 0 ;
	virtual Iosapi::Foundation::_di_NSDictionary __cdecl functionConstantsDictionary() = 0 ;
	virtual _di_MTLArgumentEncoder __cdecl newArgumentEncoderWithBufferIndex(unsigned long bufferIndex) = 0 ;
	virtual _di_MTLArgumentEncoder __cdecl newArgumentEncoderWithBufferIndexReflection(unsigned long bufferIndex, PMTLAutoreleasedArgument reflection) = 0 ;
};

__interface  INTERFACE_UUID("{4298B0BA-D300-43B0-9BCF-A45675B536EA}") MTLLibrary  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual _di_MTLFunction __cdecl newFunctionWithName(Iosapi::Foundation::_di_NSString functionName) = 0 ;
	virtual _di_MTLFunction __cdecl newFunctionWithNameConstantValuesError(Iosapi::Foundation::_di_NSString name, _di_MTLFunctionConstantValues constantValues, System::PPointer error) = 0 ;
	virtual void __cdecl newFunctionWithNameConstantValuesCompletionHandler(Iosapi::Foundation::_di_NSString name, _di_MTLFunctionConstantValues constantValues, TMTLLibraryNewFunctionWithNameConstantValuesCompletionHandler completionHandler) = 0 ;
	virtual Iosapi::Foundation::_di_NSArray __cdecl functionNames() = 0 ;
};

__interface  INTERFACE_UUID("{9BA6ED55-53E0-4D44-8CF8-4EF551A26722}") MTLArgumentEncoder  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual unsigned long __cdecl encodedLength() = 0 ;
	virtual unsigned long __cdecl alignment() = 0 ;
	virtual void __cdecl setArgumentBufferOffset(_di_MTLBuffer argumentBuffer, unsigned long offset) = 0 ;
	virtual void __cdecl setArgumentBufferStartOffsetArrayElement(_di_MTLBuffer argumentBuffer, unsigned long startOffset, unsigned long arrayElement) = 0 ;
	virtual void __cdecl setBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setBuffers(void * buffers, unsigned long offsets, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setTexture(_di_MTLTexture texture, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTextures(void * textures, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setSamplerState(_di_MTLSamplerState sampler, unsigned long atIndex) = 0 ;
	virtual void __cdecl setSamplerStates(void * samplers, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void * __cdecl constantDataAtIndex(unsigned long index) = 0 ;
	virtual void __cdecl setRenderPipelineState(_di_MTLRenderPipelineState pipeline, unsigned long atIndex) = 0 ;
	virtual void __cdecl setRenderPipelineStates(void * pipelines, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setIndirectCommandBuffer(_di_MTLIndirectCommandBuffer indirectCommandBuffer, unsigned long atIndex) = 0 ;
	virtual void __cdecl setIndirectCommandBuffers(void * buffers, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual _di_MTLArgumentEncoder __cdecl newArgumentEncoderForBufferAtIndex(unsigned long index) = 0 ;
};

__interface  INTERFACE_UUID("{A0E91871-C819-44B7-957A-B5E6050C9C51}") MTLCommandQueue  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual _di_MTLCommandBuffer __cdecl commandBuffer() = 0 ;
	virtual _di_MTLCommandBuffer __cdecl commandBufferWithUnretainedReferences() = 0 ;
	virtual void __cdecl insertDebugCaptureBoundary() = 0 ;
};

__interface  INTERFACE_UUID("{1C90F0F6-153A-4FC8-B3AA-6051232B3500}") MTLDepthStencilState  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
};

__interface  INTERFACE_UUID("{FBA5E937-E7CC-4041-9695-51C25E8FA426}") MTLSamplerState  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
};

__interface  INTERFACE_UUID("{6CF8C67F-5E88-423F-87F3-788FE7EFAE1D}") MTLRenderPipelineState  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual unsigned long __cdecl maxTotalThreadsPerThreadgroup() = 0 ;
	virtual bool __cdecl threadgroupSizeMatchesTileSize() = 0 ;
	virtual unsigned long __cdecl imageblockSampleLength() = 0 ;
	virtual unsigned long __cdecl imageblockMemoryLengthForDimensions(MTLSize imageblockDimensions) = 0 ;
	virtual bool __cdecl supportIndirectCommandBuffers() = 0 ;
};

__interface  INTERFACE_UUID("{5F67B318-EBA2-4BE7-8D08-79554B59CF86}") MTLComputePipelineState  : public Iosapi::Foundation::NSObject 
{
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual unsigned long __cdecl maxTotalThreadsPerThreadgroup() = 0 ;
	virtual unsigned long __cdecl threadExecutionWidth() = 0 ;
	virtual unsigned long __cdecl staticThreadgroupMemoryLength() = 0 ;
	virtual unsigned long __cdecl imageblockMemoryLengthForDimensions(MTLSize imageblockDimensions) = 0 ;
};

__interface  INTERFACE_UUID("{DCF0FC28-16D9-414D-A52B-E224AE23A6EF}") MTLFence  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
};

__interface  INTERFACE_UUID("{E213AEC0-C361-4601-AC9F-988B78FF1ECF}") MTLIndirectRenderCommandEncoder  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{251ED9FA-B28A-4065-B8B5-4C973AD1E57F}") MTLIndirectComputeCommandEncoder  : public Macapi::Objectivec::IObjectiveC 
{
	
};

__interface  INTERFACE_UUID("{FEE36D3A-5346-4E7A-B636-6331E039809F}") MTLIndirectCommandBuffer  : public MTLResource 
{
	virtual unsigned long __cdecl size() = 0 ;
	virtual void __cdecl resetWithRange(Iosapi::Foundation::NSRange range) = 0 ;
	virtual _di_MTLIndirectRenderCommand __cdecl indirectRenderCommandAtIndex(unsigned long commandIndex) = 0 ;
};

__interface  INTERFACE_UUID("{D617B463-8008-4B4E-9182-59AB88E165E9}") MTLEvent  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
};

__interface  INTERFACE_UUID("{1DA7324B-A022-4AFA-9883-3F60762EF435}") MTLSharedEvent  : public MTLEvent 
{
	virtual void __cdecl notifyListener(_di_MTLSharedEventListener listener, unsigned __int64 atValue, MTLSharedEventNotificationBlock block) = 0 ;
	virtual _di_MTLSharedEventHandle __cdecl newSharedEventHandle() = 0 ;
	virtual void __cdecl setSignaledValue(unsigned __int64 signaledValue) = 0 ;
	virtual unsigned __int64 __cdecl signaledValue() = 0 ;
};

__interface  INTERFACE_UUID("{506FC0AB-7046-4A94-BC71-FEF166E10296}") MTLBlitCommandEncoder  : public MTLCommandEncoder 
{
	virtual void __cdecl synchronizeResource(_di_MTLResource resource) = 0 ;
	virtual void __cdecl synchronizeTexture(_di_MTLTexture texture, unsigned long slice, unsigned long level) = 0 ;
	virtual void __cdecl copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin(void * sourceTexture, unsigned long sourceSlice, unsigned long sourceLevel, MTLOrigin sourceOrigin, MTLSize sourceSize, void * toTexture, unsigned long destinationSlice, unsigned long destinationLevel, MTLOrigin destinationOrigin) = 0 ;
	virtual void __cdecl copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOrigin(void * sourceBuffer, unsigned long sourceOffset, unsigned long sourceBytesPerRow, unsigned long sourceBytesPerImage, MTLSize sourceSize, void * toTexture, unsigned long destinationSlice, unsigned long destinationLevel, MTLOrigin destinationOrigin) = 0 ;
	virtual void __cdecl copyFromBufferSourceOffsetSourceBytesPerRowSourceBytesPerImageSourceSizeToTextureDestinationSliceDestinationLevelDestinationOriginOptions(void * sourceBuffer, unsigned long sourceOffset, unsigned long sourceBytesPerRow, unsigned long sourceBytesPerImage, MTLSize sourceSize, void * toTexture, unsigned long destinationSlice, unsigned long destinationLevel, MTLOrigin destinationOrigin, unsigned long options) = 0 ;
	virtual void __cdecl copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImage(void * sourceTexture, unsigned long sourceSlice, unsigned long sourceLevel, MTLOrigin sourceOrigin, MTLSize sourceSize, void * toBuffer, unsigned long destinationOffset, unsigned long destinationBytesPerRow, unsigned long destinationBytesPerImage) = 0 ;
	virtual void __cdecl copyFromTextureSourceSliceSourceLevelSourceOriginSourceSizeToBufferDestinationOffsetDestinationBytesPerRowDestinationBytesPerImageOptions(void * sourceTexture, unsigned long sourceSlice, unsigned long sourceLevel, MTLOrigin sourceOrigin, MTLSize sourceSize, void * toBuffer, unsigned long destinationOffset, unsigned long destinationBytesPerRow, unsigned long destinationBytesPerImage, unsigned long options) = 0 ;
	virtual void __cdecl generateMipmapsForTexture(_di_MTLTexture texture) = 0 ;
	virtual void __cdecl fillBuffer(_di_MTLBuffer buffer, Iosapi::Foundation::NSRange range, System::Byte value) = 0 ;
	virtual void __cdecl copyFromBufferSourceOffsetToBufferDestinationOffsetSize(void * sourceBuffer, unsigned long sourceOffset, void * toBuffer, unsigned long destinationOffset, unsigned long size) = 0 ;
	virtual void __cdecl updateFence(_di_MTLFence fence) = 0 ;
	virtual void __cdecl waitForFence(_di_MTLFence fence) = 0 ;
	virtual void __cdecl optimizeContentsForGPUAccess(_di_MTLTexture texture) = 0 ;
	virtual void __cdecl optimizeContentsForGPUAccessSliceLevel(_di_MTLTexture texture, unsigned long slice, unsigned long level) = 0 ;
	virtual void __cdecl optimizeContentsForCPUAccess(_di_MTLTexture texture) = 0 ;
	virtual void __cdecl optimizeContentsForCPUAccessSliceLevel(_di_MTLTexture texture, unsigned long slice, unsigned long level) = 0 ;
	virtual void __cdecl resetCommandsInBuffer(_di_MTLIndirectCommandBuffer buffer, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl copyIndirectCommandBuffer(_di_MTLIndirectCommandBuffer source, Iosapi::Foundation::NSRange sourceRange, _di_MTLIndirectCommandBuffer destination, unsigned long destinationIndex) = 0 ;
	virtual void __cdecl optimizeIndirectCommandBuffer(_di_MTLIndirectCommandBuffer indirectCommandBuffer, Iosapi::Foundation::NSRange withRange) = 0 ;
};

__interface  INTERFACE_UUID("{AC616C94-803C-4BC3-8FBA-55C24184078C}") MTLRenderCommandEncoder  : public MTLCommandEncoder 
{
	virtual void __cdecl setRenderPipelineState(_di_MTLRenderPipelineState pipelineState) = 0 ;
	virtual void __cdecl setVertexBytes(void * bytes, unsigned long length, unsigned long atIndex) = 0 ;
	virtual void __cdecl setVertexBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setVertexBufferOffset(unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setVertexBuffers(void * buffers, unsigned long offsets, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setVertexTexture(_di_MTLTexture texture, unsigned long atIndex) = 0 ;
	virtual void __cdecl setVertexTextures(void * textures, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setVertexSamplerStateAtIndex(_di_MTLSamplerState sampler, unsigned long atIndex) = 0 ;
	virtual void __cdecl setVertexSamplerStatesWithRange(void * samplers, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setVertexSamplerStateLodMinClampLodMaxClampAtIndex(_di_MTLSamplerState sampler, float lodMinClamp, float lodMaxClamp, unsigned long atIndex) = 0 ;
	virtual void __cdecl setVertexSamplerStatesLodMinClampsLodMaxClampsWithRange(void * samplers, float lodMinClamps, float lodMaxClamps, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setViewport(MTLViewport viewport) = 0 ;
	virtual void __cdecl setViewports(void * viewports, unsigned long count) = 0 ;
	virtual void __cdecl setFrontFacingWinding(unsigned long frontFacingWinding) = 0 ;
	virtual void __cdecl setCullMode(unsigned long cullMode) = 0 ;
	virtual void __cdecl setDepthClipMode(unsigned long depthClipMode) = 0 ;
	virtual void __cdecl setDepthBias(float depthBias, float slopeScale, float clamp) = 0 ;
	virtual void __cdecl setScissorRect(MTLScissorRect rect) = 0 ;
	virtual void __cdecl setScissorRects(MTLScissorRect scissorRects, unsigned long count) = 0 ;
	virtual void __cdecl setTriangleFillMode(unsigned long fillMode) = 0 ;
	virtual void __cdecl setFragmentBytes(void * bytes, unsigned long length, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentBufferOffset(unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentBuffers(void * buffers, unsigned long offsets, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setFragmentTexture(_di_MTLTexture texture, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentTextures(void * textures, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setFragmentSamplerStateAtIndex(_di_MTLSamplerState sampler, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentSamplerStatesWithRange(void * samplers, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setFragmentSamplerStateLodMinClampLodMaxClampAtIndex(_di_MTLSamplerState sampler, float lodMinClamp, float lodMaxClamp, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentSamplerStatesLodMinClampsLodMaxClampsWithRange(void * samplers, float lodMinClamps, float lodMaxClamps, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setBlendColorRed(float red, float green, float blue, float alpha) = 0 ;
	virtual void __cdecl setDepthStencilState(_di_MTLDepthStencilState depthStencilState) = 0 ;
	virtual void __cdecl setStencilReferenceValue(unsigned long referenceValue) = 0 ;
	virtual void __cdecl setStencilFrontReferenceValue(unsigned long frontReferenceValue, unsigned long backReferenceValue) = 0 ;
	virtual void __cdecl setVisibilityResultMode(unsigned long mode, unsigned long offset) = 0 ;
	virtual void __cdecl setColorStoreAction(unsigned long storeAction, unsigned long atIndex) = 0 ;
	virtual void __cdecl setDepthStoreAction(unsigned long storeAction) = 0 ;
	virtual void __cdecl setStencilStoreAction(unsigned long storeAction) = 0 ;
	virtual void __cdecl setColorStoreActionOptions(unsigned long storeActionOptions, unsigned long atIndex) = 0 ;
	virtual void __cdecl setDepthStoreActionOptions(unsigned long storeActionOptions) = 0 ;
	virtual void __cdecl setStencilStoreActionOptions(unsigned long storeActionOptions) = 0 ;
	virtual void __cdecl drawPrimitivesVertexStartVertexCountInstanceCount(unsigned long primitiveType, unsigned long vertexStart, unsigned long vertexCount, unsigned long instanceCount) = 0 ;
	virtual void __cdecl drawPrimitivesVertexStartVertexCount(unsigned long primitiveType, unsigned long vertexStart, unsigned long vertexCount) = 0 ;
	virtual void __cdecl drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffsetInstanceCount(unsigned long primitiveType, unsigned long indexCount, unsigned long indexType, _di_MTLBuffer indexBuffer, unsigned long indexBufferOffset, unsigned long instanceCount) = 0 ;
	virtual void __cdecl drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffset(unsigned long primitiveType, unsigned long indexCount, unsigned long indexType, _di_MTLBuffer indexBuffer, unsigned long indexBufferOffset) = 0 ;
	virtual void __cdecl drawPrimitivesVertexStartVertexCountInstanceCountBaseInstance(unsigned long primitiveType, unsigned long vertexStart, unsigned long vertexCount, unsigned long instanceCount, unsigned long baseInstance) = 0 ;
	virtual void __cdecl drawIndexedPrimitivesIndexCountIndexTypeIndexBufferIndexBufferOffsetInstanceCountBaseVertexBaseInstance(unsigned long primitiveType, unsigned long indexCount, unsigned long indexType, _di_MTLBuffer indexBuffer, unsigned long indexBufferOffset, unsigned long instanceCount, long baseVertex, unsigned long baseInstance) = 0 ;
	virtual void __cdecl drawPrimitivesIndirectBufferIndirectBufferOffset(unsigned long primitiveType, _di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset) = 0 ;
	virtual void __cdecl drawIndexedPrimitivesIndexTypeIndexBufferIndexBufferOffsetIndirectBufferIndirectBufferOffset(unsigned long primitiveType, unsigned long indexType, _di_MTLBuffer indexBuffer, unsigned long indexBufferOffset, _di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset) = 0 ;
	virtual void __cdecl textureBarrier() = 0 ;
	virtual void __cdecl updateFence(_di_MTLFence fence, unsigned long afterStages) = 0 ;
	virtual void __cdecl waitForFence(_di_MTLFence fence, unsigned long beforeStages) = 0 ;
	virtual void __cdecl setTessellationFactorBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long instanceStride) = 0 ;
	virtual void __cdecl setTessellationFactorScale(float scale) = 0 ;
	virtual void __cdecl drawPatchesPatchStartPatchCountPatchIndexBufferPatchIndexBufferOffsetInstanceCountBaseInstance(unsigned long numberOfPatchControlPoints, unsigned long patchStart, unsigned long patchCount, _di_MTLBuffer patchIndexBuffer, unsigned long patchIndexBufferOffset, unsigned long instanceCount, unsigned long baseInstance) = 0 ;
	virtual void __cdecl drawPatchesPatchIndexBufferPatchIndexBufferOffsetIndirectBufferIndirectBufferOffset(unsigned long numberOfPatchControlPoints, _di_MTLBuffer patchIndexBuffer, unsigned long patchIndexBufferOffset, _di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset) = 0 ;
	virtual void __cdecl drawIndexedPatchesPatchStartPatchCountPatchIndexBufferPatchIndexBufferOffsetControlPointIndexBufferControlPointIndexBufferOffsetInstanceCountBaseInstance(unsigned long numberOfPatchControlPoints, unsigned long patchStart, unsigned long patchCount, _di_MTLBuffer patchIndexBuffer, unsigned long patchIndexBufferOffset, _di_MTLBuffer controlPointIndexBuffer, unsigned long controlPointIndexBufferOffset, unsigned long instanceCount, unsigned long baseInstance) = 0 ;
	virtual void __cdecl drawIndexedPatchesPatchIndexBufferPatchIndexBufferOffsetControlPointIndexBufferControlPointIndexBufferOffsetIndirectBufferIndirectBufferOffset(unsigned long numberOfPatchControlPoints, _di_MTLBuffer patchIndexBuffer, unsigned long patchIndexBufferOffset, _di_MTLBuffer controlPointIndexBuffer, unsigned long controlPointIndexBufferOffset, _di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset) = 0 ;
	virtual unsigned long __cdecl tileWidth() = 0 ;
	virtual unsigned long __cdecl tileHeight() = 0 ;
	virtual void __cdecl setTileBytes(void * bytes, unsigned long length, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTileBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTileBufferOffset(unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTileBuffers(void * buffers, unsigned long offsets, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setTileTexture(_di_MTLTexture texture, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTileTextures(void * textures, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setTileSamplerStateAtIndex(_di_MTLSamplerState sampler, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTileSamplerStatesWithRange(void * samplers, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setTileSamplerStateLodMinClampLodMaxClampAtIndex(_di_MTLSamplerState sampler, float lodMinClamp, float lodMaxClamp, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTileSamplerStatesLodMinClampsLodMaxClampsWithRange(void * samplers, float lodMinClamps, float lodMaxClamps, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl dispatchThreadsPerTile(MTLSize threadsPerTile) = 0 ;
	virtual void __cdecl setThreadgroupMemoryLength(unsigned long length, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl useResource(_di_MTLResource resource, unsigned long usage) = 0 ;
	virtual void __cdecl useResources(void * resources, unsigned long count, unsigned long usage) = 0 ;
	virtual void __cdecl useHeap(_di_MTLHeap heap) = 0 ;
	virtual void __cdecl useHeaps(void * heaps, unsigned long count) = 0 ;
	virtual void __cdecl executeCommandsInBufferWithRange(_di_MTLIndirectCommandBuffer indirectCommandBuffer, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl executeCommandsInBufferIndirectBufferIndirectBufferOffset(_di_MTLIndirectCommandBuffer indirectCommandbuffer, _di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset) = 0 ;
	virtual void __cdecl memoryBarrierWithScope(unsigned long scope, unsigned long afterStages, unsigned long beforeStages) = 0 ;
	virtual void __cdecl memoryBarrierWithResources(void * resources, unsigned long count, unsigned long afterStages, unsigned long beforeStages) = 0 ;
};

__interface  INTERFACE_UUID("{932F58F4-6B5D-4CA8-B304-4B58DF7BB91E}") MTLParallelRenderCommandEncoder  : public MTLCommandEncoder 
{
	virtual _di_MTLRenderCommandEncoder __cdecl renderCommandEncoder() = 0 ;
	virtual void __cdecl setColorStoreAction(unsigned long storeAction, unsigned long atIndex) = 0 ;
	virtual void __cdecl setDepthStoreAction(unsigned long storeAction) = 0 ;
	virtual void __cdecl setStencilStoreAction(unsigned long storeAction) = 0 ;
	virtual void __cdecl setColorStoreActionOptions(unsigned long storeActionOptions, unsigned long atIndex) = 0 ;
	virtual void __cdecl setDepthStoreActionOptions(unsigned long storeActionOptions) = 0 ;
	virtual void __cdecl setStencilStoreActionOptions(unsigned long storeActionOptions) = 0 ;
};

__interface  INTERFACE_UUID("{604FD071-CD8A-4EE0-9685-EED4E4D38596}") MTLComputeCommandEncoder  : public MTLCommandEncoder 
{
	virtual unsigned long __cdecl dispatchType() = 0 ;
	virtual void __cdecl setComputePipelineState(_di_MTLComputePipelineState state) = 0 ;
	virtual void __cdecl setBytes(void * bytes, unsigned long length, unsigned long atIndex) = 0 ;
	virtual void __cdecl setBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setBufferOffset(unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setBuffers(void * buffers, unsigned long offsets, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setTexture(_di_MTLTexture texture, unsigned long atIndex) = 0 ;
	virtual void __cdecl setTextures(void * textures, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setSamplerStateAtIndex(_di_MTLSamplerState sampler, unsigned long atIndex) = 0 ;
	virtual void __cdecl setSamplerStatesWithRange(void * samplers, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setSamplerStateLodMinClampLodMaxClampAtIndex(_di_MTLSamplerState sampler, float lodMinClamp, float lodMaxClamp, unsigned long atIndex) = 0 ;
	virtual void __cdecl setSamplerStatesLodMinClampsLodMaxClampsWithRange(void * samplers, float lodMinClamps, float lodMaxClamps, Iosapi::Foundation::NSRange withRange) = 0 ;
	virtual void __cdecl setThreadgroupMemoryLength(unsigned long length, unsigned long atIndex) = 0 ;
	virtual void __cdecl setImageblockWidth(unsigned long width, unsigned long height) = 0 ;
	virtual void __cdecl setStageInRegion(MTLRegion region) = 0 ;
	virtual void __cdecl setStageInRegionWithIndirectBuffer(_di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset) = 0 ;
	virtual void __cdecl dispatchThreadgroups(MTLSize threadgroupsPerGrid, MTLSize threadsPerThreadgroup) = 0 ;
	virtual void __cdecl dispatchThreadgroupsWithIndirectBuffer(_di_MTLBuffer indirectBuffer, unsigned long indirectBufferOffset, MTLSize threadsPerThreadgroup) = 0 ;
	virtual void __cdecl dispatchThreads(MTLSize threadsPerGrid, MTLSize threadsPerThreadgroup) = 0 ;
	virtual void __cdecl updateFence(_di_MTLFence fence) = 0 ;
	virtual void __cdecl waitForFence(_di_MTLFence fence) = 0 ;
	virtual void __cdecl useResource(_di_MTLResource resource, unsigned long usage) = 0 ;
	virtual void __cdecl useResources(void * resources, unsigned long count, unsigned long usage) = 0 ;
	virtual void __cdecl useHeap(_di_MTLHeap heap) = 0 ;
	virtual void __cdecl useHeaps(void * heaps, unsigned long count) = 0 ;
	virtual void __cdecl memoryBarrierWithScope(unsigned long scope) = 0 ;
	virtual void __cdecl memoryBarrierWithResources(void * resources, unsigned long count) = 0 ;
};

__interface  INTERFACE_UUID("{7B979164-8DE0-4B2A-B9D1-EFD006E35D3B}") MTLDrawable  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl present() = 0 ;
	virtual void __cdecl presentAtTime(double presentationTime) = 0 ;
	virtual void __cdecl presentAfterMinimumDuration(double duration) = 0 ;
	virtual void __cdecl addPresentedHandler(MTLDrawablePresentedHandler block) = 0 ;
	virtual double __cdecl presentedTime() = 0 ;
	virtual unsigned long __cdecl drawableID() = 0 ;
};

__interface  INTERFACE_UUID("{FDA9D69B-A21A-49B5-8EF2-93443D6A6EC2}") MTLCommandBuffer  : public Iosapi::Foundation::NSObject 
{
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual _di_MTLCommandQueue __cdecl commandQueue() = 0 ;
	virtual bool __cdecl retainedReferences() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual double __cdecl kernelStartTime() = 0 ;
	virtual double __cdecl kernelEndTime() = 0 ;
	virtual double __cdecl GPUStartTime() = 0 ;
	virtual double __cdecl GPUEndTime() = 0 ;
	virtual void __cdecl enqueue() = 0 ;
	virtual void __cdecl commit() = 0 ;
	virtual void __cdecl addScheduledHandler(MTLCommandBufferHandler block) = 0 ;
	virtual void __cdecl presentDrawable(_di_MTLDrawable drawable) = 0 ;
	virtual void __cdecl presentDrawableAtTime(_di_MTLDrawable drawable, double atTime) = 0 ;
	virtual void __cdecl presentDrawableAfterMinimumDuration(_di_MTLDrawable drawable, double afterMinimumDuration) = 0 ;
	virtual void __cdecl waitUntilScheduled() = 0 ;
	virtual void __cdecl addCompletedHandler(MTLCommandBufferHandler block) = 0 ;
	virtual void __cdecl waitUntilCompleted() = 0 ;
	virtual unsigned long __cdecl status() = 0 ;
	virtual Iosapi::Foundation::_di_NSError __cdecl error() = 0 ;
	virtual _di_MTLBlitCommandEncoder __cdecl blitCommandEncoder() = 0 ;
	virtual _di_MTLRenderCommandEncoder __cdecl renderCommandEncoderWithDescriptor(_di_MTLRenderPassDescriptor renderPassDescriptor) = 0 ;
	virtual _di_MTLComputeCommandEncoder __cdecl computeCommandEncoder() = 0 ;
	virtual _di_MTLComputeCommandEncoder __cdecl computeCommandEncoderWithDispatchType(unsigned long dispatchType) = 0 ;
	virtual void __cdecl encodeWaitForEvent(_di_MTLEvent event, unsigned __int64 value) = 0 ;
	virtual void __cdecl encodeSignalEvent(_di_MTLEvent event, unsigned __int64 value) = 0 ;
	virtual _di_MTLParallelRenderCommandEncoder __cdecl parallelRenderCommandEncoderWithDescriptor(_di_MTLRenderPassDescriptor renderPassDescriptor) = 0 ;
	virtual void __cdecl pushDebugGroup(Iosapi::Foundation::_di_NSString string) = 0 ;
	virtual void __cdecl popDebugGroup() = 0 ;
};

__interface  INTERFACE_UUID("{3C068601-3E58-4321-BF92-06B7FC5F0258}") MTLCaptureScope  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl beginScope() = 0 ;
	virtual void __cdecl endScope() = 0 ;
	virtual void __cdecl setLabel(Iosapi::Foundation::_di_NSString label) = 0 ;
	virtual Iosapi::Foundation::_di_NSString __cdecl label() = 0 ;
	virtual _di_MTLDevice __cdecl device() = 0 ;
	virtual _di_MTLCommandQueue __cdecl commandQueue() = 0 ;
};

__interface  INTERFACE_UUID("{0A78AADD-AA14-4BB5-B1F4-11E483CBB082}") MTLIndirectRenderCommand  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl setRenderPipelineState(_di_MTLRenderPipelineState pipelineState) = 0 ;
	virtual void __cdecl setVertexBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl setFragmentBuffer(_di_MTLBuffer buffer, unsigned long offset, unsigned long atIndex) = 0 ;
	virtual void __cdecl drawPatches(unsigned long numberOfPatchControlPoints, unsigned long patchStart, unsigned long patchCount, _di_MTLBuffer patchIndexBuffer, unsigned long patchIndexBufferOffset, unsigned long instanceCount, unsigned long baseInstance, _di_MTLBuffer tessellationFactorBuffer, unsigned long tessellationFactorBufferOffset, unsigned long tessellationFactorBufferInstanceStride) = 0 ;
	virtual void __cdecl drawIndexedPatches(unsigned long numberOfPatchControlPoints, unsigned long patchStart, unsigned long patchCount, _di_MTLBuffer patchIndexBuffer, unsigned long patchIndexBufferOffset, _di_MTLBuffer controlPointIndexBuffer, unsigned long controlPointIndexBufferOffset, unsigned long instanceCount, unsigned long baseInstance, _di_MTLBuffer tessellationFactorBuffer, unsigned long tessellationFactorBufferOffset, unsigned long tessellationFactorBufferInstanceStride) = 0 ;
	virtual void __cdecl drawPrimitives(unsigned long primitiveType, unsigned long vertexStart, unsigned long vertexCount, unsigned long instanceCount, unsigned long baseInstance) = 0 ;
	virtual void __cdecl drawIndexedPrimitives(unsigned long primitiveType, unsigned long indexCount, unsigned long indexType, _di_MTLBuffer indexBuffer, unsigned long indexBufferOffset, unsigned long instanceCount, long baseVertex, unsigned long baseInstance) = 0 ;
	virtual void __cdecl reset() = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 MTLResourceUsageRead = System::Int8(0x1);
static constexpr System::Int8 MTLResourceUsageWrite = System::Int8(0x2);
static constexpr System::Int8 MTLResourceUsageSample = System::Int8(0x4);
static constexpr System::Int8 MTLBarrierScopeBuffers = System::Int8(0x1);
static constexpr System::Int8 MTLBarrierScopeTextures = System::Int8(0x2);
static constexpr System::Int8 MTLBarrierScopeRenderTargets = System::Int8(0x4);
static constexpr System::Int8 MTLPixelFormatInvalid = System::Int8(0x0);
static constexpr System::Int8 MTLPixelFormatA8Unorm = System::Int8(0x1);
static constexpr System::Int8 MTLPixelFormatR8Unorm = System::Int8(0xa);
static constexpr System::Int8 MTLPixelFormatR8Unorm_sRGB = System::Int8(0xb);
static constexpr System::Int8 MTLPixelFormatR8Snorm = System::Int8(0xc);
static constexpr System::Int8 MTLPixelFormatR8Uint = System::Int8(0xd);
static constexpr System::Int8 MTLPixelFormatR8Sint = System::Int8(0xe);
static constexpr System::Int8 MTLPixelFormatR16Unorm = System::Int8(0x14);
static constexpr System::Int8 MTLPixelFormatR16Snorm = System::Int8(0x16);
static constexpr System::Int8 MTLPixelFormatR16Uint = System::Int8(0x17);
static constexpr System::Int8 MTLPixelFormatR16Sint = System::Int8(0x18);
static constexpr System::Int8 MTLPixelFormatR16Float = System::Int8(0x19);
static constexpr System::Int8 MTLPixelFormatRG8Unorm = System::Int8(0x1e);
static constexpr System::Int8 MTLPixelFormatRG8Unorm_sRGB = System::Int8(0x1f);
static constexpr System::Int8 MTLPixelFormatRG8Snorm = System::Int8(0x20);
static constexpr System::Int8 MTLPixelFormatRG8Uint = System::Int8(0x21);
static constexpr System::Int8 MTLPixelFormatRG8Sint = System::Int8(0x22);
static constexpr System::Int8 MTLPixelFormatB5G6R5Unorm = System::Int8(0x28);
static constexpr System::Int8 MTLPixelFormatA1BGR5Unorm = System::Int8(0x29);
static constexpr System::Int8 MTLPixelFormatABGR4Unorm = System::Int8(0x2a);
static constexpr System::Int8 MTLPixelFormatBGR5A1Unorm = System::Int8(0x2b);
static constexpr System::Int8 MTLPixelFormatR32Uint = System::Int8(0x35);
static constexpr System::Int8 MTLPixelFormatR32Sint = System::Int8(0x36);
static constexpr System::Int8 MTLPixelFormatR32Float = System::Int8(0x37);
static constexpr System::Int8 MTLPixelFormatRG16Unorm = System::Int8(0x3c);
static constexpr System::Int8 MTLPixelFormatRG16Snorm = System::Int8(0x3e);
static constexpr System::Int8 MTLPixelFormatRG16Uint = System::Int8(0x3f);
static constexpr System::Int8 MTLPixelFormatRG16Sint = System::Int8(0x40);
static constexpr System::Int8 MTLPixelFormatRG16Float = System::Int8(0x41);
static constexpr System::Int8 MTLPixelFormatRGBA8Unorm = System::Int8(0x46);
static constexpr System::Int8 MTLPixelFormatRGBA8Unorm_sRGB = System::Int8(0x47);
static constexpr System::Int8 MTLPixelFormatRGBA8Snorm = System::Int8(0x48);
static constexpr System::Int8 MTLPixelFormatRGBA8Uint = System::Int8(0x49);
static constexpr System::Int8 MTLPixelFormatRGBA8Sint = System::Int8(0x4a);
static constexpr System::Int8 MTLPixelFormatBGRA8Unorm = System::Int8(0x50);
static constexpr System::Int8 MTLPixelFormatBGRA8Unorm_sRGB = System::Int8(0x51);
static constexpr System::Int8 MTLPixelFormatRGB10A2Unorm = System::Int8(0x5a);
static constexpr System::Int8 MTLPixelFormatRGB10A2Uint = System::Int8(0x5b);
static constexpr System::Int8 MTLPixelFormatRG11B10Float = System::Int8(0x5c);
static constexpr System::Int8 MTLPixelFormatRGB9E5Float = System::Int8(0x5d);
static constexpr System::Int8 MTLPixelFormatBGR10A2Unorm = System::Int8(0x5e);
static constexpr System::Word MTLPixelFormatBGR10_XR = System::Word(0x22a);
static constexpr System::Word MTLPixelFormatBGR10_XR_sRGB = System::Word(0x22b);
static constexpr System::Int8 MTLPixelFormatRG32Uint = System::Int8(0x67);
static constexpr System::Int8 MTLPixelFormatRG32Sint = System::Int8(0x68);
static constexpr System::Int8 MTLPixelFormatRG32Float = System::Int8(0x69);
static constexpr System::Int8 MTLPixelFormatRGBA16Unorm = System::Int8(0x6e);
static constexpr System::Int8 MTLPixelFormatRGBA16Snorm = System::Int8(0x70);
static constexpr System::Int8 MTLPixelFormatRGBA16Uint = System::Int8(0x71);
static constexpr System::Int8 MTLPixelFormatRGBA16Sint = System::Int8(0x72);
static constexpr System::Int8 MTLPixelFormatRGBA16Float = System::Int8(0x73);
static constexpr System::Word MTLPixelFormatBGRA10_XR = System::Word(0x228);
static constexpr System::Word MTLPixelFormatBGRA10_XR_sRGB = System::Word(0x229);
static constexpr System::Int8 MTLPixelFormatRGBA32Uint = System::Int8(0x7b);
static constexpr System::Int8 MTLPixelFormatRGBA32Sint = System::Int8(0x7c);
static constexpr System::Int8 MTLPixelFormatRGBA32Float = System::Int8(0x7d);
static constexpr System::Byte MTLPixelFormatBC1_RGBA = System::Byte(0x82);
static constexpr System::Byte MTLPixelFormatBC1_RGBA_sRGB = System::Byte(0x83);
static constexpr System::Byte MTLPixelFormatBC2_RGBA = System::Byte(0x84);
static constexpr System::Byte MTLPixelFormatBC2_RGBA_sRGB = System::Byte(0x85);
static constexpr System::Byte MTLPixelFormatBC3_RGBA = System::Byte(0x86);
static constexpr System::Byte MTLPixelFormatBC3_RGBA_sRGB = System::Byte(0x87);
static constexpr System::Byte MTLPixelFormatBC4_RUnorm = System::Byte(0x8c);
static constexpr System::Byte MTLPixelFormatBC4_RSnorm = System::Byte(0x8d);
static constexpr System::Byte MTLPixelFormatBC5_RGUnorm = System::Byte(0x8e);
static constexpr System::Byte MTLPixelFormatBC5_RGSnorm = System::Byte(0x8f);
static constexpr System::Byte MTLPixelFormatBC6H_RGBFloat = System::Byte(0x96);
static constexpr System::Byte MTLPixelFormatBC6H_RGBUfloat = System::Byte(0x97);
static constexpr System::Byte MTLPixelFormatBC7_RGBAUnorm = System::Byte(0x98);
static constexpr System::Byte MTLPixelFormatBC7_RGBAUnorm_sRGB = System::Byte(0x99);
static constexpr System::Byte MTLPixelFormatPVRTC_RGB_2BPP = System::Byte(0xa0);
static constexpr System::Byte MTLPixelFormatPVRTC_RGB_2BPP_sRGB = System::Byte(0xa1);
static constexpr System::Byte MTLPixelFormatPVRTC_RGB_4BPP = System::Byte(0xa2);
static constexpr System::Byte MTLPixelFormatPVRTC_RGB_4BPP_sRGB = System::Byte(0xa3);
static constexpr System::Byte MTLPixelFormatPVRTC_RGBA_2BPP = System::Byte(0xa4);
static constexpr System::Byte MTLPixelFormatPVRTC_RGBA_2BPP_sRGB = System::Byte(0xa5);
static constexpr System::Byte MTLPixelFormatPVRTC_RGBA_4BPP = System::Byte(0xa6);
static constexpr System::Byte MTLPixelFormatPVRTC_RGBA_4BPP_sRGB = System::Byte(0xa7);
static constexpr System::Byte MTLPixelFormatEAC_R11Unorm = System::Byte(0xaa);
static constexpr System::Byte MTLPixelFormatEAC_R11Snorm = System::Byte(0xac);
static constexpr System::Byte MTLPixelFormatEAC_RG11Unorm = System::Byte(0xae);
static constexpr System::Byte MTLPixelFormatEAC_RG11Snorm = System::Byte(0xb0);
static constexpr System::Byte MTLPixelFormatEAC_RGBA8 = System::Byte(0xb2);
static constexpr System::Byte MTLPixelFormatEAC_RGBA8_sRGB = System::Byte(0xb3);
static constexpr System::Byte MTLPixelFormatETC2_RGB8 = System::Byte(0xb4);
static constexpr System::Byte MTLPixelFormatETC2_RGB8_sRGB = System::Byte(0xb5);
static constexpr System::Byte MTLPixelFormatETC2_RGB8A1 = System::Byte(0xb6);
static constexpr System::Byte MTLPixelFormatETC2_RGB8A1_sRGB = System::Byte(0xb7);
static constexpr System::Byte MTLPixelFormatASTC_4x4_sRGB = System::Byte(0xba);
static constexpr System::Byte MTLPixelFormatASTC_5x4_sRGB = System::Byte(0xbb);
static constexpr System::Byte MTLPixelFormatASTC_5x5_sRGB = System::Byte(0xbc);
static constexpr System::Byte MTLPixelFormatASTC_6x5_sRGB = System::Byte(0xbd);
static constexpr System::Byte MTLPixelFormatASTC_6x6_sRGB = System::Byte(0xbe);
static constexpr System::Byte MTLPixelFormatASTC_8x5_sRGB = System::Byte(0xc0);
static constexpr System::Byte MTLPixelFormatASTC_8x6_sRGB = System::Byte(0xc1);
static constexpr System::Byte MTLPixelFormatASTC_8x8_sRGB = System::Byte(0xc2);
static constexpr System::Byte MTLPixelFormatASTC_10x5_sRGB = System::Byte(0xc3);
static constexpr System::Byte MTLPixelFormatASTC_10x6_sRGB = System::Byte(0xc4);
static constexpr System::Byte MTLPixelFormatASTC_10x8_sRGB = System::Byte(0xc5);
static constexpr System::Byte MTLPixelFormatASTC_10x10_sRGB = System::Byte(0xc6);
static constexpr System::Byte MTLPixelFormatASTC_12x10_sRGB = System::Byte(0xc7);
static constexpr System::Byte MTLPixelFormatASTC_12x12_sRGB = System::Byte(0xc8);
static constexpr System::Byte MTLPixelFormatASTC_4x4_LDR = System::Byte(0xcc);
static constexpr System::Byte MTLPixelFormatASTC_5x4_LDR = System::Byte(0xcd);
static constexpr System::Byte MTLPixelFormatASTC_5x5_LDR = System::Byte(0xce);
static constexpr System::Byte MTLPixelFormatASTC_6x5_LDR = System::Byte(0xcf);
static constexpr System::Byte MTLPixelFormatASTC_6x6_LDR = System::Byte(0xd0);
static constexpr System::Byte MTLPixelFormatASTC_8x5_LDR = System::Byte(0xd2);
static constexpr System::Byte MTLPixelFormatASTC_8x6_LDR = System::Byte(0xd3);
static constexpr System::Byte MTLPixelFormatASTC_8x8_LDR = System::Byte(0xd4);
static constexpr System::Byte MTLPixelFormatASTC_10x5_LDR = System::Byte(0xd5);
static constexpr System::Byte MTLPixelFormatASTC_10x6_LDR = System::Byte(0xd6);
static constexpr System::Byte MTLPixelFormatASTC_10x8_LDR = System::Byte(0xd7);
static constexpr System::Byte MTLPixelFormatASTC_10x10_LDR = System::Byte(0xd8);
static constexpr System::Byte MTLPixelFormatASTC_12x10_LDR = System::Byte(0xd9);
static constexpr System::Byte MTLPixelFormatASTC_12x12_LDR = System::Byte(0xda);
static constexpr System::Byte MTLPixelFormatGBGR422 = System::Byte(0xf0);
static constexpr System::Byte MTLPixelFormatBGRG422 = System::Byte(0xf1);
static constexpr System::Byte MTLPixelFormatDepth16Unorm = System::Byte(0xfa);
static constexpr System::Byte MTLPixelFormatDepth32Float = System::Byte(0xfc);
static constexpr System::Byte MTLPixelFormatStencil8 = System::Byte(0xfd);
static constexpr System::Byte MTLPixelFormatDepth24Unorm_Stencil8 = System::Byte(0xff);
static constexpr System::Word MTLPixelFormatDepth32Float_Stencil8 = System::Word(0x104);
static constexpr System::Word MTLPixelFormatX32_Stencil8 = System::Word(0x105);
static constexpr System::Word MTLPixelFormatX24_Stencil8 = System::Word(0x106);
static constexpr System::Int8 MTLPurgeableStateKeepCurrent = System::Int8(0x1);
static constexpr System::Int8 MTLPurgeableStateNonVolatile = System::Int8(0x2);
static constexpr System::Int8 MTLPurgeableStateVolatile = System::Int8(0x3);
static constexpr System::Int8 MTLPurgeableStateEmpty = System::Int8(0x4);
static constexpr System::Int8 MTLCPUCacheModeDefaultCache = System::Int8(0x0);
static constexpr System::Int8 MTLCPUCacheModeWriteCombined = System::Int8(0x1);
static constexpr System::Int8 MTLStorageModeShared = System::Int8(0x0);
static constexpr System::Int8 MTLStorageModeManaged = System::Int8(0x1);
static constexpr System::Int8 MTLStorageModePrivate = System::Int8(0x2);
static constexpr System::Int8 MTLStorageModeMemoryless = System::Int8(0x3);
static constexpr System::Int8 MTLResourceCPUCacheModeDefaultCache = System::Int8(0x0);
static constexpr System::Int8 MTLResourceCPUCacheModeWriteCombined = System::Int8(0x1);
static constexpr System::Int8 MTLResourceStorageModeShared = System::Int8(0x0);
static constexpr System::Int8 MTLResourceStorageModeManaged = System::Int8(0x10);
static constexpr System::Int8 MTLResourceStorageModePrivate = System::Int8(0x20);
static constexpr System::Int8 MTLResourceStorageModeMemoryless = System::Int8(0x30);
static constexpr System::Word MTLResourceHazardTrackingModeUntracked = System::Word(0x100);
static constexpr System::Int8 MTLResourceOptionCPUCacheModeDefault = System::Int8(0x0);
static constexpr System::Int8 MTLResourceOptionCPUCacheModeWriteCombined = System::Int8(0x1);
static constexpr System::Int8 MTLTextureType1D = System::Int8(0x0);
static constexpr System::Int8 MTLTextureType1DArray = System::Int8(0x1);
static constexpr System::Int8 MTLTextureType2D = System::Int8(0x2);
static constexpr System::Int8 MTLTextureType2DArray = System::Int8(0x3);
static constexpr System::Int8 MTLTextureType2DMultisample = System::Int8(0x4);
static constexpr System::Int8 MTLTextureTypeCube = System::Int8(0x5);
static constexpr System::Int8 MTLTextureTypeCubeArray = System::Int8(0x6);
static constexpr System::Int8 MTLTextureType3D = System::Int8(0x7);
static constexpr System::Int8 MTLTextureType2DMultisampleArray = System::Int8(0x8);
static constexpr System::Int8 MTLTextureTypeTextureBuffer = System::Int8(0x9);
static constexpr System::Int8 MTLTextureUsageUnknown = System::Int8(0x0);
static constexpr System::Int8 MTLTextureUsageShaderRead = System::Int8(0x1);
static constexpr System::Int8 MTLTextureUsageShaderWrite = System::Int8(0x2);
static constexpr System::Int8 MTLTextureUsageRenderTarget = System::Int8(0x4);
static constexpr System::Int8 MTLTextureUsagePixelFormatView = System::Int8(0x10);
static constexpr System::Int8 MTLDataTypeNone = System::Int8(0x0);
static constexpr System::Int8 MTLDataTypeStruct = System::Int8(0x1);
static constexpr System::Int8 MTLDataTypeArray = System::Int8(0x2);
static constexpr System::Int8 MTLDataTypeFloat = System::Int8(0x3);
static constexpr System::Int8 MTLDataTypeFloat2 = System::Int8(0x4);
static constexpr System::Int8 MTLDataTypeFloat3 = System::Int8(0x5);
static constexpr System::Int8 MTLDataTypeFloat4 = System::Int8(0x6);
static constexpr System::Int8 MTLDataTypeFloat2x2 = System::Int8(0x7);
static constexpr System::Int8 MTLDataTypeFloat2x3 = System::Int8(0x8);
static constexpr System::Int8 MTLDataTypeFloat2x4 = System::Int8(0x9);
static constexpr System::Int8 MTLDataTypeFloat3x2 = System::Int8(0xa);
static constexpr System::Int8 MTLDataTypeFloat3x3 = System::Int8(0xb);
static constexpr System::Int8 MTLDataTypeFloat3x4 = System::Int8(0xc);
static constexpr System::Int8 MTLDataTypeFloat4x2 = System::Int8(0xd);
static constexpr System::Int8 MTLDataTypeFloat4x3 = System::Int8(0xe);
static constexpr System::Int8 MTLDataTypeFloat4x4 = System::Int8(0xf);
static constexpr System::Int8 MTLDataTypeHalf = System::Int8(0x10);
static constexpr System::Int8 MTLDataTypeHalf2 = System::Int8(0x11);
static constexpr System::Int8 MTLDataTypeHalf3 = System::Int8(0x12);
static constexpr System::Int8 MTLDataTypeHalf4 = System::Int8(0x13);
static constexpr System::Int8 MTLDataTypeHalf2x2 = System::Int8(0x14);
static constexpr System::Int8 MTLDataTypeHalf2x3 = System::Int8(0x15);
static constexpr System::Int8 MTLDataTypeHalf2x4 = System::Int8(0x16);
static constexpr System::Int8 MTLDataTypeHalf3x2 = System::Int8(0x17);
static constexpr System::Int8 MTLDataTypeHalf3x3 = System::Int8(0x18);
static constexpr System::Int8 MTLDataTypeHalf3x4 = System::Int8(0x19);
static constexpr System::Int8 MTLDataTypeHalf4x2 = System::Int8(0x1a);
static constexpr System::Int8 MTLDataTypeHalf4x3 = System::Int8(0x1b);
static constexpr System::Int8 MTLDataTypeHalf4x4 = System::Int8(0x1c);
static constexpr System::Int8 MTLDataTypeInt = System::Int8(0x1d);
static constexpr System::Int8 MTLDataTypeInt2 = System::Int8(0x1e);
static constexpr System::Int8 MTLDataTypeInt3 = System::Int8(0x1f);
static constexpr System::Int8 MTLDataTypeInt4 = System::Int8(0x20);
static constexpr System::Int8 MTLDataTypeUInt = System::Int8(0x21);
static constexpr System::Int8 MTLDataTypeUInt2 = System::Int8(0x22);
static constexpr System::Int8 MTLDataTypeUInt3 = System::Int8(0x23);
static constexpr System::Int8 MTLDataTypeUInt4 = System::Int8(0x24);
static constexpr System::Int8 MTLDataTypeShort = System::Int8(0x25);
static constexpr System::Int8 MTLDataTypeShort2 = System::Int8(0x26);
static constexpr System::Int8 MTLDataTypeShort3 = System::Int8(0x27);
static constexpr System::Int8 MTLDataTypeShort4 = System::Int8(0x28);
static constexpr System::Int8 MTLDataTypeUShort = System::Int8(0x29);
static constexpr System::Int8 MTLDataTypeUShort2 = System::Int8(0x2a);
static constexpr System::Int8 MTLDataTypeUShort3 = System::Int8(0x2b);
static constexpr System::Int8 MTLDataTypeUShort4 = System::Int8(0x2c);
static constexpr System::Int8 MTLDataTypeChar = System::Int8(0x2d);
static constexpr System::Int8 MTLDataTypeChar2 = System::Int8(0x2e);
static constexpr System::Int8 MTLDataTypeChar3 = System::Int8(0x2f);
static constexpr System::Int8 MTLDataTypeChar4 = System::Int8(0x30);
static constexpr System::Int8 MTLDataTypeUChar = System::Int8(0x31);
static constexpr System::Int8 MTLDataTypeUChar2 = System::Int8(0x32);
static constexpr System::Int8 MTLDataTypeUChar3 = System::Int8(0x33);
static constexpr System::Int8 MTLDataTypeUChar4 = System::Int8(0x34);
static constexpr System::Int8 MTLDataTypeBool = System::Int8(0x35);
static constexpr System::Int8 MTLDataTypeBool2 = System::Int8(0x36);
static constexpr System::Int8 MTLDataTypeBool3 = System::Int8(0x37);
static constexpr System::Int8 MTLDataTypeBool4 = System::Int8(0x38);
static constexpr System::Int8 MTLDataTypeTexture = System::Int8(0x3a);
static constexpr System::Int8 MTLDataTypeSampler = System::Int8(0x3b);
static constexpr System::Int8 MTLDataTypePointer = System::Int8(0x3c);
static constexpr System::Int8 MTLDataTypeR8Unorm = System::Int8(0x3e);
static constexpr System::Int8 MTLDataTypeR8Snorm = System::Int8(0x3f);
static constexpr System::Int8 MTLDataTypeR16Unorm = System::Int8(0x40);
static constexpr System::Int8 MTLDataTypeR16Snorm = System::Int8(0x41);
static constexpr System::Int8 MTLDataTypeRG8Unorm = System::Int8(0x42);
static constexpr System::Int8 MTLDataTypeRG8Snorm = System::Int8(0x43);
static constexpr System::Int8 MTLDataTypeRG16Unorm = System::Int8(0x44);
static constexpr System::Int8 MTLDataTypeRG16Snorm = System::Int8(0x45);
static constexpr System::Int8 MTLDataTypeRGBA8Unorm = System::Int8(0x46);
static constexpr System::Int8 MTLDataTypeRGBA8Unorm_sRGB = System::Int8(0x47);
static constexpr System::Int8 MTLDataTypeRGBA8Snorm = System::Int8(0x48);
static constexpr System::Int8 MTLDataTypeRGBA16Unorm = System::Int8(0x49);
static constexpr System::Int8 MTLDataTypeRGBA16Snorm = System::Int8(0x4a);
static constexpr System::Int8 MTLDataTypeRGB10A2Unorm = System::Int8(0x4b);
static constexpr System::Int8 MTLDataTypeRG11B10Float = System::Int8(0x4c);
static constexpr System::Int8 MTLDataTypeRGB9E5Float = System::Int8(0x4d);
static constexpr System::Int8 MTLDataTypeRenderPipeline = System::Int8(0x4e);
static constexpr System::Int8 MTLDataTypeIndirectCommandBuffer = System::Int8(0x50);
static constexpr System::Int8 MTLArgumentTypeBuffer = System::Int8(0x0);
static constexpr System::Int8 MTLArgumentTypeThreadgroupMemory = System::Int8(0x1);
static constexpr System::Int8 MTLArgumentTypeTexture = System::Int8(0x2);
static constexpr System::Int8 MTLArgumentTypeSampler = System::Int8(0x3);
static constexpr System::Int8 MTLArgumentTypeImageblockData = System::Int8(0x10);
static constexpr System::Int8 MTLArgumentTypeImageblock = System::Int8(0x11);
static constexpr System::Int8 MTLArgumentAccessReadOnly = System::Int8(0x0);
static constexpr System::Int8 MTLArgumentAccessReadWrite = System::Int8(0x1);
static constexpr System::Int8 MTLArgumentAccessWriteOnly = System::Int8(0x2);
static constexpr System::Int8 MTLPatchTypeNone = System::Int8(0x0);
static constexpr System::Int8 MTLPatchTypeTriangle = System::Int8(0x1);
static constexpr System::Int8 MTLPatchTypeQuad = System::Int8(0x2);
static constexpr System::Int8 MTLFunctionTypeVertex = System::Int8(0x1);
static constexpr System::Int8 MTLFunctionTypeFragment = System::Int8(0x2);
static constexpr System::Int8 MTLFunctionTypeKernel = System::Int8(0x3);
static constexpr int MTLLanguageVersion1_0 = int(0x10000);
static constexpr int MTLLanguageVersion1_1 = int(0x10001);
static constexpr int MTLLanguageVersion1_2 = int(0x10002);
static constexpr int MTLLanguageVersion2_0 = int(0x20000);
static constexpr int MTLLanguageVersion2_1 = int(0x20001);
static constexpr System::Int8 MTLLibraryErrorUnsupported = System::Int8(0x1);
static constexpr System::Int8 MTLLibraryErrorInternal = System::Int8(0x2);
static constexpr System::Int8 MTLLibraryErrorCompileFailure = System::Int8(0x3);
static constexpr System::Int8 MTLLibraryErrorCompileWarning = System::Int8(0x4);
static constexpr System::Int8 MTLLibraryErrorFunctionNotFound = System::Int8(0x5);
static constexpr System::Int8 MTLLibraryErrorFileNotFound = System::Int8(0x6);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily1_v1 = System::Int8(0x0);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily2_v1 = System::Int8(0x1);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily1_v2 = System::Int8(0x2);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily2_v2 = System::Int8(0x3);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily3_v1 = System::Int8(0x4);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily1_v3 = System::Int8(0x5);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily2_v3 = System::Int8(0x6);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily3_v2 = System::Int8(0x7);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily1_v4 = System::Int8(0x8);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily2_v4 = System::Int8(0x9);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily3_v3 = System::Int8(0xa);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily4_v1 = System::Int8(0xb);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily1_v5 = System::Int8(0xc);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily2_v5 = System::Int8(0xd);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily3_v4 = System::Int8(0xe);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily4_v2 = System::Int8(0xf);
static constexpr System::Int8 MTLFeatureSet_iOS_GPUFamily5_v1 = System::Int8(0x10);
static constexpr System::Word MTLFeatureSet_macOS_GPUFamily1_v1 = System::Word(0x2710);
static constexpr System::Word MTLFeatureSet_OSX_GPUFamily1_v1 = System::Word(0x2710);
static constexpr System::Word MTLFeatureSet_macOS_GPUFamily1_v2 = System::Word(0x2711);
static constexpr System::Word MTLFeatureSet_OSX_GPUFamily1_v2 = System::Word(0x2711);
static constexpr System::Word MTLFeatureSet_macOS_ReadWriteTextureTier2 = System::Word(0x2712);
static constexpr System::Word MTLFeatureSet_OSX_ReadWriteTextureTier2 = System::Word(0x2712);
static constexpr System::Word MTLFeatureSet_macOS_GPUFamily1_v3 = System::Word(0x2713);
static constexpr System::Word MTLFeatureSet_macOS_GPUFamily1_v4 = System::Word(0x2714);
static constexpr System::Word MTLFeatureSet_macOS_GPUFamily2_v1 = System::Word(0x2715);
static constexpr System::Word MTLFeatureSet_tvOS_GPUFamily1_v1 = System::Word(0x7530);
static constexpr System::Word MTLFeatureSet_tvOS_GPUFamily1_v2 = System::Word(0x7531);
static constexpr System::Word MTLFeatureSet_tvOS_GPUFamily1_v3 = System::Word(0x7532);
static constexpr System::Word MTLFeatureSet_tvOS_GPUFamily1_v4 = System::Word(0x7534);
static constexpr System::Int8 MTLPipelineOptionNone = System::Int8(0x0);
static constexpr System::Int8 MTLPipelineOptionArgumentInfo = System::Int8(0x1);
static constexpr System::Int8 MTLPipelineOptionBufferTypeInfo = System::Int8(0x2);
static constexpr System::Int8 MTLReadWriteTextureTierNone = System::Int8(0x0);
static constexpr System::Int8 MTLReadWriteTextureTier1 = System::Int8(0x1);
static constexpr System::Int8 MTLReadWriteTextureTier2 = System::Int8(0x2);
static constexpr System::Int8 MTLArgumentBuffersTier1 = System::Int8(0x0);
static constexpr System::Int8 MTLArgumentBuffersTier2 = System::Int8(0x1);
static constexpr System::Int8 MTLBlitOptionNone = System::Int8(0x0);
static constexpr System::Int8 MTLBlitOptionDepthFromDepthStencil = System::Int8(0x1);
static constexpr System::Int8 MTLBlitOptionStencilFromDepthStencil = System::Int8(0x2);
static constexpr System::Int8 MTLBlitOptionRowLinearPVRTC = System::Int8(0x4);
static constexpr System::Int8 MTLCommandBufferStatusNotEnqueued = System::Int8(0x0);
static constexpr System::Int8 MTLCommandBufferStatusEnqueued = System::Int8(0x1);
static constexpr System::Int8 MTLCommandBufferStatusCommitted = System::Int8(0x2);
static constexpr System::Int8 MTLCommandBufferStatusScheduled = System::Int8(0x3);
static constexpr System::Int8 MTLCommandBufferStatusCompleted = System::Int8(0x4);
static constexpr System::Int8 MTLCommandBufferStatusError = System::Int8(0x5);
static constexpr System::Int8 MTLCommandBufferErrorNone = System::Int8(0x0);
static constexpr System::Int8 MTLCommandBufferErrorInternal = System::Int8(0x1);
static constexpr System::Int8 MTLCommandBufferErrorTimeout = System::Int8(0x2);
static constexpr System::Int8 MTLCommandBufferErrorPageFault = System::Int8(0x3);
static constexpr System::Int8 MTLCommandBufferErrorBlacklisted = System::Int8(0x4);
static constexpr System::Int8 MTLCommandBufferErrorNotPermitted = System::Int8(0x7);
static constexpr System::Int8 MTLCommandBufferErrorOutOfMemory = System::Int8(0x8);
static constexpr System::Int8 MTLCommandBufferErrorInvalidResource = System::Int8(0x9);
static constexpr System::Int8 MTLCommandBufferErrorMemoryless = System::Int8(0xa);
static constexpr System::Int8 MTLCommandBufferErrorDeviceRemoved = System::Int8(0xb);
static constexpr System::Int8 MTLDispatchTypeSerial = System::Int8(0x0);
static constexpr System::Int8 MTLDispatchTypeConcurrent = System::Int8(0x1);
static constexpr System::Int8 MTLCompareFunctionNever = System::Int8(0x0);
static constexpr System::Int8 MTLCompareFunctionLess = System::Int8(0x1);
static constexpr System::Int8 MTLCompareFunctionEqual = System::Int8(0x2);
static constexpr System::Int8 MTLCompareFunctionLessEqual = System::Int8(0x3);
static constexpr System::Int8 MTLCompareFunctionGreater = System::Int8(0x4);
static constexpr System::Int8 MTLCompareFunctionNotEqual = System::Int8(0x5);
static constexpr System::Int8 MTLCompareFunctionGreaterEqual = System::Int8(0x6);
static constexpr System::Int8 MTLCompareFunctionAlways = System::Int8(0x7);
static constexpr System::Int8 MTLStencilOperationKeep = System::Int8(0x0);
static constexpr System::Int8 MTLStencilOperationZero = System::Int8(0x1);
static constexpr System::Int8 MTLStencilOperationReplace = System::Int8(0x2);
static constexpr System::Int8 MTLStencilOperationIncrementClamp = System::Int8(0x3);
static constexpr System::Int8 MTLStencilOperationDecrementClamp = System::Int8(0x4);
static constexpr System::Int8 MTLStencilOperationInvert = System::Int8(0x5);
static constexpr System::Int8 MTLStencilOperationIncrementWrap = System::Int8(0x6);
static constexpr System::Int8 MTLStencilOperationDecrementWrap = System::Int8(0x7);
static constexpr System::Int8 MTLLoadActionDontCare = System::Int8(0x0);
static constexpr System::Int8 MTLLoadActionLoad = System::Int8(0x1);
static constexpr System::Int8 MTLLoadActionClear = System::Int8(0x2);
static constexpr System::Int8 MTLStoreActionDontCare = System::Int8(0x0);
static constexpr System::Int8 MTLStoreActionStore = System::Int8(0x1);
static constexpr System::Int8 MTLStoreActionMultisampleResolve = System::Int8(0x2);
static constexpr System::Int8 MTLStoreActionStoreAndMultisampleResolve = System::Int8(0x3);
static constexpr System::Int8 MTLStoreActionUnknown = System::Int8(0x4);
static constexpr System::Int8 MTLStoreActionCustomSampleDepthStore = System::Int8(0x5);
static constexpr System::Int8 MTLStoreActionOptionNone = System::Int8(0x0);
static constexpr System::Int8 MTLStoreActionOptionCustomSamplePositions = System::Int8(0x1);
static constexpr System::Int8 MTLMultisampleDepthResolveFilterSample0 = System::Int8(0x0);
static constexpr System::Int8 MTLMultisampleDepthResolveFilterMin = System::Int8(0x1);
static constexpr System::Int8 MTLMultisampleDepthResolveFilterMax = System::Int8(0x2);
static constexpr System::Int8 MTLMultisampleStencilResolveFilterSample0 = System::Int8(0x0);
static constexpr System::Int8 MTLMultisampleStencilResolveFilterDepthResolvedSample = System::Int8(0x1);
static constexpr System::Int8 MTLAttributeFormatInvalid = System::Int8(0x0);
static constexpr System::Int8 MTLAttributeFormatUChar2 = System::Int8(0x1);
static constexpr System::Int8 MTLAttributeFormatUChar3 = System::Int8(0x2);
static constexpr System::Int8 MTLAttributeFormatUChar4 = System::Int8(0x3);
static constexpr System::Int8 MTLAttributeFormatChar2 = System::Int8(0x4);
static constexpr System::Int8 MTLAttributeFormatChar3 = System::Int8(0x5);
static constexpr System::Int8 MTLAttributeFormatChar4 = System::Int8(0x6);
static constexpr System::Int8 MTLAttributeFormatUChar2Normalized = System::Int8(0x7);
static constexpr System::Int8 MTLAttributeFormatUChar3Normalized = System::Int8(0x8);
static constexpr System::Int8 MTLAttributeFormatUChar4Normalized = System::Int8(0x9);
static constexpr System::Int8 MTLAttributeFormatChar2Normalized = System::Int8(0xa);
static constexpr System::Int8 MTLAttributeFormatChar3Normalized = System::Int8(0xb);
static constexpr System::Int8 MTLAttributeFormatChar4Normalized = System::Int8(0xc);
static constexpr System::Int8 MTLAttributeFormatUShort2 = System::Int8(0xd);
static constexpr System::Int8 MTLAttributeFormatUShort3 = System::Int8(0xe);
static constexpr System::Int8 MTLAttributeFormatUShort4 = System::Int8(0xf);
static constexpr System::Int8 MTLAttributeFormatShort2 = System::Int8(0x10);
static constexpr System::Int8 MTLAttributeFormatShort3 = System::Int8(0x11);
static constexpr System::Int8 MTLAttributeFormatShort4 = System::Int8(0x12);
static constexpr System::Int8 MTLAttributeFormatUShort2Normalized = System::Int8(0x13);
static constexpr System::Int8 MTLAttributeFormatUShort3Normalized = System::Int8(0x14);
static constexpr System::Int8 MTLAttributeFormatUShort4Normalized = System::Int8(0x15);
static constexpr System::Int8 MTLAttributeFormatShort2Normalized = System::Int8(0x16);
static constexpr System::Int8 MTLAttributeFormatShort3Normalized = System::Int8(0x17);
static constexpr System::Int8 MTLAttributeFormatShort4Normalized = System::Int8(0x18);
static constexpr System::Int8 MTLAttributeFormatHalf2 = System::Int8(0x19);
static constexpr System::Int8 MTLAttributeFormatHalf3 = System::Int8(0x1a);
static constexpr System::Int8 MTLAttributeFormatHalf4 = System::Int8(0x1b);
static constexpr System::Int8 MTLAttributeFormatFloat = System::Int8(0x1c);
static constexpr System::Int8 MTLAttributeFormatFloat2 = System::Int8(0x1d);
static constexpr System::Int8 MTLAttributeFormatFloat3 = System::Int8(0x1e);
static constexpr System::Int8 MTLAttributeFormatFloat4 = System::Int8(0x1f);
static constexpr System::Int8 MTLAttributeFormatInt = System::Int8(0x20);
static constexpr System::Int8 MTLAttributeFormatInt2 = System::Int8(0x21);
static constexpr System::Int8 MTLAttributeFormatInt3 = System::Int8(0x22);
static constexpr System::Int8 MTLAttributeFormatInt4 = System::Int8(0x23);
static constexpr System::Int8 MTLAttributeFormatUInt = System::Int8(0x24);
static constexpr System::Int8 MTLAttributeFormatUInt2 = System::Int8(0x25);
static constexpr System::Int8 MTLAttributeFormatUInt3 = System::Int8(0x26);
static constexpr System::Int8 MTLAttributeFormatUInt4 = System::Int8(0x27);
static constexpr System::Int8 MTLAttributeFormatInt1010102Normalized = System::Int8(0x28);
static constexpr System::Int8 MTLAttributeFormatUInt1010102Normalized = System::Int8(0x29);
static constexpr System::Int8 MTLAttributeFormatUChar4Normalized_BGRA = System::Int8(0x2a);
static constexpr System::Int8 MTLAttributeFormatUChar = System::Int8(0x2d);
static constexpr System::Int8 MTLAttributeFormatChar = System::Int8(0x2e);
static constexpr System::Int8 MTLAttributeFormatUCharNormalized = System::Int8(0x2f);
static constexpr System::Int8 MTLAttributeFormatCharNormalized = System::Int8(0x30);
static constexpr System::Int8 MTLAttributeFormatUShort = System::Int8(0x31);
static constexpr System::Int8 MTLAttributeFormatShort = System::Int8(0x32);
static constexpr System::Int8 MTLAttributeFormatUShortNormalized = System::Int8(0x33);
static constexpr System::Int8 MTLAttributeFormatShortNormalized = System::Int8(0x34);
static constexpr System::Int8 MTLAttributeFormatHalf = System::Int8(0x35);
static constexpr System::Int8 MTLIndexTypeUInt16 = System::Int8(0x0);
static constexpr System::Int8 MTLIndexTypeUInt32 = System::Int8(0x1);
static constexpr System::Int8 MTLStepFunctionConstant = System::Int8(0x0);
static constexpr System::Int8 MTLStepFunctionPerVertex = System::Int8(0x1);
static constexpr System::Int8 MTLStepFunctionPerInstance = System::Int8(0x2);
static constexpr System::Int8 MTLStepFunctionPerPatch = System::Int8(0x3);
static constexpr System::Int8 MTLStepFunctionPerPatchControlPoint = System::Int8(0x4);
static constexpr System::Int8 MTLStepFunctionThreadPositionInGridX = System::Int8(0x5);
static constexpr System::Int8 MTLStepFunctionThreadPositionInGridY = System::Int8(0x6);
static constexpr System::Int8 MTLStepFunctionThreadPositionInGridXIndexed = System::Int8(0x7);
static constexpr System::Int8 MTLStepFunctionThreadPositionInGridYIndexed = System::Int8(0x8);
static constexpr System::Int8 MTLMutabilityDefault = System::Int8(0x0);
static constexpr System::Int8 MTLMutabilityMutable = System::Int8(0x1);
static constexpr System::Int8 MTLMutabilityImmutable = System::Int8(0x2);
static constexpr System::Int8 MTLPrimitiveTypePoint = System::Int8(0x0);
static constexpr System::Int8 MTLPrimitiveTypeLine = System::Int8(0x1);
static constexpr System::Int8 MTLPrimitiveTypeLineStrip = System::Int8(0x2);
static constexpr System::Int8 MTLPrimitiveTypeTriangle = System::Int8(0x3);
static constexpr System::Int8 MTLPrimitiveTypeTriangleStrip = System::Int8(0x4);
static constexpr System::Int8 MTLVisibilityResultModeDisabled = System::Int8(0x0);
static constexpr System::Int8 MTLVisibilityResultModeBoolean = System::Int8(0x1);
static constexpr System::Int8 MTLVisibilityResultModeCounting = System::Int8(0x2);
static constexpr System::Int8 MTLCullModeNone = System::Int8(0x0);
static constexpr System::Int8 MTLCullModeFront = System::Int8(0x1);
static constexpr System::Int8 MTLCullModeBack = System::Int8(0x2);
static constexpr System::Int8 MTLWindingClockwise = System::Int8(0x0);
static constexpr System::Int8 MTLWindingCounterClockwise = System::Int8(0x1);
static constexpr System::Int8 MTLDepthClipModeClip = System::Int8(0x0);
static constexpr System::Int8 MTLDepthClipModeClamp = System::Int8(0x1);
static constexpr System::Int8 MTLTriangleFillModeFill = System::Int8(0x0);
static constexpr System::Int8 MTLTriangleFillModeLines = System::Int8(0x1);
static constexpr System::Int8 MTLRenderStageVertex = System::Int8(0x1);
static constexpr System::Int8 MTLRenderStageFragment = System::Int8(0x2);
static constexpr System::Int8 MTLBlendFactorZero = System::Int8(0x0);
static constexpr System::Int8 MTLBlendFactorOne = System::Int8(0x1);
static constexpr System::Int8 MTLBlendFactorSourceColor = System::Int8(0x2);
static constexpr System::Int8 MTLBlendFactorOneMinusSourceColor = System::Int8(0x3);
static constexpr System::Int8 MTLBlendFactorSourceAlpha = System::Int8(0x4);
static constexpr System::Int8 MTLBlendFactorOneMinusSourceAlpha = System::Int8(0x5);
static constexpr System::Int8 MTLBlendFactorDestinationColor = System::Int8(0x6);
static constexpr System::Int8 MTLBlendFactorOneMinusDestinationColor = System::Int8(0x7);
static constexpr System::Int8 MTLBlendFactorDestinationAlpha = System::Int8(0x8);
static constexpr System::Int8 MTLBlendFactorOneMinusDestinationAlpha = System::Int8(0x9);
static constexpr System::Int8 MTLBlendFactorSourceAlphaSaturated = System::Int8(0xa);
static constexpr System::Int8 MTLBlendFactorBlendColor = System::Int8(0xb);
static constexpr System::Int8 MTLBlendFactorOneMinusBlendColor = System::Int8(0xc);
static constexpr System::Int8 MTLBlendFactorBlendAlpha = System::Int8(0xd);
static constexpr System::Int8 MTLBlendFactorOneMinusBlendAlpha = System::Int8(0xe);
static constexpr System::Int8 MTLBlendFactorSource1Color = System::Int8(0xf);
static constexpr System::Int8 MTLBlendFactorOneMinusSource1Color = System::Int8(0x10);
static constexpr System::Int8 MTLBlendFactorSource1Alpha = System::Int8(0x11);
static constexpr System::Int8 MTLBlendFactorOneMinusSource1Alpha = System::Int8(0x12);
static constexpr System::Int8 MTLBlendOperationAdd = System::Int8(0x0);
static constexpr System::Int8 MTLBlendOperationSubtract = System::Int8(0x1);
static constexpr System::Int8 MTLBlendOperationReverseSubtract = System::Int8(0x2);
static constexpr System::Int8 MTLBlendOperationMin = System::Int8(0x3);
static constexpr System::Int8 MTLBlendOperationMax = System::Int8(0x4);
static constexpr System::Int8 MTLColorWriteMaskNone = System::Int8(0x0);
static constexpr System::Int8 MTLColorWriteMaskRed = System::Int8(0x8);
static constexpr System::Int8 MTLColorWriteMaskGreen = System::Int8(0x4);
static constexpr System::Int8 MTLColorWriteMaskBlue = System::Int8(0x2);
static constexpr System::Int8 MTLColorWriteMaskAlpha = System::Int8(0x1);
static constexpr System::Int8 MTLColorWriteMaskAll = System::Int8(0xf);
static constexpr System::Int8 MTLPrimitiveTopologyClassUnspecified = System::Int8(0x0);
static constexpr System::Int8 MTLPrimitiveTopologyClassPoint = System::Int8(0x1);
static constexpr System::Int8 MTLPrimitiveTopologyClassLine = System::Int8(0x2);
static constexpr System::Int8 MTLPrimitiveTopologyClassTriangle = System::Int8(0x3);
static constexpr System::Int8 MTLTessellationPartitionModePow2 = System::Int8(0x0);
static constexpr System::Int8 MTLTessellationPartitionModeInteger = System::Int8(0x1);
static constexpr System::Int8 MTLTessellationPartitionModeFractionalOdd = System::Int8(0x2);
static constexpr System::Int8 MTLTessellationPartitionModeFractionalEven = System::Int8(0x3);
static constexpr System::Int8 MTLTessellationFactorStepFunctionConstant = System::Int8(0x0);
static constexpr System::Int8 MTLTessellationFactorStepFunctionPerPatch = System::Int8(0x1);
static constexpr System::Int8 MTLTessellationFactorStepFunctionPerInstance = System::Int8(0x2);
static constexpr System::Int8 MTLTessellationFactorStepFunctionPerPatchAndPerInstance = System::Int8(0x3);
static constexpr System::Int8 MTLTessellationFactorFormatHalf = System::Int8(0x0);
static constexpr System::Int8 MTLTessellationControlPointIndexTypeNone = System::Int8(0x0);
static constexpr System::Int8 MTLTessellationControlPointIndexTypeUInt16 = System::Int8(0x1);
static constexpr System::Int8 MTLTessellationControlPointIndexTypeUInt32 = System::Int8(0x2);
static constexpr System::Int8 MTLVertexFormatInvalid = System::Int8(0x0);
static constexpr System::Int8 MTLVertexFormatUChar2 = System::Int8(0x1);
static constexpr System::Int8 MTLVertexFormatUChar3 = System::Int8(0x2);
static constexpr System::Int8 MTLVertexFormatUChar4 = System::Int8(0x3);
static constexpr System::Int8 MTLVertexFormatChar2 = System::Int8(0x4);
static constexpr System::Int8 MTLVertexFormatChar3 = System::Int8(0x5);
static constexpr System::Int8 MTLVertexFormatChar4 = System::Int8(0x6);
static constexpr System::Int8 MTLVertexFormatUChar2Normalized = System::Int8(0x7);
static constexpr System::Int8 MTLVertexFormatUChar3Normalized = System::Int8(0x8);
static constexpr System::Int8 MTLVertexFormatUChar4Normalized = System::Int8(0x9);
static constexpr System::Int8 MTLVertexFormatChar2Normalized = System::Int8(0xa);
static constexpr System::Int8 MTLVertexFormatChar3Normalized = System::Int8(0xb);
static constexpr System::Int8 MTLVertexFormatChar4Normalized = System::Int8(0xc);
static constexpr System::Int8 MTLVertexFormatUShort2 = System::Int8(0xd);
static constexpr System::Int8 MTLVertexFormatUShort3 = System::Int8(0xe);
static constexpr System::Int8 MTLVertexFormatUShort4 = System::Int8(0xf);
static constexpr System::Int8 MTLVertexFormatShort2 = System::Int8(0x10);
static constexpr System::Int8 MTLVertexFormatShort3 = System::Int8(0x11);
static constexpr System::Int8 MTLVertexFormatShort4 = System::Int8(0x12);
static constexpr System::Int8 MTLVertexFormatUShort2Normalized = System::Int8(0x13);
static constexpr System::Int8 MTLVertexFormatUShort3Normalized = System::Int8(0x14);
static constexpr System::Int8 MTLVertexFormatUShort4Normalized = System::Int8(0x15);
static constexpr System::Int8 MTLVertexFormatShort2Normalized = System::Int8(0x16);
static constexpr System::Int8 MTLVertexFormatShort3Normalized = System::Int8(0x17);
static constexpr System::Int8 MTLVertexFormatShort4Normalized = System::Int8(0x18);
static constexpr System::Int8 MTLVertexFormatHalf2 = System::Int8(0x19);
static constexpr System::Int8 MTLVertexFormatHalf3 = System::Int8(0x1a);
static constexpr System::Int8 MTLVertexFormatHalf4 = System::Int8(0x1b);
static constexpr System::Int8 MTLVertexFormatFloat = System::Int8(0x1c);
static constexpr System::Int8 MTLVertexFormatFloat2 = System::Int8(0x1d);
static constexpr System::Int8 MTLVertexFormatFloat3 = System::Int8(0x1e);
static constexpr System::Int8 MTLVertexFormatFloat4 = System::Int8(0x1f);
static constexpr System::Int8 MTLVertexFormatInt = System::Int8(0x20);
static constexpr System::Int8 MTLVertexFormatInt2 = System::Int8(0x21);
static constexpr System::Int8 MTLVertexFormatInt3 = System::Int8(0x22);
static constexpr System::Int8 MTLVertexFormatInt4 = System::Int8(0x23);
static constexpr System::Int8 MTLVertexFormatUInt = System::Int8(0x24);
static constexpr System::Int8 MTLVertexFormatUInt2 = System::Int8(0x25);
static constexpr System::Int8 MTLVertexFormatUInt3 = System::Int8(0x26);
static constexpr System::Int8 MTLVertexFormatUInt4 = System::Int8(0x27);
static constexpr System::Int8 MTLVertexFormatInt1010102Normalized = System::Int8(0x28);
static constexpr System::Int8 MTLVertexFormatUInt1010102Normalized = System::Int8(0x29);
static constexpr System::Int8 MTLVertexFormatUChar4Normalized_BGRA = System::Int8(0x2a);
static constexpr System::Int8 MTLVertexFormatUChar = System::Int8(0x2d);
static constexpr System::Int8 MTLVertexFormatChar = System::Int8(0x2e);
static constexpr System::Int8 MTLVertexFormatUCharNormalized = System::Int8(0x2f);
static constexpr System::Int8 MTLVertexFormatCharNormalized = System::Int8(0x30);
static constexpr System::Int8 MTLVertexFormatUShort = System::Int8(0x31);
static constexpr System::Int8 MTLVertexFormatShort = System::Int8(0x32);
static constexpr System::Int8 MTLVertexFormatUShortNormalized = System::Int8(0x33);
static constexpr System::Int8 MTLVertexFormatShortNormalized = System::Int8(0x34);
static constexpr System::Int8 MTLVertexFormatHalf = System::Int8(0x35);
static constexpr System::Int8 MTLVertexStepFunctionConstant = System::Int8(0x0);
static constexpr System::Int8 MTLVertexStepFunctionPerVertex = System::Int8(0x1);
static constexpr System::Int8 MTLVertexStepFunctionPerInstance = System::Int8(0x2);
static constexpr System::Int8 MTLVertexStepFunctionPerPatch = System::Int8(0x3);
static constexpr System::Int8 MTLVertexStepFunctionPerPatchControlPoint = System::Int8(0x4);
static constexpr System::Int8 MTLSamplerMinMagFilterNearest = System::Int8(0x0);
static constexpr System::Int8 MTLSamplerMinMagFilterLinear = System::Int8(0x1);
static constexpr System::Int8 MTLSamplerMipFilterNotMipmapped = System::Int8(0x0);
static constexpr System::Int8 MTLSamplerMipFilterNearest = System::Int8(0x1);
static constexpr System::Int8 MTLSamplerMipFilterLinear = System::Int8(0x2);
static constexpr System::Int8 MTLSamplerAddressModeClampToEdge = System::Int8(0x0);
static constexpr System::Int8 MTLSamplerAddressModeMirrorClampToEdge = System::Int8(0x1);
static constexpr System::Int8 MTLSamplerAddressModeRepeat = System::Int8(0x2);
static constexpr System::Int8 MTLSamplerAddressModeMirrorRepeat = System::Int8(0x3);
static constexpr System::Int8 MTLSamplerAddressModeClampToZero = System::Int8(0x4);
static constexpr System::Int8 MTLSamplerAddressModeClampToBorderColor = System::Int8(0x5);
static constexpr System::Int8 MTLSamplerBorderColorTransparentBlack = System::Int8(0x0);
static constexpr System::Int8 MTLSamplerBorderColorOpaqueBlack = System::Int8(0x1);
static constexpr System::Int8 MTLSamplerBorderColorOpaqueWhite = System::Int8(0x2);
static constexpr System::Int8 MTLIndirectCommandTypeDraw = System::Int8(0x1);
static constexpr System::Int8 MTLIndirectCommandTypeDrawIndexed = System::Int8(0x2);
static constexpr System::Int8 MTLIndirectCommandTypeDrawPatches = System::Int8(0x4);
static constexpr System::Int8 MTLIndirectCommandTypeDrawIndexedPatches = System::Int8(0x8);
#define libMetal u"/System/Library/Frameworks/Metal.framework/Metal"
extern "C" MTLOrigin __cdecl MTLOriginMake(unsigned long x, unsigned long y, unsigned long z);
extern "C" MTLSize __cdecl MTLSizeMake(unsigned long width, unsigned long height, unsigned long depth);
extern "C" MTLRegion __cdecl MTLRegionMake1D(unsigned long x, unsigned long width);
extern "C" MTLRegion __cdecl MTLRegionMake2D(unsigned long x, unsigned long y, unsigned long width, unsigned long height);
extern "C" MTLRegion __cdecl MTLRegionMake3D(unsigned long x, unsigned long y, unsigned long z, unsigned long width, unsigned long height, unsigned long depth);
extern "C" MTLSamplePosition __cdecl MTLSamplePositionMake(float x, float y);
extern "C" void * __cdecl MTLCreateSystemDefaultDevice(void);
extern "C" void * __cdecl MTLCopyAllDevices(void);
extern "C" MTLClearColor __cdecl MTLClearColorMake(double red, double green, double blue, double alpha);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MTLLibraryErrorDomain(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall MTLCommandBufferErrorDomain(void);
}	/* namespace Metal */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_METAL)
using namespace Macapi::Metal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_MetalHPP
