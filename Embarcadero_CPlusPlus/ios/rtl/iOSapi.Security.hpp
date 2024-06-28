// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'iOSapi.Security.pas' rev: 34.00 (iOS)

#ifndef Iosapi_SecurityHPP
#define Iosapi_SecurityHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <iOSapi.CocoaTypes.hpp>
#include <iOSapi.Foundation.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <Macapi.Dispatch.hpp>

//-- user supplied -----------------------------------------------------------

namespace Iosapi
{
namespace Security
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
typedef System::Word SSLCipherSuite;

typedef void * SecCertificateRef;

typedef void * SecIdentityRef;

typedef void * SecKeyRef;

typedef void * SecPolicyRef;

typedef unsigned long SecPadding;

typedef void * SecRandomRef;

typedef unsigned long SecTrustResultType;

typedef void * SecTrustRef;

typedef void __fastcall (__closure *SecTrustCallback)(void * param1, unsigned long param2);

typedef void * SSLContextRef;

typedef void * SSLConnectionRef;

typedef unsigned long SSLProtocol;

typedef unsigned long SSLSessionOption;

typedef unsigned long SSLSessionState;

typedef unsigned long SSLClientCertificateState;

typedef int __cdecl (*SSLReadFunc)(void * param1, void * param2, unsigned long param3);

typedef int __cdecl (*SSLWriteFunc)(void * param1, void * param2, unsigned long param3);

typedef unsigned long SSLProtocolSide;

typedef unsigned long SSLConnectionType;

typedef unsigned long SSLAuthenticate;

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 SSL_NULL_WITH_NULL_NULL = System::Int8(0x0);
static constexpr System::Int8 SSL_RSA_WITH_NULL_MD5 = System::Int8(0x1);
static constexpr System::Int8 SSL_RSA_WITH_NULL_SHA = System::Int8(0x2);
static constexpr System::Int8 SSL_RSA_EXPORT_WITH_RC4_40_MD5 = System::Int8(0x3);
static constexpr System::Int8 SSL_RSA_WITH_RC4_128_MD5 = System::Int8(0x4);
static constexpr System::Int8 SSL_RSA_WITH_RC4_128_SHA = System::Int8(0x5);
static constexpr System::Int8 SSL_RSA_EXPORT_WITH_RC2_CBC_40_MD5 = System::Int8(0x6);
static constexpr System::Int8 SSL_RSA_WITH_IDEA_CBC_SHA = System::Int8(0x7);
static constexpr System::Int8 SSL_RSA_EXPORT_WITH_DES40_CBC_SHA = System::Int8(0x8);
static constexpr System::Int8 SSL_RSA_WITH_DES_CBC_SHA = System::Int8(0x9);
static constexpr System::Int8 SSL_RSA_WITH_3DES_EDE_CBC_SHA = System::Int8(0xa);
static constexpr System::Int8 SSL_DH_DSS_EXPORT_WITH_DES40_CBC_SHA = System::Int8(0xb);
static constexpr System::Int8 SSL_DH_DSS_WITH_DES_CBC_SHA = System::Int8(0xc);
static constexpr System::Int8 SSL_DH_DSS_WITH_3DES_EDE_CBC_SHA = System::Int8(0xd);
static constexpr System::Int8 SSL_DH_RSA_EXPORT_WITH_DES40_CBC_SHA = System::Int8(0xe);
static constexpr System::Int8 SSL_DH_RSA_WITH_DES_CBC_SHA = System::Int8(0xf);
static constexpr System::Int8 SSL_DH_RSA_WITH_3DES_EDE_CBC_SHA = System::Int8(0x10);
static constexpr System::Int8 SSL_DHE_DSS_EXPORT_WITH_DES40_CBC_SHA = System::Int8(0x11);
static constexpr System::Int8 SSL_DHE_DSS_WITH_DES_CBC_SHA = System::Int8(0x12);
static constexpr System::Int8 SSL_DHE_DSS_WITH_3DES_EDE_CBC_SHA = System::Int8(0x13);
static constexpr System::Int8 SSL_DHE_RSA_EXPORT_WITH_DES40_CBC_SHA = System::Int8(0x14);
static constexpr System::Int8 SSL_DHE_RSA_WITH_DES_CBC_SHA = System::Int8(0x15);
static constexpr System::Int8 SSL_DHE_RSA_WITH_3DES_EDE_CBC_SHA = System::Int8(0x16);
static constexpr System::Int8 SSL_DH_anon_EXPORT_WITH_RC4_40_MD5 = System::Int8(0x17);
static constexpr System::Int8 SSL_DH_anon_WITH_RC4_128_MD5 = System::Int8(0x18);
static constexpr System::Int8 SSL_DH_anon_EXPORT_WITH_DES40_CBC_SHA = System::Int8(0x19);
static constexpr System::Int8 SSL_DH_anon_WITH_DES_CBC_SHA = System::Int8(0x1a);
static constexpr System::Int8 SSL_DH_anon_WITH_3DES_EDE_CBC_SHA = System::Int8(0x1b);
static constexpr System::Int8 SSL_FORTEZZA_DMS_WITH_NULL_SHA = System::Int8(0x1c);
static constexpr System::Int8 SSL_FORTEZZA_DMS_WITH_FORTEZZA_CBC_SHA = System::Int8(0x1d);
static constexpr System::Int8 TLS_RSA_WITH_AES_128_CBC_SHA = System::Int8(0x2f);
static constexpr System::Int8 TLS_DH_DSS_WITH_AES_128_CBC_SHA = System::Int8(0x30);
static constexpr System::Int8 TLS_DH_RSA_WITH_AES_128_CBC_SHA = System::Int8(0x31);
static constexpr System::Int8 TLS_DHE_DSS_WITH_AES_128_CBC_SHA = System::Int8(0x32);
static constexpr System::Int8 TLS_DHE_RSA_WITH_AES_128_CBC_SHA = System::Int8(0x33);
static constexpr System::Int8 TLS_DH_anon_WITH_AES_128_CBC_SHA = System::Int8(0x34);
static constexpr System::Int8 TLS_RSA_WITH_AES_256_CBC_SHA = System::Int8(0x35);
static constexpr System::Int8 TLS_DH_DSS_WITH_AES_256_CBC_SHA = System::Int8(0x36);
static constexpr System::Int8 TLS_DH_RSA_WITH_AES_256_CBC_SHA = System::Int8(0x37);
static constexpr System::Int8 TLS_DHE_DSS_WITH_AES_256_CBC_SHA = System::Int8(0x38);
static constexpr System::Int8 TLS_DHE_RSA_WITH_AES_256_CBC_SHA = System::Int8(0x39);
static constexpr System::Int8 TLS_DH_anon_WITH_AES_256_CBC_SHA = System::Int8(0x3a);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_NULL_SHA = System::Word(0xc001);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_RC4_128_SHA = System::Word(0xc002);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA = System::Word(0xc003);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA = System::Word(0xc004);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA = System::Word(0xc005);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_NULL_SHA = System::Word(0xc006);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_RC4_128_SHA = System::Word(0xc007);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA = System::Word(0xc008);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA = System::Word(0xc009);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA = System::Word(0xc00a);
static constexpr System::Word TLS_ECDH_RSA_WITH_NULL_SHA = System::Word(0xc00b);
static constexpr System::Word TLS_ECDH_RSA_WITH_RC4_128_SHA = System::Word(0xc00c);
static constexpr System::Word TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA = System::Word(0xc00d);
static constexpr System::Word TLS_ECDH_RSA_WITH_AES_128_CBC_SHA = System::Word(0xc00e);
static constexpr System::Word TLS_ECDH_RSA_WITH_AES_256_CBC_SHA = System::Word(0xc00f);
static constexpr System::Word TLS_ECDHE_RSA_WITH_NULL_SHA = System::Word(0xc010);
static constexpr System::Word TLS_ECDHE_RSA_WITH_RC4_128_SHA = System::Word(0xc011);
static constexpr System::Word TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA = System::Word(0xc012);
static constexpr System::Word TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA = System::Word(0xc013);
static constexpr System::Word TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA = System::Word(0xc014);
static constexpr System::Word TLS_ECDH_anon_WITH_NULL_SHA = System::Word(0xc015);
static constexpr System::Word TLS_ECDH_anon_WITH_RC4_128_SHA = System::Word(0xc016);
static constexpr System::Word TLS_ECDH_anon_WITH_3DES_EDE_CBC_SHA = System::Word(0xc017);
static constexpr System::Word TLS_ECDH_anon_WITH_AES_128_CBC_SHA = System::Word(0xc018);
static constexpr System::Word TLS_ECDH_anon_WITH_AES_256_CBC_SHA = System::Word(0xc019);
static constexpr System::Int8 TLS_NULL_WITH_NULL_NULL = System::Int8(0x0);
static constexpr System::Int8 TLS_RSA_WITH_NULL_MD5 = System::Int8(0x1);
static constexpr System::Int8 TLS_RSA_WITH_NULL_SHA = System::Int8(0x2);
static constexpr System::Int8 TLS_RSA_WITH_RC4_128_MD5 = System::Int8(0x4);
static constexpr System::Int8 TLS_RSA_WITH_RC4_128_SHA = System::Int8(0x5);
static constexpr System::Int8 TLS_RSA_WITH_3DES_EDE_CBC_SHA = System::Int8(0xa);
static constexpr System::Int8 TLS_RSA_WITH_NULL_SHA256 = System::Int8(0x3b);
static constexpr System::Int8 TLS_RSA_WITH_AES_128_CBC_SHA256 = System::Int8(0x3c);
static constexpr System::Int8 TLS_RSA_WITH_AES_256_CBC_SHA256 = System::Int8(0x3d);
static constexpr System::Int8 TLS_DH_DSS_WITH_3DES_EDE_CBC_SHA = System::Int8(0xd);
static constexpr System::Int8 TLS_DH_RSA_WITH_3DES_EDE_CBC_SHA = System::Int8(0x10);
static constexpr System::Int8 TLS_DHE_DSS_WITH_3DES_EDE_CBC_SHA = System::Int8(0x13);
static constexpr System::Int8 TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA = System::Int8(0x16);
static constexpr System::Int8 TLS_DH_DSS_WITH_AES_128_CBC_SHA256 = System::Int8(0x3e);
static constexpr System::Int8 TLS_DH_RSA_WITH_AES_128_CBC_SHA256 = System::Int8(0x3f);
static constexpr System::Int8 TLS_DHE_DSS_WITH_AES_128_CBC_SHA256 = System::Int8(0x40);
static constexpr System::Int8 TLS_DHE_RSA_WITH_AES_128_CBC_SHA256 = System::Int8(0x67);
static constexpr System::Int8 TLS_DH_DSS_WITH_AES_256_CBC_SHA256 = System::Int8(0x68);
static constexpr System::Int8 TLS_DH_RSA_WITH_AES_256_CBC_SHA256 = System::Int8(0x69);
static constexpr System::Int8 TLS_DHE_DSS_WITH_AES_256_CBC_SHA256 = System::Int8(0x6a);
static constexpr System::Int8 TLS_DHE_RSA_WITH_AES_256_CBC_SHA256 = System::Int8(0x6b);
static constexpr System::Int8 TLS_DH_anon_WITH_RC4_128_MD5 = System::Int8(0x18);
static constexpr System::Int8 TLS_DH_anon_WITH_3DES_EDE_CBC_SHA = System::Int8(0x1b);
static constexpr System::Int8 TLS_DH_anon_WITH_AES_128_CBC_SHA256 = System::Int8(0x6c);
static constexpr System::Int8 TLS_DH_anon_WITH_AES_256_CBC_SHA256 = System::Int8(0x6d);
static constexpr System::Byte TLS_PSK_WITH_RC4_128_SHA = System::Byte(0x8a);
static constexpr System::Byte TLS_PSK_WITH_3DES_EDE_CBC_SHA = System::Byte(0x8b);
static constexpr System::Byte TLS_PSK_WITH_AES_128_CBC_SHA = System::Byte(0x8c);
static constexpr System::Byte TLS_PSK_WITH_AES_256_CBC_SHA = System::Byte(0x8d);
static constexpr System::Byte TLS_DHE_PSK_WITH_RC4_128_SHA = System::Byte(0x8e);
static constexpr System::Byte TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA = System::Byte(0x8f);
static constexpr System::Byte TLS_DHE_PSK_WITH_AES_128_CBC_SHA = System::Byte(0x90);
static constexpr System::Byte TLS_DHE_PSK_WITH_AES_256_CBC_SHA = System::Byte(0x91);
static constexpr System::Byte TLS_RSA_PSK_WITH_RC4_128_SHA = System::Byte(0x92);
static constexpr System::Byte TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA = System::Byte(0x93);
static constexpr System::Byte TLS_RSA_PSK_WITH_AES_128_CBC_SHA = System::Byte(0x94);
static constexpr System::Byte TLS_RSA_PSK_WITH_AES_256_CBC_SHA = System::Byte(0x95);
static constexpr System::Int8 TLS_PSK_WITH_NULL_SHA = System::Int8(0x2c);
static constexpr System::Int8 TLS_DHE_PSK_WITH_NULL_SHA = System::Int8(0x2d);
static constexpr System::Int8 TLS_RSA_PSK_WITH_NULL_SHA = System::Int8(0x2e);
static constexpr System::Byte TLS_RSA_WITH_AES_128_GCM_SHA256 = System::Byte(0x9c);
static constexpr System::Byte TLS_RSA_WITH_AES_256_GCM_SHA384 = System::Byte(0x9d);
static constexpr System::Byte TLS_DHE_RSA_WITH_AES_128_GCM_SHA256 = System::Byte(0x9e);
static constexpr System::Byte TLS_DHE_RSA_WITH_AES_256_GCM_SHA384 = System::Byte(0x9f);
static constexpr System::Byte TLS_DH_RSA_WITH_AES_128_GCM_SHA256 = System::Byte(0xa0);
static constexpr System::Byte TLS_DH_RSA_WITH_AES_256_GCM_SHA384 = System::Byte(0xa1);
static constexpr System::Byte TLS_DHE_DSS_WITH_AES_128_GCM_SHA256 = System::Byte(0xa2);
static constexpr System::Byte TLS_DHE_DSS_WITH_AES_256_GCM_SHA384 = System::Byte(0xa3);
static constexpr System::Byte TLS_DH_DSS_WITH_AES_128_GCM_SHA256 = System::Byte(0xa4);
static constexpr System::Byte TLS_DH_DSS_WITH_AES_256_GCM_SHA384 = System::Byte(0xa5);
static constexpr System::Byte TLS_DH_anon_WITH_AES_128_GCM_SHA256 = System::Byte(0xa6);
static constexpr System::Byte TLS_DH_anon_WITH_AES_256_GCM_SHA384 = System::Byte(0xa7);
static constexpr System::Byte TLS_PSK_WITH_AES_128_GCM_SHA256 = System::Byte(0xa8);
static constexpr System::Byte TLS_PSK_WITH_AES_256_GCM_SHA384 = System::Byte(0xa9);
static constexpr System::Byte TLS_DHE_PSK_WITH_AES_128_GCM_SHA256 = System::Byte(0xaa);
static constexpr System::Byte TLS_DHE_PSK_WITH_AES_256_GCM_SHA384 = System::Byte(0xab);
static constexpr System::Byte TLS_RSA_PSK_WITH_AES_128_GCM_SHA256 = System::Byte(0xac);
static constexpr System::Byte TLS_RSA_PSK_WITH_AES_256_GCM_SHA384 = System::Byte(0xad);
static constexpr System::Byte TLS_PSK_WITH_AES_128_CBC_SHA256 = System::Byte(0xae);
static constexpr System::Byte TLS_PSK_WITH_AES_256_CBC_SHA384 = System::Byte(0xaf);
static constexpr System::Byte TLS_PSK_WITH_NULL_SHA256 = System::Byte(0xb0);
static constexpr System::Byte TLS_PSK_WITH_NULL_SHA384 = System::Byte(0xb1);
static constexpr System::Byte TLS_DHE_PSK_WITH_AES_128_CBC_SHA256 = System::Byte(0xb2);
static constexpr System::Byte TLS_DHE_PSK_WITH_AES_256_CBC_SHA384 = System::Byte(0xb3);
static constexpr System::Byte TLS_DHE_PSK_WITH_NULL_SHA256 = System::Byte(0xb4);
static constexpr System::Byte TLS_DHE_PSK_WITH_NULL_SHA384 = System::Byte(0xb5);
static constexpr System::Byte TLS_RSA_PSK_WITH_AES_128_CBC_SHA256 = System::Byte(0xb6);
static constexpr System::Byte TLS_RSA_PSK_WITH_AES_256_CBC_SHA384 = System::Byte(0xb7);
static constexpr System::Byte TLS_RSA_PSK_WITH_NULL_SHA256 = System::Byte(0xb8);
static constexpr System::Byte TLS_RSA_PSK_WITH_NULL_SHA384 = System::Byte(0xb9);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256 = System::Word(0xc023);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384 = System::Word(0xc024);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256 = System::Word(0xc025);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384 = System::Word(0xc026);
static constexpr System::Word TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256 = System::Word(0xc027);
static constexpr System::Word TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384 = System::Word(0xc028);
static constexpr System::Word TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256 = System::Word(0xc029);
static constexpr System::Word TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384 = System::Word(0xc02a);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256 = System::Word(0xc02b);
static constexpr System::Word TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384 = System::Word(0xc02c);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256 = System::Word(0xc02d);
static constexpr System::Word TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384 = System::Word(0xc02e);
static constexpr System::Word TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 = System::Word(0xc02f);
static constexpr System::Word TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384 = System::Word(0xc030);
static constexpr System::Word TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256 = System::Word(0xc031);
static constexpr System::Word TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384 = System::Word(0xc032);
static constexpr System::Byte TLS_EMPTY_RENEGOTIATION_INFO_SCSV = System::Byte(0xff);
static constexpr System::Word SSL_RSA_WITH_RC2_CBC_MD5 = System::Word(0xff80);
static constexpr System::Word SSL_RSA_WITH_IDEA_CBC_MD5 = System::Word(0xff81);
static constexpr System::Word SSL_RSA_WITH_DES_CBC_MD5 = System::Word(0xff82);
static constexpr System::Word SSL_RSA_WITH_3DES_EDE_CBC_MD5 = System::Word(0xff83);
static constexpr System::Word SSL_NO_SUCH_CIPHERSUITE = System::Word(0xffff);
static constexpr System::Int8 errSecSuccess = System::Int8(0x0);
static constexpr System::Int8 errSecUnimplemented = System::Int8(-4);
static constexpr System::Int8 errSecIO = System::Int8(-36);
static constexpr System::Int8 errSecOpWr = System::Int8(-49);
static constexpr System::Int8 errSecParam = System::Int8(-50);
static constexpr System::Int8 errSecAllocate = System::Int8(-108);
static constexpr System::Int8 errSecUserCanceled = System::Int8(-128);
static constexpr short errSecBadReq = short(-909);
static constexpr short errSecInternalComponent = short(-2070);
static constexpr short errSecNotAvailable = short(-25291);
static constexpr short errSecDuplicateItem = short(-25299);
static constexpr short errSecItemNotFound = short(-25300);
static constexpr short errSecInteractionNotAllowed = short(-25308);
static constexpr short errSecDecode = short(-26275);
static constexpr short errSecAuthFailed = short(-25293);
static constexpr System::Int8 kSecPaddingNone = System::Int8(0x0);
static constexpr System::Int8 kSecPaddingPKCS1 = System::Int8(0x1);
static constexpr System::Int8 kSecPaddingOAEP = System::Int8(0x2);
static constexpr System::Word kSecPaddingPKCS1MD2 = System::Word(0x8000);
static constexpr System::Word kSecPaddingPKCS1MD5 = System::Word(0x8001);
static constexpr System::Word kSecPaddingPKCS1SHA1 = System::Word(0x8002);
static constexpr System::Word kSecPaddingPKCS1SHA224 = System::Word(0x8003);
static constexpr System::Word kSecPaddingPKCS1SHA256 = System::Word(0x8004);
static constexpr System::Word kSecPaddingPKCS1SHA384 = System::Word(0x8005);
static constexpr System::Word kSecPaddingPKCS1SHA512 = System::Word(0x8006);
static constexpr System::Int8 kSecRevocationOCSPMethod = System::Int8(0x1);
static constexpr System::Int8 kSecRevocationCRLMethod = System::Int8(0x2);
static constexpr System::Int8 kSecRevocationPreferCRL = System::Int8(0x4);
static constexpr System::Int8 kSecRevocationRequirePositiveResponse = System::Int8(0x8);
static constexpr System::Int8 kSecRevocationNetworkAccessDisabled = System::Int8(0x10);
static constexpr System::Int8 kSecRevocationUseAnyAvailableMethod = System::Int8(0x3);
static constexpr System::Int8 kSecTrustResultInvalid = System::Int8(0x0);
static constexpr System::Int8 kSecTrustResultProceed = System::Int8(0x1);
static constexpr System::Int8 kSecTrustResultConfirm = System::Int8(0x2);
static constexpr System::Int8 kSecTrustResultDeny = System::Int8(0x3);
static constexpr System::Int8 kSecTrustResultUnspecified = System::Int8(0x4);
static constexpr System::Int8 kSecTrustResultRecoverableTrustFailure = System::Int8(0x5);
static constexpr System::Int8 kSecTrustResultFatalTrustFailure = System::Int8(0x6);
static constexpr System::Int8 kSecTrustResultOtherError = System::Int8(0x7);
static constexpr System::Int8 kSSLProtocolUnknown = System::Int8(0x0);
static constexpr System::Int8 kSSLProtocol3 = System::Int8(0x2);
static constexpr System::Int8 kTLSProtocol1 = System::Int8(0x4);
static constexpr System::Int8 kTLSProtocol11 = System::Int8(0x7);
static constexpr System::Int8 kTLSProtocol12 = System::Int8(0x8);
static constexpr System::Int8 kDTLSProtocol1 = System::Int8(0x9);
static constexpr System::Int8 kSSLProtocol2 = System::Int8(0x1);
static constexpr System::Int8 kSSLProtocol3Only = System::Int8(0x3);
static constexpr System::Int8 kTLSProtocol1Only = System::Int8(0x5);
static constexpr System::Int8 kSSLProtocolAll = System::Int8(0x6);
static constexpr System::Int8 kSSLSessionOptionBreakOnServerAuth = System::Int8(0x0);
static constexpr System::Int8 kSSLSessionOptionBreakOnCertRequested = System::Int8(0x1);
static constexpr System::Int8 kSSLSessionOptionBreakOnClientAuth = System::Int8(0x2);
static constexpr System::Int8 kSSLSessionOptionFalseStart = System::Int8(0x3);
static constexpr System::Int8 kSSLSessionOptionSendOneByteRecord = System::Int8(0x4);
static constexpr System::Int8 kSSLIdle = System::Int8(0x0);
static constexpr System::Int8 kSSLHandshake = System::Int8(0x1);
static constexpr System::Int8 kSSLConnected = System::Int8(0x2);
static constexpr System::Int8 kSSLClosed = System::Int8(0x3);
static constexpr System::Int8 kSSLAborted = System::Int8(0x4);
static constexpr System::Int8 kSSLClientCertNone = System::Int8(0x0);
static constexpr System::Int8 kSSLClientCertRequested = System::Int8(0x1);
static constexpr System::Int8 kSSLClientCertSent = System::Int8(0x2);
static constexpr System::Int8 kSSLClientCertRejected = System::Int8(0x3);
static constexpr short errSSLProtocol = short(-9800);
static constexpr short errSSLNegotiation = short(-9801);
static constexpr short errSSLFatalAlert = short(-9802);
static constexpr short errSSLWouldBlock = short(-9803);
static constexpr short errSSLSessionNotFound = short(-9804);
static constexpr short errSSLClosedGraceful = short(-9805);
static constexpr short errSSLClosedAbort = short(-9806);
static constexpr short errSSLXCertChainInvalid = short(-9807);
static constexpr short errSSLBadCert = short(-9808);
static constexpr short errSSLCrypto = short(-9809);
static constexpr short errSSLInternal = short(-9810);
static constexpr short errSSLModuleAttach = short(-9811);
static constexpr short errSSLUnknownRootCert = short(-9812);
static constexpr short errSSLNoRootCert = short(-9813);
static constexpr short errSSLCertExpired = short(-9814);
static constexpr short errSSLCertNotYetValid = short(-9815);
static constexpr short errSSLClosedNoNotify = short(-9816);
static constexpr short errSSLBufferOverflow = short(-9817);
static constexpr short errSSLBadCipherSuite = short(-9818);
static constexpr short errSSLPeerUnexpectedMsg = short(-9819);
static constexpr short errSSLPeerBadRecordMac = short(-9820);
static constexpr short errSSLPeerDecryptionFail = short(-9821);
static constexpr short errSSLPeerRecordOverflow = short(-9822);
static constexpr short errSSLPeerDecompressFail = short(-9823);
static constexpr short errSSLPeerHandshakeFail = short(-9824);
static constexpr short errSSLPeerBadCert = short(-9825);
static constexpr short errSSLPeerUnsupportedCert = short(-9826);
static constexpr short errSSLPeerCertRevoked = short(-9827);
static constexpr short errSSLPeerCertExpired = short(-9828);
static constexpr short errSSLPeerCertUnknown = short(-9829);
static constexpr short errSSLIllegalParam = short(-9830);
static constexpr short errSSLPeerUnknownCA = short(-9831);
static constexpr short errSSLPeerAccessDenied = short(-9832);
static constexpr short errSSLPeerDecodeError = short(-9833);
static constexpr short errSSLPeerDecryptError = short(-9834);
static constexpr short errSSLPeerExportRestriction = short(-9835);
static constexpr short errSSLPeerProtocolVersion = short(-9836);
static constexpr short errSSLPeerInsufficientSecurity = short(-9837);
static constexpr short errSSLPeerInternalError = short(-9838);
static constexpr short errSSLPeerUserCancelled = short(-9839);
static constexpr short errSSLPeerNoRenegotiation = short(-9840);
static constexpr short errSSLPeerAuthCompleted = short(-9841);
static constexpr short errSSLClientCertRequested = short(-9842);
static constexpr short errSSLHostNameMismatch = short(-9843);
static constexpr short errSSLConnectionRefused = short(-9844);
static constexpr short errSSLDecryptionFail = short(-9845);
static constexpr short errSSLBadRecordMac = short(-9846);
static constexpr short errSSLRecordOverflow = short(-9847);
static constexpr short errSSLBadConfiguration = short(-9848);
static constexpr short errSSLUnexpectedRecord = short(-9849);
static constexpr System::Int8 kSSLServerSide = System::Int8(0x0);
static constexpr System::Int8 kSSLClientSide = System::Int8(0x1);
static constexpr System::Int8 kSSLStreamType = System::Int8(0x0);
static constexpr System::Int8 kSSLDatagramType = System::Int8(0x1);
static constexpr System::Int8 kNeverAuthenticate = System::Int8(0x0);
static constexpr System::Int8 kAlwaysAuthenticate = System::Int8(0x1);
static constexpr System::Int8 kTryAuthenticate = System::Int8(0x2);
#define libSecurity u"/System/Library/Frameworks/Security.framework/Security"
extern "C" unsigned long __cdecl SecCertificateGetTypeID(void);
extern "C" void * __cdecl SecCertificateCreateWithData(CFAllocatorRef allocator, CFDataRef data);
extern "C" CFDataRef __cdecl SecCertificateCopyData(void * certificate);
extern "C" CFStringRef __cdecl SecCertificateCopySubjectSummary(void * certificate);
extern "C" unsigned long __cdecl SecIdentityGetTypeID(void);
extern "C" int __cdecl SecIdentityCopyCertificate(void * identityRef, void * certificateRef);
extern "C" int __cdecl SecIdentityCopyPrivateKey(void * identityRef, void * privateKeyRef);
extern "C" int __cdecl SecPKCS12Import(CFDataRef pkcs12_data, CFDictionaryRef options, CFArrayRef items);
extern "C" int __cdecl SecItemCopyMatching(CFDictionaryRef query, void * result);
extern "C" int __cdecl SecItemAdd(CFDictionaryRef attributes, void * result);
extern "C" int __cdecl SecItemUpdate(CFDictionaryRef query, CFDictionaryRef attributesToUpdate);
extern "C" int __cdecl SecItemDelete(CFDictionaryRef query);
extern "C" unsigned long __cdecl SecKeyGetTypeID(void);
extern "C" int __cdecl SecKeyGeneratePair(CFDictionaryRef parameters, void * publicKey, void * privateKey);
extern "C" int __cdecl SecKeyRawSign(void * key, unsigned long padding, System::Byte dataToSign, unsigned long dataToSignLen, System::Byte sig, unsigned long sigLen);
extern "C" int __cdecl SecKeyRawVerify(void * key, unsigned long padding, System::Byte signedData, unsigned long signedDataLen, System::Byte sig, unsigned long sigLen);
extern "C" int __cdecl SecKeyEncrypt(void * key, unsigned long padding, System::Byte plainText, unsigned long plainTextLen, System::Byte cipherText, unsigned long cipherTextLen);
extern "C" int __cdecl SecKeyDecrypt(void * key, unsigned long padding, System::Byte cipherText, unsigned long cipherTextLen, System::Byte plainText, unsigned long plainTextLen);
extern "C" unsigned long __cdecl SecKeyGetBlockSize(void * key);
extern "C" unsigned long __cdecl SecPolicyGetTypeID(void);
extern "C" CFDictionaryRef __cdecl SecPolicyCopyProperties(void * policyRef);
extern "C" void * __cdecl SecPolicyCreateBasicX509(void);
extern "C" void * __cdecl SecPolicyCreateSSL(bool server, CFStringRef hostname);
extern "C" void * __cdecl SecPolicyCreateRevocation(unsigned long revocationFlags);
extern "C" void * __cdecl SecPolicyCreateWithProperties(void * policyIdentifier, CFDictionaryRef properties);
extern "C" int __cdecl SecRandomCopyBytes(void * rnd, unsigned long count, System::Byte bytes);
extern "C" unsigned long __cdecl SecTrustGetTypeID(void);
extern "C" int __cdecl SecTrustCreateWithCertificates(void * certificates, void * policies, void * trust);
extern "C" int __cdecl SecTrustSetPolicies(void * trust, void * policies);
extern "C" int __cdecl SecTrustCopyPolicies(void * trust, CFArrayRef policies);
extern "C" int __cdecl SecTrustSetNetworkFetchAllowed(void * trust, bool allowFetch);
extern "C" int __cdecl SecTrustGetNetworkFetchAllowed(void * trust, bool allowFetch);
extern "C" int __cdecl SecTrustSetAnchorCertificates(void * trust, CFArrayRef anchorCertificates);
extern "C" int __cdecl SecTrustSetAnchorCertificatesOnly(void * trust, bool anchorCertificatesOnly);
extern "C" int __cdecl SecTrustCopyCustomAnchorCertificates(void * trust, CFArrayRef anchors);
extern "C" int __cdecl SecTrustSetVerifyDate(void * trust, CFDateRef verifyDate);
extern "C" double __cdecl SecTrustGetVerifyTime(void * trust);
extern "C" int __cdecl SecTrustEvaluate(void * trust, unsigned long result);
extern "C" int __cdecl SecTrustEvaluateAsync(void * trust, NativeInt queue, SecTrustCallback result);
extern "C" int __cdecl SecTrustGetTrustResult(void * trust, unsigned long result);
extern "C" void * __cdecl SecTrustCopyPublicKey(void * trust);
extern "C" long __cdecl SecTrustGetCertificateCount(void * trust);
extern "C" void * __cdecl SecTrustGetCertificateAtIndex(void * trust, long ix);
extern "C" CFDataRef __cdecl SecTrustCopyExceptions(void * trust);
extern "C" int __cdecl SecTrustSetExceptions(void * trust, CFDataRef exceptions);
extern "C" CFArrayRef __cdecl SecTrustCopyProperties(void * trust);
extern "C" CFDictionaryRef __cdecl SecTrustCopyResult(void * trust);
extern "C" int __cdecl SecTrustSetOCSPResponse(void * trust, void * responseData);
extern "C" unsigned long __cdecl SSLContextGetTypeID(void);
extern "C" void * __cdecl SSLCreateContext(CFAllocatorRef alloc, unsigned long protocolSide, unsigned long connectionType);
extern "C" int __cdecl SSLGetSessionState(void * context, unsigned long state);
extern "C" int __cdecl SSLSetSessionOption(void * context, unsigned long option, bool value);
extern "C" int __cdecl SSLGetSessionOption(void * context, unsigned long option, bool value);
extern "C" int __cdecl SSLSetIOFuncs(void * context, SSLReadFunc readFunc, SSLWriteFunc writeFunc);
extern "C" int __cdecl SSLSetProtocolVersionMin(void * context, unsigned long minVersion);
extern "C" int __cdecl SSLGetProtocolVersionMin(void * context, unsigned long minVersion);
extern "C" int __cdecl SSLSetProtocolVersionMax(void * context, unsigned long maxVersion);
extern "C" int __cdecl SSLGetProtocolVersionMax(void * context, unsigned long maxVersion);
extern "C" int __cdecl SSLSetCertificate(void * context, CFArrayRef certRefs);
extern "C" int __cdecl SSLSetConnection(void * context, void * connection);
extern "C" int __cdecl SSLGetConnection(void * context, void * connection);
extern "C" int __cdecl SSLSetPeerDomainName(void * context, char * peerName, unsigned long peerNameLen);
extern "C" int __cdecl SSLGetPeerDomainNameLength(void * context, unsigned long peerNameLen);
extern "C" int __cdecl SSLGetPeerDomainName(void * context, char * peerName, unsigned long peerNameLen);
extern "C" int __cdecl SSLSetDatagramHelloCookie(void * dtlsContext, void * cookie, unsigned long cookieLen);
extern "C" int __cdecl SSLSetMaxDatagramRecordSize(void * dtlsContext, unsigned long maxSize);
extern "C" int __cdecl SSLGetMaxDatagramRecordSize(void * dtlsContext, unsigned long maxSize);
extern "C" int __cdecl SSLGetNegotiatedProtocolVersion(void * context, unsigned long protocol);
extern "C" int __cdecl SSLGetNumberSupportedCiphers(void * context, unsigned long numCiphers);
extern "C" int __cdecl SSLGetSupportedCiphers(void * context, System::Word ciphers, unsigned long numCiphers);
extern "C" int __cdecl SSLSetEnabledCiphers(void * context, System::Word ciphers, unsigned long numCiphers);
extern "C" int __cdecl SSLGetNumberEnabledCiphers(void * context, unsigned long numCiphers);
extern "C" int __cdecl SSLGetEnabledCiphers(void * context, System::Word ciphers, unsigned long numCiphers);
extern "C" int __cdecl SSLCopyPeerTrust(void * context, void * trust);
extern "C" int __cdecl SSLSetPeerID(void * context, void * peerID, unsigned long peerIDLen);
extern "C" int __cdecl SSLGetPeerID(void * context, void * peerID, unsigned long peerIDLen);
extern "C" int __cdecl SSLGetNegotiatedCipher(void * context, System::Word cipherSuite);
extern "C" int __cdecl SSLSetEncryptionCertificate(void * context, CFArrayRef certRefs);
extern "C" int __cdecl SSLSetClientSideAuthenticate(void * context, unsigned long auth);
extern "C" int __cdecl SSLAddDistinguishedName(void * context, void * derDN, unsigned long derDNLen);
extern "C" int __cdecl SSLCopyDistinguishedNames(void * context, CFArrayRef names);
extern "C" int __cdecl SSLGetClientCertificateState(void * context, unsigned long clientState);
extern "C" int __cdecl SSLHandshake(void * context);
extern "C" int __cdecl SSLWrite(void * context, void * data, unsigned long dataLength, unsigned long processed);
extern "C" int __cdecl SSLRead(void * context, void * data, unsigned long dataLength, unsigned long processed);
extern "C" int __cdecl SSLGetBufferedReadSize(void * context, unsigned long bufSize);
extern "C" int __cdecl SSLGetDatagramWriteSize(void * dtlsContext, unsigned long bufSize);
extern "C" int __cdecl SSLClose(void * context);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecImportExportPassphrase(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecImportItemLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecImportItemKeyID(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecImportItemTrust(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecImportItemCertChain(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecImportItemIdentity(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecClass(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecClassInternetPassword(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecClassGenericPassword(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecClassCertificate(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecClassKey(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecClassIdentity(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchPolicy(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchItemList(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchSearchList(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchIssuers(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchEmailAddressIfPresent(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchSubjectContains(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchCaseInsensitive(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchTrustedOnly(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchValidOnDate(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchLimit(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchLimitOne(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecMatchLimitAll(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecReturnData(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecReturnAttributes(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecReturnRef(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecReturnPersistentRef(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessible(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessControl(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessGroup(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrSynchronizable(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrSynchronizableAny(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCreationDate(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrModificationDate(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrDescription(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrComment(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCreator(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrIsInvisible(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrIsNegative(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccount(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrService(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrGeneric(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrSecurityDomain(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrServer(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocol(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrPort(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrPath(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrSubject(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrIssuer(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrSerialNumber(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrSubjectKeyID(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrPublicKeyHash(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCertificateType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCertificateEncoding(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyClass(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrApplicationLabel(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrIsPermanent(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrApplicationTag(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyType(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeySizeInBits(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrEffectiveKeySize(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanEncrypt(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanDecrypt(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanDerive(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanSign(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanVerify(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanWrap(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrCanUnwrap(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleWhenUnlocked(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleAfterFirstUnlock(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleAlways(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleWhenPasscodeSetThisDeviceOnly(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleWhenUnlockedThisDeviceOnly(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAccessibleAlwaysThisDeviceOnly(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolFTP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolFTPAccount(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolHTTP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolIRC(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolNNTP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolPOP3(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolSMTP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolSOCKS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolIMAP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolLDAP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolAppleTalk(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolAFP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolTelnet(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolSSH(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolFTPS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolHTTPS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolHTTPProxy(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolHTTPSProxy(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolFTPProxy(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolSMB(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolRTSP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolRTSPProxy(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolDAAP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolEPPC(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolIPP(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolNNTPS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolLDAPS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolTelnetS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolIMAPS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolIRCS(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrProtocolPOP3S(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeNTLM(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeMSN(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeDPA(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeRPA(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeHTTPBasic(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeHTTPDigest(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeHTMLForm(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrAuthenticationTypeDefault(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyClassPublic(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyClassPrivate(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyClassSymmetric(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyTypeRSA(void);
extern DELPHI_PACKAGE Iosapi::Foundation::_di_NSString __fastcall kSecAttrKeyTypeEC(void);
}	/* namespace Security */
}	/* namespace Iosapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI_SECURITY)
using namespace Iosapi::Security;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_IOSAPI)
using namespace Iosapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Iosapi_SecurityHPP
