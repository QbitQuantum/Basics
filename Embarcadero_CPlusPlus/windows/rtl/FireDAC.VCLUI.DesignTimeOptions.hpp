// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.DesignTimeOptions.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_DesigntimeoptionsHPP
#define Firedac_Vclui_DesigntimeoptionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
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
#include <FireDAC.VCLUI.OptsBase.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Phys.Intf.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Designtimeoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsDesignTimeOptions;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsDesignTimeOptions : public Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase
{
	typedef Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase inherited;
	
__published:
	Vcl::Stdctrls::TButton* btnRefreshMetadata;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TLabel* Label3;
	Vcl::Stdctrls::TEdit* edtCatalog;
	Vcl::Stdctrls::TEdit* edtSchema;
	Vcl::Stdctrls::TGroupBox* GroupBox2;
	Vcl::Stdctrls::TCheckBox* cbMy;
	Vcl::Stdctrls::TCheckBox* cbSystem;
	Vcl::Stdctrls::TCheckBox* cbOther;
	Vcl::Stdctrls::TGroupBox* GroupBox3;
	Vcl::Stdctrls::TLabel* Label6;
	Vcl::Stdctrls::TEdit* edtMask;
	Vcl::Stdctrls::TGroupBox* GroupBox4;
	Vcl::Stdctrls::TCheckBox* cbTable;
	Vcl::Stdctrls::TCheckBox* cbView;
	Vcl::Stdctrls::TCheckBox* cbSynonym;
	Vcl::Stdctrls::TCheckBox* cbTempTable;
	Vcl::Comctrls::TPageControl* PageControl1;
	Vcl::Comctrls::TTabSheet* TabSheet1;
	Vcl::Comctrls::TTabSheet* TabSheet2;
	Vcl::Stdctrls::TGroupBox* GroupBox5;
	Vcl::Stdctrls::TCheckBox* cbTraceDT;
	Vcl::Stdctrls::TGroupBox* GroupBox6;
	Vcl::Stdctrls::TCheckBox* cbDClickFE;
	Vcl::Stdctrls::TCheckBox* cbFullName;
	void __fastcall btnRefreshMetadataClick(System::TObject* Sender);
	
public:
	__classmethod bool __fastcall Execute();
public:
	/* TfrmFDGUIxFormsOptsBase.Create */ inline __fastcall virtual TfrmFDGUIxFormsDesignTimeOptions(System::Classes::TComponent* AOwner) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner) { }
	
public:
	/* TCustomForm.CreateNew */ inline __fastcall virtual TfrmFDGUIxFormsDesignTimeOptions(System::Classes::TComponent* AOwner, int Dummy) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsDesignTimeOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsDesignTimeOptions(HWND ParentWindow) : Firedac::Vclui::Optsbase::TfrmFDGUIxFormsOptsBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString GADDTCatalog;
extern DELPHI_PACKAGE System::UnicodeString GADDTSchema;
extern DELPHI_PACKAGE Firedac::Phys::Intf::TFDPhysObjectScopes GADDTScope;
extern DELPHI_PACKAGE System::UnicodeString GADDTMask;
extern DELPHI_PACKAGE Firedac::Phys::Intf::TFDPhysTableKinds GADDTTableKinds;
extern DELPHI_PACKAGE bool GADDTFullName;
extern DELPHI_PACKAGE bool GADMoniEnabled;
extern DELPHI_PACKAGE bool GADDCFieldsEditor;
}	/* namespace Designtimeoptions */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_DESIGNTIMEOPTIONS)
using namespace Firedac::Vclui::Designtimeoptions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI)
using namespace Firedac::Vclui;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Vclui_DesigntimeoptionsHPP
