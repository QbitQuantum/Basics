// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeChartGrid.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeechartgridHPP
#define Vcltee_TeechartgridHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Grids.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Forms.hpp>
#include <System.Types.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeNavigator.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teechartgrid
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomChartGrid;
class DELPHICLASS TChartGrid;
class DELPHICLASS TChartGridNavigator;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TChartGridShow : unsigned char { cgsAuto, cgsNo, cgsYes };

typedef void __fastcall (__closure *TEditingCellEvent)(TCustomChartGrid* Sender, int ACol, int ARow, bool &Allow);

class PASCALIMPLEMENTATION TCustomChartGrid : public Vcl::Grids::TCustomGrid
{
	typedef Vcl::Grids::TCustomGrid inherited;
	
	
private:
	typedef System::DynamicArray<bool> _TCustomChartGrid__1;
	
	
private:
	bool FAllowAppend;
	bool FAllowInsertSeries;
	Vcltee::Chart::TCustomChart* FChart;
	bool FColors;
	Vcltee::Tecanvas::TTeeGradient* FGradientCell;
	bool FGrid3DMode;
	bool FLabels;
	bool FSymbolClickable;
	TChartGridShow FVisuals;
	TChartGridShow FXValues;
	System::UnicodeString FOldValue;
	System::Classes::TNotifyEvent FOnChangeColor;
	TEditingCellEvent FOnEditing;
	Vcl::Grids::TSetEditEvent FOnSetCell;
	bool FShowFields;
	bool FWasNull;
	_TCustomChartGrid__1 IHasNo;
	TChartGridNavigator* INavigator;
	Vcl::Menus::TPopupMenu* IPopupVisual;
	Vcltee::Teengine::TChartSeries* FSeries;
	Vcltee::Teengine::TCustomAxisPanel* ISeriesChart;
	void __fastcall AddListener(Vcltee::Teengine::TCustomAxisPanel* const AChart);
	bool __fastcall AtSeriesColor(Vcltee::Teengine::TChartSeries* &Series);
	bool __fastcall CanInsertSeries();
	virtual void __fastcall CanvasChanged(System::TObject* Sender);
	void __fastcall DoChangeVisual(Vcltee::Teengine::TChartSeries* const ASeries, int AIndex);
	System::UnicodeString __fastcall FindHeaderText(int ACol);
	Vcltee::Tecanvas::TTeeGradient* __fastcall GetGradientCell();
	bool __fastcall GetReadOnly();
	void __fastcall MenuChangeVisual(System::TObject* Sender);
	void __fastcall MenuDeleteVisual(System::TObject* Sender);
	void __fastcall MenuEditVisual(System::TObject* Sender);
	Vcltee::Teengine::TChartSeries* __fastcall NewBarSeries();
	void __fastcall NotifyChange();
	void __fastcall Regenerate();
	void __fastcall RemoveListener(Vcltee::Teengine::TCustomAxisPanel* const AChart);
	void __fastcall SetBooleanProperty(bool &Variable, bool Value);
	void __fastcall SetChart(Vcltee::Chart::TCustomChart* const AChart);
	void __fastcall SetGradientCell(Vcltee::Tecanvas::TTeeGradient* const Value);
	void __fastcall SetGrid3DMode(bool Value);
	void __fastcall SetManualData(Vcltee::Teengine::TChartSeries* const ASeries);
	void __fastcall SetNavigator(TChartGridNavigator* const ANavigator);
	void __fastcall SetReadOnly(const bool Value);
	System::Types::TRect __fastcall SymbolRect(const System::Types::TRect &Rect);
	void __fastcall SetShowColors(bool Value);
	void __fastcall SetShowFields(bool Value);
	void __fastcall SetShowLabels(bool Value);
	void __fastcall SetShowVisuals(const TChartGridShow Value);
	void __fastcall SetShowXValues(const TChartGridShow Value);
	void __fastcall SetSeries(Vcltee::Teengine::TChartSeries* const Value);
	int __fastcall ValidListsOfSeries(Vcltee::Teengine::TChartSeries* const ASeries, const int AIndex);
	
protected:
	System::Classes::TNotifyEvent FActiveChanged;
	Vcl::Grids::TSelectCellEvent FSelectedChanged;
	System::Classes::TNotifyEvent FOnTopLeftChanged;
	DYNAMIC bool __fastcall CanEditModify();
	virtual bool __fastcall CanEditShow();
	DYNAMIC void __fastcall DblClick();
	virtual void __fastcall DrawCell(int ACol, int ARow, const System::Types::TRect &ARect, Vcl::Grids::TGridDrawState AState);
	DYNAMIC System::UnicodeString __fastcall GetEditText(int ACol, int ARow);
	Vcltee::Teengine::TChartSeries* __fastcall GetSeriesColor(/* out */ System::Uitypes::TColor &AColor)/* overload */;
	Vcltee::Teengine::TChartSeries* __fastcall GetSeriesColor(/* out */ System::Uitypes::TColor &AColor, int ACol, int ARow)/* overload */;
	void __fastcall EditVisual(int ACol);
	bool __fastcall HasPoints();
	bool __fastcall HasVisuals(Vcltee::Teengine::TChartSeries* const ASeries);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall Loaded();
	DYNAMIC void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	DYNAMIC void __fastcall MouseMove(System::Classes::TShiftState Shift, int X, int Y);
	virtual bool __fastcall SelectCell(int ACol, int ARow);
	DYNAMIC void __fastcall SetEditText(int ACol, int ARow, const System::UnicodeString Value);
	void __fastcall TeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	bool __fastcall IsVisualsColumn(int ACol);
	DYNAMIC void __fastcall TopLeftChanged();
	
public:
	bool AllowChanges;
	__fastcall virtual TCustomChartGrid(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomChartGrid();
	void __fastcall AppendRow();
	void __fastcall ChangeColor()/* overload */;
	void __fastcall ChangeColor(System::Uitypes::TColor AColor)/* overload */;
	void __fastcall ChangeColor(Vcltee::Teengine::TChartSeries* const ASeries, System::Uitypes::TColor AColor)/* overload */;
	int __fastcall ColorsColumn();
	void __fastcall Delete();
	int __fastcall FindXYZIndex(Vcltee::Teengine::TChartSeries* const ASeries, int ARow, int ACol);
	int __fastcall FirstRowNum();
	Vcltee::Teengine::TChartSeries* __fastcall GetSeries(int ACol)/* overload */;
	Vcltee::Teengine::TChartSeries* __fastcall GetSeries(int ACol, /* out */ Vcltee::Teengine::TChartValueList* &AList)/* overload */;
	Vcltee::Teengine::TChartSeries* __fastcall GetXYZSeries();
	HIDESBASE void __fastcall Insert();
	int __fastcall LabelsColumn();
	void __fastcall RecalcDimensions();
	void __fastcall StartEditing();
	void __fastcall StopEditing(bool Cancel);
	__property bool AllowAppend = {read=FAllowAppend, write=FAllowAppend, default=1};
	__property bool AllowInsertSeries = {read=FAllowInsertSeries, write=FAllowInsertSeries, default=0};
	__property Vcltee::Chart::TCustomChart* Chart = {read=FChart, write=SetChart};
	__property Vcltee::Tecanvas::TTeeGradient* GradientCell = {read=GetGradientCell, write=SetGradientCell};
	__property bool ReadOnly = {read=GetReadOnly, write=SetReadOnly, default=0};
	__property Vcltee::Teengine::TChartSeries* Series = {read=FSeries, write=SetSeries};
	__property bool SeriesSymbolClickable = {read=FSymbolClickable, write=FSymbolClickable, default=1};
	__property bool ShowColors = {read=FColors, write=SetShowColors, default=0};
	__property bool ShowFields = {read=FShowFields, write=SetShowFields, default=1};
	__property bool ShowLabels = {read=FLabels, write=SetShowLabels, default=1};
	__property TChartGridShow ShowVisuals = {read=FVisuals, write=SetShowVisuals, default=0};
	__property TChartGridShow ShowXValues = {read=FXValues, write=SetShowXValues, default=0};
	__property FixedCols = {default=1};
	__property DefaultRowHeight = {default=16};
	__property GridLineWidth = {default=1};
	__property bool Grid3DMode = {read=FGrid3DMode, write=SetGrid3DMode, default=0};
	__property System::Classes::TNotifyEvent OnChangeColor = {read=FOnChangeColor, write=FOnChangeColor};
	__property TEditingCellEvent OnEditingCell = {read=FOnEditing, write=FOnEditing};
	__property Vcl::Grids::TSetEditEvent OnSetEditText = {read=FOnSetCell, write=FOnSetCell};
	__property System::Classes::TNotifyEvent OnTopLeftChanged = {read=FOnTopLeftChanged, write=FOnTopLeftChanged};
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomChartGrid(HWND ParentWindow) : Vcl::Grids::TCustomGrid(ParentWindow) { }
	
private:
	void *__ITeeEventListener;	// Vcltee::Teeprocs::ITeeEventListener 
	
public:
	operator Vcltee::Teeprocs::ITeeEventListener*(void) { return (Vcltee::Teeprocs::ITeeEventListener*)&__ITeeEventListener; }
	
};


class PASCALIMPLEMENTATION TChartGrid : public TCustomChartGrid
{
	typedef TCustomChartGrid inherited;
	
public:
	__property Col;
	__property ColCount = {default=5};
	__property ColWidths;
	__property EditorMode;
	__property GridHeight;
	__property GridWidth;
	__property LeftCol;
	__property Selection;
	__property Row;
	__property RowCount = {default=5};
	__property RowHeights;
	__property TabStops;
	__property TopRow;
	
__published:
	__property Align = {default=0};
	__property Anchors = {default=3};
	__property BiDiMode;
	__property BorderStyle = {default=1};
	__property Color = {default=-16777211};
	__property Constraints;
	__property Ctl3D;
	__property DefaultColWidth = {default=64};
	__property DefaultRowHeight = {default=16};
	__property DefaultDrawing = {default=1};
	__property DragMode = {default=0};
	__property DragCursor = {default=-12};
	__property DragKind = {default=0};
	__property Enabled = {default=1};
	__property FixedColor = {default=-16777201};
	__property Font;
	__property GridLineWidth = {default=1};
	__property Options = {default=524319};
	__property ParentBiDiMode = {default=1};
	__property ParentColor = {default=0};
	__property ParentCtl3D = {default=1};
	__property ParentFont = {default=1};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property ScrollBars = {default=3};
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property TabStop = {default=1};
	__property Visible = {default=1};
	__property OnClick;
	__property OnContextPopup;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDrag;
	__property OnStartDrag;
	__property OnEndDock;
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
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnStartDock;
	__property Chart;
	__property Series;
	__property ShowColors = {default=0};
	__property ShowLabels = {default=1};
	__property ShowVisuals = {default=0};
	__property ShowXValues = {default=0};
	__property OnChangeColor;
	__property OnEditingCell;
	__property OnSetEditText;
	__property OnTopLeftChanged;
public:
	/* TCustomChartGrid.Create */ inline __fastcall virtual TChartGrid(System::Classes::TComponent* AOwner) : TCustomChartGrid(AOwner) { }
	/* TCustomChartGrid.Destroy */ inline __fastcall virtual ~TChartGrid() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartGrid(HWND ParentWindow) : TCustomChartGrid(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TChartGridNavigator : public Vcltee::Teenavigator::TCustomTeeNavigator
{
	typedef Vcltee::Teenavigator::TCustomTeeNavigator inherited;
	
private:
	TCustomChartGrid* FGrid;
	void __fastcall ActiveChanged(System::TObject* Sender);
	void __fastcall EnableButtonsColRow(int ACol, int ARow);
	void __fastcall SelectedChanged(System::TObject* Sender, int ACol, int ARow, bool &CanSelect);
	void __fastcall SetGrid(TCustomChartGrid* Value);
	
protected:
	DYNAMIC void __fastcall BtnClick(Vcltee::Teenavigator::TTeeNavigateBtn Index);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual void __fastcall EnableButtons();
	
__published:
	__property TCustomChartGrid* Grid = {read=FGrid, write=SetGrid};
public:
	/* TCustomTeeNavigator.Create */ inline __fastcall virtual TChartGridNavigator(System::Classes::TComponent* AOwner) : Vcltee::Teenavigator::TCustomTeeNavigator(AOwner) { }
	/* TCustomTeeNavigator.Destroy */ inline __fastcall virtual ~TChartGridNavigator() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartGridNavigator(HWND ParentWindow) : Vcltee::Teenavigator::TCustomTeeNavigator(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teechartgrid */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEECHARTGRID)
using namespace Vcltee::Teechartgrid;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeechartgridHPP
