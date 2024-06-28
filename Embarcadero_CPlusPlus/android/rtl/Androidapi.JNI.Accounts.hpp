// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Accounts.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_AccountsHPP
#define Androidapi_Jni_AccountsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.App.hpp>
#include <Androidapi.JNI.GraphicsContentViewText.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.JNI.Os.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Accounts
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JAccountClass;
typedef System::DelphiInterface<JAccountClass> _di_JAccountClass;
__interface DELPHIINTERFACE JAccount;
typedef System::DelphiInterface<JAccount> _di_JAccount;
class DELPHICLASS TJAccount;
__interface DELPHIINTERFACE JAccountManagerClass;
typedef System::DelphiInterface<JAccountManagerClass> _di_JAccountManagerClass;
__interface DELPHIINTERFACE JAccountManager;
typedef System::DelphiInterface<JAccountManager> _di_JAccountManager;
class DELPHICLASS TJAccountManager;
__interface DELPHIINTERFACE JAccountManagerCallbackClass;
typedef System::DelphiInterface<JAccountManagerCallbackClass> _di_JAccountManagerCallbackClass;
__interface DELPHIINTERFACE JAccountManagerCallback;
typedef System::DelphiInterface<JAccountManagerCallback> _di_JAccountManagerCallback;
class DELPHICLASS TJAccountManagerCallback;
__interface DELPHIINTERFACE JAccountManagerFutureClass;
typedef System::DelphiInterface<JAccountManagerFutureClass> _di_JAccountManagerFutureClass;
__interface DELPHIINTERFACE JAccountManagerFuture;
typedef System::DelphiInterface<JAccountManagerFuture> _di_JAccountManagerFuture;
class DELPHICLASS TJAccountManagerFuture;
__interface DELPHIINTERFACE JAuthenticatorDescriptionClass;
typedef System::DelphiInterface<JAuthenticatorDescriptionClass> _di_JAuthenticatorDescriptionClass;
__interface DELPHIINTERFACE JAuthenticatorDescription;
typedef System::DelphiInterface<JAuthenticatorDescription> _di_JAuthenticatorDescription;
class DELPHICLASS TJAuthenticatorDescription;
__interface DELPHIINTERFACE JOnAccountsUpdateListenerClass;
typedef System::DelphiInterface<JOnAccountsUpdateListenerClass> _di_JOnAccountsUpdateListenerClass;
__interface DELPHIINTERFACE JOnAccountsUpdateListener;
typedef System::DelphiInterface<JOnAccountsUpdateListener> _di_JOnAccountsUpdateListener;
class DELPHICLASS TJOnAccountsUpdateListener;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{94EE6861-F326-489F-8919-E20B39E3D9C1}") JAccountClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JAccount __cdecl init(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JString type_) = 0 /* overload */;
	HIDESBASE virtual _di_JAccount __cdecl init(Androidapi::Jni::Os::_di_JParcel in_) = 0 /* overload */;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{71476381-8B6E-471F-9189-9857ECD7508C}") JAccount  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Getname() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettype() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
	__property Androidapi::Jni::Javatypes::_di_JString name = {read=_Getname};
	__property Androidapi::Jni::Javatypes::_di_JString type = {read=_Gettype};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAccount : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountClass,_di_JAccount>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountClass,_di_JAccount> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAccount() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountClass,_di_JAccount>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAccount() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{96273844-2D84-47F0-BFD5-14B73402F843}") JAccountManagerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_ACCOUNT_REMOVED() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetACTION_AUTHENTICATOR_INTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAUTHENTICATOR_ATTRIBUTES_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetAUTHENTICATOR_META_DATA_NAME() = 0 ;
	virtual int __cdecl _GetERROR_CODE_BAD_ARGUMENTS() = 0 ;
	virtual int __cdecl _GetERROR_CODE_BAD_AUTHENTICATION() = 0 ;
	virtual int __cdecl _GetERROR_CODE_BAD_REQUEST() = 0 ;
	virtual int __cdecl _GetERROR_CODE_CANCELED() = 0 ;
	virtual int __cdecl _GetERROR_CODE_INVALID_RESPONSE() = 0 ;
	virtual int __cdecl _GetERROR_CODE_NETWORK_ERROR() = 0 ;
	virtual int __cdecl _GetERROR_CODE_REMOTE_EXCEPTION() = 0 ;
	virtual int __cdecl _GetERROR_CODE_UNSUPPORTED_OPERATION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNTS() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNT_AUTHENTICATOR_RESPONSE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNT_MANAGER_RESPONSE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNT_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNT_SESSION_BUNDLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNT_STATUS_TOKEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ACCOUNT_TYPE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ANDROID_PACKAGE_NAME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_AUTHENTICATOR_TYPES() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_AUTHTOKEN() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_AUTH_FAILED_MESSAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_AUTH_TOKEN_LABEL() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_BOOLEAN_RESULT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CALLER_PID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_CALLER_UID() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ERROR_CODE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_ERROR_MESSAGE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_INTENT() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_LAST_AUTHENTICATED_TIME() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_PASSWORD() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetKEY_USERDATA() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetLOGIN_ACCOUNTS_CHANGED_ACTION() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPACKAGE_NAME_KEY_LEGACY_NOT_VISIBLE() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetPACKAGE_NAME_KEY_LEGACY_VISIBLE() = 0 ;
	virtual int __cdecl _GetVISIBILITY_NOT_VISIBLE() = 0 ;
	virtual int __cdecl _GetVISIBILITY_UNDEFINED() = 0 ;
	virtual int __cdecl _GetVISIBILITY_USER_MANAGED_NOT_VISIBLE() = 0 ;
	virtual int __cdecl _GetVISIBILITY_USER_MANAGED_VISIBLE() = 0 ;
	virtual int __cdecl _GetVISIBILITY_VISIBLE() = 0 ;
	virtual _di_JAccountManager __cdecl get(Androidapi::Jni::Graphicscontentviewtext::_di_JContext context) = 0 ;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl newChooseAccountIntent(_di_JAccount selectedAccount, Androidapi::Jni::Javatypes::_di_JArrayList allowableAccounts, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* allowableAccountTypes, bool alwaysPromptForAccount, Androidapi::Jni::Javatypes::_di_JString descriptionOverrideText, Androidapi::Jni::Javatypes::_di_JString addAccountAuthTokenType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* addAccountRequiredFeatures, Androidapi::Jni::Os::_di_JBundle addAccountOptions) = 0 /* overload */;
	virtual Androidapi::Jni::Graphicscontentviewtext::_di_JIntent __cdecl newChooseAccountIntent(_di_JAccount selectedAccount, Androidapi::Jni::Javatypes::_di_JList allowableAccounts, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* allowableAccountTypes, Androidapi::Jni::Javatypes::_di_JString descriptionOverrideText, Androidapi::Jni::Javatypes::_di_JString addAccountAuthTokenType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* addAccountRequiredFeatures, Androidapi::Jni::Os::_di_JBundle addAccountOptions) = 0 /* overload */;
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_ACCOUNT_REMOVED = {read=_GetACTION_ACCOUNT_REMOVED};
	__property Androidapi::Jni::Javatypes::_di_JString ACTION_AUTHENTICATOR_INTENT = {read=_GetACTION_AUTHENTICATOR_INTENT};
	__property Androidapi::Jni::Javatypes::_di_JString AUTHENTICATOR_ATTRIBUTES_NAME = {read=_GetAUTHENTICATOR_ATTRIBUTES_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString AUTHENTICATOR_META_DATA_NAME = {read=_GetAUTHENTICATOR_META_DATA_NAME};
	__property int ERROR_CODE_BAD_ARGUMENTS = {read=_GetERROR_CODE_BAD_ARGUMENTS};
	__property int ERROR_CODE_BAD_AUTHENTICATION = {read=_GetERROR_CODE_BAD_AUTHENTICATION};
	__property int ERROR_CODE_BAD_REQUEST = {read=_GetERROR_CODE_BAD_REQUEST};
	__property int ERROR_CODE_CANCELED = {read=_GetERROR_CODE_CANCELED};
	__property int ERROR_CODE_INVALID_RESPONSE = {read=_GetERROR_CODE_INVALID_RESPONSE};
	__property int ERROR_CODE_NETWORK_ERROR = {read=_GetERROR_CODE_NETWORK_ERROR};
	__property int ERROR_CODE_REMOTE_EXCEPTION = {read=_GetERROR_CODE_REMOTE_EXCEPTION};
	__property int ERROR_CODE_UNSUPPORTED_OPERATION = {read=_GetERROR_CODE_UNSUPPORTED_OPERATION};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNTS = {read=_GetKEY_ACCOUNTS};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNT_AUTHENTICATOR_RESPONSE = {read=_GetKEY_ACCOUNT_AUTHENTICATOR_RESPONSE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNT_MANAGER_RESPONSE = {read=_GetKEY_ACCOUNT_MANAGER_RESPONSE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNT_NAME = {read=_GetKEY_ACCOUNT_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNT_SESSION_BUNDLE = {read=_GetKEY_ACCOUNT_SESSION_BUNDLE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNT_STATUS_TOKEN = {read=_GetKEY_ACCOUNT_STATUS_TOKEN};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ACCOUNT_TYPE = {read=_GetKEY_ACCOUNT_TYPE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ANDROID_PACKAGE_NAME = {read=_GetKEY_ANDROID_PACKAGE_NAME};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_AUTHENTICATOR_TYPES = {read=_GetKEY_AUTHENTICATOR_TYPES};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_AUTHTOKEN = {read=_GetKEY_AUTHTOKEN};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_AUTH_FAILED_MESSAGE = {read=_GetKEY_AUTH_FAILED_MESSAGE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_AUTH_TOKEN_LABEL = {read=_GetKEY_AUTH_TOKEN_LABEL};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_BOOLEAN_RESULT = {read=_GetKEY_BOOLEAN_RESULT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CALLER_PID = {read=_GetKEY_CALLER_PID};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_CALLER_UID = {read=_GetKEY_CALLER_UID};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ERROR_CODE = {read=_GetKEY_ERROR_CODE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_ERROR_MESSAGE = {read=_GetKEY_ERROR_MESSAGE};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_INTENT = {read=_GetKEY_INTENT};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_LAST_AUTHENTICATED_TIME = {read=_GetKEY_LAST_AUTHENTICATED_TIME};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_PASSWORD = {read=_GetKEY_PASSWORD};
	__property Androidapi::Jni::Javatypes::_di_JString KEY_USERDATA = {read=_GetKEY_USERDATA};
	__property Androidapi::Jni::Javatypes::_di_JString LOGIN_ACCOUNTS_CHANGED_ACTION = {read=_GetLOGIN_ACCOUNTS_CHANGED_ACTION};
	__property Androidapi::Jni::Javatypes::_di_JString PACKAGE_NAME_KEY_LEGACY_NOT_VISIBLE = {read=_GetPACKAGE_NAME_KEY_LEGACY_NOT_VISIBLE};
	__property Androidapi::Jni::Javatypes::_di_JString PACKAGE_NAME_KEY_LEGACY_VISIBLE = {read=_GetPACKAGE_NAME_KEY_LEGACY_VISIBLE};
	__property int VISIBILITY_NOT_VISIBLE = {read=_GetVISIBILITY_NOT_VISIBLE};
	__property int VISIBILITY_UNDEFINED = {read=_GetVISIBILITY_UNDEFINED};
	__property int VISIBILITY_USER_MANAGED_NOT_VISIBLE = {read=_GetVISIBILITY_USER_MANAGED_NOT_VISIBLE};
	__property int VISIBILITY_USER_MANAGED_VISIBLE = {read=_GetVISIBILITY_USER_MANAGED_VISIBLE};
	__property int VISIBILITY_VISIBLE = {read=_GetVISIBILITY_VISIBLE};
};

__interface  INTERFACE_UUID("{9FA4077B-4628-433C-BAFC-9EB299DA9C98}") JAccountManager  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JAccountManagerFuture __cdecl addAccount(Androidapi::Jni::Javatypes::_di_JString accountType, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* requiredFeatures, Androidapi::Jni::Os::_di_JBundle addAccountOptions, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual bool __cdecl addAccountExplicitly(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString password, Androidapi::Jni::Os::_di_JBundle userdata) = 0 /* overload */;
	virtual bool __cdecl addAccountExplicitly(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString password, Androidapi::Jni::Os::_di_JBundle extras, Androidapi::Jni::Javatypes::_di_JMap visibility) = 0 /* overload */;
	virtual void __cdecl addOnAccountsUpdatedListener(_di_JOnAccountsUpdateListener listener, Androidapi::Jni::Os::_di_JHandler handler, bool updateImmediately) = 0 /* overload */;
	virtual void __cdecl addOnAccountsUpdatedListener(_di_JOnAccountsUpdateListener listener, Androidapi::Jni::Os::_di_JHandler handler, bool updateImmediately, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* accountTypes) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl blockingGetAuthToken(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, bool notifyAuthFailure) = 0 ;
	virtual void __cdecl clearPassword(_di_JAccount account) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl confirmCredentials(_di_JAccount account, Androidapi::Jni::Os::_di_JBundle options, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl editProperties(Androidapi::Jni::Javatypes::_di_JString accountType, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl finishSession(Androidapi::Jni::Os::_di_JBundle sessionBundle, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual int __cdecl getAccountVisibility(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAccount>* __cdecl getAccounts() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getAccountsAndVisibilityForPackage(Androidapi::Jni::Javatypes::_di_JString packageName, Androidapi::Jni::Javatypes::_di_JString accountType) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAccount>* __cdecl getAccountsByType(Androidapi::Jni::Javatypes::_di_JString type_) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAccountManagerFuture>* __cdecl getAccountsByTypeAndFeatures(Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* features, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAccountManagerCallback>* callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAccount>* __cdecl getAccountsByTypeForPackage(Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jni::Javatypes::_di_JString packageName) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl getAuthToken(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jni::Os::_di_JBundle options, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual _di_JAccountManagerFuture __cdecl getAuthToken(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, bool notifyAuthFailure, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual _di_JAccountManagerFuture __cdecl getAuthToken(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jni::Os::_di_JBundle options, bool notifyAuthFailure, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual _di_JAccountManagerFuture __cdecl getAuthTokenByFeatures(Androidapi::Jni::Javatypes::_di_JString accountType, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* features, Androidapi::Jni::App::_di_JActivity activity, Androidapi::Jni::Os::_di_JBundle addAccountOptions, Androidapi::Jni::Os::_di_JBundle getAuthTokenOptions, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAuthenticatorDescription>* __cdecl getAuthenticatorTypes() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getPackagesAndVisibilityForAccount(_di_JAccount account) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPassword(_di_JAccount account) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPreviousName(_di_JAccount account) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUserData(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl hasFeatures(_di_JAccount account, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* features, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual void __cdecl invalidateAuthToken(Androidapi::Jni::Javatypes::_di_JString accountType, Androidapi::Jni::Javatypes::_di_JString authToken) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl isCredentialsUpdateSuggested(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString statusToken, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual bool __cdecl notifyAccountAuthenticated(_di_JAccount account) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl peekAuthToken(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl removeAccount(_di_JAccount account, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual _di_JAccountManagerFuture __cdecl removeAccount(_di_JAccount account, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 /* overload */;
	virtual bool __cdecl removeAccountExplicitly(_di_JAccount account) = 0 ;
	virtual void __cdecl removeOnAccountsUpdatedListener(_di_JOnAccountsUpdateListener listener) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl renameAccount(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString newName, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual bool __cdecl setAccountVisibility(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString packageName, int visibility) = 0 ;
	virtual void __cdecl setAuthToken(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jni::Javatypes::_di_JString authToken) = 0 ;
	virtual void __cdecl setPassword(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString password) = 0 ;
	virtual void __cdecl setUserData(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl startAddAccountSession(Androidapi::Jni::Javatypes::_di_JString accountType, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* requiredFeatures, Androidapi::Jni::Os::_di_JBundle options, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl startUpdateCredentialsSession(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jni::Os::_di_JBundle options, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
	virtual _di_JAccountManagerFuture __cdecl updateCredentials(_di_JAccount account, Androidapi::Jni::Javatypes::_di_JString authTokenType, Androidapi::Jni::Os::_di_JBundle options, Androidapi::Jni::App::_di_JActivity activity, _di_JAccountManagerCallback callback, Androidapi::Jni::Os::_di_JHandler handler) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAccountManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerClass,_di_JAccountManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerClass,_di_JAccountManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAccountManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerClass,_di_JAccountManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAccountManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{2BB75752-63FB-452C-9774-7731FF54106C}") JAccountManagerCallbackClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{BAAAB7C0-D823-4787-AD18-053B44CBBADD}") JAccountManagerCallback  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl run(_di_JAccountManagerFuture future) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAccountManagerCallback : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerCallbackClass,_di_JAccountManagerCallback>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerCallbackClass,_di_JAccountManagerCallback> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAccountManagerCallback() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerCallbackClass,_di_JAccountManagerCallback>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAccountManagerCallback() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{B87CF21F-E69E-409A-AA91-204D152A7183}") JAccountManagerFutureClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{608D5C94-7A70-44B3-8F29-7F84F825A2D2}") JAccountManagerFuture  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl cancel(bool mayInterruptIfRunning) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getResult() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getResult(__int64 timeout, Androidapi::Jni::Javatypes::_di_JTimeUnit unit_) = 0 /* overload */;
	virtual bool __cdecl isCancelled() = 0 ;
	virtual bool __cdecl isDone() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAccountManagerFuture : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerFutureClass,_di_JAccountManagerFuture>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerFutureClass,_di_JAccountManagerFuture> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAccountManagerFuture() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAccountManagerFutureClass,_di_JAccountManagerFuture>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAccountManagerFuture() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{6FDEA3E2-7412-4415-A32F-FD7689B911B4}") JAuthenticatorDescriptionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Os::_di_JParcelable_Creator __cdecl _GetCREATOR() = 0 ;
	HIDESBASE virtual _di_JAuthenticatorDescription __cdecl init(Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jni::Javatypes::_di_JString packageName, int labelId, int iconId, int smallIconId, int prefId, bool customTokens) = 0 /* overload */;
	HIDESBASE virtual _di_JAuthenticatorDescription __cdecl init(Androidapi::Jni::Javatypes::_di_JString type_, Androidapi::Jni::Javatypes::_di_JString packageName, int labelId, int iconId, int smallIconId, int prefId) = 0 /* overload */;
	virtual _di_JAuthenticatorDescription __cdecl newKey(Androidapi::Jni::Javatypes::_di_JString type_) = 0 ;
	__property Androidapi::Jni::Os::_di_JParcelable_Creator CREATOR = {read=_GetCREATOR};
};

__interface  INTERFACE_UUID("{9F482564-61EE-4E96-B6F0-B1673A7E4620}") JAuthenticatorDescription  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl _GetaccountPreferencesId() = 0 ;
	virtual bool __cdecl _GetcustomTokens() = 0 ;
	virtual int __cdecl _GeticonId() = 0 ;
	virtual int __cdecl _GetlabelId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _GetpackageName() = 0 ;
	virtual int __cdecl _GetsmallIconId() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl _Gettype() = 0 ;
	virtual int __cdecl describeContents() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject o) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual void __cdecl writeToParcel(Androidapi::Jni::Os::_di_JParcel dest, int flags) = 0 ;
	__property int accountPreferencesId = {read=_GetaccountPreferencesId};
	__property bool customTokens = {read=_GetcustomTokens};
	__property int iconId = {read=_GeticonId};
	__property int labelId = {read=_GetlabelId};
	__property Androidapi::Jni::Javatypes::_di_JString packageName = {read=_GetpackageName};
	__property int smallIconId = {read=_GetsmallIconId};
	__property Androidapi::Jni::Javatypes::_di_JString type = {read=_Gettype};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJAuthenticatorDescription : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAuthenticatorDescriptionClass,_di_JAuthenticatorDescription>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAuthenticatorDescriptionClass,_di_JAuthenticatorDescription> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJAuthenticatorDescription() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JAuthenticatorDescriptionClass,_di_JAuthenticatorDescription>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJAuthenticatorDescription() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3C07CAD3-934F-4DC2-A61F-2A7401AEC9DE}") JOnAccountsUpdateListenerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{AC1ECF5C-E922-4AC1-95B1-345E995C36E7}") JOnAccountsUpdateListener  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual void __cdecl onAccountsUpdated(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JAccount>* accounts) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJOnAccountsUpdateListener : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnAccountsUpdateListenerClass,_di_JOnAccountsUpdateListener>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnAccountsUpdateListenerClass,_di_JOnAccountsUpdateListener> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJOnAccountsUpdateListener() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JOnAccountsUpdateListenerClass,_di_JOnAccountsUpdateListener>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJOnAccountsUpdateListener() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Accounts */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_ACCOUNTS)
using namespace Androidapi::Jni::Accounts;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_AccountsHPP
