// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Mac.CFUtils.pas' rev: 34.00 (iOS)

#ifndef System_Mac_CfutilsHPP
#define System_Mac_CfutilsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <Macapi.CoreFoundation.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <System.Rtti.hpp>
#include <System.TypInfo.hpp>
#include <System.Generics.Collections.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Mac
{
namespace Cfutils
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS ECFPropertyListException;
struct TCFArray;
struct TCFBoolean;
struct TCFData;
struct TCFDate;
struct TCFDictionary;
struct TCFNumber;
struct TCFString;
struct TCFPropertyList;
struct CFGregorianDateHelper /* Helper for record 'CFGregorianDate' */;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION ECFPropertyListException : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall ECFPropertyListException(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall ECFPropertyListException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall ECFPropertyListException(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall ECFPropertyListException(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall ECFPropertyListException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall ECFPropertyListException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall ECFPropertyListException(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall ECFPropertyListException(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECFPropertyListException(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall ECFPropertyListException(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECFPropertyListException(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall ECFPropertyListException(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~ECFPropertyListException() { }
	
};


struct DECLSPEC_DRECORD TCFArray
{
public:
	__CFArray *Value;
	
private:
	template<typename T> System::TArray__1<T> __fastcall DoAsArray(bool Release)/* overload */;
	
public:
	__fastcall TCFArray(const System::TArray__1<void *> AValue)/* overload */;
	template<typename T> static TCFArray __fastcall Create(const System::TArray__1<T> AValue)/* overload */;
	System::TArray__1<void *> __fastcall AsArray(bool Release = false)/* overload */;
	template<typename T> System::TArray__1<T> __fastcall AsArray(bool Release = false)/* overload */;
	bool __fastcall TryAsArray(/* out */ System::TArray__1<void *> &AResult, bool Release = false)/* overload */;
	template<typename T> bool __fastcall TryAsArray(/* out */ System::TArray__1<T> &AResult, bool Release = false)/* overload */;
	System::Typinfo::PTypeInfo __fastcall GetTypeInfo();
	template<typename T> bool __fastcall IsArrayOf();
	long __fastcall Count();
	long __fastcall CountOfValue(void * Val);
	static TCFArray __fastcall _op_Implicit(CFArrayRef AValue);
	TCFArray() {}
	
	TCFArray& operator =(CFArrayRef AValue) { *this = TCFArray::_op_Implicit(AValue); return *this; }
};


struct DECLSPEC_DRECORD TCFBoolean
{
public:
	__CFBoolean *Value;
	
private:
	bool __fastcall DoAsBoolean();
	
public:
	bool __fastcall AsBoolean();
	bool __fastcall TryAsBoolean(/* out */ bool &AResult);
	static TCFBoolean __fastcall _op_Implicit(bool AValue);
	__fastcall operator bool();
	static TCFBoolean __fastcall _op_Implicit(CFBooleanRef AValue);
	
	TCFBoolean& operator =(bool AValue) { *this = TCFBoolean::_op_Implicit(AValue); return *this; }
	TCFBoolean& operator =(CFBooleanRef AValue) { *this = TCFBoolean::_op_Implicit(AValue); return *this; }
};


struct DECLSPEC_DRECORD TCFData
{
public:
	__CFData *Value;
	
private:
	template<typename T> System::TArray__1<T> __fastcall DoAsArray(bool Release)/* overload */;
	template<typename T> T __fastcall DoAsType(bool Release)/* overload */;
	
public:
	__fastcall TCFData(const System::TArray__1<System::Byte> AValue);
	template<typename T> static TCFData __fastcall CreateFromArray(const System::TArray__1<T> AValue);
	template<typename T> static TCFData __fastcall CreateFromType(const T AValue);
	System::TArray__1<System::Byte> __fastcall AsTBytes(bool Release = false);
	template<typename T> System::TArray__1<T> __fastcall AsArray(bool Release = false)/* overload */;
	template<typename T> bool __fastcall TryAsArray(/* out */ System::TArray__1<T> &AResult, bool Release = false)/* overload */;
	template<typename T> T __fastcall AsType(bool Release = false)/* overload */;
	template<typename T> bool __fastcall TryAsType(/* out */ T &AResult, bool Release = false)/* overload */;
	static TCFData __fastcall _op_Explicit(const System::TArray__1<System::Byte> AValue);
	__fastcall operator System::TArray__1<System::Byte>();
	static TCFData __fastcall _op_Implicit(CFDataRef AValue);
	TCFData() {}
	
	TCFData& operator =(CFDataRef AValue) { *this = TCFData::_op_Implicit(AValue); return *this; }
};


struct DECLSPEC_DRECORD TCFDate
{
public:
	__CFDate *Value;
	
private:
	System::TDateTime __fastcall DoAsTDateTime(bool Release, bool UTC);
	
public:
	__fastcall TCFDate(System::TDateTime AValue, bool UTC)/* overload */;
	System::TDateTime __fastcall AsTDateTime(bool Release = false);
	bool __fastcall TryAsTDateTime(/* out */ System::TDateTime &AResult, bool Release = false);
	System::TDateTime __fastcall AsTDateTimeUTC(bool Release = false);
	bool __fastcall TryAsTDateTimeUTC(/* out */ System::TDateTime &AResult, bool Release = false);
	static TCFDate __fastcall _op_Explicit(System::TDateTime AValue);
	__fastcall operator System::TDateTime();
	static TCFDate __fastcall _op_Implicit(CFDateRef AValue);
	TCFDate() {}
	
	TCFDate& operator =(CFDateRef AValue) { *this = TCFDate::_op_Implicit(AValue); return *this; }
};


struct DECLSPEC_DRECORD TCFDictionary
{
	
private:
	class DELPHICLASS TCFKeyValueEnumerator;
	class PASCALIMPLEMENTATION TCFKeyValueEnumerator : public System::TObject
	{
		typedef System::TObject inherited;
		
		
	private:
		typedef System::DynamicArray<System::UnicodeString> _TCFDictionary_TCFKeyValueEnumerator__1;
		
		typedef System::DynamicArray<void *> _TCFDictionary_TCFKeyValueEnumerator__2;
		
		
	private:
		int FIndex;
		_TCFDictionary_TCFKeyValueEnumerator__1 FKeys;
		_TCFDictionary_TCFKeyValueEnumerator__2 FValues;
		
	public:
		__fastcall TCFKeyValueEnumerator(CFDictionaryRef DictRef);
		System::Generics::Collections::TPair__2<System::UnicodeString,void *> __fastcall GetCurrent();
		bool __fastcall MoveNext();
		__property System::Generics::Collections::TPair__2<System::UnicodeString,void *> Current = {read=GetCurrent};
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TCFKeyValueEnumerator() { }
		
	};
	
	
	
public:
	void * operator[](const System::UnicodeString Key) { return this->Items[Key]; }
	
public:
	__CFDictionary *Value;
	
private:
	System::TArray__1<System::UnicodeString> __fastcall DoGetKeys();
	System::TArray__1<void *> __fastcall DoGetValues();
	
public:
	void * __fastcall GetValue(const System::UnicodeString Key);
	void __fastcall SetValue(const System::UnicodeString Key, void * Value);
	System::TArray__1<System::UnicodeString> __fastcall GetKeys();
	bool __fastcall TryGetKeys(/* out */ System::TArray__1<System::UnicodeString> &AResult);
	System::TArray__1<void *> __fastcall GetValues();
	bool __fastcall TryGetValues(/* out */ System::TArray__1<void *> &AResult);
	TCFKeyValueEnumerator* __fastcall GetEnumerator();
	bool __fastcall ContainsKey(const System::UnicodeString Key);
	bool __fastcall ContainsValue(void * Val);
	long __fastcall Count();
	long __fastcall CountOfValue(void * Val);
	__property void * Items[const System::UnicodeString Key] = {read=GetValue, write=SetValue};
	__property System::TArray__1<System::UnicodeString> Keys = {read=GetKeys};
	__property System::TArray__1<void *> Values = {read=GetValues};
	static TCFDictionary __fastcall _op_Implicit(CFDictionaryRef AValue);
	
	TCFDictionary& operator =(CFDictionaryRef AValue) { *this = TCFDictionary::_op_Implicit(AValue); return *this; }
};


struct DECLSPEC_DRECORD TCFNumber
{
public:
	__CFNumber *Value;
	
private:
	void __fastcall DoAsType(System::Typinfo::PTypeInfo ATypeInfo, void * ABuffer, bool Release);
	
public:
	template<typename T> static TCFNumber __fastcall CreateFromType(T AValue);
	System::Typinfo::PTypeInfo __fastcall GetTypeInfo();
	template<typename T> T __fastcall AsType(bool Release = false)/* overload */;
	template<typename T> bool __fastcall TryAsType(/* out */ T &AResult, bool Release = false)/* overload */;
	System::Rtti::TValue __fastcall AsTValue(bool Release = false)/* overload */;
	bool __fastcall TryAsTValue(/* out */ System::Rtti::TValue &AResult, bool Release = false)/* overload */;
	static TCFNumber __fastcall _op_Implicit(CFNumberRef AValue);
	
	TCFNumber& operator =(CFNumberRef AValue) { *this = TCFNumber::_op_Implicit(AValue); return *this; }
};


struct DECLSPEC_DRECORD TCFString
{
public:
	__CFString *Value;
	
private:
	System::WideChar __fastcall DoAsChar(bool Release = false);
	System::UnicodeString __fastcall DoAsString(bool Release);
	
public:
	__fastcall TCFString(const System::UnicodeString AValue);
	System::WideChar __fastcall AsChar(bool Release = false);
	System::UnicodeString __fastcall AsString(bool Release = false);
	bool __fastcall TryAsChar(/* out */ System::WideChar &AResult, bool Release = false);
	bool __fastcall TryAsString(/* out */ System::UnicodeString &AResult, bool Release = false);
	static TCFString __fastcall _op_Explicit(const System::UnicodeString AValue);
	__fastcall operator System::UnicodeString();
	static TCFString __fastcall _op_Implicit(CFStringRef AValue);
	TCFString() {}
	
	TCFString& operator =(CFStringRef AValue) { *this = TCFString::_op_Implicit(AValue); return *this; }
};


enum DECLSPEC_DENUM TCFPropertyListKind : unsigned char { vkUnknown, vkArray, vkBoolean, vkData, vkDate, vkDictionary, vkNumber, vkString };

struct DECLSPEC_DRECORD TCFPropertyList
{
public:
	void *Value;
	
private:
	static System::StaticArray<unsigned long, 8> FTypeIDs;
	// __classmethod void __fastcall Create@();
	
public:
	__fastcall TCFPropertyList(const System::UnicodeString FileName, unsigned long Mutable, Macapi::Corefoundation::PCFPropertyListFormat Format);
	__fastcall TCFPropertyList(System::Classes::TStream* AStream, unsigned long Mutable, Macapi::Corefoundation::PCFPropertyListFormat Format);
	void __fastcall SaveToFile(const System::UnicodeString FileName, long Format = (long)(0x0000000000000064LL));
	void __fastcall SaveToStream(System::Classes::TStream* AStream, long Format = (long)(0x0000000000000064LL));
	unsigned long __fastcall TypeID();
	TCFPropertyListKind __fastcall PropertyListKind();
	template<typename T> static TCFPropertyList __fastcall Create(T AValue);
	System::Rtti::TValue __fastcall AsTValue();
	// explicit __fastcall operator TCFArray();
	// explicit __fastcall operator TCFBoolean();
	// explicit __fastcall operator TCFData();
	// explicit __fastcall operator TCFDate();
	// explicit __fastcall operator TCFDictionary();
	// explicit __fastcall operator TCFNumber();
	// explicit __fastcall operator TCFString();
	static TCFPropertyList __fastcall _op_Explicit(const TCFArray &PList);
	static TCFPropertyList __fastcall _op_Explicit(const TCFBoolean &PList);
	static TCFPropertyList __fastcall _op_Explicit(const TCFData &PList);
	static TCFPropertyList __fastcall _op_Explicit(const TCFDate &PList);
	static TCFPropertyList __fastcall _op_Explicit(const TCFDictionary &PList);
	static TCFPropertyList __fastcall _op_Explicit(const TCFNumber &PList);
	static TCFPropertyList __fastcall _op_Explicit(const TCFString &PList);
	static TCFPropertyList __fastcall _op_Implicit(void * AValue);
	
private:
	// __classmethod void __fastcall Destroy@();
public:
	TCFPropertyList() {}
	TCFPropertyList& operator =(void * AValue) { *this = TCFPropertyList::_op_Implicit(AValue); return *this; }
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Cfutils */
}	/* namespace Mac */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_MAC_CFUTILS)
using namespace System::Mac::Cfutils;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_MAC)
using namespace System::Mac;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Mac_CfutilsHPP
