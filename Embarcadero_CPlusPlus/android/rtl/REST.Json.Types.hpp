// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Json.Types.pas' rev: 34.00 (Android)

#ifndef Rest_Json_TypesHPP
#define Rest_Json_TypesHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.SysUtils.hpp>
#include <System.DateUtils.hpp>
#include <System.JSON.hpp>
#include <REST.Consts.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Json
{
namespace Types
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJsonDates;
class DELPHICLASS JSONBooleanAttribute;
class DELPHICLASS JSONMarshalledAttribute;
class DELPHICLASS JSONOwnedAttribute;
class DELPHICLASS JSONNameAttribute;
class DELPHICLASS TMongoDate;
class DELPHICLASS TParseDate;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJsonDates : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	enum DECLSPEC_DENUM TFormat : unsigned char { ISO8601, Unix, Mongo, Parse };
	
	
public:
	static System::TDateTime __fastcall AsDateTime(System::Json::TJSONValue* const AValue, TFormat ADateFormat, bool AReturnUTC);
public:
	/* TObject.Create */ inline __fastcall TJsonDates() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJsonDates() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION JSONBooleanAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	bool FValue;
	
public:
	__fastcall JSONBooleanAttribute(bool val);
	__property bool Value = {read=FValue, nodefault};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JSONBooleanAttribute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION JSONMarshalledAttribute : public JSONBooleanAttribute
{
	typedef JSONBooleanAttribute inherited;
	
public:
	/* JSONBooleanAttribute.Create */ inline __fastcall JSONMarshalledAttribute(bool val) : JSONBooleanAttribute(val) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JSONMarshalledAttribute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION JSONOwnedAttribute : public JSONBooleanAttribute
{
	typedef JSONBooleanAttribute inherited;
	
public:
	/* JSONBooleanAttribute.Create */ inline __fastcall JSONOwnedAttribute(bool val) : JSONBooleanAttribute(val) { }
	
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JSONOwnedAttribute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION JSONNameAttribute : public System::TCustomAttribute
{
	typedef System::TCustomAttribute inherited;
	
private:
	System::UnicodeString FName;
	
public:
	__fastcall JSONNameAttribute(System::UnicodeString AName);
	__property System::UnicodeString Name = {read=FName};
public:
	/* TObject.Destroy */ inline __fastcall virtual ~JSONNameAttribute() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

enum DECLSPEC_DENUM TJsonIdentCase : unsigned char { jicCamel, jicUpper, jicLower, jicPreserve };

enum DECLSPEC_DENUM TJsonDateFormat : unsigned char { jdfISO8601, jdfUnix, jdfMongo, jdfParse };

enum DECLSPEC_DENUM TJsonBytesFormat : unsigned char { jbfArray, jbfBase64 };

class PASCALIMPLEMENTATION TMongoDate : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	__int64 FEpochDate;
	
public:
	__fastcall TMongoDate(__int64 AUnixDate);
	System::TDateTime __fastcall GetDatetime(bool AReturnAsUTC);
	void __fastcall SetDatetime(const System::TDateTime Value, bool InputIsUTC);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TMongoDate() { }
	
};


#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TParseDate : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	System::UnicodeString Ftype;
	System::UnicodeString Fiso;
	
public:
	__fastcall TParseDate(System::TDateTime AValue, bool InputIsUTC);
	System::TDateTime __fastcall GetDateTime(bool AReturnAsUTC);
	void __fastcall SetDateTime(const System::TDateTime Value, bool InputIsUTC);
public:
	/* TObject.Destroy */ inline __fastcall virtual ~TParseDate() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Types */
}	/* namespace Json */
}	/* namespace Rest */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_REST_JSON_TYPES)
using namespace Rest::Json::Types;
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
#endif	// Rest_Json_TypesHPP
