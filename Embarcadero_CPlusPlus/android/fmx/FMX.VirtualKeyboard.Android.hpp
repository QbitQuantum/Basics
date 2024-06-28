// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.VirtualKeyboard.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Virtualkeyboard_AndroidHPP
#define Fmx_Virtualkeyboard_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Messaging.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <FMX.Types.hpp>
#include <FMX.VirtualKeyboard.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Virtualkeyboard
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TKeyboardStateChangedListener;
class DELPHICLASS TVirtualKeyboardAndroid;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TKeyboardStateChangedListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TVirtualKeyboardAndroid* FKeyboardService;
	bool FNeedNotifyAboutFrameChanges;
	System::Types::TRect FPreviousVKRect;
	
public:
	__fastcall TKeyboardStateChangedListener(TVirtualKeyboardAndroid* const AService);
	void __cdecl onVirtualKeyboardWillShown();
	void __cdecl onVirtualKeyboardFrameChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JRect newFrame);
	void __cdecl onVirtualKeyboardWillHidden();
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TKeyboardStateChangedListener() { }
	
private:
	void *__JOnKeyboardStateChangedListener;	// Androidapi::Jni::Embarcadero::JOnKeyboardStateChangedListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {F85EB0C6-02EB-4DF3-9E2E-B320BA607CD3}
	operator Androidapi::Jni::Embarcadero::_di_JOnKeyboardStateChangedListener()
	{
		Androidapi::Jni::Embarcadero::_di_JOnKeyboardStateChangedListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Embarcadero::JOnKeyboardStateChangedListener*(void) { return (Androidapi::Jni::Embarcadero::JOnKeyboardStateChangedListener*)&__JOnKeyboardStateChangedListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TVirtualKeyboardAndroid : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	TKeyboardStateChangedListener* FKeyboardStateListener;
	bool FTransient;
	void __fastcall RegisterService();
	void __fastcall UnregisterService();
	
protected:
	bool __fastcall IsAutoShow();
	Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall DefineNativeView(Fmx::Types::TFmxObject* const AObject);
	void __fastcall SendNotificationAboutKeyboardEvent(const System::Types::TRect &AVKRect);
	
public:
	__fastcall TVirtualKeyboardAndroid();
	__fastcall virtual ~TVirtualKeyboardAndroid();
	bool __fastcall ShowVirtualKeyboard(Fmx::Types::TFmxObject* const AControl);
	bool __fastcall HideVirtualKeyboard();
	Fmx::Types::TVirtualKeyboardStates __fastcall GetVirtualKeyboardState();
	void __fastcall SetTransientState(bool Value);
	__property Fmx::Types::TVirtualKeyboardStates VirtualKeyboardState = {read=GetVirtualKeyboardState, nodefault};
private:
	void *__IFMXVirtualKeyboardService;	// Fmx::Virtualkeyboard::IFMXVirtualKeyboardService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BB6F6668-C582-42E4-A766-863C1B9139D2}
	operator Fmx::Virtualkeyboard::_di_IFMXVirtualKeyboardService()
	{
		Fmx::Virtualkeyboard::_di_IFMXVirtualKeyboardService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Virtualkeyboard::IFMXVirtualKeyboardService*(void) { return (Fmx::Virtualkeyboard::IFMXVirtualKeyboardService*)&__IFMXVirtualKeyboardService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Virtualkeyboard */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_VIRTUALKEYBOARD_ANDROID)
using namespace Fmx::Virtualkeyboard::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_VIRTUALKEYBOARD)
using namespace Fmx::Virtualkeyboard;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Virtualkeyboard_AndroidHPP
