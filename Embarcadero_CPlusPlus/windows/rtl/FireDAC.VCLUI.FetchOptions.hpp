// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.VCLUI.FetchOptions.pas' rev: 34.00 (Windows)

#ifndef Firedac_Vclui_FetchoptionsHPP
#define Firedac_Vclui_FetchoptionsHPP

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
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <FireDAC.Stan.Option.hpp>
#include <FireDAC.VCLUI.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Vclui
{
namespace Fetchoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TfrmFDGUIxFormsFetchOptions;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TfrmFDGUIxFormsFetchOptions : public Vcl::Forms::TFrame
{
	typedef Vcl::Forms::TFrame inherited;
	
__published:
	Vcl::Extctrls::TPanel* fo_gbItems;
	Vcl::Stdctrls::TCheckBox* fo_cbIBlobs;
	Vcl::Stdctrls::TCheckBox* fo_cbIDetails;
	Vcl::Stdctrls::TCheckBox* fo_cbIMeta;
	Vcl::Extctrls::TPanel* fo_gbCache;
	Vcl::Stdctrls::TCheckBox* fo_cbCBlobs;
	Vcl::Stdctrls::TCheckBox* fo_cbCDetails;
	Vcl::Stdctrls::TCheckBox* fo_cbCMeta;
	Vcl::Extctrls::TPanel* fo_GroupBox1;
	Vcl::Stdctrls::TLabel* fo_Label1;
	Vcl::Stdctrls::TLabel* fo_Label3;
	Vcl::Stdctrls::TLabel* fo_Label2;
	Vcl::Stdctrls::TEdit* fo_edtRecsMax;
	Vcl::Stdctrls::TEdit* fo_edtRowSetSize;
	Vcl::Stdctrls::TComboBox* fo_cbxMode;
	Vcl::Stdctrls::TCheckBox* fo_cbAutoClose;
	Vcl::Stdctrls::TLabel* fo_Label4;
	Vcl::Stdctrls::TComboBox* fo_cbxRecordCountMode;
	Vcl::Stdctrls::TCheckBox* fo_cbUnidirectional;
	Vcl::Stdctrls::TLabel* Label1;
	Vcl::Stdctrls::TComboBox* fo_cbxCursor;
	Vcl::Stdctrls::TComboBox* fo_cbxFetchAll;
	Vcl::Stdctrls::TLabel* fo_Label5;
	Vcl::Extctrls::TPanel* fo_gbMasterDetail;
	Vcl::Stdctrls::TLabel* Label2;
	Vcl::Stdctrls::TEdit* fo_edtDetailDelay;
	Vcl::Stdctrls::TCheckBox* fo_cbDetailOptimize;
	Vcl::Stdctrls::TCheckBox* fo_cbDetailCascade;
	Vcl::Extctrls::TPanel* fo_gbLiveDataWindow;
	Vcl::Stdctrls::TCheckBox* fo_cbLiveWindowParanoic;
	Vcl::Stdctrls::TCheckBox* fo_cbLiveWindowFastFirst;
	void __fastcall fo_Change(System::TObject* Sender);
	
private:
	System::Classes::TNotifyEvent FOnModified;
	bool FModifiedLocked;
	
public:
	void __fastcall LoadFrom(Firedac::Stan::Option::TFDFetchOptions* AOpts);
	void __fastcall SaveTo(Firedac::Stan::Option::TFDFetchOptions* AOpts);
	
__published:
	__property System::Classes::TNotifyEvent OnModified = {read=FOnModified, write=FOnModified};
public:
	/* TCustomFrame.Create */ inline __fastcall virtual TfrmFDGUIxFormsFetchOptions(System::Classes::TComponent* AOwner) : Vcl::Forms::TFrame(AOwner) { }
	
public:
	/* TScrollingWinControl.Destroy */ inline __fastcall virtual ~TfrmFDGUIxFormsFetchOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TfrmFDGUIxFormsFetchOptions(HWND ParentWindow) : Vcl::Forms::TFrame(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fetchoptions */
}	/* namespace Vclui */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_VCLUI_FETCHOPTIONS)
using namespace Firedac::Vclui::Fetchoptions;
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
#endif	// Firedac_Vclui_FetchoptionsHPP
