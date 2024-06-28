// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeDBEdit.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeedbeditHPP
#define Vcltee_TeedbeditHPP

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
#include <Data.DB.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeSourceEdit.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teedbedit
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBaseDBChartEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBaseDBChartEditor : public Vcltee::Teesourceedit::TBaseSourceEditor
{
	typedef Vcltee::Teesourceedit::TBaseSourceEditor inherited;
	
__published:
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	
private:
	void __fastcall FillSourceDatasets();
	void __fastcall FillSources();
	
protected:
	Data::Db::TDataSet* __fastcall DataSet();
	void __fastcall FillFields(Vcl::Stdctrls::TComboBox* const *Combos, const int Combos_High);
	virtual bool __fastcall IsValid(System::Classes::TComponent* AComponent);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBaseDBChartEditor(System::Classes::TComponent* AOwner) : Vcltee::Teesourceedit::TBaseSourceEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBaseDBChartEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teesourceedit::TBaseSourceEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBaseDBChartEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBaseDBChartEditor(HWND ParentWindow) : Vcltee::Teesourceedit::TBaseSourceEditor(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Vcltee::Teesourceedit::TOnGetDesignerNamesEvent OnGetDesignerNames;
}	/* namespace Teedbedit */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEDBEDIT)
using namespace Vcltee::Teedbedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeedbeditHPP
