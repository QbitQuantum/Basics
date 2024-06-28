// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.WideStrings.pas' rev: 34.00 (Windows)

#ifndef System_WidestringsHPP
#define System_WidestringsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Types.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Widestrings
{
//-- forward type declarations -----------------------------------------------
__interface DELPHIINTERFACE IWideStringsAdapter;
typedef System::DelphiInterface<IWideStringsAdapter> _di_IWideStringsAdapter;
class DELPHICLASS TWideStringsEnumerator;
class DELPHICLASS TWideStrings;
struct TWideStringItem;
class DELPHICLASS TWideStringList;
//-- type declarations -------------------------------------------------------
__interface  INTERFACE_UUID("{25FE0E3B-66CB-48AA-B23B-BCFA67E8F5DA}") IWideStringsAdapter  : public System::IInterface 
{
	virtual void __fastcall ReferenceStrings(TWideStrings* S) = 0 ;
	virtual void __fastcall ReleaseStrings() = 0 ;
};

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWideStringsEnumerator : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FIndex;
	TWideStrings* FStrings;
	
public:
	__fastcall TWideStringsEnumerator(TWideStrings* AStrings);
	System::WideString __fastcall GetCurrent();
	bool __fastcall MoveNext();
	__property System::WideString Current = {read=GetCurrent};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TWideStringsEnumerator() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TWideStrings : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	System::WideString operator[](int Index) { return this->Strings[Index]; }
	
private:
	System::Classes::TStringsDefined FDefined;
	System::WideChar FDelimiter;
	System::WideString FLineBreak;
	System::WideChar FQuoteChar;
	System::WideChar FNameValueSeparator;
	bool FStrictDelimiter;
	int FUpdateCount;
	_di_IWideStringsAdapter FAdapter;
	System::WideString __fastcall GetCommaText();
	System::WideString __fastcall GetDelimitedText();
	System::WideString __fastcall GetName(int Index);
	System::WideString __fastcall GetValue(const System::WideString Name);
	void __fastcall ReadData(System::Classes::TReader* Reader);
	void __fastcall SetCommaText(const System::WideString Value);
	void __fastcall SetDelimitedText(const System::WideString Value);
	void __fastcall SetStringsAdapter(const _di_IWideStringsAdapter Value);
	void __fastcall SetValue(const System::WideString Name, const System::WideString Value);
	void __fastcall WriteData(System::Classes::TWriter* Writer);
	System::WideChar __fastcall GetDelimiter();
	void __fastcall SetDelimiter(const System::WideChar Value);
	System::WideString __fastcall GetLineBreak();
	void __fastcall SetLineBreak(const System::WideString Value);
	System::WideChar __fastcall GetQuoteChar();
	void __fastcall SetQuoteChar(const System::WideChar Value);
	System::WideChar __fastcall GetNameValueSeparator();
	void __fastcall SetNameValueSeparator(const System::WideChar Value);
	bool __fastcall GetStrictDelimiter();
	void __fastcall SetStrictDelimiter(const bool Value);
	System::WideString __fastcall GetValueFromIndex(int Index);
	void __fastcall SetValueFromIndex(int Index, const System::WideString Value);
	
protected:
	virtual void __fastcall AssignTo(System::Classes::TPersistent* Dest);
	virtual void __fastcall DefineProperties(System::Classes::TFiler* Filer);
	void __fastcall Error(const System::WideString Msg, int Data)/* overload */;
	void __fastcall Error(System::PResStringRec Msg, int Data)/* overload */;
	System::WideString __fastcall ExtractName(const System::WideString S);
	virtual System::WideString __fastcall Get(int Index) = 0 ;
	virtual int __fastcall GetCapacity();
	virtual int __fastcall GetCount() = 0 ;
	virtual System::TObject* __fastcall GetObject(int Index);
	virtual System::WideString __fastcall GetTextStr();
	virtual void __fastcall Put(int Index, const System::WideString S);
	virtual void __fastcall PutObject(int Index, System::TObject* AObject);
	virtual void __fastcall SetCapacity(int NewCapacity);
	virtual void __fastcall SetTextStr(const System::WideString Value);
	virtual void __fastcall SetUpdateState(bool Updating);
	__property int UpdateCount = {read=FUpdateCount, nodefault};
	virtual int __fastcall CompareStrings(const System::WideString S1, const System::WideString S2);
	
public:
	__fastcall virtual ~TWideStrings();
	virtual int __fastcall Add(const System::WideString S);
	virtual int __fastcall AddObject(const System::WideString S, System::TObject* AObject);
	void __fastcall Append(const System::WideString S);
	virtual void __fastcall AddStrings(System::Classes::TStrings* Strings)/* overload */;
	virtual void __fastcall AddStrings(TWideStrings* Strings)/* overload */;
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	void __fastcall BeginUpdate();
	virtual void __fastcall Clear() = 0 ;
	virtual void __fastcall Delete(int Index) = 0 ;
	void __fastcall EndUpdate();
	HIDESBASE bool __fastcall Equals(TWideStrings* Strings);
	virtual void __fastcall Exchange(int Index1, int Index2);
	TWideStringsEnumerator* __fastcall GetEnumerator();
	virtual System::WideChar * __fastcall GetText();
	virtual int __fastcall IndexOf(const System::WideString S);
	virtual int __fastcall IndexOfName(const System::WideString Name);
	virtual int __fastcall IndexOfObject(System::TObject* AObject);
	virtual void __fastcall Insert(int Index, const System::WideString S) = 0 ;
	virtual void __fastcall InsertObject(int Index, const System::WideString S, System::TObject* AObject);
	virtual void __fastcall LoadFromFile(const System::WideString FileName)/* overload */;
	virtual void __fastcall LoadFromFile(const System::WideString FileName, System::Sysutils::TEncoding* Encoding)/* overload */;
	virtual void __fastcall LoadFromStream(System::Classes::TStream* Stream)/* overload */;
	virtual void __fastcall LoadFromStream(System::Classes::TStream* Stream, System::Sysutils::TEncoding* Encoding)/* overload */;
	virtual void __fastcall Move(int CurIndex, int NewIndex);
	virtual void __fastcall SaveToFile(const System::WideString FileName)/* overload */;
	virtual void __fastcall SaveToFile(const System::WideString FileName, System::Sysutils::TEncoding* Encoding)/* overload */;
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream)/* overload */;
	virtual void __fastcall SaveToStream(System::Classes::TStream* Stream, System::Sysutils::TEncoding* Encoding)/* overload */;
	virtual void __fastcall SetText(System::WideChar * Text);
	__property int Capacity = {read=GetCapacity, write=SetCapacity, nodefault};
	__property System::WideString CommaText = {read=GetCommaText, write=SetCommaText};
	__property int Count = {read=GetCount, nodefault};
	__property System::WideChar Delimiter = {read=GetDelimiter, write=SetDelimiter, nodefault};
	__property System::WideString DelimitedText = {read=GetDelimitedText, write=SetDelimitedText};
	__property System::WideString LineBreak = {read=GetLineBreak, write=SetLineBreak};
	__property System::WideString Names[int Index] = {read=GetName};
	__property System::TObject* Objects[int Index] = {read=GetObject, write=PutObject};
	__property System::WideChar QuoteChar = {read=GetQuoteChar, write=SetQuoteChar, nodefault};
	__property System::WideString Values[const System::WideString Name] = {read=GetValue, write=SetValue};
	__property System::WideString ValueFromIndex[int Index] = {read=GetValueFromIndex, write=SetValueFromIndex};
	__property System::WideChar NameValueSeparator = {read=GetNameValueSeparator, write=SetNameValueSeparator, nodefault};
	__property bool StrictDelimiter = {read=GetStrictDelimiter, write=SetStrictDelimiter, nodefault};
	__property System::WideString Strings[int Index] = {read=Get, write=Put/*, default*/};
	__property System::WideString Text = {read=GetTextStr, write=SetTextStr};
	__property _di_IWideStringsAdapter StringsAdapter = {read=FAdapter, write=SetStringsAdapter};
public:
	/* TObject.Create */ inline __fastcall TWideStrings() : System::Classes::TPersistent() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef TWideStringItem *PWideStringItem;

struct DECLSPEC_DRECORD TWideStringItem
{
public:
	System::WideString FString;
	System::TObject* FObject;
};


typedef System::DynamicArray<TWideStringItem> TWideStringItemList;

typedef TWideStringItemList *PWideStringItemList;

typedef int __fastcall (*TWideStringListSortCompare)(TWideStringList* List, int Index1, int Index2);

class PASCALIMPLEMENTATION TWideStringList : public TWideStrings
{
	typedef TWideStrings inherited;
	
private:
	TWideStringItemList FList;
	int FCount;
	int FCapacity;
	bool FSorted;
	System::Types::TDuplicates FDuplicates;
	bool FCaseSensitive;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnChanging;
	bool FOwnsObject;
	void __fastcall ExchangeItems(int Index1, int Index2);
	void __fastcall Grow();
	void __fastcall QuickSort(int L, int R, TWideStringListSortCompare SCompare);
	void __fastcall SetSorted(bool Value);
	void __fastcall SetCaseSensitive(const bool Value);
	
protected:
	virtual void __fastcall Changed();
	virtual void __fastcall Changing();
	virtual System::WideString __fastcall Get(int Index);
	virtual int __fastcall GetCapacity();
	virtual int __fastcall GetCount();
	virtual System::TObject* __fastcall GetObject(int Index);
	virtual void __fastcall Put(int Index, const System::WideString S);
	virtual void __fastcall PutObject(int Index, System::TObject* AObject);
	virtual void __fastcall SetCapacity(int NewCapacity);
	virtual void __fastcall SetUpdateState(bool Updating);
	virtual int __fastcall CompareStrings(const System::WideString S1, const System::WideString S2);
	virtual void __fastcall InsertItem(int Index, const System::WideString S, System::TObject* AObject);
	
public:
	__fastcall TWideStringList()/* overload */;
	__fastcall TWideStringList(bool OwnsObjects)/* overload */;
	__fastcall virtual ~TWideStringList();
	virtual int __fastcall Add(const System::WideString S);
	virtual int __fastcall AddObject(const System::WideString S, System::TObject* AObject);
	virtual void __fastcall Clear();
	virtual void __fastcall Delete(int Index);
	virtual void __fastcall Exchange(int Index1, int Index2);
	virtual bool __fastcall Find(const System::WideString S, int &Index);
	virtual int __fastcall IndexOf(const System::WideString S);
	virtual void __fastcall Insert(int Index, const System::WideString S);
	virtual void __fastcall InsertObject(int Index, const System::WideString S, System::TObject* AObject);
	virtual void __fastcall Sort();
	virtual void __fastcall CustomSort(TWideStringListSortCompare Compare);
	__property System::Types::TDuplicates Duplicates = {read=FDuplicates, write=FDuplicates, nodefault};
	__property bool Sorted = {read=FSorted, write=SetSorted, nodefault};
	__property bool CaseSensitive = {read=FCaseSensitive, write=SetCaseSensitive, nodefault};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property System::Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
	__property bool OwnsObjects = {read=FOwnsObject, write=FOwnsObject, nodefault};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Widestrings */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_WIDESTRINGS)
using namespace System::Widestrings;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_WidestringsHPP
