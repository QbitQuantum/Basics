// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Net.HttpClient.pas' rev: 34.00 (Android)

#ifndef System_Net_HttpclientHPP
#define System_Net_HttpclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Net.Mime.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Net
{
namespace Httpclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ENetHTTPException;
class DELPHICLASS ENetHTTPClientException;
class DELPHICLASS ENetHTTPRequestException;
class DELPHICLASS ENetHTTPResponseException;
class DELPHICLASS ENetHTTPCertificateException;
__interface DELPHIINTERFACE TReceiveDataCallback;
typedef System::DelphiInterface<TReceiveDataCallback> _di_TReceiveDataCallback;
__interface DELPHIINTERFACE TSendDataCallback;
typedef System::DelphiInterface<TSendDataCallback> _di_TSendDataCallback;
struct TCookie;
struct TCookieHelper /* Helper for record 'TCookie' */;
class DELPHICLASS TCookies;
class DELPHICLASS TCookieManager;
__interface DELPHIINTERFACE IHTTPRequest;
typedef System::DelphiInterface<IHTTPRequest> _di_IHTTPRequest;
class DELPHICLASS THTTPRequest;
__interface DELPHIINTERFACE IHTTPResponse;
typedef System::DelphiInterface<IHTTPResponse> _di_IHTTPResponse;
class DELPHICLASS THTTPResponse;
class DELPHICLASS THTTPClient;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENetHTTPException : public System::Net::Urlclient::ENetURIException
{
	typedef System::Net::Urlclient::ENetURIException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetHTTPException(const System::UnicodeString Msg) : System::Net::Urlclient::ENetURIException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetHTTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Net::Urlclient::ENetURIException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPException(NativeUInt Ident)/* overload */ : System::Net::Urlclient::ENetURIException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPException(System::PResStringRec ResStringRec)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetHTTPException(const System::UnicodeString Msg, int AHelpContext) : System::Net::Urlclient::ENetURIException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetHTTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Net::Urlclient::ENetURIException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetHTTPException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENetHTTPClientException : public System::Net::Urlclient::ENetURIClientException
{
	typedef System::Net::Urlclient::ENetURIClientException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetHTTPClientException(const System::UnicodeString Msg) : System::Net::Urlclient::ENetURIClientException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetHTTPClientException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Net::Urlclient::ENetURIClientException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPClientException(NativeUInt Ident)/* overload */ : System::Net::Urlclient::ENetURIClientException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPClientException(System::PResStringRec ResStringRec)/* overload */ : System::Net::Urlclient::ENetURIClientException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPClientException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIClientException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPClientException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIClientException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetHTTPClientException(const System::UnicodeString Msg, int AHelpContext) : System::Net::Urlclient::ENetURIClientException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetHTTPClientException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Net::Urlclient::ENetURIClientException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPClientException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIClientException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPClientException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIClientException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPClientException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIClientException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPClientException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIClientException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetHTTPClientException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENetHTTPRequestException : public System::Net::Urlclient::ENetURIRequestException
{
	typedef System::Net::Urlclient::ENetURIRequestException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetHTTPRequestException(const System::UnicodeString Msg) : System::Net::Urlclient::ENetURIRequestException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetHTTPRequestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Net::Urlclient::ENetURIRequestException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPRequestException(NativeUInt Ident)/* overload */ : System::Net::Urlclient::ENetURIRequestException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPRequestException(System::PResStringRec ResStringRec)/* overload */ : System::Net::Urlclient::ENetURIRequestException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPRequestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIRequestException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPRequestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIRequestException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetHTTPRequestException(const System::UnicodeString Msg, int AHelpContext) : System::Net::Urlclient::ENetURIRequestException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetHTTPRequestException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Net::Urlclient::ENetURIRequestException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPRequestException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIRequestException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPRequestException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIRequestException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPRequestException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIRequestException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPRequestException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIRequestException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetHTTPRequestException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENetHTTPResponseException : public System::Net::Urlclient::ENetURIResponseException
{
	typedef System::Net::Urlclient::ENetURIResponseException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetHTTPResponseException(const System::UnicodeString Msg) : System::Net::Urlclient::ENetURIResponseException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetHTTPResponseException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Net::Urlclient::ENetURIResponseException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPResponseException(NativeUInt Ident)/* overload */ : System::Net::Urlclient::ENetURIResponseException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPResponseException(System::PResStringRec ResStringRec)/* overload */ : System::Net::Urlclient::ENetURIResponseException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPResponseException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIResponseException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPResponseException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIResponseException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetHTTPResponseException(const System::UnicodeString Msg, int AHelpContext) : System::Net::Urlclient::ENetURIResponseException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetHTTPResponseException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Net::Urlclient::ENetURIResponseException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPResponseException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIResponseException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPResponseException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIResponseException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPResponseException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIResponseException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPResponseException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIResponseException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetHTTPResponseException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ENetHTTPCertificateException : public System::Net::Urlclient::ENetURIException
{
	typedef System::Net::Urlclient::ENetURIException inherited;
	
public:
	/* Exception.Create */ inline __fastcall ENetHTTPCertificateException(const System::UnicodeString Msg) : System::Net::Urlclient::ENetURIException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ENetHTTPCertificateException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Net::Urlclient::ENetURIException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPCertificateException(NativeUInt Ident)/* overload */ : System::Net::Urlclient::ENetURIException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ENetHTTPCertificateException(System::PResStringRec ResStringRec)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPCertificateException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ENetHTTPCertificateException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ENetHTTPCertificateException(const System::UnicodeString Msg, int AHelpContext) : System::Net::Urlclient::ENetURIException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ENetHTTPCertificateException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Net::Urlclient::ENetURIException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPCertificateException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ENetHTTPCertificateException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPCertificateException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ENetHTTPCertificateException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetURIException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ENetHTTPCertificateException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum class DECLSPEC_DENUM THTTPProtocolVersion : unsigned char { UNKNOWN_HTTP, HTTP_1_0, HTTP_1_1, HTTP_2_0 };

enum class DECLSPEC_DENUM THTTPRedirectWithGET : unsigned char { Post301, Post302, Post303, Post307, Post308, Put301, Put302, Put303, Put307, Put308, Delete301, Delete302, Delete303, Delete307, Delete308 };

typedef System::Set<THTTPRedirectWithGET, _DELPHI_SET_ENUMERATOR(THTTPRedirectWithGET::Post301), _DELPHI_SET_ENUMERATOR(THTTPRedirectWithGET::Delete308)> THTTPRedirectsWithGET;

enum class DECLSPEC_DENUM THTTPSecureProtocol : unsigned char { SSL2, SSL3, TLS1, TLS11, TLS12, TLS13 };

typedef System::Set<THTTPSecureProtocol, _DELPHI_SET_ENUMERATOR(THTTPSecureProtocol::SSL2), _DELPHI_SET_ENUMERATOR(THTTPSecureProtocol::TLS13)> THTTPSecureProtocols;

enum class DECLSPEC_DENUM THTTPSecureFailureReason : unsigned char { CertRevFailed, InvalidCert, CertRevoked, InvalidCA, CertCNInvalid, CertDateInvalid, CertWrongUsage, SecurityChannelError, CertNotAccepted };

typedef System::Set<THTTPSecureFailureReason, _DELPHI_SET_ENUMERATOR(THTTPSecureFailureReason::CertRevFailed), _DELPHI_SET_ENUMERATOR(THTTPSecureFailureReason::CertNotAccepted)> THTTPSecureFailureReasons;

enum class DECLSPEC_DENUM THTTPCompressionMethod : unsigned char { Deflate, GZip, Brotli, Any };

typedef System::Set<THTTPCompressionMethod, _DELPHI_SET_ENUMERATOR(THTTPCompressionMethod::Deflate), _DELPHI_SET_ENUMERATOR(THTTPCompressionMethod::Any)> THTTPCompressionMethods;

__interface TReceiveDataCallback  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* const Sender, __int64 AContentLength, __int64 AReadCount, bool &AAbort) = 0 ;
};

typedef void __fastcall (__closure *TReceiveDataEvent)(System::TObject* const Sender, __int64 AContentLength, __int64 AReadCount, bool &AAbort);

__interface TSendDataCallback  : public System::IInterface 
{
	virtual void __fastcall Invoke(System::TObject* const Sender, __int64 AContentLength, __int64 AWriteCount, bool &AAbort) = 0 ;
};

typedef void __fastcall (__closure *TSendDataEvent)(System::TObject* const Sender, __int64 AContentLength, __int64 AWriteCount, bool &AAbort);

struct DECLSPEC_DRECORD TCookie
{
private:
	static System::TDateTime __fastcall StrExpiresToDateTime(const System::UnicodeString AStrDate);
	
public:
	System::UnicodeString Name;
	System::UnicodeString Value;
	System::TDateTime Expires;
	System::UnicodeString Domain;
	System::UnicodeString Path;
	bool Secure;
	bool HttpOnly;
	System::UnicodeString __fastcall ToString();
	static TCookie __fastcall Create(const System::UnicodeString ACookieData, const System::Net::Urlclient::TURI &AURI);
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCookies : public System::Generics::Collections::TList__1<TCookie>
{
	typedef System::Generics::Collections::TList__1<TCookie> inherited;
	
public:
	/* {System_Generics_Collections}TList<System_Net_HttpClient_TCookie>.Create */ inline __fastcall TCookies()/* overload */ : System::Generics::Collections::TList__1<TCookie>() { }
	/* {System_Generics_Collections}TList<System_Net_HttpClient_TCookie>.Create */ inline __fastcall TCookies(const System::DelphiInterface<System::Generics::Defaults::IComparer__1<TCookie> > AComparer)/* overload */ : System::Generics::Collections::TList__1<TCookie>(AComparer) { }
	/* {System_Generics_Collections}TList<System_Net_HttpClient_TCookie>.Create */ inline __fastcall TCookies(System::Generics::Collections::TEnumerable__1<TCookie>* const Collection)/* overload */ : System::Generics::Collections::TList__1<TCookie>(Collection) { }
	/* {System_Generics_Collections}TList<System_Net_HttpClient_TCookie>.Destroy */ inline __fastcall virtual ~TCookies() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef System::TArray__1<TCookie> TCookiesArray;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TCookieManager : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TCookies* FCookies;
	void __fastcall UpdateCookie(const TCookie &ACookie, const System::Net::Urlclient::TURI &AURL);
	bool __fastcall ValidCookie(const TCookie &ACookie, const System::Net::Urlclient::TURI &AURL);
	System::TArray__1<TCookie> __fastcall GetCookies();
	void __fastcall DeleteExpiredCookies();
	
public:
	__fastcall TCookieManager();
	__fastcall virtual ~TCookieManager();
	void __fastcall AddServerCookie(const System::UnicodeString ACookieData, const System::UnicodeString ACookieURL)/* overload */;
	void __fastcall AddServerCookie(const TCookie &ACookie, const System::Net::Urlclient::TURI &AURL)/* overload */;
	System::UnicodeString __fastcall CookieHeaders(const System::Net::Urlclient::TURI &AURI);
	void __fastcall Clear();
	__property System::TArray__1<TCookie> Cookies = {read=GetCookies};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface IHTTPRequest  : public System::Net::Urlclient::IURLRequest 
{
	virtual System::UnicodeString __fastcall GetHeaderValue(const System::UnicodeString AName) = 0 ;
	virtual void __fastcall SetHeaderValue(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
	__property System::UnicodeString HeaderValue[const System::UnicodeString AName] = {read=GetHeaderValue, write=SetHeaderValue};
	virtual System::TArray__1<System::Net::Urlclient::TNameValuePair> __fastcall GetHeaders() = 0 ;
	__property System::TArray__1<System::Net::Urlclient::TNameValuePair> Headers = {read=GetHeaders};
	virtual void __fastcall AddHeader(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
	virtual bool __fastcall RemoveHeader(const System::UnicodeString AName) = 0 ;
	virtual System::UnicodeString __fastcall GetAccept() = 0 ;
	virtual System::UnicodeString __fastcall GetAcceptCharSet() = 0 ;
	virtual System::UnicodeString __fastcall GetAcceptEncoding() = 0 ;
	virtual System::UnicodeString __fastcall GetAcceptLanguage() = 0 ;
	virtual System::UnicodeString __fastcall GetUserAgent() = 0 ;
	virtual void __fastcall SetAccept(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetAcceptCharSet(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetAcceptEncoding(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetAcceptLanguage(const System::UnicodeString Value) = 0 ;
	virtual void __fastcall SetUserAgent(const System::UnicodeString Value) = 0 ;
	virtual System::Classes::TStream* __fastcall GetClientCertificate() = 0 ;
	virtual void __fastcall SetClientCertificate(System::Classes::TStream* const Value, const System::UnicodeString Password) = 0 /* overload */;
	virtual void __fastcall SetClientCertificate(const System::UnicodeString Path, const System::UnicodeString Password) = 0 /* overload */;
	__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent};
	__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept};
	__property System::UnicodeString AcceptCharSet = {read=GetAcceptCharSet, write=SetAcceptCharSet};
	__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding};
	__property System::UnicodeString AcceptLanguage = {read=GetAcceptLanguage, write=SetAcceptLanguage};
	virtual _di_TSendDataCallback __fastcall GetSendDataCallback() = 0 ;
	virtual void __fastcall SetSendDataCallback(const _di_TSendDataCallback Value) = 0 ;
	virtual TSendDataEvent __fastcall GetSendDataEvent() = 0 ;
	virtual void __fastcall SetSendDataEvent(const TSendDataEvent Value) = 0 ;
	__property _di_TSendDataCallback SendDataCallback = {read=GetSendDataCallback, write=SetSendDataCallback};
	__property TSendDataEvent OnSendData = {read=GetSendDataEvent, write=SetSendDataEvent};
	virtual _di_TReceiveDataCallback __fastcall GetReceiveDataCallback() = 0 ;
	virtual void __fastcall SetReceiveDataCallback(const _di_TReceiveDataCallback Value) = 0 ;
	virtual TReceiveDataEvent __fastcall GetReceiveDataEvent() = 0 ;
	virtual void __fastcall SetReceiveDataEvent(const TReceiveDataEvent Value) = 0 ;
	__property _di_TReceiveDataCallback ReceiveDataCallback = {read=GetReceiveDataCallback, write=SetReceiveDataCallback};
	__property TReceiveDataEvent OnReceiveData = {read=GetReceiveDataEvent, write=SetReceiveDataEvent};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPRequest : public System::Net::Urlclient::TURLRequest
{
	typedef System::Net::Urlclient::TURLRequest inherited;
	
private:
	_di_TSendDataCallback FSendDataCallback;
	TSendDataEvent FOnSendData;
	_di_TReceiveDataCallback FReceiveDataCallback;
	TReceiveDataEvent FOnReceiveData;
	System::Classes::TStream* FOwnedStream;
	System::UnicodeString __fastcall GetAccept();
	System::UnicodeString __fastcall GetAcceptCharSet();
	System::UnicodeString __fastcall GetAcceptEncoding();
	System::UnicodeString __fastcall GetAcceptLanguage();
	System::UnicodeString __fastcall GetUserAgent();
	void __fastcall SetAccept(const System::UnicodeString Value);
	void __fastcall SetAcceptCharSet(const System::UnicodeString Value);
	void __fastcall SetAcceptEncoding(const System::UnicodeString Value);
	void __fastcall SetAcceptLanguage(const System::UnicodeString Value);
	void __fastcall SetUserAgent(const System::UnicodeString Value);
	_di_TSendDataCallback __fastcall GetSendDataCallback();
	void __fastcall SetSendDataCallback(const _di_TSendDataCallback Value);
	TSendDataEvent __fastcall GetSendDataEvent();
	void __fastcall SetSendDataEvent(const TSendDataEvent Value);
	_di_TReceiveDataCallback __fastcall GetReceiveDataCallback();
	void __fastcall SetReceiveDataCallback(const _di_TReceiveDataCallback Value);
	TReceiveDataEvent __fastcall GetReceiveDataEvent();
	void __fastcall SetReceiveDataEvent(const TReceiveDataEvent Value);
	System::Classes::TStream* __fastcall GetClientCertificate();
	
protected:
	System::Classes::TStream* FClientCertificate;
	System::UnicodeString FClientCertPassword;
	System::UnicodeString FClientCertPath;
	void __fastcall DoSendDataProgress(__int64 AContentLength, __int64 AWriteCount, bool &AAbort, bool AAllowCancel);
	void __fastcall DoReceiveDataProgress(int AStatusCode, __int64 AContentLength, __int64 AReadCount, bool &AAbort);
	virtual void __fastcall DoPrepare() = 0 ;
	void __fastcall SetClientCertificate(System::Classes::TStream* const Value, const System::UnicodeString Password)/* overload */;
	void __fastcall SetClientCertificate(const System::UnicodeString Path, const System::UnicodeString Password)/* overload */;
	void __fastcall BaseAddHeader(const System::UnicodeString AName, const System::UnicodeString AValue);
	__fastcall THTTPRequest(THTTPClient* const AClient, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI);
	
public:
	virtual System::TArray__1<System::Net::Urlclient::TNameValuePair> __fastcall GetHeaders() = 0 ;
	virtual System::UnicodeString __fastcall GetHeaderValue(const System::UnicodeString AName) = 0 ;
	virtual void __fastcall SetHeaderValue(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
	virtual void __fastcall AddHeader(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
	virtual bool __fastcall RemoveHeader(const System::UnicodeString AName) = 0 ;
	__property _di_TSendDataCallback SendDataCallback = {read=GetSendDataCallback, write=SetSendDataCallback};
	__property TSendDataEvent OnSendData = {read=GetSendDataEvent, write=SetSendDataEvent};
	__property _di_TReceiveDataCallback ReceiveDataCallback = {read=GetReceiveDataCallback, write=SetReceiveDataCallback};
	__property TReceiveDataEvent OnReceiveData = {read=GetReceiveDataEvent, write=SetReceiveDataEvent};
	__fastcall virtual ~THTTPRequest();
private:
	void *__IHTTPRequest;	// IHTTPRequest 
	
public:
	operator IHTTPRequest*(void) { return (IHTTPRequest*)&__IHTTPRequest; }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ED07313B-324B-448F-84AD-F199D38981DA}") IHTTPResponse  : public System::Net::Urlclient::IURLResponse 
{
	virtual System::UnicodeString __fastcall GetHeaderValue(const System::UnicodeString AName) = 0 ;
	virtual System::UnicodeString __fastcall GetContentCharSet() = 0 ;
	virtual System::UnicodeString __fastcall GetContentEncoding() = 0 ;
	virtual System::UnicodeString __fastcall GetContentLanguage() = 0 ;
	virtual __int64 __fastcall GetContentLength() = 0 ;
	virtual System::UnicodeString __fastcall GetDate() = 0 ;
	virtual System::UnicodeString __fastcall GetLastModified() = 0 ;
	virtual int __fastcall GetStatusCode() = 0 ;
	virtual System::UnicodeString __fastcall GetStatusText() = 0 ;
	virtual THTTPProtocolVersion __fastcall GetVersion() = 0 ;
	virtual bool __fastcall ContainsHeader(const System::UnicodeString AName) = 0 ;
	virtual TCookies* __fastcall GetCookies() = 0 ;
	__property System::UnicodeString HeaderValue[const System::UnicodeString AName] = {read=GetHeaderValue};
	__property System::UnicodeString ContentCharSet = {read=GetContentCharSet};
	__property System::UnicodeString ContentEncoding = {read=GetContentEncoding};
	__property System::UnicodeString ContentLanguage = {read=GetContentLanguage};
	__property __int64 ContentLength = {read=GetContentLength};
	__property System::UnicodeString Date = {read=GetDate};
	__property System::UnicodeString LastModified = {read=GetLastModified};
	__property System::UnicodeString StatusText = {read=GetStatusText};
	__property int StatusCode = {read=GetStatusCode};
	__property THTTPProtocolVersion Version = {read=GetVersion};
	__property TCookies* Cookies = {read=GetCookies};
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPResponse : public System::Net::Urlclient::TURLResponse
{
	typedef System::Net::Urlclient::TURLResponse inherited;
	
protected:
	System::TArray__1<System::Net::Urlclient::TNameValuePair> FHeaders;
	TCookies* FCookies;
	virtual void __fastcall DoReadData(System::Classes::TStream* const AStream) = 0 ;
	
public:
	HIDESBASE System::Classes::TStream* __fastcall GetContentStream();
	virtual System::UnicodeString __fastcall GetMimeType();
	virtual System::UnicodeString __fastcall ContentAsString(System::Sysutils::TEncoding* const AnEncoding = (System::Sysutils::TEncoding*)(0x0));
	virtual bool __fastcall ContainsHeader(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetHeaderValue(const System::UnicodeString AName);
	virtual System::UnicodeString __fastcall GetContentCharSet();
	virtual System::UnicodeString __fastcall GetContentEncoding();
	virtual System::UnicodeString __fastcall GetContentLanguage();
	virtual __int64 __fastcall GetContentLength();
	virtual System::UnicodeString __fastcall GetDate();
	virtual System::UnicodeString __fastcall GetLastModified();
	virtual int __fastcall GetStatusCode() = 0 ;
	virtual System::UnicodeString __fastcall GetStatusText() = 0 ;
	virtual THTTPProtocolVersion __fastcall GetVersion() = 0 ;
	virtual TCookies* __fastcall GetCookies();
	
protected:
	void __fastcall InternalAddCookie(const System::UnicodeString ACookieData);
	System::UnicodeString __fastcall InternalGetAuthRealm();
	__fastcall THTTPResponse(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AAsyncCallback, const System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent, const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */;
	
public:
	__fastcall virtual ~THTTPResponse();
protected:
	/* TURLResponse.Create */ inline __fastcall THTTPResponse(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AAsyncCallback, const System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent, const System::Net::Urlclient::_di_IURLRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */ : System::Net::Urlclient::TURLResponse(AContext, AProc, AAsyncCallback, AAsyncCallbackEvent, ARequest, AContentStream) { }
	/* TURLResponse.Create */ inline __fastcall THTTPResponse(System::TObject* const AContext, const System::Net::Urlclient::_di_IURLRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */ : System::Net::Urlclient::TURLResponse(AContext, ARequest, AContentStream) { }
	
protected:
	/* TBaseAsyncResult.Create */ inline __fastcall THTTPResponse(System::TObject* const AContext)/* overload */ : System::Net::Urlclient::TURLResponse(AContext) { }
	
public:
	/* TBaseAsyncResult.Create */ inline __fastcall THTTPResponse()/* overload */ : System::Net::Urlclient::TURLResponse() { }
	
private:
	void *__IHTTPResponse;	// IHTTPResponse 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {ED07313B-324B-448F-84AD-F199D38981DA}
	operator _di_IHTTPResponse()
	{
		_di_IHTTPResponse intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IHTTPResponse*(void) { return (IHTTPResponse*)&__IHTTPResponse; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION THTTPClient : public System::Net::Urlclient::TURLClient
{
	typedef System::Net::Urlclient::TURLClient inherited;
	
	
protected:
	enum class DECLSPEC_DENUM TExecutionResult : unsigned char { Success, UnknownError, ServerCertificateInvalid, ClientCertificateNeeded, Retry };
	
	enum class DECLSPEC_DENUM InternalState : unsigned char { Other, ProxyAuthRequired, ServerAuthRequired };
	
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD THTTPState
	{
	public:
		bool NeedProxyCredential;
		System::Net::Urlclient::TCredentialsStorage::TCredential ProxyCredential;
		System::TArray__1<System::Net::Urlclient::TCredentialsStorage::TCredential> ProxyCredentials;
		int ProxyIterator;
		bool NeedServerCredential;
		System::Net::Urlclient::TCredentialsStorage::TCredential ServerCredential;
		System::TArray__1<System::Net::Urlclient::TCredentialsStorage::TCredential> ServerCredentials;
		int ServerIterator;
		THTTPClient::InternalState Status;
		int Redirections;
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
private:
	bool FAllowCookies;
	bool FHandleRedirects;
	_di_TSendDataCallback FSendDataCallback;
	TSendDataEvent FOnSendData;
	_di_TReceiveDataCallback FReceiveDataCallback;
	TReceiveDataEvent FOnReceiveData;
	TCookieManager* FCookieManager;
	TCookieManager* FInternalCookieManager;
	THTTPRedirectsWithGET FRedirectsWithGET;
	THTTPSecureProtocols FSecureProtocols;
	bool FPreemptiveAuthentication;
	THTTPCompressionMethods FAutomaticDecompression;
	bool FUseDefaultCredentials;
	System::Net::Urlclient::TNameValuePair __fastcall CreateRangeHeader(__int64 AStart, __int64 AnEnd);
	void __fastcall DoNeedClientCertificate(THTTPRequest* const LRequest, System::Net::Urlclient::TCertificateList* const LClientCertificateList);
	void __fastcall DoValidateServerCertificate(THTTPRequest* LRequest);
	void __fastcall ExecuteHTTPInternal(const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream, const _di_IHTTPResponse AResponse);
	void __fastcall ExecuteHTTP(const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream, const _di_IHTTPResponse AResponse);
	bool __fastcall SetProxyCredential(THTTPRequest* const ARequest, THTTPResponse* const AResponse, THTTPState &State);
	bool __fastcall SetServerCredential(THTTPRequest* const ARequest, THTTPResponse* const AResponse, THTTPState &State);
	System::UnicodeString __fastcall GetAccept();
	System::UnicodeString __fastcall GetAcceptCharSet();
	System::UnicodeString __fastcall GetAcceptEncoding();
	System::UnicodeString __fastcall GetAcceptLanguage();
	void __fastcall SetAccept(const System::UnicodeString Value);
	void __fastcall SetAcceptCharSet(const System::UnicodeString Value);
	void __fastcall SetAcceptEncoding(const System::UnicodeString Value);
	void __fastcall SetAcceptLanguage(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetContentType();
	void __fastcall SetContentType(const System::UnicodeString Value);
	void __fastcall SetCookieManager(TCookieManager* const Value);
	void __fastcall UpdateCookiesFromResponse(THTTPResponse* const AResponse);
	
protected:
	int FMaxRedirects;
	System::Net::Urlclient::TNeedClientCertificateCallback FNeedClientCertificateCallback;
	System::Net::Urlclient::TNeedClientCertificateEvent FNeedClientCertificateEvent;
	System::Net::Urlclient::TValidateCertificateCallback FValidateServerCertificateCallback;
	System::Net::Urlclient::TValidateCertificateEvent FValidateServerCertificateEvent;
	THTTPSecureFailureReasons FSecureFailureReasons;
	virtual void __fastcall DoGetClientCertificates(THTTPRequest* const ARequest, System::Generics::Collections::TList__1<System::Net::Urlclient::TCertificate>* const ACertificateList) = 0 ;
	virtual bool __fastcall DoNoClientCertificate(THTTPRequest* const ARequest);
	virtual bool __fastcall DoClientCertificateAccepted(THTTPRequest* const ARequest, const int AnIndex) = 0 ;
	virtual System::Net::Urlclient::TCertificate __fastcall DoGetSSLCertificateFromServer(THTTPRequest* const ARequest) = 0 ;
	virtual void __fastcall DoServerCertificateAccepted(THTTPRequest* const ARequest) = 0 ;
	virtual TExecutionResult __fastcall DoExecuteRequest(THTTPRequest* const ARequest, THTTPResponse* &AResponse, System::Classes::TStream* const AContentStream) = 0 ;
	virtual bool __fastcall DoSetCredential(System::Net::Urlclient::TAuthTargetType AnAuthTargetType, THTTPRequest* const ARequest, const System::Net::Urlclient::TCredentialsStorage::TCredential &ACredential) = 0 ;
	virtual bool __fastcall DoProcessStatus(const _di_IHTTPRequest ARequest, const _di_IHTTPResponse AResponse) = 0 ;
	virtual System::Net::Urlclient::_di_IURLRequest __fastcall DoGetRequestInstance(const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI);
	virtual _di_IHTTPRequest __fastcall DoGetHTTPRequestInstance(THTTPClient* const AClient, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI) = 0 ;
	virtual System::TArray__1<System::UnicodeString> __fastcall SupportedSchemes();
	virtual System::Net::Urlclient::_di_IURLResponse __fastcall DoExecute(const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders);
	virtual System::Types::_di_IAsyncResult __fastcall DoExecuteAsync(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders, bool AOwnsSourceStream);
	System::Types::_di_IAsyncResult __fastcall InternalExecuteAsync(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders, bool AOwnsSourceStream);
	int __fastcall GetMaxRedirects();
	virtual void __fastcall SetMaxRedirects(const int Value);
	void __fastcall Initializer();
	static bool __fastcall IsRedirect(const int AStatusCode);
	bool __fastcall IsAutoRedirect(THTTPResponse* const AResponse);
	bool __fastcall IsAutoRedirectWithGET(THTTPRequest* const ARequest, THTTPResponse* const AResponse);
	System::Net::Urlclient::TURI __fastcall ComposeRedirectURL(THTTPRequest* const ARequest, THTTPResponse* const AResponse);
	
public:
	__fastcall virtual ~THTTPClient();
	__classmethod THTTPClient* __fastcall Create();
	HIDESBASE _di_IHTTPRequest __fastcall GetRequest(const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI)/* overload */;
	HIDESBASE _di_IHTTPRequest __fastcall GetRequest(const System::UnicodeString ARequestMethod, const System::UnicodeString AURL)/* overload */;
	void __fastcall CreateFormFromStrings(System::Classes::TStrings* const ASource, System::Sysutils::TEncoding* const AEncoding, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders, System::Classes::TStream* &ASourceStream, System::TArray__1<System::Net::Urlclient::TNameValuePair> &ASourceHeaders);
	_di_IHTTPResponse __fastcall Delete(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginDelete(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginDelete(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginDelete(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Options(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginOptions(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginOptions(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginOptions(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Get(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginGet(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginGet(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginGet(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	bool __fastcall CheckDownloadResume(const System::UnicodeString AURL);
#ifndef __aarch64__
	_di_IHTTPResponse __fastcall GetRange(const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = -1LL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginGetRange(const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = -1LL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginGetRange(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = -1LL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginGetRange(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = -1LL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
#else /* __aarch64__ */
	_di_IHTTPResponse __fastcall GetRange(const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = (__int64)(-1LL), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginGetRange(const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = (__int64)(-1LL), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginGetRange(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = (__int64)(-1LL), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginGetRange(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, __int64 AStart, __int64 AnEnd = (__int64)(-1LL), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
#endif /* __aarch64__ */
	_di_IHTTPResponse __fastcall Trace(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginTrace(const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginTrace(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginTrace(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Head(const System::UnicodeString AURL, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginHead(const System::UnicodeString AURL, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginHead(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginHead(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Post(const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Post(const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Post(const System::UnicodeString AURL, System::Classes::TStream* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::UnicodeString AURL, System::Classes::TStream* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Post(const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPost(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Put(const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, const System::UnicodeString ASourceFile, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Put(const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStrings* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), System::Sysutils::TEncoding* const AEncoding = (System::Sysutils::TEncoding*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Put(const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Put(const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPut(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Net::Mime::TMultipartFormData* const ASource, System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Merge(const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginMerge(const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginMerge(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginMerge(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall MergeAlternative(const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginMergeAlternative(const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginMergeAlternative(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginMergeAlternative(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const ASource, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall Patch(const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginPatch(const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPatch(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPatch(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	_di_IHTTPResponse __fastcall PatchAlternative(const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>());
	System::Types::_di_IAsyncResult __fastcall BeginPatchAlternative(const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPatchAlternative(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	System::Types::_di_IAsyncResult __fastcall BeginPatchAlternative(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString AURL, System::Classes::TStream* const ASource = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AResponseContent = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	HIDESBASE _di_IHTTPResponse __fastcall Execute(const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	HIDESBASE System::Types::_di_IAsyncResult __fastcall BeginExecute(const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	HIDESBASE System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	HIDESBASE System::Types::_di_IAsyncResult __fastcall BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const _di_IHTTPRequest ARequest, System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>())/* overload */;
	__classmethod _di_IHTTPResponse __fastcall EndAsyncHTTP(const System::Types::_di_IAsyncResult AAsyncResult)/* overload */;
	__classmethod _di_IHTTPResponse __fastcall EndAsyncHTTP(const _di_IHTTPResponse AAsyncResult)/* overload */;
	__property bool HandleRedirects = {read=FHandleRedirects, write=FHandleRedirects, default=1};
	__property int MaxRedirects = {read=GetMaxRedirects, write=SetMaxRedirects, nodefault};
	__property THTTPRedirectsWithGET RedirectsWithGET = {read=FRedirectsWithGET, write=FRedirectsWithGET, nodefault};
	__property System::Net::Urlclient::TNeedClientCertificateCallback NeedClientCertificateCallback = {read=FNeedClientCertificateCallback, write=FNeedClientCertificateCallback};
	__property System::Net::Urlclient::TValidateCertificateCallback ValidateServerCertificateCallback = {read=FValidateServerCertificateCallback, write=FValidateServerCertificateCallback};
	__property THTTPSecureProtocols SecureProtocols = {read=FSecureProtocols, write=FSecureProtocols, nodefault};
	__property THTTPSecureFailureReasons SecureFailureReasons = {read=FSecureFailureReasons, nodefault};
	__property bool PreemptiveAuthentication = {read=FPreemptiveAuthentication, write=FPreemptiveAuthentication, default=0};
	__property bool UseDefaultCredentials = {read=FUseDefaultCredentials, write=FUseDefaultCredentials, default=1};
	__property _di_TSendDataCallback SendDataCallBack = {read=FSendDataCallback, write=FSendDataCallback};
	__property TSendDataEvent OnSendData = {read=FOnSendData, write=FOnSendData};
	__property _di_TReceiveDataCallback ReceiveDataCallBack = {read=FReceiveDataCallback, write=FReceiveDataCallback};
	__property TReceiveDataEvent OnReceiveData = {read=FOnReceiveData, write=FOnReceiveData};
	__property System::Net::Urlclient::TNeedClientCertificateEvent OnNeedClientCertificate = {read=FNeedClientCertificateEvent, write=FNeedClientCertificateEvent};
	__property System::Net::Urlclient::TValidateCertificateEvent OnValidateServerCertificate = {read=FValidateServerCertificateEvent, write=FValidateServerCertificateEvent};
	__property bool AllowCookies = {read=FAllowCookies, write=FAllowCookies, default=1};
	__property TCookieManager* CookieManager = {read=FCookieManager, write=SetCookieManager};
	__property THTTPCompressionMethods AutomaticDecompression = {read=FAutomaticDecompression, write=FAutomaticDecompression, default=0};
	__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept};
	__property System::UnicodeString AcceptCharSet = {read=GetAcceptCharSet, write=SetAcceptCharSet};
	__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding};
	__property System::UnicodeString AcceptLanguage = {read=GetAcceptLanguage, write=SetAcceptLanguage};
	__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
public:
	/* TURLClient.Create */ inline __fastcall THTTPClient() : System::Net::Urlclient::TURLClient() { }
	
	/* Hoisted overloads: */
	
public:
	inline System::Net::Urlclient::_di_IURLResponse __fastcall  Execute(const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::Execute(ARequestMethod, AURI, ASourceStream, AContentStream, AHeaders); }
	inline System::Net::Urlclient::_di_IURLResponse __fastcall  Execute(const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::Execute(ARequestMethod, AURIStr, ASourceStream, AContentStream, AHeaders); }
	inline System::Types::_di_IAsyncResult __fastcall  BeginExecute(const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::BeginExecute(ARequestMethod, AURI, ASourceStream, AContentStream, AHeaders); }
	inline System::Types::_di_IAsyncResult __fastcall  BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::BeginExecute(AsyncCallbackEvent, ARequestMethod, AURI, ASourceStream, AContentStream, AHeaders); }
	inline System::Types::_di_IAsyncResult __fastcall  BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::BeginExecute(AsyncCallback, ARequestMethod, AURI, ASourceStream, AContentStream, AHeaders); }
	inline System::Types::_di_IAsyncResult __fastcall  BeginExecute(const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::BeginExecute(ARequestMethod, AURIStr, ASourceStream, AContentStream, AHeaders); }
	inline System::Types::_di_IAsyncResult __fastcall  BeginExecute(const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::BeginExecute(AsyncCallbackEvent, ARequestMethod, AURIStr, ASourceStream, AContentStream, AHeaders); }
	inline System::Types::_di_IAsyncResult __fastcall  BeginExecute(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::UnicodeString ARequestMethod, const System::UnicodeString AURIStr, System::Classes::TStream* const ASourceStream = (System::Classes::TStream*)(0x0), System::Classes::TStream* const AContentStream = (System::Classes::TStream*)(0x0), const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders = System::TArray__1<System::Net::Urlclient::TNameValuePair>()){ return System::Net::Urlclient::TURLClient::BeginExecute(AsyncCallback, ARequestMethod, AURIStr, ASourceStream, AContentStream, AHeaders); }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
#define sHTTPMethodConnect u"CONNECT"
#define sHTTPMethodDelete u"DELETE"
#define sHTTPMethodGet u"GET"
#define sHTTPMethodHead u"HEAD"
#define sHTTPMethodOptions u"OPTIONS"
#define sHTTPMethodPost u"POST"
#define sHTTPMethodPut u"PUT"
#define sHTTPMethodTrace u"TRACE"
#define sHTTPMethodMerge u"MERGE"
#define sHTTPMethodPatch u"PATCH"
#define CHTTPDefRedirectsWithGET (System::Set<THTTPRedirectWithGET, _DELPHI_SET_ENUMERATOR(THTTPRedirectWithGET::Post301), _DELPHI_SET_ENUMERATOR(THTTPRedirectWithGET::Delete308)>() << THTTPRedirectWithGET::Post301 << THTTPRedirectWithGET::Post302 << THTTPRedirectWithGET::Post303 << THTTPRedirectWithGET::Put303 << THTTPRedirectWithGET::Delete303 )
#define CHTTPDefSecureProtocols System::Set<System::Byte>()
static constexpr System::Int8 CHTTPDefMaxRedirects = System::Int8(0x5);
}	/* namespace Httpclient */
}	/* namespace Net */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET_HTTPCLIENT)
using namespace System::Net::Httpclient;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET)
using namespace System::Net;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Net_HttpclientHPP
