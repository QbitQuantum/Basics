// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPDm.pas' rev: 34.00 (Windows)

#ifndef Soap_SoapdmHPP
#define Soap_SoapdmHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <System.Win.ComObj.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Classes.hpp>
#include <Datasnap.Midas.hpp>
#include <Datasnap.Provider.hpp>
#include <System.SysUtils.hpp>
#include <Web.HTTPApp.hpp>
#include <Soap.SOAPMidas.hpp>
#include <System.Types.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

/* Automatically link to SOAPMidas where IAppServer is registered */
#ifndef _WIN64
#pragma link "Soap.SOAPMidas.obj"
#endif /* not _WIN64 */


namespace Soap
{
namespace Soapdm
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSoapDataModule;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSoapDataModule : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
private:
	System::Generics::Collections::TList__1<Datasnap::Provider::TCustomProvider*>* FProviders;
	System::Syncobjs::TCriticalSection* FCriticalSection;
	int FRefCount;
	int __fastcall GetProviderCount();
	
protected:
	virtual Datasnap::Provider::TCustomProvider* __fastcall GetProvider(const System::UnicodeString ProviderName);
	System::OleVariant __fastcall GetProviderNames();
	System::OleVariant __fastcall ApplyUpdates(const System::WideString ProviderName, const System::OleVariant &Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData);
	System::OleVariant __fastcall GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	System::OleVariant __fastcall DataRequest(const System::WideString ProviderName, const System::OleVariant &Data);
	System::OleVariant __fastcall GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData);
	System::OleVariant __fastcall RowRequest(const System::WideString ProviderName, const System::OleVariant &Row, int RequestType, System::OleVariant &OwnerData);
	void __fastcall Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual System::OleVariant __stdcall SAS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData);
	virtual System::OleVariant __stdcall SAS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	virtual System::OleVariant __stdcall SAS_DataRequest(const System::WideString ProviderName, System::OleVariant Data);
#ifndef _WIN64
	virtual System::DynamicArray<System::WideString> __stdcall SAS_GetProviderNames();
#else /* _WIN64 */
	virtual System::TArray__1<System::WideString> __stdcall SAS_GetProviderNames();
#endif /* _WIN64 */
	virtual System::OleVariant __stdcall SAS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData);
	virtual System::OleVariant __stdcall SAS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData);
	virtual void __stdcall SAS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	
public:
	__fastcall virtual TSoapDataModule(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSoapDataModule();
	virtual void __fastcall AfterConstruction();
	virtual void __fastcall BeforeDestruction();
	__classmethod virtual System::TObject* __fastcall NewInstance();
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	virtual void __fastcall Lock();
	virtual void __fastcall Unlock();
	void __fastcall RegisterProvider(Datasnap::Provider::TCustomProvider* Value);
	void __fastcall UnRegisterProvider(Datasnap::Provider::TCustomProvider* Value);
	__property Datasnap::Provider::TCustomProvider* Providers[const System::UnicodeString ProviderName] = {read=GetProvider};
	__property int ProviderCount = {read=GetProviderCount, nodefault};
	__property int RefCount = {read=FRefCount, nodefault};
	virtual HRESULT __fastcall SafeCallException(System::TObject* ExceptObject, void * ExceptAddr);
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TSoapDataModule(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	
private:
	void *__IProviderContainer;	// Datasnap::Provider::IProviderContainer 
	void *__IAppServerSOAP;	// Soap::Soapmidas::IAppServerSOAP 
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {EEE9FFD4-752F-11D4-80DD-00C04F6BB88C}
	operator Datasnap::Provider::_di_IProviderContainer()
	{
		Datasnap::Provider::_di_IProviderContainer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Datasnap::Provider::IProviderContainer*(void) { return (Datasnap::Provider::IProviderContainer*)&__IProviderContainer; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {C99F4735-D6D2-495C-8CA2-E53E5A439E61}
	operator Soap::Soapmidas::_di_IAppServerSOAP()
	{
		Soap::Soapmidas::_di_IAppServerSOAP intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Soapmidas::IAppServerSOAP*(void) { return (Soap::Soapmidas::IAppServerSOAP*)&__IAppServerSOAP; }
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
}	/* namespace Soapdm */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPDM)
using namespace Soap::Soapdm;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapdmHPP
