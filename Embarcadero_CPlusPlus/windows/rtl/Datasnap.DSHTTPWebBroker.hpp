// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSHTTPWebBroker.pas' rev: 34.00 (Windows)

#ifndef Datasnap_DshttpwebbrokerHPP
#define Datasnap_DshttpwebbrokerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Web.AutoDisp.hpp>
#include <System.Classes.hpp>
#include <Datasnap.DSHTTPCommon.hpp>
#include <Datasnap.DSHTTP.hpp>
#include <Web.HTTPApp.hpp>
#include <System.Masks.hpp>
#include <System.SysUtils.hpp>
#include <Datasnap.DSSession.hpp>
#include <Datasnap.DSCommonServer.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dshttpwebbroker
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSWebDispatch;
class DELPHICLASS TDSHTTPWebDispatch;
class DELPHICLASS TDSRESTWebDispatch;
class DELPHICLASS TDSRESTWebDispatcher;
class DELPHICLASS TDSHTTPWebDispatcher;
class DELPHICLASS TDSHTTPContextWebBroker;
class DELPHICLASS TDSHTTPRequestWebBroker;
class DELPHICLASS TDSHTTPResponseWebBroker;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSWebDispatch : public Web::Autodisp::TWebDispatch
{
	typedef Web::Autodisp::TWebDispatch inherited;
	
private:
	bool FCustomPathInfo;
	virtual bool __fastcall IsPathInfoStored();
	virtual System::UnicodeString __fastcall GetDefaultPathInfo() = 0 ;
	
protected:
	virtual void __fastcall SetPathInfo(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetPathInfo();
	
public:
	__fastcall TDSWebDispatch(System::Classes::TComponent* AComponent);
	
__published:
	__property MethodType = {default=0};
	__property PathInfo = {stored=IsPathInfoStored};
public:
	/* TWebDispatch.Destroy */ inline __fastcall virtual ~TDSWebDispatch() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPWebDispatch : public TDSWebDispatch
{
	typedef TDSWebDispatch inherited;
	
private:
	TDSHTTPWebDispatcher* FDispatcher;
	virtual System::UnicodeString __fastcall GetDefaultPathInfo();
	
public:
	__fastcall TDSHTTPWebDispatch(TDSHTTPWebDispatcher* AComponent);
public:
	/* TWebDispatch.Destroy */ inline __fastcall virtual ~TDSHTTPWebDispatch() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSRESTWebDispatch : public TDSWebDispatch
{
	typedef TDSWebDispatch inherited;
	
private:
	TDSRESTWebDispatcher* FDispatcher;
	virtual System::UnicodeString __fastcall GetDefaultPathInfo();
	
public:
	__fastcall TDSRESTWebDispatch(TDSRESTWebDispatcher* AComponent);
public:
	/* TWebDispatch.Destroy */ inline __fastcall virtual ~TDSRESTWebDispatch() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TDSRESTWebDispatcher : public Datasnap::Dshttp::TDSRESTServerTransport
{
	typedef Datasnap::Dshttp::TDSRESTServerTransport inherited;
	
private:
	TDSWebDispatch* FWebDispatch;
	void __fastcall SetWebDispatch(TDSWebDispatch* const Value);
	System::UnicodeString __fastcall GetDefaultPathInfo();
	
protected:
	virtual Datasnap::Dshttp::TDSRESTServer* __fastcall CreateRESTServer();
	bool __fastcall DispatchEnabled();
	System::Masks::TMask* __fastcall DispatchMask();
	Web::Httpapp::TMethodType __fastcall DispatchMethodType();
	bool __fastcall DispatchRequest(System::TObject* Sender, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response);
	
public:
	__fastcall virtual TDSRESTWebDispatcher(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSRESTWebDispatcher();
	
__published:
	__property TDSWebDispatch* WebDispatch = {read=FWebDispatch, write=SetWebDispatch};
private:
	void *__IWebDispatch;	// Web::Httpapp::IWebDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E6D33BE4-9FAE-D511-8D38-0050568E0E44}
	operator Web::Httpapp::_di_IWebDispatch()
	{
		Web::Httpapp::_di_IWebDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Web::Httpapp::IWebDispatch*(void) { return (Web::Httpapp::IWebDispatch*)&__IWebDispatch; }
	#endif
	
};


class PASCALIMPLEMENTATION TDSHTTPWebDispatcher : public Datasnap::Dshttp::TDSHTTPServerTransport
{
	typedef Datasnap::Dshttp::TDSHTTPServerTransport inherited;
	
private:
	TDSWebDispatch* FWebDispatch;
	void __fastcall SetWebDispatch(TDSWebDispatch* const Value);
	System::UnicodeString __fastcall GetDefaultPathInfo();
	
protected:
	virtual Datasnap::Dshttp::TDSHTTPServer* __fastcall CreateHttpServer();
	bool __fastcall DispatchEnabled();
	System::Masks::TMask* __fastcall DispatchMask();
	Web::Httpapp::TMethodType __fastcall DispatchMethodType();
	bool __fastcall DispatchRequest(System::TObject* Sender, Web::Httpapp::TWebRequest* Request, Web::Httpapp::TWebResponse* Response);
	
public:
	__fastcall virtual TDSHTTPWebDispatcher(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TDSHTTPWebDispatcher();
	
__published:
	__property TDSWebDispatch* WebDispatch = {read=FWebDispatch, write=SetWebDispatch};
private:
	void *__IWebDispatch;	// Web::Httpapp::IWebDispatch 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {E6D33BE4-9FAE-D511-8D38-0050568E0E44}
	operator Web::Httpapp::_di_IWebDispatch()
	{
		Web::Httpapp::_di_IWebDispatch intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Web::Httpapp::IWebDispatch*(void) { return (Web::Httpapp::IWebDispatch*)&__IWebDispatch; }
	#endif
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPContextWebBroker : public Datasnap::Dshttpcommon::TDSHTTPContext
{
	typedef Datasnap::Dshttpcommon::TDSHTTPContext inherited;
	
private:
	TDSHTTPRequestWebBroker* FRequest;
	TDSHTTPResponseWebBroker* FResponse;
	
public:
	__fastcall TDSHTTPContextWebBroker(Web::Httpapp::TWebRequest* const ARequest, Web::Httpapp::TWebResponse* const AResponse);
	__fastcall virtual ~TDSHTTPContextWebBroker();
	virtual bool __fastcall Connected();
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPRequestWebBroker : public Datasnap::Dshttpcommon::TDSHTTPRequest
{
	typedef Datasnap::Dshttpcommon::TDSHTTPRequest inherited;
	
private:
	Web::Httpapp::TWebRequest* FRequestInfo;
	System::Classes::TMemoryStream* FPostStream;
	System::Classes::TStrings* FParams;
	System::UnicodeString FAuthUserName;
	System::UnicodeString FAuthPassword;
	bool FHaveAuth;
	void __fastcall UpdateAuthStrings();
	
protected:
	virtual System::UnicodeString __fastcall GetCommand();
	virtual Datasnap::Dshttpcommon::TDSHTTPCommandType __fastcall GetCommandType();
	virtual System::UnicodeString __fastcall GetDocument();
	virtual System::Classes::TStrings* __fastcall GetParams();
	virtual System::Classes::TStream* __fastcall GetPostStream();
	virtual System::UnicodeString __fastcall GetAuthUserName();
	virtual System::UnicodeString __fastcall GetAuthPassword();
	virtual System::UnicodeString __fastcall GetURI();
	virtual System::UnicodeString __fastcall GetPragma();
	virtual System::UnicodeString __fastcall GetAccept();
	virtual System::UnicodeString __fastcall GetRemoteIP();
	virtual System::UnicodeString __fastcall GetUserAgent();
	virtual System::UnicodeString __fastcall GetProtocolVersion();
	
public:
	__fastcall TDSHTTPRequestWebBroker(Web::Httpapp::TWebRequest* ARequestInfo);
	__fastcall virtual ~TDSHTTPRequestWebBroker();
	__property Web::Httpapp::TWebRequest* WebRequest = {read=FRequestInfo};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSHTTPResponseWebBroker : public Datasnap::Dshttpcommon::TDSHTTPResponse
{
	typedef Datasnap::Dshttpcommon::TDSHTTPResponse inherited;
	
private:
	Web::Httpapp::TWebResponse* FResponseInfo;
	bool FCloseConnection;
	
protected:
	virtual System::Classes::TStream* __fastcall GetContentStream();
	virtual int __fastcall GetResponseNo();
	virtual System::UnicodeString __fastcall GetResponseText();
	virtual void __fastcall SetContentStream(System::Classes::TStream* const Value);
	virtual void __fastcall SetResponseNo(const int Value);
	virtual void __fastcall SetResponseText(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetContentText();
	virtual void __fastcall SetContentText(const System::UnicodeString Value);
	virtual __int64 __fastcall GetContentLength();
	virtual void __fastcall SetContentLength(const __int64 Value);
	virtual bool __fastcall GetCloseConnection();
	virtual void __fastcall SetCloseConnection(const bool Value);
	virtual System::UnicodeString __fastcall GetPragma();
	virtual void __fastcall SetPragma(const System::UnicodeString Value);
	virtual System::UnicodeString __fastcall GetContentType();
	virtual void __fastcall SetContentType(const System::UnicodeString Value);
	virtual bool __fastcall GetFreeContentStream();
	virtual void __fastcall SetFreeContentStream(const bool Value);
	
public:
	__fastcall TDSHTTPResponseWebBroker(Web::Httpapp::TWebResponse* AResponseInfo);
	virtual void __fastcall SetHeaderAuthentication(const System::UnicodeString Value, const System::UnicodeString Realm);
	__property Web::Httpapp::TWebResponse* WebResponse = {read=FResponseInfo};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDSHTTPResponseWebBroker() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE Web::Httpapp::TWebModule* __fastcall GetDataSnapWebModule(void);
}	/* namespace Dshttpwebbroker */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSHTTPWEBBROKER)
using namespace Datasnap::Dshttpwebbroker;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DshttpwebbrokerHPP
