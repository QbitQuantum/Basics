// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D12sdklayers.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d12sdklayersHPP
#define Winapi_D3d12sdklayersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.D3D12.hpp>

//-- user supplied -----------------------------------------------------------
#include "windows.h"
#include "d3d12.h"
#include "d3d12sdklayers.h"
DECLARE_DINTERFACE_TYPE(ID3D12Debug);
DECLARE_DINTERFACE_TYPE(ID3D12DebugDevice);
DECLARE_DINTERFACE_TYPE(ID3D12DebugCommandQueue);
DECLARE_DINTERFACE_TYPE(ID3D12DebugCommandList);
DECLARE_DINTERFACE_TYPE(ID3D12InfoQueue);

namespace Winapi
{
namespace D3d12sdklayers
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef D3D12_DEBUG_FEATURE TD3D12DebugFeature;

typedef D3D12_RLDO_FLAGS TD3D12RldoFlags;

typedef D3D12_MESSAGE_CATEGORY TD3D12MessageCategory;

typedef D3D12_MESSAGE_CATEGORY *PD3D12MessageCategory;

typedef D3D12_MESSAGE_SEVERITY TD3D12MessageSeverity;

typedef D3D12_MESSAGE_SEVERITY *PD3D12MessageSeverity;

typedef D3D12_MESSAGE_ID TD3D12MessageId;

typedef D3D12_MESSAGE_ID *PD3D12MessageId;

typedef D3D12_MESSAGE TD3D12Message;

typedef D3D12_MESSAGE *PD3D12Message;

typedef D3D12_INFO_QUEUE_FILTER_DESC TD3D12InfoQueueFilterDesc;

typedef D3D12_INFO_QUEUE_FILTER_DESC *PD3D12InfoQueueFilterDesc;

typedef D3D12_INFO_QUEUE_FILTER TD3D12InfoQueueFilter;

typedef D3D12_INFO_QUEUE_FILTER *PD3D12InfoQueueFilter;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d12sdklayers */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D12SDKLAYERS)
using namespace Winapi::D3d12sdklayers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d12sdklayersHPP
