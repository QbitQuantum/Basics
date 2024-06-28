// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DXGI1_2.pas' rev: 34.00 (Windows)

#ifndef Winapi_Dxgi1_2HPP
#define Winapi_Dxgi1_2HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.DxgiType.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "dxgi1_2.h"
DECLARE_DINTERFACE_TYPE(IDXGIDisplayControl);
DECLARE_DINTERFACE_TYPE(IDXGIOutputDuplication);
DECLARE_DINTERFACE_TYPE(IDXGIResource1);
DECLARE_DINTERFACE_TYPE(IDXGIDevice2);
DECLARE_DINTERFACE_TYPE(IDXGISwapChain1);
DECLARE_DINTERFACE_TYPE(IDXGIFactory2);
DECLARE_DINTERFACE_TYPE(IDXGIAdapter2);
DECLARE_DINTERFACE_TYPE(IDXGIOutput1);

namespace Winapi
{
namespace Dxgi1_2
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IDXGISurface2;
typedef System::DelphiInterface<IDXGISurface2> _di_IDXGISurface2;
//-- type declarations -------------------------------------------------------
typedef DXGI_OUTDUPL_MOVE_RECT TDXGIOutduplMoveRect;

typedef DXGI_OUTDUPL_MOVE_RECT *PDXGIOutduplMoveRect;

typedef DXGI_OUTDUPL_DESC TDXGIOutduplDesc;

typedef DXGI_OUTDUPL_DESC *PDXGIOutduplDesc;

typedef DXGI_OUTDUPL_POINTER_POSITION TDXGIOutduplPointerPosition;

typedef DXGI_OUTDUPL_POINTER_POSITION *PDXGIOutduplPointerPosition;

typedef DXGI_OUTDUPL_POINTER_SHAPE_TYPE TDXGIOutduplPointerShapeType;

typedef DXGI_OUTDUPL_POINTER_SHAPE_INFO TDXGIOutduplPointerShapeInfo;

typedef DXGI_OUTDUPL_POINTER_SHAPE_INFO *PDXGIOutduplPointerShapeInfo;

typedef DXGI_OUTDUPL_FRAME_INFO TDXGIOutduplFrameInfo;

typedef DXGI_OUTDUPL_FRAME_INFO *PDXGIOutduplFrameInfo;

typedef DXGI_ALPHA_MODE TDXGIAlphaMode;

typedef _di_IDXGISurface2 IID_IDXGISurface2;

__interface  INTERFACE_UUID("{ABA496DD-B617-4CB8-A866-BC44D7EB1FA2}") IDXGISurface2  : public IDXGISurface1 
{
	virtual HRESULT __stdcall GetResource(const GUID &riid, /* out */ void *ppParentResource, /* out */ unsigned &pSubresourceIndex) = 0 ;
};

typedef _DXGI_OFFER_RESOURCE_PRIORITY T_DXGIOfferResourcePriority;

typedef _DXGI_OFFER_RESOURCE_PRIORITY *P_DXGIOfferResourcePriority;

typedef _DXGI_OFFER_RESOURCE_PRIORITY TDXGIOfferResourcePriority;

typedef DXGI_MODE_DESC1 TDXGIModeDesc1;

typedef DXGI_MODE_DESC1 *PDXGIModeDesc1;

typedef DXGI_SCALING TDXGIScaling;

typedef DXGI_SWAP_CHAIN_DESC1 TDXGISwapChainDesc1;

typedef DXGI_SWAP_CHAIN_DESC1 *PDXGISwapChainDesc1;

typedef DXGI_SWAP_CHAIN_FULLSCREEN_DESC TDXGISwapChainFullscreenDesc;

typedef DXGI_SWAP_CHAIN_FULLSCREEN_DESC *PDXGISwapChainFullscreenDesc;

typedef DXGI_PRESENT_PARAMETERS TDXGIPresentParameters;

typedef DXGI_PRESENT_PARAMETERS *PDXGIPresentParameters;

typedef DXGI_GRAPHICS_PREEMPTION_GRANULARITY TDXGIGraphicsPreemptionGranularity;

typedef DXGI_COMPUTE_PREEMPTION_GRANULARITY TDXGIComputePreemptionGranularity;

typedef DXGI_ADAPTER_DESC2 TDXGIAdapterDesc2;

typedef DXGI_ADAPTER_DESC2 *PDXGIAdapterDesc2;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dxgi1_2 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DXGI1_2)
using namespace Winapi::Dxgi1_2;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Dxgi1_2HPP
