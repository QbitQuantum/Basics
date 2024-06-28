// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.UserEnv.pas' rev: 34.00 (Windows)

#ifndef Winapi_UserenvHPP
#define Winapi_UserenvHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Wbem.hpp>
#include <Winapi.ActiveX.hpp>

//-- user supplied -----------------------------------------------------------
#include "userenv.h"
#ifndef _WIN64
#pragma link "userenv.lib"
#endif

namespace Winapi
{
namespace Userenv
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef LPPROFILEINFOW LPPROFILEINFO;

typedef _PROFILEINFOA *PProfileInfoA;

typedef _PROFILEINFOW *PProfileInfoW;

typedef PProfileInfoW PProfileInfo;

typedef _PROFILEINFOA TProfileInfoA;

typedef _PROFILEINFOW TProfileInfoW;

typedef _PROFILEINFOW TProfileInfo;

typedef _GPO_LINK TGPOLink;

typedef _GPO_LINK *PGPOLink;

typedef _GROUP_POLICY_OBJECTA TGroupPolicyObjectA;

typedef _GROUP_POLICY_OBJECTW TGroupPolicyObjectW;

typedef _GROUP_POLICY_OBJECTW TGroupPolicyObject;

typedef PGROUP_POLICY_OBJECTA PGroupPolicyObjectA;

typedef PGROUP_POLICY_OBJECTW PGroupPolicyObjectW;

typedef PGROUP_POLICY_OBJECTW PGroupPolicyObject;

typedef _RSOP_TARGET TRSOPTarget;

typedef _RSOP_TARGET *PRSOPTarget;

enum DECLSPEC_DENUM _SETTINGSTATUS : unsigned int { RSOPUnspecified, RSOPApplied, RSOPIgnored, RSOPFailed, RSOPSubsettingFailed };

typedef _SETTINGSTATUS TSettingStatus;

typedef _SETTINGSTATUS *PSettingStatus;

typedef _POLICYSETTINGSTATUSINFO TPolicySettingStatusInfo;

typedef _POLICYSETTINGSTATUSINFO *PPolicySettingStatusInfo;

//-- var, const, procedure ---------------------------------------------------
#define userenv L"userenv.dll"
}	/* namespace Userenv */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_USERENV)
using namespace Winapi::Userenv;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_UserenvHPP
