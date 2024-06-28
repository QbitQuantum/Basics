// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Xml.Internal.WideStringUtils.pas' rev: 34.00 (Windows)

#ifndef Xml_Internal_WidestringutilsHPP
#define Xml_Internal_WidestringutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Xml
{
namespace Internal
{
namespace Widestringutils
{
//-- forward type declarations -----------------------------------------------
struct TUtilsWideStringItem;
class DELPHICLASS TUtilsWideStringList;
class DELPHICLASS TUtilsNameValueList;
class DELPHICLASS TUtilsNameValueTree;
class DELPHICLASS TUtilsCustomWideStr;
class DELPHICLASS TUtilsWideStringStream;
//-- type declarations -------------------------------------------------------
struct DECLSPEC_DRECORD TUtilsWideStringItem
{
public:
	System::WideString FString;
	System::TObject* FObject;
};


typedef System::DynamicArray<TUtilsWideStringItem> TUtilsWideStringItemList;

typedef TUtilsWideStringItemList *PUtilsWideStringItemList;

class PASCALIMPLEMENTATION TUtilsWideStringList : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
public:
	System::WideString operator[](int Index) { return this->WideStrings[Index]; }
	
private:
	int FCapacity;
	int FCount;
	System::Types::TDuplicates FDuplicates;
	TUtilsWideStringItemList FList;
	bool FSorted;
	int FUpdateCount;
	System::Classes::TNotifyEvent FOnChange;
	System::Classes::TNotifyEvent FOnChanging;
	void __fastcall ExchangeItems(int Index1, int Index2);
	void __fastcall Grow();
	void __fastcall InsertItem(int Index, const System::WideString S, System::TObject* AObject);
	void __fastcall QuickSort(int L, int R);
	void __fastcall SetSorted(const bool Value);
	
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
	
public:
	__fastcall virtual ~TUtilsWideStringList();
	virtual int __fastcall Add(System::WideString S);
	virtual int __fastcall AddObject(System::WideString S, System::TObject* AObject);
	virtual void __fastcall AddWideStrings(TUtilsWideStringList* Strings);
	virtual void __fastcall Append(System::WideString S);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall BeginUpdate();
	virtual void __fastcall Clear();
	virtual void __fastcall Delete(int Index);
	virtual void __fastcall EndUpdate();
	virtual void __fastcall Exchange(int Index1, int Index2);
	virtual bool __fastcall Find(const System::WideString S, int &Index);
	virtual int __fastcall IndexOf(const System::WideString S);
	virtual int __fastcall IndexOfLast(const System::WideString S);
	virtual void __fastcall Insert(int Index, const System::WideString S);
	virtual void __fastcall InsertObject(int Index, const System::WideString S, System::TObject* AObject);
	virtual void __fastcall Sort();
	__property int Capacity = {read=GetCapacity, write=SetCapacity, nodefault};
	__property int Count = {read=GetCount, nodefault};
	__property System::Types::TDuplicates Duplicates = {read=FDuplicates, write=FDuplicates, default=0};
	__property System::TObject* Objects[int Index] = {read=GetObject, write=PutObject};
	__property bool Sorted = {read=FSorted, write=SetSorted, default=0};
	__property System::WideString WideStrings[int Index] = {read=Get, write=Put/*, default*/};
	__property System::Classes::TNotifyEvent OnChange = {read=FOnChange, write=FOnChange};
	__property System::Classes::TNotifyEvent OnChanging = {read=FOnChanging, write=FOnChanging};
public:
	/* TObject.Create */ inline __fastcall TUtilsWideStringList() : System::Classes::TPersistent() { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUtilsNameValueList : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TUtilsWideStringList* FNames;
	TUtilsWideStringList* FValues;
	virtual int __fastcall GetLength();
	virtual int __fastcall GetCapacity();
	System::Types::TDuplicates __fastcall GetDuplicates();
	virtual System::WideString __fastcall GetName(int Index);
	virtual System::TObject* __fastcall GetObject(int Index);
	virtual System::WideString __fastcall GetValue(int Index);
	virtual void __fastcall PutObject(int Index, System::TObject* AObject);
	virtual void __fastcall SetCapacity(const int Value);
	void __fastcall SetDuplicates(const System::Types::TDuplicates Value);
	void __fastcall SetSorted(const bool Value);
	bool __fastcall GetSorted();
	
public:
	__fastcall TUtilsNameValueList();
	__fastcall virtual ~TUtilsNameValueList();
	virtual int __fastcall Add(const System::WideString Name, const System::WideString Value);
	virtual int __fastcall AddObject(const System::WideString Name, const System::WideString Value, System::TObject* AObject);
	virtual void __fastcall AddNameValueList(TUtilsNameValueList* const Nvl);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Clear();
	virtual void __fastcall Delete(const int Index);
	virtual void __fastcall Exchange(const int Index1, const int Index2);
	virtual int __fastcall IndexOf(const System::WideString Name, const System::WideString Value);
	virtual int __fastcall IndexOfLast(const System::WideString Name, const System::WideString Value);
	virtual int __fastcall IndexOfLastName(const System::WideString Name);
	virtual int __fastcall IndexOfName(const System::WideString Name);
	virtual void __fastcall Insert(const int Index, const System::WideString Name, const System::WideString Value);
	virtual bool __fastcall Find(const System::WideString Name, const System::WideString Value, int &Index);
	virtual bool __fastcall FindOfName(const System::WideString Name, int &Index);
	virtual void __fastcall Sort();
	__property int Capacity = {read=GetCapacity, write=SetCapacity, nodefault};
	__property System::Types::TDuplicates Duplicates = {read=GetDuplicates, write=SetDuplicates, default=0};
	__property int Length = {read=GetLength, nodefault};
	__property System::WideString Names[int Index] = {read=GetName};
	__property System::TObject* Objects[int Index] = {read=GetObject, write=PutObject};
	__property bool Sorted = {read=GetSorted, write=SetSorted, default=0};
	__property System::WideString Values[int Index] = {read=GetValue};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUtilsNameValueTree : public TUtilsNameValueList
{
	typedef TUtilsNameValueList inherited;
	
private:
	TUtilsNameValueTree* FParentTree;
	TUtilsNameValueTree* __fastcall GetChild(int Index);
	
public:
	__fastcall virtual ~TUtilsNameValueTree();
	virtual int __fastcall AddChild(const System::WideString Name, const System::WideString Value, TUtilsNameValueTree* const child);
	virtual int __fastcall AddChildObject(const System::WideString Name, const System::WideString Value, TUtilsNameValueTree* const Child, System::TObject* const AObject);
	virtual void __fastcall Assign(System::Classes::TPersistent* Source);
	virtual void __fastcall Clear();
	virtual void __fastcall Delete(const int Index);
	virtual bool __fastcall HasChild(const int Index);
	virtual int __fastcall IndexOfChild(TUtilsNameValueTree* const Child);
	virtual void __fastcall InsertChild(const int Index, const System::WideString Name, const System::WideString Value, TUtilsNameValueTree* const Child);
	virtual bool __fastcall IsDescendantOf(TUtilsNameValueTree* const Nvtree);
	virtual TUtilsNameValueTree* __fastcall ReplaceChild(const int Index, TUtilsNameValueTree* const NewChild);
	__property TUtilsNameValueTree* Children[int Index] = {read=GetChild};
	__property TUtilsNameValueTree* ParentTree = {read=FParentTree};
public:
	/* TUtilsNameValueList.Create */ inline __fastcall TUtilsNameValueTree() : TUtilsNameValueList() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUtilsCustomWideStr : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::WideChar operator[](int Index) { return this->WideChars[Index]; }
	
private:
	int FActualLen;
	int FCapacity;
	System::WideString FContent;
	
protected:
	virtual System::WideChar __fastcall GetWideChars(int Index);
	virtual void __fastcall SetWideChars(int Index, System::WideChar C);
	
public:
	__fastcall TUtilsCustomWideStr();
	virtual void __fastcall AddUCS4Char(const int CodePoint);
	virtual void __fastcall AddWideChar(const System::WideChar C);
	virtual void __fastcall Clear();
	virtual void __fastcall AddWideString(const System::WideString S);
	virtual bool __fastcall EndsWith(const System::WideString S);
	virtual bool __fastcall IsEqual(const System::WideString S);
	virtual bool __fastcall StartsWith(const System::WideString S);
	virtual System::WideString __fastcall Value();
	__property int Length = {read=FActualLen, nodefault};
	__property System::WideChar WideChars[int Index] = {read=GetWideChars, write=SetWideChars/*, default*/};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUtilsCustomWideStr() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TUtilsWideStringStream : public System::Classes::TStream
{
	typedef System::Classes::TStream inherited;
	
private:
	char *FDataStringP;
	int FSize;
	int FCapacity;
	int FPosition;
	
protected:
	virtual void __fastcall SetCapacity(int NewCapacity);
	virtual void __fastcall SetSize(int NewSize)/* overload */;
	void __fastcall SetStringPosition(int Value);
	int __fastcall GetStringPosition();
	void __fastcall SetStringLength(int Value);
	int __fastcall GetStringLength();
	System::WideString __fastcall GetDataString();
	
public:
	__fastcall TUtilsWideStringStream(const System::WideString AString);
	__fastcall virtual ~TUtilsWideStringStream();
	virtual int __fastcall Read(void *Buffer, int Count)/* overload */;
	virtual __int64 __fastcall Seek(const __int64 Offset, System::Classes::TSeekOrigin Origin)/* overload */;
	virtual int __fastcall Write(const void *Buffer, int Count)/* overload */;
	System::WideString __fastcall ReadString(int Count);
	void __fastcall WriteString(const System::WideString AString);
	__property int Capacity = {read=FCapacity, write=SetCapacity, nodefault};
	__property int StringLength = {read=GetStringLength, write=SetStringLength, nodefault};
	__property int StringPosition = {read=GetStringPosition, write=SetStringPosition, nodefault};
	__property System::WideString DataString = {read=GetDataString};
	/* Hoisted overloads: */
	
protected:
	inline void __fastcall  SetSize(const __int64 NewSize){ System::Classes::TStream::SetSize(NewSize); }
	
public:
#ifndef _WIN64
	inline int __fastcall  Read(System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::DynamicArray<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Read(System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Read(Buffer, Offset, Count); }
	inline int __fastcall  Read(System::TArray__1<System::Byte> &Buffer, int Count){ return System::Classes::TStream::Read(Buffer, Count); }
#endif /* _WIN64 */
	inline int __fastcall  Seek(int Offset, System::Word Origin){ return System::Classes::TStream::Seek(Offset, Origin); }
#ifndef _WIN64
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::DynamicArray<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#else /* _WIN64 */
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Offset, int Count){ return System::Classes::TStream::Write(Buffer, Offset, Count); }
	inline int __fastcall  Write(const System::TArray__1<System::Byte> Buffer, int Count){ return System::Classes::TStream::Write(Buffer, Count); }
#endif /* _WIN64 */
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE int __fastcall CompareWideStr(const System::WideString S1, const System::WideString S2);
extern DELPHI_PACKAGE bool __fastcall EndsWideStr(const System::WideString SubString, const System::WideString S);
extern DELPHI_PACKAGE bool __fastcall StartsWideStr(const System::WideString SubString, const System::WideString S);
extern DELPHI_PACKAGE System::WideString __fastcall TranslateWideString(const System::WideString S, const System::WideString Pattern_1, const System::WideString Pattern_2);
extern DELPHI_PACKAGE System::WideString __fastcall TrimSpace(const System::WideString S);
extern DELPHI_PACKAGE System::Word __fastcall ExtractUTF16HighSurrogate(const int Value);
extern DELPHI_PACKAGE System::Word __fastcall ExtractUTF16LowSurrogate(const int Value);
extern DELPHI_PACKAGE int __fastcall UTF16SurrogateToInt(const System::Word HighSurrogate, const System::Word LowSurrogate);
extern DELPHI_PACKAGE bool __fastcall IsUTF16HighSurrogate(const System::Word Value);
extern DELPHI_PACKAGE bool __fastcall IsUTF16LowSurrogate(const System::Word Value);
}	/* namespace Widestringutils */
}	/* namespace Internal */
}	/* namespace Xml */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL_WIDESTRINGUTILS)
using namespace Xml::Internal::Widestringutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML_INTERNAL)
using namespace Xml::Internal;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_XML)
using namespace Xml;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Xml_Internal_WidestringutilsHPP
