// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.Gles.pas' rev: 34.00 (Android)

#ifndef Androidapi_GlesHPP
#define Androidapi_GlesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.SysTypes.hpp>
#include <Androidapi.KhrPlatform.hpp>

//-- user supplied -----------------------------------------------------------
#include <GLES/gl.h>

namespace Androidapi
{
namespace Gles
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef char * PGLchar;

typedef char * *PPGLchar;

typedef unsigned *PGLenum;

typedef int *PGLsizei;

typedef float *PGLfloat;

typedef short *PGLshort;

typedef void * PGLvoid;

typedef void * *PPGLvoid;

typedef System::Byte *PGLubyte;

typedef int *PGLint;

typedef System::Byte *PGLboolean;

typedef unsigned *PGLuint;

typedef int *PGLfixed;

//-- var, const, procedure ---------------------------------------------------
#define AndroidLib u"/usr/lib/libandroid.so"
#define AndroidJniGraphicsLib u"/usr/lib/libjnigraphics.so"
#define AndroidEglLib u"/usr/lib/libEGL.so"
#define AndroidGlesLib u"/usr/lib/libGLESv1_CM.so"
#define AndroidGles2Lib u"/usr/lib/libGLESv2.so"
#define AndroidLogLib u"/usr/lib/liblog.so"
#define AndroidOpenSlesLib u"/usr/lib/libOpenSLES.so"
#define AndroidNativeWindowLib u"/usr/lib/libnativewindow.so"
}	/* namespace Gles */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_GLES)
using namespace Androidapi::Gles;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_GlesHPP
