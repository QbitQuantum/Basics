// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXPlatform.pas' rev: 34.00 (Windows)

#ifndef Data_DbxplatformHPP
#define Data_DbxplatformHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Generics.Collections.hpp>
#include <System.SysUtils.hpp>
#include <Data.FmtBcd.hpp>
#include <Data.SqlTimSt.hpp>
#include <System.Classes.hpp>
#include <System.SyncObjs.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxplatform
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDSInvocationMetadata;
class DELPHICLASS TDBXInt32Object;
class DELPHICLASS TDBXTokenizer;
class DELPHICLASS TBaseTransportFilterCollection;
class DELPHICLASS TFactoryObject;
class DELPHICLASS TBaseTransportFactoryTools;
class DELPHICLASS TBaseTransportFilterItem;
class DELPHICLASS TBaseFilterProperties;
class DELPHICLASS TDBXArrayList;
class DELPHICLASS TDBXObjectStore;
class DELPHICLASS TDBXPlatform;
class DELPHICLASS TDBXSemaphore;
//-- type declarations -------------------------------------------------------
typedef int TInt32;

typedef System::DynamicArray<char> TDBXAnsiChars;

typedef System::DynamicArray<System::WideChar> TDBXWideChars;

typedef char * TDBXAnsiString;

typedef char * TDBXAnsiStringBuilder;

typedef System::WideChar * TDBXWideString;

typedef System::WideChar * TDBXWideStringBuilder;

typedef System::DynamicArray<int> TDBXInt32s;

typedef System::DynamicArray<bool> TDBXBooleans;

typedef System::DynamicArray<System::UnicodeString> TDBXStringArray;

typedef System::DynamicArray<System::TObject*> TDBXObjectArray;

typedef System::Classes::TStringList TDBXStringList;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDSInvocationMetadata : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	int FResponseCode;
	System::UnicodeString FResponseMessage;
	System::UnicodeString FResponseContent;
	System::UnicodeString FResponseContentType;
	bool FCloseSession;
	System::Classes::TStrings* FQueryParams;
	
public:
	__fastcall virtual TDSInvocationMetadata();
	__fastcall virtual ~TDSInvocationMetadata();
	__property int ResponseCode = {read=FResponseCode, write=FResponseCode, nodefault};
	__property System::UnicodeString ResponseMessage = {read=FResponseMessage, write=FResponseMessage};
	__property System::UnicodeString ResponseContent = {read=FResponseContent, write=FResponseContent};
	__property System::UnicodeString ResponseContentType = {read=FResponseContentType, write=FResponseContentType};
	__property bool CloseSession = {read=FCloseSession, write=FCloseSession, nodefault};
	__property System::Classes::TStrings* QueryParams = {read=FQueryParams};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXInt32Object : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall TDBXInt32Object(const int Value);
	__fastcall virtual ~TDBXInt32Object();
	int __fastcall IntValue();
	
private:
	int FValue;
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXTokenizer : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FOriginal;
	System::UnicodeString FDelimiters;
	int FNextPos;
	
public:
	__fastcall TDBXTokenizer(const System::UnicodeString Original, const System::UnicodeString Delimiters);
	bool __fastcall HasMoreTokens();
	System::UnicodeString __fastcall NextToken();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXTokenizer() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

class PASCALIMPLEMENTATION TBaseTransportFilterCollection : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
private:
	System::Classes::TNotifyEvent FEvent;
	
protected:
	void __fastcall NotifyChange();
	
public:
	__fastcall virtual ~TBaseTransportFilterCollection();
	HIDESBASE System::Classes::TCollectionItem* __fastcall GetItem(int Index);
	__property System::Classes::TNotifyEvent OnChange = {read=FEvent, write=FEvent};
public:
	/* TCollection.Create */ inline __fastcall TBaseTransportFilterCollection(System::Classes::TCollectionItemClass ItemClass) : System::Classes::TCollection(ItemClass) { }
	
};


#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION DECLSPEC_DRTTI TFactoryObject : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__fastcall virtual TFactoryObject();
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TFactoryObject() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
typedef System::TMetaClass* TObjectClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TObjectClass);
#endif /* _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TBaseTransportFactoryTools : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	__classmethod System::UnicodeString __fastcall InvokeStringFunction(TObjectClass objClass, System::UnicodeString methodName);
public:
	/* TObject.Create */ inline __fastcall TBaseTransportFactoryTools() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TBaseTransportFactoryTools() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

typedef TFactoryObject TBaseTransportFilter;

class PASCALIMPLEMENTATION TBaseTransportFilterItem : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	System::Classes::TNotifyEvent FEvent;
	
protected:
	void __fastcall NotifyChange();
	
public:
	__fastcall virtual TBaseTransportFilterItem(System::Classes::TCollection* Collection);
	void __fastcall OnChangeNotify(TBaseTransportFilterCollection* filter);
	__property System::Classes::TNotifyEvent OnChange = {read=FEvent, write=FEvent};
public:
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TBaseTransportFilterItem() { }
	
};


class PASCALIMPLEMENTATION TBaseFilterProperties : public System::Classes::TStringList
{
	typedef System::Classes::TStringList inherited;
	
public:
	HIDESBASE System::UnicodeString __fastcall GetName(int Index);
	HIDESBASE System::UnicodeString __fastcall GetValue(int Index);
	HIDESBASE void __fastcall Add(const System::UnicodeString Name, const System::UnicodeString Value);
public:
	/* TStringList.Create */ inline __fastcall TBaseFilterProperties()/* overload */ : System::Classes::TStringList() { }
	/* TStringList.Create */ inline __fastcall TBaseFilterProperties(bool OwnsObjects)/* overload */ : System::Classes::TStringList(OwnsObjects) { }
	/* TStringList.Create */ inline __fastcall TBaseFilterProperties(System::WideChar QuoteChar, System::WideChar Delimiter)/* overload */ : System::Classes::TStringList(QuoteChar, Delimiter) { }
	/* TStringList.Create */ inline __fastcall TBaseFilterProperties(System::WideChar QuoteChar, System::WideChar Delimiter, System::Classes::TStringsOptions Options)/* overload */ : System::Classes::TStringList(QuoteChar, Delimiter, Options) { }
	/* TStringList.Create */ inline __fastcall TBaseFilterProperties(System::Types::TDuplicates Duplicates, bool Sorted, bool CaseSensitive)/* overload */ : System::Classes::TStringList(Duplicates, Sorted, CaseSensitive) { }
	/* TStringList.Destroy */ inline __fastcall virtual ~TBaseFilterProperties() { }
	
};


#ifndef _WIN64
typedef System::TMetaClass* TTransportFilterClass;
#else /* _WIN64 */
_DECLARE_METACLASS(System::TMetaClass, TTransportFilterClass);
#endif /* _WIN64 */

typedef TDBXObjectArray TDBXFreeArray;

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXArrayList : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::TObject* operator[](int Index) { return this->Values[Index]; }
	
private:
	System::Generics::Collections::TList__1<System::TObject*>* FList;
	System::TObject* __fastcall GetValue(int Index);
	void __fastcall SetValue(int Index, System::TObject* Value);
	int __fastcall GetCount();
	
public:
	__fastcall TDBXArrayList();
	__fastcall virtual ~TDBXArrayList();
	void __fastcall Clear();
	void __fastcall Add(System::TObject* Element);
	void __fastcall RemoveAt(int Index);
	void __fastcall Remove(int Index)/* overload */;
	void __fastcall Remove(System::TObject* Element)/* overload */;
	__property int Count = {read=GetCount, nodefault};
	__property System::TObject* Values[int Index] = {read=GetValue, write=SetValue/*, default*/};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXObjectStore : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	System::TObject* operator[](const System::UnicodeString Name) { return this->Objects[Name]; }
	
private:
	bool FOwnsObjects;
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::TObject*>* FDictionary;
	System::TObject* __fastcall GetObjectFromName(const System::UnicodeString Name);
	void __fastcall SetObjectByName(const System::UnicodeString Name, System::TObject* const Value);
	bool __fastcall GetOwnsObjects();
	
public:
	__fastcall TDBXObjectStore()/* overload */;
	__fastcall TDBXObjectStore(const bool AOwnsObjects)/* overload */;
	__fastcall virtual ~TDBXObjectStore();
	bool __fastcall ContainsKey(const System::UnicodeString Name);
	void __fastcall Delete(const System::UnicodeString Name);
	System::TObject* __fastcall Extract(const System::UnicodeString Name);
	__property System::TObject* Objects[const System::UnicodeString Name] = {read=GetObjectFromName, write=SetObjectByName/*, default*/};
	__property bool OwnsObjects = {read=GetOwnsObjects, nodefault};
#ifndef _WIN64
	System::DynamicArray<System::UnicodeString> __fastcall Keys();
#else /* _WIN64 */
	System::TArray__1<System::UnicodeString> __fastcall Keys();
#endif /* _WIN64 */
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXPlatform : public System::TObject
{
	typedef System::TObject inherited;
	
public:
#ifndef _WIN64
	static System::DynamicArray<System::Byte> __fastcall AnsiStrToBytes(const System::AnsiString Value);
	static System::AnsiString __fastcall BytesToAnsiStr(const System::DynamicArray<System::Byte> Value);
#else /* _WIN64 */
	static System::TArray__1<System::Byte> __fastcall AnsiStrToBytes(const System::AnsiString Value);
	static System::AnsiString __fastcall BytesToAnsiStr(const System::TArray__1<System::Byte> Value);
#endif /* _WIN64 */
	static void __fastcall CopyStringBuilder(const char * Value, System::AnsiString &Dest);
	static void __fastcall CopyStringToBuilder(const System::AnsiString Source, int AnsiStringBuilderSize, char * &Value);
	static System::AnsiString __fastcall CreateAnsiString(const TDBXAnsiChars Source, int Count);
#ifndef _WIN64
	static System::DynamicArray<System::Byte> __fastcall WideStrToBytes(const System::UnicodeString Value);
	static System::UnicodeString __fastcall BytesToWideStr(const System::DynamicArray<System::Byte> Value);
#else /* _WIN64 */
	static System::TArray__1<System::Byte> __fastcall WideStrToBytes(const System::UnicodeString Value);
	static System::UnicodeString __fastcall BytesToWideStr(const System::TArray__1<System::Byte> Value);
#endif /* _WIN64 */
	static int __fastcall GetStringBuilderLength(const char * Value);
	static char * __fastcall CreateStringBuilder(int Length);
	static void __fastcall FreeAndNilStringBuilder(char * &Value);
	static void __fastcall ResizeStringBuilder(char * &Value, int Size);
	static int __fastcall GetWideStringBuilderLength(const System::WideChar * Value);
	static System::WideChar * __fastcall CreateWideStringBuilder(int Length);
	static System::UnicodeString __fastcall ToWideString(const System::WideChar * Value);
	static void __fastcall CopyWideStringBuilder(const System::WideChar * Value, System::UnicodeString &Dest);
	static void __fastcall ResizeWideStringBuilder(System::WideChar * &Value, int Size);
	static void __fastcall FreeAndNilWideStringBuilder(System::WideChar * &Value);
	static void __fastcall CopyWideStringToBuilder(const System::UnicodeString Source, int WideStringBuilderSize, System::WideChar * &Value);
	static void __fastcall CopyInt32Array(const TDBXInt32s Source, int SourceOffset, const TDBXInt32s Dest, int DestOffset, int Count);
	static void __fastcall CopyCharArray(const TDBXWideChars Source, int SourceOffset, const TDBXWideChars Dest, int DestOffset, int Count);
#ifndef _WIN64
	static void __fastcall CopyByteArray(const System::DynamicArray<System::Byte> Source, int SourceOffset, const System::DynamicArray<System::Byte> Dest, int DestOffset, int Count);
#else /* _WIN64 */
	static void __fastcall CopyByteArray(const System::TArray__1<System::Byte> Source, int SourceOffset, const System::TArray__1<System::Byte> Dest, int DestOffset, int Count);
#endif /* _WIN64 */
	static System::UnicodeString __fastcall CreateWideString(const TDBXWideChars Source, int Count);
#ifndef _WIN64
	__classmethod void __fastcall WriteAsciiBytes(const System::UnicodeString Message, System::DynamicArray<System::Byte> ByteBuffer, int Offset, int Count);
#else /* _WIN64 */
	__classmethod void __fastcall WriteAsciiBytes(const System::UnicodeString Message, System::TArray__1<System::Byte> ByteBuffer, int Offset, int Count);
#endif /* _WIN64 */
	__classmethod double __fastcall Int64BitsToDouble(const __int64 Value);
	__classmethod __int64 __fastcall DoubleToInt64Bits(const double Value);
	static float __fastcall Int32BitsToSingle(const int Value);
	static int __fastcall SingleToInt32Bits(const float Value);
#ifndef _WIN64
	static void __fastcall CopyBytesToAnsiChars(const System::DynamicArray<System::Byte> Source, int SourceOffset, const TDBXAnsiChars Dest, int DestOffset, int Count);
	static void __fastcall CopyBytesToWideChars(const System::DynamicArray<System::Byte> Source, int SourceOffset, const TDBXWideChars Dest, int DestOffset, int Count);
	static void __fastcall CopyInt32(const int Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyInt16(const short Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyUInt16(const System::Word Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyInt64(const __int64 Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyInt8(const System::Int8 Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyUInt8(const System::Byte Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopySqlTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopySqlTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyBcd(const Data::Fmtbcd::TBcd &Value, const System::DynamicArray<System::Byte> Dest, const int DestOffset);
#else /* _WIN64 */
	static void __fastcall CopyBytesToAnsiChars(const System::TArray__1<System::Byte> Source, int SourceOffset, const TDBXAnsiChars Dest, int DestOffset, int Count);
	static void __fastcall CopyBytesToWideChars(const System::TArray__1<System::Byte> Source, int SourceOffset, const TDBXWideChars Dest, int DestOffset, int Count);
	static void __fastcall CopyInt32(const int Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyInt16(const short Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyUInt16(const System::Word Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyInt64(const __int64 Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyInt8(const System::Int8 Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyUInt8(const System::Byte Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopySqlTimeStamp(const Data::Sqltimst::TSQLTimeStamp &Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopySqlTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
	static void __fastcall CopyBcd(const Data::Fmtbcd::TBcd &Value, const System::TArray__1<System::Byte> Dest, const int DestOffset);
#endif /* _WIN64 */
	__classmethod void __fastcall Sleep(const __int64 Duration);
	static System::UnicodeString __fastcall GetClassName(System::TObject* ObjectValue);
	static System::Sysutils::Exception* __fastcall GetNestedException(System::Sysutils::Exception* Ex);
	__classmethod System::UnicodeString __fastcall GetPublicKeyToken();
	static System::UnicodeString __fastcall JsonFloat(double Value);
	static double __fastcall JsonToFloat(System::UnicodeString DotValue);
	__classmethod bool __fastcall TryJsonToFloat(System::UnicodeString DotValue, double &Value);
	static bool __fastcall IsBoolean(const System::UnicodeString value);
#ifndef _WIN64
	__classmethod System::UnicodeString __fastcall StringOf(System::DynamicArray<System::Byte> Data, const int Size);
#else /* _WIN64 */
	__classmethod System::UnicodeString __fastcall StringOf(System::TArray__1<System::Byte> Data, const int Size);
#endif /* _WIN64 */
	
private:
	static void __fastcall UnexpectedStringOverflow(const System::UnicodeString Source, int WideStringBuilderSize)/* overload */;
	static void __fastcall UnexpectedStringOverflow(const System::AnsiString Source, int AnsiStringBuilderSize)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TDBXPlatform() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXPlatform() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TDBXSemaphore : public System::Syncobjs::TSemaphore
{
	typedef System::Syncobjs::TSemaphore inherited;
	
private:
	int FCount;
	
public:
	__fastcall TDBXSemaphore(int Count);
	HIDESBASE bool __fastcall Acquire(__int64 Timeout);
public:
	/* THandleObject.Destroy */ inline __fastcall virtual ~TDBXSemaphore() { }
	
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
extern DELPHI_PACKAGE TDSInvocationMetadata* __fastcall GetInvocationMetadata(bool CreateIfNil = true);
extern DELPHI_PACKAGE void __fastcall SetInvocationMetadata(TDSInvocationMetadata* MetaData);
extern DELPHI_PACKAGE void __fastcall ClearInvocationMetadata(void);
extern DELPHI_PACKAGE int __fastcall Incr(int &Arg);
extern DELPHI_PACKAGE int __fastcall Decr(int &Arg);
extern DELPHI_PACKAGE int __fastcall IncrAfter(int &Arg);
extern DELPHI_PACKAGE int __fastcall DecrAfter(int &Arg);
extern DELPHI_PACKAGE System::UnicodeString __fastcall C_Conditional(const bool Condition, const System::UnicodeString TruePart, const System::UnicodeString FalsePart);
extern DELPHI_PACKAGE int __fastcall CompareTimeStamp(const Data::Sqltimst::TSQLTimeStamp &ATimeStamp, const Data::Sqltimst::TSQLTimeStamp &BTimeStamp);
extern DELPHI_PACKAGE int __fastcall CompareTimeStampOffset(const Data::Sqltimst::TSQLTimeStampOffset &ATimeStamp, const Data::Sqltimst::TSQLTimeStampOffset &BTimeStamp);
extern DELPHI_PACKAGE void __fastcall FreeObjectArray(TDBXObjectArray &ArrayObject);
extern DELPHI_PACKAGE bool __fastcall IsIdentifierStart(const System::WideChar Ch);
extern DELPHI_PACKAGE bool __fastcall IsIdentifierPart(const System::WideChar Ch);
extern DELPHI_PACKAGE System::UnicodeString __fastcall FormatMessage(const System::UnicodeString FormatString, const TDBXStringArray Parameters);
}	/* namespace Dbxplatform */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXPLATFORM)
using namespace Data::Dbxplatform;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxplatformHPP
