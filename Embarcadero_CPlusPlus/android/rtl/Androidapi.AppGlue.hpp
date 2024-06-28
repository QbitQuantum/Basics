// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.AppGlue.pas' rev: 34.00 (Android)

#ifndef Androidapi_AppglueHPP
#define Androidapi_AppglueHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Posix.SysTypes.hpp>
#include <Posix.Stdlib.hpp>
#include <Posix.Dlfcn.hpp>
#include <Androidapi.Configuration.hpp>
#include <Androidapi.Looper.hpp>
#include <Androidapi.Input.hpp>
#include <Androidapi.Rect.hpp>
#include <Androidapi.NativeWindow.hpp>
#include <Androidapi.NativeActivity.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Appglue
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidApplicationGlue;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TAndroidApplicationCommand : unsigned char { Start, Resume, Stop, Pause, InputChanged, InitWindow, TermWindow, WindowResized, WindowRedrawNeeded, GainedFocus, LostFocus, ConfigChanged, SaveState, LowMemory, Destroy };

typedef System::Set<TAndroidApplicationCommand, TAndroidApplicationCommand::Start, TAndroidApplicationCommand::Destroy> TAndroidApplicationCommands;

typedef void __fastcall (__closure *TOnApplicationCommand)(TAndroidApplicationGlue* const App, const TAndroidApplicationCommand ACommand);

typedef int __fastcall (__closure *TOnInputEvent)(TAndroidApplicationGlue* const App, const Androidapi::Input::PAInputEvent AEvent);

typedef void __fastcall (__closure *TOnContentRectChanged)(TAndroidApplicationGlue* const App, const System::Types::TRect &ARect);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidApplicationGlue : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static TAndroidApplicationGlue* FApplication;
	ANativeActivity *FActivity;
	ALooper *FLooper;
	AInputQueue *FInputQueue;
	AConfiguration *FConfig;
	ANativeWindow *FWindow;
	void *FSavedState;
	NativeUInt FSavedStateSize;
	TOnInputEvent FOnInputEvent;
	TOnApplicationCommand FOnApplicationCommandEvent;
	TOnContentRectChanged FOnContentRectEvent;
	Androidapi::Nativeactivity::PANativeActivityCallbacks __fastcall GetActivityCallbacks();
	void __fastcall BindCallbacks();
	void __fastcall UnbindCallbacks();
	void __fastcall SetInputQueue(const Androidapi::Input::PAInputQueue AInputQueue);
	void __fastcall SetWindow(const Androidapi::Nativewindow::PANativeWindow AWindow);
	static void __cdecl OnCreate(Androidapi::Nativeactivity::PANativeActivity activity, void * savedState, NativeUInt savedStateSize);
	static void __cdecl OnStart(Androidapi::Nativeactivity::PANativeActivity activity);
	static void __cdecl OnResume(Androidapi::Nativeactivity::PANativeActivity activity);
	static void __cdecl OnPause(Androidapi::Nativeactivity::PANativeActivity activity);
	static void __cdecl OnStop(Androidapi::Nativeactivity::PANativeActivity activity);
	static void __cdecl OnDestroy(Androidapi::Nativeactivity::PANativeActivity activity);
	static void __cdecl OnInputQueueCreated(Androidapi::Nativeactivity::PANativeActivity activity, Androidapi::Input::PAInputQueue queue);
	static void __cdecl OnInputQueueDestroyed(Androidapi::Nativeactivity::PANativeActivity activity, Androidapi::Input::PAInputQueue queue);
	static int __cdecl InputEventHandler(int FileDescriptor, int Events, void * Data);
	static void __cdecl onNativeWindowCreated(Androidapi::Nativeactivity::PANativeActivity activity, Androidapi::Nativewindow::PANativeWindow window);
	static void __cdecl onNativeWindowDestroyed(Androidapi::Nativeactivity::PANativeActivity activity, Androidapi::Nativewindow::PANativeWindow window);
	static void __cdecl onWindowFocusChanged(Androidapi::Nativeactivity::PANativeActivity activity, int focused);
	static void __cdecl onNativeWindowRedrawNeeded(Androidapi::Nativeactivity::PANativeActivity activity, Androidapi::Nativewindow::PANativeWindow window);
	static void __cdecl onNativeWindowResized(Androidapi::Nativeactivity::PANativeActivity activity, Androidapi::Nativewindow::PANativeWindow window);
	static void __cdecl onContentRectChanged(Androidapi::Nativeactivity::PANativeActivity Activity, Androidapi::Rect::PARect Rect);
	static void __cdecl onConfigurationChanged(Androidapi::Nativeactivity::PANativeActivity activity);
	static void __cdecl onLowMemory(Androidapi::Nativeactivity::PANativeActivity activity);
	static void * __cdecl onSaveInstanceState(Androidapi::Nativeactivity::PANativeActivity activity, Posix::Stddef::Psize_t outLen);
	
protected:
	virtual void __fastcall DoApplicationCommandChanged(const TAndroidApplicationCommand ACommand);
	virtual void __fastcall DoContentRectChanged(const System::Types::TRect &ARect);
	void __fastcall AllocatedSavedState(void * ASavedState, NativeUInt ASavedStateSize);
	void __fastcall FreeSavedState();
	__property Androidapi::Nativeactivity::PANativeActivityCallbacks Callbacks = {read=GetActivityCallbacks};
	
public:
	__fastcall TAndroidApplicationGlue(const Androidapi::Nativeactivity::PANativeActivity AActivity, void * savedState, NativeUInt savedStateSize);
	__fastcall virtual ~TAndroidApplicationGlue();
	__classmethod virtual System::TObject* __fastcall NewInstance();
	virtual void __fastcall FreeInstance();
	/* static */ __property TAndroidApplicationGlue* Current = {read=FApplication};
	__property Androidapi::Nativeactivity::PANativeActivity NativeActivity = {read=FActivity};
	__property Androidapi::Configuration::PAConfiguration Config = {read=FConfig};
	__property Androidapi::Input::PAInputQueue InputQueue = {write=SetInputQueue};
	__property Androidapi::Looper::PALooper Looper = {read=FLooper};
	__property void * SavedState = {read=FSavedState, write=FSavedState};
#ifndef __aarch64__
	__property NativeUInt SavedStateSize = {read=FSavedStateSize, write=FSavedStateSize, nodefault};
#else /* __aarch64__ */
	__property NativeUInt SavedStateSize = {read=FSavedStateSize, write=FSavedStateSize};
#endif /* __aarch64__ */
	__property Androidapi::Nativewindow::PANativeWindow Window = {read=FWindow};
	__property TOnApplicationCommand OnApplicationCommandEvent = {read=FOnApplicationCommandEvent, write=FOnApplicationCommandEvent};
	__property TOnContentRectChanged OnContentRectEvent = {read=FOnContentRectEvent, write=FOnContentRectEvent};
	__property TOnInputEvent OnInputEvent = {read=FOnInputEvent, write=FOnInputEvent};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 LOOPER_ID_INPUT = System::Int8(0x2);
static constexpr System::Int8 LOOPER_ID_USER = System::Int8(0x3);
extern DELPHI_PACKAGE void __fastcall app_dummy(void);
}	/* namespace Appglue */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_APPGLUE)
using namespace Androidapi::Appglue;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_AppglueHPP
