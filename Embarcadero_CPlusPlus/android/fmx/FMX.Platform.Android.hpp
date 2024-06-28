// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_AndroidHPP
#define Fmx_Platform_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Messaging.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.NativeActivity.hpp>
#include <Androidapi.Input.hpp>
#include <Androidapi.AppGlue.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.Consts.hpp>
#include <FMX.Platform.hpp>
#include <FMX.VirtualKeyboard.Android.hpp>
#include <FMX.Dialogs.Android.hpp>
#include <FMX.Platform.Timer.Android.hpp>
#include <FMX.Platform.Device.Android.hpp>
#include <FMX.Platform.Logger.Android.hpp>
#include <FMX.Platform.SaveState.Android.hpp>
#include <FMX.Platform.Screen.Android.hpp>
#include <FMX.Platform.Metrics.Android.hpp>
#include <FMX.Platform.UI.Android.hpp>
#include <FMX.Graphics.Android.hpp>
#include <FMX.Controls.Android.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMessageCancelReceivingImage;
class DELPHICLASS TMessageReceivedImagePath;
class DELPHICLASS TFMXNativeActivityListener;
class DELPHICLASS TMainThreadWakeup;
class DELPHICLASS TRecognizerServiceMap;
class DELPHICLASS TPlatformAndroid;
class DELPHICLASS TRunnable;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMessageCancelReceivingImage : public System::Messaging::TMessage__1<int>
{
	typedef System::Messaging::TMessage__1<int> inherited;
	
public:
	/* {System_Messaging}TMessage<System_Integer>.Create */ inline __fastcall TMessageCancelReceivingImage(const int AValue) : System::Messaging::TMessage__1<int>(AValue) { }
	/* {System_Messaging}TMessage<System_Integer>.Destroy */ inline __fastcall virtual ~TMessageCancelReceivingImage() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMessageReceivedImagePath : public System::Messaging::TMessage__1<System::UnicodeString>
{
	typedef System::Messaging::TMessage__1<System::UnicodeString> inherited;
	
public:
	int RequestCode;
public:
	/* {System_Messaging}TMessage<System_string>.Create */ inline __fastcall TMessageReceivedImagePath(const System::UnicodeString AValue) : System::Messaging::TMessage__1<System::UnicodeString>(AValue) { }
	/* {System_Messaging}TMessage<System_string>.Destroy */ inline __fastcall virtual ~TMessageReceivedImagePath() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXNativeActivityListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
public:
	void __cdecl onCancelReceiveImage(int ARequestCode);
	void __cdecl onReceiveImagePath(int ARequestCode, Androidapi::Jni::Javatypes::_di_JString AFileName);
	void __cdecl onReceiveNotification(Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AIntent);
	void __cdecl onReceiveResult(int ARequestCode, int AResultCode, Androidapi::Jni::Graphicscontentviewtext::_di_JIntent AResultObject);
	void __cdecl onRequestPermissionsResult(int ARequestCode, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* APermissions, Androidapi::Jnibridge::TJavaArray__1<int>* AGrantResults);
public:
	/* TJavaLocal.Create */ inline __fastcall TFMXNativeActivityListener() : Androidapi::Jnibridge::TJavaLocal() { }
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TFMXNativeActivityListener() { }
	
private:
	void *__JOnActivityListener;	// Androidapi::Jni::Embarcadero::JOnActivityListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D0E0FCFB-0400-4522-B51E-220FC79F92BB}
	operator Androidapi::Jni::Embarcadero::_di_JOnActivityListener()
	{
		Androidapi::Jni::Embarcadero::_di_JOnActivityListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Embarcadero::JOnActivityListener*(void) { return (Androidapi::Jni::Embarcadero::JOnActivityListener*)&__JOnActivityListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMainThreadWakeup : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::TObject* FSignal;
	TRunnable* FRunnable;
	
protected:
	virtual void __fastcall Execute();
	virtual void __fastcall TerminatedSet();
	
public:
	__fastcall TMainThreadWakeup();
	__fastcall virtual ~TMainThreadWakeup();
	void __fastcall WakeUp();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRecognizerServiceMap : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	void __fastcall AddRecognizer(const Fmx::Types::TInteractiveGesture ARec, Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall RemoveRecognizer(const Fmx::Types::TInteractiveGesture ARec, Fmx::Forms::TCommonCustomForm* const AForm);
public:
	/* TObject.Create */ inline __fastcall TRecognizerServiceMap() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TRecognizerServiceMap() { }
	
private:
	void *__IFMXGestureRecognizersService;	// Fmx::Platform::IFMXGestureRecognizersService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5EFE3EC8-FF73-4275-A52A-43B3FCC628D8}
	operator Fmx::Platform::_di_IFMXGestureRecognizersService()
	{
		Fmx::Platform::_di_IFMXGestureRecognizersService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXGestureRecognizersService*(void) { return (Fmx::Platform::IFMXGestureRecognizersService*)&__IFMXGestureRecognizersService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPlatformAndroid : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
	class DELPHICLASS TMessageQueueIdleHandler;
	class PASCALIMPLEMENTATION TMessageQueueIdleHandler : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TPlatformAndroid* FPlatform;
		Androidapi::Jni::Os::_di_JHandler FHandler;
		TRunnable* FEmptyRunnable;
		
	public:
		__fastcall TMessageQueueIdleHandler(TPlatformAndroid* APlatform);
		bool __cdecl queueIdle();
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TMessageQueueIdleHandler() { }
		
private:
		void *__JMessageQueue_IdleHandler;	// Androidapi::Jni::Os::JMessageQueue_IdleHandler 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {36B80D1E-6D2E-421C-A29D-E7435F3023DE}
		operator Androidapi::Jni::Os::_di_JMessageQueue_IdleHandler()
		{
			Androidapi::Jni::Os::_di_JMessageQueue_IdleHandler intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Os::JMessageQueue_IdleHandler*(void) { return (Androidapi::Jni::Os::JMessageQueue_IdleHandler*)&__JMessageQueue_IdleHandler; }
		#endif
		
	};
	
	
	
private:
	static const Fmx::Types::TScreenOrientation UndefinedOrientation = (Fmx::Types::TScreenOrientation)(-1);
	
	Fmx::Platform::Timer::Android::TAndroidTimerService* FTimerService;
	Fmx::Platform::Device::Android::TAndroidDeviceServices* FDeviceServices;
	Fmx::Platform::Logger::Android::TAndroidLoggerService* FLoggerService;
	Fmx::Platform::Savestate::Android::TAndroidSaveStateService* FSaveStateService;
	Fmx::Platform::Screen::Android::TAndroidScreenServices* FScreenServices;
	Fmx::Graphics::Android::TAndroidGraphicsServices* FGraphicServices;
	Fmx::Platform::Metrics::Android::TAndroidMetricsServices* FMetricsServices;
	Fmx::Virtualkeyboard::Android::TVirtualKeyboardAndroid* FVirtualKeyboardService;
	Fmx::Platform::Ui::Android::TWindowServiceAndroid* FWindowService;
	TRecognizerServiceMap* FRecognizerServiceMap;
	Fmx::Platform::Ui::Android::TAndroidSystemAppearanceService* FSystemAppearanceService;
	Fmx::Platform::Ui::Android::TAndroidTextInputManager* FTextInputManager;
	TMessageQueueIdleHandler* FIdleHandler;
	TMainThreadWakeup* FMainThreadWakeup;
	Fmx::Platform::TApplicationEventHandler FOnApplicationEvent;
	TFMXNativeActivityListener* FActivityListener;
	bool FFirstRun;
	Fmx::Types::TScreenOrientation FLastOrientation;
	bool FRunning;
	bool FTerminating;
	System::UnicodeString FTitle;
	Fmx::Platform::TSystemThemeKind FLastThemeKind;
	void __fastcall CheckSystemThemeChanges();
	void __fastcall CheckOrientationChange();
	void __fastcall RegisterWakeMainThread();
	void __fastcall UnregisterWakeMainThread();
	void __fastcall WakeMainThread(System::TObject* Sender);
	void __fastcall RegisterServices();
	void __fastcall UnregisterServices();
	void __fastcall BindAppGlueEvents();
	void __fastcall UnbindAppGlueEvents();
	void __fastcall RegisterIdleHandler();
	void __fastcall UnregisterIdleHandler();
	
protected:
	int __fastcall HandleAndroidInputEvent(Androidapi::Appglue::TAndroidApplicationGlue* const AAppGlue, const Androidapi::Input::PAInputEvent AEvent);
	void __fastcall HandleApplicationCommandEvent(Androidapi::Appglue::TAndroidApplicationGlue* const AAppGlue, const Androidapi::Appglue::TAndroidApplicationCommand ACommand);
	void __fastcall HandleContentRectChanged(Androidapi::Appglue::TAndroidApplicationGlue* const AAppGlue, const System::Types::TRect &ARect);
	
public:
	__fastcall TPlatformAndroid();
	__fastcall virtual ~TPlatformAndroid();
	void __fastcall InternalProcessMessages();
	bool __fastcall ProcessOnIdleEvent();
	void __fastcall Run();
	bool __fastcall HandleMessage();
	void __fastcall WaitMessage();
	System::UnicodeString __fastcall GetDefaultTitle();
	System::UnicodeString __fastcall GetTitle();
	void __fastcall SetTitle(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetVersionString();
	bool __fastcall Running();
	bool __fastcall Terminating();
	void __fastcall Terminate();
	void __fastcall SetApplicationEventHandler(Fmx::Platform::TApplicationEventHandler AEventHandler);
	bool __fastcall HandleApplicationEvent(const Fmx::Platform::TApplicationEvent AEvent);
	__property Fmx::Platform::Device::Android::TAndroidDeviceServices* DeviceManager = {read=FDeviceServices};
	__property Fmx::Platform::Logger::Android::TAndroidLoggerService* Logger = {read=FLoggerService};
	__property Fmx::Platform::Metrics::Android::TAndroidMetricsServices* Metrics = {read=FMetricsServices};
	__property Fmx::Platform::Savestate::Android::TAndroidSaveStateService* SaveStateManager = {read=FSaveStateService};
	__property Fmx::Platform::Screen::Android::TAndroidScreenServices* ScreenManager = {read=FScreenServices};
	__property Fmx::Platform::Ui::Android::TAndroidTextInputManager* TextInputManager = {read=FTextInputManager};
	__property Fmx::Platform::Timer::Android::TAndroidTimerService* TimerManager = {read=FTimerService};
	__property Fmx::Virtualkeyboard::Android::TVirtualKeyboardAndroid* VirtualKeyboard = {read=FVirtualKeyboardService};
	__property Fmx::Platform::Ui::Android::TWindowServiceAndroid* WindowService = {read=FWindowService};
	__property Fmx::Platform::Ui::Android::TAndroidSystemAppearanceService* SystemAppearanceService = {read=FSystemAppearanceService};
private:
	void *__IFMXApplicationService;	// Fmx::Platform::IFMXApplicationService 
	void *__IFMXApplicationEventService;	// Fmx::Platform::IFMXApplicationEventService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EFBE3310-D103-4E9E-A8E1-4E45AB46D0D8}
	operator Fmx::Platform::_di_IFMXApplicationService()
	{
		Fmx::Platform::_di_IFMXApplicationService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXApplicationService*(void) { return (Fmx::Platform::IFMXApplicationService*)&__IFMXApplicationService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F3AAF11A-1678-4CC6-A5BF-721A24A676FD}
	operator Fmx::Platform::_di_IFMXApplicationEventService()
	{
		Fmx::Platform::_di_IFMXApplicationEventService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXApplicationEventService*(void) { return (Fmx::Platform::IFMXApplicationEventService*)&__IFMXApplicationEventService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TRunnable : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	System::Sysutils::_di_TProc FCallback;
	
public:
	__fastcall TRunnable(const System::Sysutils::_di_TProc ACallback);
	void __cdecl run();
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TRunnable() { }
	
private:
	void *__JRunnable;	// Androidapi::Jni::Javatypes::JRunnable 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BC131B27-7A72-4CAF-BB8E-170B8359B22E}
	operator Androidapi::Jni::Javatypes::_di_JRunnable()
	{
		Androidapi::Jni::Javatypes::_di_JRunnable intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Javatypes::JRunnable*(void) { return (Androidapi::Jni::Javatypes::JRunnable*)&__JRunnable; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TPlatformAndroid* PlatformAndroid;
extern DELPHI_PACKAGE Fmx::Platform::Ui::Android::TAndroidWindowHandle* __fastcall WindowHandleToPlatform(Fmx::Types::TWindowHandle* const AHandle);
extern DELPHI_PACKAGE Androidapi::Jni::Embarcadero::_di_JFMXNativeActivity __fastcall MainActivity(void);
extern DELPHI_PACKAGE void __fastcall RegisterCorePlatformServices(void);
extern DELPHI_PACKAGE void __fastcall UnregisterCorePlatformServices(void);
}	/* namespace Android */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_ANDROID)
using namespace Fmx::Platform::Android;
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
#endif	// Fmx_Platform_AndroidHPP
