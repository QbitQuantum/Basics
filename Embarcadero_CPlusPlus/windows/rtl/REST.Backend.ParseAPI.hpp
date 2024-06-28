// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.ParseApi.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_ParseapiHPP
#define Rest_Backend_ParseapiHPP

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
namespace Parseapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EParseAPIError;
class DELPHICLASS TParseApi;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EParseAPIError : public Rest::Backend::Exception::EBackendError
{
	typedef Rest::Backend::Exception::EBackendError inherited;
	
private:
	int FCode;
	System::UnicodeString FError;
	
public:
	__fastcall EParseAPIError(int ACode, const System::UnicodeString AError)/* overload */;
	__property int Code = {read=FCode, nodefault};
	__property System::UnicodeString Error = {read=FError};
public:
	/* Exception.CreateFmt */ inline __fastcall EParseAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Rest::Backend::Exception::EBackendError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EParseAPIError(NativeUInt Ident)/* overload */ : Rest::Backend::Exception::EBackendError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EParseAPIError(System::PResStringRec ResStringRec)/* overload */ : Rest::Backend::Exception::EBackendError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EParseAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EParseAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Rest::Backend::Exception::EBackendError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EParseAPIError(const System::UnicodeString Msg, int AHelpContext) : Rest::Backend::Exception::EBackendError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EParseAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Rest::Backend::Exception::EBackendError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParseAPIError(NativeUInt Ident, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EParseAPIError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParseAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EParseAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Rest::Backend::Exception::EBackendError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EParseAPIError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TParseAPIErrorClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TParseAPIErrorClass);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TParseApi : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	struct DECLSPEC_DRECORD TDeviceNames
	{
	public:
		#define TParseApi_TDeviceNames_IOS L"ios"
		
		#define TParseApi_TDeviceNames_Android L"android"
		
	};
	
	
	struct DECLSPEC_DRECORD TConnectionInfo
	{
	public:
		System::UnicodeString ApiVersion;
		System::UnicodeString ApplicationID;
		System::UnicodeString RestApiKey;
		System::UnicodeString MasterKey;
		System::UnicodeString ProxyPassword;
		int ProxyPort;
		System::UnicodeString ProxyServer;
		System::UnicodeString ProxyUsername;
		__fastcall TConnectionInfo(const System::UnicodeString AApiVersion, const System::UnicodeString AApplicationID);
		TConnectionInfo() {}
	};
	
	
	struct DECLSPEC_DRECORD TUpdatedAt
	{
	private:
		System::TDateTime FUpdatedAt;
		System::UnicodeString FObjectID;
		System::UnicodeString FBackendClassName;
		
	public:
		__fastcall TUpdatedAt(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, System::TDateTime AUpdatedAt);
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString ObjectID = {read=FObjectID};
		__property System::UnicodeString BackendClassName = {read=FBackendClassName};
		TUpdatedAt() {}
	};
	
	
	struct DECLSPEC_DRECORD TObjectID
	{
	private:
		System::TDateTime FCreatedAt;
		System::TDateTime FUpdatedAt;
		System::UnicodeString FObjectID;
		System::UnicodeString FBackendClassName;
		
	public:
		__fastcall TObjectID(const System::UnicodeString ABackendClassName, System::UnicodeString AObjectID);
		__property System::TDateTime CreatedAt = {read=FCreatedAt};
		__property System::TDateTime UpdatedAt = {read=FUpdatedAt};
		__property System::UnicodeString ObjectID = {read=FObjectID};
		__property System::UnicodeString BackendClassName = {read=FBackendClassName};
		TObjectID() {}
	};
	
	
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
	
	
	struct DECLSPEC_DRECORD TLogin
	{
	private:
		System::UnicodeString FSessionToken;
		TParseApi::TUser FUser;
		
	public:
		__fastcall TLogin(const System::UnicodeString ASessionToken, const TParseApi::TUser &AUser);
		__property System::UnicodeString SessionToken = {read=FSessionToken};
		__property TParseApi::TUser User = {read=FUser};
		TLogin() {}
	};
	
	
	struct DECLSPEC_DRECORD TFile
	{
	private:
		System::UnicodeString FName;
		System::UnicodeString FFileName;
		System::UnicodeString FDownloadURL;
		
	public:
		__fastcall TFile(const System::UnicodeString AName);
		__property System::UnicodeString FileName = {read=FFileName};
		__property System::UnicodeString DownloadURL = {read=FDownloadURL};
		__property System::UnicodeString Name = {read=FName};
		TFile() {}
	};
	
	
	enum class DECLSPEC_DENUM TAuthentication : unsigned char { Default, MasterKey, APIKey, Session, None };
	
	typedef System::Set<TAuthentication, _DELPHI_SET_ENUMERATOR(TAuthentication::Default), _DELPHI_SET_ENUMERATOR(TAuthentication::None)> TAuthentications;
	
	enum class DECLSPEC_DENUM TDefaultAuthentication : unsigned char { APIKey, MasterKey, Session, None };
	
	__interface DELPHIINTERFACE TFindObjectProc;
	typedef System::DelphiInterface<TFindObjectProc> _di_TFindObjectProc;
	__interface TFindObjectProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TParseApi::TObjectID &AID, System::Json::TJSONObject* const AObj) = 0 ;
	};
	
	__interface DELPHIINTERFACE TQueryUserNameProc;
	typedef System::DelphiInterface<TQueryUserNameProc> _di_TQueryUserNameProc;
	__interface TQueryUserNameProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TParseApi::TUser &AUser, System::Json::TJSONObject* const AUserObject) = 0 ;
	};
	
	__interface DELPHIINTERFACE TLoginProc;
	typedef System::DelphiInterface<TLoginProc> _di_TLoginProc;
	__interface TLoginProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TParseApi::TLogin &ALogin, System::Json::TJSONObject* const AUserObject) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveUserProc;
	typedef System::DelphiInterface<TRetrieveUserProc> _di_TRetrieveUserProc;
	__interface TRetrieveUserProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(const TParseApi::TUser &AUser, System::Json::TJSONObject* const AUserObject) = 0 ;
	};
	
	__interface DELPHIINTERFACE TRetrieveJSONProc;
	typedef System::DelphiInterface<TRetrieveJSONProc> _di_TRetrieveJSONProc;
	__interface TRetrieveJSONProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::Json::TJSONObject* const AUserObject) = 0 ;
	};
	
	
private:
	#define TParseApi_sClasses L"classes"
	
	#define TParseApi_sInstallations L"installations"
	
	#define TParseApi_sFiles L"files"
	
	#define TParseApi_sUsers L"users"
	
	#define TParseApi_sPush L"push"
	
	
public:
	static const System::WideChar cDefaultApiVersion = (System::WideChar)(0x31);
	
	#define TParseApi_cDefaultBaseURL L"https://api.parse.com/{ApiVersion}"
	
	static const bool DateTimeIsUTC = true;
	
	static TConnectionInfo EmptyConnectionInfo;
	
private:
	Rest::Client::TRESTClient* FRESTClient;
	Rest::Client::TRESTRequest* FRequest;
	Rest::Client::TRESTResponse* FResponse;
	bool FOwnsResponse;
	System::UnicodeString FBaseURL;
	TConnectionInfo FConnectionInfo;
	System::UnicodeString FSessionToken;
	TAuthentication FAuthentication;
	TDefaultAuthentication FDefaultAuthentication;
	void __fastcall SetConnectionInfo(const TConnectionInfo &Value);
	void __fastcall SetBaseURL(const System::UnicodeString Value);
	bool __fastcall GetLoggedIn();
	
protected:
	void __fastcall AddMasterKey(const System::UnicodeString AKey)/* overload */;
	void __fastcall AddAPIKey(const System::UnicodeString AKey)/* overload */;
	void __fastcall AddSessionToken(const System::UnicodeString AAPIKey, const System::UnicodeString ASessionToken)/* overload */;
	void __fastcall ApplyConnectionInfo();
	void __fastcall CheckAuthentication(TAuthentications AAuthentication);
	TAuthentication __fastcall GetActualAuthentication();
	EParseAPIError* __fastcall CreateException(Rest::Client::TRESTRequest* const ARequest, const TParseAPIErrorClass AClass);
	void __fastcall CheckForResponseError(int *AValidStatusCodes, const int AValidStatusCodes_High)/* overload */;
	void __fastcall CheckForResponseError()/* overload */;
	void __fastcall CheckForResponseError(Rest::Client::TRESTRequest* const ARequest)/* overload */;
	void __fastcall CheckForResponseError(Rest::Client::TRESTRequest* const ARequest, int *AValidStatusCodes, const int AValidStatusCodes_High)/* overload */;
	void __fastcall PostResource(const System::UnicodeString AResource, System::Json::TJSONObject* const AJSON, bool AReset);
	void __fastcall PutResource(const System::UnicodeString AResource, System::Json::TJSONObject* const AJSONObject, bool AReset);
	bool __fastcall DeleteResource(const System::UnicodeString AResource, bool AReset)/* overload */;
	TObjectID __fastcall ObjectIDFromObject(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TFile __fastcall FileIDFromObject(const System::UnicodeString AFileName, System::Json::TJSONObject* const AJSONObject);
	void __fastcall AddAuthParameters()/* overload */;
	void __fastcall AddAuthParameters(TAuthentication AAuthentication)/* overload */;
	bool __fastcall FindClass(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, /* out */ TObjectID &AFoundObject, System::Json::TJSONArray* const AJSON, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TQueryUserNameProc AProc)/* overload */;
	TLogin __fastcall LoginFromObject(const System::UnicodeString AUserName, System::Json::TJSONObject* const AJSONObject);
	TUser __fastcall UserFromObject(const System::UnicodeString AUserName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	TUpdatedAt __fastcall UpdatedAtFromObject(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject);
	void __fastcall QueryResource(const System::UnicodeString AResource, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, bool AReset);
	bool __fastcall RetrieveCurrentUser(const System::UnicodeString ASessionToken, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString ASessionID, const System::UnicodeString AObjectID, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON, _di_TRetrieveUserProc AProc, bool AReset)/* overload */;
	void __fastcall UpdateUser(const System::UnicodeString ASessionID, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	bool __fastcall DoRetrieveInstallation(const System::UnicodeString AObjectID, System::Json::TJSONArray* const AJSON, _di_TRetrieveJSONProc AProc, bool AReset)/* overload */;
	__property Rest::Client::TRESTClient* RestClient = {read=FRESTClient};
	__property Rest::Client::TRESTRequest* Request = {read=FRequest};
	
public:
	__fastcall TParseApi(System::Classes::TComponent* AOwner, Rest::Client::TRESTResponse* const AResponse)/* overload */;
	__fastcall virtual ~TParseApi();
	TUser __fastcall UserFromObject(System::Json::TJSONObject* const AJSONObject)/* overload */;
	TObjectID __fastcall ObjectIDFromObject(const System::UnicodeString ABackendClassName, System::Json::TJSONObject* const AJSONObject)/* overload */;
	void __fastcall CreateClass(const System::UnicodeString ABackendClassName, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject)/* overload */;
	void __fastcall CreateClass(const System::UnicodeString ABackendClassName, System::Json::TJSONObject* const AACL, System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject)/* overload */;
	bool __fastcall DeleteClass(const TObjectID &AID)/* overload */;
	bool __fastcall DeleteClass(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall FindClass(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindClass(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, /* out */ TObjectID &AFoundObjectID, System::Json::TJSONArray* const AFoundJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall FindClass(const TObjectID &AID, _di_TFindObjectProc AProc)/* overload */;
	bool __fastcall FindClass(const TObjectID &AID, /* out */ TObjectID &AFoundObjectID, System::Json::TJSONArray* const AFoundJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall UpdateClass(const System::UnicodeString ABackendClassName, const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall UpdateClass(const TObjectID &AID, System::Json::TJSONObject* const AJSONObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall QueryClass(const System::UnicodeString ABackendClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryClass(const System::UnicodeString ABackendClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TObjectID> &AObjects)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryClass(const System::UnicodeString ABackendClassName, const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TObjectID> &AObjects)/* overload */;
#endif /* _WIN64 */
	System::Json::TJSONObject* __fastcall CreateAndroidInstallationObject(const System::UnicodeString AInstallationID, const System::UnicodeString ADeviceToken, System::UnicodeString *AChannels, const int AChannels_High)/* overload */;
	System::Json::TJSONObject* __fastcall CreateAndroidInstallationObject(const System::UnicodeString AInstallationID, const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties)/* overload */;
	System::Json::TJSONObject* __fastcall CreateAndroidInstallationObject(const System::UnicodeString AGCMAppID, const System::UnicodeString AInstallationID, const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties)/* overload */;
	System::Json::TJSONObject* __fastcall CreateIOSInstallationObject(const System::UnicodeString ADeviceToken, int ABadge, System::UnicodeString *AChannels, const int AChannels_High)/* overload */;
	System::Json::TJSONObject* __fastcall CreateIOSInstallationObject(const System::UnicodeString ADeviceToken, System::Json::TJSONObject* const AProperties)/* overload */;
	void __fastcall UploadInstallation(System::Json::TJSONObject* const AJSON, /* out */ TObjectID &ANewObject);
	void __fastcall UpdateInstallation(const System::UnicodeString AObjectID, System::Json::TJSONObject* const AJSONObject, /* out */ TUpdatedAt &AUpdatedAt);
	bool __fastcall DeleteInstallation(const System::UnicodeString AObjectID)/* overload */;
	void __fastcall QueryInstallation(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryInstallation(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TObjectID> &AObjects)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryInstallation(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TObjectID> &AObjects)/* overload */;
#endif /* _WIN64 */
	bool __fastcall RetrieveInstallation(const System::UnicodeString AObjectID, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	void __fastcall PushBody(System::Json::TJSONObject* const AMessage);
	void __fastcall PushToDevices(const System::UnicodeString *ADevices, const int ADevices_High, System::Json::TJSONObject* const AData);
	void __fastcall PushBroadcast(System::Json::TJSONObject* const AData)/* overload */;
	void __fastcall PushBroadcast(System::Json::TJSONObject* const AData, System::Json::TJSONObject* const AFilter)/* overload */;
	void __fastcall PushToChannels(const System::UnicodeString *AChannels, const int AChannels_High, System::Json::TJSONObject* const AData);
	void __fastcall PushWhere(System::Json::TJSONObject* const AWhere, System::Json::TJSONObject* const AData);
	void __fastcall UploadFile(const System::UnicodeString AFileName, const System::UnicodeString AContentType, /* out */ TFile &ANewFile)/* overload */;
	void __fastcall UploadFile(const System::UnicodeString AFileName, System::Classes::TStream* const AStream, const System::UnicodeString AContentType, /* out */ TFile &ANewFile)/* overload */;
	bool __fastcall DeleteFile(const TFile &AFileID);
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, _di_TQueryUserNameProc AProc)/* overload */;
	bool __fastcall QueryUserName(const System::UnicodeString AUserName, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveUser(const System::UnicodeString AObjectID, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveUser(const TLogin &ALogin, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveUser(const TLogin &ALogin, /* out */ TUser &AUser, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall SignupUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, System::Json::TJSONObject* const AUserFields, /* out */ TLogin &ANewUser);
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, _di_TLoginProc AProc)/* overload */;
	void __fastcall LoginUser(const System::UnicodeString AUserName, const System::UnicodeString APassword, /* out */ TLogin &ALogin, System::Json::TJSONArray* const AJSONArray = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveCurrentUser(_di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveCurrentUser(/* out */ TUser &AUser, System::Json::TJSONArray* const AJSON = (System::Json::TJSONArray*)(0x0))/* overload */;
	bool __fastcall RetrieveCurrentUser(const TLogin &ALogin, _di_TRetrieveUserProc AProc)/* overload */;
	bool __fastcall RetrieveCurrentUser(const TLogin &ALogin, System::Json::TJSONArray* const AJSON)/* overload */;
	void __fastcall UpdateUser(const System::UnicodeString AObjectID, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	void __fastcall UpdateUser(const TLogin &ALogin, System::Json::TJSONObject* const AUserObject, /* out */ TUpdatedAt &AUpdatedAt)/* overload */;
	bool __fastcall DeleteUser(const System::UnicodeString AObjectID)/* overload */;
	bool __fastcall DeleteUser(const TLogin &ALogin)/* overload */;
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray)/* overload */;
#ifndef _WIN64
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::DynamicArray<TUser> &AUsers)/* overload */;
#else /* _WIN64 */
	void __fastcall QueryUsers(const System::UnicodeString *AQuery, const int AQuery_High, System::Json::TJSONArray* const AJSONArray, /* out */ System::TArray__1<TUser> &AUsers)/* overload */;
#endif /* _WIN64 */
	void __fastcall Login(const System::UnicodeString ASessionToken)/* overload */;
	void __fastcall Login(const TLogin &ALogin)/* overload */;
	void __fastcall Logout();
	__property bool LoggedIn = {read=GetLoggedIn, nodefault};
	__property TAuthentication Authentication = {read=FAuthentication, write=FAuthentication, nodefault};
	__property TDefaultAuthentication DefaultAuthentication = {read=FDefaultAuthentication, write=FDefaultAuthentication, nodefault};
	__property Rest::Client::TRESTResponse* Response = {read=FResponse};
	__property System::UnicodeString BaseURL = {read=FBaseURL, write=SetBaseURL};
	__property TConnectionInfo ConnectionInfo = {read=FConnectionInfo, write=SetConnectionInfo};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Parseapi */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_PARSEAPI)
using namespace Rest::Backend::Parseapi;
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
#endif	// Rest_Backend_ParseapiHPP
