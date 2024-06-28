// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3DX9.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3dx9HPP
#define Winapi_D3dx9HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.SysUtils.hpp>
#include <Winapi.Direct3D9.hpp>
#include <Winapi.DXTypes.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3dx9.h"
namespace Winapi
{
namespace D3dx9
{
DECLARE_DINTERFACE_TYPE(ID3DXMatrixStack);
DECLARE_DINTERFACE_TYPE(ID3DXBuffer);
DECLARE_DINTERFACE_TYPE(ID3DXSprite);
DECLARE_DINTERFACE_TYPE(ID3DXFont);
DECLARE_DINTERFACE_TYPE(ID3DXRenderToSurface);
DECLARE_DINTERFACE_TYPE(ID3DXRenderToEnvMap);
DECLARE_DINTERFACE_TYPE(ID3DXLine);
DECLARE_DINTERFACE_TYPE(ID3DXConstantTable);
DECLARE_DINTERFACE_TYPE(ID3DXTextureShader);
DECLARE_DINTERFACE_TYPE(ID3DXFragmentLinker);
DECLARE_DINTERFACE_TYPE(ID3DXEffectPool);
DECLARE_DINTERFACE_TYPE(ID3DXBaseEffect);
DECLARE_DINTERFACE_TYPE(ID3DXEffectStateManager);
DECLARE_DINTERFACE_TYPE(ID3DXEffect);
DECLARE_DINTERFACE_TYPE(ID3DXEffectCompiler);
DECLARE_DINTERFACE_TYPE(ID3DXFile);
DECLARE_DINTERFACE_TYPE(ID3DXFileSaveObject);
DECLARE_DINTERFACE_TYPE(ID3DXFileSaveData);
DECLARE_DINTERFACE_TYPE(ID3DXFileEnumObject);
DECLARE_DINTERFACE_TYPE(ID3DXFileData);
DECLARE_DINTERFACE_TYPE(ID3DXBaseMesh);
DECLARE_DINTERFACE_TYPE(ID3DXMesh);
DECLARE_DINTERFACE_TYPE(ID3DXPMesh);
DECLARE_DINTERFACE_TYPE(ID3DXSPMesh);
DECLARE_DINTERFACE_TYPE(ID3DXPatchMesh);
DECLARE_DINTERFACE_TYPE(ID3DXSkinInfo);
typedef LPD3DXUVATLASCB TD3DXUVAtlasCB;
typedef LPD3DXIMTSIGNALCALLBACK TD3DXIMTSignalCallback;
typedef LPD3DXSHPRTSIMCB TD3DXSHPRTSimCB;
DECLARE_DINTERFACE_TYPE(ID3DXPRTBuffer);
DECLARE_DINTERFACE_TYPE(ID3DXPRTCompBuffer);
DECLARE_DINTERFACE_TYPE(ID3DXTextureGutterHelper);
DECLARE_DINTERFACE_TYPE(ID3DXPRTEngine);
typedef LPD3DXFILL2D TD3DXFill2D;
typedef LPD3DXFILL3D TD3DXFill3D;
DECLARE_DINTERFACE_TYPE(ID3DXAnimationSet);
DECLARE_DINTERFACE_TYPE(ID3DXKeyframedAnimationSet);
DECLARE_DINTERFACE_TYPE(ID3DXCompressedAnimationSet);
DECLARE_DINTERFACE_TYPE(ID3DXAnimationController);
}	/* namespace D3dx9 */
}	/* namespace Winapi */

namespace Winapi
{
namespace D3dx9
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3DXFLOAT16 *PD3DXFloat16;

typedef D3DXFLOAT16 TD3DXFloat16;

typedef D3DXVECTOR2 *PD3DXVector2;

typedef D3DXVECTOR2 TD3DXVector2;

typedef D3DXVECTOR2_16F TD3DXVector2_16F;

typedef _D3DVECTOR TD3DXVector3;

typedef D3DXVECTOR3_16F *PD3DXVector3_16F;

typedef D3DXVECTOR3_16F TD3DXVector3_16F;

typedef D3DXVECTOR4 *PD3DXVector4;

typedef D3DXVECTOR4 TD3DXVector4;

typedef D3DXVECTOR4_16F *PD3DXVector4_16F;

typedef D3DXVECTOR4_16F TD3DXVector4_16F;

typedef _D3DMATRIX *PD3DXMatrix;

typedef PD3DXMatrix *PPD3DXMatrix;

typedef _D3DMATRIX TD3DXMatrix;

typedef _D3DMATRIX *PD3DXMatrixA16;

typedef _D3DMATRIX TD3DXMatrixA16;

typedef D3DXQUATERNION *PD3DXQuaternion;

typedef D3DXQUATERNION TD3DXQuaternion;

typedef D3DXPLANE *PD3DXPlane;

typedef D3DXPLANE TD3DXPlane;

typedef _D3DCOLORVALUE TD3DXColor;

typedef _di_ID3DXBuffer *PID3DXBuffer;

typedef _D3DXFONT_DESCA *PD3DXFontDescA;

typedef _D3DXFONT_DESCW *PD3DXFontDescW;

typedef PD3DXFontDescW PD3DXFontDesc;

typedef _D3DXFONT_DESCA TD3DXFontDescA;

typedef _D3DXFONT_DESCW TD3DXFontDescW;

typedef _D3DXFONT_DESCW TD3DXFontDesc;

typedef _D3DXRTS_DESC *PD3DXRTSDesc;

typedef _D3DXRTS_DESC TD3DXRTSDesc;

typedef _D3DXRTE_DESC *PD3DXRTEDesc;

typedef _D3DXRTE_DESC TD3DXRTEDesc;

typedef NativeUInt TD3DXHandle;

typedef _D3DXMACRO *PD3DXMacro;

typedef _D3DXMACRO TD3DXMacro;

typedef _D3DXSEMANTIC *PD3DXSemantic;

typedef _D3DXSEMANTIC TD3DXSemantic;

typedef _D3DXFRAGMENT_DESC *PD3DXFragmentDesc;

typedef _D3DXFRAGMENT_DESC TD3DXFragmentDesc;

typedef _D3DXREGISTER_SET TD3DXRegisterSet;

typedef _D3DXPARAMETER_CLASS TD3DXParameterClass;

typedef _D3DXPARAMETER_TYPE TD3DXParameterType;

typedef _D3DXCONSTANTTABLE_DESC *PD3DXConstantTableDesc;

typedef _D3DXCONSTANTTABLE_DESC TD3DXConstantTableDesc;

typedef _D3DXCONSTANT_DESC *PD3DXConstantDesc;

typedef _D3DXCONSTANT_DESC TD3DXConstantDesc;

typedef _di_ID3DXConstantTable *PID3DXConstantTable;

typedef _D3DXINCLUDE_TYPE *PD3DXIncludeType;

typedef _D3DXINCLUDE_TYPE TD3DXIncludeType;

typedef ID3DXInclude* *PID3DXInclude;

typedef _D3DXSHADER_CONSTANTTABLE *PD3DXShaderConstantTable;

typedef _D3DXSHADER_CONSTANTTABLE TD3DXShaderConstantTable;

typedef _D3DXSHADER_CONSTANTINFO *PD3DXShaderConstantInfo;

typedef _D3DXSHADER_CONSTANTINFO TD3DXShaderConstantInfo;

typedef _D3DXSHADER_TYPEINFO *PD3DXShaderTypeInfo;

typedef _D3DXSHADER_TYPEINFO TD3DXShaderTypeInfo;

typedef _D3DXSHADER_STRUCTMEMBERINFO *PD3DXShaderStructMemberInfo;

typedef _D3DXSHADER_STRUCTMEMBERINFO TD3DXShaderStructMemberInfo;

typedef _D3DXEFFECT_DESC TD3DXEffectDesc;

typedef _D3DXPARAMETER_DESC *PD3DXParameterDesc;

typedef _D3DXPARAMETER_DESC TD3DXParameterDesc;

typedef _D3DXTECHNIQUE_DESC *PD3DXTechniqueDesc;

typedef _D3DXTECHNIQUE_DESC TD3DXTechniqueDesc;

typedef _D3DXPASS_DESC *PD3DXPassDesc;

typedef _D3DXPASS_DESC TD3DXPassDesc;

typedef _D3DXFUNCTION_DESC *PD3DXFunctionDesc;

typedef _D3DXFUNCTION_DESC TD3DXFunctionDesc;

typedef unsigned TD3DXFFileFormat;

typedef unsigned TD3DXFFileSaveOptions;

typedef unsigned TD3DXFFileLoadOptions;

typedef _D3DXF_FILELOADRESOURCE *PD3DXFFileLoadResource;

typedef _D3DXF_FILELOADRESOURCE TD3DXFFileLoadResource;

typedef _D3DXF_FILELOADMEMORY *PD3DXFFileLoadMemory;

typedef _D3DXF_FILELOADMEMORY TD3DXFFileLoadMemory;

typedef _D3DXPATCHMESHTYPE TD3DXPatchMeshType;

typedef _D3DXMESH TD3DXMesh;

typedef _D3DXPATCHMESH TD3DXPatchMesh;

typedef _D3DXMESHSIMP TD3DXMeshSimp;

typedef _D3DXCLEANTYPE TD3DXCleanType;

typedef System::StaticArray<_D3DVERTEXELEMENT9, 65> TFVFDeclaration;

typedef unsigned D3DXTANGENT;

typedef unsigned TD3DXTangent;

typedef _D3DXIMT TD3DXIMT;

typedef _D3DXUVATLAS TD3DXUVAtlas;

typedef _D3DXATTRIBUTERANGE *PD3DXAttributeRange;

typedef _D3DXATTRIBUTERANGE TD3DXAttributeRange;

typedef _D3DXMATERIAL *PD3DXMaterial;

typedef _D3DXMATERIAL TD3DXMaterial;

typedef _D3DXEFFECTDEFAULTTYPE TD3DXEffectDefaultType;

typedef _D3DXEFFECTDEFAULT *PD3DXEffectDefault;

typedef _D3DXEFFECTDEFAULT TD3DXEffectDefault;

typedef _D3DXEFFECTINSTANCE *PD3DXEffectInstance;

typedef _D3DXEFFECTINSTANCE TD3DXEffectInstance;

typedef _D3DXATTRIBUTEWEIGHTS *PD3DXAttributeWeights;

typedef _D3DXATTRIBUTEWEIGHTS TD3DXAttributeWeights;

typedef _D3DXWELDEPSILONSFLAGS TD3DXWeldEpsilonsFlags;

typedef _D3DXWELDEPSILONS *PD3DXWeldEpsilons;

typedef _D3DXWELDEPSILONS TD3DXWeldEpsilons;

typedef _di_ID3DXMesh *PID3DXMesh;

typedef _D3DXMESHOPT TD3DXMeshOpt;

typedef _D3DXBONECOMBINATION *PD3DXBoneCombination;

typedef _D3DXBONECOMBINATION TD3DXBoneCombination;

typedef _D3DXPATCHINFO *PD3DXPatchInfo;

typedef _D3DXPATCHINFO TD3DXPatchInfo;

typedef _D3DXINTERSECTINFO *PD3DXIntersectInfo;

typedef _D3DXINTERSECTINFO TD3DXIntersectInfo;

typedef _D3DXSHCOMPRESSQUALITYTYPE *PD3DXSHCompressQualityType;

typedef _D3DXSHCOMPRESSQUALITYTYPE TD3DXSHCompressQualityType;

typedef unsigned TD3DXSHGPUSimOpt;

typedef _D3DXSHMATERIAL *PD3DXSHMaterial;

typedef PD3DXSHMaterial *PPD3DXSHMaterial;

typedef _D3DXSHMATERIAL TD3DXSHMaterial;

typedef _D3DXSHPRTSPLITMESHVERTDATA *PD3DXSHPRTSplitMeshVertData;

typedef _D3DXSHPRTSPLITMESHVERTDATA TD3DXSHPRTSplitMeshVertData;

typedef _D3DXSHPRTSPLITMESHCLUSTERDATA *PD3DXSHPRTSplitMeshClusterData;

typedef _D3DXSHPRTSPLITMESHCLUSTERDATA TD3DXSHPRTSplitMeshClusterData;

typedef _XFILECOMPRESSEDANIMATIONSET *PXFileCompressedAnimationSet;

typedef _XFILECOMPRESSEDANIMATIONSET TXFileCompressedAnimationSet;

typedef _D3DXIMAGE_FILEFORMAT *PD3DXImageFileFormat;

typedef _D3DXIMAGE_FILEFORMAT TD3DXImageFileFormat;

typedef _D3DXIMAGE_INFO *PD3DXImageInfo;

typedef _D3DXIMAGE_INFO TD3DXImageInfo;

typedef _D3DXMESHDATATYPE TD3DXMeshDataType;

typedef _D3DXMESHDATA *PD3DXMeshData;

typedef _D3DXMESHDATA TD3DXMeshData;

typedef _D3DXMESHCONTAINER *PD3DXMeshContainer;

typedef _D3DXMESHCONTAINER TD3DXMeshContainer;

typedef _D3DXFRAME *PD3DXFrame;

typedef _D3DXFRAME TD3DXFrame;

typedef _D3DXCALLBACK_SEARCH_FLAGS *PD3DXCallbackSearchFlags;

typedef _D3DXCALLBACK_SEARCH_FLAGS TD3DXCallbackSearchFlags;

typedef _D3DXPLAYBACK_TYPE *PD3DXPlaybackType;

typedef _D3DXPLAYBACK_TYPE TD3DXPlaybackType;

typedef _D3DXKEY_VECTOR3 *PD3DXKeyVector3;

typedef _D3DXKEY_VECTOR3 TD3DXKeyVector3;

typedef _D3DXKEY_QUATERNION *PD3DXKeyQuaternion;

typedef _D3DXKEY_QUATERNION TD3DXKeyQuaternion;

typedef _D3DXKEY_CALLBACK *PD3DXKeyCallback;

typedef _D3DXKEY_CALLBACK TD3DXKeyCallback;

typedef _D3DXCOMPRESSION_FLAGS *PD3DXCompressionFlags;

typedef _D3DXCOMPRESSION_FLAGS TD3DXCompressionFlags;

typedef _D3DXPRIORITY_TYPE *PD3DXPriorityType;

typedef _D3DXPRIORITY_TYPE TD3DXPriorityType;

typedef _D3DXTRACK_DESC *PD3DXTrackDesc;

typedef _D3DXTRACK_DESC TD3DXTrackDesc;

typedef _D3DXEVENT_TYPE *PD3DXEventType;

typedef _D3DXEVENT_TYPE TD3DXEventType;

typedef _D3DXTRANSITION_TYPE *PD3DXTransitionType;

typedef _D3DXTRANSITION_TYPE TD3DXTransitionType;

typedef _D3DXEVENT_DESC *PD3DXEventDesc;

typedef _D3DXEVENT_DESC TD3DXEventDesc;

typedef unsigned TD3DXEventHandle;

typedef unsigned *PD3DXEventHandle;

//-- var, const, procedure ---------------------------------------------------
#define d3dx9MicrosoftDLL L"d3dx9_33.dll"
#define d3dx9MicrosoftDebugDLL L"d3dx9d_33.dll"
#define d3dx9BorlandDLL L"d3dx9_33.dll"
#define d3dx9dll L"d3dx9_33.dll"
#define d3dx9mathDLL L"d3dx9_33.dll"
#define d3dx9coreDLL L"d3dx9_33.dll"
#define d3dx9shaderDLL L"d3dx9_33.dll"
#define d3dx9effectDLL L"d3dx9_33.dll"
#define d3dx9meshDLL L"d3dx9_33.dll"
#define d3dx9shapesDLL L"d3dx9_33.dll"
#define d3dx9texDLL L"d3dx9_33.dll"
#define d3dx9animDLL L"d3dx9_33.dll"
extern DELPHI_PACKAGE D3DXFLOAT16 D3DXFloat16Zero;
extern DELPHI_PACKAGE D3DXVECTOR2 D3DXVector2Zero;
extern DELPHI_PACKAGE D3DXVECTOR2_16F D3DXVector2_16fZero;
extern DELPHI_PACKAGE _D3DVECTOR D3DXVector3Zero;
extern DELPHI_PACKAGE D3DXVECTOR3_16F D3DXVector3_16fZero;
extern DELPHI_PACKAGE D3DXVECTOR4 D3DXVector4Zero;
extern DELPHI_PACKAGE D3DXVECTOR4_16F D3DXVector4_16fZero;
extern DELPHI_PACKAGE D3DXPLANE D3DXPlaneZero;
static const int MAKE_D3DXFERR_D = int(-2005532672);
extern DELPHI_PACKAGE bool __fastcall D3DXFloat16Equal(const D3DXFLOAT16 v1, const D3DXFLOAT16 v2);
extern DELPHI_PACKAGE float __fastcall D3DXFloat16ToFloat(D3DXFLOAT16 value);
extern DELPHI_PACKAGE bool __fastcall D3DXVector2Equal(const D3DXVECTOR2 &v1, const D3DXVECTOR2 &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector2_16fEqual(const D3DXVECTOR2_16F v1, const D3DXVECTOR2_16F v2);
extern DELPHI_PACKAGE D3DXVECTOR2_16F __fastcall D3DXVector2_16fFromVector2(const D3DXVECTOR2 &v);
extern DELPHI_PACKAGE D3DXVECTOR2 __fastcall D3DXVector2FromVector2_16f(const D3DXVECTOR2_16F v);
extern DELPHI_PACKAGE bool __fastcall D3DXVector3Equal(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector3_16fEqual(const D3DXVECTOR3_16F &v1, const D3DXVECTOR3_16F &v2);
extern DELPHI_PACKAGE D3DXVECTOR3_16F __fastcall D3DXVector3_16fFromVector3(const _D3DVECTOR &v);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall D3DXVector3FromVector3_16f(const D3DXVECTOR3_16F &v);
extern DELPHI_PACKAGE bool __fastcall D3DXVector4Equal(const D3DXVECTOR4 &v1, const D3DXVECTOR4 &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector4_16fEqual(const D3DXVECTOR4_16F &v1, const D3DXVECTOR4_16F &v2);
extern DELPHI_PACKAGE D3DXVECTOR4_16F __fastcall D3DXVector4_16fFromVector4(const D3DXVECTOR4 &v);
extern DELPHI_PACKAGE D3DXVECTOR4 __fastcall D3DXVector4FromVector4_16f(const D3DXVECTOR4_16F &v);
extern DELPHI_PACKAGE PD3DXMatrix __fastcall D3DXMatrixAdd(/* out */ _D3DMATRIX &mOut, const _D3DMATRIX &m1, const _D3DMATRIX &m2);
extern DELPHI_PACKAGE PD3DXMatrix __fastcall D3DXMatrixSubtract(/* out */ _D3DMATRIX &mOut, const _D3DMATRIX &m1, const _D3DMATRIX &m2);
extern DELPHI_PACKAGE PD3DXMatrix __fastcall D3DXMatrixMul(/* out */ _D3DMATRIX &mOut, const _D3DMATRIX &m, float MulBy);
extern DELPHI_PACKAGE bool __fastcall D3DXMatrixEqual(const _D3DMATRIX &m1, const _D3DMATRIX &m2);
extern DELPHI_PACKAGE D3DXQUATERNION __fastcall D3DXQuaternionAdd(const D3DXQUATERNION &q1, const D3DXQUATERNION &q2);
extern DELPHI_PACKAGE D3DXQUATERNION __fastcall D3DXQuaternionSubtract(const D3DXQUATERNION &q1, const D3DXQUATERNION &q2);
extern DELPHI_PACKAGE bool __fastcall D3DXQuaternionEqual(const D3DXQUATERNION &q1, const D3DXQUATERNION &q2);
extern DELPHI_PACKAGE PD3DXQuaternion __fastcall D3DXQuaternionScale(/* out */ D3DXQUATERNION &qOut, const D3DXQUATERNION &q, float s);
extern DELPHI_PACKAGE bool __fastcall D3DXPlaneEqual(const D3DXPLANE &p1, const D3DXPLANE &p2);
extern DELPHI_PACKAGE unsigned __fastcall D3DXColorToDWord(const _D3DCOLORVALUE &c);
extern DELPHI_PACKAGE _D3DCOLORVALUE __fastcall D3DXColorFromDWord(unsigned c);
extern DELPHI_PACKAGE bool __fastcall D3DXColorEqual(const _D3DCOLORVALUE &c1, const _D3DCOLORVALUE &c2);
}	/* namespace D3dx9 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3DX9)
using namespace Winapi::D3dx9;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3dx9HPP
