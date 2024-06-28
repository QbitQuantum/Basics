// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeAxMaxMin.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeaxmaxminHPP
#define Vcltee_TeeaxmaxminHPP

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
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeaxmaxmin
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAxisMaxMin;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAxisMaxMin : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TButton* BitBtn1;
	Vcl::Stdctrls::TButton* BitBtn2;
	Vcl::Stdctrls::TEdit* EMaximum;
	Vcl::Stdctrls::TEdit* EMinimum;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall BitBtn1Click(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	
public:
	bool IsDateTime;
	double MaxMin;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAxisMaxMin(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAxisMaxMin(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAxisMaxMin() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TAxisMaxMin(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeaxmaxmin */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEAXMAXMIN)
using namespace Vcltee::Teeaxmaxmin;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeaxmaxminHPP
