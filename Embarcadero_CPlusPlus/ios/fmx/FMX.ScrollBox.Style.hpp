// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ScrollBox.Style.pas' rev: 34.00 (iOS)

#ifndef Fmx_Scrollbox_StyleHPP
#define Fmx_Scrollbox_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Ani.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.InertialMovement.hpp>
#include <System.Math.Vectors.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.BehaviorManager.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Scrollbox
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TScrollCalculations;
__interface DELPHIINTERFACE IScrollableContent;
typedef System::DelphiInterface<IScrollableContent> _di_IScrollableContent;
class DELPHICLASS TStyledCustomScrollBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TScrollCalculations : public Fmx::Inertialmovement::TAniCalculations
{
	typedef Fmx::Inertialmovement::TAniCalculations inherited;
	
private:
	TStyledCustomScrollBox* FScrollBox;
	
protected:
	virtual void __fastcall DoChanged();
	virtual void __fastcall DoStart();
	virtual void __fastcall DoStop();
	
public:
	__fastcall virtual TScrollCalculations(System::Classes::TPersistent* AOwner);
	__property TStyledCustomScrollBox* ScrollBox = {read=FScrollBox};
public:
	/* TAniCalculations.Destroy */ inline __fastcall virtual ~TScrollCalculations() { }
	
};


__interface IScrollableContent  : public System::IInterface 
{
	virtual System::Types::TPointF __fastcall GetViewportPosition() = 0 ;
	virtual void __fastcall SetViewportPosition(const System::Types::TPointF &Value) = 0 ;
	virtual System::Types::TSizeF __fastcall GetViewportSize() = 0 ;
	virtual void __fastcall SetContentSize(const System::Types::TSizeF &ASize) = 0 ;
	virtual System::Types::TSizeF __fastcall GetContentSize() = 0 ;
	__property System::Types::TSizeF ContentSize = {read=GetContentSize, write=SetContentSize};
	__property System::Types::TPointF ViewportPosition = {read=GetViewportPosition};
	__property System::Types::TSizeF ViewportSize = {read=GetViewportSize};
};

class PASCALIMPLEMENTATION TStyledCustomScrollBox : public Fmx::Presentation::Style::TStyledPresentation
{
	typedef Fmx::Presentation::Style::TStyledPresentation inherited;
	
	
private:
	struct DECLSPEC_DRECORD TScrollInfo
	{
	public:
		Fmx::Stdctrls::TScrollBar* Scroll;
		Fmx::Types::TAlignLayout Align;
		System::Types::TRectF Margins;
	};
	
	
	
private:
	static constexpr System::Int8 SmallChangeFraction = System::Int8(0x5);
	
	static System::Uitypes::TAlphaColor DesignBorderColor;
	Fmx::Platform::_di_IFMXSystemInformationService FSystemInfoSrv;
	Fmx::Scrollbox::TScrollContent* FContent;
	System::Types::TPointF FLastViewportPosition;
	bool FInInternalAlign;
	System::Types::TSizeF FCachedContentSize;
	System::Types::TSizeF FOriginalContentLayoutSize;
	TScrollInfo FHScrollInfo;
	TScrollInfo FVScrollInfo;
	System::Types::TRectF FContentMargins;
	bool FVDisablePaint;
	bool FHDisablePaint;
	bool FGDisablePaint;
	bool FMouseEvents;
	bool FContentCalculated;
	TScrollCalculations* FAniCalculations;
	Fmx::Controls::TControl* FBackground;
	Fmx::Controls::TControl* FContentLayout;
	Fmx::Controls::TControl* FSizeGripContent;
	Fmx::Controls::TControl* FSizeGripParent;
	Fmx::Controls::TControl* FSizeGrip;
	Fmx::Platform::TScrollingBehaviours __fastcall GetScrollingBehaviours();
	Fmx::Types::TAlignLayout __fastcall GetHScrollAlign();
	Fmx::Types::TAlignLayout __fastcall GetVScrollAlign();
	System::Types::TRectF __fastcall GetHScrollMargins();
	System::Types::TRectF __fastcall GetVScrollMargins();
	float __fastcall GetSceneScale();
	Fmx::Stdctrls::TScrollBar* __fastcall GetVScrollBar();
	Fmx::Stdctrls::TScrollBar* __fastcall GetHScrollBar();
	HIDESBASE Fmx::Scrollbox::TCustomScrollBoxModel* __fastcall GetModel();
	void __fastcall UpdateSizeGrip();
	void __fastcall UpdateVScrollBar(const float Value, const float ViewportSize);
	void __fastcall UpdateHScrollBar(const float Value, const float ViewportSize);
	void __fastcall InternalAlign();
	void __fastcall HScrollChangeProc(System::TObject* Sender);
	void __fastcall VScrollChangeProc(System::TObject* Sender);
	void __fastcall MousePosToAni(float &X, float &Y);
	void __fastcall SaveDisablePaint();
	void __fastcall RestoreDisablePaint();
	void __fastcall SetDisablePaint();
	void __fastcall StartScrolling();
	void __fastcall StopScrolling();
	void __fastcall UpdateOriginalContentLayoutSize(const bool Force);
	void __fastcall UpdateAutoHide();
	void __fastcall UpdateBounces();
	void __fastcall UpdateTouchTracking();
	void __fastcall UpdateScrollAnimation();
	void __fastcall UpdateScrollBarsEnabled();
	System::Types::TPointF __fastcall GetViewportPosition();
	void __fastcall SetViewportPosition(const System::Types::TPointF &Value);
	System::Types::TSizeF __fastcall GetViewportSize();
	void __fastcall SetContentSize(const System::Types::TSizeF &ASize);
	System::Types::TSizeF __fastcall GetContentSize();
	MESSAGE void __fastcall MMAutoHideChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Behaviormanager::TBehaviorBoolean> &Message);
	MESSAGE void __fastcall MMBouncesChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Behaviormanager::TBehaviorBoolean> &Message);
	MESSAGE void __fastcall MMEnabledScrollChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMShowScrollBarsChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMShowSizeGripChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &Message);
	MESSAGE void __fastcall MMGetViewportPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &Message);
	MESSAGE void __fastcall MMSetViewportPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &Message);
	MESSAGE void __fastcall MMGetViewportSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &Message);
	MESSAGE void __fastcall MMScrollAnimationChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Behaviormanager::TBehaviorBoolean> &Message);
	MESSAGE void __fastcall MMScrollDirectionsChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollDirections> &Message);
	MESSAGE void __fastcall MMSetContentBounds(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TRectF> &Message);
	MESSAGE void __fastcall MMTouchTrackingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Behaviormanager::TBehaviorBoolean> &Message);
	MESSAGE void __fastcall PMScrollBy(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TCustomScrollBoxModel::TScrollByInfo> &Message);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMSetContent(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollContent*> &Message);
	MESSAGE void __fastcall PMGetContentLayout(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::TControl*> &Message);
	MESSAGE void __fastcall PMGetVScrollBar(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Stdctrls::TScrollBar*> &Message);
	MESSAGE void __fastcall PMGetHScrollBar(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Stdctrls::TScrollBar*> &Message);
	MESSAGE void __fastcall PMGetAniCalculations(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Inertialmovement::TAniCalculations*> &Message);
	MESSAGE void __fastcall PMMouseWheel(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TMouseWheelInfo> &Message);
	MESSAGE void __fastcall PMBeginPaintChildren(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMEndPaintChildren(System::TDispatchMessage &Message);
	MESSAGE void __fastcall PMScrollInRect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TCustomScrollBoxModel::TInViewRectInfo> &AMessage);
	
