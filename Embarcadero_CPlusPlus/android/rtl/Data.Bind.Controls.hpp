// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.Bind.Controls.pas' rev: 34.00 (Android)

#ifndef Data_Bind_ControlsHPP
#define Data_Bind_ControlsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.Bind.Components.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------
namespace Data
{
namespace Bind
{
namespace Controls
{
  _INIT_UNIT(Data_Bind_Controls);
}	/* namespace Controls */
}	/* namespace Bind */
}	/* namespace Data */

namespace Data
{
namespace Bind
{
namespace Controls
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBindNavigatorController;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TNavigateButton : unsigned char { nbFirst, nbPrior, nbNext, nbLast, nbInsert, nbDelete, nbEdit, nbPost, nbCancel, nbRefresh, nbApplyUpdates, nbCancelUpdates };

typedef System::Set<TNavigateButton, TNavigateButton::nbFirst, TNavigateButton::nbCancelUpdates> TNavigateButtons;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TBindNavigatorController : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	Data::Bind::Components::TBaseBindScopeComponent* FDataSource;
	Data::Bind::Components::_di_IScopeNavigator FScopeNavigator;
	Data::Bind::Components::_di_IScopeNavigatorUpdates FScopeNavigatorUpdates;
	Data::Bind::Components::_di_IScopeState FScopeState;
	Data::Bind::Components::_di_IScopeEditor FScopeEditor;
	System::Classes::TNotifyEvent FOnDataChanged;
	System::Classes::TNotifyEvent FOnEditingChanged;
	System::Classes::TNotifyEvent FOnActiveChanged;
	bool __fastcall GetActive();
	bool __fastcall GetBOF();
	bool __fastcall GetEOF();
	bool __fastcall GetSelected();
	bool __fastcall GetEditing();
	void __fastcall SetDataSource(Data::Bind::Components::TBaseBindScopeComponent* const Value);
	bool __fastcall GetCanModify();
	bool __fastcall GetCanInsert();
	bool __fastcall GetCanDelete();
	bool __fastcall GetCanRefresh();
	void __fastcall DoOnEditingChanged(System::TObject* Sender);
	void __fastcall DoOnDataChanged(System::TObject* Sender);
	void __fastcall DoOnDataScrolled(System::TObject* Sender, int Distance);
	void __fastcall DoOnActiveChanged(System::TObject* Sender);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TBindNavigatorController(System::Classes::TComponent* AComponent);
	__fastcall virtual ~TBindNavigatorController();
	void __fastcall EnableButtons(TNavigateButtons AButtons, bool ADataSourceEnabled, System::DelphiInterface<System::Sysutils::TProc__2<TNavigateButton,bool> > ASetEnabled);
	void __fastcall DisableButtons(System::DelphiInterface<System::Sysutils::TProc__2<TNavigateButton,bool> > ASetEnabled);
	void __fastcall ExecuteButton(TNavigateButton AButton, System::DelphiInterface<System::Sysutils::TFunc__1<bool> > AConfirmDelete);
	void __fastcall Next();
	void __fastcall Prior();
	void __fastcall First();
	void __fastcall Last();
	HIDESBASE void __fastcall Insert();
	void __fastcall Delete();
	void __fastcall Cancel();
	void __fastcall Post();
	void __fastcall Refresh();
	void __fastcall Edit();
	void __fastcall ApplyUpdates();
	void __fastcall CancelUpdates();
	bool __fastcall CanApplyUpdates();
	bool __fastcall CanCancelUpdates();
	__property bool Active = {read=GetActive, nodefault};
	__property bool Editing = {read=GetEditing, nodefault};
	__property bool Eof = {read=GetEOF, nodefault};
	__property bool BOF = {read=GetBOF, nodefault};
	__property bool Selected = {read=GetSelected, nodefault};
	__property Data::Bind::Components::TBaseBindScopeComponent* DataSource = {read=FDataSource, write=SetDataSource};
	__property bool CanModify = {read=GetCanModify, nodefault};
	__property bool CanInsert = {read=GetCanInsert, nodefault};
	__property bool CanDelete = {read=GetCanDelete, nodefault};
	__property bool CanRefresh = {read=GetCanRefresh, nodefault};
	__property System::Classes::TNotifyEvent OnEditingChanged = {read=FOnEditingChanged, write=FOnEditingChanged};
	__property System::Classes::TNotifyEvent OnDataChanged = {read=FOnDataChanged, write=FOnDataChanged};
	__property System::Classes::TNotifyEvent OnActiveChanged = {read=FOnActiveChanged, write=FOnActiveChanged};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define NavigatorScrollButtons (System::Set<TNavigateButton, TNavigateButton::nbFirst, TNavigateButton::nbCancelUpdates>() << TNavigateButton::nbFirst << TNavigateButton::nbPrior << TNavigateButton::nbNext << TNavigateButton::nbLast )
#define NavigatorEditButtons (System::Set<TNavigateButton, TNavigateButton::nbFirst, TNavigateButton::nbCancelUpdates>() << TNavigateButton::nbInsert << TNavigateButton::nbDelete << TNavigateButton::nbEdit << TNavigateButton::nbPost << TNavigateButton::nbCancel << TNavigateButton::nbRefresh << TNavigateButton::nbApplyUpdates << TNavigateButton::nbCancelUpdates )
#define NavigatorButtons (System::Set<TNavigateButton, TNavigateButton::nbFirst, TNavigateButton::nbCancelUpdates>() << TNavigateButton::nbFirst << TNavigateButton::nbPrior << TNavigateButton::nbNext << TNavigateButton::nbLast << TNavigateButton::nbInsert << TNavigateButton::nbDelete << TNavigateButton::nbEdit << TNavigateButton::nbPost << TNavigateButton::nbCancel << TNavigateButton::nbRefresh << TNavigateButton::nbApplyUpdates << TNavigateButton::nbCancelUpdates )
#define NavigatorDefaultButtons (System::Set<TNavigateButton, TNavigateButton::nbFirst, TNavigateButton::nbCancelUpdates>() << TNavigateButton::nbFirst << TNavigateButton::nbPrior << TNavigateButton::nbNext << TNavigateButton::nbLast << TNavigateButton::nbInsert << TNavigateButton::nbDelete << TNavigateButton::nbEdit << TNavigateButton::nbPost << TNavigateButton::nbCancel << TNavigateButton::nbRefresh )
}	/* namespace Controls */
}	/* namespace Bind */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND_CONTROLS)
using namespace Data::Bind::Controls;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_BIND)
using namespace Data::Bind;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_Bind_ControlsHPP
