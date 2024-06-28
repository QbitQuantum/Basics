// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'Data.DBJson.pas' rev: 34.00 (Windows)

#ifndef Data_DbjsonHPP
#define Data_DbjsonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Readers.hpp>
#include <System.JSON.Builders.hpp>
#include <System.JSON.Writers.hpp>
#include <Data.DB.hpp>
#include <System.SysUtils.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace Data
{
namespace Dbjson
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJSONToDataSetBridge;
//-- type declarations -------------------------------------------------------
enum class DECLSPEC_DENUM TJSONMetaMergeMode : unsigned char { None, Merge, Add, Update, AddOrError, Error };

enum class DECLSPEC_DENUM TJSONTypesMode : unsigned char { Rich, JSONOnly, StringOnly };

#ifndef _WIN64
#pragma pack(push,4)
#endif /* not _WIN64 */
class PASCALIMPLEMENTATION TJSONToDataSetBridge : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	__interface DELPHIINTERFACE IAdaptor;
	typedef System::DelphiInterface<IAdaptor> _di_IAdaptor;
	__interface IAdaptor  : public System::IInterface 
	{
		virtual System::UnicodeString __fastcall GetDefaultFieldName(System::Json::TJSONValue* const AJSON) = 0 ;
		virtual int __fastcall GetScanDepth() = 0 ;
	};
	
	
private:
	_di_IAdaptor FAdaptor;
	Data::Db::TDataSet* FDataSet;
	Data::Db::TFieldDefs* FFieldDefs;
	System::Generics::Collections::TDictionary__2<System::UnicodeString,System::UnicodeString>* FFieldPaths;
	int FStringFieldSize;
	TJSONMetaMergeMode FMetaMergeMode;
	bool FObjectView;
	int FSampleObjects;
	TJSONTypesMode FTypesMode;
	System::UnicodeString FPKFields;
	System::UnicodeString __fastcall GetDefaultFieldName(System::Json::TJSONValue* const AJSON);
	int __fastcall GetScanDepth();
	void __fastcall WriteFieldValues(Data::Db::TFields* AFields, System::Json::Builders::TJSONCollectionBuilder::TPairs* APairs);
	void __fastcall WriteDataSet(Data::Db::TDataSet* ADataSet, System::Json::Builders::TJSONCollectionBuilder::TElements* AElems);
	
public:
	__fastcall TJSONToDataSetBridge(const _di_IAdaptor AAdaptor);
	__fastcall virtual ~TJSONToDataSetBridge();
	void __fastcall Reset();
	void __fastcall Define(System::Json::Builders::TJSONIterator* AIter)/* overload */;
	void __fastcall Define(System::Json::Readers::TJsonReader* AReader)/* overload */;
	void __fastcall Define(System::Json::TJSONValue* AJSON)/* overload */;
	void __fastcall Append(System::Json::Builders::TJSONIterator* AIter)/* overload */;
	void __fastcall Append(System::Json::Readers::TJsonReader* AReader)/* overload */;
	void __fastcall Append(System::Json::TJSONValue* AValue)/* overload */;
	void __fastcall Produce(System::Json::Builders::TJSONArrayBuilder* ABldr)/* overload */;
	void __fastcall Produce(System::Json::Writers::TJsonWriter* AWriter)/* overload */;
	System::Json::TJSONAncestor* __fastcall Produce()/* overload */;
	__property System::UnicodeString PKFields = {read=FPKFields};
	__property Data::Db::TDataSet* Dataset = {read=FDataSet, write=FDataSet};
	__property Data::Db::TFieldDefs* FieldDefs = {read=FFieldDefs, write=FFieldDefs};
	__property bool ObjectView = {read=FObjectView, write=FObjectView, default=0};
	__property TJSONMetaMergeMode MetaMergeMode = {read=FMetaMergeMode, write=FMetaMergeMode, default=1};
	__property int SampleObjects = {read=FSampleObjects, write=FSampleObjects, default=2147483647};
	__property TJSONTypesMode TypesMode = {read=FTypesMode, write=FTypesMode, default=0};
	__property int StringFieldSize = {read=FStringFieldSize, write=FStringFieldSize, default=255};
};

#ifndef _WIN64
#pragma pack(pop)
#endif /* not _WIN64 */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Dbjson */
}	/* namespace Data */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA_DBJSON)
using namespace Data::Dbjson;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_DATA)
using namespace Data;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Data_DbjsonHPP
