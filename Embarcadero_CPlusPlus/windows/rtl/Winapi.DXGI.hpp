// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DXGI.pas' rev: 34.00 (Windows)

#ifndef Winapi_DxgiHPP
#define Winapi_DxgiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.MultiMon.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.DXTypes.hpp>
#include <Winapi.DxgiFormat.hpp>
#include <Winapi.DxgiType.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
#include "DXGI.h"
DECLARE_DINTERFACE_TYPE(IDXGIObject);
DECLARE_DINTERFACE_TYPE(IDXGIDeviceSubObject);
DECLARE_DINTERFACE_TYPE(IDXGIResource);
DECLARE_DINTERFACE_TYPE(IDXGIKeyedMutex);
DECLARE_DINTERFACE_TYPE(IDXGISurface);
DECLARE_DINTERFACE_TYPE(IDXGISurface1);
DECLARE_DINTERFACE_TYPE(IDXGIAdapter);
DECLARE_DINTERFACE_TYPE(IDXGIOutput);
DECLARE_DINTERFACE_TYPE(IDXGISwapChain);
DECLARE_DINTERFACE_TYPE(IDXGIFactory);
DECLARE_DINTERFACE_TYPE(IDXGIDevice);
DECLARE_DINTERFACE_TYPE(IDXGIFactory1);
DECLARE_DINTERFACE_TYPE(IDXGIAdapter1);
DECLARE_DINTERFACE_TYPE(IDXGIDevice1);

namespace Winapi
{
namespace Dxgi
{
//-- forward type declarations -----------------------------------------------
struct DXGI_DISPLAY_COLOR_SPACE;
//-- type declarations -------------------------------------------------------
typedef DXGI_USAGE TDXGIUsage;

typedef DXGI_FRAME_STATISTICS TDXGIFrameStatistics;

typedef DXGI_FRAME_STATISTICS *PDXGIFrameStatistics;

typedef DXGI_MAPPED_RECT TDXGIMappedRect;

typedef DXGI_MAPPED_RECT *PDXGIMappedRect;

typedef DXGI_ADAPTER_DESC TDXGIAdapterDesc;

typedef DXGI_ADAPTER_DESC *PDXGIAdapterDesc;

typedef DXGI_OUTPUT_DESC TDXGIOutputDesc;

typedef DXGI_OUTPUT_DESC *PDXGIOutputDesc;

typedef DXGI_SHARED_RESOURCE TDXGISharedResource;

typedef DXGI_SHARED_RESOURCE *PDXGISharedResource;

typedef DXGI_RESIDENCY TDXGIResidency;

typedef DXGI_RESIDENCY *PDXGIResidency;

typedef DXGI_SURFACE_DESC TDXGISurfaceDesc;

typedef DXGI_SURFACE_DESC *PDXGISurfaceDesc;

typedef DXGI_SWAP_EFFECT TDXGISwapEffect;

typedef DXGI_SWAP_CHAIN_FLAG TDXGISwapChainFlag;

typedef DXGI_SWAP_CHAIN_DESC TDXGISwapChainDesc;

typedef DXGI_SWAP_CHAIN_DESC *PDXGISwapChainDesc;

typedef _di_IDXGIObject IID_IDXGIObject;

typedef _di_IDXGIDeviceSubObject IID_IDXGIDeviceSubObject;

typedef _di_IDXGIResource IID_IDXGIResource;

typedef _di_IDXGIKeyedMutex IID_IDXGIKeyedMutex;

typedef _di_IDXGISurface IID_IDXGISurface;

typedef _di_IDXGISurface1 IID_IDXGISurface1;

typedef _di_IDXGIAdapter IID_IDXGIAdapter;

typedef _di_IDXGIOutput IID_IDXGIOutput;

typedef _di_IDXGISwapChain IID_IDXGISwapChain;

typedef _di_IDXGIFactory IID_IDXGIFactory;

typedef System::_di_IInterface *PIUnknown;

typedef _di_IDXGIDevice IID_IDXGIDevice;

typedef DXGI_ADAPTER_FLAG TDXGIAdapterFlag;

typedef DXGI_ADAPTER_FLAG *PDXGIAdapterFlag;

typedef DXGI_ADAPTER_DESC1 TDXGIAdapterDesc1;

typedef DXGI_ADAPTER_DESC1 *PDXGIAdapterDesc1;

struct DECLSPEC_DRECORD DXGI_DISPLAY_COLOR_SPACE
{
public:
	System::StaticArray<System::StaticArray<float, 2>, 8> PrimaryCoordinates;
	System::StaticArray<System::StaticArray<float, 2>, 16> WhitePoints;
};


typedef _di_IDXGIFactory1 IID_IDXGIFactory1;

typedef _di_IDXGIAdapter1 IID_IDXGIAdapter1;

typedef _di_IDXGIDevice1 IID_IDXGIDevice1;

//-- var, const, procedure ---------------------------------------------------
#define DXGI_dll L"dxgi.dll"
}	/* namespace Dxgi */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DXGI)
using namespace Winapi::Dxgi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DxgiHPP
