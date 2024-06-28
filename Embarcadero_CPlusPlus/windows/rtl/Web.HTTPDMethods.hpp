// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPDMethods.pas' rev: 34.00 (Windows)

#ifndef Web_HttpdmethodsHPP
#define Web_HttpdmethodsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Httpdmethods
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THTTPDMethods;
class DELPHICLASS EHTTPMethodsError;
class DELPHICLASS THTTPDInit;
//-- type declarations -------------------------------------------------------
typedef void *PHTTPDPool;

typedef void *PHTTPDRequest;

typedef void *PHTTPDServer_rec;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THTTPDMethods : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef int __cdecl (*THandlerProc)(const PHTTPDRequest p);
	
	typedef void __cdecl (*TInitiationProc)(const PHTTPDPool p, const PHTTPDServer_rec s);
	
	typedef int __cdecl (*TTerminationFunc)(const void * p);
	
	
public:
	__classmethod int __fastcall get_AP_OK();
	__classmethod int __fastcall get_AP_DONE();
	__classmethod int __fastcall get_AP_DECLINED();
	__classmethod int __fastcall get_APR_HOOK_REALLY_FIRST();
	__classmethod int __fastcall get_APR_HOOK_FIRST();
	__classmethod int __fastcall get_APR_HOOK_MIDDLE();
	__classmethod int __fastcall get_APR_HOOK_LAST();
	__classmethod int __fastcall get_APR_HOOK_REALLY_LAST();
	__classmethod void __fastcall hook_handler(const THandlerProc AHandler, const System::PPWideChar APre, const System::PPWideChar ASucc, int AOrder);
	__classmethod void __fastcall hook_child_init(const TInitiationProc AInitiation, const System::PPWideChar APre, const System::PPWideChar ASucc, int AOrder);
	__classmethod void __fastcall pool_cleanup_register(const PHTTPDPool p, const void * data, TTerminationFunc APlainTermination, TTerminationFunc AChildTermination);
	__classmethod System::UTF8String __fastcall server_root_relative(const PHTTPDRequest ARequestRec, const System::UTF8String AURI);
	__classmethod System::UTF8String __fastcall get_handler(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_method(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_ContentType(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_protocol(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_unparsed_uri(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_args(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_path_info(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_filename(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_Accept(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_From(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_hostname(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_Referer(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_UserAgent(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_content_encoding(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_ContentType(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_ContentLength(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_Title(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_ServerPort(const PHTTPDRequest ARequestRec);
#ifndef _WIN64
	__classmethod System::DynamicArray<System::Byte> __fastcall get_Content(const PHTTPDRequest ARequestRec);
#else /* _WIN64 */
	__classmethod System::TArray__1<System::Byte> __fastcall get_Content(const PHTTPDRequest ARequestRec);
#endif /* _WIN64 */
	__classmethod int __fastcall get_client_block(const PHTTPDRequest ARequestRec, System::PByte Buffer, int Count);
	__classmethod System::UTF8String __fastcall get_Field(const PHTTPDRequest ARequestRec, const System::UTF8String AName);
	__classmethod System::UTF8String __fastcall get_connection_ClientIP(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_connection_RemoteHost(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_Connection(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_Cookie(const PHTTPDRequest ARequestRec);
	__classmethod System::UTF8String __fastcall get_headers_in_Authorization(const PHTTPDRequest ARequestRec);
	__classmethod void __fastcall set_status(const PHTTPDRequest ARequestRec, int ACode);
	__classmethod void __fastcall add_headers_out(const PHTTPDRequest ARequestRec, const System::UTF8String Key, const System::UTF8String Value);
	__classmethod void __fastcall set_headers_out(const PHTTPDRequest ARequestRec, const System::UTF8String Key, const System::UTF8String Value);
	__classmethod void __fastcall set_headers_out_ContentType(const PHTTPDRequest ARequestRec, const System::UTF8String AType);
	__classmethod void __fastcall set_headers_out_ContentEncoding(const PHTTPDRequest ARequestRec, const System::UTF8String AValue);
	__classmethod void __fastcall set_ContentType(const PHTTPDRequest ARequestRec, const System::UTF8String AValue);
	__classmethod void __fastcall set_headers_out_ContentLength(const PHTTPDRequest ARequestRec, int AValue);
	__classmethod void __fastcall set_location(const PHTTPDRequest ARequestRec, const System::UTF8String AValue);
	__classmethod int __fastcall write_buffer(const PHTTPDRequest ARequestRec, void *Buffer, int Count);
	__classmethod int __fastcall write_string(const PHTTPDRequest ARequestRec, const System::UTF8String AValue);
public:
	/* TObject.Create */ inline __fastcall THTTPDMethods() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~THTTPDMethods() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EHTTPMethodsError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EHTTPMethodsError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EHTTPMethodsError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EHTTPMethodsError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EHTTPMethodsError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EHTTPMethodsError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EHTTPMethodsError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EHTTPMethodsError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EHTTPMethodsError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHTTPMethodsError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EHTTPMethodsError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHTTPMethodsError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EHTTPMethodsError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EHTTPMethodsError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION THTTPDInit : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	typedef void __fastcall (*TRegisterHooksProc)(const PHTTPDPool p);
	
	typedef System::PByte TModuleData;
	
	
private:
	static TRegisterHooksProc FRegisterHooksProc;
	static System::Byte *FModuleData;
	static System::UTF8String FHandlerName;
	static System::UTF8String FModuleName;
	static TRegisterHooksProc FRegisterCustomHooksProc;
	static char * __fastcall GetModuleName();
	
public:
	__classmethod void __fastcall InitModule(const TRegisterHooksProc ARegisterHooksProc, const System::PByte AModuleData, const System::UTF8String AHandlerName);
	/* static */ __property TRegisterHooksProc RegisterHooksProc = {read=FRegisterHooksProc};
	/* static */ __property TRegisterHooksProc RegisterCustomHooksProc = {read=FRegisterCustomHooksProc, write=FRegisterCustomHooksProc};
	/* static */ __property System::PByte ModuleData = {read=FModuleData};
	/* static */ __property System::UTF8String HandlerName = {read=FHandlerName};
	/* static */ __property char * ModuleName = {read=GetModuleName};
	
private:
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall THTTPDInit() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~THTTPDInit() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Httpdmethods */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPDMETHODS)
using namespace Web::Httpdmethods;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_HttpdmethodsHPP
