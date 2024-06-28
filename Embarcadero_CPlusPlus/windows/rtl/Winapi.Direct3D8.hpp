// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Direct3D8.pas' rev: 34.00 (Windows)

#ifndef Winapi_Direct3d8HPP
#define Winapi_Direct3d8HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.DXTypes.hpp>

//-- user supplied -----------------------------------------------------------
#include <d3d8types.h>
#include <d3d8caps.h>
#include <d3d8.h>
DECLARE_DINTERFACE_TYPE(IDirect3D8);
DECLARE_DINTERFACE_TYPE(IDirect3DDevice8);
DECLARE_DINTERFACE_TYPE(IDirect3DSwapChain8);
DECLARE_DINTERFACE_TYPE(IDirect3DResource8);
DECLARE_DINTERFACE_TYPE(IDirect3DBaseTexture8);
DECLARE_DINTERFACE_TYPE(IDirect3DTexture8);
DECLARE_DINTERFACE_TYPE(IDirect3DVolumeTexture8);
DECLARE_DINTERFACE_TYPE(IDirect3DCubeTexture8);
DECLARE_DINTERFACE_TYPE(IDirect3DVertexBuffer8);
DECLARE_DINTERFACE_TYPE(IDirect3DIndexBuffer8);
DECLARE_DINTERFACE_TYPE(IDirect3DSurface8);
DECLARE_DINTERFACE_TYPE(IDirect3DVolume8);

namespace Winapi
{
namespace Direct3d8
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3DCOLOR TD3DColor;

typedef _D3DVECTOR TD3DVector;

using Winapi::Dxtypes::PD3DVector;

typedef _D3DCOLORVALUE TD3DColorValue;

typedef LPD3DCOLORVALUE PD3DColorValue;

typedef _D3DRECT TD3DRect;

typedef LPD3DRECT PD3DRect;

typedef _D3DMATRIX TD3DMatrix;

typedef LPD3DMATRIX PD3DMatrix;

typedef _D3DVIEWPORT8 *PD3DViewport8;

typedef _D3DVIEWPORT8 TD3DViewport8;

typedef _D3DCLIPSTATUS8 *PD3DClipStatus8;

typedef _D3DCLIPSTATUS8 TD3DClipStatus8;

typedef _D3DMATERIAL8 *PD3DMaterial8;

typedef _D3DMATERIAL8 TD3DMaterial8;

typedef _D3DLIGHTTYPE TD3DLightType;

typedef _D3DLIGHT8 *PD3DLight8;

typedef _D3DLIGHT8 TD3DLight8;

typedef _D3DSHADEMODE TD3DShadeMode;

typedef _D3DFILLMODE TD3DFillMode;

typedef _D3DLINEPATTERN *PD3DLinePattern;

typedef _D3DLINEPATTERN TD3DLinePattern;

typedef _D3DBLEND TD3DBlend;

typedef _D3DBLENDOP TD3DBlendOp;

typedef _D3DTEXTUREADDRESS TD3DTextureAddress;

typedef _D3DCULL TD3DCull;

typedef _D3DCMPFUNC TD3DCmpFunc;

typedef _D3DSTENCILOP TD3DStencilOp;

typedef _D3DFOGMODE TD3DFogMode;

typedef _D3DZBUFFERTYPE TD3DZBufferType;

typedef _D3DPRIMITIVETYPE TD3DPrimitiveType;

typedef _D3DTRANSFORMSTATETYPE TD3DTransformStateType;

typedef _D3DRENDERSTATETYPE TD3DRenderStateType;

typedef _D3DMATERIALCOLORSOURCE TD3DMaterialSource;

typedef _D3DTEXTURESTAGESTATETYPE TD3DTextureStageStateType;

typedef _D3DTEXTUREOP TD3DTextureOp;

typedef _D3DTEXTUREFILTERTYPE TD3DTextureFilterType;

typedef _D3DVSD_TOKENTYPE TD3DVSDTokenType;

typedef _D3DSHADER_INSTRUCTION_OPCODE_TYPE TD3DShaderInstructionOpcodeType;

typedef _D3DSHADER_PARAM_DSTMOD_TYPE TD3DShaderParamDSTModType;

typedef _D3DSHADER_PARAM_REGISTER_TYPE TD3DShaderParamRegisterType;

typedef _D3DVS_RASTOUT_OFFSETS TD3DVSRastOutOffsets;

typedef _D3DVS_ADDRESSMODE_TYPE TD3DVSAddressModeType;

typedef _D3DSHADER_PARAM_SRCMOD_TYPE TD3DShaderParamSRCModType;

typedef _D3DBASISTYPE TD3DBasisType;

typedef _D3DORDERTYPE TD3DOrderType;

typedef _D3DPATCHEDGESTYLE TD3DPatchEdgeStyle;

typedef _D3DSTATEBLOCKTYPE TD3DStateBlockType;

typedef _D3DVERTEXBLENDFLAGS TD3DVertexBlendFlags;

typedef _D3DTEXTURETRANSFORMFLAGS TD3DTextureTransformFlags;

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

typedef _D3DADAPTER_IDENTIFIER8 *PD3DAdapterIdentifier8;

typedef _D3DADAPTER_IDENTIFIER8 TD3DAdapterIdentifier8;

typedef _D3DRASTER_STATUS *PD3DRasterStatus;

typedef _D3DRASTER_STATUS TD3DRasterStatus;

typedef unsigned TD3DDebugMonitorTokens;

typedef _D3DRESOURCESTATS *PD3DResourceStats;

typedef _D3DRESOURCESTATS TD3DResourceStats;

typedef _D3DDEVINFO_RESOURCEMANAGER *PD3DDevInfoResourceManager;

typedef _D3DDEVINFO_RESOURCEMANAGER TD3DDevInfoResourceManager;

typedef _D3DDEVINFO_D3DVERTEXSTATS *PD3DDevInfoD3DVertexStats;

typedef _D3DDEVINFO_D3DVERTEXSTATS TD3DDevInfoD3DVertexStats;

typedef _D3DCAPS8 *PD3DCaps8;

typedef _D3DCAPS8 TD3DCaps8;

typedef PD3DAdapterIdentifier8 PD3DAdapter_Identifier8;

typedef PD3DDeviceCreationParameters PD3DDevice_Creation_Parameters;

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

typedef _D3DADAPTER_IDENTIFIER8 TD3DAdapter_Identifier8;

typedef _D3DBACKBUFFER_TYPE TD3DBackBuffer_Type;

typedef _D3DCUBEMAP_FACES TD3DCubeMap_Faces;

typedef _D3DDEVICE_CREATION_PARAMETERS TD3DDevice_Creation_Parameters;

typedef _D3DINDEXBUFFER_DESC TD3DIndexBuffer_Desc;

typedef _D3DLOCKED_BOX TD3DLocked_Box;

typedef _D3DLOCKED_RECT TD3DLocked_Rect;

typedef _D3DMULTISAMPLE_TYPE TD3DMultiSample_Type;

typedef _D3DPRESENT_PARAMETERS_ TD3DPresent_Parameters;

typedef _D3DRASTER_STATUS TD3DRaster_Status;

typedef _D3DRECTPATCH_INFO TD3DRectPatch_Info;

typedef _D3DSHADER_INSTRUCTION_OPCODE_TYPE TD3DShader_Instruction_Opcode_Type;

typedef _D3DSHADER_PARAM_DSTMOD_TYPE TD3DShader_Param_DSTMod_Type;

typedef _D3DSHADER_PARAM_REGISTER_TYPE TD3DShader_Param_Register_Type;

typedef _D3DSHADER_PARAM_SRCMOD_TYPE TD3DShader_Param_SRCMod_Type;

typedef _D3DSURFACE_DESC TD3DSurface_Desc;

typedef _D3DTRIPATCH_INFO TD3DTriPatch_Info;

typedef _D3DVERTEXBUFFER_DESC TD3DVertexBuffer_Desc;

typedef _D3DVOLUME_DESC TD3DVolume_Desc;

typedef _D3DVSD_TOKENTYPE TD3DVSD_TokenType;

typedef _D3DVS_ADDRESSMODE_TYPE TD3DVS_AddressMode_Type;

typedef _D3DVS_RASTOUT_OFFSETS TD3DVS_RastOut_Offsets;

typedef _D3DDEVINFO_RESOURCEMANAGER TD3DDevInfo_ResourceManager;

typedef _D3DDEVINFO_D3DVERTEXSTATS TD3DDevInfo_D3DVertexStats;

typedef PD3DDevInfoResourceManager PD3DDevInfo_ResourceManager;

typedef PD3DDevInfoD3DVertexStats PD3DDevInfo_D3DVertexStats;

//-- var, const, procedure ---------------------------------------------------
static const unsigned iTrue = unsigned(0x1);
static const unsigned iFalse = unsigned(0x0);
static const int MAKE_D3DHRESULT_R = int(-2005532672);
extern DELPHI_PACKAGE bool __fastcall Direct3D8Loaded(void);
extern DELPHI_PACKAGE bool __fastcall UnLoadDirect3D8(void);
extern DELPHI_PACKAGE bool __fastcall LoadDirect3D8(void);
extern "C" void * __stdcall _Direct3DCreate8(unsigned SDKVersion);
}	/* namespace Direct3d8 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DIRECT3D8)
using namespace Winapi::Direct3d8;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Direct3d8HPP
