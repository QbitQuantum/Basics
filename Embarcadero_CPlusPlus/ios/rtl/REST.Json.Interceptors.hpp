// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Json.Interceptors.pas' rev: 34.00 (iOS)

#ifndef Rest_Json_InterceptorsHPP
#define Rest_Json_InterceptorsHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <REST.JsonReflect.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Json
{
namespace Interceptors
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TBase64BytesInterceptor;
class DELPHICLASS TDateTimeInterceptor;
class DELPHICLASS TISODateTimeInterceptor;
class DELPHICLASS TUnixDateTimeInterceptor;
class DELPHICLASS TMongoDateTimeInterceptor;
class DELPHICLASS TParseDateTimeInterceptor;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TBase64BytesInterceptor : public Rest::Jsonreflect::TJSONInterceptor
{
	typedef Rest::Jsonreflect::TJSONInterceptor inherited;
	
public:
	__fastcall TBase64BytesInterceptor();
	virtual System::UnicodeString __fastcall StringConverter(System::TObject* Data, System::UnicodeString Field);
	virtual void __fastcall StringReverter(System::TObject* Data, System::UnicodeString Field, System::UnicodeString Arg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TBase64BytesInterceptor() { }
	
};


class PASCALIMPLEMENTATION TDateTimeInterceptor : public Rest::Jsonreflect::TJSONInterceptor
{
	typedef Rest::Jsonreflect::TJSONInterceptor inherited;
	
private:
	bool FDateTimeIsUTC;
	
public:
	__fastcall TDateTimeInterceptor(bool ADateTimeIsUTC);
	__property bool DateTimeIsUTC = {read=FDateTimeIsUTC, write=FDateTimeIsUTC, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TDateTimeInterceptor() { }
	
};


class PASCALIMPLEMENTATION TISODateTimeInterceptor : public TDateTimeInterceptor
{
	typedef TDateTimeInterceptor inherited;
	
public:
	__fastcall TISODateTimeInterceptor(bool ADateTimeIsUTC);
	virtual System::UnicodeString __fastcall StringConverter(System::TObject* Data, System::UnicodeString Field);
	virtual void __fastcall StringReverter(System::TObject* Data, System::UnicodeString Field, System::UnicodeString Arg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TISODateTimeInterceptor() { }
	
};


class PASCALIMPLEMENTATION TUnixDateTimeInterceptor : public TDateTimeInterceptor
{
	typedef TDateTimeInterceptor inherited;
	
public:
	__fastcall TUnixDateTimeInterceptor(bool ADateTimeIsUTC);
	virtual System::UnicodeString __fastcall StringConverter(System::TObject* Data, System::UnicodeString Field);
	virtual void __fastcall StringReverter(System::TObject* Data, System::UnicodeString Field, System::UnicodeString Arg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TUnixDateTimeInterceptor() { }
	
};


class PASCALIMPLEMENTATION TMongoDateTimeInterceptor : public TDateTimeInterceptor
{
	typedef TDateTimeInterceptor inherited;
	
public:
	__fastcall TMongoDateTimeInterceptor(bool ADateTimeIsUTC);
	virtual System::TObject* __fastcall ObjectConverter(System::TObject* Data, System::UnicodeString Field);
	virtual void __fastcall ObjectReverter(System::TObject* Data, System::UnicodeString Field, System::TObject* Arg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMongoDateTimeInterceptor() { }
	
};


class PASCALIMPLEMENTATION TParseDateTimeInterceptor : public TDateTimeInterceptor
{
	typedef TDateTimeInterceptor inherited;
	
public:
	__fastcall TParseDateTimeInterceptor(bool ADateTimeIsUTC);
	virtual System::TObject* __fastcall ObjectConverter(System::TObject* Data, System::UnicodeString Field);
	virtual void __fastcall ObjectReverter(System::TObject* Data, System::UnicodeString Field, System::TObject* Arg);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TParseDateTimeInterceptor() { }
	
};


//-- var, const, procedure ---------------------------------------------------
}	/* namespace Interceptors */
}	/* namespace Json */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_JSON_INTERCEPTORS)
using namespace Rest::Json::Interceptors;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_JSON)
using namespace Rest::Json;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST)
using namespace Rest;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Rest_Json_InterceptorsHPP
