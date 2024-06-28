// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.Net.Mime.pas' rev: 34.00 (iOS)

#ifndef System_Net_MimeHPP
#define System_Net_MimeHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Generics.Defaults.hpp>
#include <System.Types.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Net
{
namespace Mime
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TMultipartFormData;
class DELPHICLASS TMimeTypes;
class DELPHICLASS TAcceptValueItem;
template<typename T> class DELPHICLASS TAcceptValueListBase__1;
class DELPHICLASS THeaderValueList;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TMultipartFormData : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	bool FOwnsOutputStream;
	System::UnicodeString FBoundary;
	System::Classes::TMemoryStream* FStream;
	bool FLastBoundaryWrited;
	System::UnicodeString __fastcall GetMimeTypeHeader();
	System::UnicodeString __fastcall GenerateBoundary();
	void __fastcall WriteStringLn(const System::UnicodeString AString);
	System::Classes::TMemoryStream* __fastcall GetStream();
	void __fastcall AdjustLastBoundary();
	
public:
	__fastcall TMultipartFormData(bool AOwnsOutputStream);
	__fastcall virtual ~TMultipartFormData();
	void __fastcall AddField(const System::UnicodeString AField, const System::UnicodeString AValue);
	void __fastcall AddStream(const System::UnicodeString AField, System::Classes::TStream* AStream, const System::UnicodeString AFileName = System::UnicodeString(), const System::UnicodeString AContentType = System::UnicodeString());
	void __fastcall AddFile(const System::UnicodeString AField, const System::UnicodeString AFilePath, const System::UnicodeString AContentType = System::UnicodeString());
	void __fastcall AddBytes(const System::UnicodeString AField, const System::TArray__1<System::Byte> ABytes, const System::UnicodeString AFileName = System::UnicodeString(), const System::UnicodeString AContentType = System::UnicodeString());
	__property System::Classes::TMemoryStream* Stream = {read=GetStream};
	__property System::UnicodeString MimeTypeHeader = {read=GetMimeTypeHeader};
	__property System::UnicodeString Boundary = {read=FBoundary};
};


class PASCALIMPLEMENTATION TMimeTypes : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum class DECLSPEC_DENUM TKind : unsigned char { Undefined, Binary, Text };
	
	__interface DELPHIINTERFACE TIterateFunc;
	typedef System::DelphiInterface<TIterateFunc> _di_TIterateFunc;
	__interface TIterateFunc  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(const System::UnicodeString AExt, const System::UnicodeString AType, TMimeTypes::TKind AKind) = 0 ;
	};
	
	
private:
	class DELPHICLASS TInfo;
	class PASCALIMPLEMENTATION TInfo : public System::TObject
	{
		typedef System::TObject inherited;
		
	public:
		System::UnicodeString FExt;
		System::UnicodeString FType;
		TMimeTypes::TKind FKind;
	public:
		/* TObject.Create */ inline __fastcall TInfo() : System::TObject() { }
		/* TObject.Destroy */ inline __fastcall virtual ~TInfo() { }
		
	};
	
	
	
private:
	static System::TObject* FLock;
	static TMimeTypes* FDefault;
	// __classmethod void __fastcall Create@();
	// __classmethod void __fastcall Destroy@();
	static TMimeTypes* __fastcall GetDefault();
	
private:
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TInfo*>* FExtDict;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,TInfo*>* FTypeDict;
	System::Generics::Collections::TObjectDictionary__2<System::UnicodeString,TInfo*>* FInfos;
	System::UnicodeString __fastcall NormalizeExt(const System::UnicodeString AExt);
	
public:
	__fastcall TMimeTypes();
	__fastcall virtual ~TMimeTypes();
	bool __fastcall GetFileInfo(const System::UnicodeString AFileName, /* out */ System::UnicodeString &AType, /* out */ TKind &AKind);
	bool __fastcall GetExtInfo(const System::UnicodeString AExt, /* out */ System::UnicodeString &AType, /* out */ TKind &AKind);
	bool __fastcall GetTypeInfo(const System::UnicodeString AType, /* out */ System::UnicodeString &AExt, /* out */ TKind &AKind);
	void __fastcall Clear();
	void __fastcall AddDefTypes();
	void __fastcall AddOSTypes();
	void __fastcall AddType(const System::UnicodeString AExt, const System::UnicodeString AType, TKind AKind = (TKind)(0x0), bool AIgnoreDups = false);
	void __fastcall ForAll(const System::UnicodeString AExtMask, const System::UnicodeString ATypeMask, _di_TIterateFunc AFunc);
	void __fastcall ForExts(const System::UnicodeString AExtMask, _di_TIterateFunc AFunc);
	void __fastcall ForTypes(const System::UnicodeString ATypeMask, _di_TIterateFunc AFunc);
	/* static */ __property TMimeTypes* Default = {read=GetDefault};
};


class PASCALIMPLEMENTATION TAcceptValueItem : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString FName;
	double FWeight;
	int FOrder;
	System::Classes::TStrings* FParams;
	System::Classes::TStrings* __fastcall GetParams();
	
protected:
	virtual void __fastcall Parse();
	
public:
	__fastcall virtual ~TAcceptValueItem();
	__property System::UnicodeString Name = {read=FName};
	__property double Weight = {read=FWeight};
	__property int Order = {read=FOrder, nodefault};
	__property System::Classes::TStrings* Params = {read=GetParams};
public:
	/* TObject.Create */ inline __fastcall TAcceptValueItem() : System::TObject() { }
	
};


// Template declaration generated by Delphi parameterized types is
// used only for accessing Delphi variables and fields.
// Don't instantiate with new type parameters in user code.
template<typename T> class PASCALIMPLEMENTATION TAcceptValueListBase__1 : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE TAcceptFunc;
	typedef System::DelphiInterface<TAcceptFunc> _di_TAcceptFunc;
	// Template declaration generated by Delphi parameterized types is
	// used only for accessing Delphi variables and fields.
	// Don't instantiate with new type parameters in user code.
	__interface TAcceptFunc  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(const System::UnicodeString AName, double AWeight, T AItem) = 0 ;
	};
	
	
private:
	enum class DECLSPEC_DENUM TMatchMode : unsigned char { Forward, Reverse, Intersect };
	
	
public:
	System::UnicodeString operator[](int AIndex) { return this->Names[AIndex]; }
	
private:
	System::Sysutils::TFormatSettings FInvariant;
	System::Generics::Collections::TObjectList__1<T>* FItems;
	int FUpdates;
	int __fastcall GetCount();
	System::UnicodeString __fastcall GetNames(int AIndex);
	double __fastcall GetWeights(int AIndex);
	T __fastcall GetItems(int AIndex);
	System::UnicodeString __fastcall InternalNegotiate(TAcceptValueListBase__1<T>* AAcceptList, _di_TAcceptFunc AAcceptFunc, TMatchMode &AMode, /* out */ double &AWeight);
	
public:
	__fastcall TAcceptValueListBase__1()/* overload */;
	__fastcall TAcceptValueListBase__1(const System::UnicodeString AValue)/* overload */;
	__fastcall virtual ~TAcceptValueListBase__1();
	System::Generics::Collections::TEnumerator__1<T>* __fastcall GetEnumerator();
	void __fastcall BeginUpdate();
	void __fastcall EndUpdate();
	void __fastcall Clear();
	void __fastcall Delete(int AIndex);
	void __fastcall Add(const System::UnicodeString AName, double AWeight = 1.000000E+00, System::Classes::TStrings* AExtra = (System::Classes::TStrings*)(0x0));
	void __fastcall Assign(TAcceptValueListBase__1<T>* const AAcceptList);
	void __fastcall Parse(const System::UnicodeString AValue);
	virtual System::UnicodeString __fastcall ToString();
	System::UnicodeString __fastcall Negotiate(TAcceptValueListBase__1<T>* const AAcceptList, /* out */ double &AWeight, _di_TAcceptFunc AAcceptFunc)/* overload */;
	System::UnicodeString __fastcall Negotiate(const System::UnicodeString AAcceptList, /* out */ double &AWeight, _di_TAcceptFunc AAcceptFunc)/* overload */;
	void __fastcall Intersect(TAcceptValueListBase__1<T>* const AAcceptList);
	static int __fastcall CompareWeights(double AWeight1, double AWeight2);
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Names[int AIndex] = {read=GetNames/*, default*/};
	__property double Weights[int AIndex] = {read=GetWeights};
	__property T Items[int AIndex] = {read=GetItems};
};


class PASCALIMPLEMENTATION THeaderValueList : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
	enum class DECLSPEC_DENUM TFlag : unsigned char { Quoted, KeyOnly };
	
	typedef System::Set<TFlag, _DELPHI_SET_ENUMERATOR(TFlag::Quoted), _DELPHI_SET_ENUMERATOR(TFlag::KeyOnly)> TFlags;
	
	struct DECLSPEC_DRECORD TItem
	{
	public:
		System::UnicodeString FName;
		System::UnicodeString FValue;
		THeaderValueList::TFlags FFlags;
	};
	
	
	
public:
	System::UnicodeString operator[](const System::UnicodeString AName) { return this->Value[AName]; }
	
private:
	System::Generics::Collections::TList__1<TItem>* FItems;
	System::UnicodeString FSubject;
	System::UnicodeString __fastcall GetNames(int AIndex);
	System::UnicodeString __fastcall GetValue(const System::UnicodeString AName);
	System::UnicodeString __fastcall GetValues(int AIndex);
	int __fastcall IndexOfName(const System::UnicodeString AName);
	void __fastcall Add(const TItem &AItem)/* overload */;
	int __fastcall GetCount();
	
public:
	__fastcall THeaderValueList()/* overload */;
	__fastcall THeaderValueList(const System::UnicodeString AValue)/* overload */;
	__fastcall virtual ~THeaderValueList();
	void __fastcall Clear();
	void __fastcall Delete(int AIndex);
	void __fastcall Add(const System::UnicodeString AName)/* overload */;
	void __fastcall Add(const System::UnicodeString AName, const System::UnicodeString AValue, bool AQuoteVal = true)/* overload */;
	void __fastcall Assign(THeaderValueList* const AValueList);
	void __fastcall Parse(const System::UnicodeString AValue);
	virtual System::UnicodeString __fastcall ToString();
	void __fastcall Merge(THeaderValueList* const AValueList)/* overload */;
	void __fastcall Merge(const System::UnicodeString AValue)/* overload */;
	__property int Count = {read=GetCount, nodefault};
	__property System::UnicodeString Subject = {read=FSubject, write=FSubject};
	__property System::UnicodeString Names[int AIndex] = {read=GetNames};
	__property System::UnicodeString Values[int AIndex] = {read=GetValues};
	__property System::UnicodeString Value[const System::UnicodeString AName] = {read=GetValue/*, default*/};
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Mime */
}	/* namespace Net */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET_MIME)
using namespace System::Net::Mime;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_NET)
using namespace System::Net;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Net_MimeHPP
