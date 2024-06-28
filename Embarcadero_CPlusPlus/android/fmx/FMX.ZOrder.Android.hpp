// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ZOrder.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Zorder_AndroidHPP
#define Fmx_Zorder_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
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
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidZOrderManager;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TAndroidZOrderManager : public Fmx::Zorder::TCustomZOrderManager__1<Androidapi::Jni::Graphicscontentviewtext::_di_JView>
{
	typedef Fmx::Zorder::TCustomZOrderManager__1<Androidapi::Jni::Graphicscontentviewtext::_di_JView> inherited;
	
private:
	System::Types::TRect __fastcall AbsoluteToParentView(Fmx::Controls::TControl* const AControl, const Androidapi::Jni::Graphicscontentviewtext::_di_JView AParentView);
	bool __fastcall IsFormLayout(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView);
	
protected:
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall GetParentView(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView);
	virtual void __fastcall RemoveFromParent(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView);
	virtual void __fastcall InsertSubview(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AParent, const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView, const Androidapi::Jni::Graphicscontentviewtext::_di_JView APreviousSiblingView);
	virtual int __fastcall IndexOfView(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView);
	virtual bool __fastcall IsFirstView(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView);
	virtual void __fastcall UpdateBounds(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView, Fmx::Controls::TControl* const AControl, const Androidapi::Jni::Graphicscontentviewtext::_di_JView AParentView)/* overload */;
	virtual void __fastcall UpdateVisible(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AView, const bool AVisible);
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall GetFormView(Fmx::Forms::TCommonCustomForm* const AForm);
	virtual bool __fastcall SameView(const Androidapi::Jni::Graphicscontentviewtext::_di_JView AViewLeft, const Androidapi::Jni::Graphicscontentviewtext::_di_JView AViewRight);
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JView __fastcall NullView();
public:
	/* {FMX_ZOrder}TCustomZOrderManager<Androidapi_JNI_GraphicsContentViewText_JView>.Create */ inline __fastcall TAndroidZOrderManager(Fmx::Types::TWindowHandle* const AOwner) : Fmx::Zorder::TCustomZOrderManager__1<Androidapi::Jni::Graphicscontentviewtext::_di_JView>(AOwner) { }
	/* {FMX_ZOrder}TCustomZOrderManager<Androidapi_JNI_GraphicsContentViewText_JView>.Destroy */ inline __fastcall virtual ~TAndroidZOrderManager() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  UpdateBounds(Fmx::Controls::TControl* const AControl){ Fmx::Zorder::TCustomZOrderManager__1<Androidapi::Jni::Graphicscontentviewtext::_di_JView>::UpdateBounds(AControl); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Zorder */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_ZORDER_ANDROID)
using namespace Fmx::Zorder::Android;
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
#endif	// Fmx_Zorder_AndroidHPP
