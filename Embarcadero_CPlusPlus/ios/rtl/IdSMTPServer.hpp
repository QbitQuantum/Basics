// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdSMTPServer.pas' rev: 34.00 (iOS)

#ifndef IdsmtpserverHPP
#define IdsmtpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdCmdTCPServer.hpp>
#include <IdCommandHandlers.hpp>
#include <IdContext.hpp>
#include <IdEMailAddress.hpp>
#include <IdException.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdReply.hpp>
#include <IdReplyRFC.hpp>
#include <IdReplySMTP.hpp>
#include <IdTCPConnection.hpp>
#include <IdTCPServer.hpp>
#include <IdYarn.hpp>
#include <IdStack.hpp>
#include <IdGlobal.hpp>
#include <System.SysUtils.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <IdTask.hpp>
#include <IdThreadSafe.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idsmtpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIdSMTPServerError;
class DELPHICLASS EIdSMTPServerNoRcptTo;
class DELPHICLASS TIdSMTPServer;
class DELPHICLASS TIdSMTPServerContext;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EIdSMTPServerError : public Idexception::EIdException
{
	typedef Idexception::EIdException inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSMTPServerError(const System::UnicodeString AMsg)/* overload */ : Idexception::EIdException(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSMTPServerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : Idexception::EIdException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPServerError(NativeUInt Ident)/* overload */ : Idexception::EIdException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPServerError(System::PResStringRec ResStringRec)/* overload */ : Idexception::EIdException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPServerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPServerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSMTPServerError(const System::UnicodeString Msg, int AHelpContext) : Idexception::EIdException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSMTPServerError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : Idexception::EIdException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPServerError(NativeUInt Ident, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPServerError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPServerError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPServerError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : Idexception::EIdException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSMTPServerError() { }
	
};


class PASCALIMPLEMENTATION EIdSMTPServerNoRcptTo : public EIdSMTPServerError
{
	typedef EIdSMTPServerError inherited;
	
public:
	/* EIdException.Create */ inline __fastcall virtual EIdSMTPServerNoRcptTo(const System::UnicodeString AMsg)/* overload */ : EIdSMTPServerError(AMsg) { }
	
public:
	/* Exception.CreateFmt */ inline __fastcall EIdSMTPServerNoRcptTo(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIdSMTPServerError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPServerNoRcptTo(NativeUInt Ident)/* overload */ : EIdSMTPServerError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIdSMTPServerNoRcptTo(System::PResStringRec ResStringRec)/* overload */ : EIdSMTPServerError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPServerNoRcptTo(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSMTPServerError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIdSMTPServerNoRcptTo(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIdSMTPServerError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIdSMTPServerNoRcptTo(const System::UnicodeString Msg, int AHelpContext) : EIdSMTPServerError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIdSMTPServerNoRcptTo(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIdSMTPServerError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPServerNoRcptTo(NativeUInt Ident, int AHelpContext)/* overload */ : EIdSMTPServerError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIdSMTPServerNoRcptTo(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIdSMTPServerError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPServerNoRcptTo(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSMTPServerError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIdSMTPServerNoRcptTo(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIdSMTPServerError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIdSMTPServerNoRcptTo() { }
	
};


enum DECLSPEC_DENUM TIdMailFromReply : unsigned char { mAccept, mReject, mSystemFull, mLimitExceeded };

enum DECLSPEC_DENUM TIdRCPToReply : unsigned char { rAddressOk, rRelayDenied, rInvalid, rWillForward, rNoForward, rTooManyAddresses, rDisabledPerm, rDisabledTemp, rSystemFull, rLimitExceeded };

enum DECLSPEC_DENUM TIdDataReply : unsigned char { dOk, dMBFull, dSystemFull, dLocalProcessingError, dTransactionFailed, dLimitExceeded };

enum DECLSPEC_DENUM TIdSPFReply : unsigned char { spfNone, spfNeutral, spfPass, spfFail, spfSoftFail, spfTempError, spfPermError };

typedef void __fastcall (__closure *TOnMailFromEvent)(TIdSMTPServerContext* ASender, const System::UnicodeString AAddress, System::Classes::TStrings* AParams, TIdMailFromReply &VAction);

typedef void __fastcall (__closure *TOnMsgReceive)(TIdSMTPServerContext* ASender, System::Classes::TStream* AMsg, TIdDataReply &VAction);

typedef void __fastcall (__closure *TOnRcptToEvent)(TIdSMTPServerContext* ASender, const System::UnicodeString AAddress, System::Classes::TStrings* AParams, TIdRCPToReply &VAction, System::UnicodeString &VForward);

typedef void __fastcall (__closure *TOnReceived)(TIdSMTPServerContext* ASender, System::UnicodeString &AReceived);

typedef void __fastcall (__closure *TOnSMTPEvent)(TIdSMTPServerContext* ASender);

typedef void __fastcall (__closure *TOnSMTPUserLoginEvent)(TIdSMTPServerContext* ASender, const System::UnicodeString AUsername, const System::UnicodeString APassword, bool &VAuthenticated);

typedef void __fastcall (__closure *TOnSPFCheck)(TIdSMTPServerContext* ASender, const System::UnicodeString AIP, const System::UnicodeString ADomain, const System::UnicodeString AIdentity, TIdSPFReply &VAction);

typedef void __fastcall (__closure *TOnDataStreamEvent)(TIdSMTPServerContext* ASender, System::Classes::TStream* &VStream);

class PASCALIMPLEMENTATION TIdSMTPServer : public Idexplicittlsclientserverbase::TIdExplicitTLSServer
{
	typedef Idexplicittlsclientserverbase::TIdExplicitTLSServer inherited;
	
protected:
	TOnDataStreamEvent FOnBeforeMsg;
	TOnMailFromEvent FOnMailFrom;
	TOnMsgReceive FOnMsgReceive;
	TOnRcptToEvent FOnRcptTo;
	TOnReceived FOnReceived;
	TOnSMTPEvent FOnReset;
	TOnSPFCheck FOnSPFCheck;
	TOnSMTPUserLoginEvent FOnUserLogin;
	System::UnicodeString FServerName;
	bool FAllowPipelining;
	int FMaxMsgSize;
	virtual Idreply::TIdReply* __fastcall CreateGreeting();
	virtual Idreply::TIdReply* __fastcall CreateReplyUnknownCommand();
	void __fastcall DoAuthLogin(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString Mechanism, const System::UnicodeString InitialResponse);
	void __fastcall CommandNOOP(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandQUIT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandEHLO(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandHELO(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandAUTH(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandMAIL(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRCPT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandDATA(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandRSET(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandSTARTTLS(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CommandBDAT(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall AuthFailed(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall CmdSyntaxError(Idcontext::TIdContext* AContext, System::UnicodeString ALine, Idreply::TIdReply* const AReply = (Idreply::TIdReply*)(0x0))/* overload */;
	void __fastcall CmdSyntaxError(Idcommandhandlers::TIdCommand* ASender)/* overload */;
	void __fastcall BadSequenceError(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall InvalidSyntax(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall NoHello(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MustUseTLS(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailFromAccept(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall MailFromReject(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall AddrValid(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall AddrInvalid(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall AddrWillForward(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString(), const System::UnicodeString ATo = System::UnicodeString());
	void __fastcall AddrNotWillForward(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString(), const System::UnicodeString ATo = System::UnicodeString());
	void __fastcall AddrDisabledPerm(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall AddrDisabledTemp(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall AddrNoRelaying(Idcommandhandlers::TIdCommand* ASender, const System::UnicodeString AAddress = System::UnicodeString());
	void __fastcall AddrTooManyRecipients(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailSubmitOk(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailSubmitLimitExceeded(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailSubmitStorageExceededFull(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailSubmitTransactionFailed(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailSubmitLocalProcessingError(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall MailSubmitSystemFull(Idcommandhandlers::TIdCommand* ASender);
	void __fastcall SetEnhReply(Idreply::TIdReply* AReply, const int ANumericCode, const System::UnicodeString AEnhReply, const System::UnicodeString AText, const bool IsEHLO);
	virtual Idreply::TIdReplyClass __fastcall GetReplyClass();
	virtual Idreply::TIdRepliesClass __fastcall GetRepliesClass();
	virtual void __fastcall InitComponent();
	virtual void __fastcall DoReplyUnknownCommand(Idcontext::TIdContext* AContext, System::UnicodeString ALine);
	virtual void __fastcall InitializeCommandHandlers();
	void __fastcall DoReset(TIdSMTPServerContext* AContext, bool AIsTLSReset = false);
	void __fastcall MsgBegan(TIdSMTPServerContext* AContext, System::Classes::TStream* &VStream);
	void __fastcall MsgReceived(Idcommandhandlers::TIdCommand* ASender, System::Classes::TStream* AMsgData);
	void __fastcall SetMaxMsgSize(int AValue);
	bool __fastcall SPFAuthOk(TIdSMTPServerContext* AContext, Idreply::TIdReply* AReply, const System::UnicodeString ACmd, const System::UnicodeString ADomain, const System::UnicodeString AIdentity);
	
public:
	__fastcall TIdSMTPServer(System::Classes::TComponent* AOwner)/* overload */;
	
__published:
	__property TOnDataStreamEvent OnBeforeMsg = {read=FOnBeforeMsg, write=FOnBeforeMsg};
	__property TOnMailFromEvent OnMailFrom = {read=FOnMailFrom, write=FOnMailFrom};
	__property TOnMsgReceive OnMsgReceive = {read=FOnMsgReceive, write=FOnMsgReceive};
	__property TOnRcptToEvent OnRcptTo = {read=FOnRcptTo, write=FOnRcptTo};
	__property TOnReceived OnReceived = {read=FOnReceived, write=FOnReceived};
	__property TOnSMTPEvent OnReset = {read=FOnReset, write=FOnReset};
	__property TOnSPFCheck OnSPFCheck = {read=FOnSPFCheck, write=FOnSPFCheck};
	__property TOnSMTPUserLoginEvent OnUserLogin = {read=FOnUserLogin, write=FOnUserLogin};
	__property bool AllowPipelining = {read=FAllowPipelining, write=FAllowPipelining, default=0};
	__property DefaultPort = {default=25};
	__property int MaxMsgSize = {read=FMaxMsgSize, write=SetMaxMsgSize, default=0};
	__property System::UnicodeString ServerName = {read=FServerName, write=FServerName};
	__property UseTLS = {default=0};
public:
	/* TIdCmdTCPServer.Destroy */ inline __fastcall virtual ~TIdSMTPServer() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdSMTPServer()/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSServer() { }
	
};


enum DECLSPEC_DENUM TIdSMTPState : unsigned char { idSMTPNone, idSMTPHelo, idSMTPMail, idSMTPRcpt, idSMTPData, idSMTPBDat };

enum DECLSPEC_DENUM TIdSMTPBodyType : unsigned char { idSMTP7Bit, idSMTP8BitMime, idSMTPBinaryMime };

class PASCALIMPLEMENTATION TIdSMTPServerContext : public Idcustomtcpserver::TIdServerContext
{
	typedef Idcustomtcpserver::TIdServerContext inherited;
	
protected:
	TIdSMTPState FSMTPState;
	System::UnicodeString FFrom;
	Idemailaddress::TIdEMailAddressList* FRCPTList;
	bool FHELO;
	bool FEHLO;
	System::UnicodeString FHeloString;
	System::UnicodeString FUsername;
	System::UnicodeString FPassword;
	bool FLoggedIn;
	int FMsgSize;
	bool FPipeLining;
	bool FFinalStage;
	System::Classes::TStream* FBDataStream;
	TIdSMTPBodyType FBodyType;
	bool __fastcall GetUsingTLS();
	bool __fastcall GetCanUseExplicitTLS();
	bool __fastcall GetTLSIsRequired();
	void __fastcall SetPipeLining(const bool AValue);
	
public:
	__fastcall virtual TIdSMTPServerContext(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList);
	__fastcall virtual ~TIdSMTPServerContext();
	void __fastcall CheckPipeLine();
	virtual void __fastcall Reset(bool AIsTLSReset = false);
	__property TIdSMTPState SMTPState = {read=FSMTPState, write=FSMTPState, nodefault};
	__property System::UnicodeString From = {read=FFrom, write=FFrom};
	__property Idemailaddress::TIdEMailAddressList* RCPTList = {read=FRCPTList};
	__property bool HELO = {read=FHELO, write=FHELO, nodefault};
	__property bool EHLO = {read=FEHLO, write=FEHLO, nodefault};
	__property System::UnicodeString HeloString = {read=FHeloString, write=FHeloString};
	__property System::UnicodeString Username = {read=FUsername, write=FUsername};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property bool LoggedIn = {read=FLoggedIn, write=FLoggedIn, nodefault};
	__property int MsgSize = {read=FMsgSize, write=FMsgSize, nodefault};
	__property bool FinalStage = {read=FFinalStage, write=FFinalStage, nodefault};
	__property bool UsingTLS = {read=GetUsingTLS, nodefault};
	__property bool CanUseExplicitTLS = {read=GetCanUseExplicitTLS, nodefault};
	__property bool TLSIsRequired = {read=GetTLSIsRequired, nodefault};
	__property bool PipeLining = {read=FPipeLining, write=SetPipeLining, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
#define IdSMTPSvrReceivedString u"Received: from $hostname[$ipaddress] (helo=$helo) by $svrh"\
	u"ostname[$svripaddress] with $protocol ($servername)"
}	/* namespace Idsmtpserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDSMTPSERVER)
using namespace Idsmtpserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdsmtpserverHPP
