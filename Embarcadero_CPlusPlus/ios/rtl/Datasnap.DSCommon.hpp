// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSCommon.pas' rev: 34.00 (iOS)

#ifndef Datasnap_DscommonHPP
#define Datasnap_DscommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSON.hpp>
#include <Data.DBXJSONReflect.hpp>
#include <Data.DbxDatasnap.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dscommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSCallbackItem;
struct TDSClientChannelEventItem;
class DELPHICLASS TDSClientCallbackChannelManager;
class DELPHICLASS TDSSessionHelper;
class DELPHICLASS TDSServiceException;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TDSCallbackTunnelEventType : unsigned char { TunnelCreate, TunnelClose, TunnelClosedByServer, CallbackAdded, CallbackRemoved };

typedef void __fastcall (__closure *TDSCallbackChannelEvent)(System::TObject* Sender);

class PASCALIMPLEMENTATION TDSCallbackItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FServerChannelName;
	Data::Dbxjson::TDBXCallback* FCallback;
	System::Classes::TStrings* FChannels;
	
public:
	__fastcall TDSCallbackItem(System::UnicodeString ServerChannelName, Data::Dbxjson::TDBXCallback* Callback, System::Classes::TStrings* Channels)/* overload */;
	__fastcall TDSCallbackItem(System::UnicodeString ServerChannelName, Data::Dbxjson::TDBXCallback* Callback, System::UnicodeString Channels)/* overload */;
	__fastcall virtual ~TDSCallbackItem();
	bool __fastcall ListeningOn(System::UnicodeString ChannelName);
	__property System::UnicodeString ServerChannelName = {read=FServerChannelName};
	__property Data::Dbxjson::TDBXCallback* Callback = {read=FCallback};
	__property System::Classes::TStrings* Channels = {read=FChannels};
};


struct DECLSPEC_DRECORD TDSClientChannelEventItem
{
public:
	TDSCallbackTunnelEventType EventType;
	System::UnicodeString TunnelId;
	TDSClientCallbackChannelManager* Tunnel;
	System::UnicodeString TunnelChannelName;
	System::UnicodeString CallbackId;
	TDSCallbackItem* CallbackItem;
};


typedef void __fastcall (__closure *TDSClientChannelManagerEvent)(System::TObject* Sender, const TDSClientChannelEventItem &EventItem);

enum DECLSPEC_DENUM TDSChannelThreadState : unsigned char { ctsStopped, ctsStarted, ctsFailed };

class PASCALIMPLEMENTATION TDSClientCallbackChannelManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
protected:
	typedef void __fastcall (__closure *TDSChannelInvokeEvent)(const System::UnicodeString Id, System::Json::TJSONValue* Data, /* out */ System::Json::TJSONValue* &Response);
	
	typedef void __fastcall (__closure *TDSChannelBroadcastEvent)(System::Json::TJSONValue* Data, System::UnicodeString ChannelName);
	
	__interface DELPHIINTERFACE TParamSetup;
	typedef System::DelphiInterface<TParamSetup> _di_TParamSetup;
	__interface TParamSetup  : public System::IInterface 
	{
		virtual void __fastcall Invoke(Data::Dbxcommon::TDBXParameterList* Params) = 0 ;
	};
	
	__interface DELPHIINTERFACE TDSWorker;
	typedef System::DelphiInterface<TDSWorker> _di_TDSWorker;
	__interface TDSWorker  : public System::IInterface 
	{
		virtual void __fastcall Invoke() = 0 ;
	};
	
	class DELPHICLASS TDSChannelCallback;
	class PASCALIMPLEMENTATION TDSChannelCallback : public Data::Dbxjson::TDBXCallback
	{
		typedef Data::Dbxjson::TDBXCallback inherited;
		
	private:
		TDSClientCallbackChannelManager::TDSChannelInvokeEvent FInvokeEvent;
		TDSClientCallbackChannelManager::TDSChannelInvokeEvent FInvokeObjectEvent;
		TDSClientCallbackChannelManager::TDSChannelBroadcastEvent FBroadcastEvent;
		TDSClientCallbackChannelManager::TDSChannelBroadcastEvent FBroadcastObjectEvent;
		
	public:
		__fastcall TDSChannelCallback(const TDSClientCallbackChannelManager::TDSChannelInvokeEvent InvokeEvent, const TDSClientCallbackChannelManager::TDSChannelInvokeEvent InvokeObjectEvent, const TDSClientCallbackChannelManager::TDSChannelBroadcastEvent BroadcastEvent, const TDSClientCallbackChannelManager::TDSChannelBroadcastEvent BroadcastObjectEvent)/* overload */;
		__fastcall virtual ~TDSChannelCallback();
		virtual System::Json::TJSONValue* __fastcall Execute(System::Json::TJSONValue* const Arg)/* overload */;
	/* Hoisted overloads: */
		
	public:
		inline System::TObject* __fastcall  Execute(System::TObject* Arg){ return Data::Dbxjson::TDBXCallback::Execute(Arg); }
		
	};
	
	
	class DELPHICLASS TDSChannelThread;
	class PASCALIMPLEMENTATION TDSChannelThread : public System::Classes::TThread
	{
		typedef System::Classes::TThread inherited;
		
	private:
		TDSClientCallbackChannelManager::_di_TDSWorker FWorker;
		TDSClientCallbackChannelManager* FManager;
		
	protected:
		virtual void __fastcall Execute();
		
	public:
		__fastcall TDSChannelThread(TDSClientCallbackChannelManager::_di_TDSWorker Worker, TDSClientCallbackChannelManager* Manager);
	public:
		/* TThread.Destroy */ inline __fastcall virtual ~TDSChannelThread() { }
		
	};
	
	
	class DELPHICLASS TDSExecuteThread;
	class PASCALIMPLEMENTATION TDSExecuteThread : public System::Classes::TThread
	{
		typedef System::Classes::TThread inherited;
		
	protected:
		Data::Dbxjson::TDBXCallback* FCallback;
		System::Json::TJSONValue* FData;
		System::Json::TJSONValue* FResponse;
		virtual void __fastcall Execute();
		
	public:
		__fastcall TDSExecuteThread(Data::Dbxjson::TDBXCallback* Callback, System::Json::TJSONValue* Data);
		__fastcall virtual ~TDSExecuteThread();
		__property System::Json::TJSONValue* Response = {read=FResponse};
	};
	
	
	
private:
	System::UnicodeString FSecurityToken;
	System::UnicodeString FDSHostname;
	System::UnicodeString FDSPort;
	System::UnicodeString FDSPath;
	System::UnicodeString FCommunicationProtocol;
	System::UnicodeString FChannelName;
	System::UnicodeString FManagerId;
	System::UnicodeString FConnectionTimeout;
	System::UnicodeString FCommunicationTimeout;
	bool FStopped;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FProxyHost;
	int FProxyPort;
	System::UnicodeString FProxyUsername;
	System::UnicodeString FProxyPassword;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TDSCallbackItem*>* FLocalCallbackRepo;
	
private:
	TDSClientChannelManagerEvent FChannelManagerEvent;
	void __fastcall NotifyChange(TDSCallbackTunnelEventType EventType, const System::UnicodeString CallbackId, TDSCallbackItem* Item);
	
private:
	TDSChannelCallback* FChannelCallback;
	TDSCallbackChannelEvent FOnServerConnectionError;
	TDSCallbackChannelEvent FOnServerConnectionTerminate;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Data::Dbxjsonreflect::TConverterEvent*>* FRegConverters;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,Data::Dbxjsonreflect::TReverterEvent*>* FRegReverters;
	TDSChannelThread* FDSChannelThread;
	System::TObject* FNotifyLock;
	
protected:
	TDSChannelThreadState FState;
	System::UnicodeString FStateError;
	Data::Dbxdatasnap::TDBXDatasnapProperties* __fastcall DBXConnectionProperties(bool NoTimeout = false);
	void __fastcall ExecuteRemote(const System::UnicodeString AClassName, const System::UnicodeString AMethodName, _di_TParamSetup ParamSetup, _di_TParamSetup ParamCheckup, bool NoTimeout = false);
	void __fastcall Broadcast(System::Json::TJSONValue* Data, System::UnicodeString ChannelName);
	void __fastcall BroadcastObject(System::Json::TJSONValue* Data, System::UnicodeString ChannelName);
	HIDESBASE void __fastcall Invoke(const System::UnicodeString Id, System::Json::TJSONValue* Data, /* out */ System::Json::TJSONValue* &Response);
	void __fastcall InvokeObject(const System::UnicodeString Id, System::Json::TJSONValue* Data, /* out */ System::Json::TJSONValue* &Response);
	
public:
	__fastcall virtual TDSClientCallbackChannelManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSClientCallbackChannelManager();
	System::TArray__1<System::UnicodeString> __fastcall GetCallbackIds();
	bool __fastcall GetCallbackItem(const System::UnicodeString CallbackId, /* out */ TDSCallbackItem* &Item);
	bool __fastcall RegisterCallback(const System::UnicodeString CallbackId, Data::Dbxjson::TDBXCallback* const Callback)/* overload */;
	bool __fastcall RegisterCallback(const System::UnicodeString CallbackId, const System::UnicodeString ChannelNames, Data::Dbxjson::TDBXCallback* const Callback)/* overload */;
	bool __fastcall RegisterCallback(const System::UnicodeString ChannelNames, Data::Dbxjson::TDBXNamedCallback* const Callback)/* overload */;
	bool __fastcall RegisterCallback(Data::Dbxjson::TDBXNamedCallback* const Callback)/* overload */;
	bool __fastcall UnregisterCallback(const System::UnicodeString CallbackId);
	bool __fastcall CloseClientChannel();
	bool __fastcall BroadcastToChannel(System::Json::TJSONValue* const Msg, System::UnicodeString ChannelName = System::UnicodeString());
	bool __fastcall BroadcastObjectToChannel(System::TObject* const Msg, System::UnicodeString ChannelName = System::UnicodeString());
	bool __fastcall NotifyCallback(const System::UnicodeString CallbackId, const System::UnicodeString ManagerId, System::Json::TJSONValue* const Msg, /* out */ System::Json::TJSONValue* &Response);
	bool __fastcall NotifyObjectCallback(const System::UnicodeString CallbackId, const System::UnicodeString ManagerId, System::TObject* const Msg, /* out */ System::TObject* &Response);
	Data::Dbxjsonreflect::TJSONMarshal* __fastcall GetJSONMarshaler();
	Data::Dbxjsonreflect::TJSONUnMarshal* __fastcall GetJSONUnMarshaler();
	void __fastcall AddConverter(Data::Dbxjsonreflect::TConverterEvent* event);
	void __fastcall AddReverter(Data::Dbxjsonreflect::TReverterEvent* event);
	System::Json::TJSONValue* __fastcall MarshalData(System::TObject* Data);
	System::TObject* __fastcall UnMarshalJSON(System::Json::TJSONValue* Data);
	TDSClientCallbackChannelManager* __fastcall Copy();
	__property TDSChannelThreadState State = {read=FState, nodefault};
	__property System::UnicodeString StateError = {read=FStateError};
	
__published:
	__property System::UnicodeString DSHostname = {read=FDSHostname, write=FDSHostname};
	__property System::UnicodeString DSPort = {read=FDSPort, write=FDSPort};
	__property System::UnicodeString DSPath = {read=FDSPath, write=FDSPath};
	__property System::UnicodeString CommunicationProtocol = {read=FCommunicationProtocol, write=FCommunicationProtocol};
	__property System::UnicodeString ChannelName = {read=FChannelName, write=FChannelName};
	__property System::UnicodeString ManagerId = {read=FManagerId, write=FManagerId};
	__property TDSCallbackChannelEvent OnServerConnectionError = {read=FOnServerConnectionError, write=FOnServerConnectionError};
	__property TDSCallbackChannelEvent OnServerConnectionTerminate = {read=FOnServerConnectionTerminate, write=FOnServerConnectionTerminate};
	__property System::UnicodeString ConnectionTimeout = {read=FConnectionTimeout, write=FConnectionTimeout};
	__property System::UnicodeString CommunicationTimeout = {read=FCommunicationTimeout, write=FCommunicationTimeout};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString ProxyHost = {read=FProxyHost, write=FProxyHost};
	__property int ProxyPort = {read=FProxyPort, write=FProxyPort, default=8888};
	__property System::UnicodeString ProxyUsername = {read=FProxyUsername, write=FProxyUsername};
	__property System::UnicodeString ProxyPassword = {read=FProxyPassword, write=FProxyPassword};
	__property TDSClientChannelManagerEvent OnChannelStateChange = {read=FChannelManagerEvent, write=FChannelManagerEvent};
};


class PASCALIMPLEMENTATION TDSSessionHelper : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::UnicodeString __fastcall GenerateSessionId();
public:
	/* TObject.Create */ inline __fastcall TDSSessionHelper() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDSSessionHelper() { }
	
};


class PASCALIMPLEMENTATION TDSServiceException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall TDSServiceException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall TDSServiceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall TDSServiceException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall TDSServiceException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSServiceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall TDSServiceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall TDSServiceException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall TDSServiceException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSServiceException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall TDSServiceException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSServiceException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall TDSServiceException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~TDSServiceException() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 ctsStarting = System::Int8(0x3);
}	/* namespace Dscommon */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSCOMMON)
using namespace Datasnap::Dscommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DscommonHPP
