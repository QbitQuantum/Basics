// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSClientRest.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsclientrestHPP
#define Datasnap_DsclientrestHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <Data.DB.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <Datasnap.DSCommonProxy.hpp>
#include <Datasnap.DSHTTPClient.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dsclientrest
{
//-- forward type declarations -----------------------------------------------
struct TDSRestParameterMetaData;
class DELPHICLASS TDSRestLoginProperties;
class DELPHICLASS TDSCustomRestConnection;
class DELPHICLASS TDSRestConnection;
class DELPHICLASS TDSRestCommand;
__interface DELPHIINTERFACE TDSRestResponseStreamProc;
typedef System::DelphiInterface<TDSRestResponseStreamProc> _di_TDSRestResponseStreamProc;
class DELPHICLASS TDSRestCacheCommand;
__interface DELPHIINTERFACE IDSRestCachedCommand;
typedef System::DelphiInterface<IDSRestCachedCommand> _di_IDSRestCachedCommand;
__interface DELPHIINTERFACE IDSRestCachedItem;
typedef System::DelphiInterface<IDSRestCachedItem> _di_IDSRestCachedItem;
__interface DELPHIINTERFACE IDSRestCachedJSONObject;
typedef System::DelphiInterface<IDSRestCachedJSONObject> _di_IDSRestCachedJSONObject;
__interface DELPHIINTERFACE IDSRestCachedJSONArray;
typedef System::DelphiInterface<IDSRestCachedJSONArray> _di_IDSRestCachedJSONArray;
__interface DELPHIINTERFACE IDSRestCachedJSONValue;
typedef System::DelphiInterface<IDSRestCachedJSONValue> _di_IDSRestCachedJSONValue;
__interface DELPHIINTERFACE IDSRestCachedDBXReader;
typedef System::DelphiInterface<IDSRestCachedDBXReader> _di_IDSRestCachedDBXReader;
__interface DELPHIINTERFACE IDSRestCachedDataSet;
typedef System::DelphiInterface<IDSRestCachedDataSet> _di_IDSRestCachedDataSet;
__interface DELPHIINTERFACE IDSRestCachedParams;
typedef System::DelphiInterface<IDSRestCachedParams> _di_IDSRestCachedParams;
__interface DELPHIINTERFACE IDSRestCachedStream;
typedef System::DelphiInterface<IDSRestCachedStream> _di_IDSRestCachedStream;
template<typename T> __interface DELPHIINTERFACE IDSRestCachedObject__1;
#ifdef __clang__
template<typename T> using _di_IDSRestCachedObject__1 = System::DelphiInterface<IDSRestCachedObject__1<T>>;
#endif
__interface DELPHIINTERFACE TGetJSONValueCallback;
typedef System::DelphiInterface<TGetJSONValueCallback> _di_TGetJSONValueCallback;
class DELPHICLASS TDSRestCachedItem;
class DELPHICLASS TDSRestCachedJSONObject;
class DELPHICLASS TDSRestCachedJSONArray;
class DELPHICLASS TDSRestCachedJSONValue;
class DELPHICLASS TDSRestCachedStream;
class DELPHICLASS TDSRestCachedDataSet;
class DELPHICLASS TDSRestCachedParams;
class DELPHICLASS TDSRestCachedDBXReader;
template<typename T> class DELPHICLASS TDSRestCachedObject__1;
struct TDSRESTChannelEventItem;
class DELPHICLASS TDSRestClientChannel;
class DELPHICLASS TDSRestCallbackLoop;
class DELPHICLASS TDSRestClientCallback;
class DELPHICLASS TDSRestException;
class DELPHICLASS TDSRestProtocolException;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TDSRestParameterMetaData
{
public:
	System::UnicodeString Name;
	int Direction;
	int DBXType;
	System::UnicodeString TypeName;
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestLoginProperties : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	
public:
	System::UnicodeString UserName;
	System::UnicodeString Password;
	bool LoginPrompt;
public:
	/* TPersistent.Destroy */ inline __fastcall virtual ~TDSRestLoginProperties() { }
	
public:
	/* TObject.Create */ inline __fastcall TDSRestLoginProperties() : System::Classes::TPersistent() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TDSRestLoginEvent)(System::TObject* Sender, TDSRestLoginProperties* LoginProperties, bool &Cancel);

enum DECLSPEC_DENUM TDSTestConnectionOption : unsigned char { toNoLoginPrompt };

typedef System::Set<TDSTestConnectionOption, TDSTestConnectionOption::toNoLoginPrompt, TDSTestConnectionOption::toNoLoginPrompt> TDSTestConnectionOptions;

class PASCALIMPLEMENTATION TDSCustomRestConnection : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
public:
	#define TDSCustomRestConnection_sCacheContext L"cache/"
	
	#define TDSCustomRestConnection_sRESTContext L"rest/"
	
	#define TDSCustomRestConnection_sContext L"datasnap/"
	
	#define TDSCustomRestConnection_sHttp L"http"
	
	
private:
	System::UnicodeString FProtocol;
	System::UnicodeString FHost;
	int FPort;
	System::UnicodeString FUrlPath;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FUniqueID;
	System::UnicodeString FContext;
	System::UnicodeString FRESTContext;
	System::UnicodeString FCacheContext;
	TDSRestLoginProperties* FLoginProperties;
	Datasnap::Dshttpclient::TDSHTTP* FHTTP;
	System::UnicodeString FSessionID;
	System::UnicodeString FProxyHost;
	int FProxyPort;
	System::UnicodeString FProxyUsername;
	System::UnicodeString FProxyPassword;
	System::UnicodeString FConnectionKeepAlive;
	System::Net::Httpclient::THTTPSecureProtocols FSecureProtocols;
	
private:
	bool FLoginPrompt;
	TDSRestLoginEvent FOnLogin;
	Data::Dbxcommon::TValidateCertificate FOnValidatePeerCertificate;
	Data::Dbxcommon::TValidateCertificateErr FOnValidatePeerCertificateERR;
	System::Net::Urlclient::TValidateCertificateEvent FOnValidateCertificate;
	System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent FOnAuthentication;
	System::Net::Urlclient::TNeedClientCertificateEvent FOnSelectClientCertificate;
	System::Classes::TNotifyEvent FBeforeExecute;
	System::Classes::TNotifyEvent FAfterExecute;
	bool FPreserveSessionID;
	void __fastcall ReadUniqueId(System::Classes::TReader* Reader);
	void __fastcall WriteUniqueId(System::Classes::TWriter* Writer);
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetUserName();
	bool __fastcall IsConnectionStored();
	bool __fastcall IsContextStored();
	bool __fastcall IsProtocolStored();
	bool __fastcall IsRESTContextStored();
	bool __fastcall IsCacheContextStored();
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	void __fastcall SetLoginPrompt(const bool Value);
	bool __fastcall GetLoginPrompt();
	void __fastcall LoginDialogTestConnection();
	void __fastcall SetContext(const System::UnicodeString Value);
	void __fastcall SetRESTContext(const System::UnicodeString Value);
	void __fastcall SetCacheContext(const System::UnicodeString Value);
	Datasnap::Dshttpclient::TDSHTTP* __fastcall GetHTTP();
	Data::Dbxcommon::TValidateCertificate __fastcall GetOnValidatePeerCertificate();
	Data::Dbxcommon::TValidateCertificateErr __fastcall GetOnValidatePeerCertificateErr();
	void __fastcall SetOnValidatePeerCertificate(const Data::Dbxcommon::TValidateCertificate Value);
	void __fastcall SetOnValidatePeerCertificateErr(const Data::Dbxcommon::TValidateCertificateErr Value);
	System::Net::Urlclient::TValidateCertificateEvent __fastcall GetOnValidateCertificate();
	void __fastcall SetOnValidateCertificate(const System::Net::Urlclient::TValidateCertificateEvent Value);
	System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent __fastcall GetOnAuthentication();
	void __fastcall SetOnAuthentication(const System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent Value);
	System::Net::Urlclient::TNeedClientCertificateEvent __fastcall GetOnNeedClientCertificate();
	void __fastcall SetOnNeedClientCertificate(const System::Net::Urlclient::TNeedClientCertificateEvent Value);
	void __fastcall SetProtocol(const System::UnicodeString Value);
	System::Net::Httpclient::THTTPSecureProtocols __fastcall GetSecureProtocols();
	void __fastcall SetSecureProtocols(const System::Net::Httpclient::THTTPSecureProtocols Value);
	
protected:
	virtual bool __fastcall Login();
	virtual void __fastcall BeforeExecute();
	virtual void __fastcall AfterExecute();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall SessionExpired();
	virtual void __fastcall SetConnection(const System::UnicodeString KeepAlive);
	virtual System::UnicodeString __fastcall GetConnection();
	virtual System::UnicodeString __fastcall GetProxyHost();
	virtual void __fastcall SetProxyHost(const System::UnicodeString Value);
	virtual int __fastcall GetProxyPort();
	void __fastcall SetProxyPort(const int Value);
	virtual System::UnicodeString __fastcall GetProxyUsername();
	virtual void __fastcall SetProxyUsername(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetProxyPassword();
	virtual void __fastcall SetProxyPassword(const System::UnicodeString Value);
	
public:
	__fastcall virtual TDSCustomRestConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSCustomRestConnection();
	void __fastcall TestConnection(TDSTestConnectionOptions AOptions = TDSTestConnectionOptions() );
	TDSRestCommand* __fastcall CreateCommand();
	System::UnicodeString __fastcall DefaultProtocol();
	void __fastcall ClearSessionCredentials();
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall GetSessionCredentials();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall GetSessionCredentials();
#endif /* _WIN64 */
	void __fastcall Reset();
	__property System::UnicodeString Protocol = {read=FProtocol, write=SetProtocol, stored=IsProtocolStored};
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property int Port = {read=FPort, write=FPort, nodefault};
	__property System::UnicodeString UrlPath = {read=FUrlPath, write=FUrlPath};
	__property System::UnicodeString Context = {read=FContext, write=SetContext, stored=IsContextStored};
	__property System::UnicodeString RESTContext = {read=FRESTContext, write=SetRESTContext, stored=IsRESTContextStored};
	__property System::UnicodeString CacheContext = {read=FCacheContext, write=SetCacheContext, stored=IsCacheContextStored};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString UniqueID = {read=FUniqueID, write=FUniqueID};
	__property bool LoginPrompt = {read=GetLoginPrompt, write=SetLoginPrompt, default=1};
	__property TDSRestLoginEvent OnLogin = {read=FOnLogin, write=FOnLogin};
	__property System::UnicodeString SessionID = {read=FSessionID, write=FSessionID};
	__property TDSRestLoginProperties* LoginProperties = {read=FLoginProperties};
	__property bool PreserveSessionID = {read=FPreserveSessionID, write=FPreserveSessionID, default=1};
	__property Data::Dbxcommon::TValidateCertificate OnValidatePeerCertificate = {read=GetOnValidatePeerCertificate, write=SetOnValidatePeerCertificate};
	__property Data::Dbxcommon::TValidateCertificateErr OnValidatePeerCertificateErr = {read=GetOnValidatePeerCertificateErr, write=SetOnValidatePeerCertificateErr};
	__property System::Net::Urlclient::TValidateCertificateEvent OnValidateCertificate = {read=GetOnValidateCertificate, write=SetOnValidateCertificate};
	__property System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent OnAuthentication = {read=GetOnAuthentication, write=SetOnAuthentication};
	__property System::Net::Urlclient::TNeedClientCertificateEvent OnSelectClientCertificate = {read=GetOnNeedClientCertificate, write=SetOnNeedClientCertificate};
	__property System::Classes::TNotifyEvent OnBeforeExecute = {read=FBeforeExecute, write=FBeforeExecute};
	__property System::Classes::TNotifyEvent OnAfterExecute = {read=FAfterExecute, write=FAfterExecute};
	__property Datasnap::Dshttpclient::TDSHTTP* HTTP = {read=GetHTTP};
	__property System::UnicodeString Connection = {read=GetConnection, write=SetConnection, stored=IsConnectionStored};
	__property System::UnicodeString ProxyHost = {read=GetProxyHost, write=SetProxyHost};
	__property int ProxyPort = {read=GetProxyPort, write=SetProxyPort, default=8888};
	__property System::UnicodeString ProxyUsername = {read=GetProxyUsername, write=SetProxyUsername};
	__property System::UnicodeString ProxyPassword = {read=GetProxyPassword, write=SetProxyPassword};
	__property System::Net::Httpclient::THTTPSecureProtocols SecureProtocols = {read=GetSecureProtocols, write=SetSecureProtocols, nodefault};
};


class PASCALIMPLEMENTATION TDSRestConnection : public TDSCustomRestConnection
{
	typedef TDSCustomRestConnection inherited;
	
__published:
	__property Protocol;
	__property Host = {default=0};
	__property Port;
	__property UrlPath = {default=0};
	__property Context;
	__property RESTContext;
	__property CacheContext;
	__property UserName = {default=0};
	__property Password = {default=0};
	__property LoginPrompt = {default=1};
	__property PreserveSessionID = {default=1};
	__property Connection;
	__property ProxyHost = {default=0};
	__property ProxyPort = {default=8888};
	__property ProxyUsername = {default=0};
	__property ProxyPassword = {default=0};
	__property SecureProtocols;
	__property OnLogin;
	__property OnValidatePeerCertificate;
	__property OnValidatePeerCertificateErr;
	__property OnValidateCertificate;
	__property OnAuthentication;
	__property OnBeforeExecute;
	__property OnAfterExecute;
	__property OnSelectClientCertificate;
public:
	/* TDSCustomRestConnection.Create */ inline __fastcall virtual TDSRestConnection(System::Classes::TComponent* AOwner) : TDSCustomRestConnection(AOwner) { }
	/* TDSCustomRestConnection.Destroy */ inline __fastcall virtual ~TDSRestConnection() { }
	
};


typedef System::DynamicArray<TDSRestParameterMetaData> TDSRestParameterMetaDataArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCommand : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxcommon::TDBXContext* FDBXContext;
	TDSCustomRestConnection* FConnection;
	System::UnicodeString FText;
	Data::Dbxcommon::TDBXParameterList* FParameters;
	System::UnicodeString FRequestType;
	System::Generics::Collections::TList__1<System::TObject*>* FFreeOnExecuteList;
	Data::Dbxcommon::TDBXParameterList* __fastcall CreateParameters(TDSRestParameterMetaData *AMetaData, const int AMetaData_High);
	
private:
	void __fastcall AfterExecute();
	void __fastcall BeforeExecute();
#ifndef _WIN64
	System::DynamicArray<TDSRestParameterMetaData> __fastcall BuildParameterMetaDataArray()/* overload */;
	System::DynamicArray<TDSRestParameterMetaData> __fastcall BuildParameterMetaDataArray(Datasnap::Dscommonproxy::TDSProxyMetadata* AProxyMetaData)/* overload */;
#else /* _WIN64 */
	System::TArray__1<TDSRestParameterMetaData> __fastcall BuildParameterMetaDataArray()/* overload */;
	System::TArray__1<TDSRestParameterMetaData> __fastcall BuildParameterMetaDataArray(Datasnap::Dscommonproxy::TDSProxyMetadata* AProxyMetaData)/* overload */;
#endif /* _WIN64 */
	System::UnicodeString __fastcall DetermineRequestType(TDSRestParameterMetaData *AMetaData, const int AMetaData_High);
	
public:
	__fastcall TDSRestCommand(TDSCustomRestConnection* AConnection);
	__fastcall virtual ~TDSRestCommand();
	void __fastcall Prepare(TDSRestParameterMetaData *AMetaData, const int AMetaData_High)/* overload */;
	void __fastcall Prepare(Datasnap::Dscommonproxy::TDSProxyMetadata* AProxyMetaData)/* overload */;
	void __fastcall Prepare()/* overload */;
	void __fastcall Execute(const System::UnicodeString ARequestFilter = System::UnicodeString());
	void __fastcall ExecuteCache(const System::UnicodeString ARequestFilter = System::UnicodeString());
	__property System::UnicodeString Text = {read=FText, write=FText};
	__property Data::Dbxcommon::TDBXParameterList* Parameters = {read=FParameters};
	__property System::UnicodeString RequestType = {read=FRequestType, write=FRequestType};
	__property TDSCustomRestConnection* Connection = {read=FConnection};
	Data::Dbxjsonreflect::TJSONMarshal* __fastcall GetJSONMarshaler();
	Data::Dbxjsonreflect::TJSONUnMarshal* __fastcall GetJSONUnMarshaler();
	void __fastcall FreeOnExecute(System::TObject* Value);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface TDSRestResponseStreamProc  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::Classes::TStream* AStream, const System::UnicodeString AResponseCharSet, bool &AOwnsStream) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCacheCommand : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FParameterPath;
	TDSCustomRestConnection* FConnection;
	void __fastcall Execute(const System::UnicodeString ARequestType, const System::UnicodeString ACachePath, _di_TDSRestResponseStreamProc AResponseStreamProc, const System::UnicodeString ARequestFilter = System::UnicodeString());
	System::UnicodeString __fastcall GetCommandPath();
	
public:
	__fastcall TDSRestCacheCommand(TDSCustomRestConnection* AConnection);
	__fastcall virtual ~TDSRestCacheCommand();
	void __fastcall GetParameter(_di_TDSRestResponseStreamProc AResponseStreamProc, const System::UnicodeString ARequestFilter = System::UnicodeString())/* overload */;
	void __fastcall GetParameter(/* out */ System::Json::TJSONValue* &AJSONValue, const System::UnicodeString ARequestFilter = System::UnicodeString())/* overload */;
	void __fastcall GetParameter(/* out */ System::Classes::TStream* &AStream, bool AOwnsObject, const System::UnicodeString ARequestFilter = System::UnicodeString())/* overload */;
	void __fastcall GetCommand(_di_TDSRestResponseStreamProc AResponseStreamProc)/* overload */;
	System::Json::TJSONObject* __fastcall GetCommand(bool AOwnsObject = true)/* overload */;
	void __fastcall DeleteCommand();
	__property TDSCustomRestConnection* Connection = {read=FConnection};
	__property System::UnicodeString ParameterPath = {read=FParameterPath, write=FParameterPath};
	__property System::UnicodeString CommandPath = {read=GetCommandPath};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

__interface  INTERFACE_UUID("{16B2E1F2-436B-45D8-A17D-5B1617F65BD6}") IDSRestCachedCommand  : public System::IInterface 
{
	virtual System::Json::TJSONObject* __fastcall GetCommand(TDSRestConnection* AConnection, bool AOwnsObject = true) = 0 ;
	virtual void __fastcall DeleteCommand(TDSRestConnection* AConnection) = 0 ;
};

