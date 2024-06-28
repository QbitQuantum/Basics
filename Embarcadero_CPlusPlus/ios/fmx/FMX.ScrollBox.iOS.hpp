// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ScrollBox.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Scrollbox_IosHPP
#define Fmx_Scrollbox_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.TypInfo.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.BehaviorManager.hpp>
#include <FMX.Controls.Model.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Scrollbox
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXUIScrollView;
typedef System::DelphiInterface<IFMXUIScrollView> _di_IFMXUIScrollView;
class DELPHICLASS TiOSScrollBox;
class DELPHICLASS TiOSScrollBoxDelegate;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{0403CDE7-1347-4E4F-9AA8-0AF4F2D437B3}") IFMXUIScrollView  : public Iosapi::Uikit::UIScrollView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	virtual void __cdecl HandlePan(Iosapi::Uikit::_di_UIPanGestureRecognizer gestureRecognizer) = 0 ;
	HIDESBASE virtual bool __cdecl gestureRecognizerShouldBegin(Iosapi::Uikit::_di_UIGestureRecognizer gestureRecognizer) = 0 ;
};

class PASCALIMPLEMENTATION TiOSScrollBox : public Fmx::Presentation::Ios::TiOSNativeView
{
	typedef Fmx::Presentation::Ios::TiOSNativeView inherited;
	
private:
	Fmx::Scrollbox::TCustomScrollBoxModel* FModel;
	TiOSScrollBoxDelegate* FDelegate;
	Iosapi::Uikit::_di_UIPanGestureRecognizer FPanRecognizer;
	bool FPanGestureRecognized;
	HIDESBASE Iosapi::Uikit::_di_UIScrollView __fastcall GetView();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual TiOSScrollBoxDelegate* __fastcall CreateDelegate();
	MESSAGE void __fastcall MMBouncesChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Behaviormanager::TBehaviorBoolean> &AMessage);
	MESSAGE void __fastcall MMShowScrollBarChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMScrollEnabledChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMSetContentBounds(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TRectF> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMSetContent(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollContent*> &Message);
	MESSAGE void __fastcall PMScrollInRect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TCustomScrollBoxModel::TInViewRectInfo> &AMessage);
	MESSAGE void __fastcall PMScrollBy(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TCustomScrollBoxModel::TScrollByInfo> &AMessage);
	MESSAGE void __fastcall PMSetViewPortPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &AMessage);
	MESSAGE void __fastcall PMGetViewPortPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &AMessage);
	MESSAGE void __fastcall PMGetViewPortSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	
public:
	__fastcall virtual TiOSScrollBox()/* overload */;
	__fastcall virtual ~TiOSScrollBox();
	void __cdecl HandlePan(Iosapi::Uikit::_di_UIPanGestureRecognizer gestureRecognizer);
	bool __cdecl gestureRecognizerShouldBegin(Iosapi::Uikit::_di_UIGestureRecognizer gestureRecognizer);
	HIDESBASE void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	__property TiOSScrollBoxDelegate* Delegate = {read=FDelegate};
	__property Fmx::Scrollbox::TCustomScrollBoxModel* Model = {read=FModel};
	__property Iosapi::Uikit::_di_UIScrollView View = {read=GetView};
	__property Iosapi::Uikit::_di_UIPanGestureRecognizer PanRecognizer = {read=FPanRecognizer};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSScrollBox(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Ios::TiOSNativeView(AModel, AControl) { }
	
};


class PASCALIMPLEMENTATION TiOSScrollBoxDelegate : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	Fmx::Scrollbox::TCustomScrollBoxModel* FModel;
	Fmx::Controls::TControl* FControl;
	Fmx::Scrollbox::TScrollContent* FContent;
	Iosapi::Foundation::NSPoint FPreviousOffset;
	
public:
	void __cdecl scrollViewDidEndDecelerating(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewDidEndDragging(Iosapi::Uikit::_di_UIScrollView scrollView, bool willDecelerate);
	void __cdecl scrollViewDidEndScrollingAnimation(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewDidEndZooming(Iosapi::Uikit::_di_UIScrollView scrollView, Iosapi::Uikit::_di_UIView withView, double atScale);
	void __cdecl scrollViewDidScroll(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewDidScrollToTop(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewDidZoom(Iosapi::Uikit::_di_UIScrollView scrollView);
	bool __cdecl scrollViewShouldScrollToTop(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewWillBeginDecelerating(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewWillBeginDragging(Iosapi::Uikit::_di_UIScrollView scrollView);
	void __cdecl scrollViewWillBeginZooming(Iosapi::Uikit::_di_UIScrollView scrollView, Iosapi::Uikit::_di_UIView withView);
	void __cdecl scrollViewWillEndDragging(Iosapi::Uikit::_di_UIScrollView scrollView, Iosapi::Foundation::NSPoint withVelocity, void * targetContentOffset);
	Iosapi::Uikit::_di_UIView __cdecl viewForZoomingInScrollView(Iosapi::Uikit::_di_UIScrollView scrollView);
	bool __fastcall HasModel();
	__property Fmx::Controls::TControl* Control = {read=FControl, write=FControl};
	__property Fmx::Scrollbox::TScrollContent* Content = {read=FContent, write=FContent};
	__property Fmx::Scrollbox::TCustomScrollBoxModel* Model = {read=FModel, write=FModel};
protected:
	/* TOCLocal.Create */ inline __fastcall TiOSScrollBoxDelegate() : Macapi::Objectivec::TOCLocal() { }
	
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TiOSScrollBoxDelegate() { }
	
private:
	void *__UIScrollViewDelegate;	// Iosapi::Uikit::UIScrollViewDelegate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {2DA8B00F-F141-48BC-9AD0-3313E4958831}
	operator Iosapi::Uikit::_di_UIScrollViewDelegate()
	{
		Iosapi::Uikit::_di_UIScrollViewDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Iosapi::Uikit::UIScrollViewDelegate*(void) { return (Iosapi::Uikit::UIScrollViewDelegate*)&__UIScrollViewDelegate; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Scrollbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SCROLLBOX_IOS)
using namespace Fmx::Scrollbox::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SCROLLBOX)
using namespace Fmx::Scrollbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Scrollbox_IosHPP
