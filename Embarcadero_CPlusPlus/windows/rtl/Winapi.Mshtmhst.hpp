// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Mshtmhst.pas' rev: 34.00 (Windows)

#ifndef Winapi_MshtmhstHPP
#define Winapi_MshtmhstHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------
#include <mshtmhst.h>
DECLARE_DINTERFACE_TYPE(IDocHostShowUI);
DECLARE_DINTERFACE_TYPE(IDocHostUIHandler);

namespace Winapi
{
namespace Mshtmhst
{
//-- forward type declarations -----------------------------------------------
struct TDocHostUIInfo;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TDocHostUIInfo
{
public:
	unsigned cbSize;
	unsigned dwFlags;
	unsigned dwDoubleClick;
	System::WideChar *pchHostCss;
	System::WideChar *pchHostNS;
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mshtmhst */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_MSHTMHST)
using namespace Winapi::Mshtmhst;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_MshtmhstHPP
