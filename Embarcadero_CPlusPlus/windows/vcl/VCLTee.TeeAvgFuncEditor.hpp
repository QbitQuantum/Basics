// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeAvgFuncEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeeavgfunceditorHPP
#define Vcltee_TeeavgfunceditorHPP

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
#include <VCLTee.TeeEdiPeri.hpp>
#include <VCLTee.TeCanvas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teeavgfunceditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAverageFuncEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAverageFuncEditor : public Vcltee::Teeediperi::TTeeFunctionEditor
{
	typedef Vcltee::Teeediperi::TTeeFunctionEditor inherited;
	
__published:
	Vcl::Stdctrls::TCheckBox* CBNulls;
	void __fastcall CBNullsClick(System::TObject* Sender);
	
protected:
	virtual void __fastcall ApplyFormChanges();
	virtual void __fastcall SetFunction();
public:
	/* TCustomForm.Create */ inline __fastcall virtual TAverageFuncEditor(System::Classes::TComponent* AOwner) : Vcltee::Teeediperi::TTeeFunctionEditor(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TAverageFuncEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcltee::Teeediperi::TTeeFunctionEditor(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TAverageFuncEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TAverageFuncEditor(HWND ParentWindow) : Vcltee::Teeediperi::TTeeFunctionEditor(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teeavgfunceditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEAVGFUNCEDITOR)
using namespace Vcltee::Teeavgfunceditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeeavgfunceditorHPP
