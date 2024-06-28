// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeArrowEdi.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeearrowediHPP
#define Vcltee_TeearrowediHPP

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
#include <VCLTee.ArrowCha.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teearrowedi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TArrowSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TArrowSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabFormat;
	Vcl::Comctrls::TTabSheet* TabBorder;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TLabel* LPercent;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TEdit* SEArrowWidth;
	Vcl::Stdctrls::TEdit* SEArrowHeight;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TCheckBox* CBColorEach;
	Vcltee::Tecanvas::TButtonColor* BArrowColor;
	Vcl::Comctrls::TUpDown* UDArrowWidth;
	Vcl::Comctrls::TUpDown* UDArrowHeight;
	Vcl::Stdctrls::TScrollBar* SBPercent;
	Vcl::Stdctrls::TEdit* ETransp;
	Vcl::Comctrls::TUpDown* UDTransp;
	Vcl::Stdctrls::TCheckBox* CBFill2D;
	void __fastcall CBColorEachClick(System::TObject* Sender);
	void __fastcall SEArrowWidthChange(System::TObject* Sender);
	void __fastcall SEArrowHeightChange(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall SBPercentChange(System::TObject* Sender);
	void __fastcall ETranspChange(System::TObject* Sender);
	void __fastcall PageControl1Change(System::TObject* Sender);
	void __fastcall CBFill2DClick(System::TObject* Sender);
	
private:
	Vcltee::Arrowcha::TArrowSeries* Arrow;
	void __fastcall SetLPercent();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TArrowSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TArrowSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TArrowSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TArrowSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teearrowedi */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEARROWEDI)
using namespace Vcltee::Teearrowedi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeearrowediHPP
