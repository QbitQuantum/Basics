// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Posix.SysTime.pas' rev: 34.00 (Android)

#ifndef Posix_SystimeHPP
#define Posix_SystimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Posix.Base.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.Time.hpp>

//-- user supplied -----------------------------------------------------------
#include <sys/time.h>

namespace Posix
{
namespace Systime
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef timeval *Ptimeval;

typedef itimerval *Pitimerval;

enum DECLSPEC_DENUM cmpTimerType : unsigned char { cmpGreater, cmpGreaterEqual, cmpEquals, cmpLess, cmpLessEqual };

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Systime */
}	/* namespace Posix */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Posix_SystimeHPP
