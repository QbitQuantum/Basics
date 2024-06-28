// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.DBChart.pas' rev: 34.00 (Windows)

#ifndef Vcltee_DbchartHPP
#define Vcltee_DbchartHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.DateUtils.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Data.DB.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Dbchart
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS DBChartException;
class DELPHICLASS TListOfDataSources;
class DELPHICLASS TCustomDBChart;
class DELPHICLASS TDBChart;
class DELPHICLASS TDBChartDataSource;
class DELPHICLASS TTeeSeriesDBSource;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DBChartException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall DBChartException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall DBChartException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall DBChartException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall DBChartException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall DBChartException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall DBChartException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall DBChartException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall DBChartException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall DBChartException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall DBChartException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall DBChartException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall DBChartException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~DBChartException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TTeeDBGroup : unsigned char { dgHour, dgDay, dgWeek, dgWeekDay, dgMonth, dgQuarter, dgYear, dgNone };

class PASCALIMPLEMENTATION TListOfDataSources : public System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>
{
	typedef System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*> inherited;
	
public:
	Data::Db::TDataSource* operator[](int Index) { return this->DataSource[Index]; }
	
private:
	void __fastcall Put(int Index, Data::Db::TDataSource* const Value);
	Data::Db::TDataSource* __fastcall Get(int Index);
	
public:
	HIDESBASE int __fastcall IndexOf(Data::Db::TDataSet* const ADataSet);
	__property Data::Db::TDataSource* DataSource[int Index] = {read=Get, write=Put/*, default*/};
public:
	/* {System_Generics_Collections}TObjectList<Data_DB_TDataSource>.Create */ inline __fastcall TListOfDataSources()/* overload */ : System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>() { }
	/* {System_Generics_Collections}TObjectList<Data_DB_TDataSource>.Create */ inline __fastcall TListOfDataSources(bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>(AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<Data_DB_TDataSource>.Create */ inline __fastcall TListOfDataSources(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<Data::Db::TDataSource*> > AComparer, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>(AComparer, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<Data_DB_TDataSource>.Create */ inline __fastcall TListOfDataSources(System::Generics::Collections::TEnumerable__1<Data::Db::TDataSource*>* const Collection, bool AOwnsObjects)/* overload */ : System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>(Collection, AOwnsObjects) { }
	/* {System_Generics_Collections}TObjectList<Data_DB_TDataSource>.Destroy */ inline __fastcall virtual ~TListOfDataSources() { }
	
public:
	/* {System_Generics_Collections}TList<Data_DB_TDataSource>.Create */ inline __fastcall TListOfDataSources(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<Data::Db::TDataSource*> > AComparer)/* overload */ : System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>(AComparer) { }
	/* {System_Generics_Collections}TList<Data_DB_TDataSource>.Create */ inline __fastcall TListOfDataSources(System::Generics::Collections::TEnumerable__1<Data::Db::TDataSource*>* const Collection)/* overload */ : System::Generics::Collections::TObjectList__1<Data::Db::TDataSource*>(Collection) { }
	
};


typedef void __fastcall (__closure *TProcessRecordEvent)(TCustomDBChart* Sender, Data::Db::TDataSet* DataSet);

class PASCALIMPLEMENTATION TCustomDBChart : public Vcltee::Chart::TCustomChart
{
	typedef Vcltee::Chart::TCustomChart inherited;
	
private:
	bool FAutoRefresh;
	int FRefreshInterval;
	bool FShowGlassCursor;
	TProcessRecordEvent FOnProcessRecord;
	bool IUpdating;
	Vcl::Extctrls::TTimer* ITimer;
	TListOfDataSources* IDataSources;
	void __fastcall DataSourceCheckDataSet(Data::Db::TDataSet* const ADataSet);
	void __fastcall DataSourceCloseDataSet(Data::Db::TDataSet* const ADataSet);
	void __fastcall CheckDataSet(Data::Db::TDataSet* const ADataSet, Vcltee::Teengine::TChartSeries* const ASeries = (Vcltee::Teengine::TChartSeries*)(0x0));
	void __fastcall CheckNewDataSource(Data::Db::TDataSet* const ADataSet, bool SingleRow);
	void __fastcall SetRefreshInterval(int Value);
	void __fastcall CheckTimer();
	void __fastcall OnRefreshTimer(System::TObject* Sender);
	
protected:
	Data::Db::TDataSource* __fastcall CreateDataSource(System::Classes::TComponent* const AOwner, Data::Db::TDataSet* const ADataSet, bool SingleRow);
	DYNAMIC void __fastcall RemovedDataSource(Vcltee::Teengine::TChartSeries* ASeries, System::Classes::TComponent* AComponent);
	
public:
	__fastcall virtual TCustomDBChart(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDBChart();
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall CheckDatasource(Vcltee::Teengine::TChartSeries* ASeries);
	DYNAMIC bool __fastcall IsValidDataSource(Vcltee::Teengine::TChartSeries* ASeries, System::Classes::TComponent* AComponent);
	DYNAMIC void __fastcall FillValueSourceItems(Vcltee::Teengine::TChartValueList* AValueList, System::Classes::TGetStrProc Proc);
	DYNAMIC void __fastcall FillSeriesSourceItems(Vcltee::Teengine::TChartSeries* ASeries, System::Classes::TGetStrProc Proc);
	void __fastcall RefreshDataSet(Data::Db::TDataSet* const ADataSet, Vcltee::Teengine::TChartSeries* const ASeries);
	void __fastcall RefreshData();
	__property bool AutoRefresh = {read=FAutoRefresh, write=FAutoRefresh, default=1};
	__property int RefreshInterval = {read=FRefreshInterval, write=SetRefreshInterval, default=0};
	__property bool ShowGlassCursor = {read=FShowGlassCursor, write=FShowGlassCursor, default=1};
	__property TProcessRecordEvent OnProcessRecord = {read=FOnProcessRecord, write=FOnProcessRecord};
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomDBChart(HWND ParentWindow) : Vcltee::Chart::TCustomChart(ParentWindow) { }
	
};


class PASCALIMPLEMENTATION TDBChart : public TCustomDBChart
{
	typedef TCustomDBChart inherited;
	
__published:
	__property AutoRefresh = {default=1};
	__property RefreshInterval = {default=0};
	__property ShowGlassCursor = {default=1};
	__property OnProcessRecord;
	__property AllowPanning = {default=3};
	__property BackImage;
	__property BackImageInside = {default=0};
	__property BackImageMode = {default=0};
	__property BackImageTransp = {default=0};
	__property BackWall;
	__property Border;
	__property BorderRound = {default=0};
	__property BottomWall;
	__property Foot;
	__property Gradient;
	__property LeftWall;
	__property MarginBottom = {index=3, default=4};
	__property MarginLeft = {index=0, default=3};
	__property MarginRight = {index=2, default=3};
	__property MarginTop = {index=1, default=4};
	__property MarginUnits = {default=0};
	__property PrintProportional = {default=1};
	__property RightWall;
	__property ScrollMouseButton = {default=1};
	__property SubFoot;
	__property SubTitle;
	__property Title;
	__property OnAllowScroll;
	__property OnClickAxis;
	__property OnClickBackground;
	__property OnClickLegend;
	__property OnClickSeries;
	__property OnClickTitle;
	__property OnGetLegendPos;
	__property OnGetLegendRect;
	__property OnScroll;
	__property OnUndoZoom;
	__property OnZoom;
	__property Animations;
	__property AxisBehind = {default=1};
	__property AxisVisible = {default=1};
	__property BottomAxis;
	__property Chart3DPercent = {default=15};
	__property ClipPoints = {default=1};
	__property CustomAxes;
	__property DepthAxis;
	__property DepthTopAxis;
	__property Emboss;
	__property Frame;
	__property Hover;
	__property LeftAxis;
	__property Legend;
	__property Monochrome = {default=0};
	__property Pages;
	__property Panning;
	__property RightAxis;
	__property SeriesGroups;
	__property SeriesList;
	__property Shadow;
	__property Tools;
	__property TopAxis;
	__property View3D = {default=1};
	__property View3DOptions;
	__property View3DWalls = {default=1};
	__property Zoom;
	__property ZoomWheel = {default=2};
	__property OnAddSeries;
	__property OnAfterDraw;
	__property OnBeforeDrawAxes;
	__property OnBeforeDrawChart;
	__property OnBeforeDrawSeries;
	__property OnBeforePrint;
	__property OnGetAxisLabel;
	__property OnGetLegendText;
	__property OnGetNextAxisLabel;
	__property OnPageChange;
	__property OnRemoveSeries;
	__property OnValidDataSource;
	__property Align = {default=0};
	__property BevelInner = {default=0};
	__property BevelOuter = {default=2};
	__property BevelWidth = {default=1};
	__property BorderWidth = {default=0};
	__property Color = {default=-16777201};
	__property DragCursor = {default=-12};
	__property DragMode = {default=0};
	__property Enabled = {default=1};
	__property ParentColor = {default=0};
	__property ParentShowHint = {default=1};
	__property PopupMenu;
	__property TabStop = {default=1};
	__property ShowHint;
	__property TabOrder = {default=-1};
	__property Touch;
	__property Visible = {default=1};
	__property Anchors = {default=3};
	__property AutoSize = {default=0};
	__property Constraints;
	__property DragKind = {default=0};
	__property Locked = {default=0};
	__property OnClick;
	__property OnDblClick;
	__property OnDragDrop;
	__property OnDragOver;
	__property OnContextPopup;
	__property OnEndDrag;
	__property OnStartDrag;
	__property OnEnter;
	__property OnExit;
	__property OnKeyPress;
	__property OnMouseWheelDown;
	__property OnMouseWheelUp;
	__property OnKeyDown;
	__property OnKeyUp;
	__property OnMouseDown;
	__property OnMouseMove;
	__property OnMouseUp;
	__property OnMouseWheel;
	__property OnResize;
	__property OnCanResize;
	__property OnConstrainedResize;
	__property OnDockDrop;
	__property OnDockOver;
	__property OnEndDock;
	__property OnGesture;
	__property OnGetSiteInfo;
	__property OnStartDock;
	__property OnUnDock;
	__property OnMouseEnter;
	__property OnMouseLeave;
public:
	/* TCustomDBChart.Create */ inline __fastcall virtual TDBChart(System::Classes::TComponent* AOwner) : TCustomDBChart(AOwner) { }
	/* TCustomDBChart.Destroy */ inline __fastcall virtual ~TDBChart() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDBChart(HWND ParentWindow) : TCustomDBChart(ParentWindow) { }
	
};


typedef void __fastcall (*TTeeOnGetFieldType)(const Data::Db::TFieldType AType, Vcltee::Teengine::TTeeFieldType &TeeType);

typedef void __fastcall (__closure *TCheckDataSetEvent)(Data::Db::TDataSet* const DataSet);

class PASCALIMPLEMENTATION TDBChartDataSource : public Data::Db::TDataSource
{
	typedef Data::Db::TDataSource inherited;
	
private:
	TCustomDBChart* FDBChart;
	bool FWasActive;
	void __fastcall DataSourceRowChange(System::TObject* Sender, Data::Db::TField* Field);
	void __fastcall DataSourceStateChange(System::TObject* Sender);
	void __fastcall DataSourceUpdateData(System::TObject* Sender);
	
protected:
	TCheckDataSetEvent OnCheckDataSet;
	TCheckDataSetEvent OnCloseDataSet;
	HIDESBASE void __fastcall SetDataSet(Data::Db::TDataSet* const Value, bool SingleRow = false);
public:
	/* TDataSource.Create */ inline __fastcall virtual TDBChartDataSource(System::Classes::TComponent* AOwner) : Data::Db::TDataSource(AOwner) { }
	/* TDataSource.Destroy */ inline __fastcall virtual ~TDBChartDataSource() { }
	
};


class PASCALIMPLEMENTATION TTeeSeriesDBSource : public Vcltee::Teengine::TTeeSeriesSource
{
	typedef Vcltee::Teengine::TTeeSeriesSource inherited;
	
public:
	__classmethod virtual bool __fastcall Available(Vcltee::Teengine::TCustomAxisPanel* AChart);
	__classmethod virtual bool __fastcall HasNew();
public:
	/* TTeeSeriesSource.Create */ inline __fastcall virtual TTeeSeriesDBSource(System::Classes::TComponent* AOwner) : Vcltee::Teengine::TTeeSeriesSource(AOwner) { }
	/* TTeeSeriesSource.Destroy */ inline __fastcall virtual ~TTeeSeriesDBSource() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TTeeOnGetFieldType TeeOnGetFieldType;
extern DELPHI_PACKAGE void __fastcall FillDataSetFields(Data::Db::TDataSet* const DataSet, const System::Classes::TGetStrProc Proc);
extern DELPHI_PACKAGE int __fastcall DateToWeek(System::TDateTime ADate, System::Word &Year);
extern DELPHI_PACKAGE int __fastcall DateToWeekOld(const System::TDateTime ADate, System::Word &Year);
extern DELPHI_PACKAGE Vcltee::Teengine::TTeeFieldType __fastcall TeeFieldType(Data::Db::TFieldType AType);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeGetDBPart(int Num, System::UnicodeString St);
extern DELPHI_PACKAGE TTeeDBGroup __fastcall StrToDBGroup(System::UnicodeString St);
extern DELPHI_PACKAGE Vcltee::Teengine::TChartListOrder __fastcall StrToDBOrder(System::UnicodeString St);
}	/* namespace Dbchart */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_DBCHART)
using namespace Vcltee::Dbchart;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_DbchartHPP
