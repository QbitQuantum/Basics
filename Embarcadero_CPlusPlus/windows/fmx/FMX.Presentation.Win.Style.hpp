// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.Win.Style.pas' rev: 34.00 (Windows)

#ifndef Fmx_Presentation_Win_StyleHPP
#define Fmx_Presentation_Win_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Messages.hpp>
#include <Winapi.Windows.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Win.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Platform.Win.hpp>
#include <FMX.Presentation.Win.hpp>
#include <FMX.Presentation.Style.Common.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Win
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TWinNativeStyledControl;
class DELPHICLASS TWinNativeScene;
class DELPHICLASS TWinStyledPresentation;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TWinNativeStyledControl : public Fmx::Presentation::Style::Common::TNativeStyledControl
{
	typedef Fmx::Presentation::Style::Common::TNativeStyledControl inherited;
	
private:
	TWinNativeScene* __fastcall GetScene();
	
protected:
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall AdjustSize();
	__property TWinNativeScene* Scene = {read=GetScene};
public:
	/* TStyledControl.Create */ inline __fastcall virtual TWinNativeStyledControl(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Presentation::Style::Common::TNativeStyledControl(AOwner) { }
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TWinNativeStyledControl() { }
	
};


class PASCALIMPLEMENTATION TWinNativeScene : public Fmx::Presentation::Style::Common::TNativeScene
{
	typedef Fmx::Presentation::Style::Common::TNativeScene inherited;
	
private:
	Fmx::Graphics::TBitmap* FBackground;
	Fmx::Graphics::TCanvas* FCanvas;
	Fmx::Platform::Win::TWinWindowHandle* FWindowHandle;
	System::Types::TPointF __fastcall GetParentedPosition(const HWND ParentHandle);
	void __fastcall DrawFMBackground(const HWND ParentHandle);
	void __fastcall DrawNativeBackground(const HWND ParentHandle);
	void __fastcall DrawBackground(const HWND Handle);
	TWinStyledPresentation* __fastcall GetPresentation();
	TWinNativeStyledControl* __fastcall GetStyledControl();
	
protected:
	virtual Fmx::Graphics::TCanvas* __fastcall DoGetCanvas();
	virtual float __fastcall DoGetSceneScale();
	virtual Fmx::Controls::TStyleBook* __fastcall DoGetStyleBook();
	virtual void __fastcall DoAddUpdateRect(const System::Types::TRectF &R);
	virtual void __fastcall DoResized(const System::Types::TSizeF &NewSize);
	virtual System::Types::TPointF __fastcall DoLocalToScreen(const System::Types::TPointF &P);
	virtual System::Types::TPointF __fastcall DoScreenToLocal(const System::Types::TPointF &P);
	virtual Fmx::Controls::TControl* __fastcall GetPresentedControl();
	
public:
	__fastcall TWinNativeScene(TWinStyledPresentation* APresentation, const Fmx::Presentation::Style::Common::TNativeStyledControlClass ControlClass);
	__fastcall virtual ~TWinNativeScene();
	void __fastcall Paint(const HDC DC);
	__property TWinStyledPresentation* Presentation = {read=GetPresentation};
	__property Fmx::Platform::Win::TWinWindowHandle* Handle = {read=FWindowHandle};
	__property TWinNativeStyledControl* StyledControl = {read=GetStyledControl};
};


class PASCALIMPLEMENTATION TWinStyledPresentation : public Fmx::Presentation::Win::TWinPresentation
{
	typedef Fmx::Presentation::Win::TWinPresentation inherited;
	
public:
	static System::Word Atom;
	static System::UnicodeString AtomString;
	__classmethod bool __fastcall IsParentNative(const HWND Handle);
	__classmethod Fmx::Types::TFmxObject* __fastcall WindowToObject(HWND Handle);
	
private:
	TWinNativeScene* FNativeScene;
	TWinNativeStyledControl* __fastcall GetStyledControl();
	Fmx::Types::TFmxObject* __fastcall GetResourceLink();
	MESSAGE void __fastcall WMPaint(Winapi::Messages::TWMPaint &Message);
	MESSAGE void __fastcall WMEraseBkgnd(Winapi::Messages::TWMEraseBkgnd &Message);
	
protected:
	virtual System::Types::TPoint __fastcall ExtractPoint(Winapi::Messages::TWMMouse &Message);
	virtual void __fastcall Resized();
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual System::UnicodeString __fastcall GetParentClassStyleLookupName();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	
public:
	__fastcall virtual TWinStyledPresentation(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TWinStyledPresentation();
	virtual void __fastcall Dispatch(void *Message);
	__property TWinNativeStyledControl* StyledControl = {read=GetStyledControl};
	__property Fmx::Types::TFmxObject* ResourceLink = {read=GetResourceLink};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TWinPresentation.Create */ inline __fastcall virtual TWinStyledPresentation(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Win::TWinPresentation(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Win */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_WIN_STYLE)
using namespace Fmx::Presentation::Win::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_WIN)
using namespace Fmx::Presentation::Win;
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
#endif	// Fmx_Presentation_Win_StyleHPP
