// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Datasnap.DSHTTPClient.pas' rev: 34.00 (iOS)

#ifndef Datasnap_DshttpclientHPP
#define Datasnap_DshttpclientHPP

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
#include <Data.DBXCommon.hpp>
#include <System.Net.HttpClient.hpp>
#include <System.Net.URLClient.hpp>

//-- user supplied -----------------------------------------------------------

namespace Datasnap
{
namespace Dshttpclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EHTTPProtocolException;
class DELPHICLASS TDSHTTP;
class DELPHICLASS TDSHTTPS;
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


_DECLARE_METACLASS(System::TMetaClass, TDSHTTPClass);

class PASCALIMPLEMENTATION TDSHTTP : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
	
public:
	typedef System::Net::Urlclient::TValidateCertificateEvent TValidateCertificateEvent;
	
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
		virtual System::UnicodeString __fastcall GetProxyScheme() = 0 ;
		virtual void __fastcall SetProxyScheme(System::UnicodeString Val) = 0 ;
		__property System::UnicodeString ProxyScheme = {read=GetProxyScheme, write=SetProxyScheme};
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
	__interface IRequestHeaderList  : public TDSHTTP::IHeaderList 
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
		virtual TDSHTTP::_di_IRequestHeaderList __fastcall GetCustomHeaders() = 0 ;
		__property TDSHTTP::_di_IRequestHeaderList CustomHeaders = {read=GetCustomHeaders};
		virtual System::UnicodeString __fastcall GetAcceptEncoding() = 0 ;
		virtual void __fastcall SetAcceptEncoding(const System::UnicodeString Val) = 0 ;
		__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding};
		virtual System::UnicodeString __fastcall GetContentType() = 0 ;
		virtual void __fastcall SetContentType(System::UnicodeString LContentType) = 0 ;
		__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
		virtual System::UnicodeString __fastcall GetUserAgent() = 0 ;
		virtual void __fastcall SetUserAgent(const System::UnicodeString Val) = 0 ;
		__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent};
		virtual System::UnicodeString __fastcall GetUserName() = 0 ;
		virtual System::UnicodeString __fastcall GetPassword() = 0 ;
		virtual void __fastcall SetAuthentication(const System::UnicodeString AUserName, const System::UnicodeString APassword) = 0 ;
	};
	
	__interface DELPHIINTERFACE IResponse;
	typedef System::DelphiInterface<IResponse> _di_IResponse;
	__interface IResponse  : public System::IInterface 
	{
		virtual System::UnicodeString __fastcall GetCharSet() = 0 ;
		__property System::UnicodeString CharSet = {read=GetCharSet};
		virtual System::UnicodeString __fastcall GetContentType() = 0 ;
		__property System::UnicodeString ContentType = {read=GetContentType};
		virtual System::UnicodeString __fastcall GetContentEncoding() = 0 ;
		__property System::UnicodeString ContentEncoding = {read=GetContentEncoding};
		virtual TDSHTTP::_di_IHeaderList __fastcall GetHeaders() = 0 ;
		__property TDSHTTP::_di_IHeaderList Headers = {read=GetHeaders};
	};
	
	
private:
	System::Net::Httpclient::THTTPClient* FHTTPClient;
	System::Net::Httpclient::_di_IHTTPResponse FHTTPResponse;
	_di_IRequest FIPHTTPRequestIntf;
	_di_IProxyConnectionInfo FProxyConnectionInfo;
	System::Net::Urlclient::TValidateCertificateEvent FOnValidateCertificate;
	Data::Dbxcommon::TValidateCertificate FOnValidatePeerCertificate;
	Data::Dbxcommon::TValidateCertificateErr FOnValidatePeerCertificateErr;
	System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent FOnAuthEvent;
	System::UnicodeString FProtocol;
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
	void __fastcall DoCustomAuthentication(System::TObject* const Sender, System::Net::Urlclient::TAuthTargetType AnAuthTarget, const System::UnicodeString ARealm, const System::UnicodeString AURL, System::UnicodeString &AUserName, System::UnicodeString &APassword, bool &AbortAuth, System::Net::Urlclient::TAuthPersistenceType &Persistence);
	void __fastcall DoValidateServerCertificate(System::TObject* const Sender, System::Net::Urlclient::TURLRequest* const ARequest, const System::Net::Urlclient::TCertificate &Certificate, bool &Accepted);
	System::UnicodeString __fastcall GetProtocol();
	void __fastcall SetProtocol(const System::UnicodeString protocol);
	System::Net::Urlclient::TNeedClientCertificateEvent __fastcall GetOnSelectClientCertificate();
	void __fastcall SetOnSelectClientCertificate(const System::Net::Urlclient::TNeedClientCertificateEvent Value);
	System::Net::Httpclient::THTTPSecureProtocols __fastcall GetSecureProtocols();
	void __fastcall SetSecureProtocols(const System::Net::Httpclient::THTTPSecureProtocols Value);
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	
public:
	__fastcall virtual TDSHTTP()/* overload */;
	__fastcall virtual TDSHTTP(System::Classes::TComponent* AOwner)/* overload */;
	__fastcall virtual ~TDSHTTP();
	__classmethod virtual bool __fastcall HasPeerCertificate();
	static System::TArray__1<System::UnicodeString> __fastcall RegisteredProtocolList();
	static TDSHTTPClass __fastcall ProtocolClass(const System::UnicodeString AName);
	void __fastcall Delete(const System::UnicodeString AURL, System::Classes::TStream* AResponseStream = (System::Classes::TStream*)(0x0));
	void __fastcall Merge(const System::UnicodeString AURL, System::Classes::TStream* ARequestStream = (System::Classes::TStream*)(0x0));
	void __fastcall Head(const System::UnicodeString AURL);
	void __fastcall Patch(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent = (System::Classes::TStream*)(0x0));
	void __fastcall Put(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent = (System::Classes::TStream*)(0x0));
	void __fastcall Post(const System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent = (System::Classes::TStream*)(0x0));
	void __fastcall Get(const System::UnicodeString AURL, System::Classes::TStream* AResponseContent = (System::Classes::TStream*)(0x0));
	void __fastcall SetAuthentication(const System::UnicodeString user, const System::UnicodeString password);
	void __fastcall ClearClientCredentials();
	System::TArray__1<System::Net::Urlclient::TCredentialsStorage::TCredential> __fastcall GetClientCredentials();
	void __fastcall AddServerCookie(const System::UnicodeString ACookie, const System::UnicodeString AURL);
	__property _di_IRequest Request = {read=GetRequest};
	__property _di_IResponse Response = {read=GetResponse};
	__property _di_IProxyConnectionInfo ProxyParams = {read=GetProxyParams};
	__property int ResponseCode = {read=GetResponseCode, nodefault};
	__property System::UnicodeString ResponseText = {read=GetResponseText};
	__property bool HandleRedirects = {read=GetHandleRedirects, write=SetHandleRedirects, nodefault};
	__property bool AllowCookies = {read=GetAllowCookies, write=SetAllowCookies, nodefault};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, nodefault};
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout, nodefault};
	__property System::Net::Httpclient::THTTPSecureProtocols SecureProtocols = {read=GetSecureProtocols, write=SetSecureProtocols, nodefault};
	__property System::Net::Urlclient::TValidateCertificateEvent OnValidateCertificate = {read=FOnValidateCertificate, write=FOnValidateCertificate};
	__property System::Net::Urlclient::TNeedClientCertificateEvent OnSelectClientCertificate = {read=GetOnSelectClientCertificate, write=SetOnSelectClientCertificate};
	__property Data::Dbxcommon::TValidateCertificate OnValidatePeerCertificate = {read=FOnValidatePeerCertificate, write=FOnValidatePeerCertificate};
	__property Data::Dbxcommon::TValidateCertificateErr OnValidatePeerCertificateErr = {read=FOnValidatePeerCertificateErr, write=FOnValidatePeerCertificateErr};
	__property System::Net::Urlclient::TCredentialsStorage::TCredentialAuthEvent OnCustomAuthentication = {read=FOnAuthEvent, write=FOnAuthEvent};
	void __fastcall Disconnect();
	__property System::UnicodeString protocol = {read=GetProtocol, write=SetProtocol};
};


class PASCALIMPLEMENTATION TDSHTTPS : public TDSHTTP
{
	typedef TDSHTTP inherited;
	
public:
	__classmethod virtual bool __fastcall HasPeerCertificate();
public:
	/* TDSHTTP.Create */ inline __fastcall virtual TDSHTTPS()/* overload */ : TDSHTTP() { }
	/* TDSHTTP.Create */ inline __fastcall virtual TDSHTTPS(System::Classes::TComponent* AOwner)/* overload */ : TDSHTTP(AOwner) { }
	/* TDSHTTP.Destroy */ inline __fastcall virtual ~TDSHTTPS() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dshttpclient */
}	/* namespace Datasnap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP_DSHTTPCLIENT)
using namespace Datasnap::Dshttpclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATASNAP)
using namespace Datasnap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Datasnap_DshttpclientHPP
