// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IdFTPServerContextBase.pas' rev: 34.00 (Windows)

#ifndef IdftpservercontextbaseHPP
#define IdftpservercontextbaseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdFTPList.hpp>
#include <IdContext.hpp>
#include <IdTask.hpp>

//-- user supplied -----------------------------------------------------------

namespace Idftpservercontextbase
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TIdFTPServerContextBase;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TIdFTPUserType : unsigned char { utNone, utAnonymousUser, utNormalUser };

class PASCALIMPLEMENTATION TIdFTPServerContextBase : public Idcustomtcpserver::TIdServerContext
{
	typedef Idcustomtcpserver::TIdServerContext inherited;
	
protected:
	TIdFTPUserType FUserType;
	bool FAuthenticated;
	int FALLOSize;
	System::UnicodeString FCurrentDir;
	System::UnicodeString FHomeDir;
	System::UnicodeString FHost;
	System::UnicodeString FUsername;
	System::UnicodeString FPassword;
	System::UnicodeString FAccount;
	bool FAccountNeeded;
	int FRESTPos;
	System::UnicodeString FRNFR;
	bool FNLSTUtf8;
	virtual void __fastcall ReInitialize();
	
public:
	__property bool Authenticated = {read=FAuthenticated, write=FAuthenticated, nodefault};
	__property int ALLOSize = {read=FALLOSize, write=FALLOSize, nodefault};
	__property System::UnicodeString CurrentDir = {read=FCurrentDir, write=FCurrentDir};
	__property System::UnicodeString HomeDir = {read=FHomeDir, write=FHomeDir};
	__property System::UnicodeString Password = {read=FPassword, write=FPassword};
	__property System::UnicodeString Username = {read=FUsername, write=FUsername};
	__property System::UnicodeString Account = {read=FAccount, write=FAccount};
	__property bool AccountNeeded = {read=FAccountNeeded, write=FAccountNeeded, nodefault};
	__property System::UnicodeString Host = {read=FHost, write=FHost};
	__property TIdFTPUserType UserType = {read=FUserType, write=FUserType, nodefault};
	__property int RESTPos = {read=FRESTPos, write=FRESTPos, nodefault};
	__property System::UnicodeString RNFR = {read=FRNFR, write=FRNFR};
	__property bool NLSTUtf8 = {read=FNLSTUtf8, write=FNLSTUtf8, nodefault};
public:
	/* TIdContext.Create */ inline __fastcall virtual TIdFTPServerContextBase(Idtcpconnection::TIdTCPConnection* AConnection, Idyarn::TIdYarn* AYarn, Idthreadsafe::TIdThreadSafeObjectList* AList) : Idcustomtcpserver::TIdServerContext(AConnection, AYarn, AList) { }
	/* TIdContext.Destroy */ inline __fastcall virtual ~TIdFTPServerContextBase() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Idftpservercontextbase */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IDFTPSERVERCONTEXTBASE)
using namespace Idftpservercontextbase;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IdftpservercontextbaseHPP
