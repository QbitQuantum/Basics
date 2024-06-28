// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ZOrder.iOS.pas' rev: 34.00 (iOS)

#ifndef Fmx_Zorder_IosHPP
#define Fmx_Zorder_IosHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.ZOrder.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Zorder
{
namespace Ios
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TiOSZOrderManager;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TiOSZOrderManager : public Fmx::Zorder::TCustomZOrderManager__1<Iosapi::Uikit::_di_UIView>
{
	typedef Fmx::Zorder::TCustomZOrderManager__1<Iosapi::Uikit::_di_UIView> inherited;
	
private:
	Iosapi::Foundation::NSRect __fastcall AbsoluteToParentView(Fmx::Controls::TControl* const AControl, const Iosapi::Uikit::_di_UIView AParentView);
	
protected:
	virtual Iosapi::Uikit::_di_UIView __fastcall GetParentView(const Iosapi::Uikit::_di_UIView AView);
	virtual void __fastcall RemoveFromParent(const Iosapi::Uikit::_di_UIView AChildView);
	virtual void __fastcall InsertSubview(const Iosapi::Uikit::_di_UIView AParent, const Iosapi::Uikit::_di_UIView AChildView, const Iosapi::Uikit::_di_UIView APreviousSiblingView);
	virtual int __fastcall IndexOfView(const Iosapi::Uikit::_di_UIView AView);
	virtual void __fastcall UpdateVisible(const Iosapi::Uikit::_di_UIView AView, const bool AVisible);
	virtual void __fastcall UpdateBounds(const Iosapi::Uikit::_di_UIView AView, Fmx::Controls::TControl* const AControl, const Iosapi::Uikit::_di_UIView AParentView)/* overload */;
	virtual Iosapi::Uikit::_di_UIView __fastcall GetFormView(Fmx::Forms::TCommonCustomForm* const AForm);
	virtual bool __fastcall SameView(const Iosapi::Uikit::_di_UIView AViewLeft, const Iosapi::Uikit::_di_UIView AViewRight);
	virtual Iosapi::Uikit::_di_UIView __fastcall NullView();
public:
	/* {FMX_ZOrder}TCustomZOrderManager<iOSapi_UIKit_UIView>.Create */ inline __fastcall TiOSZOrderManager(Fmx::Types::TWindowHandle* const AOwner) : Fmx::Zorder::TCustomZOrderManager__1<Iosapi::Uikit::_di_UIView>(AOwner) { }
	/* {FMX_ZOrder}TCustomZOrderManager<iOSapi_UIKit_UIView>.Destroy */ inline __fastcall virtual ~TiOSZOrderManager() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  UpdateBounds(Fmx::Controls::TControl* const AControl){ Fmx::Zorder::TCustomZOrderManager__1<Iosapi::Uikit::_di_UIView>::UpdateBounds(AControl); }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Ios */
}	/* namespace Zorder */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ZORDER_IOS)
using namespace Fmx::Zorder::Ios;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ZORDER)
using namespace Fmx::Zorder;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Zorder_IosHPP
