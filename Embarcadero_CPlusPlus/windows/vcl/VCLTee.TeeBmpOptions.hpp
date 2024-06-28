// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeBmpOptions.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeebmpoptionsHPP
#define Vcltee_TeebmpoptionsHPP

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
#include <Vcl.Buttons.hpp>
#include <Vcl.ComCtrls.hpp>
#include <System.Types.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeExport.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeeFilters.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teebmpoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBMPOptions;
class DELPHICLASS TBMPExportFormat;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBMPOptions : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TCheckBox* CBMono;
	Vcl::Stdctrls::TLabel* Label1;
	Vcltee::Tecanvas::TComboFlat* CBColors;
	Vcl::Stdctrls::TButton* Button1;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcltee::Teefilters::TImageFiltered* ImageFiltered1;
	Vcl::Comctrls::TUpDown* UDDpi;
	Vcl::Stdctrls::TEdit* EDpi;
	Vcl::Stdctrls::TLabel* Label2;
	void __fastcall CBMonoClick(System::TObject* Sender);
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall Button1Click(System::TObject* Sender);
	void __fastcall CBColorsChange(System::TObject* Sender);
	
private:
	void __fastcall Preview();
	
protected:
	TBMPExportFormat* IFormat;
public:
	/* TCustomForm.Create */ inline __fastcall virtual TBMPOptions(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TBMPOptions(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TBMPOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TBMPOptions(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBMPExportFormat : public Vcltee::Teeexport::TTeeExportFormat
{
	typedef Vcltee::Teeexport::TTeeExportFormat inherited;
	
private:
	Vcltee::Tecanvas::TFilterItems* FFilters;
	TBMPOptions* FProperties;
	void __fastcall CheckProperties();
	Vcl::Graphics::TBitmap* __fastcall InternalGetBitmap();
	
protected:
	virtual void __fastcall DoCopyToClipboard();
	
public:
	__fastcall virtual TBMPExportFormat();
	__fastcall virtual ~TBMPExportFormat();
	Vcl::Graphics::TBitmap* __fastcall Bitmap(TBMPOptions* const AOptions);
	virtual System::UnicodeString __fastcall Description();
	virtual System::UnicodeString __fastcall FileExtension();
	__classmethod virtual System::UnicodeString __fastcall FileFilter();
	virtual Vcl::Graphics::TGraphicClass __fastcall GraphicClass();
	virtual Vcl::Forms::TForm* __fastcall Options(bool Check = true);
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream)/* overload */;
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream, Vcl::Forms::TForm* const AOptions)/* overload */;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall TeeSaveToBitmap(Vcltee::Teeprocs::TCustomTeePanel* APanel, const System::WideString FileName, const System::Types::TRect &R, int Dpi = 0x0);
}	/* namespace Teebmpoptions */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEBMPOPTIONS)
using namespace Vcltee::Teebmpoptions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeebmpoptionsHPP
