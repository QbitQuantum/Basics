// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.Screen.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Platform_Screen_IosHPP
#define Fmx_Platform_Screen_IosHPP

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
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Screen
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXInterfaceOrientationChanged;
typedef System::DelphiInterface<IFMXInterfaceOrientationChanged> _di_IFMXInterfaceOrientationChanged;
class DELPHICLASS TInterfaceOrientationChangedListener;
class DELPHICLASS TCocoaTouchScreenServices;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{AAF2DF0E-C4BF-4057-8C5F-1B8A832BC39E}") IFMXInterfaceOrientationChanged  : public Iosapi::Foundation::NSObject 
{
	virtual void __cdecl DeviceOrientationChanged() = 0 ;
};

class PASCALIMPLEMENTATION TInterfaceOrientationChangedListener : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	TCocoaTouchScreenServices* FScreenService;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	
public:
	__fastcall TInterfaceOrientationChangedListener(TCocoaTouchScreenServices* const AService);
	__fastcall virtual ~TInterfaceOrientationChangedListener();
	void __cdecl DeviceOrientationChanged();
};


class PASCALIMPLEMENTATION TCocoaTouchScreenServices : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Iosapi::Uikit::_di_UIScreen FMainScreen;
	int FDisplayCount;
	System::Types::TRect FWorkAreaRect;
	System::Types::TRect FDesktopRect;
	System::Generics::Collections::TList__1<Fmx::Types::TDisplay>* FDisplayList;
	TInterfaceOrientationChangedListener* FOrientationListener;
	System::Types::TRect __fastcall CGRectToRect(const Iosapi::Foundation::NSRect &ACGRect);
	void __fastcall UpdateDisplays();
	Fmx::Types::TDisplay __fastcall FindDisplay(const Iosapi::Uikit::_di_UIScreen screen);
	
protected:
	virtual void __fastcall RegisterServices();
	virtual void __fastcall UnregisterServices();
	
public:
	__fastcall TCocoaTouchScreenServices();
	__fastcall virtual ~TCocoaTouchScreenServices();
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
	__property Iosapi::Uikit::_di_UIScreen MainScreen = {read=FMainScreen};
private:
	void *__IFMXDeviceMetricsService;	// Fmx::Platform::IFMXDeviceMetricsService 
	void *__IFMXScreenService;	// Fmx::Platform::IFMXScreenService 
	void *__IFMXMultiDisplayService;	// Fmx::Platform::IFMXMultiDisplayService 
	
public:
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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Screen */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_SCREEN_IOS)
using namespace Fmx::Platform::Screen::Ios;
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
#endif	// Fmx_Platform_Screen_IosHPP
