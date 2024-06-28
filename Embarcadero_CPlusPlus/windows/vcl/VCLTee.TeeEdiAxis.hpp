// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiAxis.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeediaxisHPP
#define Vcltee_TeeediaxisHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeEdiFont.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeCustomShapeEditor.hpp>
#include <VCLTee.TeeMargins.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeediaxis
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeAxis;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeeAxis : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageAxis;
	Vcl::Comctrls::TTabSheet* TabScales;
	Vcl::Comctrls::TTabSheet* TabTitle;
	Vcl::Comctrls::TTabSheet* TabLabels;
	Vcl::Comctrls::TTabSheet* TabTicks;
	Vcl::Comctrls::TTabSheet* TabPositions;
	Vcl::Stdctrls::TLabel* Label41;
	Vcl::Stdctrls::TLabel* Label42;
	Vcl::Stdctrls::TLabel* Label43;
	Vcl::Stdctrls::TEdit* EPos;
	Vcl::Stdctrls::TEdit* EStart;
	Vcl::Stdctrls::TEdit* EEnd;
	Vcl::Comctrls::TUpDown* UDPos;
	Vcl::Comctrls::TUpDown* UDStart;
	Vcl::Comctrls::TUpDown* UDEnd;
	Vcl::Comctrls::TTabSheet* TabGrids;
	Vcl::Stdctrls::TCheckBox* CBOtherSide;
	Vcl::Stdctrls::TCheckBox* CBHorizAxis;
	Vcl::Comctrls::TPageControl* PageTitle;
	Vcl::Comctrls::TTabSheet* TabTitleStyle;
	Vcl::Stdctrls::TLabel* L14;
	Vcl::Stdctrls::TEdit* ETitle;
	Vcl::Stdctrls::TLabel* L3;
	Vcl::Stdctrls::TEdit* SETitleAngle;
	Vcl::Comctrls::TUpDown* UDTitleAngle;
	Vcl::Stdctrls::TLabel* L9;
	Vcl::Stdctrls::TEdit* SETitleSize;
	Vcl::Comctrls::TUpDown* UDTitleSize;
	Vcl::Stdctrls::TCheckBox* CBTitleVisible;
	Vcl::Comctrls::TPageControl* PageLabels;
	Vcl::Comctrls::TTabSheet* TabLabStyle;
	Vcl::Stdctrls::TCheckBox* CBLabels;
	Vcl::Stdctrls::TCheckBox* CBMultiline;
	Vcl::Stdctrls::TCheckBox* CBOnAxis;
	Vcl::Stdctrls::TCheckBox* CBRoundFirst;
	Vcl::Stdctrls::TEdit* SELabelsSize;
	Vcl::Stdctrls::TLabel* L26;
	Vcl::Stdctrls::TLabel* L23;
	Vcl::Stdctrls::TEdit* SELabelsAngle;
	Vcl::Comctrls::TUpDown* UDLabelsAngle;
	Vcl::Comctrls::TUpDown* UDLabelsSize;
	Vcl::Stdctrls::TLabel* L20;
	Vcl::Stdctrls::TEdit* SESepar;
	Vcl::Comctrls::TUpDown* UDSepar;
	Vcl::Comctrls::TTabSheet* TabLabelsFormat;
	Vcl::Extctrls::TPanel* PanelAxes;
	Vcl::Comctrls::TTabSheet* TabLabFormat;
	Vcl::Stdctrls::TLabel* LabelAxisFormat;
	Vcltee::Tecanvas::TComboFlat* CBFormat;
	Vcl::Stdctrls::TCheckBox* CBExpo;
	Vcl::Stdctrls::TCheckBox* CBLabelAlign;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Buttons::TSpeedButton* BAdd;
	Vcl::Buttons::TSpeedButton* BDelete;
	Vcl::Extctrls::TPanel* Panel4;
	Vcl::Stdctrls::TCheckBox* CBShow;
	Vcl::Stdctrls::TCheckBox* CBAxisBeh;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TListBox* LBAxes;
	Vcl::Stdctrls::TLabel* LabelZ;
	Vcl::Stdctrls::TEdit* Edit1;
	Vcl::Comctrls::TUpDown* UDZ;
	Vcl::Comctrls::TPageControl* PageScales;
	Vcl::Comctrls::TTabSheet* TabMin;
	Vcl::Comctrls::TTabSheet* TabMax;
	Vcl::Stdctrls::TCheckBox* CBAutoMax;
	Vcl::Stdctrls::TButton* BAxisMax;
	Vcl::Stdctrls::TCheckBox* CBAutoMin;
	Vcl::Stdctrls::TButton* BAxisMin;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* EMinOff;
	Vcl::Comctrls::TUpDown* UDMinOff;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* EMaxOff;
	Vcl::Comctrls::TUpDown* UDMaxOff;
	Vcl::Stdctrls::TLabel* Label7;
	Vcltee::Tecanvas::TComboFlat* CBPosUnits;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBLabelStyle;
	Vcl::Stdctrls::TCheckBox* CBAlternate;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Comctrls::TTabSheet* TabIncrement;
	Vcl::Stdctrls::TButton* BIncre;
	Vcl::Stdctrls::TLabel* L6;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Stdctrls::TCheckBox* CBAutomatic;
	Vcl::Stdctrls::TCheckBox* CBLogarithmic;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcl::Stdctrls::TCheckBox* CBInverted;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* ELogBase;
	Vcl::Stdctrls::TCheckBox* LogE;
	Vcl::Stdctrls::TCheckBox* CBShowAll;
	Vcl::Stdctrls::TCheckBox* CBMinRound;
	Vcl::Stdctrls::TCheckBox* CBMaxRound;
	Vcl::Comctrls::TTabSheet* TabTitleFormat;
	Vcl::Comctrls::TPageControl* PageTitleFormat;
	Vcl::Stdctrls::TCheckBox* CBLabelsBehind;
	Vcl::Comctrls::TTabSheet* TabItems;
	Vcl::Stdctrls::TListBox* ListItems;
	Vcl::Extctrls::TPanel* PanelItems;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TCheckBox* CBItemsAuto;
	Vcl::Extctrls::TSplitter* Splitter2;
	Vcl::Comctrls::TPageControl* PageControl2;
	Vcl::Comctrls::TTabSheet* TabGridBorder;
	Vcl::Comctrls::TTabSheet* TabGridMinor;
	Vcl::Extctrls::TPanel* Panel5;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TLabel* Label8;
	Vcl::Stdctrls::TEdit* Edit2;
	Vcl::Comctrls::TUpDown* UDGridZ;
	Vcl::Stdctrls::TCheckBox* CBGridCentered;
	Vcl::Stdctrls::TEdit* EMarksEvery;
	Vcl::Comctrls::TUpDown* UDEvery;
	Vcl::Extctrls::TPanel* Panel6;
	Vcl::Stdctrls::TLabel* L31;
	Vcl::Stdctrls::TEdit* SEMinorCount;
	Vcl::Comctrls::TUpDown* UDMinorCount;
	Vcl::Stdctrls::TCheckBox* CBAutoInc;
	Vcl::Comctrls::TTabSheet* TabAxisBorder;
	Vcl::Comctrls::TPageControl* PageTicks;
	Vcl::Comctrls::TTabSheet* TabOuter;
	Vcl::Comctrls::TTabSheet* TabInner;
	Vcl::Comctrls::TTabSheet* TabMinor;
	Vcl::Extctrls::TPanel* Panel7;
	Vcl::Stdctrls::TLabel* L28;
	Vcl::Stdctrls::TEdit* SEAxisTickLength;
	Vcl::Stdctrls::TCheckBox* CBTickOnLabels;
	Vcl::Comctrls::TUpDown* UDAxisTickLength;
	Vcl::Extctrls::TPanel* Panel8;
	Vcl::Stdctrls::TLabel* Label12;
	Vcl::Stdctrls::TEdit* Edit4;
	Vcl::Comctrls::TUpDown* UDInnerTicksLength;
	Vcl::Extctrls::TPanel* Panel9;
	Vcl::Stdctrls::TLabel* L30;
	Vcl::Stdctrls::TLabel* Label9;
	Vcl::Stdctrls::TEdit* SEAxisMinorTickLen;
	Vcl::Comctrls::TUpDown* UDAxisMinorTickLen;
	Vcl::Stdctrls::TEdit* Edit3;
	Vcl::Comctrls::TUpDown* UDMinorC;
	Vcl::Stdctrls::TEdit* EIncrement;
	Vcl::Stdctrls::TEdit* EAxisMin;
	Vcl::Stdctrls::TEdit* EAxisMax;
	Vcl::Extctrls::TPanel* Panel10;
	Vcl::Stdctrls::TLabel* Label10;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Stdctrls::TEdit* EItemValue;
	Vcl::Stdctrls::TMemo* AxisItemText;
	Vcl::Comctrls::TTabSheet* TabMargins;
	Vcl::Comctrls::TTabSheet* TabBack;
	Vcl::Stdctrls::TLabel* Label13;
	Vcltee::Tecanvas::TComboFlat* CBLabelsPos;
	Vcl::Extctrls::TRadioGroup* RGTitlePos;
	Vcl::Stdctrls::TCheckBox* CBGridAlways;
	Vcl::Stdctrls::TLabel* Label14;
	Vcltee::Tecanvas::TComboFlat* CBTitleFormat;
	Vcl::Buttons::TSpeedButton* SBAddItem;
	Vcl::Buttons::TSpeedButton* SBDeleteItem;
	Vcl::Stdctrls::TLabel* LInvalidValue;
	Vcl::Stdctrls::TListBox* LBSubAxis;
	Vcl::Extctrls::TSplitter* Splitter3;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Buttons::TSpeedButton* BAddSub;
	Vcl::Buttons::TSpeedButton* BDeleteSub;
	Vcl::Extctrls::TPanel* MainPanel;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall SEAxisTickLengthChange(System::TObject* Sender);
	void __fastcall CBAutomaticClick(System::TObject* Sender);
	void __fastcall ETitleChange(System::TObject* Sender);
	void __fastcall BAxisMaxClick(System::TObject* Sender);
	void __fastcall BAxisMinClick(System::TObject* Sender);
	void __fastcall BIncreClick(System::TObject* Sender);
	void __fastcall CBLogarithmicClick(System::TObject* Sender);
	void __fastcall SEAxisMinorTickLenChange(System::TObject* Sender);
	void __fastcall SEMinorCountChange(System::TObject* Sender);
	void __fastcall CBAutoMaxClick(System::TObject* Sender);
	void __fastcall CBInvertedClick(System::TObject* Sender);
	void __fastcall SETitleAngleChange(System::TObject* Sender);
	void __fastcall SETitleSizeChange(System::TObject* Sender);
	void __fastcall CBLabelsClick(System::TObject* Sender);
	void __fastcall SELabelsAngleChange(System::TObject* Sender);
	void __fastcall RGLabelStyleClick(System::TObject* Sender);
	void __fastcall SELabelsSizeChange(System::TObject* Sender);
	void __fastcall CBOnAxisClick(System::TObject* Sender);
	void __fastcall SESeparChange(System::TObject* Sender);
	void __fastcall CBRoundFirstClick(System::TObject* Sender);
	void __fastcall CBTickOnLabelsClick(System::TObject* Sender);
	void __fastcall CBGridCenteredClick(System::TObject* Sender);
	void __fastcall CBMultilineClick(System::TObject* Sender);
	void __fastcall PageAxisChange(System::TObject* Sender);
	void __fastcall CBShowClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall PageAxisChanging(System::TObject* Sender, bool &AllowChange);
	void __fastcall EPosChange(System::TObject* Sender);
	void __fastcall EStartChange(System::TObject* Sender);
	void __fastcall EEndChange(System::TObject* Sender);
	void __fastcall LBAxesClick(System::TObject* Sender);
	void __fastcall BAddClick(System::TObject* Sender);
	void __fastcall CBOtherSideClick(System::TObject* Sender);
	void __fastcall BDeleteClick(System::TObject* Sender);
	void __fastcall CBHorizAxisClick(System::TObject* Sender);
	void __fastcall ELogBaseChange(System::TObject* Sender);
	void __fastcall CBTitleVisibleClick(System::TObject* Sender);
	void __fastcall CBFormatChange(System::TObject* Sender);
	void __fastcall CBExpoClick(System::TObject* Sender);
	void __fastcall CBAxisBehClick(System::TObject* Sender);
	void __fastcall CBLabelAlignClick(System::TObject* Sender);
	void __fastcall Edit1Change(System::TObject* Sender);
	void __fastcall EMinOffChange(System::TObject* Sender);
	void __fastcall EMaxOffChange(System::TObject* Sender);
	void __fastcall LogEClick(System::TObject* Sender);
	void __fastcall Edit2Change(System::TObject* Sender);
	void __fastcall CBPosUnitsChange(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBAlternateClick(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall EMarksEveryChange(System::TObject* Sender);
	void __fastcall CBShowAllClick(System::TObject* Sender);
	void __fastcall CBMinRoundClick(System::TObject* Sender);
	void __fastcall CBMaxRoundClick(System::TObject* Sender);
	void __fastcall Edit3Change(System::TObject* Sender);
	void __fastcall PageTitleFormatChange(System::TObject* Sender);
	void __fastcall PageLabelsChange(System::TObject* Sender);
	void __fastcall PageTitleChange(System::TObject* Sender);
	void __fastcall CBLabelsBehindClick(System::TObject* Sender);
	void __fastcall ListItemsClick(System::TObject* Sender);
	void __fastcall EItemValueChange(System::TObject* Sender);
	void __fastcall CBItemsAutoClick(System::TObject* Sender);
	void __fastcall AxisItemTextChange(System::TObject* Sender);
	void __fastcall CBAutoIncClick(System::TObject* Sender);
	void __fastcall Edit4Change(System::TObject* Sender);
	void __fastcall PageTicksChange(System::TObject* Sender);
	void __fastcall EIncrementChange(System::TObject* Sender);
	void __fastcall EAxisMinChange(System::TObject* Sender);
	void __fastcall EAxisMaxChange(System::TObject* Sender);
	void __fastcall CBLabelsPosChange(System::TObject* Sender);
	void __fastcall RGTitlePosClick(System::TObject* Sender);
	void __fastcall CBGridAlwaysClick(System::TObject* Sender);
	void __fastcall CBTitleFormatChange(System::TObject* Sender);
	void __fastcall SBAddItemClick(System::TObject* Sender);
	void __fastcall SBDeleteItemClick(System::TObject* Sender);
	void __fastcall BDeleteSubClick(System::TObject* Sender);
	void __fastcall LBSubAxisClick(System::TObject* Sender);
	void __fastcall BAddSubClick(System::TObject* Sender);
	void __fastcall PageAxisGetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	
private:
	bool CreatingForm;
	bool IChangingItems;
	bool IChangingAuto;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* ILabelsFormat;
	Vcltee::Teemargins::TMarginsEditor* ILabelsMargins;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* IBack;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* ITitleEditor;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* IItemsFormat;
	Vcltee::Teependlg::TPenDialog* IAxisEditor;
	Vcltee::Teependlg::TPenDialog* IOuterEditor;
	Vcltee::Teependlg::TPenDialog* IInnerEditor;
	Vcltee::Teependlg::TPenDialog* IMinorEditor;
	Vcltee::Teependlg::TPenDialog* IGridEditor;
	Vcltee::Teependlg::TPenDialog* IMinorGridEditor;
	void __fastcall AddAxisItem(int Index);
	void __fastcall AddAxisItems();
	void __fastcall AddSubAxes();
	void __fastcall EditAxisMaxMin(const System::UnicodeString ATitle, Vcl::Stdctrls::TCheckBox* const ACheckBox, bool IsMax);
	void __fastcall EnableLogBaseControls();
	Vcltee::Teengine::TChartAxis* __fastcall SelectedMainAxis();
	void __fastcall SetAxisIndex();
	void __fastcall SetAxisScales();
	void __fastcall SetScaleEdit(const double Value, Vcl::Stdctrls::TEdit* const AEdit);
	
public:
	Vcltee::Teengine::TChartAxis* TheAxis;
	System::Classes::TNotifyEvent NotifyCustom;
	__fastcall TFormTeeAxis(System::Classes::TComponent* const AOwner, Vcltee::Teengine::TChartAxis* const AAxis);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeeAxis(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeAxis(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeAxis() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeAxis(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall TeeAddAxes(Vcltee::Teengine::TCustomAxisPanel* const AChart, System::Classes::TStrings* const AList, bool AddDepth);
}	/* namespace Teeediaxis */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIAXIS)
using namespace Vcltee::Teeediaxis;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeediaxisHPP
