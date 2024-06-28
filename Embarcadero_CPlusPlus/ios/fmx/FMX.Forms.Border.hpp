// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Forms.Border.pas' rev: 34.00 (iOS)

#ifndef Fmx_Forms_BorderHPP
#define Fmx_Forms_BorderHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Messaging.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Graphics.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Forms
{
namespace Border
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledWindowBorder;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStyledWindowBorder : public Fmx::Forms::TWindowBorder
{
	typedef Fmx::Forms::TWindowBorder inherited;
	
private:
	bool FNeedStyleLookup;
	float FLastWidth;
	float FLastHeight;
	System::Types::TPointF FMousePos;
	System::Types::TPointF FDownPos;
	Fmx::Types::_di_IControl FHovered;
	Fmx::Types::_di_IControl FCaptured;
	Fmx::Types::_di_IControl FFocused;
	int FStyleChangedId;
	Fmx::Forms::_di_IFMXWindowService FWinService;
	int FDisableUpdating;
	Fmx::Controls::TControl* __fastcall GetStyleObject();
	Fmx::Types::TFmxObject* __fastcall GetObject();
	Fmx::Types::_di_IControl __fastcall GetActiveControl();
	void __fastcall SetActiveControl(const Fmx::Types::_di_IControl AControl);
	void __fastcall SetCaptured(const Fmx::Types::_di_IControl Value);
	Fmx::Types::_di_IControl __fastcall NewFocusedControl(const Fmx::Types::_di_IControl Value);
	void __fastcall SetFocused(const Fmx::Types::_di_IControl Value);
	void __fastcall SetHovered(const Fmx::Types::_di_IControl Value);
	Fmx::Types::_di_IControl __fastcall GetCaptured();
	Fmx::Types::_di_IControl __fastcall GetFocused();
	System::Classes::TBiDiMode __fastcall GetBiDiMode();
	Fmx::Types::_di_IControl __fastcall GetHovered();
	void __fastcall BeginInternalDrag(System::TObject* const Source, System::TObject* const ABitmap);
	void __fastcall AddUpdateRect(const System::Types::TRectF &R);
	int __fastcall GetUpdateRectsCount();
	System::Types::TRectF __fastcall GetUpdateRect(const int Index);
	System::Types::TPointF __fastcall LocalToScreen(const System::Types::TPointF &P);
	System::Types::TPointF __fastcall ScreenToLocal(const System::Types::TPointF &P);
	float __fastcall GetSceneScale();
	void __fastcall ChangeScrollingState(Fmx::Controls::TControl* const AControl, const bool Active);
	void __fastcall DisableUpdating();
	void __fastcall EnableUpdating();
	Fmx::Controls::TStyleBook* __fastcall GetStyleBook();
	void __fastcall SetStyleBook(Fmx::Controls::TStyleBook* const Value);
	float __fastcall GetContainerWidth();
	float __fastcall GetContainerHeight();
	bool __fastcall GetActive();
	void __fastcall StyleChangedHandler(System::TObject* const Sender, System::Messaging::TMessageBase* const Msg);
	
protected:
	Fmx::Controls::TControl* FClientObject;
	Fmx::Controls::TControl* FCloseObject;
	Fmx::Controls::TControl* FIconObject;
	Fmx::Controls::TControl* FTitleObject;
	Fmx::Controls::TControl* FMinObject;
	Fmx::Controls::TControl* FMaxObject;
	Fmx::Controls::TControl* FResObject;
	Fmx::Controls::TControl* FMaskObject;
	bool FDisableAlign;
	Fmx::Controls::TControl* FResourceLink;
	void __fastcall ApplyStyleLookup();
	virtual void __fastcall DoApplyStyle();
	void __fastcall DoCloseClick(System::TObject* Sender);
	void __fastcall DoMaxClick(System::TObject* Sender);
	void __fastcall DoResClick(System::TObject* Sender);
	void __fastcall DoMinClick(System::TObject* Sender);
	virtual System::UnicodeString __fastcall GetStyleLookup();
	virtual System::Types::TSizeF __fastcall GetFormSize();
	virtual void __fastcall FreeNotification(System::TObject* AObject);
	virtual void __fastcall DoAddObject(Fmx::Types::TFmxObject* const AObject);
	virtual void __fastcall DoRemoveObject(Fmx::Types::TFmxObject* const AObject);
	void __fastcall SetScene(Fmx::Types::TFmxObject* const AObject, const Fmx::Controls::_di_IScene Scene);
	virtual void __fastcall DoAddUpdateRect(const System::Types::TRectF &R);
	virtual System::Types::TRectF __fastcall GetClientMargins();
	virtual void __fastcall StyleChanged();
	virtual void __fastcall ScaleChanged();
	virtual void __fastcall Invalidate();
	virtual void __fastcall Resize();
	virtual void __fastcall Activate();
	virtual void __fastcall Deactivate();
	virtual bool __fastcall GetSupported();
	virtual Fmx::Graphics::TCanvas* __fastcall GetCanvas();
	void __fastcall Realign();
	void __fastcall ChildrenAlignChanged();
	
public:
	__fastcall virtual TStyledWindowBorder(Fmx::Forms::TCommonCustomForm* const AForm);
	__fastcall virtual ~TStyledWindowBorder();
	Fmx::Types::_di_IControl __fastcall ObjectAtPoint(const System::Types::TPointF &P);
	void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	void __fastcall MouseLeave();
	__property System::Types::TRectF ClientMargins = {read=GetClientMargins};
	__property System::Types::TSizeF FormSize = {read=GetFormSize};
	__property bool IsActive = {read=GetActive, nodefault};
private:
	void *__IAlignRoot;	// Fmx::Types::IAlignRoot 
	void *__IContainerObject;	// Fmx::Types::IContainerObject 
	void *__IScene;	// Fmx::Controls::IScene 
	void *__IRoot;	// Fmx::Types::IRoot 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {86DF30A6-0394-4A0E-8722-1F2CDB242CE8}
	operator Fmx::Types::_di_IAlignRoot()
	{
		Fmx::Types::_di_IAlignRoot intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IAlignRoot*(void) { return (Fmx::Types::IAlignRoot*)&__IAlignRoot; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DE635E60-CB00-4741-92BB-3B8F1F29A67C}
	operator Fmx::Types::_di_IContainerObject()
	{
		Fmx::Types::_di_IContainerObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IContainerObject*(void) { return (Fmx::Types::IContainerObject*)&__IContainerObject; }
	#endif
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
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {BA1AE6C6-FCF7-43E2-92AA-2869FF203309}
	operator Fmx::Controls::_di_IStyleBookOwner()
	{
		Fmx::Controls::_di_IStyleBookOwner intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Controls::IStyleBookOwner*(void) { return (Fmx::Controls::IStyleBookOwner*)&__IScene; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {7F7BB7B0-5932-49DD-9D35-712B2BA5D8EF}
	operator Fmx::Types::_di_IRoot()
	{
		Fmx::Types::_di_IRoot intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Types::IRoot*(void) { return (Fmx::Types::IRoot*)&__IRoot; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Border */
}	/* namespace Forms */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FORMS_BORDER)
using namespace Fmx::Forms::Border;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_FORMS)
using namespace Fmx::Forms;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Forms_BorderHPP
