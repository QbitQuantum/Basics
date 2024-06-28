// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Backend.Exception.pas' rev: 34.00 (Windows)

#ifndef Rest_Backend_ExceptionHPP
#define Rest_Backend_ExceptionHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Backend
{
namespace Exception
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS EBackendError;
class DELPHICLASS EBackendServiceError;
class DELPHICLASS EBackendProviderError;
class DELPHICLASS EBackendAPIError;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBackendError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBackendError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBackendError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBackendError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBackendError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBackendError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBackendError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBackendError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBackendServiceError : public EBackendError
{
	typedef EBackendError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBackendServiceError(const System::UnicodeString Msg) : EBackendError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBackendServiceError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBackendError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBackendServiceError(NativeUInt Ident)/* overload */ : EBackendError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBackendServiceError(System::PResStringRec ResStringRec)/* overload */ : EBackendError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendServiceError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBackendError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendServiceError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBackendError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBackendServiceError(const System::UnicodeString Msg, int AHelpContext) : EBackendError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBackendServiceError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBackendError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendServiceError(NativeUInt Ident, int AHelpContext)/* overload */ : EBackendError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendServiceError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBackendError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendServiceError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBackendError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendServiceError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBackendError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBackendServiceError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBackendProviderError : public EBackendError
{
	typedef EBackendError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBackendProviderError(const System::UnicodeString Msg) : EBackendError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBackendProviderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBackendError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBackendProviderError(NativeUInt Ident)/* overload */ : EBackendError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBackendProviderError(System::PResStringRec ResStringRec)/* overload */ : EBackendError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendProviderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBackendError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendProviderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBackendError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBackendProviderError(const System::UnicodeString Msg, int AHelpContext) : EBackendError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBackendProviderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBackendError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendProviderError(NativeUInt Ident, int AHelpContext)/* overload */ : EBackendError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendProviderError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBackendError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendProviderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBackendError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendProviderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBackendError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBackendProviderError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION EBackendAPIError : public EBackendError
{
	typedef EBackendError inherited;
	
public:
	/* Exception.Create */ inline __fastcall EBackendAPIError(const System::UnicodeString Msg) : EBackendError(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EBackendAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : EBackendError(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EBackendAPIError(NativeUInt Ident)/* overload */ : EBackendError(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EBackendAPIError(System::PResStringRec ResStringRec)/* overload */ : EBackendError(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : EBackendError(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EBackendAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : EBackendError(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EBackendAPIError(const System::UnicodeString Msg, int AHelpContext) : EBackendError(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EBackendAPIError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : EBackendError(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendAPIError(NativeUInt Ident, int AHelpContext)/* overload */ : EBackendError(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EBackendAPIError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : EBackendError(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendAPIError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBackendError(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EBackendAPIError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : EBackendError(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EBackendAPIError() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Exception */
}	/* namespace Backend */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND_EXCEPTION)
using namespace Rest::Backend::Exception;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_BACKEND)
using namespace Rest::Backend;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Backend_ExceptionHPP
