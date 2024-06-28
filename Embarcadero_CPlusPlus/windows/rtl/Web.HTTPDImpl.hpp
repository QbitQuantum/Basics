// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPDImpl.pas' rev: 34.00 (Windows)

#ifndef Web_HttpdimplHPP
#define Web_HttpdimplHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Web.HTTPDMethods.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Httpdimpl
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TAbstractHTTPDMethods;
class DELPHICLASS TCommonHTTPDMethods;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TAbstractHTTPDMethods : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	virtual void __fastcall InitModule() = 0 ;
	virtual int __fastcall get_AP_OK() = 0 ;
	virtual int __fastcall get_AP_DONE() = 0 ;
	virtual int __fastcall get_AP_DECLINED() = 0 ;
	virtual int __fastcall get_APR_HOOK_REALLY_FIRST() = 0 ;
	virtual int __fastcall get_APR_HOOK_FIRST() = 0 ;
	virtual int __fastcall get_APR_HOOK_MIDDLE() = 0 ;
	virtual int __fastcall get_APR_HOOK_LAST() = 0 ;
	virtual int __fastcall get_APR_HOOK_REALLY_LAST() = 0 ;
	virtual System::UTF8String __fastcall server_root_relative(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AURI) = 0 ;
	virtual void __fastcall hook_handler(const Web::Httpdmethods::THTTPDMethods::THandlerProc AHandler, const System::PPWideChar APre, const System::PPWideChar ASucc, int AOrder) = 0 ;
	virtual void __fastcall hook_child_init(const Web::Httpdmethods::THTTPDMethods::TInitiationProc AInitiation, const System::PPWideChar APre, const System::PPWideChar ASucc, int AOrder) = 0 ;
	virtual void __fastcall pool_cleanup_register(const Web::Httpdmethods::PHTTPDPool p, const void * data, Web::Httpdmethods::THTTPDMethods::TTerminationFunc APlainTermination, Web::Httpdmethods::THTTPDMethods::TTerminationFunc AChildTermination) = 0 ;
	virtual System::UTF8String __fastcall get_handler(const Web::Httpdmethods::PHTTPDRequest ARequestRect) = 0 ;
	virtual System::UTF8String __fastcall get_method(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_ContentType(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_protocol(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_unparsed_uri(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_args(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_path_info(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_filename(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Field(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AKey) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Accept(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_From(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_hostname(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Referer(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_UserAgent(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_content_encoding(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_ContentType(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_ContentLength(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Title(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_ServerPort(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual int __fastcall get_client_block(const Web::Httpdmethods::PHTTPDRequest ARequestRec, System::PByte Buffer, int Count) = 0 ;
#ifndef _WIN64
	virtual System::DynamicArray<System::Byte> __fastcall get_Content(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
#else /* _WIN64 */
	virtual System::TArray__1<System::Byte> __fastcall get_Content(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
#endif /* _WIN64 */
	virtual System::UTF8String __fastcall get_connection_ClientIP(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_connection_RemoteHost(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Connection(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Cookie(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual System::UTF8String __fastcall get_headers_in_Authorization(const Web::Httpdmethods::PHTTPDRequest ARequestRec) = 0 ;
	virtual void __fastcall set_status(const Web::Httpdmethods::PHTTPDRequest ARequestRec, int ACode) = 0 ;
	virtual void __fastcall add_headers_out(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String Key, const System::UTF8String Value) = 0 ;
	virtual void __fastcall set_headers_out(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String Key, const System::UTF8String Value) = 0 ;
	virtual void __fastcall set_headers_out_ContentType(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AType) = 0 ;
	virtual void __fastcall set_headers_out_ContentEncoding(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AValue) = 0 ;
	virtual void __fastcall set_ContentType(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AValue) = 0 ;
	virtual void __fastcall set_headers_out_ContentLength(const Web::Httpdmethods::PHTTPDRequest ARequestRec, int AValue) = 0 ;
	virtual void __fastcall set_headers_out_Location(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AValue) = 0 ;
	virtual int __fastcall write_buffer(const Web::Httpdmethods::PHTTPDRequest ARequestRec, void *Buffer, int Count) = 0 ;
	virtual int __fastcall write_string(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AValue) = 0 ;
public:
	/* TObject.Create */ inline __fastcall TAbstractHTTPDMethods() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TAbstractHTTPDMethods() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TCommonHTTPDMethods : public TAbstractHTTPDMethods
{
	typedef TAbstractHTTPDMethods inherited;
	
public:
	#define TCommonHTTPDMethods_cUserAgent L"User-Agent"
	
	#define TCommonHTTPDMethods_cContentType L"Content-Type"
	
	#define TCommonHTTPDMethods_cAccept L"Accept"
	
	#define TCommonHTTPDMethods_cCookie L"Cookie"
	
	#define TCommonHTTPDMethods_cAuthorization L"Authorization"
	
	#define TCommonHTTPDMethods_cFrom L"From"
	
	#define TCommonHTTPDMethods_cReferer L"Referer"
	
	#define TCommonHTTPDMethods_cTitle L"Title"
	
	#define TCommonHTTPDMethods_cConnection L"Connection"
	
	#define TCommonHTTPDMethods_cContentLength L"Content-Length"
	
	#define TCommonHTTPDMethods_cLocation L"Location"
	
	static const System::Int8 cAP_OK = System::Int8(0x0);
	
	static const System::Int8 cAP_DONE = System::Int8(-2);
	
	static const System::Int8 cAP_DECLINED = System::Int8(-1);
	
	static const System::Int8 cAPR_HOOK_REALLY_FIRST = System::Int8(-10);
	
	static const System::Int8 cAPR_HOOK_FIRST = System::Int8(0x0);
	
	static const System::Int8 cAPR_HOOK_MIDDLE = System::Int8(0xa);
	
	static const System::Int8 cAPR_HOOK_LAST = System::Int8(0x14);
	
	static const System::Int8 cAPR_HOOK_REALLY_LAST = System::Int8(0x1e);
	
	
protected:
	virtual System::UTF8String __fastcall get_headers_in(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AKey) = 0 ;
	
public:
	virtual int __fastcall get_AP_OK();
	virtual int __fastcall get_AP_DONE();
	virtual int __fastcall get_AP_DECLINED();
	virtual int __fastcall get_APR_HOOK_REALLY_FIRST();
	virtual int __fastcall get_APR_HOOK_FIRST();
	virtual int __fastcall get_APR_HOOK_MIDDLE();
	virtual int __fastcall get_APR_HOOK_LAST();
	virtual int __fastcall get_APR_HOOK_REALLY_LAST();
	virtual System::UTF8String __fastcall get_headers_in_Accept(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_Field(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AKey);
	virtual System::UTF8String __fastcall get_headers_in_Connection(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_ContentLength(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_ContentType(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_Cookie(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_Authorization(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_From(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_Referer(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_Title(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual System::UTF8String __fastcall get_headers_in_UserAgent(const Web::Httpdmethods::PHTTPDRequest ARequestRec);
	virtual void __fastcall set_headers_out_ContentLength(const Web::Httpdmethods::PHTTPDRequest ARequestRec, int AValue);
	virtual void __fastcall set_headers_out_Location(const Web::Httpdmethods::PHTTPDRequest ARequestRec, const System::UTF8String AValue);
public:
	/* TObject.Create */ inline __fastcall TCommonHTTPDMethods() : TAbstractHTTPDMethods() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TCommonHTTPDMethods() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TAbstractHTTPDMethods* GHTTPDImpl;
extern DELPHI_PACKAGE void __fastcall RegisterHTTPD(TAbstractHTTPDMethods* const AHTTPDImpl);
}	/* namespace Httpdimpl */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPDIMPL)
using namespace Web::Httpdimpl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_HttpdimplHPP
