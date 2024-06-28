// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXSqlScanner.pas' rev: 34.00 (Windows)

#ifndef Data_DbxsqlscannerHPP
#define Data_DbxsqlscannerHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Data.DBXPlatform.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxsqlscanner
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXSqlScanner;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSqlScanner : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXSqlScanner(const System::UnicodeString QuoteChar, const System::UnicodeString QuotePrefix, const System::UnicodeString QuoteSuffix);
	__fastcall virtual ~TDBXSqlScanner();
	void __fastcall RegisterId(const System::UnicodeString Id, const int Token);
	void __fastcall Init(const System::UnicodeString Query)/* overload */;
	void __fastcall Init(const System::UnicodeString Query, const int StartIndex)/* overload */;
	int __fastcall LookAtNextToken();
	int __fastcall NextToken();
	bool __fastcall IsKeyword(const System::UnicodeString Keyword);
	
protected:
	System::UnicodeString __fastcall GetId();
	
private:
	static System::WideChar __fastcall ToQuoteChar(const System::UnicodeString QuoteString);
	void __fastcall ResetId();
	int __fastcall ScanNumber();
	int __fastcall QuotedToken();
	int __fastcall PrefixQuotedToken();
	int __fastcall UnquotedToken();
	int __fastcall ScanSymbol();
	void __fastcall SkipToEndOfLine();
	System::UnicodeString FQuotePrefix;
	System::UnicodeString FQuoteSuffix;
	System::UnicodeString FQuote;
	System::WideChar FQuotePrefixChar;
	System::WideChar FQuoteSuffixChar;
	System::WideChar FQuoteChar;
	Data::Dbxplatform::TDBXObjectStore* FKeywords;
	System::UnicodeString FQuery;
	int FQueryLength;
	int FIndex;
	int FStartOfId;
	int FEndOfId;
	System::UnicodeString FId;
	bool FWasId;
	bool FWasQuoted;
	System::WideChar FSymbol;
	
public:
	__property System::UnicodeString Id = {read=GetId};
	__property bool Quoted = {read=FWasQuoted, nodefault};
	__property System::WideChar Symbol = {read=FSymbol, nodefault};
	__property System::UnicodeString SqlQuery = {read=FQuery};
	__property int NextIndex = {read=FIndex, nodefault};
	static const System::Int8 TokenEos = System::Int8(-1);
	
	static const System::Int8 TokenId = System::Int8(-2);
	
	static const System::Int8 TokenComma = System::Int8(-3);
	
	static const System::Int8 TokenPeriod = System::Int8(-4);
	
	static const System::Int8 TokenSemicolon = System::Int8(-5);
	
	static const System::Int8 TokenOpenParen = System::Int8(-6);
	
	static const System::Int8 TokenCloseParen = System::Int8(-7);
	
	static const System::Int8 TokenNumber = System::Int8(-8);
	
	static const System::Int8 TokenSymbol = System::Int8(-9);
	
	static const System::Int8 TokenError = System::Int8(-10);
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbxsqlscanner */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXSQLSCANNER)
using namespace Data::Dbxsqlscanner;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxsqlscannerHPP
