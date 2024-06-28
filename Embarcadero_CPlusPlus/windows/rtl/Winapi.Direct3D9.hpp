// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Direct3D9.pas' rev: 34.00 (Windows)

#ifndef Winapi_Direct3d9HPP
#define Winapi_Direct3d9HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.DXTypes.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3d9.h"
#include "d3d9types.h"
#include "d3d9caps.h"
DECLARE_DINTERFACE_TYPE(IDirect3D9);
DECLARE_DINTERFACE_TYPE(IDirect3D9Ex);
DECLARE_DINTERFACE_TYPE(IDirect3DDevice9);
DECLARE_DINTERFACE_TYPE(IDirect3DDevice9Ex);
DECLARE_DINTERFACE_TYPE(IDirect3DStateBlock9);
DECLARE_DINTERFACE_TYPE(IDirect3DSwapChain9);
DECLARE_DINTERFACE_TYPE(IDirect3DSwapChain9Ex);
DECLARE_DINTERFACE_TYPE(IDirect3DResource9);
DECLARE_DINTERFACE_TYPE(IDirect3DVertexDeclaration9);
DECLARE_DINTERFACE_TYPE(IDirect3DVertexShader9);
DECLARE_DINTERFACE_TYPE(IDirect3DPixelShader9);
DECLARE_DINTERFACE_TYPE(IDirect3DBaseTexture9);
DECLARE_DINTERFACE_TYPE(IDirect3DTexture9);
DECLARE_DINTERFACE_TYPE(IDirect3DVolumeTexture9);
DECLARE_DINTERFACE_TYPE(IDirect3DCubeTexture9);
DECLARE_DINTERFACE_TYPE(IDirect3DVertexBuffer9);
DECLARE_DINTERFACE_TYPE(IDirect3DIndexBuffer9);
DECLARE_DINTERFACE_TYPE(IDirect3DSurface9);
DECLARE_DINTERFACE_TYPE(IDirect3DVolume9);
DECLARE_DINTERFACE_TYPE(IDirect3DQuery9);

namespace Winapi
{
namespace Direct3d9
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _D3DDEVTYPE TD3DDevType;

typedef _D3DMULTISAMPLE_TYPE TD3DMultiSampleType;

typedef _D3DFORMAT *PD3DFormat;

typedef _D3DFORMAT TD3DFormat;

typedef _D3DDISPLAYMODE *PD3DDisplayMode;

typedef _D3DDISPLAYMODE TD3DDisplayMode;

typedef _D3DDEVICE_CREATION_PARAMETERS *PD3DDeviceCreationParameters;

typedef _D3DDEVICE_CREATION_PARAMETERS TD3DDeviceCreationParameters;

typedef _D3DSWAPEFFECT TD3DSwapEffect;

typedef _D3DPOOL TD3DPool;

typedef _D3DPRESENT_PARAMETERS_ *PD3DPresentParameters;

typedef _D3DPRESENT_PARAMETERS_ TD3DPresentParameters;

typedef _D3DGAMMARAMP *PD3DGammaRamp;

typedef _D3DGAMMARAMP TD3DGammaRamp;

typedef _D3DBACKBUFFER_TYPE TD3DBackbufferType;

typedef _D3DRESOURCETYPE TD3DResourceType;

typedef _D3DCUBEMAP_FACES TD3DCubemapFaces;

typedef _D3DVERTEXBUFFER_DESC *PD3DVertexBufferDesc;

typedef _D3DVERTEXBUFFER_DESC TD3DVertexBufferDesc;

typedef _D3DINDEXBUFFER_DESC *PD3DIndexBufferDesc;

typedef _D3DINDEXBUFFER_DESC TD3DIndexBufferDesc;

typedef _D3DSURFACE_DESC *PD3DSurfaceDesc;

typedef _D3DSURFACE_DESC TD3DSurfaceDesc;

typedef _D3DVOLUME_DESC *PD3DVolumeDesc;

typedef _D3DVOLUME_DESC TD3DVolumeDesc;

typedef _D3DLOCKED_RECT *PD3DLockedRect;

typedef _D3DLOCKED_RECT TD3DLockedRect;

typedef _D3DBOX *PD3DBox;

typedef _D3DBOX TD3DBox;

typedef _D3DLOCKED_BOX *PD3DLockedBox;

typedef _D3DLOCKED_BOX TD3DLockedBox;

typedef _D3DRANGE *PD3DRange;

typedef _D3DRANGE TD3DRange;

typedef _D3DRECTPATCH_INFO *PD3DRectPatchInfo;

typedef _D3DRECTPATCH_INFO TD3DRectPatchInfo;

typedef _D3DTRIPATCH_INFO *PD3DTriPatchInfo;

typedef _D3DTRIPATCH_INFO TD3DTriPatchInfo;

typedef _D3DADAPTER_IDENTIFIER9 *PD3DAdapterIdentifier9;

typedef _D3DADAPTER_IDENTIFIER9 TD3DAdapterIdentifier9;

typedef _D3DRASTER_STATUS *PD3DRasterStatus;

typedef _D3DRASTER_STATUS TD3DRasterStatus;

typedef unsigned TD3DDebugMonitorTokens;

typedef _D3DQUERYTYPE TD3DQueryType;

typedef _D3DRESOURCESTATS *PD3DResourceStats;

typedef _D3DRESOURCESTATS TD3DResourceStats;

typedef _D3DDEVINFO_RESOURCEMANAGER *PD3DDevInfoResourceManager;

typedef _D3DDEVINFO_RESOURCEMANAGER TD3DDevInfoResourceManager;

typedef _D3DDEVINFO_D3DVERTEXSTATS *PD3DDevInfoD3DVertexStats;

typedef _D3DDEVINFO_D3DVERTEXSTATS TD3DDevInfoD3DVertexStats;

typedef _D3DDEVINFO_VCACHE *PD3DDevInfoVCache;

typedef _D3DDEVINFO_VCACHE TD3DDevInfoVCache;

typedef _D3DDEVINFO_D3D9PIPELINETIMINGS *PD3DDevInfoD3D9PipelineTimings;

typedef _D3DDEVINFO_D3D9PIPELINETIMINGS TD3DDevInfoD3D9PipelineTimings;

typedef _D3DDEVINFO_D3D9INTERFACETIMINGS *PD3DDevInfoD3D9InterfaceTimings;

typedef _D3DDEVINFO_D3D9INTERFACETIMINGS TD3DDevInfoD3D9InterfaceTimings;

typedef _D3DDEVINFO_D3D9STAGETIMINGS *PD3DDevInfoD3D9StageTimings;

typedef _D3DDEVINFO_D3D9STAGETIMINGS TD3DDevInfoD3D9StageTimings;

typedef _D3DDEVINFO_D3D9BANDWIDTHTIMINGS *PD3DDevInfoD3D9BandwidthTimings;

typedef _D3DDEVINFO_D3D9BANDWIDTHTIMINGS TD3DDevInfoD3D9BandwidthTimings;

typedef _D3DDEVINFO_D3D9CACHEUTILIZATION *PD3DDevInfoD3D9CacheUtilization;

typedef _D3DDEVINFO_D3D9CACHEUTILIZATION TD3DDevInfoD3D9CacheUtilization;

typedef _D3DCOMPOSERECTSOP *PD3DComposeRectsOp;

typedef _D3DCOMPOSERECTSOP TD3DComposeRectsOp;

typedef _D3DCOMPOSERECTDESC *PD3DComposeRectDesc;

typedef _D3DCOMPOSERECTDESC TD3DComposeRectDesc;

typedef _D3DCOMPOSERECTDESTINATION *PD3DComposeRectDestination;

typedef _D3DCOMPOSERECTDESTINATION TD3DComposeRectDestination;

typedef _D3DPRESENTSTATS *PD3DPresentStats;

typedef _D3DPRESENTSTATS TD3DPresentStats;

typedef D3DSCANLINEORDERING *PD3DScanlineOrdering;

typedef D3DSCANLINEORDERING TD3DScanlineOrdering;

typedef D3DDISPLAYMODEEX *PD3DDisplayModeEx;

typedef D3DDISPLAYMODEEX TD3DDisplayModeEx;

typedef D3DDISPLAYMODEFILTER *PD3DDisplayModeFilter;

typedef D3DDISPLAYMODEFILTER TD3DDisplayModeFilter;

typedef D3DDISPLAYROTATION *PD3DDisplayRotation;

typedef D3DDISPLAYROTATION TD3DDisplayRotation;

typedef _D3DVSHADERCAPS2_0 *PD3DVShaderCaps2_0;

typedef _D3DVSHADERCAPS2_0 TD3DVShaderCaps2_0;

typedef _D3DPSHADERCAPS2_0 *PD3DPShaderCaps2_0;

typedef _D3DPSHADERCAPS2_0 TD3DPShaderCaps2_0;

typedef _D3DCAPS9 *PD3DCaps9;

typedef _D3DCAPS9 TD3DCaps9;

typedef PD3DAdapterIdentifier9 PD3DAdapter_Identifier9;

typedef PD3DDeviceCreationParameters PD3DDevice_Creation_Parameters;

typedef PD3DDevInfoD3DVertexStats PD3DDevInfo_D3DVertexStats;

typedef PD3DDevInfoResourceManager PD3DDevInfo_ResourceManager;

typedef PD3DDevInfoVCache PD3DDevInfo_VCache;

typedef PD3DIndexBufferDesc PD3DIndexBuffer_Desc;

typedef PD3DLockedBox PD3DLocked_Box;

typedef PD3DLockedRect PD3DLocked_Rect;

typedef PD3DPresentParameters PD3DPresent_Parameters;

typedef PD3DRasterStatus PD3DRaster_Status;

typedef PD3DRectPatchInfo PD3DRectPatch_Info;

typedef PD3DSurfaceDesc PD3DSurface_Desc;

typedef PD3DTriPatchInfo PD3DTriPatch_Info;

typedef PD3DVertexBufferDesc PD3DVertexBuffer_Desc;

typedef PD3DVolumeDesc PD3DVolume_Desc;

typedef _D3DADAPTER_IDENTIFIER9 TD3DAdapter_Identifier9;

typedef _D3DBACKBUFFER_TYPE TD3DBackBuffer_Type;

typedef _D3DCUBEMAP_FACES TD3DCubeMap_Faces;

typedef _D3DDEVICE_CREATION_PARAMETERS TD3DDevice_Creation_Parameters;

typedef _D3DDEVINFO_D3DVERTEXSTATS TD3DDevInfo_D3DVertexStats;

typedef _D3DDEVINFO_RESOURCEMANAGER TD3DDevInfo_ResourceManager;

typedef _D3DDEVINFO_VCACHE TD3DDevInfo_VCache;

typedef _D3DINDEXBUFFER_DESC TD3DIndexBuffer_Desc;

typedef _D3DLOCKED_BOX TD3DLocked_Box;

typedef _D3DLOCKED_RECT TD3DLocked_Rect;

typedef _D3DMULTISAMPLE_TYPE TD3DMultiSample_Type;

typedef _D3DPRESENT_PARAMETERS_ TD3DPresent_Parameters;

typedef _D3DRASTER_STATUS TD3DRaster_Status;

typedef _D3DRECTPATCH_INFO TD3DRectPatch_Info;

typedef _D3DSAMPLER_TEXTURE_TYPE TD3DSampler_Texture_Type;

typedef _D3DSHADER_ADDRESSMODE_TYPE TD3DShader_AddressMode_Type;

typedef _D3DSHADER_COMPARISON TD3DShader_Comparison;

typedef _D3DSHADER_INSTRUCTION_OPCODE_TYPE TD3DShader_Instruction_Opcode_Type;

typedef _D3DSHADER_MISCTYPE_OFFSETS TD3DShader_MiscType_Offsets;

typedef _D3DSHADER_PARAM_REGISTER_TYPE TD3DShader_Param_Register_Type;

typedef _D3DSHADER_PARAM_SRCMOD_TYPE TD3DShader_Param_SRCMod_Type;

typedef _D3DSURFACE_DESC TD3DSurface_Desc;

typedef _D3DTRIPATCH_INFO TD3DTriPatch_Info;

typedef _D3DVERTEXBUFFER_DESC TD3DVertexBuffer_Desc;

typedef _D3DVOLUME_DESC TD3DVolume_Desc;

typedef _D3DVS_ADDRESSMODE_TYPE TD3DVS_AddressMode_Type;

typedef _D3DVS_RASTOUT_OFFSETS TD3DVS_RastOut_Offsets;

//-- var, const, procedure ---------------------------------------------------
#define Direct3D9dll L"d3d9.dll"
extern DELPHI_PACKAGE bool __fastcall Direct3D9Loaded(void);
extern DELPHI_PACKAGE bool __fastcall UnLoadDirect3D9(void);
extern DELPHI_PACKAGE bool __fastcall LoadDirect3D9(void);
extern "C" void * __stdcall _Direct3DCreate9(unsigned SDKVersion);
}	/* namespace Direct3d9 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECT3D9)
using namespace Winapi::Direct3d9;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Direct3d9HPP
