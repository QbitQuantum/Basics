// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Switch.Style.pas' rev: 34.00 (Windows)

#ifndef Fmx_Switch_StyleHPP
#define Fmx_Switch_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.UITypes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Styles.Switch.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Switch
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledSwitch;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStyledSwitch : public Fmx::Presentation::Style::TStyledPresentation
{
	typedef Fmx::Presentation::Style::TStyledPresentation inherited;
	
private:
	Fmx::Styles::Switch::TCustomSwitchObject* FSwitchObject;
	void __fastcall SwitchObjectChanged(System::TObject* Sender);
	HIDESBASE Fmx::Stdctrls::TSwitchModel* __fastcall GetModel();
	
protected:
	MESSAGE void __fastcall MMValueChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoMouseEnter();
	virtual void __fastcall DoMouseLeave();
	virtual void __fastcall DoSwitch();
	__property Fmx::Styles::Switch::TCustomSwitchObject* SwitchObject = {read=FSwitchObject};
	
public:
	__fastcall virtual TStyledSwitch(System::Classes::TComponent* AOwner)/* overload */;
	__property Fmx::Stdctrls::TSwitchModel* Model = {read=GetModel};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledSwitch(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Style::TStyledPresentation(AOwner, AModel, AControl) { }
	
public:
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TStyledSwitch() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Switch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SWITCH_STYLE)
using namespace Fmx::Switch::Style;
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
#endif	// Fmx_Switch_StyleHPP
