// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.KinveyApi.pas' rev: 34.00 (Android)

#ifndef Rest_Backend_KinveyapiHPP
#define Rest_Backend_KinveyapiHPP

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
#include <REST.Backend.Exception.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Kinveyapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EKinveyAPIError;
class DELPHICLASS TKinveyApi;
class DELPHICLASS EKinveyDuplicateUser;
class DELPHICLASS EKinveyFileNotFound;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EKinveyAPIError : public Rest::Backend::Exception::EBackendAPIError
{
	typedef Rest::Backend::Exception::EBackendAPIError inherited;
	
private:
	System::UnicodeString FError;
	System::UnicodeString FDescription;
	
public:
	__fastcall EKinveyAPIError(const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */;
	__property System::UnicodeString Error = {read=FError};
	__property System::UnicodeString Description = {read=FDescription};
public:
	/* Exception.CreateFmt */ inline __fastcall EKinveyAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Backend::Exception::EBackendAPIError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyAPIError(NativeUInt Ident)/* overload */ : Rest::Backend::Exception::EBackendAPIError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyAPIError(System::PResStringRec ResStringRec)/* overload */ : Rest::Backend::Exception::EBackendAPIError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendAPIError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendAPIError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EKinveyAPIError(const System::UnicodeString Msg, int AHelpContext) : Rest::Backend::Exception::EBackendAPIError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EKinveyAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Backend::Exception::EBackendAPIError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyAPIError(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendAPIError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyAPIError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendAPIError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendAPIError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendAPIError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EKinveyAPIError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

_DECLARE_METACLASS(System::TMetaClass, TKinveyAPIErrorClass);

struct TUser;
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TKinveyApi : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	enum class DECLSPEC_DENUM TPlatformType : unsigned char { IOS, Android };
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TConnectionInfo
	{
	public:
		System::UnicodeString ApiVersion;
		System::UnicodeString AppKey;
		System::UnicodeString AppSecret;
		System::UnicodeString MasterSecret;
		System::UnicodeString UserName;
		System::UnicodeString Password;
		System::UnicodeString ProxyPassword;
		int ProxyPort;
		System::UnicodeString ProxyServer;
		System::UnicodeString ProxyUsername;
		__fastcall TConnectionInfo(const System::UnicodeString AApiVersion, const System::UnicodeString AAppKey)/* overload */;
		TConnectionInfo() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TUpdatedAt
	{
	private:
		System::TDateTime FUpdatedAt;
		
	public:
		__fastcall TUpdatedAt(System::TDateTime AUpdatedAt);
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		TUpdatedAt() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TObjectID
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FObjectID;
		System::UnicodeString FBackendCollectionName;
		
	public:
		__fastcall TObjectID(const System::UnicodeString ABackendCollectionName, System::UnicodeString AObjectID);
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString ObjectID = {read=FObjectID};
		__property System::UnicodeString BackendCollectionName = {read=FBackendCollectionName};
		TObjectID() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TFile
	{
	private:
		System::UnicodeString FID;
		System::UnicodeString FFileName;
		System::UnicodeString FDownloadURL;
		System::TDateTime FExpiresAt;
		
	public:
		__fastcall TFile(const System::UnicodeString AID);
		__property System::UnicodeString FileName = {read=FFileName};
		__property System::UnicodeString DownloadURL = {read=FDownloadURL};
		__property System::UnicodeString ID = {read=FID};
		__property System::TDateTime ExpiresAt = {read=FExpiresAt};
		TFile() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TUser
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FObjectID;
		System::UnicodeString FUserName;
		
	public:
		__fastcall TUser(const System::UnicodeString AUserName);
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString ObjectID = {read=FObjectID};
		__property System::UnicodeString UserName = {read=FUserName};
		TUser() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TUserGroup
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FObjectID;
		
	public:
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString ObjectID = {read=FObjectID};
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TLogin
	{
	private:
		System::UnicodeString FAuthToken;
		TKinveyApi::TUser FUser;
		
	public:
		__fastcall TLogin(const System::UnicodeString AAuthToken, const TKinveyApi::TUser &AUser);
		__property System::UnicodeString AuthToken = {read=FAuthToken};
		__property TKinveyApi::TUser User = {read=FUser};
		TLogin() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	enum class DECLSPEC_DENUM TAuthentication : unsigned char { Default, MasterSecret, AppSecret, UserName, Session, None };
	
	enum class DECLSPEC_DENUM TDefaultAuthentication : unsigned char { MasterSecret, AppSecret, UserName, Session, None };
	
	__interface DELPHIINTERFACE TFindObjectProc;
	typedef System::DelphiInterface<TFindObjectProc> _di_TFindObjectProc;
	__interface TFindObjectProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TKinveyApi::TObjectID &AID, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TQueryUserNameProc;
	typedef System::DelphiInterface<TQueryUserNameProc> _di_TQueryUserNameProc;
	__interface TQueryUserNameProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TKinveyApi::TUser &AUser, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TLoginProc;
	typedef System::DelphiInterface<TLoginProc> _di_TLoginProc;
	__interface TLoginProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TKinveyApi::TLogin &ALogin, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveUserProc;
	typedef System::DelphiInterface<TRetrieveUserProc> _di_TRetrieveUserProc;
	__interface TRetrieveUserProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TKinveyApi::TUser &AUser, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveFileProc;
	typedef System::DelphiInterface<TRetrieveFileProc> _di_TRetrieveFileProc;
	__interface TRetrieveFileProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TKinveyApi::TFile &AFile, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveUserGroupProc;
	typedef System::DelphiInterface<TRetrieveUserGroupProc> _di_TRetrieveUserGroupProc;
	__interface TRetrieveUserGroupProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TKinveyApi::TUserGroup &AUserGroup, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	
public:
	static constexpr bool DateTimeIsUTC = true;
	
	static TConnectionInfo EmptyConnectionInfo;
	
private:
	#define TKinveyApi_sAppKey u"appKey"
	
	#define TKinveyApi_sDateCreated u"ect"
	
	#define TKinveyApi_sDateUpdated u"lmt"
	
	static constexpr bool cDateTimeIsUTC = true;
	
	#define TKinveyApi_sDataStore u"appdata"
	
	#define TKinveyApi_sUserGroup u"group"
	
	#define TKinveyApi_sBlob u"blob"
	
	#define TKinveyApi_sUser u"user"
	
	#define TKinveyApi_sLogin u"login"
	
	#define TKinveyApi_sPush u"push"
	
	#define TKinveyApi_sRpc u"rpc"
	
	#define TKinveyApi_sRegisterDevice u"register-device"
	
	#define TKinveyApi_sUnregisterDevice u"unregister-device"
	
	#define TKinveyApi_sAppKeySegment u"/{appKey}"
	
	#define TKinveyApi_sUserAppKey u"user/{appKey}"
	
	#define TKinveyApi_sDataStoreAppKey u"appdata/{appKey}"
	
	#define TKinveyApi_sUserGroupAppKey u"group/{appKey}"
	
	#define TKinveyApi_sPushAppKey u"push/{appKey}"
	
	#define TKinveyApi_sBlobAppKey u"blob/{appKey}"
	
	#define TKinveyApi_sRpcAppKey u"rpc/{appKey}"
	
	#define TKinveyApi_sMessageElement u"message"
	
	#define TKinveyApi_sIOSApsElement u"iosaps"
	
	#define TKinveyApi_sIOSExtrasElement u"iosextras"
	
	#define TKinveyApi_sAndroidPayloadElement u"androidpayload"
	
	#define TKinveyApi_sUsersElement u"users"
	
	
public:
	static constexpr System::WideChar cDefaultApiVersion = (System::WideChar)(0x33);
	
	#define TKinveyApi_cDefaultBaseURL u"https://baas.kinvey.com/"
	
	
private:
	Rest::Client::TRESTClient* FRESTClient;
	Rest::Client::TRESTRequest* FRequest;
	Rest::Client::TRESTResponse* FResponse;
	System::UnicodeString FBaseURL;
	bool FOwnsResponse;
	TConnectionInfo FConnectionInfo;
	System::UnicodeString FSessionAuthToken;
	TAuthentication FAuthentication;
	TDefaultAuthentication FDefaultAuthentication;
	void __fastcall SetBaseURL(const System::UnicodeString Value);
	void __fastcall SetConnectionInfo(const TConnectionInfo &Value);
	bool __fastcall GetLoggedIn();
	
protected:
	TAuthentication __fastcall GetActualAuthentication();
	EKinveyAPIError* __fastcall CreateException(Rest::Client::TRESTRequest* const ARequest, const TKinveyAPIErrorClass AClass);
	void __fastcall AddAuthParameter()/* overload */;
	void __fastcall AddAuthParameter(TAuthentication Authentication)/* overload */;
	void __fastcall ApplyConnectionInfo();
	void __fastcall CheckForResponseError(Rest::Client::TRESTRequest* const ARequest)/* overload */;
	void __fastcall CheckForResponseError()/* overload */;
	void __fastcall CheckForResponseError(int *AValidStatusCodes, const int AValidStatusCodes_High)/* overload */;
	void __fastcall PostObject(const System::UnicodeString AResource, const System::UnicodeString ABackendCollectionName, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject, bool AReset)/* overload */;
	void __fastcall PostObject(const System::UnicodeString AResource, const System::UnicodeString ABackendCollectionName, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject, bool AReset)/* overload */;
	void __fastcall PutObject(const System::UnicodeString AResource, const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &AObject, bool AReset)/* overload */;
	void __fastcall PutObject(const System::UnicodeString AResource, const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &AObject, bool AReset)/* overload */;
	TObjectID __fastcall ObjectIDFromObject(const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TFile __fastcall FileFromObject(const System::UnicodeString AFileName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TFile __fastcall FileFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	int __fastcall DeleteObject(const System::UnicodeString AResource, bool AReset);
	bool __fastcall FindAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, /* out */ TObjectID &AFoundObject, System::Json::TJSONArray* const AJSON, _di_TFindObjectProc AProc)/* overload */;
	TLogin __fastcall LoginFromObject(const System::UnicodeString AUserName, System::Json::TJSONObject* const AJSONObject);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ TLogin &ALogin, System::Json::TJSONArray* const AJSON, _di_TLoginProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TQueryUserNameProc AProc)/* overload */;
	TUpdatedAt __fastcall UpdatedAtFromObject(System::Json::TJSONObject* const AJSONObject);
	TUser __fastcall UserFromObject(const System::UnicodeString AUserName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TUserGroup __fastcall UserGroupFromObject(const System::UnicodeString AUserGroupName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	bool __fastcall DeleteOrSuspendUser(const System::UnicodeString AObjectID, bool ADelete);
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TRetrieveUserProc AProc)/* overload */;
	void __fastcall QueryResource(const System::UnicodeString AResource, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, bool AReset);
	bool __fastcall RetrieveFile(const System::UnicodeString AFileID, /* out */ TFile &AFile, System::Json::TJSONArray* const AJSON, _di_TRetrieveFileProc AProc)/* overload */;
	bool __fastcall RetrieveUserGroup(const System::UnicodeString AObjectID, /* out */ TUserGroup &AUserGroup, System::Json::TJSONArray* const AJSON, _di_TRetrieveUserGroupProc AProc)/* overload */;
	bool __fastcall RetrieveUserGroup(const System::UnicodeString AObjectID, _di_TRetrieveUserGroupProc AProc)/* overload */;
	void __fastcall InvokeEndpoint(const System::UnicodeString AEndpointName, System::Json::TJSONObject* const AJSONParameters, bool AReset, bool ACheckError)/* overload */;
	__property Rest::Client::TRESTClient* RestClient = {read=FRESTClient};
	__property Rest::Client::TRESTRequest* Request = {read=FRequest};
	
public:
	__fastcall TKinveyApi(System::Classes::TComponent* AOwner, Rest::Client::TRESTResponse* const AResponse)/* overload */;
	__fastcall virtual ~TKinveyApi();
	TUser __fastcall UserFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	TObjectID __fastcall ObjectIDFromObject(const System::UnicodeString ABackendCollectionName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	void __fastcall AppHandshake(System::Json::TJSONArray* const AJSONArray);
	void __fastcall PushRegisterDevice(TPlatformType APlatformType, const System::UnicodeString ADeviceID, const System::UnicodeString AUserID)/* overload */;
	void __fastcall PushRegisterDevice(TPlatformType APlatformType, const System::UnicodeString ADeviceID)/* overload */;
	void __fastcall PushRegisterDevice(TPlatformType APlatformType, const System::UnicodeString ADeviceID, const TUser &AUser)/* overload */;
	void __fastcall PushUnregisterDevice(TPlatformType APlatformType, const System::UnicodeString ADeviceID, const System::UnicodeString AUserID)/* overload */;
	void __fastcall PushUnregisterDevice(TPlatformType APlatformType, const System::UnicodeString ADeviceID, const TUser &AUser)/* overload */;
	void __fastcall PushUnregisterDevice(TPlatformType APlatformType, const System::UnicodeString ADeviceID)/* overload */;
	void __fastcall CreateAppData(const System::UnicodeString ABackendCollectionName, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject)/* overload */;
	void __fastcall CreateAppData(const System::UnicodeString ABackendCollectionName, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject)/* overload */;
	bool __fastcall FindAppData(const TObjectID &AObject, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindAppData(const TObjectID &AObject, /* out */ TObjectID &AFoundObject, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall FindAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, /* out */ TObjectID &AFoundObject, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	int __fastcall DeleteAppData(const TObjectID &AObject)/* overload */;
	int __fastcall DeleteAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID)/* overload */;
	int __fastcall DeleteAppDataCollection(const System::UnicodeString ABackendCollectionName);
	void __fastcall UpdateAppData(const TObjectID &AObject, System::Json::TJSONObject* const AJSONObject, /* out */ TObjectID &AUpdateObject)/* overload */;
	void __fastcall UpdateAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject, /* out */ TObjectID &AUpdateObject)/* overload */;
	void __fastcall QueryAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryAppData(const System::UnicodeString ABackendCollectionName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TObjectID> &AObjects)/* overload */;
	bool __fastcall DeleteFile(const TFile &AFile)/* overload */;
	bool __fastcall DeleteFile(const System::UnicodeString AFileID)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, System::UnicodeString AContentType, bool APublic, System::Json::TJSONObject* const AUserFields, /* out */ TFile &ANewFile)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, System::Classes::TStream* const AStream, System::UnicodeString AContentType, bool APublic, System::Json::TJSONObject* const AUserFields, /* out */ TFile &ANewFile)/* overload */;
	void __fastcall DownloadFile(const TFile &AFile, System::Classes::TStream* const AStream);
	void __fastcall QueryFiles(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryFiles(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TFile> &AFiles)/* overload */;
	bool __fastcall RetrieveFile(const TFile &AFile, _di_TRetrieveFileProc AProc)/* overload */;
	bool __fastcall RetrieveFile(const TFile &AFile, /* out */ TFile &AFoundFile, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveFile(const System::UnicodeString AFileID, /* out */ TFile &AFile, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveFile(const System::UnicodeString AFileID, _di_TRetrieveFileProc AProc)/* overload */;
	void __fastcall CreateUserGroup(const System::UnicodeString AID, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AUsersAndGroups, /* out */ TUserGroup &ANewUserGroup)/* overload */;
	void __fastcall CreateUserGroup(const System::UnicodeString AID, System::Json::TJSONObject* const AUsersAndGroups, /* out */ TUserGroup &ANewUserGroup)/* overload */;
	void __fastcall UpdateUserGroup(const System::UnicodeString AID, System::Json::TJSONObject* const AUsersAndGroups, /* out */ TObjectID &AUpdateObject)/* overload */;
	void __fastcall UpdateUserGroup(const TUserGroup &AUserGroup, System::Json::TJSONObject* const AUsersAndGroups, /* out */ TObjectID &AUpdateObject)/* overload */;
	bool __fastcall DeleteUserGroup(const TUserGroup &AUserGroup)/* overload */;
	bool __fastcall DeleteUserGroup(const System::UnicodeString AID)/* overload */;
	bool __fastcall RetrieveUserGroup(const TUserGroup &AUserGroup, _di_TRetrieveUserGroupProc AProc)/* overload */;
	bool __fastcall RetrieveUserGroup(const TUserGroup &AUserGroup, /* out */ TUserGroup &AFoundUserGroup, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUserGroup(const System::UnicodeString AObjectID, /* out */ TUserGroup &AUserGroup, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, _di_TQueryUserNameProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const TUser &AUser, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveUser(const TUser &AUser, /* out */ TUser &AFoundUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, _di_TRetrieveUserProc AProc)/* overload */;
	void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserFields, /* out */ TLogin &ALogin);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, _di_TLoginProc AProc)/* overload */;
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ TLogin &ALogin, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall LogoutUser();
	void __fastcall RestoreSuspendedUser(const System::UnicodeString AObjectID)/* overload */;
	void __fastcall RestoreSuspendedUser(const TUser &AUser)/* overload */;
	bool __fastcall RetrieveCurrentUser(_di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveCurrentUser(/* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall UpdateUser(const System::UnicodeString AObjectID, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall UpdateUser(const TUser &AUser, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	bool __fastcall DeleteUser(const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall DeleteUser(const TUser &AUser)/* overload */;
	bool __fastcall SuspendUser(const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall SuspendUser(const TUser &AUser)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TUser> &AUsers)/* overload */;
	void __fastcall InvokeCustomEndpoint(const System::UnicodeString AEndpointName, System::Json::TJSONObject* const AJSONParameters, System::Json::TJSONArray* const AJSONResult);
	void __fastcall InvokeEndpoint(const System::UnicodeString AEndpointName, System::Json::TJSONObject* const AJSONParameters, System::Json::TJSONArray* const AJSONResult)/* overload */;
	void __fastcall BroadcastMessage(const System::UnicodeString AEndpointName, const System::UnicodeString AMessage);
	void __fastcall SendMessage(const System::UnicodeString AEndpointName, TUser *AUsers, const int AUsers_High, const System::UnicodeString AMessage);
	void __fastcall BroadcastPayload(const System::UnicodeString AEndpointName, System::Json::TJSONObject* const AIOSAps, System::Json::TJSONObject* const AIOSExtras, System::Json::TJSONObject* const AAndroidPayload);
	void __fastcall SendPayload(const System::UnicodeString AEndpointName, TUser *AUsers, const int AUsers_High, System::Json::TJSONObject* const AIOSAps, System::Json::TJSONObject* const AIOSExtras, System::Json::TJSONObject* const AAndroidPayload)/* overload */;
	void __fastcall SendPayload(const System::UnicodeString AEndpointName, System::UnicodeString *AUsers, const int AUsers_High, System::Json::TJSONObject* const AIOSAps, System::Json::TJSONObject* const AIOSExtras, System::Json::TJSONObject* const AAndroidPayload)/* overload */;
	void __fastcall Login(const System::UnicodeString ASessionAuthToken)/* overload */;
	void __fastcall Login(const TLogin &ALogin)/* overload */;
	void __fastcall Logout();
	__property bool LoggedIn = {read=GetLoggedIn, nodefault};
	__property TAuthentication Authentication = {read=FAuthentication, write=FAuthentication, nodefault};
	__property TDefaultAuthentication DefaultAuthentication = {read=FDefaultAuthentication, write=FDefaultAuthentication, nodefault};
	__property Rest::Client::TRESTResponse* Response = {read=FResponse};
	__property System::UnicodeString BaseURL = {read=FBaseURL, write=SetBaseURL};
	__property TConnectionInfo ConnectionInfo = {read=FConnectionInfo, write=SetConnectionInfo};
	
private:
	// __classmethod void __fastcall Create_();
	// __classmethod void __fastcall Destroy_();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EKinveyDuplicateUser : public EKinveyAPIError
{
	typedef EKinveyAPIError inherited;
	
public:
	/* EKinveyAPIError.Create */ inline __fastcall EKinveyDuplicateUser(const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EKinveyAPIError(AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EKinveyDuplicateUser(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EKinveyAPIError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyDuplicateUser(NativeUInt Ident)/* overload */ : EKinveyAPIError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyDuplicateUser(System::PResStringRec ResStringRec)/* overload */ : EKinveyAPIError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyDuplicateUser(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EKinveyAPIError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyDuplicateUser(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EKinveyAPIError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EKinveyDuplicateUser(const System::UnicodeString Msg, int AHelpContext) : EKinveyAPIError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EKinveyDuplicateUser(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EKinveyAPIError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyDuplicateUser(NativeUInt Ident, int AHelpContext)/* overload */ : EKinveyAPIError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyDuplicateUser(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EKinveyAPIError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyDuplicateUser(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EKinveyAPIError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyDuplicateUser(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EKinveyAPIError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EKinveyDuplicateUser() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EKinveyFileNotFound : public EKinveyAPIError
{
	typedef EKinveyAPIError inherited;
	
public:
	/* EKinveyAPIError.Create */ inline __fastcall EKinveyFileNotFound(const System::UnicodeString AError, const System::UnicodeString ADescription)/* overload */ : EKinveyAPIError(AError, ADescription) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EKinveyFileNotFound(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EKinveyAPIError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyFileNotFound(NativeUInt Ident)/* overload */ : EKinveyAPIError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EKinveyFileNotFound(System::PResStringRec ResStringRec)/* overload */ : EKinveyAPIError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyFileNotFound(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EKinveyAPIError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EKinveyFileNotFound(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EKinveyAPIError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EKinveyFileNotFound(const System::UnicodeString Msg, int AHelpContext) : EKinveyAPIError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EKinveyFileNotFound(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EKinveyAPIError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyFileNotFound(NativeUInt Ident, int AHelpContext)/* overload */ : EKinveyAPIError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EKinveyFileNotFound(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EKinveyAPIError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyFileNotFound(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EKinveyAPIError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EKinveyFileNotFound(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EKinveyAPIError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EKinveyFileNotFound() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Kinveyapi */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_KINVEYAPI)
using namespace Rest::Backend::Kinveyapi;
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
#endif	// Rest_Backend_KinveyapiHPP
