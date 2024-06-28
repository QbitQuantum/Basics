// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.AnsiStrings.pas' rev: 34.00 (Windows)

#ifndef System_AnsistringsHPP
#define System_AnsistringsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.StrUtils.hpp>
#include <Winapi.Windows.hpp>
#include <System.SysConst.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Ansistrings
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFilenameCaseMatch : unsigned char { mkNone, mkExactMatch, mkSingleMatch, mkAmbiguous };

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::AnsiString EmptyAnsiStr;
extern DELPHI_PACKAGE System::AnsiString *NullAnsiStr;
extern DELPHI_PACKAGE System::Set<System::Byte, 0, 255> WordDelimiters;
extern DELPHI_PACKAGE System::AnsiString __fastcall Format(const System::AnsiString Format, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall Format(const System::AnsiString Format, const System::TVarRec *Args, const int Args_High, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE void __fastcall FmtStr(System::AnsiString &Result, const System::AnsiString Format, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE void __fastcall FmtStr(System::AnsiString &Result, const System::AnsiString Format, const System::TVarRec *Args, const int Args_High, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall AnsiFormatBuf(void *Buffer, unsigned BufLen, const void *Format, unsigned FmtLen, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall AnsiFormatBuf(void *Buffer, unsigned BufLen, const void *Format, unsigned FmtLen, const System::TVarRec *Args, const int Args_High, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall StringReplace(const System::AnsiString S, const System::AnsiString OldPattern, const System::AnsiString NewPattern, System::Sysutils::TReplaceFlags Flags)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall UpperCase(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall UpperCase(const System::AnsiString S, System::Sysutils::TLocaleOptions LocaleOptions)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall LowerCase(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall LowerCase(const System::AnsiString S, System::Sysutils::TLocaleOptions LocaleOptions)/* overload */;
extern DELPHI_PACKAGE int __fastcall CompareStr(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE int __fastcall CompareStr(const System::AnsiString S1, const System::AnsiString S2, System::Sysutils::TLocaleOptions LocaleOptions)/* overload */;
extern DELPHI_PACKAGE bool __fastcall SameStr(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall SameStr(const System::AnsiString S1, const System::AnsiString S2, System::Sysutils::TLocaleOptions LocaleOptions)/* overload */;
extern DELPHI_PACKAGE int __fastcall CompareText(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE int __fastcall CompareText(const System::AnsiString S1, const System::AnsiString S2, System::Sysutils::TLocaleOptions LocaleOptions)/* overload */;
extern DELPHI_PACKAGE bool __fastcall SameText(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall SameText(const System::AnsiString S1, const System::AnsiString S2, System::Sysutils::TLocaleOptions LocaleOptions)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiUpperCase(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiLowerCase(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiCompareStr(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiSameStr(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiCompareText(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiSameText(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiLastChar(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall Trim(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall TrimLeft(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall TrimRight(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall QuotedStr(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiQuotedStr(const System::AnsiString S, char Quote)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiDequotedStr(const System::AnsiString S, char AQuote)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AdjustLineBreaks(const System::AnsiString S, System::TTextLineBreakStyle Style)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsValidIdent(const System::AnsiString Ident, bool AllowDots);
extern DELPHI_PACKAGE int __fastcall CharLength(const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall NextCharIndex(const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiCompareFileName(const System::AnsiString S1, const System::AnsiString S2);
extern DELPHI_PACKAGE bool __fastcall SameFileName(const System::AnsiString S1, const System::AnsiString S2)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiLowerCaseFileName _DEPRECATED_ATTRIBUTE1("Use AnsiLowerCase instead") (const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiUpperCaseFileName _DEPRECATED_ATTRIBUTE1("Use AnsiUpperCase instead") (const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiPos(const System::AnsiString Substr, const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE bool __fastcall ContainsText(const System::AnsiString AText, const System::AnsiString ASubText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiContainsText(const System::AnsiString AText, const System::AnsiString ASubText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall StartsText(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiStartsText(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall EndsText(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiEndsText(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ReplaceStr(const System::AnsiString AText, const System::AnsiString AFromText, const System::AnsiString AToText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiReplaceStr(const System::AnsiString AText, const System::AnsiString AFromText, const System::AnsiString AToText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ReplaceText(const System::AnsiString AText, const System::AnsiString AFromText, const System::AnsiString AToText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiReplaceText(const System::AnsiString AText, const System::AnsiString AFromText, const System::AnsiString AToText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall MatchText(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiMatchText(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE int __fastcall IndexText(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiIndexText(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE bool __fastcall ContainsStr(const System::AnsiString AText, const System::AnsiString ASubText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiContainsStr(const System::AnsiString AText, const System::AnsiString ASubText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall StartsStr(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiStartsStr(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall EndsStr(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiEndsStr(const System::AnsiString ASubText, const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE bool __fastcall MatchStr(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE bool __fastcall AnsiMatchStr(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE int __fastcall IndexStr(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiIndexStr(const System::AnsiString AText, const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall DupeString(const System::AnsiString AText, int ACount)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ReverseString(const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiReverseString(const System::AnsiString AText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall StuffString(const System::AnsiString AText, unsigned AStart, unsigned ALength, const System::AnsiString ASubText)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall RandomFrom(const System::AnsiString *AValues, const int AValues_High)/* overload */;
extern DELPHI_PACKAGE int __fastcall PosEx(const System::AnsiString SubStr, const System::AnsiString S, int Offset = 0x1)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ChangeFileExt(const System::AnsiString FileName, const System::AnsiString Extension)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ChangeFilePath(const System::AnsiString FileName, const System::AnsiString Path)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractFilePath(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractFileDir(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractFileDrive(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractFileName(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractFileExt(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExpandFileName(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExpandFileNameCase(const System::AnsiString FileName, /* out */ TFilenameCaseMatch &MatchFound)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExpandUNCFileName(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractRelativePath(const System::AnsiString BaseName, const System::AnsiString DestName)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExtractShortPathName(const System::AnsiString FileName)/* overload */;
extern DELPHI_PACKAGE int __fastcall LastDelimiter(const System::AnsiString Delimiters, const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsPathDelimiter(const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE bool __fastcall IsDelimiter(const System::AnsiString Delimiters, const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall IncludeTrailingBackslash(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall IncludeTrailingPathDelimiter(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExcludeTrailingBackslash(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall ExcludeTrailingPathDelimiter(const System::AnsiString S)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiLeftStr(const System::AnsiString AText, const int ACount)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiRightStr(const System::AnsiString AText, const int ACount)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiMidStr(const System::AnsiString AText, const int AStart, const int ACount)/* overload */;
extern DELPHI_PACKAGE System::PAnsiString __fastcall NewStr _DEPRECATED_ATTRIBUTE0 (const System::AnsiString S);
extern DELPHI_PACKAGE void __fastcall DisposeStr _DEPRECATED_ATTRIBUTE0 (System::PAnsiString P);
extern DELPHI_PACKAGE void __fastcall AssignStr _DEPRECATED_ATTRIBUTE0 (System::PAnsiString &P, const System::AnsiString S);
extern DELPHI_PACKAGE void __fastcall AppendStr _DEPRECATED_ATTRIBUTE0 (System::AnsiString &Dest, const System::AnsiString S);
extern DELPHI_PACKAGE int __fastcall AnsiStrComp(char * S1, char * S2)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiStrIComp(char * S1, char * S2)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiStrLComp(char * S1, char * S2, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE int __fastcall AnsiStrLIComp(char * S1, char * S2, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrLower(char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrUpper(char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrLastChar(char * P)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall AnsiExtractQuotedStr(char * &Src, char Quote)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall StrLen(const char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrEnd(const char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrMove(char * Dest, const char * Source, unsigned Count)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrCopy(char * Dest, const char * Source)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrECopy(char * Dest, const char * Source)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrLCopy(char * Dest, const char * Source, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrPCopy(char * Dest, const System::AnsiString Source)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrPLCopy(char * Dest, const System::AnsiString Source, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrCat(char * Dest, const char * Source)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrLCat(char * Dest, const char * Source, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE int __fastcall StrComp(const char * Str1, const char * Str2)/* overload */;
extern DELPHI_PACKAGE int __fastcall StrIComp(const char * Str1, const char * Str2)/* overload */;
extern DELPHI_PACKAGE int __fastcall StrLComp(const char * Str1, const char * Str2, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE int __fastcall StrLIComp(const char * Str1, const char * Str2, unsigned MaxLen)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrScan(const char * Str, char Chr)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrRScan(const char * Str, char Chr)/* overload */;
extern DELPHI_PACKAGE char * __fastcall TextPos(char * Str, char * SubStr)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrPos(const char * Str1, const char * Str2)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrUpper(char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrLower(char * Str)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall StrPas(const char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrAlloc(unsigned Size);
extern DELPHI_PACKAGE unsigned __fastcall StrBufSize(const char * Str)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrNew(const char * Str)/* overload */;
extern DELPHI_PACKAGE void __fastcall StrDispose(char * Str)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall FormatBuf(void *Buffer, unsigned BufLen, const void *Format, unsigned FmtLen, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrFmt(char * Buffer, char * Format, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrFmt(char * Buffer, char * Format, const System::TVarRec *Args, const int Args_High, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrLFmt(char * Buffer, unsigned MaxBufLen, char * Format, const System::TVarRec *Args, const int Args_High)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrLFmt(char * Buffer, unsigned MaxBufLen, char * Format, const System::TVarRec *Args, const int Args_High, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE int __fastcall FloatToText(char * BufferArg, const void *Value, System::Sysutils::TFloatValue ValueType, System::Sysutils::TFloatFormat Format, int Precision, int Digits)/* overload */;
extern DELPHI_PACKAGE int __fastcall FloatToText(char * BufferArg, const void *Value, System::Sysutils::TFloatValue ValueType, System::Sysutils::TFloatFormat Format, int Precision, int Digits, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE unsigned __fastcall FormatBuf(void *Buffer, unsigned BufLen, const void *Format, unsigned FmtLen, const System::TVarRec *Args, const int Args_High, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE int __fastcall FloatToTextFmt(char * Buf, const void *Value, System::Sysutils::TFloatValue ValueType, char * Format)/* overload */;
extern DELPHI_PACKAGE int __fastcall FloatToTextFmt(char * Buf, const void *Value, System::Sysutils::TFloatValue ValueType, char * Format, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TextToFloat(char * Buffer, void *Value, System::Sysutils::TFloatValue ValueType)/* overload */;
extern DELPHI_PACKAGE bool __fastcall TextToFloat(char * Buffer, void *Value, System::Sysutils::TFloatValue ValueType, const System::Sysutils::TFormatSettings &AFormatSettings)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrPos(char * Str, char * SubStr)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrRScan(char * Str, char Chr)/* overload */;
extern DELPHI_PACKAGE char * __fastcall AnsiStrScan(char * Str, char Chr)/* overload */;
extern DELPHI_PACKAGE System::Sysutils::TMbcsByteType __fastcall ByteType(const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE System::Sysutils::TMbcsByteType __fastcall StrByteType(char * Str, unsigned Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall ElementToCharLen(const System::AnsiString S, int MaxLen)/* overload */;
extern DELPHI_PACKAGE int __fastcall ByteToCharLen _DEPRECATED_ATTRIBUTE1("Use ElementToCharLen") (const System::AnsiString S, int MaxLen)/* overload */;
extern DELPHI_PACKAGE int __fastcall ElementToCharIndex(const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall ByteToCharIndex _DEPRECATED_ATTRIBUTE1("Use ElementToCharIndex.") (const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall CharToElementIndex(const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall CharToByteIndex _DEPRECATED_ATTRIBUTE1("Use CharToElementIndex.") (const System::AnsiString S, int Index)/* overload */;
extern DELPHI_PACKAGE int __fastcall CharToElementLen(const System::AnsiString S, int MaxLen)/* overload */;
extern DELPHI_PACKAGE int __fastcall CharToByteLen _DEPRECATED_ATTRIBUTE1("Use CharToElementLen.") (const System::AnsiString S, int MaxLen)/* overload */;
extern DELPHI_PACKAGE char * __fastcall StrNextChar(const char * Str)/* overload */;
extern DELPHI_PACKAGE int __fastcall StrCharLength(const char * Str)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall LeftStr(const System::AnsiString AText, const int ACount)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall RightStr(const System::AnsiString AText, const int ACount)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall MidStr(const System::AnsiString AText, const int AStart, const int ACount)/* overload */;
extern DELPHI_PACKAGE System::AnsiString __fastcall LeftBStr(const System::AnsiString AText, const int AByteCount);
extern DELPHI_PACKAGE System::AnsiString __fastcall RightBStr(const System::AnsiString AText, const int AByteCount);
extern DELPHI_PACKAGE System::AnsiString __fastcall MidBStr(const System::AnsiString AText, const int AByteStart, const int AByteCount);
extern DELPHI_PACKAGE char * __fastcall SearchBuf(char * Buf, int BufLen, int SelStart, int SelLength, System::AnsiString SearchString, System::Strutils::TStringSearchOptions Options = (System::Strutils::TStringSearchOptions() << System::Strutils::TStringSeachOption::soDown ))/* overload */;
}	/* namespace Ansistrings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_ANSISTRINGS)
using namespace System::Ansistrings;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_AnsistringsHPP
