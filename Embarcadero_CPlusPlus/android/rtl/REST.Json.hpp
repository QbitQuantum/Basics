// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'REST.Json.pas' rev: 34.00 (Android)

#ifndef Rest_JsonHPP
#define Rest_JsonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <REST.Json.Types.hpp>
#include <REST.JsonReflect.hpp>

//-- user supplied -----------------------------------------------------------

namespace Rest
{
namespace Json
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJson;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TJsonOption : unsigned char { joIgnoreEmptyStrings, joIgnoreEmptyArrays, joDateIsUTC, joDateFormatUnix, joDateFormatISO8601, joDateFormatMongo, joDateFormatParse, joBytesFormatArray, joBytesFormatBase64, joIndentCaseCamel, joIndentCaseLower, joIndentCaseUpper, joIndentCasePreserve };

typedef System::Set<TJsonOption, TJsonOption::joIgnoreEmptyStrings, TJsonOption::joIndentCasePreserve> TJsonOptions;

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJson : public System::TObject
{
	typedef System::TObject inherited;
	
private:
	static System::Json::TJSONValue* __fastcall ObjectToJsonValue(System::TObject* AObject, TJsonOptions AOptions);
	static void __fastcall ProcessOptions(System::Json::TJSONObject* AJsonObject, TJsonOptions AOptions);
	static Rest::Json::Types::TJsonDateFormat __fastcall OptionsToDateFormat(TJsonOptions AOptions);
	static Rest::Json::Types::TJsonBytesFormat __fastcall OptionsToBytesFormat(TJsonOptions AOptions);
	static Rest::Json::Types::TJsonIdentCase __fastcall OptionsToIdentCase(TJsonOptions AOptions);
	
public:
	__classmethod System::Json::TJSONObject* __fastcall ObjectToJsonObject(System::TObject* AObject, TJsonOptions AOptions = (TJsonOptions() << TJsonOption::joDateIsUTC << TJsonOption::joDateFormatISO8601 << TJsonOption::joBytesFormatArray << TJsonOption::joIndentCaseCamel ));
	__classmethod System::UnicodeString __fastcall ObjectToJsonString(System::TObject* AObject, TJsonOptions AOptions = (TJsonOptions() << TJsonOption::joDateIsUTC << TJsonOption::joDateFormatISO8601 << TJsonOption::joBytesFormatArray << TJsonOption::joIndentCaseCamel ));
	template<typename T> __classmethod T __fastcall JsonToObject(System::Json::TJSONObject* AJsonObject, TJsonOptions AOptions = (TJsonOptions() << TJsonOption::joDateIsUTC << TJsonOption::joDateFormatISO8601 << TJsonOption::joBytesFormatArray << TJsonOption::joIndentCaseCamel ))/* overload */;
	template<typename T> __classmethod T __fastcall JsonToObject(const System::UnicodeString AJson, TJsonOptions AOptions = (TJsonOptions() << TJsonOption::joDateIsUTC << TJsonOption::joDateFormatISO8601 << TJsonOption::joBytesFormatArray << TJsonOption::joIndentCaseCamel ))/* overload */;
	__classmethod void __fastcall JsonToObject(System::TObject* AObject, System::Json::TJSONObject* AJsonObject, TJsonOptions AOptions = (TJsonOptions() << TJsonOption::joDateIsUTC << TJsonOption::joDateFormatISO8601 << TJsonOption::joBytesFormatArray << TJsonOption::joIndentCaseCamel ))/* overload */;
	__classmethod System::UnicodeString __fastcall Format _DEPRECATED_ATTRIBUTE1("Use TJSONAncestor.Format instead") (System::Json::TJSONValue* AJsonValue);
	__classmethod System::UnicodeString __fastcall JsonEncode(System::Json::TJSONValue* AJsonValue)/* overload */;
	__classmethod System::UnicodeString __fastcall JsonEncode(const System::UnicodeString AJsonString)/* overload */;
public:
	/* TObject.Create */ inline __fastcall TJson() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TJson() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Json */
}	/* namespace Rest */
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
#endif	// Rest_JsonHPP
