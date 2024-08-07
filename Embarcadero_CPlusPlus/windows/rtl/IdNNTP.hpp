﻿// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdNNTP.pas' rev: 34.00 (Windows)

#ifndef IdnntpHPP
#define IdnntpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdException.hpp>
#include <IdGlobal.hpp>
#include <IdMessage.hpp>
#include <IdMessageClient.hpp>
#include <IdReplyRFC.hpp>
#include <IdTCPServer.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPClient.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idnntp
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdNNTP;
class DELPHICLASS EIdNNTPException;
class DELPHICLASS EIdNNTPNoOnNewGroupsList;
class DELPHICLASS EIdNNTPNoOnNewNewsList;
class DELPHICLASS EIdNNTPNoOnNewsgroupList;
class DELPHICLASS EIdNNTPNoOnXHDREntry;
class DELPHICLASS EIdNNTPNoOnXOVER;
class DELPHICLASS EIdNNTPStringListNotInitialized;
class DELPHICLASS EIdNNTPConnectionRefused;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdModeType : unsigned char { mtStream, mtIHAVE, mtReader };

enum DECLSPEC_DENUM TIdNNTPPermission : unsigned char { crCanPost, crNoPost, crAuthRequired, crTempUnavailable };

enum DECLSPEC_DENUM TIdModeSetResult : unsigned char { mrCanStream, mrNoStream, mrCanIHAVE, mrNoIHAVE, mrCanPost, mrNoPost };

typedef void __fastcall (__closure *TIdEventStreaming)(System::UnicodeString AMesgID, bool &AAccepted);

typedef void __fastcall (__closure *TIdNewsTransporTIdEvent)(System::Classes::TStrings* AMsg);

typedef void __fastcall (__closure *TIdEvenTIdNewsgroupList)(System::UnicodeString ANewsgroup, __int64 ALow, __int64 AHigh, System::UnicodeString AType, bool &ACanContinue);

typedef void __fastcall (__closure *TIdEventXOVER)(__int64 AArticleIndex, System::UnicodeString ASubject, System::UnicodeString AFrom, System::TDateTime ADate, System::UnicodeString AMsgId, System::UnicodeString AReferences, int AByteCount, int ALineCount, System::UnicodeString AExtraData, bool &VCanContinue);

typedef void __fastcall (__closure *TIdEventNewNewsList)(System::UnicodeString AMsgID, bool &ACanContinue);

typedef void __fastcall (__closure *TIdEventXHDREntry)(System::UnicodeString AHeader, System::UnicodeString AMsg, System::UnicodeString AHeaderData, bool &ACanContinue);

class PASCALIMPLEMENTATION TIdNNTP : public Idmessageclient::TIdMessageClient
{
	typedef Idmessageclient::TIdMessageClient inherited;
	
protected:
	int FGreetingCode;
	__int64 FMsgHigh;
	__int64 FMsgLow;
	__int64 FMsgCount;
	System::UnicodeString FNewsAgent;
	TIdEvenTIdNewsgroupList FOnNewsgroupList;
	TIdEvenTIdNewsgroupList FOnNewGroupsList;
	TIdEventNewNewsList FOnNewNewsList;
	TIdEventXHDREntry FOnXHDREntry;
	TIdEventXOVER FOnXOVER;
	TIdModeType FModeType;
	TIdModeSetResult FModeResult;
	TIdNNTPPermission FPermission;
	bool FForceAuth;
	bool FHDRSupported;
	bool FOVERSupported;
	void __fastcall AfterConnect();
	void __fastcall GetCapability();
	System::UnicodeString __fastcall ConvertDateTimeDist(System::TDateTime ADate, bool AGMT, System::UnicodeString ADistributions);
	virtual bool __fastcall GetSupportsTLS();
	virtual void __fastcall InitComponent();
	void __fastcall ProcessGroupList(System::UnicodeString ACmd, int AResponse, TIdEvenTIdNewsgroupList ALisTIdEvent);
	void __fastcall XHDRCommon(System::UnicodeString AHeader, System::UnicodeString AParam);
	void __fastcall XOVERCommon(System::UnicodeString AParam);
	void __fastcall StartTLS();
	
public:
	void __fastcall Check(System::Classes::TStrings* AMsgIDs, System::Classes::TStrings* AResponses);
	virtual void __fastcall Connect()/* overload */;
	__fastcall virtual ~TIdNNTP();
	virtual void __fastcall DisconnectNotifyPeer();
	bool __fastcall GetArticle(Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetArticle(__int64 AMsgNo, Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetArticle(System::UnicodeString AMsgID, Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetArticle(System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetArticle(__int64 AMsgNo, System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetArticle(System::UnicodeString AMsgID, System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetArticle(System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetArticle(__int64 AMsgNo, System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetArticle(System::UnicodeString AMsgID, System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetBody(Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetBody(__int64 AMsgNo, Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetBody(System::UnicodeString AMsgID, Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetBody(System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetBody(__int64 AMsgNo, System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetBody(System::UnicodeString AMsgID, System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetBody(System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetBody(__int64 AMsgNo, System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetBody(System::UnicodeString AMsgID, System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetHeader(Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetHeader(__int64 AMsgNo, Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetHeader(System::UnicodeString AMsgID, Idmessage::TIdMessage* AMsg)/* overload */;
	bool __fastcall GetHeader(System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetHeader(__int64 AMsgNo, System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetHeader(System::UnicodeString AMsgID, System::Classes::TStrings* AMsg)/* overload */;
	bool __fastcall GetHeader(System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetHeader(__int64 AMsgNo, System::Classes::TStream* AMsg)/* overload */;
	bool __fastcall GetHeader(System::UnicodeString AMsgID, System::Classes::TStream* AMsg)/* overload */;
	void __fastcall GetNewsgroupList()/* overload */;
	void __fastcall GetNewsgroupList(System::Classes::TStrings* AList)/* overload */;
	void __fastcall GetNewsgroupList(System::Classes::TStream* AStream)/* overload */;
	void __fastcall GetNewGroupsList(System::TDateTime ADate, bool AGMT, System::UnicodeString ADistributions)/* overload */;
	void __fastcall GetNewGroupsList(System::TDateTime ADate, bool AGMT, System::UnicodeString ADistributions, System::Classes::TStrings* AList)/* overload */;
	void __fastcall GetNewNewsList(System::UnicodeString ANewsgroups, System::TDateTime ADate, bool AGMT, System::UnicodeString ADistributions)/* overload */;
	void __fastcall GetNewNewsList(System::UnicodeString ANewsgroups, System::TDateTime ADate, bool AGMT, System::UnicodeString ADistributions, System::Classes::TStrings* AList)/* overload */;
	void __fastcall GetOverviewFMT(System::Classes::TStrings* AResponse);
	bool __fastcall IsExtCmdSupported(System::UnicodeString AExtension);
	void __fastcall IHAVE(System::Classes::TStrings* AMsg);
	bool __fastcall Next();
	bool __fastcall Previous();
	void __fastcall ParseXOVER(System::UnicodeString Aline, __int64 &AArticleIndex, System::UnicodeString &ASubject, System::UnicodeString &AFrom, System::TDateTime &ADate, System::UnicodeString &AMsgId, System::UnicodeString &AReferences, int &AByteCount, int &ALineCount, System::UnicodeString &AExtraData);
	void __fastcall ParseNewsGroup(System::UnicodeString ALine, /* out */ System::UnicodeString &ANewsGroup, /* out */ __int64 &AHi, /* out */ __int64 &ALo, /* out */ System::UnicodeString &AStatus);
	void __fastcall ParseXHDRLine(System::UnicodeString ALine, /* out */ System::UnicodeString &AMsg, /* out */ System::UnicodeString &AHeaderData);
	void __fastcall Post(Idmessage::TIdMessage* AMsg)/* overload */;
	void __fastcall Post(System::Classes::TStream* AStream)/* overload */;
	virtual short __fastcall SendCmd(System::UnicodeString AOut, const short *AResponse, const int AResponse_High, Idglobal::_di_IIdTextEncoding AEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	bool __fastcall SelectArticle(__int64 AMsgNo);
	void __fastcall SelectGroup(System::UnicodeString AGroup);
	System::UnicodeString __fastcall TakeThis(System::UnicodeString AMsgID, System::Classes::TStream* AMsg);
	void __fastcall XHDR(System::UnicodeString AHeader, System::UnicodeString AParam, System::Classes::TStrings* AResponse)/* overload */;
	void __fastcall XHDR(System::UnicodeString AHeader, System::UnicodeString AParam)/* overload */;
	void __fastcall XOVER(System::UnicodeString AParam, System::Classes::TStrings* AResponse)/* overload */;
	void __fastcall XOVER(System::UnicodeString AParam, System::Classes::TStream* AResponse)/* overload */;
	void __fastcall XOVER(System::UnicodeString AParam)/* overload */;
	void __fastcall SendAuth();
	__property TIdModeSetResult ModeResult = {read=FModeResult, write=FModeResult, nodefault};
	__property __int64 MsgCount = {read=FMsgCount};
	__property __int64 MsgHigh = {read=FMsgHigh};
	__property __int64 MsgLow = {read=FMsgLow};
	__property TIdNNTPPermission Permission = {read=FPermission, nodefault};
	
__published:
	__property System::UnicodeString NewsAgent = {read=FNewsAgent, write=FNewsAgent};
	__property TIdModeType Mode = {read=FModeType, write=FModeType, default=2};
	__property Password = {default=0};
	__property Username = {default=0};
	__property TIdEvenTIdNewsgroupList OnNewsgroupList = {read=FOnNewsgroupList, write=FOnNewsgroupList};
	__property TIdEvenTIdNewsgroupList OnNewGroupsList = {read=FOnNewGroupsList, write=FOnNewGroupsList};
	__property TIdEventNewNewsList OnNewNewsList = {read=FOnNewNewsList, write=FOnNewNewsList};
	__property TIdEventXHDREntry OnXHDREntry = {read=FOnXHDREntry, write=FOnXHDREntry};
	__property TIdEventXOVER OnXOVER = {read=FOnXOVER, write=FOnXOVER};
	__property OnTLSNotAvailable;
	__property Port = {default=119};
	__property Host = {default=0};
	__property UseTLS = {default=0};
	__property bool ForceAuth = {read=FForceAuth, write=FForceAuth, default=0};
public:
	/* TIdMessageClient.Create */ inline __fastcall TIdNNTP(System::Classes::TComponent* AOwner)/* overload */ : Idmessageclient::TIdMessageClient(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdNNTP()/* overload */ : Idmessageclient::TIdMessageClient() { }
	
	/* Hoisted overloads: */
	
public:
	inline void __fastcall  Connect(const System::UnicodeString AHost){ Idtcpclient::TIdTCPClientCustom::Connect(AHost); }
	inline void __fastcall  Connect(const System::UnicodeString AHost, const System::Word APort){ Idtcpclient::TIdTCPClientCustom::Connect(AHost, APort); }
	inline short __fastcall  SendCmd(System::UnicodeString AOut, const short AResponse = (short)(0xffffffff), Idglobal::_di_IIdTextEncoding AEncoding = Idglobal::_di_IIdTextEncoding()){ return Idtcpconnection::TIdTCPConnection::SendCmd(AOut, AResponse, AEncoding); }
	inline System::UnicodeString __fastcall  SendCmd(System::UnicodeString AOut, const System::UnicodeString AResponse, Idglobal::_di_IIdTextEncoding AEncoding = Idglobal::_di_IIdTextEncoding()){ return Idtcpconnection::TIdTCPConnection::SendCmd(AOut, AResponse, AEncoding); }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPException : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPException(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPException(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPException(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPException(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPException(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPNoOnNewGroupsList : public EIdNNTPException
{
	typedef EIdNNTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPNoOnNewGroupsList(const System::UnicodeString AMsg)/* overload */ : EIdNNTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPNoOnNewGroupsList(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdNNTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnNewGroupsList(NativeUInt Ident)/* overload */ : EIdNNTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnNewGroupsList(System::PResStringRec ResStringRec)/* overload */ : EIdNNTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnNewGroupsList(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnNewGroupsList(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPNoOnNewGroupsList(const System::UnicodeString Msg, int AHelpContext) : EIdNNTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPNoOnNewGroupsList(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdNNTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnNewGroupsList(NativeUInt Ident, int AHelpContext)/* overload */ : EIdNNTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnNewGroupsList(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnNewGroupsList(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnNewGroupsList(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPNoOnNewGroupsList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPNoOnNewNewsList : public EIdNNTPException
{
	typedef EIdNNTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPNoOnNewNewsList(const System::UnicodeString AMsg)/* overload */ : EIdNNTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPNoOnNewNewsList(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdNNTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnNewNewsList(NativeUInt Ident)/* overload */ : EIdNNTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnNewNewsList(System::PResStringRec ResStringRec)/* overload */ : EIdNNTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnNewNewsList(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnNewNewsList(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPNoOnNewNewsList(const System::UnicodeString Msg, int AHelpContext) : EIdNNTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPNoOnNewNewsList(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdNNTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnNewNewsList(NativeUInt Ident, int AHelpContext)/* overload */ : EIdNNTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnNewNewsList(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnNewNewsList(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnNewNewsList(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPNoOnNewNewsList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPNoOnNewsgroupList : public EIdNNTPException
{
	typedef EIdNNTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPNoOnNewsgroupList(const System::UnicodeString AMsg)/* overload */ : EIdNNTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPNoOnNewsgroupList(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdNNTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnNewsgroupList(NativeUInt Ident)/* overload */ : EIdNNTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnNewsgroupList(System::PResStringRec ResStringRec)/* overload */ : EIdNNTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnNewsgroupList(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnNewsgroupList(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPNoOnNewsgroupList(const System::UnicodeString Msg, int AHelpContext) : EIdNNTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPNoOnNewsgroupList(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdNNTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnNewsgroupList(NativeUInt Ident, int AHelpContext)/* overload */ : EIdNNTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnNewsgroupList(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnNewsgroupList(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnNewsgroupList(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPNoOnNewsgroupList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPNoOnXHDREntry : public EIdNNTPException
{
	typedef EIdNNTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPNoOnXHDREntry(const System::UnicodeString AMsg)/* overload */ : EIdNNTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPNoOnXHDREntry(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdNNTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnXHDREntry(NativeUInt Ident)/* overload */ : EIdNNTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnXHDREntry(System::PResStringRec ResStringRec)/* overload */ : EIdNNTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnXHDREntry(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnXHDREntry(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPNoOnXHDREntry(const System::UnicodeString Msg, int AHelpContext) : EIdNNTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPNoOnXHDREntry(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdNNTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnXHDREntry(NativeUInt Ident, int AHelpContext)/* overload */ : EIdNNTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnXHDREntry(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnXHDREntry(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnXHDREntry(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPNoOnXHDREntry() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPNoOnXOVER : public EIdNNTPException
{
	typedef EIdNNTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPNoOnXOVER(const System::UnicodeString AMsg)/* overload */ : EIdNNTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPNoOnXOVER(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdNNTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnXOVER(NativeUInt Ident)/* overload */ : EIdNNTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPNoOnXOVER(System::PResStringRec ResStringRec)/* overload */ : EIdNNTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnXOVER(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPNoOnXOVER(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPNoOnXOVER(const System::UnicodeString Msg, int AHelpContext) : EIdNNTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPNoOnXOVER(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdNNTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnXOVER(NativeUInt Ident, int AHelpContext)/* overload */ : EIdNNTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPNoOnXOVER(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnXOVER(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPNoOnXOVER(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPNoOnXOVER() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPStringListNotInitialized : public EIdNNTPException
{
	typedef EIdNNTPException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPStringListNotInitialized(const System::UnicodeString AMsg)/* overload */ : EIdNNTPException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPStringListNotInitialized(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdNNTPException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPStringListNotInitialized(NativeUInt Ident)/* overload */ : EIdNNTPException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPStringListNotInitialized(System::PResStringRec ResStringRec)/* overload */ : EIdNNTPException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPStringListNotInitialized(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPStringListNotInitialized(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPStringListNotInitialized(const System::UnicodeString Msg, int AHelpContext) : EIdNNTPException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPStringListNotInitialized(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdNNTPException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPStringListNotInitialized(NativeUInt Ident, int AHelpContext)/* overload */ : EIdNNTPException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPStringListNotInitialized(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPStringListNotInitialized(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPStringListNotInitialized(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdNNTPException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPStringListNotInitialized() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EIdNNTPConnectionRefused : public Idreplyrfc::EIdReplyRFCError
{
	typedef Idreplyrfc::EIdReplyRFCError inherited;
	
public:
	/* EIdReplyRFCError.CreateError */ inline __fastcall virtual EIdNNTPConnectionRefused(const int AErrorCode, const System::UnicodeString AReplyMessage) : Idreplyrfc::EIdReplyRFCError(AErrorCode, AReplyMessage) { }
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdNNTPConnectionRefused(const System::UnicodeString AMsg)/* overload */ : Idreplyrfc::EIdReplyRFCError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdNNTPConnectionRefused(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPConnectionRefused(NativeUInt Ident)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdNNTPConnectionRefused(System::PResStringRec ResStringRec)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPConnectionRefused(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdNNTPConnectionRefused(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdNNTPConnectionRefused(const System::UnicodeString Msg, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdNNTPConnectionRefused(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idreplyrfc::EIdReplyRFCError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPConnectionRefused(NativeUInt Ident, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdNNTPConnectionRefused(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPConnectionRefused(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdNNTPConnectionRefused(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idreplyrfc::EIdReplyRFCError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdNNTPConnectionRefused() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idnntp */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDNNTP)
using namespace Idnntp;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdnntpHPP
