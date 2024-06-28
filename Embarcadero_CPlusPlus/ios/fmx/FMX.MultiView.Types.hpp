// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiView.Types.pas' rev: 34.00 (iOS)

#ifndef Fmx_Multiview_TypesHPP
#define Fmx_Multiview_TypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multiview
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTouchInterceptingLayoutModel;
class DELPHICLASS TCustomTouchInterceptingLayout;
class DELPHICLASS TTouchInterceptingLayout;
class DELPHICLASS TCustomPopover;
class DELPHICLASS TSeparatorLine;
class DELPHICLASS TMultiViewAppearance;
class DELPHICLASS TMultiViewBorderOptions;
class DELPHICLASS TDrawerAppearance;
class DELPHICLASS TShadowAppearance;
class DELPHICLASS TPopoverAppearance;
class DELPHICLASS TSplitViewAppearance;
class DELPHICLASS TNavigationPaneAppearance;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TOverlayMode : unsigned char { None, AllLocalArea, LeftSide, RightSide, BottomSide, TopSide };

typedef bool __fastcall (__closure *TOnPointInObjectEvent)(System::TObject* Sender, const float X, const float Y);

class PASCALIMPLEMENTATION TTouchInterceptingLayoutModel : public Fmx::Controls::Model::TDataModel
{
	typedef Fmx::Controls::Model::TDataModel inherited;
	
public:
	static const TOverlayMode DefaultMode = (TOverlayMode)(1);
	
	static constexpr System::Int8 DefaultSizeInterception = System::Int8(0x14);
	
	
private:
	TOverlayMode FMode;
	float FInterceptionSize;
	bool FEnabledShadow;
	System::Uitypes::TAlphaColor FColor;
	TOnPointInObjectEvent FOnPointInObjectEvent;
	void __fastcall SetMode(const TOverlayMode Value);
	void __fastcall SetInterceptionSize(const float Value);
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetEnabledShadow(const bool Value);
	
public:
	__fastcall virtual TTouchInterceptingLayoutModel()/* overload */;
	__property TOverlayMode Mode = {read=FMode, write=SetMode, nodefault};
	__property float InterceptionSize = {read=FInterceptionSize, write=SetInterceptionSize};
	__property bool EnabledShadow = {read=FEnabledShadow, write=SetEnabledShadow, default=1};
	__property System::Uitypes::TAlphaColor ShadowColor = {read=FColor, write=SetColor, nodefault};
	__property TOnPointInObjectEvent OnPointInObjectEvent = {read=FOnPointInObjectEvent, write=FOnPointInObjectEvent};
public:
	/* TDataModel.Create */ inline __fastcall virtual TTouchInterceptingLayoutModel(System::Classes::TComponent* const AOwner)/* overload */ : Fmx::Controls::Model::TDataModel(AOwner) { }
	/* TDataModel.Destroy */ inline __fastcall virtual ~TTouchInterceptingLayoutModel() { }
	
};


class PASCALIMPLEMENTATION TCustomTouchInterceptingLayout : public Fmx::Controls::Presentation::TPresentedControl
{
	typedef Fmx::Controls::Presentation::TPresentedControl inherited;
	
	
public:
	typedef TOverlayMode TOverlayMode;
	
	
private:
	System::Types::TPointF FMousePressedPos;
	void __fastcall SetMode(const TOverlayMode Value);
	TOverlayMode __fastcall GetMode();
	void __fastcall SetInterceptionSize(const float Value);
	float __fastcall GetInterceptionSize();
	bool __fastcall IsInterceptionSizeStored();
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	System::Uitypes::TAlphaColor __fastcall GetColor();
	void __fastcall SetEnabledShadow(const bool Value);
	bool __fastcall GetEnabledShadow();
	void __fastcall SetOnPointInObjectEvent(const TOnPointInObjectEvent Value);
	TOnPointInObjectEvent __fastcall GetOnPointInObjectEvent();
	HIDESBASE TTouchInterceptingLayoutModel* __fastcall GetModel()/* overload */;
	
protected:
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoMouseLeave();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__fastcall virtual TCustomTouchInterceptingLayout(System::Classes::TComponent* AOwner)/* overload */;
	__property TTouchInterceptingLayoutModel* Model = {read=GetModel};
	__property System::Types::TPointF MousePressedPosition = {read=FMousePressedPos};
	__property Pressed;
	__property TOverlayMode Mode = {read=GetMode, write=SetMode, default=1};
	__property float InterceptionSize = {read=GetInterceptionSize, write=SetInterceptionSize, stored=IsInterceptionSizeStored};
	__property System::Uitypes::TAlphaColor Color = {read=GetColor, write=SetColor, nodefault};
	__property bool EnabledShadow = {read=GetEnabledShadow, write=SetEnabledShadow, default=1};
	__property TOnPointInObjectEvent OnPointInObjectEvent = {read=GetOnPointInObjectEvent, write=SetOnPointInObjectEvent};
public:
	/* TPresentedControl.Destroy */ inline __fastcall virtual ~TCustomTouchInterceptingLayout() { }
	
};


