// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Switch.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Switch_IosHPP
#define Fmx_Switch_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <Macapi.Helpers.hpp>
#include <FMX.Types.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <Macapi.ObjectiveC.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Switch
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXUISwitch;
typedef System::DelphiInterface<IFMXUISwitch> _di_IFMXUISwitch;
class DELPHICLASS TiOSNativeSwitch;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{B82F48FD-C9A1-46EC-AC6D-58DEEC7546F5}") IFMXUISwitch  : public Iosapi::Uikit::UISwitch 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	virtual void __cdecl ValueChanged() = 0 ;
};

class PASCALIMPLEMENTATION TiOSNativeSwitch : public Fmx::Presentation::Ios::TiOSNativeControl
{
	typedef Fmx::Presentation::Ios::TiOSNativeControl inherited;
	
private:
	bool FProcessingTouches;
	bool FOldValue;
	HIDESBASE Fmx::Stdctrls::TSwitchModel* __fastcall GetModel();
	void __fastcall SetValue(const bool Value);
	bool __fastcall GetValue();
	HIDESBASE Iosapi::Uikit::_di_UISwitch __fastcall GetView();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	MESSAGE void __fastcall MMValueChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMGetAdjustSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMGetAdjustType(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TAdjustType> &AMessage);
	
public:
	__fastcall virtual TiOSNativeSwitch()/* overload */;
	void __cdecl ValueChanged();
	HIDESBASE void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	HIDESBASE void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	HIDESBASE void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent);
	__property bool Value = {read=GetValue, write=SetValue, nodefault};
	__property Iosapi::Uikit::_di_UISwitch View = {read=GetView};
	__property Fmx::Stdctrls::TSwitchModel* Model = {read=GetModel};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSNativeSwitch(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Ios::TiOSNativeControl(AModel, AControl) { }
	/* TiOSNativeView.Destroy */ inline __fastcall virtual ~TiOSNativeSwitch() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Switch */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SWITCH_IOS)
using namespace Fmx::Switch::Ios;
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
#endif	// Fmx_Switch_IosHPP
