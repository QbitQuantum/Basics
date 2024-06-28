// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Style.Common.pas' rev: 34.00 (iOS)

#ifndef Fmx_Presentation_Style_CommonHPP
#define Fmx_Presentation_Style_CommonHPP

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
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.UITypes.hpp>
#include <System.Math.hpp>
#include <System.Generics.Collections.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Style
{
namespace Common
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TNativeStyledControl;
class DELPHICLASS TNativeScene;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TNativeStyledControl : public Fmx::Controls::TStyledControl
{
	typedef Fmx::Controls::TStyledControl inherited;
	
private:
	TNativeScene* FScene;
	
protected:
	virtual void __fastcall AdjustSize();
	__property TNativeScene* Scene = {read=FScene};
public:
	/* TStyledControl.Create */ inline __fastcall virtual TNativeStyledControl(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Controls::TStyledControl(AOwner) { }
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TNativeStyledControl() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TNativeStyledControlClass);

typedef System::Generics::Collections::TList__1<System::Types::TRectF>* TUpdateRects;

class PASCALIMPLEMENTATION TNativeScene : public Fmx::Types::TFmxObject
{
	typedef Fmx::Types::TFmxObject inherited;
	
private:
	System::TObject* FPresentation;
	Fmx::Types::TWindowHandle* FHandle;
	TNativeStyledControl* FStyledControl;
	System::Generics::Collections::TList__1<System::Types::TRectF>* FUpdateRects;
	int FDisableUpdating;
	bool __fastcall GetDisableUpdating();
	void __fastcall AddUpdateRect(const System::Types::TRectF &R);
	Fmx::Types::TFmxObject* __fastcall GetObject();
	int __fastcall GetUpdateRectsCount();
	System::Types::TRectF __fastcall GetUpdateRect(const int Index);
	Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	float __fastcall GetSceneScale();
	Fmx::Controls::TStyleBook* __fastcall GetStyleBook();
	Fmx::Types::_di_IControl __fastcall ObjectAtPoint(const System::Types::TPointF &P);
	System::Types::TPointF __fastcall ScreenToLocal(const System::Types::TPointF &P);
	System::Types::TPointF __fastcall LocalToScreen(const System::Types::TPointF &P);
	void __fastcall SetStyleBook(Fmx::Controls::TStyleBook* const Value);
	void __fastcall ChangeScrollingState(Fmx::Controls::TControl* const AControl, const bool Active);
	void __fastcall DisableUpdating();
	void __fastcall EnableUpdating();
	MESSAGE void __fastcall PMApplyStyleLookup(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMNeedStyleLookup(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMPaintChildren(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMSetStyleLookup(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::UnicodeString> &AMessage);
	MESSAGE void __fastcall PMFindStyleResource(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TFindStyleResourceInfo> &AMessage);
	MESSAGE void __fastcall PMRealign(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMGetRecommendSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMObjectAtPoint(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TObjectAtPointInfo> &AMessage);
	MESSAGE void __fastcall PMStartTriggerAnimation(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TTriggerInfo> &AMessage);
	MESSAGE void __fastcall PMApplyTriggerEffect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Controls::Presentation::TTriggerInfo> &AMessage);
	MESSAGE void __fastcall PMGetResourceLink(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TFmxObject*> &AMessage);
	MESSAGE void __fastcall PMGetAdjustSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMSetAdjustSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall PMGetAdjustType(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TAdjustType> &AMessage);
	MESSAGE void __fastcall PMSetAdjustType(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Types::TAdjustType> &AMessage);
	void __fastcall SetCustomSceneAddRect(Fmx::Controls::TControl* const Control);
	void __fastcall PaintPresentedChildren();
	
protected:
	virtual void __fastcall DoAddUpdateRect(const System::Types::TRectF &R) = 0 ;
	virtual Fmx::Graphics::TCanvas* __fastcall DoGetCanvas() = 0 ;
	virtual float __fastcall DoGetSceneScale() = 0 ;
	virtual Fmx::Controls::TStyleBook* __fastcall DoGetStyleBook() = 0 ;
	virtual void __fastcall DoResized(const System::Types::TSizeF &NewSize);
	virtual System::Types::TPointF __fastcall DoScreenToLocal(const System::Types::TPointF &P) = 0 ;
	virtual System::Types::TPointF __fastcall DoLocalToScreen(const System::Types::TPointF &P) = 0 ;
	void __fastcall CustomSceneAddRect(Fmx::Controls::TControl* Sender, const System::Types::TRectF &ARect);
	virtual Fmx::Controls::TControl* __fastcall GetPresentedControl() = 0 ;
	__property bool IsDisableUpdating = {read=GetDisableUpdating, nodefault};
	void __fastcall PaintControls();
	__property System::TObject* Presentation = {read=FPresentation};
	__property Fmx::Types::TWindowHandle* Handle = {read=FHandle};
	__property TNativeStyledControl* StyledControl = {read=FStyledControl};
	__property Fmx::Controls::TControl* PresentedControl = {read=GetPresentedControl};
	__property System::Generics::Collections::TList__1<System::Types::TRectF>* UpdateRects = {read=FUpdateRects};
	
public:
	__fastcall TNativeScene(Fmx::Types::TWindowHandle* const AHandle, System::TObject* APresentation, const TNativeStyledControlClass ControlClass);
	__fastcall virtual ~TNativeScene();
	void __fastcall SetSize(const System::Types::TSizeF &ASize);
private:
	void *__IScene;	// Fmx::Controls::IScene 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16DB110E-DA7D-4E75-BC2D-999FA12E45F5}
	operator Fmx::Controls::_di_IScene()
	{
		Fmx::Controls::_di_IScene intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Controls::IScene*(void) { return (Fmx::Controls::IScene*)&__IScene; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Common */
}	/* namespace Style */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_STYLE_COMMON)
using namespace Fmx::Presentation::Style::Common;
#endif
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
#endif	// Fmx_Presentation_Style_CommonHPP
