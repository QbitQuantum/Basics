// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'IPPeerAPI.pas' rev: 34.00 (Android)

#ifndef IppeerapiHPP
#define IppeerapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Ippeerapi
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EIPPeerException;
class DELPHICLASS EIPAbstractError;
class DELPHICLASS EIPHTTPProtocolExceptionPeer;
struct TIPSSLULong;
__interface DELPHIINTERFACE IIPPeerFactory;
typedef System::DelphiInterface<IIPPeerFactory> _di_IIPPeerFactory;
class DELPHICLASS TIPPeerFactory;
__interface DELPHIINTERFACE IIPMultipartFormDataStream;
typedef System::DelphiInterface<IIPMultipartFormDataStream> _di_IIPMultipartFormDataStream;
__interface DELPHIINTERFACE IIPPeerProcs;
typedef System::DelphiInterface<IIPPeerProcs> _di_IIPPeerProcs;
__interface DELPHIINTERFACE IIPeerProcsGlobals;
typedef System::DelphiInterface<IIPeerProcsGlobals> _di_IIPeerProcsGlobals;
__interface DELPHIINTERFACE IIPObject;
typedef System::DelphiInterface<IIPObject> _di_IIPObject;
struct TIPv4Subnet;
__interface DELPHIINTERFACE IIPStack;
typedef System::DelphiInterface<IIPStack> _di_IIPStack;
__interface DELPHIINTERFACE IIPURI;
typedef System::DelphiInterface<IIPURI> _di_IIPURI;
__interface DELPHIINTERFACE IIPCookieManager;
typedef System::DelphiInterface<IIPCookieManager> _di_IIPCookieManager;
__interface DELPHIINTERFACE IIPBuffer;
typedef System::DelphiInterface<IIPBuffer> _di_IIPBuffer;
__interface DELPHIINTERFACE IIPSSLOptions;
typedef System::DelphiInterface<IIPSSLOptions> _di_IIPSSLOptions;
__interface DELPHIINTERFACE IIPIOHandler;
typedef System::DelphiInterface<IIPIOHandler> _di_IIPIOHandler;
__interface DELPHIINTERFACE IIPIOHandlerSocket;
typedef System::DelphiInterface<IIPIOHandlerSocket> _di_IIPIOHandlerSocket;
__interface DELPHIINTERFACE IIPIOHandlerStack;
typedef System::DelphiInterface<IIPIOHandlerStack> _di_IIPIOHandlerStack;
__interface DELPHIINTERFACE IIPSSLIOHandlerSocketBase;
typedef System::DelphiInterface<IIPSSLIOHandlerSocketBase> _di_IIPSSLIOHandlerSocketBase;
__interface DELPHIINTERFACE IIPSSLIOHandlerSocketOpenSSL;
typedef System::DelphiInterface<IIPSSLIOHandlerSocketOpenSSL> _di_IIPSSLIOHandlerSocketOpenSSL;
__interface DELPHIINTERFACE IIPHeaderList;
typedef System::DelphiInterface<IIPHeaderList> _di_IIPHeaderList;
__interface DELPHIINTERFACE IIPAuthentication;
typedef System::DelphiInterface<IIPAuthentication> _di_IIPAuthentication;
__interface DELPHIINTERFACE IIPEntityHeaderInfo;
typedef System::DelphiInterface<IIPEntityHeaderInfo> _di_IIPEntityHeaderInfo;
__interface DELPHIINTERFACE IIPHTTPRequest;
typedef System::DelphiInterface<IIPHTTPRequest> _di_IIPHTTPRequest;
__interface DELPHIINTERFACE IIPHTTPResponse;
typedef System::DelphiInterface<IIPHTTPResponse> _di_IIPHTTPResponse;
__interface DELPHIINTERFACE IIPProxyConnectionInfo;
typedef System::DelphiInterface<IIPProxyConnectionInfo> _di_IIPProxyConnectionInfo;
__interface DELPHIINTERFACE IIPTCPConnection;
typedef System::DelphiInterface<IIPTCPConnection> _di_IIPTCPConnection;
__interface DELPHIINTERFACE IIPTCPClientCustom;
typedef System::DelphiInterface<IIPTCPClientCustom> _di_IIPTCPClientCustom;
__interface DELPHIINTERFACE IIPHTTP;
typedef System::DelphiInterface<IIPHTTP> _di_IIPHTTP;
__interface DELPHIINTERFACE IIPTCPClient;
typedef System::DelphiInterface<IIPTCPClient> _di_IIPTCPClient;
__interface DELPHIINTERFACE IIPX509Name;
typedef System::DelphiInterface<IIPX509Name> _di_IIPX509Name;
__interface DELPHIINTERFACE IIPX509SigInfo;
typedef System::DelphiInterface<IIPX509SigInfo> _di_IIPX509SigInfo;
__interface DELPHIINTERFACE IIPX509;
typedef System::DelphiInterface<IIPX509> _di_IIPX509;
__interface DELPHIINTERFACE IIPBasicAuthentication;
typedef System::DelphiInterface<IIPBasicAuthentication> _di_IIPBasicAuthentication;
__interface DELPHIINTERFACE IIPHashMessageDigest5;
typedef System::DelphiInterface<IIPHashMessageDigest5> _di_IIPHashMessageDigest5;
__interface DELPHIINTERFACE IIPTask;
typedef System::DelphiInterface<IIPTask> _di_IIPTask;
__interface DELPHIINTERFACE IIPContext;
typedef System::DelphiInterface<IIPContext> _di_IIPContext;
__interface DELPHIINTERFACE IIPServerIOHandler;
typedef System::DelphiInterface<IIPServerIOHandler> _di_IIPServerIOHandler;
__interface DELPHIINTERFACE IIPServerIOHandlerSSLBase;
typedef System::DelphiInterface<IIPServerIOHandlerSSLBase> _di_IIPServerIOHandlerSSLBase;
__interface DELPHIINTERFACE IIPServerIOHandlerSSLOpenSSL;
typedef System::DelphiInterface<IIPServerIOHandlerSSLOpenSSL> _di_IIPServerIOHandlerSSLOpenSSL;
__interface DELPHIINTERFACE IIPRequestHeaderInfo;
typedef System::DelphiInterface<IIPRequestHeaderInfo> _di_IIPRequestHeaderInfo;
__interface DELPHIINTERFACE IIPHTTPSession;
typedef System::DelphiInterface<IIPHTTPSession> _di_IIPHTTPSession;
__interface DELPHIINTERFACE IIPHTTPRequestInfo;
typedef System::DelphiInterface<IIPHTTPRequestInfo> _di_IIPHTTPRequestInfo;
__interface DELPHIINTERFACE IIPResponseHeaderInfo;
typedef System::DelphiInterface<IIPResponseHeaderInfo> _di_IIPResponseHeaderInfo;
__interface DELPHIINTERFACE IIPHTTPResponseInfo;
typedef System::DelphiInterface<IIPHTTPResponseInfo> _di_IIPHTTPResponseInfo;
__interface DELPHIINTERFACE IIPSocketHandle;
typedef System::DelphiInterface<IIPSocketHandle> _di_IIPSocketHandle;
__interface DELPHIINTERFACE IIPSocketHandles;
typedef System::DelphiInterface<IIPSocketHandles> _di_IIPSocketHandles;
__interface DELPHIINTERFACE IIPScheduler;
typedef System::DelphiInterface<IIPScheduler> _di_IIPScheduler;
__interface DELPHIINTERFACE IIPSchedulerOfThread;
typedef System::DelphiInterface<IIPSchedulerOfThread> _di_IIPSchedulerOfThread;
__interface DELPHIINTERFACE IIPSchedulerOfThreadPool;
typedef System::DelphiInterface<IIPSchedulerOfThreadPool> _di_IIPSchedulerOfThreadPool;
__interface DELPHIINTERFACE IIPTestServer;
typedef System::DelphiInterface<IIPTestServer> _di_IIPTestServer;
__interface DELPHIINTERFACE IIPCustomTCPServer;
typedef System::DelphiInterface<IIPCustomTCPServer> _di_IIPCustomTCPServer;
__interface DELPHIINTERFACE IIPTCPServer;
typedef System::DelphiInterface<IIPTCPServer> _di_IIPTCPServer;
__interface DELPHIINTERFACE IIPUDPListenerThread;
typedef System::DelphiInterface<IIPUDPListenerThread> _di_IIPUDPListenerThread;
__interface DELPHIINTERFACE IIPCustomUDPServer;
typedef System::DelphiInterface<IIPCustomUDPServer> _di_IIPCustomUDPServer;
__interface DELPHIINTERFACE IIPUDPServer;
typedef System::DelphiInterface<IIPUDPServer> _di_IIPUDPServer;
__interface DELPHIINTERFACE IIPHTTPServer;
typedef System::DelphiInterface<IIPHTTPServer> _di_IIPHTTPServer;
__interface DELPHIINTERFACE IIPCustomMulticastBase;
typedef System::DelphiInterface<IIPCustomMulticastBase> _di_IIPCustomMulticastBase;
__interface DELPHIINTERFACE IIPCustomMulticastClient;
typedef System::DelphiInterface<IIPCustomMulticastClient> _di_IIPCustomMulticastClient;
__interface DELPHIINTERFACE IIPMulticastClient;
typedef System::DelphiInterface<IIPMulticastClient> _di_IIPMulticastClient;
__interface DELPHIINTERFACE IIPCustomMulticastServer;
typedef System::DelphiInterface<IIPCustomMulticastServer> _di_IIPCustomMulticastServer;
__interface DELPHIINTERFACE IIPMulticastServer;
typedef System::DelphiInterface<IIPMulticastServer> _di_IIPMulticastServer;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIPPeerException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIPPeerException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIPPeerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIPPeerException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIPPeerException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIPPeerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIPPeerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIPPeerException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIPPeerException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIPPeerException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIPPeerException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIPPeerException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIPPeerException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIPPeerException() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIPAbstractError : public EIPPeerException
{
	typedef EIPPeerException inherited;
	
public:
	/* Exception.Create */ inline __fastcall EIPAbstractError(const System::UnicodeString Msg) : EIPPeerException(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EIPAbstractError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIPPeerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIPAbstractError(NativeUInt Ident)/* overload */ : EIPPeerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIPAbstractError(System::PResStringRec ResStringRec)/* overload */ : EIPPeerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIPAbstractError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIPPeerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIPAbstractError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIPPeerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIPAbstractError(const System::UnicodeString Msg, int AHelpContext) : EIPPeerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIPAbstractError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIPPeerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIPAbstractError(NativeUInt Ident, int AHelpContext)/* overload */ : EIPPeerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIPAbstractError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIPPeerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIPAbstractError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIPPeerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIPAbstractError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIPPeerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIPAbstractError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EIPHTTPProtocolExceptionPeer : public EIPPeerException
{
	typedef EIPPeerException inherited;
	
private:
	System::Sysutils::Exception* FException;
	System::UnicodeString FErrorMsg;
	int FErrorCode;
	
public:
	__property System::UnicodeString ErrorMessage = {read=FErrorMsg};
	__property int ErrorCode = {read=FErrorCode, nodefault};
	__fastcall EIPHTTPProtocolExceptionPeer(System::Sysutils::Exception* Ex, const System::UnicodeString ErrorMsg, const System::UnicodeString Msg, int ErrorCode)/* overload */;
public:
	/* Exception.CreateFmt */ inline __fastcall EIPHTTPProtocolExceptionPeer(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EIPPeerException(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EIPHTTPProtocolExceptionPeer(NativeUInt Ident)/* overload */ : EIPPeerException(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EIPHTTPProtocolExceptionPeer(System::PResStringRec ResStringRec)/* overload */ : EIPPeerException(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EIPHTTPProtocolExceptionPeer(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EIPPeerException(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EIPHTTPProtocolExceptionPeer(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EIPPeerException(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EIPHTTPProtocolExceptionPeer(const System::UnicodeString Msg, int AHelpContext) : EIPPeerException(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EIPHTTPProtocolExceptionPeer(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EIPPeerException(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIPHTTPProtocolExceptionPeer(NativeUInt Ident, int AHelpContext)/* overload */ : EIPPeerException(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EIPHTTPProtocolExceptionPeer(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EIPPeerException(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIPHTTPProtocolExceptionPeer(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIPPeerException(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EIPHTTPProtocolExceptionPeer(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EIPPeerException(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EIPHTTPProtocolExceptionPeer() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

typedef void * PX509Peer;

typedef void * PRSAPeer;

typedef System::PByte *PPByte;

typedef System::_di_IInterface IIPTextEncodingPeer;

typedef System::TArray__1<System::Byte> TIPBytesPeer;

typedef System::Word TIPPortPeer;

enum DECLSPEC_DENUM TIPVersionPeer : unsigned char { IP_IPv4, IP_IPv6 };

#ifndef __aarch64__
typedef int TIPC_INT;
#else /* __aarch64__ */
typedef long TIPC_INT;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef int TIPC_LONG;
#else /* __aarch64__ */
typedef long TIPC_LONG;
#endif /* __aarch64__ */

#ifndef __aarch64__
typedef unsigned TIPC_ULONG;
#else /* __aarch64__ */
typedef unsigned long TIPC_ULONG;
#endif /* __aarch64__ */

typedef void * TIPHMACIntCtx;

#pragma pack(push,1)
struct DECLSPEC_DRECORD TIPSSLULong
{
	
public:
	union
	{
		struct 
		{
#ifndef __aarch64__
			unsigned C1;
#else /* __aarch64__ */
			unsigned long C1;
#endif /* __aarch64__ */
		};
		struct 
		{
#ifndef __aarch64__
			int L1;
#else /* __aarch64__ */
			long L1;
#endif /* __aarch64__ */
		};
		struct 
		{
			System::Word W1;
			System::Word W2;
		};
		struct 
		{
			System::Byte B1;
			System::Byte B2;
			System::Byte B3;
			System::Byte B4;
		};
		
	};
};
#pragma pack(pop)


enum DECLSPEC_DENUM TIPHTTPOptionPeer : unsigned char { hoInProcessAuth, hoKeepOrigProtocol, hoForceEncodeParams, hoNonSSLProxyUseConnectVerb, hoNoParseMetaHTTPEquiv, hoWaitForUnexpectedData };

typedef System::Set<TIPHTTPOptionPeer, TIPHTTPOptionPeer::hoInProcessAuth, TIPHTTPOptionPeer::hoWaitForUnexpectedData> TIPHTTPOptionsPeer;

enum DECLSPEC_DENUM TIPSSLVerifyModePeer : unsigned char { sslvrfPeer, sslvrfFailIfNoPeerCert, sslvrfClientOnce };

typedef System::Set<TIPSSLVerifyModePeer, TIPSSLVerifyModePeer::sslvrfPeer, TIPSSLVerifyModePeer::sslvrfClientOnce> TIPSSLVerifyModeSetPeer;

enum DECLSPEC_DENUM TIPSSLModePeer : unsigned char { sslmUnassigned, sslmClient, sslmServer, sslmBoth };

enum DECLSPEC_DENUM TIPSSLVersionPeer : unsigned char { sslvSSLv2, sslvSSLv23, sslvSSLv3, sslvTLSv1, sslvTLSv1_1, sslvTLSv1_2 };

enum DECLSPEC_DENUM THTTPCommandTypePeer : unsigned char { hcUnknown, hcHEAD, hcGET, hcPOST, hcDELETE, hcPUT, hcTRACE, hcOPTION };

typedef NativeUInt TSocket;

typedef NativeUInt TIPStackSocketHandlePeer;

__interface  INTERFACE_UUID("{3FE74AEB-0FD1-495E-8527-D008EA2A06F4}") IIPPeerFactory  : public System::IInterface 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TIPPeerFactory : public System::TInterfacedObject
{
	typedef System::TInterfacedObject inherited;
	
	
public:
	typedef System::Generics::Collections::TDictionary__2<GUID,System::TClass>* TPeerDictionary;
	
	
private:
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,System::Generics::Collections::TDictionary__2<GUID,System::TClass>*>* FImplDict;
	
protected:
	bool __fastcall ContainsPeer(const System::UnicodeString ImplementationID, const GUID &Key);
	
public:
	__fastcall TIPPeerFactory();
	__fastcall virtual ~TIPPeerFactory();
	System::_di_IInterface __fastcall CreatePeer(const System::UnicodeString ImplementationID, const GUID &Key)/* overload */;
	System::_di_IInterface __fastcall CreatePeer(const System::UnicodeString ImplementationID, const GUID &Key, const System::Rtti::TValue *Args, const int Args_High)/* overload */;
	System::_di_IInterface __fastcall CreatePeer(const System::UnicodeString ImplementationID, const GUID &Key, System::TObject* AObj)/* overload */;
	System::_di_IInterface __fastcall CreatePeer(const System::UnicodeString ImplementationID, const GUID &Key, System::Classes::TComponent* AComponent)/* overload */;
	System::_di_IInterface __fastcall CreatePeer(const System::UnicodeString ImplementationID, const GUID &Key, void * V1, bool V2)/* overload */;
	void __fastcall RegisterPeer(const System::UnicodeString ImplementationID, const GUID &Key, const System::TClass ImplClass);
	void __fastcall UnregisterPeerClass(const System::UnicodeString ImplementationID, const System::TClass ImplClass);
	void __fastcall UnregisterPeers(const System::UnicodeString ImplementationID);
private:
	void *__IIPPeerFactory;	// IIPPeerFactory 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3FE74AEB-0FD1-495E-8527-D008EA2A06F4}
	operator _di_IIPPeerFactory()
	{
		_di_IIPPeerFactory intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator IIPPeerFactory*(void) { return (IIPPeerFactory*)&__IIPPeerFactory; }
	#endif
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{57136AC4-E926-4A3F-BE2E-1509488B8DD0}") IIPMultipartFormDataStream  : public System::IInterface 
{
	virtual void __fastcall AddFormField(const System::UnicodeString AFieldName, const System::UnicodeString AFieldValue) = 0 ;
	virtual void __fastcall AddFormFile(const System::UnicodeString AFieldName, const System::UnicodeString AFieldValue, const System::UnicodeString AContentType) = 0 ;
	virtual System::UnicodeString __fastcall GetRequestContentType() = 0 ;
	virtual System::Classes::TStream* __fastcall GetStream(bool AInstanceOwner) = 0 ;
};

__interface  INTERFACE_UUID("{DAE26801-CA52-43FD-9332-5CD951E3B756}") IIPPeerProcs  : public System::IInterface 
{
	virtual int __fastcall RSA_PKCS1_PADDING() = 0 ;
	virtual void __fastcall _RSA_free(void * Ptr) = 0 ;
#ifndef __aarch64__
	virtual void * __fastcall _RSA_generate_key(int bits, unsigned e) = 0 ;
	virtual int __fastcall _i2d_RSAPublicKey(void * x, PPByte buf) = 0 ;
	virtual void * __fastcall _d2i_RSAPublicKey(void * pr, PPByte _in, int len) = 0 ;
#else /* __aarch64__ */
	virtual void * __fastcall _RSA_generate_key(long bits, unsigned long e) = 0 ;
	virtual long __fastcall _i2d_RSAPublicKey(void * x, PPByte buf) = 0 ;
	virtual void * __fastcall _d2i_RSAPublicKey(void * pr, PPByte _in, long len) = 0 ;
#endif /* __aarch64__ */
	virtual bool __fastcall _SSLLoad() = 0 ;
	virtual void __fastcall _ERR_load_crypto_strings() = 0 ;
	virtual void __fastcall _OpenSSL_add_all_ciphers() = 0 ;
#ifndef __aarch64__
	virtual int __fastcall _RSA_size(void * key) = 0 ;
	virtual int __fastcall _RSA_private_decrypt(int flen, System::PByte from, System::PByte _to, void * rsa, int padding) = 0 ;
	virtual int __fastcall _RSA_public_encrypt(int flen, System::PByte from, System::PByte _to, void * rsa, int padding) = 0 ;
	virtual System::TPtrWrapper __fastcall _ERR_error_string(unsigned e, System::TPtrWrapper buf) = 0 /* overload */;
	virtual unsigned __fastcall _ERR_get_error() = 0 ;
	virtual void * __fastcall _d2i_X509(void * pr, PPByte _in, int len) = 0 ;
#else /* __aarch64__ */
	virtual long __fastcall _RSA_size(void * key) = 0 ;
	virtual long __fastcall _RSA_private_decrypt(long flen, System::PByte from, System::PByte _to, void * rsa, long padding) = 0 ;
	virtual long __fastcall _RSA_public_encrypt(long flen, System::PByte from, System::PByte _to, void * rsa, long padding) = 0 ;
	virtual System::TPtrWrapper __fastcall _ERR_error_string(unsigned long e, const System::TPtrWrapper &buf) = 0 /* overload */;
	virtual unsigned long __fastcall _ERR_get_error() = 0 ;
	virtual void * __fastcall _d2i_X509(void * pr, PPByte _in, long len) = 0 ;
#endif /* __aarch64__ */
	virtual void * __fastcall _PEM_read_bio_X509(void * mp, __int64 size) = 0 ;
	virtual void * __fastcall _d2i_PKCS12_bio(void * mp, __int64 size, System::UnicodeString certpassword) = 0 ;
	virtual System::UnicodeString __fastcall URLEncode(const System::UnicodeString ASrc) = 0 ;
	virtual System::UnicodeString __fastcall URLDecode(System::UnicodeString ASrc, System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 ;
	virtual System::UnicodeString __fastcall ReadStringAsCharset(System::Classes::TStream* AStream, const System::UnicodeString ACharset) = 0 ;
	virtual System::UnicodeString __fastcall ParamsEncode(const System::UnicodeString ASrc, System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 ;
	virtual System::UnicodeString __fastcall ReadStringFromStream(System::Classes::TStream* AStream, int ASize = 0xffffffff, System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 ;
	virtual System::TDateTime __fastcall GMTToLocalDateTime(System::UnicodeString S) = 0 ;
	virtual bool __fastcall IsHMACSHA256Avail() = 0 ;
	virtual void * __fastcall GetHMACSHA256HashInst(const System::TArray__1<System::Byte> AKey) = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall HashSHA256(const System::TArray__1<System::Byte> AData) = 0 ;
	virtual void __fastcall UpdateHMACInst(void * ACtx, const System::TArray__1<System::Byte> AIn) = 0 ;
	virtual System::TArray__1<System::Byte> __fastcall FinalHMACInst(void * ACtx) = 0 ;
	virtual bool __fastcall IsHMACSHA1Avail() = 0 ;
	virtual void * __fastcall GetHMACSHA1HashInst(const System::TArray__1<System::Byte> AKey) = 0 ;
	virtual System::UnicodeString __fastcall HashHMACSHA1(const System::UnicodeString AData, const System::UnicodeString AKey) = 0 ;
};

__interface  INTERFACE_UUID("{2CD26FAB-193A-43E0-9783-67E2FE777D0F}") IIPeerProcsGlobals  : public System::IInterface 
{
	virtual void __fastcall RSA_register_global(void * APtr) = 0 ;
	virtual void __fastcall RSA_free_global(void * APtr) = 0 ;
};

__interface  INTERFACE_UUID("{30FB4EF1-6942-47F9-8ECB-5E2454CE3ED7}") IIPObject  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

struct DECLSPEC_DRECORD TIPv4Subnet
{
public:
	System::UnicodeString Address;
	unsigned Subnet;
	unsigned Mask;
	__fastcall TIPv4Subnet(const System::UnicodeString AAddress, unsigned ASubnet, unsigned AMask);
	TIPv4Subnet() {}
};


__interface  INTERFACE_UUID("{02945AA3-4EF1-4B58-BA30-675AB8C69705}") IIPStack  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual void __fastcall SetKeepAliveValues(NativeUInt ASocket, const bool AEnabled, const int ATimeMS, const int AInterval) = 0 ;
	virtual bool __fastcall SupportsIPv6() = 0 ;
	virtual System::UnicodeString __fastcall ResolveHost(const System::UnicodeString AHostName, const TIPVersionPeer AIPVersion = (TIPVersionPeer)(0x0)) = 0 ;
	virtual System::TArray__1<TIPv4Subnet> __fastcall GetIPv4Subnets() = 0 ;
	virtual unsigned __fastcall IPv4ToUInt32(const System::UnicodeString AIPAddress) = 0 ;
};

__interface  INTERFACE_UUID("{E0125434-B354-482C-BD99-7E61623721FF}") IIPURI  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall URLEncode(const System::UnicodeString ASrc, System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 ;
	virtual System::UnicodeString __fastcall GetProtocol() = 0 ;
	virtual System::UnicodeString __fastcall GetFullURI() = 0 ;
	virtual void __fastcall SetURI(const System::UnicodeString AValue) = 0 ;
	virtual System::UnicodeString __fastcall GetURI() = 0 ;
	__property System::UnicodeString URI = {read=GetURI, write=SetURI};
};

__interface  INTERFACE_UUID("{10485220-0D73-44D4-A6C1-469B1D5E3E50}") IIPCookieManager  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual void __fastcall AddServerCookie(const System::UnicodeString ACookie, const System::UnicodeString AURL) = 0 ;
};

__interface  INTERFACE_UUID("{CF9F94FB-390C-486A-A89D-322C6F3162D9}") IIPBuffer  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual int __fastcall GetSize() = 0 ;
	__property int Size = {read=GetSize};
};

__interface  INTERFACE_UUID("{D5E0819E-C612-46E5-971C-4D1A3412C430}") IIPSSLOptions  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual TIPSSLVerifyModeSetPeer __fastcall GetVerifyMode() = 0 ;
	virtual void __fastcall SetVerifyMode(TIPSSLVerifyModeSetPeer mode) = 0 ;
	__property TIPSSLVerifyModeSetPeer VerifyMode = {read=GetVerifyMode, write=SetVerifyMode};
	virtual System::UnicodeString __fastcall GetCertFile() = 0 ;
	virtual void __fastcall SetCertFile(System::UnicodeString ctfile) = 0 ;
	__property System::UnicodeString CertFile = {read=GetCertFile, write=SetCertFile};
	virtual System::UnicodeString __fastcall GetKeyFile() = 0 ;
	virtual void __fastcall SetKeyFile(System::UnicodeString kfile) = 0 ;
	__property System::UnicodeString KeyFile = {read=GetKeyFile, write=SetKeyFile};
	virtual System::UnicodeString __fastcall GetRootCertFile() = 0 ;
	virtual void __fastcall SetRootCertFile(System::UnicodeString rootfile) = 0 ;
	__property System::UnicodeString RootCertFile = {read=GetRootCertFile, write=SetRootCertFile};
	virtual TIPSSLModePeer __fastcall GetMode() = 0 ;
	virtual void __fastcall SetMode(TIPSSLModePeer mode) = 0 ;
	__property TIPSSLModePeer Mode = {read=GetMode, write=SetMode};
	virtual TIPSSLVersionPeer __fastcall GetMethod() = 0 ;
	virtual void __fastcall SetMethod(TIPSSLVersionPeer method) = 0 ;
	__property TIPSSLVersionPeer Method = {read=GetMethod, write=SetMethod};
};

__interface  INTERFACE_UUID("{ADB82592-F88C-4762-A266-EED3288E917D}") IIPIOHandler  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual void __fastcall Close() = 0 ;
	virtual System::Byte __fastcall ReadByte() = 0 ;
	virtual _di_IIPBuffer __fastcall GetInputBuffer() = 0 ;
	__property _di_IIPBuffer InputBuffer = {read=GetInputBuffer};
	virtual void __fastcall ReadBytes(System::TArray__1<System::Byte> &VBuffer, int AByteCount, bool AAppend = true) = 0 ;
#ifndef __aarch64__
	virtual void __fastcall ReadStream(System::Classes::TStream* const AStream, const __int64 AByteCount = -1LL, bool AReadUntilDisconnect = false) = 0 ;
#else /* __aarch64__ */
	virtual void __fastcall ReadStream(System::Classes::TStream* const AStream, const __int64 AByteCount = (__int64)(-1LL), bool AReadUntilDisconnect = false) = 0 ;
#endif /* __aarch64__ */
	virtual void __fastcall Write(const System::TArray__1<System::Byte> ABuffer, const int ALength = 0xffffffff, const int AOffset = 0x0) = 0 /* overload */;
#ifndef __aarch64__
	virtual void __fastcall Write(System::Classes::TStream* const AStream, const __int64 ASize = 0LL, bool AWriteByteCount = false) = 0 /* overload */;
#else /* __aarch64__ */
	virtual void __fastcall Write(System::Classes::TStream* const AStream, const __int64 ASize = (__int64)(0LL), bool AWriteByteCount = false) = 0 /* overload */;
#endif /* __aarch64__ */
	virtual __int64 __fastcall WriteFile(const System::UnicodeString AFile, bool AEnableTransferFile = false) = 0 ;
	virtual bool __fastcall CheckForDataOnSource(int ATimeout = 0x0) = 0 ;
	virtual bool __fastcall Connected() = 0 ;
};

__interface  INTERFACE_UUID("{9B355D35-E331-437E-B787-7BE90943DA0F}") IIPIOHandlerSocket  : public IIPIOHandler 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPSocketHandle __fastcall GetBinding() = 0 ;
	__property _di_IIPSocketHandle Binding = {read=GetBinding};
};

__interface  INTERFACE_UUID("{3B32976F-4977-4759-8C68-F91A60E7F0BB}") IIPIOHandlerStack  : public IIPIOHandlerSocket 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

__interface  INTERFACE_UUID("{2A97E6B9-6FBB-46DA-BB9C-1C31A0FD5644}") IIPSSLIOHandlerSocketBase  : public IIPIOHandlerStack 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual bool __fastcall GetPassThrough() = 0 ;
	virtual void __fastcall SetPassThrough(bool pass) = 0 ;
	__property bool PassThrough = {read=GetPassThrough, write=SetPassThrough};
};

typedef bool __fastcall (__closure *TVerifyPeerEventPeer)(_di_IIPX509 Certificate, bool AOk, int ADepth, int AError);

__interface  INTERFACE_UUID("{19D164A0-81B6-4535-9889-F178486EFEFA}") IIPSSLIOHandlerSocketOpenSSL  : public IIPSSLIOHandlerSocketBase 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual TVerifyPeerEventPeer __fastcall GetOnVerifyPeer() = 0 ;
	virtual void __fastcall SetOnVerifyPeer(TVerifyPeerEventPeer OnVerify) = 0 ;
	__property TVerifyPeerEventPeer OnVerifyPeer = {read=GetOnVerifyPeer, write=SetOnVerifyPeer};
	virtual _di_IIPSSLOptions __fastcall GetSSLOptions() = 0 ;
	virtual void __fastcall SetSSLOptions(_di_IIPSSLOptions options) = 0 ;
	__property _di_IIPSSLOptions SSLOptions = {read=GetSSLOptions, write=SetSSLOptions};
};

__interface  INTERFACE_UUID("{A29972BC-E366-4755-A4E8-A32A4FCB60DC}") IIPHeaderList  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual void __fastcall AddValue(const System::UnicodeString AName, const System::UnicodeString AValue) = 0 ;
	virtual bool __fastcall GetFoldLines() = 0 ;
	virtual void __fastcall SetFoldLines(bool Val) = 0 ;
	__property bool FoldLines = {read=GetFoldLines, write=SetFoldLines};
	virtual System::UnicodeString __fastcall GetValue(const System::UnicodeString Name) = 0 ;
	virtual void __fastcall SetValue(const System::UnicodeString Name, System::UnicodeString Val) = 0 ;
	virtual int __fastcall Add(const System::UnicodeString S) = 0 ;
	__property System::UnicodeString Values[const System::UnicodeString Name] = {read=GetValue, write=SetValue};
	virtual void __fastcall Clear() = 0 ;
	virtual int __fastcall IndexOfName(const System::UnicodeString AName) = 0 ;
	virtual int __fastcall GetCount() = 0 ;
	__property int Count = {read=GetCount};
	virtual System::UnicodeString __fastcall GetName(int Index) = 0 ;
	__property System::UnicodeString Names[int Index] = {read=GetName};
};

__interface  INTERFACE_UUID("{DFDC8E65-FB15-4BD8-8317-8F4AF78A30C8}") IIPAuthentication  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetUserName() = 0 ;
	virtual void __fastcall SetUsername(System::UnicodeString user) = 0 ;
	__property System::UnicodeString Username = {read=GetUserName, write=SetUsername};
	virtual System::UnicodeString __fastcall GetPassword() = 0 ;
	virtual void __fastcall SetPassword(System::UnicodeString pass) = 0 ;
	__property System::UnicodeString Password = {read=GetPassword, write=SetPassword};
};

__interface  INTERFACE_UUID("{98EE87B9-2E96-4AFD-B857-03C5F7011E59}") IIPEntityHeaderInfo  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetContentType() = 0 ;
	virtual void __fastcall SetContentType(System::UnicodeString LContentType) = 0 ;
	__property System::UnicodeString ContentType = {read=GetContentType, write=SetContentType};
	virtual System::UnicodeString __fastcall GetContentLanguage() = 0 ;
	virtual void __fastcall SetContentLanguage(System::UnicodeString LContentLanguage) = 0 ;
	__property System::UnicodeString ContentLanguage = {read=GetContentLanguage, write=SetContentLanguage};
	virtual System::UnicodeString __fastcall GetContentEncoding() = 0 ;
	virtual void __fastcall SetContentEncoding(System::UnicodeString LContentEncoding) = 0 ;
	__property System::UnicodeString ContentEncoding = {read=GetContentEncoding, write=SetContentEncoding};
	virtual __int64 __fastcall GetContentRangeEnd() = 0 ;
	virtual void __fastcall SetContentRangeEnd(__int64 LContentRangeEnd) = 0 ;
	__property __int64 ContentRangeEnd = {read=GetContentRangeEnd, write=SetContentRangeEnd};
	virtual __int64 __fastcall GetContentRangeStart() = 0 ;
	virtual void __fastcall SetContentRangeStart(__int64 LContentRangeStart) = 0 ;
	__property __int64 ContentRangeStart = {read=GetContentRangeStart, write=SetContentRangeStart};
	virtual System::UnicodeString __fastcall GetContentVersion() = 0 ;
	virtual void __fastcall SetContentVersion(System::UnicodeString LContentVersion) = 0 ;
	__property System::UnicodeString ContentVersion = {read=GetContentVersion, write=SetContentVersion};
	virtual __int64 __fastcall GetContentLength() = 0 ;
	virtual void __fastcall SetContentLength(__int64 LContentLength) = 0 ;
	__property __int64 ContentLength = {read=GetContentLength, write=SetContentLength};
	virtual _di_IIPHeaderList __fastcall GetCustomHeaders() = 0 ;
	__property _di_IIPHeaderList CustomHeaders = {read=GetCustomHeaders};
	virtual _di_IIPHeaderList __fastcall GetRawHeaders() = 0 ;
	__property _di_IIPHeaderList RawHeaders = {read=GetRawHeaders};
	virtual System::UnicodeString __fastcall GetPragma() = 0 ;
	virtual void __fastcall SetPragma(System::UnicodeString Val) = 0 ;
	__property System::UnicodeString Pragma = {read=GetPragma, write=SetPragma};
	virtual System::UnicodeString __fastcall GetConnection() = 0 ;
	virtual void __fastcall SetConnection(System::UnicodeString conn) = 0 ;
	__property System::UnicodeString Connection = {read=GetConnection, write=SetConnection};
	virtual System::UnicodeString __fastcall GetCharSet() = 0 ;
	virtual void __fastcall SetCharSet(System::UnicodeString Val) = 0 ;
	__property System::UnicodeString CharSet = {read=GetCharSet, write=SetCharSet};
	virtual System::TDateTime __fastcall GetLastModified() = 0 ;
	virtual void __fastcall SetLastModified(System::TDateTime dt) = 0 ;
	__property System::TDateTime LastModified = {read=GetLastModified, write=SetLastModified};
	virtual System::TDateTime __fastcall GetDate() = 0 ;
	virtual void __fastcall SetDate(System::TDateTime LDate) = 0 ;
	__property System::TDateTime Date = {read=GetDate, write=SetDate};
	virtual System::UnicodeString __fastcall GetETag() = 0 ;
	virtual void __fastcall SetETag(System::UnicodeString LETag) = 0 ;
	__property System::UnicodeString ETag = {read=GetETag, write=SetETag};
};

__interface  INTERFACE_UUID("{39633B1B-96D4-4178-ABC2-11B2CE5496B0}") IIPHTTPRequest  : public IIPEntityHeaderInfo 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPAuthentication __fastcall GetAuthentication() = 0 ;
	virtual void __fastcall SetAuthentication(const _di_IIPAuthentication auth) = 0 ;
	__property _di_IIPAuthentication Authentication = {read=GetAuthentication, write=SetAuthentication};
	virtual System::UnicodeString __fastcall GetAccept() = 0 ;
	virtual void __fastcall SetAccept(const System::UnicodeString Val) = 0 ;
	virtual System::UnicodeString __fastcall GetUserAgent() = 0 ;
	virtual void __fastcall SetUserAgent(const System::UnicodeString Val) = 0 ;
	virtual System::UnicodeString __fastcall GetAcceptCharSet() = 0 ;
	virtual void __fastcall SetAcceptCharSet(const System::UnicodeString Val) = 0 ;
	virtual System::UnicodeString __fastcall GetAcceptEncoding() = 0 ;
	virtual void __fastcall SetAcceptEncoding(const System::UnicodeString Val) = 0 ;
	__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept};
	__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent};
	__property System::UnicodeString AcceptCharSet = {read=GetAcceptCharSet, write=SetAcceptCharSet};
	__property System::UnicodeString AcceptEncoding = {read=GetAcceptEncoding, write=SetAcceptEncoding};
};

__interface  INTERFACE_UUID("{03EDCF40-C924-4932-A5C9-37A1E14FDFD8}") IIPHTTPResponse  : public IIPEntityHeaderInfo 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetResponseText() = 0 ;
	virtual void __fastcall SetResponseText(System::UnicodeString LResponseText) = 0 ;
	__property System::UnicodeString ResponseText = {read=GetResponseText, write=SetResponseText};
};

__interface  INTERFACE_UUID("{C4DCD800-5288-468F-9496-8D1821E8458A}") IIPProxyConnectionInfo  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual int __fastcall GetProxyPort() = 0 ;
	virtual void __fastcall SetProxyPort(int Val) = 0 ;
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
	virtual bool __fastcall GetBasicAuthentication() = 0 ;
	virtual void __fastcall SetBasicAuthentication(bool Val) = 0 ;
	__property bool BasicAuthentication = {read=GetBasicAuthentication, write=SetBasicAuthentication};
};

__interface  INTERFACE_UUID("{EB5DB0CE-3D5B-43F1-B214-95AE3E1548AD}") IIPTCPConnection  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual bool __fastcall Connected() = 0 ;
	virtual _di_IIPIOHandler __fastcall GetIOHandler() = 0 ;
	virtual void __fastcall SetIOHandler(_di_IIPIOHandler Handler) = 0 ;
	__property _di_IIPIOHandler IOHandler = {read=GetIOHandler, write=SetIOHandler};
	virtual void __fastcall Disconnect() = 0 ;
	virtual _di_IIPIOHandlerSocket __fastcall GetSocket() = 0 ;
	__property _di_IIPIOHandlerSocket Socket = {read=GetSocket};
	virtual bool __fastcall GetManagedIOHandler() = 0 ;
	virtual void __fastcall SetManagedIOHandler(bool AManagedIOHandler) = 0 ;
	__property bool ManagedIOHandler = {read=GetManagedIOHandler, write=SetManagedIOHandler};
};

__interface  INTERFACE_UUID("{2C0539B1-2733-4E17-A71C-991D62C98B8E}") IIPTCPClientCustom  : public IIPTCPConnection 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual void __fastcall SetIPVersion(const TIPVersionPeer AValue) = 0 ;
	virtual TIPVersionPeer __fastcall GetIPVersion() = 0 ;
	__property TIPVersionPeer IPVersion = {read=GetIPVersion, write=SetIPVersion};
};

__interface  INTERFACE_UUID("{B8BD5BD8-C39D-4DF1-BB14-625FC86029DB}") IIPHTTP  : public IIPTCPClientCustom 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetProtocol() = 0 ;
	virtual void __fastcall SetProtocol(System::UnicodeString Protocol) = 0 ;
	__property System::UnicodeString Protocol = {read=GetProtocol, write=SetProtocol};
	virtual int __fastcall GetResponseCode() = 0 ;
	__property int ResponseCode = {read=GetResponseCode};
	virtual System::UnicodeString __fastcall GetResponseText() = 0 ;
	__property System::UnicodeString ResponseText = {read=GetResponseText};
	virtual _di_IIPHTTPResponse __fastcall GetResponse() = 0 ;
	__property _di_IIPHTTPResponse Response = {read=GetResponse};
	virtual _di_IIPHTTPRequest __fastcall GetRequest() = 0 ;
	__property _di_IIPHTTPRequest Request = {read=GetRequest};
	virtual void __fastcall FreeIOHandler() = 0 ;
	virtual _di_IIPProxyConnectionInfo __fastcall GetProxyParams() = 0 ;
	virtual void __fastcall SetProxyParams(const _di_IIPProxyConnectionInfo Value) = 0 ;
	__property _di_IIPProxyConnectionInfo ProxyParams = {read=GetProxyParams, write=SetProxyParams};
	virtual TIPHTTPOptionsPeer __fastcall GetHTTPOptions() = 0 ;
	virtual void __fastcall SetHTTPOptions(TIPHTTPOptionsPeer Options) = 0 ;
	__property TIPHTTPOptionsPeer HTTPOptions = {read=GetHTTPOptions, write=SetHTTPOptions};
	virtual void __fastcall DoRequestMethod(System::UnicodeString AMethod, System::UnicodeString URL, System::Classes::TStream* Source, System::Classes::TStream* ResponseContent, short *AIgnoreReplies, const int AIgnoreReplies_High) = 0 ;
	virtual void __fastcall DoRequestDelete(System::UnicodeString URL, System::Classes::TStream* Source, System::Classes::TStream* ResponseContent, short *AIgnoreReplies, const int AIgnoreReplies_High) = 0 ;
	virtual void __fastcall DoRequestHead(System::UnicodeString URL, System::Classes::TStream* Source, System::Classes::TStream* ResponseContent, short *AIgnoreReplies, const int AIgnoreReplies_High) = 0 ;
	virtual System::UnicodeString __fastcall DoGet(System::UnicodeString AURL) = 0 /* overload */;
	virtual System::UnicodeString __fastcall DoGet(System::UnicodeString AURL, System::Classes::TStream* AResponseContent) = 0 /* overload */;
	virtual System::UnicodeString __fastcall DoPost(System::UnicodeString AURL, System::Classes::TStream* Source) = 0 /* overload */;
	virtual System::UnicodeString __fastcall DoPost(System::UnicodeString AURL, System::Classes::TStrings* Source) = 0 /* overload */;
	virtual void __fastcall DoPost(System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent) = 0 /* overload */;
	virtual System::UnicodeString __fastcall DoPut(System::UnicodeString AURL, System::Classes::TStream* Source) = 0 /* overload */;
	virtual void __fastcall DoPut(System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent) = 0 /* overload */;
	virtual System::UnicodeString __fastcall DoPatch(System::UnicodeString AURL, System::Classes::TStream* Source) = 0 /* overload */;
	virtual void __fastcall DoPatch(System::UnicodeString AURL, System::Classes::TStream* ASource, System::Classes::TStream* AResponseContent) = 0 /* overload */;
	virtual bool __fastcall GetUseNagle() = 0 ;
	virtual void __fastcall SetUseNagle(bool Use) = 0 ;
	__property bool UseNagle = {read=GetUseNagle, write=SetUseNagle};
	virtual int __fastcall GetConnectTimeout() = 0 ;
	virtual void __fastcall SetConnectTimeout(int timeout) = 0 ;
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout};
	virtual int __fastcall GetReadTimeout() = 0 ;
	virtual void __fastcall SetReadTimeout(int timeout) = 0 ;
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout};
	virtual _di_IIPURI __fastcall GetURL() = 0 ;
	__property _di_IIPURI URL = {read=GetURL};
	virtual _di_IIPCookieManager __fastcall GetCookieManager() = 0 ;
	__property _di_IIPCookieManager CookieManager = {read=GetCookieManager};
	virtual bool __fastcall GetHandleRedirects() = 0 ;
	virtual void __fastcall SetHandleRedirects(bool AValue) = 0 ;
	__property bool HandleRedirects = {read=GetHandleRedirects, write=SetHandleRedirects};
	virtual bool __fastcall GetAllowCookies() = 0 ;
	virtual void __fastcall SetAllowCookies(bool AValue) = 0 ;
	__property bool AllowCookies = {read=GetAllowCookies, write=SetAllowCookies};
};

__interface  INTERFACE_UUID("{9BB0BE5C-9D9E-485E-803D-999645CE1B8F}") IIPTCPClient  : public IIPTCPClientCustom 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetBoundIP() = 0 ;
	virtual void __fastcall SetBoundIP(System::UnicodeString IP) = 0 ;
	__property System::UnicodeString BoundIP = {read=GetBoundIP, write=SetBoundIP};
	virtual System::UnicodeString __fastcall GetHost() = 0 ;
	virtual void __fastcall SetHost(System::UnicodeString LHost) = 0 ;
	__property System::UnicodeString Host = {read=GetHost, write=SetHost};
	virtual System::Word __fastcall GetPort() = 0 ;
	virtual void __fastcall SetPort(System::Word LPort) = 0 ;
	__property System::Word Port = {read=GetPort, write=SetPort};
	virtual bool __fastcall GetUseNagle() = 0 ;
	virtual void __fastcall SetUseNagle(bool Use) = 0 ;
	__property bool UseNagle = {read=GetUseNagle, write=SetUseNagle};
	virtual void __fastcall Connect() = 0 ;
	HIDESBASE virtual bool __fastcall GetManagedIOHandler() = 0 ;
	HIDESBASE virtual void __fastcall SetManagedIOHandler(bool AManagedIOHandler) = 0 ;
	virtual int __fastcall GetConnectTimeout() = 0 ;
	virtual void __fastcall SetConnectTimeout(int timeout) = 0 ;
	__property int ConnectTimeout = {read=GetConnectTimeout, write=SetConnectTimeout};
	virtual int __fastcall GetReadTimeout() = 0 ;
	virtual void __fastcall SetReadTimeout(int timeout) = 0 ;
	__property int ReadTimeout = {read=GetReadTimeout, write=SetReadTimeout};
};

__interface  INTERFACE_UUID("{F3DC885A-07C9-42F5-A07B-92E95BDAFEB0}") IIPX509Name  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual TIPSSLULong __fastcall GetHash() = 0 ;
	__property TIPSSLULong Hash = {read=GetHash};
	virtual System::UnicodeString __fastcall GetOneLine() = 0 ;
	__property System::UnicodeString OneLine = {read=GetOneLine};
};

__interface  INTERFACE_UUID("{A93FF0DD-7E16-48E9-A0FC-6CF0AFDB19B3}") IIPX509SigInfo  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetSigTypeAsString() = 0 ;
	__property System::UnicodeString SigTypeAsString = {read=GetSigTypeAsString};
	virtual System::UnicodeString __fastcall GetSignature() = 0 ;
	__property System::UnicodeString Signature = {read=GetSignature};
};

__interface  INTERFACE_UUID("{4B101B6D-9C18-4579-A381-0F238A01CC18}") IIPX509  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::TDateTime __fastcall GetNotAfter() = 0 ;
	__property System::TDateTime notAfter = {read=GetNotAfter};
	virtual System::TDateTime __fastcall GetNotBefore() = 0 ;
	__property System::TDateTime notBefore = {read=GetNotBefore};
	virtual _di_IIPX509Name __fastcall GetIssuer() = 0 ;
	__property _di_IIPX509Name Issuer = {read=GetIssuer};
	virtual _di_IIPX509Name __fastcall GetSubject() = 0 ;
	__property _di_IIPX509Name Subject = {read=GetSubject};
	virtual System::UnicodeString __fastcall GetSerialNumber() = 0 ;
	__property System::UnicodeString SerialNumber = {read=GetSerialNumber};
	virtual _di_IIPX509SigInfo __fastcall GetSigInfo() = 0 ;
	__property _di_IIPX509SigInfo SigInfo = {read=GetSigInfo};
#ifndef __aarch64__
	virtual int __fastcall GetVersion() = 0 ;
	__property int Version = {read=GetVersion};
#else /* __aarch64__ */
	virtual long __fastcall GetVersion() = 0 ;
	__property long Version = {read=GetVersion};
#endif /* __aarch64__ */
	virtual System::TArray__1<System::Byte> __fastcall GetEncoded() = 0 ;
	__property System::TArray__1<System::Byte> EncodedCertificate = {read=GetEncoded};
	virtual int __fastcall GetBasicConstraints() = 0 ;
	__property int BasicConstraints = {read=GetBasicConstraints};
	virtual System::UnicodeString __fastcall GetKeyAlgorithm() = 0 ;
	__property System::UnicodeString KeyAlgorithm = {read=GetKeyAlgorithm};
	virtual System::TArray__1<System::Byte> __fastcall GetEncodedKey() = 0 ;
	__property System::TArray__1<System::Byte> EncodedKey = {read=GetEncodedKey};
	virtual System::UnicodeString __fastcall GetKeyFormat() = 0 ;
	__property System::UnicodeString KeyFormat = {read=GetKeyFormat};
	virtual bool __fastcall Verify(_di_IIPX509 Root) = 0 ;
};

__interface  INTERFACE_UUID("{B44903AF-A307-47D5-AA2C-6C7967741C9D}") IIPBasicAuthentication  : public IIPAuthentication 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetAuthentication() = 0 ;
};

__interface  INTERFACE_UUID("{DF4F2321-EAC7-4D69-A290-8E0303627C6B}") IIPHashMessageDigest5  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall HashBytesAsHex(const System::TArray__1<System::Byte> ASrc) = 0 ;
	virtual System::UnicodeString __fastcall HashStringAsHex(const System::UnicodeString ASrc) = 0 ;
};

__interface  INTERFACE_UUID("{86E02B92-FE6E-4270-AD67-3BA5EC0DC17D}") IIPTask  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::TObject* __fastcall GetData() = 0 ;
	virtual void __fastcall SetData(System::TObject* obj) = 0 ;
	__property System::TObject* Data = {read=GetData, write=SetData};
};

__interface  INTERFACE_UUID("{8606D1C2-A4A1-4A44-974C-873294194710}") IIPContext  : public IIPTask 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPTCPConnection __fastcall GetConnection() = 0 ;
	__property _di_IIPTCPConnection Connection = {read=GetConnection};
};

__interface  INTERFACE_UUID("{86AAE104-1DFD-42BF-9413-80924AD69E0D}") IIPServerIOHandler  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

__interface  INTERFACE_UUID("{7096171F-E11C-42F1-9EA4-63B518707918}") IIPServerIOHandlerSSLBase  : public IIPServerIOHandler 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

typedef void __fastcall (__closure *TPasswordEventPeer)(System::Sysutils::TStringBuilder* Password);

__interface  INTERFACE_UUID("{1DAC20E8-A925-409F-AD04-5E7F34DAA838}") IIPServerIOHandlerSSLOpenSSL  : public IIPServerIOHandlerSSLBase 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPSSLOptions __fastcall GetSSLOptions() = 0 ;
	__property _di_IIPSSLOptions SSLOptions = {read=GetSSLOptions};
	virtual TPasswordEventPeer __fastcall GetOnGetPassword() = 0 ;
	virtual void __fastcall SetOnGetPassword(TPasswordEventPeer event) = 0 ;
	__property TPasswordEventPeer OnGetPassword = {read=GetOnGetPassword, write=SetOnGetPassword};
};

__interface  INTERFACE_UUID("{669C7234-B3D3-4DF4-8A1F-4A5DA39AD3AF}") IIPRequestHeaderInfo  : public IIPEntityHeaderInfo 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetAccept() = 0 ;
	virtual void __fastcall SetAccept(System::UnicodeString Val) = 0 ;
	__property System::UnicodeString Accept = {read=GetAccept, write=SetAccept};
	virtual System::UnicodeString __fastcall GetUserAgent() = 0 ;
	virtual void __fastcall SetUserAgent(System::UnicodeString agent) = 0 ;
	__property System::UnicodeString UserAgent = {read=GetUserAgent, write=SetUserAgent};
};

__interface  INTERFACE_UUID("{ECE3C261-E15E-4526-80FE-1E99D4B96106}") IIPHTTPSession  : public System::IInterface 
{
	virtual System::UnicodeString __fastcall GetSessionID() = 0 ;
	__property System::UnicodeString SessionID = {read=GetSessionID};
};

__interface  INTERFACE_UUID("{02280AAE-0D78-435D-B962-9A47E84F9D8A}") IIPHTTPRequestInfo  : public IIPRequestHeaderInfo 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPHTTPSession __fastcall GetSession() = 0 ;
	__property _di_IIPHTTPSession Session = {read=GetSession};
	virtual System::UnicodeString __fastcall GetAuthPassword() = 0 ;
	__property System::UnicodeString AuthPassword = {read=GetAuthPassword};
	virtual System::UnicodeString __fastcall GetAuthUsername() = 0 ;
	__property System::UnicodeString AuthUsername = {read=GetAuthUsername};
	virtual System::UnicodeString __fastcall GetCommand() = 0 ;
	__property System::UnicodeString Command = {read=GetCommand};
	virtual THTTPCommandTypePeer __fastcall GetCommandType() = 0 ;
	__property THTTPCommandTypePeer CommandType = {read=GetCommandType};
	virtual System::UnicodeString __fastcall GetDocument() = 0 ;
	virtual void __fastcall SetDocument(System::UnicodeString doc) = 0 ;
	__property System::UnicodeString Document = {read=GetDocument, write=SetDocument};
	virtual System::Classes::TStrings* __fastcall GetParams() = 0 ;
	__property System::Classes::TStrings* Params = {read=GetParams};
	virtual System::Classes::TStream* __fastcall GetPostStream() = 0 ;
	virtual void __fastcall SetPostStream(System::Classes::TStream* ps) = 0 ;
	__property System::Classes::TStream* PostStream = {read=GetPostStream, write=SetPostStream};
	virtual System::UnicodeString __fastcall GetRemoteIP() = 0 ;
	__property System::UnicodeString RemoteIP = {read=GetRemoteIP};
	virtual System::UnicodeString __fastcall GetURI() = 0 ;
	__property System::UnicodeString URI = {read=GetURI};
	virtual System::UnicodeString __fastcall GetVersion() = 0 ;
	__property System::UnicodeString Version = {read=GetVersion};
};

__interface  INTERFACE_UUID("{884397D2-D332-40BA-823E-1B100C0499D9}") IIPResponseHeaderInfo  : public IIPEntityHeaderInfo 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPHeaderList __fastcall GetWWWAuthenticate() = 0 ;
	virtual void __fastcall SetWWWAuthenticate(_di_IIPHeaderList wwwAuth) = 0 ;
	__property _di_IIPHeaderList WWWAuthenticate = {read=GetWWWAuthenticate, write=SetWWWAuthenticate};
};

__interface  INTERFACE_UUID("{BBBAA4A7-C28B-4128-B21C-B1437FB3A57F}") IIPHTTPResponseInfo  : public IIPResponseHeaderInfo 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetAuthRealm() = 0 ;
	virtual void __fastcall SetAuthRealm(System::UnicodeString realm) = 0 ;
	__property System::UnicodeString AuthRealm = {read=GetAuthRealm, write=SetAuthRealm};
	virtual bool __fastcall GetCloseConnection() = 0 ;
	virtual void __fastcall SetCloseConnection(bool closeConn) = 0 ;
	__property bool CloseConnection = {read=GetCloseConnection, write=SetCloseConnection};
	virtual System::Classes::TStream* __fastcall GetContentStream() = 0 ;
	virtual void __fastcall SetContentStream(System::Classes::TStream* content) = 0 ;
	__property System::Classes::TStream* ContentStream = {read=GetContentStream, write=SetContentStream};
	virtual System::UnicodeString __fastcall GetContentText() = 0 ;
	virtual void __fastcall SetContentText(System::UnicodeString text) = 0 ;
	__property System::UnicodeString ContentText = {read=GetContentText, write=SetContentText};
	virtual bool __fastcall GetFreeContentStream() = 0 ;
	virtual void __fastcall SetFreeContentStream(bool Val) = 0 ;
	__property bool FreeContentStream = {read=GetFreeContentStream, write=SetFreeContentStream};
	virtual int __fastcall GetResponseNo() = 0 ;
	virtual void __fastcall SetResponseNo(int Num) = 0 ;
	__property int ResponseNo = {read=GetResponseNo, write=SetResponseNo};
	virtual System::UnicodeString __fastcall GetResponseText() = 0 ;
	virtual void __fastcall SetResponseText(System::UnicodeString text) = 0 ;
	__property System::UnicodeString ResponseText = {read=GetResponseText, write=SetResponseText};
	virtual bool __fastcall GetHeaderHasBeenWritten() = 0 ;
	virtual void __fastcall SetHeaderHasBeenWritten(bool Val) = 0 ;
	__property bool HeaderHasBeenWritten = {read=GetHeaderHasBeenWritten, write=SetHeaderHasBeenWritten};
	virtual void __fastcall WriteHeader() = 0 ;
	virtual void __fastcall WriteContent() = 0 ;
};

__interface  INTERFACE_UUID("{542114D6-53EA-4EBC-82CF-BA0C81024660}") IIPSocketHandle  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::UnicodeString __fastcall GetIP() = 0 ;
	virtual void __fastcall SetIP(const System::UnicodeString AIP) = 0 ;
	__property System::UnicodeString IP = {read=GetIP, write=SetIP};
	virtual System::Word __fastcall GetPort() = 0 ;
	virtual void __fastcall SetPort(System::Word APort) = 0 ;
	__property System::Word Port = {read=GetPort, write=SetPort};
	virtual TIPVersionPeer __fastcall GetIPVersion() = 0 ;
	virtual void __fastcall SetIPVersion(const TIPVersionPeer Value) = 0 ;
	__property TIPVersionPeer IPVersion = {read=GetIPVersion, write=SetIPVersion};
	virtual NativeUInt __fastcall GetHandle() = 0 ;
	__property NativeUInt Handle = {read=GetHandle};
	virtual System::UnicodeString __fastcall GetPeerIP() = 0 ;
	__property System::UnicodeString PeerIP = {read=GetPeerIP};
	virtual System::Word __fastcall GetPeerPort() = 0 ;
	__property System::Word PeerPort = {read=GetPeerPort};
	virtual void __fastcall Broadcast(const System::TArray__1<System::Byte> AData, const System::Word APort, const System::UnicodeString AIP = System::UnicodeString()) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{E9ADA63C-3488-4E2F-9FBC-95B77D743EA0}") IIPSocketHandles  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPSocketHandle __fastcall Add() = 0 ;
	virtual int __fastcall GetCount() = 0 ;
	__property int Count = {read=GetCount};
	virtual _di_IIPSocketHandle __fastcall GetSocket(int Index) = 0 ;
	__property _di_IIPSocketHandle Sockets[int Index] = {read=GetSocket};
};

__interface  INTERFACE_UUID("{D8438597-7E6C-4391-AA46-7461A8D4DFCF}") IIPScheduler  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

__interface  INTERFACE_UUID("{30111A7A-6DE1-4226-B89D-25BCE9B0C948}") IIPSchedulerOfThread  : public IIPScheduler 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual int __fastcall GetMaxThreads() = 0 ;
	virtual void __fastcall SetMaxThreads(int AMaxThreads) = 0 ;
	__property int MaxThreads = {read=GetMaxThreads, write=SetMaxThreads};
};

__interface  INTERFACE_UUID("{B13D508C-4086-436C-8AD9-12B35357D459}") IIPSchedulerOfThreadPool  : public IIPSchedulerOfThread 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual int __fastcall GetPoolSize() = 0 ;
	virtual void __fastcall SetPoolSize(int APoolSize) = 0 ;
	__property int PoolSize = {read=GetPoolSize, write=SetPoolSize};
};

typedef void __fastcall (__closure *TIPServerThreadEventPeer)(_di_IIPContext AContext);

__interface  INTERFACE_UUID("{46682F3B-9FC8-4ED2-8D75-89849A685875}") IIPTestServer  : public System::IInterface 
{
	virtual int __fastcall GetOpenPort() = 0 ;
	virtual void __fastcall TestOpenPort(const int APort, const TIPServerThreadEventPeer AOnExecute) = 0 ;
	virtual void __fastcall TestCertificateFiles(const int APort, const System::UnicodeString ACertFileName, const System::UnicodeString AKeyFileName, const System::UnicodeString ARootCertFile, const System::UnicodeString AKeyFilePassword) = 0 ;
	virtual void __fastcall GetExtensionMimeType(System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* const ADictionary) = 0 ;
};

__interface  INTERFACE_UUID("{2CF0128C-5F38-4F66-BC22-148C6AFF731C}") IIPCustomTCPServer  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall SetActive(bool Val) = 0 ;
	__property bool Active = {read=GetActive, write=SetActive};
	virtual System::Word __fastcall GetDefaultPort() = 0 ;
	virtual void __fastcall SetDefaultPort(System::Word port) = 0 ;
	__property System::Word DefaultPort = {read=GetDefaultPort, write=SetDefaultPort};
	virtual _di_IIPServerIOHandler __fastcall GetIOHandler() = 0 ;
	virtual void __fastcall SetIOHandler(_di_IIPServerIOHandler handler) = 0 ;
	__property _di_IIPServerIOHandler IOHandler = {read=GetIOHandler, write=SetIOHandler};
	virtual TIPServerThreadEventPeer __fastcall GetOnConnect() = 0 ;
	virtual void __fastcall SetOnConnect(TIPServerThreadEventPeer event) = 0 ;
	__property TIPServerThreadEventPeer OnConnect = {read=GetOnConnect, write=SetOnConnect};
	virtual TIPServerThreadEventPeer __fastcall GetOnDisconnect() = 0 ;
	virtual void __fastcall SetOnDisconnect(TIPServerThreadEventPeer event) = 0 ;
	__property TIPServerThreadEventPeer OnDisconnect = {read=GetOnDisconnect, write=SetOnDisconnect};
	virtual TIPServerThreadEventPeer __fastcall GetOnExecute() = 0 ;
	virtual void __fastcall SetOnExecute(TIPServerThreadEventPeer event) = 0 ;
	__property TIPServerThreadEventPeer OnExecute = {read=GetOnExecute, write=SetOnExecute};
	virtual bool __fastcall GetUseNagle() = 0 ;
	virtual void __fastcall SetUseNagle(bool Use) = 0 ;
	__property bool UseNagle = {read=GetUseNagle, write=SetUseNagle};
	virtual _di_IIPSocketHandles __fastcall GetBindings() = 0 ;
	virtual void __fastcall SetBindings(_di_IIPSocketHandles ABindings) = 0 ;
	__property _di_IIPSocketHandles Bindings = {read=GetBindings, write=SetBindings};
	virtual _di_IIPScheduler __fastcall GetScheduler() = 0 ;
	virtual void __fastcall SetScheduler(_di_IIPScheduler AScheduler) = 0 ;
	__property _di_IIPScheduler Scheduler = {read=GetScheduler, write=SetScheduler};
};

__interface  INTERFACE_UUID("{EA8DE2F9-9055-4073-8118-437283DC02D6}") IIPTCPServer  : public IIPCustomTCPServer 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

__interface  INTERFACE_UUID("{8C917297-CC97-419B-8FEB-130512FDD595}") IIPUDPListenerThread  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

typedef void __fastcall (__closure *TIPUDPReadEventPeer)(_di_IIPUDPListenerThread AThread, const System::TArray__1<System::Byte> AData, _di_IIPSocketHandle ABinding);

typedef void __fastcall (__closure *TIPUDPExceptionEventPeer)(_di_IIPUDPListenerThread AThread, _di_IIPSocketHandle ABinding, const System::UnicodeString AMessage, const System::TClass AExceptionClass);

__interface  INTERFACE_UUID("{2BEFBDFB-D277-429A-8DAB-C96BE0A650E2}") IIPCustomUDPServer  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall SetActive(bool Val) = 0 ;
	__property bool Active = {read=GetActive, write=SetActive};
	virtual System::Word __fastcall GetDefaultPort() = 0 ;
	virtual void __fastcall SetDefaultPort(System::Word APort) = 0 ;
	__property System::Word DefaultPort = {read=GetDefaultPort, write=SetDefaultPort};
	virtual TIPUDPReadEventPeer __fastcall GetOnRead() = 0 ;
	virtual void __fastcall SetOnRead(TIPUDPReadEventPeer AEvent) = 0 ;
	__property TIPUDPReadEventPeer OnRead = {read=GetOnRead, write=SetOnRead};
	virtual TIPUDPExceptionEventPeer __fastcall GetOnException() = 0 ;
	virtual void __fastcall SetOnException(TIPUDPExceptionEventPeer AEvent) = 0 ;
	__property TIPUDPExceptionEventPeer OnException = {read=GetOnException, write=SetOnException};
	virtual _di_IIPSocketHandles __fastcall GetBindings() = 0 ;
	virtual void __fastcall SetBindings(_di_IIPSocketHandles ABindings) = 0 ;
	__property _di_IIPSocketHandles Bindings = {read=GetBindings, write=SetBindings};
	virtual bool __fastcall GetThreadedEvent() = 0 ;
	virtual void __fastcall SetThreadedEvent(const bool Value) = 0 ;
	__property bool ThreadedEvent = {read=GetThreadedEvent, write=SetThreadedEvent};
	virtual void __fastcall Broadcast(const System::UnicodeString AData, const System::Word APort, const System::UnicodeString AIP = System::UnicodeString(), System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 /* overload */;
	virtual void __fastcall Broadcast(const System::TArray__1<System::Byte> AData, const System::Word APort, const System::UnicodeString AIP = System::UnicodeString()) = 0 /* overload */;
	virtual void __fastcall Send(const System::UnicodeString AHost, const System::Word APort, const System::UnicodeString AData, System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 ;
	virtual void __fastcall SendBuffer(const System::UnicodeString AHost, const System::Word APort, const System::TArray__1<System::Byte> ABuffer) = 0 ;
	virtual TIPVersionPeer __fastcall GetIPVersion() = 0 ;
	virtual void __fastcall SetIPVersion(const TIPVersionPeer AValue) = 0 ;
	__property TIPVersionPeer IPVersion = {read=GetIPVersion, write=SetIPVersion};
};

__interface  INTERFACE_UUID("{71471FE5-5CA0-4C80-B856-000628214707}") IIPUDPServer  : public IIPCustomUDPServer 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

typedef void __fastcall (__closure *TIPHTTPCommandEventPeer)(_di_IIPContext AContext, _di_IIPHTTPRequestInfo ARequestInfo, _di_IIPHTTPResponseInfo AResponseInfo);

__interface  INTERFACE_UUID("{D8568F50-B792-4516-8B0B-4E3EB8868194}") IIPHTTPServer  : public IIPCustomTCPServer 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	HIDESBASE virtual bool __fastcall GetUseNagle() = 0 ;
	HIDESBASE virtual void __fastcall SetUseNagle(bool Use) = 0 ;
	__property bool UseNagle = {read=GetUseNagle, write=SetUseNagle};
	virtual bool __fastcall GetKeepAlive() = 0 ;
	virtual void __fastcall SetKeepAlive(bool keep) = 0 ;
	__property bool KeepAlive = {read=GetKeepAlive, write=SetKeepAlive};
	virtual System::UnicodeString __fastcall GetServerSoftware() = 0 ;
	virtual void __fastcall SetServerSoftware(System::UnicodeString software) = 0 ;
	__property System::UnicodeString ServerSoftware = {read=GetServerSoftware, write=SetServerSoftware};
	virtual TIPHTTPCommandEventPeer __fastcall GetOnCommandGet() = 0 ;
	virtual void __fastcall SetOnCommandGet(TIPHTTPCommandEventPeer commandGet) = 0 ;
	__property TIPHTTPCommandEventPeer OnCommandGet = {read=GetOnCommandGet, write=SetOnCommandGet};
	virtual TIPHTTPCommandEventPeer __fastcall GetOnCommandOther() = 0 ;
	virtual void __fastcall SetOnCommandOther(TIPHTTPCommandEventPeer commandOther) = 0 ;
	__property TIPHTTPCommandEventPeer OnCommandOther = {read=GetOnCommandOther, write=SetOnCommandOther};
};

typedef void __fastcall (__closure *TIPMCastReadEventPeer)(System::TObject* Sender, const System::TArray__1<System::Byte> AData, const _di_IIPSocketHandle ABinding);

__interface  INTERFACE_UUID("{E6221277-6558-48BB-9E85-970D1E86FA42}") IIPCustomMulticastBase  : public System::IInterface 
{
	virtual System::TObject* __fastcall GetObject() = 0 ;
	virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual _di_IIPSocketHandle __fastcall GetBinding() = 0 ;
	virtual bool __fastcall GetActive() = 0 ;
	virtual void __fastcall SetActive(const bool AValue) = 0 ;
	virtual System::UnicodeString __fastcall GetMulticastGroup() = 0 ;
	virtual void __fastcall SetMulticastGroup(const System::UnicodeString AValue) = 0 ;
	virtual System::Word __fastcall GetPort() = 0 ;
	virtual void __fastcall SetPort(const System::Word Value) = 0 ;
	virtual TIPVersionPeer __fastcall GetIPVersion() = 0 ;
	virtual void __fastcall SetIPVersion(const TIPVersionPeer AValue) = 0 ;
	__property bool Active = {read=GetActive, write=SetActive};
	__property System::UnicodeString MulticastGroup = {read=GetMulticastGroup, write=SetMulticastGroup};
	__property System::Word Port = {read=GetPort, write=SetPort};
	__property TIPVersionPeer IPVersion = {read=GetIPVersion, write=SetIPVersion};
};

__interface  INTERFACE_UUID("{89B13261-3AAE-43D8-9D28-0D072ACD5641}") IIPCustomMulticastClient  : public IIPCustomMulticastBase 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual TIPMCastReadEventPeer __fastcall GetOnMulticast() = 0 ;
	virtual void __fastcall SetOnMulticast(const TIPMCastReadEventPeer AEvent) = 0 ;
	__property TIPMCastReadEventPeer OnMulticast = {read=GetOnMulticast, write=SetOnMulticast};
	virtual System::Word __fastcall GetDefaultPort() = 0 ;
	virtual void __fastcall SetDefaultPort(const System::Word APort) = 0 ;
	__property System::Word DefaultPort = {read=GetDefaultPort, write=SetDefaultPort};
	virtual bool __fastcall GetThreadedEvent() = 0 ;
	virtual void __fastcall SetThreadedEvent(const bool AValue) = 0 ;
	__property bool ThreadedEvent = {read=GetThreadedEvent, write=SetThreadedEvent};
	virtual _di_IIPSocketHandles __fastcall GetBindings() = 0 ;
	virtual void __fastcall SetBindings(_di_IIPSocketHandles ABindings) = 0 ;
	__property _di_IIPSocketHandles Bindings = {read=GetBindings, write=SetBindings};
};

__interface  INTERFACE_UUID("{26A69A5F-5DD7-4A3A-9A03-7399EB8F6605}") IIPMulticastClient  : public IIPCustomMulticastClient 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

__interface  INTERFACE_UUID("{BB277203-62F9-47CF-A159-88929E94B7FF}") IIPCustomMulticastServer  : public IIPCustomMulticastBase 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
	virtual System::Word __fastcall GetBoundPort() = 0 ;
	virtual void __fastcall SetBoundPort(const System::Word APort) = 0 ;
	virtual System::UnicodeString __fastcall GetBoundIP() = 0 ;
	virtual void __fastcall SetBoundIP(const System::UnicodeString ABoundIP) = 0 ;
	virtual bool __fastcall GetLoopback() = 0 ;
	virtual void __fastcall SetLoopback(const bool AValue) = 0 ;
	virtual System::Byte __fastcall GetTTL() = 0 ;
	virtual void __fastcall SetTTL(const System::Byte AValue) = 0 ;
	virtual void __fastcall Send(const System::UnicodeString AData, const System::_di_IInterface AByteEncoding = System::_di_IInterface()) = 0 /* overload */;
	virtual void __fastcall Send(const System::TArray__1<System::Byte> ABuffer) = 0 /* overload */;
	virtual void __fastcall Send(const System::TArray__1<System::Byte> ABuffer, const System::Word APort) = 0 /* overload */;
	__property _di_IIPSocketHandle Binding = {read=GetBinding};
	__property System::UnicodeString BoundIP = {read=GetBoundIP, write=SetBoundIP};
	__property System::Word BoundPort = {read=GetBoundPort, write=SetBoundPort};
	__property bool Loopback = {read=GetLoopback, write=SetLoopback};
	__property System::Byte TimeToLive = {read=GetTTL, write=SetTTL};
};

__interface  INTERFACE_UUID("{42FACB28-10EA-4334-9E68-22DFB3072999}") IIPMulticastServer  : public IIPCustomMulticastServer 
{
	HIDESBASE virtual System::TObject* __fastcall GetObject() = 0 ;
	HIDESBASE virtual System::UnicodeString __fastcall GetIPImplementationID() = 0 ;
};

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 _IPPORT_HTTP = System::Int8(0x50);
extern DELPHI_PACKAGE _di_IIPStack GStackPeer;
extern DELPHI_PACKAGE _di_IIPStack __fastcall GStackPeers(const System::UnicodeString ImplementationID = System::UnicodeString());
extern DELPHI_PACKAGE _di_IIPPeerProcs __fastcall IPProcs(const System::UnicodeString ImplementationID = System::UnicodeString());
extern DELPHI_PACKAGE TIPPeerFactory* __fastcall PeerFactory(void);
}	/* namespace Ippeerapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IPPEERAPI)
using namespace Ippeerapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// IppeerapiHPP
