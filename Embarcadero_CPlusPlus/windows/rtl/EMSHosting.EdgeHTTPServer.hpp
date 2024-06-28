// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'EMSHosting.EdgeHTTPServer.pas' rev: 34.00 (Windows)

#ifndef Emshosting_EdgehttpserverHPP
#define Emshosting_EdgehttpserverHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.hpp>
#include <IdCustomHTTPServer.hpp>
#include <IdBaseComponent.hpp>
#include <IdComponent.hpp>
#include <IdCustomTCPServer.hpp>
#include <IdHTTPServer.hpp>
#include <IdContext.hpp>
#include <EMSHosting.EdgeService.hpp>

//-- user supplied -----------------------------------------------------------

namespace Emshosting
{
namespace Edgehttpserver
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TEMSEdgeHTTPServer;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TEMSEdgeHTTPServer : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef void __fastcall (__closure *TGetPasswordEvent)(System::UnicodeString &APassword);
	
	
private:
	Idhttpserver::TIdHTTPServer* FIdHTTPServer;
	int FPort;
	Emshosting::Edgeservice::TEMSEdgeListener::TModule* FModule;
	bool FThreadPool;
	int FThreadPoolSize;
	int FListenQueue;
	System::UnicodeString FKeyFile;
	System::UnicodeString FRootCertFile;
	System::UnicodeString FCertFile;
	TGetPasswordEvent FOnGetSSLPassword;
	bool FHTTPS;
	unsigned __fastcall GetPort();
	void __fastcall SetPort(const unsigned Value);
	void __fastcall DoCommand(Idcontext::TIdContext* AContext, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	void __fastcall CommandGet(Idcontext::TIdContext* AContext, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	void __fastcall CommandOther(Idcontext::TIdContext* AContext, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo);
	void __fastcall CommandError(Idcontext::TIdContext* AContext, Idcustomhttpserver::TIdHTTPRequestInfo* ARequestInfo, Idcustomhttpserver::TIdHTTPResponseInfo* AResponseInfo, System::Sysutils::Exception* AException);
	bool __fastcall GetActive();
	void __fastcall SetActive(const bool Value);
	void __fastcall DoOnGetSSLPassword(System::UnicodeString &APassword);
	
public:
	__fastcall TEMSEdgeHTTPServer();
	__fastcall virtual ~TEMSEdgeHTTPServer();
	__property bool Active = {read=GetActive, write=SetActive, nodefault};
	__property unsigned Port = {read=GetPort, write=SetPort, nodefault};
	__property Emshosting::Edgeservice::TEMSEdgeListener::TModule* Module = {write=FModule};
	__property bool ThreadPool = {read=FThreadPool, write=FThreadPool, nodefault};
	__property int ThreadPoolSize = {read=FThreadPoolSize, write=FThreadPoolSize, nodefault};
	__property int ListenQueue = {read=FListenQueue, write=FListenQueue, nodefault};
	__property System::UnicodeString CertFile = {read=FCertFile, write=FCertFile};
	__property System::UnicodeString RootCertFile = {read=FRootCertFile, write=FRootCertFile};
	__property System::UnicodeString KeyFile = {read=FKeyFile, write=FKeyFile};
	__property TGetPasswordEvent OnGetSSLPassword = {read=FOnGetSSLPassword, write=FOnGetSSLPassword};
	__property bool HTTPS = {read=FHTTPS, write=FHTTPS, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Edgehttpserver */
}	/* namespace Emshosting */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING_EDGEHTTPSERVER)
using namespace Emshosting::Edgehttpserver;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_EMSHOSTING)
using namespace Emshosting;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Emshosting_EdgehttpserverHPP
