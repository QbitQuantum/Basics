// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSHTTP.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DshttpHPP
#define Datasnap_DshttpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXTransport.hpp>
#include <Data.DbxDatasnap.hpp>
#include <Datasnap.DSHTTPCommon.hpp>
#include <Datasnap.DSAuth.hpp>
#include <Datasnap.DSTransport.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSServer.hpp>
#include <Datasnap.DSService.hpp>
#include <Datasnap.DSSession.hpp>
#include <System.Generics.Collections.hpp>
#include <Web.WebFileDispatcher.hpp>
#include <IPPeerAPI.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dshttp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSHTTPCacheContextService;
class DELPHICLASS TDSRESTServer;
class DELPHICLASS TDSHTTPServer;
class DELPHICLASS TDSDefaultResponseHandler;
class DELPHICLASS TCustomDSRESTServerTransport;
class DELPHICLASS TCustomDSHTTPServerTransport;
class DELPHICLASS TDSRESTServerTransport;
class DELPHICLASS TDSHTTPServerTransport;
class DELPHICLASS TDSCacheResponseHandler;
class DELPHICLASS TDSResponseHandlerFactory;
class DELPHICLASS TDSHTTPService;
class DELPHICLASS TDSCustomCertFiles;
class DELPHICLASS TDSCertFiles;
class DELPHICLASS TDSHTTPServiceComponent;
class DELPHICLASS TDSCustomHTTPServiceFileDispatcher;
class DELPHICLASS TDSHTTPServiceFileDispatcher;
class DELPHICLASS TDSHTTPContextIndy;
class DELPHICLASS TDSHTTPRequestIndy;
class DELPHICLASS TDSHTTPResponseIndy;
class DELPHICLASS TDSHTTPApplication;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPCacheContextService : public Datasnap::Dsservice::TDSRequestFilterManager
{
	typedef Datasnap::Dsservice::TDSRequestFilterManager inherited;
	
private:
	Datasnap::Dssession::TDSSession* FSession;
	bool FLocalConnection;
	bool __fastcall ParseRequst(System::UnicodeString Request, /* out */ int &CacheId, /* out */ int &CommandIndex, /* out */ int &ParameterIndex);
	void __fastcall InvalidRequest(Datasnap::Dshttpcommon::TDSHTTPResponse* Response, System::UnicodeString Request);
	void __fastcall GetCacheContents(/* out */ System::Json::TJSONValue* &Value);
	void __fastcall GetCacheItemContents(const int CacheId, /* out */ System::Json::TJSONValue* &Value);
	void __fastcall GetCommandContents(const int CacheId, const int CommandIndex, /* out */ System::Json::TJSONValue* &Value);
	void __fastcall GetParameterValue(Datasnap::Dshttpcommon::TDSHTTPRequest* const RequestInfo, const int CacheId, const int CommandIndex, const int ParameterIndex, /* out */ System::Json::TJSONValue* &Response, /* out */ System::Classes::TStream* &ResponseStream, /* out */ bool &IsError);
	int __fastcall GetOriginalParamIndex(Data::Dbxcommon::TDBXCommand* const Command, Data::Dbxcommon::TDBXParameter* const Parameter);
	bool __fastcall StreamsAsJSON(Datasnap::Dshttpcommon::TDSHTTPRequest* const RequestInfo);
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ByteContent(System::Json::TJSONValue* JsonValue);
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ByteContent(System::Json::TJSONValue* JsonValue);
#endif /* _WIN64 */
	
public:
	__fastcall virtual TDSHTTPCacheContextService(Datasnap::Dssession::TDSSession* Session, bool LocalConnection);
	void __fastcall ProcessGETRequest(Datasnap::Dshttpcommon::TDSHTTPRequest* const RequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* Response, System::UnicodeString Request);
	void __fastcall ProcessDELETERequest(Datasnap::Dshttpcommon::TDSHTTPRequest* const RequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* Response, System::UnicodeString Request);
public:
	/* TDSRequestFilterManager.Destroy */ inline __fastcall virtual ~TDSHTTPCacheContextService() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSRESTServer : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	int FSessionTimeout;
	System::UnicodeString FDSServerName;
	Datasnap::Dsauth::TDSCustomAuthenticationManager* FDSHTTPAuthenticationManager;
	Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* FProtocolHandlerFactory;
	System::UnicodeString FIPImplementationID;
	System::UnicodeString FRESTContext;
	System::UnicodeString FDSContext;
	Datasnap::Dssession::TDSSessionLifetime FSessionLifetime;
	Datasnap::Dshttpcommon::TDSHTTPServiceTraceEvent FTrace;
	Datasnap::Dshttpcommon::TDSServiceResponseHandler::TParseRequestEvent FParseRequestEvent;
	Datasnap::Dshttpcommon::TDSServiceResponseHandler::TParsingRequestEvent FParsingRequestEvent;
	Datasnap::Dshttpcommon::TDSRESTResultEvent FResultEvent;
	Datasnap::Dscommonserver::TDSCustomServer* FDSServer;
	System::UnicodeString __fastcall GetRestContext();
	System::UnicodeString __fastcall GetDsContext();
	void __fastcall SetRestContext(const System::UnicodeString ctx);
	void __fastcall SetDsContext(const System::UnicodeString ctx);
	bool __fastcall Consume(const System::UnicodeString Prefix, const System::UnicodeString Context, /* out */ System::UnicodeString &Unused);
#ifndef _WIN64
	System::DynamicArray<System::Byte> __fastcall ByteContent(System::Classes::TStream* DataStream)/* overload */;
	System::DynamicArray<System::Byte> __fastcall ByteContent(System::Json::TJSONValue* JsonValue)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::Byte> __fastcall ByteContent(System::Classes::TStream* DataStream)/* overload */;
	System::TArray__1<System::Byte> __fastcall ByteContent(System::Json::TJSONValue* JsonValue)/* overload */;
#endif /* _WIN64 */
	__property System::UnicodeString RESTContext = {read=GetRestContext, write=SetRestContext};
	__property System::UnicodeString DSContext = {read=GetDsContext, write=SetDsContext};
	virtual void __fastcall SetAuthenticationManager(Datasnap::Dsauth::TDSCustomAuthenticationManager* AuthenticationManager);
	bool __fastcall IsClosingSession(const System::UnicodeString Request);
	bool __fastcall IsOpeningClientChannel(const System::UnicodeString Request);
	bool __fastcall IsClosingClientChannel(const System::UnicodeString Request);
	virtual void __fastcall UpdateSessionTunnelHook(const System::UnicodeString Request, Datasnap::Dssession::TDSSession* Session, Datasnap::Dshttpcommon::TDSHTTPRequest* RequestInfo);
	void __fastcall CloseRESTSession(Datasnap::Dssession::TDSSession* Session, Datasnap::Dshttpcommon::TDSHTTPResponse* ResponseInfo);
	void __fastcall CheckClientChannelMethod(const System::UnicodeString Request);
	virtual Datasnap::Dsservice::TDSRESTService* __fastcall CreateRESTService(const System::UnicodeString AuthUserName, const System::UnicodeString AuthPassword);
	
protected:
	virtual void __fastcall SetDSServerName(System::UnicodeString AName);
	virtual bool __fastcall ConsumeOtherContext(const System::UnicodeString AContext, /* out */ System::UnicodeString &APrefix, /* out */ System::UnicodeString &AUnused);
	virtual void __fastcall DoDSOtherCommand(Datasnap::Dshttpcommon::TDSHTTPContext* const AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* const ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* const AResponseInfo, const System::UnicodeString APrefix, const System::UnicodeString ARequest, bool ALocalConnection);
	void __fastcall DoDSRESTCommand(Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo, System::UnicodeString Request);
	void __fastcall DoCommand(Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo);
	virtual void __fastcall DoCommandOtherContext(Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo, const System::UnicodeString ARequest);
	
protected:
	virtual System::UnicodeString __fastcall Decode(System::UnicodeString Data) = 0 ;
	
public:
	__fastcall TDSRESTServer()/* overload */;
	__fastcall TDSRESTServer(const System::UnicodeString AIPImplementationID)/* overload */;
	__fastcall TDSRESTServer(Datasnap::Dscommonserver::TDSCustomServer* const ADSServer)/* overload */;
	__fastcall virtual TDSRESTServer(Datasnap::Dscommonserver::TDSCustomServer* const ADSServer, const System::UnicodeString AIPImplementationID)/* overload */;
	__fastcall virtual ~TDSRESTServer();
	virtual void __fastcall CreateProtocolHandlerFactory(Datasnap::Dscommonserver::TDSServerTransport* ATransport);
	virtual void __fastcall ClearProtocolHandlerFactory();
	__property Datasnap::Dscommonserver::TDSCustomServer* DSServer = {read=FDSServer, write=FDSServer};
	__property System::UnicodeString DSServerName = {read=FDSServerName, write=SetDSServerName};
	__property Datasnap::Dsauth::TDSCustomAuthenticationManager* DSAuthenticationManager = {read=FDSHTTPAuthenticationManager, write=SetAuthenticationManager};
	__property int SessionTimeout = {read=FSessionTimeout, write=FSessionTimeout, nodefault};
	__property Datasnap::Dssession::TDSSessionLifetime SessionLifetime = {read=FSessionLifetime, write=FSessionLifetime, nodefault};
	__property System::UnicodeString IPImplementationID = {read=FIPImplementationID};
	__property Datasnap::Dshttpcommon::TDSRESTResultEvent ResultEvent = {read=FResultEvent, write=FResultEvent};
	__property Datasnap::Dshttpcommon::TDSServiceResponseHandler::TParsingRequestEvent OnParsingRequest = {read=FParsingRequestEvent, write=FParsingRequestEvent};
	__property Datasnap::Dshttpcommon::TDSServiceResponseHandler::TParseRequestEvent OnParseRequest = {read=FParseRequestEvent, write=FParseRequestEvent};
};


class PASCALIMPLEMENTATION TDSHTTPServer : public TDSRESTServer
{
	typedef TDSRESTServer inherited;
	
private:
	System::UnicodeString FDSHostname;
	int FDSPort;
	Data::Dbxtransport::TTransportFilterCollection* FFilters;
	bool FCredentialsPassThrough;
	System::UnicodeString FDSAuthUser;
	System::UnicodeString FDSAuthPassword;
	System::UnicodeString FCacheContext;
	Datasnap::Dssession::_di_TDSSessionEvent FSessionEvent;
	
private:
	Datasnap::Dssession::TDSTunnelService* FTunnelService;
	void __fastcall SetDSHostname(System::UnicodeString AHostname);
	void __fastcall SetDSPort(int APort);
	void __fastcall SetFilters(Data::Dbxtransport::TTransportFilterCollection* AFilterCollection);
	virtual void __fastcall SetAuthenticationManager(Datasnap::Dsauth::TDSCustomAuthenticationManager* AuthenticationManager);
	Datasnap::Dssession::TDSTunnelService* __fastcall GetTunnelService();
	void __fastcall CloseAllTunnelSessions();
	virtual Datasnap::Dsservice::TDSRESTService* __fastcall CreateRESTService(const System::UnicodeString AuthUserName, const System::UnicodeString AuthPassword);
	System::UnicodeString __fastcall GetCacheContext();
	void __fastcall SetCacheContext(const System::UnicodeString ctx);
	bool __fastcall GetClientChannelInfo(System::UnicodeString Request, /* out */ System::UnicodeString &ChannelName, /* out */ System::UnicodeString &ClientChannelId, /* out */ System::UnicodeString &ClientCallbackID, /* out */ System::UnicodeString &SecurityToken);
	virtual void __fastcall UpdateSessionTunnelHook(const System::UnicodeString Request, Datasnap::Dssession::TDSSession* Session, Datasnap::Dshttpcommon::TDSHTTPRequest* RequestInfo);
	void __fastcall CloseSessionTunnels(Datasnap::Dssession::TDSSession* Session);
	
protected:
	virtual void __fastcall SetDSServerName(System::UnicodeString AName);
	void __fastcall DoTunnelCommand(Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo);
	virtual bool __fastcall ConsumeOtherContext(const System::UnicodeString AContext, /* out */ System::UnicodeString &APrefix, /* out */ System::UnicodeString &AUnused);
	virtual void __fastcall DoDSOtherCommand(Datasnap::Dshttpcommon::TDSHTTPContext* const AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* const ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* const AResponseInfo, const System::UnicodeString APrefix, const System::UnicodeString ARequest, bool ALocalConnection);
	void __fastcall DoDSCacheCommand(Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo, System::UnicodeString Request, bool LocalConnection);
	
public:
	__fastcall virtual TDSHTTPServer(Datasnap::Dscommonserver::TDSCustomServer* const ADSServer, const System::UnicodeString AIPImplementationID)/* overload */;
	__fastcall virtual ~TDSHTTPServer();
	virtual void __fastcall CreateProtocolHandlerFactory(Datasnap::Dscommonserver::TDSServerTransport* ATransport);
	virtual void __fastcall ClearProtocolHandlerFactory();
	__property System::UnicodeString CacheContext = {read=GetCacheContext, write=SetCacheContext};
	__property Datasnap::Dssession::TDSTunnelService* TunnelService = {read=GetTunnelService};
	__property System::UnicodeString DSHostname = {read=FDSHostname, write=SetDSHostname};
	__property int DSPort = {read=FDSPort, write=SetDSPort, nodefault};
	__property Data::Dbxtransport::TTransportFilterCollection* Filters = {read=FFilters, write=SetFilters};
	__property bool CredentialsPassThrough = {read=FCredentialsPassThrough, write=FCredentialsPassThrough, nodefault};
	__property System::UnicodeString DSAuthUser = {read=FDSAuthUser, write=FDSAuthUser};
	__property System::UnicodeString DSAuthPassword = {read=FDSAuthPassword, write=FDSAuthPassword};
public:
	/* TDSRESTServer.Create */ inline __fastcall TDSHTTPServer()/* overload */ : TDSRESTServer() { }
	/* TDSRESTServer.Create */ inline __fastcall TDSHTTPServer(const System::UnicodeString AIPImplementationID)/* overload */ : TDSRESTServer(AIPImplementationID) { }
	/* TDSRESTServer.Create */ inline __fastcall TDSHTTPServer(Datasnap::Dscommonserver::TDSCustomServer* const ADSServer)/* overload */ : TDSRESTServer(ADSServer) { }
	
};


class PASCALIMPLEMENTATION TDSDefaultResponseHandler : public Datasnap::Dshttpcommon::TDSJsonResponseHandler
{
	typedef Datasnap::Dshttpcommon::TDSJsonResponseHandler inherited;
	
private:
	bool FStoreHandler;
	
protected:
	virtual bool __fastcall HandleParameter(Data::Dbxcommon::TDBXCommand* const Command, Data::Dbxcommon::TDBXParameter* const Parameter, /* out */ System::Json::TJSONValue* &Response, System::Classes::TStream* &ResponseStream);
	virtual void __fastcall PopulateContent(Datasnap::Dshttpcommon::TDSHTTPResponse* ResponseInfo, System::Json::TJSONValue* Response, System::Classes::TStream* ResponseStream);
	
public:
	__fastcall TDSDefaultResponseHandler(bool AllowBinaryStream, Datasnap::Dsservice::TDSService* DSService, Datasnap::Dshttpcommon::TDSHTTPCommandType CommandType, bool ServiceInstanceOwner);
	__fastcall virtual ~TDSDefaultResponseHandler();
	virtual void __fastcall Close();
};


class PASCALIMPLEMENTATION TCustomDSRESTServerTransport : public Datasnap::Dscommonserver::TDSServerTransport
{
	typedef Datasnap::Dscommonserver::TDSServerTransport inherited;
	
	
public:
	typedef void __fastcall (__closure *TParsingRequestEvent)(System::TObject* Sender, const System::UnicodeString ARequest, System::Classes::TStrings* const ASegments, System::UnicodeString &ADSMethodName, System::Classes::TStrings* const AParamValues, bool &AHandled);
	
	typedef void __fastcall (__closure *TParseRequestEvent)(System::TObject* Sender, const System::UnicodeString ARequest, System::Classes::TStrings* const ASegments, System::UnicodeString &ADSMethodName, System::Classes::TStrings* const AParamValues);
	
	
protected:
	TDSRESTServer* FRESTServer;
	
private:
	Datasnap::Dssession::TDSSessionLifetime FSessionLifetime;
	int FSessionTimeout;
	System::UnicodeString FDSContext;
	System::UnicodeString FDSRestContext;
	Datasnap::Dsauth::TDSCustomAuthenticationManager* FAuthenticationManager;
	Datasnap::Dshttpcommon::TDSHTTPServiceTraceEvent FTrace;
	Datasnap::Dshttpcommon::TDSRESTResultEvent FResultEvent;
	TParsingRequestEvent FParsingRequestEvent;
	TParseRequestEvent FParseRequestEvent;
	
private:
	TDSRESTServer* __fastcall GetRESTServer();
	void __fastcall UpdateDSServerName();
	bool __fastcall IsDSContextStored();
	bool __fastcall IsRESTContextStored();
	void __fastcall ReadTrace(System::Classes::TReader* Reader);
	void __fastcall ReadFormatResult(System::Classes::TReader* Reader);
	void __fastcall ReadProperty(System::Classes::TReader* Reader, const System::UnicodeString ANewProperty);
	
protected:
	virtual void __fastcall Loaded();
	void __fastcall RequiresServer();
	virtual TDSRESTServer* __fastcall CreateRESTServer() = 0 ;
	virtual void __fastcall InitializeRESTServer();
	void __fastcall SetRESTContext(const System::UnicodeString Ctx);
	void __fastcall SetDSContext(const System::UnicodeString Ctx);
	void __fastcall SetTraceEvent(Datasnap::Dshttpcommon::TDSHTTPServiceTraceEvent Event);
	void __fastcall SetParseRequestEvent(TParseRequestEvent Event);
	TParseRequestEvent __fastcall GetParseRequestEvent();
	void __fastcall SetParsingRequestEvent(TParsingRequestEvent Event);
	TParsingRequestEvent __fastcall GetParsingRequestEvent();
	virtual void __fastcall SetServer(Datasnap::Dscommonserver::TDSCustomServer* const AServer);
	void __fastcall SetAuthenticationManager(Datasnap::Dsauth::TDSCustomAuthenticationManager* const AuthenticationManager);
	void __fastcall SetResultEvent(const Datasnap::Dshttpcommon::TDSRESTResultEvent RestEvent);
	virtual void __fastcall SetIPImplementationID(const System::UnicodeString AIPImplementationID);
	System::UnicodeString __fastcall GetRESTContext();
	System::UnicodeString __fastcall GetDSContext();
	Datasnap::Dshttpcommon::TDSHTTPServiceTraceEvent __fastcall GetTraceEvent();
	Datasnap::Dsauth::TDSCustomAuthenticationManager* __fastcall GetAuthenticationManager();
	Datasnap::Dshttpcommon::TDSRESTResultEvent __fastcall GetResultEvent();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual int __fastcall GetSessionTimeout();
	virtual void __fastcall SetSessionTimeout(const int Milliseconds);
	virtual System::UnicodeString __fastcall GetIPImplementationID();
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TCustomDSRESTServerTransport(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TCustomDSRESTServerTransport();
	__property TDSRESTServer* RESTServer = {read=GetRESTServer};
	__property System::UnicodeString DSContext = {read=GetDSContext, write=SetDSContext, stored=IsDSContextStored};
	__property System::UnicodeString RESTContext = {read=GetRESTContext, write=SetRESTContext, stored=IsRESTContextStored};
	__property Datasnap::Dsauth::TDSCustomAuthenticationManager* AuthenticationManager = {read=GetAuthenticationManager, write=SetAuthenticationManager};
	__property int SessionTimeout = {read=GetSessionTimeout, write=SetSessionTimeout, default=1200000};
	__property Datasnap::Dssession::TDSSessionLifetime SessionLifetime = {read=FSessionLifetime, write=FSessionLifetime, default=0};
	__property Datasnap::Dshttpcommon::TDSHTTPServiceTraceEvent OnHTTPTrace = {read=GetTraceEvent, write=SetTraceEvent};
	__property Datasnap::Dshttpcommon::TDSHTTPServiceTraceEvent Trace = {read=GetTraceEvent, write=SetTraceEvent};
	__property Datasnap::Dshttpcommon::TDSRESTResultEvent OnFormatResult = {read=GetResultEvent, write=SetResultEvent};
	__property Datasnap::Dshttpcommon::TDSRESTResultEvent FormatResult = {read=GetResultEvent, write=SetResultEvent};
	__property TParseRequestEvent OnParseRequest = {read=GetParseRequestEvent, write=SetParseRequestEvent};
	__property TParsingRequestEvent OnParsingRequest = {read=GetParsingRequestEvent, write=SetParsingRequestEvent};
};


class PASCALIMPLEMENTATION TCustomDSHTTPServerTransport : public TCustomDSRESTServerTransport
{
	typedef TCustomDSRESTServerTransport inherited;
	
protected:
	TDSHTTPServer* FHttpServer;
	
private:
	bool FCredentialsPassthrough;
	System::UnicodeString FDSAuthPassword;
	System::UnicodeString FDSAuthUser;
	int FDSPort;
	System::UnicodeString FDSHostName;
	System::UnicodeString FDSCacheContext;
	bool __fastcall IsCacheContextStored();
	
private:
	TDSHTTPServer* __fastcall GetHttpServer();
	bool __fastcall IsDSHostnameStored();
	void __fastcall SetCacheContext(const System::UnicodeString Ctx);
	System::UnicodeString __fastcall GetCacheContext();
	
protected:
	virtual TDSHTTPServer* __fastcall CreateHttpServer() = 0 ;
	virtual TDSRESTServer* __fastcall CreateRESTServer();
	virtual void __fastcall InitializeRESTServer();
	virtual void __fastcall InitializeHttpServer();
	void __fastcall SetDSHostname(System::UnicodeString Host);
	void __fastcall SetDSPort(int Port);
	System::UnicodeString __fastcall GetDSHostname();
	int __fastcall GetDSPort();
	virtual void __fastcall SetFilters(Data::Dbxtransport::TTransportFilterCollection* const Value);
	void __fastcall ServerCloseAllTunnelSessions();
	virtual void __fastcall SetCredentialsPassThrough(const bool AFlag);
	virtual void __fastcall SetDSAuthUser(const System::UnicodeString UserName);
	virtual void __fastcall SetDSAuthPassword(const System::UnicodeString UserPassword);
	bool __fastcall GetCredentialsPassThrough();
	virtual System::UnicodeString __fastcall GetDSAuthUser();
	virtual System::UnicodeString __fastcall GetDSAuthPassword();
	
public:
	__fastcall virtual TCustomDSHTTPServerTransport(System::Classes::TComponent* AOwner);
	__property TDSHTTPServer* HttpServer = {read=GetHttpServer};
	__property System::UnicodeString CacheContext = {read=GetCacheContext, write=SetCacheContext, stored=IsCacheContextStored};
	__property System::UnicodeString DSHostname = {read=GetDSHostname, write=SetDSHostname, stored=IsDSHostnameStored};
	__property int DSPort = {read=GetDSPort, write=SetDSPort, default=211};
	__property bool CredentialsPassThrough = {read=GetCredentialsPassThrough, write=SetCredentialsPassThrough, default=0};
	__property System::UnicodeString DSAuthUser = {read=GetDSAuthUser, write=SetDSAuthUser};
	__property System::UnicodeString DSAuthPassword = {read=GetDSAuthPassword, write=SetDSAuthPassword};
public:
	/* TCustomDSRESTServerTransport.Destroy */ inline __fastcall virtual ~TCustomDSHTTPServerTransport() { }
	
};


class PASCALIMPLEMENTATION TDSRESTServerTransport : public TCustomDSRESTServerTransport
{
	typedef TCustomDSRESTServerTransport inherited;
	
__published:
	__property DSContext;
	__property RESTContext;
	__property Server;
	__property AuthenticationManager;
	__property SessionTimeout = {default=1200000};
	__property SessionLifetime = {default=0};
	__property OnParseRequest;
	__property OnParsingRequest;
	__property OnHTTPTrace;
	__property OnFormatResult;
public:
	/* TCustomDSRESTServerTransport.Create */ inline __fastcall virtual TDSRESTServerTransport(System::Classes::TComponent* AOwner) : TCustomDSRESTServerTransport(AOwner) { }
	/* TCustomDSRESTServerTransport.Destroy */ inline __fastcall virtual ~TDSRESTServerTransport() { }
	
};


class PASCALIMPLEMENTATION TDSHTTPServerTransport : public TCustomDSHTTPServerTransport
{
	typedef TCustomDSHTTPServerTransport inherited;
	
__published:
	__property DSContext;
	__property RESTContext;
	__property CacheContext;
	__property Server;
	__property DSHostname;
	__property DSPort = {default=211};
	__property Filters;
	__property AuthenticationManager;
	__property CredentialsPassThrough = {default=0};
	__property DSAuthUser = {default=0};
	__property DSAuthPassword = {default=0};
	__property SessionTimeout = {default=1200000};
	__property OnHTTPTrace;
	__property OnFormatResult;
public:
	/* TCustomDSHTTPServerTransport.Create */ inline __fastcall virtual TDSHTTPServerTransport(System::Classes::TComponent* AOwner) : TCustomDSHTTPServerTransport(AOwner) { }
	
public:
	/* TCustomDSRESTServerTransport.Destroy */ inline __fastcall virtual ~TDSHTTPServerTransport() { }
	
};


class PASCALIMPLEMENTATION TDSCacheResponseHandler : public Datasnap::Dshttpcommon::TDSJsonResponseHandler
{
	typedef Datasnap::Dshttpcommon::TDSJsonResponseHandler inherited;
	
protected:
	Datasnap::Dshttpcommon::TDSCacheResultCommandHandler* FResultHandler;
	int FCacheId;
	Datasnap::Dshttpcommon::TDSCacheResultCommandHandler* __fastcall GetCacheObject();
	virtual bool __fastcall HandleParameter(Data::Dbxcommon::TDBXCommand* const Command, Data::Dbxcommon::TDBXParameter* const Parameter, /* out */ System::Json::TJSONValue* &Response, System::Classes::TStream* &ResponseStream);
	virtual void __fastcall PopulateContent(Datasnap::Dshttpcommon::TDSHTTPResponse* ResponseInfo, System::Json::TJSONValue* Response, System::Classes::TStream* ResponseStream);
	Datasnap::Dshttpcommon::TDSCommandComplexParams* __fastcall GetComplexParams(Data::Dbxcommon::TDBXCommand* Command, /* out */ int &Index, bool AddIfNotFound = true);
	virtual void __fastcall ProcessResultObject(System::Json::TJSONObject* &ResultObj, Data::Dbxcommon::TDBXCommand* Command);
	
public:
	__fastcall TDSCacheResponseHandler(Datasnap::Dsservice::TDSService* DSService, Datasnap::Dshttpcommon::TDSHTTPCommandType CommandType, bool ServiceInstanceOwner);
	__fastcall virtual ~TDSCacheResponseHandler();
	virtual void __fastcall Close();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSResponseHandlerFactory : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod Datasnap::Dshttpcommon::TDSServiceResponseHandler* __fastcall CreateResponseHandler(Datasnap::Dsservice::TDSService* DSService, Datasnap::Dshttpcommon::TDSHTTPRequest* RequestInfo, Datasnap::Dshttpcommon::TDSHTTPCommandType CommandType = (Datasnap::Dshttpcommon::TDSHTTPCommandType)(0x0), TDSHTTPServer* HTTPServer = (TDSHTTPServer*)(0x0))/* overload */;
	__classmethod Datasnap::Dshttpcommon::TDSServiceResponseHandler* __fastcall CreateResponseHandler(Datasnap::Dsservice::TDSService* DSService, Datasnap::Dshttpcommon::TDSHTTPRequest* RequestInfo, Datasnap::Dshttpcommon::TDSHTTPCommandType CommandType, TDSRESTServer* HTTPServer)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDSResponseHandlerFactory() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSResponseHandlerFactory() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSHTTPService : public TCustomDSHTTPServerTransport
{
	typedef TCustomDSHTTPServerTransport inherited;
	
private:
	System::Generics::Collections::TList__1<System::Classes::TComponent*>* FComponentList;
	TDSCustomCertFiles* FCertFiles;
	int FDefaultPort;
	bool FActive;
	HIDESBASE void __fastcall RemoveComponent(TDSHTTPServiceComponent* const AComponent);
	void __fastcall AddComponent(TDSHTTPServiceComponent* const AComponent);
	void __fastcall SetCertFiles(TDSCustomCertFiles* const AValue);
	
protected:
	virtual TDSHTTPServer* __fastcall CreateHttpServer();
	virtual void __fastcall InitializeHttpServer();
	virtual void __fastcall HTTPOtherContext(Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo, const System::UnicodeString ARequest, bool &AHandled);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	__fastcall virtual TDSHTTPService(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSHTTPService();
	virtual System::Word __fastcall GetHttpPort();
	virtual System::UnicodeString __fastcall GetServerSoftware();
	virtual void __fastcall SetIPImplementationID(const System::UnicodeString Value);
	virtual bool __fastcall IsActive();
	virtual void __fastcall SetActive(bool Status);
	virtual void __fastcall SetHttpPort(const System::Word Port);
	virtual void __fastcall Start();
	virtual void __fastcall Stop();
	
__published:
	__property System::Word HttpPort = {read=GetHttpPort, write=SetHttpPort, default=80};
	__property bool Active = {read=IsActive, write=SetActive, default=0};
	__property System::UnicodeString ServerSoftware = {read=GetServerSoftware};
	__property TDSCustomCertFiles* CertFiles = {read=FCertFiles, write=SetCertFiles};
	__property IPImplementationID = {default=0};
	__property DSContext;
	__property RESTContext;
	__property CacheContext;
	__property OnHTTPTrace;
	__property OnFormatResult;
	__property Server;
	__property DSHostname;
	__property DSPort = {default=211};
	__property Filters;
	__property AuthenticationManager;
	__property CredentialsPassThrough = {default=0};
	__property DSAuthUser = {default=0};
	__property DSAuthPassword = {default=0};
	__property SessionTimeout = {default=1200000};
};


typedef void __fastcall (__closure *TGetPEMFilePasskey)(System::TObject* ASender, System::AnsiString &APasskey);

typedef void __fastcall (__closure *TGetPEMFileSBPasskey)(System::TObject* ASender, System::Sysutils::TStringBuilder* APasskey);

class PASCALIMPLEMENTATION TDSCustomCertFiles : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::UnicodeString FCertFile;
	System::UnicodeString FKeyFile;
	System::UnicodeString FRootCertFile;
	TGetPEMFilePasskey FGetPEMFilePasskey;
	TGetPEMFileSBPasskey FGetPEMFileSBPasskey;
	Ippeerapi::TIPSSLVersionPeer FSSLVersion;
	System::UnicodeString __fastcall GetCertFile();
	System::UnicodeString __fastcall GetKeyFile();
	System::UnicodeString __fastcall GetRootCertFile();
	void __fastcall SetCertFile(const System::UnicodeString Value);
	void __fastcall SetRootCertFile(const System::UnicodeString Value);
	void __fastcall SetKeyFile(const System::UnicodeString Value);
	void __fastcall SetOnGetPEMFilePasskey(const TGetPEMFilePasskey Value);
	TGetPEMFilePasskey __fastcall GetOnGetPEMFilePasskey();
	void __fastcall SetOnGetPEMFileSBPasskey(const TGetPEMFileSBPasskey Value);
	TGetPEMFileSBPasskey __fastcall GetOnGetPEMFileSBPasskey();
	Ippeerapi::TIPSSLVersionPeer __fastcall GetSSLVersion();
	void __fastcall SetSSLVersion(const Ippeerapi::TIPSSLVersionPeer Value);
	
__published:
	virtual void __fastcall SetServerProperties(System::TObject* AServer);
	
public:
	__fastcall virtual TDSCustomCertFiles(System::Classes::TComponent* AOwner);
	__property Ippeerapi::TIPSSLVersionPeer SSLVersion = {read=GetSSLVersion, write=SetSSLVersion, default=3};
	__property System::UnicodeString RootCertFile = {read=GetRootCertFile, write=SetRootCertFile};
	__property System::UnicodeString CertFile = {read=GetCertFile, write=SetCertFile};
	__property System::UnicodeString KeyFile = {read=GetKeyFile, write=SetKeyFile};
	__property TGetPEMFilePasskey OnGetPEMFilePasskey = {read=GetOnGetPEMFilePasskey, write=SetOnGetPEMFilePasskey};
	__property TGetPEMFileSBPasskey OnGetPEMFileSBPasskey = {read=GetOnGetPEMFileSBPasskey, write=SetOnGetPEMFileSBPasskey};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCustomCertFiles() { }
	
};


class PASCALIMPLEMENTATION TDSCertFiles : public TDSCustomCertFiles
{
	typedef TDSCustomCertFiles inherited;
	
__published:
	__property SSLVersion = {default=3};
	__property RootCertFile = {default=0};
	__property CertFile = {default=0};
	__property KeyFile = {default=0};
	__property OnGetPEMFilePasskey;
	__property OnGetPEMFileSBPasskey;
public:
	/* TDSCustomCertFiles.Create */ inline __fastcall virtual TDSCertFiles(System::Classes::TComponent* AOwner) : TDSCustomCertFiles(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCertFiles() { }
	
};


class PASCALIMPLEMENTATION TDSHTTPServiceComponent : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TDSHTTPService* FService;
	void __fastcall SetService(TDSHTTPService* const AValue);
	
protected:
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	
public:
	virtual void __fastcall DoCommand(Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo, const System::UnicodeString ARequest, bool &AHandled) = 0 ;
	
__published:
	__property TDSHTTPService* Service = {read=FService, write=SetService};
public:
	/* TComponent.Create */ inline __fastcall virtual TDSHTTPServiceComponent(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSHTTPServiceComponent() { }
	
};


typedef void __fastcall (__closure *TDispatchFileEvent)(System::TObject* Sender, const System::UnicodeString AFileName, Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* Request, Datasnap::Dshttpcommon::TDSHTTPResponse* Response, bool &Handled);

class PASCALIMPLEMENTATION TDSCustomHTTPServiceFileDispatcher : public TDSHTTPServiceComponent
{
	typedef TDSHTTPServiceComponent inherited;
	
private:
	Web::Webfiledispatcher::TWebFileDispatcherProperties* FFileDispatcherProperties;
	TDispatchFileEvent FBeforeDispatch;
	TDispatchFileEvent FAfterDispatch;
	void __fastcall SetWebFileExtensions(Web::Webfiledispatcher::TWebFileExtensions* const Value);
	Web::Webfiledispatcher::TWebFileExtensions* __fastcall GetWebFileExtensions();
	void __fastcall SetWebDirectories(Web::Webfiledispatcher::TWebDirectories* const Value);
	Web::Webfiledispatcher::TWebDirectories* __fastcall GetWebDirectories();
	System::UnicodeString __fastcall GetRootDirectory();
	void __fastcall SetRootDirectory(const System::UnicodeString Value);
	bool __fastcall IsRootDirectoryStored();
	
public:
	__fastcall virtual TDSCustomHTTPServiceFileDispatcher(System::Classes::TComponent* AOwner);
	virtual void __fastcall DoCommand(Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* ARequestInfo, Datasnap::Dshttpcommon::TDSHTTPResponse* AResponseInfo, const System::UnicodeString ARequest, bool &AHandled);
	
protected:
	virtual void __fastcall DoBeforeDispatch(System::TObject* Sender, const System::UnicodeString AFileName, Datasnap::Dshttpcommon::TDSHTTPContext* AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* Request, Datasnap::Dshttpcommon::TDSHTTPResponse* Response, bool &Handled);
	__property TDispatchFileEvent BeforeDispatch = {read=FBeforeDispatch, write=FBeforeDispatch};
	__property TDispatchFileEvent AfterDispatch = {read=FAfterDispatch, write=FAfterDispatch};
	__property Web::Webfiledispatcher::TWebFileExtensions* WebFileExtensions = {read=GetWebFileExtensions, write=SetWebFileExtensions};
	__property Web::Webfiledispatcher::TWebDirectories* WebDirectories = {read=GetWebDirectories, write=SetWebDirectories};
	__property System::UnicodeString RootDirectory = {read=GetRootDirectory, write=SetRootDirectory, stored=IsRootDirectoryStored};
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSCustomHTTPServiceFileDispatcher() { }
	
};


class PASCALIMPLEMENTATION TDSHTTPServiceFileDispatcher : public TDSCustomHTTPServiceFileDispatcher
{
	typedef TDSCustomHTTPServiceFileDispatcher inherited;
	
__published:
	__property BeforeDispatch;
	__property AfterDispatch;
	__property WebFileExtensions;
	__property WebDirectories;
	__property RootDirectory;
public:
	/* TDSCustomHTTPServiceFileDispatcher.Create */ inline __fastcall virtual TDSHTTPServiceFileDispatcher(System::Classes::TComponent* AOwner) : TDSCustomHTTPServiceFileDispatcher(AOwner) { }
	
public:
	/* TComponent.Destroy */ inline __fastcall virtual ~TDSHTTPServiceFileDispatcher() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPContextIndy : public Datasnap::Dshttpcommon::TDSHTTPContext
{
	typedef Datasnap::Dshttpcommon::TDSHTTPContext inherited;
	
private:
	Ippeerapi::_di_IIPContext FContext;
	TDSHTTPRequestIndy* FRequest;
	TDSHTTPResponseIndy* FResponse;
	
public:
	__fastcall TDSHTTPContextIndy(const Ippeerapi::_di_IIPContext AContext, const Ippeerapi::_di_IIPHTTPRequestInfo ARequestInfo, const Ippeerapi::_di_IIPHTTPResponseInfo AResponseInfo);
	__fastcall virtual ~TDSHTTPContextIndy();
	virtual bool __fastcall Connected();
	__property Ippeerapi::_di_IIPContext Context = {read=FContext};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPRequestIndy : public Datasnap::Dshttpcommon::TDSHTTPRequest
{
	typedef Datasnap::Dshttpcommon::TDSHTTPRequest inherited;
	
private:
	Ippeerapi::_di_IIPHTTPRequestInfo FRequestInfo;
	System::UnicodeString FDocument;
	
protected:
	virtual System::UnicodeString __fastcall GetCommand();
	virtual Datasnap::Dshttpcommon::TDSHTTPCommandType __fastcall GetCommandType();
	virtual System::UnicodeString __fastcall GetDocument();
	virtual System::Classes::TStrings* __fastcall GetParams();
	virtual System::Classes::TStream* __fastcall GetPostStream();
	virtual System::UnicodeString __fastcall GetAuthUserName();
	virtual System::UnicodeString __fastcall GetAuthPassword();
	virtual System::UnicodeString __fastcall GetURI();
	virtual System::UnicodeString __fastcall GetPragma();
	virtual System::UnicodeString __fastcall GetAccept();
	virtual System::UnicodeString __fastcall GetRemoteIP();
	virtual System::UnicodeString __fastcall GetUserAgent();
	virtual System::UnicodeString __fastcall GetProtocolVersion();
	
public:
	__fastcall TDSHTTPRequestIndy(Ippeerapi::_di_IIPHTTPRequestInfo ARequestInfo);
	__property Ippeerapi::_di_IIPHTTPRequestInfo RequestInfo = {read=FRequestInfo};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPRequestIndy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPResponseIndy : public Datasnap::Dshttpcommon::TDSHTTPResponse
{
	typedef Datasnap::Dshttpcommon::TDSHTTPResponse inherited;
	
private:
	Ippeerapi::_di_IIPHTTPResponseInfo FResponseInfo;
	
protected:
	virtual System::Classes::TStream* __fastcall GetContentStream();
	virtual int __fastcall GetResponseNo();
	virtual System::UnicodeString __fastcall GetResponseText();
	virtual void __fastcall SetContentStream(System::Classes::TStream* const Value);
	virtual void __fastcall SetResponseNo(const int Value);
	virtual void __fastcall SetResponseText(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetContentText();
	virtual void __fastcall SetContentText(const System::UnicodeString Value);
	virtual __int64 __fastcall GetContentLength();
	virtual void __fastcall SetContentLength(const __int64 Value);
	virtual bool __fastcall GetCloseConnection();
	virtual void __fastcall SetCloseConnection(const bool Value);
	virtual System::UnicodeString __fastcall GetPragma();
	virtual void __fastcall SetPragma(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetContentType();
	virtual void __fastcall SetContentType(const System::UnicodeString Value);
	virtual bool __fastcall GetFreeContentStream();
	virtual void __fastcall SetFreeContentStream(const bool Value);
	
public:
	__fastcall TDSHTTPResponseIndy(Ippeerapi::_di_IIPHTTPResponseInfo AResponseInfo);
	virtual void __fastcall SetHeaderAuthentication(const System::UnicodeString Value, const System::UnicodeString Realm);
	__property Ippeerapi::_di_IIPHTTPResponseInfo ResponseInfo = {read=FResponseInfo};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPResponseIndy() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPApplication : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	#define TDSHTTPApplication_sSessionObject L"session"
	
	
private:
	static TDSHTTPApplication* FInstance;
	bool __fastcall LoadRESTSession(const System::UnicodeString SessionId, const System::UnicodeString UserName, int SessionTimeout, Datasnap::Dssession::TDSSessionLifetime ASessionLifetime, Datasnap::Dssession::TDSTunnelService* const TunnelService, Datasnap::Dsauth::TDSCustomAuthenticationManager* const AuthManager, Datasnap::Dshttpcommon::TDSHTTPRequest* const ARequestInfo, /* out */ bool &IsNewSession);
	Datasnap::Dshttpcommon::TDSHTTPDispatch* __fastcall GetHTTPDispatch();
	void __fastcall SetSessionRequestInfo(Datasnap::Dssession::TDSSession* const ASession, Datasnap::Dshttpcommon::TDSHTTPRequest* const ARequest);
	bool __fastcall GetDispatching();
	
public:
	System::UnicodeString __fastcall GetRequestSessionId(Datasnap::Dshttpcommon::TDSHTTPRequest* const ARequestInfo, const bool CheckURLParams = true);
	void __fastcall StartDispatch(Datasnap::Dshttpcommon::TDSHTTPContext* const AContext, Datasnap::Dshttpcommon::TDSHTTPRequest* const ARequest, Datasnap::Dshttpcommon::TDSHTTPResponse* const AResponse);
	void __fastcall EndDispatch();
	__property bool Dispatching = {read=GetDispatching, nodefault};
	__property Datasnap::Dshttpcommon::TDSHTTPDispatch* HTTPDispatch = {read=GetHTTPDispatch};
	/* static */ __property TDSHTTPApplication* Instance = {read=FInstance};
public:
	/* TObject.Create */ inline __fastcall TDSHTTPApplication() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPApplication() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dshttp */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSHTTP)
using namespace Datasnap::Dshttp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DshttpHPP
