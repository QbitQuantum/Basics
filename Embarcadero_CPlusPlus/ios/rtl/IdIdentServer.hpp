// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdIdentServer.pas' rev: 34.00 (iOS)

#ifndef IdidentserverHPP
#define IdidentserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdAssignedNumbers.hpp>
#include <IdContext.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdGlobal.hpp>
#include <IdComponent.hpp>
#include <IdBaseComponent.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ididentserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdIdentServer;
//-- type declarations -------------------------------------------------------
typedef void __fastcall (__closure *TIdIdentQueryEvent)(Idcontext::TIdContext* AContext, System::Word AServerPort, System::Word AClientPort);

enum DECLSPEC_DENUM TIdIdentErrorType : unsigned char { ieInvalidPort, ieNoUser, ieHiddenUser, ieUnknownError };

class PASCALIMPLEMENTATION TIdIdentServer : public Idcustomtcpserver::TIdCustomTCPServer
{
	typedef Idcustomtcpserver::TIdCustomTCPServer inherited;
	
protected:
	TIdIdentQueryEvent FOnIdentQuery;
	int FQueryTimeOut;
	virtual bool __fastcall DoExecute(Idcontext::TIdContext* AContext);
	virtual void __fastcall InitComponent();
	
public:
	void __fastcall ReplyError(Idcontext::TIdContext* AContext, System::Word AServerPort, System::Word AClientPort, TIdIdentErrorType AErr);
	void __fastcall ReplyIdent(Idcontext::TIdContext* AContext, System::Word AServerPort, System::Word AClientPort, System::UnicodeString AOS, System::UnicodeString AUserName, const System::UnicodeString ACharset = System::UnicodeString());
	void __fastcall ReplyOther(Idcontext::TIdContext* AContext, System::Word AServerPort, System::Word AClientPort, System::UnicodeString AOther);
	
__published:
	__property int QueryTimeOut = {read=FQueryTimeOut, write=FQueryTimeOut, default=60000};
	__property TIdIdentQueryEvent OnIdentQuery = {read=FOnIdentQuery, write=FOnIdentQuery};
	__property DefaultPort = {default=113};
public:
	/* TIdCustomTCPServer.Destroy */ inline __fastcall virtual ~TIdIdentServer() { }
	
public:
	/* TIdBaseComponent.Create */ inline __fastcall TIdIdentServer(System::Classes::TComponent* AOwner)/* overload */ : Idcustomtcpserver::TIdCustomTCPServer(AOwner) { }
	
public:
	/* TIdInitializerComponent.Create */ inline __fastcall TIdIdentServer()/* overload */ : Idcustomtcpserver::TIdCustomTCPServer() { }
	
};


//-- var, const, procedure ---------------------------------------------------
static constexpr System::Word IdDefIdentQueryTimeOut = System::Word(0xea60);
}	/* namespace Ididentserver */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDIDENTSERVER)
using namespace Ididentserver;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdidentserverHPP
