// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Android.Notification.pas' rev: 34.00 (Android)

#ifndef System_Android_NotificationHPP
#define System_Android_NotificationHPP

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
namespace Android
{
namespace Notification
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPlatformNotificationCenter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPlatformNotificationCenter : public System::Notification::TBaseNotificationCenter
{
	typedef System::Notification::TBaseNotificationCenter inherited;
	
protected:
	__classmethod virtual System::Notification::TBaseNotificationCenter* __fastcall GetInstance();
public:
	/* TBaseNotificationCenter.Create */ inline __fastcall TPlatformNotificationCenter() : System::Notification::TBaseNotificationCenter() { }
	/* TBaseNotificationCenter.Destroy */ inline __fastcall virtual ~TPlatformNotificationCenter() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Notification */
}	/* namespace Android */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID_NOTIFICATION)
using namespace System::Android::Notification;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANDROID)
using namespace System::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Android_NotificationHPP
