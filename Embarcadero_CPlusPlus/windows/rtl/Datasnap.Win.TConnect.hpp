// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.Win.TConnect.pas' rev: 34.00 (Windows)

#ifndef Datasnap_Win_TconnectHPP
#define Datasnap_Win_TconnectHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Datasnap.Midas.hpp>
#include <Data.DB.hpp>
#include <Datasnap.DBClient.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.ActiveX.hpp>
#include <System.Win.ComObj.hpp>
#include <Datasnap.Provider.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Win
{
namespace Tconnect
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TLocalConnection;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TLocalConnection : public Datasnap::Dbclient::TCustomRemoteServer
{
	typedef Datasnap::Dbclient::TCustomRemoteServer inherited;
	
private:
	Datasnap::Midas::_di_IAppServer FAppServer;
	System::Classes::TList* FProviders;
	int __fastcall GetProviderCount();
	
protected:
	virtual Datasnap::Provider::TCustomProvider* __fastcall GetProvider(const System::UnicodeString ProviderName);
	HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	HRESULT __stdcall InterfaceSupportsErrorInfo(const GUID &iid);
	virtual bool __fastcall GetConnected();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall RegisterProvider(Datasnap::Provider::TCustomProvider* Prov);
	void __fastcall UnRegisterProvider(Datasnap::Provider::TCustomProvider* Prov);
	
public:
	__fastcall virtual TLocalConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TLocalConnection();
	__property Datasnap::Midas::_di_IAppServer AppServer = {read=FAppServer};
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	virtual void __fastcall GetProviderNames(System::Classes::TGetStrProc Proc);
	__property Datasnap::Provider::TCustomProvider* Providers[const System::UnicodeString ProviderName] = {read=GetProvider};
	__property int ProviderCount = {read=GetProviderCount, nodefault};
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
private:
	void *__ISupportErrorInfo;	// ISupportErrorInfo 
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {DF0B3D60-548F-101B-8E65-08002B2BD119}
	operator _di_ISupportErrorInfo()
	{
		_di_ISupportErrorInfo intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator ISupportErrorInfo*(void) { return (ISupportErrorInfo*)&__ISupportErrorInfo; }
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
}	/* namespace Tconnect */
}	/* namespace Win */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_WIN_TCONNECT)
using namespace Datasnap::Win::Tconnect;
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
#endif	// Datasnap_Win_TconnectHPP
