// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Fmx.Bind.Navigator.pas' rev: 34.00 (Android)

#ifndef Fmx_Bind_NavigatorHPP
#define Fmx_Bind_NavigatorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ExtCtrls.hpp>
#include <Data.Bind.Components.hpp>
#include <Data.Bind.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.ActnList.hpp>
#include <FMX.Effects.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <System.Actions.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Bind
{
namespace Navigator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBindNavException;
class DELPHICLASS TCustomBindNavigator;
class DELPHICLASS TBindNavigator;
class DELPHICLASS TBindNavButton;
class DELPHICLASS TFMXBindNavigateAction;
class DELPHICLASS TFMXBindNavigateFirst;
class DELPHICLASS TFMXBindNavigatePrior;
class DELPHICLASS TFMXBindNavigateNext;
class DELPHICLASS TFMXBindNavigateLast;
class DELPHICLASS TFMXBindNavigateInsert;
class DELPHICLASS TFMXBindNavigateDelete;
class DELPHICLASS TFMXBindNavigateEdit;
class DELPHICLASS TFMXBindNavigatePost;
class DELPHICLASS TFMXBindNavigateCancel;
class DELPHICLASS TFMXBindNavigateRefresh;
class DELPHICLASS TFMXBindNavigateApplyUpdates;
class DELPHICLASS TFMXBindNavigateCancelUpdates;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EBindNavException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBindNavException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBindNavException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBindNavException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBindNavException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindNavException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBindNavException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBindNavException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBindNavException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindNavException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBindNavException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindNavException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBindNavException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBindNavException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TBindNavGlyph : unsigned char { ngEnabled, ngDisabled };

typedef Data::Bind::Controls::TNavigateButton TBindNavigateBtn;

typedef Data::Bind::Controls::TNavigateButtons TBindNavButtonSet;

enum DECLSPEC_DENUM Fmx_Bind_Navigator__2 : unsigned char { nsAllowTimer, nsFocusRect };

typedef System::Set<Fmx_Bind_Navigator__2, Fmx_Bind_Navigator__2::nsAllowTimer, Fmx_Bind_Navigator__2::nsFocusRect> TBindNavButtonStyle;

typedef void __fastcall (__closure *EBindNavClick)(System::TObject* Sender, Data::Bind::Controls::TNavigateButton Button);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCustomBindNavigator : public Fmx::Layouts::TLayout
{
	typedef Fmx::Layouts::TLayout inherited;
	
private:
	Data::Bind::Controls::TBindNavigatorController* FController;
	Data::Bind::Controls::TNavigateButtons FVisibleButtons;
	System::Classes::TStrings* FHints;
	System::Classes::TStrings* FDefHints;
	int ButtonWidth;
	System::Types::TPoint MinBtnSize;
	EBindNavClick FOnNavClick;
	EBindNavClick FBeforeAction;
	Data::Bind::Controls::TNavigateButton FocusedButton;
	bool FConfirmDelete;
	float FyRadius;
	float FxRadius;
	Fmx::Types::TCornerType FCornerType;
	Fmx::Types::TCorners FCorners;
	System::UnicodeString FBindScopeName;
	void __fastcall BtnMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall ClickHandler(System::TObject* Sender);
	Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetDataSource();
	System::Classes::TStrings* __fastcall GetHints();
	void __fastcall HintsChanged(System::TObject* Sender);
	void __fastcall InitButtons();
	void __fastcall InitHints();
	void __fastcall SetDataSource(Data::Bind::Components::TBaseLinkingBindSource* Value);
	void __fastcall SetHints(System::Classes::TStrings* Value);
	HIDESBASE void __fastcall SetSize(float &W, float &H);
	void __fastcall SetVisibleButtons(Data::Bind::Controls::TNavigateButtons Value);
	void __fastcall SetCornerType(const Fmx::Types::TCornerType Value);
	void __fastcall SetxRadius(const float Value);
	void __fastcall SetyRadius(const float Value);
	bool __fastcall IsCornersStored();
	void __fastcall SetCorners(const Fmx::Types::TCorners Value);
	void __fastcall OnActiveChanged(System::TObject* Sender);
	void __fastcall OnDataChanged(System::TObject* Sender);
	void __fastcall OnEditingChanged(System::TObject* Sender);
	void __fastcall ReadBindScope(System::Classes::TReader* Reader);
	
protected:
	System::StaticArray<TBindNavButton*, 12> Buttons;
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall DataChanged();
	void __fastcall EditingChanged();
	void __fastcall ActiveChanged();
	virtual void __fastcall Loaded();
	virtual void __fastcall DoRealign();
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	void __fastcall CalcMinSize(float &W, float &H);
	__property System::Classes::TStrings* Hints = {read=GetHints, write=SetHints};
	__property ShowHint;
	
public:
	__fastcall virtual TCustomBindNavigator(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomBindNavigator();
	virtual void __fastcall BtnClick(Data::Bind::Controls::TNavigateButton Index);
	__property Data::Bind::Components::TBaseLinkingBindSource* DataSource = {read=GetDataSource, write=SetDataSource};
	__property Data::Bind::Controls::TNavigateButtons VisibleButtons = {read=FVisibleButtons, write=SetVisibleButtons, default=1023};
	__property Align = {default=0};
	__property Enabled;
	__property Fmx::Types::TCornerType CornerType = {read=FCornerType, write=SetCornerType, default=0};
	__property Fmx::Types::TCorners Corners = {read=FCorners, write=SetCorners, stored=IsCornersStored, nodefault};
	__property float xRadius = {read=FxRadius, write=SetxRadius};
	__property float yRadius = {read=FyRadius, write=SetyRadius};
	__property bool ConfirmDelete = {read=FConfirmDelete, write=FConfirmDelete, default=1};
	__property Visible = {default=1};
	__property EBindNavClick BeforeAction = {read=FBeforeAction, write=FBeforeAction};
	__property EBindNavClick OnClick = {read=FOnNavClick, write=FOnNavClick};
private:
	void *__IBindNavigator;	// Data::Bind::Components::IBindNavigator 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {50307CDD-63CD-4538-A211-D605C3811A0B}
	operator Data::Bind::Components::_di_IBindNavigator()
	{
		Data::Bind::Components::_di_IBindNavigator intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Data::Bind::Components::IBindNavigator*(void) { return (Data::Bind::Components::IBindNavigator*)&__IBindNavigator; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindNavigator : public TCustomBindNavigator
{
	typedef TCustomBindNavigator inherited;
	
protected:
	__property Hints;
	__property ShowHint;
	
__published:
	__property DataSource;
	__property VisibleButtons = {default=1023};
	__property Align = {default=0};
	__property Enabled;
	__property CornerType = {default=0};
	__property Corners;
	__property xRadius = {default=0};
	__property yRadius = {default=0};
	__property ConfirmDelete = {default=1};
	__property Visible = {default=1};
	__property BeforeAction;
	__property OnClick;
public:
	/* TCustomBindNavigator.Create */ inline __fastcall virtual TBindNavigator(System::Classes::TComponent* AOwner) : TCustomBindNavigator(AOwner) { }
	/* TCustomBindNavigator.Destroy */ inline __fastcall virtual ~TBindNavigator() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindNavButton : public Fmx::Stdctrls::TCornerButton
{
	typedef Fmx::Stdctrls::TCornerButton inherited;
	
private:
	Data::Bind::Controls::TNavigateButton FIndex;
	TBindNavButtonStyle FNavStyle;
	Fmx::Types::TTimer* FRepeatTimer;
	Fmx::Objects::TPath* FPath;
	void __fastcall TimerExpired(System::TObject* Sender);
	
protected:
	virtual void __fastcall ApplyStyle();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	
public:
	__fastcall virtual TBindNavButton(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TBindNavButton();
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	__property TBindNavButtonStyle NavStyle = {read=FNavStyle, write=FNavStyle, nodefault};
	__property Data::Bind::Controls::TNavigateButton Index = {read=FIndex, write=FIndex, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateAction : public Fmx::Actnlist::TAction
{
	typedef Fmx::Actnlist::TAction inherited;
	
private:
	Data::Bind::Controls::TBindNavigatorController* FController;
	Data::Bind::Controls::TNavigateButton FButton;
	Data::Bind::Components::TBaseLinkingBindSource* __fastcall GetDataSource();
	void __fastcall SetDataSource(Data::Bind::Components::TBaseLinkingBindSource* Value);
	bool __fastcall InvokeController(System::TObject* Target, System::DelphiInterface<System::Sysutils::TProc__1<Data::Bind::Controls::TBindNavigatorController*> > AProc);
	
protected:
	__property Data::Bind::Controls::TBindNavigatorController* Controller = {read=FController};
	
public:
	__fastcall virtual TFMXBindNavigateAction(System::Classes::TComponent* AComponent)/* overload */;
	__fastcall TFMXBindNavigateAction(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */;
	__fastcall virtual ~TFMXBindNavigateAction();
	virtual bool __fastcall HandlesTarget(System::TObject* Target);
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	virtual void __fastcall UpdateTarget(System::TObject* Target);
	
__published:
	__property Data::Bind::Components::TBaseLinkingBindSource* DataSource = {read=GetDataSource, write=SetDataSource};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateFirst : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateFirst(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateFirst(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateFirst() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigatePrior : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigatePrior(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigatePrior(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigatePrior() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateNext : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateNext(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateNext(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateNext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateLast : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateLast(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateLast(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateLast() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateInsert : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateInsert(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateInsert(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateInsert() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateDelete : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
private:
	bool FConfirmDelete;
	
public:
	__fastcall virtual TFMXBindNavigateDelete(System::Classes::TComponent* AComponent)/* overload */;
	virtual void __fastcall ExecuteTarget(System::TObject* Target);
	
__published:
	__property bool ConfirmDelete = {read=FConfirmDelete, write=FConfirmDelete, default=1};
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateDelete(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateDelete() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateEdit : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateEdit(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateEdit(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateEdit() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigatePost : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigatePost(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigatePost(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigatePost() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateCancel : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateCancel(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateCancel(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateCancel() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateRefresh : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateRefresh(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateRefresh(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateRefresh() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateApplyUpdates : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateApplyUpdates(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateApplyUpdates(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateApplyUpdates() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TFMXBindNavigateCancelUpdates : public TFMXBindNavigateAction
{
	typedef TFMXBindNavigateAction inherited;
	
public:
	__fastcall virtual TFMXBindNavigateCancelUpdates(System::Classes::TComponent* AComponent)/* overload */;
public:
	/* TFMXBindNavigateAction.Create */ inline __fastcall TFMXBindNavigateCancelUpdates(System::Classes::TComponent* AComponent, Data::Bind::Controls::TNavigateButton AButton)/* overload */ : TFMXBindNavigateAction(AComponent, AButton) { }
	/* TFMXBindNavigateAction.Destroy */ inline __fastcall virtual ~TFMXBindNavigateCancelUpdates() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word InitRepeatPause = System::Word(0x190);
static constexpr System::Int8 RepeatPause = System::Int8(0x64);
static constexpr System::Int8 SpaceSize = System::Int8(0x5);
}	/* namespace Navigator */
}	/* namespace Bind */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_BIND_NAVIGATOR)
using namespace Fmx::Bind::Navigator;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_BIND)
using namespace Fmx::Bind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Bind_NavigatorHPP