class PASCALIMPLEMENTATION TTouchInterceptingLayout : public TCustomTouchInterceptingLayout
{
	typedef TCustomTouchInterceptingLayout inherited;
	
__published:
	__property Color;
	__property ControlType = {default=0};
	__property EnabledShadow = {default=1};
	__property Mode = {default=1};
	__property InterceptionSize;
	__property OnPointInObjectEvent;
public:
	/* TCustomTouchInterceptingLayout.Create */ inline __fastcall virtual TTouchInterceptingLayout(System::Classes::TComponent* AOwner)/* overload */ : TCustomTouchInterceptingLayout(AOwner) { }
	
public:
	/* TPresentedControl.Destroy */ inline __fastcall virtual ~TTouchInterceptingLayout() { }
	
};


typedef TTouchInterceptingLayout TShadowedOverlayLayout _DEPRECATED_ATTRIBUTE1("Use TTouchInterceptingLayout instead") ;

typedef TTouchInterceptingLayout TOverlayLayout _DEPRECATED_ATTRIBUTE1("Use TTouchInterceptingLayout instead") ;

enum class DECLSPEC_DENUM TArrowDirection : unsigned char { None, Top, Bottom, Left, Right };

class PASCALIMPLEMENTATION TCustomPopover : public Fmx::Controls::TPopup
{
	typedef Fmx::Controls::TPopup inherited;
	
	
protected:
	struct DECLSPEC_DRECORD TArrowInfo
	{
	public:
		TArrowDirection Direction;
		Fmx::Controls::TControl* Container;
		Fmx::Controls::TControl* Arrow;
		Fmx::Controls::_di_ITintedObject Tint;
		bool __fastcall IsEmpty();
		static TCustomPopover::TArrowInfo __fastcall Empty();
	};
	
	
	
public:
	#define TCustomPopover_DefaultAppearanceDuration  (3.000000E-01)
	
	#define TCustomPopover_DefaultShadowOpacity  (1.000000E-01)
	
	static constexpr bool DefaultShadowEnabled = false;
	
	static constexpr System::Int8 DefaultIndentFromScreenBorder = System::Int8(0x5);
	
	
private:
	Fmx::Ani::TFloatAnimation* FOpacityAnimation;
	float FAppearanceDuration;
	Fmx::Objects::TRectangle* FShadow;
	bool FShadowEnabled;
	float FIndentFromScreenBorder;
	Fmx::Controls::TControl* FContent;
	TArrowInfo FTopArrow;
	TArrowInfo FBottomArrow;
	TArrowInfo FLeftArrow;
	TArrowInfo FRightArrow;
	System::Uitypes::TAlphaColor FTintColor;
	Fmx::Controls::_di_ITintedObject FTintContent;
	void __fastcall SetAppearanceDuration(const float Value);
	bool __fastcall IsAppearanceDurationStored();
	bool __fastcall IsIndentFromScreenBorderStored();
	TArrowInfo __fastcall GetCurrentArrow();
	void __fastcall DoPlacementChanged(System::TObject* Sender);
	void __fastcall SetTintColor(const System::Uitypes::TAlphaColor Value);
	bool __fastcall IsTintColorStored();
	
protected:
	virtual void __fastcall UpdateArrowPosition();
	virtual void __fastcall UpdatePadding();
	virtual void __fastcall UpdateTint();
	void __fastcall HideArrows();
	virtual void __fastcall DoClosePopup();
	virtual void __fastcall DoPopup();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	__property Fmx::Controls::TControl* Content = {read=FContent};
	__property Fmx::Objects::TRectangle* Shadow = {read=FShadow};
	__property TArrowInfo TopArrow = {read=FTopArrow};
	__property TArrowInfo BottomArrow = {read=FBottomArrow};
	__property TArrowInfo LeftArrow = {read=FLeftArrow};
	__property TArrowInfo RightArrow = {read=FRightArrow};
	__property TArrowInfo CurrentArrow = {read=GetCurrentArrow};
	
public:
	__fastcall virtual TCustomPopover(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCustomPopover();
	virtual void __fastcall Popup(const bool AShowModal = false);
	__property Fmx::Controls::_di_ITintedObject TintContent = {read=FTintContent};
	__property float AppearanceDuration = {read=FAppearanceDuration, write=SetAppearanceDuration, stored=IsAppearanceDurationStored};
	__property bool ShadowEnabled = {read=FShadowEnabled, write=FShadowEnabled, default=0};
	__property float IndentFromScreenBorder = {read=FIndentFromScreenBorder, write=FIndentFromScreenBorder, stored=IsIndentFromScreenBorderStored};
	__property System::Uitypes::TAlphaColor TintColor = {read=FTintColor, write=SetTintColor, stored=IsTintColorStored, nodefault};
};


class PASCALIMPLEMENTATION TSeparatorLine : public Fmx::Objects::TLine
{
	typedef Fmx::Objects::TLine inherited;
	
public:
	/* TLine.Create */ inline __fastcall virtual TSeparatorLine(System::Classes::TComponent* AOwner) : Fmx::Objects::TLine(AOwner) { }
	
public:
	/* TShape.Destroy */ inline __fastcall virtual ~TSeparatorLine() { }
	
};


class PASCALIMPLEMENTATION TMultiViewAppearance : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	System::Classes::TComponent* FOwner;
	System::Classes::TNotifyEvent FOnChanged;
	
protected:
	virtual void __fastcall DoChanged();
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TMultiViewAppearance(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	__property System::Classes::TComponent* Owner = {read=FOwner};
	__property System::Classes::TNotifyEvent OnChanged = {read=FOnChanged};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TMultiViewAppearance() { }
	
};


class PASCALIMPLEMENTATION TMultiViewBorderOptions : public TMultiViewAppearance
{
	typedef TMultiViewAppearance inherited;
	
public:
	static constexpr bool DefaultVisible = true;
	
	static constexpr System::Uitypes::TAlphaColor DefaultColor = System::Uitypes::TAlphaColor(0x0);
	
	
private:
	bool FVisible;
	System::Uitypes::TAlphaColor FColor;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetVisible(const bool Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TMultiViewBorderOptions(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, default=0};
	__property bool Visible = {read=FVisible, write=SetVisible, default=1};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TMultiViewBorderOptions() { }
	
};


enum class DECLSPEC_DENUM TSlidingMode : unsigned char { PushingDetailView, OverlapDetailView };

enum class DECLSPEC_DENUM TPanelPlacement : unsigned char { Left, Right, Top, Bottom };

class PASCALIMPLEMENTATION TDrawerAppearance : public TMultiViewAppearance
{
	typedef TMultiViewAppearance inherited;
	
public:
	#define TDrawerAppearance_DefaultDurationSliding  (2.500000E-01)
	
	static constexpr System::Int8 DefaultTouchAreaSize = System::Int8(0x14);
	
	static const TSlidingMode DefaultMode = (TSlidingMode)(1);
	
	static const TPanelPlacement DefaultPlacement = (TPanelPlacement)(0);
	
	
private:
	TSlidingMode FMode;
	TPanelPlacement FPlacement;
	float FDurationSliding;
	float FTouchAreaSize;
	void __fastcall SetDurationSliding(const float Value);
	void __fastcall SetMode(const TSlidingMode Value);
	void __fastcall SetTouchAreaSize(const float Value);
	void __fastcall SetPlacement(const TPanelPlacement Value);
	
protected:
	virtual bool __fastcall IsDurationSlidingStored();
	virtual bool __fastcall IsTouchAreaSizeStored();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TDrawerAppearance(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	
__published:
	__property float DurationSliding = {read=FDurationSliding, write=SetDurationSliding, stored=IsDurationSlidingStored};
	__property TPanelPlacement Placement = {read=FPlacement, write=SetPlacement, default=0};
	__property TSlidingMode Mode = {read=FMode, write=SetMode, default=1};
	__property float TouchAreaSize = {read=FTouchAreaSize, write=SetTouchAreaSize, stored=IsTouchAreaSizeStored};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDrawerAppearance() { }
	
};


class PASCALIMPLEMENTATION TShadowAppearance : public TMultiViewAppearance
{
	typedef TMultiViewAppearance inherited;
	
public:
	static constexpr bool DefaultEnabled = true;
	
	static constexpr unsigned DefaultColor = unsigned(0xff000000);
	
	#define TShadowAppearance_DefaultOpacity  (3.000000E-01)
	
	
private:
	bool FEnabled;
	System::Uitypes::TAlphaColor FColor;
	float FOpacity;
	void __fastcall SetColor(const System::Uitypes::TAlphaColor Value);
	void __fastcall SetOpacity(const float Value);
	void __fastcall SetEnabled(const bool Value);
	
protected:
	virtual bool __fastcall IsOpacityStored();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TShadowAppearance(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	
__published:
	__property System::Uitypes::TAlphaColor Color = {read=FColor, write=SetColor, default=-16777216};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property float Opacity = {read=FOpacity, write=SetOpacity, stored=IsOpacityStored};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TShadowAppearance() { }
	
};


class PASCALIMPLEMENTATION TPopoverAppearance : public TMultiViewAppearance
{
	typedef TMultiViewAppearance inherited;
	
public:
	static constexpr System::Word DefaultHeight = System::Word(0x190);
	
	#define TPopoverAppearance_DefaultAppearanceDuration  (2.500000E-01)
	
	static constexpr System::Uitypes::TAlphaColor DefaultTintColor = System::Uitypes::TAlphaColor(0x0);
	
	
private:
	float FPopupHeight;
	float FAppearanceDuration;
	System::UnicodeString FStyleLookup;
	System::Uitypes::TAlphaColor FTintColor;
	void __fastcall SetPopupHeight(const float Value);
	void __fastcall SetStyleLookup(const System::UnicodeString Value);
	void __fastcall SetAppearanceDuration(const float Value);
	void __fastcall SetTintColor(const System::Uitypes::TAlphaColor Value);
	
protected:
	virtual bool __fastcall IsHeightStored();
	virtual bool __fastcall IsAppearanceDurationStored();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TPopoverAppearance(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	
__published:
	__property System::UnicodeString StyleLookup = {read=FStyleLookup, write=SetStyleLookup};
	__property float PopupHeight = {read=FPopupHeight, write=SetPopupHeight, stored=IsHeightStored};
	__property float AppearanceDuration = {read=FAppearanceDuration, write=SetAppearanceDuration, stored=IsAppearanceDurationStored};
	__property System::Uitypes::TAlphaColor TintColor = {read=FTintColor, write=SetTintColor, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TPopoverAppearance() { }
	
};


class PASCALIMPLEMENTATION TSplitViewAppearance : public TMultiViewAppearance
{
	typedef TMultiViewAppearance inherited;
	
public:
	static const TPanelPlacement DefaultPlacement = (TPanelPlacement)(0);
	
	
private:
	TPanelPlacement FPlacement;
	void __fastcall SetPlacement(const TPanelPlacement Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TSplitViewAppearance(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	
__published:
	__property TPanelPlacement Placement = {read=FPlacement, write=SetPlacement, default=0};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TSplitViewAppearance() { }
	
};


class PASCALIMPLEMENTATION TNavigationPaneAppearance : public TMultiViewAppearance
{
	typedef TMultiViewAppearance inherited;
	
public:
	static constexpr System::Int8 DefaultCollapsedWidth = System::Int8(0x32);
	
	
private:
	float FCollapsedWidth;
	void __fastcall SetCollapsedWidth(const float Value);
	
protected:
	virtual bool __fastcall IsCollapsedWidthStored();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	__fastcall TNavigationPaneAppearance(System::Classes::TComponent* AOwner, const System::Classes::TNotifyEvent AInternalChange);
	virtual bool __fastcall AreDefaultValues();
	
__published:
	__property float CollapsedWidth = {read=FCollapsedWidth, write=SetCollapsedWidth, stored=IsCollapsedWidthStored};
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TNavigationPaneAppearance() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word MM_MODE_CHANGED = System::Word(0x1701);
static constexpr System::Word MM_INTERCEPTION_SIZE_CHANGED = System::Word(0x1702);
static constexpr System::Word MM_COLOR_CHANGED = System::Word(0x1703);
static constexpr System::Word MM_ENABLED_SHADOW_CHANGED = System::Word(0x1704);
static constexpr System::Word MM_SHADOW_OPACITY_CHANGED = System::Word(0x1705);
static constexpr System::Word MM_SHADOWED_OVERLAY_LAYOUT_USER = System::Word(0x1706);
}	/* namespace Types */
}	/* namespace Multiview */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW_TYPES)
using namespace Fmx::Multiview::Types;
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
#endif	// Fmx_Multiview_TypesHPP
