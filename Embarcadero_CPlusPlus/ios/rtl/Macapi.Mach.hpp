// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Macapi.Mach.pas' rev: 34.00 (iOS)

#ifndef Macapi_MachHPP
#define Macapi_MachHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>

//-- user supplied -----------------------------------------------------------
#ifdef __clang__
#include <mach/mach.h>
#endif

namespace Macapi
{
namespace Mach
{
//-- forward type declarations -----------------------------------------------
struct TTimebaseInfoData;
//-- type declarations -------------------------------------------------------
typedef int clock_id_t;

typedef unsigned clock_serv_t;

struct DECLSPEC_DRECORD TTimebaseInfoData
{
public:
	unsigned Numer;
	unsigned Denom;
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE unsigned __int64 __fastcall AbsoluteToNanoseconds(unsigned __int64 AbsoluteTime);
}	/* namespace Mach */
}	/* namespace Macapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI_MACH)
using namespace Macapi::Mach;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_MACAPI)
using namespace Macapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Macapi_MachHPP
