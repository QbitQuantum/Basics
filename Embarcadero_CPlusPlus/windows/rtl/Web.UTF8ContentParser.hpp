// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.UTF8ContentParser.pas' rev: 34.00 (Windows)

#ifndef Web_Utf8contentparserHPP
#define Web_Utf8contentparserHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Web.HTTPApp.hpp>

//-- user supplied -----------------------------------------------------------
#pragma link "Web.UTF8ContentParser"

namespace Web
{
namespace Utf8contentparser
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TUTF8ContentParser;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUTF8ContentParser : public Web::Httpapp::TContentParser
{
	typedef Web::Httpapp::TContentParser inherited;
	
public:
	/* TContentParser.Destroy */ inline __fastcall virtual ~TUTF8ContentParser() { }
	
public:
	/* TAbstractContentParser.Create */ inline __fastcall virtual TUTF8ContentParser(Web::Httpapp::TWebRequest* AWebRequest) : Web::Httpapp::TContentParser(AWebRequest) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Utf8contentparser */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_UTF8CONTENTPARSER)
using namespace Web::Utf8contentparser;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_Utf8contentparserHPP
