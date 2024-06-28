// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Functiondiscovery.pas' rev: 34.00 (Windows)

#ifndef Winapi_FunctiondiscoveryHPP
#define Winapi_FunctiondiscoveryHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.ActiveX.hpp>
#include <Winapi.PropKey.hpp>
#include <Winapi.PropSys.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------

#include <functiondiscoverycategories.h>
#include <functiondiscoveryerror.h>
#include <functiondiscoverykeys.h>
#include <functiondiscoveryserviceids.h>
#include <functiondiscoveryapi.h>
#include <functiondiscovery.h>

DECLARE_DINTERFACE_TYPE(IFunctionDiscoveryNotification);
DECLARE_DINTERFACE_TYPE(IFunctionDiscovery);
DECLARE_DINTERFACE_TYPE(IFunctionInstance);
DECLARE_DINTERFACE_TYPE(IFunctionInstanceCollection);
DECLARE_DINTERFACE_TYPE(IPropertyStoreCollection);
DECLARE_DINTERFACE_TYPE(IFunctionInstanceQuery);
DECLARE_DINTERFACE_TYPE(IFunctionInstanceCollectionQuery);

namespace Winapi
{
namespace Functiondiscovery
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef unsigned __int64 *PFDQUERYCONTEXT;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Functiondiscovery */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_FUNCTIONDISCOVERY)
using namespace Winapi::Functiondiscovery;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_FunctiondiscoveryHPP
