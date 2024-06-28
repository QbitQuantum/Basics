// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.Controls.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_ControlsHPP
#define Firedac_Vclui_ControlsHPP

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
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <System.IniFiles.hpp>
#include <Vcl.Dialogs.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Controls
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDGUIxFormsPanelTree;
class DELPHICLASS TFDGUIxFormsDblListBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFDGUIxFormsPanelTree : public Vcl::Forms::TScrollBox
{
	typedef Vcl::Forms::TScrollBox inherited;
	
private:
	System::Classes::TList* FPanels;
	bool FLock;
	MESSAGE void __fastcall CMControlChange(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMEnabledChanged(Winapi::Messages::TMessage &Message);
	void __fastcall ChangeAllState(bool AExpand);
	
protected:
	virtual void __fastcall Loaded();
	DYNAMIC bool __fastcall DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos);
	
public:
	__fastcall virtual TFDGUIxFormsPanelTree(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDGUIxFormsPanelTree();
	void __fastcall LoadState(const System::UnicodeString ASection, System::Inifiles::TCustomIniFile* AIni);
	void __fastcall SaveState(const System::UnicodeString ASection, System::Inifiles::TCustomIniFile* AIni);
	
__published:
	__property BevelOuter = {index=1, default=1};
public:
	/* TWinControl.CreateParented */ inline __fastcall TFDGUIxFormsPanelTree(HWND ParentWindow) : Vcl::Forms::TScrollBox(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TFDGUIxFormsDblListBox : public Vcl::Extctrls::TCustomPanel
{
	typedef Vcl::Extctrls::TCustomPanel inherited;
	
private:
	void __fastcall IncludeBtnClick(System::TObject* Sender);
	void __fastcall ExcludeBtnClick(System::TObject* Sender);
	void __fastcall IncAllBtnClick(System::TObject* Sender);
	void __fastcall ExcAllBtnClick(System::TObject* Sender);
	void __fastcall DownBtnClick(System::TObject* Sender);
	void __fastcall UpBtnClick(System::TObject* Sender);
	void __fastcall MoveSelected(Vcl::Stdctrls::TCustomListBox* List, System::Classes::TStrings* Items);
	void __fastcall SetItem(Vcl::Stdctrls::TListBox* List, int Index);
	int __fastcall GetFirstSelection(Vcl::Stdctrls::TCustomListBox* List);
	void __fastcall ListDragOver(System::TObject* Sender, System::TObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept);
	void __fastcall ListDragDrop(System::TObject* Sender, System::TObject* Source, int X, int Y);
	void __fastcall SetS(int AIndex, const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetS(int AIndex);
	void __fastcall SetItems(int AIndex, System::Classes::TStrings* AValues);
	System::Classes::TStrings* __fastcall GetItems(int AIndex);
	System::Classes::TNotifyEvent __fastcall GetEvent(int AIndex);
	void __fastcall SetEvent(int AIndex, System::Classes::TNotifyEvent AValue);
	void __fastcall SetI(int AIndex, int AValue);
	int __fastcall GetI(int AIndex);
	void __fastcall SetB(int AIndex, bool AValue);
	bool __fastcall GetB(int AIndex);
	void __fastcall ListKeys(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall ListClick(System::TObject* Sender);
	
protected:
	virtual void __fastcall AlignControls(Vcl::Controls::TControl* AControl, System::Types::TRect &Rect);
	
public:
	Vcl::Stdctrls::TLabel* DstLabel;
	Vcl::Stdctrls::TLabel* SrcLabel;
	Vcl::Stdctrls::TListBox* SrcList;
	Vcl::Buttons::TSpeedButton* IncludeBtn;
	Vcl::Buttons::TSpeedButton* IncAllBtn;
	Vcl::Buttons::TSpeedButton* ExcludeBtn;
	Vcl::Buttons::TSpeedButton* ExAllBtn;
	Vcl::Buttons::TSpeedButton* UpBtn;
	Vcl::Buttons::TSpeedButton* DownBtn;
	Vcl::Stdctrls::TListBox* DstList;
	__fastcall virtual TFDGUIxFormsDblListBox(System::Classes::TComponent* AOwner);
	void __fastcall SetButtons();
	__property int SrcItemIndex = {read=GetI, write=SetI, index=0, nodefault};
	__property int DstItemIndex = {read=GetI, write=SetI, index=1, nodefault};
	
__published:
	__property System::UnicodeString DestCaption = {read=GetS, write=SetS, index=0};
	__property System::UnicodeString SrcCaption = {read=GetS, write=SetS, index=1};
	__property System::UnicodeString DestListHint = {read=GetS, write=SetS, index=2};
	__property System::UnicodeString SrcListHint = {read=GetS, write=SetS, index=3};
	__property System::UnicodeString IncHint = {read=GetS, write=SetS, index=4};
	__property System::UnicodeString IncAllHint = {read=GetS, write=SetS, index=5};
	__property System::UnicodeString ExHint = {read=GetS, write=SetS, index=6};
	__property System::UnicodeString ExAllHint = {read=GetS, write=SetS, index=7};
	__property System::UnicodeString UpHint = {read=GetS, write=SetS, index=8};
	__property System::UnicodeString DownHint = {read=GetS, write=SetS, index=9};
	__property System::Classes::TStrings* SrcItems = {read=GetItems, write=SetItems, index=0};
	__property System::Classes::TStrings* DstItems = {read=GetItems, write=SetItems, index=1};
	__property bool SrcItemsSorted = {read=GetB, write=SetB, index=0, default=1};
	__property System::Classes::TNotifyEvent OnSrcClick = {read=GetEvent, write=SetEvent, index=0};
	__property System::Classes::TNotifyEvent OnDstClick = {read=GetEvent, write=SetEvent, index=1};
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property BevelEdges = {default=15};
	__property BevelKind = {default=0};
	__property BevelOuter = {default=2};
	__property BevelInner = {default=0};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property BorderStyle = {default=0};
	__property DragCursor = {default=-12};
	__property Enabled = {default=1};
	__property Color = {default=-16777201};
	__property Font;
	__property Ctl3D;
	__property ParentCtl3D = {default=1};
	__property ParentColor = {default=0};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=0};
	__property Visible = {default=1};
	__property OnEnter;
	__property OnExit;
	__property OnResize;
public:
	/* TCustomControl.Destroy */ inline __fastcall virtual ~TFDGUIxFormsDblListBox() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFDGUIxFormsDblListBox(HWND ParentWindow) : Vcl::Extctrls::TCustomPanel(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall FDGUIxSetupEditor(Vcl::Stdctrls::TComboBox* ACombo, Vcl::Stdctrls::TEdit* AEdit, Vcl::Stdctrls::TCustomEdit* AFileEdt, Vcl::Dialogs::TOpenDialog* AOpenDlg, const System::UnicodeString AType);
extern DELPHI_PACKAGE void __fastcall FDGUIxCancel(void);
extern DELPHI_PACKAGE void * __fastcall FDGUIxBeginModal(Vcl::Forms::TCustomForm* AForm, bool ASaveActive = true);
extern DELPHI_PACKAGE void __fastcall FDGUIxEndModal(void * &AData);
}	/* namespace Controls */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_CONTROLS)
using namespace Firedac::Vclui::Controls;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI)
using namespace Firedac::Vclui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Vclui_ControlsHPP
