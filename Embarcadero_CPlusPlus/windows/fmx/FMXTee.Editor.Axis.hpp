// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Axis.pas' rev: 34.00 (Windows)

#ifndef Fmxtee_Editor_AxisHPP
#define Fmxtee_Editor_AxisHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.TabControl.hpp>
#include <FMXTee.Engine.hpp>
#include <FMXTee.Editor.CustomShape.hpp>
#include <FMXTee.Editor.Margins.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMXTee.Editor.Stroke.hpp>
#include <FMXTee.RadioGroup.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Axis
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAxisEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAxisEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TSplitter* Splitter1;
	Fmx::Tabcontrol::TTabControl* PageAxis;
	Fmx::Tabcontrol::TTabItem* TabScales;
	Fmx::Tabcontrol::TTabControl* PageScales;
	Fmx::Tabcontrol::TTabItem* TabOptions;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TCheckBox* CBAutomatic;
	Fmx::Stdctrls::TCheckBox* CBLogarithmic;
	Fmx::Stdctrls::TCheckBox* CBVisible;
	Fmx::Stdctrls::TCheckBox* CBInverted;
	Fmx::Edit::TEdit* ELogBase;
	Fmx::Stdctrls::TCheckBox* LogE;
	Fmx::Tabcontrol::TTabItem* TabSheet1;
	Fmx::Stdctrls::TLabel* Label4;
	Fmx::Stdctrls::TCheckBox* CBAutoMin;
	Fmx::Stdctrls::TButton* BAxisMin;
	Fmx::Spinbox::TSpinBox* UDMinOff;
	Fmx::Stdctrls::TCheckBox* CBMinRound;
	Fmx::Tabcontrol::TTabItem* TabSheet2;
	Fmx::Stdctrls::TLabel* Label5;
	Fmx::Stdctrls::TCheckBox* CBAutoMax;
	Fmx::Stdctrls::TButton* BAxisMax;
	Fmx::Spinbox::TSpinBox* UDMaxOff;
	Fmx::Stdctrls::TCheckBox* CBMaxRound;
	Fmx::Tabcontrol::TTabItem* TabSheet3;
	Fmx::Stdctrls::TLabel* L6;
	Fmx::Stdctrls::TButton* BIncre;
	Fmx::Stdctrls::TCheckBox* CBShowAll;
	Fmx::Tabcontrol::TTabItem* TabTitle;
	Fmx::Tabcontrol::TTabControl* PageTitle;
	Fmx::Tabcontrol::TTabItem* TabTitleStyle;
	Fmx::Stdctrls::TLabel* L14;
	Fmx::Stdctrls::TLabel* L3;
	Fmx::Stdctrls::TLabel* L9;
	Fmx::Edit::TEdit* ETitle;
	Fmx::Spinbox::TSpinBox* UDTitleSize;
	Fmx::Stdctrls::TCheckBox* CBTitleVisible;
	Fmx::Tabcontrol::TTabItem* TabLabels;
	Fmx::Tabcontrol::TTabControl* PageLabels;
	Fmx::Tabcontrol::TTabItem* TabLabStyle;
	Fmx::Stdctrls::TLabel* L26;
	Fmx::Stdctrls::TLabel* L23;
	Fmx::Stdctrls::TLabel* L20;
	Fmx::Stdctrls::TLabel* Label3;
	Fmx::Stdctrls::TCheckBox* CBLabels;
	Fmx::Stdctrls::TCheckBox* CBMultiline;
	Fmx::Stdctrls::TCheckBox* CBOnAxis;
	Fmx::Stdctrls::TCheckBox* CBRoundFirst;
	Fmx::Spinbox::TSpinBox* UDLabelsSize;
	Fmx::Spinbox::TSpinBox* UDSepar;
	Fmx::Listbox::TComboBox* CBLabelStyle;
	Fmx::Stdctrls::TCheckBox* CBAlternate;
	Fmx::Stdctrls::TCheckBox* CBLabelsBehind;
	Fmx::Tabcontrol::TTabItem* TabLabOptions;
	Fmx::Stdctrls::TLabel* LabelAxisFormat;
	Fmx::Comboedit::TComboEdit* CBFormat;
	Fmx::Stdctrls::TCheckBox* CBExpo;
	Fmx::Stdctrls::TCheckBox* CBLabelAlign;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Tabcontrol::TTabItem* TabTicks;
	Fmx::Tabcontrol::TTabItem* TabGrid;
	Fmx::Tabcontrol::TTabItem* TabPositions;
	Fmx::Stdctrls::TLabel* Label41;
	Fmx::Stdctrls::TLabel* Label42;
	Fmx::Stdctrls::TLabel* Label43;
	Fmx::Stdctrls::TLabel* LabelZ;
	Fmx::Stdctrls::TLabel* Label7;
	Fmx::Spinbox::TSpinBox* UDPos;
	Fmx::Spinbox::TSpinBox* UDStart;
	Fmx::Spinbox::TSpinBox* UDEnd;
	Fmx::Stdctrls::TCheckBox* CBOtherSide;
	Fmx::Stdctrls::TCheckBox* CBHorizAxis;
	Fmx::Spinbox::TSpinBox* UDZ;
	Fmx::Listbox::TComboBox* CBPosUnits;
	Fmx::Tabcontrol::TTabItem* TabItems;
	Fmx::Stdctrls::TSplitter* Splitter2;
	Fmx::Listbox::TListBox* ListItems;
	Fmx::Stdctrls::TPanel* PanelItems;
	Fmx::Stdctrls::TLabel* Label10;
	Fmx::Stdctrls::TLabel* Label11;
	Fmx::Edit::TEdit* EItemValue;
	Fmx::Stdctrls::TButton* ButtonFormat;
	Fmx::Memo::TMemo* AxisItemText;
	Fmx::Stdctrls::TPanel* Panel3;
	Fmx::Stdctrls::TCheckBox* CBItemsAuto;
	Fmx::Stdctrls::TPanel* Panel1;
	Fmx::Stdctrls::TPanel* PanelCustomAxes;
	Fmx::Stdctrls::TButton* BAdd;
	Fmx::Stdctrls::TButton* BDelete;
	Fmx::Stdctrls::TPanel* Panel4;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TCheckBox* CBShow;
	Fmx::Stdctrls::TCheckBox* CBAxisBeh;
	Fmx::Listbox::TListBox* LBAxes;
	Fmx::Edit::TEdit* EAxisMin;
	Fmx::Edit::TEdit* EAxisMax;
	Fmx::Edit::TEdit* EIncrement;
	Fmx::Stdctrls::TCheckBox* CBAutoInc;
	Fmx::Tabcontrol::TTabItem* TabTitleFormat;
	Fmx::Tabcontrol::TTabItem* TabLabFormat;
	Fmx::Tabcontrol::TTabItem* TabLabMargins;
	Fmx::Tabcontrol::TTabItem* TabLabBack;
	Fmx::Stdctrls::TLabel* Label12;
	Fmx::Listbox::TComboBox* CBLabelsPos;
	Fmx::Tabcontrol::TTabItem* TabAxis;
	Fmx::Tabcontrol::TTabControl* TabControlTicks;
	Fmx::Tabcontrol::TTabItem* TabOuter;
	Fmx::Tabcontrol::TTabItem* TabInner;
	Fmx::Tabcontrol::TTabItem* TabMinor;
	Fmx::Layouts::TLayout* Layout1;
	Fmx::Stdctrls::TLabel* L28;
	Fmx::Spinbox::TSpinBox* UDAxisTickLength;
	Fmx::Stdctrls::TCheckBox* CBTickOnLabels;
	Fmx::Layouts::TLayout* Layout2;
	Fmx::Stdctrls::TLabel* L29;
	Fmx::Spinbox::TSpinBox* UDInnerTicksLength;
	Fmx::Layouts::TLayout* Layout3;
	Fmx::Stdctrls::TLabel* L30;
	Fmx::Spinbox::TSpinBox* UDAxisMinorTickLen;
	Fmx::Stdctrls::TLabel* Label9;
	Fmx::Spinbox::TSpinBox* UDMinorC;
	Fmx::Tabcontrol::TTabControl* TabControlGrid;
	Fmx::Tabcontrol::TTabItem* TabGridBorder;
	Fmx::Tabcontrol::TTabItem* TabMinorGrid;
	Fmx::Layouts::TLayout* Layout4;
	Fmx::Layouts::TLayout* Layout5;
	Fmx::Stdctrls::TCheckBox* CBGridCentered;
	Fmx::Stdctrls::TLabel* Label6;
	Fmx::Spinbox::TSpinBox* UDGridZ;
	Fmx::Stdctrls::TLabel* Label8;
	Fmx::Spinbox::TSpinBox* UDEvery;
	Fmx::Stdctrls::TLabel* L31;
	Fmx::Spinbox::TSpinBox* UDMinorCount;
	Fmx::Combotrackbar::TComboTrackBar* CBAngle;
	Fmx::Combotrackbar::TComboTrackBar* CBTitleAngle;
	Fmxtee::Radiogroup::TRadioGroup* RGTitlePos;
	Fmx::Stdctrls::TRadioButton* RadioButton1;
	Fmx::Stdctrls::TRadioButton* RadioButton2;
	Fmx::Stdctrls::TRadioButton* RadioButton3;
	void __fastcall PageAxisChange(System::TObject* Sender);
	void __fastcall BAxisMinClick(System::TObject* Sender);
	void __fastcall BAxisMaxClick(System::TObject* Sender);
	void __fastcall BIncreClick(System::TObject* Sender);
	void __fastcall PageTitleChange(System::TObject* Sender);
	void __fastcall PageLabelsChange(System::TObject* Sender);
	void __fastcall CBFormatChange(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall CBPosUnitsChange(System::TObject* Sender);
	void __fastcall ButtonFormatClick(System::TObject* Sender);
	void __fastcall BAddClick(System::TObject* Sender);
	void __fastcall BDeleteClick(System::TObject* Sender);
	void __fastcall LBAxesChange(System::TObject* Sender);
	void __fastcall CBShowChange(System::TObject* Sender);
	void __fastcall CBAxisBehChange(System::TObject* Sender);
	void __fastcall CBAutomaticChange(System::TObject* Sender);
	void __fastcall CBVisibleChange(System::TObject* Sender);
	void __fastcall CBLogarithmicChange(System::TObject* Sender);
	void __fastcall CBInvertedChange(System::TObject* Sender);
	void __fastcall LogEChange(System::TObject* Sender);
	void __fastcall CBTitleVisibleChange(System::TObject* Sender);
	void __fastcall UDTitleSizeChangeTracking(System::TObject* Sender);
	void __fastcall CBAutoMinChange(System::TObject* Sender);
	void __fastcall UDMinOffChangeTracking(System::TObject* Sender);
	void __fastcall CBMinRoundChange(System::TObject* Sender);
	void __fastcall CBAutoMaxChange(System::TObject* Sender);
	void __fastcall UDMaxOffChangeTracking(System::TObject* Sender);
	void __fastcall CBMaxRoundChange(System::TObject* Sender);
	void __fastcall CBShowAllChange(System::TObject* Sender);
	void __fastcall CBLabelsChange(System::TObject* Sender);
	void __fastcall CBMultilineChange(System::TObject* Sender);
	void __fastcall CBRoundFirstChange(System::TObject* Sender);
	void __fastcall CBOnAxisChange(System::TObject* Sender);
	void __fastcall CBAlternateChange(System::TObject* Sender);
	void __fastcall CBLabelsBehindChange(System::TObject* Sender);
	void __fastcall CBLabelStyleChange(System::TObject* Sender);
	void __fastcall UDLabelsSizeChangeTracking(System::TObject* Sender);
	void __fastcall UDSeparChangeTracking(System::TObject* Sender);
	void __fastcall CBExpoChange(System::TObject* Sender);
	void __fastcall CBLabelAlignChange(System::TObject* Sender);
	void __fastcall CBTickOnLabelsChange(System::TObject* Sender);
	void __fastcall UDAxisTickLengthChangeTracking(System::TObject* Sender);
	void __fastcall UDInnerTicksLengthChangeTracking(System::TObject* Sender);
	void __fastcall UDAxisMinorTickLenChangeTracking(System::TObject* Sender);
	void __fastcall UDMinorCChangeTracking(System::TObject* Sender);
	void __fastcall CBGridCenteredChange(System::TObject* Sender);
	void __fastcall UDGridZChangeTracking(System::TObject* Sender);
	void __fastcall UDEveryChangeTracking(System::TObject* Sender);
	void __fastcall UDMinorCountChangeTracking(System::TObject* Sender);
	void __fastcall UDPosChangeTracking(System::TObject* Sender);
	void __fastcall UDStartChangeTracking(System::TObject* Sender);
	void __fastcall UDEndChangeTracking(System::TObject* Sender);
	void __fastcall CBOtherSideChange(System::TObject* Sender);
	void __fastcall CBHorizAxisChange(System::TObject* Sender);
	void __fastcall UDZChangeTracking(System::TObject* Sender);
	void __fastcall CBItemsAutoChange(System::TObject* Sender);
	void __fastcall AxisItemTextChangeTracking(System::TObject* Sender);
	void __fastcall ListItemsChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall ELogBaseTyping(System::TObject* Sender);
	void __fastcall EItemValueTyping(System::TObject* Sender);
	void __fastcall ETitleTyping(System::TObject* Sender);
	void __fastcall CBAutoIncChange(System::TObject* Sender);
	void __fastcall EIncrementChangeTracking(System::TObject* Sender);
	void __fastcall EAxisMaxChangeTracking(System::TObject* Sender);
	void __fastcall EAxisMinChangeTracking(System::TObject* Sender);
	void __fastcall CBLabelsPosChange(System::TObject* Sender);
	void __fastcall TabControlTicksChange(System::TObject* Sender);
	void __fastcall TabControlGridChange(System::TObject* Sender);
	void __fastcall CBAngleChangeTracking(System::TObject* Sender);
	void __fastcall CBAngleChange(System::TObject* Sender);
	void __fastcall CBTitleAngleChangeTracking(System::TObject* Sender);
	void __fastcall CBTitleAngleChange(System::TObject* Sender);
	void __fastcall RGTitlePosChange(System::TObject* Sender);
	
private:
	Fmxtee::Engine::TChartAxes* Axes;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* ILabelsFormat;
	Fmxtee::Editor::Margins::TMarginsEditor* ILabelsMargins;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* IBack;
	Fmxtee::Editor::Stroke::TStrokeEditor* IGrid;
	Fmxtee::Editor::Stroke::TStrokeEditor* IMinorGrid;
	Fmxtee::Editor::Stroke::TStrokeEditor* IOuter;
	Fmxtee::Editor::Stroke::TStrokeEditor* IInner;
	Fmxtee::Editor::Stroke::TStrokeEditor* IMinor;
	Fmxtee::Editor::Stroke::TStrokeEditor* IAxisEditor;
	Fmxtee::Editor::Customshape::TTeeShapeEditor* ITitleEditor;
	Fmxtee::Engine::TChartAxis* __fastcall Axis();
	void __fastcall EnableLogBaseControls();
	void __fastcall RefreshAxes(Fmxtee::Engine::TChartAxes* const AAxes);
	void __fastcall SetAxisIndex(Fmxtee::Engine::TChartAxis* const Axis);
	void __fastcall SetAxisScales();
	void __fastcall SetScaleEdit(const double Value, Fmx::Edit::TEdit* const AEdit);
	
public:
	__classmethod TAxisEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartAxes* const AAxes)/* overload */;
	__classmethod TAxisEditor* __fastcall CreateEditor(System::Classes::TComponent* const AOwner, Fmxtee::Engine::TChartAxis* const AAxis)/* overload */;
	void __fastcall RefreshAxis(Fmxtee::Engine::TChartAxis* const Axis);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAxisEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAxisEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAxisEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall FillAxesList(Fmxtee::Engine::TChartAxes* const Axes, Fmx::Listbox::TCustomListBox* const AList, bool AddDepth);
}	/* namespace Axis */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_AXIS)
using namespace Fmxtee::Editor::Axis;
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
#endif	// Fmxtee_Editor_AxisHPP
