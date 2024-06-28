// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Switch.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Switch_WinHPP
#define Fmx_Switch_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Winapi.Messages.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Styles.Switch.hpp>
#include <FMX.Presentation.Win.Style.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Win.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Switch
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinSwitch;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWinSwitch : public Fmx::Presentation::Win::Style::TWinStyledPresentation
{
	typedef Fmx::Presentation::Win::Style::TWinStyledPresentation inherited;
	
private:
	Fmx::Stdctrls::TSwitchModel* FModel;
	Fmx::Styles::Switch::TCustomSwitchObject* FSwitchObject;
	bool FMouseEntered;
	void __fastcall SwitchObjectChanged(System::TObject* Sender);
	
protected:
	MESSAGE void __fastcall MMValueChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall WMLButtonDown(Winapi::Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMMouseMove(Winapi::Messages::TWMMouse &Message);
	HIDESBASE MESSAGE void __fastcall WMLButtonUp(Winapi::Messages::TWMMouse &Message);
	MESSAGE void __fastcall WMMouseLeave(Winapi::Messages::TMessage &Message);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall DoMouseEnter();
	virtual void __fastcall DoMouseLeave();
	virtual void __fastcall DoSwitch();
	
public:
	__fastcall virtual TWinSwitch(System::Classes::TComponent* AOwner)/* overload */;
	__property Fmx::Stdctrls::TSwitchModel* Model = {read=FModel};
	__property Fmx::Styles::Switch::TCustomSwitchObject* SwitchObject = {read=FSwitchObject};
public:
	/* TWinStyledPresentation.Destroy */ inline __fastcall virtual ~TWinSwitch() { }
	
public:
	/* TWinPresentation.Create */ inline __fastcall virtual TWinSwitch(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Win::Style::TWinStyledPresentation(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Switch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SWITCH_WIN)
using namespace Fmx::Switch::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SWITCH)
using namespace Fmx::Switch;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Switch_WinHPP
