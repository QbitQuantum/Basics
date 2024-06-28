// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Soap.SOAPHTTPTrans.pas' rev: 34.00 (Windows)

#ifndef Soap_SoaphttptransHPP
#define Soap_SoaphttptransHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.Net.URLClient.hpp>
#include <System.Net.HttpClient.hpp>
#include <Soap.IntfInfo.hpp>
#include <Soap.SOAPAttachIntf.hpp>
#include <Soap.WebNode.hpp>
#include <Soap.WSDLIntf.hpp>
#include <Soap.WSDLNode.hpp>

//-- user supplied -----------------------------------------------------------

namespace Soap
{
namespace Soaphttptrans
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ESOAPHTTPException;
__interface DELPHIINTERFACE IHTTPReqResp;
typedef System::DelphiInterface<IHTTPReqResp> _di_IHTTPReqResp;
class DELPHICLASS TClientCert;
class DELPHICLASS THTTPReqResp;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION ESOAPHTTPException : public System::Net::Urlclient::ENetException
{
	typedef System::Net::Urlclient::ENetException inherited;
	
private:
	int FStatusCode;
	System::UnicodeString FStatusText;
	System::UnicodeString FURL;
	
public:
	__fastcall ESOAPHTTPException(int AStatusCode, const System::UnicodeString AStatusText, const System::UnicodeString AURL)/* overload */;
	__property int StatusCode = {read=FStatusCode, nodefault};
	__property System::UnicodeString StatusText = {read=FStatusText};
	__property System::UnicodeString URL = {read=FURL};
public:
	/* Exception.CreateFmt */ inline __fastcall ESOAPHTTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Net::Urlclient::ENetException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ESOAPHTTPException(NativeUInt Ident)/* overload */ : System::Net::Urlclient::ENetException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ESOAPHTTPException(System::PResStringRec ResStringRec)/* overload */ : System::Net::Urlclient::ENetException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ESOAPHTTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ESOAPHTTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Net::Urlclient::ENetException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ESOAPHTTPException(const System::UnicodeString Msg, int AHelpContext) : System::Net::Urlclient::ENetException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ESOAPHTTPException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Net::Urlclient::ENetException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESOAPHTTPException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ESOAPHTTPException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESOAPHTTPException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ESOAPHTTPException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Net::Urlclient::ENetException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ESOAPHTTPException() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

enum DECLSPEC_DENUM SOAPInvokeOptions : unsigned char { soNoValueForEmptySOAPAction, soIgnoreInvalidCerts, soNoSOAPActionHeader, soAutoCheckAccessPointViaUDDI, soPickFirstClientCertificate };

typedef System::Set<SOAPInvokeOptions, SOAPInvokeOptions::soNoValueForEmptySOAPAction, SOAPInvokeOptions::soPickFirstClientCertificate> TSOAPInvokeOptions;

enum DECLSPEC_DENUM TSOAPHttpErrorAction : unsigned char { heaSuccess, heaError, heaAbort, heaRetry };

__interface  INTERFACE_UUID("{5FA6A197-32DE-4225-BC85-216CB80D1561}") IHTTPReqResp  : public System::IInterface 
{
	virtual THTTPReqResp* __fastcall GetHTTPReqResp() = 0 ;
};

typedef void __fastcall (__closure *TBeforePostEvent)(THTTPReqResp* const HTTPReqResp, System::Net::Httpclient::THTTPClient* Client);

typedef void __fastcall (__closure *TPostingDataEvent)(int Sent, int Total);

typedef void __fastcall (__closure *TReceivingDataEvent)(int Read, int Total);

typedef void __fastcall (__closure *TSOAPHttpErrorEvent)(THTTPReqResp* const HTTPReqResp, const System::Net::Httpclient::_di_IHTTPResponse HTTPResponse, ESOAPHTTPException* const Error, TSOAPHttpErrorAction &Action);

class PASCALIMPLEMENTATION TClientCert : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Net::Urlclient::TCertificate FCert;
	
__published:
	__property System::UnicodeString SerialNum = {read=FCert.SerialNum, write=FCert.SerialNum};
	__property System::UnicodeString CertName = {read=FCert.CertName, write=FCert.CertName};
	__property System::UnicodeString Subject = {read=FCert.Subject, write=FCert.Subject};
	__property System::UnicodeString Issuer = {read=FCert.Issuer, write=FCert.Issuer};
	__property System::UnicodeString ProtocolName = {read=FCert.ProtocolName, write=FCert.ProtocolName};
public:
	/* TComponent.Create */ inline __fastcall virtual TClientCert(System::Classes::TComponent* AOwner) : System::Classes::TComponent(AOwner) { }
	/* TComponent.Destroy */ inline __fastcall virtual ~TClientCert() { }
	
};


class PASCALIMPLEMENTATION THTTPReqResp : public System::Classes::TComponent
{
	typedef System::Classes::TComponent inherited;
	
private:
	System::Net::Httpclient::THTTPClient* FHTTP;
	bool FUserSetURL;
	int FRefCount;
	bool FOwnerIsComponent;
	System::UnicodeString FURL;
	Soap::Wsdlintf::TWebServiceBindingType FBindingType;
	System::UnicodeString FMimeBoundary;
	Soap::Webnode::WebNodeOptions FWebNodeOptions;
	System::UnicodeString FUserName;
	System::UnicodeString FPassword;
	System::UnicodeString FProxy;
	Soap::Wsdlnode::TWSDLView* FWSDLView;
	System::UnicodeString FSoapAction;
	bool FUseUTF8InHeader;
	TSOAPInvokeOptions FInvokeOptions;
	System::UnicodeString FUDDIBindingKey;
	System::UnicodeString FUDDIOperator;
	TBeforePostEvent FOnBeforePost;
	TPostingDataEvent FOnPostingData;
	TReceivingDataEvent FOnReceivingData;
	TClientCert* FClientCertificate;
	System::Net::Urlclient::TNeedClientCertificateEvent FNeedClientCertificateEvent;
	TSOAPHttpErrorEvent FOnHttpError;
	void __fastcall SetURL(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSOAPAction();
	void __fastcall SetSOAPAction(const System::UnicodeString SOAPAction);
	bool __fastcall IsSOAPActionStored();
	void __fastcall SetWSDLView(Soap::Wsdlnode::TWSDLView* const WSDLVIew);
	System::UnicodeString __fastcall GetContentType();
	System::UnicodeString __fastcall GetSOAPActionHeader();
	void __fastcall SetUsername(const System::UnicodeString NameValue);
	void __fastcall SetPassword(const System::UnicodeString PasswordValue);
	void __fastcall SetProxy(const System::UnicodeString ProxyValue);
	bool __fastcall GetAgentIsStored();
	void __fastcall SetupHttp(System::Net::Httpclient::THTTPClient* Http);
	int __fastcall GetConnectTimeout();
	int __fastcall GetSendTimeout();
	int __fastcall GetReceiveTimeout();
	void __fastcall SetConnectTimeout(const int Value);
	void __fastcall SetSendTimeout(const int Value);
	void __fastcall SetReceiveTimeout(const int Value);
	System::UnicodeString __fastcall GetAgent();
	void __fastcall SetAgent(const System::UnicodeString Value);
	System::Net::Httpclient::THTTPClient* __fastcall GetHTTP();
	System::Net::Httpclient::THTTPSecureProtocols __fastcall GetSecureProtocols();
	void __fastcall SetSecureProtocols(const System::Net::Httpclient::THTTPSecureProtocols AValue);
	bool __fastcall GetPreemptiveAuthentication();
	void __fastcall SetPreemptiveAuthentication(const bool AValue);
	System::Net::Httpclient::THTTPCompressionMethods __fastcall GetAutomaticDecompression();
	void __fastcall SetAutomaticDecompression(const System::Net::Httpclient::THTTPCompressionMethods AValue);
	bool __fastcall GetUseDefaultCredentials();
	void __fastcall SetUseDefaultCredentials(const bool AValue);
	void __fastcall DoValidateServerCertificate(System::TObject* const Sender, System::Net::Urlclient::TURLRequest* const ARequest, const System::Net::Urlclient::TCertificate &Certificate, bool &Accepted);
	void __fastcall DoNeedClientCertificate(System::TObject* const Sender, System::Net::Urlclient::TURLRequest* const ARequest, System::Net::Urlclient::TCertificateList* const ACertificateList, int &AnIndex);
	void __fastcall DoSendData(System::TObject* const Sender, __int64 AContentLength, __int64 AWriteCount, bool &AAbort);
	void __fastcall DoReceiveData(System::TObject* const Sender, __int64 AContentLength, __int64 AReadCount, bool &AAbort);
	TSOAPHttpErrorAction __fastcall CheckResponseError(const System::Net::Httpclient::_di_IHTTPResponse AHTTPResponse, bool AFailOn500);
	
protected:
	HIDESBASE int __stdcall _AddRef();
	HIDESBASE int __stdcall _Release();
	System::UnicodeString __fastcall GetMimeBoundary();
	void __fastcall SetMimeBoundary(const System::UnicodeString Value);
	Soap::Webnode::WebNodeOptions __fastcall GetWebNodeOptions();
	void __fastcall SetWebNodeOptions(Soap::Webnode::WebNodeOptions Value);
	
public:
	__fastcall virtual THTTPReqResp(System::Classes::TComponent* Owner);
	__classmethod virtual System::TObject* __fastcall NewInstance();
	virtual void __fastcall AfterConstruction();
	__fastcall virtual ~THTTPReqResp();
	THTTPReqResp* __fastcall GetHTTPReqResp();
	virtual void __fastcall Get(System::Classes::TStream* Resp);
	void __fastcall BeforeExecute(const Soap::Intfinfo::TIntfMetaData &IntfMD, const Soap::Intfinfo::TIntfMethEntry &MethMD, int MethodIndex, Soap::Soapattachintf::_di_IMimeAttachmentHandler AttachHandler);
	virtual void __fastcall Execute(const System::UnicodeString DataMsg, System::Classes::TStream* Resp)/* overload */;
	virtual void __fastcall Execute(System::Classes::TStream* const Request, System::Classes::TStream* Response)/* overload */;
	virtual System::Classes::TStream* __fastcall Execute(System::Classes::TStream* const Request)/* overload */;
	void __fastcall Customize(const System::_di_IInterface ATransport);
	__property System::Net::Httpclient::THTTPClient* HTTP = {read=GetHTTP};
	
__published:
	__property System::UnicodeString URL = {read=FURL, write=SetURL};
	__property System::UnicodeString SoapAction = {read=GetSOAPAction, write=SetSOAPAction, stored=IsSOAPActionStored};
	__property Soap::Wsdlnode::TWSDLView* WSDLView = {read=FWSDLView, write=SetWSDLView};
	__property System::UnicodeString Agent = {read=GetAgent, write=SetAgent, stored=GetAgentIsStored};
	__property System::UnicodeString UserName = {read=FUserName, write=SetUsername};
	__property System::UnicodeString Password = {read=FPassword, write=SetPassword};
	__property System::UnicodeString Proxy = {read=FProxy, write=SetProxy};
	__property TClientCert* ClientCertificate = {read=FClientCertificate};
	__property bool UseUTF8InHeader = {read=FUseUTF8InHeader, write=FUseUTF8InHeader, default=1};
	__property TSOAPInvokeOptions InvokeOptions = {read=FInvokeOptions, write=FInvokeOptions, default=10};
	__property Soap::Webnode::WebNodeOptions WebNodeOptions = {read=GetWebNodeOptions, write=SetWebNodeOptions, default=0};
	__property System::UnicodeString UDDIBindingKey = {read=FUDDIBindingKey, write=FUDDIBindingKey};
	__property System::UnicodeString UDDIOperator = {read=FUDDIOperator, write=FUDDIOperator};
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout, default=60000};
	__property int SendTimeout = {read=GetSendTimeout, write=SetSendTimeout, default=60000};
	__property int ReceiveTimeout = {read=GetReceiveTimeout, write=SetReceiveTimeout, default=60000};
	__property System::Net::Httpclient::THTTPSecureProtocols SecureProtocols = {read=GetSecureProtocols, write=SetSecureProtocols, default=0};
	__property System::Net::Httpclient::THTTPCompressionMethods AutomaticDecompression = {read=GetAutomaticDecompression, write=SetAutomaticDecompression, default=0};
	__property bool PreemptiveAuthentication = {read=GetPreemptiveAuthentication, write=SetPreemptiveAuthentication, default=1};
	__property bool UseDefaultCredentials = {read=GetUseDefaultCredentials, write=SetUseDefaultCredentials, default=1};
	__property TBeforePostEvent OnBeforePost = {read=FOnBeforePost, write=FOnBeforePost};
	__property TPostingDataEvent OnPostingData = {read=FOnPostingData, write=FOnPostingData};
	__property TReceivingDataEvent OnReceivingData = {read=FOnReceivingData, write=FOnReceivingData};
	__property System::Net::Urlclient::TNeedClientCertificateEvent OnNeedClientCertificate = {read=FNeedClientCertificateEvent, write=FNeedClientCertificateEvent};
	__property TSOAPHttpErrorEvent OnHttpError = {read=FOnHttpError, write=FOnHttpError};
private:
	void *__IStreamLoaderCustomizer;	// Soap::Wsdlintf::IStreamLoaderCustomizer 
	void *__IHTTPReqResp;	// IHTTPReqResp 
	void *__IWebNode;	// Soap::Webnode::IWebNode 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {582D78AC-1FE4-49C2-9275-7DA54BD20C99}
	operator Soap::Wsdlintf::_di_IStreamLoaderCustomizer()
	{
		Soap::Wsdlintf::_di_IStreamLoaderCustomizer intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Wsdlintf::IStreamLoaderCustomizer*(void) { return (Soap::Wsdlintf::IStreamLoaderCustomizer*)&__IStreamLoaderCustomizer; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5FA6A197-32DE-4225-BC85-216CB80D1561}
	operator _di_IHTTPReqResp()
	{
		_di_IHTTPReqResp intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IHTTPReqResp*(void) { return (IHTTPReqResp*)&__IHTTPReqResp; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {77DB2644-0C12-4C0A-920E-89579DB9CC16}
	operator Soap::Webnode::_di_IWebNode()
	{
		Soap::Webnode::_di_IWebNode intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Soap::Webnode::IWebNode*(void) { return (Soap::Webnode::IWebNode*)&__IWebNode; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {00000000-0000-0000-C000-000000000046}
	operator System::_di_IInterface()
	{
		System::_di_IInterface intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::IInterface*(void) { return (System::IInterface*)&__IStreamLoaderCustomizer; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Soaphttptrans */
}	/* namespace Soap */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP_SOAPHTTPTRANS)
using namespace Soap::Soaphttptrans;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SOAP)
using namespace Soap;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Soap_SoaphttptransHPP
