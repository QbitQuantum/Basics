// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D11_2.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d11_2HPP
#define Winapi_D3d11_2HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.D3D11_1.hpp>
#include <Winapi.D3D11.hpp>
#include <Winapi.D3DCommon.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "d3d11_2.h"
DECLARE_DINTERFACE_TYPE(ID3D11DeviceContext);
DECLARE_DINTERFACE_TYPE(ID3D11Device2);

namespace Winapi
{
namespace D3d11_2
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D11_TILED_RESOURCE_COORDINATE TD3D11TiledResourceCoordinate;

typedef D3D11_TILED_RESOURCE_COORDINATE *PD3D11TiledResourceCoordinate;

typedef D3D11_TILE_REGION_SIZE TD3D11TileRegionSize;

typedef D3D11_TILE_REGION_SIZE *PD3D11TileRegionSize;

typedef D3D11_TILE_MAPPING_FLAG TD3D11TileMappingFlag;

typedef D3D11_TILE_MAPPING_FLAG *PD3D11TileMappingFlag;

typedef D3D11_TILE_RANGE_FLAG TD3D11TileRangeFlag;

typedef D3D11_SUBRESOURCE_TILING TD3D11SubresourceTiling;

typedef D3D11_SUBRESOURCE_TILING *PD3D11SubresourceTiling;

typedef D3D11_TILE_SHAPE TD3D11TileShape;

typedef D3D11_TILE_SHAPE *PD3D11TileShape;

typedef D3D11_PACKED_MIP_DESC TD3D11PackedMipDesc;

typedef D3D11_PACKED_MIP_DESC *PD3D11PackedMipDesc;

typedef D3D11_CHECK_MULTISAMPLE_QUALITY_LEVELS_FLAG TD3D11CheckMultisampleQualityLevelsFlag;

typedef D3D11_TILE_COPY_FLAG TD3D11TileCopyFlag;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d11_2 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D11_2)
using namespace Winapi::D3d11_2;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d11_2HPP