protected:
	virtual void __fastcall AniMouseDown(const bool Touch, const float X, const float Y);
	virtual void __fastcall AniMouseMove(const bool Touch, const float X, const float Y);
	virtual void __fastcall AniMouseUp(const bool Touch, const float X, const float Y);
	virtual void __fastcall DoRealign();
	virtual void __fastcall DoHScrollChange();
	virtual void __fastcall DoVScrollChange();
	virtual void __fastcall DoViewportPositionChange(const System::Types::TPointF &OldViewportPosition, const System::Types::TPointF &NewViewportPosition, const bool ContentSizeChanged);
	virtual void __fastcall Paint();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual TScrollCalculations* __fastcall CreateAniCalculations();
	virtual void __fastcall DoRealignContent(const System::Types::TRectF &ContentRect);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoMouseLeave();
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	virtual void __fastcall CMGesture(Fmx::Types::TGestureEventInfo &EventInfo);
	void __fastcall ReloadScrollBars();
	__property Fmx::Types::TAlignLayout HScrollAlign = {read=GetHScrollAlign, nodefault};
	__property Fmx::Types::TAlignLayout VScrollAlign = {read=GetVScrollAlign, nodefault};
	__property System::Types::TRectF HScrollMargins = {read=GetHScrollMargins};
	__property System::Types::TRectF VScrollMargins = {read=GetVScrollMargins};
	__property bool InInternalAlign = {read=FInInternalAlign, nodefault};
	__property System::Types::TPointF ViewportPosition = {read=GetViewportPosition, write=SetViewportPosition};
	__property Fmx::Stdctrls::TScrollBar* HScrollBar = {read=GetHScrollBar};
	__property Fmx::Stdctrls::TScrollBar* VScrollBar = {read=GetVScrollBar};
	__property TScrollCalculations* AniCalculations = {read=FAniCalculations};
	__property Fmx::Scrollbox::TScrollContent* Content = {read=FContent};
	__property Fmx::Controls::TControl* ContentLayout = {read=FContentLayout};
	
public:
	__fastcall virtual TStyledCustomScrollBox(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledCustomScrollBox();
	void __fastcall InvalidateContentSize();
	void __fastcall RealignContent();
	__property Fmx::Scrollbox::TCustomScrollBoxModel* Model = {read=GetModel};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledCustomScrollBox(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Style::TStyledPresentation(AOwner, AModel, AControl) { }
	
private:
	void *__IScrollableContent;	// IScrollableContent 
	
public:
	operator IScrollableContent*(void) { return (IScrollableContent*)&__IScrollableContent; }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Scrollbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SCROLLBOX_STYLE)
using namespace Fmx::Scrollbox::Style;
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
#endif	// Fmx_Scrollbox_StyleHPP
