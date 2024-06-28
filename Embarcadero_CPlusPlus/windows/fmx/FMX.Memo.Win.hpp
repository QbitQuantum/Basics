// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Memo.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Memo_WinHPP
#define Fmx_Memo_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <Winapi.Windows.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Presentation.Win.hpp>
#include <Winapi.Messages.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Win.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Text.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Memo
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinNativeMemo;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWinNativeMemo : public Fmx::Presentation::Win::TWinPresentation
{
	typedef Fmx::Presentation::Win::TWinPresentation inherited;
	
private:
	Fmx::Memo::TCustomMemoModel* FModel;
	HFONT FFontHandle;
	Fmx::Memo::TCustomMemo* __fastcall GetMemo();
	void __fastcall UpdateTextSettings();
	void __fastcall CopyModelToNative();
	void __fastcall CopyNativeToModel();
	void __fastcall SetReadOnly();
	void __fastcall SetMaxLength();
	void __fastcall SetSelStart();
	void __fastcall SetSelLength();
	void __fastcall RecreateFont();
	void __fastcall DeleteFont();
	
protected:
	virtual void __fastcall CreateHandle();
	virtual void __fastcall DestroyHandle();
	virtual void __fastcall CreateParams(Fmx::Controls::Win::TCreateParams &Params);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall UpdateScrollBarsVisibility();
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMReadOnly(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMGetCaretPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Text::TCaretPosition> &AMessage);
	MESSAGE void __fastcall MMSetCaretPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Text::TCaretPosition> &AMessage);
	MESSAGE void __fastcall MMMaxLengthChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMLinesInsertLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesPutLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesDeleteLine(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesExchangeLines(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Memo::TCustomMemoModel::TLineInfo> &Message);
	MESSAGE void __fastcall MMLinesClear(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMLinesChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMShowScrollBarChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMCharCaseChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMHideSelectionOnExitChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMScrollDirectionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollDirections> &AMessage);
	HIDESBASE MESSAGE void __fastcall PMDoEnter(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Winapi::Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Winapi::Messages::TWMKillFocus &Message);
	MESSAGE void __fastcall WMChar(Winapi::Messages::TWMKey &Message);
	HIDESBASE MESSAGE void __fastcall WMKeyDown(Winapi::Messages::TWMKey &Message);
	
public:
	__fastcall virtual TWinNativeMemo(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TWinNativeMemo();
	__property Fmx::Memo::TCustomMemo* Memo = {read=GetMemo};
	__property Fmx::Memo::TCustomMemoModel* Model = {read=FModel};
public:
	/* TWinPresentation.Create */ inline __fastcall virtual TWinNativeMemo(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Win::TWinPresentation(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Memo */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MEMO_WIN)
using namespace Fmx::Memo::Win;
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
#endif	// Fmx_Memo_WinHPP
