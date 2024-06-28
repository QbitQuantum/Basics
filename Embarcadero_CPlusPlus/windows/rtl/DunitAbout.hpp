// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DUnitAbout.pas' rev: 34.00 (Windows)

#ifndef DunitaboutHPP
#define DunitaboutHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Dunitabout
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDUnitAboutBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDUnitAboutBox : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* MainPanel;
	Vcl::Extctrls::TPanel* NamePanel;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TMemo* IdentMemo;
	Vcl::Stdctrls::TMemo* Credits;
	Vcl::Extctrls::TTimer* Timer;
	Vcl::Extctrls::TPanel* LogoPanel;
	Vcl::Extctrls::TImage* LogoImage;
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall TimerTimer(System::TObject* Sender);
	void __fastcall MainPanelClick(System::TObject* Sender);
	void __fastcall FormKeyDown(System::TObject* Sender, System::Word &Key, System::Classes::TShiftState Shift);
	void __fastcall FormCreate(System::TObject* Sender);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDUnitAboutBox(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDUnitAboutBox(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDUnitAboutBox() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDUnitAboutBox(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString rcs_id;
extern DELPHI_PACKAGE void __fastcall Splash(void);
}	/* namespace Dunitabout */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DUNITABOUT)
using namespace Dunitabout;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DunitaboutHPP
