// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.RegularExpressionsCore.pas' rev: 34.00 (Android)

#ifndef System_RegularexpressionscoreHPP
#define System_RegularexpressionscoreHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.RegularExpressionsAPI.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Regularexpressionscore
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TPerlRegEx;
class DELPHICLASS TPerlRegExList;
class DELPHICLASS ERegularExpressionError;
//-- type declarations -------------------------------------------------------
typedef System::UTF8String PCREString;

enum DECLSPEC_DENUM System_Regularexpressionscore__1 : unsigned char { preCaseLess, preMultiLine, preSingleLine, preExtended, preAnchored, preUnGreedy, preNoAutoCapture };

typedef System::Set<System_Regularexpressionscore__1, System_Regularexpressionscore__1::preCaseLess, System_Regularexpressionscore__1::preNoAutoCapture> TPerlRegExOptions;

enum DECLSPEC_DENUM System_Regularexpressionscore__2 : unsigned char { preNotBOL, preNotEOL, preNotEmpty };

typedef System::Set<System_Regularexpressionscore__2, System_Regularexpressionscore__2::preNotBOL, System_Regularexpressionscore__2::preNotEmpty> TPerlRegExState;

typedef void __fastcall (__closure *TPerlRegExReplaceEvent)(System::TObject* Sender, System::UnicodeString &ReplaceWith);

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPerlRegEx : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	typedef System::DynamicArray<System::UnicodeString> _TPerlRegEx__1;
	
	
private:
	bool FCompiled;
	bool FStudied;
	TPerlRegExOptions FOptions;
	TPerlRegExState FState;
	System::UnicodeString FRegEx;
	System::UTF8String FReplacement;
	System::UTF8String FSubject;
	int FStart;
	int FStop;
	System::Classes::TNotifyEvent FOnMatch;
	TPerlRegExReplaceEvent FOnReplace;
	int LastIndex1;
	int LastIndexResult1;
	int LastIndex2;
	int LastIndexResult2;
	int __fastcall UTF8IndexToUnicode(int AIndex);
	System::UnicodeString __fastcall GetMatchedText();
	int __fastcall GetMatchedLength();
	int __fastcall GetMatchedOffset();
	int __fastcall InternalGetMatchedOffset();
	int __fastcall InternalGetMatchedLength();
	void __fastcall SetOptions(TPerlRegExOptions Value);
	void __fastcall SetRegEx(const System::UnicodeString Value);
	int __fastcall GetGroupCount();
	System::UnicodeString __fastcall GetGroups(int Index);
	int __fastcall GetGroupLengths(int Index);
	int __fastcall GetGroupOffsets(int Index);
	int __fastcall InternalGetGroupLengths(int Index);
	int __fastcall InternalGetGroupOffsets(int Index);
	void __fastcall SetFSubject(const System::UTF8String Value);
	void __fastcall SetSubject(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSubject();
	void __fastcall SetStart(const int Value);
	void __fastcall SetStop(const int Value);
	bool __fastcall GetFoundMatch();
	System::StaticArray<int, 301> Offsets;
	int OffsetCount;
	int FPCREOptions;
	void *FPattern;
	void *FHints;
	void *FCharTable;
	bool FHasStoredGroups;
	_TPerlRegEx__1 FStoredGroups;
	System::UnicodeString __fastcall GetSubjectLeft();
	System::UTF8String __fastcall GetSubjectLeftUTF8();
	System::UnicodeString __fastcall GetSubjectRight();
	System::UTF8String __fastcall GetSubjectRightUTF8();
	void __fastcall SetReplacement(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetReplacement();
	int __fastcall GetStart();
	int __fastcall InternalNamedGroup(const System::UTF8String Name);
	
protected:
	void __fastcall CleanUp();
	void __fastcall ClearStoredGroups();
	
public:
	__fastcall TPerlRegEx();
	__fastcall virtual ~TPerlRegEx();
	__classmethod System::UnicodeString __fastcall EscapeRegExChars(const System::UnicodeString S);
	void __fastcall Compile();
	void __fastcall Study();
	bool __fastcall Match();
	bool __fastcall MatchAgain();
	System::UnicodeString __fastcall Replace();
	bool __fastcall ReplaceAll();
	System::UnicodeString __fastcall ComputeReplacement();
	void __fastcall StoreGroups();
	int __fastcall NamedGroup(const System::UnicodeString Name);
	void __fastcall Split(System::Classes::TStrings* const Strings, int Limit);
	void __fastcall SplitCapture(System::Classes::TStrings* const Strings, int Limit)/* overload */;
	void __fastcall SplitCapture(System::Classes::TStrings* const Strings, int Limit, int Offset)/* overload */;
	__property bool Compiled = {read=FCompiled, nodefault};
	__property bool FoundMatch = {read=GetFoundMatch, nodefault};
	__property bool Studied = {read=FStudied, nodefault};
	__property System::UnicodeString MatchedText = {read=GetMatchedText};
	__property int MatchedLength = {read=GetMatchedLength, nodefault};
	__property int MatchedOffset = {read=GetMatchedOffset, nodefault};
	__property int Start = {read=GetStart, write=SetStart, nodefault};
	__property int Stop = {read=FStop, write=SetStop, nodefault};
	__property TPerlRegExState State = {read=FState, write=FState, nodefault};
	__property int GroupCount = {read=GetGroupCount, nodefault};
	__property System::UnicodeString Groups[int Index] = {read=GetGroups};
	__property int GroupLengths[int Index] = {read=GetGroupLengths};
	__property int GroupOffsets[int Index] = {read=GetGroupOffsets};
	__property System::UnicodeString Subject = {read=GetSubject, write=SetSubject};
	__property System::UnicodeString SubjectLeft = {read=GetSubjectLeft};
	__property System::UnicodeString SubjectRight = {read=GetSubjectRight};
	__property TPerlRegExOptions Options = {read=FOptions, write=SetOptions, nodefault};
	__property System::UnicodeString RegEx = {read=FRegEx, write=SetRegEx};
	__property System::UnicodeString Replacement = {read=GetReplacement, write=SetReplacement};
	__property System::Classes::TNotifyEvent OnMatch = {read=FOnMatch, write=FOnMatch};
	__property TPerlRegExReplaceEvent OnReplace = {read=FOnReplace, write=FOnReplace};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TPerlRegExList : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::Generics::Collections::TList__1<TPerlRegEx*>* FList;
	System::UTF8String FSubject;
	TPerlRegEx* FMatchedRegEx;
	int FStart;
	int FStop;
	TPerlRegEx* __fastcall GetRegEx(int Index);
	void __fastcall SetRegEx(int Index, TPerlRegEx* const Value);
	void __fastcall SetSubject(const System::UnicodeString Value);
	System::UnicodeString __fastcall GetSubject();
	void __fastcall SetStart(const int Value);
	void __fastcall SetStop(const int Value);
	int __fastcall GetCount();
	int __fastcall GetStart();
	int __fastcall GetStop();
	
protected:
	void __fastcall UpdateRegEx(TPerlRegEx* const ARegEx);
	
public:
	__fastcall TPerlRegExList();
	__fastcall virtual ~TPerlRegExList();
	int __fastcall Add(TPerlRegEx* const ARegEx);
	void __fastcall Clear();
	void __fastcall Delete(int Index);
	int __fastcall IndexOf(TPerlRegEx* const ARegEx);
	void __fastcall Insert(int Index, TPerlRegEx* const ARegEx);
	bool __fastcall Match();
	bool __fastcall MatchAgain();
	__property TPerlRegEx* RegEx[int Index] = {read=GetRegEx, write=SetRegEx};
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Subject = {read=GetSubject, write=SetSubject};
	__property int Start = {read=GetStart, write=SetStart, nodefault};
	__property int Stop = {read=GetStop, write=SetStop, nodefault};
	__property TPerlRegEx* MatchedRegEx = {read=FMatchedRegEx};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION ERegularExpressionError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ERegularExpressionError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ERegularExpressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ERegularExpressionError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ERegularExpressionError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ERegularExpressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ERegularExpressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ERegularExpressionError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ERegularExpressionError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERegularExpressionError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ERegularExpressionError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERegularExpressionError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ERegularExpressionError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ERegularExpressionError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
static constexpr System::Int8 MAX_SUBEXPRESSIONS = System::Int8(0x63);
extern DELPHI_PACKAGE int __fastcall _UnicodeIndexToUTF8 _DEPRECATED_ATTRIBUTE0 (const System::UnicodeString S, int AIndex);
extern DELPHI_PACKAGE int __fastcall _UTF8IndexToUnicode _DEPRECATED_ATTRIBUTE0 (const System::TArray__1<System::Byte> S, int AIndex);
}	/* namespace Regularexpressionscore */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_REGULAREXPRESSIONSCORE)
using namespace System::Regularexpressionscore;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_RegularexpressionscoreHPP
