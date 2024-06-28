// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeAbout.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeaboutHPP
#define Vcltee_TeeaboutHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <Vcl.Imaging.jpeg.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeabout
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeAboutForm;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeAboutForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TButton* BClose;
	Vcl::Stdctrls::TLabel* LabelCopy;
	Vcl::Stdctrls::TLabel* LabelVersion;
	Vcl::Stdctrls::TLabel* LabelRights;
	Vcl::Stdctrls::TLabel* Labelwww;
	Vcl::Extctrls::TImage* Image1;
	Vcl::Extctrls::TBevel* Bevel1;
	Vcl::Stdctrls::TLabel* LabelExtra;
	Vcl::Stdctrls::TLabel* LabelUpdate;
	Vcl::Stdctrls::TLabel* LabelLicense;
	Vcl::Stdctrls::TLabel* LabelEval;
	Vcl::Extctrls::TTimer* Timer1;
	void __fastcall LabelwwwClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall LabelUpdateClick(System::TObject* Sender);
	void __fastcall Timer1Timer(System::TObject* Sender);
	
protected:
	virtual System::UnicodeString __fastcall GetLicense();
	void __fastcall Prepare(const System::UnicodeString ACaption, const System::UnicodeString AVersion, const System::UnicodeString AExtra);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeAboutForm(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeAboutForm(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeAboutForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeAboutForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall (*TeeAboutBoxProc)(void);
extern DELPHI_PACKAGE bool TeeIsTrial;
extern DELPHI_PACKAGE void __fastcall TeeShowAboutBox(const System::UnicodeString ACaption = System::UnicodeString(), const System::UnicodeString AVersion = System::UnicodeString(), const System::UnicodeString AExtra = System::UnicodeString());
}	/* namespace Teeabout */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEABOUT)
using namespace Vcltee::Teeabout;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeaboutHPP
