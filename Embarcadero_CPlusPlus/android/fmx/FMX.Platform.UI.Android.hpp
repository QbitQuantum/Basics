// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Platform.UI.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Platform_Ui_AndroidHPP
#define Fmx_Platform_Ui_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Messaging.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.Input.hpp>
#include <Androidapi.NativeActivity.hpp>
#include <Androidapi.Helpers.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Types.hpp>
#include <FMX.Types3D.hpp>
#include <FMX.KeyMapping.hpp>
#include <FMX.Helpers.Android.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Text.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Gestures.hpp>
#include <FMX.VirtualKeyboard.hpp>
#include <FMX.Consts.hpp>
#include <FMX.Utils.hpp>
#include <FMX.Platform.hpp>
#include <FMX.MultiTouch.Android.hpp>
#include <FMX.ZOrder.Android.hpp>
#include <FMX.Platform.Text.Android.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Platform
{
namespace Ui
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormRender;
class DELPHICLASS TFormManager;
class DELPHICLASS TAndroidWindowHandle;
class DELPHICLASS TWindowServiceAndroid;
class DELPHICLASS TAndroidMotionManager;
class DELPHICLASS TAndroidGestureListener;
class DELPHICLASS TAndroidDoubleTapGestureListener;
class DELPHICLASS TAndroidTextInputManager;
class DELPHICLASS TFMXTextListener;
class DELPHICLASS TTextServiceAndroid;
class DELPHICLASS TAndroidSystemAppearanceService;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFormRender : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidWindowHandle* FHandle;
	bool FIsNeededUpdate;
	void __fastcall ApplicationEventHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	
public:
	__fastcall TFormRender(TAndroidWindowHandle* const AHandle);
	__fastcall virtual ~TFormRender();
	void __cdecl run();
	void __fastcall Render();
	void __fastcall PostRender();
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

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFormManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<void *>* FZOrderForms;
	System::Generics::Collections::TList__1<void *>* FDelayedHideForm;
	void __fastcall RefreshFormsVisibility();
	bool __fastcall IsSurfaceAttached(TAndroidWindowHandle* const AHandle);
	
public:
	__fastcall TFormManager();
	__fastcall virtual ~TFormManager();
	void __fastcall RemoveForm(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall ShowForm(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall HideForm(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall BringToFront(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall SendToBack(Fmx::Forms::TCommonCustomForm* const AForm);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidWindowHandle : public Fmx::Types::TWindowHandle
{
	typedef Fmx::Types::TWindowHandle inherited;
	
	
private:
	class DELPHICLASS TFormViewListener;
	class PASCALIMPLEMENTATION TFormViewListener : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TAndroidWindowHandle* FOwner;
		
	public:
		__fastcall TFormViewListener(TAndroidWindowHandle* const AOwner);
		bool __cdecl onTouchEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
		void __cdecl onSizeChanged(int w, int h, int oldw, int oldh);
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TFormViewListener() { }
		
private:
		void *__JFormViewListener;	// Androidapi::Jni::Embarcadero::JFormViewListener 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {BF611734-2D29-4D3D-83DD-53F9D948470D}
		operator Androidapi::Jni::Embarcadero::_di_JFormViewListener()
		{
			Androidapi::Jni::Embarcadero::_di_JFormViewListener intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Embarcadero::JFormViewListener*(void) { return (Androidapi::Jni::Embarcadero::JFormViewListener*)&__JFormViewListener; }
		#endif
		
	};
	
	
	class DELPHICLASS TSurfaceFlingerRenderingObserver;
	class PASCALIMPLEMENTATION TSurfaceFlingerRenderingObserver : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		Fmx::Forms::TCommonCustomForm* FForm;
		
	public:
		__fastcall TSurfaceFlingerRenderingObserver(Fmx::Forms::TCommonCustomForm* const AForm);
		void __cdecl doFrame(__int64 frameTimeNanos);
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TSurfaceFlingerRenderingObserver() { }
		
private:
		void *__JChoreographer_FrameCallback;	// Androidapi::Jni::Graphicscontentviewtext::JChoreographer_FrameCallback 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {33BCDF1F-93C8-4BBC-AFB9-631C80E6E8E0}
		operator Androidapi::Jni::Graphicscontentviewtext::_di_JChoreographer_FrameCallback()
		{
			Androidapi::Jni::Graphicscontentviewtext::_di_JChoreographer_FrameCallback intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Graphicscontentviewtext::JChoreographer_FrameCallback*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JChoreographer_FrameCallback*)&__JChoreographer_FrameCallback; }
		#endif
		
	};
	
	
	class DELPHICLASS TSurfaceViewListener;
	class PASCALIMPLEMENTATION TSurfaceViewListener : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TAndroidWindowHandle* FOwner;
		TAndroidWindowHandle::TSurfaceFlingerRenderingObserver* FSurfaceFlingerRenderingObserver;
		
	public:
		__fastcall TSurfaceViewListener(TAndroidWindowHandle* const AOwner);
		__fastcall virtual ~TSurfaceViewListener();
		void __cdecl surfaceCreated(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder);
		void __cdecl surfaceChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder, int format, int width, int height);
		void __cdecl surfaceDestroyed(Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder holder);
private:
		void *__JSurfaceHolder_Callback;	// Androidapi::Jni::Graphicscontentviewtext::JSurfaceHolder_Callback 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {A126B8BF-D9CA-4D5B-95A5-5ADC0EAAC38B}
		operator Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder_Callback()
		{
			Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder_Callback intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Graphicscontentviewtext::JSurfaceHolder_Callback*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JSurfaceHolder_Callback*)&__JSurfaceHolder_Callback; }
		#endif
		
	};
	
	
	
private:
	bool FWasFormRealignedFirstTime;
	
private:
	Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup FFormLayout;
	Androidapi::Jni::Embarcadero::_di_JFormView FView;
	Fmx::Forms::TCommonCustomForm* FForm;
	TFormViewListener* FListener;
	TSurfaceViewListener* FSurfaceListener;
	Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder FHolder;
	Fmx::Zorder::Android::TAndroidZOrderManager* FZOrderManager;
	Fmx::Multitouch::Android::TMultiTouchManagerAndroid* FMultiTouchManager;
	TAndroidMotionManager* FMotionManager;
	TFormRender* FRender;
	System::Types::TRectF FFormBounds;
	void __fastcall SetBounds(const System::Types::TRectF &AValue);
	System::Types::TRectF __fastcall GetBounds();
	Fmx::Zorder::Android::TAndroidZOrderManager* __fastcall GetZOrderManager();
	Fmx::Multitouch::Android::TMultiTouchManagerAndroid* __fastcall GetMultiTouchManager();
	TAndroidMotionManager* __fastcall GetMotionManager();
	
private:
	void __fastcall HandleMultiTouch(const Fmx::Types::TTouches ATouches, const Fmx::Types::TTouchAction AAction, const Fmx::Types::TInteractiveGestures AEnabledGestures);
	
protected:
	virtual float __fastcall GetScale();
	
public:
	__fastcall TAndroidWindowHandle(Fmx::Forms::TCommonCustomForm* const AForm);
	__fastcall virtual ~TAndroidWindowHandle();
	bool __fastcall IsPopupForm();
	void __fastcall Hide();
	void __fastcall Show();
	void __fastcall Invalidate();
	__property bool WasFormRealignedFirstTime = {read=FWasFormRealignedFirstTime, nodefault};
	__property System::Types::TRectF Bounds = {read=GetBounds, write=SetBounds};
	__property Fmx::Forms::TCommonCustomForm* Form = {read=FForm};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JSurfaceHolder Holder = {read=FHolder};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup FormLayout = {read=FFormLayout};
	__property Androidapi::Jni::Embarcadero::_di_JFormView View = {read=FView, write=FView};
	__property Fmx::Zorder::Android::TAndroidZOrderManager* ZOrderManager = {read=GetZOrderManager};
	__property Fmx::Multitouch::Android::TMultiTouchManagerAndroid* MultiTouchManager = {read=GetMultiTouchManager};
	__property TAndroidMotionManager* MotionManager = {read=GetMotionManager};
	__property TFormRender* Render = {read=FRender};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TWindowServiceAndroid : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
	class DELPHICLASS TActivityInsetsChangedListener;
	class PASCALIMPLEMENTATION TActivityInsetsChangedListener : public Androidapi::Jnibridge::TJavaLocal
	{
		typedef Androidapi::Jnibridge::TJavaLocal inherited;
		
	private:
		TWindowServiceAndroid* FWindowService;
		
	public:
		__fastcall TActivityInsetsChangedListener(TWindowServiceAndroid* const AWindowServiceAndroid);
		void __cdecl insetsChanged(Androidapi::Jni::Graphicscontentviewtext::_di_JRect Inset);
	public:
		/* TJavaLocal.Destroy */ inline __fastcall virtual ~TActivityInsetsChangedListener() { }
		
private:
		void *__JOnActivityInsetsChangedListener;	// Androidapi::Jni::Embarcadero::JOnActivityInsetsChangedListener 
		
public:
		#if defined(MANAGED_INTERFACE_OPERATORS)
		// {EAEEA616-D505-45EB-90B2-88350F18DF07}
		operator Androidapi::Jni::Embarcadero::_di_JOnActivityInsetsChangedListener()
		{
			Androidapi::Jni::Embarcadero::_di_JOnActivityInsetsChangedListener intf;
			this->GetInterface(intf);
			return intf;
		}
		#else
		operator Androidapi::Jni::Embarcadero::JOnActivityInsetsChangedListener*(void) { return (Androidapi::Jni::Embarcadero::JOnActivityInsetsChangedListener*)&__JOnActivityInsetsChangedListener; }
		#endif
		
	};
	
	
	
public:
	static constexpr System::Int8 UndefinedScreenScale = System::Int8(0x0);
	
	
private:
	Fmx::Types::_di_IFMXTimerService FTimerService;
	Fmx::Virtualkeyboard::_di_IFMXVirtualKeyboardService FVirtualKeyboard;
	System::Classes::TComponent* FGestureControl;
	Fmx::Controls::TControl* FMouseDownControl;
	float FScale;
	System::Types::TPointF FScreenMousePos;
	Fmx::Types::_di_IControl FFocusedControl;
	Fmx::Forms::TCommonCustomForm* FCapturedForm;
	bool FSelectionInProgress;
	Fmx::Platform::Text::Android::TAndroidTextInputContextMenu* FContextMenu;
	TFormManager* FFormManager;
	TActivityInsetsChangedListener* FActivityInsetsChangedListener;
	float FStatusBarHeight;
	float __fastcall GetScale();
	float __fastcall GetStatusBarHeight();
	void __fastcall ShowContextMenu();
	void __fastcall HideContextMenu();
	float __fastcall DefineDefaultStatusBarHeight();
	void __fastcall PrepareClosePopups(Fmx::Forms::TCommonCustomForm* const ASaveForm);
	void __fastcall ClosePopups();
	void __fastcall FreeNotification(System::TObject* AObject);
	
protected:
	bool __fastcall HasStatusBar(Fmx::Forms::TCommonCustomForm* const AForm);
	
public:
	__fastcall TWindowServiceAndroid();
	__fastcall virtual ~TWindowServiceAndroid();
	__classmethod bool __fastcall IsPopupForm(Fmx::Forms::TCommonCustomForm* const AForm);
	System::Types::TPointF __fastcall PixelToPoint(const System::Types::TPointF &APixel);
	System::Types::TPointF __fastcall PointToPixel(const System::Types::TPointF &APixel);
	Fmx::Forms::TCommonCustomForm* __fastcall FindForm(Fmx::Types::TWindowHandle* const AHandle);
	Fmx::Types::TWindowHandle* __fastcall CreateWindow(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall DestroyWindow(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall ReleaseWindow(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall ShowWindow(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall HideWindow(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall BringToFront(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall SendToBack(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall Activate(Fmx::Forms::TCommonCustomForm* const AForm);
	System::Uitypes::TModalResult __fastcall ShowWindowModal(Fmx::Forms::TCommonCustomForm* const AForm);
	bool __fastcall CanShowModal();
	void __fastcall InvalidateWindowRect(Fmx::Forms::TCommonCustomForm* const AForm, const System::Types::TRectF &ARect);
	void __fastcall InvalidateImmediately(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall SetWindowRect(Fmx::Forms::TCommonCustomForm* const AForm, const System::Types::TRectF &ARect);
	System::Types::TRectF __fastcall GetWindowRect(Fmx::Forms::TCommonCustomForm* const AForm);
	System::Types::TPointF __fastcall GetClientSize(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall SetClientSize(Fmx::Forms::TCommonCustomForm* const AForm, const System::Types::TPointF &ASize);
	void __fastcall SetWindowCaption(Fmx::Forms::TCommonCustomForm* const AForm, const System::UnicodeString ACaption);
	void __fastcall SetCapture(Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall SetWindowState(Fmx::Forms::TCommonCustomForm* const AForm, const System::Uitypes::TWindowState AState);
	void __fastcall ReleaseCapture(Fmx::Forms::TCommonCustomForm* const AForm);
	System::Types::TPointF __fastcall ClientToScreen(Fmx::Forms::TCommonCustomForm* const AForm, const System::Types::TPointF &ALocalFormPoint);
	System::Types::TPointF __fastcall ScreenToClient(Fmx::Forms::TCommonCustomForm* const AForm, const System::Types::TPointF &AScreenPoint)/* overload */;
	float __fastcall GetWindowScale(Fmx::Forms::TCommonCustomForm* const AForm);
	System::Types::TPointF __fastcall GetMousePos();
	void __fastcall MouseDown(Fmx::Forms::TCommonCustomForm* const AForm, const System::Uitypes::TMouseButton AButton, const System::Classes::TShiftState AShift, const System::Types::TPointF &AClientPoint);
	void __fastcall MouseMove(Fmx::Forms::TCommonCustomForm* const AForm, const System::Classes::TShiftState AShift, const System::Types::TPointF &AClientPoint);
	void __fastcall MouseUp(Fmx::Forms::TCommonCustomForm* const AForm, const System::Uitypes::TMouseButton AButton, const System::Classes::TShiftState AShift, const System::Types::TPointF &AClientPoint, const bool ADoClick = true);
	bool __fastcall SendCMGestureMessage(Fmx::Forms::TCommonCustomForm* AForm, const Fmx::Types::TGestureEventInfo &AEventInfo);
	void __fastcall BeginSelection();
	void __fastcall EndSelection();
	TTextServiceAndroid* __fastcall GetTextService();
	void __fastcall SetFocusedControl(const Fmx::Types::_di_IControl AControl);
	__property float Scale = {read=GetScale};
	__property float StatusBarHeight = {read=GetStatusBarHeight};
	__property TFormManager* FormManager = {read=FFormManager};
	__property System::Types::TPointF ScreenMousePos = {read=FScreenMousePos, write=FScreenMousePos};
private:
	void *__IFMXMouseService;	// Fmx::Types::IFMXMouseService 
	void *__IFMXWindowService;	// Fmx::Forms::IFMXWindowService 
	void *__IFreeNotification;	// Fmx::Types::IFreeNotification 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2370205F-CF27-4DF6-9B1F-5EBC27271D5A}
	operator Fmx::Types::_di_IFMXMouseService()
	{
		Fmx::Types::_di_IFMXMouseService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IFMXMouseService*(void) { return (Fmx::Types::IFMXMouseService*)&__IFMXMouseService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {26C42398-9AFC-4D09-9541-9C71E769FC35}
	operator Fmx::Forms::_di_IFMXWindowService()
	{
		Fmx::Forms::_di_IFMXWindowService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Forms::IFMXWindowService*(void) { return (Fmx::Forms::IFMXWindowService*)&__IFMXWindowService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FEB50EAF-A3B9-4B37-8EDB-1EF9EE2F22D4}
	operator Fmx::Types::_di_IFreeNotification()
	{
		Fmx::Types::_di_IFreeNotification intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IFreeNotification*(void) { return (Fmx::Types::IFreeNotification*)&__IFreeNotification; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidMotionManager : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
private:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TMotionEvent
	{
	public:
		System::Types::TPointF Position;
		int EventAction;
		System::Classes::TShiftState Shift;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	typedef System::Generics::Collections::TList__1<TMotionEvent>* TMotionEvents;
	
	
private:
	TAndroidWindowHandle* FHandle;
	Fmx::Types::TInteractiveGestures FEnabledInteractiveGestures;
	bool FIsLongTapRecognized;
	System::Generics::Collections::TList__1<TMotionEvent>* FMotionEvents;
	bool FGestureEnded;
	Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector FGestureDetector;
	TAndroidGestureListener* FGestureListener;
	TAndroidDoubleTapGestureListener* FGestureDoubleTapListener;
	System::Types::TPointF FMouseCoord;
	System::Types::TPointF FMouseDownCoordinates;
	void __fastcall HandleMultiTouch();
	void __fastcall UpdateMousePosition();
	
protected:
	Fmx::Types::TGestureEventInfo __fastcall CreateGestureEventInfo(const Fmx::Types::TInteractiveGesture AGesture, const Fmx::Types::TInteractiveGestureFlags AFlags);
	void __fastcall ReadMotionEvent(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent, System::Generics::Collections::TList__1<TMotionEvent>* &AMotionEvents);
	void __fastcall ProcessGestureEvents(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent);
	void __fastcall ProcessDoubleTap(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent);
	void __fastcall ProcessLongTap(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent, const Fmx::Types::TInteractiveGestureFlags AFlags);
	void __fastcall ProcessMouseEvents();
	
public:
	__fastcall TAndroidMotionManager(TAndroidWindowHandle* const AHandle);
	__fastcall virtual ~TAndroidMotionManager();
	bool __fastcall HandleMotionEvent(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent);
	void __fastcall AddRecognizer(const Fmx::Types::TInteractiveGesture AGesture, Fmx::Forms::TCommonCustomForm* const AForm);
	void __fastcall RemoveRecognizer(const Fmx::Types::TInteractiveGesture AGesture, Fmx::Forms::TCommonCustomForm* const AForm);
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
class PASCALIMPLEMENTATION TAndroidGestureListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidMotionManager* FMotionManager;
	
public:
	__fastcall TAndroidGestureListener(TAndroidMotionManager* const AMotionMangager);
	bool __cdecl onDown(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onFling(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e1, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e2, float velocityX, float velocityY);
	void __cdecl onLongPress(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e1, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e2, float distanceX, float distanceY);
	void __cdecl onShowPress(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onSingleTapUp(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidGestureListener() { }
	
private:
	void *__JGestureDetector_OnGestureListener;	// Androidapi::Jni::Graphicscontentviewtext::JGestureDetector_OnGestureListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A72C80A3-7E4C-4FDD-98FC-99B328D6BFDD}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector_OnGestureListener()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector_OnGestureListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JGestureDetector_OnGestureListener*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JGestureDetector_OnGestureListener*)&__JGestureDetector_OnGestureListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidDoubleTapGestureListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidMotionManager* FMotionManager;
	
public:
	__fastcall TAndroidDoubleTapGestureListener(TAndroidMotionManager* const AMotionMangager);
	bool __cdecl onDoubleTap(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onDoubleTapEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onSingleTapConfirmed(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidDoubleTapGestureListener() { }
	
private:
	void *__JGestureDetector_OnDoubleTapListener;	// Androidapi::Jni::Graphicscontentviewtext::JGestureDetector_OnDoubleTapListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {759D27FB-6DD3-4C4C-BA8D-3814CB8278A2}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector_OnDoubleTapListener()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector_OnDoubleTapListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JGestureDetector_OnDoubleTapListener*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JGestureDetector_OnDoubleTapListener*)&__JGestureDetector_OnDoubleTapListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidTextInputManager : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	Fmx::Virtualkeyboard::_di_IFMXVirtualKeyboardService FVirtualKeyboard;
	Fmx::Keymapping::TKeyMapping* FKeyMapping;
	Androidapi::Jni::Graphicscontentviewtext::_di_JKeyCharacterMap FKeyCharacterMap;
	System::Word FDownKey;
	System::WideChar FDownKeyChar;
	bool FKeyDownHandled;
	Androidapi::Jni::Embarcadero::_di_JFMXEditText FEditText;
	Androidapi::Jni::Graphicscontentviewtext::_di_JKeyCharacterMap __fastcall ObtainKeyCharacterMap(int DeviceId);
	System::Classes::TShiftState __fastcall ShiftStateFromMetaState(const int AMetaState);
	
protected:
	Fmx::Forms::TCommonCustomForm* __fastcall FindActiveForm();
	void __fastcall KeyDown(System::Word &AKey, System::WideChar &AKeyChar, const System::Classes::TShiftState AShift);
	void __fastcall KeyUp(System::Word &AKey, System::WideChar &AKeyChar, const System::Classes::TShiftState AShift, const bool AKeyDownHandled);
	
public:
	__fastcall TAndroidTextInputManager();
	__fastcall virtual ~TAndroidTextInputManager();
	int __fastcall HandleAndroidKeyEvent(Androidapi::Input::PAInputEvent AEvent);
	Androidapi::Jni::Embarcadero::_di_JFMXEditText __fastcall GetEditText();
	Fmx::Text::TTextServiceClass __fastcall GetTextServiceClass();
	bool __fastcall RegisterKeyMapping(const System::Word PlatformKey, const System::Word VirtualKey, const Fmx::Types::TKeyKind KeyKind);
	bool __fastcall UnregisterKeyMapping(const System::Word PlatformKey);
	System::Word __fastcall PlatformKeyToVirtualKey(const System::Word PlatformKey, Fmx::Types::TKeyKind &KeyKind);
	System::Word __fastcall VirtualKeyToPlatformKey(const System::Word VirtualKey);
private:
	void *__IFMXTextService;	// Fmx::Platform::IFMXTextService 
	void *__IFMXKeyMappingService;	// Fmx::Keymapping::IFMXKeyMappingService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {A5FECE29-9A9C-4E8A-8794-89271EC71F1A}
	operator Fmx::Platform::_di_IFMXTextService()
	{
		Fmx::Platform::_di_IFMXTextService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXTextService*(void) { return (Fmx::Platform::IFMXTextService*)&__IFMXTextService; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {8908B4A3-0214-42EE-B912-0F94C2F30A1C}
	operator Fmx::Keymapping::_di_IFMXKeyMappingService()
	{
		Fmx::Keymapping::_di_IFMXKeyMappingService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Keymapping::IFMXKeyMappingService*(void) { return (Fmx::Keymapping::IFMXKeyMappingService*)&__IFMXKeyMappingService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXTextListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TTextServiceAndroid* FTextService;
	
public:
	__fastcall TFMXTextListener(TTextServiceAndroid* const ATextService)/* overload */;
	void __cdecl onTextUpdated(Androidapi::Jni::Javatypes::_di_JCharSequence text, int caretPosition);
	void __cdecl onComposingText(int beginPosition, int endPosition);
	void __cdecl onEditorAction(int actionCode);
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TFMXTextListener() { }
	
private:
	void *__JFMXTextListener;	// Androidapi::Jni::Embarcadero::JFMXTextListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {343503D5-CA05-4DAE-AABF-C112202B9CFA}
	operator Androidapi::Jni::Embarcadero::_di_JFMXTextListener()
	{
		Androidapi::Jni::Embarcadero::_di_JFMXTextListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Embarcadero::JFMXTextListener*(void) { return (Androidapi::Jni::Embarcadero::JFMXTextListener*)&__JFMXTextListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TTextServiceAndroid : public Fmx::Text::TTextService
{
	typedef Fmx::Text::TTextService inherited;
	
private:
	System::UnicodeString FText;
	Androidapi::Jni::Embarcadero::_di_JFMXEditText FTextView;
	TFMXTextListener* FTextListener;
	int FComposingBegin;
	int FComposingEnd;
	System::Classes::TStrings* FLines;
	bool FInternalUpdate;
	void __fastcall ReadLines();
	void __fastcall CalculateSelectionBounds(/* out */ int &ASelectionStart, /* out */ int &ASelectionEnd);
	bool __fastcall IsFocused();
	void __fastcall ApplicationEventHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	
protected:
	virtual void __fastcall SetText(const System::UnicodeString AValue);
	virtual System::UnicodeString __fastcall GetText();
	virtual void __fastcall SetMaxLength(const int AValue);
	virtual void __fastcall SetCharCase(const System::Uitypes::TEditCharCase AValue);
	virtual void __fastcall SetFilterChar(const System::UnicodeString AValue);
	virtual void __fastcall CaretPositionChanged();
	
public:
	void __fastcall InternalUpdate();
	void __fastcall InternalUpdateSelection();
	virtual System::UnicodeString __fastcall CombinedText();
	virtual System::Types::TPoint __fastcall TargetClausePosition();
	virtual void __fastcall EnterControl(Fmx::Types::TWindowHandle* const AFormHandle);
	virtual void __fastcall ExitControl(Fmx::Types::TWindowHandle* const AFormHandle);
	virtual void __fastcall DrawSingleLine(Fmx::Graphics::TCanvas* const ACanvas, const System::Types::TRectF &ARect, const int AFirstVisibleChar, Fmx::Graphics::TFont* const AFont, const float AOpacity, const Fmx::Graphics::TFillTextFlags AFlags, const Fmx::Types::TTextAlign ATextAlign, const Fmx::Types::TTextAlign AVTextAlign = (Fmx::Types::TTextAlign)(0x0), const bool AWordWrap = false)/* overload */;
	virtual void __fastcall DrawSingleLine(Fmx::Graphics::TCanvas* const ACanvas, const System::UnicodeString S, const System::Types::TRectF &ARect, Fmx::Graphics::TFont* const AFont, const float AOpacity, const Fmx::Graphics::TFillTextFlags AFlags, const Fmx::Types::TTextAlign ATextAlign, const Fmx::Types::TTextAlign AVTextAlign = (Fmx::Types::TTextAlign)(0x0), const bool AWordWrap = false)/* overload */;
	virtual bool __fastcall HasMarkedText();
	virtual void __fastcall BeginSelection();
	virtual void __fastcall EndSelection();
	void __fastcall ProcessUpdate(const int APos, System::UnicodeString AText);
	__fastcall virtual TTextServiceAndroid(const Fmx::Types::_di_IControl AOwner, const bool ASupportMultiLine);
	__fastcall virtual ~TTextServiceAndroid();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidSystemAppearanceService : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	Fmx::Platform::TSystemThemeKind __fastcall GetSystemThemeKind();
	System::Uitypes::TAlphaColor __fastcall GetSystemColor(const Fmx::Platform::TSystemColorType AType);
public:
	/* TObject.Create */ inline __fastcall TAndroidSystemAppearanceService() : System::TInterfacedObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidSystemAppearanceService() { }
	
private:
	void *__IFMXSystemAppearanceService;	// Fmx::Platform::IFMXSystemAppearanceService 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {AB6A83D9-0118-4C5F-95CC-351DBB5EA943}
	operator Fmx::Platform::_di_IFMXSystemAppearanceService()
	{
		Fmx::Platform::_di_IFMXSystemAppearanceService intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Platform::IFMXSystemAppearanceService*(void) { return (Fmx::Platform::IFMXSystemAppearanceService*)&__IFMXSystemAppearanceService; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::Types::TPointF __fastcall ConvertPixelToPoint(const System::Types::TPointF &APixel);
extern DELPHI_PACKAGE System::Types::TPointF __fastcall ConvertPointToPixel(const System::Types::TPointF &APoint);
}	/* namespace Android */
}	/* namespace Ui */
}	/* namespace Platform */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_UI_ANDROID)
using namespace Fmx::Platform::Ui::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PLATFORM_UI)
using namespace Fmx::Platform::Ui;
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
#endif	// Fmx_Platform_Ui_AndroidHPP
