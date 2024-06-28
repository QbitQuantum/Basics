// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiPage.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedipageHPP
#define Vcltee_TeeedipageHPP

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
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeNavigator.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeEdiGene.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedipage
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeePage;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeePage : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TLabel* L17;
	Vcl::Stdctrls::TEdit* SEPointsPerPage;
	Vcl::Stdctrls::TCheckBox* CBScaleLast;
	Vcl::Stdctrls::TLabel* LabelPages;
	Vcl::Comctrls::TUpDown* UDPointsPerPage;
	Vcl::Stdctrls::TCheckBox* CBPageLegend;
	Vcltee::Teeedigene::TChartPageNavigator* ChartPageNavigator1;
	Vcl::Stdctrls::TCheckBox* CBPageNum;
	Vcl::Stdctrls::TCheckBox* CBAutoScale;
	Vcl::Stdctrls::TCheckBox* CBNoPages;
	Vcl::Stdctrls::TButton* BEditTool;
	void __fastcall SEPointsPerPageChange(System::TObject* Sender);
	void __fastcall CBScaleLastClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBPageLegendClick(System::TObject* Sender);
	void __fastcall CBPageNumClick(System::TObject* Sender);
	void __fastcall ChartPageNavigator1ButtonClicked(Vcltee::Teenavigator::TTeeNavigateBtn Index);
	void __fastcall CBAutoScaleClick(System::TObject* Sender);
	void __fastcall CBNoPagesClick(System::TObject* Sender);
	void __fastcall BEditToolClick(System::TObject* Sender);
	
private:
	Vcltee::Chart::TCustomChart* __fastcall Chart();
	Vcltee::Teengine::TTeeCustomTool* __fastcall PageNumTool(bool CreateTool);
	void __fastcall SetEditTool();
	void __fastcall SetNoPages();
	
public:
	__fastcall TFormTeePage(System::Classes::TComponent* Owner, Vcltee::Chart::TCustomChart* AChart);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeePage(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeePage(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeePage() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeePage(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeedipage */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIPAGE)
using namespace Vcltee::Teeedipage;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedipageHPP
