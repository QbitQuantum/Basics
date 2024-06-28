// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeEmfOptions.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeemfoptionsHPP
#define Vcltee_TeeemfoptionsHPP

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
#include <System.Types.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeeExport.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeemfoptions
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMFExportFormat;
class DELPHICLASS TEMFOptions;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TEMFExportFormat : public Vcltee::Teeexport::TTeeExportFormat
{
	typedef Vcltee::Teeexport::TTeeExportFormat inherited;
	
private:
	TEMFOptions* FProperties;
	bool __fastcall GetEnhanced();
	void __fastcall SetEnhanced(const bool Value);
	
protected:
	virtual void __fastcall DoCopyToClipboard();
	virtual int __fastcall FileFilterIndex();
	virtual void __fastcall IncFileFilterIndex(int &FilterIndex);
	virtual bool __fastcall WantsFilterIndex(int Index);
	
public:
	virtual System::UnicodeString __fastcall Description();
	virtual System::UnicodeString __fastcall FileExtension();
	__classmethod virtual System::UnicodeString __fastcall FileFilter();
	virtual Vcl::Graphics::TGraphicClass __fastcall GraphicClass();
	Vcl::Graphics::TMetafile* __fastcall Metafile();
	virtual Vcl::Forms::TForm* __fastcall Options(bool Check = true);
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream)/* overload */;
	__property bool Enhanced = {read=GetEnhanced, write=SetEnhanced, nodefault};
public:
	/* TTeeExportFormat.Create */ inline __fastcall virtual TEMFExportFormat() : Vcltee::Teeexport::TTeeExportFormat() { }
	/* TTeeExportFormat.Destroy */ inline __fastcall virtual ~TEMFExportFormat() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  SaveToStream(System::Classes::TStream* Stream, Vcl::Forms::TForm* const AOptions){ Vcltee::Teeexport::TTeeExportFormat::SaveToStream(Stream, AOptions); }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TEMFOptions : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TCheckBox* CBEnhanced;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Extctrls::TImage* ImagePreview;
	void __fastcall CBEnhancedClick(System::TObject* Sender);
	void __fastcall FormShow(System::TObject* Sender);
	
private:
	TEMFExportFormat* IFormat;
	void __fastcall Preview();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TEMFOptions(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TEMFOptions(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TEMFOptions() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TEMFOptions(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeemfoptions */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEEMFOPTIONS)
using namespace Vcltee::Teeemfoptions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeemfoptionsHPP
