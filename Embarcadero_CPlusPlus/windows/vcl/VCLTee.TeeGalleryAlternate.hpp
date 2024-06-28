// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeGalleryAlternate.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeegalleryalternateHPP
#define Vcltee_TeegalleryalternateHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.TeeLisB.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teegalleryalternate
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeGalleryForm;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeGalleryForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcltee::Teegallerypanel::TChartGalleryPanel* ChartGalleryPanel1;
	Vcltee::Teelisb::TChartListBox* ChartListBox1;
	Vcl::Extctrls::TSplitter* Splitter1;
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Tecanvas::TComboFlat* CBPage;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TCheckBox* CB3D;
	Vcl::Stdctrls::TCheckBox* CBSmooth;
	Vcl::Extctrls::TPanel* PanelBottom;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* BOK;
	Vcl::Stdctrls::TButton* BCancel;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall ChartListBox1Click(System::TObject* Sender);
	void __fastcall CBPageChange(System::TObject* Sender);
	void __fastcall CB3DClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBSmoothClick(System::TObject* Sender);
	void __fastcall ChartGalleryPanel1SelectedChart(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	
private:
	Vcltee::Chart::TChart* Chart;
	Vcltee::Teengine::TChartSeriesClass OldClass;
	void __fastcall CreateChartList(const System::UnicodeString APage);
	void __fastcall CreateGallery(Vcltee::Teengine::TChartSeriesClass AClass);
	void __fastcall FillGalleryPages(System::Classes::TStrings* const AItems);
	
public:
	int IGalleryWidth;
	int IGalleryHeight;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeGalleryForm(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeGalleryForm(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeGalleryForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeGalleryForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teegalleryalternate */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEGALLERYALTERNATE)
using namespace Vcltee::Teegalleryalternate;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeegalleryalternateHPP
