// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.D3D11sdklayers.pas' rev: 34.00 (Windows)

#ifndef Winapi_D3d11sdklayersHPP
#define Winapi_D3d11sdklayersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.D3D11.hpp>
#include <Winapi.DXGI.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
DECLARE_DINTERFACE_TYPE(ID3D11Debug);
DECLARE_DINTERFACE_TYPE(ID3D11SwitchToRef);
DECLARE_DINTERFACE_TYPE(ID3D11InfoQueue);

namespace Winapi
{
namespace D3d11sdklayers
{
//-- forward type declarations -----------------------------------------------
struct TD3D11_RLDO_FLAGSHelper;
//-- type declarations -------------------------------------------------------
typedef D3D11_RLDO_FLAGS TD3D11_RLDO_FLAGS;

typedef D3D11_MESSAGE_CATEGORY TD3D11_MESSAGE_CATEGORY;

typedef D3D11_MESSAGE_CATEGORY *PD3D11_MESSAGE_CATEGORY;

typedef D3D11_MESSAGE_SEVERITY TD3D11_MESSAGE_SEVERITY;

typedef D3D11_MESSAGE_SEVERITY *PD3D11_MESSAGE_SEVERITY;

typedef D3D11_MESSAGE_ID TD3D11_MESSAGE_ID;

typedef D3D11_MESSAGE_ID *PD3D11_MESSAGE_ID;

typedef D3D11_MESSAGE TD3D11_MESSAGE;

typedef D3D11_MESSAGE *PD3D11_MESSAGE;

typedef D3D11_INFO_QUEUE_FILTER_DESC TD3D11_INFO_QUEUE_FILTER_DESC;

typedef D3D11_INFO_QUEUE_FILTER TD3D11_INFO_QUEUE_FILTER;

typedef D3D11_INFO_QUEUE_FILTER *PD3D11_INFO_QUEUE_FILTER;

struct DECLSPEC_DRECORD TD3D11_RLDO_FLAGSHelper
{
public:
	D3D11_RLDO_FLAGS data;
	__fastcall TD3D11_RLDO_FLAGSHelper(D3D11_RLDO_FLAGS aData);
	static TD3D11_RLDO_FLAGSHelper __fastcall _op_LogicalNot(TD3D11_RLDO_FLAGSHelper a);
	static TD3D11_RLDO_FLAGSHelper __fastcall _op_LogicalAnd(TD3D11_RLDO_FLAGSHelper a, TD3D11_RLDO_FLAGSHelper b);
	static TD3D11_RLDO_FLAGSHelper __fastcall _op_LogicalOr(TD3D11_RLDO_FLAGSHelper a, TD3D11_RLDO_FLAGSHelper b);
	static TD3D11_RLDO_FLAGSHelper __fastcall _op_ExclusiveOr(TD3D11_RLDO_FLAGSHelper a, TD3D11_RLDO_FLAGSHelper b);
	static void __fastcall LogicalAndEqual(TD3D11_RLDO_FLAGSHelper &a, TD3D11_RLDO_FLAGSHelper b);
	static void __fastcall LogicalOrEqual(TD3D11_RLDO_FLAGSHelper &a, TD3D11_RLDO_FLAGSHelper b);
	static void __fastcall LogicalXorEqual(TD3D11_RLDO_FLAGSHelper &a, TD3D11_RLDO_FLAGSHelper b);
	TD3D11_RLDO_FLAGSHelper() {}
	
	TD3D11_RLDO_FLAGSHelper operator !() { return TD3D11_RLDO_FLAGSHelper::_op_LogicalNot(*this); }
	friend TD3D11_RLDO_FLAGSHelper operator &&(TD3D11_RLDO_FLAGSHelper a, TD3D11_RLDO_FLAGSHelper b) { return TD3D11_RLDO_FLAGSHelper::_op_LogicalAnd(a, b); }
	friend TD3D11_RLDO_FLAGSHelper operator ||(TD3D11_RLDO_FLAGSHelper a, TD3D11_RLDO_FLAGSHelper b) { return TD3D11_RLDO_FLAGSHelper::_op_LogicalOr(a, b); }
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace D3d11sdklayers */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_D3D11SDKLAYERS)
using namespace Winapi::D3d11sdklayers;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_D3d11sdklayersHPP
