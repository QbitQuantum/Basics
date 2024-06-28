// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Androidapi.JNI.Java.Net.pas' rev: 34.00 (Android)

#ifndef Androidapi_Jni_Java_NetHPP
#define Androidapi_Jni_Java_NetHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Androidapi.JNIBridge.hpp>
#include <Androidapi.JNI.Java.Security.hpp>
#include <Androidapi.JNI.JavaTypes.hpp>
#include <Androidapi.Jni.hpp>
#include <System.Rtti.hpp>

//-- user supplied -----------------------------------------------------------

namespace Androidapi
{
namespace Jni
{
namespace Java
{
namespace Net
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE JCacheRequestClass;
typedef System::DelphiInterface<JCacheRequestClass> _di_JCacheRequestClass;
__interface DELPHIINTERFACE JCacheRequest;
typedef System::DelphiInterface<JCacheRequest> _di_JCacheRequest;
class DELPHICLASS TJCacheRequest;
__interface DELPHIINTERFACE JCacheResponseClass;
typedef System::DelphiInterface<JCacheResponseClass> _di_JCacheResponseClass;
__interface DELPHIINTERFACE JCacheResponse;
typedef System::DelphiInterface<JCacheResponse> _di_JCacheResponse;
class DELPHICLASS TJCacheResponse;
__interface DELPHIINTERFACE Jnet_ContentHandlerClass;
typedef System::DelphiInterface<Jnet_ContentHandlerClass> _di_Jnet_ContentHandlerClass;
__interface DELPHIINTERFACE Jnet_ContentHandler;
typedef System::DelphiInterface<Jnet_ContentHandler> _di_Jnet_ContentHandler;
class DELPHICLASS TJnet_ContentHandler;
__interface DELPHIINTERFACE JContentHandlerFactoryClass;
typedef System::DelphiInterface<JContentHandlerFactoryClass> _di_JContentHandlerFactoryClass;
__interface DELPHIINTERFACE JContentHandlerFactory;
typedef System::DelphiInterface<JContentHandlerFactory> _di_JContentHandlerFactory;
class DELPHICLASS TJContentHandlerFactory;
__interface DELPHIINTERFACE JDatagramPacketClass;
typedef System::DelphiInterface<JDatagramPacketClass> _di_JDatagramPacketClass;
__interface DELPHIINTERFACE JDatagramPacket;
typedef System::DelphiInterface<JDatagramPacket> _di_JDatagramPacket;
class DELPHICLASS TJDatagramPacket;
__interface DELPHIINTERFACE JDatagramSocketClass;
typedef System::DelphiInterface<JDatagramSocketClass> _di_JDatagramSocketClass;
__interface DELPHIINTERFACE JDatagramSocket;
typedef System::DelphiInterface<JDatagramSocket> _di_JDatagramSocket;
class DELPHICLASS TJDatagramSocket;
__interface DELPHIINTERFACE JDatagramSocketImplClass;
typedef System::DelphiInterface<JDatagramSocketImplClass> _di_JDatagramSocketImplClass;
__interface DELPHIINTERFACE JDatagramSocketImpl;
typedef System::DelphiInterface<JDatagramSocketImpl> _di_JDatagramSocketImpl;
class DELPHICLASS TJDatagramSocketImpl;
__interface DELPHIINTERFACE JDatagramSocketImplFactoryClass;
typedef System::DelphiInterface<JDatagramSocketImplFactoryClass> _di_JDatagramSocketImplFactoryClass;
__interface DELPHIINTERFACE JDatagramSocketImplFactory;
typedef System::DelphiInterface<JDatagramSocketImplFactory> _di_JDatagramSocketImplFactory;
class DELPHICLASS TJDatagramSocketImplFactory;
__interface DELPHIINTERFACE JFileNameMapClass;
typedef System::DelphiInterface<JFileNameMapClass> _di_JFileNameMapClass;
__interface DELPHIINTERFACE JFileNameMap;
typedef System::DelphiInterface<JFileNameMap> _di_JFileNameMap;
class DELPHICLASS TJFileNameMap;
__interface DELPHIINTERFACE JURLConnectionClass;
typedef System::DelphiInterface<JURLConnectionClass> _di_JURLConnectionClass;
__interface DELPHIINTERFACE JURLConnection;
typedef System::DelphiInterface<JURLConnection> _di_JURLConnection;
class DELPHICLASS TJURLConnection;
__interface DELPHIINTERFACE JHttpURLConnectionClass;
typedef System::DelphiInterface<JHttpURLConnectionClass> _di_JHttpURLConnectionClass;
__interface DELPHIINTERFACE JHttpURLConnection;
typedef System::DelphiInterface<JHttpURLConnection> _di_JHttpURLConnection;
class DELPHICLASS TJHttpURLConnection;
__interface DELPHIINTERFACE JInetAddressClass;
typedef System::DelphiInterface<JInetAddressClass> _di_JInetAddressClass;
__interface DELPHIINTERFACE JInetAddress;
typedef System::DelphiInterface<JInetAddress> _di_JInetAddress;
class DELPHICLASS TJInetAddress;
__interface DELPHIINTERFACE JInet4AddressClass;
typedef System::DelphiInterface<JInet4AddressClass> _di_JInet4AddressClass;
__interface DELPHIINTERFACE JInet4Address;
typedef System::DelphiInterface<JInet4Address> _di_JInet4Address;
class DELPHICLASS TJInet4Address;
__interface DELPHIINTERFACE JInet6AddressClass;
typedef System::DelphiInterface<JInet6AddressClass> _di_JInet6AddressClass;
__interface DELPHIINTERFACE JInet6Address;
typedef System::DelphiInterface<JInet6Address> _di_JInet6Address;
class DELPHICLASS TJInet6Address;
__interface DELPHIINTERFACE JSocketAddressClass;
typedef System::DelphiInterface<JSocketAddressClass> _di_JSocketAddressClass;
__interface DELPHIINTERFACE JSocketAddress;
typedef System::DelphiInterface<JSocketAddress> _di_JSocketAddress;
class DELPHICLASS TJSocketAddress;
__interface DELPHIINTERFACE JInetSocketAddressClass;
typedef System::DelphiInterface<JInetSocketAddressClass> _di_JInetSocketAddressClass;
__interface DELPHIINTERFACE JInetSocketAddress;
typedef System::DelphiInterface<JInetSocketAddress> _di_JInetSocketAddress;
class DELPHICLASS TJInetSocketAddress;
__interface DELPHIINTERFACE JNetworkInterfaceClass;
typedef System::DelphiInterface<JNetworkInterfaceClass> _di_JNetworkInterfaceClass;
__interface DELPHIINTERFACE JNetworkInterface;
typedef System::DelphiInterface<JNetworkInterface> _di_JNetworkInterface;
class DELPHICLASS TJNetworkInterface;
__interface DELPHIINTERFACE JProtocolFamilyClass;
typedef System::DelphiInterface<JProtocolFamilyClass> _di_JProtocolFamilyClass;
__interface DELPHIINTERFACE JProtocolFamily;
typedef System::DelphiInterface<JProtocolFamily> _di_JProtocolFamily;
class DELPHICLASS TJProtocolFamily;
__interface DELPHIINTERFACE JProxyClass;
typedef System::DelphiInterface<JProxyClass> _di_JProxyClass;
__interface DELPHIINTERFACE JProxy;
typedef System::DelphiInterface<JProxy> _di_JProxy;
class DELPHICLASS TJProxy;
__interface DELPHIINTERFACE JProxy_TypeClass;
typedef System::DelphiInterface<JProxy_TypeClass> _di_JProxy_TypeClass;
__interface DELPHIINTERFACE JProxy_Type;
typedef System::DelphiInterface<JProxy_Type> _di_JProxy_Type;
class DELPHICLASS TJProxy_Type;
__interface DELPHIINTERFACE JResponseCacheClass;
typedef System::DelphiInterface<JResponseCacheClass> _di_JResponseCacheClass;
__interface DELPHIINTERFACE JResponseCache;
typedef System::DelphiInterface<JResponseCache> _di_JResponseCache;
class DELPHICLASS TJResponseCache;
__interface DELPHIINTERFACE JServerSocketClass;
typedef System::DelphiInterface<JServerSocketClass> _di_JServerSocketClass;
__interface DELPHIINTERFACE JServerSocket;
typedef System::DelphiInterface<JServerSocket> _di_JServerSocket;
class DELPHICLASS TJServerSocket;
__interface DELPHIINTERFACE JSocketClass;
typedef System::DelphiInterface<JSocketClass> _di_JSocketClass;
__interface DELPHIINTERFACE JSocket;
typedef System::DelphiInterface<JSocket> _di_JSocket;
class DELPHICLASS TJSocket;
__interface DELPHIINTERFACE JSocketImplClass;
typedef System::DelphiInterface<JSocketImplClass> _di_JSocketImplClass;
__interface DELPHIINTERFACE JSocketImpl;
typedef System::DelphiInterface<JSocketImpl> _di_JSocketImpl;
class DELPHICLASS TJSocketImpl;
__interface DELPHIINTERFACE JSocketImplFactoryClass;
typedef System::DelphiInterface<JSocketImplFactoryClass> _di_JSocketImplFactoryClass;
__interface DELPHIINTERFACE JSocketImplFactory;
typedef System::DelphiInterface<JSocketImplFactory> _di_JSocketImplFactory;
class DELPHICLASS TJSocketImplFactory;
__interface DELPHIINTERFACE JSocketOptionClass;
typedef System::DelphiInterface<JSocketOptionClass> _di_JSocketOptionClass;
__interface DELPHIINTERFACE JSocketOption;
typedef System::DelphiInterface<JSocketOption> _di_JSocketOption;
class DELPHICLASS TJSocketOption;
__interface DELPHIINTERFACE JURIClass;
typedef System::DelphiInterface<JURIClass> _di_JURIClass;
__interface DELPHIINTERFACE JURI;
typedef System::DelphiInterface<JURI> _di_JURI;
class DELPHICLASS TJURI;
__interface DELPHIINTERFACE JURLClass;
typedef System::DelphiInterface<JURLClass> _di_JURLClass;
__interface DELPHIINTERFACE JURL;
typedef System::DelphiInterface<JURL> _di_JURL;
class DELPHICLASS TJURL;
__interface DELPHIINTERFACE JURLStreamHandlerClass;
typedef System::DelphiInterface<JURLStreamHandlerClass> _di_JURLStreamHandlerClass;
__interface DELPHIINTERFACE JURLStreamHandler;
typedef System::DelphiInterface<JURLStreamHandler> _di_JURLStreamHandler;
class DELPHICLASS TJURLStreamHandler;
__interface DELPHIINTERFACE JURLStreamHandlerFactoryClass;
typedef System::DelphiInterface<JURLStreamHandlerFactoryClass> _di_JURLStreamHandlerFactoryClass;
__interface DELPHIINTERFACE JURLStreamHandlerFactory;
typedef System::DelphiInterface<JURLStreamHandlerFactory> _di_JURLStreamHandlerFactory;
class DELPHICLASS TJURLStreamHandlerFactory;
__interface DELPHIINTERFACE JServerSocketFactoryClass;
typedef System::DelphiInterface<JServerSocketFactoryClass> _di_JServerSocketFactoryClass;
__interface DELPHIINTERFACE JServerSocketFactory;
typedef System::DelphiInterface<JServerSocketFactory> _di_JServerSocketFactory;
class DELPHICLASS TJServerSocketFactory;
__interface DELPHIINTERFACE Jnet_SocketFactoryClass;
typedef System::DelphiInterface<Jnet_SocketFactoryClass> _di_Jnet_SocketFactoryClass;
__interface DELPHIINTERFACE Jnet_SocketFactory;
typedef System::DelphiInterface<Jnet_SocketFactory> _di_Jnet_SocketFactory;
class DELPHICLASS TJnet_SocketFactory;
__interface DELPHIINTERFACE JHostnameVerifierClass;
typedef System::DelphiInterface<JHostnameVerifierClass> _di_JHostnameVerifierClass;
__interface DELPHIINTERFACE JHostnameVerifier;
typedef System::DelphiInterface<JHostnameVerifier> _di_JHostnameVerifier;
class DELPHICLASS TJHostnameVerifier;
__interface DELPHIINTERFACE JHttpsURLConnectionClass;
typedef System::DelphiInterface<JHttpsURLConnectionClass> _di_JHttpsURLConnectionClass;
__interface DELPHIINTERFACE JHttpsURLConnection;
typedef System::DelphiInterface<JHttpsURLConnection> _di_JHttpsURLConnection;
class DELPHICLASS TJHttpsURLConnection;
__interface DELPHIINTERFACE JKeyManagerClass;
typedef System::DelphiInterface<JKeyManagerClass> _di_JKeyManagerClass;
__interface DELPHIINTERFACE JKeyManager;
typedef System::DelphiInterface<JKeyManager> _di_JKeyManager;
class DELPHICLASS TJKeyManager;
__interface DELPHIINTERFACE JKeyManagerFactoryClass;
typedef System::DelphiInterface<JKeyManagerFactoryClass> _di_JKeyManagerFactoryClass;
__interface DELPHIINTERFACE JKeyManagerFactory;
typedef System::DelphiInterface<JKeyManagerFactory> _di_JKeyManagerFactory;
class DELPHICLASS TJKeyManagerFactory;
__interface DELPHIINTERFACE JManagerFactoryParametersClass;
typedef System::DelphiInterface<JManagerFactoryParametersClass> _di_JManagerFactoryParametersClass;
__interface DELPHIINTERFACE JManagerFactoryParameters;
typedef System::DelphiInterface<JManagerFactoryParameters> _di_JManagerFactoryParameters;
class DELPHICLASS TJManagerFactoryParameters;
__interface DELPHIINTERFACE JSSLContextClass;
typedef System::DelphiInterface<JSSLContextClass> _di_JSSLContextClass;
__interface DELPHIINTERFACE JSSLContext;
typedef System::DelphiInterface<JSSLContext> _di_JSSLContext;
class DELPHICLASS TJSSLContext;
__interface DELPHIINTERFACE JSSLEngineClass;
typedef System::DelphiInterface<JSSLEngineClass> _di_JSSLEngineClass;
__interface DELPHIINTERFACE JSSLEngine;
typedef System::DelphiInterface<JSSLEngine> _di_JSSLEngine;
class DELPHICLASS TJSSLEngine;
__interface DELPHIINTERFACE JSSLEngineResultClass;
typedef System::DelphiInterface<JSSLEngineResultClass> _di_JSSLEngineResultClass;
__interface DELPHIINTERFACE JSSLEngineResult;
typedef System::DelphiInterface<JSSLEngineResult> _di_JSSLEngineResult;
class DELPHICLASS TJSSLEngineResult;
__interface DELPHIINTERFACE JSSLEngineResult_HandshakeStatusClass;
typedef System::DelphiInterface<JSSLEngineResult_HandshakeStatusClass> _di_JSSLEngineResult_HandshakeStatusClass;
__interface DELPHIINTERFACE JSSLEngineResult_HandshakeStatus;
typedef System::DelphiInterface<JSSLEngineResult_HandshakeStatus> _di_JSSLEngineResult_HandshakeStatus;
class DELPHICLASS TJSSLEngineResult_HandshakeStatus;
__interface DELPHIINTERFACE JSSLEngineResult_StatusClass;
typedef System::DelphiInterface<JSSLEngineResult_StatusClass> _di_JSSLEngineResult_StatusClass;
__interface DELPHIINTERFACE JSSLEngineResult_Status;
typedef System::DelphiInterface<JSSLEngineResult_Status> _di_JSSLEngineResult_Status;
class DELPHICLASS TJSSLEngineResult_Status;
__interface DELPHIINTERFACE JSSLParametersClass;
typedef System::DelphiInterface<JSSLParametersClass> _di_JSSLParametersClass;
__interface DELPHIINTERFACE JSSLParameters;
typedef System::DelphiInterface<JSSLParameters> _di_JSSLParameters;
class DELPHICLASS TJSSLParameters;
__interface DELPHIINTERFACE JSSLServerSocketFactoryClass;
typedef System::DelphiInterface<JSSLServerSocketFactoryClass> _di_JSSLServerSocketFactoryClass;
__interface DELPHIINTERFACE JSSLServerSocketFactory;
typedef System::DelphiInterface<JSSLServerSocketFactory> _di_JSSLServerSocketFactory;
class DELPHICLASS TJSSLServerSocketFactory;
__interface DELPHIINTERFACE JSSLSessionClass;
typedef System::DelphiInterface<JSSLSessionClass> _di_JSSLSessionClass;
__interface DELPHIINTERFACE JSSLSession;
typedef System::DelphiInterface<JSSLSession> _di_JSSLSession;
class DELPHICLASS TJSSLSession;
__interface DELPHIINTERFACE JSSLSessionContextClass;
typedef System::DelphiInterface<JSSLSessionContextClass> _di_JSSLSessionContextClass;
__interface DELPHIINTERFACE JSSLSessionContext;
typedef System::DelphiInterface<JSSLSessionContext> _di_JSSLSessionContext;
class DELPHICLASS TJSSLSessionContext;
__interface DELPHIINTERFACE Jssl_SSLSocketFactoryClass;
typedef System::DelphiInterface<Jssl_SSLSocketFactoryClass> _di_Jssl_SSLSocketFactoryClass;
__interface DELPHIINTERFACE Jssl_SSLSocketFactory;
typedef System::DelphiInterface<Jssl_SSLSocketFactory> _di_Jssl_SSLSocketFactory;
class DELPHICLASS TJssl_SSLSocketFactory;
__interface DELPHIINTERFACE JTrustManagerClass;
typedef System::DelphiInterface<JTrustManagerClass> _di_JTrustManagerClass;
__interface DELPHIINTERFACE JTrustManager;
typedef System::DelphiInterface<JTrustManager> _di_JTrustManager;
class DELPHICLASS TJTrustManager;
__interface DELPHIINTERFACE JTrustManagerFactoryClass;
typedef System::DelphiInterface<JTrustManagerFactoryClass> _di_JTrustManagerFactoryClass;
__interface DELPHIINTERFACE JTrustManagerFactory;
typedef System::DelphiInterface<JTrustManagerFactory> _di_JTrustManagerFactory;
class DELPHICLASS TJTrustManagerFactory;
__interface DELPHIINTERFACE JX509KeyManagerClass;
typedef System::DelphiInterface<JX509KeyManagerClass> _di_JX509KeyManagerClass;
__interface DELPHIINTERFACE JX509KeyManager;
typedef System::DelphiInterface<JX509KeyManager> _di_JX509KeyManager;
class DELPHICLASS TJX509KeyManager;
__interface DELPHIINTERFACE JX509TrustManagerClass;
typedef System::DelphiInterface<JX509TrustManagerClass> _di_JX509TrustManagerClass;
__interface DELPHIINTERFACE JX509TrustManager;
typedef System::DelphiInterface<JX509TrustManager> _di_JX509TrustManager;
class DELPHICLASS TJX509TrustManager;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{D36EC641-6B9D-46D0-B123-5EA7BE16D112}") JCacheRequestClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCacheRequest __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{CF398AA9-E113-42FB-9F46-F383FAAADB4B}") JCacheRequest  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl abort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JOutputStream __cdecl getBody() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCacheRequest : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCacheRequestClass,_di_JCacheRequest>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCacheRequestClass,_di_JCacheRequest> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCacheRequest() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCacheRequestClass,_di_JCacheRequest>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCacheRequest() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E685129F-73FD-4DEE-AB8A-B7835E8F8328}") JCacheResponseClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JCacheResponse __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{92BF69EB-CECF-4AFC-9389-4CAE451B41ED}") JCacheResponse  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getBody() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getHeaders() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJCacheResponse : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCacheResponseClass,_di_JCacheResponse>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCacheResponseClass,_di_JCacheResponse> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJCacheResponse() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JCacheResponseClass,_di_JCacheResponse>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJCacheResponse() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BC2D6F56-52C9-43EC-94BA-CE531E710CDD}") Jnet_ContentHandlerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_Jnet_ContentHandler __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{2DB56D97-EA55-4AF4-8891-3FA76F459DAF}") Jnet_ContentHandler  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getContent(_di_JURLConnection urlc) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getContent(_di_JURLConnection urlc, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_Jlang_Class>* classes) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJnet_ContentHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jnet_ContentHandlerClass,_di_Jnet_ContentHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jnet_ContentHandlerClass,_di_Jnet_ContentHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJnet_ContentHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jnet_ContentHandlerClass,_di_Jnet_ContentHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJnet_ContentHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{84FB0402-3D19-4B41-961D-5E0960A4BF47}") JContentHandlerFactoryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{19888BC1-C4B8-4ED1-8596-611F57F04D4D}") JContentHandlerFactory  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_Jnet_ContentHandler __cdecl createContentHandler(Androidapi::Jni::Javatypes::_di_JString mimetype) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJContentHandlerFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContentHandlerFactoryClass,_di_JContentHandlerFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContentHandlerFactoryClass,_di_JContentHandlerFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJContentHandlerFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JContentHandlerFactoryClass,_di_JContentHandlerFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJContentHandlerFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4BCE7F27-040D-4DBA-8F3D-D4CECB6501EC}") JDatagramPacketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDatagramPacket __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int offset, int length) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramPacket __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int length) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramPacket __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int offset, int length, _di_JInetAddress address, int port) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramPacket __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int offset, int length, _di_JSocketAddress address) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramPacket __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int length, _di_JInetAddress address, int port) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramPacket __cdecl init(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int length, _di_JSocketAddress address) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{10CA443B-A668-47A8-BF8E-4C95A97ED561}") JDatagramPacket  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JInetAddress __cdecl getAddress() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getData() = 0 ;
	virtual int __cdecl getLength() = 0 ;
	virtual int __cdecl getOffset() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	virtual _di_JSocketAddress __cdecl getSocketAddress() = 0 ;
	virtual void __cdecl setAddress(_di_JInetAddress iaddr) = 0 ;
	virtual void __cdecl setData(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf, int offset, int length) = 0 /* overload */;
	virtual void __cdecl setData(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* buf) = 0 /* overload */;
	virtual void __cdecl setLength(int length) = 0 ;
	virtual void __cdecl setPort(int iport) = 0 ;
	virtual void __cdecl setSocketAddress(_di_JSocketAddress address) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDatagramPacket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramPacketClass,_di_JDatagramPacket>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramPacketClass,_di_JDatagramPacket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDatagramPacket() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramPacketClass,_di_JDatagramPacket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDatagramPacket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0F66163B-C40D-48E1-A9C1-06CFEB60D382}") JDatagramSocketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDatagramSocket __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramSocket __cdecl init(_di_JSocketAddress bindaddr) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramSocket __cdecl init(int port) = 0 /* overload */;
	HIDESBASE virtual _di_JDatagramSocket __cdecl init(int port, _di_JInetAddress laddr) = 0 /* overload */;
	virtual void __cdecl setDatagramSocketImplFactory(_di_JDatagramSocketImplFactory fac) = 0 ;
};

__interface  INTERFACE_UUID("{A72F09A9-7901-41BE-AAF9-CE4D38CA39A0}") JDatagramSocket  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl bind(_di_JSocketAddress addr) = 0 ;
	virtual void __cdecl close() = 0 ;
	virtual void __cdecl connect(_di_JInetAddress address, int port) = 0 /* overload */;
	virtual void __cdecl connect(_di_JSocketAddress addr) = 0 /* overload */;
	virtual void __cdecl disconnect() = 0 ;
	virtual bool __cdecl getBroadcast() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JDatagramChannel __cdecl getChannel() = 0 ;
	virtual _di_JInetAddress __cdecl getInetAddress() = 0 ;
	virtual _di_JInetAddress __cdecl getLocalAddress() = 0 ;
	virtual int __cdecl getLocalPort() = 0 ;
	virtual _di_JSocketAddress __cdecl getLocalSocketAddress() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	virtual int __cdecl getReceiveBufferSize() = 0 ;
	virtual _di_JSocketAddress __cdecl getRemoteSocketAddress() = 0 ;
	virtual bool __cdecl getReuseAddress() = 0 ;
	virtual int __cdecl getSendBufferSize() = 0 ;
	virtual int __cdecl getSoTimeout() = 0 ;
	virtual int __cdecl getTrafficClass() = 0 ;
	virtual bool __cdecl isBound() = 0 ;
	virtual bool __cdecl isClosed() = 0 ;
	virtual bool __cdecl isConnected() = 0 ;
	virtual void __cdecl receive(_di_JDatagramPacket p) = 0 ;
	virtual void __cdecl send(_di_JDatagramPacket p) = 0 ;
	virtual void __cdecl setBroadcast(bool on) = 0 ;
	virtual void __cdecl setReceiveBufferSize(int size) = 0 ;
	virtual void __cdecl setReuseAddress(bool on) = 0 ;
	virtual void __cdecl setSendBufferSize(int size) = 0 ;
	virtual void __cdecl setSoTimeout(int timeout) = 0 ;
	virtual void __cdecl setTrafficClass(int tc) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDatagramSocket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketClass,_di_JDatagramSocket>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketClass,_di_JDatagramSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDatagramSocket() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketClass,_di_JDatagramSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDatagramSocket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A50B237A-F40E-46AB-B83F-79EB87DEB1AD}") JDatagramSocketImplClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JDatagramSocketImpl __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{FFE4E364-CF9B-443F-BE0B-44A6334B3325}") JDatagramSocketImpl  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDatagramSocketImpl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketImplClass,_di_JDatagramSocketImpl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketImplClass,_di_JDatagramSocketImpl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDatagramSocketImpl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketImplClass,_di_JDatagramSocketImpl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDatagramSocketImpl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4E896116-9C88-44E6-813E-084FD44707E7}") JDatagramSocketImplFactoryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{0936C4BF-2746-4093-8BDE-F260F9AC7278}") JDatagramSocketImplFactory  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JDatagramSocketImpl __cdecl createDatagramSocketImpl() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJDatagramSocketImplFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketImplFactoryClass,_di_JDatagramSocketImplFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketImplFactoryClass,_di_JDatagramSocketImplFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJDatagramSocketImplFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JDatagramSocketImplFactoryClass,_di_JDatagramSocketImplFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJDatagramSocketImplFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1A47F358-1E33-4E1B-B024-22A77BBFA3A4}") JFileNameMapClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{66E2FAD8-8B79-4E8F-BCE8-A88B68A4F094}") JFileNameMap  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getContentTypeFor(Androidapi::Jni::Javatypes::_di_JString fileName) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJFileNameMap : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFileNameMapClass,_di_JFileNameMap>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFileNameMapClass,_di_JFileNameMap> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJFileNameMap() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JFileNameMapClass,_di_JFileNameMap>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJFileNameMap() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{1E41F00D-AF0A-4B08-94F3-0D5B93B249AC}") JURLConnectionClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual bool __cdecl getDefaultAllowUserInteraction() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultRequestProperty(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual _di_JFileNameMap __cdecl getFileNameMap() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl guessContentTypeFromName(Androidapi::Jni::Javatypes::_di_JString fname) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl guessContentTypeFromStream(Androidapi::Jni::Javatypes::_di_JInputStream is_) = 0 ;
	virtual void __cdecl setContentHandlerFactory(_di_JContentHandlerFactory fac) = 0 ;
	virtual void __cdecl setDefaultAllowUserInteraction(bool defaultallowuserinteraction) = 0 ;
	virtual void __cdecl setDefaultRequestProperty(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setFileNameMap(_di_JFileNameMap map) = 0 ;
};

__interface  INTERFACE_UUID("{81A3990E-E273-4A22-9380-7FFFD145261A}") JURLConnection  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl addRequestProperty(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl connect() = 0 ;
	virtual bool __cdecl getAllowUserInteraction() = 0 ;
	virtual int __cdecl getConnectTimeout() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getContent() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getContent(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_Jlang_Class>* classes) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getContentEncoding() = 0 ;
	virtual int __cdecl getContentLength() = 0 ;
	virtual __int64 __cdecl getContentLengthLong() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getContentType() = 0 ;
	virtual __int64 __cdecl getDate() = 0 ;
	virtual bool __cdecl getDefaultUseCaches() = 0 ;
	virtual bool __cdecl getDoInput() = 0 ;
	virtual bool __cdecl getDoOutput() = 0 ;
	virtual __int64 __cdecl getExpiration() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHeaderField(Androidapi::Jni::Javatypes::_di_JString name) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHeaderField(int n) = 0 /* overload */;
	virtual __int64 __cdecl getHeaderFieldDate(Androidapi::Jni::Javatypes::_di_JString name, __int64 Default) = 0 ;
	virtual int __cdecl getHeaderFieldInt(Androidapi::Jni::Javatypes::_di_JString name, int Default) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHeaderFieldKey(int n) = 0 ;
	virtual __int64 __cdecl getHeaderFieldLong(Androidapi::Jni::Javatypes::_di_JString name, __int64 Default) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getHeaderFields() = 0 ;
	virtual __int64 __cdecl getIfModifiedSince() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getInputStream() = 0 ;
	virtual __int64 __cdecl getLastModified() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JOutputStream __cdecl getOutputStream() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPermission __cdecl getPermission() = 0 ;
	virtual int __cdecl getReadTimeout() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JMap __cdecl getRequestProperties() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRequestProperty(Androidapi::Jni::Javatypes::_di_JString key) = 0 ;
	virtual _di_JURL __cdecl getURL() = 0 ;
	virtual bool __cdecl getUseCaches() = 0 ;
	virtual void __cdecl setAllowUserInteraction(bool allowuserinteraction) = 0 ;
	virtual void __cdecl setConnectTimeout(int timeout) = 0 ;
	virtual void __cdecl setDefaultUseCaches(bool defaultusecaches) = 0 ;
	virtual void __cdecl setDoInput(bool doinput) = 0 ;
	virtual void __cdecl setDoOutput(bool dooutput) = 0 ;
	virtual void __cdecl setIfModifiedSince(__int64 ifmodifiedsince) = 0 ;
	virtual void __cdecl setReadTimeout(int timeout) = 0 ;
	virtual void __cdecl setRequestProperty(Androidapi::Jni::Javatypes::_di_JString key, Androidapi::Jni::Javatypes::_di_JString value) = 0 ;
	virtual void __cdecl setUseCaches(bool usecaches) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJURLConnection : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLConnectionClass,_di_JURLConnection>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLConnectionClass,_di_JURLConnection> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJURLConnection() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLConnectionClass,_di_JURLConnection>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJURLConnection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AFFFAD91-C0D9-4691-9F26-A8B154AF909A}") JHttpURLConnectionClass  : public JURLConnectionClass 
{
	virtual int __cdecl _GetHTTP_ACCEPTED() = 0 ;
	virtual int __cdecl _GetHTTP_BAD_GATEWAY() = 0 ;
	virtual int __cdecl _GetHTTP_BAD_METHOD() = 0 ;
	virtual int __cdecl _GetHTTP_BAD_REQUEST() = 0 ;
	virtual int __cdecl _GetHTTP_CLIENT_TIMEOUT() = 0 ;
	virtual int __cdecl _GetHTTP_CONFLICT() = 0 ;
	virtual int __cdecl _GetHTTP_CREATED() = 0 ;
	virtual int __cdecl _GetHTTP_ENTITY_TOO_LARGE() = 0 ;
	virtual int __cdecl _GetHTTP_FORBIDDEN() = 0 ;
	virtual int __cdecl _GetHTTP_GATEWAY_TIMEOUT() = 0 ;
	virtual int __cdecl _GetHTTP_GONE() = 0 ;
	virtual int __cdecl _GetHTTP_INTERNAL_ERROR() = 0 ;
	virtual int __cdecl _GetHTTP_LENGTH_REQUIRED() = 0 ;
	virtual int __cdecl _GetHTTP_MOVED_PERM() = 0 ;
	virtual int __cdecl _GetHTTP_MOVED_TEMP() = 0 ;
	virtual int __cdecl _GetHTTP_MULT_CHOICE() = 0 ;
	virtual int __cdecl _GetHTTP_NOT_ACCEPTABLE() = 0 ;
	virtual int __cdecl _GetHTTP_NOT_AUTHORITATIVE() = 0 ;
	virtual int __cdecl _GetHTTP_NOT_FOUND() = 0 ;
	virtual int __cdecl _GetHTTP_NOT_IMPLEMENTED() = 0 ;
	virtual int __cdecl _GetHTTP_NOT_MODIFIED() = 0 ;
	virtual int __cdecl _GetHTTP_NO_CONTENT() = 0 ;
	virtual int __cdecl _GetHTTP_OK() = 0 ;
	virtual int __cdecl _GetHTTP_PARTIAL() = 0 ;
	virtual int __cdecl _GetHTTP_PAYMENT_REQUIRED() = 0 ;
	virtual int __cdecl _GetHTTP_PRECON_FAILED() = 0 ;
	virtual int __cdecl _GetHTTP_PROXY_AUTH() = 0 ;
	virtual int __cdecl _GetHTTP_REQ_TOO_LONG() = 0 ;
	virtual int __cdecl _GetHTTP_RESET() = 0 ;
	virtual int __cdecl _GetHTTP_SEE_OTHER() = 0 ;
	virtual int __cdecl _GetHTTP_SERVER_ERROR() = 0 ;
	virtual int __cdecl _GetHTTP_UNAUTHORIZED() = 0 ;
	virtual int __cdecl _GetHTTP_UNAVAILABLE() = 0 ;
	virtual int __cdecl _GetHTTP_UNSUPPORTED_TYPE() = 0 ;
	virtual int __cdecl _GetHTTP_USE_PROXY() = 0 ;
	virtual int __cdecl _GetHTTP_VERSION() = 0 ;
	virtual bool __cdecl getFollowRedirects() = 0 ;
	virtual void __cdecl setFollowRedirects(bool set_) = 0 ;
	__property int HTTP_ACCEPTED = {read=_GetHTTP_ACCEPTED};
	__property int HTTP_BAD_GATEWAY = {read=_GetHTTP_BAD_GATEWAY};
	__property int HTTP_BAD_METHOD = {read=_GetHTTP_BAD_METHOD};
	__property int HTTP_BAD_REQUEST = {read=_GetHTTP_BAD_REQUEST};
	__property int HTTP_CLIENT_TIMEOUT = {read=_GetHTTP_CLIENT_TIMEOUT};
	__property int HTTP_CONFLICT = {read=_GetHTTP_CONFLICT};
	__property int HTTP_CREATED = {read=_GetHTTP_CREATED};
	__property int HTTP_ENTITY_TOO_LARGE = {read=_GetHTTP_ENTITY_TOO_LARGE};
	__property int HTTP_FORBIDDEN = {read=_GetHTTP_FORBIDDEN};
	__property int HTTP_GATEWAY_TIMEOUT = {read=_GetHTTP_GATEWAY_TIMEOUT};
	__property int HTTP_GONE = {read=_GetHTTP_GONE};
	__property int HTTP_INTERNAL_ERROR = {read=_GetHTTP_INTERNAL_ERROR};
	__property int HTTP_LENGTH_REQUIRED = {read=_GetHTTP_LENGTH_REQUIRED};
	__property int HTTP_MOVED_PERM = {read=_GetHTTP_MOVED_PERM};
	__property int HTTP_MOVED_TEMP = {read=_GetHTTP_MOVED_TEMP};
	__property int HTTP_MULT_CHOICE = {read=_GetHTTP_MULT_CHOICE};
	__property int HTTP_NOT_ACCEPTABLE = {read=_GetHTTP_NOT_ACCEPTABLE};
	__property int HTTP_NOT_AUTHORITATIVE = {read=_GetHTTP_NOT_AUTHORITATIVE};
	__property int HTTP_NOT_FOUND = {read=_GetHTTP_NOT_FOUND};
	__property int HTTP_NOT_IMPLEMENTED = {read=_GetHTTP_NOT_IMPLEMENTED};
	__property int HTTP_NOT_MODIFIED = {read=_GetHTTP_NOT_MODIFIED};
	__property int HTTP_NO_CONTENT = {read=_GetHTTP_NO_CONTENT};
	__property int HTTP_OK = {read=_GetHTTP_OK};
	__property int HTTP_PARTIAL = {read=_GetHTTP_PARTIAL};
	__property int HTTP_PAYMENT_REQUIRED = {read=_GetHTTP_PAYMENT_REQUIRED};
	__property int HTTP_PRECON_FAILED = {read=_GetHTTP_PRECON_FAILED};
	__property int HTTP_PROXY_AUTH = {read=_GetHTTP_PROXY_AUTH};
	__property int HTTP_REQ_TOO_LONG = {read=_GetHTTP_REQ_TOO_LONG};
	__property int HTTP_RESET = {read=_GetHTTP_RESET};
	__property int HTTP_SEE_OTHER = {read=_GetHTTP_SEE_OTHER};
	__property int HTTP_SERVER_ERROR = {read=_GetHTTP_SERVER_ERROR};
	__property int HTTP_UNAUTHORIZED = {read=_GetHTTP_UNAUTHORIZED};
	__property int HTTP_UNAVAILABLE = {read=_GetHTTP_UNAVAILABLE};
	__property int HTTP_UNSUPPORTED_TYPE = {read=_GetHTTP_UNSUPPORTED_TYPE};
	__property int HTTP_USE_PROXY = {read=_GetHTTP_USE_PROXY};
	__property int HTTP_VERSION = {read=_GetHTTP_VERSION};
};

__interface  INTERFACE_UUID("{B83F875D-71D7-4629-B008-9289FC607C98}") JHttpURLConnection  : public JURLConnection 
{
	virtual void __cdecl disconnect() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getErrorStream() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHeaderField(int n) = 0 ;
	HIDESBASE virtual __int64 __cdecl getHeaderFieldDate(Androidapi::Jni::Javatypes::_di_JString name, __int64 Default) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHeaderFieldKey(int n) = 0 ;
	virtual bool __cdecl getInstanceFollowRedirects() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Java::Security::_di_JPermission __cdecl getPermission() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRequestMethod() = 0 ;
	virtual int __cdecl getResponseCode() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getResponseMessage() = 0 ;
	virtual void __cdecl setChunkedStreamingMode(int chunklen) = 0 ;
	virtual void __cdecl setFixedLengthStreamingMode(int contentLength) = 0 /* overload */;
	virtual void __cdecl setFixedLengthStreamingMode(__int64 contentLength) = 0 /* overload */;
	virtual void __cdecl setInstanceFollowRedirects(bool followRedirects) = 0 ;
	virtual void __cdecl setRequestMethod(Androidapi::Jni::Javatypes::_di_JString method) = 0 ;
	virtual bool __cdecl usingProxy() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHttpURLConnection : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpURLConnectionClass,_di_JHttpURLConnection>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpURLConnectionClass,_di_JHttpURLConnection> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHttpURLConnection() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpURLConnectionClass,_di_JHttpURLConnection>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHttpURLConnection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{492EE337-5445-46CE-94D6-942FAEFF4CFA}") JInetAddressClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JInetAddress>* __cdecl getAllByName(Androidapi::Jni::Javatypes::_di_JString host) = 0 ;
	virtual _di_JInetAddress __cdecl getByAddress(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* addr) = 0 /* overload */;
	virtual _di_JInetAddress __cdecl getByAddress(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* addr) = 0 /* overload */;
	virtual _di_JInetAddress __cdecl getByName(Androidapi::Jni::Javatypes::_di_JString host) = 0 ;
	virtual _di_JInetAddress __cdecl getLocalHost() = 0 ;
	virtual _di_JInetAddress __cdecl getLoopbackAddress() = 0 ;
};

__interface  INTERFACE_UUID("{B6B43DAF-D7CE-4794-AC69-E787DADC9035}") JInetAddress  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCanonicalHostName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHostAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHostName() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isAnyLocalAddress() = 0 ;
	virtual bool __cdecl isLinkLocalAddress() = 0 ;
	virtual bool __cdecl isLoopbackAddress() = 0 ;
	virtual bool __cdecl isMCGlobal() = 0 ;
	virtual bool __cdecl isMCLinkLocal() = 0 ;
	virtual bool __cdecl isMCNodeLocal() = 0 ;
	virtual bool __cdecl isMCOrgLocal() = 0 ;
	virtual bool __cdecl isMCSiteLocal() = 0 ;
	virtual bool __cdecl isMulticastAddress() = 0 ;
	virtual bool __cdecl isReachable(int timeout) = 0 /* overload */;
	virtual bool __cdecl isReachable(_di_JNetworkInterface netif, int ttl, int timeout) = 0 /* overload */;
	virtual bool __cdecl isSiteLocalAddress() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInetAddress : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInetAddressClass,_di_JInetAddress>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInetAddressClass,_di_JInetAddress> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInetAddress() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInetAddressClass,_di_JInetAddress>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInetAddress() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{60903748-BDC9-4C60-8683-4B5D22432958}") JInet4AddressClass  : public JInetAddressClass 
{
	
};

__interface  INTERFACE_UUID("{0C7F53CB-4917-4653-829B-B70619BCF0D5}") JInet4Address  : public JInetAddress 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	HIDESBASE virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getAddress() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHostAddress() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual bool __cdecl isAnyLocalAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isLinkLocalAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isLoopbackAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isMCGlobal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCLinkLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCNodeLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCOrgLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCSiteLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMulticastAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isSiteLocalAddress() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInet4Address : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInet4AddressClass,_di_JInet4Address>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInet4AddressClass,_di_JInet4Address> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInet4Address() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInet4AddressClass,_di_JInet4Address>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInet4Address() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D49DB1D9-4A6E-4A91-B376-5DAA96802A0F}") JInet6AddressClass  : public JInetAddressClass 
{
	HIDESBASE virtual _di_JInet6Address __cdecl getByAddress(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* addr, _di_JNetworkInterface nif) = 0 /* overload */;
	HIDESBASE virtual _di_JInet6Address __cdecl getByAddress(Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jnibridge::TJavaArray__1<System::Byte>* addr, int scope_id) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{42E7D54F-1482-4691-8919-6280C467B0DF}") JInet6Address  : public JInetAddress 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	HIDESBASE virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getAddress() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHostAddress() = 0 ;
	virtual int __cdecl getScopeId() = 0 ;
	virtual _di_JNetworkInterface __cdecl getScopedInterface() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual bool __cdecl isAnyLocalAddress() = 0 ;
	virtual bool __cdecl isIPv4CompatibleAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isLinkLocalAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isLoopbackAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isMCGlobal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCLinkLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCNodeLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCOrgLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMCSiteLocal() = 0 ;
	HIDESBASE virtual bool __cdecl isMulticastAddress() = 0 ;
	HIDESBASE virtual bool __cdecl isSiteLocalAddress() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInet6Address : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInet6AddressClass,_di_JInet6Address>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInet6AddressClass,_di_JInet6Address> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInet6Address() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInet6AddressClass,_di_JInet6Address>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInet6Address() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{60D20DB8-E40A-4A52-9EFD-00CA47BB770C}") JSocketAddressClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSocketAddress __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{942580A2-69D7-4E40-8DE0-87D70A5961E0}") JSocketAddress  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSocketAddress : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketAddressClass,_di_JSocketAddress>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketAddressClass,_di_JSocketAddress> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSocketAddress() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketAddressClass,_di_JSocketAddress>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSocketAddress() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{12E81771-62EC-45BD-B615-621F654E27E3}") JInetSocketAddressClass  : public JSocketAddressClass 
{
	HIDESBASE virtual _di_JInetSocketAddress __cdecl init(int port) = 0 /* overload */;
	HIDESBASE virtual _di_JInetSocketAddress __cdecl init(_di_JInetAddress addr, int port) = 0 /* overload */;
	HIDESBASE virtual _di_JInetSocketAddress __cdecl init(Androidapi::Jni::Javatypes::_di_JString hostname, int port) = 0 /* overload */;
	virtual _di_JInetSocketAddress __cdecl createUnresolved(Androidapi::Jni::Javatypes::_di_JString host, int port) = 0 ;
};

__interface  INTERFACE_UUID("{14EAE4FF-039F-4FC8-8734-667C436EA016}") JInetSocketAddress  : public JSocketAddress 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual _di_JInetAddress __cdecl getAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHostName() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHostString() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isUnresolved() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJInetSocketAddress : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInetSocketAddressClass,_di_JInetSocketAddress>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInetSocketAddressClass,_di_JInetSocketAddress> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJInetSocketAddress() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JInetSocketAddressClass,_di_JInetSocketAddress>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJInetSocketAddress() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BB9045C7-8663-41A9-83E4-12C122370595}") JNetworkInterfaceClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JNetworkInterface __cdecl getByIndex(int index) = 0 ;
	virtual _di_JNetworkInterface __cdecl getByInetAddress(_di_JInetAddress addr) = 0 ;
	virtual _di_JNetworkInterface __cdecl getByName(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JEnumeration __cdecl getNetworkInterfaces() = 0 ;
};

__interface  INTERFACE_UUID("{15C9BDCC-62F9-405C-B889-F50A5F9B6ABF}") JNetworkInterface  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDisplayName() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getHardwareAddress() = 0 ;
	virtual int __cdecl getIndex() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JEnumeration __cdecl getInetAddresses() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getInterfaceAddresses() = 0 ;
	virtual int __cdecl getMTU() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getName() = 0 ;
	virtual _di_JNetworkInterface __cdecl getParent() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JEnumeration __cdecl getSubInterfaces() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isLoopback() = 0 ;
	virtual bool __cdecl isPointToPoint() = 0 ;
	virtual bool __cdecl isUp() = 0 ;
	virtual bool __cdecl isVirtual() = 0 ;
	virtual bool __cdecl supportsMulticast() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJNetworkInterface : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNetworkInterfaceClass,_di_JNetworkInterface>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNetworkInterfaceClass,_di_JNetworkInterface> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJNetworkInterface() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JNetworkInterfaceClass,_di_JNetworkInterface>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJNetworkInterface() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{61151ABC-4E86-426D-AD5A-7DFC5A53E4F1}") JProtocolFamilyClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{72D117D9-5582-4BE3-9037-2C5E6ED99D16}") JProtocolFamily  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl name() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJProtocolFamily : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProtocolFamilyClass,_di_JProtocolFamily>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProtocolFamilyClass,_di_JProtocolFamily> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJProtocolFamily() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProtocolFamilyClass,_di_JProtocolFamily>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJProtocolFamily() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{048E50A7-1BAE-4279-A463-E3902204EC7A}") JProxyClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JProxy __cdecl _GetNO_PROXY() = 0 ;
	HIDESBASE virtual _di_JProxy __cdecl init(_di_JProxy_Type type_, _di_JSocketAddress sa) = 0 ;
	__property _di_JProxy NO_PROXY = {read=_GetNO_PROXY};
};

__interface  INTERFACE_UUID("{E39BB6C6-22C5-46E8-8069-7190553008E9}") JProxy  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JSocketAddress __cdecl address() = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual _di_JProxy_Type __cdecl type() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJProxy : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxyClass,_di_JProxy>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxyClass,_di_JProxy> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJProxy() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxyClass,_di_JProxy>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJProxy() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0ED40B46-7D55-478F-89C7-09417890A5AF}") JProxy_TypeClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JProxy_Type __cdecl _GetDIRECT() = 0 ;
	virtual _di_JProxy_Type __cdecl _GetHTTP() = 0 ;
	virtual _di_JProxy_Type __cdecl _GetSOCKS() = 0 ;
	HIDESBASE virtual _di_JProxy_Type __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JProxy_Type>* __cdecl values() = 0 ;
	__property _di_JProxy_Type DIRECT = {read=_GetDIRECT};
	__property _di_JProxy_Type HTTP = {read=_GetHTTP};
	__property _di_JProxy_Type SOCKS = {read=_GetSOCKS};
};

__interface  INTERFACE_UUID("{BCD6DC15-85B1-44DA-8772-10FC2727FD38}") JProxy_Type  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJProxy_Type : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxy_TypeClass,_di_JProxy_Type>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxy_TypeClass,_di_JProxy_Type> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJProxy_Type() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JProxy_TypeClass,_di_JProxy_Type>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJProxy_Type() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D813947F-B9AE-41F0-B400-46BA236FD5C8}") JResponseCacheClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JResponseCache __cdecl init() = 0 ;
	virtual _di_JResponseCache __cdecl getDefault() = 0 ;
	virtual void __cdecl setDefault(_di_JResponseCache responseCache) = 0 ;
};

__interface  INTERFACE_UUID("{07B7E607-A0CF-47A2-95EE-A8A0E0735C7F}") JResponseCache  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JCacheResponse __cdecl get(_di_JURI uri, Androidapi::Jni::Javatypes::_di_JString rqstMethod, Androidapi::Jni::Javatypes::_di_JMap rqstHeaders) = 0 ;
	virtual _di_JCacheRequest __cdecl put(_di_JURI uri, _di_JURLConnection conn) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJResponseCache : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResponseCacheClass,_di_JResponseCache>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResponseCacheClass,_di_JResponseCache> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJResponseCache() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JResponseCacheClass,_di_JResponseCache>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJResponseCache() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F387AEB9-A572-4E58-B1A1-F23460842F07}") JServerSocketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JServerSocket __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JServerSocket __cdecl init(int port) = 0 /* overload */;
	HIDESBASE virtual _di_JServerSocket __cdecl init(int port, int backlog) = 0 /* overload */;
	HIDESBASE virtual _di_JServerSocket __cdecl init(int port, int backlog, _di_JInetAddress bindAddr) = 0 /* overload */;
	virtual void __cdecl setSocketFactory(_di_JSocketImplFactory fac) = 0 ;
};

__interface  INTERFACE_UUID("{2626AEBA-E1F8-4E6F-AE4E-747C2AC1005D}") JServerSocket  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JSocket __cdecl accept() = 0 ;
	virtual void __cdecl bind(_di_JSocketAddress endpoint) = 0 /* overload */;
	virtual void __cdecl bind(_di_JSocketAddress endpoint, int backlog) = 0 /* overload */;
	virtual void __cdecl close() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JServerSocketChannel __cdecl getChannel() = 0 ;
	virtual _di_JInetAddress __cdecl getInetAddress() = 0 ;
	virtual int __cdecl getLocalPort() = 0 ;
	virtual _di_JSocketAddress __cdecl getLocalSocketAddress() = 0 ;
	virtual int __cdecl getReceiveBufferSize() = 0 ;
	virtual bool __cdecl getReuseAddress() = 0 ;
	virtual int __cdecl getSoTimeout() = 0 ;
	virtual bool __cdecl isBound() = 0 ;
	virtual bool __cdecl isClosed() = 0 ;
	virtual void __cdecl setPerformancePreferences(int connectionTime, int latency, int bandwidth) = 0 ;
	virtual void __cdecl setReceiveBufferSize(int size) = 0 ;
	virtual void __cdecl setReuseAddress(bool on) = 0 ;
	virtual void __cdecl setSoTimeout(int timeout) = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServerSocket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerSocketClass,_di_JServerSocket>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerSocketClass,_di_JServerSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServerSocket() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerSocketClass,_di_JServerSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServerSocket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{DB5E8FED-7D12-4514-B19B-AF6DF5F6FC01}") JSocketClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSocket __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(_di_JProxy proxy) = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(Androidapi::Jni::Javatypes::_di_JString host, int port) = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(_di_JInetAddress address, int port) = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(Androidapi::Jni::Javatypes::_di_JString host, int port, _di_JInetAddress localAddr, int localPort) = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(_di_JInetAddress address, int port, _di_JInetAddress localAddr, int localPort) = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(Androidapi::Jni::Javatypes::_di_JString host, int port, bool stream) = 0 /* overload */;
	HIDESBASE virtual _di_JSocket __cdecl init(_di_JInetAddress host, int port, bool stream) = 0 /* overload */;
	virtual void __cdecl setSocketImplFactory(_di_JSocketImplFactory fac) = 0 ;
};

__interface  INTERFACE_UUID("{211F5BA9-1676-41BF-AA86-3FFDD53632F0}") JSocket  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl bind(_di_JSocketAddress bindpoint) = 0 ;
	virtual void __cdecl close() = 0 ;
	virtual void __cdecl connect(_di_JSocketAddress endpoint) = 0 /* overload */;
	virtual void __cdecl connect(_di_JSocketAddress endpoint, int timeout) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JSocketChannel __cdecl getChannel() = 0 ;
	virtual _di_JInetAddress __cdecl getInetAddress() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl getInputStream() = 0 ;
	virtual bool __cdecl getKeepAlive() = 0 ;
	virtual _di_JInetAddress __cdecl getLocalAddress() = 0 ;
	virtual int __cdecl getLocalPort() = 0 ;
	virtual _di_JSocketAddress __cdecl getLocalSocketAddress() = 0 ;
	virtual bool __cdecl getOOBInline() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JOutputStream __cdecl getOutputStream() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	virtual int __cdecl getReceiveBufferSize() = 0 ;
	virtual _di_JSocketAddress __cdecl getRemoteSocketAddress() = 0 ;
	virtual bool __cdecl getReuseAddress() = 0 ;
	virtual int __cdecl getSendBufferSize() = 0 ;
	virtual int __cdecl getSoLinger() = 0 ;
	virtual int __cdecl getSoTimeout() = 0 ;
	virtual bool __cdecl getTcpNoDelay() = 0 ;
	virtual int __cdecl getTrafficClass() = 0 ;
	virtual bool __cdecl isBound() = 0 ;
	virtual bool __cdecl isClosed() = 0 ;
	virtual bool __cdecl isConnected() = 0 ;
	virtual bool __cdecl isInputShutdown() = 0 ;
	virtual bool __cdecl isOutputShutdown() = 0 ;
	virtual void __cdecl sendUrgentData(int data) = 0 ;
	virtual void __cdecl setKeepAlive(bool on) = 0 ;
	virtual void __cdecl setOOBInline(bool on) = 0 ;
	virtual void __cdecl setPerformancePreferences(int connectionTime, int latency, int bandwidth) = 0 ;
	virtual void __cdecl setReceiveBufferSize(int size) = 0 ;
	virtual void __cdecl setReuseAddress(bool on) = 0 ;
	virtual void __cdecl setSendBufferSize(int size) = 0 ;
	virtual void __cdecl setSoLinger(bool on, int linger) = 0 ;
	virtual void __cdecl setSoTimeout(int timeout) = 0 ;
	virtual void __cdecl setTcpNoDelay(bool on) = 0 ;
	virtual void __cdecl setTrafficClass(int tc) = 0 ;
	virtual void __cdecl shutdownInput() = 0 ;
	virtual void __cdecl shutdownOutput() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSocket : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketClass,_di_JSocket>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketClass,_di_JSocket> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSocket() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketClass,_di_JSocket>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSocket() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{115EBD14-0CFA-4AF7-B9C9-764D7B87A468}") JSocketImplClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSocketImpl __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{B35C8A07-5814-4987-A2C2-E331D82D5A1B}") JSocketImpl  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSocketImpl : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketImplClass,_di_JSocketImpl>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketImplClass,_di_JSocketImpl> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSocketImpl() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketImplClass,_di_JSocketImpl>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSocketImpl() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{AABBCC1A-57AD-4EA8-ADE7-D9B6A7C2B866}") JSocketImplFactoryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{B4CAFC5B-CE9F-4934-8739-8EE50CD7F227}") JSocketImplFactory  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JSocketImpl __cdecl createSocketImpl() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSocketImplFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketImplFactoryClass,_di_JSocketImplFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketImplFactoryClass,_di_JSocketImplFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSocketImplFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketImplFactoryClass,_di_JSocketImplFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSocketImplFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D35E9729-9405-4625-ADDD-FEDA4FA0466C}") JSocketOptionClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{AF34E663-DA85-4DDA-902C-AD6EF5DAE75D}") JSocketOption  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl name() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_Jlang_Class __cdecl type() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSocketOption : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketOptionClass,_di_JSocketOption>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketOptionClass,_di_JSocketOption> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSocketOption() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSocketOptionClass,_di_JSocketOption>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSocketOption() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{248E7A13-8C00-4246-B62A-26973AF67439}") JURIClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JURI __cdecl init(Androidapi::Jni::Javatypes::_di_JString str) = 0 /* overload */;
	HIDESBASE virtual _di_JURI __cdecl init(Androidapi::Jni::Javatypes::_di_JString scheme, Androidapi::Jni::Javatypes::_di_JString userInfo, Androidapi::Jni::Javatypes::_di_JString host, int port, Androidapi::Jni::Javatypes::_di_JString path, Androidapi::Jni::Javatypes::_di_JString query, Androidapi::Jni::Javatypes::_di_JString fragment) = 0 /* overload */;
	HIDESBASE virtual _di_JURI __cdecl init(Androidapi::Jni::Javatypes::_di_JString scheme, Androidapi::Jni::Javatypes::_di_JString authority, Androidapi::Jni::Javatypes::_di_JString path, Androidapi::Jni::Javatypes::_di_JString query, Androidapi::Jni::Javatypes::_di_JString fragment) = 0 /* overload */;
	HIDESBASE virtual _di_JURI __cdecl init(Androidapi::Jni::Javatypes::_di_JString scheme, Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString path, Androidapi::Jni::Javatypes::_di_JString fragment) = 0 /* overload */;
	HIDESBASE virtual _di_JURI __cdecl init(Androidapi::Jni::Javatypes::_di_JString scheme, Androidapi::Jni::Javatypes::_di_JString ssp, Androidapi::Jni::Javatypes::_di_JString fragment) = 0 /* overload */;
	virtual _di_JURI __cdecl create(Androidapi::Jni::Javatypes::_di_JString str) = 0 ;
};

__interface  INTERFACE_UUID("{621C74EA-9C1E-4279-9DFF-253F28359DB1}") JURI  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl compareTo(_di_JURI that) = 0 ;
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject ob) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAuthority() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFragment() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHost() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPath() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getQuery() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRawAuthority() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRawFragment() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRawPath() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRawQuery() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRawSchemeSpecificPart() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRawUserInfo() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getScheme() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getSchemeSpecificPart() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUserInfo() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual bool __cdecl isAbsolute() = 0 ;
	virtual bool __cdecl isOpaque() = 0 ;
	virtual _di_JURI __cdecl normalize() = 0 ;
	virtual _di_JURI __cdecl parseServerAuthority() = 0 ;
	virtual _di_JURI __cdecl relativize(_di_JURI uri) = 0 ;
	virtual _di_JURI __cdecl resolve(_di_JURI uri) = 0 /* overload */;
	virtual _di_JURI __cdecl resolve(Androidapi::Jni::Javatypes::_di_JString str) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toASCIIString() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual _di_JURL __cdecl toURL() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJURI : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURIClass,_di_JURI>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURIClass,_di_JURI> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJURI() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURIClass,_di_JURI>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJURI() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BE22C128-8F58-4B04-A961-76BCD93FCBBD}") JURLClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JURL __cdecl init(Androidapi::Jni::Javatypes::_di_JString protocol, Androidapi::Jni::Javatypes::_di_JString host, int port, Androidapi::Jni::Javatypes::_di_JString file_) = 0 /* overload */;
	HIDESBASE virtual _di_JURL __cdecl init(Androidapi::Jni::Javatypes::_di_JString protocol, Androidapi::Jni::Javatypes::_di_JString host, Androidapi::Jni::Javatypes::_di_JString file_) = 0 /* overload */;
	HIDESBASE virtual _di_JURL __cdecl init(Androidapi::Jni::Javatypes::_di_JString protocol, Androidapi::Jni::Javatypes::_di_JString host, int port, Androidapi::Jni::Javatypes::_di_JString file_, _di_JURLStreamHandler handler) = 0 /* overload */;
	HIDESBASE virtual _di_JURL __cdecl init(Androidapi::Jni::Javatypes::_di_JString spec) = 0 /* overload */;
	HIDESBASE virtual _di_JURL __cdecl init(_di_JURL context, Androidapi::Jni::Javatypes::_di_JString spec) = 0 /* overload */;
	HIDESBASE virtual _di_JURL __cdecl init(_di_JURL context, Androidapi::Jni::Javatypes::_di_JString spec, _di_JURLStreamHandler handler) = 0 /* overload */;
	virtual void __cdecl setURLStreamHandlerFactory(_di_JURLStreamHandlerFactory fac) = 0 ;
};

__interface  INTERFACE_UUID("{BCC8860A-E48B-4894-95A9-26B3AFDF3EDC}") JURL  : public Androidapi::Jni::Javatypes::JObject 
{
	HIDESBASE virtual bool __cdecl equals(Androidapi::Jni::Javatypes::_di_JObject obj) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAuthority() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getContent() = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getContent(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_Jlang_Class>* classes) = 0 /* overload */;
	virtual int __cdecl getDefaultPort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getFile() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getHost() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPath() = 0 ;
	virtual int __cdecl getPort() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProtocol() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getQuery() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getRef() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getUserInfo() = 0 ;
	HIDESBASE virtual int __cdecl hashCode() = 0 ;
	virtual _di_JURLConnection __cdecl openConnection() = 0 /* overload */;
	virtual _di_JURLConnection __cdecl openConnection(_di_JProxy proxy) = 0 /* overload */;
	virtual Androidapi::Jni::Javatypes::_di_JInputStream __cdecl openStream() = 0 ;
	virtual bool __cdecl sameFile(_di_JURL other) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toExternalForm() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
	virtual _di_JURI __cdecl toURI() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJURL : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLClass,_di_JURL>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLClass,_di_JURL> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJURL() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLClass,_di_JURL>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJURL() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8304BD07-354D-40DA-9F39-B863F9F124A4}") JURLStreamHandlerClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JURLStreamHandler __cdecl init() = 0 ;
};

__interface  INTERFACE_UUID("{EA0348E3-8A6E-491D-86E9-C36120279679}") JURLStreamHandler  : public Androidapi::Jni::Javatypes::JObject 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJURLStreamHandler : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLStreamHandlerClass,_di_JURLStreamHandler>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLStreamHandlerClass,_di_JURLStreamHandler> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJURLStreamHandler() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLStreamHandlerClass,_di_JURLStreamHandler>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJURLStreamHandler() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{EFF1D603-CDE5-4858-948E-2871F2E373F3}") JURLStreamHandlerFactoryClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{8893C36E-5F82-4B08-8229-EE4A2A1E9BFC}") JURLStreamHandlerFactory  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual _di_JURLStreamHandler __cdecl createURLStreamHandler(Androidapi::Jni::Javatypes::_di_JString protocol) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJURLStreamHandlerFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLStreamHandlerFactoryClass,_di_JURLStreamHandlerFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLStreamHandlerFactoryClass,_di_JURLStreamHandlerFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJURLStreamHandlerFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JURLStreamHandlerFactoryClass,_di_JURLStreamHandlerFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJURLStreamHandlerFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7E3304CF-103B-4DD1-B1B3-5BF686D3838A}") JServerSocketFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JServerSocketFactory __cdecl getDefault() = 0 ;
};

__interface  INTERFACE_UUID("{AE28B65C-1BC3-4FF1-B4A0-D42276761437}") JServerSocketFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JServerSocket __cdecl createServerSocket() = 0 /* overload */;
	virtual _di_JServerSocket __cdecl createServerSocket(int port) = 0 /* overload */;
	virtual _di_JServerSocket __cdecl createServerSocket(int port, int backlog) = 0 /* overload */;
	virtual _di_JServerSocket __cdecl createServerSocket(int port, int backlog, _di_JInetAddress ifAddress) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJServerSocketFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerSocketFactoryClass,_di_JServerSocketFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerSocketFactoryClass,_di_JServerSocketFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJServerSocketFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JServerSocketFactoryClass,_di_JServerSocketFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJServerSocketFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{80B284D0-84F4-4C1A-8CC1-D98B0C1B0AFC}") Jnet_SocketFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_Jnet_SocketFactory __cdecl getDefault() = 0 ;
};

__interface  INTERFACE_UUID("{A0B638C3-8814-4356-B0EE-A398E4EAFDA9}") Jnet_SocketFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JSocket __cdecl createSocket() = 0 /* overload */;
	virtual _di_JSocket __cdecl createSocket(Androidapi::Jni::Javatypes::_di_JString host, int port) = 0 /* overload */;
	virtual _di_JSocket __cdecl createSocket(Androidapi::Jni::Javatypes::_di_JString host, int port, _di_JInetAddress localHost, int localPort) = 0 /* overload */;
	virtual _di_JSocket __cdecl createSocket(_di_JInetAddress host, int port) = 0 /* overload */;
	virtual _di_JSocket __cdecl createSocket(_di_JInetAddress address, int port, _di_JInetAddress localAddress, int localPort) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJnet_SocketFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jnet_SocketFactoryClass,_di_Jnet_SocketFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jnet_SocketFactoryClass,_di_Jnet_SocketFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJnet_SocketFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jnet_SocketFactoryClass,_di_Jnet_SocketFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJnet_SocketFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{4C9B1E29-39D4-4124-8BBC-7827D45EB16B}") JHostnameVerifierClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{550462A6-05E0-4E07-9D81-3F5A8613F787}") JHostnameVerifier  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual bool __cdecl verify(Androidapi::Jni::Javatypes::_di_JString hostname, _di_JSSLSession session) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHostnameVerifier : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHostnameVerifierClass,_di_JHostnameVerifier>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHostnameVerifierClass,_di_JHostnameVerifier> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHostnameVerifier() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHostnameVerifierClass,_di_JHostnameVerifier>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHostnameVerifier() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{A4110139-AC54-4852-A7EE-2C3DFF71DA76}") JHttpsURLConnectionClass  : public JHttpURLConnectionClass 
{
	virtual _di_JHostnameVerifier __cdecl getDefaultHostnameVerifier() = 0 ;
	virtual _di_Jssl_SSLSocketFactory __cdecl getDefaultSSLSocketFactory() = 0 ;
	virtual void __cdecl setDefaultHostnameVerifier(_di_JHostnameVerifier v) = 0 ;
	virtual void __cdecl setDefaultSSLSocketFactory(_di_Jssl_SSLSocketFactory sf) = 0 ;
};

__interface  INTERFACE_UUID("{69D72BE0-8A67-4107-88DB-57ACF8204FE8}") JHttpsURLConnection  : public JHttpURLConnection 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCipherSuite() = 0 ;
	virtual _di_JHostnameVerifier __cdecl getHostnameVerifier() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JCertificate>* __cdecl getLocalCertificates() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPrincipal __cdecl getLocalPrincipal() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPrincipal __cdecl getPeerPrincipal() = 0 ;
	virtual _di_Jssl_SSLSocketFactory __cdecl getSSLSocketFactory() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JCertificate>* __cdecl getServerCertificates() = 0 ;
	virtual void __cdecl setHostnameVerifier(_di_JHostnameVerifier v) = 0 ;
	virtual void __cdecl setSSLSocketFactory(_di_Jssl_SSLSocketFactory sf) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJHttpsURLConnection : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpsURLConnectionClass,_di_JHttpsURLConnection>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpsURLConnectionClass,_di_JHttpsURLConnection> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJHttpsURLConnection() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JHttpsURLConnectionClass,_di_JHttpsURLConnection>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJHttpsURLConnection() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{21F40812-C2DB-4D37-A88C-424FB51C75E0}") JKeyManagerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{5B24A8D6-C338-4D60-8836-61572B51D66D}") JKeyManager  : public Androidapi::Jnibridge::IJavaInstance 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyManagerClass,_di_JKeyManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyManagerClass,_di_JKeyManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyManagerClass,_di_JKeyManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{8E3CB328-DC3A-4C08-BD80-6B708E222A88}") JKeyManagerFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultAlgorithm() = 0 ;
	virtual _di_JKeyManagerFactory __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString algorithm) = 0 /* overload */;
	virtual _di_JKeyManagerFactory __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString algorithm, Androidapi::Jni::Javatypes::_di_JString provider) = 0 /* overload */;
	virtual _di_JKeyManagerFactory __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString algorithm, Androidapi::Jni::Java::Security::_di_JProvider provider) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{B9E8F2EF-F22B-4B4C-A66D-0F9999DF5111}") JKeyManagerFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAlgorithm() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JKeyManager>* __cdecl getKeyManagers() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JProvider __cdecl getProvider() = 0 ;
	virtual void __cdecl init(Androidapi::Jni::Java::Security::_di_JKeyStore ks, Androidapi::Jnibridge::TJavaArray__1<System::WideChar>* password) = 0 /* overload */;
	virtual void __cdecl init(_di_JManagerFactoryParameters spec) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJKeyManagerFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyManagerFactoryClass,_di_JKeyManagerFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyManagerFactoryClass,_di_JKeyManagerFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJKeyManagerFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JKeyManagerFactoryClass,_di_JKeyManagerFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJKeyManagerFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FF4318C7-BC46-4379-BD8D-D861CFFECAFC}") JManagerFactoryParametersClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{F2FDD21B-EEBE-4832-B2ED-6EFFEEB0B835}") JManagerFactoryParameters  : public Androidapi::Jnibridge::IJavaInstance 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJManagerFactoryParameters : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManagerFactoryParametersClass,_di_JManagerFactoryParameters>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManagerFactoryParametersClass,_di_JManagerFactoryParameters> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJManagerFactoryParameters() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JManagerFactoryParametersClass,_di_JManagerFactoryParameters>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJManagerFactoryParameters() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{ECA2D26C-92C5-4B93-939E-8A26B85CA07D}") JSSLContextClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual _di_JSSLContext __cdecl getDefault() = 0 ;
	virtual _di_JSSLContext __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString protocol) = 0 /* overload */;
	virtual _di_JSSLContext __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString protocol, Androidapi::Jni::Javatypes::_di_JString provider) = 0 /* overload */;
	virtual _di_JSSLContext __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString protocol, Androidapi::Jni::Java::Security::_di_JProvider provider) = 0 /* overload */;
	virtual void __cdecl setDefault(_di_JSSLContext context) = 0 ;
};

__interface  INTERFACE_UUID("{265755CC-73B3-4A0E-9211-049A7B57809E}") JSSLContext  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual _di_JSSLEngine __cdecl createSSLEngine() = 0 /* overload */;
	virtual _di_JSSLEngine __cdecl createSSLEngine(Androidapi::Jni::Javatypes::_di_JString peerHost, int peerPort) = 0 /* overload */;
	virtual _di_JSSLSessionContext __cdecl getClientSessionContext() = 0 ;
	virtual _di_JSSLParameters __cdecl getDefaultSSLParameters() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProtocol() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JProvider __cdecl getProvider() = 0 ;
	virtual _di_JSSLSessionContext __cdecl getServerSessionContext() = 0 ;
	virtual _di_JSSLServerSocketFactory __cdecl getServerSocketFactory() = 0 ;
	virtual _di_Jssl_SSLSocketFactory __cdecl getSocketFactory() = 0 ;
	virtual _di_JSSLParameters __cdecl getSupportedSSLParameters() = 0 ;
	virtual void __cdecl init(Androidapi::Jnibridge::TJavaObjectArray__1<_di_JKeyManager>* km, Androidapi::Jnibridge::TJavaObjectArray__1<_di_JTrustManager>* tm, Androidapi::Jni::Java::Security::_di_JSecureRandom random) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLContext : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLContextClass,_di_JSSLContext>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLContextClass,_di_JSSLContext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLContext() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLContextClass,_di_JSSLContext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLContext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BAAABE20-6E5F-4021-B7CD-182A2264C7DA}") JSSLEngineClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	
};

__interface  INTERFACE_UUID("{012D2973-85C8-4763-8883-A4EAECC3A570}") JSSLEngine  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual void __cdecl beginHandshake() = 0 ;
	virtual void __cdecl closeInbound() = 0 ;
	virtual void __cdecl closeOutbound() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JRunnable __cdecl getDelegatedTask() = 0 ;
	virtual bool __cdecl getEnableSessionCreation() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getEnabledCipherSuites() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getEnabledProtocols() = 0 ;
	virtual _di_JSSLSession __cdecl getHandshakeSession() = 0 ;
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl getHandshakeStatus() = 0 ;
	virtual bool __cdecl getNeedClientAuth() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPeerHost() = 0 ;
	virtual int __cdecl getPeerPort() = 0 ;
	virtual _di_JSSLParameters __cdecl getSSLParameters() = 0 ;
	virtual _di_JSSLSession __cdecl getSession() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getSupportedCipherSuites() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getSupportedProtocols() = 0 ;
	virtual bool __cdecl getUseClientMode() = 0 ;
	virtual bool __cdecl getWantClientAuth() = 0 ;
	virtual bool __cdecl isInboundDone() = 0 ;
	virtual bool __cdecl isOutboundDone() = 0 ;
	virtual void __cdecl setEnableSessionCreation(bool flag) = 0 ;
	virtual void __cdecl setEnabledCipherSuites(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* suites) = 0 ;
	virtual void __cdecl setEnabledProtocols(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* protocols) = 0 ;
	virtual void __cdecl setNeedClientAuth(bool need) = 0 ;
	virtual void __cdecl setSSLParameters(_di_JSSLParameters params) = 0 ;
	virtual void __cdecl setUseClientMode(bool mode) = 0 ;
	virtual void __cdecl setWantClientAuth(bool want) = 0 ;
	virtual _di_JSSLEngineResult __cdecl unwrap(Androidapi::Jni::Javatypes::_di_JByteBuffer src, Androidapi::Jni::Javatypes::_di_JByteBuffer dst) = 0 /* overload */;
	virtual _di_JSSLEngineResult __cdecl unwrap(Androidapi::Jni::Javatypes::_di_JByteBuffer src, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JByteBuffer>* dsts) = 0 /* overload */;
	virtual _di_JSSLEngineResult __cdecl unwrap(Androidapi::Jni::Javatypes::_di_JByteBuffer src, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JByteBuffer>* dsts, int offset, int length) = 0 /* overload */;
	virtual _di_JSSLEngineResult __cdecl wrap(Androidapi::Jni::Javatypes::_di_JByteBuffer src, Androidapi::Jni::Javatypes::_di_JByteBuffer dst) = 0 /* overload */;
	virtual _di_JSSLEngineResult __cdecl wrap(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JByteBuffer>* srcs, Androidapi::Jni::Javatypes::_di_JByteBuffer dst) = 0 /* overload */;
	virtual _di_JSSLEngineResult __cdecl wrap(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JByteBuffer>* srcs, int offset, int length, Androidapi::Jni::Javatypes::_di_JByteBuffer dst) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLEngine : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineClass,_di_JSSLEngine>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineClass,_di_JSSLEngine> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLEngine() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineClass,_di_JSSLEngine>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLEngine() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{F8F1D25C-A489-4F86-BCEB-CC48F7AC2994}") JSSLEngineResultClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSSLEngineResult __cdecl init(_di_JSSLEngineResult_Status status, _di_JSSLEngineResult_HandshakeStatus handshakeStatus, int bytesConsumed, int bytesProduced) = 0 ;
};

__interface  INTERFACE_UUID("{C4F26352-D6EF-4DF7-8EBF-22F65BA5BC3A}") JSSLEngineResult  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual int __cdecl bytesConsumed() = 0 ;
	virtual int __cdecl bytesProduced() = 0 ;
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl getHandshakeStatus() = 0 ;
	virtual _di_JSSLEngineResult_Status __cdecl getStatus() = 0 ;
	HIDESBASE virtual Androidapi::Jni::Javatypes::_di_JString __cdecl toString() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLEngineResult : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResultClass,_di_JSSLEngineResult>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResultClass,_di_JSSLEngineResult> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLEngineResult() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResultClass,_di_JSSLEngineResult>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLEngineResult() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{39AAE6A5-C19F-41CD-BBC8-393E2FCD6AFF}") JSSLEngineResult_HandshakeStatusClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl _GetFINISHED() = 0 ;
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl _GetNEED_TASK() = 0 ;
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl _GetNEED_UNWRAP() = 0 ;
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl _GetNEED_WRAP() = 0 ;
	virtual _di_JSSLEngineResult_HandshakeStatus __cdecl _GetNOT_HANDSHAKING() = 0 ;
	HIDESBASE virtual _di_JSSLEngineResult_HandshakeStatus __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JSSLEngineResult_HandshakeStatus>* __cdecl values() = 0 ;
	__property _di_JSSLEngineResult_HandshakeStatus FINISHED = {read=_GetFINISHED};
	__property _di_JSSLEngineResult_HandshakeStatus NEED_TASK = {read=_GetNEED_TASK};
	__property _di_JSSLEngineResult_HandshakeStatus NEED_UNWRAP = {read=_GetNEED_UNWRAP};
	__property _di_JSSLEngineResult_HandshakeStatus NEED_WRAP = {read=_GetNEED_WRAP};
	__property _di_JSSLEngineResult_HandshakeStatus NOT_HANDSHAKING = {read=_GetNOT_HANDSHAKING};
};

__interface  INTERFACE_UUID("{421FAE1D-BB23-4B9D-A8F0-27751CF8B1E0}") JSSLEngineResult_HandshakeStatus  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLEngineResult_HandshakeStatus : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResult_HandshakeStatusClass,_di_JSSLEngineResult_HandshakeStatus>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResult_HandshakeStatusClass,_di_JSSLEngineResult_HandshakeStatus> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLEngineResult_HandshakeStatus() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResult_HandshakeStatusClass,_di_JSSLEngineResult_HandshakeStatus>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLEngineResult_HandshakeStatus() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{FEAE2C82-9632-460B-8579-805E32F2C367}") JSSLEngineResult_StatusClass  : public Androidapi::Jni::Javatypes::JEnumClass 
{
	virtual _di_JSSLEngineResult_Status __cdecl _GetBUFFER_OVERFLOW() = 0 ;
	virtual _di_JSSLEngineResult_Status __cdecl _GetBUFFER_UNDERFLOW() = 0 ;
	virtual _di_JSSLEngineResult_Status __cdecl _GetCLOSED() = 0 ;
	virtual _di_JSSLEngineResult_Status __cdecl _GetOK() = 0 ;
	HIDESBASE virtual _di_JSSLEngineResult_Status __cdecl valueOf(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JSSLEngineResult_Status>* __cdecl values() = 0 ;
	__property _di_JSSLEngineResult_Status BUFFER_OVERFLOW = {read=_GetBUFFER_OVERFLOW};
	__property _di_JSSLEngineResult_Status BUFFER_UNDERFLOW = {read=_GetBUFFER_UNDERFLOW};
	__property _di_JSSLEngineResult_Status CLOSED = {read=_GetCLOSED};
	__property _di_JSSLEngineResult_Status OK = {read=_GetOK};
};

__interface  INTERFACE_UUID("{5BF63075-A1E1-4B56-A3E8-A469C9F9E077}") JSSLEngineResult_Status  : public Androidapi::Jni::Javatypes::JEnum 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLEngineResult_Status : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResult_StatusClass,_di_JSSLEngineResult_Status>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResult_StatusClass,_di_JSSLEngineResult_Status> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLEngineResult_Status() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLEngineResult_StatusClass,_di_JSSLEngineResult_Status>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLEngineResult_Status() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3AE4F5A2-6FE0-4F13-BD73-DB3DB1312ABA}") JSSLParametersClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	HIDESBASE virtual _di_JSSLParameters __cdecl init() = 0 /* overload */;
	HIDESBASE virtual _di_JSSLParameters __cdecl init(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* cipherSuites) = 0 /* overload */;
	HIDESBASE virtual _di_JSSLParameters __cdecl init(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* cipherSuites, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* protocols) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{8F0342F0-7FC5-494A-984F-7A12BCCDB1EE}") JSSLParameters  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Java::Security::_di_JAlgorithmConstraints __cdecl getAlgorithmConstraints() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getCipherSuites() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getEndpointIdentificationAlgorithm() = 0 ;
	virtual bool __cdecl getNeedClientAuth() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getProtocols() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JCollection __cdecl getSNIMatchers() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JList __cdecl getServerNames() = 0 ;
	virtual bool __cdecl getUseCipherSuitesOrder() = 0 ;
	virtual bool __cdecl getWantClientAuth() = 0 ;
	virtual void __cdecl setAlgorithmConstraints(Androidapi::Jni::Java::Security::_di_JAlgorithmConstraints constraints) = 0 ;
	virtual void __cdecl setCipherSuites(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* cipherSuites) = 0 ;
	virtual void __cdecl setEndpointIdentificationAlgorithm(Androidapi::Jni::Javatypes::_di_JString algorithm) = 0 ;
	virtual void __cdecl setNeedClientAuth(bool needClientAuth) = 0 ;
	virtual void __cdecl setProtocols(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* protocols) = 0 ;
	virtual void __cdecl setSNIMatchers(Androidapi::Jni::Javatypes::_di_JCollection matchers) = 0 ;
	virtual void __cdecl setServerNames(Androidapi::Jni::Javatypes::_di_JList serverNames) = 0 ;
	virtual void __cdecl setUseCipherSuitesOrder(bool honorOrder) = 0 ;
	virtual void __cdecl setWantClientAuth(bool wantClientAuth) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLParameters : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLParametersClass,_di_JSSLParameters>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLParametersClass,_di_JSSLParameters> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLParameters() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLParametersClass,_di_JSSLParameters>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLParameters() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{D9E9A467-AEB3-4D12-8C2D-F736D3DEE702}") JSSLServerSocketFactoryClass  : public JServerSocketFactoryClass 
{
	HIDESBASE virtual _di_JServerSocketFactory __cdecl getDefault() = 0 ;
};

__interface  INTERFACE_UUID("{E98E0C65-85C2-43B3-BC05-AA0469744526}") JSSLServerSocketFactory  : public JServerSocketFactory 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getDefaultCipherSuites() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getSupportedCipherSuites() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLServerSocketFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLServerSocketFactoryClass,_di_JSSLServerSocketFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLServerSocketFactoryClass,_di_JSSLServerSocketFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLServerSocketFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLServerSocketFactoryClass,_di_JSSLServerSocketFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLServerSocketFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{C6972B16-AD10-4299-BCEB-8984204AB41E}") JSSLSessionClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{77CF05C7-35CD-4DA0-9CCA-1300E7780808}") JSSLSession  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual int __cdecl getApplicationBufferSize() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getCipherSuite() = 0 ;
	virtual __int64 __cdecl getCreationTime() = 0 ;
	virtual Androidapi::Jnibridge::TJavaArray__1<System::Byte>* __cdecl getId() = 0 ;
	virtual __int64 __cdecl getLastAccessedTime() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JCertificate>* __cdecl getLocalCertificates() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPrincipal __cdecl getLocalPrincipal() = 0 ;
	virtual int __cdecl getPacketBufferSize() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_Jcert_X509Certificate>* __cdecl getPeerCertificateChain() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JCertificate>* __cdecl getPeerCertificates() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getPeerHost() = 0 ;
	virtual int __cdecl getPeerPort() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPrincipal __cdecl getPeerPrincipal() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getProtocol() = 0 ;
	virtual _di_JSSLSessionContext __cdecl getSessionContext() = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JObject __cdecl getValue(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getValueNames() = 0 ;
	virtual void __cdecl invalidate() = 0 ;
	virtual bool __cdecl isValid() = 0 ;
	virtual void __cdecl putValue(Androidapi::Jni::Javatypes::_di_JString name, Androidapi::Jni::Javatypes::_di_JObject value) = 0 ;
	virtual void __cdecl removeValue(Androidapi::Jni::Javatypes::_di_JString name) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLSession : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLSessionClass,_di_JSSLSession>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLSessionClass,_di_JSSLSession> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLSession() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLSessionClass,_di_JSSLSession>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLSession() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{E7289973-3A07-44F8-AB30-F73387E95E40}") JSSLSessionContextClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{85F3AEDC-01A1-4365-8096-27F150D132FA}") JSSLSessionContext  : public Androidapi::Jnibridge::IJavaInstance 
{
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JEnumeration>* __cdecl getIds() = 0 ;
	virtual _di_JSSLSession __cdecl getSession(Androidapi::Jnibridge::TJavaArray__1<System::Byte>* sessionId) = 0 ;
	virtual int __cdecl getSessionCacheSize() = 0 ;
	virtual int __cdecl getSessionTimeout() = 0 ;
	virtual void __cdecl setSessionCacheSize(int size) = 0 ;
	virtual void __cdecl setSessionTimeout(int seconds) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSSLSessionContext : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLSessionContextClass,_di_JSSLSessionContext>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLSessionContextClass,_di_JSSLSessionContext> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJSSLSessionContext() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JSSLSessionContextClass,_di_JSSLSessionContext>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJSSLSessionContext() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{3EAA39D3-A9AA-44A7-8F6E-D9C807FE607D}") Jssl_SSLSocketFactoryClass  : public Jnet_SocketFactoryClass 
{
	HIDESBASE virtual _di_Jssl_SSLSocketFactory __cdecl init() = 0 ;
	HIDESBASE virtual _di_Jnet_SocketFactory __cdecl getDefault() = 0 ;
};

__interface  INTERFACE_UUID("{7F1F07B3-D38E-4C4B-AF90-A79EE2B8D53B}") Jssl_SSLSocketFactory  : public Jnet_SocketFactory 
{
	HIDESBASE virtual _di_JSocket __cdecl createSocket(_di_JSocket s, Androidapi::Jni::Javatypes::_di_JString host, int port, bool autoClose) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getDefaultCipherSuites() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getSupportedCipherSuites() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJssl_SSLSocketFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jssl_SSLSocketFactoryClass,_di_Jssl_SSLSocketFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jssl_SSLSocketFactoryClass,_di_Jssl_SSLSocketFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJssl_SSLSocketFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_Jssl_SSLSocketFactoryClass,_di_Jssl_SSLSocketFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJssl_SSLSocketFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0856E6B9-F405-4346-B20D-E9E20425EFC2}") JTrustManagerClass  : public Androidapi::Jnibridge::IJavaClass 
{
	
};

__interface  INTERFACE_UUID("{A6DD0C52-928E-4E65-980F-9167C55840FA}") JTrustManager  : public Androidapi::Jnibridge::IJavaInstance 
{
	
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTrustManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrustManagerClass,_di_JTrustManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrustManagerClass,_di_JTrustManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTrustManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrustManagerClass,_di_JTrustManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTrustManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{0BE1CDA3-C6D6-4A69-88EE-C349F77BEAB5}") JTrustManagerFactoryClass  : public Androidapi::Jni::Javatypes::JObjectClass 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getDefaultAlgorithm() = 0 ;
	virtual _di_JTrustManagerFactory __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString algorithm) = 0 /* overload */;
	virtual _di_JTrustManagerFactory __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString algorithm, Androidapi::Jni::Javatypes::_di_JString provider) = 0 /* overload */;
	virtual _di_JTrustManagerFactory __cdecl getInstance(Androidapi::Jni::Javatypes::_di_JString algorithm, Androidapi::Jni::Java::Security::_di_JProvider provider) = 0 /* overload */;
};

__interface  INTERFACE_UUID("{F907542C-2731-4410-93E0-76986A871C2D}") JTrustManagerFactory  : public Androidapi::Jni::Javatypes::JObject 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl getAlgorithm() = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JProvider __cdecl getProvider() = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<_di_JTrustManager>* __cdecl getTrustManagers() = 0 ;
	virtual void __cdecl init(Androidapi::Jni::Java::Security::_di_JKeyStore ks) = 0 /* overload */;
	virtual void __cdecl init(_di_JManagerFactoryParameters spec) = 0 /* overload */;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJTrustManagerFactory : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrustManagerFactoryClass,_di_JTrustManagerFactory>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrustManagerFactoryClass,_di_JTrustManagerFactory> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJTrustManagerFactory() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JTrustManagerFactoryClass,_di_JTrustManagerFactory>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJTrustManagerFactory() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{BAC0E0B6-EA29-4228-AC17-AF9A7BA85B5C}") JX509KeyManagerClass  : public JKeyManagerClass 
{
	
};

__interface  INTERFACE_UUID("{6B79A5A5-619D-44E9-90B4-4B0369F96055}") JX509KeyManager  : public JKeyManager 
{
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl chooseClientAlias(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* keyType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* issuers, _di_JSocket socket) = 0 ;
	virtual Androidapi::Jni::Javatypes::_di_JString __cdecl chooseServerAlias(Androidapi::Jni::Javatypes::_di_JString keyType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* issuers, _di_JSocket socket) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JX509Certificate>* __cdecl getCertificateChain(Androidapi::Jni::Javatypes::_di_JString alias) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getClientAliases(Androidapi::Jni::Javatypes::_di_JString keyType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* issuers) = 0 ;
	virtual Androidapi::Jni::Java::Security::_di_JPrivateKey __cdecl getPrivateKey(Androidapi::Jni::Javatypes::_di_JString alias) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Javatypes::_di_JString>* __cdecl getServerAliases(Androidapi::Jni::Javatypes::_di_JString keyType, Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JPrincipal>* issuers) = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJX509KeyManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JX509KeyManagerClass,_di_JX509KeyManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JX509KeyManagerClass,_di_JX509KeyManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJX509KeyManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JX509KeyManagerClass,_di_JX509KeyManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJX509KeyManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

__interface  INTERFACE_UUID("{7684B973-52C4-49C0-BE3D-9CD5C97C9062}") JX509TrustManagerClass  : public JTrustManagerClass 
{
	
};

__interface  INTERFACE_UUID("{B1BE4FF6-227F-4672-B975-C55D8CCD53D5}") JX509TrustManager  : public JTrustManager 
{
	virtual void __cdecl checkClientTrusted(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JX509Certificate>* chain, Androidapi::Jni::Javatypes::_di_JString authType) = 0 ;
	virtual void __cdecl checkServerTrusted(Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JX509Certificate>* chain, Androidapi::Jni::Javatypes::_di_JString authType) = 0 ;
	virtual Androidapi::Jnibridge::TJavaObjectArray__1<Androidapi::Jni::Java::Security::_di_JX509Certificate>* __cdecl getAcceptedIssuers() = 0 ;
};

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJX509TrustManager : public Androidapi::Jnibridge::TJavaGenericImport__2<_di_JX509TrustManagerClass,_di_JX509TrustManager>
{
	typedef Androidapi::Jnibridge::TJavaGenericImport__2<_di_JX509TrustManagerClass,_di_JX509TrustManager> inherited;
	
public:
	/* TObject.Create */ inline __fastcall TJX509TrustManager() : Androidapi::Jnibridge::TJavaGenericImport__2<_di_JX509TrustManagerClass,_di_JX509TrustManager>() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJX509TrustManager() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Net */
}	/* namespace Java */
}	/* namespace Jni */
}	/* namespace Androidapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_JAVA_NET)
using namespace Androidapi::Jni::Java::Net;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI_JAVA)
using namespace Androidapi::Jni::Java;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI_JNI)
using namespace Androidapi::Jni;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_ANDROIDAPI)
using namespace Androidapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Androidapi_Jni_Java_NetHPP
