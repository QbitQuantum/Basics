// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeShapeEdi.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeshapeediHPP
#define Vcltee_TeeshapeediHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeShape.hpp>
#include <VCLTee.TeeEdiFont.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeEdiGrad.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeshapeedi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TChartShapeEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TChartShapeEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* LX1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* LY1;
	Vcl::Stdctrls::TEdit* SEX0;
	Vcl::Stdctrls::TEdit* SEX1;
	Vcl::Stdctrls::TEdit* SEY0;
	Vcl::Stdctrls::TEdit* SEY1;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBStyle;
	Vcltee::Tecanvas::TButtonColor* BShapeColor;
	Vcl::Stdctrls::TCheckBox* CBTrans;
	Vcl::Stdctrls::TLabel* Label4;
	Vcltee::Tecanvas::TComboFlat* CBUnits;
	Vcl::Comctrls::TTabSheet* TabFont;
	Vcl::Stdctrls::TCheckBox* CBRound;
	Vcl::Comctrls::TTabSheet* TabSheet3;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TMemo* MemoText;
	Vcl::Extctrls::TRadioGroup* RGVertAlign;
	Vcl::Extctrls::TRadioGroup* RGAlign;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* LTransp;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall SEX0Change(System::TObject* Sender);
	void __fastcall SEY0Change(System::TObject* Sender);
	void __fastcall SEX1Change(System::TObject* Sender);
	void __fastcall SEY1Change(System::TObject* Sender);
	void __fastcall MemoTextChange(System::TObject* Sender);
	void __fastcall RGAlignClick(System::TObject* Sender);
	void __fastcall CBTransClick(System::TObject* Sender);
	void __fastcall CBStyleChange(System::TObject* Sender);
	void __fastcall CBUnitsChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBRoundClick(System::TObject* Sender);
	void __fastcall RGVertAlignClick(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Teeshape::TChartShape* TheSeries;
	void __fastcall EnableRound();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TChartShapeEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TChartShapeEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TChartShapeEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TChartShapeEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeshapeedi */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESHAPEEDI)
using namespace Vcltee::Teeshapeedi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeshapeediHPP
