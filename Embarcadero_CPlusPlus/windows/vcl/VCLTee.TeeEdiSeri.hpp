// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiSeri.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeediseriHPP
#define Vcltee_TeeediseriHPP

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
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Grids.hpp>
#include <VCLTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeCustomShapeEditor.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeSourceEdit.hpp>
#include <VCLTee.TeeChartGrid.hpp>
#include <VCLTee.TeeNavigator.hpp>
#include <VCLTee.TeeLisB.hpp>
#include <VCLTee.TeeMargins.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeeBackImage.hpp>
#include <VCLTee.TeeTextShapeEditor.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeediseri
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeSeries;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (*TOnCreateEditSeries)(TFormTeeSeries* Sender, Vcltee::Chart::TCustomChart* AChart);

typedef void __fastcall (__closure *TOnCreateEditSeriesObj)(TFormTeeSeries* Sender, Vcltee::Chart::TCustomChart* AChart);

typedef void __fastcall (__closure *TNotifyTeeEvent)(TFormTeeSeries* Sender, Vcltee::Teeprocs::TTeeEvent* Event);

class PASCALIMPLEMENTATION TFormTeeSeries : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TCheckBox* CBPersistent;
	Vcl::Comctrls::TPageControl* PageSeries;
	Vcl::Comctrls::TTabSheet* TheTabSheet;
	Vcl::Comctrls::TTabSheet* TabGeneral;
	Vcl::Comctrls::TTabSheet* TabMarks;
	Vcl::Comctrls::TTabSheet* TabDataSource;
	Vcl::Comctrls::TPageControl* PageControlMarks;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Stdctrls::TCheckBox* CBMarksVisible;
	Vcl::Stdctrls::TCheckBox* CBMarkClip;
	Vcl::Stdctrls::TLabel* L23;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* EMarksEvery;
	Vcl::Comctrls::TUpDown* UDEvery;
	Vcl::Stdctrls::TCheckBox* CBMultiLine;
	Vcltee::Tecanvas::TComboFlat* CBSeries;
	Vcl::Extctrls::TImage* ImageSeries;
	Vcl::Stdctrls::TLabel* LabelSeriesClass;
	Vcl::Extctrls::TPanel* PanelTop;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Extctrls::TPanel* PanTop;
	Vcltee::Tecanvas::TComboFlat* CBDataSourcestyle;
	Vcl::Stdctrls::TCheckBox* CBAllVisible;
	Vcl::Extctrls::TPaintBox* PaintBox1;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* NewDataButton;
	Vcl::Stdctrls::TButton* EditDataButton;
	Vcl::Stdctrls::TButton* DeleteDataButton;
	Vcltee::Teechartgrid::TChartGrid* ChartGrid1;
	Vcltee::Teechartgrid::TChartGridNavigator* ChartGridNavigator1;
	Vcl::Extctrls::TPanel* PanelRandomSource;
	Vcl::Extctrls::TPanel* PanelSeriesSource;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* ESamples;
	Vcl::Stdctrls::TCheckBox* CBSamplesDefault;
	Vcl::Stdctrls::TButton* BApplyRandom;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Extctrls::TTimer* Timer1;
	Vcl::Comctrls::TTabSheet* TabSymbol;
	Vcl::Stdctrls::TButton* Button3;
	Vcl::Stdctrls::TLabel* Label5;
	Vcltee::Tecanvas::TComboFlat* CBSeriesSource;
	Vcl::Stdctrls::TButton* BApplySource;
	Vcl::Stdctrls::TButton* BClearSource;
	Vcl::Comctrls::TTabSheet* TabMargins;
	Vcl::Stdctrls::TCheckBox* CBFontSeriesColor;
	Vcl::Stdctrls::TCheckBox* CBAutoPos;
	Vcl::Comctrls::TTabSheet* TabMarksText;
	Vcl::Comctrls::TTabSheet* TabMarksGallery;
	Vcltee::Teegallerypanel::TChartGalleryPanel* MarksGallery;
	Vcltee::Chart::TChart* ChartMarks;
	Vcltee::Series::TBarSeries* Series1;
	Vcltee::Series::TBarSeries* Series2;
	Vcltee::Series::TBarSeries* Series3;
	Vcltee::Series::TBarSeries* Series4;
	Vcltee::Series::TBarSeries* Series5;
	Vcltee::Series::TBarSeries* Series6;
	Vcltee::Series::TBarSeries* Series7;
	Vcltee::Series::TBarSeries* Series8;
	Vcltee::Series::TBarSeries* Series9;
	Vcl::Comctrls::TPageControl* PageArrows;
	Vcl::Comctrls::TTabSheet* TabSheet3;
	Vcl::Comctrls::TTabSheet* TabArrowBorder;
	Vcl::Comctrls::TTabSheet* TabArrowPointer;
	Vcl::Stdctrls::TLabel* L32;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Stdctrls::TLabel* Label12;
	Vcl::Stdctrls::TEdit* SEArrowLength;
	Vcl::Comctrls::TUpDown* UDArrowsLength;
	Vcl::Stdctrls::TEdit* EArrowDist;
	Vcl::Comctrls::TUpDown* UDArrowDist;
	Vcltee::Tecanvas::TComboFlat* CBHead;
	Vcl::Stdctrls::TEdit* Edit1;
	Vcl::Comctrls::TUpDown* UDHeadSize;
	Vcl::Comctrls::TPageControl* PageMarksItems;
	Vcl::Comctrls::TTabSheet* TabSheet4;
	Vcl::Comctrls::TTabSheet* TabMarksFormat;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel4;
	Vcl::Buttons::TSpeedButton* BAdd;
	Vcl::Buttons::TSpeedButton* BDelete;
	Vcltee::Tecanvas::TComboFlat* CBLayout;
	Vcl::Stdctrls::TListBox* LBChildren;
	Vcl::Stdctrls::TLabel* Label1;
	Vcltee::Tecanvas::TComboFlat* RGMarkStyle;
	Vcl::Stdctrls::TCheckBox* CBMarkChildVisible;
	Vcl::Stdctrls::TLabel* Label6;
	Vcltee::Tecanvas::TComboFlat* CBTextAlign;
	Vcl::Stdctrls::TCheckBox* CBOnTop;
	Vcl::Comctrls::TTrackBar* TBAngle;
	Vcl::Stdctrls::TLabel* LAngle;
	Vcl::Stdctrls::TCheckBox* CBSoftClip;
	Vcl::Stdctrls::TCheckBox* CBSeriesTransp;
	Vcl::Stdctrls::TCheckBox* CBTransparent;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Comctrls::TTabSheet* TabLegend;
	Vcl::Stdctrls::TGroupBox* GB5;
	Vcl::Stdctrls::TLabel* L27;
	Vcl::Stdctrls::TLabel* LDepth;
	Vcl::Buttons::TSpeedButton* SpeedButton1;
	Vcltee::Tecanvas::TComboFlat* CBCursor;
	Vcl::Stdctrls::TEdit* EDepth;
	Vcl::Comctrls::TUpDown* UDDepth;
	Vcl::Stdctrls::TCheckBox* CBDepth;
	Vcl::Stdctrls::TGroupBox* GB2;
	Vcl::Stdctrls::TLabel* L15;
	Vcl::Stdctrls::TLabel* L21;
	Vcl::Buttons::TSpeedButton* Button1;
	Vcl::Buttons::TSpeedButton* Button2;
	Vcl::Stdctrls::TEdit* EPercentFormat;
	Vcltee::Tecanvas::TComboFlat* CBFormat;
	Vcl::Stdctrls::TGroupBox* GBHorizAxis;
	Vcltee::Tecanvas::TComboFlat* CBHorizAxis;
	Vcl::Stdctrls::TCheckBox* CBXDateTime;
	Vcl::Stdctrls::TGroupBox* GBVertAxis;
	Vcltee::Tecanvas::TComboFlat* CBVertAxis;
	Vcl::Stdctrls::TCheckBox* CBYDateTime;
	Vcl::Stdctrls::TCheckBox* CBZDateTime;
	Vcl::Stdctrls::TCheckBox* CBShowInEditor;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcltee::Tecanvas::TComboFlat* CBSortBy;
	Vcltee::Tecanvas::TComboFlat* CBSortOrder;
	Vcl::Stdctrls::TButton* BVisual;
	Vcl::Stdctrls::TCheckBox* CBCaseSensitive;
	Vcl::Extctrls::TPanel* Panel5;
	Vcl::Stdctrls::TCheckBox* CBShowInLegend;
	Vcl::Stdctrls::TLabel* Label7;
	Vcl::Stdctrls::TEdit* ELegendText;
	Vcl::Comctrls::TTabSheet* TabHover;
	Vcl::Extctrls::TPanel* PanelDetail;
	Vcltee::Teechartgrid::TChartGrid* DetailGrid;
	Vcltee::Tecanvas::TComboFlat* CBAggregate;
	Vcl::Extctrls::TSplitter* Splitter2;
	Vcl::Extctrls::TPanel* PanelDetailTotal;
	Vcl::Stdctrls::TLabel* LabelDetail;
	Vcl::Stdctrls::TLabel* LabelDetailTotal;
	void __fastcall EPercentFormatChange(System::TObject* Sender);
	void __fastcall PageSeriesChange(System::TObject* Sender);
	void __fastcall CBSeriesChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall RGMarkStyleClick(System::TObject* Sender);
	void __fastcall CBPersistentClick(System::TObject* Sender);
	void __fastcall CBYDateTimeClick(System::TObject* Sender);
	void __fastcall CBXDateTimeClick(System::TObject* Sender);
	void __fastcall CBDataSourcestyleChange(System::TObject* Sender);
	void __fastcall CBCursorChange(System::TObject* Sender);
	void __fastcall SEArrowLengthChange(System::TObject* Sender);
	void __fastcall CBMarkClipClick(System::TObject* Sender);
	void __fastcall CBMarksVisibleClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBHorizAxisChange(System::TObject* Sender);
	void __fastcall CBVertAxisChange(System::TObject* Sender);
	void __fastcall EMarksEveryChange(System::TObject* Sender);
	void __fastcall CBMultiLineClick(System::TObject* Sender);
	void __fastcall CBSortOrderChange(System::TObject* Sender);
	void __fastcall CBFormatChange(System::TObject* Sender);
	void __fastcall PageSeriesChanging(System::TObject* Sender, bool &AllowChange);
	void __fastcall CBDepthClick(System::TObject* Sender);
	void __fastcall EDepthChange(System::TObject* Sender);
	void __fastcall FormCloseQuery(System::TObject* Sender, bool &CanClose);
	void __fastcall CBAllVisibleClick(System::TObject* Sender);
	void __fastcall PaintBox1Paint(System::TObject* Sender);
	void __fastcall PaintBox1Click(System::TObject* Sender);
	void __fastcall CBSamplesDefaultClick(System::TObject* Sender);
	void __fastcall ESamplesChange(System::TObject* Sender);
	void __fastcall BApplyRandomClick(System::TObject* Sender);
	void __fastcall EArrowDistChange(System::TObject* Sender);
	void __fastcall CBHeadChange(System::TObject* Sender);
	void __fastcall Edit1Change(System::TObject* Sender);
	void __fastcall ChartGrid1SetEditText(System::TObject* Sender, int ACol, int ARow, const System::UnicodeString Value);
	void __fastcall Timer1Timer(System::TObject* Sender);
	void __fastcall CBZDateTimeClick(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall CBShowInEditorClick(System::TObject* Sender);
	void __fastcall CBSeriesSourceChange(System::TObject* Sender);
	void __fastcall BApplySourceClick(System::TObject* Sender);
	void __fastcall BClearSourceClick(System::TObject* Sender);
	void __fastcall PageControlMarksChange(System::TObject* Sender);
	void __fastcall CBTextAlignChange(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall CBFontSeriesColorClick(System::TObject* Sender);
	void __fastcall CBSortByChange(System::TObject* Sender);
	void __fastcall BVisualClick(System::TObject* Sender);
	void __fastcall CBCaseSensitiveClick(System::TObject* Sender);
	void __fastcall CBAutoPosClick(System::TObject* Sender);
	void __fastcall MarksGalleryChangeChart(System::TObject* Sender);
	void __fastcall PageArrowsChange(System::TObject* Sender);
	void __fastcall PageMarksItemsChange(System::TObject* Sender);
	void __fastcall BAddClick(System::TObject* Sender);
	void __fastcall CBLayoutChange(System::TObject* Sender);
	void __fastcall BDeleteClick(System::TObject* Sender);
	void __fastcall LBChildrenClick(System::TObject* Sender);
	void __fastcall CBMarkChildVisibleClick(System::TObject* Sender);
	void __fastcall TBAngleChange(System::TObject* Sender);
	void __fastcall CBOnTopClick(System::TObject* Sender);
	void __fastcall CBSoftClipClick(System::TObject* Sender);
	void __fastcall CBSeriesTranspClick(System::TObject* Sender);
	void __fastcall CBTransparentClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBShowInLegendClick(System::TObject* Sender);
	void __fastcall ELegendTextChange(System::TObject* Sender);
	void __fastcall ChartGrid1Click(System::TObject* Sender);
	void __fastcall PanTopResize(System::TObject* Sender);
	void __fastcall CBAggregateChange(System::TObject* Sender);
	void __fastcall DetailGridClick(System::TObject* Sender);
	void __fastcall DetailGridSetEditText(System::TObject* Sender, int ACol, int ARow, const System::UnicodeString Value);
	
private:
	Vcltee::Teengine::TCustomAxisPanel* TheChart;
	bool CreatingForm;
	bool ChangingPage;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* IHover;
	Vcltee::Teebackimage::TBackImageEditor* ILegend;
	Vcltee::Teemargins::TMarginsEditor* IMarksMargins;
	Vcl::Forms::TForm* IMarksObject;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* IMarksSymbol;
	Vcltee::Teengine::TChartSeries* LastSeries;
	TNotifyTeeEvent FOnTeeEvent;
	bool IChangingMarks;
	void __fastcall AddChildItem(int Index);
	Vcl::Forms::TForm* __fastcall AddToTab(Vcl::Forms::TForm* AForm, Vcl::Comctrls::TTabSheet* ATab, System::Classes::TPersistent* AObject);
	bool __fastcall AllSeriesMarksVisible();
	bool __fastcall CanModifySeries();
	bool __fastcall CheckCanClose();
	void __fastcall CheckCBSamples();
	void __fastcall DestroyDataSourceForm();
	void __fastcall EnableMultiLine();
	void __fastcall FillAxis(System::Classes::TStrings* Items, bool Horizontal);
	Vcltee::Teengine::TChartValueList* __fastcall FindZList();
	void __fastcall SetTabDataSource();
	void __fastcall SetTabSeriesMarks();
	void __fastcall TeeEvent(Vcltee::Teeprocs::TTeeEvent* Event);
	
protected:
	void __fastcall CreateDataSourceForm();
	
public:
	Vcltee::Teengine::TChartSeries* TheSeries;
	bool IsDssGraph;
	bool ShowTabDataSource;
	bool ShowTabGeneral;
	bool ShowTabMarks;
	Vcltee::Teesourceedit::TBaseSourceEditor* DataSourceStyle;
	Vcltee::Teelisb::TChartListBox* TheListBox;
	void __fastcall DestroySeriesForms();
	void __fastcall FillAxes();
	__classmethod Vcl::Forms::TCustomForm* __fastcall InsertSeriesForm(Vcl::Controls::TControl* AParent, Vcl::Forms::TFormClass EditorClass, int Position, const System::UnicodeString EditorTabName, System::Classes::TPersistent* AnObject);
	__classmethod void __fastcall FillMarksStyle(System::Classes::TStrings* const AItems);
	__classmethod Vcltee::Teecustomshapeeditor::TFormTeeShape* __fastcall MarkSymbolsForm(System::Classes::TComponent* AOwner, Vcltee::Teengine::TSeriesMarksSymbol* Symbol, Vcl::Controls::TWinControl* AParent = (Vcl::Controls::TWinControl*)(0x0));
	void __fastcall SetCBSeries();
	__property TNotifyTeeEvent OnTeeEvent = {read=FOnTeeEvent, write=FOnTeeEvent};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeeSeries(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeSeries(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeSeries() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeSeries(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
private:
	void *__ITeeEventListener;	// Vcltee::Teeprocs::ITeeEventListener 
	
public:
	operator Vcltee::Teeprocs::ITeeEventListener*(void) { return (Vcltee::Teeprocs::ITeeEventListener*)&__ITeeEventListener; }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TOnCreateEditSeries InternalOnCreateEditSeries;
extern DELPHI_PACKAGE TOnCreateEditSeriesObj InternalOnCreateEditSeriesObj;
extern DELPHI_PACKAGE void __fastcall EditSeriesDialog(System::Classes::TComponent* AOwner, Vcltee::Teengine::TChartSeries* ASeries);
extern DELPHI_PACKAGE Vcl::Forms::TFormClass __fastcall SeriesEditorForm(Vcltee::Teengine::TChartSeries* Series);
}	/* namespace Teeediseri */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDISERI)
using namespace Vcltee::Teeediseri;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeediseriHPP
