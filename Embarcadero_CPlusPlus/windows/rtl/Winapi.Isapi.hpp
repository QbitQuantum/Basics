// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Winapi.Isapi.pas' rev: 34.00 (Windows)

#ifndef Winapi_IsapiHPP
#define Winapi_IsapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Winapi.Windows.hpp>

//-- user supplied -----------------------------------------------------------
#include <httpext.h>

namespace Winapi
{
namespace Isapi
{
//-- forward type declarations -----------------------------------------------
struct TEXTENSION_CONTROL_BLOCK;
//-- type declarations -------------------------------------------------------
typedef HSE_VERSION_INFO *PHSE_VERSION_INFO;

typedef HSE_VERSION_INFO THSE_VERSION_INFO;

typedef System::LongBool __stdcall (*TGetServerVariableProc)(NativeUInt hConn, char * VariableName, void * Buffer, unsigned &Size);

typedef System::LongBool __stdcall (*TWriteClientProc)(NativeUInt ConnID, void * Buffer, unsigned &Bytes, unsigned dwReserved);

typedef System::LongBool __stdcall (*TReadClientProc)(NativeUInt ConnID, void * Buffer, unsigned &Size);

typedef System::LongBool __stdcall (*TServerSupportFunctionProc)(NativeUInt hConn, unsigned HSERRequest, void * Buffer, unsigned &Size, unsigned &DataType);

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


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Isapi */
}	/* namespace Winapi */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI_ISAPI)
using namespace Winapi::Isapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WINAPI)
using namespace Winapi;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Winapi_IsapiHPP
