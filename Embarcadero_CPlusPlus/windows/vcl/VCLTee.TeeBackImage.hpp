// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeBackImage.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeebackimageHPP
#define Vcltee_TeebackimageHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeFiltersEditor.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teebackimage
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBackImageEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBackImageEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Comctrls::TTabSheet* TabFilters;
	Vcl::Comctrls::TTabSheet* TabGallery;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Extctrls::TImage* Image1;
	Vcl::Stdctrls::TLabel* LabelSize;
	Vcl::Stdctrls::TLabel* LabelExt;
	Vcl::Stdctrls::TButton* BBrowse;
	Vcl::Stdctrls::TCheckBox* CBTransp;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Stdctrls::TButton* Button3;
	Vcl::Comctrls::TTabSheet* TabBounds;
	Vcl::Stdctrls::TGroupBox* GBPosition;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* ELeft;
	Vcl::Comctrls::TUpDown* UDLeft;
	Vcl::Stdctrls::TEdit* ETop;
	Vcl::Comctrls::TUpDown* UDTop;
	Vcl::Extctrls::TRadioGroup* RGBitmap;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* ERight;
	Vcl::Comctrls::TUpDown* UDRight;
	Vcl::Stdctrls::TEdit* EBottom;
	Vcl::Comctrls::TUpDown* UDBottom;
	Vcl::Stdctrls::TLabel* LQuality;
	Vcltee::Tecanvas::TComboFlat* CBQuality;
	Vcl::Stdctrls::TLabel* LabelFileSize;
	void __fastcall RGBitmapClick(System::TObject* Sender);
	void __fastcall BBrowseClick(System::TObject* Sender);
	void __fastcall CBTranspClick(System::TObject* Sender);
	void __fastcall ELeftChange(System::TObject* Sender);
	void __fastcall ETopChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall ERightChange(System::TObject* Sender);
	void __fastcall EBottomChange(System::TObject* Sender);
	void __fastcall CBQualityChange(System::TObject* Sender);
	void __fastcall PageControl1GetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	
private:
	Vcltee::Tecanvas::TTeePicture* Image;
	Vcltee::Teefilterseditor::TFiltersEditor* IFilters;
	void __fastcall EnableImageControls();
	void __fastcall FiltersChanged(System::TObject* Sender);
	void __fastcall SetBrowseCaption();
	void __fastcall TextureChanged(System::TObject* Sender);
	
public:
	__classmethod TBackImageEditor* __fastcall InsertForm(Vcl::Controls::TWinControl* const AParent, Vcltee::Tecanvas::TTeePicture* const APicture);
	void __fastcall RefreshControls(Vcltee::Tecanvas::TTeePicture* const AImage);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBackImageEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBackImageEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBackImageEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBackImageEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall EditTeePicture(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TTeePicture* const APicture);
}	/* namespace Teebackimage */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEBACKIMAGE)
using namespace Vcltee::Teebackimage;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeebackimageHPP
