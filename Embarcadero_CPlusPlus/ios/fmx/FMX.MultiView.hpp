// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiView.pas' rev: 34.00 (iOS)

#ifndef Fmx_MultiviewHPP
#define Fmx_MultiviewHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Messaging.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.UITypes.hpp>
#include <System.Devices.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Forms.hpp>
#include <FMX.MultiView.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multiview
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultiViewPresentation;
class DELPHICLASS TMultiViewlDisplayedMessage;
class DELPHICLASS TCustomMultiView;
class DELPHICLASS TMultiView;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TPresentationState : unsigned char { Installed, Opened, Moving };

typedef System::Set<TPresentationState, _DELPHI_SET_ENUMERATOR(TPresentationState::Installed), _DELPHI_SET_ENUMERATOR(TPresentationState::Moving)> TPresentationStates;

class PASCALIMPLEMENTATION TMultiViewPresentation : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
public:
	static constexpr System::Int8 DefaultSpeed = System::Int8(0x0);
	
	
private:
	TCustomMultiView* FMultiView;
	TPresentationStates FState;
	int FInternalRealign;
	
protected:
	float __fastcall GetParentWidth();
	float __fastcall GetParentHeight();
	virtual void __fastcall SetExpandedSize(const System::Types::TSizeF &Value);
	virtual System::Types::TSizeF __fastcall GetExpandedSize();
	virtual System::Types::TSizeF __fastcall GetCollapsedSize();
	virtual void __fastcall DoShown();
	virtual void __fastcall DoStartShowing();
	virtual void __fastcall DoStartHiding();
	virtual void __fastcall DoHidden();
	virtual void __fastcall DoInstall();
	virtual void __fastcall DoUninstall();
	virtual void __fastcall DoOpen(const float ASpeed = 0.000000E+00f);
	virtual void __fastcall DoClose(const float ASpeed = 0.000000E+00f);
	virtual void __fastcall DoStartMoving(const float ASpeed = 0.000000E+00f);
	virtual void __fastcall DoEndMoving();
	void __fastcall StartMoving(const float ASpeed = 0.000000E+00f);
	void __fastcall EndMoving();
	virtual bool __fastcall GetMasterButtonVisible();
	virtual System::UnicodeString __fastcall GetDisplayName();
	void __fastcall BeginInternalRealign();
	void __fastcall EndInternalRealign();
	bool __fastcall IsInternalRealign();
	
public:
	__fastcall virtual TMultiViewPresentation(TCustomMultiView* AMultiView);
	__fastcall virtual ~TMultiViewPresentation();
	void __fastcall Install();
	void __fastcall Uninstall();
	void __fastcall Open(const float ASpeed = 0.000000E+00f);
	void __fastcall Close(const float ASpeed = 0.000000E+00f);
	bool __fastcall Opened();
	bool __fastcall Moving();
	virtual void __fastcall Realign();
	virtual void __fastcall TargetControlChanging(Fmx::Controls::TControl* AOldControl, Fmx::Controls::TControl* ANewControl);
	virtual void __fastcall UpdateSettings();
	virtual void __fastcall UpdateStyle();
	virtual void __fastcall ControlTypeChanged();
	virtual void __fastcall ParentChanged();
	virtual void __fastcall EnabledChanged();
	virtual bool __fastcall NeedHideInDesignTime();
	virtual bool __fastcall CanShowHideInDesignTime();
	__property System::UnicodeString DisplayName = {read=GetDisplayName};
	__property System::Types::TSizeF ExpandedSize = {read=GetExpandedSize, write=SetExpandedSize};
	__property System::Types::TSizeF CollapsedSize = {read=GetCollapsedSize};
	__property TCustomMultiView* MultiView = {read=FMultiView};
	__property TPresentationStates State = {read=FState, nodefault};
	__property bool MasterButtonVisible = {read=GetMasterButtonVisible, nodefault};
};


_DECLARE_METACLASS(System::TMetaClass, TMultiViewPresentationClass);

enum class DECLSPEC_DENUM TMultiViewMode : unsigned char { PlatformBehaviour, Panel, Popover, Drawer, Custom, NavigationPane };

typedef void __fastcall (__closure *TOnPresenterChanging)(System::TObject* Sender, TMultiViewPresentationClass &PresenterClass);

class PASCALIMPLEMENTATION TMultiViewlDisplayedMessage : public System::Messaging::TMessageBase
{
	typedef System::Messaging::TMessageBase inherited;
	
public:
	/* TObject.Create */ inline __fastcall TMultiViewlDisplayedMessage() : System::Messaging::TMessageBase() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TMultiViewlDisplayedMessage() { }
	
};


class PASCALIMPLEMENTATION TCustomMultiView : public Fmx::Controls::Presentation::TPresentedControl
{
	typedef Fmx::Controls::Presentation::TPresentedControl inherited;
	
public:
	static constexpr System::Byte DefaultWidth = System::Byte(0xfa);
	
	
private:
	TMultiViewMode FMode;
	Fmx::Controls::TContent* FMasterContent;
	Fmx::Controls::TControl* FMasterButton;
	bool FSavedMasterButtonVisible;
	Fmx::Controls::TControl* FTargetControl;
	Fmx::Multiview::Types::TMultiViewBorderOptions* FBorderOptions;
	Fmx::Multiview::Types::TShadowAppearance* FShadowOptions;
	Fmx::Multiview::Types::TDrawerAppearance* FDrawerOptions;
	Fmx::Multiview::Types::TPopoverAppearance* FPopoverOptions;
	Fmx::Multiview::Types::TSplitViewAppearance* FSplitViewOptions;
	Fmx::Multiview::Types::TNavigationPaneAppearance* FNavigationPaneOptions;
	TMultiViewPresentation* FPresenter;
	TMultiViewPresentationClass FCustomPresentationClass;
	Fmx::Platform::_di_IFMXScreenService FScreenService;
	Fmx::Platform::_di_IFMXDeviceService FDeviceService;
	TOnPresenterChanging FOnPresenterChanging;
	System::Classes::TNotifyEvent FOnStartShowing;
	System::Classes::TNotifyEvent FOnStartHiding;
	System::Classes::TNotifyEvent FOnShown;
	System::Classes::TNotifyEvent FOnHidden;
	void __fastcall SetMasterButton(Fmx::Controls::TControl* const Value);
	void __fastcall SetTargetControl(Fmx::Controls::TControl* const Value);
	void __fastcall SetMode(const TMultiViewMode Value);
	void __fastcall SetBorderOptions(Fmx::Multiview::Types::TMultiViewBorderOptions* const Value);
	void __fastcall SetDrawerOptions(Fmx::Multiview::Types::TDrawerAppearance* const Value);
	void __fastcall SetShadowOptions(Fmx::Multiview::Types::TShadowAppearance* const Value);
	void __fastcall SetSplitViewOptions(Fmx::Multiview::Types::TSplitViewAppearance* const Value);
	void __fastcall SetPopoverAppearance(Fmx::Multiview::Types::TPopoverAppearance* const Value);
	void __fastcall SetNavigationPaneOptions(Fmx::Multiview::Types::TNavigationPaneAppearance* const Value);
	void __fastcall SetCustomPresentationClass(const TMultiViewPresentationClass Value);
	bool __fastcall AreBorderOptionsStored();
	bool __fastcall AreShadowOptionsStored();
	bool __fastcall AreDrawerOptionsStored();
	bool __fastcall ArePopoverOptionsStored();
	bool __fastcall AreSplitViewOptionsStored();
	bool __fastcall AreNavigationPaneOptionsStored();
	Fmx::Types::TFmxObject* __fastcall DefineContext();
	void __fastcall DoOrientationChanged(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	void __fastcall DoAnotherMultiViewDisplayed(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	void __fastcall DoFormSizeChanged(System::TObject* const Sender, System::Messaging::TMessageBase* const M);
	void __fastcall DoOptionsChanged(System::TObject* Sender);
	
protected:
	Fmx::Types::TScreenOrientation __fastcall GetOrientation();
	System::Devices::TDeviceInfo::TDeviceClass __fastcall GetDeviceClass();
	System::Devices::TDeviceInfo* __fastcall GetDevice();
	virtual bool __fastcall IsObjectForContent(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoInsertObject(int Index, Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoRemoveObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoMasterButtonClick(System::TObject* Sender);
	virtual void __fastcall ParentChanged();
	bool __fastcall IsMobilePreview();
	virtual void __fastcall Loaded();
	virtual void __fastcall Resize();
	virtual void __fastcall DoAbsoluteChanged();
	virtual void __fastcall EnabledChanged();
	virtual void __fastcall Show();
	virtual void __fastcall ControlTypeChanged();
	virtual void __fastcall WriteState(System::Classes::TWriter* Writer);
	virtual void __fastcall ReadState(System::Classes::TReader* Reader);
	virtual void __fastcall DoStartShowing();
	virtual void __fastcall DoStartHiding();
	virtual void __fastcall DoShown();
	virtual void __fastcall DoHidden();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall PaintChildren();
	virtual void __fastcall FreeNotification(System::TObject* AObject);
	virtual bool __fastcall RequestPresenter();
	virtual TMultiViewPresentationClass __fastcall DefineDrawerPresenterClass();
	virtual TMultiViewPresentationClass __fastcall DefinePlatformBehaviourPresenter();
	virtual TMultiViewPresentationClass __fastcall DefinePresenterClass();
	virtual void __fastcall DoPresenterChanging(TMultiViewPresentationClass &PresenterClass);
	
public:
	__fastcall virtual TCustomMultiView(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TCustomMultiView();
	bool __fastcall HasMasterButton();
	bool __fastcall HasTargetControl();
	bool __fastcall HasPresenter();
	void __fastcall HideMaster();
	void __fastcall ShowMaster();
	virtual void __fastcall UpdateAlignment();
	bool __fastcall IsShowed();
	void __fastcall ClearContent();
	__property Fmx::Controls::TContent* MasterContent = {read=FMasterContent};
	__property TMultiViewPresentation* Presenter = {read=FPresenter};
	__property TMultiViewPresentationClass CustomPresentationClass = {read=FCustomPresentationClass, write=SetCustomPresentationClass};
	__property Fmx::Controls::TControl* TargetControl = {read=FTargetControl, write=SetTargetControl};
	__property Fmx::Multiview::Types::TPopoverAppearance* PopoverOptions = {read=FPopoverOptions, write=SetPopoverAppearance, stored=ArePopoverOptionsStored};
	__property Fmx::Controls::TControl* MasterButton = {read=FMasterButton, write=SetMasterButton};
	__property TMultiViewMode Mode = {read=FMode, write=SetMode, default=0};
	__property Fmx::Multiview::Types::TMultiViewBorderOptions* BorderOptions = {read=FBorderOptions, write=SetBorderOptions, stored=AreBorderOptionsStored};
	__property Fmx::Multiview::Types::TShadowAppearance* ShadowOptions = {read=FShadowOptions, write=SetShadowOptions, stored=AreShadowOptionsStored};
	__property Fmx::Multiview::Types::TSplitViewAppearance* SplitViewOptions = {read=FSplitViewOptions, write=SetSplitViewOptions, stored=AreSplitViewOptionsStored};
	__property Fmx::Multiview::Types::TDrawerAppearance* DrawerOptions = {read=FDrawerOptions, write=SetDrawerOptions, stored=AreDrawerOptionsStored};
	__property Fmx::Multiview::Types::TNavigationPaneAppearance* NavigationPaneOptions = {read=FNavigationPaneOptions, write=SetNavigationPaneOptions, stored=AreNavigationPaneOptionsStored};
	__property System::Classes::TNotifyEvent OnStartShowing = {read=FOnStartShowing, write=FOnStartShowing};
	__property System::Classes::TNotifyEvent OnStartHiding = {read=FOnStartHiding, write=FOnStartHiding};
	__property System::Classes::TNotifyEvent OnShown = {read=FOnShown, write=FOnShown};
	__property System::Classes::TNotifyEvent OnHidden = {read=FOnHidden, write=FOnHidden};
	__property TOnPresenterChanging OnPresenterChanging = {read=FOnPresenterChanging, write=FOnPresenterChanging};
};


class PASCALIMPLEMENTATION TMultiView : public TCustomMultiView
{
	typedef TCustomMultiView inherited;
	
__published:
	__property TargetControl;
	__property BorderOptions;
	__property DrawerOptions;
	__property PopoverOptions;
	__property MasterButton;
	__property Mode = {default=0};
	__property NavigationPaneOptions;
	__property ShadowOptions;
	__property SplitViewOptions;
	__property OnPresenterChanging;
	__property OnStartShowing;
	__property OnStartHiding;
	__property OnShown;
	__property OnHidden;
	__property ControlType = {default=0};
	__property ClipChildren = {default=0};
	__property ClipParent = {default=0};
	__property Cursor = {default=0};
	__property DragMode = {default=0};
	__property EnableDragHighlight = {default=1};
	__property Enabled = {default=1};
	__property Locked = {default=0};
	__property HelpContext = {default=0};
	__property HelpKeyword = {default=0};
	__property HelpType = {default=1};
	__property Height;
	__property HitTest = {default=1};
	__property Padding;
	__property Opacity;
	__property PopupMenu;
	__property Scale;
	__property Size;
	__property StyleLookup = {default=0};
	__property TouchTargetExpansion;
	__property Visible = {default=1};
	__property Width;
	__property TabOrder = {default=-1};
	__property OnApplyStyleLookup;
	__property OnDragEnter;
	__property OnDragLeave;
	__property OnDragOver;
	__property OnDragDrop;
	__property OnDragEnd;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnCanFocus;
	__property OnEnter;
	__property OnExit;
	__property OnClick;
	__property OnDblClick;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnPainting;
	__property OnPaint;
	__property OnResize;
	__property OnResized;
public:
	/* TCustomMultiView.Create */ inline __fastcall virtual TMultiView(System::Classes::TComponent* AOwner)/* overload */ : TCustomMultiView(AOwner) { }
	/* TCustomMultiView.Destroy */ inline __fastcall virtual ~TMultiView() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Multiview */
}	/* namespace Fmx */
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
#endif	// Fmx_MultiviewHPP
