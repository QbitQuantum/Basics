﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.BindSource.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_BindsourceHPP
#define Rest_Backend_BindsourceHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <System.Generics.Collections.hpp>
#include <REST.Json.hpp>
#include <REST.Backend.Providers.hpp>
#include <Data.Bind.ObjectScope.hpp>
#include <REST.BindSource.hpp>
#include <Data.Bind.Components.hpp>
#include <System.SyncObjs.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Bindsource
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBackendBindSourceComponent;
template<typename TI, typename T> class DELPHICLASS TBackendBindSourceComponent__2;
template<typename TI, typename T> class DELPHICLASS TBackendBindSourceComponentAuth__2;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBackendBindSourceComponent : public Data::Bind::Objectscope::TBaseObjectBindSourceDelegate
{
	typedef Data::Bind::Objectscope::TBaseObjectBindSourceDelegate inherited;
	
private:
	Rest::Backend::Providers::_di_IBackendProvider FProvider;
	void __fastcall SetProvider(const Rest::Backend::Providers::_di_IBackendProvider Value);
	Rest::Backend::Providers::_di_IBackendProvider __fastcall GetProvider();
	
protected:
	virtual void __fastcall ProviderChanged();
	virtual GUID __fastcall GetServiceIID() = 0 ;
	Rest::Backend::Providers::_di_IBackendService __fastcall CreateService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	virtual void __fastcall ClearProvider();
	virtual void __fastcall UpdateProvider(const Rest::Backend::Providers::_di_IBackendProvider AProvider) = 0 ;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TBackendBindSourceComponent(System::Classes::TComponent* AOwner);
	__property GUID ServiceIID = {read=GetServiceIID};
	__property Rest::Backend::Providers::_di_IBackendProvider Provider = {read=FProvider, write=SetProvider};
public:
	/* TBaseBindScopeComponent.Destroy */ inline __fastcall virtual ~TBackendBindSourceComponent() { }
	
private:
	void *__IBackendServiceComponent;	// Rest::Backend::Providers::IBackendServiceComponent 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {085164DF-FCA7-45CD-BAC3-42C6B0B08170}
	operator Rest::Backend::Providers::_di_IBackendServiceComponent()
	{
		Rest::Backend::Providers::_di_IBackendServiceComponent intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Rest::Backend::Providers::IBackendServiceComponent*(void) { return (Rest::Backend::Providers::IBackendServiceComponent*)&__IBackendServiceComponent; }
	#endif
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TI, typename T> class PASCALIMPLEMENTATION TBackendBindSourceComponent__2 : public TBackendBindSourceComponent
{
	typedef TBackendBindSourceComponent inherited;
	
	
public:
	/* [Template Alias] */
	#if defined(__clang__)
	using TExecuteEvent = void __fastcall (__closure *)(System::TObject* Sender, T AApi);
	#endif
	
	
private:
	TI FBackendService;
	T FBackendServiceAPI;
	Rest::Backend::Providers::TBackendAPIThread__1<T>* FAPIThread;
	TI __fastcall CreateBackendService(const Rest::Backend::Providers::_di_IBackendProvider AProvider);
	void __fastcall SetAPIThread(Rest::Backend::Providers::TBackendAPIThread__1<T>* const Value);
	
protected:
	T __fastcall GetBackendServiceAPI();
	virtual void __fastcall ClearProvider();
	TI __fastcall GetBackendService();
	virtual GUID __fastcall GetServiceIID();
	virtual void __fastcall UpdateProvider(const Rest::Backend::Providers::_di_IBackendProvider AValue);
	virtual T __fastcall InternalCreateBackendServiceAPI() = 0 ;
	virtual T __fastcall InternalCreateIndependentBackendServiceAPI();
	
public:
	__fastcall virtual TBackendBindSourceComponent__2(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TBackendBindSourceComponent__2();
	__property Rest::Backend::Providers::TBackendAPIThread__1<T>* APIThread = {read=FAPIThread, write=SetAPIThread};
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename TI, typename T> class PASCALIMPLEMENTATION TBackendBindSourceComponentAuth__2 : public TBackendBindSourceComponent__2<TI,T>
{
	typedef TBackendBindSourceComponent__2<TI,T> inherited;
	
private:
	Rest::Backend::Providers::_di_IBackendAuthReg FAuth;
	Rest::Backend::Providers::_di_IAuthAccess FAuthAccess;
	void __fastcall SetAuth(const Rest::Backend::Providers::_di_IBackendAuthReg Value);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual Rest::Backend::Providers::_di_IAuthAccess __fastcall CreateAuthAccess();
	
public:
	__fastcall virtual ~TBackendBindSourceComponentAuth__2();
	__property Rest::Backend::Providers::_di_IBackendAuthReg Auth = {read=FAuth, write=SetAuth};
public:
	/* {REST_Backend_BindSource}TBackendBindSourceComponent<REST_Backend_BindSource_TBackendBindSourceComponentAuth<TI,T>_TI,REST_Backend_BindSource_TBackendBindSourceComponentAuth<TI,T>_T>.Create */ inline __fastcall virtual TBackendBindSourceComponentAuth__2(System::Classes::TComponent* AOwner) : TBackendBindSourceComponent__2<TI,T>(AOwner) { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bindsource */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_BINDSOURCE)
using namespace Rest::Backend::Bindsource;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND)
using namespace Rest::Backend;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Backend_BindsourceHPP
