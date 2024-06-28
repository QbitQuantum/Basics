// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.ReqMulti.pas' rev: 34.00 (Windows)

#ifndef Web_ReqmultiHPP
#define Web_ReqmultiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Masks.hpp>
#include <System.Generics.Collections.hpp>
#include <Web.HTTPApp.hpp>
#include <Web.ReqFiles.hpp>
#include <Web.HTTPParse.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Reqmulti
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultipartContentParser;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMultipartContentParser : public Web::Httpapp::TAbstractContentParser
{
	typedef Web::Httpapp::TAbstractContentParser inherited;
	
private:
	System::Classes::TStrings* FContentFields;
	Web::Reqfiles::TWebRequestFiles* FFiles;
#ifndef _WIN64
	System::DynamicArray<System::Byte> FContentBuffer;
#else /* _WIN64 */
	System::TArray__1<System::Byte> FContentBuffer;
#endif /* _WIN64 */
	
protected:
	virtual System::Classes::TStrings* __fastcall GetContentFields();
	virtual Web::Httpapp::TAbstractWebRequestFiles* __fastcall GetFiles();
	void __fastcall ExtractContentTypeFields(System::Classes::TStrings* Strings);
	void __fastcall ParseMultiPartContent();
	void __fastcall ParseMultiPart(System::PByte APart, int ASize);
	void __fastcall BufferContent();
	void __fastcall ParseMultipartHeaders(Web::Httpparse::THTTPParser* Parser, System::PByte AContent, int AContentLength);
	void __fastcall ExtractMultipartContentFields();
	
public:
	__fastcall virtual ~TMultipartContentParser();
	__classmethod virtual bool __fastcall CanParse(Web::Httpapp::TWebRequest* AWebRequest);
public:
	/* TAbstractContentParser.Create */ inline __fastcall virtual TMultipartContentParser(Web::Httpapp::TWebRequest* AWebRequest) : Web::Httpapp::TAbstractContentParser(AWebRequest) { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Reqmulti */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_REQMULTI)
using namespace Web::Reqmulti;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_ReqmultiHPP
