// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.RtsCom.pas' rev: 34.00 (Windows)

#ifndef Winapi_RtscomHPP
#define Winapi_RtscomHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.TpcShrd.hpp>
#include <Winapi.MsInkAut.hpp>
#include <Winapi.Manipulations.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------

#include "rtscom.h"

DECLARE_DINTERFACE_TYPE(IRealTimeStylus);
DECLARE_DINTERFACE_TYPE(IRealTimeStylus2);
DECLARE_DINTERFACE_TYPE(IRealTimeStylus3);
DECLARE_DINTERFACE_TYPE(IRealTimeStylusSynchronization);
DECLARE_DINTERFACE_TYPE(IStrokeBuilder);
DECLARE_DINTERFACE_TYPE(IStylusPlugin);
DECLARE_DINTERFACE_TYPE(IStylusSyncPlugin);
DECLARE_DINTERFACE_TYPE(IStylusAsyncPlugin);
DECLARE_DINTERFACE_TYPE(IDynamicRenderer);
DECLARE_DINTERFACE_TYPE(IGestureRecognizer);

namespace Winapi
{
namespace Rtscom
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef StylusInfo TStylusInfo;

typedef StylusInfo *PStylusInfo;

typedef GESTURE_DATA TGestureData;

typedef GESTURE_DATA *PGestureData;

typedef DYNAMIC_RENDERER_CACHED_DATA TDynamicRendererCachedData;

typedef DYNAMIC_RENDERER_CACHED_DATA *PDynamicRendererCachedData;

//-- var, const, procedure ---------------------------------------------------
#define SID_IRealTimeStylus L"{A8BB5D22-3144-4a7b-93CD-F34A16BE513A}"
#define SID_IRealTimeStylus2 L"{B5F2A6CD-3179-4a3e-B9C4-BB5865962BE2}"
#define SID_IRealTimeStylus3 L"{D70230A3-6986-4051-B57A-1CF69F4D9DB5}"
#define SID_IRealTimeStylusSynchronization L"{AA87EAB8-AB4A-4cea-B5CB-46D84C6A2509}"
#define SID_IStrokeBuilder L"{A5FD4E2D-C44B-4092-9177-260905EB672B}"
#define SID_IStylusPlugin L"{A81436D8-4757-4fd1-A185-133F97C6C545}"
#define SID_IStylusSyncPlugin L"{A157B174-482F-4d71-A3F6-3A41DDD11BE9}"
#define SID_IStylusAsyncPlugin L"{A7CCA85A-31BC-4cd2-AADC-3289A3AF11C8}"
#define SID_IDynamicRenderer L"{A079468E-7165-46f9-B7AF-98AD01A93009}"
#define SID_IGestureRecognizer L"{AE9EF86B-7054-45e3-AE22-3174DC8811B7}"
}	/* namespace Rtscom */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_RTSCOM)
using namespace Winapi::Rtscom;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_RtscomHPP
