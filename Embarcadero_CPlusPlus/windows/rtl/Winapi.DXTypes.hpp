// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.DXTypes.pas' rev: 34.00 (Windows)

#ifndef Winapi_DxtypesHPP
#define Winapi_DxtypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#define DIRECT3D_VERSION 0x0900
#include <d3dtypes.h>

namespace Winapi
{
namespace Dxtypes
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef _D3DCOLORVALUE TD3DColorValue;

typedef LPD3DCOLORVALUE PD3DColorValue;

typedef _D3DRECT TD3DRect;

typedef LPD3DRECT PD3DRect;

typedef _D3DMATRIX TD3DMatrix;

typedef LPD3DMATRIX PD3DMatrix;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dxtypes */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_DXTYPES)
using namespace Winapi::Dxtypes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_DxtypesHPP
