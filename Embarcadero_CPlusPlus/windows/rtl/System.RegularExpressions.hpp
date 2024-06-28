// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.RegularExpressions.pas' rev: 34.00 (Windows)

#ifndef System_RegularexpressionsHPP
#define System_RegularexpressionsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.RegularExpressionsCore.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Regularexpressions
{
//-- forward type declarations -----------------------------------------------
struct TGroup;
struct TGroupCollection;
class DELPHICLASS TGroupCollectionEnumerator;
struct TMatch;
struct TMatchCollection;
class DELPHICLASS TMatchCollectionEnumerator;
struct TRegEx;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TRegExOption : unsigned char { roNone, roIgnoreCase, roMultiLine, roExplicitCapture, roCompiled, roSingleLine, roIgnorePatternSpace, roNotEmpty };

typedef System::Set<TRegExOption, TRegExOption::roNone, TRegExOption::roNotEmpty> TRegExOptions;

struct DECLSPEC_DRECORD TGroup
{
private:
	int FIndex;
	int FLength;
	bool FSuccess;
	System::UnicodeString FValue;
	
protected:
	__fastcall TGroup(const System::UnicodeString AValue, int AIndex, int ALength, bool ASuccess);
	
private:
	System::UnicodeString __fastcall GetValue();
	
public:
	__property int Index = {read=FIndex};
	__property int Length = {read=FLength};
	__property bool Success = {read=FSuccess};
	__property System::UnicodeString Value = {read=GetValue};
	TGroup() {}
};


struct DECLSPEC_DRECORD TGroupCollection
{
public:
	TGroup operator[](const System::Variant Index) { return this->Item[Index]; }
	
private:
#ifndef _WIN64
	System::DynamicArray<TGroup> FList;
#else /* _WIN64 */
	System::TArray__1<TGroup> FList;
#endif /* _WIN64 */
	System::_di_IInterface FNotifier;
	
protected:
	__fastcall TGroupCollection(const System::_di_IInterface ANotifier, const System::UnicodeString AValue, int AIndex, int ALength, bool ASuccess);
	
private:
	int __fastcall GetCount();
	TGroup __fastcall GetItem(const System::Variant &Index);
	
public:
	TGroupCollectionEnumerator* __fastcall GetEnumerator();
	__property int Count = {read=GetCount};
	__property TGroup Item[const System::Variant Index] = {read=GetItem};
	TGroupCollection() {}
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TGroupCollectionEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TGroupCollection FCollection;
	int FIndex;
	
public:
	__fastcall TGroupCollectionEnumerator(const TGroupCollection &ACollection);
	TGroup __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property TGroup Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TGroupCollectionEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

struct DECLSPEC_DRECORD TMatch
{
private:
	TGroup FGroup;
	TGroupCollection FGroups;
	System::_di_IInterface FNotifier;
	
protected:
	__fastcall TMatch(const System::_di_IInterface ANotifier, const System::UnicodeString AValue, int AIndex, int ALength, bool ASuccess);
	
private:
	int __fastcall GetIndex();
	TGroupCollection __fastcall GetGroups();
	int __fastcall GetLength();
	bool __fastcall GetSuccess();
	System::UnicodeString __fastcall GetValue();
	
public:
	TMatch __fastcall NextMatch();
	System::UnicodeString __fastcall Result(const System::UnicodeString Pattern);
	__property TGroupCollection Groups = {read=GetGroups};
	__property int Index = {read=GetIndex};
	__property int Length = {read=GetLength};
	__property bool Success = {read=GetSuccess};
	__property System::UnicodeString Value = {read=GetValue};
	TMatch() {}
};


struct DECLSPEC_DRECORD TMatchCollection
{
public:
	TMatch operator[](int Index) { return this->Item[Index]; }
	
private:
#ifndef _WIN64
	System::DynamicArray<TMatch> FList;
#else /* _WIN64 */
	System::TArray__1<TMatch> FList;
#endif /* _WIN64 */
	
protected:
	__fastcall TMatchCollection(const System::_di_IInterface ANotifier, const System::UnicodeString Input, TRegExOptions AOptions, int StartPos);
	
private:
	int __fastcall GetCount();
	TMatch __fastcall GetItem(int Index);
	
public:
	TMatchCollectionEnumerator* __fastcall GetEnumerator();
	__property int Count = {read=GetCount};
	__property TMatch Item[int Index] = {read=GetItem};
	TMatchCollection() {}
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TMatchCollectionEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	TMatchCollection FCollection;
	int FIndex;
	
public:
#ifndef _WIN64
	__fastcall TMatchCollectionEnumerator(const TMatchCollection ACollection);
#else /* _WIN64 */
	__fastcall TMatchCollectionEnumerator(const TMatchCollection &ACollection);
#endif /* _WIN64 */
	TMatch __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property TMatch Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMatchCollectionEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef System::UnicodeString __fastcall (__closure *TMatchEvaluator)(const TMatch &Match);

struct DECLSPEC_DRECORD TRegEx
{
private:
	TRegExOptions FOptions;
	TMatchEvaluator FMatchEvaluator;
	System::_di_IInterface FNotifier;
	System::Regularexpressionscore::TPerlRegEx* FRegEx;
	void __fastcall InternalOnReplace(System::TObject* Sender, System::UnicodeString &ReplaceWith);
	
public:
	__fastcall TRegEx(const System::UnicodeString Pattern, TRegExOptions Options);
	bool __fastcall IsMatch(const System::UnicodeString Input)/* overload */;
	bool __fastcall IsMatch(const System::UnicodeString Input, int StartPos)/* overload */;
	static bool __fastcall IsMatch(const System::UnicodeString Input, const System::UnicodeString Pattern)/* overload */;
	static bool __fastcall IsMatch(const System::UnicodeString Input, const System::UnicodeString Pattern, TRegExOptions Options)/* overload */;
	static System::UnicodeString __fastcall Escape(const System::UnicodeString Str, bool UseWildCards = false);
	TMatch __fastcall Match(const System::UnicodeString Input)/* overload */;
	TMatch __fastcall Match(const System::UnicodeString Input, int StartPos)/* overload */;
	TMatch __fastcall Match(const System::UnicodeString Input, int StartPos, int Length)/* overload */;
	static TMatch __fastcall Match(const System::UnicodeString Input, const System::UnicodeString Pattern)/* overload */;
	static TMatch __fastcall Match(const System::UnicodeString Input, const System::UnicodeString Pattern, TRegExOptions Options)/* overload */;
	TMatchCollection __fastcall Matches(const System::UnicodeString Input)/* overload */;
	TMatchCollection __fastcall Matches(const System::UnicodeString Input, int StartPos)/* overload */;
	static TMatchCollection __fastcall Matches(const System::UnicodeString Input, const System::UnicodeString Pattern)/* overload */;
	static TMatchCollection __fastcall Matches(const System::UnicodeString Input, const System::UnicodeString Pattern, TRegExOptions Options)/* overload */;
	System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Replacement)/* overload */;
	System::UnicodeString __fastcall Replace(const System::UnicodeString Input, TMatchEvaluator Evaluator)/* overload */;
	System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Replacement, int Count)/* overload */;
	System::UnicodeString __fastcall Replace(const System::UnicodeString Input, TMatchEvaluator Evaluator, int Count)/* overload */;
	static System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Pattern, const System::UnicodeString Replacement)/* overload */;
	static System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Pattern, TMatchEvaluator Evaluator)/* overload */;
	static System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Pattern, const System::UnicodeString Replacement, TRegExOptions Options)/* overload */;
	static System::UnicodeString __fastcall Replace(const System::UnicodeString Input, const System::UnicodeString Pattern, TMatchEvaluator Evaluator, TRegExOptions Options)/* overload */;
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall Split(const System::UnicodeString Input)/* overload */;
	System::DynamicArray<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, int Count)/* overload */;
	System::DynamicArray<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, int Count, int StartPos)/* overload */;
	static System::DynamicArray<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, const System::UnicodeString Pattern)/* overload */;
	static System::DynamicArray<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, const System::UnicodeString Pattern, TRegExOptions Options)/* overload */;
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall Split(const System::UnicodeString Input)/* overload */;
	System::TArray__1<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, int Count)/* overload */;
	System::TArray__1<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, int Count, int StartPos)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, const System::UnicodeString Pattern)/* overload */;
	static System::TArray__1<System::UnicodeString> __fastcall Split(const System::UnicodeString Input, const System::UnicodeString Pattern, TRegExOptions Options)/* overload */;
#endif /* _WIN64 */
	TRegEx() {}
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Regularexpressions */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_REGULAREXPRESSIONS)
using namespace System::Regularexpressions;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_RegularexpressionsHPP
