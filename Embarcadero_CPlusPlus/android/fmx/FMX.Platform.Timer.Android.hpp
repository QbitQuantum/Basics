// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Timer.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Timer_AndroidHPP
#define Fmx_Platform_Timer_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Messaging.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Timer
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidTimerService;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidTimerService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
protected:
	virtual void __fastcall RegisterService();
	virtual void __fastcall UnregisterService();
	
public:
	__fastcall TAndroidTimerService();
	__fastcall virtual ~TAndroidTimerService();
	NativeUInt __fastcall CreateTimer(int AInterval, Fmx::Types::TTimerProc ATimerProc);
	bool __fastcall DestroyTimer(NativeUInt ATimer);
	double __fastcall GetTick();
private:
	void *__IFMXTimerService;	// Fmx::Types::IFMXTimerService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {856E938B-FF7B-4E13-85D4-3414A6A9FF2F}
	operator Fmx::Types::_di_IFMXTimerService()
	{
		Fmx::Types::_di_IFMXTimerService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IFMXTimerService*(void) { return (Fmx::Types::IFMXTimerService*)&__IFMXTimerService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Timer */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_TIMER_ANDROID)
using namespace Fmx::Platform::Timer::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_TIMER)
using namespace Fmx::Platform::Timer;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM)
using namespace Fmx::Platform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Platform_Timer_AndroidHPP
