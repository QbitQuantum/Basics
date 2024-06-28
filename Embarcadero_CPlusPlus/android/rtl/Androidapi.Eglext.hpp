// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.Eglext.pas' rev: 34.00 (Android)

#ifndef Androidapi_EglextHPP
#define Androidapi_EglextHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <Androidapi.Egl.hpp>
#include <Androidapi.KhrPlatform.hpp>
#include <Androidapi.EglPlatform.hpp>

//-- user supplied -----------------------------------------------------------
#include <EGL/eglext.h>

namespace Androidapi
{
namespace Eglext
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD ANativeWindowBuffer
{
};


//-- type declarations -------------------------------------------------------
typedef unsigned __cdecl (*PFNEGLLOCKSURFACEKHRPROC)(void * display, void * surface, Androidapi::Egl::PEGLint attrib_list);

typedef unsigned __cdecl (*PFNEGLUNLOCKSURFACEKHRPROC)(void * display, void * surface);

typedef void * EGLImageKHR;

typedef void * __cdecl (*PFNEGLCREATEIMAGEKHRPROC)(void * dpy, void * ctx, unsigned target, void * buffer, Androidapi::Egl::PEGLint attrib_list);

typedef unsigned __cdecl (*PFNEGLDESTROYIMAGEKHRPROC)(void * dpy, void * image);

typedef void * EGLSyncKHR;

typedef unsigned __int64 EGLTimeKHR;

typedef void * EGLSyncNV;

typedef unsigned __int64 EGLTimeNV;

typedef unsigned __cdecl (*PFNEGLSETSWAPRECTANGLEANDROIDPROC)(void * dpy, void * draw, int left, int top, int width, int height);

//-- var, const, procedure ---------------------------------------------------
#define AndroidLib u"/usr/lib/libandroid.so"
#define AndroidJniGraphicsLib u"/usr/lib/libjnigraphics.so"
#define AndroidEglLib u"/usr/lib/libEGL.so"
#define AndroidGlesLib u"/usr/lib/libGLESv1_CM.so"
#define AndroidGles2Lib u"/usr/lib/libGLESv2.so"
#define AndroidLogLib u"/usr/lib/liblog.so"
#define AndroidOpenSlesLib u"/usr/lib/libOpenSLES.so"
#define AndroidNativeWindowLib u"/usr/lib/libnativewindow.so"
#define EGL_NO_IMAGE_KHR (void *)(0)
}	/* namespace Eglext */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_EGLEXT)
using namespace Androidapi::Eglext;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_EglextHPP
