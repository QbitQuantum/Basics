// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Security.Credentials.pas' rev: 34.00 (Windows)

#ifndef Winapi_Security_CredentialsHPP
#define Winapi_Security_CredentialsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.WinRT.hpp>
#include <System.Types.hpp>
#include <System.Win.WinRT.hpp>
#include <Winapi.CommonTypes.hpp>
#include <Winapi.CommonNames.hpp>

//-- user supplied -----------------------------------------------------------

namespace Winapi
{
namespace Security
{
namespace Credentials
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IWebAccountProvider;
typedef System::DelphiInterface<IWebAccountProvider> _di_IWebAccountProvider;
__interface DELPHIINTERFACE IWebAccount;
typedef System::DelphiInterface<IWebAccount> _di_IWebAccount;
__interface DELPHIINTERFACE IPasswordCredential;
typedef System::DelphiInterface<IPasswordCredential> _di_IPasswordCredential;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability_Delegate_Base> _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability> _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability;
__interface DELPHIINTERFACE IAsyncOperation_1__UI_UserConsentVerifierAvailability_Base;
typedef System::DelphiInterface<IAsyncOperation_1__UI_UserConsentVerifierAvailability_Base> _di_IAsyncOperation_1__UI_UserConsentVerifierAvailability_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__UI_UserConsentVerifierAvailability;
typedef System::DelphiInterface<IAsyncOperation_1__UI_UserConsentVerifierAvailability> _di_IAsyncOperation_1__UI_UserConsentVerifierAvailability;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult> _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult;
__interface DELPHIINTERFACE IAsyncOperation_1__UI_UserConsentVerificationResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__UI_UserConsentVerificationResult_Base> _di_IAsyncOperation_1__UI_UserConsentVerificationResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__UI_UserConsentVerificationResult;
typedef System::DelphiInterface<IAsyncOperation_1__UI_UserConsentVerificationResult> _di_IAsyncOperation_1__UI_UserConsentVerificationResult;
__interface DELPHIINTERFACE UI_IUserConsentVerifierStatics;
typedef System::DelphiInterface<UI_IUserConsentVerifierStatics> _di_UI_IUserConsentVerifierStatics;
__interface DELPHIINTERFACE IKeyCredentialOperationResult;
typedef System::DelphiInterface<IKeyCredentialOperationResult> _di_IKeyCredentialOperationResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult> _di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IKeyCredentialOperationResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IKeyCredentialOperationResult_Base> _di_IAsyncOperation_1__IKeyCredentialOperationResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IKeyCredentialOperationResult;
typedef System::DelphiInterface<IAsyncOperation_1__IKeyCredentialOperationResult> _di_IAsyncOperation_1__IKeyCredentialOperationResult;
__interface DELPHIINTERFACE IKeyCredentialAttestationResult;
typedef System::DelphiInterface<IKeyCredentialAttestationResult> _di_IKeyCredentialAttestationResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult> _di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IKeyCredentialAttestationResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IKeyCredentialAttestationResult_Base> _di_IAsyncOperation_1__IKeyCredentialAttestationResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IKeyCredentialAttestationResult;
typedef System::DelphiInterface<IAsyncOperation_1__IKeyCredentialAttestationResult> _di_IAsyncOperation_1__IKeyCredentialAttestationResult;
__interface DELPHIINTERFACE IKeyCredential;
typedef System::DelphiInterface<IKeyCredential> _di_IKeyCredential;
__interface DELPHIINTERFACE IKeyCredentialRetrievalResult;
typedef System::DelphiInterface<IKeyCredentialRetrievalResult> _di_IKeyCredentialRetrievalResult;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult> _di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult;
__interface DELPHIINTERFACE IAsyncOperation_1__IKeyCredentialRetrievalResult_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IKeyCredentialRetrievalResult_Base> _di_IAsyncOperation_1__IKeyCredentialRetrievalResult_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IKeyCredentialRetrievalResult;
typedef System::DelphiInterface<IAsyncOperation_1__IKeyCredentialRetrievalResult> _di_IAsyncOperation_1__IKeyCredentialRetrievalResult;
__interface DELPHIINTERFACE IKeyCredentialManagerStatics;
typedef System::DelphiInterface<IKeyCredentialManagerStatics> _di_IKeyCredentialManagerStatics;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IWebAccount_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IWebAccount_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IWebAccount_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IWebAccount;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IWebAccount> _di_AsyncOperationCompletedHandler_1__IWebAccount;
__interface DELPHIINTERFACE IAsyncOperation_1__IWebAccount_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IWebAccount_Base> _di_IAsyncOperation_1__IWebAccount_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IWebAccount;
typedef System::DelphiInterface<IAsyncOperation_1__IWebAccount> _di_IAsyncOperation_1__IWebAccount;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IWebAccountProvider_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IWebAccountProvider_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IWebAccountProvider_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IWebAccountProvider;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IWebAccountProvider> _di_AsyncOperationCompletedHandler_1__IWebAccountProvider;
__interface DELPHIINTERFACE IAsyncOperation_1__IWebAccountProvider_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IWebAccountProvider_Base> _di_IAsyncOperation_1__IWebAccountProvider_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IWebAccountProvider;
typedef System::DelphiInterface<IAsyncOperation_1__IWebAccountProvider> _di_IAsyncOperation_1__IWebAccountProvider;
__interface DELPHIINTERFACE IIterator_1__IWebAccount_Base;
typedef System::DelphiInterface<IIterator_1__IWebAccount_Base> _di_IIterator_1__IWebAccount_Base;
__interface DELPHIINTERFACE IIterator_1__IWebAccount;
typedef System::DelphiInterface<IIterator_1__IWebAccount> _di_IIterator_1__IWebAccount;
__interface DELPHIINTERFACE IIterable_1__IWebAccount_Base;
typedef System::DelphiInterface<IIterable_1__IWebAccount_Base> _di_IIterable_1__IWebAccount_Base;
__interface DELPHIINTERFACE IIterable_1__IWebAccount;
typedef System::DelphiInterface<IIterable_1__IWebAccount> _di_IIterable_1__IWebAccount;
__interface DELPHIINTERFACE IVectorView_1__IWebAccount;
typedef System::DelphiInterface<IVectorView_1__IWebAccount> _di_IVectorView_1__IWebAccount;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount_Delegate_Base;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount_Delegate_Base> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount_Delegate_Base;
__interface DELPHIINTERFACE AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount;
typedef System::DelphiInterface<AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount> _di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IWebAccount_Base;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IWebAccount_Base> _di_IAsyncOperation_1__IVectorView_1__IWebAccount_Base;
__interface DELPHIINTERFACE IAsyncOperation_1__IVectorView_1__IWebAccount;
typedef System::DelphiInterface<IAsyncOperation_1__IVectorView_1__IWebAccount> _di_IAsyncOperation_1__IVectorView_1__IWebAccount;
__interface DELPHIINTERFACE IWebAccountFactory;
typedef System::DelphiInterface<IWebAccountFactory> _di_IWebAccountFactory;
__interface DELPHIINTERFACE IWebAccount2;
typedef System::DelphiInterface<IWebAccount2> _di_IWebAccount2;
__interface DELPHIINTERFACE IWebAccountProviderFactory;
typedef System::DelphiInterface<IWebAccountProviderFactory> _di_IWebAccountProviderFactory;
__interface DELPHIINTERFACE IWebAccountProvider2;
typedef System::DelphiInterface<IWebAccountProvider2> _di_IWebAccountProvider2;
__interface DELPHIINTERFACE IWebAccountProvider3;
typedef System::DelphiInterface<IWebAccountProvider3> _di_IWebAccountProvider3;
__interface DELPHIINTERFACE ICredentialFactory;
typedef System::DelphiInterface<ICredentialFactory> _di_ICredentialFactory;
__interface DELPHIINTERFACE IIterator_1__IPasswordCredential_Base;
typedef System::DelphiInterface<IIterator_1__IPasswordCredential_Base> _di_IIterator_1__IPasswordCredential_Base;
__interface DELPHIINTERFACE IIterator_1__IPasswordCredential;
typedef System::DelphiInterface<IIterator_1__IPasswordCredential> _di_IIterator_1__IPasswordCredential;
__interface DELPHIINTERFACE IIterable_1__IPasswordCredential_Base;
typedef System::DelphiInterface<IIterable_1__IPasswordCredential_Base> _di_IIterable_1__IPasswordCredential_Base;
__interface DELPHIINTERFACE IIterable_1__IPasswordCredential;
typedef System::DelphiInterface<IIterable_1__IPasswordCredential> _di_IIterable_1__IPasswordCredential;
__interface DELPHIINTERFACE IVectorView_1__IPasswordCredential;
typedef System::DelphiInterface<IVectorView_1__IPasswordCredential> _di_IVectorView_1__IPasswordCredential;
__interface DELPHIINTERFACE IPasswordVault;
typedef System::DelphiInterface<IPasswordVault> _di_IPasswordVault;
class DELPHICLASS TUI_UserConsentVerifier;
class DELPHICLASS TKeyCredentialManager;
class DELPHICLASS TWebAccountProvider;
class DELPHICLASS TWebAccount;
class DELPHICLASS TPasswordCredential;
class DELPHICLASS TPasswordVault;
class DELPHICLASS TPasswordCredentialPropertyStore;
//-- type declarations -------------------------------------------------------
typedef _di_IWebAccountProvider *PIWebAccountProvider;

typedef _di_IWebAccount *PIWebAccount;

typedef _di_IPasswordCredential *PIPasswordCredential;

typedef _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability *PAsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability;

typedef _di_IAsyncOperation_1__UI_UserConsentVerifierAvailability *PIAsyncOperation_1__UI_UserConsentVerifierAvailability;

typedef _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult *PAsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult;

typedef _di_IAsyncOperation_1__UI_UserConsentVerificationResult *PIAsyncOperation_1__UI_UserConsentVerificationResult;

typedef _di_UI_IUserConsentVerifierStatics *PUI_IUserConsentVerifierStatics;

typedef _di_IKeyCredentialOperationResult *PIKeyCredentialOperationResult;

typedef _di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult *PAsyncOperationCompletedHandler_1__IKeyCredentialOperationResult;

typedef _di_IAsyncOperation_1__IKeyCredentialOperationResult *PIAsyncOperation_1__IKeyCredentialOperationResult;

typedef _di_IKeyCredentialAttestationResult *PIKeyCredentialAttestationResult;

typedef _di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult *PAsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult;

typedef _di_IAsyncOperation_1__IKeyCredentialAttestationResult *PIAsyncOperation_1__IKeyCredentialAttestationResult;

typedef _di_IKeyCredential *PIKeyCredential;

typedef _di_IKeyCredentialRetrievalResult *PIKeyCredentialRetrievalResult;

typedef _di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult *PAsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult;

typedef _di_IAsyncOperation_1__IKeyCredentialRetrievalResult *PIAsyncOperation_1__IKeyCredentialRetrievalResult;

typedef _di_IKeyCredentialManagerStatics *PIKeyCredentialManagerStatics;

typedef _di_AsyncOperationCompletedHandler_1__IWebAccount *PAsyncOperationCompletedHandler_1__IWebAccount;

typedef _di_IAsyncOperation_1__IWebAccount *PIAsyncOperation_1__IWebAccount;

typedef _di_AsyncOperationCompletedHandler_1__IWebAccountProvider *PAsyncOperationCompletedHandler_1__IWebAccountProvider;

typedef _di_IAsyncOperation_1__IWebAccountProvider *PIAsyncOperation_1__IWebAccountProvider;

typedef _di_IIterator_1__IWebAccount *PIIterator_1__IWebAccount;

typedef _di_IIterable_1__IWebAccount *PIIterable_1__IWebAccount;

typedef _di_IVectorView_1__IWebAccount *PIVectorView_1__IWebAccount;

typedef _di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount *PAsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount;

typedef _di_IAsyncOperation_1__IVectorView_1__IWebAccount *PIAsyncOperation_1__IVectorView_1__IWebAccount;

typedef _di_IWebAccountFactory *PIWebAccountFactory;

typedef _di_IWebAccount2 *PIWebAccount2;

typedef _di_IWebAccountProviderFactory *PIWebAccountProviderFactory;

typedef _di_IWebAccountProvider2 *PIWebAccountProvider2;

typedef _di_IWebAccountProvider3 *PIWebAccountProvider3;

typedef _di_ICredentialFactory *PICredentialFactory;

typedef _di_IIterator_1__IPasswordCredential *PIIterator_1__IPasswordCredential;

typedef _di_IIterable_1__IPasswordCredential *PIIterable_1__IPasswordCredential;

typedef _di_IVectorView_1__IPasswordCredential *PIVectorView_1__IPasswordCredential;

typedef _di_IPasswordVault *PIPasswordVault;

__interface  INTERFACE_UUID("{29DCC8C3-7AB9-4A7C-A336-B942F9DBF7C7}") IWebAccountProvider  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_DisplayName(HSTRING &__get_DisplayName_result) = 0 ;
	virtual HRESULT __safecall get_IconUri(Winapi::Commontypes::_di_IUriRuntimeClass &__get_IconUri_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayName() { HSTRING __r; HRESULT __hr = get_DisplayName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayName = {read=_scw_get_DisplayName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUriRuntimeClass _scw_get_IconUri() { Winapi::Commontypes::_di_IUriRuntimeClass __r; HRESULT __hr = get_IconUri(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUriRuntimeClass IconUri = {read=_scw_get_IconUri};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
};

__interface  INTERFACE_UUID("{69473EB2-8031-49BE-80BB-96CB46D99ABA}") IWebAccount  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_WebAccountProvider(_di_IWebAccountProvider &__get_WebAccountProvider_result) = 0 ;
	virtual HRESULT __safecall get_UserName(HSTRING &__get_UserName_result) = 0 ;
	virtual HRESULT __safecall get_State(Winapi::Commontypes::WebAccountState &__get_State_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::WebAccountState _scw_get_State() { Winapi::Commontypes::WebAccountState __r; HRESULT __hr = get_State(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::WebAccountState State = {read=_scw_get_State};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UserName() { HSTRING __r; HRESULT __hr = get_UserName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UserName = {read=_scw_get_UserName};
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWebAccountProvider _scw_get_WebAccountProvider() { _di_IWebAccountProvider __r; HRESULT __hr = get_WebAccountProvider(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWebAccountProvider WebAccountProvider = {read=_scw_get_WebAccountProvider};
};

__interface  INTERFACE_UUID("{6AB18989-C720-41A7-A6C1-FEADB36329A0}") IPasswordCredential  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Resource(HSTRING &__get_Resource_result) = 0 ;
	virtual HRESULT __safecall put_Resource(HSTRING resource) = 0 ;
	virtual HRESULT __safecall get_UserName(HSTRING &__get_UserName_result) = 0 ;
	virtual HRESULT __safecall put_UserName(HSTRING userName) = 0 ;
	virtual HRESULT __safecall get_Password(HSTRING &__get_Password_result) = 0 ;
	virtual HRESULT __safecall put_Password(HSTRING password) = 0 ;
	virtual HRESULT __safecall RetrievePassword() = 0 ;
	virtual HRESULT __safecall get_Properties(Winapi::Commontypes::_di_IPropertySet &__get_Properties_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Password() { HSTRING __r; HRESULT __hr = get_Password(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Password = {read=_scw_get_Password, write=put_Password};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IPropertySet _scw_get_Properties() { Winapi::Commontypes::_di_IPropertySet __r; HRESULT __hr = get_Properties(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IPropertySet Properties = {read=_scw_get_Properties};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Resource() { HSTRING __r; HRESULT __hr = get_Resource(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Resource = {read=_scw_get_Resource, write=put_Resource};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_UserName() { HSTRING __r; HRESULT __hr = get_UserName(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING UserName = {read=_scw_get_UserName, write=put_UserName};
};

__interface  INTERFACE_UUID("{28988174-ACE2-5C15-A0DF-580A26D94294}") AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability  : public AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__UI_UserConsentVerifierAvailability asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{DDD384F3-D818-5D83-AB4B-32119C28587C}") IAsyncOperation_1__UI_UserConsentVerifierAvailability_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__UI_UserConsentVerifierAvailability  : public IAsyncOperation_1__UI_UserConsentVerifierAvailability_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::UI_UserConsentVerifierAvailability &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerifierAvailability Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{0CFFC6C9-4C2B-5CD4-B38C-7B8DF3FF5AFB}") AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{E08EC1E0-E4AE-55A1-9A15-180859E0FA0F}") AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult  : public AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__UI_UserConsentVerificationResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{FD596FFD-2318-558F-9DBE-D21DF43764A5}") IAsyncOperation_1__UI_UserConsentVerificationResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{CA76FC11-A2C1-513E-B837-B4E39C42DC6B}") IAsyncOperation_1__UI_UserConsentVerificationResult  : public IAsyncOperation_1__UI_UserConsentVerificationResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(Winapi::Commontypes::UI_UserConsentVerificationResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__UI_UserConsentVerificationResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{AF4F3F91-564C-4DDC-B8B5-973447627C65}") UI_IUserConsentVerifierStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CheckAvailabilityAsync(_di_IAsyncOperation_1__UI_UserConsentVerifierAvailability &__CheckAvailabilityAsync_result) = 0 ;
	virtual HRESULT __safecall RequestVerificationAsync(HSTRING message, _di_IAsyncOperation_1__UI_UserConsentVerificationResult &__RequestVerificationAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{F53786C1-5261-4CDD-976D-CC909AC71620}") IKeyCredentialOperationResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Result(Winapi::Commontypes::_di_IBuffer &__get_Result_result) = 0 ;
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::KeyCredentialStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_Result() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_Result(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer Result = {read=_scw_get_Result};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::KeyCredentialStatus _scw_get_Status() { Winapi::Commontypes::KeyCredentialStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::KeyCredentialStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{39B4609A-0202-55FA-8005-6F83709E20F3}") AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{F6D2BE52-9016-57D4-8CC1-06F861215406}") AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult  : public AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IKeyCredentialOperationResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{6576E5B3-9535-50D6-98F6-C67D6AACA2C5}") IAsyncOperation_1__IKeyCredentialOperationResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{2B1CF200-85BE-58C2-8380-15F6F437E5B7}") IAsyncOperation_1__IKeyCredentialOperationResult  : public IAsyncOperation_1__IKeyCredentialOperationResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IKeyCredentialOperationResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IKeyCredentialOperationResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{78AAB3A1-A3C1-4103-B6CC-472C44171CBB}") IKeyCredentialAttestationResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_CertificateChainBuffer(Winapi::Commontypes::_di_IBuffer &__get_CertificateChainBuffer_result) = 0 ;
	virtual HRESULT __safecall get_AttestationBuffer(Winapi::Commontypes::_di_IBuffer &__get_AttestationBuffer_result) = 0 ;
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::KeyCredentialAttestationStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_AttestationBuffer() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_AttestationBuffer(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer AttestationBuffer = {read=_scw_get_AttestationBuffer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IBuffer _scw_get_CertificateChainBuffer() { Winapi::Commontypes::_di_IBuffer __r; HRESULT __hr = get_CertificateChainBuffer(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IBuffer CertificateChainBuffer = {read=_scw_get_CertificateChainBuffer};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::KeyCredentialAttestationStatus _scw_get_Status() { Winapi::Commontypes::KeyCredentialAttestationStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::KeyCredentialAttestationStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{2C16E103-F783-5DD9-A5F3-3362BCBDAABD}") AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{019B23FA-0731-54AF-9B44-5E7A9E2D2160}") AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult  : public AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IKeyCredentialAttestationResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{B83D29E9-F4E4-5AA4-92D5-B262CB40C622}") IAsyncOperation_1__IKeyCredentialAttestationResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{67AD516F-C0D7-5C2C-8A02-64EC5361E1AA}") IAsyncOperation_1__IKeyCredentialAttestationResult  : public IAsyncOperation_1__IKeyCredentialAttestationResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IKeyCredentialAttestationResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IKeyCredentialAttestationResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{9585EF8D-457B-4847-B11A-FA960BBDB138}") IKeyCredential  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Name(HSTRING &__get_Name_result) = 0 ;
	virtual HRESULT __safecall RetrievePublicKey(Winapi::Commontypes::_di_IBuffer &__RetrievePublicKey_result) = 0 /* overload */;
	virtual HRESULT __safecall RetrievePublicKey(Winapi::Commontypes::Core_CryptographicPublicKeyBlobType blobType, Winapi::Commontypes::_di_IBuffer &__RetrievePublicKey_result) = 0 /* overload */;
	virtual HRESULT __safecall RequestSignAsync(Winapi::Commontypes::_di_IBuffer data, _di_IAsyncOperation_1__IKeyCredentialOperationResult &__RequestSignAsync_result) = 0 ;
	virtual HRESULT __safecall GetAttestationAsync(_di_IAsyncOperation_1__IKeyCredentialAttestationResult &__GetAttestationAsync_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Name() { HSTRING __r; HRESULT __hr = get_Name(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Name = {read=_scw_get_Name};
};

__interface  INTERFACE_UUID("{58CD7703-8D87-4249-9B58-F6598CC9644E}") IKeyCredentialRetrievalResult  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Credential(_di_IKeyCredential &__get_Credential_result) = 0 ;
	virtual HRESULT __safecall get_Status(Winapi::Commontypes::KeyCredentialStatus &__get_Status_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IKeyCredential _scw_get_Credential() { _di_IKeyCredential __r; HRESULT __hr = get_Credential(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IKeyCredential Credential = {read=_scw_get_Credential};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::KeyCredentialStatus _scw_get_Status() { Winapi::Commontypes::KeyCredentialStatus __r; HRESULT __hr = get_Status(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::KeyCredentialStatus Status = {read=_scw_get_Status};
};

__interface  INTERFACE_UUID("{03EA60B1-A874-58CE-8E8E-FFF448B6733E}") AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{1BC39F2F-E816-5800-BF7F-19BB52D9352A}") AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult  : public AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IKeyCredentialRetrievalResult asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{89D0AD1E-BD4C-55B4-810E-BDDD4CEC7A2A}") IAsyncOperation_1__IKeyCredentialRetrievalResult_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{FDE031B9-B951-5F3B-ADEA-C0C87D793496}") IAsyncOperation_1__IKeyCredentialRetrievalResult  : public IAsyncOperation_1__IKeyCredentialRetrievalResult_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IKeyCredentialRetrievalResult &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IKeyCredentialRetrievalResult Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{6AAC468B-0EF1-4CE0-8290-4106DA6A63B5}") IKeyCredentialManagerStatics  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall IsSupportedAsync(Winapi::Commontypes::_di_IAsyncOperation_1__Boolean &__IsSupportedAsync_result) = 0 ;
	virtual HRESULT __safecall RenewAttestationAsync(Winapi::Commontypes::_di_IAsyncAction &__RenewAttestationAsync_result) = 0 ;
	virtual HRESULT __safecall RequestCreateAsync(HSTRING name, Winapi::Commontypes::KeyCredentialCreationOption option, _di_IAsyncOperation_1__IKeyCredentialRetrievalResult &__RequestCreateAsync_result) = 0 ;
	virtual HRESULT __safecall OpenAsync(HSTRING name, _di_IAsyncOperation_1__IKeyCredentialRetrievalResult &__OpenAsync_result) = 0 ;
	virtual HRESULT __safecall DeleteAsync(HSTRING name, Winapi::Commontypes::_di_IAsyncAction &__DeleteAsync_result) = 0 ;
};

__interface  INTERFACE_UUID("{4BD6F1E5-CA89-5240-8F3D-7F1B54AE90A7}") AsyncOperationCompletedHandler_1__IWebAccount_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{B10C69CC-B076-5988-B147-09363CA35D01}") AsyncOperationCompletedHandler_1__IWebAccount  : public AsyncOperationCompletedHandler_1__IWebAccount_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IWebAccount asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{ACD76B54-297F-5A18-9143-20A309E2DFD3}") IAsyncOperation_1__IWebAccount_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{691C50CC-BB04-5825-805C-A80108E1F539}") IAsyncOperation_1__IWebAccount  : public IAsyncOperation_1__IWebAccount_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IWebAccount handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IWebAccount &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IWebAccount &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IWebAccount _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IWebAccount __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IWebAccount Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{9477622B-1340-5574-81FC-5013581F57C9}") AsyncOperationCompletedHandler_1__IWebAccountProvider_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{C39FF379-8E7D-54D3-A6A2-30732DBECB20}") AsyncOperationCompletedHandler_1__IWebAccountProvider  : public AsyncOperationCompletedHandler_1__IWebAccountProvider_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IWebAccountProvider asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{88C66009-12F7-58E2-8DBE-6EFC620C85BA}") IAsyncOperation_1__IWebAccountProvider_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{5DF2D5A2-29BE-588D-A865-2D532F0CFEB4}") IAsyncOperation_1__IWebAccountProvider  : public IAsyncOperation_1__IWebAccountProvider_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IWebAccountProvider handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IWebAccountProvider &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IWebAccountProvider &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IWebAccountProvider _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IWebAccountProvider __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IWebAccountProvider Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{BFB82CCA-AEBC-567C-95D9-EBA25C365FAA}") IIterator_1__IWebAccount_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{7B1BB16E-3EAB-508A-9EB6-4F170A834193}") IIterator_1__IWebAccount  : public IIterator_1__IWebAccount_Base 
{
	virtual HRESULT __safecall get_Current(_di_IWebAccount &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIWebAccount items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IWebAccount _scw_get_Current() { _di_IWebAccount __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IWebAccount Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{CB15D439-A910-542A-89ED-7CFE67848A83}") IIterable_1__IWebAccount_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{4EA35D15-AA11-5236-9708-C8030DCA63DC}") IIterable_1__IWebAccount  : public IIterable_1__IWebAccount_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IWebAccount &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{4C618663-2E68-5686-9058-F0A1B557EF74}") IVectorView_1__IWebAccount  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IWebAccount &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IWebAccount value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIWebAccount items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{C2090D8C-37D8-5C47-9581-0F17B91A0CD3}") AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount_Delegate_Base  : public System::IInterface 
{
	
};

__interface  INTERFACE_UUID("{D7DC33D6-EF58-5AD6-823F-F907097A8CBB}") AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount  : public AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount_Delegate_Base 
{
	virtual HRESULT __safecall Invoke(_di_IAsyncOperation_1__IVectorView_1__IWebAccount asyncInfo, Winapi::Commontypes::AsyncStatus asyncStatus) = 0 ;
};

__interface  INTERFACE_UUID("{66B59040-7C93-5F96-B52F-2C098D1557D0}") IAsyncOperation_1__IVectorView_1__IWebAccount_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{5D82779F-56CD-593C-BCF2-64A212D2DD67}") IAsyncOperation_1__IVectorView_1__IWebAccount  : public IAsyncOperation_1__IVectorView_1__IWebAccount_Base 
{
	virtual HRESULT __safecall put_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount handler) = 0 ;
	virtual HRESULT __safecall get_Completed(_di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount &__get_Completed_result) = 0 ;
	virtual HRESULT __safecall GetResults(_di_IVectorView_1__IWebAccount &__GetResults_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount _scw_get_Completed() { _di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount __r; HRESULT __hr = get_Completed(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_AsyncOperationCompletedHandler_1__IVectorView_1__IWebAccount Completed = {read=_scw_get_Completed, write=put_Completed};
};

__interface  INTERFACE_UUID("{AC9AFB39-1DE9-4E92-B78F-0581A87F6E5C}") IWebAccountFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWebAccount(_di_IWebAccountProvider webAccountProvider, HSTRING userName, Winapi::Commontypes::WebAccountState state, _di_IWebAccount &__CreateWebAccount_result) = 0 ;
};

__interface  INTERFACE_UUID("{7B56D6F8-990B-4EB5-94A7-5621F3A8B824}") IWebAccount2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_Id(HSTRING &__get_Id_result) = 0 ;
	virtual HRESULT __safecall get_Properties(Winapi::Commontypes::_di_IMapView_2__HSTRING__HSTRING &__get_Properties_result) = 0 ;
	virtual HRESULT __safecall GetPictureAsync(Winapi::Commontypes::WebAccountPictureSize desizedSize, Winapi::Commontypes::_di_IAsyncOperation_1__IRandomAccessStream &__GetPictureAsync_result) = 0 ;
	virtual HRESULT __safecall SignOutAsync(Winapi::Commontypes::_di_IAsyncAction &__SignOutAsync_result) = 0 /* overload */;
	virtual HRESULT __safecall SignOutAsync(HSTRING clientId, Winapi::Commontypes::_di_IAsyncAction &__SignOutAsync_result) = 0 /* overload */;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Id() { HSTRING __r; HRESULT __hr = get_Id(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Id = {read=_scw_get_Id};
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IMapView_2__HSTRING__HSTRING _scw_get_Properties() { Winapi::Commontypes::_di_IMapView_2__HSTRING__HSTRING __r; HRESULT __hr = get_Properties(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IMapView_2__HSTRING__HSTRING Properties = {read=_scw_get_Properties};
};

__interface  INTERFACE_UUID("{1D767DF1-E1E1-4B9A-A774-5C7C7E3BF371}") IWebAccountProviderFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreateWebAccountProvider(HSTRING id, HSTRING displayName, Winapi::Commontypes::_di_IUriRuntimeClass iconUri, _di_IWebAccountProvider &__CreateWebAccountProvider_result) = 0 ;
};

__interface  INTERFACE_UUID("{4A01EB05-4E42-41D4-B518-E008A5163614}") IWebAccountProvider2  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_DisplayPurpose(HSTRING &__get_DisplayPurpose_result) = 0 ;
	virtual HRESULT __safecall get_Authority(HSTRING &__get_Authority_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_Authority() { HSTRING __r; HRESULT __hr = get_Authority(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING Authority = {read=_scw_get_Authority};
	#pragma option push -w-inl
	/* safecall wrapper */ inline HSTRING _scw_get_DisplayPurpose() { HSTRING __r; HRESULT __hr = get_DisplayPurpose(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property HSTRING DisplayPurpose = {read=_scw_get_DisplayPurpose};
};

__interface  INTERFACE_UUID("{DA1C518B-970D-4D49-825C-F2706F8CA7FE}") IWebAccountProvider3  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall get_User(Winapi::Commontypes::_di_IUser &__get_User_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline Winapi::Commontypes::_di_IUser _scw_get_User() { Winapi::Commontypes::_di_IUser __r; HRESULT __hr = get_User(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property Winapi::Commontypes::_di_IUser User = {read=_scw_get_User};
};

__interface  INTERFACE_UUID("{54EF13A1-BF26-47B5-97DD-DE779B7CAD58}") ICredentialFactory  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall CreatePasswordCredential(HSTRING resource, HSTRING userName, HSTRING password, _di_IPasswordCredential &__CreatePasswordCredential_result) = 0 ;
};

__interface  INTERFACE_UUID("{B01093D8-4F52-50F0-9AA4-E22639111162}") IIterator_1__IPasswordCredential_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{C3C5D889-E8E7-591B-BAB3-6F1E4C8B74B2}") IIterator_1__IPasswordCredential  : public IIterator_1__IPasswordCredential_Base 
{
	virtual HRESULT __safecall get_Current(_di_IPasswordCredential &__get_Current_result) = 0 ;
	virtual HRESULT __safecall get_HasCurrent(bool &__get_HasCurrent_result) = 0 ;
	virtual HRESULT __safecall MoveNext(bool &__MoveNext_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned itemsSize, PIPasswordCredential items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline _di_IPasswordCredential _scw_get_Current() { _di_IPasswordCredential __r; HRESULT __hr = get_Current(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property _di_IPasswordCredential Current = {read=_scw_get_Current};
	#pragma option push -w-inl
	/* safecall wrapper */ inline bool _scw_get_HasCurrent() { bool __r; HRESULT __hr = get_HasCurrent(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property bool HasCurrent = {read=_scw_get_HasCurrent};
};

__interface  INTERFACE_UUID("{0D224A66-BAD5-5AD5-9ADE-1E9F5A60FE73}") IIterable_1__IPasswordCredential_Base  : public Winapi::Winrt::IInspectable 
{
	
};

__interface  INTERFACE_UUID("{B86DD1B0-F6AB-5DEE-926A-B8F623D76255}") IIterable_1__IPasswordCredential  : public IIterable_1__IPasswordCredential_Base 
{
	virtual HRESULT __safecall First(_di_IIterator_1__IPasswordCredential &__First_result) = 0 ;
};

__interface  INTERFACE_UUID("{A1AC5012-3C00-5B22-ADC1-095F7E86CA11}") IVectorView_1__IPasswordCredential  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall GetAt(unsigned index, _di_IPasswordCredential &__GetAt_result) = 0 ;
	virtual HRESULT __safecall get_Size(unsigned &__get_Size_result) = 0 ;
	virtual HRESULT __safecall IndexOf(_di_IPasswordCredential value, /* out */ unsigned &index, bool &__IndexOf_result) = 0 ;
	virtual HRESULT __safecall GetMany(unsigned startIndex, unsigned itemsSize, PIPasswordCredential items, unsigned &__GetMany_result) = 0 ;
	#pragma option push -w-inl
	/* safecall wrapper */ inline unsigned _scw_get_Size() { unsigned __r; HRESULT __hr = get_Size(__r); System::CheckSafecallResult(__hr); return __r; }
	#pragma option pop
	__property unsigned Size = {read=_scw_get_Size};
};

__interface  INTERFACE_UUID("{61FD2C0B-C8D4-48C1-A54F-BC5A64205AF2}") IPasswordVault  : public Winapi::Winrt::IInspectable 
{
	virtual HRESULT __safecall Add(_di_IPasswordCredential credential) = 0 ;
	virtual HRESULT __safecall Remove(_di_IPasswordCredential credential) = 0 ;
	virtual HRESULT __safecall Retrieve(HSTRING resource, HSTRING userName, _di_IPasswordCredential &__Retrieve_result) = 0 ;
	virtual HRESULT __safecall FindAllByResource(HSTRING resource, _di_IVectorView_1__IPasswordCredential &__FindAllByResource_result) = 0 ;
	virtual HRESULT __safecall FindAllByUserName(HSTRING userName, _di_IVectorView_1__IPasswordCredential &__FindAllByUserName_result) = 0 ;
	virtual HRESULT __safecall RetrieveAll(_di_IVectorView_1__IPasswordCredential &__RetrieveAll_result) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUI_UserConsentVerifier : public System::Win::Winrt::TWinRTGenericImportS__1<_di_UI_IUserConsentVerifierStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_UI_IUserConsentVerifierStatics> inherited;
	
public:
	static _di_IAsyncOperation_1__UI_UserConsentVerifierAvailability __fastcall CheckAvailabilityAsync();
	static _di_IAsyncOperation_1__UI_UserConsentVerificationResult __fastcall RequestVerificationAsync(HSTRING message);
public:
	/* TObject.Create */ inline __fastcall TUI_UserConsentVerifier() : System::Win::Winrt::TWinRTGenericImportS__1<_di_UI_IUserConsentVerifierStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TUI_UserConsentVerifier() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TKeyCredentialManager : public System::Win::Winrt::TWinRTGenericImportS__1<_di_IKeyCredentialManagerStatics>
{
	typedef System::Win::Winrt::TWinRTGenericImportS__1<_di_IKeyCredentialManagerStatics> inherited;
	
public:
	static Winapi::Commontypes::_di_IAsyncOperation_1__Boolean __fastcall IsSupportedAsync();
	static Winapi::Commontypes::_di_IAsyncAction __fastcall RenewAttestationAsync();
	static _di_IAsyncOperation_1__IKeyCredentialRetrievalResult __fastcall RequestCreateAsync(HSTRING name, Winapi::Commontypes::KeyCredentialCreationOption option);
	static _di_IAsyncOperation_1__IKeyCredentialRetrievalResult __fastcall OpenAsync(HSTRING name);
	static Winapi::Commontypes::_di_IAsyncAction __fastcall DeleteAsync(HSTRING name);
public:
	/* TObject.Create */ inline __fastcall TKeyCredentialManager() : System::Win::Winrt::TWinRTGenericImportS__1<_di_IKeyCredentialManagerStatics>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TKeyCredentialManager() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebAccountProvider : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IWebAccountProviderFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IWebAccountProviderFactory> inherited;
	
public:
	static _di_IWebAccountProvider __fastcall CreateWebAccountProvider(HSTRING id, HSTRING displayName, Winapi::Commontypes::_di_IUriRuntimeClass iconUri);
public:
	/* TObject.Create */ inline __fastcall TWebAccountProvider() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IWebAccountProviderFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWebAccountProvider() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWebAccount : public System::Win::Winrt::TWinRTGenericImportF__1<_di_IWebAccountFactory>
{
	typedef System::Win::Winrt::TWinRTGenericImportF__1<_di_IWebAccountFactory> inherited;
	
public:
	static _di_IWebAccount __fastcall CreateWebAccount(_di_IWebAccountProvider webAccountProvider, HSTRING userName, Winapi::Commontypes::WebAccountState state);
public:
	/* TObject.Create */ inline __fastcall TWebAccount() : System::Win::Winrt::TWinRTGenericImportF__1<_di_IWebAccountFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TWebAccount() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPasswordCredential : public System::Win::Winrt::TWinRTGenericImportFI__2<_di_ICredentialFactory,_di_IPasswordCredential>
{
	typedef System::Win::Winrt::TWinRTGenericImportFI__2<_di_ICredentialFactory,_di_IPasswordCredential> inherited;
	
public:
	static _di_IPasswordCredential __fastcall CreatePasswordCredential(HSTRING resource, HSTRING userName, HSTRING password);
public:
	/* TObject.Create */ inline __fastcall TPasswordCredential() : System::Win::Winrt::TWinRTGenericImportFI__2<_di_ICredentialFactory,_di_IPasswordCredential>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPasswordCredential() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPasswordVault : public System::Win::Winrt::TWinRTGenericImportI__1<_di_IPasswordVault>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<_di_IPasswordVault> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TPasswordVault() : System::Win::Winrt::TWinRTGenericImportI__1<_di_IPasswordVault>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPasswordVault() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TPasswordCredentialPropertyStore : public System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet>
{
	typedef System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TPasswordCredentialPropertyStore() : System::Win::Winrt::TWinRTGenericImportI__1<Winapi::Commontypes::_di_IPropertySet>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TPasswordCredentialPropertyStore() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Credentials */
}	/* namespace Security */
}	/* namespace Winapi */
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Security_CredentialsHPP
