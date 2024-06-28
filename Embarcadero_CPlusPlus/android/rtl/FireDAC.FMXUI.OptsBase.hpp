// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.FMXUI.OptsBase.pas' rev: 34.00 (Android)

#ifndef Firedac_Fmxui_OptsbaseHPP
#define Firedac_Fmxui_OptsbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.IniFiles.hpp>
#include <System.UITypes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ExtCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Edit.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Dialogs.hpp>
#include <FMX.StdCtrls.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Fmxui
{
namespace Optsbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFMXOptsBase;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TfrmFDGUIxFMXOptsBase : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* pnlTop;
	Fmx::Objects::TImage* Image2;
	Fmx::Stdctrls::TLabel* lblPrompt;
	Fmx::Stdctrls::TPanel* pnlButtons;
	Fmx::Stdctrls::TButton* btnOk;
	Fmx::Stdctrls::TButton* btnCancel;
	Fmx::Objects::TLine* Line1;
	Fmx::Objects::TLine* Line2;
	Fmx::Objects::TLine* Line3;
	Fmx::Objects::TLine* Line4;
	Fmx::Stdctrls::TPanel* pnlAlign;
	void __fastcall FormActivate(System::TObject* Sender);
	void __fastcall FormClose(System::TObject* Sender, System::Uitypes::TCloseAction &Action);
	void __fastcall FormCreate(System::TObject* Sender);
	
private:
	bool FShown;
	
protected:
	bool FCentered;
	virtual void __fastcall LoadFormState(System::Inifiles::TCustomIniFile* AIni);
	virtual void __fastcall SaveFormState(System::Inifiles::TCustomIniFile* AIni);
	void __fastcall WaitModal();
	
public:
	void __fastcall LoadState();
	HIDESBASE void __fastcall SaveState();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TfrmFDGUIxFMXOptsBase(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFMXOptsBase(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFMXOptsBase() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall FDGUIxFMXCancel(void);
extern DELPHI_PACKAGE void * __fastcall FDGUIxFMXBeginModal(Fmx::Forms::TCustomForm* AForm, bool ASaveActive = true);
extern DELPHI_PACKAGE void __fastcall FDGUIxFMXEndModal(void * &AData);
extern DELPHI_PACKAGE int __fastcall FDGUIxFMXSetupEditor(Fmx::Listbox::TComboBox* ACombo, Fmx::Edit::TEdit* AEdit, Fmx::Edit::TCustomEdit* AFileEdt, Fmx::Dialogs::TOpenDialog* AOpenDlg, const System::UnicodeString AType);
}	/* namespace Optsbase */
}	/* namespace Fmxui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI_OPTSBASE)
using namespace Firedac::Fmxui::Optsbase;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_FMXUI)
using namespace Firedac::Fmxui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Fmxui_OptsbaseHPP
