// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Timer.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Platform_Timer_IosHPP
#define Fmx_Platform_Timer_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Timer
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCocoaTouchTimerService;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCocoaTouchTimerService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::Generics::Collections::TList__1<NativeUInt>* FTimers;
	System::Generics::Collections::TDictionary__2<NativeUInt,System::TObject*>* FObjectMap;
	NativeUInt FHandleCounter;
	bool FTerminating;
	void __fastcall ApplicationTerminatingHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	
protected:
	NativeUInt __fastcall NewFmxHandle();
	NativeUInt __fastcall AllocObjectHandle(System::TObject* const AObject);
	void __fastcall DeleteObjectHandle(const NativeUInt AHandle);
	System::TObject* __fastcall HandleToObject(const NativeUInt AHandle);
	void __fastcall ValidateHandle(const NativeUInt AHandle);
	void __fastcall DestroyTimers();
	virtual void __fastcall RegisterService();
	virtual void __fastcall UnregisterService();
	
public:
	__fastcall TCocoaTouchTimerService();
	__fastcall virtual ~TCocoaTouchTimerService();
	NativeUInt __fastcall CreateTimer(int AInterval, Fmx::Types::TTimerProc ATimerFunc);
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Timer */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_TIMER_IOS)
using namespace Fmx::Platform::Timer::Ios;
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
#endif	// Fmx_Platform_Timer_IosHPP
