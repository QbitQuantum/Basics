// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeNavigator.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeenavigatorHPP
#define Vcltee_TeenavigatorHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <System.Types.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Forms.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teenavigator
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeNavButton;
class DELPHICLASS TCustomTeeNavigator;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TTeePageNavigatorClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TTeePageNavigatorClass);
#endif /* _WIN64 */

enum DECLSPEC_DENUM TTeeNavGlyph : unsigned char { ngEnabled, ngDisabled };

enum DECLSPEC_DENUM TTeeNavigateBtn : unsigned char { nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel };

typedef System::Set<TTeeNavigateBtn, TTeeNavigateBtn::nbFirst, TTeeNavigateBtn::nbCancel> TTeeButtonSet;

class PASCALIMPLEMENTATION TTeeNavButton : public Vcl::Buttons::TSpeedButton
{
	typedef Vcl::Buttons::TSpeedButton inherited;
	
private:
	TTeeNavigateBtn FIndex;
	Vcl::Extctrls::TTimer* FRepeatTimer;
	void __fastcall TimerExpired(System::TObject* Sender);
	
protected:
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Paint();
	
public:
	__fastcall virtual ~TTeeNavButton();
	__property TTeeNavigateBtn Index = {read=FIndex, write=FIndex, nodefault};
public:
	/* TCustomSpeedButton.Create */ inline __fastcall virtual TTeeNavButton(System::Classes::TComponent* AOwner) : Vcl::Buttons::TSpeedButton(AOwner) { }
	
};


typedef void __fastcall (__closure *TNotifyButtonClickedEvent)(TTeeNavigateBtn Index);

class PASCALIMPLEMENTATION TCustomTeeNavigator : public Vcltee::Teeprocs::TCustomPanelNoCaption
{
	typedef Vcltee::Teeprocs::TCustomPanelNoCaption inherited;
	
private:
	System::Classes::TStrings* FHints;
	System::Classes::TStrings* FDefHints;
	int ButtonWidth;
	System::Types::TPoint MinBtnSize;
	TTeeNavigateBtn FocusedButton;
	TNotifyButtonClickedEvent FOnButtonClicked;
	Vcltee::Teeprocs::TCustomTeePanel* FPanel;
	void __fastcall BtnMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ClickHandler(System::TObject* Sender);
	void __fastcall CheckSize();
	void __fastcall HintsChanged(System::TObject* Sender);
	void __fastcall SetSize(int &W, int &H);
	HIDESBASE MESSAGE void __fastcall WMSize(Winapi::Messages::TWMSize &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Winapi::Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Winapi::Messages::TWMKillFocus &Message);
	MESSAGE void __fastcall WMGetDlgCode(Winapi::Messages::TWMNoParams &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Winapi::Messages::TMessage &Message);
	void __fastcall TeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	
protected:
	DYNAMIC void __fastcall BtnClick(TTeeNavigateBtn Index);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall InitButtons();
	virtual void __fastcall Loaded();
	virtual void __fastcall DoTeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetPanel(Vcltee::Teeprocs::TCustomTeePanel* const Value);
	
public:
	System::StaticArray<TTeeNavButton*, 9> Buttons;
	__fastcall virtual TCustomTeeNavigator(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomTeeNavigator();
	virtual void __fastcall EnableButtons();
	void __fastcall InitHints();
	virtual void __fastcall SetBounds(int ALeft, int ATop, int AWidth, int AHeight);
	virtual int __fastcall PageCount();
	__property Vcltee::Teeprocs::TCustomTeePanel* Panel = {read=FPanel, write=SetPanel};
	virtual void __fastcall Print();
	__property TNotifyButtonClickedEvent OnButtonClicked = {read=FOnButtonClicked, write=FOnButtonClicked};
	
__published:
	__property Align = {default=0};
	__property BorderStyle = {default=0};
	__property Color = {default=-16777201};
	__property UseDockManager = {default=1};
	__property DockSite = {default=0};
	__property DragMode = {default=0};
	__property DragCursor = {default=-12};
	__property Enabled = {default=1};
	__property ParentColor = {default=0};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=0};
	__property Visible = {default=1};
	__property Anchors = {default=3};
	__property Constraints;
	__property DragKind = {default=0};
	__property Locked = {default=0};
	__property OnClick;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDrag;
	__property OnEnter;
	__property OnExit;
	__property OnKeyDown;
	__property OnKeyPress;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnResize;
	__property OnCanResize;
	__property OnConstrainedResize;
	__property OnDockDrop;
	__property OnDockOver;
	__property OnEndDock;
	__property OnGetSiteInfo;
	__property OnStartDock;
	__property OnUnDock;
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomTeeNavigator(HWND ParentWindow) : Vcltee::Teeprocs::TCustomPanelNoCaption(ParentWindow) { }
	
private:
	void *__ITeeEventListener;	// Vcltee::Teeprocs::ITeeEventListener 
	
public:
	operator Vcltee::Teeprocs::ITeeEventListener*(void) { return (Vcltee::Teeprocs::ITeeEventListener*)&__ITeeEventListener; }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teenavigator */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEENAVIGATOR)
using namespace Vcltee::Teenavigator;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeenavigatorHPP
