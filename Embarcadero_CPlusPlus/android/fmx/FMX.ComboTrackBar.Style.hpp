// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ComboTrackBar.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Combotrackbar_StyleHPP
#define Fmx_Combotrackbar_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.EditBox.Style.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.ComboTrackBar.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Combotrackbar
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledComboTrackBar;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledComboTrackBar : public Fmx::Editbox::Style::TStyledEditBox
{
	typedef Fmx::Editbox::Style::TStyledEditBox inherited;
	
private:
	bool FNeedSetFocusAfterButtonClick;
	Fmx::Controls::TControl* FArrowButton;
	Fmx::Controls::TPopup* FPopup;
	Fmx::Stdctrls::TTrackBar* FTrackBar;
	bool FValueChanged;
	bool FTextUpdating;
	HIDESBASE Fmx::Combotrackbar::TComboTrackBarModel* __fastcall GetModel();
	void __fastcall BeforeChangeProc(System::TObject* Sender);
	void __fastcall AfterChangeProc(System::TObject* Sender);
	void __fastcall ClosePopupProc(System::TObject* Sender);
	
protected:
	HIDESBASE MESSAGE void __fastcall MMValueRangeChanged(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMDropDown(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMCloseDropDown(System::TDispatchMessage &AMessage);
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall DoEnter();
	virtual void __fastcall DoExit();
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall Change();
	virtual void __fastcall SetText(const System::UnicodeString AValue);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoComboMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float x, float Y);
	virtual void __fastcall ActionChange(System::Classes::TBasicAction* Sender, bool CheckDefaults);
	virtual void __fastcall DoAbsoluteChanged();
	virtual void __fastcall DoActionClientChanged();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__fastcall virtual TStyledComboTrackBar(System::Classes::TComponent* AOwner)/* overload */;
	bool __fastcall CanDropDown(const System::Uitypes::TMouseButton AButton, const System::Classes::TShiftState AShift);
	void __fastcall DropDown();
	void __fastcall CloseDropDown();
	__property Fmx::Combotrackbar::TComboTrackBarModel* Model = {read=GetModel};
	__property Fmx::Stdctrls::TTrackBar* TrackBar = {read=FTrackBar, write=FTrackBar};
public:
	/* TStyledEdit.Destroy */ inline __fastcall virtual ~TStyledComboTrackBar() { }
	
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledComboTrackBar(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Editbox::Style::TStyledEditBox(AOwner, AModel, AControl) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Combotrackbar */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_COMBOTRACKBAR_STYLE)
using namespace Fmx::Combotrackbar::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_COMBOTRACKBAR)
using namespace Fmx::Combotrackbar;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Combotrackbar_StyleHPP
