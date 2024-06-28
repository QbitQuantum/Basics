// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.NumberBox.Style.pas' rev: 34.00 (Windows)

#ifndef Fmx_Numberbox_StyleHPP
#define Fmx_Numberbox_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.UITypes.hpp>
#include <System.Classes.hpp>
#include <FMX.EditBox.Style.hpp>
#include <FMX.NumberBox.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Numberbox
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledNumberBox;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TStyledNumberBox : public Fmx::Editbox::Style::TStyledEditBox
{
	typedef Fmx::Editbox::Style::TStyledEditBox inherited;
	
	
public:
	enum class DECLSPEC_DENUM TMouseMoved : unsigned char { None, Vertical, Horizontal };
	
	
public:
	static const System::Int8 Backlash = System::Int8(0x5);
	
	static const System::Int8 MinimumMovement = System::Int8(0x1);
	
	
private:
	TMouseMoved FMouseMoved;
	System::Types::TPointF FPressedPos;
	HIDESBASE Fmx::Numberbox::TNumberBoxModel* __fastcall GetModel();
	
protected:
	virtual void __fastcall MouseDown(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseMove(System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall MouseUp(System::Uitypes::TMouseButton Button, System::Classes::TShiftState Shift, float X, float Y);
	virtual void __fastcall SetText(const System::UnicodeString AText);
	__property TMouseMoved MouseMoved = {read=FMouseMoved, nodefault};
	
public:
	__property Fmx::Numberbox::TNumberBoxModel* Model = {read=GetModel};
public:
	/* TStyledEdit.Create */ inline __fastcall virtual TStyledNumberBox(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Editbox::Style::TStyledEditBox(AOwner) { }
	/* TStyledEdit.Destroy */ inline __fastcall virtual ~TStyledNumberBox() { }
	
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledNumberBox(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Editbox::Style::TStyledEditBox(AOwner, AModel, AControl) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Numberbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_NUMBERBOX_STYLE)
using namespace Fmx::Numberbox::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_NUMBERBOX)
using namespace Fmx::Numberbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Numberbox_StyleHPP
