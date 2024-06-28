// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiView.Types.Android.pas' rev: 34.00 (Android)

#ifndef Fmx_Multiview_Types_AndroidHPP
#define Fmx_Multiview_Types_AndroidHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.MultiView.Types.hpp>
#include <FMX.Presentation.Android.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multiview
{
namespace Types
{
namespace Android
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAndroidTouchInterceptingLayout;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TAndroidTouchInterceptingLayout : public Fmx::Presentation::Android::TAndroidNativeView
{
	typedef Fmx::Presentation::Android::TAndroidNativeView inherited;
	
private:
	bool FPressedInDefinedArea;
	void __fastcall UpdateShadowColor();
	HIDESBASE Fmx::Multiview::Types::TTouchInterceptingLayoutModel* __fastcall GetModel();
	bool __fastcall CheckPointOwnership(const System::Types::TPointF &ALocalPoint);
	
protected:
	MESSAGE void __fastcall MMColorChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TAlphaColor> &AMessage);
	MESSAGE void __fastcall MMEnabledShadowChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	HIDESBASE MESSAGE void __fastcall PMSetAlpha(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<float> &AMessage);
	HIDESBASE MESSAGE void __fastcall PMPointInObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TPointInObjectLocalInfo> &AMessage);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual bool __fastcall PointInside(const System::Types::TPointF &AScreenPoint, const Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent AEvent);
	virtual bool __fastcall ProcessTouch(Androidapi::Jni::Graphicscontentviewtext::_di_JView view, Androidapi::Jni::Graphicscontentviewtext::_di_JMotionEvent event);
	
public:
	__property Fmx::Multiview::Types::TTouchInterceptingLayoutModel* Model = {read=GetModel};
	__property bool PressedInDefinedArea = {read=FPressedInDefinedArea, nodefault};
public:
	/* TAndroidNativeView.Create */ inline __fastcall virtual TAndroidTouchInterceptingLayout()/* overload */ : Fmx::Presentation::Android::TAndroidNativeView() { }
	/* TAndroidNativeView.Create */ inline __fastcall TAndroidTouchInterceptingLayout(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Android::TAndroidNativeView(AModel, AControl) { }
	/* TAndroidNativeView.Destroy */ inline __fastcall virtual ~TAndroidTouchInterceptingLayout() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Android */
}	/* namespace Types */
}	/* namespace Multiview */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW_TYPES_ANDROID)
using namespace Fmx::Multiview::Types::Android;
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
#endif	// Fmx_Multiview_Types_AndroidHPP
