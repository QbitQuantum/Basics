// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.ScrollBox.Win.pas' rev: 34.00 (Windows)

#ifndef Fmx_Scrollbox_WinHPP
#define Fmx_Scrollbox_WinHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <FMX.Presentation.Win.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.StdActns.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Win.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Scrollbox
{
namespace Win
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinScrollBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWinScrollBox : public Fmx::Presentation::Win::TWinPresentation
{
	typedef Fmx::Presentation::Win::TWinPresentation inherited;
	
	
protected:
	struct DECLSPEC_DRECORD TViewportSaveState
	{
	public:
		System::Types::TPointF OldPosition;
		System::Types::TPointF NewPosition;
		bool ContentSizeChanged;
	};
	
	
	
public:
	static const System::Int8 SmallIncrement = System::Int8(0x14);
	
	static const System::Int8 LargeIncrement = System::Int8(0x1e);
	
	
private:
	Fmx::Scrollbox::TCustomScrollBoxModel* FModel;
	Fmx::Scrollbox::TScrollContent* FContent;
	Fmx::Stdactns::TValueRange* FHScrollBarInfo;
	Fmx::Stdactns::TValueRange* FVScrollBarInfo;
	int FChanging;
	bool FNeedCallViewPortPositionChanged;
	TViewportSaveState FSavedState;
	System::Types::TSizeF __fastcall GetViewPortSize();
	void __fastcall ScrollBarsChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall CreateParams(Fmx::Controls::Win::TCreateParams &Params);
	virtual void __fastcall UpdateScrollBarsRange();
	virtual void __fastcall UpdateScrollBarsVisibile();
	virtual void __fastcall UpdateScrollBarsPosition();
	virtual void __fastcall UpdateScrollBarsPageSize();
	virtual void __fastcall UpdateScrollBarsEnabled();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	MESSAGE void __fastcall MMShowScrollBarChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall MMSetContentBounds(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TRectF> &AMessage);
	MESSAGE void __fastcall MMScrollDirectionChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollDirections> &AMessage);
	MESSAGE void __fastcall MMEnabledScrollChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall PMSetContent(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TScrollContent*> &AMessage);
	MESSAGE void __fastcall PMScrollInRect(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TCustomScrollBoxModel::TInViewRectInfo> &AMessage);
	MESSAGE void __fastcall PMScrollBy(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<Fmx::Scrollbox::TCustomScrollBoxModel::TScrollByInfo> &AMessage);
	MESSAGE void __fastcall PMSetViewPortPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &AMessage);
	MESSAGE void __fastcall PMGetViewPortPosition(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TPointF> &AMessage);
	MESSAGE void __fastcall PMGetViewPortSize(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Types::TSizeF> &AMessage);
	MESSAGE void __fastcall WMSize(Winapi::Messages::TWMSize &Message);
	MESSAGE void __fastcall WMHScroll(Winapi::Messages::TWMScroll &Message);
	MESSAGE void __fastcall WMVScroll(Winapi::Messages::TWMScroll &Message);
	MESSAGE void __fastcall WMMouseWheel(Winapi::Messages::TWMMouseWheel &Message);
	virtual void __fastcall DoScroll(const Winapi::Messages::TWMScroll &Message, Fmx::Stdactns::TValueRange* &AScrollValueRange);
	virtual void __fastcall DoViewportPositionChanged(const System::Types::TPointF &OldViewportPosition, const System::Types::TPointF &NewViewportPosition, const bool ContentSizeChanged);
	__property bool NeedCallViewPortPositionChanged = {read=FNeedCallViewPortPositionChanged, nodefault};
	
public:
	__fastcall virtual TWinScrollBox(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TWinScrollBox();
	void __fastcall BeginChanging();
	void __fastcall EndChanging();
	bool __fastcall IsChanging();
	__property Fmx::Scrollbox::TScrollContent* Content = {read=FContent, write=FContent};
	__property Fmx::Scrollbox::TCustomScrollBoxModel* Model = {read=FModel};
	__property System::Types::TSizeF ViewPortSize = {read=GetViewPortSize};
	__property Fmx::Stdactns::TValueRange* HScrollBarInfo = {read=FHScrollBarInfo};
	__property Fmx::Stdactns::TValueRange* VScrollBarInfo = {read=FVScrollBarInfo};
public:
	/* TWinPresentation.Create */ inline __fastcall virtual TWinScrollBox(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Win::TWinPresentation(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Win */
}	/* namespace Scrollbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SCROLLBOX_WIN)
using namespace Fmx::Scrollbox::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SCROLLBOX)
using namespace Fmx::Scrollbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Scrollbox_WinHPP
