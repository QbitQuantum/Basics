// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Win.MtsRdm.pas' rev: 34.00 (Windows)

#ifndef Datasnap_Win_MtsrdmHPP
#define Datasnap_Win_MtsrdmHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DataBkr.hpp>
#include <Winapi.Mtx.hpp>
#include <Datasnap.Midas.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Win
{
namespace Mtsrdm
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMtsDataModule;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TMtsDataModule : public Datasnap::Databkr::TRemoteDataModule
{
	typedef Datasnap::Databkr::TRemoteDataModule inherited;
	
private:
	bool FAutoComplete;
	System::Classes::TNotifyEvent FOnActivate;
	System::Classes::TNotifyEvent FOnDeActivate;
	_di_IObjectContext FObjectContext;
	bool FCanBePooled;
	
protected:
	HRESULT __safecall Activate();
	void __stdcall Deactivate();
	virtual System::LongBool __stdcall CanBePooled();
	HIDESBASE HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HIDESBASE HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HIDESBASE HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HIDESBASE HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HIDESBASE HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HIDESBASE HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HIDESBASE HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual void __fastcall CallComplete(bool Complete);
	__property _di_IObjectContext ObjectContext = {read=FObjectContext};
	
public:
	__fastcall virtual TMtsDataModule(System::Classes::TComponent* AOwner);
	void __fastcall SetComplete();
	void __fastcall SetAbort();
	void __fastcall EnableCommit();
	void __fastcall DisableCommit();
	bool __fastcall IsInTransaction();
	bool __fastcall IsSecurityEnabled();
	bool __fastcall IsCallerInRole(const System::WideString Role);
	
__published:
	__property bool AutoComplete = {read=FAutoComplete, write=FAutoComplete, default=1};
	__property System::Classes::TNotifyEvent OnActivate = {read=FOnActivate, write=FOnActivate};
	__property System::Classes::TNotifyEvent OnDeactivate = {read=FOnDeActivate, write=FOnDeActivate};
	__property bool Pooled = {read=FCanBePooled, write=FCanBePooled, nodefault};
public:
	/* TRemoteDataModule.Destroy */ inline __fastcall virtual ~TMtsDataModule() { }
	
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TMtsDataModule(System::Classes::TComponent* AOwner, int Dummy) : Datasnap::Databkr::TRemoteDataModule(AOwner, Dummy) { }
	
private:
	void *__IObjectControl;	// IObjectControl 
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {51372AEC-CAE7-11CF-BE81-00AA00A2FA25}
	operator _di_IObjectControl()
	{
		_di_IObjectControl intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IObjectControl*(void) { return (IObjectControl*)&__IObjectControl; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {1AEFCC20-7A24-11D2-98B0-C69BEB4B5B6D}
	operator Datasnap::Midas::_di_IAppServer()
	{
		Datasnap::Midas::_di_IAppServer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Datasnap::Midas::IAppServer*(void) { return (Datasnap::Midas::IAppServer*)&__IAppServer; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mtsrdm */
}	/* namespace Win */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN_MTSRDM)
using namespace Datasnap::Win::Mtsrdm;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN)
using namespace Datasnap::Win;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_Win_MtsrdmHPP
