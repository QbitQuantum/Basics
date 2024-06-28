// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeSymbolEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeesymboleditorHPP
#define Vcltee_TeesymboleditorHPP

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
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeeShadowEditor.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teesymboleditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSymbolEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSymbolEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabGradient;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Stdctrls::TLabel* Label3;
	Vcltee::Tecanvas::TComboFlat* CBSymbolPos;
	Vcl::Stdctrls::TCheckBox* CBContinuous;
	Vcl::Stdctrls::TCheckBox* CBVisible;
	Vcl::Stdctrls::TCheckBox* CBSymPen;
	Vcl::Comctrls::TTabSheet* TabSize;
	Vcl::Stdctrls::TLabel* L11;
	Vcl::Stdctrls::TEdit* SEColWi;
	Vcl::Comctrls::TUpDown* UDColWi;
	Vcltee::Tecanvas::TComboFlat* CBColWUnits;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TEdit* SEColHe;
	Vcl::Comctrls::TUpDown* UDColHe;
	Vcltee::Tecanvas::TComboFlat* CBColHUnits;
	Vcl::Stdctrls::TCheckBox* CBSquared;
	void __fastcall CBVisibleClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall SEColWiChange(System::TObject* Sender);
	void __fastcall CBColWUnitsChange(System::TObject* Sender);
	void __fastcall CBSymbolPosChange(System::TObject* Sender);
	void __fastcall CBContinuousClick(System::TObject* Sender);
	void __fastcall CBSymPenClick(System::TObject* Sender);
	void __fastcall CBSquaredClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall PageControl1GetImageIndex(System::TObject* Sender, int TabIndex, int &ImageIndex);
	void __fastcall CBColHUnitsChange(System::TObject* Sender);
	void __fastcall SEColHeChange(System::TObject* Sender);
	
private:
	bool CreatingForm;
	Vcltee::Chart::TLegendSymbol* Symbol;
	Vcltee::Teependlg::TPenDialog* IBorderEditor;
	Vcltee::Teeedigrad::TTeeGradientEditor* IGradientEditor;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* IShadowEditor;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* IEmbossEditor;
	
public:
	__classmethod TSymbolEditor* __fastcall InsertForm(Vcltee::Chart::TLegendSymbol* const ASymbol, Vcl::Controls::TWinControl* const AParent);
	void __fastcall RefreshSymbol(Vcltee::Chart::TLegendSymbol* ASymbol);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSymbolEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSymbolEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSymbolEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TSymbolEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teesymboleditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESYMBOLEDITOR)
using namespace Vcltee::Teesymboleditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeesymboleditorHPP
