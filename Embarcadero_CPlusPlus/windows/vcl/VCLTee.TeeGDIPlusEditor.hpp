// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeGDIPlusEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeegdipluseditorHPP
#define Vcltee_TeegdipluseditorHPP

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
#include <VCLTee.TeeGDIPlus.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <Vcl.ComCtrls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teegdipluseditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGDIPlusEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGDIPlusEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TCheckBox* CBAntiAlias;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* XDPI;
	Vcl::Stdctrls::TLabel* YDPI;
	Vcl::Stdctrls::TCheckBox* CBBuffered;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBTextQuality;
	Vcl::Stdctrls::TCheckBox* CBActive;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Comctrls::TTrackBar* TBScale;
	Vcl::Stdctrls::TLabel* LScale;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBAntiAliasClick(System::TObject* Sender);
	void __fastcall CBBufferedClick(System::TObject* Sender);
	void __fastcall CBTextQualityChange(System::TObject* Sender);
	void __fastcall CBActiveClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall TBScaleChange(System::TObject* Sender);
	
private:
	bool ICreating;
	Vcltee::Teegdiplus::TTeeGDIPlus* GDIPlus;
	Vcltee::Teegdiplus::TGDIPlusCanvas* GDIPlusCanvas;
	void __fastcall ForceGDIPLUSComponent();
	
public:
	__classmethod bool __fastcall ModalShow(System::Classes::TComponent* AOwner, Vcltee::Teegdiplus::TTeeGDIPlus* const AGDIPlus);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TGDIPlusEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TGDIPlusEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TGDIPlusEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TGDIPlusEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teegdipluseditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEGDIPLUSEDITOR)
using namespace Vcltee::Teegdipluseditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeegdipluseditorHPP
