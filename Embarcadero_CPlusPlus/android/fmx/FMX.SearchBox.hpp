// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FMX.SearchBox.pas' rev: 34.00 (Android)

#ifndef Fmx_SearchboxHPP
#define Fmx_SearchboxHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Controls.Model.hpp>
#include <FMX.Presentation.Messages.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Types.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Fmx
{
namespace Searchbox
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSearchBoxModel;
class DELPHICLASS TSearchBox;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TFilterEvent)(System::TObject* Sender, const System::UnicodeString AFilter, const System::UnicodeString AValue, bool &Accept);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSearchBoxModel : public Fmx::Edit::TCustomEditModel
{
	typedef Fmx::Edit::TCustomEditModel inherited;
	
private:
	Fmx::Controls::_di_ISearchResponder FSearchResponder;
	TFilterEvent FOnFilter;
	
protected:
	virtual void __fastcall DoChangeTracking();
	
public:
	__property Fmx::Controls::_di_ISearchResponder SearchResponder = {read=FSearchResponder, write=FSearchResponder};
	__property TFilterEvent OnFilter = {read=FOnFilter, write=FOnFilter};
public:
	/* TCustomEditModel.Create */ inline __fastcall virtual TSearchBoxModel()/* overload */ : Fmx::Edit::TCustomEditModel() { }
	/* TCustomEditModel.Destroy */ inline __fastcall virtual ~TSearchBoxModel() { }
	
public:
	/* TDataModel.Create */ inline __fastcall virtual TSearchBoxModel(System::Classes::TComponent* const AOwner)/* overload */ : Fmx::Edit::TCustomEditModel(AOwner) { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TSearchBox : public Fmx::Edit::TEdit
{
	typedef Fmx::Edit::TEdit inherited;
	
private:
	TFilterEvent __fastcall GetOnFilter();
	void __fastcall SetOnFilter(const TFilterEvent Value);
	HIDESBASE TSearchBoxModel* __fastcall GetModel()/* overload */;
	
protected:
	virtual System::UnicodeString __fastcall DefinePresentationName();
	virtual Fmx::Controls::Model::TDataModelClass __fastcall DefineModelClass();
	virtual void __fastcall ParentChanged();
	
public:
	__fastcall virtual TSearchBox(System::Classes::TComponent* AOwner)/* overload */;
	__property TSearchBoxModel* Model = {read=GetModel};
	
__published:
	__property TFilterEvent OnFilter = {read=GetOnFilter, write=SetOnFilter};
public:
	/* TCustomEdit.Destroy */ inline __fastcall virtual ~TSearchBox() { }
	
private:
	void *__IListBoxHeaderTrait;	// Fmx::Controls::IListBoxHeaderTrait 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C7BDF195-C1E2-48F9-9376-1382C60A6BCC}
	operator Fmx::Controls::_di_IListBoxHeaderTrait()
	{
		Fmx::Controls::_di_IListBoxHeaderTrait intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Fmx::Controls::IListBoxHeaderTrait*(void) { return (Fmx::Controls::IListBoxHeaderTrait*)&__IListBoxHeaderTrait; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Searchbox */
}	/* namespace Fmx */
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
#endif	// Fmx_SearchboxHPP
