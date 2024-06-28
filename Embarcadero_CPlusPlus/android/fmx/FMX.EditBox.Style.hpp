// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.EditBox.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Editbox_StyleHPP
#define Fmx_Editbox_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.EditBox.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Editbox
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledEditBox;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledEditBox : public Fmx::Edit::Style::TStyledEdit
{
	typedef Fmx::Edit::Style::TStyledEdit inherited;
	
private:
	HIDESBASE Fmx::Editbox::TEditBoxModel* __fastcall GetModel()/* overload */;
	Fmx::Editbox::TCustomEditBox* __fastcall GetEditBox();
	
protected:
	MESSAGE void __fastcall MMValueTypeChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMDecimalDigitsChanged(System::TDispatchMessage &AMessage);
	MESSAGE void __fastcall MMValueRangeChanged(System::TDispatchMessage &AMessage);
	virtual void __fastcall KeyDown(System::Word &Key, System::WideChar &KeyChar, System::Classes::TShiftState Shift);
	virtual void __fastcall MouseWheel(System::Classes::TShiftState Shift, int WheelDelta, bool &Handled);
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	
public:
	__property Fmx::Editbox::TEditBoxModel* Model = {read=GetModel};
	__property Fmx::Editbox::TCustomEditBox* EditBox = {read=GetEditBox};
public:
	/* TStyledEdit.Create */ inline __fastcall virtual TStyledEditBox(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Edit::Style::TStyledEdit(AOwner) { }
	/* TStyledEdit.Destroy */ inline __fastcall virtual ~TStyledEditBox() { }
	
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledEditBox(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Edit::Style::TStyledEdit(AOwner, AModel, AControl) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Editbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDITBOX_STYLE)
using namespace Fmx::Editbox::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_EDITBOX)
using namespace Fmx::Editbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Editbox_StyleHPP
