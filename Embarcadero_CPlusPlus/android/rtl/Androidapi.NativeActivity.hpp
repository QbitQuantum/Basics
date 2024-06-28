// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.NativeActivity.pas' rev: 34.00 (Android)

#ifndef Androidapi_NativeactivityHPP
#define Androidapi_NativeactivityHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <Androidapi.AssetManager.hpp>
#include <Androidapi.Input.hpp>
#include <Androidapi.NativeWindow.hpp>
#include <Androidapi.Rect.hpp>
#include <Androidapi.Jni.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------
#include <android/native_activity.h>

namespace Androidapi
{
namespace Nativeactivity
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef ANativeActivityCallbacks *PANativeActivityCallbacks;

typedef ANativeActivity *PANativeActivity;

typedef void __cdecl (*TOnStartCallback)(PANativeActivity Activity);

typedef void __cdecl (*TOnResumeCallback)(PANativeActivity Activity);

typedef void * __cdecl (*TOnSaveInstanceStateCallback)(PANativeActivity Activity, Posix::Stddef::Psize_t OutSize);

typedef void __cdecl (*TOnPauseCallback)(PANativeActivity Activity);

typedef void __cdecl (*TOnStopCallback)(PANativeActivity Activity);

typedef void __cdecl (*TOnDestroyCallback)(PANativeActivity Activity);

typedef void __cdecl (*TOnWindowFocusChangedCallback)(PANativeActivity Activity, int HasFocus);

typedef void __cdecl (*TOnNativeWindowCreatedCallback)(PANativeActivity Activity, Androidapi::Nativewindow::PANativeWindow Window);

typedef void __cdecl (*TOnNativeWindowResizedCallback)(PANativeActivity Activity, Androidapi::Nativewindow::PANativeWindow Window);

typedef void __cdecl (*TOnNativeWindowRedrawNeededCallback)(PANativeActivity Activity, Androidapi::Nativewindow::PANativeWindow Window);

typedef void __cdecl (*TOnNativeWindowDestroyedCallback)(PANativeActivity Activity, Androidapi::Nativewindow::PANativeWindow Window);

typedef void __cdecl (*TOnInputQueueCreatedCallback)(PANativeActivity Activity, Androidapi::Input::PAInputQueue Queue);

typedef void __cdecl (*TOnInputQueueDestroyedCallback)(PANativeActivity Activity, Androidapi::Input::PAInputQueue Queue);

typedef void __cdecl (*TOnContentRectChangedCallback)(PANativeActivity Activity, Androidapi::Rect::PARect Rect);

typedef void __cdecl (*TOnConfigurationChangedCallback)(PANativeActivity Activity);

typedef void __cdecl (*TOnLowMemoryCallback)(PANativeActivity Activity);

typedef void __cdecl (*ANativeActivity_createFunc)(PANativeActivity Activity, void * SavedState, NativeUInt SavedStateSize);

//-- var, const, procedure ---------------------------------------------------
#define AndroidLib u"/usr/lib/libandroid.so"
#define AndroidJniGraphicsLib u"/usr/lib/libjnigraphics.so"
#define AndroidEglLib u"/usr/lib/libEGL.so"
#define AndroidGlesLib u"/usr/lib/libGLESv1_CM.so"
#define AndroidGles2Lib u"/usr/lib/libGLESv2.so"
#define AndroidLogLib u"/usr/lib/liblog.so"
#define AndroidOpenSlesLib u"/usr/lib/libOpenSLES.so"
#define AndroidNativeWindowLib u"/usr/lib/libnativewindow.so"
extern DELPHI_PACKAGE ANativeActivity_createFunc ANativeActivity_onCreate;
}	/* namespace Nativeactivity */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_NATIVEACTIVITY)
using namespace Androidapi::Nativeactivity;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_NativeactivityHPP
