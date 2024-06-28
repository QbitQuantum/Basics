// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.HTTPParse.pas' rev: 34.00 (Windows)

#ifndef Web_HttpparseHPP
#define Web_HttpparseHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Httpparse
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS THTTPParser;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION THTTPParser : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStream* FStream;
	__int64 FOrigin;
	char *FBuffer;
	char *FBufPtr;
	char *FBufEnd;
	char *FSourcePtr;
	char *FSourceEnd;
	char *FStringPtr;
	int FSourceLine;
	char FSaveChar;
	char FToken;
	bool FHeaderField;
	char *FTokenPtr;
	void __fastcall ReadBuffer();
	void __fastcall SkipBlanks();
	
public:
	__fastcall THTTPParser(System::Classes::TStream* Stream);
	__fastcall virtual ~THTTPParser();
	void __fastcall CheckToken(char T);
	void __fastcall CheckTokenSymbol(const System::UTF8String S);
	System::UTF8String __fastcall CopyTo(int Length);
	System::UTF8String __fastcall CopyToEOL();
	System::UTF8String __fastcall CopyToEOF();
	void __fastcall Error(const System::UnicodeString Ident);
	void __fastcall ErrorFmt(const System::UnicodeString Ident, const System::TVarRec *Args, const int Args_High);
	void __fastcall ErrorStr(const System::UnicodeString Message);
	void __fastcall HexToBinary(System::Classes::TStream* Stream);
	char __fastcall NextToken();
	void __fastcall SkipEOL();
	__int64 __fastcall SourcePos();
	System::Extended __fastcall TokenFloat();
	int __fastcall TokenInt();
	System::UTF8String __fastcall TokenString();
	bool __fastcall TokenSymbolIs(const System::UTF8String S);
	System::Classes::TStream* __fastcall BufferRequest(int Length);
	__property int SourceLine = {read=FSourceLine, nodefault};
	__property char Token = {read=FToken, nodefault};
	__property bool HeaderField = {read=FHeaderField, write=FHeaderField, nodefault};
	__property char * SourcePtr = {read=FSourcePtr, write=FSourcePtr};
	__property char * TokenPtr = {read=FTokenPtr, write=FTokenPtr};
	__property System::Classes::TStream* Stream = {read=FStream};
	__property char * SourceEnd = {read=FSourceEnd};
};


//-- var, const, procedure ---------------------------------------------------
static const char toEOF = '\0';
static const char toSymbol = '\x01';
static const char toString = '\x02';
static const char toInteger = '\x03';
static const char toFloat = '\x04';
static const char toEOL = '\x05';
static const char toGET = '\x06';
static const char toHEAD = '\x07';
static const char toPUT = '\x08';
static const char toDELETE = '\x09';
static const char toPOST = '\x0a';
static const char toPATCH = '\x0b';
static const char toCOPY = '\x0c';
static const char toUserAgent = '\x0d';
static const char toAccept = '\x0e';
static const char toContentType = '\x0f';
static const char toContentLength = '\x10';
static const char toReferer = '\x11';
static const char toAuthorization = '\x12';
static const char toCacheControl = '\x13';
static const char toDate = '\x14';
static const char toFrom = '\x15';
static const char toHost = '\x16';
static const char toIfModified = '\x17';
static const char toContentEncoding = '\x18';
static const char toContentVersion = '\x19';
static const char toAllow = '\x1a';
static const char toConnection = '\x1b';
static const char toCookie = '\x1c';
static const char toContentDisposition = '\x1d';
static const System::Word hcGET = System::Word(0x14f5);
static const System::Word hcPUT = System::Word(0x4af5);
static const System::Word hcDELETE = System::Word(0x92b2);
static const System::Word hcPOST = System::Word(0x361d);
static const System::Word hcCacheControl = System::Word(0x4ff6);
static const System::Word hcDate = System::Word(0xee6);
static const System::Word hcFrom = System::Word(0x418f);
static const System::Word hcHost = System::Word(0x3611);
static const System::Word hcIfModified = System::Word(0xddf0);
static const System::Word hcAllow = System::Word(0x3d80);
static const System::Word hcUserAgent = System::Word(0xe890);
static const System::Word hcAccept = System::Word(0x1844);
static const System::Word hcContentEncoding = System::Word(0xc586);
static const System::Word hcContentVersion = System::Word(0xedf4);
static const System::Word hcContentType = System::Word(0xf0e0);
static const System::Word hcContentLength = System::Word(0xb0c4);
static const System::Word hcReferer = System::Word(0xcea5);
static const System::Word hcAuthorization = System::Word(0xabca);
static const System::Word hcConnection = System::Word(0xede);
static const System::Word hcCookie = System::Word(0x27b3);
static const System::Word hcContentDisposition = System::Word(0xcbeb);
}	/* namespace Httpparse */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_HTTPPARSE)
using namespace Web::Httpparse;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_HttpparseHPP
