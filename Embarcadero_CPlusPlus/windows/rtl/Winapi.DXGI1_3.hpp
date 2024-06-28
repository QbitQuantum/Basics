// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DXGI1_3.pas' rev: 34.00 (Windows)

#ifndef Winapi_Dxgi1_3HPP
#define Winapi_Dxgi1_3HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.DXGI1_2.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include "dxgi1_3.h"
DECLARE_DINTERFACE_TYPE(IDXGIDevice3);
DECLARE_DINTERFACE_TYPE(IDXGISwapChain2);
DECLARE_DINTERFACE_TYPE(IDXGIOutput2);
DECLARE_DINTERFACE_TYPE(IDXGIFactory3)
DECLARE_DINTERFACE_TYPE(IDXGIDecodeSwapChain);
DECLARE_DINTERFACE_TYPE(IDXGIFactoryMedia);
DECLARE_DINTERFACE_TYPE(IDXGISwapChainMedia);
DECLARE_DINTERFACE_TYPE(IDXGIOutput3)

namespace Winapi
{
namespace Dxgi1_3
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef DXGI_MATRIX_3X2_F TDXGIMatrix3x2F;

typedef DXGI_MATRIX_3X2_F *PDXGIMatrix3x2F;

typedef DXGI_DECODE_SWAP_CHAIN_DESC TDXGIDecodeSwapChainDesc;

typedef DXGI_DECODE_SWAP_CHAIN_DESC *PDXGIDecodeSwapChainDesc;

typedef DXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS TDXGI_MULTIPLANE_OVERLAY_YCbCr_FLAGS;

typedef DXGI_FRAME_PRESENTATION_MODE TDXGIFramePresentationMode;

typedef DXGI_FRAME_STATISTICS_MEDIA TDXGIFrameStatisticsMedia;

typedef DXGI_FRAME_STATISTICS_MEDIA *PDXGIFrameStatisticsMedia;

typedef DXGI_OVERLAY_SUPPORT_FLAG TDXGIOverlaySupportFlag;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dxgi1_3 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DXGI1_3)
using namespace Winapi::Dxgi1_3;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Dxgi1_3HPP
