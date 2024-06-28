// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3DX8.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3dx8HPP
#define Winapi_D3dx8HPP

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
#include <Winapi.Direct3D8.hpp>
#include <Winapi.DXTypes.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3dx8.h"
#include "dxfile.h"
namespace D3dx8
{
typedef D3DXVECTOR2 TD3DXVector2;
typedef D3DXVECTOR2 *PD3DXVector2;
typedef D3DXVECTOR3 TD3DXVector3;
typedef D3DXVECTOR3 *PD3DXVector3;
typedef D3DXVECTOR4 TD3DXVector4;
typedef D3DXVECTOR4 *PD3DXVector4;
typedef D3DXMATRIX TD3DXMatrix;
typedef D3DXMATRIX *PD3DXMatrix;
typedef D3DXQUATERNION TD3DXQuaternion;
typedef D3DXPLANE TD3DXPlane;
typedef D3DXCOLOR TD3DXColor;
typedef D3DXCOLOR *PD3DXColor;
DECLARE_DINTERFACE_TYPE(ID3DXMatrixStack);
DECLARE_DINTERFACE_TYPE(ID3DXBuffer);
DECLARE_DINTERFACE_TYPE(ID3DXFont);
DECLARE_DINTERFACE_TYPE(ID3DXSprite);
DECLARE_DINTERFACE_TYPE(ID3DXRenderToSurface);
DECLARE_DINTERFACE_TYPE(ID3DXRenderToEnvMap);
DECLARE_DINTERFACE_TYPE(ID3DXEffect);
DECLARE_DINTERFACE_TYPE(ID3DXBaseMesh);
DECLARE_DINTERFACE_TYPE(ID3DXMesh);
DECLARE_DINTERFACE_TYPE(ID3DXPMesh);
DECLARE_DINTERFACE_TYPE(ID3DXSPMesh);
DECLARE_DINTERFACE_TYPE(ID3DXSkinMesh);
}  /* namespace D3dx8 */

namespace Winapi
{
namespace D3dx8
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _D3DMATRIX *PD3DXMatrixA16;

typedef _D3DMATRIX TD3DXMatrixA16;

typedef TD3DXQuaternion *PD3DXQuaternion;

typedef TD3DXPlane *PD3DXPlane;

typedef _di_ID3DXBuffer *PID3DXBuffer;

typedef _D3DXRTS_DESC *PD3DXRTSDesc;

typedef _D3DXRTS_DESC TD3DXRTSDesc;

typedef _D3DXRTE_DESC *PD3DXRTEDesc;

typedef _D3DXRTE_DESC TD3DXRTEDesc;

typedef _D3DXPARAMETERTYPE TD3DXParameterType;

typedef _D3DXEFFECT_DESC *PD3DXEffectDesc;

typedef _D3DXEFFECT_DESC TD3DXEffectDesc;

typedef _D3DXPARAMETER_DESC *PD3DXParameterDesc;

typedef _D3DXPARAMETER_DESC TD3DXParameterDesc;

typedef _D3DXTECHNIQUE_DESC *PD3DXTechniqueDesc;

typedef _D3DXTECHNIQUE_DESC TD3DXTechniqueDesc;

typedef _D3DXPASS_DESC *PD3DXPassDesc;

typedef _D3DXPASS_DESC TD3DXPassDesc;

typedef _D3DXMESH TD3DXMesh;

typedef _D3DXMESHSIMP TD3DMeshSimp;

typedef System::StaticArray<unsigned, 20> TFVFDeclaration;

typedef _D3DXATTRIBUTERANGE *PD3DXAttributeRange;

typedef _D3DXATTRIBUTERANGE TD3DXAttributeRange;

typedef D3DXMATERIAL *PD3DXMaterial;

typedef D3DXMATERIAL TD3DXMaterial;

typedef _D3DXATTRIBUTEWEIGHTS *PD3DXAttributeWeights;

typedef _D3DXATTRIBUTEWEIGHTS TD3DXAttributeWeights;

typedef _D3DXWELDEPSILONSFLAGS TD3DXWeldEpsilonsFlags;

typedef _D3DXWELDEPSILONS *PD3DXWeldEpsilons;

typedef _D3DXWELDEPSILONS TD3DXWeldEpsilons;

typedef _D3DXMESHOPT TD3DXMeshOpt;

typedef _D3DXBONECOMBINATION *PD3DXBoneCombination;

typedef _D3DXBONECOMBINATION TD3DXBoneCombination;

typedef _D3DXINTERSECTINFO *PD3DXIntersectInfo;

typedef _D3DXINTERSECTINFO TD3DXIntersectInfo;

typedef _D3DXIMAGE_FILEFORMAT *PD3DXImageFileFormat;

typedef _D3DXIMAGE_FILEFORMAT TD3DXImageFileFormat;

typedef LPD3DXFILL2D TD3DXFill2D;

typedef LPD3DXFILL3D TD3DXFill3D;

typedef _D3DXIMAGE_INFO *PD3DXImageInfo;

typedef _D3DXIMAGE_INFO TD3DXImageInfo;

typedef PD3DXEffectDesc PD3DXEffect_Desc;

typedef PD3DXImageInfo PD3DXImage_Info;

typedef PD3DXParameterDesc PD3DXParameter_Desc;

typedef PD3DXPassDesc PD3DXPass_Desc;

typedef PD3DXRTEDesc PD3DXRTE_Desc;

typedef PD3DXRTSDesc PD3DXRTS_Desc;

typedef PD3DXTechniqueDesc PD3DXTechnique_Desc;

typedef _D3DXEFFECT_DESC TD3DXEffect_Desc;

typedef _D3DXIMAGE_INFO TD3DXImage_Info;

typedef _D3DXPARAMETER_DESC TD3DXParameter_Desc;

typedef _D3DXPASS_DESC TD3DXPass_Desc;

typedef _D3DXRTE_DESC TD3DXRTE_Desc;

typedef _D3DXRTS_DESC TD3DXRTS_Desc;

typedef _D3DXTECHNIQUE_DESC TD3DXTechnique_Desc;

typedef PD3DXImageFileFormat PD3DXImage_FileFormat;

typedef _D3DXIMAGE_FILEFORMAT TD3DXImage_FileFormat;

//-- var, const, procedure ---------------------------------------------------
#define d3dx8dll L"D3DX81ab.dll"
extern DELPHI_PACKAGE TD3DXVector2 D3DXVector2Zero;
extern DELPHI_PACKAGE _D3DVECTOR D3DXVector3Zero;
extern DELPHI_PACKAGE TD3DXVector4 D3DXVector4Zero;
extern DELPHI_PACKAGE TD3DXPlane D3DXPlaneZero;
extern DELPHI_PACKAGE TD3DXVector2 __fastcall D3DXVector2(float _x, float _y);
extern DELPHI_PACKAGE bool __fastcall D3DXVector2Equal(const TD3DXVector2 &v1, const TD3DXVector2 &v2);
extern DELPHI_PACKAGE _D3DVECTOR __fastcall D3DXVector3(float _x, float _y, float _z);
extern DELPHI_PACKAGE bool __fastcall D3DXVector3Equal(const _D3DVECTOR &v1, const _D3DVECTOR &v2);
extern DELPHI_PACKAGE TD3DXVector4 __fastcall D3DXVector4(float _x, float _y, float _z, float _w);
extern DELPHI_PACKAGE bool __fastcall D3DXVector4Equal(const TD3DXVector4 &v1, const TD3DXVector4 &v2);
extern DELPHI_PACKAGE _D3DMATRIX __fastcall D3DXMatrix(float _m00, float _m01, float _m02, float _m03, float _m10, float _m11, float _m12, float _m13, float _m20, float _m21, float _m22, float _m23, float _m30, float _m31, float _m32, float _m33);
extern DELPHI_PACKAGE PD3DXMatrix __fastcall D3DXMatrixAdd(/* out */ _D3DMATRIX &mOut, const _D3DMATRIX &m1, const _D3DMATRIX &m2);
extern DELPHI_PACKAGE PD3DXMatrix __fastcall D3DXMatrixSubtract(/* out */ _D3DMATRIX &mOut, const _D3DMATRIX &m1, const _D3DMATRIX &m2);
extern DELPHI_PACKAGE PD3DXMatrix __fastcall D3DXMatrixMul(/* out */ _D3DMATRIX &mOut, const _D3DMATRIX &m, float MulBy);
extern DELPHI_PACKAGE bool __fastcall D3DXMatrixEqual(const _D3DMATRIX &m1, const _D3DMATRIX &m2);
extern DELPHI_PACKAGE TD3DXQuaternion __fastcall D3DXQuaternion(float _x, float _y, float _z, float _w);
extern DELPHI_PACKAGE TD3DXQuaternion __fastcall D3DXQuaternionAdd(const TD3DXQuaternion &q1, const TD3DXQuaternion &q2);
extern DELPHI_PACKAGE TD3DXQuaternion __fastcall D3DXQuaternionSubtract(const TD3DXQuaternion &q1, const TD3DXQuaternion &q2);
extern DELPHI_PACKAGE bool __fastcall D3DXQuaternionEqual(const TD3DXQuaternion &q1, const TD3DXQuaternion &q2);
extern DELPHI_PACKAGE PD3DXQuaternion __fastcall D3DXQuaternionScale(/* out */ TD3DXQuaternion &qOut, const TD3DXQuaternion &q, float s);
extern DELPHI_PACKAGE TD3DXPlane __fastcall D3DXPlane(float _a, float _b, float _c, float _d);
extern DELPHI_PACKAGE bool __fastcall D3DXPlaneEqual(const TD3DXPlane &p1, const TD3DXPlane &p2);
extern DELPHI_PACKAGE _D3DCOLORVALUE __fastcall D3DXColor(float _r, float _g, float _b, float _a);
extern DELPHI_PACKAGE unsigned __fastcall D3DXColorToDWord(const _D3DCOLORVALUE &c);
extern DELPHI_PACKAGE _D3DCOLORVALUE __fastcall D3DXColorFromDWord(unsigned c);
extern DELPHI_PACKAGE bool __fastcall D3DXColorEqual(const _D3DCOLORVALUE &c1, const _D3DCOLORVALUE &c2);
}	/* namespace D3dx8 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3DX8)
using namespace Winapi::D3dx8;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3dx8HPP
