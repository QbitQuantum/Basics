// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFilterGallery.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeefiltergalleryHPP
#define Vcltee_TeefiltergalleryHPP

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
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>
#include <VCLTee.TeeFilters.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teefiltergallery
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFilterGallery;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFilterGallery : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcltee::Teegallerypanel::TChartGalleryPanel* ChartGalleryPanel1;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* BOK;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Extctrls::TImage* SampleImage;
	void __fastcall ChartGalleryPanel1SelectedChart(System::TObject* Sender);
	void __fastcall BOKClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall ChartGalleryPanel1ChangeChart(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	
private:
	Vcl::Graphics::TPicture* ISample;
	Vcl::Graphics::TGraphic* Sample;
	Vcltee::Tecanvas::TFilterClass SelectedFilter;
	void __fastcall AddItems();
	Vcltee::Teegallerypanel::TChartGalleryPanel* __fastcall CurrentGallery();
	
public:
	__classmethod Vcltee::Tecanvas::TFilterClass __fastcall Choose(System::Classes::TComponent* AOwner, Vcl::Graphics::TGraphic* const ASample = (Vcl::Graphics::TGraphic*)(0x0));
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFilterGallery(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFilterGallery(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFilterGallery() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFilterGallery(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teefiltergallery */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFILTERGALLERY)
using namespace Vcltee::Teefiltergallery;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeefiltergalleryHPP
