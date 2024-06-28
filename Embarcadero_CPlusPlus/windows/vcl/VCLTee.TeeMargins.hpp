// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeMargins.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeemarginsHPP
#define Vcltee_TeemarginsHPP

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
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teemargins
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMarginsEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMarginsEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TRadioGroup* RGUnits;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Comctrls::TTrackBar* TBLeft;
	Vcl::Stdctrls::TLabel* LLeft;
	Vcl::Comctrls::TTrackBar* TBTop;
	Vcl::Stdctrls::TLabel* LTop;
	Vcl::Comctrls::TTrackBar* TBRight;
	Vcl::Stdctrls::TLabel* LRight;
	Vcl::Comctrls::TTrackBar* TBBottom;
	Vcl::Stdctrls::TLabel* LBottom;
	void __fastcall RGUnitsClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall TBLeftChange(System::TObject* Sender);
	void __fastcall TBTopChange(System::TObject* Sender);
	void __fastcall TBRightChange(System::TObject* Sender);
	void __fastcall TBBottomChange(System::TObject* Sender);
	
private:
	Vcltee::Teengine::TMargins* Margins;
	
public:
	void __fastcall RefreshControls(Vcltee::Teengine::TMargins* const AMargins);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TMarginsEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TMarginsEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TMarginsEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TMarginsEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teemargins */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEMARGINS)
using namespace Vcltee::Teemargins;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeemarginsHPP
