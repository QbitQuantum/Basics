// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'DUnitMainForm.pas' rev: 34.00 (Windows)

#ifndef DunitmainformHPP
#define DunitmainformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <System.Classes.hpp>
#include <TestFramework.hpp>
#include <GUITestRunner.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ActnList.hpp>
#include <Vcl.ImgList.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ToolWin.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Forms.hpp>

//-- user supplied -----------------------------------------------------------

namespace Dunitmainform
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDUnitForm;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDUnitForm : public Guitestrunner::TGUITestRunner
{
	typedef Guitestrunner::TGUITestRunner inherited;
	
__published:
	Vcl::Actnlist::TActionList* DUnitActions;
	Vcl::Actnlist::TAction* LoadTestsAction;
	Vcl::Actnlist::TAction* UnloadTestscAction;
	Vcl::Dialogs::TOpenDialog* OpenTestsDialog;
	Vcl::Menus::TMenuItem* LoadTests1;
	Vcl::Actnlist::TAction* AboutAction;
	Vcl::Menus::TMenuItem* Help1;
	Vcl::Menus::TMenuItem* AboutItem;
	void __fastcall LoadTestsActionExecute(System::TObject* Sender);
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	HIDESBASE void __fastcall FormDestroy(System::TObject* Sender);
	void __fastcall AboutActionExecute(System::TObject* Sender);
	
protected:
	Testframework::_di_ITestSuite FRootSuite;
	
public:
	__property Testframework::_di_ITestSuite RootSuite = {read=FRootSuite};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TDUnitForm(System::Classes::TComponent* AOwner) : Guitestrunner::TGUITestRunner(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TDUnitForm(System::Classes::TComponent* AOwner, int Dummy) : Guitestrunner::TGUITestRunner(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TDUnitForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TDUnitForm(HWND ParentWindow) : Guitestrunner::TGUITestRunner(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString rcs_id;
extern DELPHI_PACKAGE TDUnitForm* DUnitForm;
}	/* namespace Dunitmainform */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DUNITMAINFORM)
using namespace Dunitmainform;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// DunitmainformHPP
