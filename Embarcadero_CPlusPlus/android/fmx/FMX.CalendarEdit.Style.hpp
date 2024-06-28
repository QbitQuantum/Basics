// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.CalendarEdit.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Calendaredit_StyleHPP
#define Fmx_Calendaredit_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.ComboEdit.Style.hpp>
#include <FMX.Pickers.hpp>
#include <FMX.CalendarEdit.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Calendaredit
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledCalendarEdit;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledCalendarEdit : public Fmx::Comboedit::Style::TStyledComboEdit
{
	typedef Fmx::Comboedit::Style::TStyledComboEdit inherited;
	
private:
	Fmx::Pickers::TCustomDateTimePicker* FDateTimePicker;
	HIDESBASE Fmx::Calendaredit::TCalendarEditModel* __fastcall GetModel();
	
protected:
	MESSAGE void __fastcall MMDateTimeChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMClosePicker(System::TDispatchMessage &AMessage);
	virtual void __fastcall DoDateChanged(System::TObject* Sender, const System::TDateTime ADate);
	virtual void __fastcall DoPopupClose(System::TObject* Sender);
	HIDESBASE virtual void __fastcall DoPopup(System::TObject* Sender);
	virtual void __fastcall DoExit();
	void __fastcall SetInputSupport(const bool Value);
	virtual void __fastcall Change();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__fastcall virtual TStyledCalendarEdit(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledCalendarEdit();
	virtual void __fastcall DropDown();
	void __fastcall ClosePicker();
	bool __fastcall HasPicker();
	__property Fmx::Calendaredit::TCalendarEditModel* Model = {read=GetModel};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledCalendarEdit(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Comboedit::Style::TStyledComboEdit(AOwner, AModel, AControl) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Calendaredit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAREDIT_STYLE)
using namespace Fmx::Calendaredit::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_CALENDAREDIT)
using namespace Fmx::Calendaredit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Calendaredit_StyleHPP
