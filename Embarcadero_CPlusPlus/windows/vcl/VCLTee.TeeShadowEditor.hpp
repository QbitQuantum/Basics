// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeShadowEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeshadoweditorHPP
#define Vcltee_TeeshadoweditorHPP

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
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeshadoweditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeShadowEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeShadowEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelButtons;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TButton* ButtonOK;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* LBlur;
	Vcl::Stdctrls::TCheckBox* CBSmooth;
	Vcl::Comctrls::TTrackBar* TBBlur;
	Vcl::Stdctrls::TCheckBox* CBClip;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcltee::Tecanvas::TButtonColor* BShadowColor;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* Edit1;
	Vcl::Comctrls::TUpDown* UDShadowSize;
	Vcl::Stdctrls::TEdit* EVertSize;
	Vcl::Comctrls::TUpDown* UDShaVert;
	Vcl::Comctrls::TTrackBar* TBSize;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcl::Comctrls::TTrackBar* TBColor;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBDirection;
	void __fastcall Edit1Change(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall EVertSizeChange(System::TObject* Sender);
	void __fastcall ButtonOKClick(System::TObject* Sender);
	void __fastcall CBSmoothClick(System::TObject* Sender);
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall TBBlurChange(System::TObject* Sender);
	void __fastcall TBColorChange(System::TObject* Sender);
	void __fastcall BShadowColorClick(System::TObject* Sender);
	void __fastcall CBClipClick(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall TBSizeChange(System::TObject* Sender);
	void __fastcall CBDirectionChange(System::TObject* Sender);
	
private:
	bool IChanging;
	bool CreatingForm;
	System::Word H;
	System::Word L;
	System::Word S;
	bool __fastcall CanChange();
	void __fastcall SetTrackBarSize();
	
protected:
	Vcltee::Tecanvas::TTeeShadow* Shadow;
	
public:
	__classmethod TTeeShadowEditor* __fastcall InsertForm(Vcltee::Tecanvas::TTeeShadow* const AShadow, Vcl::Controls::TWinControl* const AParent);
	void __fastcall RefreshControls(Vcltee::Tecanvas::TTeeShadow* const AShadow);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeShadowEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeShadowEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeShadowEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeShadowEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall EditTeeShadow(System::Classes::TComponent* AOwner, Vcltee::Tecanvas::TTeeShadow* AShadow);
}	/* namespace Teeshadoweditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESHADOWEDITOR)
using namespace Vcltee::Teeshadoweditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeshadoweditorHPP
