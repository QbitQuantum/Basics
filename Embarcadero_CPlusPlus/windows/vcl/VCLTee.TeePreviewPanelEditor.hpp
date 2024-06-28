// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeePreviewPanelEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeepreviewpaneleditorHPP
#define Vcltee_TeepreviewpaneleditorHPP

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
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeePreviewPanel.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teepreviewpaneleditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormPreviewPanelEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormPreviewPanelEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Stdctrls::TCheckBox* CBAllowMove;
	Vcl::Stdctrls::TCheckBox* CBAllowResize;
	Vcl::Stdctrls::TCheckBox* CBDragImage;
	Vcl::Stdctrls::TCheckBox* CBAsBitmap;
	Vcl::Stdctrls::TCheckBox* CBShowImage;
	Vcl::Extctrls::TRadioGroup* RGOrientation;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Comctrls::TTabSheet* TabPanel;
	Vcl::Comctrls::TTabSheet* TabMargins;
	Vcltee::Tecanvas::TButtonColor* BPaperColor;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* Button1;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBAllowMoveClick(System::TObject* Sender);
	void __fastcall CBAllowResizeClick(System::TObject* Sender);
	void __fastcall CBDragImageClick(System::TObject* Sender);
	void __fastcall CBAsBitmapClick(System::TObject* Sender);
	void __fastcall CBShowImageClick(System::TObject* Sender);
	void __fastcall RGOrientationClick(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	
private:
	Vcltee::Teepreviewpanel::TTeePreviewPanel* TeePreviewPanel1;
	
public:
	__fastcall TFormPreviewPanelEditor(System::Classes::TComponent* AOwner, Vcltee::Teepreviewpanel::TTeePreviewPanel* APanel);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormPreviewPanelEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormPreviewPanelEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormPreviewPanelEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormPreviewPanelEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teepreviewpaneleditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEPREVIEWPANELEDITOR)
using namespace Vcltee::Teepreviewpaneleditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeepreviewpaneleditorHPP
