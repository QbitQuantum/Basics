// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3DX10.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3dx10HPP
#define Winapi_D3dx10HPP

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
#include <Winapi.D3D10.hpp>
#include <Winapi.D3D10_1.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------
#include "D3DX10.h"
#include "d3dtypes.h"
typedef D3DXCOLOR TD3DXColor;
typedef D3DXCOLOR *PD3DXColor;
DECLARE_DINTERFACE_TYPE(ID3DXMatrixStack);
DECLARE_DINTERFACE_TYPE(ID3DX10Sprite);
DECLARE_DINTERFACE_TYPE(ID3DX10ThreadPump);
DECLARE_DINTERFACE_TYPE(ID3DX10Font);
DECLARE_DINTERFACE_TYPE(ID3DX10MeshBuffer);
DECLARE_DINTERFACE_TYPE(ID3DX10Mesh);
DECLARE_DINTERFACE_TYPE(ID3DX10SkinInfo);

namespace Winapi
{
namespace D3dx10
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

typedef _D3DX_CPU_OPTIMIZATION TD3DXCpuOptimization;

typedef _D3DX_CPU_OPTIMIZATION *PD3DXCpuOptimization;

typedef _D3DX10_SPRITE *PD3DX10_Sprite;

typedef _D3DX10_SPRITE TD3DX10_Sprite;

typedef _D3DX10_FONT_DESCA *PD3DX10_FontDescA;

typedef _D3DX10_FONT_DESCW *PD3DX10_FontDescW;

typedef PD3DX10_FontDescW PD3DX10_FontDesc;

typedef _D3DX10_FONT_DESCW D3DX10_FONT_DESC;

typedef _D3DX10_FONT_DESCA TD3DX10_FontDescA;

typedef _D3DX10_FONT_DESCW TD3DX10_FontDescW;

typedef _D3DX10_FONT_DESCW TD3DX10_FontDesc;

typedef D3DX10_IMAGE_FILE_FORMAT *PD3DX10ImageFileFormat;

typedef D3DX10_IMAGE_FILE_FORMAT TD3DX10ImageFileFormat;

typedef D3DX10_IMAGE_INFO *PD3DX10ImageInfo;

typedef D3DX10_IMAGE_INFO TD3DX10ImageInfo;

typedef D3DX10_IMAGE_LOAD_INFO *PD3DX10ImageLoadInfo;

typedef D3DX10_IMAGE_LOAD_INFO TD3DX10ImageLoadInfo;

typedef _D3DX10_TEXTURE_LOAD_INFO *PD3DX10_TextureLoadInfo;

typedef _D3DX10_TEXTURE_LOAD_INFO TD3DX10_TextureLoadInfo;

typedef _D3DX10_ATTRIBUTE_RANGE *PD3DX10_AttributeRange;

typedef _D3DX10_ATTRIBUTE_RANGE TD3DX10_AttributeRange;

typedef unsigned TD3DX10_MeshDiscardFlags;

typedef _D3DX10_WELD_EPSILONS *PD3DX10_WeldEpsilons;

typedef _D3DX10_WELD_EPSILONS TD3DX10_WeldEpsilons;

typedef _D3DX10_INTERSECT_INFO *PD3DX10_IntersectInfo;

typedef _D3DX10_INTERSECT_INFO TD3DX10_IntersectInfo;

typedef unsigned TD3DX10_MeshOpt;

typedef _D3DX10_SKINNING_CHANNEL *PD3DX10_SkinningChannel;

typedef _D3DX10_SKINNING_CHANNEL TD3DX10_SkinningChannel;

typedef _D3DX10_ATTRIBUTE_WEIGHTS *PD3DX10_AttributeWeights;

typedef _D3DX10_ATTRIBUTE_WEIGHTS TD3DX10_AttributeWeights;

//-- var, const, procedure ---------------------------------------------------
#define d3dx10_retail_DLL L"d3dx10_41.dll"
#define d3dx10_debug_DLL L"d3dx10d_41.dll"
#define d3dx10dll L"d3dx10_41.dll"
static const int MAKE_DDHRESULT_R = int(-2005532672);
extern DELPHI_PACKAGE D3DXFLOAT16 D3DXFloat16Zero;
extern DELPHI_PACKAGE D3DXVECTOR2 D3DXVector2Zero;
extern DELPHI_PACKAGE D3DXVECTOR2_16F D3DXVector2_16fZero;
extern DELPHI_PACKAGE _D3DVECTOR D3DXVector3Zero;
extern DELPHI_PACKAGE D3DXVECTOR3_16F D3DXVector3_16fZero;
extern DELPHI_PACKAGE D3DXVECTOR4 D3DXVector4Zero;
extern DELPHI_PACKAGE D3DXVECTOR4_16F D3DXVector4_16fZero;
extern DELPHI_PACKAGE D3DXPLANE D3DXPlaneZero;
extern DELPHI_PACKAGE D3DX10_IMAGE_LOAD_INFO D3DX10_IMAGE_LOAD_INFO_default;
extern DELPHI_PACKAGE _D3DX10_TEXTURE_LOAD_INFO D3DX10_TEXTURE_LOAD_INFO_default;
extern "C" HRESULT __stdcall D3DX10CreateAsyncResourceLoader(NativeUInt hSrcModule, System::WideChar * pSrcResource, /* out */ ID3DX10DataLoader* &ppDataLoader);
extern "C" HRESULT __stdcall D3DX10CreateAsyncResourceLoaderW(NativeUInt hSrcModule, System::WideChar * pSrcResource, /* out */ ID3DX10DataLoader* &ppDataLoader);
extern DELPHI_PACKAGE bool __fastcall D3DXFloat16Equal(const D3DXFLOAT16 v1, const D3DXFLOAT16 v2);
extern DELPHI_PACKAGE bool __fastcall D3DXFloat16NotEqual(const D3DXFLOAT16 v1, const D3DXFLOAT16 v2);
extern DELPHI_PACKAGE float __fastcall D3DXFloat16ToFloat(D3DXFLOAT16 value);
extern DELPHI_PACKAGE bool __fastcall D3DXVector2Equal(const D3DXVECTOR2 &v1, const D3DXVECTOR2 &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector2_16fEqual(const D3DXVECTOR2_16F v1, const D3DXVECTOR2_16F v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector2_16fNotEqual(const D3DXVECTOR2_16F v1, const D3DXVECTOR2_16F v2);
extern DELPHI_PACKAGE D3DXVECTOR2_16F __fastcall D3DXVector2_16fFromVector2(const D3DXVECTOR2 &v);
extern DELPHI_PACKAGE D3DXVECTOR2 __fastcall D3DXVector2FromVector2_16f(const D3DXVECTOR2_16F v);
extern DELPHI_PACKAGE bool __fastcall D3DXVector3Equal(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector3_16fEqual(const D3DXVECTOR3_16F &v1, const D3DXVECTOR3_16F &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector3_16fNotEqual(const D3DXVECTOR3_16F &v1, const D3DXVECTOR3_16F &v2);
extern DELPHI_PACKAGE D3DXVECTOR3_16F __fastcall D3DXVector3_16fFromVector3(const _D3DVECTOR &v);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall D3DXVector3FromVector3_16f(const D3DXVECTOR3_16F &v);
extern DELPHI_PACKAGE bool __fastcall D3DXVector4Equal(const D3DXVECTOR4 &v1, const D3DXVECTOR4 &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector4_16fEqual(const D3DXVECTOR4_16F &v1, const D3DXVECTOR4_16F &v2);
extern DELPHI_PACKAGE bool __fastcall D3DXVector4_16fNotEqual(const D3DXVECTOR4_16F &v1, const D3DXVECTOR4_16F &v2);
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
extern DELPHI_PACKAGE _D3DCOLORVALUE __fastcall D3DXColor(float _r, float _g, float _b, float _a);
extern DELPHI_PACKAGE unsigned __fastcall D3DXColorToDWord(const _D3DCOLORVALUE &c);
extern DELPHI_PACKAGE unsigned __fastcall D3DXColorToUINT(const _D3DCOLORVALUE &c);
extern DELPHI_PACKAGE _D3DCOLORVALUE __fastcall D3DXColorFromDWord(unsigned c);
extern DELPHI_PACKAGE _D3DCOLORVALUE __fastcall D3DXColorFromUINT(unsigned c);
extern DELPHI_PACKAGE bool __fastcall D3DXColorEqual(const _D3DCOLORVALUE &c1, const _D3DCOLORVALUE &c2);

#if defined(UNICODE)
#pragma option push -w-inl
inline HRESULT __stdcall D3DX10CreateAsyncResourceLoader(NativeUInt hSrcModule, System::WideChar * pSrcResource, /* out */ ID3DX10DataLoader* &ppDataLoader)
{
	return D3DX10CreateAsyncResourceLoaderW(hSrcModule, pSrcResource, ppDataLoader);
}
#pragma option pop

#else
#pragma option push -w-inl
inline HRESULT __stdcall D3DX10CreateAsyncResourceLoader(NativeUInt hSrcModule, System::WideChar * pSrcResource, /* out */ ID3DX10DataLoader* &ppDataLoader)
{
	return D3DX10CreateAsyncResourceLoaderA(hSrcModule, pSrcResource, ppDataLoader);
}
#pragma option pop

#endif

}	/* namespace D3dx10 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3DX10)
using namespace Winapi::D3dx10;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3dx10HPP
