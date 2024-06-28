// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeAxisIncr.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeaxisincrHPP
#define Vcltee_TeeaxisincrHPP

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
#include <VCLTee.Chart.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeaxisincr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAxisIncrement;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAxisIncrement : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TRadioGroup* RadioGroup1;
	Vcltee::Tecanvas::TComboFlat* CBSteps;
	Vcl::Stdctrls::TEdit* ECustom;
	Vcl::Stdctrls::TButton* BOk;
	Vcl::Stdctrls::TButton* BCancel;
	Vcl::Stdctrls::TLabel* LIncrement;
	Vcl::Stdctrls::TCheckBox* CBExact;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall RadioGroup1Click(System::TObject* Sender);
	void __fastcall BOkClick(System::TObject* Sender);
	void __fastcall CBExactClick(System::TObject* Sender);
	void __fastcall CBStepsChange(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	
private:
	void __fastcall SetEditText();
	
public:
	bool IsDateTime;
	bool IsExact;
	double Increment;
	Vcltee::Teeprocs::TDateTimeStep IStep;
	__classmethod bool __fastcall ChangeIncrement(System::Classes::TComponent* AOwner, Vcltee::Teengine::TChartAxis* Axis);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAxisIncrement(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAxisIncrement(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAxisIncrement() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TAxisIncrement(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall TeeShowIncorrect(const System::UnicodeString Message);
extern DELPHI_PACKAGE System::UnicodeString __fastcall GetIncrementText(System::Classes::TComponent* AOwner, const double Increment, bool IsDateTime, bool ExactDateTime, const System::UnicodeString AFormat);
}	/* namespace Teeaxisincr */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEAXISINCR)
using namespace Vcltee::Teeaxisincr;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeaxisincrHPP
