// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeTextShapeEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeetextshapeeditorHPP
#define Vcltee_TeetextshapeeditorHPP

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
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeMargins.hpp>
#include <VCLTee.TeeCustomShapeEditor.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teetextshapeeditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTextShapeEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTextShapeEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabText;
	Vcl::Stdctrls::TMemo* MemoText;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label9;
	Vcl::Buttons::TSpeedButton* SpeedButton1;
	Vcltee::Tecanvas::TComboFlat* CBTextAlign;
	Vcltee::Tecanvas::TComboFlat* CBCursor;
	Vcl::Stdctrls::TCheckBox* CBClip;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Comctrls::TTabSheet* TabMargins;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcl::Comctrls::TPageControl* PageFormat;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcl::Stdctrls::TLabel* Label2;
	Vcltee::Tecanvas::TComboFlat* CBAlign;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Comctrls::TTrackBar* TBAngle;
	Vcl::Extctrls::TRadioGroup* RGFormat;
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall MemoTextChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBTextAlignChange(System::TObject* Sender);
	void __fastcall CBCursorChange(System::TObject* Sender);
	void __fastcall CBClipClick(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall SpeedButton1Click(System::TObject* Sender);
	void __fastcall PageFormatChange(System::TObject* Sender);
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall CBAlignChange(System::TObject* Sender);
	void __fastcall PageControl1GetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	void __fastcall TBAngleChange(System::TObject* Sender);
	void __fastcall RGFormatClick(System::TObject* Sender);
	
private:
	Vcltee::Teengine::TCustomTextShape* Shape;
	bool AssigningText;
	bool CreatingForm;
	Vcltee::Teecustomshapeeditor::TFormTeeShape* ShapeForm;
	Vcltee::Teemargins::TMarginsEditor* MarginsForm;
	
public:
	__classmethod TTextShapeEditor* __fastcall InsertForm(Vcltee::Teengine::TCustomTextShape* const AShape, Vcl::Controls::TWinControl* const AParent);
	void __fastcall RefreshShape(Vcltee::Teengine::TCustomTextShape* const AShape);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTextShapeEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTextShapeEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTextShapeEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTextShapeEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teetextshapeeditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEETEXTSHAPEEDITOR)
using namespace Vcltee::Teetextshapeeditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeetextshapeeditorHPP
