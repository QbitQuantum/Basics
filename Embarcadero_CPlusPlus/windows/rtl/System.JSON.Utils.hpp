// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.Utils.pas' rev: 34.00 (Windows)

#ifndef System_Json_UtilsHPP
#define System_Json_UtilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Types.hpp>
#include <System.TypInfo.hpp>
#include <System.Classes.hpp>
#include <System.JSON.Types.hpp>
#include <System.NetEncoding.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
namespace Utils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJsonTextUtils;
class DELPHICLASS TJsonTypeUtils;
//-- type declarations -------------------------------------------------------
#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonTextUtils : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static const System::Byte kArrayEscapedArraySize = System::Byte(0x80);
	
	static const System::WideChar EscapedUnicodeText = (System::WideChar)(0x21);
	
	
private:
#ifndef _WIN64
	static System::DynamicArray<bool> FSingleQuoteCharEscapeFlags;
	static System::DynamicArray<bool> FDoubleQuoteCharEscapeFlags;
	static System::DynamicArray<bool> FHtmlCharEscapeFlags;
#else /* _WIN64 */
	static System::TArray__1<bool> FSingleQuoteCharEscapeFlags;
	static System::TArray__1<bool> FDoubleQuoteCharEscapeFlags;
	static System::TArray__1<bool> FHtmlCharEscapeFlags;
#endif /* _WIN64 */
	
private:
	// __classmethod void __fastcall Create@();
	
public:
#ifndef _WIN64
	__classmethod void __fastcall WriteEscapedString(System::Classes::TTextWriter* const Writer, const System::UnicodeString Str, System::WideChar Delimiter, bool AppendDelimiters, const bool *CharEscapeFlags, const int CharEscapeFlags_High, System::Json::Types::TJsonStringEscapeHandling StringEscapeHandling, System::DynamicArray<System::WideChar> &WriteBuffer);
#else /* _WIN64 */
	__classmethod void __fastcall WriteEscapedString(System::Classes::TTextWriter* const Writer, const System::UnicodeString Str, System::WideChar Delimiter, bool AppendDelimiters, const bool *CharEscapeFlags, const int CharEscapeFlags_High, System::Json::Types::TJsonStringEscapeHandling StringEscapeHandling, System::TArray__1<System::WideChar> &WriteBuffer);
#endif /* _WIN64 */
	__classmethod bool __fastcall ShouldEscapeJavaScriptString(const System::UnicodeString S, const bool *CharEscapeFlags, const int CharEscapeFlags_High);
#ifndef _WIN64
	/* static */ __property System::DynamicArray<bool> SingleQuoteCharEscapeFlags = {read=FSingleQuoteCharEscapeFlags};
	/* static */ __property System::DynamicArray<bool> DoubleQuoteCharEscapeFlags = {read=FDoubleQuoteCharEscapeFlags};
	/* static */ __property System::DynamicArray<bool> HtmlCharEscapeFlags = {read=FHtmlCharEscapeFlags};
#else /* _WIN64 */
	/* static */ __property System::TArray__1<bool> SingleQuoteCharEscapeFlags = {read=FSingleQuoteCharEscapeFlags};
	/* static */ __property System::TArray__1<bool> DoubleQuoteCharEscapeFlags = {read=FDoubleQuoteCharEscapeFlags};
	/* static */ __property System::TArray__1<bool> HtmlCharEscapeFlags = {read=FHtmlCharEscapeFlags};
#endif /* _WIN64 */
	__classmethod void __fastcall ToCharAsUnicode(System::WideChar C, System::WideChar *Buffer, const int Buffer_High);
	__classmethod bool __fastcall IsWhiteSpace(const System::UnicodeString Str);
	
private:
	// __classmethod void __fastcall Destroy@();
public:
	/* TObject.Create */ inline __fastcall TJsonTextUtils() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonTextUtils() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJsonTypeUtils : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static bool __fastcall InheritsFrom(System::Typinfo::PTypeInfo ATypeInfo, const System::TClass AParentClass);
	static bool __fastcall IsAssignableFrom(System::Typinfo::PTypeInfo ATo, System::Typinfo::PTypeInfo AFrom);
public:
	/* TObject.Create */ inline __fastcall TJsonTypeUtils() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonTypeUtils() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Utils */
}	/* namespace Json */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON_UTILS)
using namespace System::Json::Utils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON)
using namespace System::Json;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Json_UtilsHPP
