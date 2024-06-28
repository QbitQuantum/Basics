// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.RegularExpressionsAPI.pas' rev: 34.00 (Windows)

#ifndef System_RegularexpressionsapiHPP
#define System_RegularexpressionsapiHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Regularexpressionsapi
{
//-- forward type declarations -----------------------------------------------
struct DECLSPEC_DRECORD real_pcre
{
};


struct DECLSPEC_DRECORD real_pcre_jit_stack
{
};


struct real_pcre_extra;
struct pcre_callout_block;
//-- type declarations -------------------------------------------------------
typedef System::WideChar * PCRE_STR;

typedef System::WideChar * *PCRE_SPTR;

typedef PCRE_SPTR *PCRE_SPTR_PTR;

typedef real_pcre TPCRE;

typedef real_pcre *PPCRE;

typedef real_pcre_jit_stack TRealPCREJitStack;

typedef real_pcre_jit_stack *PRealPCREJitStack;

typedef real_pcre_jit_stack pcre_jit_stack;

typedef real_pcre_jit_stack TPCREJitStack;

typedef real_pcre_jit_stack *PPCREJitStack;

struct DECLSPEC_DRECORD real_pcre_extra
{
public:
	unsigned flags;
	void *study_data;
	unsigned match_limit;
	void *callout_data;
	System::WideChar *tables;
	unsigned match_limit_recursion;
	System::WideChar *mark;
	void *executable_jit;
};


typedef real_pcre_extra TPCREExtra;

typedef real_pcre_extra *PPCREExtra;

struct DECLSPEC_DRECORD pcre_callout_block
{
public:
	int version;
	int callout_number;
	int *offset_vector;
	System::WideChar *subject;
	int subject_length;
	int start_match;
	int current_position;
	int capture_top;
	int capture_last;
	void *callout_data;
	int pattern_position;
	int next_item_length;
	System::WideChar *mark;
};


typedef void * __cdecl (*pcre_malloc_callback)(NativeUInt Size);

typedef void __cdecl (*pcre_free_callback)(void * P);

typedef void * __cdecl (*pcre_stack_malloc_callback)(NativeUInt Size);

typedef void __cdecl (*pcre_stack_free_callback)(void * P);

typedef int __cdecl (*pcre_callout_callback)(pcre_callout_block &callout_block);

typedef int __cdecl (*pcre_stack_guard_callback)(void);

//-- var, const, procedure ---------------------------------------------------
static const int MAX_PATTERN_LENGTH = int(0x10003);
static const int MAX_QUANTIFY_REPEAT = int(0x10000);
static const System::Word MAX_CAPTURE_COUNT = System::Word(0xffff);
static const System::Byte MAX_NESTING_DEPTH = System::Byte(0xc8);
static const System::Int8 PCRE_CASELESS = System::Int8(0x1);
static const System::Int8 PCRE_MULTILINE = System::Int8(0x2);
static const System::Int8 PCRE_DOTALL = System::Int8(0x4);
static const System::Int8 PCRE_EXTENDED = System::Int8(0x8);
static const System::Int8 PCRE_ANCHORED = System::Int8(0x10);
static const System::Int8 PCRE_DOLLAR_ENDONLY = System::Int8(0x20);
static const System::Int8 PCRE_EXTRA = System::Int8(0x40);
static const System::Byte PCRE_NOTBOL = System::Byte(0x80);
static const System::Word PCRE_NOTEOL = System::Word(0x100);
static const System::Word PCRE_UNGREEDY = System::Word(0x200);
static const System::Word PCRE_NOTEMPTY = System::Word(0x400);
static const System::Word PCRE_UTF8 = System::Word(0x800);
static const System::Word PCRE_UTF16 = System::Word(0x800);
static const System::Word PCRE_UTF32 = System::Word(0x800);
static const System::Word PCRE_NO_AUTO_CAPTURE = System::Word(0x1000);
static const System::Word PCRE_NO_UTF8_CHECK = System::Word(0x2000);
static const System::Word PCRE_NO_UTF16_CHECK = System::Word(0x2000);
static const System::Word PCRE_NO_UTF32_CHECK = System::Word(0x2000);
static const System::Word PCRE_AUTO_CALLOUT = System::Word(0x4000);
static const System::Word PCRE_PARTIAL = System::Word(0x8000);
static const int PCRE_NEVER_UTF = int(0x10000);
static const int PCRE_DFA_SHORTEST = int(0x10000);
static const int PCRE_NO_AUTO_POSSESS = int(0x20000);
static const int PCRE_DFA_RESTART = int(0x20000);
static const int PCRE_FIRSTLINE = int(0x40000);
static const int PCRE_DUPNAMES = int(0x80000);
static const int PCRE_NEWLINE_CR = int(0x100000);
static const int PCRE_NEWLINE_LF = int(0x200000);
static const int PCRE_NEWLINE_CRLF = int(0x300000);
static const int PCRE_NEWLINE_ANY = int(0x400000);
static const int PCRE_NEWLINE_ANYCRLF = int(0x500000);
static const int PCRE_BSR_ANYCRLF = int(0x800000);
static const int PCRE_BSR_UNICODE = int(0x1000000);
static const int PCRE_JAVASCRIPT_COMPAT = int(0x2000000);
static const int PCRE_NO_START_OPTIMIZE = int(0x4000000);
static const int PCRE_NO_START_OPTIMISE = int(0x4000000);
static const int PCRE_PARTIAL_HARD = int(0x8000000);
static const int PCRE_NOTEMPTY_ATSTART = int(0x10000000);
static const int PCRE_UCP = int(0x20000000);
static const System::Int8 PCRE_ERROR_NOMATCH = System::Int8(-1);
static const System::Int8 PCRE_ERROR_NULL = System::Int8(-2);
static const System::Int8 PCRE_ERROR_BADOPTION = System::Int8(-3);
static const System::Int8 PCRE_ERROR_BADMAGIC = System::Int8(-4);
static const System::Int8 PCRE_ERROR_UNKNOWN_NODE = System::Int8(-5);
static const System::Int8 PCRE_ERROR_NOMEMORY = System::Int8(-6);
static const System::Int8 PCRE_ERROR_NOSUBSTRING = System::Int8(-7);
static const System::Int8 PCRE_ERROR_MATCHLIMIT = System::Int8(-8);
static const System::Int8 PCRE_ERROR_CALLOUT = System::Int8(-9);
static const System::Int8 PCRE_ERROR_BADUTF8 = System::Int8(-10);
static const System::Int8 PCRE_ERROR_BADUTF16 = System::Int8(-10);
static const System::Int8 PCRE_ERROR_BADUTF32 = System::Int8(-10);
static const System::Int8 PCRE_ERROR_BADUTF8_OFFSET = System::Int8(-11);
static const System::Int8 PCRE_ERROR_BADUTF16_OFFSET = System::Int8(-11);
static const System::Int8 PCRE_ERROR_PARTIAL = System::Int8(-12);
static const System::Int8 PCRE_ERROR_BADPARTIAL = System::Int8(-13);
static const System::Int8 PCRE_ERROR_INTERNAL = System::Int8(-14);
static const System::Int8 PCRE_ERROR_BADCOUNT = System::Int8(-15);
static const System::Int8 PCRE_ERROR_DFA_UITEM = System::Int8(-16);
static const System::Int8 PCRE_ERROR_DFA_UCOND = System::Int8(-17);
static const System::Int8 PCRE_ERROR_DFA_UMLIMIT = System::Int8(-18);
static const System::Int8 PCRE_ERROR_DFA_WSSIZE = System::Int8(-19);
static const System::Int8 PCRE_ERROR_DFA_RECURSE = System::Int8(-20);
static const System::Int8 PCRE_ERROR_RECURSIONLIMIT = System::Int8(-21);
static const System::Int8 PCRE_ERROR_NULLWSLIMIT = System::Int8(-22);
static const System::Int8 PCRE_ERROR_BADNEWLINE = System::Int8(-23);
static const System::Int8 PCRE_ERROR_BADOFFSET = System::Int8(-24);
static const System::Int8 PCRE_ERROR_SHORTUTF8 = System::Int8(-25);
static const System::Int8 PCRE_ERROR_SHORTUTF16 = System::Int8(-25);
static const System::Int8 PCRE_ERROR_RECURSELOOP = System::Int8(-26);
static const System::Int8 PCRE_ERROR_JIT_STACKLIMIT = System::Int8(-27);
static const System::Int8 PCRE_ERROR_BADMODE = System::Int8(-28);
static const System::Int8 PCRE_ERROR_BADENDIANNESS = System::Int8(-29);
static const System::Int8 PCRE_ERROR_DFA_BADRESTART = System::Int8(-30);
static const System::Int8 PCRE_ERROR_JIT_BADOPTION = System::Int8(-31);
static const System::Int8 PCRE_ERROR_BADLENGTH = System::Int8(-32);
static const System::Int8 PCRE_ERROR_UNSET = System::Int8(-33);
static const System::Int8 PCRE_UTF8_ERR0 = System::Int8(0x0);
static const System::Int8 PCRE_UTF8_ERR1 = System::Int8(0x1);
static const System::Int8 PCRE_UTF8_ERR2 = System::Int8(0x2);
static const System::Int8 PCRE_UTF8_ERR3 = System::Int8(0x3);
static const System::Int8 PCRE_UTF8_ERR4 = System::Int8(0x4);
static const System::Int8 PCRE_UTF8_ERR5 = System::Int8(0x5);
static const System::Int8 PCRE_UTF8_ERR6 = System::Int8(0x6);
static const System::Int8 PCRE_UTF8_ERR7 = System::Int8(0x7);
static const System::Int8 PCRE_UTF8_ERR8 = System::Int8(0x8);
static const System::Int8 PCRE_UTF8_ERR9 = System::Int8(0x9);
static const System::Int8 PCRE_UTF8_ERR10 = System::Int8(0xa);
static const System::Int8 PCRE_UTF8_ERR11 = System::Int8(0xb);
static const System::Int8 PCRE_UTF8_ERR12 = System::Int8(0xc);
static const System::Int8 PCRE_UTF8_ERR13 = System::Int8(0xd);
static const System::Int8 PCRE_UTF8_ERR14 = System::Int8(0xe);
static const System::Int8 PCRE_UTF8_ERR15 = System::Int8(0xf);
static const System::Int8 PCRE_UTF8_ERR16 = System::Int8(0x10);
static const System::Int8 PCRE_UTF8_ERR17 = System::Int8(0x11);
static const System::Int8 PCRE_UTF8_ERR18 = System::Int8(0x12);
static const System::Int8 PCRE_UTF8_ERR19 = System::Int8(0x13);
static const System::Int8 PCRE_UTF8_ERR20 = System::Int8(0x14);
static const System::Int8 PCRE_UTF8_ERR21 = System::Int8(0x15);
static const System::Int8 PCRE_UTF8_ERR22 = System::Int8(0x16);
static const System::Int8 PCRE_UTF16_ERR0 = System::Int8(0x0);
static const System::Int8 PCRE_UTF16_ERR1 = System::Int8(0x1);
static const System::Int8 PCRE_UTF16_ERR2 = System::Int8(0x2);
static const System::Int8 PCRE_UTF16_ERR3 = System::Int8(0x3);
static const System::Int8 PCRE_UTF16_ERR4 = System::Int8(0x4);
static const System::Int8 PCRE_UTF32_ERR0 = System::Int8(0x0);
static const System::Int8 PCRE_UTF32_ERR1 = System::Int8(0x1);
static const System::Int8 PCRE_UTF32_ERR2 = System::Int8(0x2);
static const System::Int8 PCRE_UTF32_ERR3 = System::Int8(0x3);
static const System::Int8 PCRE_INFO_OPTIONS = System::Int8(0x0);
static const System::Int8 PCRE_INFO_SIZE = System::Int8(0x1);
static const System::Int8 PCRE_INFO_CAPTURECOUNT = System::Int8(0x2);
static const System::Int8 PCRE_INFO_BACKREFMAX = System::Int8(0x3);
static const System::Int8 PCRE_INFO_FIRSTCHAR = System::Int8(0x4);
static const System::Int8 PCRE_INFO_FIRSTTABLE = System::Int8(0x5);
static const System::Int8 PCRE_INFO_LASTLITERAL = System::Int8(0x6);
static const System::Int8 PCRE_INFO_NAMEENTRYSIZE = System::Int8(0x7);
static const System::Int8 PCRE_INFO_NAMECOUNT = System::Int8(0x8);
static const System::Int8 PCRE_INFO_NAMETABLE = System::Int8(0x9);
static const System::Int8 PCRE_INFO_STUDYSIZE = System::Int8(0xa);
static const System::Int8 PCRE_INFO_DEFAULT_TABLES = System::Int8(0xb);
static const System::Int8 PCRE_INFO_OKPARTIAL = System::Int8(0xc);
static const System::Int8 PCRE_INFO_JCHANGED = System::Int8(0xd);
static const System::Int8 PCRE_INFO_HASCRORLF = System::Int8(0xe);
static const System::Int8 PCRE_INFO_MINLENGTH = System::Int8(0xf);
static const System::Int8 PCRE_INFO_JIT = System::Int8(0x10);
static const System::Int8 PCRE_INFO_JITSIZE = System::Int8(0x11);
static const System::Int8 PCRE_INFO_MAXLOOKBEHIND = System::Int8(0x12);
static const System::Int8 PCRE_INFO_FIRSTCHARACTER = System::Int8(0x13);
static const System::Int8 PCRE_INFO_FIRSTCHARACTERFLAGS = System::Int8(0x14);
static const System::Int8 PCRE_INFO_REQUIREDCHAR = System::Int8(0x15);
static const System::Int8 PCRE_INFO_REQUIREDCHARFLAGS = System::Int8(0x16);
static const System::Int8 PCRE_INFO_MATCHLIMIT = System::Int8(0x17);
static const System::Int8 PCRE_INFO_RECURSIONLIMIT = System::Int8(0x18);
static const System::Int8 PCRE_INFO_MATCH_EMPTY = System::Int8(0x19);
static const System::Int8 PCRE_CONFIG_UTF8 = System::Int8(0x0);
static const System::Int8 PCRE_CONFIG_NEWLINE = System::Int8(0x1);
static const System::Int8 PCRE_CONFIG_LINK_SIZE = System::Int8(0x2);
static const System::Int8 PCRE_CONFIG_POSIX_MALLOC_THRESHOLD = System::Int8(0x3);
static const System::Int8 PCRE_CONFIG_MATCH_LIMIT = System::Int8(0x4);
static const System::Int8 PCRE_CONFIG_STACKRECURSE = System::Int8(0x5);
static const System::Int8 PCRE_CONFIG_UNICODE_PROPERTIES = System::Int8(0x6);
static const System::Int8 PCRE_CONFIG_MATCH_LIMIT_RECURSION = System::Int8(0x7);
static const System::Int8 PCRE_CONFIG_BSR = System::Int8(0x8);
static const System::Int8 PCRE_CONFIG_JIT = System::Int8(0x9);
static const System::Int8 PCRE_CONFIG_UTF16 = System::Int8(0xa);
static const System::Int8 PCRE_CONFIG_JITTARGET = System::Int8(0xb);
static const System::Int8 PCRE_CONFIG_UTF32 = System::Int8(0xc);
static const System::Int8 PCRE_CONFIG_PARENS_LIMIT = System::Int8(0xd);
static const System::Int8 PCRE_STUDY_JIT_COMPILE = System::Int8(0x1);
static const System::Int8 PCRE_STUDY_JIT_PARTIAL_SOFT_COMPILE = System::Int8(0x2);
static const System::Int8 PCRE_STUDY_JIT_PARTIAL_HARD_COMPILE = System::Int8(0x4);
static const System::Int8 PCRE_STUDY_EXTRA_NEEDED = System::Int8(0x8);
static const System::Int8 PCRE_EXTRA_STUDY_DATA = System::Int8(0x1);
static const System::Int8 PCRE_EXTRA_MATCH_LIMIT = System::Int8(0x2);
static const System::Int8 PCRE_EXTRA_CALLOUT_DATA = System::Int8(0x4);
static const System::Int8 PCRE_EXTRA_TABLES = System::Int8(0x8);
static const System::Int8 PCRE_EXTRA_MATCH_LIMIT_RECURSION = System::Int8(0x10);
static const System::Int8 PCRE_EXTRA_MARK = System::Int8(0x20);
static const System::Int8 PCRE_EXTRA_EXECUTABLE_JIT = System::Int8(0x40);
#ifndef _WIN64
static const System::WideChar PU = (System::WideChar)(0x5f);
#else /* _WIN64 */
#define PU L""
#endif /* _WIN64 */
extern DELPHI_PACKAGE void __fastcall SetPCREMallocCallback(const pcre_malloc_callback Value);
extern DELPHI_PACKAGE pcre_malloc_callback __fastcall GetPCREMallocCallback(void);
extern DELPHI_PACKAGE void * __fastcall CallPCREMalloc(NativeUInt Size);
extern DELPHI_PACKAGE void __fastcall SetPCREFreeCallback(const pcre_free_callback Value);
extern DELPHI_PACKAGE pcre_free_callback __fastcall GetPCREFreeCallback(void);
extern DELPHI_PACKAGE void __fastcall CallPCREFree(void * P);
extern DELPHI_PACKAGE void __fastcall SetPCREStackMallocCallback(const pcre_stack_malloc_callback Value);
extern DELPHI_PACKAGE pcre_stack_malloc_callback __fastcall GetPCREStackMallocCallback(void);
extern DELPHI_PACKAGE void * __fastcall CallPCREStackMalloc(NativeUInt Size);
extern DELPHI_PACKAGE void __fastcall SetPCREStackFreeCallback(const pcre_stack_free_callback Value);
extern DELPHI_PACKAGE pcre_stack_free_callback __fastcall GetPCREStackFreeCallback(void);
extern DELPHI_PACKAGE void __fastcall CallPCREStackFree(void * P);
extern DELPHI_PACKAGE void __fastcall SetPCRECalloutCallback(const pcre_callout_callback Value);
extern DELPHI_PACKAGE pcre_callout_callback __fastcall GetPCRECalloutCallback(void);
extern DELPHI_PACKAGE int __fastcall CallPCRECallout(pcre_callout_block &callout_block);
extern DELPHI_PACKAGE void __fastcall pcre_dispose(void * pattern, void * hints, void * chartable);
extern DELPHI_PACKAGE PPCREExtra __cdecl pcre_study(const PPCRE code, int options, const System::PPAnsiChar errptr);
extern DELPHI_PACKAGE void __cdecl pcre_free_study(PPCREExtra extra);
extern DELPHI_PACKAGE PPCRE __cdecl pcre_compile(const System::WideChar * pattern, int options, const System::PPAnsiChar errptr, PInteger erroffset, const char * tableptr);
extern DELPHI_PACKAGE PPCRE __cdecl pcre_compile2(const System::WideChar * pattern, int options, const PInteger errorcodeptr, const System::PPAnsiChar errorptr, PInteger erroroffset, const char * tables);
extern DELPHI_PACKAGE int __cdecl pcre_config(int what, void * where);
extern DELPHI_PACKAGE int __cdecl pcre_dfa_exec(const PPCRE argument_re, const PPCREExtra extra_data, const System::WideChar * subject, int length, int start_offset, int options, PInteger offsets, int offsetcount, PInteger workspace, int wscount);
extern DELPHI_PACKAGE int __cdecl pcre_exec(const PPCRE code, const PPCREExtra extra, const System::WideChar * subject, int length, int startoffset, int options, PInteger ovector, int ovecsize);
extern DELPHI_PACKAGE int __cdecl pcre_fullinfo(const PPCRE code, const PPCREExtra extra, int what, void * where);
extern DELPHI_PACKAGE int __cdecl pcre_get_stringnumber(const PPCRE code, const System::WideChar * stringname);
extern DELPHI_PACKAGE int __cdecl pcre_get_stringtable_entries(const PPCRE code, const System::WideChar * stringname, PCRE_SPTR firstptr, PCRE_SPTR lastptr);
extern DELPHI_PACKAGE int __cdecl pcre_copy_substring(const System::WideChar * subject, PInteger ovector, int stringcount, int stringnumber, System::WideChar * buffer, int buffersize);
extern DELPHI_PACKAGE int __cdecl pcre_copy_named_substring(const PPCRE code, const System::WideChar * subject, PInteger ovector, int stringcount, const System::WideChar * stringname, System::WideChar * buffer, int size);
extern DELPHI_PACKAGE int __cdecl pcre_get_substring_list(const System::WideChar * subject, PInteger ovector, int stringcount, PCRE_SPTR_PTR listptr);
extern DELPHI_PACKAGE void __cdecl pcre_free_substring_list(PCRE_SPTR stringlistptr);
extern DELPHI_PACKAGE int __cdecl pcre_get_substring(const System::WideChar * subject, PInteger ovector, int stringcount, int stringnumber, const PCRE_SPTR stringptr);
extern DELPHI_PACKAGE int __cdecl pcre_get_named_substring(const PPCRE code, const System::WideChar * subject, PInteger ovector, int stringcount, const System::WideChar * stringname, const PCRE_SPTR stringptr);
extern DELPHI_PACKAGE void __cdecl pcre_free_substring(System::WideChar * stringptr);
extern DELPHI_PACKAGE char * __cdecl pcre_maketables(void);
extern DELPHI_PACKAGE int __cdecl pcre_refcount(PPCRE argument_re, int adjust);
extern DELPHI_PACKAGE char * __cdecl pcre_version(void);
}	/* namespace Regularexpressionsapi */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_REGULAREXPRESSIONSAPI)
using namespace System::Regularexpressionsapi;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_RegularexpressionsapiHPP
