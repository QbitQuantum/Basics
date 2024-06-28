// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeCustEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeecusteditHPP
#define Vcltee_TeecusteditHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeEdiGrad.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teecustedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCustomSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCustomSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcltee::Tecanvas::TButtonColor* BLineColor;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcl::Stdctrls::TCheckBox* CBDark3D;
	Vcl::Comctrls::TTrackBar* TBTransp;
	Vcl::Stdctrls::TLabel* LTransp;
	Vcl::Stdctrls::TCheckBox* CBEachLine;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* LHeight;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TGroupBox* GBStair;
	Vcl::Stdctrls::TCheckBox* CBStairs;
	Vcl::Stdctrls::TCheckBox* CBInvStairs;
	Vcl::Stdctrls::TCheckBox* CBSmoothed;
	Vcltee::Tecanvas::TComboFlat* CBStack;
	Vcl::Stdctrls::TEdit* EHeight;
	Vcl::Comctrls::TUpDown* UDHeight;
	Vcl::Stdctrls::TCheckBox* CBClick;
	Vcltee::Tecanvas::TComboFlat* CBNulls;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* ETolerance;
	Vcl::Comctrls::TUpDown* UDTolerance;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Comctrls::TTabSheet* TabOutline;
	Vcl::Stdctrls::TLabel* LDrawStyle;
	Vcltee::Tecanvas::TComboFlat* CBDrawStyle;
	Vcl::Stdctrls::TCheckBox* CBDefColor;
	Vcl::Stdctrls::TCheckBox* CBPointerBehind;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TCheckBox* CBInflate;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBStairsClick(System::TObject* Sender);
	void __fastcall CBInvStairsClick(System::TObject* Sender);
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall CBDark3DClick(System::TObject* Sender);
	void __fastcall CBStackChange(System::TObject* Sender);
	void __fastcall EHeightChange(System::TObject* Sender);
	void __fastcall CBClickClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBEachLineClick(System::TObject* Sender);
	void __fastcall BLineColorClick(System::TObject* Sender);
	void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall CBNullsChange(System::TObject* Sender);
	void __fastcall TBTranspChange(System::TObject* Sender);
	void __fastcall CBSmoothedClick(System::TObject* Sender);
	void __fastcall EToleranceChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBDrawStyleChange(System::TObject* Sender);
	void __fastcall CBDefColorClick(System::TObject* Sender);
	void __fastcall CBPointerBehindClick(System::TObject* Sender);
	void __fastcall CBInflateClick(System::TObject* Sender);
	
private:
	Vcl::Forms::TCustomForm* PointerForm;
	Vcltee::Series::TCustomSeries* TheSeries;
	Vcltee::Teependlg::TPenDialog* IBorderEditor;
	void __fastcall CheckDefColor();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TCustomSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TCustomSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TCustomSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TCustomSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teecustedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEECUSTEDIT)
using namespace Vcltee::Teecustedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeecusteditHPP
