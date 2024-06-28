// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Edit.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Edit_IosHPP
#define Fmx_Edit_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <Macapi.ObjCRuntime.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Edit
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXTextField;
typedef System::DelphiInterface<IFMXTextField> _di_IFMXTextField;
class DELPHICLASS TiOSNativeEdit;
class DELPHICLASS TiOSTextFieldDelegate;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{E0EA93B8-E2B2-4B02-A832-FAAC42AEA154}") IFMXTextField  : public Iosapi::Uikit::UITextField 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	virtual void __cdecl ControlEventEditingChanged() = 0 ;
	virtual void __cdecl ControlEventEditingDidEnd() = 0 ;
	HIDESBASE virtual bool __cdecl canBecomeFirstResponder() = 0 ;
	HIDESBASE virtual bool __cdecl canPerformAction(void * action, void * withSender) = 0 ;
};

class PASCALIMPLEMENTATION TiOSNativeEdit : public Fmx::Presentation::Ios::TiOSNativeControl
{
	typedef Fmx::Presentation::Ios::TiOSNativeControl inherited;
	
private:
	TiOSTextFieldDelegate* FTextFieldDelegate;
	bool FSavedButtomsContentVisible;
	Iosapi::Foundation::NSRange FPreviousSelection;
	Iosapi::Foundation::_di_NSMutableAttributedString FAttributedString;
	Fmx::Edit::TCustomEdit* __fastcall GetEdit();
	HIDESBASE Iosapi::Uikit::_di_UITextField __fastcall GetView();
	HIDESBASE Fmx::Edit::TCustomEditModel* __fastcall GetModel();
	void __fastcall ShowCaret();
	void __fastcall HideCaret();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	void __fastcall UpdateTextSettings();
	void __fastcall UpdateCaretColor();
	void __fastcall UpdateSelection();
	void __fastcall UpdateVisibleOfClearButton();
	void __fastcall UpdateSpellChecking();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	void __fastcall UpdateTextInField();
	MESSAGE void __fastcall MMCheckSpellingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMTextPromptChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall MMIsPasswordChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMKeyboardTypeChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TVirtualKeyboardType> &AMessage);
	MESSAGE void __fastcall MMReturnKeyTypeChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TReturnKeyType> &AMessage);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMEditButtonsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMTextChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMCaretPositionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMCaretChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMSelStartChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall MMSelLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMUnload(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMAbsoluteChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSetStyleLookup(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	HIDESBASE MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	
public:
	__fastcall virtual TiOSNativeEdit()/* overload */;
	__fastcall virtual ~TiOSNativeEdit();
	void __cdecl ControlEventEditingChanged();
	void __cdecl ControlEventEditingDidEnd();
	virtual void __fastcall SelectionChanged();
	bool __cdecl canPerformAction(void * action, void * withSender);
	bool __cdecl canBecomeFirstResponder();
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	Iosapi::Foundation::NSRange __fastcall SelectedRange();
	__property Fmx::Edit::TCustomEdit* Edit = {read=GetEdit};
	__property Fmx::Edit::TCustomEditModel* Model = {read=GetModel};
	__property Iosapi::Uikit::_di_UITextField View = {read=GetView};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSNativeEdit(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Ios::TiOSNativeControl(AModel, AControl) { }
	
};


class PASCALIMPLEMENTATION TiOSTextFieldDelegate : public Macapi::Objectivec::TOCLocal
{
	typedef Macapi::Objectivec::TOCLocal inherited;
	
private:
	TiOSNativeEdit* FNativeEdit;
	bool FSkipEditing;
	
public:
	__fastcall TiOSTextFieldDelegate(TiOSNativeEdit* const ANativeEdit);
	bool __cdecl textField(Iosapi::Uikit::_di_UITextField textField, Iosapi::Foundation::NSRange shouldChangeCharactersInRange, Iosapi::Foundation::_di_NSString replacementString);
	void __cdecl textFieldDidBeginEditing(Iosapi::Uikit::_di_UITextField textField);
	void __cdecl textFieldDidEndEditing(Iosapi::Uikit::_di_UITextField textField);
	bool __cdecl textFieldShouldBeginEditing(Iosapi::Uikit::_di_UITextField textField);
	bool __cdecl textFieldShouldClear(Iosapi::Uikit::_di_UITextField textField);
	bool __cdecl textFieldShouldEndEditing(Iosapi::Uikit::_di_UITextField textField);
	bool __cdecl textFieldShouldReturn(Iosapi::Uikit::_di_UITextField textField);
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TiOSTextFieldDelegate() { }
	
private:
	void *__UITextFieldDelegate;	// Iosapi::Uikit::UITextFieldDelegate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {B76C73F8-2740-4580-9987-A040C245441A}
	operator Iosapi::Uikit::_di_UITextFieldDelegate()
	{
		Iosapi::Uikit::_di_UITextFieldDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Iosapi::Uikit::UITextFieldDelegate*(void) { return (Iosapi::Uikit::UITextFieldDelegate*)&__UITextFieldDelegate; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Edit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT_IOS)
using namespace Fmx::Edit::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT)
using namespace Fmx::Edit;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Edit_IosHPP
