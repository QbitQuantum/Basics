// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.About.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_AboutHPP
#define Firedac_Vclui_AboutHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace About
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsAbout;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsAbout : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TLabel* lblVersion;
	Vcl::Stdctrls::TLabel* lblCopyright;
	Vcl::Stdctrls::TLabel* lblInternetLink;
	Vcl::Extctrls::TImage* Image1;
	void __fastcall lblInternetLinkClick(System::TObject* Sender);
	void __fastcall Image1Click(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	
public:
	void __fastcall Setup(NativeUInt AModHInst, const System::UnicodeString ACaption);
#ifndef _WIN64
	__classmethod void __fastcall Execute(NativeUInt AModHInst = (NativeUInt)(0x0), const System::UnicodeString ACaption = System::UnicodeString());
#else /* _WIN64 */
	__classmethod void __fastcall Execute(NativeUInt AModHInst = (NativeUInt)(0ULL), const System::UnicodeString ACaption = System::UnicodeString());
#endif /* _WIN64 */
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmFDGUIxFormsAbout(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsAbout(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsAbout() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsAbout(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TfrmFDGUIxFormsAbout* frmFDGUIxFormsAbout;
}	/* namespace About */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_ABOUT)
using namespace Firedac::Vclui::About;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI)
using namespace Firedac::Vclui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Vclui_AboutHPP
