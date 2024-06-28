// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.SHFolder.pas' rev: 34.00 (Windows)

#ifndef Winapi_ShfolderHPP
#define Winapi_ShfolderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
// SHFolder is the deprecated Shell API:
// * https://msdn.microsoft.com/en-us/library/windows/desktop/jj635743(v=vs.85).aspx
#if (NTDDI_VERSION < NTDDI_WIN2K)
#include <shfolder.h>

namespace Winapi
{
namespace Shfolder
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef PFNSHGETFOLDERPATHW PFNSHGETFOLDERPATH;

typedef PFNSHGETFOLDERPATHA TSHGetFolderPathA;

typedef PFNSHGETFOLDERPATHW TSHGetFolderPathW;

typedef PFNSHGETFOLDERPATHW TSHGetFolderPath;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Shfolder */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_SHFOLDER)
using namespace Winapi::Shfolder;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif

//-- user supplied -----------------------------------------------------------
#endif

#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_ShfolderHPP
