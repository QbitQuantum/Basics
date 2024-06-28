// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Memo.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Memo_IosHPP
#define Fmx_Memo_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>
#include <System.TypInfo.hpp>
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <FMX.ScrollBox.iOS.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Text.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Memo
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXUITextView;
typedef System::DelphiInterface<IFMXUITextView> _di_IFMXUITextView;
class DELPHICLASS TiOSNativeMemo;
class DELPHICLASS TiOSTextViewDelegate;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{F24D110A-BDC7-4653-94E1-4FF6305FCAC0}") IFMXUITextView  : public Iosapi::Uikit::UITextView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	virtual void __cdecl HandlePan(Iosapi::Uikit::_di_UIPanGestureRecognizer gestureRecognizer) = 0 ;
	HIDESBASE virtual bool __cdecl gestureRecognizerShouldBegin(Iosapi::Uikit::_di_UIGestureRecognizer gestureRecognizer) = 0 ;
	HIDESBASE virtual bool __cdecl canBecomeFirstResponder() = 0 ;
};

class PASCALIMPLEMENTATION TiOSNativeMemo : public Fmx::Scrollbox::Ios::TiOSScrollBox
{
	typedef Fmx::Scrollbox::Ios::TiOSScrollBox inherited;
	
private:
	Iosapi::Uikit::_di_UIColor FDefaultBackgroundColor;
	Iosapi::Foundation::_di_NSMutableAttributedString FAttributedString;
	HIDESBASE Fmx::Memo::TCustomMemoModel* __fastcall GetModel();
	Fmx::Memo::TCustomMemo* __fastcall GetMemo();
	HIDESBASE Iosapi::Uikit::_di_UITextView __fastcall GetView();
	void __fastcall ShowCaret();
	void __fastcall HideCaret();
	
protected:
	void __fastcall UpdateTextSettings();
	void __fastcall UpdateTextSelection();
	virtual Fmx::Scrollbox::Ios::TiOSScrollBoxDelegate* __fastcall CreateDelegate();
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	MESSAGE void __fastcall MMCaretChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::TCaret*> &AMessage);
	MESSAGE void __fastcall MMCheckSpellingChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMDataDetectoTypes(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TDataDetectorTypes> &AMessage);
	MESSAGE void __fastcall MMKeyboardTypeChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TVirtualKeyboardType> &AMessage);
	MESSAGE void __fastcall MMLinesChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMReadOnlyChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMSelStartChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMSelLengthChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMCaretPositionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Text::TCaretPosition> &AMessage);
	MESSAGE void __fastcall MMLinesClear(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMAbsoluteChanged(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMDoEnter(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSetStyleLookup(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	HIDESBASE MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	HIDESBASE MESSAGE void __fastcall PMSetClipChildren(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMGoToLineBegin(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMGoToLineEnd(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSelectText(System::TDispatchMessage &AMessage);
	
public:
	__fastcall virtual TiOSNativeMemo()/* overload */;
	__fastcall virtual ~TiOSNativeMemo();
	void __fastcall Clear();
	bool __cdecl canBecomeFirstResponder();
	virtual void __fastcall SetFocus();
	virtual void __fastcall ResetFocus();
	__property Fmx::Memo::TCustomMemoModel* Model = {read=GetModel};
	__property Fmx::Memo::TCustomMemo* Memo = {read=GetMemo};
	__property Iosapi::Uikit::_di_UITextView View = {read=GetView};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSNativeMemo(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Scrollbox::Ios::TiOSScrollBox(AModel, AControl) { }
	
};


class PASCALIMPLEMENTATION TiOSTextViewDelegate : public Fmx::Scrollbox::Ios::TiOSScrollBoxDelegate
{
	typedef Fmx::Scrollbox::Ios::TiOSScrollBoxDelegate inherited;
	
private:
	TiOSNativeMemo* FNativeMemo;
	bool FSkipEditing;
	
public:
	__fastcall TiOSTextViewDelegate(TiOSNativeMemo* const ANativeMemo);
	void __cdecl textViewDidBeginEditing(Iosapi::Uikit::_di_UITextView textView);
	void __cdecl textViewDidChange(Iosapi::Uikit::_di_UITextView textView);
	void __cdecl textViewDidChangeSelection(Iosapi::Uikit::_di_UITextView textView);
	void __cdecl textViewDidEndEditing(Iosapi::Uikit::_di_UITextView textView);
	bool __cdecl textViewShouldBeginEditing(Iosapi::Uikit::_di_UITextView textView);
	bool __cdecl textViewShouldEndEditing(Iosapi::Uikit::_di_UITextView textView);
	bool __cdecl textViewShouldChangeTextInRangeReplacementText(Iosapi::Uikit::_di_UITextView textView, Iosapi::Foundation::NSRange shouldChangeTextInRange, Iosapi::Foundation::_di_NSString replacementText);
	bool __cdecl textViewShouldInteractWithURLInRange(Iosapi::Uikit::_di_UITextView textView, Iosapi::Foundation::_di_NSURL shouldInteractWithURL, Iosapi::Foundation::NSRange inRange);
	bool __cdecl textViewShouldInteractWithTextAttachmentInRange(Iosapi::Uikit::_di_UITextView textView, Iosapi::Uikit::_di_NSTextAttachment shouldInteractWithTextAttachment, Iosapi::Foundation::NSRange inRange);
public:
	/* TOCLocal.Destroy */ inline __fastcall virtual ~TiOSTextViewDelegate() { }
	
private:
	void *__UITextViewDelegate;	// Iosapi::Uikit::UITextViewDelegate 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {D22276B3-5E9C-49F4-8A63-0062F9221EC2}
	operator Iosapi::Uikit::_di_UITextViewDelegate()
	{
		Iosapi::Uikit::_di_UITextViewDelegate intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Iosapi::Uikit::UITextViewDelegate*(void) { return (Iosapi::Uikit::UITextViewDelegate*)&__UITextViewDelegate; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Memo */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEMO_IOS)
using namespace Fmx::Memo::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEMO)
using namespace Fmx::Memo;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Memo_IosHPP
