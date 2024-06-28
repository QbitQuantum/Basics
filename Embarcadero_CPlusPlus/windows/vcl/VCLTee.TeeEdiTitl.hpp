// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiTitl.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedititlHPP
#define Vcltee_TeeedititlHPP

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
#include <VCLTee.TeeTextShapeEditor.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedititl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeeTitle;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeeTitle : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControlTitle;
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Tecanvas::TComboFlat* CBTitles;
	Vcl::Comctrls::TTabSheet* TabPosition;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* ECustLeft;
	Vcl::Comctrls::TUpDown* UDLeft;
	Vcl::Stdctrls::TEdit* ECustTop;
	Vcl::Comctrls::TUpDown* UDTop;
	Vcl::Stdctrls::TCheckBox* CBCustPos;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* EMargin;
	Vcl::Comctrls::TUpDown* UDMargin;
	Vcl::Stdctrls::TCheckBox* CBAdjust;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBAdjustClick(System::TObject* Sender);
	void __fastcall CBTitlesChange(System::TObject* Sender);
	void __fastcall CBCustPosClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall ECustLeftChange(System::TObject* Sender);
	void __fastcall ECustTopChange(System::TObject* Sender);
	void __fastcall EMarginChange(System::TObject* Sender);
	void __fastcall PageControlTitleChange(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Chart::TCustomChart* TheChart;
	Vcltee::Teetextshapeeditor::TTextShapeEditor* ITeeObject;
	bool __fastcall CanChangeCust();
	void __fastcall EnableCustomPosition();
	void __fastcall SetTitleControls();
	
public:
	Vcltee::Chart::TChartTitle* TheTitle;
	__fastcall TFormTeeTitle(System::Classes::TComponent* Owner, Vcltee::Chart::TCustomChart* AChart, Vcltee::Chart::TChartTitle* ATitle);
	Vcl::Stdctrls::TMemo* __fastcall MemoText();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeeTitle(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeeTitle(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeeTitle() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeeTitle(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeedititl */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDITITL)
using namespace Vcltee::Teeedititl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedititlHPP
