// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Net.FileClient.pas' rev: 34.00 (Windows)

#ifndef System_Net_FileclientHPP
#define System_Net_FileclientHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>
#include <System.Net.URLClient.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Net
{
namespace Fileclient
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFileRequest;
class DELPHICLASS TFileResponse;
class DELPHICLASS TFileClient;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TFileRequest : public System::Net::Urlclient::TURLRequest
{
	typedef System::Net::Urlclient::TURLRequest inherited;
	
protected:
	/* TURLRequest.Create */ inline __fastcall TFileRequest(System::Net::Urlclient::TURLClient* const AClient, const System::UnicodeString AMethodString, const System::Net::Urlclient::TURI &AURI) : System::Net::Urlclient::TURLRequest(AClient, AMethodString, AURI) { }
	
public:
	/* TURLRequest.Destroy */ inline __fastcall virtual ~TFileRequest() { }
	
private:
	void *__IURLRequest;	// System::Net::Urlclient::IURLRequest 
	
public:
	operator System::Net::Urlclient::IURLRequest*(void) { return (System::Net::Urlclient::IURLRequest*)&__IURLRequest; }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TFileResponse : public System::Net::Urlclient::TURLResponse
{
	typedef System::Net::Urlclient::TURLResponse inherited;
	
protected:
	__fastcall TFileResponse(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AAsyncCallback, const System::Classes::TAsyncProcedureEvent AAsyncCallbackEvent, const System::Net::Urlclient::_di_IURLRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */;
	virtual System::Classes::TStream* __fastcall DoCreateInternalStream();
	virtual bool __fastcall DoCancel();
	
public:
#ifndef _WIN64
	virtual System::DynamicArray<System::Net::Urlclient::TNameValuePair> __fastcall GetHeaders();
#else /* _WIN64 */
	virtual System::TArray__1<System::Net::Urlclient::TNameValuePair> __fastcall GetHeaders();
#endif /* _WIN64 */
	virtual System::UnicodeString __fastcall GetMimeType();
	virtual System::UnicodeString __fastcall ContentAsString(System::Sysutils::TEncoding* const AnEncoding = (System::Sysutils::TEncoding*)(0x0));
protected:
	/* TURLResponse.Create */ inline __fastcall TFileResponse(System::TObject* const AContext, const System::Net::Urlclient::_di_IURLRequest ARequest, System::Classes::TStream* const AContentStream)/* overload */ : System::Net::Urlclient::TURLResponse(AContext, ARequest, AContentStream) { }
	
public:
	/* TURLResponse.Destroy */ inline __fastcall virtual ~TFileResponse() { }
	
protected:
	/* TBaseAsyncResult.Create */ inline __fastcall TFileResponse(System::TObject* const AContext)/* overload */ : System::Net::Urlclient::TURLResponse(AContext) { }
	
public:
	/* TBaseAsyncResult.Create */ inline __fastcall TFileResponse()/* overload */ : System::Net::Urlclient::TURLResponse() { }
	
private:
	void *__IURLResponse;	// System::Net::Urlclient::IURLResponse 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {5D687C75-5C36-4302-B0AB-989DDB7558FE}
	operator System::Net::Urlclient::_di_IURLResponse()
	{
		System::Net::Urlclient::_di_IURLResponse intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator System::Net::Urlclient::IURLResponse*(void) { return (System::Net::Urlclient::IURLResponse*)&__IURLResponse; }
	#endif
	
};


class PASCALIMPLEMENTATION TFileClient : public System::Net::Urlclient::TURLClient
{
	typedef System::Net::Urlclient::TURLClient inherited;
	
protected:
	virtual System::Types::_di_IAsyncResult __fastcall DoGetResponseInstance(System::TObject* const AContext, const System::Sysutils::_di_TProc AProc, const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::Net::Urlclient::_di_IURLRequest ARequest, System::Classes::TStream* const AContentStream);
	virtual System::Net::Urlclient::_di_IURLRequest __fastcall DoGetRequestInstance(const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI);
#ifndef _WIN64
	virtual System::Types::_di_IAsyncResult __fastcall DoExecuteAsync(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::DynamicArray<System::Net::Urlclient::TNameValuePair> AHeaders, bool AOwnsSourceStream);
#else /* _WIN64 */
	virtual System::Types::_di_IAsyncResult __fastcall DoExecuteAsync(const System::Classes::_di_TAsyncCallback AsyncCallback, const System::Classes::TAsyncProcedureEvent AsyncCallbackEvent, const System::UnicodeString ARequestMethod, const System::Net::Urlclient::TURI &AURI, System::Classes::TStream* const ASourceStream, System::Classes::TStream* const AContentStream, const System::TArray__1<System::Net::Urlclient::TNameValuePair> AHeaders, bool AOwnsSourceStream);
#endif /* _WIN64 */
	
public:
	__classmethod virtual System::Net::Urlclient::TURLClient* __fastcall CreateInstance();
public:
	/* TURLClient.Create */ inline __fastcall TFileClient() : System::Net::Urlclient::TURLClient() { }
	/* TURLClient.Destroy */ inline __fastcall virtual ~TFileClient() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Fileclient */
}	/* namespace Net */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET_FILECLIENT)
using namespace System::Net::Fileclient;
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
#endif	// System_Net_FileclientHPP
