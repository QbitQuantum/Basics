// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeCircledEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeecirclededitHPP
#define Vcltee_TeecirclededitHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeePenDlg.hpp>
#include <VCLTee.TeeBrushDlg.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teecirclededit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCircledSeriesEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCircledSeriesEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabOptions;
	Vcl::Comctrls::TTabSheet* TabRadius;
	Vcl::Comctrls::TTabSheet* TabShadow;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TCheckBox* CBCircled;
	Vcl::Stdctrls::TCheckBox* CB3D;
	Vcl::Stdctrls::TGroupBox* GroupBox2;
	Vcl::Stdctrls::TLabel* Label4;
	Vcl::Stdctrls::TLabel* Label5;
	Vcl::Stdctrls::TEdit* Edit2;
	Vcl::Stdctrls::TCheckBox* CBAutoXR;
	Vcl::Stdctrls::TEdit* Edit3;
	Vcl::Stdctrls::TCheckBox* CBAutoYR;
	Vcl::Comctrls::TUpDown* UDY;
	Vcl::Comctrls::TUpDown* UDX;
	Vcl::Comctrls::TTabSheet* TabEmboss;
	Vcl::Comctrls::TTrackBar* TBRotation;
	Vcl::Stdctrls::TLabel* LRotation;
	Vcl::Stdctrls::TCheckBox* CBUniqueRadius;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBCircledClick(System::TObject* Sender);
	void __fastcall SEXRadiusChange(System::TObject* Sender);
	void __fastcall SEYRadiusChange(System::TObject* Sender);
	void __fastcall CBAutoXRClick(System::TObject* Sender);
	void __fastcall CBAutoYRClick(System::TObject* Sender);
	void __fastcall CB3DClick(System::TObject* Sender);
	void __fastcall TBRotationChange(System::TObject* Sender);
	void __fastcall CBUniqueRadiusClick(System::TObject* Sender);
	
private:
	Vcltee::Series::TCircledSeries* Circled;
	bool CreatingForm;
	
public:
	__classmethod TCircledSeriesEditor* __fastcall CreateForm(Vcl::Forms::TCustomForm* AForm, Vcltee::Series::TCircledSeries* const Circled);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TCircledSeriesEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TCircledSeriesEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TCircledSeriesEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TCircledSeriesEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teecirclededit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEECIRCLEDEDIT)
using namespace Vcltee::Teecirclededit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeecirclededitHPP
