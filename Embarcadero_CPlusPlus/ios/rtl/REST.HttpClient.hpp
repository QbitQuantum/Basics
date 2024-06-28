// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.HttpClient.pas' rev: 34.00 (iOS)

#ifndef Rest_HttpclientHPP
#define Rest_HttpclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Net.HttpClient.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Httpclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EHTTPProtocolException;
class DELPHICLASS TRESTHTTP;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION EHTTPProtocolException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
private:
	System::UnicodeString FErrorMessage;
	int FErrorCode;
	
public:
	__fastcall EHTTPProtocolException(int AErrorCode, const System::UnicodeString AErrorMessage, const System::UnicodeString AMessage);
	__property int ErrorCode = {read=FErrorCode, nodefault};
	__property System::UnicodeString ErrorMessage = {read=FErrorMessage};
public:
	/* Exception.CreateFmt */ inline __fastcall EHTTPProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EHTTPProtocolException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EHTTPProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EHTTPProtocolException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EHTTPProtocolException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHTTPProtocolException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHTTPProtocolException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHTTPProtocolException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EHTTPProtocolException() { }
	
};


class PASCALIMPLEMENTATION TRESTHTTP : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE IProxyConnectionInfo;
	typedef System::DelphiInterface<IProxyConnectionInfo> _di_IProxyConnectionInfo;
	__interface IProxyConnectionInfo  : public System::IInterface 
	{
		virtual void __fastcall SetProxyPort(int Val) = 0 ;
		virtual int __fastcall GetProxyPort() = 0 ;
		__property int ProxyPort = {read=GetProxyPort, write=SetProxyPort};
		virtual System::UnicodeString __fastcall GetProxyServer() = 0 ;
		virtual void __fastcall SetProxyServer(System::UnicodeString Val) = 0 ;
		__property System::UnicodeString ProxyServer = {read=GetProxyServer, write=SetProxyServer};
		virtual System::UnicodeString __fastcall GetProxyUserName() = 0 ;
		virtual void __fastcall SetProxyUserName(System::UnicodeString user) = 0 ;
		__property System::UnicodeString ProxyUserName = {read=GetProxyUserName, write=SetProxyUserName};
		virtual System::UnicodeString __fastcall GetProxyPassword() = 0 ;
		virtual void __fastcall SetProxyPassword(System::UnicodeString pass) = 0 ;
		__property System::UnicodeString ProxyPassword = {read=GetProxyPassword, write=SetProxyPassword};
	};
	
	__interface DELPHIINTERFACE IHeaderList;
	typedef System::DelphiInterface<IHeaderList> _di_IHeaderList;
	__interface IHeaderList  : public System::IInterface 
	{
		virtual int __fastcall GetCount() = 0 ;
		__property int Count = {read=GetCount};
		virtual System::UnicodeString __fastcall GetName(int Index) = 0 ;
		__property System::UnicodeString Names[int Index] = {read=GetName};
		virtual System::UnicodeString __fastcall GetValue(const System::UnicodeString Name) = 0 ;
		__property System::UnicodeString Values[const System::UnicodeString Name] = {read=GetValue};
	};
	
	__interface DELPHIINTERFACE IRequestHeaderList;
	typedef System::DelphiInterface<IRequestHeaderList> _di_IRequestHeaderList;
	__interface IRequestHeaderList  : public TRESTHTTP::IHeaderList 
	{
		virtual void __fastcall Clear() = 0 ;
		virtual void __fastcall SetValue(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
		__property System::UnicodeString Values[const System::UnicodeString Name] = {read=GetValue, write=SetValue};
	};
	
	__interface DELPHIINTERFACE IRequest;
	typedef System::DelphiInterface<IRequest> _di_IRequest;
	__interface IRequest  : public System::IInterface 
	{
		virtual System::UnicodeString __fastcall GetAccept() = 0 ;
		virtual void __fastcall SetAccept(const System::UnicodeString Val) = 0 ;
		__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept};
		virtual System::UnicodeString __fastcall GetAcceptCharSet() = 0 ;
		virtual void __fastcall SetAcceptCharSet(const System::UnicodeString Val) = 0 ;
		__property System::UnicodeString AcceptCharSet = {read=GetAcceptCharSet, write=SetAcceptCharSet};
		virtual TRESTHTTP::_di_IRequestHeaderList __fastcall GetCustomHeaders() = 0 ;
		__property TRESTHTTP::_di_IRequestHeaderList CustomHeaders = {read=GetCustomHeaders};
		virtual System::UnicodeString __fastcall GetAcceptEncoding() = 0 ;
		virtual void __fastcall SetAcceptEncoding(const System::UnicodeString Val) = 0 ;
		__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding};
		virtual System::UnicodeString __fastcall GetContentType() = 0 ;
		virtual void __fastcall SetContentType(System::UnicodeString LContentType) = 0 ;
		__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
		virtual System::UnicodeString __fastcall GetUserAgent() = 0 ;
		virtual void __fastcall SetUserAgent(const System::UnicodeString Val) = 0 ;
		__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent};
	};
	
	__interface DELPHIINTERFACE IURLResponse;
	typedef System::DelphiInterface<IURLResponse> _di_IURLResponse;
	__interface IURLResponse  : public System::IInterface 
	{
		virtual System::UnicodeString __fastcall ContentAsString(System::Sysutils::TEncoding* const AnEncoding = (System::Sysutils::TEncoding*)(0x0)) = 0 ;
	};
	
	__interface DELPHIINTERFACE IResponse;
	typedef System::DelphiInterface<IResponse> _di_IResponse;
	__interface IResponse  : public TRESTHTTP::IURLResponse 
	{
		virtual System::UnicodeString __fastcall GetCharSet() = 0 ;
		__property System::UnicodeString CharSet = {read=GetCharSet};
		virtual System::UnicodeString __fastcall GetContentType() = 0 ;
		__property System::UnicodeString ContentType = {read=GetContentType};
		virtual System::UnicodeString __fastcall GetContentEncoding() = 0 ;
		__property System::UnicodeString ContentEncoding = {read=GetContentEncoding};
		virtual TRESTHTTP::_di_IHeaderList __fastcall GetHeaders() = 0 ;
		virtual System::Net::Httpclient::TCookies* __fastcall GetCookies() = 0 ;
		__property TRESTHTTP::_di_IHeaderList Headers = {read=GetHeaders};
		__property System::Net::Httpclient::TCookies* Cookies = {read=GetCookies};
	};
	
	
private:
	System::Net::Httpclient::THTTPClient* FHTTPClient;
	System::Net::Httpclient::_di_IHTTPRequest FHTTPRequest;
	System::Net::Httpclient::_di_IHTTPResponse FHTTPResponse;
	_di_IRequest FIPHTTPRequestIntf;
	_di_IProxyConnectionInfo FProxyConnectionInfo;
	System::Net::Urlclient::TValidateCertificateEvent FOnValidateCertificate;
	_di_IRequest __fastcall GetRequest();
	_di_IResponse __fastcall GetResponse();
	_di_IProxyConnectionInfo __fastcall GetProxyParams();
	int __fastcall GetResponseCode();
	System::UnicodeString __fastcall GetResponseText();
	bool __fastcall GetHandleRedirects();
	void __fastcall SetHandleRedirects(bool AValue);
	bool __fastcall GetAllowCookies();
	void __fastcall SetAllowCookies(bool AValue);
	int __fastcall GetConnectTimeout();
	void __fastcall SetConnectTimeout(const int Value);
	int __fastcall GetReadTimeout();
	void __fastcall SetReadTimeout(const int Value);
	void __fastcall CheckResponse();
	void __fastcall PrepareRequest(const System::Net::Httpclient::_di_IHTTPRequest ARequest);
	void __fastcall Execute(const System::UnicodeString AMethod, System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Execute(const System::UnicodeString AMethod, System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall RaiseProtocolException(const System::Net::Httpclient::_di_IHTTPResponse AResponse);
	void __fastcall DoValidateServerCertificate(System::TObject* const Sender, System::Net::Urlclient::TURLRequest* const ARequest, const System::Net::Urlclient::TCertificate &Certificate, bool &Accepted);
	System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent __fastcall GetAuthEvent();
	System::Net::Urlclient::TNeedClientCertificateEvent __fastcall GetNeedClientCertificateEvent();
	System::Net::Httpclient::THTTPRedirectsWithGET __fastcall GetRedirectsWithGET();
	System::Net::Httpclient::THTTPSecureProtocols __fastcall GetSecureProtocols();
	void __fastcall SetAuthEvent(const System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent AValue);
	void __fastcall SetNeedClientCertificateEvent(const System::Net::Urlclient::TNeedClientCertificateEvent AValue);
	void __fastcall SetRedirectsWithGET(const System::Net::Httpclient::THTTPRedirectsWithGET AValue);
	void __fastcall SetSecureProtocols(const System::Net::Httpclient::THTTPSecureProtocols AValue);
	int __fastcall GetSendTimeout();
	void __fastcall SetSendTimeout(const int AValue);
	bool __fastcall GetIsCancelled();
	
public:
	__fastcall TRESTHTTP();
	__fastcall virtual ~TRESTHTTP();
	void __fastcall Delete(const System::UnicodeString AURL, System::Classes::TStream* AResponseStream)/* overload */;
	void __fastcall Delete(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseStream)/* overload */;
	void __fastcall Patch(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent);
	void __fastcall Put(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent);
	void __fastcall Post(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent);
	void __fastcall Get(const System::UnicodeString AURL, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall Get(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent)/* overload */;
	void __fastcall AddServerCookie(const System::UnicodeString ACookie, const System::UnicodeString AURL);
	void __fastcall Cancel();
	__property bool IsCancelled = {read=GetIsCancelled, nodefault};
	__property _di_IRequest Request = {read=GetRequest};
	__property _di_IResponse Response = {read=GetResponse};
	__property _di_IProxyConnectionInfo ProxyParams = {read=GetProxyParams};
	__property int ResponseCode = {read=GetResponseCode, nodefault};
	__property System::UnicodeString ResponseText = {read=GetResponseText};
	__property bool HandleRedirects = {read=GetHandleRedirects, write=SetHandleRedirects, nodefault};
	__property System::Net::Httpclient::THTTPRedirectsWithGET RedirectsWithGET = {read=GetRedirectsWithGET, write=SetRedirectsWithGET, nodefault};
	__property System::Net::Httpclient::THTTPSecureProtocols SecureProtocols = {read=GetSecureProtocols, write=SetSecureProtocols, nodefault};
	__property bool AllowCookies = {read=GetAllowCookies, write=SetAllowCookies, nodefault};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, nodefault};
	__property int SendTimeout = {read=GetSendTimeout, write=SetSendTimeout, nodefault};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, nodefault};
	__property System::Net::Urlclient::TValidateCertificateEvent OnValidateCertificate = {read=FOnValidateCertificate, write=FOnValidateCertificate};
	__property System::Net::Urlclient::TNeedClientCertificateEvent OnNeedClientCertificate = {read=GetNeedClientCertificateEvent, write=SetNeedClientCertificateEvent};
	__property System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent OnAuthEvent = {read=GetAuthEvent, write=SetAuthEvent};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Httpclient */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_HTTPCLIENT)
using namespace Rest::Httpclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_HttpclientHPP
