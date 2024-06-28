// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdMappedPOP3.pas' rev: 34.00 (Windows)

#ifndef Idmappedpop3HPP
#define Idmappedpop3HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdMappedPortTCP.hpp>
#include <IdMappedTelnet.hpp>
#include <IdReplyPOP3.hpp>
#include <IdTCPServer.hpp>
#include <IdContext.hpp>
#include <IdTask.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idmappedpop3
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdMappedPOP3Context;
class DELPHICLASS TIdMappedPOP3;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TIdMappedPOP3Context : public Idmappedtelnet::TIdMappedTelnetContext
{
	typedef Idmappedtelnet::TIdMappedTelnetContext inherited;
	
protected:
	System::UnicodeString FErrorMsg;
	System::UnicodeString FGreeting;
	System::UnicodeString FUserName;
	virtual void __fastcall OutboundConnect();
	
public:
	__property System::UnicodeString ErrorMsg = {read=FErrorMsg};
	__property System::UnicodeString Greeting = {read=FGreeting};
	__property System::UnicodeString UserName = {read=FUserName, write=FUserName};
public:
	/* TIdMappedPortContext.Create */ inline __fastcall virtual TIdMappedPOP3Context(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList) : Idmappedtelnet::TIdMappedTelnetContext(AConnection, AYarn, AList) { }
	/* TIdMappedPortContext.Destroy */ inline __fastcall virtual ~TIdMappedPOP3Context() { }
	
};


class PASCALIMPLEMENTATION TIdMappedPOP3 : public Idmappedtelnet::TIdMappedTelnet
{
	typedef Idmappedtelnet::TIdMappedTelnet inherited;
	
protected:
	Idreplypop3::TIdReplyPOP3* FReplyUnknownCommand;
	Idreplypop3::TIdReplyPOP3* FGreeting;
	System::UnicodeString FUserHostDelimiter;
	virtual void __fastcall InitComponent();
	void __fastcall SetGreeting(Idreplypop3::TIdReplyPOP3* AValue);
	void __fastcall SetReplyUnknownCommand(Idreplypop3::TIdReplyPOP3* const AValue);
	
public:
	__fastcall TIdMappedPOP3(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TIdMappedPOP3();
	
__published:
	__property Idreplypop3::TIdReplyPOP3* Greeting = {read=FGreeting, write=SetGreeting};
	__property Idreplypop3::TIdReplyPOP3* ReplyUnknownCommand = {read=FReplyUnknownCommand, write=SetReplyUnknownCommand};
	__property DefaultPort = {default=110};
	__property MappedPort = {default=110};
	__property System::UnicodeString UserHostDelimiter = {read=FUserHostDelimiter, write=FUserHostDelimiter};
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdMappedPOP3()/* overload */ : Idmappedtelnet::TIdMappedTelnet() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idmappedpop3 */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDMAPPEDPOP3)
using namespace Idmappedpop3;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Idmappedpop3HPP
