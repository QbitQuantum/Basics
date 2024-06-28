// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.Presentation.iOS.Style.pas' rev: 34.00 (iOS)

#ifndef Fmx_Presentation_Ios_StyleHPP
#define Fmx_Presentation_Ios_StyleHPP

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
#include <Macapi.ObjectiveC.hpp>
#include <iOSapi.Foundation.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.UIKit.hpp>
#include <iOSapi.CoreGraphics.hpp>
#include <iOSapi.GLKit.hpp>
#include <Macapi.MetalKit.hpp>
#include <FMX.Types.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Presentation.iOS.hpp>
#include <FMX.Platform.iOS.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Presentation.Style.Common.hpp>
#include <FMX.Context.Metal.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Presentation
{
namespace Ios
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TiOSNativeStyledControl;
class DELPHICLASS TiOSNativeScene;
__interface DELPHIINTERFACE IiOSGLKSceneControl;
typedef System::DelphiInterface<IiOSGLKSceneControl> _di_IiOSGLKSceneControl;
__interface DELPHIINTERFACE IiOSMTKSceneControl;
typedef System::DelphiInterface<IiOSMTKSceneControl> _di_IiOSMTKSceneControl;
class DELPHICLASS TiOSStyledPresentation;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TiOSNativeStyledControl : public Fmx::Presentation::Style::Common::TNativeStyledControl
{
	typedef Fmx::Presentation::Style::Common::TNativeStyledControl inherited;
	
private:
	TiOSNativeScene* __fastcall GetScene();
	
protected:
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall AdjustSize();
	__property TiOSNativeScene* Scene = {read=GetScene};
public:
	/* TStyledControl.Create */ inline __fastcall virtual TiOSNativeStyledControl(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Presentation::Style::Common::TNativeStyledControl(AOwner) { }
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TiOSNativeStyledControl() { }
	
};


class PASCALIMPLEMENTATION TiOSNativeScene : public Fmx::Presentation::Style::Common::TNativeScene
{
	typedef Fmx::Presentation::Style::Common::TNativeScene inherited;
	
private:
	Fmx::Graphics::TCanvas* FCanvas;
	Iosapi::Uikit::_di_UIView __fastcall GetView();
	Fmx::Platform::Ios::TiOSWindowHandle* __fastcall GetHandle();
	TiOSStyledPresentation* __fastcall GetPresentation();
	TiOSNativeStyledControl* __fastcall GetStyledControl();
	
protected:
	virtual void __fastcall DoAddUpdateRect(const System::Types::TRectF &R);
	virtual Fmx::Graphics::TCanvas* __fastcall DoGetCanvas();
	virtual float __fastcall DoGetSceneScale();
	virtual Fmx::Controls::TStyleBook* __fastcall DoGetStyleBook();
	virtual System::Types::TPointF __fastcall DoLocalToScreen(const System::Types::TPointF &P);
	virtual System::Types::TPointF __fastcall DoScreenToLocal(const System::Types::TPointF &P);
	virtual void __fastcall DoResized(const System::Types::TSizeF &NewSize);
	virtual Fmx::Controls::TControl* __fastcall GetPresentedControl();
	
public:
	__fastcall TiOSNativeScene(TiOSStyledPresentation* APresentation);
	__fastcall virtual ~TiOSNativeScene();
	void __fastcall Paint();
	__property TiOSStyledPresentation* Presentation = {read=GetPresentation};
	__property Fmx::Platform::Ios::TiOSWindowHandle* Handle = {read=GetHandle};
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
	__property TiOSNativeStyledControl* StyledControl = {read=GetStyledControl};
};


__interface  INTERFACE_UUID("{3A907753-FF20-4EB7-A791-E30C62016759}") IiOSGLKSceneControl  : public Iosapi::Glkit::GLKView 
{
	HIDESBASE virtual void __cdecl drawRect(Iosapi::Foundation::NSRect R) = 0 ;
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

__interface  INTERFACE_UUID("{8A835023-0C2E-4BEF-B0C9-40691CF915CD}") IiOSMTKSceneControl  : public Macapi::Metalkit::MTKView 
{
	HIDESBASE virtual void __cdecl touchesBegan(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesCancelled(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesEnded(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
	HIDESBASE virtual void __cdecl touchesMoved(Iosapi::Foundation::_di_NSSet touches, Iosapi::Uikit::_di_UIEvent withEvent) = 0 ;
};

class PASCALIMPLEMENTATION TiOSStyledPresentation : public Fmx::Presentation::Ios::TiOSNativeView
{
	typedef Fmx::Presentation::Ios::TiOSNativeView inherited;
	
private:
	TiOSNativeScene* FNativeScene;
	HIDESBASE Iosapi::Uikit::_di_UIView __fastcall GetView();
	TiOSNativeStyledControl* __fastcall GetStyledControl();
	
protected:
	virtual System::Typinfo::PTypeInfo __fastcall GetObjectiveCClass();
	virtual void __fastcall InitView();
	virtual void __fastcall SetSize(const System::Types::TSizeF &ASize);
	virtual System::UnicodeString __fastcall GetDefaultStyleLookupName();
	virtual System::UnicodeString __fastcall GetParentClassStyleLookupName();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
	virtual void __fastcall DoApplyStyleLookup();
	
public:
	__fastcall virtual TiOSStyledPresentation()/* overload */;
	__fastcall virtual ~TiOSStyledPresentation();
	virtual void __fastcall Dispatch(void *Message);
	void __cdecl drawRect(Iosapi::Foundation::NSRect R);
	__property Iosapi::Uikit::_di_UIView View = {read=GetView};
	__property TiOSNativeStyledControl* StyledControl = {read=GetStyledControl};
public:
	/* TiOSNativeView.Create */ inline __fastcall virtual TiOSStyledPresentation(Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Ios::TiOSNativeView(AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Ios */
}	/* namespace Presentation */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_IOS_STYLE)
using namespace Fmx::Presentation::Ios::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_PRESENTATION_IOS)
using namespace Fmx::Presentation::Ios;
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
#endif	// Fmx_Presentation_Ios_StyleHPP
