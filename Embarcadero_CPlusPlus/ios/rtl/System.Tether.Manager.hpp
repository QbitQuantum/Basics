// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Tether.Manager.pas' rev: 34.00 (iOS)

#ifndef System_Tether_ManagerHPP
#define System_Tether_ManagerHPP

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
#include <System.Tether.Comm.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Tether
{
namespace Manager
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ETetheringException;
struct TTetheringAllowedConnection;
struct TTetheringManagerInfo;
struct TTetheringProfileInfo;
class DELPHICLASS TTetheringConnection;
class DELPHICLASS TTetheringManagerInfoList;
class DELPHICLASS TTetheringProfileInfoList;
class DELPHICLASS TTetheringAdapter;
class DELPHICLASS TTetheringAdapters;
struct TTetheringCommand;
class DELPHICLASS TTetheringProtocol;
class DELPHICLASS TTetheringProtocols;
struct TTetheringManagerCommand;
class DELPHICLASS TTetheringManagerCommunicationThread;
class DELPHICLASS TTetheringCustomStorage;
class DELPHICLASS TTetheringManager;
class DELPHICLASS TTetheringProfile;
class DELPHICLASS TTetheringProfiles;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI ETetheringException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETetheringException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETetheringException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETetheringException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETetheringException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETetheringException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETetheringException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETetheringException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETetheringException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETetheringException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETetheringException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETetheringException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETetheringException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETetheringException() { }
	
};


typedef System::UnicodeString TTetheringProfileType;

typedef System::TArray__1<System::UnicodeString> TTetheringProfileTypes;

typedef System::UnicodeString TTetheringProtocolType;

typedef System::TArray__1<System::UnicodeString> TTetheringProtocolTypes;

typedef System::UnicodeString TTetheringAdapterType;

typedef System::TArray__1<System::UnicodeString> TTetheringAdapterTypes;

typedef System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> TTetheringProtocolAdapterType;

typedef System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > TTetheringProtocolAdapterTypes;

typedef System::UnicodeString TTetheringTargetHost;

typedef System::TArray__1<System::UnicodeString> TTetheringTargetHosts;

struct DECLSPEC_DRECORD TTetheringAllowedConnection
{
public:
	System::UnicodeString ProtocolType;
	System::UnicodeString AdapterType;
	System::UnicodeString Connection;
};


typedef System::TArray__1<TTetheringAllowedConnection> TTetheringAllowedConnections;

enum class DECLSPEC_DENUM TTetheringAdapterState : unsigned char { Connected, DiscoveringManagers, DiscoveringProfiles };

struct DECLSPEC_DRECORD TTetheringManagerInfo
{
public:
	System::UnicodeString ManagerIdentifier;
	System::UnicodeString ManagerName;
	System::UnicodeString ManagerText;
	System::UnicodeString ConnectionString;
	System::UnicodeString ManagerAdapters;
	int Version;
	TTetheringAdapter* Adapter;
};


struct DECLSPEC_DRECORD TTetheringProfileInfo
{
public:
	System::UnicodeString ManagerIdentifier;
	System::UnicodeString ProfileIdentifier;
	System::UnicodeString ProfileText;
	System::UnicodeString ProfileGroup;
	System::UnicodeString ProfileType;
	int ProfileVersion;
	System::TArray__1<TTetheringAllowedConnection> AllowedConnections;
	System::UnicodeString __fastcall ToString();
	void __fastcall FromString(const System::UnicodeString AProfileInfoString);
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringConnection : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FConnectionString;
	System::UnicodeString FProtocolType;
	TTetheringProtocol* FProtocol;
	
public:
	__fastcall virtual ~TTetheringConnection();
	TTetheringConnection* __fastcall Clone();
	__property System::UnicodeString ConnectionString = {read=FConnectionString, write=FConnectionString};
	__property System::UnicodeString ProtocolType = {read=FProtocolType, write=FProtocolType};
	__property TTetheringProtocol* Protocol = {read=FProtocol, write=FProtocol};
public:
	/* TObject.Create */ inline __fastcall TTetheringConnection() : System::TObject() { }
	
};


enum class DECLSPEC_DENUM TTetheringError : unsigned char { InitAdapterError };

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringManagerInfoList : public System::Generics::Collections::TList__1<TTetheringManagerInfo>
{
	typedef System::Generics::Collections::TList__1<TTetheringManagerInfo> inherited;
	
public:
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringManagerInfo>.Create */ inline __fastcall TTetheringManagerInfoList()/* overload */ : System::Generics::Collections::TList__1<TTetheringManagerInfo>() { }
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringManagerInfo>.Create */ inline __fastcall TTetheringManagerInfoList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TTetheringManagerInfo> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TTetheringManagerInfo>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringManagerInfo>.Create */ inline __fastcall TTetheringManagerInfoList(System::Generics::Collections::TEnumerable__1<TTetheringManagerInfo>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TTetheringManagerInfo>(Collection) { }
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringManagerInfo>.Destroy */ inline __fastcall virtual ~TTetheringManagerInfoList() { }
	
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringProfileInfoList : public System::Generics::Collections::TList__1<TTetheringProfileInfo>
{
	typedef System::Generics::Collections::TList__1<TTetheringProfileInfo> inherited;
	
public:
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringProfileInfo>.Create */ inline __fastcall TTetheringProfileInfoList()/* overload */ : System::Generics::Collections::TList__1<TTetheringProfileInfo>() { }
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringProfileInfo>.Create */ inline __fastcall TTetheringProfileInfoList(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TTetheringProfileInfo> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TTetheringProfileInfo>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringProfileInfo>.Create */ inline __fastcall TTetheringProfileInfoList(System::Generics::Collections::TEnumerable__1<TTetheringProfileInfo>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TTetheringProfileInfo>(Collection) { }
	/* {System_Generics_Collections}TList<System_Tether_Manager_TTetheringProfileInfo>.Destroy */ inline __fastcall virtual ~TTetheringProfileInfoList() { }
	
};


typedef void __fastcall (__closure *TTetheringAdapterReadEvent)(System::TObject* const Sender, TTetheringConnection* const ASource, const System::TArray__1<System::Byte> AData);

typedef void __fastcall (__closure *TTetheringEndManagersDiscoveryEvent)(System::TObject* const Sender, TTetheringManagerInfoList* const ARemoteManagers);

typedef void __fastcall (__closure *TTetheringEndProfilesDiscoveryEvent)(System::TObject* const Sender, TTetheringProfileInfoList* const ARemoteProfiles);

typedef void __fastcall (__closure *TTetheringRequestManagerPasswordEvent)(System::TObject* const Sender, const System::UnicodeString ARemoteIdentifier, System::UnicodeString &Password);

typedef void __fastcall (__closure *TTetheringManagerPairedEvent)(System::TObject* const Sender, const TTetheringManagerInfo &AManagerInfo);

typedef void __fastcall (__closure *TTetheringErrorAuthEvent)(System::TObject* const Sender, const System::UnicodeString AManagerIdentifier);

typedef void __fastcall (__closure *TTetheringNewManagerEvent)(System::TObject* const Sender, const TTetheringManagerInfo &AManagerInfo);

typedef void __fastcall (__closure *TTetheringUnPairManagerEvent)(System::TObject* const Sender, const TTetheringManagerInfo &AManagerInfo);

typedef void __fastcall (__closure *TTetheringLaunchNotificationEvent)(System::TObject* const Sender, const System::UnicodeString AProfileId, const System::UnicodeString ANotification, const System::UnicodeString Data);

typedef void __fastcall (__closure *TTetheringRemoteManagerShutdownEvent)(System::TObject* const Sender, const System::UnicodeString AManagerIdentifier);

typedef void __fastcall (__closure *TTetheringBeforeConnectEvent)(System::TObject* const Sender, const TTetheringProfileInfo &AProfileInfo, bool &AllowConnect);

typedef void __fastcall (__closure *TTetheringProfileEvent)(System::TObject* const Sender, const TTetheringProfileInfo &AProfileInfo);

typedef void __fastcall (__closure *TTetheringNotifyEvent)(System::TObject* const Sender);

typedef void __fastcall (__closure *TTetheringNotifyErrorEvent)(System::TObject* const Sender, System::TObject* const Data, TTetheringError AError);

typedef void __fastcall (__closure *TTetheringNotifyCommErrorEvent)(System::TObject* const Sender, const TTetheringManagerInfo &AManagerInfo, const TTetheringProfileInfo &AProfileInfo);

typedef void __fastcall (__closure *TTetheringDoLog)(const System::UnicodeString Msg);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringAdapter : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TTetheringLogItem : unsigned char { Manager, Adapter, Protocol, Comm, CommThread, Profile };
	
	
protected:
	typedef System::Set<TTetheringLogItem, _DELPHI_SET_ENUMERATOR(TTetheringLogItem::Manager), _DELPHI_SET_ENUMERATOR(TTetheringLogItem::Profile)> TTetheringLogItems;
	
	class DELPHICLASS TTetheringLog;
	class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringLog : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		static System::Generics::Collections::TQueue__1<System::UnicodeString>* FLogs;
		static TTetheringDoLog FTetheringLog;
		
	private:
		// __classmethod void __fastcall Create@();
		// __classmethod void __fastcall Destroy@();
		
	private:
		__classmethod void __fastcall QueueLog();
		__classmethod void __fastcall DoLog(const System::UnicodeString Msg);
		
	public:
		__classmethod void __fastcall Log(const System::UnicodeString Msg);
		__classmethod void __fastcall RegisterLog(const TTetheringDoLog DoLog);
	public:
		/* TObject.Create */ inline __fastcall TTetheringLog() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TTetheringLog() { }
		
	};
	
	
	
private:
	class DELPHICLASS TThreadTimer;
	class PASCALIMPLEMENTATION DECLSPEC_DRTTI TThreadTimer : public System::Classes::TThread
	{
		typedef System::Classes::TThread inherited;
		
	private:
		unsigned FTimeout;
		TTetheringNotifyEvent FOnTimer;
		System::Syncobjs::TEvent* FEvent;
		bool FCancelled;
		void __fastcall Stop();
		
	public:
		__fastcall TThreadTimer(const TTetheringNotifyEvent AEvent, unsigned Timeout)/* overload */;
		__fastcall virtual ~TThreadTimer();
		virtual void __fastcall Execute();
		void __fastcall Cancel();
		__property bool IsCancelled = {read=FCancelled, nodefault};
	public:
		/* TThread.Create */ inline __fastcall TThreadTimer()/* overload */ : System::Classes::TThread() { }
		/* TThread.Create */ inline __fastcall TThreadTimer(bool CreateSuspended)/* overload */ : System::Classes::TThread(CreateSuspended) { }
		
	};
	
	
	
private:
	TThreadTimer* FTimerManager;
	TTetheringManagerInfoList* FRemoteManagers;
	TTetheringManager* FManager;
	System::Classes::TStringList* __fastcall GetKnownManagers();
	
protected:
	static TTetheringLogItems FLogItems;
	System::UnicodeString FAdapterConnectionString;
	TTetheringManagerCommunicationThread* FCommThread;
	__classmethod void __fastcall Log(const System::UnicodeString Msg);
	
private:
	// __classmethod void __fastcall Create@();
	
protected:
	virtual unsigned __fastcall GetAutomaticTimeout() = 0 ;
	virtual System::UnicodeString __fastcall GetAdapterType() = 0 ;
	void __fastcall AddManagerInfo(const System::UnicodeString AManagerIdentifier, const System::UnicodeString AManagerName, const System::UnicodeString AManagerText, const System::UnicodeString AConnectionString, const System::UnicodeString AManagerAdapters, int AVersion)/* overload */;
	void __fastcall AddManagerInfo(const TTetheringManagerInfo &AManagerInfo)/* overload */;
	virtual void __fastcall EndManagersTimer(System::TObject* const Sender);
	virtual void __fastcall AutoConnectEndManagersTimer(System::TObject* const Sender);
	virtual void __fastcall EndProfilesTimerProc(System::TObject* const Sender);
	virtual void __fastcall DoRequestManagerPassword(const System::UnicodeString ARemoteIdentifier, System::UnicodeString &Password);
	virtual void __fastcall DoPairedToRemote(const System::UnicodeString AManagerIdentifier, const System::UnicodeString AManagerName, const System::UnicodeString AManagerText, const System::UnicodeString AConnectionString, int AVersion);
	virtual void __fastcall DoPairedFromLocal(const System::UnicodeString AManagerIdentifier, const System::UnicodeString AManagerName, const System::UnicodeString AManagerText, const System::UnicodeString AConnectionString, int AVersion);
	virtual void __fastcall DoAuthErrorFromLocal(const System::UnicodeString AManagerIdentifier);
	virtual void __fastcall DoAuthErrorFromRemote(const System::UnicodeString AManagerIdentifier);
	virtual void __fastcall DoLaunchNotification(const System::UnicodeString AProfileId, const System::UnicodeString ANotification, const System::UnicodeString Data);
	virtual void __fastcall DoDiscoverManagers(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList, const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts) = 0 ;
	virtual TTetheringManagerCommunicationThread* __fastcall DoCreateCommunicationThread(TTetheringAdapter* const AnAdapter, const System::UnicodeString ABindToAddress) = 0 ;
	virtual void __fastcall DoStopListening();
	virtual void __fastcall DoNewManager(const TTetheringManagerInfo &AManager);
	virtual void __fastcall DoUnPairManager(const TTetheringManagerInfo &AManager);
	virtual void __fastcall DoRemoteManagerShutdown(const System::UnicodeString AManagerIdentifier);
	void __fastcall SetLocalConnectionString(const System::UnicodeString ALocalConnection);
	virtual __classmethod TTetheringAdapter* __fastcall CreateInstance() = 0 ;
	__property System::Classes::TStringList* KnownManagers = {read=GetKnownManagers};
	System::UnicodeString __fastcall ProfilesInfo();
	System::UnicodeString __fastcall GetRandomString(const int Len = 0xa);
	System::Classes::TThread* __fastcall GenerateTimer(const TTetheringNotifyEvent AEvent, unsigned Timeout);
	virtual void __fastcall StartManagersAutoConnect(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList, const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts)/* overload */;
	void __fastcall StartManagersAutoConnect(const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	System::UnicodeString __fastcall GenerateToken(const System::UnicodeString AManager, const System::UnicodeString Seed);
	void __fastcall SaveTokenFromRemote(const System::UnicodeString AManager, const System::UnicodeString Seed);
	bool __fastcall CheckToken(const System::UnicodeString AManager, const System::UnicodeString Seed, const System::UnicodeString Token);
	bool __fastcall CheckPassword(const System::UnicodeString APassword, const System::UnicodeString Seed);
	void __fastcall SaveTokenFromLocal(const System::UnicodeString AManager, const System::UnicodeString Seed);
	System::UnicodeString __fastcall GetHash(const System::UnicodeString Data);
	
public:
	__fastcall virtual TTetheringAdapter();
	__fastcall virtual ~TTetheringAdapter();
	virtual System::Tether::Comm::TTetheringCustomComm* __fastcall GetClientPeer(const System::UnicodeString ProtocolId) = 0 ;
	virtual System::Tether::Comm::TTetheringCustomServerComm* __fastcall GetServerPeer(const System::UnicodeString ProtocolId) = 0 ;
	virtual void __fastcall PairManager(const TTetheringManagerInfo &ARemoteManager)/* overload */;
	virtual void __fastcall PairManager(const TTetheringManagerInfo &ARemoteManager, int ATimeout)/* overload */;
	virtual void __fastcall UnPairManager(const TTetheringManagerInfo &ARemoteManager);
	virtual void __fastcall SendNotification(const TTetheringManagerInfo &AManager, const System::UnicodeString AProfileId, const System::UnicodeString ANotification, const System::UnicodeString Data);
	virtual void __fastcall NotifyShutdown();
	void __fastcall StartManagersDiscovery(const System::UnicodeString ATarget)/* overload */;
	void __fastcall StartManagersDiscovery(unsigned Timeout, const System::UnicodeString ATarget)/* overload */;
	void __fastcall StartManagersDiscovery(const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	virtual void __fastcall StartManagersDiscovery(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList, const System::TArray__1<System::UnicodeString> AProfileGroups = System::TArray__1<System::UnicodeString>(), const System::TArray__1<System::UnicodeString> AProfileTexts = System::TArray__1<System::UnicodeString>())/* overload */;
	virtual void __fastcall StartProfilesDiscovery(const TTetheringManagerInfo &ARemoteManager, unsigned Timeout);
	void __fastcall CancelManagersDiscovery();
	void __fastcall CancelProfilesDiscovery(const TTetheringManagerInfo &ARemoteManager);
	bool __fastcall StartListening();
	bool __fastcall IsListening();
	void __fastcall StopListening();
	virtual int __fastcall MaxConnections() = 0 ;
	virtual System::UnicodeString __fastcall GetTargetConnection(const int Port, const int Offset) = 0 ;
	__property TTetheringManager* Manager = {read=FManager};
	__property System::UnicodeString AdapterType = {read=GetAdapterType};
	__classmethod void __fastcall RegisterLog(const TTetheringDoLog DoLog);
	__classmethod bool __fastcall IsLoggingItem(TTetheringLogItem ALogItem);
	__classmethod void __fastcall AddLogItem(TTetheringLogItem ALogItem);
	__classmethod void __fastcall RemoveLogItem(TTetheringLogItem ALogItem);
	
private:
	// __classmethod void __fastcall Destroy@();
};


_DECLARE_METACLASS(System::TMetaClass, TTetheringAdapterClass);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringAdapters : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,TTetheringAdapterClass>* FAdapters;
	static System::TArray__1<System::UnicodeString> __fastcall GetAdapterTypes();
	
public:
	__classmethod void __fastcall RegisterAdapter(const TTetheringAdapterClass AnAdapter, const System::UnicodeString AType);
	__classmethod void __fastcall UnRegisterAdapter(const System::UnicodeString AType);
	__classmethod TTetheringAdapter* __fastcall GetAdapterInstance(const System::UnicodeString AType);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	/* static */ __property System::TArray__1<System::UnicodeString> Adapters = {read=GetAdapterTypes};
public:
	/* TObject.Create */ inline __fastcall TTetheringAdapters() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringAdapters() { }
	
};


enum class DECLSPEC_DENUM TTetheringCommandType : unsigned char { Command, SendResponse, CloseConnection, CreateConnection, SendStream, ReadStream, None, SendString, ReadString };

struct DECLSPEC_DRECORD TTetheringCommand
{
private:
	TTetheringCommandType FCommandType;
	System::UnicodeString FCommand;
	System::TArray__1<System::UnicodeString> FParameters;
	System::TObject* FData;
	int FVersion;
	static constexpr System::WideChar CommandSep = (System::WideChar)(0x24);
	
	static constexpr System::Int8 CommandsLength = System::Int8(0xb);
	
	static constexpr System::WideChar ParameterSep = (System::WideChar)(0x23);
	
	
public:
	__fastcall TTetheringCommand(const System::UnicodeString ACommand, int AVersion, const System::UnicodeString *AParameters, const int AParameters_High, System::TObject* const AData)/* overload */;
	__fastcall TTetheringCommand(const System::UnicodeString ACommand, int AVersion, const System::TArray__1<System::UnicodeString> AParameters, System::TObject* const AData)/* overload */;
	__fastcall TTetheringCommand(TTetheringCommandType AType, const System::UnicodeString ACommand, int AVersion, const System::TArray__1<System::UnicodeString> AParameters, System::TObject* const AData)/* overload */;
	__fastcall TTetheringCommand(TTetheringCommandType AType, const System::UnicodeString ACommand, int AVersion, const System::UnicodeString *AParameters, const int AParameters_High, System::TObject* const AData)/* overload */;
	__fastcall TTetheringCommand(const System::UnicodeString ACommand, int AVersion)/* overload */;
	__fastcall TTetheringCommand(const System::TArray__1<System::Byte> RawData)/* overload */;
	System::UnicodeString __fastcall ToString();
	System::TArray__1<System::Byte> __fastcall ToBytes();
	__property TTetheringCommandType CommandType = {read=FCommandType};
	__property System::UnicodeString Command = {read=FCommand};
	__property System::TObject* Data = {read=FData};
	__property System::TArray__1<System::UnicodeString> Parameters = {read=FParameters};
	__property int Version = {read=FVersion};
	TTetheringCommand() {}
};


typedef System::TArray__1<TTetheringCommand> TTetheringCommands;

typedef void __fastcall (__closure *TProtocolCommandEvent)(System::TObject* const Sender, System::Tether::Comm::TTetheringCustomComm* const AConnection, const TTetheringCommand &ACommand, System::TArray__1<TTetheringCommand> &Response);

typedef void __fastcall (__closure *TStreamReceivedEvent)(System::TObject* const Sender, const System::UnicodeString AProfileId, System::Classes::TStream* const AStream, const System::UnicodeString ADescription);

typedef void __fastcall (__closure *TStringReceivedEvent)(System::TObject* const Sender, const System::UnicodeString AProfileId, const System::UnicodeString AString, const System::UnicodeString ADescription);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringProtocol : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TProtocolCommandEvent FOnCommand;
	System::Tether::Comm::TTetheringDataEvent FOnAfterReceiveData;
	System::Tether::Comm::TTetheringDataEvent FOnBeforeSendData;
	System::Tether::Comm::TTetheringStreamEvent FOnAfterReceiveStream;
	System::Tether::Comm::TTetheringStreamEvent FOnBeforeSendStream;
	
protected:
	TTetheringAdapter* FAdapter;
	TTetheringProfile* FProfile;
	void __fastcall DoOnCommand(System::TObject* const Sender, System::Tether::Comm::TTetheringCustomComm* const AConnection, const TTetheringCommand &ACommand, System::TArray__1<TTetheringCommand> &Response);
	virtual System::UnicodeString __fastcall GetProtocolType() = 0 ;
	virtual bool __fastcall GetIsConnected() = 0 ;
	System::UnicodeString __fastcall GenerateToken(const System::UnicodeString AManager, const System::UnicodeString Seed);
	void __fastcall SaveTokenFromRemote(const System::UnicodeString AManager, const System::UnicodeString Seed);
	bool __fastcall CheckToken(const System::UnicodeString AManager, const System::UnicodeString Seed, const System::UnicodeString Token);
	bool __fastcall CheckPassword(const System::UnicodeString APassword, const System::UnicodeString Seed);
	void __fastcall SaveTokenFromLocal(const System::UnicodeString AManager, const System::UnicodeString Seed);
	System::UnicodeString __fastcall GetHash(const System::UnicodeString AValue);
	System::UnicodeString __fastcall GetRandomString(const int Len = 0xa);
	virtual void __fastcall StopCommunication() = 0 ;
	virtual void __fastcall StartCommunication() = 0 ;
	virtual void __fastcall DoSendData(const System::TArray__1<System::Byte> AData) = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall DoReceiveData() = 0 ;
	virtual bool __fastcall DoReceiveStream(System::Classes::TStream* const AStream) = 0 ;
	virtual bool __fastcall DoSendStream(System::Classes::TStream* const AStream) = 0 ;
	
public:
	__fastcall virtual TTetheringProtocol(TTetheringAdapter* const AnAdapter, bool AsClient) = 0 ;
	virtual bool __fastcall Connect(TTetheringConnection* const AProfile) = 0 /* overload */;
	virtual bool __fastcall Connect(TTetheringConnection* const AProfile, int ATimeout) = 0 /* overload */;
	virtual void __fastcall Disconnect() = 0 ;
	void __fastcall SendData(const System::UnicodeString AData)/* overload */;
	void __fastcall SendData(const System::TArray__1<System::Byte> AData)/* overload */;
	System::UnicodeString __fastcall ReceiveStringData();
	System::TArray__1<System::Byte> __fastcall ReceiveData();
	bool __fastcall ReceiveStream(System::Classes::TStream* const AStream);
	bool __fastcall SendStream(System::Classes::TStream* const AStream);
	System::UnicodeString __fastcall ReadStringData _DEPRECATED_ATTRIBUTE1("Use ReceiveStringData") ();
	System::TArray__1<System::Byte> __fastcall ReadData _DEPRECATED_ATTRIBUTE1("Use ReceiveData") ();
	bool __fastcall ReadStream _DEPRECATED_ATTRIBUTE1("Use ReceiveStream") (System::Classes::TStream* const AStream);
	bool __fastcall TransferStream _DEPRECATED_ATTRIBUTE1("Use SendStream") (System::Classes::TStream* const AStream);
	virtual System::UnicodeString __fastcall GetConnectionString(const System::UnicodeString ManagerConnectionString) = 0 ;
	virtual __classmethod TTetheringProtocol* __fastcall CreateInstance(TTetheringAdapter* const AnAdapter, bool AsClient) = 0 ;
	__property System::UnicodeString ProtocolType = {read=GetProtocolType};
	__property bool IsConnected = {read=GetIsConnected, nodefault};
	__property System::Tether::Comm::TTetheringDataEvent OnBeforeSendData = {read=FOnBeforeSendData, write=FOnBeforeSendData};
	__property System::Tether::Comm::TTetheringDataEvent OnAfterReceiveData = {read=FOnAfterReceiveData, write=FOnAfterReceiveData};
	__property System::Tether::Comm::TTetheringStreamEvent OnBeforeSendStream = {read=FOnBeforeSendStream, write=FOnBeforeSendStream};
	__property System::Tether::Comm::TTetheringStreamEvent OnAfterReceiveStream = {read=FOnAfterReceiveStream, write=FOnAfterReceiveStream};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringProtocol() { }
	
};


_DECLARE_METACLASS(System::TMetaClass, TTetheringProtocolClass);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringProtocols : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,TTetheringProtocolClass>* FProtocols;
	static System::TArray__1<System::UnicodeString> __fastcall GetProtocolTypes();
	
public:
	__classmethod void __fastcall RegisterProtocol(const TTetheringProtocolClass AProtocol, const System::UnicodeString AProtocolType);
	__classmethod void __fastcall UnRegisterProtocol(const System::UnicodeString AProtocolType);
	__classmethod TTetheringProtocol* __fastcall GetProtocolInstance(TTetheringProfile* const AProfile, const System::UnicodeString AProtocolType, TTetheringAdapter* const AnAdapter, bool AsClient);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	/* static */ __property System::TArray__1<System::UnicodeString> Protocols = {read=GetProtocolTypes};
public:
	/* TObject.Create */ inline __fastcall TTetheringProtocols() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringProtocols() { }
	
};


typedef System::UnicodeString TTetheringParam;

typedef System::TArray__1<System::UnicodeString> TTetheringParams;

struct DECLSPEC_DRECORD TTetheringManagerCommand
{
private:
	static constexpr System::WideChar EscapePrefix = (System::WideChar)(0x5c);
	
	static constexpr System::Int8 NumStaticParams = System::Int8(0x3);
	
	int __fastcall GetNumParams();
	
public:
	bool ValidCommand;
	System::UnicodeString CommandText;
	System::UnicodeString ConnectionString;
	int Version;
	System::TArray__1<System::UnicodeString> Params;
	static TTetheringManagerCommand __fastcall Create(const System::UnicodeString ACommandText, const System::UnicodeString AConnectionString, int AVersion, const System::TArray__1<System::UnicodeString> AParams);
	__property int NumParams = {read=GetNumParams};
	System::UnicodeString __fastcall ToString();
	void __fastcall DecodeCommand(const System::UnicodeString ACommandString);
	static System::UnicodeString __fastcall EscapeSeparator(const System::UnicodeString AText, const System::WideChar *Separators, const int Separators_High);
	static System::UnicodeString __fastcall UnEscapeSeparator(const System::UnicodeString AText, const System::WideChar *Separators, const int Separators_High);
	static System::UnicodeString __fastcall Join(const System::WideChar ASeparator, const System::TArray__1<System::UnicodeString> AValues);
	static System::TArray__1<System::UnicodeString> __fastcall Split(const System::UnicodeString AString, const System::WideChar ASeparator);
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringManagerCommunicationThread : public System::Classes::TThread
{
	typedef System::Classes::TThread inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TPairingState : unsigned char { Waiting, WaitingPairResponse, Paired, WaitingPassword };
	
	class DELPHICLASS TNetworkInfo;
	class PASCALIMPLEMENTATION DECLSPEC_DRTTI TNetworkInfo : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		TTetheringManagerCommunicationThread::TPairingState State;
		System::UnicodeString RandomString;
		System::Classes::TThread* EndProfilesTimer;
		System::UnicodeString ManagerId;
		int ManagerVersion;
		System::UnicodeString ManagerAdapters;
		__fastcall virtual ~TNetworkInfo();
	public:
		/* TObject.Create */ inline __fastcall TNetworkInfo() : System::TObject() { }
		
	};
	
	
	class DELPHICLASS TCommandQueue;
	class PASCALIMPLEMENTATION DECLSPEC_DRTTI TCommandQueue : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		System::Generics::Collections::TQueue__1<System::UnicodeString>* FQueue;
		System::Syncobjs::TEvent* FEvent;
		
	public:
		__fastcall TCommandQueue();
		__fastcall virtual ~TCommandQueue();
		void __fastcall Enqueue(const System::UnicodeString Acommand);
		System::UnicodeString __fastcall Dequeue();
		int __fastcall Count();
		void __fastcall WaitCommand();
	};
	
	
	
protected:
	#define TTetheringManagerCommunicationThread_TetheringDiscoverManagers u"TetheringDiscoverManagers"
	
	#define TTetheringManagerCommunicationThread_TetheringServerDiscovered u"TetheringServerDiscovered"
	
	#define TTetheringManagerCommunicationThread_TetheringDiscoverProfiles u"TetheringDiscoverProfiles"
	
	#define TTetheringManagerCommunicationThread_TetheringBeginProfiles u"TetheringBeginProfiles"
	
	#define TTetheringManagerCommunicationThread_TetheringEndProfiles u"TetheringEndProfiles"
	
	#define TTetheringManagerCommunicationThread_TetheringRequestPair u"TetheringRequestPair"
	
	#define TTetheringManagerCommunicationThread_TetheringRequestUnPair u"TetheringRequestUnPair"
	
	#define TTetheringManagerCommunicationThread_TetheringRequestPassword u"TetheringRequestPassword"
	
	#define TTetheringManagerCommunicationThread_TetheringPassword u"TetheringPassword"
	
	#define TTetheringManagerCommunicationThread_TetheringPairAccepted u"TetheringPairAccepted"
	
	#define TTetheringManagerCommunicationThread_TetheringPairDenied u"TetheringPairDenied"
	
	#define TTetheringManagerCommunicationThread_TetheringNotification u"TetheringNotification"
	
	#define TTetheringManagerCommunicationThread_TetheringPairingToken u"TetheringPairingToken"
	
	#define TTetheringManagerCommunicationThread_TetheringGeneratedToken u"TetheringGeneratedToken"
	
	#define TTetheringManagerCommunicationThread_EMPTYTOKEN u"EMPTYTOKEN"
	
	#define TTetheringManagerCommunicationThread_TetheringOk u"Ok"
	
	#define TTetheringManagerCommunicationThread_TetheringError u"Error"
	
	#define TTetheringManagerCommunicationThread_TetheringEmpty u""
	
	static constexpr System::WideChar TetheringVersion = (System::WideChar)(0x31);
	
	TCommandQueue* FCommandQueue;
	TTetheringAdapter* FAdapter;
	TTetheringNotifyEvent FNotifyEndProfileDiscovery;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TNetworkInfo*>* FNetworkInfo;
	int FReconnectTimeout;
	System::Syncobjs::TEvent* FEventAdapterSync;
	void __fastcall CommunicationThreadInitialized();
	void __fastcall AddProfiles(const System::UnicodeString AConnectionString, const System::UnicodeString AData);
	virtual bool __fastcall IsListening() = 0 ;
	virtual TPairingState __fastcall GetState(const System::UnicodeString Connection);
	virtual void __fastcall SetState(const System::UnicodeString Connection, TPairingState AState);
	virtual void __fastcall SetManagerId(const System::UnicodeString Connection, const System::UnicodeString AManagerId);
	virtual TNetworkInfo* __fastcall GetNetworkInfo(const System::UnicodeString Connection);
	virtual TNetworkInfo* __fastcall GetNetworkInfoByManager(const System::UnicodeString AManagerId);
	virtual System::UnicodeString __fastcall GenerateRandomString(const System::UnicodeString AConnection);
	virtual System::UnicodeString __fastcall GetRandomString(const System::UnicodeString AConnection);
	TTetheringManagerInfo __fastcall CreateManagerInfo(const System::UnicodeString AIdentifier, const System::UnicodeString AName, const System::UnicodeString AText, const System::UnicodeString AConnectionString, int AVersion);
	void __fastcall CreateDiscoverProfilesTimer(const System::UnicodeString AConnection, unsigned Timeout);
	void __fastcall DestroyDiscoverProfilesTimer(const System::UnicodeString AConnection);
	void __fastcall CancelDiscoverProfilesTimer(const System::UnicodeString AConnection);
	bool __fastcall IsDiscoveringProfiles(const System::UnicodeString AConnection);
	virtual System::UnicodeString __fastcall GetRemoteConnectionString(const System::UnicodeString AConnection);
	virtual System::UnicodeString __fastcall ProcessResponse(const System::UnicodeString AData, System::UnicodeString &RemoteConnectionString);
	virtual void __fastcall DoSendCommand(const System::UnicodeString AConnection, const System::UnicodeString AData) = 0 ;
	__property TTetheringNotifyEvent NotifyEndProfileDiscovery = {read=FNotifyEndProfileDiscovery, write=FNotifyEndProfileDiscovery};
	virtual void __fastcall WaitCommThreadInitialization();
	
public:
	__fastcall virtual TTetheringManagerCommunicationThread(TTetheringAdapter* const AnAdapter);
	__fastcall virtual ~TTetheringManagerCommunicationThread();
	System::UnicodeString __fastcall CommandStr(const System::UnicodeString ACommand, int AVersion, const System::TArray__1<System::UnicodeString> Params);
	void __fastcall SendCommand(const System::UnicodeString AConnection, const System::UnicodeString AData);
	__property int ReconnectTimeout = {read=FReconnectTimeout, write=FReconnectTimeout, default=-1};
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringCustomStorage : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual System::UnicodeString __fastcall LoadManagerGUID() = 0 ;
	virtual void __fastcall SaveManagerGUID(const System::UnicodeString AIdentifier) = 0 ;
	virtual void __fastcall LoadRemoteManagersGUIDs(System::Classes::TStringList* const AGUIDPassList) = 0 ;
	virtual void __fastcall SaveRemoteManagersGUIDs(System::Classes::TStringList* const AGUIDPassList) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TTetheringCustomStorage() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringCustomStorage() { }
	
};


typedef void __fastcall (__closure *TTetheringOnRequestStorage)(System::TObject* const Sender, TTetheringCustomStorage* &AStorage);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringManager : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	TTetheringProfileInfoList* FRemoteProfiles;
	TTetheringManagerInfoList* FRemoteManagers;
	TTetheringManagerInfoList* FRemoteAutoManagers;
	TTetheringManagerInfoList* FPairedManagers;
	TTetheringEndManagersDiscoveryEvent FOnEndManagersDiscovery;
	TTetheringEndProfilesDiscoveryEvent FOnEndProfilesDiscovery;
	System::Classes::TNotifyEvent FOnEndAutoConnect;
	System::Classes::TStringList* FKnownManagers;
	System::UnicodeString FIdentifier;
	System::UnicodeString FText;
	int FVersion;
	System::Generics::Collections::TList__1<TTetheringProfile*>* FRegisteredProfiles;
	System::Generics::Collections::TObjectList__1<TTetheringAdapter*>* FAdapters;
	TTetheringRequestManagerPasswordEvent FOnRequestManagerPassword;
	TTetheringManagerPairedEvent FOnPairedToRemote;
	TTetheringManagerPairedEvent FOnPairedFromLocal;
	TTetheringErrorAuthEvent FOnAuthErrorFromLocal;
	TTetheringErrorAuthEvent FOnAuthErrorFromRemote;
	TTetheringNewManagerEvent FOnNewManager;
	TTetheringUnPairManagerEvent FOnUnPairManager;
	TTetheringRemoteManagerShutdownEvent FOnRemoteManagerShutdown;
	TTetheringOnRequestStorage FOnRequestStorage;
	System::UnicodeString FPassword;
	TTetheringCustomStorage* FStorage;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FTempPasswords;
	bool FAutoConnect;
	bool FEnabled;
	TTetheringNotifyErrorEvent FOnError;
	TTetheringNotifyCommErrorEvent FOnCommError;
	System::TArray__1<System::UnicodeString> FAllowedAdapters;
	bool FSynchronizeEvents;
	System::UnicodeString FBindToAddress;
	bool __fastcall AdapterAllowed(System::UnicodeString AnAdapterType);
	void __fastcall DoEndManagersDiscovery(TTetheringManagerInfoList* const ARemoteManagers);
	void __fastcall DoEndProfilesDiscovery(TTetheringProfileInfoList* const ARemoteProfiles);
	void __fastcall RegisterManagers(TTetheringManagerInfoList* const ARemoteManagers);
	void __fastcall RegisterProfiles(TTetheringProfileInfoList* const ARemoteProfiles);
	void __fastcall DoRequestManagerPassword(const System::UnicodeString ARemoteIdentifier, System::UnicodeString &APassword);
	void __fastcall DoPairedToRemote(const TTetheringManagerInfo &AManagerInfo);
	void __fastcall DoPairedFromLocal(const TTetheringManagerInfo &AManagerInfo);
	void __fastcall DoRequestedNotification(const System::UnicodeString AProfileId, const System::UnicodeString ANotification, const System::UnicodeString Data);
	void __fastcall DoAuthErrorFromLocal(const System::UnicodeString AManagerIdentifier);
	void __fastcall DoAuthErrorFromRemote(const System::UnicodeString AManagerIdentifier);
	void __fastcall DoNewManager(const TTetheringManagerInfo &AManager);
	void __fastcall DoUnPairManager(const TTetheringManagerInfo &AManager);
	void __fastcall DoRemoteManagerShutdown(const System::UnicodeString AManagerIdentifier);
	void __fastcall DoRequestStorage(TTetheringCustomStorage* &AStorage);
	void __fastcall DoEndAutoConnectDiscover(TTetheringManagerInfoList* const ARemoteManagers);
	void __fastcall DisconnetProfilesFromManager(const System::UnicodeString AManagerId);
	bool __fastcall ManagerExists(System::Generics::Collections::TList__1<TTetheringManagerInfo>* const ARemoteManagers, const System::UnicodeString AManagerIdentifier);
	TTetheringManagerInfo __fastcall FindManager(const System::UnicodeString Id)/* overload */;
	TTetheringManagerInfo __fastcall FindManager(const System::UnicodeString Id, TTetheringManagerInfoList* const AList)/* overload */;
	int __fastcall FindAutoManager(const System::UnicodeString AManagerIdentifier);
	void __fastcall AutoCreateAdapters();
	void __fastcall RegisterAdapter(TTetheringAdapter* const AnAdapter);
	void __fastcall UnRegisterAdapter(TTetheringAdapter* const AnAdapter);
	System::Classes::TThread* __fastcall GenerateTimer(const TTetheringNotifyEvent AEvent, unsigned Timeout);
	System::UnicodeString __fastcall GenerateToken(const System::UnicodeString AManager, const System::UnicodeString Seed);
	void __fastcall SaveTokenFromRemote(const System::UnicodeString AManager, const System::UnicodeString Seed);
	bool __fastcall CheckToken(const System::UnicodeString AManager, const System::UnicodeString Seed, const System::UnicodeString Token);
	bool __fastcall CheckPassword(const System::UnicodeString APassword, const System::UnicodeString Seed);
	void __fastcall SaveTokenFromLocal(const System::UnicodeString AManager, const System::UnicodeString Seed);
	void __fastcall SetEnabled(const bool Value);
	System::UnicodeString __fastcall GetAllowedAdapters();
	void __fastcall SetAllowedAdapters(const System::UnicodeString Value);
	void __fastcall AddRemoteAutoManager(const TTetheringManagerInfo &AManagerInfo);
	void __fastcall DeleteRemoteAutoManagers(int AManagerIndex);
	static bool __fastcall IsInArray(const System::UnicodeString AItem, const System::TArray__1<System::UnicodeString> AnArray);
	
protected:
	void __fastcall GetGroupsAndTexts(System::TArray__1<System::UnicodeString> &AProfileGroups, System::TArray__1<System::UnicodeString> &AProfileTexts);
	bool __fastcall IsCompatible(const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts);
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	void __fastcall DoCommError(const TTetheringProfileInfo &AProfile);
	
public:
	__fastcall virtual TTetheringManager(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTetheringManager();
	void __fastcall DiscoverManagers(unsigned Timeout, const System::UnicodeString ATarget = System::UnicodeString())/* overload */;
	void __fastcall DiscoverManagers(const System::UnicodeString ATarget = System::UnicodeString())/* overload */;
	void __fastcall DiscoverManagers(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	void __fastcall DiscoverManagers(const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	void __fastcall DiscoverManagersFiltered(const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts, const System::UnicodeString ATarget = System::UnicodeString())/* overload */;
	void __fastcall DiscoverManagersFiltered(const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts, unsigned Timeout, const System::UnicodeString ATarget = System::UnicodeString())/* overload */;
	void __fastcall DiscoverManagersFiltered(const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts, const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	void __fastcall DiscoverManagersFiltered(const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts, unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	void __fastcall CancelDiscoverManagers();
	void __fastcall PairManager(const TTetheringManagerInfo &ARemoteManager)/* overload */;
	void __fastcall PairManager(const TTetheringManagerInfo &ARemoteManager, int ATimeout)/* overload */;
	void __fastcall UnPairManager(const TTetheringManagerInfo &ARemoteManager)/* overload */;
	void __fastcall UnPairManager(const System::UnicodeString ARemoteManagerIdentifier)/* overload */;
	void __fastcall DiscoverProfiles(const TTetheringManagerInfo &ARemoteManager, unsigned Timeout = (unsigned)(0x1388));
	void __fastcall CancelDiscoverProfiles(const TTetheringManagerInfo &ARemoteManager);
	void __fastcall RegisterProfile(TTetheringProfile* const AProfile);
	void __fastcall UnRegisterProfile(TTetheringProfile* const AProfile);
	TTetheringProfile* __fastcall FindRegisteredProfile(const System::UnicodeString AProfileId);
	void __fastcall SendNotification(const System::UnicodeString AManagerId, const System::UnicodeString AProfileId, const System::UnicodeString ANotification, const System::UnicodeString Data);
	void __fastcall AutoConnect(unsigned Timeout, const System::UnicodeString ATarget = System::UnicodeString())/* overload */;
	void __fastcall AutoConnect(const System::UnicodeString ATarget = System::UnicodeString())/* overload */;
	void __fastcall AutoConnect(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	void __fastcall AutoConnect(const System::TArray__1<System::UnicodeString> ATargetList)/* overload */;
	__classmethod System::UnicodeString __fastcall ProfileInfoToString(const TTetheringProfileInfo &AProfileInfo);
	__classmethod TTetheringProfileInfo __fastcall StringToProfileInfo(const System::UnicodeString AProfileString);
	__property System::Generics::Collections::TObjectList__1<TTetheringAdapter*>* Adapters = {read=FAdapters};
	__property System::UnicodeString Identifier = {read=FIdentifier};
	__property System::Generics::Collections::TList__1<TTetheringProfile*>* RegisteredProfiles = {read=FRegisteredProfiles};
	__property TTetheringManagerInfoList* RemoteManagers = {read=FRemoteManagers};
	__property TTetheringProfileInfoList* RemoteProfiles = {read=FRemoteProfiles};
	__property TTetheringManagerInfoList* PairedManagers = {read=FPairedManagers};
	__property int Version = {read=FVersion, nodefault};
	__property System::UnicodeString BindToAddress = {read=FBindToAddress, write=FBindToAddress};
	
__published:
	__property TTetheringErrorAuthEvent OnAuthErrorFromLocal = {read=FOnAuthErrorFromLocal, write=FOnAuthErrorFromLocal};
	__property TTetheringErrorAuthEvent OnAuthErrorFromRemote = {read=FOnAuthErrorFromRemote, write=FOnAuthErrorFromRemote};
	__property TTetheringEndManagersDiscoveryEvent OnEndManagersDiscovery = {read=FOnEndManagersDiscovery, write=FOnEndManagersDiscovery};
	__property TTetheringEndProfilesDiscoveryEvent OnEndProfilesDiscovery = {read=FOnEndProfilesDiscovery, write=FOnEndProfilesDiscovery};
	__property TTetheringManagerPairedEvent OnPairedFromLocal = {read=FOnPairedFromLocal, write=FOnPairedFromLocal};
	__property TTetheringManagerPairedEvent OnPairedToRemote = {read=FOnPairedToRemote, write=FOnPairedToRemote};
	__property TTetheringRequestManagerPasswordEvent OnRequestManagerPassword = {read=FOnRequestManagerPassword, write=FOnRequestManagerPassword};
	__property TTetheringNewManagerEvent OnNewManager = {read=FOnNewManager, write=FOnNewManager};
	__property TTetheringUnPairManagerEvent OnUnPairManager = {read=FOnUnPairManager, write=FOnUnPairManager};
	__property TTetheringRemoteManagerShutdownEvent OnRemoteManagerShutdown = {read=FOnRemoteManagerShutdown, write=FOnRemoteManagerShutdown};
	__property System::Classes::TNotifyEvent OnEndAutoConnect = {read=FOnEndAutoConnect, write=FOnEndAutoConnect};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property TTetheringOnRequestStorage OnRequestStorage = {read=FOnRequestStorage, write=FOnRequestStorage};
	__property System::UnicodeString Text = {read=FText, write=FText};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property System::UnicodeString AllowedAdapters = {read=GetAllowedAdapters, write=SetAllowedAdapters};
	__property TTetheringNotifyErrorEvent OnError = {read=FOnError, write=FOnError};
	__property TTetheringNotifyCommErrorEvent OnCommError = {read=FOnCommError, write=FOnCommError};
	__property bool SynchronizeEvents = {read=FSynchronizeEvents, write=FSynchronizeEvents, default=1};
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringProfile : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Generics::Collections::TList__1<TTetheringProtocol*>* FProtocols;
	System::UnicodeString FIdentifier;
	System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > FImplementedProtocolAdapters;
	TTetheringManager* FManager;
	TTetheringProfileEvent FOnDisconnect;
	bool FVisible;
	System::UnicodeString FText;
	System::UnicodeString FGroup;
	bool FEnabled;
	System::Tether::Comm::TTetheringDataEvent FOnAfterReceiveData;
	System::Tether::Comm::TTetheringDataEvent FOnBeforeSendData;
	System::Tether::Comm::TTetheringStreamEvent FOnAfterReceiveStream;
	System::Tether::Comm::TTetheringStreamEvent FOnBeforeSendStream;
	TTetheringBeforeConnectEvent FOnBeforeConnectProfile;
	TTetheringProfileEvent FOnAfterConnectProfile;
	bool FSynchronizeEvents;
	void __fastcall SetupProtocols();
	void __fastcall ClearProtocols();
	void __fastcall SetImplementedProtocols(const System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > Value);
	void __fastcall SetManager(TTetheringManager* const AManager);
	void __fastcall SetEnabled(const bool Value);
	
protected:
	System::UnicodeString FProfileType;
	TTetheringProfileInfoList* FConnectedProfiles;
	System::Generics::Collections::TObjectDictionary__2<TTetheringProfileInfo,TTetheringConnection*>* FConnections;
	int FVersion;
	bool __fastcall CheckManager(const System::UnicodeString AManagerID);
	virtual System::UnicodeString __fastcall GetProfileType() = 0 ;
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual bool __fastcall DoOnBeforeConnect(const TTetheringProfileInfo &AProfileInfo);
	virtual void __fastcall DoOnAfterConnect(const TTetheringProfileInfo &AProfileInfo);
	virtual void __fastcall DoOnDisconnect(const TTetheringProfileInfo &AProfileInfo);
	virtual void __fastcall DoOnIncomingData(TTetheringProtocol* const AProtocol, const System::TArray__1<System::Byte> AData) = 0 ;
	virtual void __fastcall OnStreamReceived(System::TObject* const Sender, const System::UnicodeString AProfileId, System::Classes::TStream* const AStream, const System::UnicodeString ADescription) = 0 ;
	virtual void __fastcall OnStringReceived(System::TObject* const Sender, const System::UnicodeString AProfileId, const System::UnicodeString AString, const System::UnicodeString ADescription) = 0 ;
	virtual void __fastcall SetName(const System::Classes::TComponentName NewName);
	virtual void __fastcall AddConnectedProfile(const TTetheringProfileInfo &AProfileInfo);
	virtual void __fastcall DisconnectFromManager(const System::UnicodeString AManagerId) = 0 ;
	virtual bool __fastcall CheckProtocolAdapter(const System::UnicodeString AProtocolType, const System::UnicodeString AnAdapterType);
	virtual TTetheringAdapter* __fastcall GetAdapter(System::UnicodeString AnAdapterType);
	void __fastcall StartCommunication();
	void __fastcall StopCommunication();
	virtual void __fastcall InternalConsistencyCheck();
	bool __fastcall IsProfileConnected(const TTetheringProfileInfo &AProfileInfo);
	void __fastcall CheckProfileIsConnected(const TTetheringProfileInfo &AProfile);
	bool __fastcall FindProfile(const System::UnicodeString AProfileId, TTetheringProfileInfo &AProfileInfo);
	virtual TTetheringConnection* __fastcall FindConnection(const TTetheringProfileInfo &AProfile);
	virtual TTetheringConnection* __fastcall GetConnectionTo(const TTetheringProfileInfo &AProfile, const System::UnicodeString AProtocolType = System::UnicodeString(), const System::UnicodeString AnAdapterType = System::UnicodeString(), bool Connect = true);
	virtual TTetheringCommand __fastcall DoReceiveCommand(TTetheringConnection* const AConnection);
	virtual void __fastcall DoSendCommand(TTetheringConnection* const AConnection, const TTetheringCommand &ACommand);
	virtual TTetheringCommand __fastcall DoSendCommandWithResponse(TTetheringConnection* const AConnection, const TTetheringCommand &ACommand);
	void __fastcall DoCommError(const TTetheringProfileInfo &AProfile);
	virtual TTetheringProfileInfo __fastcall FindProfileFromConnection(TTetheringConnection* const AConnection);
	
public:
	__fastcall virtual TTetheringProfile(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TTetheringProfile();
	virtual __classmethod TTetheringProfile* __fastcall CreateInstance(TTetheringManager* const AOwnerManager) = 0 ;
	virtual bool __fastcall Connect(const TTetheringProfileInfo &AProfile, const System::UnicodeString AProtocolType = System::UnicodeString(), const System::UnicodeString AnAdapterType = System::UnicodeString()) = 0 /* overload */;
	virtual bool __fastcall Connect(const TTetheringProfileInfo &AProfile, int ATimeout, const System::UnicodeString AProtocolType = System::UnicodeString(), const System::UnicodeString AnAdapterType = System::UnicodeString()) = 0 /* overload */;
	virtual void __fastcall Disconnect(const TTetheringProfileInfo &AProfile);
	virtual System::TArray__1<TTetheringProfileInfo> __fastcall GetConnectedProfiles();
	virtual void __fastcall Notify(const System::UnicodeString ANotification, const System::UnicodeString Data) = 0 ;
	virtual __classmethod System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetAllowedProtocolsAdapters() = 0 ;
	__property System::UnicodeString Identifier = {read=FIdentifier};
	__property System::Generics::Collections::TList__1<TTetheringProtocol*>* Protocols = {read=FProtocols};
	__property TTetheringProfileInfoList* ConnectedProfiles = {read=FConnectedProfiles};
	__property int Version = {read=FVersion, nodefault};
	TTetheringCommand __fastcall ReceiveCommand(const TTetheringProfileInfo &AProfile)/* overload */;
	TTetheringCommand __fastcall ReceiveCommand(TTetheringConnection* const AConnection)/* overload */;
	void __fastcall SendCommand(const TTetheringProfileInfo &AProfile, const TTetheringCommand &ACommand)/* overload */;
	void __fastcall SendCommand(TTetheringConnection* const AConnection, const TTetheringCommand &ACommand)/* overload */;
	TTetheringCommand __fastcall SendCommandWithResponse(const TTetheringProfileInfo &AProfile, const TTetheringCommand &ACommand)/* overload */;
	TTetheringCommand __fastcall SendCommandWithResponse(TTetheringConnection* const AConnection, const TTetheringCommand &ACommand)/* overload */;
	
__published:
	__property System::UnicodeString ProfileType = {read=GetProfileType};
	__property System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > ImplementedProtocolAdapters = {read=FImplementedProtocolAdapters, write=SetImplementedProtocols};
	__property TTetheringManager* Manager = {read=FManager, write=SetManager};
	__property System::UnicodeString Text = {read=FText, write=FText};
	__property bool Visible = {read=FVisible, write=FVisible, default=1};
	__property System::UnicodeString Group = {read=FGroup, write=FGroup};
	__property bool Enabled = {read=FEnabled, write=SetEnabled, default=1};
	__property TTetheringProfileEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property TTetheringBeforeConnectEvent OnBeforeConnectProfile = {read=FOnBeforeConnectProfile, write=FOnBeforeConnectProfile};
	__property TTetheringProfileEvent OnAfterConnectProfile = {read=FOnAfterConnectProfile, write=FOnAfterConnectProfile};
	__property System::Tether::Comm::TTetheringDataEvent OnBeforeSendData = {read=FOnBeforeSendData, write=FOnBeforeSendData};
	__property System::Tether::Comm::TTetheringDataEvent OnAfterReceiveData = {read=FOnAfterReceiveData, write=FOnAfterReceiveData};
	__property System::Tether::Comm::TTetheringStreamEvent OnBeforeSendStream = {read=FOnBeforeSendStream, write=FOnBeforeSendStream};
	__property System::Tether::Comm::TTetheringStreamEvent OnAfterReceiveStream = {read=FOnAfterReceiveStream, write=FOnAfterReceiveStream};
	__property bool SynchronizeEvents = {read=FSynchronizeEvents, write=FSynchronizeEvents, default=1};
};


_DECLARE_METACLASS(System::TMetaClass, TTetheringProfileClass);

class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringProfiles : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Generics::Collections::TDictionary__2<System::UnicodeString,TTetheringProfileClass>* FProfiles;
	static System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TList__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> >*>* FProfileProtocolsAdapters;
	static System::TArray__1<System::UnicodeString> __fastcall GetProfiles();
	
public:
	static System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > __fastcall GetProfileProtocolAdapters(const System::UnicodeString AProfileType);
	__classmethod void __fastcall RegisterProfile(const TTetheringProfileClass AProfile, const System::UnicodeString AType);
	__classmethod void __fastcall UnRegisterProfile(const System::UnicodeString AType);
	__classmethod TTetheringProfile* __fastcall GetProfileInstance(const System::UnicodeString AType, TTetheringManager* const AOwnerManager);
	__classmethod void __fastcall RegisterProfileProtocolAdapter(const System::UnicodeString AProfileType, const System::UnicodeString AProtocol, const System::UnicodeString AnAdapter);
	__classmethod void __fastcall UnRegisterProfileProtocolAdapter(const System::UnicodeString AProfileType, const System::UnicodeString AProtocol, const System::UnicodeString AnAdapter);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	/* static */ __property System::TArray__1<System::UnicodeString> Profiles = {read=GetProfiles};
	/* static */ __property System::TArray__1<System::Generics::Collections::TPair__2<System::UnicodeString,System::UnicodeString> > AllowedProtocolAdapters[const System::UnicodeString AProfileType] = {read=GetProfileProtocolAdapters};
public:
	/* TObject.Create */ inline __fastcall TTetheringProfiles() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringProfiles() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Manager */
}	/* namespace Tether */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER_MANAGER)
using namespace System::Tether::Manager;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER)
using namespace System::Tether;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Tether_ManagerHPP
