// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Tether.BluetoothAdapter.pas' rev: 34.00 (Android)

#ifndef System_Tether_BluetoothadapterHPP
#define System_Tether_BluetoothadapterHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SyncObjs.hpp>
#include <System.Tether.Manager.hpp>
#include <System.Tether.Comm.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Tether
{
namespace Bluetoothadapter
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TTetheringBluetoothManagerCommunicationThread;
class DELPHICLASS TTetheringBluetoothAdapter;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringBluetoothManagerCommunicationThread : public System::Tether::Manager::TTetheringManagerCommunicationThread
{
	typedef System::Tether::Manager::TTetheringManagerCommunicationThread inherited;
	
private:
	static GUID TTetheringBTBaseUUID;
	static constexpr System::Int8 MAXCONNECTIONS = System::Int8(0xa);
	
	System::Tether::Comm::TTetheringBTServerComm* FServerComm;
	System::Tether::Comm::TTetheringBTComm* FClientComm;
	System::UnicodeString FLastConnection;
	void __fastcall DoOnExecute(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall DoOnConnect(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	void __fastcall DoOnDisconnect(System::Tether::Comm::TTetheringCustomComm* const AConnection);
	
protected:
	virtual System::UnicodeString __fastcall ProcessResponse(const System::UnicodeString AData, System::UnicodeString &RemoteConnectionString);
	virtual void __fastcall DoSendCommand(const System::UnicodeString AConnection, const System::UnicodeString AData);
	virtual bool __fastcall IsListening();
	
public:
	__fastcall virtual TTetheringBluetoothManagerCommunicationThread(System::Tether::Manager::TTetheringAdapter* const AnAdapter);
	__fastcall virtual ~TTetheringBluetoothManagerCommunicationThread();
	virtual void __fastcall Execute();
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TTetheringBluetoothAdapter : public System::Tether::Manager::TTetheringAdapter
{
	typedef System::Tether::Manager::TTetheringAdapter inherited;
	
public:
	static constexpr System::Int8 MaxBluetoothConnections = System::Int8(0x6);
	
	#define TTetheringBluetoothAdapter_AdapterID u"Bluetooth"
	
	
private:
	TTetheringBluetoothManagerCommunicationThread* FCommunicationThread;
	
protected:
	virtual unsigned __fastcall GetAutomaticTimeout();
	virtual void __fastcall DoDiscoverManagers(unsigned Timeout, const System::TArray__1<System::UnicodeString> ATargetList, const System::TArray__1<System::UnicodeString> AProfileGroups, const System::TArray__1<System::UnicodeString> AProfileTexts);
	virtual System::UnicodeString __fastcall GetAdapterType();
	virtual System::Tether::Manager::TTetheringManagerCommunicationThread* __fastcall DoCreateCommunicationThread(System::Tether::Manager::TTetheringAdapter* const AnAdapter, const System::UnicodeString ABindToAddress);
	virtual void __fastcall DoStopListening();
	
public:
	__fastcall virtual TTetheringBluetoothAdapter();
	__fastcall virtual ~TTetheringBluetoothAdapter();
	__classmethod virtual System::Tether::Manager::TTetheringAdapter* __fastcall CreateInstance();
	virtual System::Tether::Comm::TTetheringCustomComm* __fastcall GetClientPeer(const System::UnicodeString ProtocolId);
	virtual System::Tether::Comm::TTetheringCustomServerComm* __fastcall GetServerPeer(const System::UnicodeString ProtocolId);
	virtual int __fastcall MaxConnections();
	virtual System::UnicodeString __fastcall GetTargetConnection(const int Port, const int Offset);
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Bluetoothadapter */
}	/* namespace Tether */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER_BLUETOOTHADAPTER)
using namespace System::Tether::Bluetoothadapter;
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
#endif	// System_Tether_BluetoothadapterHPP
