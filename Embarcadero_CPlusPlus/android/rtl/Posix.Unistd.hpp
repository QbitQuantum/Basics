// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.Unistd.pas' rev: 34.00 (Android)

#ifndef Posix_UnistdHPP
#define Posix_UnistdHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.Stdio.hpp>
#include <Posix.Dlfcn.hpp>
#include <Posix.StdDef.hpp>

//-- user supplied -----------------------------------------------------------
#include <unistd.h>

namespace Posix
{
namespace Unistd
{
//-- forward type declarations -----------------------------------------------
struct TPipeDescriptors;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TPipeDescriptors
{
public:
	int ReadDes;
	int WriteDes;
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall euidaccess(char * Name, int Mode);
}	/* namespace Unistd */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_UnistdHPP
