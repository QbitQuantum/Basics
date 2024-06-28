// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeGalleryPanel.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeegallerypanelHPP
#define Vcltee_TeegallerypanelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.UIConsts.hpp>
#include <System.UITypes.hpp>
#include <System.Generics.Collections.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Graphics.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>
#include <Vcl.Menus.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teegallerypanel
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGalleryChart;
class DELPHICLASS TChartList;
class DELPHICLASS TChartGalleryPanel;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGalleryChart : public Vcltee::Chart::TCustomChart
{
	typedef Vcltee::Chart::TCustomChart inherited;
	
private:
	bool FSmooth;
	bool ICreatingBitmap;
	bool IMouseInside;
	bool DisabledSeries;
	Vcltee::Teengine::TTeeSeriesType* SeriesType;
	void __fastcall AfterDraw(System::TObject* Sender);
	System::Types::TRect __fastcall ArrowRect();
	void __fastcall CreateSeriesType(TChartGalleryPanel* const AGallery);
	bool __fastcall DoFocusRotation();
	HIDESBASE MESSAGE void __fastcall CMMouseEnter(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall CMMouseLeave(Winapi::Messages::TMessage &Message);
	void __fastcall DrawSmoothChart();
	void __fastcall DrawSubGalleryArrow();
	TChartGalleryPanel* __fastcall ParentGallery();
	void __fastcall SetTitleFontSize(int AOffset = 0x0);
	void __fastcall SetSmooth(bool Value);
	
protected:
	bool CanSetFocus;
	
public:
	__fastcall virtual TGalleryChart(System::Classes::TComponent* AOwner);
	void __fastcall Focus(bool Is3D);
	HIDESBASE void __fastcall SetMargins();
	void __fastcall UnFocus(bool Is3D);
	__property bool Smooth = {read=FSmooth, write=SetSmooth, default=0};
public:
	/* TCustomChart.Destroy */ inline __fastcall virtual ~TGalleryChart() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TGalleryChart(HWND ParentWindow) : Vcltee::Chart::TCustomChart(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TChartList : public System::Generics::Collections::TObjectList__1<TGalleryChart*>
{
	typedef System::Generics::Collections::TObjectList__1<TGalleryChart*> inherited;
	
private:
	TChartGalleryPanel* IGallery;
	
public:
	void __fastcall FreeAll();
public:
	/* {System_Generics_Collections}TObjectList<VCLTee_TeeGalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList()/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>() { }
	/* {System_Generics_Collections}TObjectList<VCLTee_TeeGalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<VCLTee_TeeGalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TGalleryChart*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<VCLTee_TeeGalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(System::Generics::Collections::TEnumerable__1<TGalleryChart*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<VCLTee_TeeGalleryPanel_TGalleryChart>.Destroy */ inline __fastcall virtual ~TChartList() { }
	
public:
	/* {System_Generics_Collections}TList<VCLTee_TeeGalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TGalleryChart*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(AComparer) { }
	/* {System_Generics_Collections}TList<VCLTee_TeeGalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(System::Generics::Collections::TEnumerable__1<TGalleryChart*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TChartGalleryPanel : public Vcl::Forms::TScrollBox
{
	typedef Vcl::Forms::TScrollBox inherited;
	
public:
	TGalleryChart* operator[](int Index) { return this->Chart[Index]; }
	
private:
	float FAspectRatio;
	TChartList* FCharts;
	int FColWidth;
	bool FDisplaySub;
	bool FFocusRotation;
	int FNumRows;
	int FNumCols;
	int FRowHeight;
	bool FSmooth;
	bool FView3D;
	System::Classes::TNotifyEvent FOnChangeChart;
	System::Classes::TNotifyEvent FOnSelectedChart;
	System::Classes::TNotifyEvent FOnSubSelected;
	System::Classes::TNotifyEvent FOnSubShow;
	bool ISubGallery;
	TGalleryChart* ISelectedChart;
	bool FOldSmooth;
	bool IRemoving;
	bool IResizing;
	bool ICreating;
	int __fastcall CalcNumCols();
	void __fastcall ChartKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	bool __fastcall ClickedArrow(const System::Types::TPoint &P);
	void __fastcall DoRealignCharts();
	TGalleryChart* __fastcall GetChart(int Index);
	void __fastcall SetAspectRatio(const float Value);
	void __fastcall SetNumCols(int Value);
	void __fastcall SetNumRows(int Value);
	void __fastcall SetSmooth(bool Value);
	void __fastcall SetView3D(bool Value);
	void __fastcall ShowSubGallery();
	bool __fastcall ValidSeries(Vcltee::Teengine::TTeeSeriesType* const ASeriesType, const System::UnicodeString APage);
	MESSAGE void __fastcall WMGetDlgCode(Winapi::Messages::TWMNoParams &Message);
	
protected:
	TChartGalleryPanel* tmpG;
	Vcltee::Teengine::TChartSeries* tmpSeries;
	Vcltee::Teengine::TTeeSeriesType* tmpType;
	bool CanSetFocus;
	Vcltee::Chart::TTeeCanvasClass CanvasClass;
	void __fastcall CalcChartWidthHeight();
	void __fastcall ChartEvent(System::TObject* Sender);
	void __fastcall ChartMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, int X, int Y);
	void __fastcall ChartOnDblClick(System::TObject* Sender);
	Vcltee::Teengine::TCustomAxisPanel* __fastcall CreateSubChart(const System::UnicodeString ATitle);
	void __fastcall CreateSubGallery(TChartGalleryPanel* const AGallery, Vcltee::Teengine::TChartSeriesClass AClass);
	DYNAMIC bool __fastcall DoMouseWheel(System::Classes::TShiftState Shift, int WheelDelta, const System::Types::TPoint &MousePos);
	void __fastcall GetChartXY(TGalleryChart* const AChart, /* out */ int &x, /* out */ int &y);
	DYNAMIC void __fastcall KeyDown(System::Word &Key, System::Classes::TShiftState Shift);
	virtual void __fastcall Loaded();
	DYNAMIC void __fastcall Resize();
	void __fastcall ResizeChart(TGalleryChart* const AChart, int TopOffset = 0x0);
	void __fastcall AddSubCharts(TChartGalleryPanel* AGallery);
	void __fastcall FindSelectedChart();
	void __fastcall ShowSelectedChart();
	
public:
	bool CheckSeries;
	bool FunctionsVisible;
	Vcltee::Teengine::TChartSeries* SelectedSeries;
	__fastcall virtual TChartGalleryPanel(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TChartGalleryPanel();
	void __fastcall SelectSeries(Vcltee::Teengine::TChartSeries* const Series);
	virtual void __fastcall SelectChart(TGalleryChart* const Chart);
	Vcltee::Teengine::TCustomAxisPanel* __fastcall CreateChart(Vcltee::Teengine::TTeeSeriesType* const AType);
	void __fastcall CreateChartList(Vcltee::Teengine::TChartSeriesClass *ASeriesList, const int ASeriesList_High);
	void __fastcall CreateGalleryPage(const System::UnicodeString PageName);
	__property int ColWidth = {read=FColWidth, nodefault};
	__classmethod int __fastcall DefaultMode();
	__classmethod bool __fastcall DefaultSmooth();
	bool __fastcall GetSeriesClass(/* out */ Vcltee::Teengine::TChartSeriesClass &AClass, /* out */ Vcltee::Teengine::TTeeFunctionClass &AFunctionClass, /* out */ int &ASubIndex);
	void __fastcall FinishAdd(TGalleryChart* const Chart, bool IsDisabled = false);
	void __fastcall FreeAllCharts();
	void __fastcall ResizeCharts();
	__classmethod void __fastcall SaveMode(int Value);
	__classmethod void __fastcall SaveSmooth(bool Value);
	Vcltee::Teengine::TChartSeriesClass __fastcall SelectedSeriesClass();
	void __fastcall UseTheme(const Vcltee::Chart::TChartThemeClass Theme);
	__property float AspectRatio = {read=FAspectRatio, write=SetAspectRatio};
	__property TGalleryChart* Chart[int Index] = {read=GetChart/*, default*/};
	__property TChartList* Charts = {read=FCharts};
	__property int RowHeight = {read=FRowHeight, nodefault};
	__property TGalleryChart* SelectedChart = {read=ISelectedChart, write=SelectChart};
	
__published:
	__property bool DisplaySub = {read=FDisplaySub, write=FDisplaySub, default=0};
	__property bool FocusRotation = {read=FFocusRotation, write=FFocusRotation, default=1};
	__property int NumRows = {read=FNumRows, write=SetNumRows, default=0};
	__property int NumCols = {read=FNumCols, write=SetNumCols, default=4};
	__property bool Smooth = {read=FSmooth, write=SetSmooth, default=0};
	__property bool View3D = {read=FView3D, write=SetView3D, default=1};
	__property System::Classes::TNotifyEvent OnSelectedChart = {read=FOnSelectedChart, write=FOnSelectedChart};
	__property System::Classes::TNotifyEvent OnChangeChart = {read=FOnChangeChart, write=FOnChangeChart};
	__property System::Classes::TNotifyEvent OnShowSubGallery = {read=FOnSubShow, write=FOnSubShow};
	__property System::Classes::TNotifyEvent OnSubSelected = {read=FOnSubSelected, write=FOnSubSelected};
	__property Align = {default=0};
	__property BevelInner = {index=0, default=2};
	__property BevelOuter = {index=1, default=1};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property BorderStyle = {default=1};
	__property DragCursor = {default=-12};
	__property ParentColor = {default=1};
	__property ParentShowHint = {default=1};
	__property TabStop = {default=0};
	__property AutoSize = {default=0};
	__property Constraints;
	__property ShowHint;
	__property Color;
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property PopupMenu;
	__property TabOrder = {default=-1};
	__property Visible = {default=1};
	__property Anchors = {default=3};
	__property DragKind = {default=0};
	__property OnClick;
	__property OnContextPopup;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEndDrag;
	__property OnStartDrag;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnResize;
	__property OnConstrainedResize;
	__property OnCanResize;
	__property OnDockDrop;
	__property OnDockOver;
	__property OnEndDock;
	__property OnStartDock;
	__property OnUnDock;
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartGalleryPanel(HWND ParentWindow) : Vcl::Forms::TScrollBox(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 TeeGalleryNumRows = System::Int8(0x0);
static const System::Int8 TeeGalleryNumCols = System::Int8(0x4);
static const short TeeCursorDisabled = short(-13);
#define TeeMsg_GalleryRender L"GalleryRender"
extern DELPHI_PACKAGE System::Uitypes::TColor clTeeGallery;
extern DELPHI_PACKAGE bool TeeGalleryCheckMaximize;
}	/* namespace Teegallerypanel */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEGALLERYPANEL)
using namespace Vcltee::Teegallerypanel;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeegallerypanelHPP
