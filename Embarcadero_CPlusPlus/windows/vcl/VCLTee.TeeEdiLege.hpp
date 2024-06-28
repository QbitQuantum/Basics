// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiLege.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedilegeHPP
#define Vcltee_TeeedilegeHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeTextShapeEditor.hpp>
#include <VCLTee.TeeCustomShapeEditor.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeEdiGrad.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedilege
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeLegend;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeeLegend : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Stdctrls::TLabel* L12;
	Vcl::Stdctrls::TLabel* L7;
	Vcl::Stdctrls::TCheckBox* CBShow;
	Vcl::Stdctrls::TCheckBox* CBInverted;
	Vcltee::Tecanvas::TComboFlat* CBLegendStyle;
	Vcltee::Tecanvas::TComboFlat* CBLegStyle;
	Vcl::Comctrls::TTabSheet* TabSymbol;
	Vcl::Comctrls::TTabSheet* TabSheet3;
	Vcl::Stdctrls::TCheckBox* CBResizeChart;
	Vcl::Stdctrls::TLabel* L10;
	Vcl::Stdctrls::TEdit* SETopPos;
	Vcl::Comctrls::TUpDown* UDTopPos;
	Vcl::Stdctrls::TLabel* L1;
	Vcl::Stdctrls::TEdit* SEMargin;
	Vcl::Comctrls::TUpDown* UDMargin;
	Vcl::Extctrls::TRadioGroup* RGPosition;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* ECustLeft;
	Vcl::Comctrls::TUpDown* UDLeft;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* ECustTop;
	Vcl::Comctrls::TUpDown* UDTop;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* EVertSpacing;
	Vcl::Comctrls::TUpDown* UDVertSpacing;
	Vcl::Stdctrls::TCheckBox* CBCustPos;
	Vcl::Stdctrls::TCheckBox* CBFontColor;
	Vcltee::Tecanvas::TComboFlat* CBCheckBoxes;
	Vcl::Comctrls::TTabSheet* TabTitle;
	Vcl::Stdctrls::TCheckBox* CBPosPercent;
	Vcl::Comctrls::TTabSheet* TabItems;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TCheckBox* CBCustom;
	Vcl::Stdctrls::TCheckBox* CBCustPosition;
	Vcl::Stdctrls::TListBox* LBItems;
	Vcl::Buttons::TSpeedButton* SBAddItem;
	Vcl::Buttons::TSpeedButton* SBDeleteItem;
	Vcl::Extctrls::TPanel* PanelItem;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* EItemText;
	Vcl::Stdctrls::TEdit* EItemText2;
	Vcl::Stdctrls::TLabel* Label8;
	Vcltee::Tecanvas::TComboFlat* CBItemAlign;
	Vcl::Stdctrls::TLabel* Label9;
	Vcl::Stdctrls::TEdit* EItemX;
	Vcl::Stdctrls::TEdit* EItemY;
	Vcl::Stdctrls::TLabel* Label10;
	Vcl::Comctrls::TUpDown* UDItemLeft;
	Vcl::Comctrls::TUpDown* UDItemTop;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Stdctrls::TCheckBox* CBDefItemFont;
	Vcl::Stdctrls::TLabel* Label11;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcl::Stdctrls::TCheckBox* CBBehind;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Comctrls::TTrackBar* TBTextGap;
	Vcl::Comctrls::TTabSheet* TabLines;
	Vcl::Stdctrls::TLabel* Label7;
	Vcltee::Tecanvas::TComboFlat* CBJustify;
	void __fastcall SEMarginChange(System::TObject* Sender);
	void __fastcall CBLegendStyleChange(System::TObject* Sender);
	void __fastcall SETopPosChange(System::TObject* Sender);
	void __fastcall CBLegStyleChange(System::TObject* Sender);
	void __fastcall CBShowClick(System::TObject* Sender);
	void __fastcall CBResizeChartClick(System::TObject* Sender);
	void __fastcall CBInvertedClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall EVertSpacingChange(System::TObject* Sender);
	void __fastcall RGPositionClick(System::TObject* Sender);
	void __fastcall ECustLeftChange(System::TObject* Sender);
	void __fastcall ECustTopChange(System::TObject* Sender);
	void __fastcall CBCustPosClick(System::TObject* Sender);
	void __fastcall CBFontColorClick(System::TObject* Sender);
	void __fastcall CBCheckBoxesChange(System::TObject* Sender);
	void __fastcall CBPosPercentClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBCustomClick(System::TObject* Sender);
	void __fastcall CBCustPositionClick(System::TObject* Sender);
	void __fastcall LBItemsClick(System::TObject* Sender);
	void __fastcall EItemTextChange(System::TObject* Sender);
	void __fastcall CBItemAlignChange(System::TObject* Sender);
	void __fastcall EItemXChange(System::TObject* Sender);
	void __fastcall EItemYChange(System::TObject* Sender);
	void __fastcall EItemText2Change(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall CBDefItemFontClick(System::TObject* Sender);
	void __fastcall SBAddItemClick(System::TObject* Sender);
	void __fastcall SBDeleteItemClick(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBBehindClick(System::TObject* Sender);
	void __fastcall TBTextGapChange(System::TObject* Sender);
	void __fastcall CBJustifyChange(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Chart::TChartLegend* FLegend;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* ITeeObject;
	Vcltee::Teetextshapeeditor::TTextShapeEditor* ITitleObject;
	Vcltee::Teependlg::TPenDialog* ILinesObject;
	void __fastcall AddItem(int Index);
	bool __fastcall CanChangePos();
	void __fastcall EnableCustItemPos();
	void __fastcall EnableCustomItems();
	void __fastcall EnableCustomPosition();
	void __fastcall EnableMarginControls();
	Vcltee::Chart::TLegendItem* __fastcall LegendItem();
	void __fastcall SetItems();
	void __fastcall SetLeftTop();
	void __fastcall SetLegend(Vcltee::Chart::TChartLegend* const Value);
	
public:
	__fastcall virtual TFormTeeLegend(System::Classes::TComponent* Owner);
	__fastcall TFormTeeLegend(System::Classes::TComponent* const Owner, Vcltee::Chart::TChartLegend* const ALegend);
	__property Vcltee::Chart::TChartLegend* Legend = {read=FLegend, write=SetLegend};
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeLegend(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeLegend() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeLegend(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeedilege */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDILEGE)
using namespace Vcltee::Teeedilege;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedilegeHPP
