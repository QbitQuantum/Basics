// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.SpinBox.Style.pas' rev: 34.00 (iOS)

#ifndef Fmx_Spinbox_StyleHPP
#define Fmx_Spinbox_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.EditBox.Style.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.SpinBox.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Spinbox
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledSpinBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStyledSpinBox : public Fmx::Editbox::Style::TStyledEditBox
{
	typedef Fmx::Editbox::Style::TStyledEditBox inherited;
	
private:
	bool FCanFocusOnPlusMinus;
	Fmx::Stdctrls::TCustomButton* FMinus;
	Fmx::Stdctrls::TCustomButton* FPlus;
	void __fastcall MinusClick(System::TObject* Sender);
	void __fastcall PlusClick(System::TObject* Sender);
	HIDESBASE Fmx::Spinbox::TSpinBoxModel* __fastcall GetModel();
	void __fastcall ButtonClick(bool APlus);
	
protected:
	MESSAGE void __fastcall MMRepeatClickChanged(System::TDispatchMessage &AMessage);
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	
public:
	__fastcall virtual TStyledSpinBox(System::Classes::TComponent* AOwner)/* overload */;
	__property Fmx::Spinbox::TSpinBoxModel* Model = {read=GetModel};
public:
	/* TStyledEdit.Destroy */ inline __fastcall virtual ~TStyledSpinBox() { }
	
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledSpinBox(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Editbox::Style::TStyledEditBox(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Spinbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SPINBOX_STYLE)
using namespace Fmx::Spinbox::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SPINBOX)
using namespace Fmx::Spinbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Spinbox_StyleHPP
