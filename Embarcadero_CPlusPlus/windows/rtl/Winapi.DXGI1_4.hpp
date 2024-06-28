// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DXGI1_4.pas' rev: 34.00 (Windows)

#ifndef Winapi_Dxgi1_4HPP
#define Winapi_Dxgi1_4HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.DXGI1_2.hpp>
#include <Winapi.DXGI1_3.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.DxgiType.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "dxgi1_4.h"
DECLARE_DINTERFACE_TYPE(IDXGISwapChain3);
DECLARE_DINTERFACE_TYPE(IDXGIOutput4);
DECLARE_DINTERFACE_TYPE(IDXGIFactory4);
DECLARE_DINTERFACE_TYPE(IDXGIAdapter3);

namespace Winapi
{
namespace Dxgi1_4
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef DXGI_SWAP_CHAIN_COLOR_SPACE_SUPPORT_FLAG TDXGISwapChainColorSpaceSupportFlag;

typedef DXGI_OVERLAY_COLOR_SPACE_SUPPORT_FLAG TDXGIOverlayColorSpaceSupportFlag;

typedef DXGI_MEMORY_SEGMENT_GROUP TDXGIMemorySegmentGroup;

typedef DXGI_QUERY_VIDEO_MEMORY_INFO TDXGIQueryVideoMemoryInfo;

typedef DXGI_QUERY_VIDEO_MEMORY_INFO *PDXGIQueryVideoMemoryInfo;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dxgi1_4 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DXGI1_4)
using namespace Winapi::Dxgi1_4;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Dxgi1_4HPP
