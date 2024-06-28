// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEdiPane.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeedipaneHPP
#define Vcltee_TeeedipaneHPP

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
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeEdiGrad.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeBackImage.hpp>
#include <VCLTee.TeeShadowEditor.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeedipane
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormTeePanel;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormTeePanel : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabBack;
	Vcl::Comctrls::TTabSheet* TabBorders;
	Vcl::Comctrls::TTabSheet* TabGradient;
	Vcltee::Tecanvas::TButtonColor* BPanelColor;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Stdctrls::TCheckBox* CBColorDef;
	Vcl::Comctrls::TTabSheet* TabImage;
	Vcl::Comctrls::TTabSheet* TabMargins;
	Vcl::Stdctrls::TGroupBox* GBMargins;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* SETopMa;
	Vcl::Stdctrls::TEdit* SELeftMa;
	Vcl::Stdctrls::TEdit* SEBotMa;
	Vcl::Stdctrls::TEdit* SERightMa;
	Vcl::Comctrls::TUpDown* UDTopMa;
	Vcl::Comctrls::TUpDown* UDRightMa;
	Vcl::Comctrls::TUpDown* UDLeftMa;
	Vcl::Comctrls::TUpDown* UDBotMa;
	Vcltee::Tecanvas::TComboFlat* CBMarUnits;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Extctrls::TPanel* PanelBackImage;
	Vcl::Stdctrls::TCheckBox* CBImageInside;
	Vcl::Comctrls::TPageControl* PageControl2;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TLabel* L19;
	Vcl::Stdctrls::TLabel* L2;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* SEPanelBor;
	Vcl::Stdctrls::TEdit* SEPanelWi;
	Vcl::Comctrls::TUpDown* UDPanelWi;
	Vcl::Comctrls::TUpDown* UDPanelBor;
	Vcltee::Tecanvas::TComboFlat* CBInner;
	Vcltee::Tecanvas::TComboFlat* CBOuter;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Comctrls::TTrackBar* TBRound;
	Vcl::Stdctrls::TLabel* LRound;
	Vcl::Stdctrls::TButton* Button1;
	void __fastcall SEPanelWiChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBImageInsideClick(System::TObject* Sender);
	void __fastcall SEPanelBorChange(System::TObject* Sender);
	void __fastcall BPanelColorClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBColorDefClick(System::TObject* Sender);
	void __fastcall CBInnerChange(System::TObject* Sender);
	void __fastcall CBOuterChange(System::TObject* Sender);
	void __fastcall CBMarUnitsChange(System::TObject* Sender);
	void __fastcall SERightMaChange(System::TObject* Sender);
	void __fastcall SETopMaChange(System::TObject* Sender);
	void __fastcall SEBotMaChange(System::TObject* Sender);
	void __fastcall SELeftMaChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall TBRoundChange(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	
private:
	bool Changing;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* FEmbossEditor;
	Vcltee::Teeedigrad::TTeeGradientEditor* FGradientEditor;
	Vcltee::Teebackimage::TBackImageEditor* FImageEditor;
	Vcltee::Teeshadoweditor::TTeeShadowEditor* FShadowEditor;
	Vcltee::Teependlg::TPenDialog* IBorderEditor;
	void __fastcall AdjustMarginMinMax();
	int __fastcall ChangeMargin(Vcl::Comctrls::TUpDown* UpDown, int APos, int OtherSide);
	void __fastcall CheckColorDef();
	
public:
	Vcltee::Teeprocs::TCustomTeePanelExtended* ThePanel;
	__fastcall TFormTeePanel(System::Classes::TComponent* Owner, Vcltee::Teeprocs::TCustomTeePanelExtended* APanel);
	__classmethod TFormTeePanel* __fastcall InsertAt(System::Classes::TComponent* AOwner, Vcl::Controls::TWinControl* AParent, Vcltee::Teeprocs::TCustomTeePanelExtended* APanel);
	void __fastcall RefreshPanel(Vcltee::Teeprocs::TCustomTeePanelExtended* APanel);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormTeePanel(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormTeePanel(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormTeePanel() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormTeePanel(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeedipane */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEDIPANE)
using namespace Vcltee::Teeedipane;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeedipaneHPP
