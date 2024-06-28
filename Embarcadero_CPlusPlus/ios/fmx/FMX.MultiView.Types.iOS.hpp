// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiView.Types.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Multiview_Types_IosHPP
#define Fmx_Multiview_Types_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.TypInfo.hpp>
#include <System.UITypes.hpp>
#include <System.Types.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.UIKit.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.MultiView.Types.hpp>
#include <FMX.Controls.Model.hpp>
#include <Macapi.ObjectiveC.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multiview
{
namespace Types
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IFMXTouchInterceptingLayout;
typedef System::DelphiInterface<IFMXTouchInterceptingLayout> _di_IFMXTouchInterceptingLayout;
class DELPHICLASS TiOSTouchInterceptingLayout;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{50546536-EE2A-42C5-9852-0A9483ADA45C}") IFMXTouchInterceptingLayout  : public Iosapi::Uikit::UIView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual bool __cdecl pointInside(Iosapi::Foundation::NSPoint point, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSTouchInterceptingLayout : public Fmx::Presentation::Ios::TiOSNativeView
{
	typedef Fmx::Presentation::Ios::TiOSNativeView inherited;
	
private:
	Iosapi::Uikit::_di_UIView FShadowView;
	void __fastcall UpdateShadowColor();
	HIDESBASE Fmx::Multiview::Types::TTouchInterceptingLayoutModel* __fastcall GetModel();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	MESSAGE void __fastcall MMColorChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TAlphaColor> &AMessage);
	MESSAGE void __fastcall MMEnabledShadowChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMSetAlpha(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<float> &AMessage);
	HIDESBASE MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	
public:
	__fastcall virtual TiOSTouchInterceptingLayout()/* overload */;
	__fastcall virtual ~TiOSTouchInterceptingLayout();
	virtual bool __cdecl pointInside(Iosapi::Foundation::NSPoint point, Iosapi::Uikit::_di_UIEvent withEvent);
	__property Fmx::Multiview::Types::TTouchInterceptingLayoutModel* Model = {read=GetModel};
	__property Iosapi::Uikit::_di_UIView ShadowView = {read=FShadowView, write=FShadowView};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSTouchInterceptingLayout(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Ios::TiOSNativeView(AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Types */
}	/* namespace Multiview */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW_TYPES_IOS)
using namespace Fmx::Multiview::Types::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW_TYPES)
using namespace Fmx::Multiview::Types;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW)
using namespace Fmx::Multiview;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Multiview_Types_IosHPP
