// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Win.Notification.pas' rev: 34.00 (Windows)

#ifndef System_Win_NotificationHPP
#define System_Win_NotificationHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Notification.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Win
{
namespace Notification
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformNotificationCenter;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TPlatformNotificationCenter : public System::Notification::TBaseNotificationCenter
{
	typedef System::Notification::TBaseNotificationCenter inherited;
	
protected:
	__classmethod virtual System::Notification::TBaseNotificationCenter* __fastcall GetInstance();
public:
	/* TBaseNotificationCenter.Create */ inline __fastcall TPlatformNotificationCenter() : System::Notification::TBaseNotificationCenter() { }
	/* TBaseNotificationCenter.Destroy */ inline __fastcall virtual ~TPlatformNotificationCenter() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Notification */
}	/* namespace Win */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN_NOTIFICATION)
using namespace System::Win::Notification;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIN)
using namespace System::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Win_NotificationHPP
