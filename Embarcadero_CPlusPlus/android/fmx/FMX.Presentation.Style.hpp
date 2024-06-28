// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Presentation_StyleHPP
#define Fmx_Presentation_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.Math.Vectors.hpp>
#include <System.Rtti.hpp>
#include <System.UITypes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledPresentation;
class DELPHICLASS TStyledPresentationProxy;
template<typename T> class DELPHICLASS TStyledPresentationProxy__1;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledPresentation : public Fmx::Controls::TStyledControl
{
	typedef Fmx::Controls::TStyledControl inherited;
	
private:
	Fmx::Controls::Model::TDataModel* FModel;
	Fmx::Controls::TControl* FPresentedControl;
	void __fastcall SetDataToStyleObject(const System::UnicodeString AName, const System::Rtti::TValue &AValue);
	System::Rtti::TValue __fastcall GetDataFromStyleObject(const System::UnicodeString AName);
	System::Classes::TComponentState __fastcall GetComponentState();
	
protected:
	MESSAGE void __fastcall MMDataChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::Rtti::TValue> > &AMessage);
	MESSAGE void __fastcall MMGetData(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::Rtti::TValue> > &AMessage);
	MESSAGE void __fastcall PMUnload(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSetSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMGetSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMDoEnter(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMDoExit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMIsFocused(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMSetStyleLookup(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall PMGetStyleLookup(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall PMFindStyleResource(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TFindStyleResourceInfo> &AMessage);
	MESSAGE void __fastcall PMKeyDown(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TKeyInfo> &AMessage);
	MESSAGE void __fastcall PMKeyUp(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TKeyInfo> &AMessage);
	MESSAGE void __fastcall PMRealign(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMActionClientChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMActionChange(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TActionInfo> &AMessage);
	MESSAGE void __fastcall PMApplyStyleLookup(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMNeedStyleLookup(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMHitTestChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMGetAdjustSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMSetAdjustSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMGetAdjustType(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TAdjustType> &AMessage);
	MESSAGE void __fastcall PMSetAdjustType(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TAdjustType> &AMessage);
	MESSAGE void __fastcall PMStartTriggerAnimation(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TTriggerInfo> &AMessage);
	MESSAGE void __fastcall PMApplyTriggerEffect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TTriggerInfo> &AMessage);
	MESSAGE void __fastcall PMGetResourceLink(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TFmxObject*> &AMessage);
	MESSAGE void __fastcall PMPointInObject(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TPointInObjectLocalInfo> &AMessage);
	MESSAGE void __fastcall PMAbsoluteChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMGetFirstControlWithGesture(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TFirstControlWithGestureInfo> &AMessage);
	virtual bool __fastcall HasHint();
	virtual System::UnicodeString __fastcall GetHintString();
	virtual System::Classes::TObservers* __fastcall GetObservers();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual System::UnicodeString __fastcall GetParentClassStyleLookupName();
	virtual void __fastcall AdjustSize();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual Fmx::Types::TFmxObject* __fastcall GetStyleContext();
	virtual Fmx::Types::TFmxObject* __fastcall GetStyleObject(const bool Clone)/* overload */;
	virtual Fmx::Types::TFmxObject* __fastcall GetStyleObject()/* overload */;
	virtual void __fastcall DoApplyStyleLookup();
	virtual bool __fastcall ShowContextMenu(const System::Types::TPointF &ScreenPosition);
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	virtual void __fastcall MouseClick(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall DoMouseEnter();
	virtual void __fastcall DoMouseLeave();
	virtual void __fastcall DragDrop(const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point);
	virtual void __fastcall DragEnd();
	virtual void __fastcall DragEnter(const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point);
	virtual void __fastcall DragLeave();
	virtual void __fastcall DragOver(const Fmx::Types::TDragObject &Data, const System::Types::TPointF &Point, Fmx::Types::TDragOperation &Operation);
	virtual System::Uitypes::TDragMode __fastcall GetDragMode();
	virtual void __fastcall BeginAutoDrag();
	virtual bool __fastcall GetCanParentFocus();
	virtual void __fastcall Tap(const System::Types::TPointF &Point);
	virtual void __fastcall CMGesture(Fmx::Types::TGestureEventInfo &EventInfo);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	template<typename T> T __fastcall GetModel();
	
public:
	__fastcall virtual TStyledPresentation(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual TStyledPresentation(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */;
	virtual void __fastcall SetNewScene(Fmx::Controls::_di_IScene AScene);
	bool __fastcall HasModel();
	virtual bool __fastcall PointInObjectLocal(float X, float Y);
	__property Fmx::Controls::TControl* PresentedControl = {read=FPresentedControl};
	__property System::Classes::TComponentState ComponentState = {read=GetComponentState, nodefault};
public:
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TStyledPresentation() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TStyledPresentationClass);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledPresentationProxy : public Fmx::Controls::Presentation::TPresentationProxy
{
	typedef Fmx::Controls::Presentation::TPresentationProxy inherited;
	
protected:
	virtual System::TObject* __fastcall CreateReceiver();
public:
	/* TPresentationProxy.Create */ inline __fastcall virtual TStyledPresentationProxy()/* overload */ : Fmx::Controls::Presentation::TPresentationProxy() { }
	/* TPresentationProxy.Create */ inline __fastcall virtual TStyledPresentationProxy(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Controls::Presentation::TPresentationProxy(AModel, AControl) { }
	/* TPresentationProxy.Destroy */ inline __fastcall virtual ~TStyledPresentationProxy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TStyledPresentationProxy__1 : public TStyledPresentationProxy
{
	typedef TStyledPresentationProxy inherited;
	
protected:
	virtual System::TObject* __fastcall CreateReceiver();
public:
	/* TPresentationProxy.Create */ inline __fastcall virtual TStyledPresentationProxy__1()/* overload */ : TStyledPresentationProxy() { }
	/* TPresentationProxy.Create */ inline __fastcall virtual TStyledPresentationProxy__1(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : TStyledPresentationProxy(AModel, AControl) { }
	/* TPresentationProxy.Destroy */ inline __fastcall virtual ~TStyledPresentationProxy__1() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_STYLE)
using namespace Fmx::Presentation::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION)
using namespace Fmx::Presentation;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Presentation_StyleHPP
