// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.OpenGL.pas' rev: 34.00 (Windows)

#ifndef Winapi_OpenglHPP
#define Winapi_OpenglHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <gl/gl.h>

namespace Winapi
{
namespace Opengl
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD _GLUquadricObj
{
};


struct DECLSPEC_DRECORD _GLUtesselator
{
};


struct DECLSPEC_DRECORD TGLUnurbsObj
{
};


//-- type declarations -------------------------------------------------------
typedef System::Byte *PGLBoolean;

typedef PGLBoolean *PPGLBoolean;

typedef unsigned *PGLEnum;

typedef System::Int8 *PGLByte;

typedef short *PGLShort;

typedef int *PGLInt;

typedef int *PGLSizei;

typedef System::Byte *PGLubyte;

typedef System::Word *PGLushort;

typedef unsigned *PGLuint;

typedef float *PGLclampf;

typedef float *PGLfloat;

typedef double *PGLdouble;

typedef double *PGLclampd;

typedef System::StaticArray<float, 4> TGLArrayf4;

typedef System::StaticArray<float, 3> TGLArrayf3;

typedef System::StaticArray<int, 4> TGLArrayi4;

//-- var, const, procedure ---------------------------------------------------
#define glu32 L"glu32.dll"
}	/* namespace Opengl */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_OPENGL)
using namespace Winapi::Opengl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_OpenglHPP
