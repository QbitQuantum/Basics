// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Edit.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Edit_WinHPP
#define Fmx_Edit_WinHPP

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
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Presentation.Win.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Win.hpp>
#include <FMX.Helpers.Win.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Edit
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinNativeEdit;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWinNativeEdit : public Fmx::Presentation::Win::TWinPresentation
{
	typedef Fmx::Presentation::Win::TWinPresentation inherited;
	
private:
	bool FAlignedVertically;
	Fmx::Edit::TCustomEditModel* FModel;
	HFONT FFontHandle;
	Fmx::Edit::TCustomEdit* __fastcall GetEdit();
	void __fastcall UpdateTextSettings();
	void __fastcall CopyModelToNative();
	void __fastcall CopyNativeToModel();
	void __fastcall SetPasswordChar();
	void __fastcall SetReadOnly();
	void __fastcall SetMaxLength();
	void __fastcall SetPromptText();
	void __fastcall SetSelStart();
	void __fastcall SetSelLength();
	void __fastcall RecreateFont();
	void __fastcall DeleteFont();
	MESSAGE void __fastcall MMSelLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMSelStartChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMPasswordChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMTextSettingsChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMTextChanged(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMReadOnly(System::TDispatchMessage &Message);
	MESSAGE void __fastcall MMPromptTextChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &Message);
	MESSAGE void __fastcall MMMaxLengthChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMCaretPositionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<int> &Message);
	MESSAGE void __fastcall MMCharCaseChanged(System::TDispatchMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMSetFocus(Winapi::Messages::TWMSetFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKillFocus(Winapi::Messages::TWMKillFocus &Message);
	HIDESBASE MESSAGE void __fastcall WMKeyDown(Winapi::Messages::TWMKey &Message);
	MESSAGE void __fastcall WMChar(Winapi::Messages::TWMKey &Message);
	MESSAGE void __fastcall WMNCCalcSize(Winapi::Messages::TMessage &Message);
	HIDESBASE MESSAGE void __fastcall WMTextColor(Winapi::Messages::TMessage &Message);
	
protected:
	virtual void __fastcall CreateHandle();
	virtual void __fastcall DestroyHandle();
	virtual void __fastcall CreateParams(Fmx::Controls::Win::TCreateParams &Params);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__fastcall virtual TWinNativeEdit(System::Classes::TComponent* AOwner)/* overload */;
	__property Fmx::Edit::TCustomEdit* Edit = {read=GetEdit};
	__property Fmx::Edit::TCustomEditModel* Model = {read=FModel};
public:
	/* TWinPresentation.Create */ inline __fastcall virtual TWinNativeEdit(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Win::TWinPresentation(AOwner, AModel, AControl) { }
	/* TWinPresentation.Destroy */ inline __fastcall virtual ~TWinNativeEdit() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Edit */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDIT_WIN)
using namespace Fmx::Edit::Win;
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
#endif	// Fmx_Edit_WinHPP
