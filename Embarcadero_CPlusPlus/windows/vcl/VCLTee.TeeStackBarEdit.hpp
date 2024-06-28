// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeStackBarEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeestackbareditHPP
#define Vcltee_TeestackbareditHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teestackbaredit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStackBarSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStackBarSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Tecanvas::TComboFlat* CBMultiBar;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TCheckBox* CBYOrigin;
	Vcl::Stdctrls::TEdit* EYOrigin;
	Vcl::Stdctrls::TEdit* EGroup;
	Vcl::Comctrls::TUpDown* UDGroup;
	Vcltee::Teegallerypanel::TChartGalleryPanel* MultiBarGallery;
	Vcl::Extctrls::TTimer* Timer1;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBYOriginClick(System::TObject* Sender);
	void __fastcall EYOriginChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall EGroupChange(System::TObject* Sender);
	void __fastcall CBMultiBarChange(System::TObject* Sender);
	void __fastcall MultiBarGalleryChangeChart(System::TObject* Sender);
	void __fastcall Timer1Timer(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Series::TCustomBarSeries* Bar;
	void __fastcall CreateGallery();
	void __fastcall EnableGroup();
	void __fastcall SelectGallery();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TStackBarSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TStackBarSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TStackBarSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TStackBarSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teestackbaredit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESTACKBAREDIT)
using namespace Vcltee::Teestackbaredit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeestackbareditHPP
