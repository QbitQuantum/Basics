// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.MultiView.Types.Style.pas' rev: 34.00 (iOS)

#ifndef Fmx_Multiview_Types_StyleHPP
#define Fmx_Multiview_Types_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <FMX.Types.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.MultiView.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Controls.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Multiview
{
namespace Types
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledTouchInterceptingLayout;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStyledTouchInterceptingLayout : public Fmx::Presentation::Style::TStyledPresentation
{
	typedef Fmx::Presentation::Style::TStyledPresentation inherited;
	
private:
	Fmx::Objects::TRectangle* FShadow;
	HIDESBASE Fmx::Multiview::Types::TTouchInterceptingLayoutModel* __fastcall GetModel();
	
protected:
	MESSAGE void __fastcall MMColorChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<System::Uitypes::TAlphaColor> &AMessage);
	MESSAGE void __fastcall MMEnabledShadowChanged(Fmx::Presentation::Messages::TDispatchMessageWithValue__1<bool> &AMessage);
	MESSAGE void __fastcall PMInit(System::TDispatchMessage &AMessage);
	
public:
	__fastcall virtual TStyledTouchInterceptingLayout(System::Classes::TComponent* AOwner)/* overload */;
	virtual bool __fastcall PointInObjectLocal(float X, float Y);
	__property Fmx::Multiview::Types::TTouchInterceptingLayoutModel* Model = {read=GetModel};
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledTouchInterceptingLayout(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Presentation::Style::TStyledPresentation(AOwner, AModel, AControl) { }
	
public:
	/* TStyledControl.Destroy */ inline __fastcall virtual ~TStyledTouchInterceptingLayout() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Types */
}	/* namespace Multiview */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_MULTIVIEW_TYPES_STYLE)
using namespace Fmx::Multiview::Types::Style;
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
#endif	// Fmx_Multiview_Types_StyleHPP
