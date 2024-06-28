// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Odbc.pas' rev: 34.00 (Windows)

#ifndef System_OdbcHPP
#define System_OdbcHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#if defined(__APPLE__) && !defined(_NO_REMAP_CONFLICTING_TYPES)
#define ULONG _ULONG // sqltypes.h/ULONG conflicts with sysmac.h 
#define DWORD _DWORD // iodbcunix.h/DWORD conflicts with sysmac.h 
#define BOOL  _BOOL_ // iodbcunix.h/BOOL conflicts with sysmac.h 
#endif

#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include <sqlucode.h>

#if defined(__APPLE__) && !defined(_NO_REMAP_CONFLICTING_TYPES)
#undef ULONG 
#undef DWORD 
#undef BOOL 
#endif

namespace System
{
namespace Odbc
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::Byte *PSqlChar;

typedef short *PSqlSmallInt;

#ifndef _WIN64
typedef int *PSqlLen;

typedef unsigned SQLROWCOUNT_CONST;
#else /* _WIN64 */
typedef __int64 *PSqlLen;
#endif /* _WIN64 */

typedef System::WideChar *PSqlWChar;

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Odbc */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ODBC)
using namespace System::Odbc;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_OdbcHPP
