// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.EMSApi.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_EmsapiHPP
#define Rest_Backend_EmsapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.hpp>
#include <REST.Client.hpp>
#include <REST.Types.hpp>
#include <System.Net.URLClient.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Emsapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSClientAPI;
class DELPHICLASS EEMSClientAPIError;
class DELPHICLASS EEMSClientHTTPError;
class DELPHICLASS EEMSClientHTTPBadRequest;
class DELPHICLASS EEMSClientHTTPNotFound;
class DELPHICLASS EEMSClientHTTPDuplicate;
class DELPHICLASS EEMSClientHTTPUnauthorized;
class DELPHICLASS EEMSClientHTTPForbidden;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
typedef System::TMetaClass* TEMSClientHTTPErrorClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TEMSClientHTTPErrorClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TEMSClientAPI : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	struct DECLSPEC_DRECORD TConnectionInfo
	{
	public:
		System::UnicodeString ApiVersion;
		System::UnicodeString ApplicationId;
		System::UnicodeString AppSecret;
		System::UnicodeString MasterSecret;
		System::UnicodeString UserName;
		System::UnicodeString Password;
		System::UnicodeString ProxyPassword;
		int ProxyPort;
		System::UnicodeString ProxyServer;
		System::UnicodeString ProxyUsername;
		System::UnicodeString BaseURL;
		System::UnicodeString LoginResource;
		System::Net::Urlclient::TValidateCertificateEvent OnValidateCertificate;
		System::UnicodeString TenantId;
		System::UnicodeString TenantSecret;
	};
	
	
	struct DECLSPEC_DRECORD THeaderNames
	{
	public:
		#define TEMSClientAPI_THeaderNames_ApiVersion L"X-Embarcadero-Api-Version"
		
		#define TEMSClientAPI_THeaderNames_ApplicationId L"X-Embarcadero-Application-Id"
		
		#define TEMSClientAPI_THeaderNames_SessionToken L"X-Embarcadero-Session-Token"
		
		#define TEMSClientAPI_THeaderNames_MasterSecret L"X-Embarcadero-Master-Secret"
		
		#define TEMSClientAPI_THeaderNames_AppSecret L"X-Embarcadero-App-Secret"
		
		#define TEMSClientAPI_THeaderNames_TenantId L"X-Embarcadero-Tenant-Id"
		
		#define TEMSClientAPI_THeaderNames_TenantSecret L"X-Embarcadero-Tenant-Secret"
		
	};
	
	
	struct DECLSPEC_DRECORD TJSONNames
	{
	public:
		#define TEMSClientAPI_TJSONNames_UserName L"username"
		
		#define TEMSClientAPI_TJSONNames_Password L"password"
		
		#define TEMSClientAPI_TJSONNames_SessionToken L"sessionToken"
		
		#define TEMSClientAPI_TJSONNames_Error L"error"
		
		#define TEMSClientAPI_TJSONNames_Description L"description"
		
		#define TEMSClientAPI_TJSONNames_UserID L"_id"
		
		#define TEMSClientAPI_TJSONNames_GroupName L"groupname"
		
		#define TEMSClientAPI_TJSONNames_InstallationID L"_id"
		
		#define TEMSClientAPI_TJSONNames_MetaData L"_meta"
		
		#define TEMSClientAPI_TJSONNames_MetaCreated L"created"
		
		#define TEMSClientAPI_TJSONNames_MetaUpdated L"updated"
		
		#define TEMSClientAPI_TJSONNames_MetaCreator L"creator"
		
		#define TEMSClientAPI_TJSONNames_PushWhere L"where"
		
		#define TEMSClientAPI_TJSONNames_PushChannels L"channels"
		
		#define TEMSClientAPI_TJSONNames_PushData L"data"
		
		#define TEMSClientAPI_TJSONNames_PushBadge L"badge"
		
		#define TEMSClientAPI_TJSONNames_FieldName L"name"
		
		#define TEMSClientAPI_TJSONNames_FieldCustom L"custom"
		
		#define TEMSClientAPI_TJSONNames_FieldFields L"fields"
		
		#define TEMSClientAPI_TJSONNames_ModuleID L"_id"
		
		#define TEMSClientAPI_TJSONNames_ResourceModuleID L"moduleid"
		
		#define TEMSClientAPI_TJSONNames_ModuleName L"modulename"
		
		#define TEMSClientAPI_TJSONNames_Protocol L"protocol"
		
		#define TEMSClientAPI_TJSONNames_ResourceName L"resourcename"
		
		#define TEMSClientAPI_TJSONNames_ProtocolProps L"protocolprops"
		
		#define TEMSClientAPI_TJSONNames_Resources L"resources"
		
	};
	
	
	struct DECLSPEC_DRECORD TSegmentNames
	{
	public:
		#define TEMSClientAPI_TSegmentNames_Users L"users"
		
		#define TEMSClientAPI_TSegmentNames_UsersFields L"users/fields"
		
		#define TEMSClientAPI_TSegmentNames_Groups L"groups"
		
		#define TEMSClientAPI_TSegmentNames_GroupsFields L"groups/fields"
		
		#define TEMSClientAPI_TSegmentNames_Installations L"installations"
		
		#define TEMSClientAPI_TSegmentNames_InstallationsChannels L"installations/channels"
		
		#define TEMSClientAPI_TSegmentNames_InstallationsFields L"installations/fields"
		
		#define TEMSClientAPI_TSegmentNames_Login L"login"
		
		#define TEMSClientAPI_TSegmentNames_Signup L"signup"
		
		#define TEMSClientAPI_TSegmentNames_Logout L"logout"
		
		#define TEMSClientAPI_TSegmentNames_Restore L"_restore"
		
		#define TEMSClientAPI_TSegmentNames_Me L"me"
		
		#define TEMSClientAPI_TSegmentNames_Push L"push"
		
		#define TEMSClientAPI_TSegmentNames_Modules L"edgemodules"
		
		#define TEMSClientAPI_TSegmentNames_ModulesResources L"edgemodules/resources"
		
		#define TEMSClientAPI_TSegmentNames_ModulesFields L"edgemodules/fields"
		
		#define TEMSClientAPI_TSegmentNames_ResourcesFields L"edgemodules/resources/fields"
		
		#define TEMSClientAPI_TSegmentNames_Resources L"resources"
		
	};
	
	
	struct DECLSPEC_DRECORD TQueryParamNames
	{
	public:
		#define TEMSClientAPI_TQueryParamNames_Order L"order"
		
		#define TEMSClientAPI_TQueryParamNames_Where L"where"
		
		#define TEMSClientAPI_TQueryParamNames_Limit L"limit"
		
		#define TEMSClientAPI_TQueryParamNames_Skip L"skip"
		
	};
	
	
	struct DECLSPEC_DRECORD TUpdatedAt
	{
	private:
		System::TDateTime FUpdatedAt;
		
	public:
		__fastcall TUpdatedAt(System::TDateTime AUpdatedAt);
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		TUpdatedAt() {}
	};
	
	
	struct DECLSPEC_DRECORD TUser
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FUserID;
		System::UnicodeString FUserName;
		System::UnicodeString FCreator;
		
	public:
		__fastcall TUser(const System::UnicodeString AUserName, const System::UnicodeString AUserID);
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString UserID = {read=FUserID};
		__property System::UnicodeString UserName = {read=FUserName};
		__property System::UnicodeString Creator = {read=FCreator};
		TUser() {}
	};
	
	
	struct DECLSPEC_DRECORD TGroup
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FGroupName;
		System::UnicodeString FCreator;
		
	public:
		__fastcall TGroup(const System::UnicodeString AGroupName);
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString GroupName = {read=FGroupName};
		__property System::UnicodeString Creator = {read=FCreator};
		TGroup() {}
	};
	
	
	struct DECLSPEC_DRECORD TLogin
	{
	private:
		System::UnicodeString FAuthToken;
		TEMSClientAPI::TUser FUser;
		
	public:
		__fastcall TLogin(const System::UnicodeString AAuthToken, const TEMSClientAPI::TUser &AUser);
		__property System::UnicodeString AuthToken = {read=FAuthToken};
		__property TEMSClientAPI::TUser User = {read=FUser};
		TLogin() {}
	};
	
	
	struct DECLSPEC_DRECORD TInstallation
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FInstallationID;
		System::UnicodeString FCreator;
		
	public:
		__fastcall TInstallation(const System::UnicodeString AInstallationID);
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString InstallationID = {read=FInstallationID};
		__property System::UnicodeString Creator = {read=FCreator};
		TInstallation() {}
	};
	
	
	struct DECLSPEC_DRECORD TModule
	{
	private:
		System::UnicodeString FModuleID;
		System::UnicodeString FModuleName;
		System::UnicodeString FProtocol;
		System::UnicodeString FProtocolProps;
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FCreator;
		
	public:
		__fastcall TModule(const System::UnicodeString AModuleID, const System::UnicodeString AName);
		__property System::UnicodeString ModuleID = {read=FModuleID};
		__property System::UnicodeString ModuleName = {read=FModuleName};
		__property System::UnicodeString Protocol = {read=FProtocol};
		__property System::UnicodeString ProtocolProps = {read=FProtocolProps};
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString Creator = {read=FCreator};
		TModule() {}
	};
	
	
	struct DECLSPEC_DRECORD TModuleResource
	{
	private:
		System::UnicodeString FResourceName;
		System::UnicodeString FModuleName;
		System::UnicodeString FModuleID;
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FCreator;
		
	public:
		__fastcall TModuleResource(const System::UnicodeString AName, const System::UnicodeString AModuleID, const System::UnicodeString AModuleName);
		__property System::UnicodeString ResourceName = {read=FResourceName};
		__property System::UnicodeString ModuleName = {read=FModuleName};
		__property System::UnicodeString ModuleID = {read=FModuleID};
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString Creator = {read=FCreator};
		TModuleResource() {}
	};
	
	
	typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::Json::TJSONObject*> TResourcePair;
	
#ifndef _WIN64
	typedef System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::Json::TJSONObject*> > TResourceList;
#else /* _WIN64 */
	typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::Json::TJSONObject*> > TResourceList;
#endif /* _WIN64 */
	
	struct DECLSPEC_DRECORD TDeviceTypes
	{
	public:
		#define TEMSClientAPI_TDeviceTypes_IOS L"ios"
		
		#define TEMSClientAPI_TDeviceTypes_Android L"android"
		
	};
	
	
	struct DECLSPEC_DRECORD TPushStatus
	{
	private:
		int FAndroid;
		int FIOS;
		
	public:
		__fastcall TPushStatus(int AIOS, int AAndroid);
		__property int QueuedIOS = {read=FIOS};
		__property int QueuedAndroid = {read=FAndroid};
		TPushStatus() {}
	};
	
	
	struct DECLSPEC_DRECORD TCreatorNames
	{
	public:
		#define TEMSClientAPI_TCreatorNames_Master L"00000000-0000-0000-0000-000000000001"
		
		#define TEMSClientAPI_TCreatorNames_Null L"00000000-0000-0000-0000-000000000000"
		
	};
	
	
	enum class DECLSPEC_DENUM TAuthentication : unsigned char { Default, MasterSecret, AppSecret, Session, None };
	
	enum class DECLSPEC_DENUM TDefaultAuthentication : unsigned char { AppSecret, MasterSecret, Session, None };
	
	__interface DELPHIINTERFACE TAppHandshakeProc;
	typedef System::DelphiInterface<TAppHandshakeProc> _di_TAppHandshakeProc;
	__interface TAppHandshakeProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TQueryUserNameProc;
	typedef System::DelphiInterface<TQueryUserNameProc> _di_TQueryUserNameProc;
	__interface TQueryUserNameProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TUser &AUser, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TLoginProc;
	typedef System::DelphiInterface<TLoginProc> _di_TLoginProc;
	__interface TLoginProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TLogin &ALogin, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveUserProc;
	typedef System::DelphiInterface<TRetrieveUserProc> _di_TRetrieveUserProc;
	__interface TRetrieveUserProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TUser &AUser, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveGroupProc;
	typedef System::DelphiInterface<TRetrieveGroupProc> _di_TRetrieveGroupProc;
	__interface TRetrieveGroupProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TGroup &AGroup, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveInstallationProc;
	typedef System::DelphiInterface<TRetrieveInstallationProc> _di_TRetrieveInstallationProc;
	__interface TRetrieveInstallationProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TInstallation &AInstallation, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveModuleProc;
	typedef System::DelphiInterface<TRetrieveModuleProc> _di_TRetrieveModuleProc;
	__interface TRetrieveModuleProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TModule &AModule, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveModuleResourceProc;
	typedef System::DelphiInterface<TRetrieveModuleResourceProc> _di_TRetrieveModuleResourceProc;
	__interface TRetrieveModuleResourceProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TModuleResource &AResource, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TQueryModuleNameProc;
	typedef System::DelphiInterface<TQueryModuleNameProc> _di_TQueryModuleNameProc;
	__interface TQueryModuleNameProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TEMSClientAPI::TModule &AModule, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	
public:
	static const bool DateTimeIsUTC = true;
	
	static TConnectionInfo EmptyConnectionInfo;
	static const System::WideChar cDefaultApiVersion = (System::WideChar)(0x32);
	
	
private:
	Rest::Client::TRESTClient* FRESTClient;
	Rest::Client::TRESTRequest* FRequest;
	Rest::Client::TRESTResponse* FResponse;
	bool FOwnsResponse;
	TConnectionInfo FConnectionInfo;
	System::UnicodeString FSessionAuthToken;
	TAuthentication FAuthentication;
	TDefaultAuthentication FDefaultAuthentication;
	bool FInLogin;
	void __fastcall SetConnectionInfo(const TConnectionInfo &Value);
	bool __fastcall GetLoggedIn();
	
protected:
	void __fastcall AddAuthHeader(Rest::Client::TCustomRESTRequest* const ARequest, const System::UnicodeString AKey, const System::UnicodeString AValue);
	System::UnicodeString __fastcall MakeLoginResource(const System::UnicodeString ASegmentName);
	bool __fastcall MetaDataFromObject(System::Json::TJSONObject* const AJSONObject, /* out */ System::TDateTime &ACreatedAt, /* out */ System::TDateTime &AUpdatedAt, /* out */ System::UnicodeString &ACreator);
	bool __fastcall DeleteResource(const System::UnicodeString AResource, const System::UnicodeString AID, const System::Sysutils::_di_TProc AAddParameters = System::Sysutils::_di_TProc());
	void __fastcall PutResource(const System::UnicodeString AResource, const System::UnicodeString AID, System::Json::TJSONObject* const AJSON, const System::Sysutils::_di_TProc AAddParameters = System::Sysutils::_di_TProc());
	void __fastcall AddResource(const System::UnicodeString AResource, System::Json::TJSONObject* const AJSON, const System::Sysutils::_di_TProc AAddParameters = System::Sysutils::_di_TProc());
	void __fastcall QueryResource(const System::UnicodeString AResource, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, bool AReset, const System::Sysutils::_di_TProc AAddParameters = System::Sysutils::_di_TProc());
	bool __fastcall RetrieveInstallation(const System::UnicodeString AInstallationID, /* out */ TInstallation &AFoundInstallation, System::Json::TJSONArray* const AJSON, _di_TRetrieveInstallationProc AProc, bool AReset)/* overload */;
	void __fastcall AddAppSecret(Rest::Client::TCustomRESTRequest* const ARequest, const System::UnicodeString AKey);
	void __fastcall DoAddAuthParameters()/* overload */;
	void __fastcall DoAddAuthParameters(TAuthentication AAuthentication)/* overload */;
	void __fastcall DoAddAuthParameters(Rest::Client::TCustomRESTRequest* const ARequest, TAuthentication AAuthentication)/* overload */;
	void __fastcall AddMasterKey(Rest::Client::TCustomRESTRequest* const ARequest, const System::UnicodeString AKey);
	void __fastcall AddSessionToken(Rest::Client::TCustomRESTRequest* const ARequest, const System::UnicodeString ASessionToken);
	void __fastcall AddTenantId(Rest::Client::TCustomRESTRequest* const ARequest, const System::UnicodeString AKey);
	TAuthentication __fastcall GetActualAuthentication();
	EEMSClientHTTPError* __fastcall CreateHTTPException(Rest::Client::TCustomRESTResponse* const AResponse, const TEMSClientHTTPErrorClass AClass)/* overload */;
	EEMSClientHTTPError* __fastcall CreateHTTPException(Rest::Client::TCustomRESTResponse* const AResponse)/* overload */;
	void __fastcall CheckForResponseError()/* overload */;
	void __fastcall CheckForResponseError(int *AValidStatusCodes, const int AValidStatusCodes_High)/* overload */;
	TLogin __fastcall LoginFromObject(const System::UnicodeString AUserName, System::Json::TJSONObject* const AJSONObject);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ TLogin &ALogin, System::Json::TJSONArray* const AJSON, _di_TLoginProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TQueryUserNameProc AProc)/* overload */;
	TUpdatedAt __fastcall UpdatedAtFromObject(System::Json::TJSONObject* const AJSONObject);
	TUser __fastcall UserFromObject(const System::UnicodeString AUserName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveGroup(const System::UnicodeString AGroupName, /* out */ TGroup &AGroup, System::Json::TJSONArray* const AJSON, _di_TRetrieveGroupProc AProc)/* overload */;
	bool __fastcall RetrieveModule(const System::UnicodeString AModuleID, /* out */ TModule &AModule, System::Json::TJSONArray* const AJSON, _di_TRetrieveModuleProc AProc)/* overload */;
	bool __fastcall RetrieveModuleResource(const System::UnicodeString AModuleID, const System::UnicodeString AResourceName, /* out */ TModuleResource &AResource, System::Json::TJSONArray* const AJSON, _di_TRetrieveModuleResourceProc AProc)/* overload */;
	TGroup __fastcall GroupFromObject(const System::UnicodeString AGroupName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TGroup __fastcall GroupFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	TInstallation __fastcall InstallationFromObject(const System::UnicodeString AInstallationID, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TInstallation __fastcall InstallationFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	void __fastcall ApplyConnectionInfo()/* overload */;
	__property Rest::Client::TRESTClient* RestClient = {read=FRESTClient};
	__property Rest::Client::TRESTRequest* Request = {read=FRequest};
	void __fastcall PushBody(System::Json::TJSONObject* const AMessage)/* overload */;
	void __fastcall PushBody(System::Json::TJSONObject* const AMessage, /* out */ TPushStatus &AStatus)/* overload */;
	TPushStatus __fastcall PushStatusFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	System::Json::TJSONObject* __fastcall CreateInstallationObject(const System::UnicodeString ADeviceType, const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties)/* overload */;
	System::Json::TJSONObject* __fastcall CreateInstallationObject(const System::UnicodeString ADeviceType, const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties, System::UnicodeString *AChannels, const int AChannels_High)/* overload */;
	void __fastcall RetrieveFields(const System::UnicodeString AResourceName, System::Json::TJSONArray* const AFields);
	TModule __fastcall ModuleFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	TModule __fastcall ModuleFromObject(const System::UnicodeString AModuleID, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TModuleResource __fastcall ResourceFromObject(System::Json::TJSONObject* const AJSONObject);
	bool __fastcall QueryModuleName(const System::UnicodeString AModuleName, /* out */ TModule &AModule, System::Json::TJSONArray* const AJSON, _di_TQueryModuleNameProc AProc)/* overload */;
	
public:
	__fastcall TEMSClientAPI()/* overload */;
	__fastcall TEMSClientAPI(System::Classes::TComponent* AOwner, Rest::Client::TRESTResponse* const AResponse)/* overload */;
	__fastcall virtual ~TEMSClientAPI();
	void __fastcall CheckForResponseError(Rest::Client::TCustomRESTResponse* const AResponse, const int *AValidStatusCodes, const int AValidStatusCodes_High)/* overload */;
	void __fastcall CheckForResponseError(Rest::Client::TCustomRESTResponse* const AResponse)/* overload */;
	void __fastcall ApplyConnectionInfo(Rest::Client::TCustomRESTClient* const AClient)/* overload */;
	void __fastcall AddAuthParameters(Rest::Client::TCustomRESTRequest* const ARequest)/* overload */;
	TUser __fastcall UserFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	void __fastcall AppHandshake(System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall AppHandshake(const _di_TAppHandshakeProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, _di_TQueryUserNameProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const TUser &AUser, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveUser(const TUser &AUser, /* out */ TUser &AFoundUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, _di_TRetrieveUserProc AProc)/* overload */;
	void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserFields, /* out */ TLogin &ALogin);
	void __fastcall AddUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserFields, /* out */ TUser &AUser);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, _di_TLoginProc AProc)/* overload */;
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ TLogin &ALogin, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall LogoutUser();
	bool __fastcall RetrieveCurrentUser(_di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveCurrentUser(/* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall UpdateUser(const System::UnicodeString AObjectID, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall UpdateUser(const TUser &AUser, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	bool __fastcall DeleteUser(const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall DeleteUser(const TUser &AUser)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TUser> &AUsers)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TUser> &AUsers)/* overload */;
#endif /* _WIN64 */
	void __fastcall RetrieveUsersFields(System::Json::TJSONArray* const AFields);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall RetrieveUsersNames();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall RetrieveUsersNames();
#endif /* _WIN64 */
	void __fastcall QueryGroups(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryGroups(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TGroup> &AGroups)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryGroups(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TGroup> &AGroups)/* overload */;
#endif /* _WIN64 */
	void __fastcall CreateGroup(const System::UnicodeString AGroupName, System::Json::TJSONObject* const AGroupFields, /* out */ TGroup &AGroup);
	void __fastcall UpdateGroup(const System::UnicodeString AGroupName, System::Json::TJSONObject* const AGroupObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall UpdateGroup(const TGroup &AGroup, System::Json::TJSONObject* const AGroupObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	bool __fastcall DeleteGroup(const System::UnicodeString AGroupName)/* overload */;
	bool __fastcall DeleteGroup(const TGroup &AGroup)/* overload */;
	bool __fastcall RetrieveGroup(const System::UnicodeString AGroupName, /* out */ TGroup &AFoundGroup, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveGroup(const System::UnicodeString AGroupName, _di_TRetrieveGroupProc AProc)/* overload */;
	bool __fastcall RetrieveGroup(const TGroup &AGroup, /* out */ TGroup &AFoundGroup, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveGroup(const TGroup &AGroup, _di_TRetrieveGroupProc AProc)/* overload */;
#ifndef _WIN64
	void __fastcall AddUsersToGroup(const System::UnicodeString AGroupName, const System::DynamicArray<System::UnicodeString> AUsers, /* out */ TUpdatedAt &AUpdatedAt);
	bool __fastcall RemoveUsersFromGroup(const System::UnicodeString AGroupName, const System::DynamicArray<System::UnicodeString> AUsers, /* out */ TUpdatedAt &AUpdatedAt);
#else /* _WIN64 */
	void __fastcall AddUsersToGroup(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ TUpdatedAt &AUpdatedAt);
	bool __fastcall RemoveUsersFromGroup(const System::UnicodeString AGroupName, const System::TArray__1<System::UnicodeString> AUsers, /* out */ TUpdatedAt &AUpdatedAt);
#endif /* _WIN64 */
	void __fastcall RetrieveGroupsFields(System::Json::TJSONArray* const AFields);
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall RetrieveGroupsNames();
	System::DynamicArray<System::UnicodeString> __fastcall RetrieveUserGroups(const System::UnicodeString AUserID);
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall RetrieveGroupsNames();
	System::TArray__1<System::UnicodeString> __fastcall RetrieveUserGroups(const System::UnicodeString AUserID);
#endif /* _WIN64 */
	System::Json::TJSONObject* __fastcall CreateAndroidInstallationObject(const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties)/* overload */;
	System::Json::TJSONObject* __fastcall CreateAndroidInstallationObject(const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties, System::UnicodeString *AChannels, const int AChannels_High)/* overload */;
	System::Json::TJSONObject* __fastcall CreateIOSInstallationObject(const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties)/* overload */;
	System::Json::TJSONObject* __fastcall CreateIOSInstallationObject(const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties, System::UnicodeString *AChannels, const int AChannels_High)/* overload */;
	void __fastcall UploadInstallation(System::Json::TJSONObject* const AJSON, /* out */ TInstallation &ANewObject);
	void __fastcall UpdateInstallation(const System::UnicodeString AInstallationID, System::Json::TJSONObject* const AJSONObject, /* out */ TUpdatedAt &AUpdatedAt);
	bool __fastcall DeleteInstallation(const System::UnicodeString AInstallationID)/* overload */;
	void __fastcall QueryInstallations(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryInstallations(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TInstallation> &AObjects)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryInstallations(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TInstallation> &AObjects)/* overload */;
#endif /* _WIN64 */
	bool __fastcall RetrieveInstallation(const System::UnicodeString AInstallationID, /* out */ TInstallation &AFoundInstallation, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveInstallation(const System::UnicodeString AInstallationID, _di_TRetrieveInstallationProc AProc)/* overload */;
	bool __fastcall RetrieveInstallation(const TInstallation &AInstallation, /* out */ TInstallation &AFoundInstallation, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveInstallation(const TInstallation &AInstallation, _di_TRetrieveInstallationProc AProc)/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall RetrieveInstallationsChannelNames();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall RetrieveInstallationsChannelNames();
#endif /* _WIN64 */
	void __fastcall RetrieveInstallationsFields(System::Json::TJSONArray* const AFields);
	void __fastcall PushBroadcast(System::Json::TJSONObject* const AData)/* overload */;
	void __fastcall PushBroadcast(System::Json::TJSONObject* const AData, /* out */ TPushStatus &AStatus)/* overload */;
	void __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget)/* overload */;
	void __fastcall PushToTarget(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const ATarget, /* out */ TPushStatus &AStatus)/* overload */;
	void __fastcall PushToChannels(System::Json::TJSONObject* const AData, const System::UnicodeString *AChannels, const int AChannels_High)/* overload */;
	void __fastcall PushToChannels(System::Json::TJSONObject* const AData, const System::UnicodeString *AChannels, const int AChannels_High, /* out */ TPushStatus &AStatus)/* overload */;
	void __fastcall PushWhere(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const AWhere)/* overload */;
	void __fastcall PushWhere(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const AWhere, /* out */ TPushStatus &AStatus)/* overload */;
	void __fastcall RegisterModule(const System::UnicodeString AName, const System::UnicodeString AProtocol, const System::UnicodeString AProtocolProps, System::Json::TJSONObject* const ADetails, System::Json::TJSONArray* const AResources, /* out */ TModule &AModule)/* overload */;
#ifndef _WIN64
	void __fastcall RegisterModule(const System::UnicodeString AModuleName, const System::UnicodeString AProtocol, const System::UnicodeString AProtocolProps, System::Json::TJSONObject* const ADetails, const System::DynamicArray<System::Generics::Collections::TPair__2<System::UnicodeString,System::Json::TJSONObject*> > Resources, /* out */ TModule &AModule)/* overload */;
#else /* _WIN64 */
	void __fastcall RegisterModule(const System::UnicodeString AModuleName, const System::UnicodeString AProtocol, const System::UnicodeString AProtocolProps, System::Json::TJSONObject* const ADetails, const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::Json::TJSONObject*> > Resources, /* out */ TModule &AModule)/* overload */;
#endif /* _WIN64 */
	bool __fastcall UnregisterModule(const System::UnicodeString AModuleID);
	void __fastcall QueryModules(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryModules(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TModule> &AModules)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryModules(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TModule> &AModules)/* overload */;
#endif /* _WIN64 */
	void __fastcall UpdateModule(const System::UnicodeString AModuleID, const System::UnicodeString AModuleName, const System::UnicodeString AProtocol, const System::UnicodeString AProtocolProps, System::Json::TJSONObject* const AJSONObject, System::Json::TJSONArray* const AResources, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall UpdateModule(const System::UnicodeString AModuleID, System::Json::TJSONObject* const AJSONObject, System::Json::TJSONArray* const AResources, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	bool __fastcall RetrieveModule(const System::UnicodeString AModuleID, /* out */ TModule &AFoundModule, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveModule(const System::UnicodeString AModuleID, _di_TRetrieveModuleProc AProc)/* overload */;
	bool __fastcall RetrieveModule(const TModule &AModule, /* out */ TModule &AFoundModule, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveModule(const TModule &AModule, _di_TRetrieveModuleProc AProc)/* overload */;
	void __fastcall RetrieveModulesFields(System::Json::TJSONArray* const AFields);
	bool __fastcall QueryModuleName(const System::UnicodeString AModuleName, _di_TQueryModuleNameProc AProc)/* overload */;
	bool __fastcall QueryModuleName(const System::UnicodeString AModuleName, /* out */ TModule &AModule, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall UnregisterModuleResource(const System::UnicodeString AModuleID, const System::UnicodeString AName);
	void __fastcall QueryModuleResources(const System::UnicodeString AModuleID, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryModuleResources(const System::UnicodeString AModuleID, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TModuleResource> &AResources)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryModuleResources(const System::UnicodeString AModuleID, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TModuleResource> &AResources)/* overload */;
#endif /* _WIN64 */
	void __fastcall UpdateModuleResource(const System::UnicodeString AModuleID, const System::UnicodeString AResourceName, System::Json::TJSONObject* const AJSONObject, /* out */ TUpdatedAt &AUpdatedAt);
	bool __fastcall RetrieveModuleResource(const System::UnicodeString AModuleID, const System::UnicodeString AResourceName, /* out */ TModuleResource &AFoundResource, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveModuleResource(const System::UnicodeString AModuleID, const System::UnicodeString AResourceName, _di_TRetrieveModuleResourceProc AProc)/* overload */;
	bool __fastcall RetrieveModuleResource(const TModuleResource &AResource, /* out */ TModuleResource &AFoundResource, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveModuleResource(const TModuleResource &AResource, _di_TRetrieveModuleResourceProc AProc)/* overload */;
	void __fastcall RetrieveModuleResourcesFields(System::Json::TJSONArray* const AFields);
	void __fastcall Login(const System::UnicodeString ASessionAuthToken)/* overload */;
	void __fastcall Login(const TLogin &ALogin)/* overload */;
	void __fastcall Logout();
	__property bool LoggedIn = {read=GetLoggedIn, nodefault};
	__property TAuthentication Authentication = {read=FAuthentication, write=FAuthentication, nodefault};
	__property TDefaultAuthentication DefaultAuthentication = {read=FDefaultAuthentication, write=FDefaultAuthentication, nodefault};
	__property Rest::Client::TRESTResponse* Response = {read=FResponse};
	__property TConnectionInfo ConnectionInfo = {read=FConnectionInfo, write=SetConnectionInfo};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientAPIError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EEMSClientAPIError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EEMSClientAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientAPIError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientAPIError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientAPIError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientAPIError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientAPIError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientAPIError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientHTTPError : public EEMSClientAPIError
{
	typedef EEMSClientAPIError inherited;
	
	
public:
#ifndef _WIN64
	#pragma pack(push,8)
#endif /* not _WIN64 */
	struct DECLSPEC_DRECORD TCodes
	{
	public:
		static const System::Word BadRequest = System::Word(0x190);
		
		static const System::Word NotFound = System::Word(0x194);
		
		static const System::Word Duplicate = System::Word(0x199);
		
		static const System::Word Unauthorized = System::Word(0x191);
		
		static const System::Word Forbidden = System::Word(0x193);
		
	};
#ifndef _WIN64
	#pragma pack(pop)
#endif /* not _WIN64 */
	
	
	
private:
	System::UnicodeString FError;
	System::UnicodeString FDescription;
	int FCode;
	
public:
	__fastcall EEMSClientHTTPError(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */;
	__property int Code = {read=FCode, nodefault};
	__property System::UnicodeString Error = {read=FError};
	__property System::UnicodeString Description = {read=FDescription};
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSClientHTTPError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSClientAPIError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPError(NativeUInt Ident)/* overload */ : EEMSClientAPIError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPError(System::PResStringRec ResStringRec)/* overload */ : EEMSClientAPIError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientAPIError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientAPIError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientHTTPError(const System::UnicodeString Msg, int AHelpContext) : EEMSClientAPIError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientHTTPError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSClientAPIError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPError(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSClientAPIError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSClientAPIError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientAPIError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientAPIError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientHTTPError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientHTTPBadRequest : public EEMSClientHTTPError
{
	typedef EEMSClientHTTPError inherited;
	
public:
	/* EEMSClientHTTPError.Create */ inline __fastcall EEMSClientHTTPBadRequest(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EEMSClientHTTPError(ACode, AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSClientHTTPBadRequest(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSClientHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPBadRequest(NativeUInt Ident)/* overload */ : EEMSClientHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPBadRequest(System::PResStringRec ResStringRec)/* overload */ : EEMSClientHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPBadRequest(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPBadRequest(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientHTTPBadRequest(const System::UnicodeString Msg, int AHelpContext) : EEMSClientHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientHTTPBadRequest(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSClientHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPBadRequest(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPBadRequest(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPBadRequest(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPBadRequest(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientHTTPBadRequest() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientHTTPNotFound : public EEMSClientHTTPError
{
	typedef EEMSClientHTTPError inherited;
	
public:
	/* EEMSClientHTTPError.Create */ inline __fastcall EEMSClientHTTPNotFound(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EEMSClientHTTPError(ACode, AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSClientHTTPNotFound(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSClientHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPNotFound(NativeUInt Ident)/* overload */ : EEMSClientHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPNotFound(System::PResStringRec ResStringRec)/* overload */ : EEMSClientHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPNotFound(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPNotFound(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientHTTPNotFound(const System::UnicodeString Msg, int AHelpContext) : EEMSClientHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientHTTPNotFound(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSClientHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPNotFound(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPNotFound(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPNotFound(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPNotFound(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientHTTPNotFound() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientHTTPDuplicate : public EEMSClientHTTPError
{
	typedef EEMSClientHTTPError inherited;
	
public:
	/* EEMSClientHTTPError.Create */ inline __fastcall EEMSClientHTTPDuplicate(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EEMSClientHTTPError(ACode, AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSClientHTTPDuplicate(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSClientHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPDuplicate(NativeUInt Ident)/* overload */ : EEMSClientHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPDuplicate(System::PResStringRec ResStringRec)/* overload */ : EEMSClientHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPDuplicate(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPDuplicate(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientHTTPDuplicate(const System::UnicodeString Msg, int AHelpContext) : EEMSClientHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientHTTPDuplicate(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSClientHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPDuplicate(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPDuplicate(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPDuplicate(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPDuplicate(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientHTTPDuplicate() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientHTTPUnauthorized : public EEMSClientHTTPError
{
	typedef EEMSClientHTTPError inherited;
	
public:
	/* EEMSClientHTTPError.Create */ inline __fastcall EEMSClientHTTPUnauthorized(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EEMSClientHTTPError(ACode, AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSClientHTTPUnauthorized(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSClientHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPUnauthorized(NativeUInt Ident)/* overload */ : EEMSClientHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPUnauthorized(System::PResStringRec ResStringRec)/* overload */ : EEMSClientHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPUnauthorized(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPUnauthorized(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientHTTPUnauthorized(const System::UnicodeString Msg, int AHelpContext) : EEMSClientHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientHTTPUnauthorized(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSClientHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPUnauthorized(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPUnauthorized(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPUnauthorized(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPUnauthorized(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientHTTPUnauthorized() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EEMSClientHTTPForbidden : public EEMSClientHTTPError
{
	typedef EEMSClientHTTPError inherited;
	
public:
	/* EEMSClientHTTPError.Create */ inline __fastcall EEMSClientHTTPForbidden(int ACode, const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EEMSClientHTTPError(ACode, AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EEMSClientHTTPForbidden(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EEMSClientHTTPError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPForbidden(NativeUInt Ident)/* overload */ : EEMSClientHTTPError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EEMSClientHTTPForbidden(System::PResStringRec ResStringRec)/* overload */ : EEMSClientHTTPError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPForbidden(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EEMSClientHTTPForbidden(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EEMSClientHTTPForbidden(const System::UnicodeString Msg, int AHelpContext) : EEMSClientHTTPError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EEMSClientHTTPForbidden(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EEMSClientHTTPError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPForbidden(NativeUInt Ident, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EEMSClientHTTPForbidden(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPForbidden(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EEMSClientHTTPForbidden(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EEMSClientHTTPError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EEMSClientHTTPForbidden() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Emsapi */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EMSAPI)
using namespace Rest::Backend::Emsapi;
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
#endif	// Rest_Backend_EmsapiHPP
