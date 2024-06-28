// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPD24Impl.pas' rev: 34.00 (Windows)

#ifndef Web_Httpd24implHPP
#define Web_Httpd24implHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Web.HTTPD24.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Httpd24impl
{
//-- forward type declarations -----------------------------------------------
struct TApacheModuleData;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TApacheModuleData
{
public:
#ifndef _WIN64
	System::StaticArray<System::Byte, 57> FBytes;
#else /* _WIN64 */
	System::StaticArray<System::Byte, 105> FBytes;
#endif /* _WIN64 */
};


//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE void __fastcall RegisterHTTPD24();
}	/* namespace Httpd24impl */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPD24IMPL)
using namespace Web::Httpd24impl;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_Httpd24implHPP
