// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeSelectList.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeselectlistHPP
#define Vcltee_TeeselectlistHPP

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
#include <Vcl.Buttons.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeeProcs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeselectlist
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSelectListForm;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSelectListForm : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TListBox* FromList;
	Vcl::Stdctrls::TListBox* ToList;
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Buttons::TSpeedButton* BMoveUP;
	Vcl::Buttons::TSpeedButton* BMoveDown;
	Vcl::Extctrls::TPanel* Panel2;
	Vcl::Stdctrls::TLabel* L22;
	Vcl::Stdctrls::TLabel* L24;
	Vcl::Extctrls::TPanel* Panel3;
	Vcl::Stdctrls::TButton* BRightOne;
	Vcl::Stdctrls::TButton* BRightAll;
	Vcl::Stdctrls::TButton* BLeftOne;
	Vcl::Stdctrls::TButton* BLeftAll;
	Vcl::Extctrls::TSplitter* Splitter1;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall BMoveUPClick(System::TObject* Sender);
	void __fastcall ToListDblClick(System::TObject* Sender);
	void __fastcall FromListDblClick(System::TObject* Sender);
	void __fastcall BLeftAllClick(System::TObject* Sender);
	void __fastcall BRightAllClick(System::TObject* Sender);
	void __fastcall BLeftOneClick(System::TObject* Sender);
	void __fastcall BRightOneClick(System::TObject* Sender);
	void __fastcall ToListClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	
private:
	HIDESBASE void __fastcall Changed();
	
public:
	System::Classes::TNotifyEvent OnChange;
	void __fastcall EnableButtons();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TSelectListForm(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TSelectListForm(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TSelectListForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TSelectListForm(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeselectlist */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEESELECTLIST)
using namespace Vcltee::Teeselectlist;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeselectlistHPP
