// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFormatting.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeformattingHPP
#define Vcltee_TeeformattingHPP

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
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeformatting
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormatEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormatEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* PanelOK;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Stdctrls::TButton* Button2;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcltee::Tecanvas::TComboFlat* CBCustom;
	Vcltee::Tecanvas::TComboFlat* CBDate;
	Vcl::Stdctrls::TRadioButton* RBDate;
	Vcl::Stdctrls::TRadioButton* RBCustom;
	Vcl::Stdctrls::TRadioButton* RBGeo;
	Vcltee::Tecanvas::TComboFlat* CBGeo;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TRadioButton* RBInteger;
	Vcl::Stdctrls::TCheckBox* CBPercent;
	Vcl::Stdctrls::TCheckBox* CBThousands;
	Vcl::Stdctrls::TCheckBox* CBCurrency;
	Vcl::Stdctrls::TCheckBox* CBFixedDecimals;
	Vcl::Comctrls::TUpDown* UpDown1;
	Vcl::Stdctrls::TEdit* Edit1;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* Edit2;
	Vcl::Comctrls::TUpDown* UpDown2;
	void __fastcall RadioGroup1Click(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBDateChange(System::TObject* Sender);
	void __fastcall CBCustomChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBPercentClick(System::TObject* Sender);
	void __fastcall CBThousandsClick(System::TObject* Sender);
	void __fastcall CBGeoChange(System::TObject* Sender);
	void __fastcall RBIntegerClick(System::TObject* Sender);
	
private:
	bool tmpChanging;
	void __fastcall AddDate(const System::UnicodeString S);
	void __fastcall AddGeo(const System::UnicodeString S);
	
public:
	System::UnicodeString Format;
	bool IsDate;
	bool IsGeo;
	__classmethod void __fastcall AddDefaultFormats(System::Classes::TStrings* AItems);
	System::UnicodeString __fastcall TheFormat();
	__classmethod System::UnicodeString __fastcall Change(System::Classes::TComponent* AOwner, const System::UnicodeString AFormat, bool AllowDates = true);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormatEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormatEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormatEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFormatEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeformatting */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFORMATTING)
using namespace Vcltee::Teeformatting;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeformattingHPP
