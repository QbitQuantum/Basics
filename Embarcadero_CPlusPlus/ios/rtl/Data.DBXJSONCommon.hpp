// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBXJSONCommon.pas' rev: 34.00 (iOS)

#ifndef Data_DbxjsoncommonHPP
#define Data_DbxjsoncommonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.JSON.hpp>
#include <Data.DBXCommon.hpp>
#include <Data.DBXJSON.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbxjsoncommon
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TDBXJSONTools;
//-- type declarations -------------------------------------------------------
class PASCALIMPLEMENTATION TDBXJSONTools : public System::TObject
{
	typedef System::TObject inherited;
	
public:
	static System::Json::TJSONArray* __fastcall ValueTypeToJSON(Data::Dbxcommon::TDBXValueType* const DataType);
	static Data::Dbxcommon::TDBXValueType* __fastcall JSONToValueType(System::Json::TJSONArray* const JsonArray);
	static System::Json::TJSONObject* __fastcall TableToJSON(Data::Dbxcommon::TDBXReader* &Value, const int RowCount, const bool IsLocalConnection);
	static System::Json::TJSONValue* __fastcall DBXToJSON(Data::Dbxcommon::TDBXValue* const Value, const int DataType, const bool IsLocalConnection);
	static void __fastcall JSONToDBX(System::Json::TJSONValue* const Data, Data::Dbxcommon::TDBXWritableValue* const Value, const int DataType, const bool IsLocalConnection, const bool OwnsJSONValue = false)/* overload */;
	static void __fastcall JSONToDBX(System::Json::TJSONValue* const Data, Data::Dbxcommon::TDBXWritableValue* const Value, const int DataType, const bool IsLocalConnection, const bool OwnsJSONValue, /* out */ bool &ACanFreeJSON)/* overload */;
	static void __fastcall JSONStringToDBX(const System::UnicodeString AStringValue, Data::Dbxcommon::TDBXWritableValue* const ADBXValue, const int ADataType);
	static void __fastcall JSONNullToDBX(Data::Dbxcommon::TDBXWritableValue* const ADBXValue, const int ADataType);
	static System::Json::TJSONArray* __fastcall StreamToJSON(System::Classes::TStream* const Stream, const int Offset, const int ByteCount);
	static System::Classes::TStream* __fastcall JSONToStream(System::Json::TJSONArray* const Data);
public:
	/* TObject.Create */ inline __fastcall TDBXJSONTools() : System::TObject() { }
	/* TObject.Destroy */ inline __fastcall virtual ~TDBXJSONTools() { }
	
};


//-- var, const, procedure ---------------------------------------------------
#define TABLE_PAIR u"table"
}	/* namespace Dbxjsoncommon */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBXJSONCOMMON)
using namespace Data::Dbxjsoncommon;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbxjsoncommonHPP
