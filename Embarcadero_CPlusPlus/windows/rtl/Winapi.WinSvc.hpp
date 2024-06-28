// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.WinSvc.pas' rev: 34.00 (Windows)

#ifndef Winapi_WinsvcHPP
#define Winapi_WinsvcHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <winsvc.h>

namespace Winapi
{
namespace Winsvc
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef LPSERVICE_STATUS PServiceStatus;

typedef SERVICE_STATUS TServiceStatus;

typedef LPENUM_SERVICE_STATUSA PEnumServiceStatusA;

typedef LPENUM_SERVICE_STATUSW PEnumServiceStatusW;

typedef LPENUM_SERVICE_STATUSW PEnumServiceStatus;

typedef _ENUM_SERVICE_STATUSA TEnumServiceStatusA;

typedef _ENUM_SERVICE_STATUSW TEnumServiceStatusW;

typedef _ENUM_SERVICE_STATUSW TEnumServiceStatus;

typedef _ENUM_SERVICE_STATUS_PROCESSA *LPENUM_SERVICE_STATUS_PROCESSA;

typedef _ENUM_SERVICE_STATUS_PROCESSW *LPENUM_SERVICE_STATUS_PROCESSW;

typedef LPQUERY_SERVICE_LOCK_STATUSA PQueryServiceLockStatusA;

typedef LPQUERY_SERVICE_LOCK_STATUSW PQueryServiceLockStatusW;

typedef LPQUERY_SERVICE_LOCK_STATUSW PQueryServiceLockStatus;

typedef _QUERY_SERVICE_LOCK_STATUSA TQueryServiceLockStatusA;

typedef _QUERY_SERVICE_LOCK_STATUSW TQueryServiceLockStatusW;

typedef _QUERY_SERVICE_LOCK_STATUSW TQueryServiceLockStatus;

typedef LPQUERY_SERVICE_CONFIGA PQueryServiceConfigA;

typedef LPQUERY_SERVICE_CONFIGW PQueryServiceConfigW;

typedef LPQUERY_SERVICE_CONFIGW PQueryServiceConfig;

typedef _QUERY_SERVICE_CONFIGA TQueryServiceConfigA;

typedef _QUERY_SERVICE_CONFIGW TQueryServiceConfigW;

typedef _QUERY_SERVICE_CONFIGW TQueryServiceConfig;

typedef LPSERVICE_MAIN_FUNCTIONA TServiceMainFunctionA;

typedef LPSERVICE_MAIN_FUNCTIONW TServiceMainFunctionW;

typedef LPSERVICE_MAIN_FUNCTIONW TServiceMainFunction;

typedef LPSERVICE_TABLE_ENTRYA PServiceTableEntryA;

typedef LPSERVICE_TABLE_ENTRYW PServiceTableEntryW;

typedef LPSERVICE_TABLE_ENTRYW PServiceTableEntry;

typedef _SERVICE_TABLE_ENTRYA TServiceTableEntryA;

typedef _SERVICE_TABLE_ENTRYW TServiceTableEntryW;

typedef _SERVICE_TABLE_ENTRYW TServiceTableEntry;

typedef LPHANDLER_FUNCTION THandlerFunction;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Winsvc */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WINSVC)
using namespace Winapi::Winsvc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_WinsvcHPP
