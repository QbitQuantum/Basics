// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'GUITesting.pas' rev: 34.00 (Windows)

#ifndef GuitestingHPP
#define GuitestingHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <TestFramework.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Messages.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.Forms.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Guitesting
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TGUITestCase;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TGUITestCase : public Testframework::TTestCase
{
	typedef Testframework::TTestCase inherited;
	
public:
	__fastcall virtual TGUITestCase(System::UnicodeString MethodName)/* overload */;
	__fastcall virtual ~TGUITestCase();
	virtual void __fastcall TearDown();
	
protected:
	Vcl::Controls::TControl* FGUI;
	int FActionDelay;
	Vcl::Controls::TControl* __fastcall FindControl(System::Classes::TComponent* Comp, const System::UnicodeString CtlName, void * Addrs = (void *)(0x0))/* overload */;
	Vcl::Controls::TControl* __fastcall FindControl(const System::UnicodeString AName, void * Addrs = (void *)(0x0))/* overload */;
	Vcl::Controls::TWinControl* __fastcall FindParentWinControl(Vcl::Controls::TControl* Control);
	void __fastcall SetKeyboardStateDown(Vcl::Controls::TWinControl* pControl, System::Classes::TShiftState pShiftState);
	void __fastcall SetKeyboardStateUp(Vcl::Controls::TWinControl* pControl, System::Classes::TShiftState pShiftState);
	void __fastcall ClickLeftMouseButtonOn(Vcl::Controls::TControl* Control);
	void __fastcall Click()/* overload */;
	void __fastcall Click(System::UnicodeString ControlName)/* overload */;
	void __fastcall Click(Vcl::Controls::TControl* control)/* overload */;
	void __fastcall EnterKey(System::Word Key, const System::Classes::TShiftState ShiftState = System::Classes::TShiftState() )/* overload */;
	void __fastcall EnterKeyInto(Vcl::Controls::TControl* Control, System::Word Key, const System::Classes::TShiftState ShiftState = System::Classes::TShiftState() )/* overload */;
	void __fastcall EnterKeyInto(System::UnicodeString ControlName, System::Word Key, const System::Classes::TShiftState ShiftState = System::Classes::TShiftState() )/* overload */;
	void __fastcall EnterKey(System::WideChar Key, const System::Classes::TShiftState ShiftState = System::Classes::TShiftState() )/* overload */;
	void __fastcall EnterKeyInto(Vcl::Controls::TControl* Control, System::WideChar Key, const System::Classes::TShiftState ShiftState = System::Classes::TShiftState() )/* overload */;
	void __fastcall EnterKeyInto(System::UnicodeString ControlName, System::WideChar Key, const System::Classes::TShiftState ShiftState = System::Classes::TShiftState() )/* overload */;
	void __fastcall EnterText(System::UnicodeString Text);
	void __fastcall EnterTextInto(Vcl::Controls::TControl* Control, System::UnicodeString Text)/* overload */;
	void __fastcall EnterTextInto(System::UnicodeString ControlName, System::UnicodeString Text)/* overload */;
	void __fastcall Show(bool OnOff = true)/* overload */;
	void __fastcall Show(Vcl::Controls::TControl* Control, bool OnOff = true)/* overload */;
	void __fastcall Show(System::UnicodeString ControlName, bool OnOff = true)/* overload */;
	void __fastcall Hide()/* overload */;
	void __fastcall Hide(Vcl::Controls::TControl* Control)/* overload */;
	void __fastcall Hide(System::UnicodeString ControlName)/* overload */;
	void __fastcall Tab(int n = 0x1);
	void __fastcall CheckTabTo(Vcl::Controls::TControl* Control, void * Addrs = (void *)(0x0))/* overload */;
	void __fastcall CheckTabTo(System::UnicodeString ControlName)/* overload */;
	Vcl::Controls::TControl* __fastcall GetFocused();
	bool __fastcall IsFocused(Vcl::Controls::TControl* Control);
	void __fastcall SetFocus(Vcl::Controls::TControl* Control, void * Addrs = (void *)(0x0))/* overload */;
	void __fastcall SetFocus(System::UnicodeString ControlName)/* overload */;
	void __fastcall CheckFocused(Vcl::Controls::TControl* Control, void * Addrs = (void *)(0x0))/* overload */;
	void __fastcall CheckFocused(System::UnicodeString ControlName)/* overload */;
	void __fastcall CheckEnabled(Vcl::Controls::TControl* Control, void * Addrs = (void *)(0x0))/* overload */;
	void __fastcall CheckEnabled(System::UnicodeString ControlName)/* overload */;
	void __fastcall CheckVisible(Vcl::Controls::TControl* Control, void * Addrs = (void *)(0x0))/* overload */;
	void __fastcall CheckVisible(System::UnicodeString ControlName)/* overload */;
	void __fastcall CheckVisible()/* overload */;
	__property Vcl::Controls::TControl* GUI = {read=FGUI, write=FGUI};
	__property int ActionDelay = {read=FActionDelay, write=FActionDelay, nodefault};
public:
	/* TTestCase.Create */ inline __fastcall virtual TGUITestCase(System::UnicodeString MethodName, __int64 RunCount)/* overload */ : Testframework::TTestCase(MethodName, RunCount) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::UnicodeString rcs_id;
}	/* namespace Guitesting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_GUITESTING)
using namespace Guitesting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// GuitestingHPP
