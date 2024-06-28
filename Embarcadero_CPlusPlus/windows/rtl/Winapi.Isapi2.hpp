// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Isapi2.pas' rev: 34.00 (Windows)

#ifndef Winapi_Isapi2HPP
#define Winapi_Isapi2HPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <httpfilt.h>

namespace Winapi
{
namespace Isapi2
{
//-- forward type declarations -----------------------------------------------
struct HSE_VERSION_INFO;
struct TEXTENSION_CONTROL_BLOCK;
struct THSE_TF_INFO;
struct THTTP_FILTER_CONTEXT;
struct THTTP_FILTER_PREPROC_HEADERS;
//-- type declarations -------------------------------------------------------
typedef HSE_VERSION_INFO *PHSE_VERSION_INFO;

struct DECLSPEC_DRECORD HSE_VERSION_INFO
{
public:
	unsigned dwExtensionVersion;
	System::StaticArray<char, 256> lpszExtensionDesc;
};


typedef HSE_VERSION_INFO THSE_VERSION_INFO;

typedef System::LongBool __stdcall (*TGetServerVariableProc)(NativeUInt hConn, char * VariableName, void * Buffer, unsigned &Size);

typedef System::LongBool __stdcall (*TWriteClientProc)(NativeUInt ConnID, void * Buffer, unsigned &Bytes, unsigned dwReserved);

typedef System::LongBool __stdcall (*TReadClientProc)(NativeUInt ConnID, void * Buffer, unsigned &Size);

typedef System::LongBool __stdcall (*TServerSupportFunctionProc)(NativeUInt hConn, unsigned HSERRequest, void * Buffer, unsigned* Size, unsigned* DataType);

typedef TEXTENSION_CONTROL_BLOCK *PEXTENSION_CONTROL_BLOCK;

struct DECLSPEC_DRECORD TEXTENSION_CONTROL_BLOCK
{
public:
	unsigned cbSize;
	unsigned dwVersion;
	NativeUInt ConnID;
	unsigned dwHttpStatusCode;
	System::StaticArray<char, 80> lpszLogData;
	char *lpszMethod;
	char *lpszQueryString;
	char *lpszPathInfo;
	char *lpszPathTranslated;
	unsigned cbTotalBytes;
	unsigned cbAvailable;
	void *lpbData;
	char *lpszContentType;
	TGetServerVariableProc GetServerVariable;
	TWriteClientProc WriteClient;
	TReadClientProc ReadClient;
	TServerSupportFunctionProc ServerSupportFunction;
};


typedef System::LongBool __stdcall (*TGetExtensionVersion)(HSE_VERSION_INFO &Ver);

typedef unsigned __stdcall (*THttpExtensionProc)(TEXTENSION_CONTROL_BLOCK &ECB);

typedef System::LongBool __stdcall (*TTerminateExtension)(unsigned dwFlags);

typedef void __stdcall (*THseIoCompletion)(TEXTENSION_CONTROL_BLOCK &ECB, void * pContext, unsigned cbIO, unsigned dwError);

typedef THSE_TF_INFO *PHSE_TF_INFO;

struct DECLSPEC_DRECORD THSE_TF_INFO
{
public:
	THseIoCompletion pfnHseIO;
	void *pContext;
	NativeUInt hFile;
	char *pszStatusCode;
	unsigned BytesToWrite;
	unsigned Offset;
	void *pHead;
	unsigned HeadLength;
	void *pTail;
	unsigned TailLength;
	unsigned dwFlags;
};


typedef System::LongBool __stdcall (*TFilterGetServerVariableProc)(void *pfc, char * VariableName, void * Buffer, unsigned &Size);

typedef System::LongBool __stdcall (*TFilterAddResponseHeadersProc)(void *pfc, char * lpszHeaders, unsigned dwReserved);

typedef System::LongBool __stdcall (*TFilterWriteClientProc)(void *pfc, void * Buffer, unsigned &Bytes, unsigned dwReserved);

typedef void * __stdcall (*TFilterAllocMemProc)(void *pfc, unsigned cbSize, unsigned dwReserved);

typedef System::LongBool __stdcall (*TFilterServerSupportFunctionProc)(void *pfc, unsigned sfReq, void * pData, unsigned ul1, unsigned ul2);

typedef THTTP_FILTER_CONTEXT *PHTTP_FILTER_CONTEXT;

struct DECLSPEC_DRECORD THTTP_FILTER_CONTEXT
{
public:
	unsigned cbSize;
	unsigned Revision;
	void *ServerContext;
	unsigned ulReserved;
	System::LongBool fIsSecurePort;
	void *pFilterContext;
	TFilterGetServerVariableProc GetServerVariable;
	TFilterAddResponseHeadersProc AddResponseHeaders;
	TFilterWriteClientProc WriteClient;
	TFilterAllocMemProc AllocMem;
	TFilterServerSupportFunctionProc ServerSupportFunction;
};


typedef HTTP_FILTER_RAW_DATA *PHTTP_FILTER_RAW_DATA;

typedef HTTP_FILTER_RAW_DATA THTTP_FILTER_RAW_DATA;

typedef System::LongBool __stdcall (*TGetHeaderProc)(THTTP_FILTER_CONTEXT &pfc, char * lpszName, void *lpvBuffer, unsigned &lpdwSize);

typedef System::LongBool __stdcall (*TSetHeaderProc)(THTTP_FILTER_CONTEXT &pfc, char * lpszName, char * lpszValue);

typedef System::LongBool __stdcall (*TAddHeaderProc)(THTTP_FILTER_CONTEXT &pfc, char * lpszName, char * lpszValue);

typedef THTTP_FILTER_PREPROC_HEADERS *PHTTP_FILTER_PREPROC_HEADERS;

struct DECLSPEC_DRECORD THTTP_FILTER_PREPROC_HEADERS
{
public:
	TGetHeaderProc GetHeader;
	TSetHeaderProc SetHeader;
	TAddHeaderProc AddHeader;
	unsigned HttpStatus;
	unsigned dwReserved;
};


typedef HTTP_FILTER_AUTHENT *PHTTP_FILTER_AUTHENT;

typedef HTTP_FILTER_AUTHENT THTTP_FILTER_AUTHENT;

typedef HTTP_FILTER_URL_MAP *PHTTP_FILTER_URL_MAP;

typedef HTTP_FILTER_URL_MAP THTTP_FILTER_URL_MAP;

typedef HTTP_FILTER_ACCESS_DENIED *PHTTP_FILTER_ACCESS_DENIED;

typedef HTTP_FILTER_ACCESS_DENIED THTTP_FILTER_ACCESS_DENIED;

typedef HTTP_FILTER_LOG *PHTTP_FILTER_LOG;

typedef HTTP_FILTER_LOG THTTP_FILTER_LOG;

typedef HTTP_FILTER_VERSION *PHTTP_FILTER_VERSION;

typedef HTTP_FILTER_VERSION THTTP_FILTER_VERSION;

typedef unsigned __stdcall (*THttpFilterProc)(THTTP_FILTER_CONTEXT &pfc, unsigned Notificationtype, void * pvNotification);

typedef System::LongBool __stdcall (*TGetFilterVersion)(HTTP_FILTER_VERSION &pVer);

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Isapi2 */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_ISAPI2)
using namespace Winapi::Isapi2;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_Isapi2HPP
