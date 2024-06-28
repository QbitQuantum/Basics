// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeExport.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeexportHPP
#define Vcltee_TeexportHPP

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
#include <System.Types.hpp>
#include <Vcl.Graphics.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Dialogs.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.Buttons.hpp>
#include <VCLTee.TeeExport.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teexport
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTeeExportForm;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TTeeExportForm : public Vcltee::Teeexport::TTeeExportFormBase
{
	typedef Vcltee::Teeexport::TTeeExportFormBase inherited;
	
__published:
	Vcl::Comctrls::TTabSheet* TabDataFormat;
	Vcl::Stdctrls::TCheckBox* CBUseSeriesFormat;
	Vcl::Stdctrls::TLabel* Label5;
	Vcltee::Tecanvas::TComboFlat* SeriesValueFormat;
	Vcl::Buttons::TSpeedButton* BFormat;
	HIDESBASE void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBUseSeriesFormatClick(System::TObject* Sender);
	void __fastcall BFormatClick(System::TObject* Sender);
	HIDESBASE void __fastcall FormCreate(System::TObject* Sender);
	
private:
	HIDESBASE MESSAGE void __fastcall CMShowingChanged(Winapi::Messages::TMessage &Message);
	
protected:
	virtual Vcltee::Teeprocs::TTeeExportData* __fastcall CreateData();
	virtual System::Classes::TStream* __fastcall CreateNativeStream();
	virtual void __fastcall DoSaveNativeToFile(const System::UnicodeString FileName, bool IncludeData);
	virtual bool __fastcall ExistData();
	virtual void __fastcall PrepareOnShow();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TTeeExportForm(System::Classes::TComponent* AOwner) : Vcltee::Teeexport::TTeeExportFormBase(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TTeeExportForm(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teeexport::TTeeExportFormBase(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TTeeExportForm() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TTeeExportForm(HWND ParentWindow) : Vcltee::Teeexport::TTeeExportFormBase(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall TeeExport(System::Classes::TComponent* const AOwner, Vcltee::Teeprocs::TCustomTeePanel* const APanel, System::UnicodeString InitialDir = System::UnicodeString());
extern DELPHI_PACKAGE void __fastcall TeeSavePanel(Vcltee::Teeexport::TTeeExportFormatClass AFormat, Vcltee::Teeprocs::TCustomTeePanel* const APanel);
extern DELPHI_PACKAGE void __fastcall TeeEmailFile(const System::UnicodeString FileName, const System::UnicodeString Subject = L"TeeChart");
}	/* namespace Teexport */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEXPORT)
using namespace Vcltee::Teexport;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeexportHPP
