// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiView.Presentations.pas' rev: 34.00 (Android)

#ifndef Fmx_Multiview_PresentationsHPP
#define Fmx_Multiview_PresentationsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Messaging.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.MultiView.Types.hpp>
#include <FMX.Ani.hpp>
#include <FMX.MultiView.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multiview
{
namespace Presentations
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultiViewBaseBorderedPresentation;
class DELPHICLASS TMultiViewBaseBorderWithOverlayPresentation;
class DELPHICLASS TMultiViewDrawerBasePresentation;
class DELPHICLASS TMultiViewDrawerPushingPresentation;
class DELPHICLASS TMultiViewDrawerOverlapPresentation;
class DELPHICLASS TMultiViewPopoverPresentation;
class DELPHICLASS TMultiViewDockedPanelPresentation;
class DELPHICLASS TMultiViewNavigationPanePresentation;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewBaseBorderedPresentation : public Fmx::Multiview::TMultiViewPresentation
{
	typedef Fmx::Multiview::TMultiViewPresentation inherited;
	
private:
	Fmx::Objects::TLine* FBorderLine;
	System::Types::TSizeF FSavedSize;
	Fmx::Types::TAlignLayout FSavedAlign;
	bool __fastcall IsHorizontalAlign(const Fmx::Types::TAlignLayout AAlign);
	bool __fastcall IsVerticalAlign(const Fmx::Types::TAlignLayout AAlign);
	
protected:
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoUninstall();
	
public:
	__fastcall virtual TMultiViewBaseBorderedPresentation(Fmx::Multiview::TCustomMultiView* AMultiView);
	__fastcall virtual ~TMultiViewBaseBorderedPresentation();
	virtual void __fastcall UpdateSettings();
	virtual void __fastcall UpdateStyle();
	virtual void __fastcall Realign();
	__property Fmx::Objects::TLine* BorderLine = {read=FBorderLine};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewBaseBorderWithOverlayPresentation : public TMultiViewBaseBorderedPresentation
{
	typedef TMultiViewBaseBorderedPresentation inherited;
	
private:
	Fmx::Multiview::Types::TTouchInterceptingLayout* FDetailOverlay;
	Fmx::Ani::TFloatAnimation* FShadowAnimation;
	
protected:
	virtual Fmx::Multiview::Types::TOverlayMode __fastcall DefineDetailOverlayMode();
	void __fastcall LinkDetailOverlayToParent(Fmx::Types::TFmxObject* const AParent);
	void __fastcall UnlinkDetailOverlayFromParent();
	void __fastcall FormReleased(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	void __fastcall FreeNotification(System::TObject* AObject);
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoUninstall();
	virtual void __fastcall DoOpen(const float ASpeed);
	virtual void __fastcall DoClose(const float ASpeed);
	void __fastcall UpdateDetailOverlayParent(Fmx::Controls::TControl* const ATargetControl);
	
public:
	__fastcall virtual TMultiViewBaseBorderWithOverlayPresentation(Fmx::Multiview::TCustomMultiView* AMultiView);
	__fastcall virtual ~TMultiViewBaseBorderWithOverlayPresentation();
	virtual void __fastcall ParentChanged();
	virtual void __fastcall EnabledChanged();
	void __fastcall ResetFocus();
	virtual void __fastcall TargetControlChanging(Fmx::Controls::TControl* AOldControl, Fmx::Controls::TControl* ANewControl);
	virtual void __fastcall UpdateSettings();
	__property Fmx::Multiview::Types::TTouchInterceptingLayout* DetailOverlay = {read=FDetailOverlay};
	__property Fmx::Ani::TFloatAnimation* ShadowAnimation = {read=FShadowAnimation};
private:
	void *__IFreeNotification;	// Fmx::Types::IFreeNotification 
	
public:
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
class PASCALIMPLEMENTATION TMultiViewDrawerBasePresentation : public TMultiViewBaseBorderWithOverlayPresentation
{
	typedef TMultiViewBaseBorderWithOverlayPresentation inherited;
	
	
protected:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TTrackingInfo
	{
	public:
		System::Types::TPointF Position;
		System::TDateTime Time;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
protected:
	static constexpr System::Byte MinimalSpeedThreshold = System::Byte(0x96);
	
	#define TMultiViewDrawerBasePresentation_HidingThreshold  (7.000000E-01)
	
	static constexpr System::Int8 ClickAreaExpansion = System::Int8(0x5);
	
	#define TMultiViewDrawerBasePresentation_StorageTrackingTime  (2.500000E-01)
	
	#define TMultiViewDrawerBasePresentation_SlidingSpeedReduction  (5.000000E-01)
	
	static constexpr System::Int8 DefaultDeadZone = System::Int8(0x1);
	
	
private:
	Fmx::Ani::TFloatAnimation* FMasterAnimation;
	System::Generics::Collections::TList__1<TTrackingInfo>* FTracksInfo;
	System::Types::TPointF FMousePressedAbsolutePosition;
	bool FDrawerCaptured;
	float FPreviousOffset;
	float FDeadZone;
	void __fastcall DoAnimationFinished(System::TObject* Sender);
	bool __fastcall DoPointInObjectEvent(System::TObject* Sender, const float X, const float Y);
	void __fastcall UpdateMasterAlignment();
	
protected:
	float __fastcall DefineShadowOpacity(const float AOffset);
	virtual System::Types::TPointF __fastcall DefineOpenedPanelPosition() = 0 ;
	virtual System::Types::TPointF __fastcall DefineHiddenPanelPosition() = 0 ;
	virtual void __fastcall ShiftPanels(const float AOffset) = 0 ;
	virtual bool __fastcall NeedHidePanel(const float ASpeed) = 0 ;
	virtual void __fastcall CaptureDrawer(const float AX, const float AY);
	void __fastcall TrackInfo(const float AX, const float AY);
	float __fastcall CalculateMovingSpeed();
	virtual float __fastcall CalculateSlidingTime(const float ASpeed) = 0 ;
	virtual void __fastcall DoMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoMouseMove(System::TObject* Sender, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoUninstall();
	virtual void __fastcall DoOpen(const float ASpeed);
	virtual void __fastcall DoClose(const float ASpeed);
	virtual void __fastcall DoHidden();
	virtual void __fastcall DoStartMoving(const float ASpeed);
	
public:
	__fastcall virtual TMultiViewDrawerBasePresentation(Fmx::Multiview::TCustomMultiView* AMultiView);
	__fastcall virtual ~TMultiViewDrawerBasePresentation();
	virtual void __fastcall Realign();
	virtual void __fastcall UpdateSettings();
	virtual void __fastcall ControlTypeChanged();
	__property Fmx::Ani::TFloatAnimation* MasterAnimation = {read=FMasterAnimation};
	__property float DeadZone = {read=FDeadZone, write=FDeadZone};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewDrawerPushingPresentation : public TMultiViewDrawerBasePresentation
{
	typedef TMultiViewDrawerBasePresentation inherited;
	
public:
	#define TMultiViewDrawerPushingPresentation_PushPanelStyle u"pushpanel"
	
	
private:
	Fmx::Ani::TRectAnimation* FDetailAnimation;
	System::UnicodeString FSavedTargetControlStyleLookup;
	
protected:
	virtual void __fastcall ShiftPanels(const float AOffset);
	virtual System::Types::TPointF __fastcall DefineOpenedPanelPosition();
	virtual System::Types::TPointF __fastcall DefineHiddenPanelPosition();
	virtual bool __fastcall NeedHidePanel(const float ASpeed);
	virtual void __fastcall DoOpen(const float ASpeed);
	virtual void __fastcall DoClose(const float ASpeed);
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoUninstall();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual float __fastcall CalculateSlidingTime(const float ASpeed);
	void __fastcall SaveStyleLookupAndUpdateStyle(Fmx::Controls::TStyledControl* const AControl);
	void __fastcall RestoreSavedStyleLookup(Fmx::Controls::TStyledControl* const AControl);
	
public:
	__fastcall virtual TMultiViewDrawerPushingPresentation(Fmx::Multiview::TCustomMultiView* AMultiView);
	__fastcall virtual ~TMultiViewDrawerPushingPresentation();
	virtual void __fastcall Realign();
	virtual void __fastcall UpdateSettings();
	virtual void __fastcall TargetControlChanging(Fmx::Controls::TControl* AOldControl, Fmx::Controls::TControl* ANewControl);
	__property Fmx::Ani::TRectAnimation* DetailAnimation = {read=FDetailAnimation};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewDrawerOverlapPresentation : public TMultiViewDrawerBasePresentation
{
	typedef TMultiViewDrawerBasePresentation inherited;
	
protected:
	virtual System::Types::TPointF __fastcall DefineOpenedPanelPosition();
	virtual System::Types::TPointF __fastcall DefineHiddenPanelPosition();
	virtual void __fastcall ShiftPanels(const float AOffset);
	virtual bool __fastcall NeedHidePanel(const float ASpeed);
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual float __fastcall CalculateSlidingTime(const float ASpeed);
	virtual void __fastcall DoMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoOpen(const float ASpeed);
	virtual void __fastcall DoClose(const float ASpeed);
	
public:
	virtual void __fastcall Realign();
	virtual void __fastcall UpdateSettings();
public:
	/* TMultiViewDrawerBasePresentation.Create */ inline __fastcall virtual TMultiViewDrawerOverlapPresentation(Fmx::Multiview::TCustomMultiView* AMultiView) : TMultiViewDrawerBasePresentation(AMultiView) { }
	/* TMultiViewDrawerBasePresentation.Destroy */ inline __fastcall virtual ~TMultiViewDrawerOverlapPresentation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewPopoverPresentation : public Fmx::Multiview::TMultiViewPresentation
{
	typedef Fmx::Multiview::TMultiViewPresentation inherited;
	
private:
	Fmx::Multiview::Types::TCustomPopover* FPopover;
	
protected:
	void __fastcall DoClosePopup(System::TObject* Sender);
	virtual void __fastcall DoUninstall();
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoOpen(const float ASpeed);
	virtual void __fastcall DoClose(const float ASpeed);
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual System::Types::TSizeF __fastcall GetExpandedSize();
	
public:
	__fastcall virtual TMultiViewPopoverPresentation(Fmx::Multiview::TCustomMultiView* AMultiView);
	virtual void __fastcall Realign();
	virtual void __fastcall UpdateSettings();
	__property Fmx::Multiview::Types::TCustomPopover* Popover = {read=FPopover};
public:
	/* TMultiViewPresentation.Destroy */ inline __fastcall virtual ~TMultiViewPopoverPresentation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewDockedPanelPresentation : public TMultiViewBaseBorderedPresentation
{
	typedef TMultiViewBaseBorderedPresentation inherited;
	
private:
	void __fastcall UpdateMasterAlignment();
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual bool __fastcall GetMasterButtonVisible();
	virtual void __fastcall DoInstall();
	
public:
	virtual void __fastcall UpdateSettings();
	virtual bool __fastcall NeedHideInDesignTime();
	virtual bool __fastcall CanShowHideInDesignTime();
	virtual void __fastcall TargetControlChanging(Fmx::Controls::TControl* AOldControl, Fmx::Controls::TControl* ANewControl);
public:
	/* TMultiViewBaseBorderedPresentation.Create */ inline __fastcall virtual TMultiViewDockedPanelPresentation(Fmx::Multiview::TCustomMultiView* AMultiView) : TMultiViewBaseBorderedPresentation(AMultiView) { }
	/* TMultiViewBaseBorderedPresentation.Destroy */ inline __fastcall virtual ~TMultiViewDockedPanelPresentation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TMultiViewNavigationPanePresentation : public TMultiViewBaseBorderWithOverlayPresentation
{
	typedef TMultiViewBaseBorderWithOverlayPresentation inherited;
	
public:
	#define TMultiViewNavigationPanePresentation_CloseSpeedReduction  (5.000000E-01)
	
	
private:
	Fmx::Ani::TFloatAnimation* FMasterAnimation;
	void __fastcall OverlayClickHandler(System::TObject* Sender);
	void __fastcall AnimationFinishedHandler(System::TObject* Sender);
	
protected:
	virtual Fmx::Multiview::Types::TOverlayMode __fastcall DefineDetailOverlayMode();
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoUninstall();
	virtual void __fastcall DoOpen(const float ASpeed);
	virtual void __fastcall DoClose(const float ASpeed);
	virtual void __fastcall SetExpandedSize(const System::Types::TSizeF &Value);
	virtual System::Types::TSizeF __fastcall GetExpandedSize();
	virtual System::Types::TSizeF __fastcall GetCollapsedSize();
	
public:
	__fastcall virtual TMultiViewNavigationPanePresentation(Fmx::Multiview::TCustomMultiView* AMultiView);
	__fastcall virtual ~TMultiViewNavigationPanePresentation();
	virtual bool __fastcall NeedHideInDesignTime();
	HIDESBASE void __fastcall ResetFocus();
	virtual void __fastcall TargetControlChanging(Fmx::Controls::TControl* AOldControl, Fmx::Controls::TControl* ANewControl);
	virtual void __fastcall UpdateSettings();
	virtual void __fastcall Realign();
	void __fastcall RecalculateWidth();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Presentations */
}	/* namespace Multiview */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW_PRESENTATIONS)
using namespace Fmx::Multiview::Presentations;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW)
using namespace Fmx::Multiview;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Multiview_PresentationsHPP
