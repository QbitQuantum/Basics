// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeLisB.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeelisbHPP
#define Vcltee_TeelisbHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeEngine.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teelisb
{
//-- forward type declarations -----------------------------------------------
struct TListBoxSection;
class DELPHICLASS TChartListBox;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TListBoxSection
{
public:
	int Width;
	bool Visible;
};


typedef System::StaticArray<TListBoxSection, 4> TListBoxSections;

typedef void __fastcall (__closure *TDblClickSeriesEvent)(TChartListBox* Sender, int Index);

typedef void __fastcall (__closure *TNotifySeriesEvent)(TChartListBox* Sender, Vcltee::Teengine::TCustomChartSeries* Series);

typedef void __fastcall (__closure *TChangeOrderEvent)(TChartListBox* Sender, Vcltee::Teengine::TCustomChartSeries* Series1, Vcltee::Teengine::TCustomChartSeries* Series2);

class PASCALIMPLEMENTATION TChartListBox : public Vcl::Stdctrls::TCustomListBox
{
	typedef Vcl::Stdctrls::TCustomListBox inherited;
	
private:
	bool FAllowAdd;
	bool FAllowDelete;
	bool FAskDelete;
	Vcltee::Chart::TCustomChart* FChart;
	Vcltee::Chart::TCheckBoxesStyle FCheckStyle;
	Vcl::Stdctrls::TEdit* FEditor;
	bool FEnableChangeColor;
	bool FEnableDragSeries;
	bool FEnableChangeType;
	bool FFontSeriesColor;
	Vcltee::Teengine::TSeriesGroup* FGroup;
	System::Types::TPoint FHitTest;
	bool FNames;
	TNotifySeriesEvent FOnChangeActive;
	TNotifySeriesEvent FOnChangeColor;
	TChangeOrderEvent FOnChangeOrder;
	TDblClickSeriesEvent FOnEditSeries;
	TNotifySeriesEvent FOnRemovedSeries;
	System::Classes::TStrings* FOtherItems;
	System::Classes::TNotifyEvent FOtherItemsChange;
	System::Classes::TNotifyEvent FRefresh;
	bool ComingFromDoubleClick;
	bool IChanging;
	void __fastcall CheckLegendBoxes();
	HIDESBASE MESSAGE void __fastcall CMColorChanged(Winapi::Messages::TMessage &Message);
	void __fastcall DoRefresh();
	void __fastcall EditorKey(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall EditorPress(System::TObject* Sender, System::WideChar &Key);
	Vcltee::Teengine::TChartSeries* __fastcall GetSelectedSeries();
	Vcltee::Teengine::TCustomSeriesList* __fastcall GetSeriesGroup();
	bool __fastcall GetShowActive();
	bool __fastcall GetShowIcon();
	bool __fastcall GetShowColor();
	bool __fastcall GetShowTitle();
	Vcltee::Teengine::TChartSeries* __fastcall GetSeries(int Index);
	void __fastcall LBSeriesClick(System::TObject* Sender);
	void __fastcall LBSeriesDrawItem(Vcl::Controls::TWinControl* Control, int Index, const System::Types::TRect &Rect, Winapi::Windows::TOwnerDrawState State);
	void __fastcall LBSeriesDragOver(System::TObject* Sender, System::TObject* Source, int X, int Y, System::Uitypes::TDragState State, bool &Accept);
	void __fastcall RefreshDesigner();
	int __fastcall SectionLeft(int ASection);
	void __fastcall SelectSeries(int AIndex);
	void __fastcall SetChart(Vcltee::Chart::TCustomChart* const Value);
	void __fastcall SetCheckStyle(Vcltee::Chart::TCheckBoxesStyle Value);
	void __fastcall SetFontSeriesColor(const bool Value);
	void __fastcall SetGroup(Vcltee::Teengine::TSeriesGroup* const Value);
	void __fastcall SetNames(bool Value);
	void __fastcall SetSelectedSeries(Vcltee::Teengine::TChartSeries* const Value);
	void __fastcall SetShowActive(bool Value);
	void __fastcall SetShowIcon(bool Value);
	void __fastcall SetShowColor(bool Value);
	void __fastcall SetShowTitle(bool Value);
	Vcl::Controls::TWinControl* __fastcall VerifyParent(/* out */ Vcl::Controls::TWinControl* &AControl);
	
protected:
	Vcl::Controls::TControl* OtherItemsControl;
	DYNAMIC void __fastcall DblClick();
	virtual void __fastcall CreateWindowHandle(const Vcl::Controls::TCreateParams &Params);
	virtual int __fastcall GetItemIndex();
	DYNAMIC void __fastcall KeyUp(System::Word &Key, System::Classes::TShiftState Shift);
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	HIDESBASE MESSAGE void __fastcall WMNCHitTest(Winapi::Messages::TWMNCHitTest &Msg);
	HIDESBASE MESSAGE void __fastcall WMSetCursor(Winapi::Messages::TWMSetCursor &Msg);
	virtual void __fastcall SetParent(Vcl::Controls::TWinControl* Control);
	void __fastcall TeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	
public:
	TListBoxSections Sections;
	__fastcall virtual TChartListBox(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TChartListBox();
	Vcltee::Teengine::TChartSeries* __fastcall AddSeriesGallery();
	bool __fastcall AnySelected();
	void __fastcall ChangeTypeSeries(System::TObject* Sender);
	void __fastcall ClearItems();
	void __fastcall CloneSeries();
	bool __fastcall DeleteSeries();
	DYNAMIC void __fastcall DragDrop(System::TObject* Source, int X, int Y);
	void __fastcall FillSeries(Vcltee::Teengine::TChartSeries* const OldSeries);
	__classmethod System::Uitypes::TColor __fastcall GetBackColor(Vcl::Controls::TControl* const AList, bool IsSelected, bool IsNotFocusedAndSelected, bool IsFocused);
	__classmethod System::Uitypes::TColor __fastcall GetFontColor(Vcl::Controls::TControl* const AControl, Vcl::Graphics::TFont* const AFont, bool IsSelected);
	void __fastcall HideEditor();
	void __fastcall MoveCurrentDown();
	void __fastcall MoveCurrentUp();
	__property System::Classes::TStrings* OtherItems = {read=FOtherItems, write=FOtherItems};
	bool __fastcall PointInSection(const System::Types::TPoint &P, int ASection);
	bool __fastcall RenameSeries();
	virtual void __fastcall SelectAll();
	__property Vcltee::Teengine::TChartSeries* Series[int Index] = {read=GetSeries};
	__property Vcltee::Teengine::TSeriesGroup* SeriesGroup = {read=FGroup, write=SetGroup};
	int __fastcall SeriesAtMousePos(/* out */ System::Types::TPoint &p);
	void __fastcall ShowEditor();
	void __fastcall SwapSeries(int tmp1, int tmp2);
	void __fastcall UpdateSeries();
	__property Vcltee::Teengine::TChartSeries* SelectedSeries = {read=GetSelectedSeries, write=SetSelectedSeries};
	__property bool ShowSeriesNames = {read=FNames, write=SetNames, nodefault};
	
__published:
	__property bool AllowAddSeries = {read=FAllowAdd, write=FAllowAdd, default=1};
	__property bool AllowDeleteSeries = {read=FAllowDelete, write=FAllowDelete, default=1};
	__property bool AskDelete = {read=FAskDelete, write=FAskDelete, default=1};
	__property Vcltee::Chart::TCustomChart* Chart = {read=FChart, write=SetChart};
	__property Vcltee::Chart::TCheckBoxesStyle CheckStyle = {read=FCheckStyle, write=SetCheckStyle, default=0};
	__property bool EnableChangeColor = {read=FEnableChangeColor, write=FEnableChangeColor, default=1};
	__property bool EnableDragSeries = {read=FEnableDragSeries, write=FEnableDragSeries, default=1};
	__property bool EnableChangeType = {read=FEnableChangeType, write=FEnableChangeType, default=1};
	__property bool FontSeriesColor = {read=FFontSeriesColor, write=SetFontSeriesColor, default=0};
	__property TNotifySeriesEvent OnChangeActive = {read=FOnChangeActive, write=FOnChangeActive};
	__property TNotifySeriesEvent OnChangeColor = {read=FOnChangeColor, write=FOnChangeColor};
	__property TChangeOrderEvent OnChangeOrder = {read=FOnChangeOrder, write=FOnChangeOrder};
	__property TDblClickSeriesEvent OnDblClickSeries = {read=FOnEditSeries, write=FOnEditSeries};
	__property System::Classes::TNotifyEvent OnOtherItemsChange = {read=FOtherItemsChange, write=FOtherItemsChange};
	__property System::Classes::TNotifyEvent OnRefresh = {read=FRefresh, write=FRefresh};
	__property TNotifySeriesEvent OnRemovedSeries = {read=FOnRemovedSeries, write=FOnRemovedSeries};
	__property bool ShowActiveCheck = {read=GetShowActive, write=SetShowActive, default=1};
	__property bool ShowSeriesColor = {read=GetShowColor, write=SetShowColor, default=1};
	__property bool ShowSeriesIcon = {read=GetShowIcon, write=SetShowIcon, default=1};
	__property bool ShowSeriesTitle = {read=GetShowTitle, write=SetShowTitle, default=1};
	__property OnDrawItem;
	__property Align = {default=0};
	__property BorderStyle = {default=1};
	__property Color = {default=-16777211};
	__property Ctl3D;
	__property Enabled = {default=1};
	__property ExtendedSelect = {default=1};
	__property Font;
	__property ImeMode = {default=3};
	__property ImeName = {default=0};
	__property ItemHeight = {default=16};
	__property MultiSelect = {default=1};
	__property ParentColor = {default=0};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ShowHint;
	__property Sorted = {default=0};
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property OnClick;
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
	__property OnStartDock;
	__property OnStartDrag;
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartListBox(HWND ParentWindow) : Vcl::Stdctrls::TCustomListBox(ParentWindow) { }
	
private:
	void *__ITeeEventListener;	// Vcltee::Teeprocs::ITeeEventListener 
	
public:
	operator Vcltee::Teeprocs::ITeeEventListener*(void) { return (Vcltee::Teeprocs::ITeeEventListener*)&__ITeeEventListener; }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Vcltee::Teengine::TChartSeries* __fastcall (*TeeAddGalleryProc)(System::Classes::TComponent* const AOwner, Vcltee::Chart::TCustomChart* const Chart, Vcltee::Teengine::TChartSeries* const Series);
extern DELPHI_PACKAGE Vcltee::Teengine::TChartSeriesClass __fastcall (*TeeChangeGalleryProc)(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartSeries* &Series);
}	/* namespace Teelisb */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEELISB)
using namespace Vcltee::Teelisb;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeelisbHPP
