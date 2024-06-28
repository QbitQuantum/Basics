// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DataBkr.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DatabkrHPP
#define Datasnap_DatabkrHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Datasnap.Midas.hpp>
#include <Datasnap.Provider.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Databkr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TProviderDataModule;
class DELPHICLASS TRemoteDataModule;
class DELPHICLASS TCRemoteDataModule;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TProviderDataModule : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
private:
	System::Generics::Collections::TList__1<Datasnap::Provider::TCustomProvider*>* FProviders;
	int __fastcall GetProviderCount();
	
protected:
	virtual Datasnap::Provider::TCustomProvider* __fastcall GetProvider(const System::UnicodeString ProviderName);
	void __fastcall CleanProviders();
	
public:
	__fastcall virtual TProviderDataModule(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TProviderDataModule();
	System::OleVariant __fastcall ProviderNamesToVariant();
	virtual void __fastcall RegisterProvider(Datasnap::Provider::TCustomProvider* Value);
	virtual void __fastcall UnRegisterProvider(Datasnap::Provider::TCustomProvider* Value);
	__property Datasnap::Provider::TCustomProvider* Providers[const System::UnicodeString ProviderName] = {read=GetProvider};
	__property int ProviderCount = {read=GetProviderCount, nodefault};
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TProviderDataModule(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TRemoteDataModule : public TProviderDataModule
{
	typedef TProviderDataModule inherited;
	
private:
	System::TObject* FLock;
	
protected:
	__classmethod virtual void __fastcall UpdateRegistry(bool Register, const System::UnicodeString ClassID, const System::UnicodeString ProgID);
	HRESULT __safecall AS_GetProviderNames(System::OleVariant &__AS_GetProviderNames_result);
	HRESULT __safecall AS_ApplyUpdates(const System::WideString ProviderName, System::OleVariant Delta, int MaxErrors, /* out */ int &ErrorCount, System::OleVariant &OwnerData, System::OleVariant &__AS_ApplyUpdates_result);
	HRESULT __safecall AS_GetRecords(const System::WideString ProviderName, int Count, /* out */ int &RecsOut, int Options, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData, System::OleVariant &__AS_GetRecords_result);
	HRESULT __safecall AS_DataRequest(const System::WideString ProviderName, System::OleVariant Data, System::OleVariant &__AS_DataRequest_result);
	HRESULT __safecall AS_GetParams(const System::WideString ProviderName, System::OleVariant &OwnerData, System::OleVariant &__AS_GetParams_result);
	HRESULT __safecall AS_RowRequest(const System::WideString ProviderName, System::OleVariant Row, int RequestType, System::OleVariant &OwnerData, System::OleVariant &__AS_RowRequest_result);
	HRESULT __safecall AS_Execute(const System::WideString ProviderName, const System::WideString CommandText, System::OleVariant &Params, System::OleVariant &OwnerData);
	
public:
	__fastcall virtual TRemoteDataModule(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TRemoteDataModule();
	virtual void __fastcall Lock();
	virtual void __fastcall Unlock();
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TRemoteDataModule(System::Classes::TComponent* AOwner, int Dummy) : TProviderDataModule(AOwner, Dummy) { }
	
private:
	void *__IAppServer;	// Datasnap::Midas::IAppServer 
	
public:
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


#ifndef _WIN64
typedef System::TMetaClass* TRemoteDataModuleClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TRemoteDataModuleClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TCRemoteDataModule : public System::Classes::TDataModule
{
	typedef System::Classes::TDataModule inherited;
	
private:
	System::Generics::Collections::TList__1<Datasnap::Provider::TCustomProvider*>* FProviders;
	System::TObject* FLock;
	int __fastcall GetProviderCount();
	
public:
	__fastcall virtual TCRemoteDataModule(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCRemoteDataModule();
	virtual void __fastcall RegisterProvider(Datasnap::Provider::TCustomProvider* Value);
	virtual void __fastcall UnRegisterProvider(Datasnap::Provider::TCustomProvider* Value);
	virtual void __fastcall Lock();
	virtual void __fastcall UnLock();
	System::OleVariant __fastcall CRDMGetProviderNames();
	virtual Datasnap::Provider::TCustomProvider* __fastcall GetProvider(const System::UnicodeString ProviderName);
	__property Datasnap::Provider::TCustomProvider* Providers[const System::UnicodeString ProviderName] = {read=GetProvider};
	__property int ProviderCount = {read=GetProviderCount, nodefault};
public:
	/* TDataModule.CreateNew */ inline __fastcall virtual TCRemoteDataModule(System::Classes::TComponent* AOwner, int Dummy) : System::Classes::TDataModule(AOwner, Dummy) { }
	
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterPooled(const System::UnicodeString ClassID, int Max, int Timeout, bool Singleton = false);
extern DELPHI_PACKAGE void __fastcall UnregisterPooled(const System::UnicodeString ClassID);
extern DELPHI_PACKAGE void __fastcall EnableSocketTransport(const System::UnicodeString ClassID);
extern DELPHI_PACKAGE void __fastcall DisableSocketTransport(const System::UnicodeString ClassID);
extern DELPHI_PACKAGE void __fastcall EnableWebTransport(const System::UnicodeString ClassID);
extern DELPHI_PACKAGE void __fastcall DisableWebTransport(const System::UnicodeString ClassID);
}	/* namespace Databkr */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DATABKR)
using namespace Datasnap::Databkr;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DatabkrHPP
