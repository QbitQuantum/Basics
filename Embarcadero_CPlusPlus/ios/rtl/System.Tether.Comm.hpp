// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Tether.Comm.pas' rev: 34.00 (iOS)

#ifndef System_Tether_CommHPP
#define System_Tether_CommHPP

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
#include <System.Types.hpp>
#include <IPPeerAPI.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Tether
{
namespace Comm
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ETetheringCommException;
class DELPHICLASS TTetheringCustomComm;
class DELPHICLASS TTetheringCustomServerComm;
class DELPHICLASS TTetheringNetworkComm;
class DELPHICLASS TTetheringNetworkServerComm;
class DELPHICLASS TTetheringNetworkServerCommUDP;
class DELPHICLASS TTetheringNetworkServerCommMulticast;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION ETetheringCommException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ETetheringCommException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ETetheringCommException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ETetheringCommException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ETetheringCommException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ETetheringCommException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ETetheringCommException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ETetheringCommException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ETetheringCommException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETetheringCommException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ETetheringCommException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETetheringCommException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ETetheringCommException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ETetheringCommException() { }
	
};


typedef Ippeerapi::TIPVersionPeer TCommIPVersion;

typedef System::TArray__1<System::Byte> __fastcall (__closure *TTetheringDataEvent)(System::TObject* const Sender, const System::TArray__1<System::Byte> ADataBuffer);

typedef void __fastcall (__closure *TTetheringStreamEvent)(System::TObject* const Sender, System::Classes::TStream* const AInputStream, System::Classes::TStream* const AOutputStream);

class PASCALIMPLEMENTATION TTetheringCustomComm : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static constexpr System::Int8 ProtocolSpecificTimeout = System::Int8(-1);
	
	
private:
	TTetheringDataEvent FOnAfterReceiveData;
	TTetheringDataEvent FOnBeforeSendData;
	TTetheringStreamEvent FOnAfterReceiveStream;
	TTetheringStreamEvent FOnBeforeSendStream;
	
protected:
	bool FSecured;
	System::UnicodeString FTarget;
	virtual bool __fastcall DoConnect(const System::UnicodeString ATarget, int ATimeout) = 0 ;
	virtual void __fastcall DoDisconnect() = 0 ;
	virtual bool __fastcall GetConnected() = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall DoReadData() = 0 ;
	virtual void __fastcall DoWriteData(const System::TArray__1<System::Byte> AData) = 0 ;
	virtual void __fastcall DoReadStream(System::Classes::TStream* const AStream) = 0 ;
	virtual void __fastcall DoWriteStream(System::Classes::TStream* const AStream) = 0 ;
	
public:
	bool __fastcall Connect(const System::UnicodeString ATarget)/* overload */;
	bool __fastcall Connect(const System::UnicodeString ATarget, int ATimeout)/* overload */;
	bool __fastcall ReConnect();
	void __fastcall Disconnect();
	System::TArray__1<System::Byte> __fastcall ReadData();
	void __fastcall WriteData(const System::TArray__1<System::Byte> AData);
	void __fastcall ReadStream(System::Classes::TStream* const AStream);
	void __fastcall WriteStream(System::Classes::TStream* const AStream);
	__property bool Connected = {read=GetConnected, nodefault};
	__property bool Secured = {read=FSecured, write=FSecured, default=0};
	__property TTetheringDataEvent OnBeforeSendData = {read=FOnBeforeSendData, write=FOnBeforeSendData};
	__property TTetheringDataEvent OnAfterReceiveData = {read=FOnAfterReceiveData, write=FOnAfterReceiveData};
	__property TTetheringStreamEvent OnBeforeSendStream = {read=FOnBeforeSendStream, write=FOnBeforeSendStream};
	__property TTetheringStreamEvent OnAfterReceiveStream = {read=FOnAfterReceiveStream, write=FOnAfterReceiveStream};
public:
	/* TObject.Create */ inline __fastcall TTetheringCustomComm() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringCustomComm() { }
	
};


typedef void __fastcall (__closure *TServerCommExecuteEvent)(TTetheringCustomComm* const AConnection);

typedef void __fastcall (__closure *TServerCommConnectEvent)(TTetheringCustomComm* const AConnection);

typedef void __fastcall (__closure *TServerCommDisconnectEvent)(TTetheringCustomComm* const AConnection);

class PASCALIMPLEMENTATION TTetheringCustomServerComm : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TTetheringDataEvent FOnAfterReceiveData;
	TTetheringDataEvent FOnBeforeSendData;
	TTetheringStreamEvent FOnAfterReceiveStream;
	TTetheringStreamEvent FOnBeforeSendStream;
	
protected:
	System::UnicodeString FTarget;
	bool FActive;
	bool FSecured;
	TServerCommExecuteEvent FOnExecute;
	TServerCommConnectEvent FOnConnect;
	TServerCommDisconnectEvent FOnDisconnect;
	virtual bool __fastcall DoStartServer() = 0 ;
	virtual void __fastcall DoStopServer() = 0 ;
	virtual void __fastcall SetTarget(const System::UnicodeString Value);
	virtual void __fastcall DoOnExecute(TTetheringCustomComm* const AConnection);
	virtual void __fastcall DoOnConnect(TTetheringCustomComm* const AConnection);
	virtual void __fastcall DoOnDisconnect(TTetheringCustomComm* const AConnection);
	
public:
	bool __fastcall StartServer();
	void __fastcall StopServer();
	__property System::UnicodeString Target = {read=FTarget, write=SetTarget};
	__property bool Active = {read=FActive, nodefault};
	__property bool Secured = {read=FSecured, write=FSecured, default=0};
	__property TServerCommExecuteEvent OnExecute = {read=FOnExecute, write=FOnExecute};
	__property TServerCommConnectEvent OnConnect = {read=FOnConnect, write=FOnConnect};
	__property TServerCommDisconnectEvent OnDisconnect = {read=FOnDisconnect, write=FOnDisconnect};
	__property TTetheringDataEvent OnBeforeSendData = {read=FOnBeforeSendData, write=FOnBeforeSendData};
	__property TTetheringDataEvent OnAfterReceiveData = {read=FOnAfterReceiveData, write=FOnAfterReceiveData};
	__property TTetheringStreamEvent OnBeforeSendStream = {read=FOnBeforeSendStream, write=FOnBeforeSendStream};
	__property TTetheringStreamEvent OnAfterReceiveStream = {read=FOnAfterReceiveStream, write=FOnAfterReceiveStream};
public:
	/* TObject.Create */ inline __fastcall TTetheringCustomServerComm() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TTetheringCustomServerComm() { }
	
};


typedef void __fastcall (__closure *TNetworkCommUDPData)(const System::UnicodeString AConnectionString, const System::TArray__1<System::Byte> AData);

typedef void __fastcall (__closure *TNetworkCommUDPException)(const System::UnicodeString AMessage, const System::TClass AExceptionClass);

typedef void __fastcall (__closure *TNetworkCommMulticastData)(const System::UnicodeString AConnectionString, const System::TArray__1<System::Byte> AData);

class PASCALIMPLEMENTATION TTetheringNetworkComm : public TTetheringCustomComm
{
	typedef TTetheringCustomComm inherited;
	
private:
	static constexpr System::Byte ReadTimeout = System::Byte(0xc8);
	
	
protected:
	Ippeerapi::TIPVersionPeer FIPVersion;
	Ippeerapi::_di_IIPTCPClient FTCPClient;
	Ippeerapi::_di_IIPIOHandler FIOHandler;
	System::UnicodeString FRemoteConnectionString;
	virtual bool __fastcall DoConnect(const System::UnicodeString ATarget, int ATimeout);
	virtual void __fastcall DoDisconnect();
	virtual bool __fastcall GetConnected();
	virtual System::TArray__1<System::Byte> __fastcall DoReadData();
	virtual void __fastcall DoWriteData(const System::TArray__1<System::Byte> AData);
	virtual void __fastcall DoReadStream(System::Classes::TStream* const AStream);
	virtual void __fastcall DoWriteStream(System::Classes::TStream* const AStream);
	
public:
	__fastcall TTetheringNetworkComm(const Ippeerapi::_di_IIPIOHandler AIOHandler, const System::UnicodeString ARemoteConnectionString, Ippeerapi::TIPVersionPeer AIPVersion);
	__fastcall virtual ~TTetheringNetworkComm();
	__property System::UnicodeString RemoteConnectionString = {read=FRemoteConnectionString};
};


class PASCALIMPLEMENTATION TTetheringNetworkServerComm : public TTetheringCustomServerComm
{
	typedef TTetheringCustomServerComm inherited;
	
private:
	Ippeerapi::TIPVersionPeer FIPVersion;
	Ippeerapi::_di_IIPTCPServer FTCPServer;
	System::Generics::Collections::TObjectDictionary__2<Ippeerapi::_di_IIPContext,TTetheringNetworkComm*>* FContexts;
	Ippeerapi::_di_IIPSocketHandle FSocket;
	TTetheringNetworkComm* __fastcall GetComm(const Ippeerapi::_di_IIPContext AContext);
	void __fastcall DoOnExecuteServer(Ippeerapi::_di_IIPContext AContext);
	void __fastcall DoOnConnectServer(Ippeerapi::_di_IIPContext AContext);
	void __fastcall DoOnDisconnectServer(Ippeerapi::_di_IIPContext AContext);
	
protected:
	virtual void __fastcall SetTarget(const System::UnicodeString Value);
	virtual bool __fastcall DoStartServer();
	virtual void __fastcall DoStopServer();
	
public:
	__fastcall TTetheringNetworkServerComm(Ippeerapi::TIPVersionPeer AIPVersion);
	__fastcall virtual ~TTetheringNetworkServerComm();
};


class PASCALIMPLEMENTATION TTetheringNetworkServerCommUDP : public TTetheringCustomServerComm
{
	typedef TTetheringCustomServerComm inherited;
	
private:
	Ippeerapi::TIPVersionPeer FIPVersion;
	Ippeerapi::_di_IIPUDPServer FUDPServer;
	Ippeerapi::_di_IIPSocketHandle FSocketUDP;
	TNetworkCommUDPData FOnUDPData;
	TNetworkCommUDPException FOnUDPException;
	void __fastcall DoUDPException(Ippeerapi::_di_IIPUDPListenerThread AThread, Ippeerapi::_di_IIPSocketHandle ABinding, const System::UnicodeString AMessage, const System::TClass AExceptionClass);
	void __fastcall DoUDPRead(Ippeerapi::_di_IIPUDPListenerThread AThread, const System::TArray__1<System::Byte> AData, Ippeerapi::_di_IIPSocketHandle ABinding);
	int __fastcall GetUDPPort();
	
protected:
	virtual void __fastcall SetTarget(const System::UnicodeString Value);
	virtual bool __fastcall DoStartServer();
	virtual void __fastcall DoStopServer();
	
public:
	void __fastcall BroadcastData(const System::TArray__1<System::Byte> AData, const System::UnicodeString AHost, int InitialPort, int FinalPort);
	__fastcall TTetheringNetworkServerCommUDP(Ippeerapi::TIPVersionPeer AIPVersion, const System::UnicodeString ABindToAddress);
	__fastcall virtual ~TTetheringNetworkServerCommUDP();
	__property int UDPPort = {read=GetUDPPort, nodefault};
	__property TNetworkCommUDPData OnUDPData = {read=FOnUDPData, write=FOnUDPData};
	__property TNetworkCommUDPException OnUDPException = {read=FOnUDPException, write=FOnUDPException};
};


class PASCALIMPLEMENTATION TTetheringNetworkServerCommMulticast : public TTetheringCustomServerComm
{
	typedef TTetheringCustomServerComm inherited;
	
	
private:
	typedef System::StaticArray<System::UnicodeString, 2> _TTetheringNetworkServerCommMulticast__1;
	
	
private:
	static _TTetheringNetworkServerCommMulticast__1 TetheringMulticastGroup;
	Ippeerapi::TIPVersionPeer FIPVersion;
	Ippeerapi::_di_IIPMulticastServer FMulticastServer;
	Ippeerapi::_di_IIPMulticastClient FMulticastClient;
	TNetworkCommMulticastData FOnMulticastData;
	void __fastcall DoMulticastRead(System::TObject* Sender, const System::TArray__1<System::Byte> AData, const Ippeerapi::_di_IIPSocketHandle ABinding);
	int __fastcall GetMulticastPort();
	
protected:
	virtual void __fastcall SetTarget(const System::UnicodeString Value);
	virtual bool __fastcall DoStartServer();
	virtual void __fastcall DoStopServer();
	
public:
	void __fastcall MulticastData(const System::TArray__1<System::Byte> AData, const System::UnicodeString AHost, int InitialPort, int FinalPort);
	__fastcall TTetheringNetworkServerCommMulticast(Ippeerapi::TIPVersionPeer AIPVersion);
	__fastcall virtual ~TTetheringNetworkServerCommMulticast();
	__property int MulticastPort = {read=GetMulticastPort, nodefault};
	__property TNetworkCommMulticastData OnMulticastData = {read=FOnMulticastData, write=FOnMulticastData};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Comm */
}	/* namespace Tether */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_TETHER_COMM)
using namespace System::Tether::Comm;
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
#endif	// System_Tether_CommHPP
