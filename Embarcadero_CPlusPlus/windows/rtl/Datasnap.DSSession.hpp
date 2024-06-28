// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSSession.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DssessionHPP
#define Datasnap_DssessionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SyncObjs.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DbxDatasnap.hpp>
#include <Data.DBXTransport.hpp>
#include <Data.DBXMessageHandlerCommon.hpp>
#include <Data.DbxSocketChannelNative.hpp>
#include <Datasnap.DSAuth.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSTransport.hpp>
#include <Datasnap.DSCommon.hpp>
#include <Datasnap.DSService.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dssession
{
//-- forward type declarations -----------------------------------------------
struct TDSSessionTunnelInfo;
class DELPHICLASS TDSSessionCache;
class DELPHICLASS TDSSessionData;
class DELPHICLASS TDSSessionDictionaryData;
class DELPHICLASS TDSSession;
class DELPHICLASS TDSSessionError;
class DELPHICLASS TDSAuthSession;
class DELPHICLASS TDSRESTSession;
class DELPHICLASS TDSTunnelSession;
class DELPHICLASS TDSRemoteSession;
__interface DELPHIINTERFACE TDSSessionEvent;
typedef System::DelphiInterface<TDSSessionEvent> _di_TDSSessionEvent;
__interface DELPHIINTERFACE TDSSessionVisitor;
typedef System::DelphiInterface<TDSSessionVisitor> _di_TDSSessionVisitor;
class DELPHICLASS TDSSessionManager;
class DELPHICLASS TDSSynchronizedLocalChannel;
class DELPHICLASS TDSLocalServer;
class DELPHICLASS TDSLocalSession;
class DELPHICLASS TDSTunnelService;
class DELPHICLASS TDSTCPSession;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TDSSessionTunnelInfo
{
public:
	System::UnicodeString ChannelName;
	System::UnicodeString ClientChannelId;
	System::UnicodeString SecurityToken;
	System::UnicodeString AuthUser;
	System::UnicodeString AuthPassword;
};


typedef System::Generics::Collections::TList__1<int>* TDSSessionCacheKeys;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSessionCache : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<int,Data::Dbxcommon::TResultCommandHandler*>* FItems;
	
public:
	__fastcall TDSSessionCache();
	__fastcall virtual ~TDSSessionCache();
	int __fastcall AddItem(Data::Dbxcommon::TResultCommandHandler* Item);
	void __fastcall RemoveItem(Data::Dbxcommon::TResultCommandHandler* Item)/* overload */;
	Data::Dbxcommon::TResultCommandHandler* __fastcall RemoveItem(int ID, bool InstanceOwner = true)/* overload */;
	Data::Dbxcommon::TResultCommandHandler* __fastcall GetItem(int ID);
	int __fastcall GetItemID(Data::Dbxcommon::TResultCommandHandler* Item);
	System::Generics::Collections::TList__1<int>* __fastcall GetItemIDs();
	void __fastcall ClearAllItems(bool InstanceOwner = true);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum class DECLSPEC_DENUM TDSSessionLifetime : unsigned char { TimeOut, Request };

enum DECLSPEC_DENUM TDSSessionStatus : unsigned char { Active, Closed, Idle, Terminated, Connected, Expired };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSessionData : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TDSSession* FDSSession;
	void __fastcall SetSession(TDSSession* const ASession);
	
public:
	__fastcall virtual TDSSessionData();
	virtual bool __fastcall HasData(const System::UnicodeString AKey) = 0 ;
	virtual System::UnicodeString __fastcall GetData(const System::UnicodeString AKey) = 0 ;
	virtual void __fastcall PutData(const System::UnicodeString AKey, const System::UnicodeString LValue) = 0 ;
	virtual void __fastcall RemoveData(const System::UnicodeString AKey) = 0 ;
	virtual bool __fastcall HasObject(const System::UnicodeString AKey) = 0 ;
	virtual System::TObject* __fastcall GetObject(const System::UnicodeString AKey) = 0 ;
	virtual bool __fastcall PutObject(const System::UnicodeString AKey, System::TObject* AValue) = 0 ;
	virtual System::TObject* __fastcall RemoveObject(const System::UnicodeString AKey, bool AInstanceOwner) = 0 ;
	__property TDSSession* Session = {read=FDSSession};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSSessionData() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSessionDictionaryData : public TDSSessionData
{
	typedef TDSSessionData inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FMetaData;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TObject*>* FMetaObjects;
	void __fastcall CheckTransient();
	
public:
	__fastcall virtual TDSSessionDictionaryData();
	__fastcall virtual ~TDSSessionDictionaryData();
	virtual bool __fastcall HasData(const System::UnicodeString AKey);
	virtual System::UnicodeString __fastcall GetData(const System::UnicodeString AKey);
	virtual void __fastcall PutData(const System::UnicodeString AKey, const System::UnicodeString LValue);
	virtual void __fastcall RemoveData(const System::UnicodeString AKey);
	virtual bool __fastcall HasObject(const System::UnicodeString AKey);
	virtual System::TObject* __fastcall GetObject(const System::UnicodeString AKey);
	virtual bool __fastcall PutObject(const System::UnicodeString AKey, System::TObject* AValue);
	virtual System::TObject* __fastcall RemoveObject(const System::UnicodeString AKey, bool AInstanceOwner);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSSession : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TDSSessionData* FSessionData;
	System::TDateTime FStartDateTime;
	int FDuration;
	TDSSessionStatus FStatus;
	unsigned FLastActivity;
	System::UnicodeString FUserName;
	System::UnicodeString FSessionName;
	System::Classes::TStrings* FUserRoles;
	TDSSessionCache* FCache;
	System::TObject* FLastResultStream;
	System::TObject* FCreator;
	TDSSessionLifetime FSessionLifetime;
	void __fastcall SetSessionName(const System::UnicodeString sessionId);
	void __fastcall SetUserName(const System::UnicodeString userName);
	void __fastcall SetLifetime(TDSSessionLifetime Value);
	void __fastcall CheckSessionData();
	TDSSessionData* __fastcall CreateSessionData();
	
protected:
	NativeInt __fastcall GetId();
	virtual void __fastcall TerminateSession();
	virtual void __fastcall TerminateInactiveSession();
	bool __fastcall IsIdle(unsigned Seconds);
	bool __fastcall IsIdleMS(unsigned Milliseconds);
	virtual TDSSessionStatus __fastcall GetSessionStatus();
	void __fastcall GetAuthRoleInternal(Datasnap::Dscommonserver::TDSServerMethod* ServerMethod, Datasnap::Dsauth::TDSCustomAuthenticationManager* AuthManager, /* out */ System::Classes::TStrings* &AuthorizedRoles, /* out */ System::Classes::TStrings* &DeniedRoles);
	virtual void __fastcall CheckTransient();
	
public:
	__fastcall virtual TDSSession()/* overload */;
	__fastcall virtual TDSSession(const System::UnicodeString SessionName)/* overload */;
	__fastcall virtual TDSSession(const System::UnicodeString SessionName, const System::UnicodeString AUser)/* overload */;
	__fastcall virtual ~TDSSession();
	void __fastcall MarkActivity();
	void __fastcall ScheduleUserEvent(Data::Dbxcommon::_di_TDBXScheduleEvent Event, int ElapsedTime);
	void __fastcall ScheduleTerminationEvent();
	void __fastcall ScheduleInactiveTerminationEvent();
	void __fastcall CancelScheduledEvent();
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, Data::Dbxcommon::TDBXProperties* connectionProps)/* overload */;
	virtual bool __fastcall Authorize(Datasnap::Dscommonserver::TDSAuthorizeEventObject* EventObject)/* overload */;
	virtual bool __fastcall RequiresAuthorization(Datasnap::Dscommonserver::TDSMethodInfo* MethodInfo);
	virtual void __fastcall GetAuthRoles(Datasnap::Dscommonserver::TDSServerMethod* ServerMethod, /* out */ System::Classes::TStrings* &AuthorizedRoles, /* out */ System::Classes::TStrings* &DeniedRoles);
	virtual bool __fastcall IsValid();
	static System::UnicodeString __fastcall GenerateSessionId();
	virtual void __fastcall Close();
	virtual void __fastcall Terminate();
	bool __fastcall HasData(System::UnicodeString Key);
	System::UnicodeString __fastcall GetData(System::UnicodeString Key);
	void __fastcall PutData(System::UnicodeString Key, System::UnicodeString Value);
	void __fastcall RemoveData(System::UnicodeString Key);
	bool __fastcall HasObject(System::UnicodeString Key);
	System::TObject* __fastcall GetObject(System::UnicodeString Key);
	bool __fastcall PutObject(System::UnicodeString Key, System::TObject* Value);
	System::TObject* __fastcall RemoveObject(System::UnicodeString Key, bool InstanceOwner = true);
	unsigned __fastcall ElapsedSinceLastActvity();
	unsigned __fastcall ExpiresIn();
	__property int LifeDuration = {read=FDuration, write=FDuration, nodefault};
#ifndef _WIN64
	__property NativeInt Id = {read=GetId, nodefault};
#else /* _WIN64 */
	__property NativeInt Id = {read=GetId};
#endif /* _WIN64 */
	__property TDSSessionStatus Status = {read=GetSessionStatus, nodefault};
	__property System::TDateTime StartDateTime = {read=FStartDateTime};
	__property System::UnicodeString UserName = {read=FUserName};
	__property System::UnicodeString SessionName = {read=FSessionName};
	__property System::Classes::TStrings* UserRoles = {read=FUserRoles};
	__property TDSSessionCache* ParameterCache = {read=FCache};
	__property System::TObject* LastResultStream = {read=FLastResultStream, write=FLastResultStream};
	__property System::TObject* ObjectCreator = {read=FCreator, write=FCreator};
	__property TDSSessionLifetime SessionLifetime = {read=FSessionLifetime, nodefault};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSessionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall TDSSessionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall TDSSessionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDSSessionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDSSessionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSSessionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSSessionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDSSessionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDSSessionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSSessionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSSessionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSSessionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSSessionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDSSessionError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSAuthSession : public TDSSession
{
	typedef TDSSession inherited;
	
protected:
	Datasnap::Dsauth::TDSCustomAuthenticationManager* FAuthManager;
	
public:
	virtual void __fastcall GetAuthRoles(Datasnap::Dscommonserver::TDSServerMethod* ServerMethod, /* out */ System::Classes::TStrings* &AuthorizedRoles, /* out */ System::Classes::TStrings* &DeniedRoles);
	virtual bool __fastcall Authorize(Datasnap::Dscommonserver::TDSAuthorizeEventObject* EventObject)/* overload */;
	__property Datasnap::Dsauth::TDSCustomAuthenticationManager* AuthManager = {read=FAuthManager};
public:
	/* TDSSession.Create */ inline __fastcall virtual TDSAuthSession()/* overload */ : TDSSession() { }
	/* TDSSession.Create */ inline __fastcall virtual TDSAuthSession(const System::UnicodeString SessionName)/* overload */ : TDSSession(SessionName) { }
	/* TDSSession.Create */ inline __fastcall virtual TDSAuthSession(const System::UnicodeString SessionName, const System::UnicodeString AUser)/* overload */ : TDSSession(SessionName, AUser) { }
	/* TDSSession.Destroy */ inline __fastcall virtual ~TDSAuthSession() { }
	
};


class PASCALIMPLEMENTATION TDSRESTSession : public TDSAuthSession
{
	typedef TDSAuthSession inherited;
	
public:
	__fastcall virtual TDSRESTSession(Datasnap::Dsauth::TDSCustomAuthenticationManager* AAuthManager);
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, Data::Dbxcommon::TDBXProperties* connectionProps)/* overload */;
public:
	/* TDSSession.Destroy */ inline __fastcall virtual ~TDSRESTSession() { }
	
};


class PASCALIMPLEMENTATION TDSTunnelSession : public TDSAuthSession
{
	typedef TDSAuthSession inherited;
	
private:
	void *FUserPointer;
	int FUserFlag;
	
protected:
	virtual void __fastcall TerminateSession();
	
public:
	__fastcall TDSTunnelSession();
	__fastcall virtual ~TDSTunnelSession();
	virtual void __fastcall Open() = 0 ;
	virtual void __fastcall Reopen(Data::Dbxdatasnap::TDBXDatasnapProperties* DBXDatasnapProperties);
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count) = 0 ;
#endif /* _WIN64 */
	__property void * UserPointer = {read=FUserPointer, write=FUserPointer};
	__property int UserFlag = {read=FUserFlag, write=FUserFlag, nodefault};
};


class PASCALIMPLEMENTATION TDSRemoteSession : public TDSTunnelSession
{
	typedef TDSTunnelSession inherited;
	
private:
	Data::Dbxsocketchannelnative::TDBXSocketChannel* FSocketChannel;
	
public:
	__fastcall TDSRemoteSession(Data::Dbxdatasnap::TDBXDatasnapProperties* DBXDatasnapProperties);
	__fastcall virtual ~TDSRemoteSession();
	virtual void __fastcall Open();
	virtual void __fastcall Reopen(Data::Dbxdatasnap::TDBXDatasnapProperties* DBXDatasnapProperties);
	virtual void __fastcall Close();
	virtual void __fastcall Terminate();
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, Data::Dbxcommon::TDBXProperties* connectionProps)/* overload */;
	__property Data::Dbxsocketchannelnative::TDBXSocketChannel* SocketChannel = {read=FSocketChannel, write=FSocketChannel};
};


enum DECLSPEC_DENUM TDSSessionEventType : unsigned char { SessionCreate, SessionClose };

__interface TDSSessionEvent  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* Sender, const TDSSessionEventType EventType, TDSSession* const Session) = 0 ;
};

__interface TDSSessionVisitor  : public System::IInterface 
{
	virtual void __fastcall Invoke(TDSSession* const Session) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSessionManager : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE TFactoryMethod;
	typedef System::DelphiInterface<TFactoryMethod> _di_TFactoryMethod;
	__interface TFactoryMethod  : public System::IInterface 
	{
		virtual TDSSession* __fastcall Invoke() = 0 ;
	};
	
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDSSession*>* FSessionContainer;
	System::Generics::Collections::TList__1<_di_TDSSessionEvent>* FListeners;
	
private:
	static TDSSessionManager* FInstance;
	TDSSession* __fastcall GetSession(System::UnicodeString SessionId);
	TDSTunnelSession* __fastcall GetTunnelSession(System::UnicodeString SessionId);
	System::UnicodeString __fastcall GetUniqueSessionId();
	void __fastcall TerminateSession(TDSSession* session)/* overload */;
	void __fastcall CloseSession(TDSSession* session)/* overload */;
	void __fastcall NotifyEvents(TDSSession* session, TDSSessionEventType EventType);
	void __fastcall TerminateAllSessions(System::TObject* const ACreator, bool AAllSessions)/* overload */;
	
public:
	__fastcall TDSSessionManager();
	__fastcall virtual ~TDSSessionManager();
	template<typename T> T __fastcall CreateSession(_di_TFactoryMethod factory, TDSSessionLifetime ASessionLifetime, bool DoNotify = true)/* overload */;
	template<typename T> T __fastcall CreateSession(_di_TFactoryMethod factory, System::UnicodeString userName)/* overload */;
	template<typename T> T __fastcall CreateSession(_di_TFactoryMethod factory, System::UnicodeString userName, TDSSessionLifetime ASessionLifetime)/* overload */;
	template<typename T> T __fastcall CreateSession(_di_TFactoryMethod factory, bool DoNotify = true)/* overload */;
	void __fastcall AddSessionEvent(_di_TDSSessionEvent Event);
	bool __fastcall RemoveSessionEvent(_di_TDSSessionEvent Event);
	void __fastcall CloseSession(System::UnicodeString SessionId)/* overload */;
	void __fastcall TerminateAllSessions(System::TObject* const ACreator)/* overload */;
	void __fastcall TerminateAllSessions()/* overload */;
	void __fastcall ForEachSession(_di_TDSSessionVisitor AVisitor);
	void __fastcall TerminateSession(const System::UnicodeString sessionId)/* overload */;
	int __fastcall GetSessionCount();
	TDSSession* __fastcall RemoveSession(System::UnicodeString SessionId);
	void __fastcall GetOpenSessionKeys(System::Classes::TStrings* Container)/* overload */;
	void __fastcall GetOpenSessionKeys(System::Classes::TStrings* Container, System::TObject* ACreator)/* overload */;
	__classmethod TDSSession* __fastcall GetThreadSession();
	__classmethod void __fastcall SetAsThreadSession(TDSSession* Session);
	__classmethod void __fastcall ClearThreadSession();
	__property TDSSession* Session[System::UnicodeString id] = {read=GetSession};
	__property TDSTunnelSession* TunnelSession[System::UnicodeString id] = {read=GetTunnelSession};
	/* static */ __property TDSSessionManager* Instance = {read=FInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSSynchronizedLocalChannel : public Data::Dbxtransport::TDBXLocalChannel
{
	typedef Data::Dbxtransport::TDBXLocalChannel inherited;
	
private:
	System::Syncobjs::TSemaphore* FReadSemaphore;
	System::Syncobjs::TSemaphore* FLocalReadSemaphore;
	System::Syncobjs::TSemaphore* FWriteSemaphore;
	System::Syncobjs::TSemaphore* FLocalWriteSemaphore;
	bool FTerminated;
	
public:
	__fastcall TDSSynchronizedLocalChannel(const System::UnicodeString ServerName);
	__fastcall virtual ~TDSSynchronizedLocalChannel();
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall WriteLocalData(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall ReadLocalData(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall WriteLocalData(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall ReadLocalData(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
	void __fastcall Terminate();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSLocalServer : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
private:
	System::UnicodeString FErrorMsg;
	Data::Dbxtransport::TDBXLocalChannel* FLocalChannel;
	Data::Dbxmessagehandlercommon::TDBXProtocolHandler* FDBXProtocolHandler;
	TDSSession* FSession;
	
protected:
	virtual void __fastcall Execute();
	void __fastcall ConsumeByteStream();
	
public:
	__fastcall TDSLocalServer(Data::Dbxtransport::TDBXLocalChannel* ALocalChannel, Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* AProtocolHandlerFactory, Data::Dbxtransport::TTransportFilterCollection* AFilters, TDSSession* Session);
	__fastcall virtual ~TDSLocalServer();
	bool __fastcall HasError();
	__property System::UnicodeString ErrorMsg = {read=FErrorMsg};
};


class PASCALIMPLEMENTATION TDSLocalSession : public TDSTunnelSession
{
	typedef TDSTunnelSession inherited;
	
private:
	Data::Dbxtransport::TTransportFilterCollection* FFilters;
	Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* FProtocolHandlerFactory;
	TDSSynchronizedLocalChannel* FLocalChannel;
	TDSLocalServer* FDSLocalServer;
	
public:
	__fastcall TDSLocalSession(Data::Dbxtransport::TTransportFilterCollection* AFilters, Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* AProtocolHandlerFactory);
	__fastcall virtual ~TDSLocalSession();
	virtual void __fastcall Open();
	virtual void __fastcall Close();
	virtual void __fastcall Terminate();
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, Data::Dbxcommon::TDBXProperties* connectionProps)/* overload */;
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
};


#ifndef _WIN64
typedef System::DynamicArray<System::Byte> _dt_Datasnap_Dssession_1;
typedef void __fastcall (__closure *TTunnelSessionEvent)(System::TObject* Sender, TDSTunnelSession* Session, _dt_Datasnap_Dssession_1 Content, int &Count);
#else /* _WIN64 */
typedef void __fastcall (__closure *TTunnelSessionEvent)(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
#endif /* _WIN64 */

class PASCALIMPLEMENTATION TDSTunnelService : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	Data::Dbxtransport::TTransportFilterCollection* FFilters;
	Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* FProtocolHandlerFactory;
	System::UnicodeString FDSHostname;
	int FDSPort;
	bool FHasLocalServer;
	
private:
	Data::Dbxdatasnap::TDBXDatasnapProperties* FDBXProperties;
	TTunnelSessionEvent FOnOpenSession;
	TTunnelSessionEvent FOnErrorOpenSession;
	TTunnelSessionEvent FOnCloseSession;
	TTunnelSessionEvent FOnWriteSession;
	TTunnelSessionEvent FOnReadSession;
	TTunnelSessionEvent FOnErrorWriteSession;
	TTunnelSessionEvent FOnErrorReadSession;
	Datasnap::Dsauth::TDSCustomAuthenticationManager* FDSAuthenticationManager;
	
protected:
	__classmethod bool __fastcall CanCloseSession(System::UnicodeString &id);
	void __fastcall CreateSession(/* out */ TDSTunnelSession* &Session, System::UnicodeString RemoteIP = System::UnicodeString())/* overload */;
	void __fastcall CreateSession(/* out */ TDSTunnelSession* &Session, const Data::Dbxtransport::TDBXClientInfo &ClientInfo)/* overload */;
	TDSTunnelSession* __fastcall GetSession(const System::UnicodeString SessionId);
#ifndef _WIN64
	void __fastcall DefaultOpenSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
	void __fastcall DefaultErrorOpenSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
	void __fastcall DefaultCloseSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
	void __fastcall DefaultWriteSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
	void __fastcall DefaultReadSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
	void __fastcall DefaultErrorWriteSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
	void __fastcall DefaultErrorReadSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::DynamicArray<System::Byte> Content, int &Count);
#else /* _WIN64 */
	void __fastcall DefaultOpenSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
	void __fastcall DefaultErrorOpenSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
	void __fastcall DefaultCloseSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
	void __fastcall DefaultWriteSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
	void __fastcall DefaultReadSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
	void __fastcall DefaultErrorWriteSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
	void __fastcall DefaultErrorReadSessionEvent(System::TObject* Sender, TDSTunnelSession* Session, System::TArray__1<System::Byte> Content, int &Count);
#endif /* _WIN64 */
	void __fastcall SetDSHostname(System::UnicodeString AHostname);
	void __fastcall SetDSPort(int APort);
	
public:
	__fastcall virtual TDSTunnelService(System::UnicodeString DSHostname, int DSPort, Data::Dbxtransport::TTransportFilterCollection* AFilters, Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* AProtocolHandlerFactory);
	__fastcall virtual ~TDSTunnelService();
	void __fastcall AddUserCredentials(const System::UnicodeString userName, const System::UnicodeString userPass);
	void __fastcall TerminateAllSessions();
	__classmethod void __fastcall TerminateSession(System::Classes::TStrings* const Params)/* overload */;
	int __fastcall GetSessionCount();
	void __fastcall CloseSession(System::UnicodeString SessionId)/* overload */;
	void __fastcall GetOpenSessionKeys(System::Classes::TStrings* Container);
	TDSTunnelSession* __fastcall InitializeSession(System::Classes::TStrings* Params, System::UnicodeString RemoteIP = System::UnicodeString())/* overload */;
	TDSTunnelSession* __fastcall InitializeSession(System::Classes::TStrings* Params, const Data::Dbxtransport::TDBXClientInfo &ClientInfo)/* overload */;
#ifndef _WIN64
	void __fastcall ProcessPOST(System::Classes::TStrings* Params, System::DynamicArray<System::Byte> Content, /* out */ System::Json::TJSONValue* &JsonResponse, /* out */ bool &CloseConnection);
#else /* _WIN64 */
	void __fastcall ProcessPOST(System::Classes::TStrings* Params, System::TArray__1<System::Byte> Content, /* out */ System::Json::TJSONValue* &JsonResponse, /* out */ bool &CloseConnection);
#endif /* _WIN64 */
	System::Classes::TStream* __fastcall ProcessGET(System::Classes::TStrings* Params, int &Len, /* out */ bool &CloseConnection);
	bool __fastcall NeedsAuthentication(System::Classes::TStrings* Params);
	__property System::UnicodeString DSHostname = {read=FDSHostname, write=SetDSHostname};
	__property int DSPort = {read=FDSPort, write=SetDSPort, nodefault};
	__property bool HasLocalServer = {read=FHasLocalServer, write=FHasLocalServer, nodefault};
	__property Data::Dbxtransport::TTransportFilterCollection* Filters = {read=FFilters, write=FFilters};
	__property Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* ProtocolHandlerFactory = {read=FProtocolHandlerFactory, write=FProtocolHandlerFactory};
	__property TTunnelSessionEvent OnOpenSession = {read=FOnOpenSession, write=FOnOpenSession};
	__property TTunnelSessionEvent OnErrorOpenSession = {read=FOnErrorOpenSession, write=FOnErrorOpenSession};
	__property TTunnelSessionEvent OnCloseSession = {read=FOnCloseSession, write=FOnCloseSession};
	__property TTunnelSessionEvent OnWriteSession = {read=FOnWriteSession, write=FOnWriteSession};
	__property TTunnelSessionEvent OnReadSession = {read=FOnReadSession, write=FOnReadSession};
	__property TTunnelSessionEvent OnErrorWriteSession = {read=FOnErrorWriteSession, write=FOnErrorWriteSession};
	__property TTunnelSessionEvent OnErrorReadSession = {read=FOnErrorReadSession, write=FOnErrorReadSession};
	__property int SessionCount = {read=GetSessionCount, nodefault};
	__property Datasnap::Dsauth::TDSCustomAuthenticationManager* DSAuthenticationManager = {read=FDSAuthenticationManager, write=FDSAuthenticationManager};
};


class PASCALIMPLEMENTATION TDSTCPSession : public TDSAuthSession
{
	typedef TDSAuthSession inherited;
	
public:
	__fastcall virtual TDSTCPSession(Datasnap::Dsauth::TDSCustomAuthenticationManager* AAuthManager)/* overload */;
	__fastcall virtual TDSTCPSession(System::TObject* AAuthManager)/* overload */;
	virtual bool __fastcall Authenticate(Datasnap::Dscommonserver::TDSAuthenticateEventObject* const AuthenticateEventObject, Data::Dbxcommon::TDBXProperties* connectionProps)/* overload */;
public:
	/* TDSSession.Create */ inline __fastcall virtual TDSTCPSession()/* overload */ : TDSAuthSession() { }
	/* TDSSession.Create */ inline __fastcall virtual TDSTCPSession(const System::UnicodeString SessionName)/* overload */ : TDSAuthSession(SessionName) { }
	/* TDSSession.Create */ inline __fastcall virtual TDSTCPSession(const System::UnicodeString SessionName, const System::UnicodeString AUser)/* overload */ : TDSAuthSession(SessionName, AUser) { }
	/* TDSSession.Destroy */ inline __fastcall virtual ~TDSTCPSession() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dssession */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSSESSION)
using namespace Datasnap::Dssession;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DssessionHPP