__interface  INTERFACE_UUID("{CCCDC036-04F0-4CF6-A74F-D2759F1E635A}") IDSRestCachedItem  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetItemPath() = 0 ;
	__property System::UnicodeString ItemPath = {read=GetItemPath};
};

__interface  INTERFACE_UUID("{3C45664B-BAAB-42AA-8FD9-9D3AB0198455}") IDSRestCachedJSONObject  : public IDSRestCachedItem 
{
	virtual System::Json::TJSONObject* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface  INTERFACE_UUID("{38E0EFCC-A1B6-4E11-BD9D-F640B7822D44}") IDSRestCachedJSONArray  : public IDSRestCachedItem 
{
	virtual System::Json::TJSONArray* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface  INTERFACE_UUID("{12458118-91A1-4A67-87AB-947CB8970D7B}") IDSRestCachedJSONValue  : public IDSRestCachedItem 
{
	virtual System::Json::TJSONValue* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface  INTERFACE_UUID("{567DBA1E-2CAE-4C15-824B-0B678FBBD5B1}") IDSRestCachedDBXReader  : public IDSRestCachedItem 
{
	virtual Data::Dbxcommon::TDBXReader* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface  INTERFACE_UUID("{54D0BA3F-9159-4DD5-802A-0097BA842D91}") IDSRestCachedDataSet  : public IDSRestCachedItem 
{
	virtual Data::Db::TDataSet* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface  INTERFACE_UUID("{FD14E67B-D225-4FED-8B45-451B6627962C}") IDSRestCachedParams  : public IDSRestCachedItem 
{
	virtual Data::Db::TParams* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface  INTERFACE_UUID("{0E09C8A7-11A5-4CD5-B175-A35C9B0BEDF5}") IDSRestCachedStream  : public IDSRestCachedItem 
{
	virtual System::Classes::TStream* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> __interface IDSRestCachedObject__1  : public System::IInterface 
{
	virtual T __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString()) = 0 ;
};

__interface TGetJSONValueCallback  : public System::IInterface 
{
	virtual bool __fastcall Invoke(System::Json::TJSONValue* AValue) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedItem : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
private:
	System::UnicodeString FItemPath;
	System::Generics::Collections::TList__1<System::TObject*>* FOwnedObjects;
	
protected:
	System::UnicodeString __fastcall GetItemPath();
	System::Json::TJSONValue* __fastcall GetJSONValue(TDSRestConnection* AConnection, bool AOwnsObject, const System::UnicodeString ARequestFilter);
	System::Json::TJSONValue* __fastcall GetJSONValueCallback(TDSRestConnection* AConnection, _di_TGetJSONValueCallback ACallBack, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
	template<typename T> T __fastcall UnmarshalValue(TDSRestConnection* AConnection, bool AOwnsObject, const System::UnicodeString ARequestFilter);
	__property System::Generics::Collections::TList__1<System::TObject*>* OwnedObjects = {read=FOwnedObjects};
	
public:
	__fastcall TDSRestCachedItem(const System::UnicodeString AItemPath);
	__fastcall virtual ~TDSRestCachedItem();
	void __fastcall DeleteCommand(TDSRestConnection* AConnection);
	System::Json::TJSONObject* __fastcall GetCommand(TDSRestConnection* AConnection, bool AOwnsObject = true);
	__property System::UnicodeString ItemPath = {read=GetItemPath};
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedItem;	// IDSRestCachedItem 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {CCCDC036-04F0-4CF6-A74F-D2759F1E635A}
	operator _di_IDSRestCachedItem()
	{
		_di_IDSRestCachedItem intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedItem*(void) { return (IDSRestCachedItem*)&__IDSRestCachedItem; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedJSONObject : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	System::Json::TJSONObject* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedJSONObject(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedJSONObject() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedJSONObject;	// IDSRestCachedJSONObject 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3C45664B-BAAB-42AA-8FD9-9D3AB0198455}
	operator _di_IDSRestCachedJSONObject()
	{
		_di_IDSRestCachedJSONObject intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedJSONObject*(void) { return (IDSRestCachedJSONObject*)&__IDSRestCachedJSONObject; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedJSONArray : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	System::Json::TJSONArray* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedJSONArray(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedJSONArray() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedJSONArray;	// IDSRestCachedJSONArray 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {38E0EFCC-A1B6-4E11-BD9D-F640B7822D44}
	operator _di_IDSRestCachedJSONArray()
	{
		_di_IDSRestCachedJSONArray intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedJSONArray*(void) { return (IDSRestCachedJSONArray*)&__IDSRestCachedJSONArray; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedJSONValue : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	System::Json::TJSONValue* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedJSONValue(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedJSONValue() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedJSONValue;	// IDSRestCachedJSONValue 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {12458118-91A1-4A67-87AB-947CB8970D7B}
	operator _di_IDSRestCachedJSONValue()
	{
		_di_IDSRestCachedJSONValue intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedJSONValue*(void) { return (IDSRestCachedJSONValue*)&__IDSRestCachedJSONValue; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedStream : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	System::Classes::TStream* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedStream(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedStream() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedStream;	// IDSRestCachedStream 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {0E09C8A7-11A5-4CD5-B175-A35C9B0BEDF5}
	operator _di_IDSRestCachedStream()
	{
		_di_IDSRestCachedStream intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedStream*(void) { return (IDSRestCachedStream*)&__IDSRestCachedStream; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedDataSet : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	Data::Db::TDataSet* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedDataSet(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedDataSet() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedDataSet;	// IDSRestCachedDataSet 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {54D0BA3F-9159-4DD5-802A-0097BA842D91}
	operator _di_IDSRestCachedDataSet()
	{
		_di_IDSRestCachedDataSet intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedDataSet*(void) { return (IDSRestCachedDataSet*)&__IDSRestCachedDataSet; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedParams : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	Data::Db::TParams* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedParams(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedParams() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedParams;	// IDSRestCachedParams 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {FD14E67B-D225-4FED-8B45-451B6627962C}
	operator _di_IDSRestCachedParams()
	{
		_di_IDSRestCachedParams intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedParams*(void) { return (IDSRestCachedParams*)&__IDSRestCachedParams; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCachedDBXReader : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	Data::Dbxcommon::TDBXReader* __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedDBXReader(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedDBXReader() { }
	
private:
	void *__IDSRestCachedCommand;	// IDSRestCachedCommand 
	void *__IDSRestCachedDBXReader;	// IDSRestCachedDBXReader 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {16B2E1F2-436B-45D8-A17D-5B1617F65BD6}
	operator _di_IDSRestCachedCommand()
	{
		_di_IDSRestCachedCommand intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedCommand*(void) { return (IDSRestCachedCommand*)&__IDSRestCachedCommand; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {567DBA1E-2CAE-4C15-824B-0B678FBBD5B1}
	operator _di_IDSRestCachedDBXReader()
	{
		_di_IDSRestCachedDBXReader intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IDSRestCachedDBXReader*(void) { return (IDSRestCachedDBXReader*)&__IDSRestCachedDBXReader; }
	#endif
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TDSRestCachedObject__1 : public TDSRestCachedItem
{
	typedef TDSRestCachedItem inherited;
	
public:
	T __fastcall GetValue(TDSRestConnection* AConnection, bool AOwnsObject = true, const System::UnicodeString ARequestFilter = System::UnicodeString());
public:
	/* TDSRestCachedItem.Create */ inline __fastcall TDSRestCachedObject__1(const System::UnicodeString AItemPath) : TDSRestCachedItem(AItemPath) { }
	/* TDSRestCachedItem.Destroy */ inline __fastcall virtual ~TDSRestCachedObject__1() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TDSRESTChannelEventType : unsigned char { rChannelCreate, rChannelClose, rChannelClosedByServer, rCallbackAdded, rCallbackRemoved };

struct DECLSPEC_DRECORD TDSRESTChannelEventItem
{
public:
	TDSRESTChannelEventType EventType;
	TDSRestClientChannel* ClientChannel;
	System::UnicodeString ClientChannelId;
	System::UnicodeString ClientChannelName;
	System::UnicodeString CallbackId;
	TDSRestClientCallback* Callback;
};


typedef void __fastcall (__closure *TDSRESRChannelEvent)(const TDSRESTChannelEventItem &EventItem);

class PASCALIMPLEMENTATION TDSRestClientChannel : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDSCustomRestConnection* FConnection;
	TDSRestCallbackLoop* FCallbackLoop;
	System::Classes::TNotifyEvent FOnDisconnect;
	TDSRESRChannelEvent FChannelEvent;
	bool FStopped;
	System::Generics::Collections::TList__1<TDSRestClientCallback*>* FCallbacks;
	void __fastcall EnumerateCallbacks(System::DelphiInterface<System::Sysutils::TFunc__2<TDSRestClientCallback*,bool> > AMethod)/* overload */;
	void __fastcall EnumerateCallbacks(System::DelphiInterface<System::Sysutils::TProc__1<TDSRestClientCallback*> > AMethod)/* overload */;
	void __fastcall NotifyEvent(TDSRESTChannelEventType EventType, TDSRestClientCallback* Callback);
	
private:
	System::UnicodeString FChannelId;
	System::UnicodeString FServerChannelName;
	bool __fastcall GetConnected();
	System::UnicodeString __fastcall GetSessionId();
	
public:
	__fastcall TDSRestClientChannel(const System::UnicodeString AChannelId, const System::UnicodeString AServerChannelName, TDSCustomRestConnection* AConnection);
	__fastcall virtual ~TDSRestClientChannel();
	void __fastcall RegisterCallback(TDSRestClientCallback* AClientCallback);
	void __fastcall Connect(TDSRestClientCallback* AFirstCallback);
	void __fastcall UnregisterCallback(TDSRestClientCallback* AClientCallback);
	bool __fastcall Broadcast(System::Json::TJSONValue* AMessage, System::UnicodeString AChannelName = System::UnicodeString());
	void __fastcall Disconnect();
	bool __fastcall Notify(const System::UnicodeString AClientId, const System::UnicodeString ACallbackId, System::Json::TJSONValue* AMessage);
	__property bool Connected = {read=GetConnected, nodefault};
	__property System::Classes::TNotifyEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property System::UnicodeString ServerChannelName = {read=FServerChannelName};
	__property System::UnicodeString ChannelId = {read=FChannelId};
	__property System::UnicodeString SessionID = {read=GetSessionId};
	__property System::Generics::Collections::TList__1<TDSRestClientCallback*>* Callbacks = {read=FCallbacks};
	__property TDSRESRChannelEvent OnChannelStateChange = {read=FChannelEvent, write=FChannelEvent};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestCallbackLoop : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDSRestClientChannel* FClientChannel;
	TDSCustomRestConnection* FConnection;
	System::Classes::TThread* FThread;
	bool FStopping;
	void __fastcall OnThreadTerminateDirect();
	bool __fastcall GetStopped();
	System::UnicodeString __fastcall GetSessionId();
	
public:
	__fastcall TDSRestCallbackLoop(TDSRestClientChannel* AClientChannel, TDSCustomRestConnection* AConnection);
	__fastcall virtual ~TDSRestCallbackLoop();
	void __fastcall Callback(System::Json::TJSONValue* responseValue, bool &AStatus, bool &AStop);
	void __fastcall Start(TDSRestClientCallback* AFirstCallback);
	void __fastcall Stop();
	__property bool Stopped = {read=GetStopped, nodefault};
	__property TDSRestClientChannel* ClientChannel = {read=FClientChannel};
	__property System::UnicodeString SessionID = {read=GetSessionId};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::DelphiInterface<System::Sysutils::TFunc__3<System::Json::TJSONValue*,System::UnicodeString,bool> > TDSRestClientCallbackFunction;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestClientCallback : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FCallbackId;
	System::Classes::TStrings* FChannelNames;
	System::DelphiInterface<System::Sysutils::TFunc__3<System::Json::TJSONValue*,System::UnicodeString,bool> > FClientCallbackFunction;
	TDSRestClientChannel* FClientChannel;
	
public:
	__fastcall TDSRestClientCallback(TDSRestClientChannel* AClientChannel, const System::UnicodeString ACallbackId, System::DelphiInterface<System::Sysutils::TFunc__3<System::Json::TJSONValue*,System::UnicodeString,bool> > AClientCallbackFunction, System::Classes::TStrings* AChannelNames);
	__fastcall virtual ~TDSRestClientCallback();
	__property System::UnicodeString CallbackId = {read=FCallbackId};
	__property System::DelphiInterface<System::Sysutils::TFunc__3<System::Json::TJSONValue*,System::UnicodeString,bool> > ClientCallbackFunction = {read=FClientCallbackFunction};
	__property System::Classes::TStrings* ChannelNames = {read=FChannelNames};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef void __fastcall (__closure *TTestConnectionMethod)(void);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall TDSRestException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall TDSRestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDSRestException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDSRestException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSRestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSRestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDSRestException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDSRestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSRestException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSRestException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSRestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSRestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDSRestException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRestProtocolException : public TDSRestException
{
	typedef TDSRestException inherited;
	
private:
	int FStatus;
	System::UnicodeString FResponseText;
	
public:
	__fastcall TDSRestProtocolException(int AStatus, const System::UnicodeString AMessage, const System::UnicodeString AResponseText);
	__property int Status = {read=FStatus, nodefault};
	__property System::UnicodeString ResponseText = {read=FResponseText};
public:
	/* Exception.CreateFmt */ inline __fastcall TDSRestProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : TDSRestException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDSRestProtocolException(NativeUInt Ident)/* overload */ : TDSRestException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDSRestProtocolException(System::PResStringRec ResStringRec)/* overload */ : TDSRestException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSRestProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : TDSRestException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSRestProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : TDSRestException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDSRestProtocolException(const System::UnicodeString Msg, int AHelpContext) : TDSRestException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDSRestProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : TDSRestException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSRestProtocolException(NativeUInt Ident, int AHelpContext)/* overload */ : TDSRestException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSRestProtocolException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : TDSRestException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSRestProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : TDSRestException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSRestProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : TDSRestException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDSRestProtocolException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE bool __fastcall (*DSRestLoginDialogProc)(System::TObject* ASender, TDSRestLoginProperties* &LoginProperties, TTestConnectionMethod ATestConnectionMethod);
}	/* namespace Dsclientrest */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCLIENTREST)
using namespace Datasnap::Dsclientrest;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsclientrestHPP
