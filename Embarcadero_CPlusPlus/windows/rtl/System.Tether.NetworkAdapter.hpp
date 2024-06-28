// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Tether.NetworkAdapter.pas' rev: 34.00 (Windows)

#ifndef System_Tether_NetworkadapterHPP
#define System_Tether_NetworkadapterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.SyncObjs.hpp>
#include <System.Tether.Manager.hpp>
#include <System.Tether.Comm.hpp>
#include <System.Generics.Collections.hpp>
#include <IPPeerAPI.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Tether
{
namespace Networkadapter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTetheringNetworkManagerCommunicationThread;
class DELPHICLASS TTetheringNetworkManagerCommunicationThread_UDP;
class DELPHICLASS TTetheringNetworkManagerCommunicationThread_Multicast;
class DELPHICLASS TTetheringNetworkAdapterCommon;
class DELPHICLASS TTetheringNetworkAdapterV4_UDP;
class DELPHICLASS TTetheringNetworkAdapterMulticast;
class DELPHICLASS TTetheringNetworkAdapterMulticast_V4;
class DELPHICLASS TTetheringNetworkAdapterMulticast_V6;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkManagerCommunicationThread : public System::Tether::Manager::TTetheringManagerCommunicationThread
{
	typedef System::Tether::Manager::TTetheringManagerCommunicationThread inherited;
	
private:
	#define TTetheringNetworkManagerCommunicationThread_TetheringNewManager L"TetheringNewManager"
	
	#define TTetheringNetworkManagerCommunicationThread_TetheringShutdown L"TetheringShutdown"
	
	#define TTetheringNetworkManagerCommunicationThread_TetheringRemoteConnection L"TetheringRemoteConnection"
	
	Ippeerapi::TIPVersionPeer FIPVersion;
	System::UnicodeString FLastConnection;
	System::Tether::Comm::TTetheringNetworkComm* FClientComm;
	System::UnicodeString FTarget;
#ifndef _WIN64
	System::DynamicArray<Ippeerapi::TIPv4Subnet> FSubnetTable;
#else /* _WIN64 */
	System::TArray__1<Ippeerapi::TIPv4Subnet> FSubnetTable;
#endif /* _WIN64 */
	System::Tether::Comm::TTetheringNetworkServerComm* FServerComm;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Tether::Comm::TTetheringNetworkComm*>* FClientConnections;
	void __fastcall DoOnExecute(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall DoOnConnect(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall DoOnDisconnect(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall PrepareClientConnection(const System::UnicodeString AConnection);
	
protected:
#ifndef _WIN64
	virtual void __fastcall DoOnReceiveData(const System::UnicodeString AConnection, const System::DynamicArray<System::Byte> AData);
#else /* _WIN64 */
	virtual void __fastcall DoOnReceiveData(const System::UnicodeString AConnection, const System::TArray__1<System::Byte> AData);
#endif /* _WIN64 */
	void __fastcall DoOnReceiveException(const System::UnicodeString AMessage, const System::TClass AExceptionClass);
	System::UnicodeString __fastcall MergeConnectionString(const System::UnicodeString AConnectionWithIP, const System::UnicodeString AConnectionWithPort);
	virtual bool __fastcall IsListening();
	virtual bool __fastcall StartListening(const System::UnicodeString ATarget);
	virtual void __fastcall StopListening();
	virtual System::UnicodeString __fastcall GetRemoteConnectionString(const System::UnicodeString AConnection);
	virtual System::UnicodeString __fastcall ProcessResponse(const System::UnicodeString AData, System::UnicodeString &RemoteConnectionString);
	virtual void __fastcall DoSendCommand(const System::UnicodeString AConnection, const System::UnicodeString AData);
	virtual void __fastcall BroadcastCommand(const System::UnicodeString AData, const System::UnicodeString AHost = System::UnicodeString()) = 0 ;
	
public:
	__fastcall TTetheringNetworkManagerCommunicationThread(System::Tether::Manager::TTetheringAdapter* const AnAdapter, Ippeerapi::TIPVersionPeer AIPVersion, const System::UnicodeString ABindToAddress);
	__fastcall virtual ~TTetheringNetworkManagerCommunicationThread();
	virtual void __fastcall Execute();
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkManagerCommunicationThread_UDP : public TTetheringNetworkManagerCommunicationThread
{
	typedef TTetheringNetworkManagerCommunicationThread inherited;
	
private:
	System::Tether::Comm::TTetheringNetworkServerCommUDP* FServerCommUDP;
	
protected:
	virtual bool __fastcall IsListening();
	virtual bool __fastcall StartListening(const System::UnicodeString ATarget);
	virtual void __fastcall StopListening();
	virtual void __fastcall BroadcastCommand(const System::UnicodeString AData, const System::UnicodeString AHost = System::UnicodeString());
	
public:
	__fastcall TTetheringNetworkManagerCommunicationThread_UDP(System::Tether::Manager::TTetheringAdapter* const AnAdapter, Ippeerapi::TIPVersionPeer AIPVersion, const System::UnicodeString ABindToAddress);
	__fastcall virtual ~TTetheringNetworkManagerCommunicationThread_UDP();
};


class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkManagerCommunicationThread_Multicast : public TTetheringNetworkManagerCommunicationThread
{
	typedef TTetheringNetworkManagerCommunicationThread inherited;
	
private:
	System::Tether::Comm::TTetheringNetworkServerCommMulticast* FServerCommMulticast;
	
protected:
	virtual bool __fastcall IsListening();
	virtual bool __fastcall StartListening(const System::UnicodeString ATarget);
	virtual void __fastcall StopListening();
	virtual void __fastcall BroadcastCommand(const System::UnicodeString AData, const System::UnicodeString AHost = System::UnicodeString());
	
public:
	__fastcall TTetheringNetworkManagerCommunicationThread_Multicast(System::Tether::Manager::TTetheringAdapter* const AnAdapter, Ippeerapi::TIPVersionPeer AIPVersion, const System::UnicodeString ABindToAddress);
	__fastcall virtual ~TTetheringNetworkManagerCommunicationThread_Multicast();
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkAdapterCommon : public System::Tether::Manager::TTetheringAdapter
{
	typedef System::Tether::Manager::TTetheringAdapter inherited;
	
public:
	static const System::Word FirstManagerPort = System::Word(0x7e4);
	
	static const System::Word LastManagerPort = System::Word(0x7f7);
	
	static const System::Word FirstAvPort = System::Word(0x7f8);
	
	static const System::Word LastAvPort = System::Word(0x83e);
	
	
private:
	TTetheringNetworkManagerCommunicationThread* FCommunicationThread;
	void __fastcall SendManagerCommand(const System::UnicodeString ATarget, const System::Tether::Manager::TTetheringManagerCommand &ACommand);
	
protected:
	Ippeerapi::TIPVersionPeer FIPVersion;
	virtual bool __fastcall IsIP(const System::UnicodeString ATarget);
	virtual bool __fastcall IsIPRange(const System::UnicodeString ATarget);
	virtual void __fastcall SendManagerCommandToRange(const System::UnicodeString ATarget, const System::Tether::Manager::TTetheringManagerCommand &ACommand);
	virtual unsigned __fastcall GetAutomaticTimeout();
#ifndef _WIN64
	virtual void __fastcall DoDiscoverManagers(unsigned Timeout, const System::DynamicArray<System::UnicodeString> ATargetList, const System::DynamicArray<System::UnicodeString> AProfileGroups, const System::DynamicArray<System::UnicodeString> AProfileTexts);
#else /* _WIN64 */
	virtual void __fastcall DoDiscoverManagers(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList, const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts);
#endif /* _WIN64 */
	virtual void __fastcall DoStopListening();
	
public:
	__fastcall TTetheringNetworkAdapterCommon(Ippeerapi::TIPVersionPeer AIPVersion);
	__fastcall virtual ~TTetheringNetworkAdapterCommon();
	virtual System::Tether::Comm::TTetheringCustomComm* __fastcall GetClientPeer(const System::UnicodeString ProtocolId);
	virtual System::Tether::Comm::TTetheringCustomServerComm* __fastcall GetServerPeer(const System::UnicodeString ProtocolId);
	virtual int __fastcall MaxConnections();
	virtual System::UnicodeString __fastcall GetTargetConnection(const int Port, const int Offset);
	virtual void __fastcall NotifyShutdown();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkAdapterV4_UDP : public TTetheringNetworkAdapterCommon
{
	typedef TTetheringNetworkAdapterCommon inherited;
	
public:
	#define TTetheringNetworkAdapterV4_UDP_AdapterID L"Network"
	
	
protected:
	virtual System::UnicodeString __fastcall GetAdapterType();
	virtual System::Tether::Manager::TTetheringManagerCommunicationThread* __fastcall DoCreateCommunicationThread(System::Tether::Manager::TTetheringAdapter* const AnAdapter, const System::UnicodeString ABindToAddress);
	
public:
	__fastcall TTetheringNetworkAdapterV4_UDP(Ippeerapi::TIPVersionPeer AIPVersion);
	__classmethod virtual System::Tether::Manager::TTetheringAdapter* __fastcall CreateInstance();
public:
	/* TTetheringNetworkAdapterCommon.Destroy */ inline __fastcall virtual ~TTetheringNetworkAdapterV4_UDP() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkAdapterMulticast : public TTetheringNetworkAdapterCommon
{
	typedef TTetheringNetworkAdapterCommon inherited;
	
protected:
	virtual System::Tether::Manager::TTetheringManagerCommunicationThread* __fastcall DoCreateCommunicationThread(System::Tether::Manager::TTetheringAdapter* const AnAdapter, const System::UnicodeString ABindToAddress);
	
public:
	__fastcall TTetheringNetworkAdapterMulticast(Ippeerapi::TIPVersionPeer AIPVersion);
public:
	/* TTetheringNetworkAdapterCommon.Destroy */ inline __fastcall virtual ~TTetheringNetworkAdapterMulticast() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkAdapterMulticast_V4 : public TTetheringNetworkAdapterMulticast
{
	typedef TTetheringNetworkAdapterMulticast inherited;
	
public:
	#define TTetheringNetworkAdapterMulticast_V4_AdapterID L"Network_V4"
	
	
protected:
	virtual System::UnicodeString __fastcall GetAdapterType();
	
public:
	__classmethod virtual System::Tether::Manager::TTetheringAdapter* __fastcall CreateInstance();
public:
	/* TTetheringNetworkAdapterMulticast.Create */ inline __fastcall TTetheringNetworkAdapterMulticast_V4(Ippeerapi::TIPVersionPeer AIPVersion) : TTetheringNetworkAdapterMulticast(AIPVersion) { }
	
public:
	/* TTetheringNetworkAdapterCommon.Destroy */ inline __fastcall virtual ~TTetheringNetworkAdapterMulticast_V4() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringNetworkAdapterMulticast_V6 : public TTetheringNetworkAdapterMulticast
{
	typedef TTetheringNetworkAdapterMulticast inherited;
	
public:
	#define TTetheringNetworkAdapterMulticast_V6_AdapterID L"Network_V6"
	
	
protected:
	virtual bool __fastcall IsIP(const System::UnicodeString ATarget);
	virtual bool __fastcall IsIPRange(const System::UnicodeString ATarget);
	virtual void __fastcall SendManagerCommandToRange(const System::UnicodeString ATarget, const System::Tether::Manager::TTetheringManagerCommand &ACommand);
	virtual System::UnicodeString __fastcall GetAdapterType();
	
public:
	__classmethod virtual System::Tether::Manager::TTetheringAdapter* __fastcall CreateInstance();
public:
	/* TTetheringNetworkAdapterMulticast.Create */ inline __fastcall TTetheringNetworkAdapterMulticast_V6(Ippeerapi::TIPVersionPeer AIPVersion) : TTetheringNetworkAdapterMulticast(AIPVersion) { }
	
public:
	/* TTetheringNetworkAdapterCommon.Destroy */ inline __fastcall virtual ~TTetheringNetworkAdapterMulticast_V6() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Networkadapter */
}	/* namespace Tether */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER_NETWORKADAPTER)
using namespace System::Tether::Networkadapter;
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
#endif	// System_Tether_NetworkadapterHPP
