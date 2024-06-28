// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiFont.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedifontHPP
#define Vcltee_TeeedifontHPP

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
#include <System.UITypes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeeShadowEditor.hpp>
#include <VCLTee.TeeBackImage.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedifont
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeFontEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeFontEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabFont;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Stdctrls::TButton* Button3;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TCheckBox* CBItalic;
	Vcl::Stdctrls::TCheckBox* CBBold;
	Vcl::Stdctrls::TCheckBox* CBStrike;
	Vcl::Stdctrls::TCheckBox* CBUnder;
	Vcltee::Tecanvas::TButtonColor* BColor;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* EInter;
	Vcl::Comctrls::TUpDown* UDInter;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Comctrls::TTabSheet* TabGradient;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBName;
	Vcl::Comctrls::TTabSheet* TabPicture;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Stdctrls::TLabel* Label4;
	Vcltee::Tecanvas::TComboFlat* CBQuality;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* EDepth;
	Vcl::Comctrls::TUpDown* UDDepth;
	Vcl::Comctrls::TTabSheet* TabOutline;
	Vcl::Comctrls::TTrackBar* TBSize;
	Vcl::Stdctrls::TLabel* LSize;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Comctrls::TTrackBar* TBTransp;
	void __fastcall BFontClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall EInterChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall Button2Click(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBItalicClick(System::TObject* Sender);
	void __fastcall CBBoldClick(System::TObject* Sender);
	void __fastcall CBStrikeClick(System::TObject* Sender);
	void __fastcall CBUnderClick(System::TObject* Sender);
	void __fastcall CBNameChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBQualityChange(System::TObject* Sender);
	void __fastcall EDepthChange(System::TObject* Sender);
	void __fastcall TBSizeChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall BColorClick(System::TObject* Sender);
	
private:
	Vcltee::Tecanvas::TTeeFont* Backup;
	Vcltee::Tecanvas::TTeeFont* TheFont;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* FEmbossEditor;
	Vcltee::Teeedigrad::TTeeGradientEditor* FGradientEditor;
	Vcltee::Teebackimage::TBackImageEditor* FPicEditor;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* FShadowEditor;
	Vcltee::Teependlg::TPenDialog* FOutlineEditor;
	void __fastcall CheckStyle(Vcl::Stdctrls::TCheckBox* Check, System::Uitypes::TFontStyle Value);
	void __fastcall RefreshBasicProps();
	
public:
	void __fastcall RefreshControls(Vcltee::Tecanvas::TTeeFont* AFont);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeFontEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeFontEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeFontEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeFontEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TTeeFontEditor* __fastcall InsertTeeFontEditor(Vcl::Comctrls::TTabSheet* ATab);
extern DELPHI_PACKAGE bool __fastcall EditTeeFontEx(System::Classes::TComponent* AOwner, Vcltee::Tecanvas::TTeeFont* AFont);
}	/* namespace Teeedifont */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIFONT)
using namespace Vcltee::Teeedifont;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedifontHPP
