// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Chart.GalleryPanel.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Chart_GallerypanelHPP
#define Fmxtee_Chart_GallerypanelHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UIConsts.hpp>
#include <System.UITypes.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Platform.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Controls.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <FMXTee.Canvas.hpp>
#include <FMXTee.Procs.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Chart.hpp>
#include <FMXTee.Series.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Chart
{
namespace Gallerypanel
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGalleryChart;
class DELPHICLASS TChartList;
class DELPHICLASS TChartGalleryPanel;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGalleryChart : public Fmxtee::Chart::TCustomChart
{
	typedef Fmxtee::Chart::TCustomChart inherited;
	
private:
	bool FSmooth;
	bool ICreatingBitmap;
	bool IMouseInside;
	bool DisabledSeries;
	Fmxtee::Engine::TTeeSeriesType* SeriesType;
	void __fastcall AfterDraw(System::TObject* Sender);
	System::Types::TRectF __fastcall ArrowRect();
	void __fastcall CreateSeriesType(TChartGalleryPanel* const AGallery);
	bool __fastcall DoFocusRotation();
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
	
};


class PASCALIMPLEMENTATION TChartList : public System::Generics::Collections::TObjectList__1<TGalleryChart*>
{
	typedef System::Generics::Collections::TObjectList__1<TGalleryChart*> inherited;
	
private:
	TChartGalleryPanel* IGallery;
	
public:
	void __fastcall FreeAll();
public:
	/* {System_Generics_Collections}TObjectList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList()/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>() { }
	/* {System_Generics_Collections}TObjectList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TGalleryChart*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(System::Generics::Collections::TEnumerable__1<TGalleryChart*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Destroy */ inline __fastcall virtual ~TChartList() { }
	
public:
	/* {System_Generics_Collections}TList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TGalleryChart*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(AComparer) { }
	/* {System_Generics_Collections}TList<FMXTee_Chart_GalleryPanel_TGalleryChart>.Create */ inline __fastcall TChartList(System::Generics::Collections::TEnumerable__1<TGalleryChart*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<TGalleryChart*>(Collection) { }
	
};


class PASCALIMPLEMENTATION TChartGalleryPanel : public Fmx::Layouts::TVertScrollBox
{
	typedef Fmx::Layouts::TVertScrollBox inherited;
	
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
	void __fastcall ChartKeyDown(System::TObject* Sender, System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	bool __fastcall ClickedArrow(const System::Types::TPointF &P);
	void __fastcall DoRealignCharts();
	TGalleryChart* __fastcall GetChart(int Index);
	void __fastcall SetAspectRatio(const float Value);
	void __fastcall SetNumCols(int Value);
	void __fastcall SetNumRows(int Value);
	void __fastcall SetSmooth(bool Value);
	void __fastcall SetView3D(bool Value);
	void __fastcall ShowSubGallery();
	bool __fastcall ValidSeries(Fmxtee::Engine::TTeeSeriesType* const ASeriesType, const System::UnicodeString APage);
	
protected:
	TChartGalleryPanel* tmpG;
	Fmxtee::Engine::TChartSeries* tmpSeries;
	Fmxtee::Engine::TTeeSeriesType* tmpType;
	bool CanSetFocus;
	Fmxtee::Chart::TTeeCanvasClass CanvasClass;
	void __fastcall CalcChartWidthHeight();
	void __fastcall ChartEvent(System::TObject* Sender);
	void __fastcall ChartMouseUp(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall ChartOnDblClick(System::TObject* Sender);
	Fmxtee::Engine::TCustomAxisPanel* __fastcall CreateSubChart(const System::UnicodeString ATitle);
	void __fastcall CreateSubGallery(TChartGalleryPanel* const AGallery, Fmxtee::Engine::TChartSeriesClass AClass);
	virtual void __fastcall DoRealign();
	void __fastcall GetChartXY(TGalleryChart* const AChart, /* out */ int &x, /* out */ int &y);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall Loaded();
	virtual void __fastcall Resize();
	void __fastcall ResizeChart(TGalleryChart* const AChart, int TopOffset = 0x0);
	void __fastcall AddSubCharts(TChartGalleryPanel* AGallery);
	void __fastcall FindSelectedChart();
	void __fastcall ShowSelectedChart();
	
public:
	bool CheckSeries;
	bool FunctionsVisible;
	Fmxtee::Engine::TChartSeries* SelectedSeries;
	__fastcall virtual TChartGalleryPanel(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TChartGalleryPanel();
	void __fastcall SelectSeries(Fmxtee::Engine::TChartSeries* const Series);
	virtual void __fastcall SelectChart(TGalleryChart* const Chart);
	Fmxtee::Engine::TCustomAxisPanel* __fastcall CreateChart(Fmxtee::Engine::TTeeSeriesType* const AType);
	void __fastcall CreateChartList(Fmxtee::Engine::TChartSeriesClass *ASeriesList, const int ASeriesList_High);
	void __fastcall CreateGalleryPage(const System::UnicodeString PageName);
	__property int ColWidth = {read=FColWidth, nodefault};
	__classmethod int __fastcall DefaultMode();
	__classmethod bool __fastcall DefaultSmooth();
	bool __fastcall GetSeriesClass(/* out */ Fmxtee::Engine::TChartSeriesClass &AClass, /* out */ Fmxtee::Engine::TTeeFunctionClass &AFunctionClass, /* out */ int &ASubIndex);
	void __fastcall FinishAdd(TGalleryChart* const Chart, bool IsDisabled = false);
	void __fastcall FreeAllCharts();
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	void __fastcall ResizeCharts();
	__classmethod void __fastcall SaveMode(int Value);
	__classmethod void __fastcall SaveSmooth(bool Value);
	Fmxtee::Engine::TChartSeriesClass __fastcall SelectedSeriesClass();
	void __fastcall UseTheme(const Fmxtee::Chart::TChartThemeClass Theme);
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
	__property Action;
	__property Align = {default=0};
	__property ParentShowHint = {default=1};
	__property ShowHint;
	__property DragMode = {default=0};
	__property Enabled;
	__property PopupMenu;
	__property TabOrder = {default=-1};
	__property Visible = {default=1};
	__property Anchors;
	__property OnClick;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnEnter;
	__property OnExit;
	__property OnMouseDown;
	__property OnMouseEnter;
	__property OnMouseLeave;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnResize;
};


//-- var, const, procedure ---------------------------------------------------
static const System::Int8 TeeGalleryNumRows = System::Int8(0x0);
static const System::Int8 TeeGalleryNumCols = System::Int8(0x4);
static const short TeeCursorDisabled = short(-18);
#define TeeMsg_GalleryRender L"GalleryRender"
extern DELPHI_PACKAGE System::Uitypes::TAlphaColor clTeeGallery;
extern DELPHI_PACKAGE bool TeeGalleryCheckMaximize;
}	/* namespace Gallerypanel */
}	/* namespace Chart */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART_GALLERYPANEL)
using namespace Fmxtee::Chart::Gallerypanel;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_CHART)
using namespace Fmxtee::Chart;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Chart_GallerypanelHPP
