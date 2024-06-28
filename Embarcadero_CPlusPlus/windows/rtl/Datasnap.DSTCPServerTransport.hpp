// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSTCPServerTransport.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DstcpservertransportHPP
#define Datasnap_DstcpservertransportHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <Data.DBXTransport.hpp>
#include <Datasnap.DSAuth.hpp>
#include <Datasnap.DSCommonServer.hpp>
#include <Datasnap.DSTransport.hpp>
#include <Datasnap.DSSession.hpp>
#include <IPPeerAPI.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dstcpservertransport
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSTCPChannel;
struct TDSTCPConnectEventObject;
struct TDSTCPDisconnectEventObject;
class DELPHICLASS TDSTCPServerTransport;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSTCPChannel : public Data::Dbxtransport::TDbxChannel
{
	typedef Data::Dbxtransport::TDbxChannel inherited;
	
private:
	Ippeerapi::_di_IIPContext FContext;
	Data::Dbxtransport::TDBXSocketChannelInfo* FChannelInfo;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FReadBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FReadBuffer;
#endif /* _WIN64 */
	bool FConnectionLost;
	System::UnicodeString FSessionId;
	Datasnap::Dssession::_di_TDSSessionEvent FEventMethod;
	void __fastcall ChannelSessionEvent(System::TObject* Sender, const Datasnap::Dssession::TDSSessionEventType EventType, Datasnap::Dssession::TDSSession* const Session);
	
protected:
	virtual bool __fastcall IsConnectionLost();
	virtual Data::Dbxtransport::TDBXChannelInfo* __fastcall GetChannelInfo();
	
public:
	__fastcall TDSTCPChannel(Ippeerapi::_di_IIPContext AContext);
	__fastcall virtual ~TDSTCPChannel();
	virtual void __fastcall Open();
	virtual void __fastcall Close();
#ifndef _WIN64
	virtual int __fastcall Read(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::DynamicArray<System::Byte> Buffer, const int Offset, const int Count);
#else /* _WIN64 */
	virtual int __fastcall Read(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
	virtual int __fastcall Write(const System::TArray__1<System::Byte> Buffer, const int Offset, const int Count);
#endif /* _WIN64 */
	bool __fastcall EnableKeepAlive(int KeepAliveTime, int KeepAliveInterval = 0x64);
	void __fastcall DisableKeepAlive();
	System::TObject* __fastcall GetConnection();
	__property System::UnicodeString SessionId = {read=FSessionId};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TDSTCPConnectEventObject
{
private:
	System::TObject* FConnection;
	TDSTCPChannel* FChannel;
	
public:
	__fastcall TDSTCPConnectEventObject(System::TObject* AConnection, TDSTCPChannel* AChannel);
	__property System::TObject* Connection = {read=FConnection};
	__property TDSTCPChannel* Channel = {read=FChannel};
	TDSTCPConnectEventObject() {}
};


struct DECLSPEC_DRECORD TDSTCPDisconnectEventObject
{
private:
	System::TObject* FConnection;
	
public:
	__fastcall TDSTCPDisconnectEventObject(System::TObject* AConnection);
	__property System::TObject* Connection = {read=FConnection};
	TDSTCPDisconnectEventObject() {}
};


typedef void __fastcall (__closure *TDSTCPConnectEvent)(const TDSTCPConnectEventObject &Event);

#ifndef _WIN64
typedef void __fastcall (__closure *TDSTCPDisconnectEvent)(TDSTCPDisconnectEventObject Event);
#else /* _WIN64 */
typedef void __fastcall (__closure *TDSTCPDisconnectEvent)(const TDSTCPDisconnectEventObject &Event);
#endif /* _WIN64 */

enum DECLSPEC_DENUM TDSKeepAliveEnablement : unsigned char { kaDefault, kaEnabled, kaDisabled };

class PASCALIMPLEMENTATION TDSTCPServerTransport : public Datasnap::Dscommonserver::TDSServerTransport
{
	typedef Datasnap::Dscommonserver::TDSServerTransport inherited;
	
private:
	int FPort;
	int FMaxThreads;
	int FPoolSize;
	Datasnap::Dstransport::TDSJSONProtocolHandlerFactory* FProtocolHandlerFactory;
	Datasnap::Dsauth::TDSCustomAuthenticationManager* FAuthenticationManager;
	TDSTCPConnectEvent FTDSTCPConnectEvent;
	TDSTCPDisconnectEvent FTDSTCPDisconnectEvent;
	TDSKeepAliveEnablement FKeepAliveEnablement;
	int FKeepAliveTime;
	int FKeepAliveInterval;
	void __fastcall DoOnConnect(Ippeerapi::_di_IIPContext AContext);
	void __fastcall DoOnDisconnect(Ippeerapi::_di_IIPContext AContext);
	void __fastcall DoOnExecute(Ippeerapi::_di_IIPContext AContext);
	
protected:
	Ippeerapi::_di_IIPTCPServer FTcpServer;
	static Data::Dbxtransport::TDbxChannel* __fastcall GetTcpChannel(Datasnap::Dscommonserver::TDSServerConnectionHandler* AConnectionHandler);
	virtual Ippeerapi::_di_IIPTCPServer __fastcall CreateTcpServer();
	virtual Data::Dbxtransport::TDbxChannel* __fastcall CreateTcpChannel(Ippeerapi::_di_IIPContext AContext);
	virtual void __fastcall SetServer(Datasnap::Dscommonserver::TDSCustomServer* const AServer);
	void __fastcall SetAuthenticationManager(Datasnap::Dsauth::TDSCustomAuthenticationManager* const AuthManager);
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	virtual void __fastcall SetIPImplementationID(const System::UnicodeString AIPImplementationID);
	
public:
	__fastcall virtual ~TDSTCPServerTransport();
	__fastcall virtual TDSTCPServerTransport(System::Classes::TComponent* AOwner);
	virtual void __fastcall Start();
	virtual void __fastcall Stop();
	
__published:
	__property int Port = {read=FPort, write=FPort, default=211};
	__property int MaxThreads = {read=FMaxThreads, write=FMaxThreads, default=0};
	__property int PoolSize = {read=FPoolSize, write=FPoolSize, default=10};
	__property Server;
	__property BufferKBSize = {default=32};
	__property Filters;
	__property Datasnap::Dsauth::TDSCustomAuthenticationManager* AuthenticationManager = {read=FAuthenticationManager, write=SetAuthenticationManager};
	__property TDSTCPConnectEvent OnConnect = {read=FTDSTCPConnectEvent, write=FTDSTCPConnectEvent};
	__property TDSTCPDisconnectEvent OnDisconnect = {read=FTDSTCPDisconnectEvent, write=FTDSTCPDisconnectEvent};
	__property TDSKeepAliveEnablement KeepAliveEnablement = {read=FKeepAliveEnablement, write=FKeepAliveEnablement, default=0};
	__property int KeepAliveTime = {read=FKeepAliveTime, write=FKeepAliveTime, default=300000};
	__property int KeepAliveInterval = {read=FKeepAliveInterval, write=FKeepAliveInterval, default=100};
	__property IPImplementationID = {default=0};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dstcpservertransport */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSTCPSERVERTRANSPORT)
using namespace Datasnap::Dstcpservertransport;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DstcpservertransportHPP
