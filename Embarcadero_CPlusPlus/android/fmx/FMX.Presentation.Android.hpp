// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Presentation_AndroidHPP
#define Fmx_Presentation_AndroidHPP

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
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Embarcadero.hpp>
#include <Androidapi.JNI.Widget.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.hpp>
#include <FMX.ZOrder.Android.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidNativeView;
class DELPHICLASS TAndroidBaseViewListener;
class DELPHICLASS TAndroidFocusChangedListener;
class DELPHICLASS TAndroidViewTouchListener;
class DELPHICLASS TAndroidViewDblTapListener;
class DELPHICLASS TAndroidViewGestureListener;
class DELPHICLASS TAndroidViewScaleGestureListener;
class DELPHICLASS TAndroidRotationGestureDetector;
template<typename TPresentation> class DELPHICLASS TAndroidPresentationProxy__1;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAndroidNativeView : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	enum class DECLSPEC_DENUM TGestureKind : unsigned char { LongTap, Pan };
	
	
private:
	Fmx::Controls::TControl* FControl;
	Fmx::Controls::Model::TDataModel* FModel;
	Fmx::Forms::TCommonCustomForm* FForm;
	float FScreenScale;
	Androidapi::Jni::Graphicscontentviewtext::_di_JView FView;
	Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup FLayout;
	Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup FChildrenLayout;
	System::Types::TSizeF FSize;
	bool FVisible;
	TAndroidFocusChangedListener* FFocusChangedListener;
	TAndroidViewTouchListener* FTouchListener;
	TAndroidViewDblTapListener* FDblTapListener;
	TAndroidViewGestureListener* FGestureListener;
	TAndroidViewScaleGestureListener* FScaleGestureListener;
	Androidapi::Jni::Graphicscontentviewtext::_di_JGestureDetector FGestureDetector;
	Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector FScaleGestureDetector;
	TAndroidRotationGestureDetector* FRotationGestureDetector;
	System::Set<TGestureKind, _DELPHI_SET_ENUMERATOR(TGestureKind::LongTap), _DELPHI_SET_ENUMERATOR(TGestureKind::Pan)> FActiveGestures;
	System::StaticArray<Fmx::Types::TGestureEventInfo, 2> FActiveGesturesInfo;
	System::Classes::TObservers* __fastcall GetObservers();
	Fmx::Zorder::Android::TAndroidZOrderManager* __fastcall GetZOrderManager();
	void __fastcall BeforeDestroyHandleListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	void __fastcall AfterCreateHandleListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	
protected:
	virtual void __fastcall SetSize(const System::Types::TSizeF &ASize);
	bool __fastcall IsActiveGesture(const TGestureKind AKind);
	bool __fastcall FindGesturedControl(const System::Types::TPointF &AScreenTouchPoint, const Fmx::Types::TInteractiveGesture AGestureKind, /* out */ Fmx::Types::_di_IGestureControl &AGestureObject);
	virtual bool __fastcall ProcessTouch(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
	virtual bool __fastcall ProcessLongTap(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, const Fmx::Types::TInteractiveGestureFlags APhase);
	virtual bool __fastcall ProcessDoubleTap(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
	bool __fastcall ProcessPan(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event, const int Distance, const Fmx::Types::TInteractiveGestureFlags APhase);
	bool __fastcall ProcessScale(const Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector detector, const Fmx::Types::TInteractiveGestureFlags APhase);
	void __fastcall RotationGestureHandler(const System::Types::TPointF &AScreenPoint, const float ADistance, const float AAngle);
	virtual bool __fastcall PointInside(const System::Types::TPointF &AScreenPoint, const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent);
	void __fastcall UpdateVisible();
	MESSAGE void __fastcall PMGetNativeObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::_di_IInterface> &AMessage);
	MESSAGE void __fastcall PMSetAbsoluteEnabled(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMSetVisible(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMGetVisible(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMSetAlpha(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<float> &AMessage);
	MESSAGE void __fastcall PMGetAlpha(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<float> &AMessage);
	MESSAGE void __fastcall PMSetSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMGetSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMIsFocused(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMDoExit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMDoEnter(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMResetFocus(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSetClipChildren(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncestorVisibleChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncestorPresentationLoaded(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncestorPresentationUnloading(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TFmxObject*> &AMessage);
	MESSAGE void __fastcall PMUnload(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMRefreshParent(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMAbsoluteChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMPointInObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TPointInObjectLocalInfo> &AMessage);
	MESSAGE void __fastcall PMChangeOrder(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMRootChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::_di_IRoot> &AMessage);
	template<typename T> T __fastcall GetView()/* overload */;
	void __fastcall UpdateFrame();
	virtual void __fastcall RefreshNativeParent();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	template<typename T> T __fastcall GetModel();
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall CreateView();
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup __fastcall CreateLayout();
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup __fastcall CreateChildrenLayout();
	virtual void __fastcall InitView();
	
public:
	__fastcall virtual TAndroidNativeView()/* overload */;
	__fastcall TAndroidNativeView(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */;
	__fastcall virtual ~TAndroidNativeView();
	bool __fastcall HasZOrderManager();
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	__property Fmx::Forms::TCommonCustomForm* Form = {read=FForm};
	__property Fmx::Zorder::Android::TAndroidZOrderManager* ZOrderManager = {read=GetZOrderManager};
	__property Fmx::Controls::Model::TDataModel* Model = {read=FModel};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup ChildrenLayout = {read=FChildrenLayout};
	__property Fmx::Controls::TControl* Control = {read=FControl};
	__property System::Classes::TObservers* Observers = {read=GetObservers};
	__property float ScreenScale = {read=FScreenScale};
	__property System::Types::TSizeF Size = {read=FSize, write=SetSize};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JViewGroup Layout = {read=FLayout};
	__property Androidapi::Jni::Graphicscontentviewtext::_di_JView View = {read=FView};
	__property bool Visible = {read=FVisible, nodefault};
};


_DECLARE_METACLASS(System::TMetaClass, TAndroidNativeViewClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidBaseViewListener : public Androidapi::Jnibridge::TJavaLocal
{
	typedef Androidapi::Jnibridge::TJavaLocal inherited;
	
private:
	TAndroidNativeView* FView;
	
public:
	__fastcall TAndroidBaseViewListener(TAndroidNativeView* const AView);
	__property TAndroidNativeView* Presentation = {read=FView};
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidBaseViewListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidFocusChangedListener : public TAndroidBaseViewListener
{
	typedef TAndroidBaseViewListener inherited;
	
public:
	void __cdecl onFocusChange(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, bool hasFocus);
public:
	/* TAndroidBaseViewListener.Create */ inline __fastcall TAndroidFocusChangedListener(TAndroidNativeView* const AView) : TAndroidBaseViewListener(AView) { }
	
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidFocusChangedListener() { }
	
private:
	void *__JView_OnFocusChangeListener;	// Androidapi::Jni::Graphicscontentviewtext::JView_OnFocusChangeListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5FFFED8A-78CC-4E8C-BD41-8F7DBC6DF4AC}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnFocusChangeListener()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnFocusChangeListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JView_OnFocusChangeListener*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JView_OnFocusChangeListener*)&__JView_OnFocusChangeListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidViewTouchListener : public TAndroidBaseViewListener
{
	typedef TAndroidBaseViewListener inherited;
	
public:
	bool __cdecl onTouch(Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
public:
	/* TAndroidBaseViewListener.Create */ inline __fastcall TAndroidViewTouchListener(TAndroidNativeView* const AView) : TAndroidBaseViewListener(AView) { }
	
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidViewTouchListener() { }
	
private:
	void *__JView_OnTouchListener;	// Androidapi::Jni::Graphicscontentviewtext::JView_OnTouchListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CE4A1789-BAF5-4C37-9A87-54BF5842504B}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnTouchListener()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JView_OnTouchListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JView_OnTouchListener*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JView_OnTouchListener*)&__JView_OnTouchListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidViewDblTapListener : public TAndroidBaseViewListener
{
	typedef TAndroidBaseViewListener inherited;
	
public:
	bool __cdecl onDoubleTap(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onDoubleTapEvent(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onSingleTapConfirmed(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
public:
	/* TAndroidBaseViewListener.Create */ inline __fastcall TAndroidViewDblTapListener(TAndroidNativeView* const AView) : TAndroidBaseViewListener(AView) { }
	
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidViewDblTapListener() { }
	
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
class PASCALIMPLEMENTATION TAndroidViewGestureListener : public TAndroidBaseViewListener
{
	typedef TAndroidBaseViewListener inherited;
	
public:
	bool __cdecl onDown(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onFling(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e1, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e2, float velocityX, float velocityY);
	void __cdecl onLongPress(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onScroll(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e1, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e2, float distanceX, float distanceY);
	void __cdecl onShowPress(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
	bool __cdecl onSingleTapUp(Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent e);
public:
	/* TAndroidBaseViewListener.Create */ inline __fastcall TAndroidViewGestureListener(TAndroidNativeView* const AView) : TAndroidBaseViewListener(AView) { }
	
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidViewGestureListener() { }
	
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
class PASCALIMPLEMENTATION TAndroidViewScaleGestureListener : public TAndroidBaseViewListener
{
	typedef TAndroidBaseViewListener inherited;
	
public:
	bool __cdecl onScale(Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector detector);
	bool __cdecl onScaleBegin(Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector detector);
	void __cdecl onScaleEnd(Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector detector);
public:
	/* TAndroidBaseViewListener.Create */ inline __fastcall TAndroidViewScaleGestureListener(TAndroidNativeView* const AView) : TAndroidBaseViewListener(AView) { }
	
public:
	/* TJavaLocal.Destroy */ inline __fastcall virtual ~TAndroidViewScaleGestureListener() { }
	
private:
	void *__JScaleGestureDetector_OnScaleGestureListener;	// Androidapi::Jni::Graphicscontentviewtext::JScaleGestureDetector_OnScaleGestureListener 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {17BA86A8-F7BA-45D9-BEFE-67F92E6F034A}
	operator Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector_OnScaleGestureListener()
	{
		Androidapi::Jni::Graphicscontentviewtext::_di_JScaleGestureDetector_OnScaleGestureListener intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Androidapi::Jni::Graphicscontentviewtext::JScaleGestureDetector_OnScaleGestureListener*(void) { return (Androidapi::Jni::Graphicscontentviewtext::JScaleGestureDetector_OnScaleGestureListener*)&__JScaleGestureDetector_OnScaleGestureListener; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TRotationGestureEvent)(const System::Types::TPointF &AScreenPoint, const float ADistance, const float AAngle);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidRotationGestureDetector : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	enum class DECLSPEC_DENUM TTouchPointerKind : unsigned char { First, Second };
	
	
private:
	static constexpr System::Int8 InvalidPointerID = System::Int8(-1);
	
	TRotationGestureEvent FCallback;
	int FPointerID1;
	int FPointerID2;
	System::Types::TPointF FInitialPoint1;
	System::Types::TPointF FInitialPoint2;
	float FAngle;
	float __fastcall AngleBetweenLines(const System::Types::TPointF &ANewPoint1, const System::Types::TPointF &ANewPoint2);
	System::Types::TPointF __fastcall ExtractTouchpoint(const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent, const TTouchPointerKind AKind);
	
public:
	__fastcall TAndroidRotationGestureDetector(const TRotationGestureEvent ACallback);
	void __fastcall ProcessTouch(Androidapi::Jni::Graphicscontentviewtext::_di_JView v, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TAndroidRotationGestureDetector() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TPresentation> class PASCALIMPLEMENTATION TAndroidPresentationProxy__1 : public Fmx::Controls::Presentation::TPresentationProxy
{
	typedef Fmx::Controls::Presentation::TPresentationProxy inherited;
	
protected:
	virtual System::TObject* __fastcall CreateReceiver();
public:
	/* TPresentationProxy.Create */ inline __fastcall virtual TAndroidPresentationProxy__1()/* overload */ : Fmx::Controls::Presentation::TPresentationProxy() { }
	/* TPresentationProxy.Create */ inline __fastcall virtual TAndroidPresentationProxy__1(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Controls::Presentation::TPresentationProxy(AModel, AControl) { }
	/* TPresentationProxy.Destroy */ inline __fastcall virtual ~TAndroidPresentationProxy__1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_ANDROID)
using namespace Fmx::Presentation::Android;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION)
using namespace Fmx::Presentation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Presentation_AndroidHPP
