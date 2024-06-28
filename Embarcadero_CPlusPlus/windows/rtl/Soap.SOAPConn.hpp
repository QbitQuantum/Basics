// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPConn.pas' rev: 34.00 (Windows)

#ifndef Soap_SoapconnHPP
#define Soap_SoapconnHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <System.Classes.hpp>
#include <Datasnap.Midas.hpp>
#include <Datasnap.DBClient.hpp>
#include <Soap.SOAPHTTPTrans.hpp>
#include <Soap.Rio.hpp>
#include <Soap.SOAPHTTPClient.hpp>
#include <Soap.SOAPMidas.hpp>
#include <Data.DB.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soapconn
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TSoapConnection;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TSoapConnection : public Datasnap::Dbclient::TCustomRemoteServer
{
	typedef Datasnap::Dbclient::TCustomRemoteServer inherited;
	
private:
	Soap::Soaphttpclient::THTTPRIO* FRIO;
	System::UnicodeString FURL;
	System::UnicodeString FAgent;
	System::UnicodeString FPassword;
	System::UnicodeString FProxy;
	System::UnicodeString FUserName;
	Datasnap::Midas::_di_IAppServer FAppServer;
	Soap::Soapmidas::_di_IAppServerSOAP FSOAPServer;
	bool FUseSOAPAdapter;
	System::UnicodeString FSOAPServerIID;
	Soap::Rio::TAfterExecuteEvent FOnAfterExecute;
	Soap::Rio::TBeforeExecuteEvent FOnBeforeExecute;
	System::UnicodeString __fastcall GetAgent();
	System::UnicodeString __fastcall GetPassword();
	System::UnicodeString __fastcall GetProxy();
	System::UnicodeString __fastcall GetUserName();
	void __fastcall SetAgent(const System::UnicodeString Value);
	void __fastcall SetPassword(const System::UnicodeString Value);
	void __fastcall SetProxy(const System::UnicodeString Value);
	void __fastcall SetURL(const System::UnicodeString Value);
	void __fastcall SetUserName(const System::UnicodeString Value);
	
protected:
	virtual void __fastcall DoConnect();
	virtual bool __fastcall GetConnected();
	virtual void __fastcall DoDisconnect();
	virtual void __fastcall Notification(System::Classes::TComponent* AComponent, System::Classes::TOperation Operation);
	void __fastcall SetUseSoapAdapter(bool Value);
	void __fastcall SetSOAPServerIID(const System::UnicodeString IID);
	GUID __fastcall GetSOAPServerIID();
	
public:
	__fastcall virtual TSoapConnection(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TSoapConnection();
	virtual System::OleVariant __fastcall GetServerList();
	virtual void __fastcall GetProviderNames(System::Classes::TGetStrProc Proc);
	virtual Datasnap::Midas::_di_IAppServer __fastcall GetServer();
	Soap::Soapmidas::_di_IAppServerSOAP __fastcall GetSOAPServer();
	__property Soap::Soaphttpclient::THTTPRIO* RIO = {read=FRIO};
	
__published:
	__property System::UnicodeString Agent = {read=GetAgent, write=SetAgent};
	__property Connected = {default=0};
	__property AfterConnect;
	__property BeforeConnect;
	__property AfterDisconnect;
	__property BeforeDisconnect;
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
	__property System::UnicodeString Proxy = {read=GetProxy, write=SetProxy};
	__property System::UnicodeString URL = {read=FURL, write=SetURL};
	__property System::UnicodeString SOAPServerIID = {read=FSOAPServerIID, write=SetSOAPServerIID};
	__property System::UnicodeString UserName = {read=GetUserName, write=SetUserName};
	__property bool UseSOAPAdapter = {read=FUseSOAPAdapter, write=SetUseSoapAdapter, nodefault};
	__property Soap::Rio::TAfterExecuteEvent OnAfterExecute = {read=FOnAfterExecute, write=FOnAfterExecute};
	__property Soap::Rio::TBeforeExecuteEvent OnBeforeExecute = {read=FOnBeforeExecute, write=FOnBeforeExecute};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soapconn */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPCONN)
using namespace Soap::Soapconn;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoapconnHPP
