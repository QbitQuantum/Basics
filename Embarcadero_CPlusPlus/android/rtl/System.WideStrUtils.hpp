// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.WideStrUtils.pas' rev: 34.00 (Android)

#ifndef System_WidestrutilsHPP
#define System_WidestrutilsHPP

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

namespace System
{
namespace Widestrutils
{
//-- forward type declarations -----------------------------------------------
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TEncodeType : unsigned char { etUSASCII, etUTF8, etANSI };

typedef System::Set<char, _DELPHI_SET_CHAR(0), _DELPHI_SET_CHAR(255)> CharSet;

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE System::StaticArray<char, 3> sUTF8BOMString;
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrAlloc(unsigned Size);
extern DELPHI_PACKAGE unsigned __fastcall WStrBufSize(const System::WideChar * Str);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrMove(System::WideChar * Dest, const System::WideChar * Source, unsigned Count);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrNew(const System::WideChar * Str);
extern DELPHI_PACKAGE void __fastcall WStrDispose(System::WideChar * Str);
extern DELPHI_PACKAGE unsigned __fastcall WStrLen(const System::WideChar * Str);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrEnd(const System::WideChar * Str);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrCat(System::WideChar * Dest, const System::WideChar * Source);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrCopy(System::WideChar * Dest, const System::WideChar * Source);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrLCopy(System::WideChar * Dest, const System::WideChar * Source, unsigned MaxLen);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrPCopy(System::WideChar * Dest, const System::WideString Source);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrPLCopy(System::WideChar * Dest, const System::WideString Source, unsigned MaxLen);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrScan(System::WideChar * Str, System::WideChar Chr);
extern DELPHI_PACKAGE int __fastcall WStrComp(const System::WideChar * Str1, const System::WideChar * Str2);
extern DELPHI_PACKAGE System::WideChar * __fastcall WStrPos(const System::WideChar * Str1, const System::WideChar * Str2);
extern DELPHI_PACKAGE System::UTF8String __fastcall UTF8LowerCase(const System::UTF8String S);
extern DELPHI_PACKAGE System::UTF8String __fastcall UTF8UpperCase(const System::UTF8String S);
extern DELPHI_PACKAGE System::UTF8String __fastcall AnsiToUtf8Ex(const System::AnsiString S, const int cp);
extern DELPHI_PACKAGE System::AnsiString __fastcall Utf8ToAnsiEx(const System::UTF8String S, const int cp);
extern DELPHI_PACKAGE TEncodeType __fastcall DetectUTF8Encoding(const System::RawByteString s);
extern DELPHI_PACKAGE bool __fastcall IsUTF8String(const System::RawByteString s);
extern DELPHI_PACKAGE bool __fastcall HasExtendCharacter(const System::RawByteString s);
extern DELPHI_PACKAGE bool __fastcall HasUTF8BOM(System::Classes::TStream* S)/* overload */;
extern DELPHI_PACKAGE bool __fastcall HasUTF8BOM(const System::RawByteString S)/* overload */;
extern DELPHI_PACKAGE void __fastcall ConvertStreamFromAnsiToUTF8(System::Classes::TStream* Src, System::Classes::TStream* Dst, int cp = 0x0);
extern DELPHI_PACKAGE void __fastcall ConvertStreamFromUTF8ToAnsi(System::Classes::TStream* Src, System::Classes::TStream* Dst, int cp = 0x0);
extern DELPHI_PACKAGE System::WideChar * __fastcall WideLastChar(const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall WideQuotedStr(const System::WideString S, System::WideChar Quote);
extern DELPHI_PACKAGE System::WideString __fastcall WideExtractQuotedStr(System::WideChar * &Src, System::WideChar Quote);
extern DELPHI_PACKAGE System::WideString __fastcall WideDequotedStr(const System::WideString S, System::WideChar AQuote);
extern DELPHI_PACKAGE System::WideString __fastcall WideAdjustLineBreaks(const System::WideString S, System::TTextLineBreakStyle Style = (System::TTextLineBreakStyle)(0x1));
extern DELPHI_PACKAGE System::WideString __fastcall WideStringReplace(const System::WideString S, const System::WideString OldPattern, const System::WideString NewPattern, const System::Sysutils::TReplaceFlags Flags);
extern DELPHI_PACKAGE System::WideString __fastcall WideReplaceStr(const System::WideString AText, const System::WideString AFromText, const System::WideString AToText);
extern DELPHI_PACKAGE System::WideString __fastcall WideReplaceText(const System::WideString AText, const System::WideString AFromText, const System::WideString AToText);
extern DELPHI_PACKAGE System::WideString __fastcall LoadWideStr(NativeUInt Ident);
extern DELPHI_PACKAGE System::WideString __fastcall LoadResWideString(System::PResStringRec ResStringRec);
extern DELPHI_PACKAGE bool __fastcall InOpSet(System::WideChar W, const CharSet &Sets);
extern DELPHI_PACKAGE bool __fastcall InOpArray(System::WideChar W, const System::WideChar *Sets, const int Sets_High);
extern DELPHI_PACKAGE bool __fastcall IsUTF8LeadByte(char Lead);
extern DELPHI_PACKAGE bool __fastcall IsUTF8TrailByte(char Lead);
extern DELPHI_PACKAGE int __fastcall UTF8CharSize(char Lead);
extern DELPHI_PACKAGE int __fastcall UTF8CharLength(char Lead);
}	/* namespace Widestrutils */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIDESTRUTILS)
using namespace System::Widestrutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_WidestrutilsHPP
