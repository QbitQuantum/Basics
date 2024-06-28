// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeFrames.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeframesHPP
#define Vcltee_TeeframesHPP

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
#include <System.Math.hpp>
#include <System.Types.hpp>
#include <System.StrUtils.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeEdiGrad.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeframes
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFramedBorderEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFramedBorderEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl2;
	Vcl::Comctrls::TTabSheet* TabSheet8;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TCheckBox* CBFrameVisible;
	Vcl::Stdctrls::TEdit* EWidth;
	Vcl::Comctrls::TUpDown* UDWidth;
	Vcl::Comctrls::TTabSheet* TabSheet4;
	Vcl::Comctrls::TTabSheet* TabSheet5;
	Vcl::Comctrls::TTabSheet* TabSheet6;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Comctrls::TTabSheet* TabPattern;
	Vcl::Extctrls::TRadioGroup* RGStyle;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBFrameVisibleClick(System::TObject* Sender);
	void __fastcall EWidthChange(System::TObject* Sender);
	void __fastcall PageControl2Change(System::TObject* Sender);
	void __fastcall RGStyleClick(System::TObject* Sender);
	
private:
	Vcltee::Series::TFramedBorder* Frame;
	
public:
	__classmethod TFramedBorderEditor* __fastcall InsertDialog(Vcl::Controls::TWinControl* AParent, Vcltee::Series::TFramedBorder* AFrame);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFramedBorderEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFramedBorderEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFramedBorderEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TFramedBorderEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeframes */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEFRAMES)
using namespace Vcltee::Teeframes;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeframesHPP
