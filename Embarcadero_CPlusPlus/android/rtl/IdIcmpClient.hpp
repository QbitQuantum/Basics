// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdIcmpClient.pas' rev: 34.00 (Android)

#ifndef IdicmpclientHPP
#define IdicmpclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdGlobal.hpp>
#include <IdRawBase.hpp>
#include <IdRawClient.hpp>
#include <IdStackConsts.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idicmpclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TReplyStatus;
class DELPHICLASS TIdCustomIcmpClient;
class DELPHICLASS TIdIcmpClient;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TReplyStatusTypes : unsigned char { rsEcho, rsError, rsTimeOut, rsErrorUnreachable, rsErrorTTLExceeded, rsErrorPacketTooBig, rsErrorParameter, rsErrorDatagramConversion, rsErrorSecurityFailure, rsSourceQuench, rsRedirect, rsTimeStamp, rsInfoRequest, rsAddressMaskRequest, rsTraceRoute, rsMobileHostReg, rsMobileHostRedir, rsIPv6WhereAreYou, rsIPv6IAmHere, rsSKIP };

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TReplyStatus : public System::TObject
{
	typedef System::TObject inherited;
	
protected:
	int FBytesReceived;
	System::UnicodeString FFromIpAddress;
	System::UnicodeString FToIpAddress;
	System::Byte FMsgType;
	System::Byte FMsgCode;
	System::Word FSequenceId;
	unsigned FMsRoundTripTime;
	System::Byte FTimeToLive;
	TReplyStatusTypes FReplyStatusType;
	int FPacketNumber;
	System::UnicodeString FHostName;
	System::UnicodeString FMsg;
	System::UnicodeString FRedirectTo;
	
public:
	__property System::UnicodeString RedirectTo = {read=FRedirectTo, write=FRedirectTo};
	__property System::UnicodeString Msg = {read=FMsg, write=FMsg};
	__property int BytesReceived = {read=FBytesReceived, write=FBytesReceived, nodefault};
	__property System::UnicodeString FromIpAddress = {read=FFromIpAddress, write=FFromIpAddress};
	__property System::UnicodeString ToIpAddress = {read=FToIpAddress, write=FToIpAddress};
	__property System::Byte MsgType = {read=FMsgType, write=FMsgType, nodefault};
	__property System::Byte MsgCode = {read=FMsgCode, write=FMsgCode, nodefault};
	__property System::Word SequenceId = {read=FSequenceId, write=FSequenceId, nodefault};
	__property unsigned MsRoundTripTime = {read=FMsRoundTripTime, write=FMsRoundTripTime, nodefault};
	__property System::Byte TimeToLive = {read=FTimeToLive, write=FTimeToLive, nodefault};
	__property TReplyStatusTypes ReplyStatusType = {read=FReplyStatusType, write=FReplyStatusType, nodefault};
	__property System::UnicodeString HostName = {read=FHostName, write=FHostName};
	__property int PacketNumber = {read=FPacketNumber, write=FPacketNumber, nodefault};
public:
	/* TObject.Create */ inline __fastcall TReplyStatus() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TReplyStatus() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void __fastcall (__closure *TOnReplyEvent)(System::Classes::TComponent* ASender, TReplyStatus* const AReplyStatus);

class PASCALIMPLEMENTATION TIdCustomIcmpClient : public Idrawclient::TIdRawClient
{
	typedef Idrawclient::TIdRawClient inherited;
	
protected:
	unsigned __int64 FStartTime;
	int FPacketSize;
	Idglobal::TIdBytes FBufReceive;
	Idglobal::TIdBytes FBufIcmp;
	System::Word wSeqNo;
	int iDataSize;
	TReplyStatus* FReplyStatus;
	TOnReplyEvent FOnReply;
	System::UnicodeString FReplydata;
	bool __fastcall DecodeIPv6Packet(unsigned BytesRead);
	bool __fastcall DecodeIPv4Packet(unsigned BytesRead);
	bool __fastcall DecodeResponse(unsigned BytesRead);
	virtual void __fastcall DoReply();
	void __fastcall GetEchoReply();
	virtual void __fastcall InitComponent();
	void __fastcall PrepareEchoRequestIPv6(const System::UnicodeString ABuffer);
	void __fastcall PrepareEchoRequestIPv4(const System::UnicodeString ABuffer);
	void __fastcall PrepareEchoRequest(const System::UnicodeString ABuffer);
	void __fastcall SendEchoRequest()/* overload */;
	void __fastcall SendEchoRequest(const System::UnicodeString AIP)/* overload */;
	int __fastcall GetPacketSize();
	void __fastcall SetPacketSize(const int AValue);
	void __fastcall InternalPing(const System::UnicodeString AIP, const System::UnicodeString ABuffer = System::UnicodeString(), System::Word SequenceID = (System::Word)(0x0))/* overload */;
	__property int PacketSize = {read=GetPacketSize, write=SetPacketSize, default=32};
	__property System::UnicodeString ReplyData = {read=FReplydata};
	__property TReplyStatus* ReplyStatus = {read=FReplyStatus};
	__property TOnReplyEvent OnReply = {read=FOnReply, write=FOnReply};
	
public:
	__fastcall virtual ~TIdCustomIcmpClient();
	virtual void __fastcall Send(const System::UnicodeString AHost, const System::Word APort, const Idglobal::TIdBytes ABuffer)/* overload */;
	virtual void __fastcall Send(const Idglobal::TIdBytes ABuffer)/* overload */;
	TReplyStatus* __fastcall Receive(int ATimeOut);
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdCustomIcmpClient(System::Classes::TComponent* AOwner)/* overload */ : Idrawclient::TIdRawClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdCustomIcmpClient()/* overload */ : Idrawclient::TIdRawClient() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Send(const System::UnicodeString AData, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding()){ Idrawbase::TIdRawBase::Send(AData, AByteEncoding); }
	inline void __fastcall  Send(const System::UnicodeString AHost, const System::Word APort, const System::UnicodeString AData, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding()){ Idrawbase::TIdRawBase::Send(AHost, APort, AData, AByteEncoding); }
	
};


class PASCALIMPLEMENTATION TIdIcmpClient : public TIdCustomIcmpClient
{
	typedef TIdCustomIcmpClient inherited;
	
public:
	void __fastcall Ping(const System::UnicodeString ABuffer = System::UnicodeString(), System::Word SequenceID = (System::Word)(0x0));
	__property ReplyData = {default=0};
	__property ReplyStatus;
	
__published:
	__property Host = {default=0};
	__property IPVersion = {default=0};
	__property PacketSize = {default=32};
	__property ReceiveTimeout = {default=5000};
	__property OnReply;
public:
	/* TIdCustomIcmpClient.Destroy */ inline __fastcall virtual ~TIdIcmpClient() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdIcmpClient(System::Classes::TComponent* AOwner)/* overload */ : TIdCustomIcmpClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdIcmpClient()/* overload */ : TIdCustomIcmpClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 DEF_PACKET_SIZE = System::Int8(0x20);
static constexpr System::Word MAX_PACKET_SIZE = System::Word(0x400);
static constexpr System::Word Id_TIDICMP_ReceiveTimeout = System::Word(0x1388);
}	/* namespace Idicmpclient */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDICMPCLIENT)
using namespace Idicmpclient;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdicmpclientHPP
