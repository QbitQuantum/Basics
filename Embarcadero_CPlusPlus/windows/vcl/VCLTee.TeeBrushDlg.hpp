// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeBrushDlg.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeebrushdlgHPP
#define Vcltee_TeebrushdlgHPP

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
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeGalleryPanel.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teebrushdlg
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBrushDialog;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBrushDialog : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelOk;
	Vcl::Extctrls::TImage* ImageMetal;
	Vcl::Extctrls::TImage* ImageWood;
	Vcl::Extctrls::TImage* ImageStone;
	Vcl::Extctrls::TImage* ImageClouds;
	Vcl::Extctrls::TImage* ImageGrass;
	Vcl::Extctrls::TImage* ImageFire;
	Vcl::Extctrls::TImage* ImageSnow;
	Vcltee::Tecanvas::TButtonColor* BColor;
	Vcl::Stdctrls::TCheckBox* CBClear;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSolid;
	Vcl::Comctrls::TTabSheet* TabGradient;
	Vcl::Comctrls::TTabSheet* TabHatch;
	Vcl::Comctrls::TTabSheet* TabTexture;
	Vcl::Comctrls::TTabSheet* TabCustom;
	Vcl::Stdctrls::TLabel* LImage;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Extctrls::TImage* Image1;
	Vcltee::Teegallerypanel::TChartGalleryPanel* TextureGallery;
	Vcl::Extctrls::TImage* ImageCarbon;
	Vcltee::Teegallerypanel::TChartGalleryPanel* HatchGallery;
	Vcl::Extctrls::TPanel* Panel1;
	Vcltee::Tecanvas::TButtonColor* BColor2;
	Vcltee::Tecanvas::TButtonColor* BBackColor;
	Vcl::Stdctrls::TButton* Button4;
	Vcl::Stdctrls::TCheckBox* CBTransp;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Stdctrls::TButton* Button3;
	Vcl::Extctrls::TImage* ImageCarbon2;
	Vcl::Extctrls::TImage* ImagePaper;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Stdctrls::TCheckBox* CBDefColor;
	Vcl::Extctrls::TImage* ImageMe;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBTranspClick(System::TObject* Sender);
	void __fastcall BBackColorClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall BSwapClick(System::TObject* Sender);
	void __fastcall BColorClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall HatchGalleryChangeChart(System::TObject* Sender);
	void __fastcall TextureGalleryChangeChart(System::TObject* Sender);
	void __fastcall PageControl1GetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	void __fastcall TextureGallerySelectedChart(System::TObject* Sender);
	void __fastcall CBClearClick(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBDefColorClick(System::TObject* Sender);
	
private:
	Vcltee::Teeprocs::TColorEvent FLinkedColor;
	Vcltee::Tecanvas::TTeeBrush* BackupBrush;
	Vcltee::Teeedigrad::TTeeGradientEditor* FGradientEditor;
	void __fastcall CheckImageButton();
	Vcl::Extctrls::TImage* __fastcall GetInternalTexture(int Index);
	void __fastcall PrepareDefColor();
	void __fastcall RedrawShape();
	void __fastcall RefreshHatchGallery();
	void __fastcall SetLTransp();
	
public:
	Vcltee::Tecanvas::TTeeBrush* TheBrush;
	__classmethod TBrushDialog* __fastcall AddDialog(Vcltee::Tecanvas::TTeeBrush* const ABrush, Vcl::Controls::TWinControl* const AParent);
	__classmethod bool __fastcall ImageGallery(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TTeePicture* const AImage);
	void __fastcall RefreshBrush(Vcltee::Tecanvas::TTeeBrush* const ABrush);
	__property Vcltee::Teeprocs::TColorEvent LinkedColor = {read=FLinkedColor, write=FLinkedColor};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBrushDialog(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBrushDialog(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBrushDialog() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBrushDialog(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall EditTeeFont(System::Classes::TComponent* const AOwner, Vcl::Graphics::TFont* const AFont);
extern DELPHI_PACKAGE bool __fastcall EditChartBrush(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TTeeBrush* const ChartBrush);
extern DELPHI_PACKAGE bool __fastcall EditChartBrushLinkedColor(System::Classes::TComponent* const AOwner, Vcltee::Tecanvas::TTeeBrush* const ChartBrush, Vcltee::Teeprocs::TColorEvent aLinkedColor);
extern DELPHI_PACKAGE System::UnicodeString __fastcall TeeGetPictureFileName(System::Classes::TComponent* const AOwner);
extern DELPHI_PACKAGE void __fastcall TeeLoadClearImage(System::Classes::TComponent* const AOwner, Vcl::Graphics::TPicture* const AImage);
extern DELPHI_PACKAGE void __fastcall GetTeeBrush(int Index, Vcl::Graphics::TBitmap* const ABitmap);
}	/* namespace Teebrushdlg */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEBRUSHDLG)
using namespace Vcltee::Teebrushdlg;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeebrushdlgHPP
