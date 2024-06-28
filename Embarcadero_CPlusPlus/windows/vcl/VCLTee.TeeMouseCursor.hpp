// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'VCLTee.TeeMouseCursor.pas' rev: 34.00 (Windows)

#ifndef Vcltee_TeemousecursorHPP
#define Vcltee_TeemousecursorHPP

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
#include <VCLTee.TeeProcs.hpp>
#include <VCLTee.TeCanvas.hpp>
#include <System.UITypes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Vcltee
{
namespace Teemousecursor
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMouseCursorEdit;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMouseCursorEdit : public Vcl::Forms::TForm
{
	typedef Vcl::Forms::TForm inherited;
	
__published:
	Vcl::Stdctrls::TLabel* Label6;
	Vcltee::Tecanvas::TComboFlat* CBCursor;
	Vcl::Stdctrls::TGroupBox* GroupBox1;
	Vcl::Extctrls::TImage* ImageCursor;
	Vcl::Stdctrls::TButton* BLoad;
	Vcl::Dialogs::TOpenDialog* OpenDialog1;
	void __fastcall FormShow(System::TObject* Sender);
	void __fastcall CBCursorChange(System::TObject* Sender);
	void __fastcall BLoadClick(System::TObject* Sender);
	
private:
	System::Classes::TNotifyEvent FOnChange;
	void __fastcall ChangeCursor(System::Uitypes::TCursor ACursor);
	
public:
	System::Uitypes::TCursor TheCursor;
	System::Classes::TComponent* TheComponent;
	__classmethod System::Uitypes::TCursor __fastcall Choose(System::Classes::TComponent* const AOwner, System::Uitypes::TCursor ACursor);
	__classmethod void __fastcall SetComboCursor(Vcltee::Tecanvas::TComboFlat* const ACombo, System::Uitypes::TCursor ACursor);
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
public:
	/* TCustomForm.Create */ inline __fastcall virtual TMouseCursorEdit(System::Classes::TComponent* AOwner) : Vcl::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TMouseCursorEdit(System::Classes::TComponent* AOwner, int Dummy) : Vcl::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TMouseCursorEdit() { }
	
public:
	/* TWinControl.CreateParented */ inline __fastcall TMouseCursorEdit(HWND ParentWindow) : Vcl::Forms::TForm(ParentWindow) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall TeeIdentToCursor(const System::UnicodeString AName, /* out */ int &ACursor);
extern DELPHI_PACKAGE System::Uitypes::TCursor __fastcall TeeSetCursor(System::Uitypes::TCursor ACursor, const System::UnicodeString S);
extern DELPHI_PACKAGE bool __fastcall TeeCursorToIdent(int ACursor, /* out */ System::UnicodeString &AName);
extern DELPHI_PACKAGE void __fastcall TeeFillCursors(Vcltee::Tecanvas::TComboFlat* const ACombo, System::Uitypes::TCursor ACursor);
extern DELPHI_PACKAGE void __fastcall TeePreviewCursor(const System::Uitypes::TCursor ACursor, Vcl::Graphics::TPicture* const APicture);
}	/* namespace Teemousecursor */
}	/* namespace Vcltee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE_TEEMOUSECURSOR)
using namespace Vcltee::Teemousecursor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_VCLTEE)
using namespace Vcltee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Vcltee_TeemousecursorHPP
