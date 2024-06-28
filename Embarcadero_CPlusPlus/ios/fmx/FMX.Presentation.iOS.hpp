// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Presentation_IosHPP
#define Fmx_Presentation_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Messaging.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ZOrder.iOS.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Model.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXUIClipView;
typedef System::DelphiInterface<IFMXUIClipView> _di_IFMXUIClipView;
class DELPHICLASS TiOSClipView;
__interface DELPHIINTERFACE IFMXUIView;
typedef System::DelphiInterface<IFMXUIView> _di_IFMXUIView;
class DELPHICLASS TiOSNativeView;
__interface DELPHIINTERFACE IFMXUIControl;
typedef System::DelphiInterface<IFMXUIControl> _di_IFMXUIControl;
class DELPHICLASS TiOSNativeControl;
template<typename TPresentation> class DELPHICLASS TiOSPresentationProxy__1;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{C045708E-2F18-483F-A214-E58D6199442C}") IFMXUIClipView  : public Iosapi::Uikit::UIView 
{
	HIDESBASE virtual bool __cdecl pointInside(Iosapi::Foundation::NSPoint point, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSClipView : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	TiOSNativeView* FContentView;
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	
public:
	bool __cdecl pointInside(Iosapi::Foundation::NSPoint point, Iosapi::Uikit::_di_UIEvent withEvent);
	__fastcall TiOSClipView(TiOSNativeView* const AContentView);
	__fastcall virtual ~TiOSClipView();
	__property TiOSNativeView* ContentView = {read=FContentView};
};


__interface  INTERFACE_UUID("{BA60202C-47E6-4FD2-9999-30EC62C6384C}") IFMXUIView  : public Iosapi::Uikit::UIView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSNativeView : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	Iosapi::Uikit::_di_UIView FParentView;
	Fmx::Controls::TControl* FControl;
	Fmx::Controls::Model::TDataModel* FModel;
	Fmx::Controls::TControl* FParentPlatformControl;
	Fmx::Forms::TCommonCustomForm* FForm;
	TiOSClipView* FClipView;
	bool FIsParentNativeForm;
	System::Types::TSizeF FSize;
	bool FVisible;
	bool FIgnoreResetFocus;
	System::Types::TRectF __fastcall GetAncestorClipRect();
	System::Classes::TObservers* __fastcall GetObservers();
	Iosapi::Uikit::_di_UIView __fastcall GetView()/* overload */;
	Iosapi::Uikit::_di_UIView __fastcall GetClipView();
	void __fastcall SendDblTapToGestureControl(const System::Types::TPointF &TouchPoint);
	Fmx::Zorder::Ios::TiOSZOrderManager* __fastcall GetZOrderManager();
	void __fastcall BeforeDestroyHandleListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	void __fastcall AfterCreateHandleListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	void __fastcall FormChangingFocusControlListener(System::TObject* const Sender, System::Messaging::TMessageBase* const AMessage);
	
protected:
	virtual void __fastcall InitView();
	Iosapi::Foundation::NSRect __fastcall GetViewFrame();
	Iosapi::Uikit::_di_UIView __fastcall GetFormView(Fmx::Forms::TCommonCustomForm* const AForm);
	virtual void __fastcall SetSize(const System::Types::TSizeF &ASize);
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
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
	MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMSetClipChildren(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncesstorVisibleChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncestorPresentationLoaded(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMAncestorPresentationUnloading(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TFmxObject*> &AMessage);
	MESSAGE void __fastcall PMUnload(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMRefreshParent(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMAbsoluteChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMPointInObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TPointInObjectLocalInfo> &AMessage);
	MESSAGE void __fastcall PMChangeOrder(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMRootChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::_di_IRoot> &AMessage);
	template<typename T> T __fastcall GetView()/* overload */;
	virtual bool __fastcall FindAncestorPresentedControl(/* out */ Fmx::Controls::TControl* &APlatformControl);
	virtual bool __fastcall FindParentView(/* out */ Iosapi::Uikit::_di_UIView &AParentView);
	void __fastcall UpdateFrame();
	virtual void __fastcall RefreshNativeParent();
	bool __fastcall IsParentViewChanged();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	template<typename T> T __fastcall GetModel();
	
public:
	System::Types::TPointF __fastcall ExtractFirstTouchPoint(Iosapi::Foundation::_di_NSSet touches);
	void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	virtual bool __cdecl pointInside(Iosapi::Foundation::NSPoint point, Iosapi::Uikit::_di_UIEvent withEvent);
	__fastcall virtual TiOSNativeView()/* overload */;
	__fastcall virtual TiOSNativeView(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */;
	__fastcall virtual ~TiOSNativeView();
	bool __fastcall HasZOrderManager();
	bool __fastcall HasControl _DEPRECATED_ATTRIBUTE1("Native presentation guarantees the availability of the Control during the presentation's lifetime.") ();
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	System::Types::TPointF __fastcall LocalToParentView(const System::Types::TPointF &ALocalPoint);
	bool __fastcall PressKey(const System::Word AKey, const System::WideChar AKeyChar, const System::Classes::TShiftState AShift);
	__property bool IsParentNativeForm = {read=FIsParentNativeForm, nodefault};
	__property Fmx::Forms::TCommonCustomForm* Form = {read=FForm};
	__property System::Types::TRectF AncestorClipRect = {read=GetAncestorClipRect};
	__property Fmx::Controls::TControl* Control = {read=FControl};
	__property Iosapi::Uikit::_di_UIView ClipView = {read=GetClipView};
	__property System::Classes::TObservers* Observers = {read=GetObservers};
	__property Fmx::Controls::TControl* ParentControl = {read=FParentPlatformControl};
	__property Iosapi::Uikit::_di_UIView ParentView = {read=FParentView};
	__property System::Types::TSizeF Size = {read=FSize, write=SetSize};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
	__property Iosapi::Foundation::NSRect ViewFrame = {read=GetViewFrame};
	__property bool Visible = {read=FVisible, nodefault};
	__property Fmx::Zorder::Ios::TiOSZOrderManager* ZOrderManager = {read=GetZOrderManager};
	__property Fmx::Controls::Model::TDataModel* Model = {read=FModel};
	__property bool IgnoreResetFocus = {read=FIgnoreResetFocus, nodefault};
};


_DECLARE_METACLASS(System::TMetaClass, TiOSNativeViewClass);

__interface  INTERFACE_UUID("{6C2C163B-3646-4A79-82A6-4FDFB60CF5E5}") IFMXUIControl  : public IFMXUIView 
{
	
};

class PASCALIMPLEMENTATION TiOSNativeControl : public TiOSNativeView
{
	typedef TiOSNativeView inherited;
	
private:
	HIDESBASE Iosapi::Uikit::_di_UIControl __fastcall GetView();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	void __fastcall RegisterNativeEventHandler(const System::UnicodeString ASelector, const unsigned long AEvents);
	void __fastcall UnRegisterNativeEventHandler(const System::UnicodeString ASelector, const unsigned long AEvents);
	
public:
	virtual void __cdecl ControlEventEditingDidBegin();
	__property Iosapi::Uikit::_di_UIControl View = {read=GetView};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSNativeControl()/* overload */ : TiOSNativeView() { }
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSNativeControl(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : TiOSNativeView(AModel, AControl) { }
	/* TiOSNativeView.Destroy */ inline __fastcall virtual ~TiOSNativeControl() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TPresentation> class PASCALIMPLEMENTATION TiOSPresentationProxy__1 : public Fmx::Controls::Presentation::TPresentationProxy
{
	typedef Fmx::Controls::Presentation::TPresentationProxy inherited;
	
protected:
	virtual System::TObject* __fastcall CreateReceiver();
public:
	/* TPresentationProxy.Create */ inline __fastcall virtual TiOSPresentationProxy__1()/* overload */ : Fmx::Controls::Presentation::TPresentationProxy() { }
	/* TPresentationProxy.Create */ inline __fastcall virtual TiOSPresentationProxy__1(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Controls::Presentation::TPresentationProxy(AModel, AControl) { }
	/* TPresentationProxy.Destroy */ inline __fastcall virtual ~TiOSPresentationProxy__1() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_IOS)
using namespace Fmx::Presentation::Ios;
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
#endif	// Fmx_Presentation_IosHPP
