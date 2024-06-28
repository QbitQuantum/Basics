// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMessageClient.pas' rev: 34.00 (Android)

#ifndef IdmessageclientHPP
#define IdmessageclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdCoderMIME.hpp>
#include <IdExplicitTLSClientServerBase.hpp>
#include <IdGlobal.hpp>
#include <IdHeaderList.hpp>
#include <IdIOHandlerStream.hpp>
#include <IdBaseComponent.hpp>
#include <IdMessage.hpp>
#include <IdTCPClient.hpp>
#include <IdIOHandler.hpp>
#include <IdComponent.hpp>
#include <IdTCPConnection.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmessageclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdIOHandlerStreamMsg;
class DELPHICLASS TIdMessageClient;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdIOHandlerStreamMsg : public Idiohandlerstream::TIdIOHandlerStream
{
	typedef Idiohandlerstream::TIdIOHandlerStream inherited;
	
protected:
	bool FTerminatorWasRead;
	bool FEscapeLines;
	bool FUnescapeLines;
	System::Byte FLastByteRecv;
	virtual int __fastcall ReadDataFromSource(Idglobal::TIdBytes &VBuffer);
	
public:
	__fastcall virtual TIdIOHandlerStreamMsg(System::Classes::TComponent* AOwner, System::Classes::TStream* AReceiveStream, System::Classes::TStream* ASendStream)/* overload */;
	virtual bool __fastcall Readable(int AMSec = 0xffffffff);
	virtual System::UnicodeString __fastcall ReadLn(System::UnicodeString ATerminator, int ATimeout = 0xffffffff, int AMaxLineLength = 0xffffffff, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	virtual void __fastcall WriteLn(const System::UnicodeString AOut, Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding())/* overload */;
	__property bool EscapeLines = {read=FEscapeLines, write=FEscapeLines, nodefault};
	__property bool UnescapeLines = {read=FUnescapeLines, write=FUnescapeLines, nodefault};
	
__published:
	__property MaxLineLength = {default=2147483647};
public:
	/* TIdIOHandlerStream.Create */ inline __fastcall TIdIOHandlerStreamMsg(System::Classes::TComponent* AOwner)/* overload */ : Idiohandlerstream::TIdIOHandlerStream(AOwner) { }
	
public:
	/* TIdIOHandler.Destroy */ inline __fastcall virtual ~TIdIOHandlerStreamMsg() { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdIOHandlerStreamMsg()/* overload */ : Idiohandlerstream::TIdIOHandlerStream() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::UnicodeString __fastcall  ReadLn(Idglobal::_di_IIdTextEncoding AByteEncoding = Idglobal::_di_IIdTextEncoding()){ return Idiohandler::TIdIOHandler::ReadLn(AByteEncoding); }
	inline System::UnicodeString __fastcall  ReadLn(System::UnicodeString ATerminator, Idglobal::_di_IIdTextEncoding AByteEncoding){ return Idiohandler::TIdIOHandler::ReadLn(ATerminator, AByteEncoding); }
	inline void __fastcall  WriteLn(Idglobal::_di_IIdTextEncoding AEncoding = Idglobal::_di_IIdTextEncoding()){ Idiohandler::TIdIOHandler::WriteLn(AEncoding); }
	
};


class PASCALIMPLEMENTATION TIdMessageClient : public Idexplicittlsclientserverbase::TIdExplicitTLSClient
{
	typedef Idexplicittlsclientserverbase::TIdExplicitTLSClient inherited;
	
protected:
	int FMsgLineLength;
	System::UnicodeString FMsgLineFold;
	virtual void __fastcall ReceiveBody(Idmessage::TIdMessage* AMsg, const System::UnicodeString ADelim = u".");
	virtual System::UnicodeString __fastcall ReceiveHeader(Idmessage::TIdMessage* AMsg, const System::UnicodeString AAltTerm = System::UnicodeString());
	virtual void __fastcall SendBody(Idmessage::TIdMessage* AMsg);
	virtual void __fastcall SendHeader(Idmessage::TIdMessage* AMsg);
	void __fastcall EncodeAndWriteText(System::Classes::TStrings* const ABody, Idglobal::_di_IIdTextEncoding AEncoding);
	void __fastcall WriteFoldedLine(const System::UnicodeString ALine);
	virtual void __fastcall InitComponent();
	
public:
	__fastcall TIdMessageClient(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIdMessageClient();
	void __fastcall ProcessMessage(Idmessage::TIdMessage* AMsg, bool AHeaderOnly = false)/* overload */;
	void __fastcall ProcessMessage(Idmessage::TIdMessage* AMsg, System::Classes::TStream* AStream, bool AHeaderOnly = false)/* overload */;
	void __fastcall ProcessMessage(Idmessage::TIdMessage* AMsg, const System::UnicodeString AFilename, bool AHeaderOnly = false)/* overload */;
	virtual void __fastcall SendMsg(Idmessage::TIdMessage* AMsg, bool AHeadersOnly = false)/* overload */;
	__property int MsgLineLength = {read=FMsgLineLength, write=FMsgLineLength, nodefault};
	__property System::UnicodeString MsgLineFold = {read=FMsgLineFold, write=FMsgLineFold};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMessageClient()/* overload */ : Idexplicittlsclientserverbase::TIdExplicitTLSClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmessageclient */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMESSAGECLIENT)
using namespace Idmessageclient;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdmessageclientHPP
