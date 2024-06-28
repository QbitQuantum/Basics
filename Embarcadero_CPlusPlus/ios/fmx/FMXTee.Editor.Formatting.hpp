// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMXTee.Editor.Formatting.pas' rev: 34.00 (iOS)

#ifndef Fmxtee_Editor_FormattingHPP
#define Fmxtee_Editor_FormattingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Variants.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Dialogs.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmxtee
{
namespace Editor
{
namespace Formatting
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFormatEditor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TFormatEditor : public Fmx::Forms::TForm
{
	typedef Fmx::Forms::TForm inherited;
	
__published:
	Fmx::Stdctrls::TPanel* PanelOK;
	Fmx::Stdctrls::TButton* Button1;
	Fmx::Stdctrls::TButton* Button2;
	Fmx::Stdctrls::TGroupBox* GroupBox1;
	Fmx::Comboedit::TComboEdit* CBCustom;
	Fmx::Comboedit::TComboEdit* CBDate;
	Fmx::Stdctrls::TRadioButton* RBDate;
	Fmx::Stdctrls::TRadioButton* RBCustom;
	Fmx::Stdctrls::TRadioButton* RBGeo;
	Fmx::Comboedit::TComboEdit* CBGeo;
	Fmx::Stdctrls::TPanel* Panel2;
	Fmx::Stdctrls::TLabel* Label1;
	Fmx::Stdctrls::TLabel* Label2;
	Fmx::Stdctrls::TRadioButton* RBInteger;
	Fmx::Stdctrls::TCheckBox* CBPercent;
	Fmx::Stdctrls::TCheckBox* CBThousands;
	Fmx::Stdctrls::TCheckBox* CBCurrency;
	Fmx::Stdctrls::TCheckBox* CBFixedDecimals;
	Fmx::Spinbox::TSpinBox* UpDown1;
	Fmx::Spinbox::TSpinBox* UpDown2;
	void __fastcall FormCreate(System::TObject* Sender);
	void __fastcall CBCustomChange(System::TObject* Sender);
	void __fastcall CBDateChange(System::TObject* Sender);
	void __fastcall RadioGroup1Click(System::TObject* Sender);
	void __fastcall CBGeoChange(System::TObject* Sender);
	void __fastcall RBIntegerChange(System::TObject* Sender);
	void __fastcall CBThousandsChange(System::TObject* Sender);
	void __fastcall CBPercentChange(System::TObject* Sender);
	void __fastcall RBDateChange(System::TObject* Sender);
	void __fastcall RBGeoChange(System::TObject* Sender);
	void __fastcall RBCustomChange(System::TObject* Sender);
	void __fastcall CBCurrencyChange(System::TObject* Sender);
	void __fastcall UpDown2Change(System::TObject* Sender);
	void __fastcall UpDown1Change(System::TObject* Sender);
	void __fastcall CBFixedDecimalsChange(System::TObject* Sender);
	void __fastcall CBGeoChangeTracking(System::TObject* Sender);
	void __fastcall CBDateChangeTracking(System::TObject* Sender);
	void __fastcall CBCustomChangeTracking(System::TObject* Sender);
	
private:
	System::UnicodeString Format;
	bool tmpChanging;
	void __fastcall AddDate(const System::UnicodeString S);
	void __fastcall AddGeo(const System::UnicodeString S);
	void __fastcall RefreshFormat(const System::UnicodeString AFormat);
	System::UnicodeString __fastcall TheFormat();
	
public:
	bool IsDate;
	bool IsGeo;
	__classmethod void __fastcall AddDefaultFormats(Fmx::Comboedit::TComboEdit* const AComboEdit);
	__classmethod System::UnicodeString __fastcall Change(System::Classes::TComponent* const AOwner, const System::UnicodeString AFormat, bool AllowDates = true);
public:
	/* TCustomForm.Create */ inline __fastcall virtual TFormatEditor(System::Classes::TComponent* AOwner) : Fmx::Forms::TForm(AOwner) { }
	/* TCustomForm.CreateNew */ inline __fastcall virtual TFormatEditor(System::Classes::TComponent* AOwner, NativeInt Dummy) : Fmx::Forms::TForm(AOwner, Dummy) { }
	/* TCustomForm.Destroy */ inline __fastcall virtual ~TFormatEditor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Formatting */
}	/* namespace Editor */
}	/* namespace Fmxtee */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR_FORMATTING)
using namespace Fmxtee::Editor::Formatting;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE_EDITOR)
using namespace Fmxtee::Editor;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMXTEE)
using namespace Fmxtee;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmxtee_Editor_FormattingHPP
