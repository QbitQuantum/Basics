// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeVisualsEditor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeevisualseditorHPP
#define Vcltee_TeevisualseditorHPP

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
#include <System.Variants.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeePenDlg.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teevisualseditor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TVisualsEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TVisualsEditor : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Extctrls::TPanel* Panel1;
	Vcl::Stdctrls::TButton* Button3;
	Vcl::Stdctrls::TButton* BClearVisual;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall Button3Click(System::TObject* Sender);
	void __fastcall BClearVisualClick(System::TObject* Sender);
	
private:
	Vcltee::Teengine::TVisualsList* Visuals;
	Vcltee::Tecanvas::TVisualEditor* IEditor;
	System::Classes::TNotifyEvent FOnChangedVisual;
	void __fastcall EnableClear();
	void __fastcall TemplateChanged(System::TObject* Sender);
	
public:
	__classmethod bool __fastcall ModalShow(System::Classes::TComponent* AOwner, Vcltee::Teengine::TVisualsList* AVisuals);
	__property System::Classes::TNotifyEvent OnChangedVisual = {read=FOnChangedVisual, write=FOnChangedVisual};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TVisualsEditor(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TVisualsEditor(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TVisualsEditor() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TVisualsEditor(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Teevisualseditor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEVISUALSEDITOR)
using namespace Vcltee::Teevisualseditor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeevisualseditorHPP
