// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.WinHTTP.pas' rev: 34.00 (Windows)

#ifndef Winapi_WinhttpHPP
#define Winapi_WinhttpHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>
#include <Winapi.Winsock2.hpp>

//-- user supplied -----------------------------------------------------------

#include "winhttp.h"
#pragma comment(lib, "winhttp")


namespace Winapi
{
namespace Winhttp
{
//-- forward type declarations -----------------------------------------------
struct _URL_COMPONENTS;
//-- type declarations -------------------------------------------------------
typedef System::Word TInternetPort;

typedef System::Word *PInternetPort;

typedef WINHTTP_ASYNC_RESULT TWinHttpAsyncResult;

typedef WINHTTP_ASYNC_RESULT *PWinHttpAsyncResult;

typedef HTTP_VERSION_INFO THttpVersionInfo;

typedef HTTP_VERSION_INFO *PHttpVersionInfo;

typedef int TInternetScheme;

typedef int *PInternetScheme;

struct DECLSPEC_DRECORD _URL_COMPONENTS
{
public:
	unsigned dwStructSize;
	System::WideChar *lpszScheme;
	unsigned dwSchemeLength;
	int nScheme;
	System::WideChar *lpszHostName;
	unsigned dwHostNameLength;
	System::Word nPort;
	System::WideChar *lpszUserName;
	unsigned dwUserNameLength;
	System::WideChar *lpszPassword;
	unsigned dwPasswordLength;
	System::WideChar *lpszUrlPath;
	unsigned dwUrlPathLength;
	System::WideChar *lpszExtraInfo;
	unsigned dwExtraInfoLength;
};


typedef _URL_COMPONENTS TURLComponents;

typedef _URL_COMPONENTS *PURLComponents;

typedef _URL_COMPONENTS TURLComponentsW;

typedef _URL_COMPONENTS *PURLComponentsW;

typedef WINHTTP_PROXY_INFO *PWINHTTP_PROXY_INFO;

typedef WINHTTP_PROXY_INFO TWinHttpProxyInfo;

typedef WINHTTP_PROXY_INFO *PWinHttpProxyInfo;

typedef WINHTTP_PROXY_INFO TWinHttpProxyInfoW;

typedef WINHTTP_PROXY_INFO *PWinHttpProxyInfoW;

typedef WINHTTP_AUTOPROXY_OPTIONS *PWINHTTP_AUTOPROXY_OPTIONS;

typedef WINHTTP_AUTOPROXY_OPTIONS TWinHttpAutoProxyOptions;

typedef WINHTTP_AUTOPROXY_OPTIONS *PWinHttpAutoProxyOptions;

typedef WINHTTP_CERTIFICATE_INFO TWinHttpCertificateInfo;

typedef WINHTTP_CERTIFICATE_INFO *PWinHttpCertificateInfo;

typedef WINHTTP_CONNECTION_INFO TWinHttpConnectionInfo;

typedef WINHTTP_CONNECTION_INFO *PWinHttpConnectionInfo;

typedef WINHTTP_CREDS tagWINHTTP_CREDS;

typedef WINHTTP_CREDS TWinHttpCreds;

typedef WINHTTP_CREDS *PWinHttpCreds;

typedef WINHTTP_CREDS_EX tagWINHTTP_CREDS_EX;

typedef WINHTTP_CREDS_EX TWinHttpCredsEx;

typedef WINHTTP_CREDS_EX *PWinHttpCredsEx;

typedef WINHTTP_STATUS_CALLBACK TWinHttpStatusCallback;

typedef WINHTTP_STATUS_CALLBACK *PWinHttpStatusCallback;

typedef WINHTTP_CURRENT_USER_IE_PROXY_CONFIG *PWINHTTP_CURRENT_USER_IE_PROXY_CONFIG;

typedef WINHTTP_CURRENT_USER_IE_PROXY_CONFIG TWinHttpCurrentUserIEProxyConfig;

typedef WINHTTP_CURRENT_USER_IE_PROXY_CONFIG *PWinHttpCurrentUserIEProxyConfig;

//-- var, const, procedure ---------------------------------------------------
static const System::Word WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3 = System::Word(0x2000);
}	/* namespace Winhttp */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_WINHTTP)
using namespace Winapi::Winhttp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_WinhttpHPP
