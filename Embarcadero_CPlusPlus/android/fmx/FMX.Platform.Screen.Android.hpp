// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Screen.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Screen_AndroidHPP
#define Fmx_Platform_Screen_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Util.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Hardware.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Screen
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidScreenServices;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidScreenServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TDisplayAndroid
	{
	public:
		Fmx::Types::TDisplay Display;
		int Id;
		__fastcall TDisplayAndroid(const int AIndex, const bool APrimary, const System::Types::TRect &ABounds, const System::Types::TRect &AWorkArea, const int AId);
		TDisplayAndroid() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	class DELPHICLASS TFullScreenStateChangedListener;
	class PASCALIMPLEMENTATION TFullScreenStateChangedListener : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TAndroidScreenServices* FScreenServices;
		
	public:
		__fastcall TFullScreenStateChangedListener(TAndroidScreenServices* const AScreenServices);
		void __cdecl stateChanged(int oldState, int newState);
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TFullScreenStateChangedListener() { }
		
private:
		void *__JOnFullScreenStateChangedListener;	// Androidapi::Jni::Embarcadero::JOnFullScreenStateChangedListener 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {8EE73E7B-9BC0-4983-AFBC-9B133DB3F73B}
		operator Androidapi::Jni::Embarcadero::_di_JOnFullScreenStateChangedListener()
		{
			Androidapi::Jni::Embarcadero::_di_JOnFullScreenStateChangedListener intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Embarcadero::JOnFullScreenStateChangedListener*(void) { return (Androidapi::Jni::Embarcadero::JOnFullScreenStateChangedListener*)&__JOnFullScreenStateChangedListener; }
		#endif
		
	};
	
	
	
private:
	float FScreenScale;
	System::Types::TPointF FScreenSize;
	Androidapi::Jni::Hardware::_di_JDisplayManager FDisplayManager;
	Androidapi::Jni::Graphicscontentviewtext::_di_JWindowManager FWindowManager;
	int FDisplayCount;
	int FSystemDisplayCount;
	System::Types::TRect FWorkAreaRect;
	System::Types::TRect FDesktopRect;
	System::Generics::Collections::TList__1<TDisplayAndroid>* FDisplayList;
	TFullScreenStateChangedListener* FFullScreenStateChangedListener;
	bool FIsFullScreen;
	bool __fastcall GetDisplayInfo(const Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay Display, System::Types::TRect &BoundsRect, System::Types::TRect &WorkareaRect);
	Fmx::Types::TDisplay __fastcall FindDisplay(const Androidapi::Jni::App::_di_JActivity Activity);
	
protected:
	virtual void __fastcall RegisterServices();
	virtual void __fastcall UnregisterServices();
	void __fastcall UpdateDisplays();
	
public:
	__fastcall TAndroidScreenServices();
	__fastcall virtual ~TAndroidScreenServices();
	static float __fastcall ScaleByMetrics(const Androidapi::Jni::Util::_di_JDisplayMetrics Metrics);
	static Fmx::Types::TScreenOrientation __fastcall OrientationByDisplay(const Androidapi::Jni::Graphicscontentviewtext::_di_JDisplay Display);
	void __fastcall UpdateDisplayInformation();
	int __fastcall GetDisplayCount();
	System::Types::TRect __fastcall GetDesktopCenterRect(const System::Types::TSize &Size);
	System::Types::TRect __fastcall GetWorkAreaRect();
	System::Types::TRect __fastcall GetDesktopRect();
	Fmx::Types::TDisplay __fastcall GetDisplay(const int AIndex);
	Fmx::Types::TDisplay __fastcall DisplayFromWindow(Fmx::Types::TWindowHandle* const AHandle);
	Fmx::Types::TDisplay __fastcall DisplayFromPoint(Fmx::Types::TWindowHandle* const AHandle, const System::Types::TPoint &APoint);
	System::Types::TPointF __fastcall GetScreenSize();
	float __fastcall GetScreenScale();
	Fmx::Types::TScreenOrientation __fastcall GetScreenOrientation();
	void __fastcall SetSupportedScreenOrientations(const Fmx::Types::TScreenOrientations AOrientations);
	Fmx::Types::TDeviceDisplayMetrics __fastcall GetDisplayMetrics();
	void __fastcall SetFullScreen(Fmx::Forms::TCommonCustomForm* const AForm, const bool AValue);
	bool __fastcall GetFullScreen(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall SetShowFullScreenIcon(Fmx::Forms::TCommonCustomForm* const AForm, const bool AValue);
	__property Androidapi::Jni::Hardware::_di_JDisplayManager DisplayManager = {read=FDisplayManager};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JWindowManager WindowManager = {read=FWindowManager};
private:
	void *__IFMXFullScreenWindowService;	// Fmx::Forms::IFMXFullScreenWindowService 
	void *__IFMXDeviceMetricsService;	// Fmx::Platform::IFMXDeviceMetricsService 
	void *__IFMXScreenService;	// Fmx::Platform::IFMXScreenService 
	void *__IFMXMultiDisplayService;	// Fmx::Platform::IFMXMultiDisplayService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {103EB4B7-E899-4684-8174-2EEEE24F1E58}
	operator Fmx::Forms::_di_IFMXFullScreenWindowService()
	{
		Fmx::Forms::_di_IFMXFullScreenWindowService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Forms::IFMXFullScreenWindowService*(void) { return (Fmx::Forms::IFMXFullScreenWindowService*)&__IFMXFullScreenWindowService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CCC4D351-BA3A-4884-B4F6-4F020600F15F}
	operator Fmx::Platform::_di_IFMXDeviceMetricsService()
	{
		Fmx::Platform::_di_IFMXDeviceMetricsService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXDeviceMetricsService*(void) { return (Fmx::Platform::IFMXDeviceMetricsService*)&__IFMXDeviceMetricsService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BBA246B6-8DEF-4490-9D9C-D2CBE6251A24}
	operator Fmx::Platform::_di_IFMXScreenService()
	{
		Fmx::Platform::_di_IFMXScreenService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXScreenService*(void) { return (Fmx::Platform::IFMXScreenService*)&__IFMXScreenService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {133A6050-AC29-4233-9EE2-D49082C33BBF}
	operator Fmx::Platform::_di_IFMXMultiDisplayService()
	{
		Fmx::Platform::_di_IFMXMultiDisplayService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXMultiDisplayService*(void) { return (Fmx::Platform::IFMXMultiDisplayService*)&__IFMXMultiDisplayService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (*TScreenScaleOverrideHook)(const void * UserContext, const float DensityScale, const float DensityDPI, float &ScreenScale);

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall SetScreenScaleOverrideHook(const void * UserContext, const TScreenScaleOverrideHook Hook);
extern DELPHI_PACKAGE void __fastcall UnsetScreenScaleOverrideHook(void);
}	/* namespace Android */
}	/* namespace Screen */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_SCREEN_ANDROID)
using namespace Fmx::Platform::Screen::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_SCREEN)
using namespace Fmx::Platform::Screen;
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
#endif	// Fmx_Platform_Screen_AndroidHPP
