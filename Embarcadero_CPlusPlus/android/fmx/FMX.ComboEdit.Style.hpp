// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ComboEdit.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Comboedit_StyleHPP
#define Fmx_Comboedit_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.ComboEdit.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.Pickers.hpp>
#include <FMX.ListBox.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Comboedit
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TComboEditListBox;
class DELPHICLASS TStyledComboEditBase;
class DELPHICLASS TStyledComboEdit;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TComboEditListBox : public Fmx::Listbox::TCustomListBox
{
	typedef Fmx::Listbox::TCustomListBox inherited;
	
private:
	TStyledComboEdit* FStyledComboEdit;
	Fmx::Comboedit::TComboEditModel* FModel;
	bool FInKeyDown;
	void __fastcall HandleStringsChanged(const System::UnicodeString S, const Fmx::Listbox::TCustomListBox::TStringsChangeOp Op);
	
protected:
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual System::Classes::TObservers* __fastcall GetObservers();
	__property Fmx::Comboedit::TComboEditModel* Model = {read=FModel, write=FModel};
	
public:
	__fastcall virtual TComboEditListBox(System::Classes::TComponent* AOwner)/* overload */;
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
public:
	/* TCustomListBox.Destroy */ inline __fastcall virtual ~TComboEditListBox() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledComboEditBase : public Fmx::Edit::Style::TStyledEdit
{
	typedef Fmx::Edit::Style::TStyledEdit inherited;
	
private:
	bool FNeedSetFocusAfterButtonClick;
	Fmx::Controls::TControl* FArrowButton;
	
protected:
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	__property Fmx::Controls::TControl* ArrowButton = {read=FArrowButton};
	MESSAGE void __fastcall PMDropDown(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMCloseDropDown(System::TDispatchMessage &AMessage);
	virtual void __fastcall Change();
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoComboMouseDown(System::TObject* Sender, System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float x, float Y);
	virtual bool __fastcall CanDropDown(const System::Uitypes::TMouseButton AButton, const System::Classes::TShiftState AShift);
	virtual void __fastcall DropDown() = 0 ;
	virtual void __fastcall CloseDropDown() = 0 ;
	
public:
	__fastcall virtual TStyledComboEditBase(System::Classes::TComponent* AOwner)/* overload */;
public:
	/* TStyledEdit.Destroy */ inline __fastcall virtual ~TStyledComboEditBase() { }
	
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledComboEditBase(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Edit::Style::TStyledEdit(AOwner, AModel, AControl) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledComboEdit : public TStyledComboEditBase
{
	typedef TStyledComboEditBase inherited;
	
	
private:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TStateInfo
	{
	public:
		bool Saved;
		int ItemIndex;
		System::UnicodeString Text;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
private:
	Fmx::Controls::TPopup* FPopup;
	TComboEditListBox* FListBox;
	Fmx::Pickers::TCustomListPicker* FListPicker;
	TStateInfo FSavedState;
	Fmx::Comboedit::TCustomComboEdit* __fastcall GetComboEdit();
	void __fastcall RebuildList();
	void __fastcall RefreshSelectedItem();
	HIDESBASE Fmx::Comboedit::TComboEditModel* __fastcall GetModel();
	void __fastcall DoOnValueChangedFromDropDownList(System::TObject* Sender, const int AValueIndex);
	void __fastcall DoPopup(System::TObject* Sender);
	void __fastcall DoClosePopup(System::TObject* Sender);
	
protected:
	MESSAGE void __fastcall MMItemIndexChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMItemHeightChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMItemWidthChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMItemsChanged(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	virtual void __fastcall DoAbsoluteChanged();
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual TComboEditListBox* __fastcall CreateListBox();
	virtual void __fastcall DoRealign();
	virtual void __fastcall DoExit();
	void __fastcall SaveState();
	void __fastcall RestoreState();
	virtual void __fastcall InitPicker(Fmx::Pickers::TCustomListPicker* AListPicker);
	virtual void __fastcall RecalculatePopupSize();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__fastcall virtual TStyledComboEdit(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TStyledComboEdit();
	virtual void __fastcall DropDown();
	virtual void __fastcall CloseDropDown();
	void __fastcall Clear();
	__property Fmx::Comboedit::TCustomComboEdit* ComboEdit = {read=GetComboEdit};
	__property Fmx::Comboedit::TComboEditModel* Model = {read=GetModel};
	__property TComboEditListBox* ListBox = {read=FListBox};
	__property Fmx::Pickers::TCustomListPicker* ListPicker = {read=FListPicker};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledComboEdit(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : TStyledComboEditBase(AOwner, AModel, AControl) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Comboedit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_COMBOEDIT_STYLE)
using namespace Fmx::Comboedit::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_COMBOEDIT)
using namespace Fmx::Comboedit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Comboedit_StyleHPP
