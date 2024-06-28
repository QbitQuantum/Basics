// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Web.CopyPrsr.pas' rev: 34.00 (Windows)

#ifndef Web_CopyprsrHPP
#define Web_CopyprsrHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>

//-- user supplied -----------------------------------------------------------

namespace Web
{
namespace Copyprsr
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TCopyParser;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TCopyParser : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Classes::TStream* FStream;
	System::Classes::TStream* FOutStream;
	__int64 FOrigin;
	char *FBuffer;
	char *FBufPtr;
	char *FBufEnd;
	char *FSourcePtr;
	char *FSourceEnd;
	char *FTokenPtr;
	char *FStringPtr;
	int FSourceLine;
	char FSaveChar;
	char FToken;
	void __fastcall ReadBuffer();
	void __fastcall SkipBlanks(bool DoCopy);
	char __fastcall SkipToNextToken(bool CopyBlanks, bool DoCopy);
	System::UTF8String __fastcall CopySkipTo(int Length, bool DoCopy);
	System::UTF8String __fastcall CopySkipToToken(char AToken, bool DoCopy);
	System::UTF8String __fastcall CopySkipToEOL(bool DoCopy);
	System::UTF8String __fastcall CopySkipToEOF(bool DoCopy);
	void __fastcall UpdateOutStream(char * StartPos);
	
public:
	__fastcall TCopyParser(System::Classes::TStream* Stream, System::Classes::TStream* OutStream);
	__fastcall virtual ~TCopyParser();
	void __fastcall CheckToken(char T);
	void __fastcall CheckTokenSymbol(const System::UTF8String S);
	System::UTF8String __fastcall CopyTo(int Length);
	System::UTF8String __fastcall CopyToToken(char AToken);
	System::UTF8String __fastcall CopyToEOL();
	System::UTF8String __fastcall CopyToEOF();
	void __fastcall CopyTokenToOutput();
	void __fastcall Error(const System::UnicodeString Ident);
	void __fastcall ErrorFmt(const System::UnicodeString Ident, const System::TVarRec *Args, const int Args_High);
	void __fastcall ErrorStr(const System::UnicodeString Message);
	char __fastcall NextToken();
	char __fastcall SkipToken(bool CopyBlanks);
	void __fastcall SkipEOL();
	System::UTF8String __fastcall SkipTo(int Length);
	System::UTF8String __fastcall SkipToToken(char AToken);
	System::UTF8String __fastcall SkipToEOL();
	System::UTF8String __fastcall SkipToEOF();
	__int64 __fastcall SourcePos();
	System::UTF8String __fastcall TokenComponentIdent();
	System::Extended __fastcall TokenFloat();
	int __fastcall TokenInt();
	System::UTF8String __fastcall TokenString();
	bool __fastcall TokenSymbolIs(const System::UTF8String S);
	__property int SourceLine = {read=FSourceLine, nodefault};
	__property char Token = {read=FToken, nodefault};
	__property System::Classes::TStream* OutputStream = {read=FOutStream, write=FOutStream};
};


//-- var, const, procedure ---------------------------------------------------
static const char toEOL = '\x05';
static const char toEOF = '\0';
static const char toSymbol = '\x01';
static const char toString = '\x02';
static const char toInteger = '\x03';
static const char toFloat = '\x04';
}	/* namespace Copyprsr */
}	/* namespace Web */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB_COPYPRSR)
using namespace Web::Copyprsr;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_WEB)
using namespace Web;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Web_CopyprsrHPP
