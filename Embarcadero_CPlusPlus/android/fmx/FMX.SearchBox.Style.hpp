// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.SearchBox.Style.pas' rev: 34.00 (Android)

#ifndef Fmx_Searchbox_StyleHPP
#define Fmx_Searchbox_StyleHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <FMX.Edit.Style.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Presentation.Style.hpp>
#include <FMX.Types.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Searchbox
{
namespace Style
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TStyledSearchBox;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TStyledSearchBox : public Fmx::Edit::Style::TStyledEdit
{
	typedef Fmx::Edit::Style::TStyledEdit inherited;
	
private:
	Fmx::Edit::TEditButton* FMagGlass;
	Fmx::Edit::TEditButton* FClearButton;
	void __fastcall RealignButtons();
	
protected:
	virtual void __fastcall RealignButtonsContainer();
	virtual void __fastcall DoChangeTracking();
	virtual void __fastcall ApplyStyle();
	virtual void __fastcall FreeStyle();
public:
	/* TStyledEdit.Create */ inline __fastcall virtual TStyledSearchBox(System::Classes::TComponent* AOwner)/* overload */ : Fmx::Edit::Style::TStyledEdit(AOwner) { }
	/* TStyledEdit.Destroy */ inline __fastcall virtual ~TStyledSearchBox() { }
	
public:
	/* TStyledPresentation.Create */ inline __fastcall virtual TStyledSearchBox(System::Classes::TComponent* AOwner, Fmx::Controls::Model::TDataModel* const AModel, Fmx::Controls::TControl* const AControl)/* overload */ : Fmx::Edit::Style::TStyledEdit(AOwner, AModel, AControl) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Style */
}	/* namespace Searchbox */
}	/* namespace Fmx */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SEARCHBOX_STYLE)
using namespace Fmx::Searchbox::Style;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX_SEARCHBOX)
using namespace Fmx::Searchbox;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FMX)
using namespace Fmx;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Fmx_Searchbox_StyleHPP
