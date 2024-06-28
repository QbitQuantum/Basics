// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Series.pas' rev: 34.00 (Android)

#ifndef Fmxtee_Editor_SeriesHPP
#define Fmxtee_Editor_SeriesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.UIConsts.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Objects.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Editor.CustomShape.hpp>
#include <FMXTee.Editor.Source.hpp>
#include <FMXTee.Editor.Series.Pointer.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.Editor.Picture.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Layouts.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Series
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSeriesEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Tabcontrol::TTabControl* PageSeries;
	Fmx::Tabcontrol::TTabItem* TheTabSheet;
	Fmx::Tabcontrol::TTabItem* TabGeneral;
	Fmx::Stdctrls::TGroupBox* GB5;
	Fmx::Stdctrls::TLabel* L27;
	Fmx::Stdctrls::TLabel* LDepth;
	Fmx::Listbox::TComboBox* CBCursor;
	Fmx::Spinbox::TSpinBox* UDDepth;
	Fmx::Stdctrls::TCheckBox* CBDepth;
	Fmx::Stdctrls::TGroupBox* GB2;
	Fmx::Stdctrls::TLabel* L15;
	Fmx::Stdctrls::TLabel* L21;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Edit::TEdit* EPercentFormat;
	Fmx::Stdctrls::TGroupBox* GBHorizAxis;
	Fmx::Listbox::TComboBox* CBHorizAxis;
	Fmx::Stdctrls::TCheckBox* CBXDateTime;
	Fmx::Stdctrls::TGroupBox* GBVertAxis;
	Fmx::Listbox::TComboBox* CBVertAxis;
	Fmx::Stdctrls::TCheckBox* CBYDateTime;
	Fmx::Stdctrls::TCheckBox* CBZDateTime;
	Fmx::Stdctrls::TCheckBox* CBShowInEditor;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Listbox::TComboBox* CBSortBy;
	Fmx::Listbox::TComboBox* CBSortOrder;
	Fmx::Stdctrls::TButton* BVisual;
	Fmx::Tabcontrol::TTabItem* TabMarks;
	Fmx::Tabcontrol::TTabControl* PageControlMarks;
	Fmx::Tabcontrol::TTabItem* TabSheet1;
	Fmx::Stdctrls::TLabel* L23;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Stdctrls::TCheckBox* CBMarksVisible;
	Fmx::Stdctrls::TCheckBox* CBMarkClip;
	Fmx::Spinbox::TSpinBox* UDMarksAngle;
	Fmx::Spinbox::TSpinBox* UDEvery;
	Fmx::Stdctrls::TCheckBox* CBMultiLine;
	Fmx::Stdctrls::TCheckBox* CBAllVisible;
	Fmx::Listbox::TComboBox* RGMarkStyle;
	Fmx::Listbox::TComboBox* CBTextAlign;
	Fmx::Stdctrls::TCheckBox* CBFontSeriesColor;
	Fmx::Tabcontrol::TTabItem* TabSheet2;
	Fmx::Tabcontrol::TTabItem* TabSymbol;
	Fmx::Tabcontrol::TTabItem* TabMargins;
	Fmx::Tabcontrol::TTabItem* TabDataSource;
	Fmx::Stdctrls::TPanel* PanelRandomSource;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Edit::TEdit* ESamples;
	Fmx::Stdctrls::TCheckBox* CBSamplesDefault;
	Fmx::Stdctrls::TButton* BApplyRandom;
	Fmx::Stdctrls::TButton* Button3;
	Fmx::Stdctrls::TPanel* PanelFunctions;
	Fmx::Stdctrls::TPanel* PanTop;
	Fmx::Listbox::TComboBox* CBDataSourcestyle;
	Fmx::Stdctrls::TButton* NewDataButton;
	Fmx::Stdctrls::TButton* EditDataButton;
	Fmx::Stdctrls::TButton* DeleteDataButton;
	Fmx::Stdctrls::TPanel* PanelSeriesSource;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Listbox::TComboBox* CBSeriesSource;
	Fmx::Stdctrls::TButton* BApplySource;
	Fmx::Stdctrls::TButton* BClearSource;
	Fmx::Stdctrls::TCheckBox* CBPersistent;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Objects::TImage* ImageSeries;
	Fmx::Stdctrls::TLabel* LabelSeriesClass;
	Fmx::Objects::TPaintBox* PaintBox1;
	Fmx::Listbox::TComboBox* CBSeries;
	Fmx::Comboedit::TComboEdit* CBFormat;
	Fmx::Effects::TGlowEffect* GlowEffect1;
	Fmx::Listbox::TListBoxItem* LBFunctions;
	Fmx::Stdctrls::TPanel* PanelManual;
	Fmx::Tabcontrol::TTabItem* TabMarksFormat;
	Fmx::Listbox::TListBoxItem* LBSeriesSource;
	Fmx::Tabcontrol::TTabControl* PageArrows;
	Fmx::Tabcontrol::TTabItem* TabArrowOptions;
	Fmx::Tabcontrol::TTabItem* TabArrowBorder;
	Fmx::Tabcontrol::TTabItem* TabArrowPointer;
	Fmx::Stdctrls::TLabel* Label11;
	Fmx::Listbox::TComboBox* CBHead;
	Fmx::Listbox::TListBoxItem* ListBoxItem27;
	Fmx::Listbox::TListBoxItem* ListBoxItem28;
	Fmx::Listbox::TListBoxItem* ListBoxItem29;
	Fmx::Stdctrls::TLabel* Label12;
	Fmx::Spinbox::TSpinBox* UDHeadSize;
	Fmx::Stdctrls::TLabel* L32;
	Fmx::Spinbox::TSpinBox* UDArrowsLength;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Spinbox::TSpinBox* UDArrowDist;
	Fmx::Stdctrls::TCheckBox* CBOnTop;
	Fmx::Listbox::TListBoxItem* ListBoxItem32;
	Fmx::Listbox::TListBoxItem* ListBoxItem33;
	Fmx::Tabcontrol::TTabControl* TabControl1;
	Fmx::Tabcontrol::TTabItem* TabGenOptions;
	Fmx::Tabcontrol::TTabItem* TabGenLegend;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TCheckBox* CBShowInLegend;
	Fmx::Stdctrls::TLabel* Label7;
	Fmx::Edit::TEdit* ELegendTitle;
	Fmx::Tabcontrol::TTabItem* TabHover;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBCursorChange(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall CBHorizAxisChange(System::TObject* Sender);
	void __fastcall CBVertAxisChange(System::TObject* Sender);
	void __fastcall CBSortByChange(System::TObject* Sender);
	void __fastcall CBSortOrderChange(System::TObject* Sender);
	void __fastcall BVisualClick(System::TObject* Sender);
	void __fastcall PageControlMarksChange(System::TObject* Sender);
	void __fastcall RGMarkStyleClick(System::TObject* Sender);
	void __fastcall CBTextAlignChange(System::TObject* Sender);
	void __fastcall CBHeadChange(System::TObject* Sender);
	void __fastcall BApplyRandomClick(System::TObject* Sender);
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall ChartGrid1SetEditText();
	void __fastcall CBDataSourcestyleChange(System::TObject* Sender);
	void __fastcall CBSeriesSourceChange(System::TObject* Sender);
	void __fastcall BApplySourceClick(System::TObject* Sender);
	void __fastcall BClearSourceClick(System::TObject* Sender);
	void __fastcall PaintBox1Click(System::TObject* Sender);
	void __fastcall CBSeriesChange(System::TObject* Sender);
	void __fastcall CBPersistentChange(System::TObject* Sender);
	void __fastcall CBMarksVisibleChange(System::TObject* Sender);
	void __fastcall UDEveryChangeTracking(System::TObject* Sender);
	void __fastcall CBMarkClipChange(System::TObject* Sender);
	void __fastcall CBMultiLineChange(System::TObject* Sender);
	void __fastcall CBFontSeriesColorChange(System::TObject* Sender);
	void __fastcall UDMarksAngleChangeTracking(System::TObject* Sender);
	void __fastcall UDDepthChangeTracking(System::TObject* Sender);
	void __fastcall CBXDateTimeChange(System::TObject* Sender);
	void __fastcall CBYDateTimeChange(System::TObject* Sender);
	void __fastcall CBShowInLegendChange(System::TObject* Sender);
	void __fastcall CBShowInEditorChange(System::TObject* Sender);
	void __fastcall CBSamplesDefaultChange(System::TObject* Sender);
	void __fastcall CBDepthChange(System::TObject* Sender);
	void __fastcall PaintBox1Paint(System::TObject* Sender, Fmx::Graphics::TCanvas* const Canvas);
	void __fastcall UDArrowsLengthChangeTracking(System::TObject* Sender);
	void __fastcall UDArrowDistChangeTracking(System::TObject* Sender);
	void __fastcall UDHeadSizeChangeTracking(System::TObject* Sender);
	void __fastcall CBZDateTimeChange(System::TObject* Sender);
	void __fastcall CBAllVisibleChange(System::TObject* Sender);
	void __fastcall CBFormatChangeTracking(System::TObject* Sender);
	void __fastcall ELegendTitleTyping(System::TObject* Sender);
	void __fastcall EPercentFormatTyping(System::TObject* Sender);
	void __fastcall ESamplesTyping(System::TObject* Sender);
	void __fastcall PageArrowsChange(System::TObject* Sender);
	void __fastcall CBOnTopChange(System::TObject* Sender);
	void __fastcall TabControl1Change(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TChartSeries* Series;
	bool ChangingSeries;
	Fmxtee::Editor::Source::TBaseSourceEditor* DataSourceStyle;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* IMarks;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* IMarksSymbol;
	Fmx::Forms::TForm* FMarginsEditor;
	Fmxtee::Engine::TChartSeries* LastSeries;
	Fmx::Forms::TCustomForm* LastSeriesForm;
	Fmxtee::Editor::Stroke::TStrokeEditor* IArrowBorder;
	Fmxtee::Editor::Series::Pointer::TSeriesPointerEditor* IArrowPointer;
	Fmxtee::Editor::Picture::TBackImageEditor* ILegend;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* IHover;
	void __fastcall CheckCBSamples();
	void __fastcall CreateDataSourceForm();
	void __fastcall DestroyDataSourceForm();
	Fmxtee::Engine::TChartValueList* __fastcall FindZList();
	__classmethod Fmxtee::Editor::Customshape::TTeeShapeEditor* __fastcall MarkSymbolsForm(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TSeriesMarksSymbol* const Symbol);
	void __fastcall RefreshSeries(Fmxtee::Engine::TChartSeries* const ASeries);
	
public:
	__classmethod TSeriesEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartSeries* const ASeries);
	__classmethod void __fastcall Edit(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartSeries* const ASeries);
	__classmethod void __fastcall EditMarks(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TSeriesMarks* const AMarks);
	Fmx::Forms::TCommonCustomForm* __fastcall Embedd(Fmx::Forms::TForm* const AForm, const System::UnicodeString ATitle = System::UnicodeString());
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSeriesEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSeriesEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSeriesEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Series */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_SERIES)
using namespace Fmxtee::Editor::Series;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR)
using namespace Fmxtee::Editor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Editor_SeriesHPP
