// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSServer.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DsserverHPP
#define Datasnap_DsserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXPlatform.hpp>
#include <Data.DBXJSON.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <Datasnap.DSCommon.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSReflect.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------
namespace Datasnap
{
namespace Dsserver
{
typedef ::System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,::Data::Dbxjsonreflect::TConverterEvent*>  TConverterEventDictionary;
typedef void __fastcall (__closure *TDSSetupConverterEvent)(TConverterEventDictionary* RegisteredConverters);
typedef ::System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,::Data::Dbxjsonreflect::TReverterEvent*>  TReverterEventDictionary;
typedef void __fastcall (__closure *TDSSetupReverterEvent)(TReverterEventDictionary* RegisteredReverters);
}	/* namespace Dsserver */
}	/* namespace Datasnap */

namespace Datasnap
{
namespace Dsserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSCallbackTunnelBufferItem;
class DELPHICLASS TDSCallbackTunnel;
struct TDSCallbackTunnelEventItem;
__interface DELPHIINTERFACE TDSCallbackTunnelEvent;
typedef System::DelphiInterface<TDSCallbackTunnelEvent> _di_TDSCallbackTunnelEvent;
class DELPHICLASS TDSCallbackTunnelManager;
class DELPHICLASS TDSCallbackTunnelManagerInternal;
class DELPHICLASS TDSServer;
class DELPHICLASS TDSServerDriver;
class DELPHICLASS TDSServerClass;
class DELPHICLASS TServerClassAdapter;
class DELPHICLASS TServerClassAdapterFactory;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TDSGetClassEvent)(TDSServerClass* DSServerClass, System::Classes::TPersistentClass &PersistentClass);

typedef void __fastcall (__closure *TDSCreateInstanceEvent)(Datasnap::Dscommonserver::TDSCreateInstanceEventObject* DSCreateInstanceEventObject);

typedef void __fastcall (__closure *TDSDestroyInstanceEvent)(Datasnap::Dscommonserver::TDSDestroyInstanceEventObject* DSDestroyInstanceEventObject);

typedef void __fastcall (__closure *TDSPrepareEvent)(Datasnap::Dscommonserver::TDSPrepareEventObject* DSPrepareEventObject);

typedef void __fastcall (__closure *TDSConnectEvent)(Datasnap::Dscommonserver::TDSConnectEventObject* DSConnectEventObject);

typedef void __fastcall (__closure *TDSErrorEvent)(Datasnap::Dscommonserver::TDSErrorEventObject* DSErrorEventObject);

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCallbackTunnelBufferItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FChannelName;
	System::UnicodeString FCallbackId;
	System::Json::TJSONValue* FMsg;
	bool FIsBroadcast;
	bool FInstanceOwner;
	System::Json::TJSONValue* FResponse;
	int FArgType;
	bool FError;
	
public:
	__fastcall TDSCallbackTunnelBufferItem(const System::UnicodeString ChannelName, const System::UnicodeString CallbackId, const bool IsBroadcast, System::Json::TJSONValue* const Msg, const int MsgType, const bool InstanceOwner);
	__fastcall virtual ~TDSCallbackTunnelBufferItem();
	__property System::UnicodeString ChannelName = {read=FChannelName};
	__property System::UnicodeString CallbackId = {read=FCallbackId};
	__property bool IsBroadcast = {read=FIsBroadcast, nodefault};
	__property System::Json::TJSONValue* Msg = {read=FMsg, write=FMsg};
	__property int ArgType = {read=FArgType, nodefault};
	__property bool InstanceOwner = {read=FInstanceOwner, write=FInstanceOwner, nodefault};
	__property System::Json::TJSONValue* Response = {read=FResponse, write=FResponse};
	__property bool IsError = {read=FError, write=FError, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM TDSCallbackTunnelState : unsigned char { ctsWaitingOnServer, ctsWaitingForClient };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCallbackTunnel : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FServerChannelName;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::Classes::TStrings*>* FCallbacks;
	System::UnicodeString FClientId;
	System::Generics::Collections::TThreadedQueue__1<TDSCallbackTunnelBufferItem*>* FQueue;
	TDSCallbackTunnelBufferItem* FThinPop;
	System::UnicodeString FSecurityToken;
	TDSCallbackTunnelState FState;
	System::UnicodeString FServerName;
	int FTimeoutLength;
	void __fastcall SetState(TDSCallbackTunnelState State);
	NativeInt __fastcall GetId();
	void __fastcall TerminateTimedOutTunnel();
	void __fastcall GracefullyFreeTunnelItem(TDSCallbackTunnelBufferItem* Item);
	
protected:
	void __fastcall Lock();
	void __fastcall UnLock();
	
public:
	__fastcall virtual TDSCallbackTunnel(const System::UnicodeString ServerChannelName, const System::UnicodeString ClientId, const System::UnicodeString SecurityToken, const int QueueSize)/* overload */;
	__fastcall virtual ~TDSCallbackTunnel();
	bool __fastcall ListeningOn(const System::UnicodeString ChannelName);
	void __fastcall AddListeningOnChannelNames(System::Generics::Collections::TList__1<System::UnicodeString>* &ChannelNames, const bool AllowDuplicates = false);
	bool __fastcall BroadcastMessage(System::Json::TJSONValue* const Msg, System::UnicodeString ChannelName = System::UnicodeString(), const unsigned Timeout = (unsigned)(0x1388), const int ArgType = 0x1)/* overload */;
	bool __fastcall BroadcastMessage(const System::UnicodeString CallbackId, System::Json::TJSONValue* const Msg, const unsigned Timeout = (unsigned)(0x1388), const int ArgType = 0x1)/* overload */;
	bool __fastcall SendMessage(const System::UnicodeString Id, System::Json::TJSONValue* const Msg, /* out */ System::Json::TJSONValue* &RespMsg, const unsigned Timeout = (unsigned)(0x0), const int ArgType = 0x1);
	bool __fastcall HasId(const System::UnicodeString Id);
	void __fastcall AddAllIds(System::Generics::Collections::TList__1<System::UnicodeString>* container);
	bool __fastcall AddId(const System::UnicodeString Id, System::Classes::TStrings* Channels);
	bool __fastcall RemoveId(const System::UnicodeString Id);
	int __fastcall CallbackCount();
	__property System::UnicodeString ServerChannelName = {read=FServerChannelName};
	__property System::UnicodeString ClientId = {read=FClientId};
	__property System::Generics::Collections::TThreadedQueue__1<TDSCallbackTunnelBufferItem*>* Queue = {read=FQueue};
	__property TDSCallbackTunnelBufferItem* ThinPop = {read=FThinPop, write=FThinPop};
	__property System::UnicodeString SecurityToken = {read=FSecurityToken, write=FSecurityToken};
	__property TDSCallbackTunnelState State = {read=FState, write=SetState, nodefault};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TDSCallbackTunnelEventItem
{
public:
	Datasnap::Dscommon::TDSCallbackTunnelEventType EventType;
	TDSCallbackTunnel* Tunnel;
	System::UnicodeString TunnelId;
	System::UnicodeString TunnelChannelName;
	System::UnicodeString CallbackId;
	System::Classes::TStrings* CallbackChannelNames;
};


__interface TDSCallbackTunnelEvent  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* Sender, const TDSCallbackTunnelEventItem &EventItem) = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCallbackTunnelManager : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	static TDSCallbackTunnelManager* FInstance;
	System::Generics::Collections::TList__1<_di_TDSCallbackTunnelEvent>* FListeners;
	
public:
	__fastcall TDSCallbackTunnelManager();
	__fastcall virtual ~TDSCallbackTunnelManager();
	void __fastcall AddTunnelEvent(_di_TDSCallbackTunnelEvent Event);
	bool __fastcall RemoveTunnelEvent(_di_TDSCallbackTunnelEvent Event);
	/* static */ __property TDSCallbackTunnelManager* Instance = {read=FInstance};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSCallbackTunnelManagerInternal : public TDSCallbackTunnelManager
{
	typedef TDSCallbackTunnelManager inherited;
	
private:
	void __fastcall NotifyEvents(const TDSCallbackTunnelEventItem &EventItem);
	
public:
	TDSCallbackTunnel* __fastcall CreateChannelTunnel(const System::UnicodeString ServerChannelName, const System::UnicodeString ClientId, const System::UnicodeString SecurityToken, const int QueueSize);
	void __fastcall AddCallbackToTunnel(TDSCallbackTunnel* const Tunnel, const System::UnicodeString CallbackId, System::Classes::TStringList* ChannelNames);
	bool __fastcall RemoveCallbackFromTunnel(TDSCallbackTunnel* const Tunnel, const System::UnicodeString CallbackId);
	void __fastcall CloseChannelTunnel(TDSCallbackTunnel* tunnel);
public:
	/* TDSCallbackTunnelManager.Create */ inline __fastcall TDSCallbackTunnelManagerInternal() : TDSCallbackTunnelManager() { }
	/* TDSCallbackTunnelManager.Destroy */ inline __fastcall virtual ~TDSCallbackTunnelManagerInternal() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServer : public Datasnap::Dscommonserver::TDSCustomServer
{
	typedef Datasnap::Dscommonserver::TDSCustomServer inherited;
	
private:
	bool FAutoStart;
	TDSConnectEvent FConnectEvent;
	TDSPrepareEvent FPrepareEvent;
	TDSConnectEvent FDisconnectEvent;
	TDSErrorEvent FErrorEvent;
	System::Generics::Collections::TObjectList__1<TDSCallbackTunnel*>* FCallbacks;
	TDSSetupConverterEvent FSetupConverterEvent;
	TDSSetupReverterEvent FSetupReverterEvent;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,Data::Dbxjsonreflect::TConverterEvent*>* FRegConverters;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,Data::Dbxjsonreflect::TReverterEvent*>* FRegReverters;
	int FChannelQueueSize;
	int FChannelResponseTimeout;
	static Data::Dbxplatform::TDBXArrayList* FServerList;
	static void __fastcall AddServer(Datasnap::Dscommonserver::TDSCustomServer* Server);
	static void __fastcall RemoveServer(Datasnap::Dscommonserver::TDSCustomServer* Server);
	void __fastcall ReadHideDSAdmin(System::Classes::TReader* Reader);
	void __fastcall ShutdownCallbacks();
	
protected:
	virtual void __fastcall TransportStopping(Datasnap::Dscommonserver::TDSServerTransport* const Sender);
	virtual void __fastcall Loaded();
	virtual void __fastcall Connecting(Datasnap::Dscommonserver::TDSConnectEventObject* const ConnectEventObject);
	virtual void __fastcall Preparing(Datasnap::Dscommonserver::TDSPrepareEventObject* const PrepareEventObject);
	virtual void __fastcall Disconnecting(Datasnap::Dscommonserver::TDSConnectEventObject* const ConnectEventObject);
	virtual void __fastcall Error(Datasnap::Dscommonserver::TDSErrorEventObject* const ErrorEventObject);
	virtual Data::Dbxcommon::TDBXTraceEvent __fastcall GetTraceInfoEvent();
	virtual void __fastcall SetTraceInfoEvent(const Data::Dbxcommon::TDBXTraceEvent TraceInfoEvent);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	
public:
	__fastcall virtual TDSServer(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSServer();
	static Datasnap::Dscommonserver::TDSCustomServer* __fastcall FindServer(System::UnicodeString Name);
	virtual Data::Dbxcommon::TDBXConnection* __fastcall GetServerConnection(Data::Dbxcommon::TDBXProperties* const Properties)/* overload */;
	virtual void __fastcall Start();
	virtual void __fastcall Stop();
	TDSCallbackTunnel* __fastcall CreateChannelTunnel(const System::UnicodeString ChannelName, const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::Classes::TStringList* ChannelNames, const System::UnicodeString SecurityToken);
	bool __fastcall RegisterChannelCallback(const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::Classes::TStringList* ChannelNames, const System::UnicodeString SecurityToken);
	TDSCallbackTunnel* __fastcall GetCallbackTunnel(const System::UnicodeString ClientManagerId);
	TDSCallbackTunnel* __fastcall CallbackTunnelOf(const System::UnicodeString ClientManagerId);
	bool __fastcall HasChannelCallback(const System::UnicodeString ClientId);
	void __fastcall UnregisterChannelCallback(const System::UnicodeString ClientId, const System::UnicodeString SecurityToken, bool Owner = false)/* overload */;
	void __fastcall UnregisterChannelCallback(const System::UnicodeString ClientId, const System::UnicodeString CallbackId, const System::UnicodeString SecurityToken)/* overload */;
	void __fastcall UnregisterChannelCallback(TDSCallbackTunnel* Tunnel, bool DoBroadcast = true)/* overload */;
	bool __fastcall BroadcastMessage(const System::UnicodeString ChannelName, System::Json::TJSONValue* const Msg, const int ArgType = 0x1)/* overload */;
	bool __fastcall BroadcastObject(const System::UnicodeString ChannelName, System::TObject* const Msg)/* overload */;
	bool __fastcall BroadcastMessage(const System::UnicodeString ChannelName, const System::UnicodeString CallbackId, System::Json::TJSONValue* const Msg, const int ArgType = 0x1)/* overload */;
	bool __fastcall BroadcastObject(const System::UnicodeString ChannelName, const System::UnicodeString CallbackId, System::TObject* const Msg)/* overload */;
	bool __fastcall NotifyCallback _DEPRECATED_ATTRIBUTE1("ChannelName is no longer required") (const System::UnicodeString ChannelName, const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::Json::TJSONValue* const Msg, /* out */ System::Json::TJSONValue* &Response, unsigned Timeout = (unsigned)(0xffffffff), const int ArgType = 0x1)/* overload */;
	bool __fastcall NotifyObject _DEPRECATED_ATTRIBUTE1("ChannelName is no longer required") (const System::UnicodeString ChannelName, const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::TObject* const Msg, /* out */ System::TObject* &Response, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	bool __fastcall NotifyCallback(const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::Json::TJSONValue* const Msg, /* out */ System::Json::TJSONValue* &Response, unsigned Timeout = (unsigned)(0xffffffff), const int ArgType = 0x1)/* overload */;
	bool __fastcall NotifyObject(const System::UnicodeString ClientId, const System::UnicodeString CallbackId, System::TObject* const Msg, /* out */ System::TObject* &Response, unsigned Timeout = (unsigned)(0xffffffff))/* overload */;
	System::Generics::Collections::TList__1<System::UnicodeString>* __fastcall GetAllChannelNames();
	System::Generics::Collections::TList__1<System::UnicodeString>* __fastcall GetAllChannelCallbackId(const System::UnicodeString ChannelName);
	System::Generics::Collections::TList__1<System::UnicodeString>* __fastcall GetAllChannelClientId(const System::UnicodeString ChannelName);
	Data::Dbxjsonreflect::TJSONMarshal* __fastcall GetJSONMarshaler();
	Data::Dbxjsonreflect::TJSONUnMarshal* __fastcall GetJSONUnMarshaler();
	System::Json::TJSONValue* __fastcall MarshalData(System::TObject* Data);
	System::TObject* __fastcall UnMarshalJSON(System::Json::TJSONValue* Data);
	__property HideDSAdmin;
	
__published:
	__property TDSPrepareEvent OnPrepare = {read=FPrepareEvent, write=FPrepareEvent};
	__property TDSConnectEvent OnConnect = {read=FConnectEvent, write=FConnectEvent};
	__property TDSConnectEvent OnDisconnect = {read=FDisconnectEvent, write=FDisconnectEvent};
	__property TDSErrorEvent OnError = {read=FErrorEvent, write=FErrorEvent};
	__property bool AutoStart = {read=FAutoStart, write=FAutoStart, default=1};
	__property Data::Dbxcommon::TDBXTraceEvent OnTrace = {read=GetTraceInfoEvent, write=SetTraceInfoEvent};
	__property int ChannelQueueSize = {read=FChannelQueueSize, write=FChannelQueueSize, default=100};
	__property int ChannelResponseTimeout = {read=FChannelResponseTimeout, write=FChannelResponseTimeout, default=30000};
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSServerDriver : public Data::Dbxcommon::TDBXDriver
{
	typedef Data::Dbxcommon::TDBXDriver inherited;
	
private:
	Data::Dbxcommon::TDBXCommand* __fastcall CreateServerCommand(Data::Dbxcommon::TDBXContext* DbxContext, Data::Dbxcommon::TDBXConnection* Connection, Data::Dbxcommon::TDBXCommand* MorphicCommand);
	
protected:
	virtual void __fastcall Close();
	virtual Data::Dbxcommon::TDBXConnection* __fastcall CreateConnection(Data::Dbxcommon::TDBXConnectionBuilder* ConnectionBuilder);
	
public:
	__fastcall virtual TDSServerDriver(const Data::Dbxcommon::TDBXDriverDef &DBXDriverDef)/* overload */;
	__fastcall virtual ~TDSServerDriver();
	virtual System::UnicodeString __fastcall GetDriverVersion();
public:
	/* TDBXDriver.Create */ inline __fastcall TDSServerDriver()/* overload */ : Data::Dbxcommon::TDBXDriver() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSServerClass : public Datasnap::Dscommonserver::TDSCustomServerClass
{
	typedef Datasnap::Dscommonserver::TDSCustomServerClass inherited;
	
private:
	TDSGetClassEvent FGetClassEvent;
	TDSCreateInstanceEvent FCreateInstanceEvent;
	TDSDestroyInstanceEvent FDestroyInstanceEvent;
	TDSPrepareEvent FPrepareEvent;
	bool __fastcall IsLifeCycleStored();
	
protected:
	virtual void __fastcall SetServer(Datasnap::Dscommonserver::TDSCustomServer* const AServer);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall CreateInstance(Datasnap::Dscommonserver::TDSCreateInstanceEventObject* const CreateInstanceEventObject);
	virtual void __fastcall DestroyInstance(Datasnap::Dscommonserver::TDSDestroyInstanceEventObject* const DestroyInstanceEventObject);
	virtual void __fastcall Preparing(Datasnap::Dscommonserver::TDSPrepareEventObject* const PrepareEventObject);
	virtual Datasnap::Dsreflect::TDSClass* __fastcall GetDSClass();
	
public:
	__fastcall virtual TDSServerClass(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSServerClass();
	virtual void __fastcall Start();
	virtual void __fastcall Stop();
	
__published:
	__property TDSGetClassEvent OnGetClass = {read=FGetClassEvent, write=FGetClassEvent};
	__property TDSCreateInstanceEvent OnCreateInstance = {read=FCreateInstanceEvent, write=FCreateInstanceEvent};
	__property TDSDestroyInstanceEvent OnDestroyInstance = {read=FDestroyInstanceEvent, write=FDestroyInstanceEvent};
	__property TDSPrepareEvent OnPrepare = {read=FPrepareEvent, write=FPrepareEvent};
	__property Server;
	__property LifeCycle = {stored=IsLifeCycleStored, default=0};
};


#ifndef _WIN64
typedef System::TMetaClass* TServerClassAdapterClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TServerClassAdapterClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TServerClassAdapter : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::TObject* __fastcall CreateInstance(System::TObject* const Instance) = 0 ;
	virtual bool __fastcall IsSupportedAdapterType(System::TObject* const AObj);
	virtual bool __fastcall IsSupportedType(System::TObject* const AObj) = 0 /* overload */;
	virtual bool __fastcall IsSupportedType(const System::TClass AClass) = 0 /* overload */;
	virtual System::Classes::TPersistentClass __fastcall GetType() = 0 ;
	virtual System::Classes::TDataModule* __fastcall GetDataModule(System::TObject* const AObj);
	virtual void __fastcall ClearDataModule(System::TObject* const AObj);
public:
	/* TObject.Create */ inline __fastcall TServerClassAdapter() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TServerClassAdapter() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TServerClassAdapterFactory : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TServerClassAdapterClass>* FAdapterClasses;
	static TServerClassAdapterFactory* AdapterClassRegistry;
	
public:
	__fastcall TServerClassAdapterFactory();
	__fastcall virtual ~TServerClassAdapterFactory();
	__classmethod TServerClassAdapter* __fastcall GetAdapter(const System::UnicodeString AdapterClassName);
	static void __fastcall RegisterAdapterClass(const System::UnicodeString AdapterClassName, const TServerClassAdapterClass AdapterClass);
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
static const System::Word CALLBACK_TIMEOUT = System::Word(0x1388);
extern DELPHI_PACKAGE void __fastcall InternalRemoveCallbackTunnel(TDSServer* AServer, TDSCallbackTunnel* ATunnel);
}	/* namespace Dsserver */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSSERVER)
using namespace Datasnap::Dsserver;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DsserverHPP
