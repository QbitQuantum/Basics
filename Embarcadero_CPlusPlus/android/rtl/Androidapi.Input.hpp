// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.Input.pas' rev: 34.00 (Android)

#ifndef Androidapi_InputHPP
#define Androidapi_InputHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.StdDef.hpp>
#include <Androidapi.Looper.hpp>
#include <Androidapi.KeyCodes.hpp>

//-- user supplied -----------------------------------------------------------
#include <android/input.h>

namespace Androidapi
{
namespace Input
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef AInputQueue *PAInputQueue;

typedef AInputEvent *PAInputEvent;

typedef PAInputEvent *PPAInputEvent;

//-- var, const, procedure ---------------------------------------------------
#define AndroidLib u"/usr/lib/libandroid.so"
#define AndroidJniGraphicsLib u"/usr/lib/libjnigraphics.so"
#define AndroidEglLib u"/usr/lib/libEGL.so"
#define AndroidGlesLib u"/usr/lib/libGLESv1_CM.so"
#define AndroidGles2Lib u"/usr/lib/libGLESv2.so"
#define AndroidLogLib u"/usr/lib/liblog.so"
#define AndroidOpenSlesLib u"/usr/lib/libOpenSLES.so"
#define AndroidNativeWindowLib u"/usr/lib/libnativewindow.so"
static constexpr int AINPUT_SOURCE_MOUSE_RELATIVE = int(0x20004);
static constexpr int AINPUT_SOURCE_ROTARY_ENCODER = int(0x400000);
}	/* namespace Input */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_INPUT)
using namespace Androidapi::Input;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_InputHPP
