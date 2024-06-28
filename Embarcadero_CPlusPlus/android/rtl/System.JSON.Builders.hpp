// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'System.JSON.Builders.pas' rev: 34.00 (Android)

#ifndef System_Json_BuildersHPP
#define System_Json_BuildersHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.JSON.hpp>
#include <System.SysUtils.hpp>
#include <System.JSON.Writers.hpp>
#include <System.Classes.hpp>
#include <System.Generics.Collections.hpp>
#include <System.Rtti.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.Readers.hpp>
#include <System.Generics.Defaults.hpp>

//-- user supplied -----------------------------------------------------------

namespace System
{
namespace Json
{
namespace Builders
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TJSONCollectionBuilder;
class DELPHICLASS TJSONArrayBuilder;
class DELPHICLASS TJSONObjectBuilder;
class DELPHICLASS TJSONIterator;
class DELPHICLASS EJSONCollectionBuilderError;
class DELPHICLASS EJSONIteratorError;
//-- type declarations -------------------------------------------------------
#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSONCollectionBuilder : public System::TObject
{
	typedef System::TObject inherited;
	
	
public:
	class DELPHICLASS TElements;
	class DELPHICLASS TBaseCollection;
	class DELPHICLASS TPairs;
	class DELPHICLASS TParentCollection;
	class PASCALIMPLEMENTATION TBaseCollection : public System::TObject
	{
		typedef System::TObject inherited;
		
	private:
		int FRootDepth;
		TJSONCollectionBuilder* FOwner;
		System::Json::Writers::TJsonWriter* FWriter;
		
	private:
		void __fastcall AddingElement();
		void __fastcall AddingPair();
		void __fastcall ErrorInvalidSetOfItems();
		void __fastcall WriteVarRec(const System::TVarRec &AValue);
		void __fastcall WriteVariant(const System::Variant &AValue);
		void __fastcall WriteOpenArray(const System::TVarRec *AItems, const int AItems_High);
		bool __fastcall WriteReader(System::Json::Readers::TJsonReader* const AReader, bool AOnlyEnclosed);
		void __fastcall WriteBuilder(TJSONCollectionBuilder* const ABuilder);
		void __fastcall WriteJSON(const System::UnicodeString AJSON);
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::UnicodeString AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const int AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const unsigned AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const __int64 AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const unsigned __int64 AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const float AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const double AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Extended AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const bool AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::WideChar AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Byte AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::TDateTime AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const GUID &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonOid &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonRegEx &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonDBRef &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Rtti::TValue &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::TVarRec &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall Add(const System::Variant &AValue)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddElements(const System::TVarRec *AElements, const int AElements_High)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddElements(TJSONCollectionBuilder* const ABuilder)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddElements(const System::UnicodeString AJSON)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddNull()/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddUndefined()/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddMinKey()/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall AddMaxKey()/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::UnicodeString AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const int AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const unsigned AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const __int64 AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const unsigned __int64 AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const float AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const double AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Extended AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const bool AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::WideChar AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Byte AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TDateTime AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const GUID &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonOid &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonRegEx &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonDBRef &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Rtti::TValue &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Variant &AValue)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddPairs(const System::TVarRec *APairs, const int APairs_High)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddPairs(TJSONCollectionBuilder* const ABuilder)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddPairs(const System::UnicodeString AJSON)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddNull(const System::UnicodeString AKey)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddUndefined(const System::UnicodeString AKey)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddMinKey(const System::UnicodeString AKey)/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall AddMaxKey(const System::UnicodeString AKey)/* overload */;
		TJSONCollectionBuilder::TParentCollection* __fastcall EndArray();
		TJSONCollectionBuilder::TParentCollection* __fastcall EndObject();
		TJSONCollectionBuilder::TPairs* __fastcall BeginObject()/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall BeginArray()/* overload */;
		TJSONCollectionBuilder::TPairs* __fastcall BeginObject(const System::UnicodeString AKey)/* overload */;
		TJSONCollectionBuilder::TElements* __fastcall BeginArray(const System::UnicodeString AKey)/* overload */;
		__property TJSONCollectionBuilder* Owner = {read=FOwner};
		__property System::Json::Writers::TJsonWriter* Writer = {read=FWriter};
		__property int RootDepth = {read=FRootDepth, nodefault};
		
	public:
		__fastcall TBaseCollection(TJSONCollectionBuilder* const AOwner, const int ARootDepth);
		void __fastcall EndAll();
		bool __fastcall Ended();
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TBaseCollection() { }
		
	};
	
	
	class PASCALIMPLEMENTATION TElements : public TJSONCollectionBuilder::TBaseCollection
	{
		typedef TJSONCollectionBuilder::TBaseCollection inherited;
		
	public:
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::UnicodeString AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const int AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const unsigned AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const unsigned __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const float AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const double AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Extended AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const bool AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::WideChar AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Byte AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::TDateTime AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const GUID &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonOid &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonRegEx &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonDBRef &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Rtti::TValue &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::TVarRec &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Variant &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddNull();
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddUndefined();
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddMinKey();
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddMaxKey();
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddElements(const System::TVarRec *AElements, const int AElements_High)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddElements(TJSONCollectionBuilder* const ABuilder)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddElements(const System::UnicodeString AJSON)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall BeginObject()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall BeginArray()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TParentCollection* __fastcall EndArray();
		TJSONCollectionBuilder::TElements* __fastcall AsRoot();
	public:
		/* TBaseCollection.Create */ inline __fastcall TElements(TJSONCollectionBuilder* const AOwner, const int ARootDepth) : TJSONCollectionBuilder::TBaseCollection(AOwner, ARootDepth) { }
		
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TElements() { }
		
	/* Hoisted overloads: */
		
	};
	
	
	class PASCALIMPLEMENTATION TPairs : public TJSONCollectionBuilder::TBaseCollection
	{
		typedef TJSONCollectionBuilder::TBaseCollection inherited;
		
	public:
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::UnicodeString AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const int AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const unsigned AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const unsigned __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const float AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const double AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Extended AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const bool AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::WideChar AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Byte AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TDateTime AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const GUID &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonOid &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonRegEx &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonDBRef &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Rtti::TValue &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Variant &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddNull(const System::UnicodeString AKey);
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddUndefined(const System::UnicodeString AKey);
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddMinKey(const System::UnicodeString AKey);
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddMaxKey(const System::UnicodeString AKey);
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddPairs(const System::TVarRec *APairs, const int APairs_High)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddPairs(TJSONCollectionBuilder* const ABuilder)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddPairs(const System::UnicodeString AJSON)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall BeginObject(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall BeginArray(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TParentCollection* __fastcall EndObject();
		TJSONCollectionBuilder::TPairs* __fastcall AsRoot();
	public:
		/* TBaseCollection.Create */ inline __fastcall TPairs(TJSONCollectionBuilder* const AOwner, const int ARootDepth) : TJSONCollectionBuilder::TBaseCollection(AOwner, ARootDepth) { }
		
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TPairs() { }
		
	/* Hoisted overloads: */
		
	};
	
	
	class PASCALIMPLEMENTATION TParentCollection : public TJSONCollectionBuilder::TBaseCollection
	{
		typedef TJSONCollectionBuilder::TBaseCollection inherited;
		
	public:
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::UnicodeString AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const int AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const unsigned AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const unsigned __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const float AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const double AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Extended AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const bool AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::WideChar AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Byte AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::TDateTime AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const GUID &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonOid &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonRegEx &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonDBRef &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Rtti::TValue &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::TVarRec &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall Add(const System::Variant &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddNull()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddUndefined()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddMinKey()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddMaxKey()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddElements(const System::TVarRec *AElements, const int AElements_High)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddElements(TJSONCollectionBuilder* const ABuilder)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall AddElements(const System::UnicodeString AJSON)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::UnicodeString AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const int AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const unsigned AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const unsigned __int64 AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const float AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const double AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, System::Extended AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, bool AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, System::WideChar AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, System::Byte AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, System::TDateTime AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const GUID &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TArray__1<System::Byte> AValue, System::Json::Types::TJsonBinaryType ABinaryType = (System::Json::Types::TJsonBinaryType)(0x0))/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonOid &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonRegEx &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonDBRef &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Json::Types::TJsonCodeWScope &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Rtti::TValue &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::TVarRec &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall Add(const System::UnicodeString AKey, const System::Variant &AValue)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddNull(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddUndefined(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddMinKey(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddMaxKey(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddPairs(const System::TVarRec *APairs, const int APairs_High)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddPairs(TJSONCollectionBuilder* const ABuilder)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall AddPairs(const System::UnicodeString AJSON)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall BeginObject()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall BeginArray()/* overload */;
		HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall BeginObject(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TElements* __fastcall BeginArray(const System::UnicodeString AKey)/* overload */;
		HIDESBASE TJSONCollectionBuilder::TParentCollection* __fastcall EndArray();
		HIDESBASE TJSONCollectionBuilder::TParentCollection* __fastcall EndObject();
		TJSONCollectionBuilder::TElements* __fastcall AsArray();
		TJSONCollectionBuilder::TPairs* __fastcall AsObject();
	public:
		/* TBaseCollection.Create */ inline __fastcall TParentCollection(TJSONCollectionBuilder* const AOwner, const int ARootDepth) : TJSONCollectionBuilder::TBaseCollection(AOwner, ARootDepth) { }
		
	public:
		/* TObject.Destroy */ inline __fastcall virtual ~TParentCollection() { }
		
	};
	
	
	enum class DECLSPEC_DENUM TParentType : unsigned char { None, Elements, Pairs };
	
	__interface DELPHIINTERFACE TGetReaderProc;
	typedef System::DelphiInterface<TGetReaderProc> _di_TGetReaderProc;
	__interface TGetReaderProc  : public System::IInterface 
	{
		virtual System::Json::Readers::TJsonReader* __fastcall Invoke(System::Json::Writers::TJsonWriter* AWriter) = 0 ;
	};
	
	__interface DELPHIINTERFACE TReleaseReaderProc;
	typedef System::DelphiInterface<TReleaseReaderProc> _di_TReleaseReaderProc;
	__interface TReleaseReaderProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::Json::Writers::TJsonWriter* AWriter, System::Json::Readers::TJsonReader* AReader) = 0 ;
	};
	
	__interface DELPHIINTERFACE TResetWriterProc;
	typedef System::DelphiInterface<TResetWriterProc> _di_TResetWriterProc;
	__interface TResetWriterProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::Json::Writers::TJsonWriter* AWriter) = 0 ;
	};
	
	
private:
	bool FEmpty;
	System::Generics::Collections::TDictionary__2<int,TPairs*>* FPairs;
	System::Generics::Collections::TDictionary__2<int,TElements*>* FElements;
	System::Generics::Collections::TDictionary__2<int,TParentCollection*>* FParentCollections;
	System::Generics::Collections::TStack__1<TParentType>* FParentTypes;
	System::Json::Writers::TJsonWriter* FJSONWriter;
	_di_TGetReaderProc FGetReader;
	_di_TReleaseReaderProc FReleaseReader;
	_di_TResetWriterProc FResetWriter;
	System::Json::Types::TJsonDateTimeZoneHandling FDateTimeZoneHandling;
	System::Json::Types::TJsonExtendedJsonMode FExtendedJsonMode;
	
private:
	void __fastcall CheckParentType(int ARootDepth, TParentType AParentType);
	void __fastcall CheckEmpty();
	TParentCollection* __fastcall EndArray(int ARootDepth);
	TParentCollection* __fastcall EndObject(int ARootDepth);
	void __fastcall Complete(const int ARootDepth);
	TPairs* __fastcall GetPairs(int ARootDepth);
	TElements* __fastcall GetElements(int ARootDepth);
	TParentCollection* __fastcall GetParentCollection(int ARootDepth);
	TPairs* __fastcall BeginObject(int ARootDepth)/* overload */;
	TElements* __fastcall BeginArray(int ARootDepth)/* overload */;
	TPairs* __fastcall PairsAsRoot();
	TElements* __fastcall ElementsAsRoot();
	TElements* __fastcall AsArray(int ARootDepth);
	TPairs* __fastcall AsObject(int ARootDepth);
	bool __fastcall Ended(int ARootDepth);
	System::UnicodeString __fastcall GetAsJSON();
	void __fastcall ClearContent();
	TParentType __fastcall GetParentType();
	TElements* __fastcall GetParentArray();
	TPairs* __fastcall GetParentObject();
	
protected:
	virtual void __fastcall DoResetWriter(System::Json::Writers::TJsonWriter* AWriter);
	virtual System::Json::Readers::TJsonReader* __fastcall DoGetReader(System::Json::Writers::TJsonWriter* AWriter);
	virtual void __fastcall DoReleaseReader(System::Json::Writers::TJsonWriter* AWriter, System::Json::Readers::TJsonReader* AReader);
	virtual void __fastcall DoWriteCustomVariant(System::Json::Writers::TJsonWriter* AWriter, const System::Variant &AValue);
	TElements* __fastcall DoBeginArray();
	TPairs* __fastcall DoBeginObject();
	
public:
	__fastcall TJSONCollectionBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter)/* overload */;
	__fastcall TJSONCollectionBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter, _di_TGetReaderProc AGetReader, _di_TReleaseReaderProc AReleaseReader, _di_TResetWriterProc AResetWriter)/* overload */;
	__fastcall virtual ~TJSONCollectionBuilder();
	__property System::UnicodeString AsJSON = {read=GetAsJSON};
	__property TParentType ParentType = {read=GetParentType, nodefault};
	__property TElements* ParentArray = {read=GetParentArray};
	__property TPairs* ParentObject = {read=GetParentObject};
	__property System::Json::Types::TJsonExtendedJsonMode ExtendedJsonMode = {read=FExtendedJsonMode, write=FExtendedJsonMode, default=0};
	__property System::Json::Types::TJsonDateTimeZoneHandling DateTimeZoneHandling = {read=FDateTimeZoneHandling, write=FDateTimeZoneHandling, default=0};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSONArrayBuilder : public TJSONCollectionBuilder
{
	typedef TJSONCollectionBuilder inherited;
	
public:
	HIDESBASE TJSONCollectionBuilder::TElements* __fastcall BeginArray();
	TJSONArrayBuilder* __fastcall Clear();
public:
	/* TJSONCollectionBuilder.Create */ inline __fastcall TJSONArrayBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter)/* overload */ : TJSONCollectionBuilder(AJSONWriter) { }
	/* TJSONCollectionBuilder.Create */ inline __fastcall TJSONArrayBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter, TJSONCollectionBuilder::_di_TGetReaderProc AGetReader, TJSONCollectionBuilder::_di_TReleaseReaderProc AReleaseReader, TJSONCollectionBuilder::_di_TResetWriterProc AResetWriter)/* overload */ : TJSONCollectionBuilder(AJSONWriter, AGetReader, AReleaseReader, AResetWriter) { }
	/* TJSONCollectionBuilder.Destroy */ inline __fastcall virtual ~TJSONArrayBuilder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSONObjectBuilder : public TJSONCollectionBuilder
{
	typedef TJSONCollectionBuilder inherited;
	
public:
	HIDESBASE TJSONCollectionBuilder::TPairs* __fastcall BeginObject();
	TJSONObjectBuilder* __fastcall Clear();
public:
	/* TJSONCollectionBuilder.Create */ inline __fastcall TJSONObjectBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter)/* overload */ : TJSONCollectionBuilder(AJSONWriter) { }
	/* TJSONCollectionBuilder.Create */ inline __fastcall TJSONObjectBuilder(System::Json::Writers::TJsonWriter* const AJSONWriter, TJSONCollectionBuilder::_di_TGetReaderProc AGetReader, TJSONCollectionBuilder::_di_TReleaseReaderProc AReleaseReader, TJSONCollectionBuilder::_di_TResetWriterProc AResetWriter)/* overload */ : TJSONCollectionBuilder(AJSONWriter, AGetReader, AReleaseReader, AResetWriter) { }
	/* TJSONCollectionBuilder.Destroy */ inline __fastcall virtual ~TJSONObjectBuilder() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION TJSONIterator : public System::TObject
{
	typedef System::TObject inherited;
	
	
private:
#ifndef __aarch64__
	#pragma pack(push,8)
#endif /* not __aarch64__ */
	struct DECLSPEC_DRECORD TContext
	{
	public:
		System::Json::Types::TJsonToken FToken;
		int FIndex;
		__fastcall TContext(System::Json::Types::TJsonToken AToken);
		TContext() {}
	};
#ifndef __aarch64__
	#pragma pack(pop)
#endif /* not __aarch64__ */
	
	
	
public:
	__interface DELPHIINTERFACE TRewindReaderProc;
	typedef System::DelphiInterface<TRewindReaderProc> _di_TRewindReaderProc;
	__interface TRewindReaderProc  : public System::IInterface 
	{
		virtual void __fastcall Invoke(System::Json::Readers::TJsonReader* AReader) = 0 ;
	};
	
	__interface DELPHIINTERFACE TIterateFunc;
	typedef System::DelphiInterface<TIterateFunc> _di_TIterateFunc;
	__interface TIterateFunc  : public System::IInterface 
	{
		virtual bool __fastcall Invoke(TJSONIterator* AIter) = 0 ;
	};
	
	
private:
	System::Json::Readers::TJsonReader* FReader;
	System::Generics::Collections::TStack__1<TContext>* FStack;
	System::UnicodeString FKey;
	System::UnicodeString FPath;
	System::Json::Types::TJsonToken FType;
	bool FStarting;
	bool FFinished;
	bool FRecursion;
	_di_TRewindReaderProc FRewindReader;
	bool __fastcall GetAsBoolean();
	System::TArray__1<System::Byte> __fastcall GetAsBytes();
	System::TDateTime __fastcall GetAsDateTime();
	System::Json::Types::TJsonDBRef __fastcall GetAsDBRef();
	System::Extended __fastcall GetAsExtended();
	double __fastcall GetAsDouble();
	GUID __fastcall GetAsGUID();
	int __fastcall GetAsInteger();
	__int64 __fastcall GetAsInt64();
	System::Json::Types::TJsonOid __fastcall GetAsOid();
	System::Json::Types::TJsonRegEx __fastcall GetAsRegEx();
	System::UnicodeString __fastcall GetAsString();
	System::Rtti::TValue __fastcall GetAsValue();
	System::Variant __fastcall GetAsVariant();
	int __fastcall GetDepth();
	bool __fastcall GetInRecurse();
	bool __fastcall GetIsMaxKey();
	bool __fastcall GetIsMinKey();
	bool __fastcall GetIsNull();
	bool __fastcall GetIsUndefined();
	System::Json::Types::TJsonCodeWScope __fastcall GetAsCodeWScope();
	int __fastcall GetIndex();
	System::Json::Types::TJsonToken __fastcall GetParentType();
	System::UnicodeString __fastcall GetPath()/* overload */;
	
protected:
	virtual void __fastcall DoRewindReader(System::Json::Readers::TJsonReader* AReader);
	
public:
	__fastcall TJSONIterator(System::Json::Readers::TJsonReader* AReader)/* overload */;
	__fastcall TJSONIterator(System::Json::Readers::TJsonReader* AReader, _di_TRewindReaderProc ARewindReader)/* overload */;
	__fastcall virtual ~TJSONIterator();
	void __fastcall Rewind();
	bool __fastcall Next(const System::UnicodeString AKey = System::UnicodeString());
	bool __fastcall Recurse();
	void __fastcall Return();
	bool __fastcall Find(const System::UnicodeString APath);
	void __fastcall Iterate(_di_TIterateFunc AFunc);
	System::UnicodeString __fastcall GetPath(int AFromDepth)/* overload */;
	__property System::Json::Readers::TJsonReader* Reader = {read=FReader};
	__property System::UnicodeString Key = {read=FKey};
	__property System::UnicodeString Path = {read=GetPath};
	__property System::Json::Types::TJsonToken Type = {read=FType, nodefault};
	__property System::Json::Types::TJsonToken ParentType = {read=GetParentType, nodefault};
	__property int Index = {read=GetIndex, nodefault};
	__property bool InRecurse = {read=GetInRecurse, nodefault};
	__property int Depth = {read=GetDepth, nodefault};
	__property System::UnicodeString AsString = {read=GetAsString};
	__property int AsInteger = {read=GetAsInteger, nodefault};
	__property __int64 AsInt64 = {read=GetAsInt64};
	__property double AsDouble = {read=GetAsDouble};
	__property System::Extended AsExtended = {read=GetAsExtended};
	__property bool AsBoolean = {read=GetAsBoolean, nodefault};
	__property System::TDateTime AsDateTime = {read=GetAsDateTime};
	__property GUID AsGUID = {read=GetAsGUID};
	__property System::TArray__1<System::Byte> AsBytes = {read=GetAsBytes};
	__property System::Json::Types::TJsonOid AsOid = {read=GetAsOid};
	__property System::Json::Types::TJsonRegEx AsRegEx = {read=GetAsRegEx};
	__property System::Json::Types::TJsonDBRef AsDBRef = {read=GetAsDBRef};
	__property System::Json::Types::TJsonCodeWScope AsCodeWScope = {read=GetAsCodeWScope};
	__property System::Variant AsVariant = {read=GetAsVariant};
	__property System::Rtti::TValue AsValue = {read=GetAsValue};
	__property bool IsNull = {read=GetIsNull, nodefault};
	__property bool IsUndefined = {read=GetIsUndefined, nodefault};
	__property bool IsMinKey = {read=GetIsMinKey, nodefault};
	__property bool IsMaxKey = {read=GetIsMaxKey, nodefault};
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EJSONCollectionBuilderError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJSONCollectionBuilderError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJSONCollectionBuilderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJSONCollectionBuilderError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJSONCollectionBuilderError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONCollectionBuilderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONCollectionBuilderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJSONCollectionBuilderError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJSONCollectionBuilderError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONCollectionBuilderError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONCollectionBuilderError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONCollectionBuilderError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONCollectionBuilderError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJSONCollectionBuilderError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

#ifndef __aarch64__
#pragma pack(push,4)
#endif /* not __aarch64__ */
class PASCALIMPLEMENTATION EJSONIteratorError : public System::Sysutils::Exception
{
	typedef System::Sysutils::Exception inherited;
	
public:
	/* Exception.Create */ inline __fastcall EJSONIteratorError(const System::UnicodeString Msg) : System::Sysutils::Exception(Msg) { }
	/* Exception.CreateFmt */ inline __fastcall EJSONIteratorError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High) : System::Sysutils::Exception(Msg, Args, Args_High) { }
	/* Exception.CreateRes */ inline __fastcall EJSONIteratorError(NativeUInt Ident)/* overload */ : System::Sysutils::Exception(Ident) { }
	/* Exception.CreateRes */ inline __fastcall EJSONIteratorError(System::PResStringRec ResStringRec)/* overload */ : System::Sysutils::Exception(ResStringRec) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONIteratorError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High) { }
	/* Exception.CreateResFmt */ inline __fastcall EJSONIteratorError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High) { }
	/* Exception.CreateHelp */ inline __fastcall EJSONIteratorError(const System::UnicodeString Msg, int AHelpContext) : System::Sysutils::Exception(Msg, AHelpContext) { }
	/* Exception.CreateFmtHelp */ inline __fastcall EJSONIteratorError(const System::UnicodeString Msg, const System::TVarRec *Args, const int Args_High, int AHelpContext) : System::Sysutils::Exception(Msg, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONIteratorError(NativeUInt Ident, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, AHelpContext) { }
	/* Exception.CreateResHelp */ inline __fastcall EJSONIteratorError(System::PResStringRec ResStringRec, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONIteratorError(System::PResStringRec ResStringRec, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(ResStringRec, Args, Args_High, AHelpContext) { }
	/* Exception.CreateResFmtHelp */ inline __fastcall EJSONIteratorError(NativeUInt Ident, const System::TVarRec *Args, const int Args_High, int AHelpContext)/* overload */ : System::Sysutils::Exception(Ident, Args, Args_High, AHelpContext) { }
	/* Exception.Destroy */ inline __fastcall virtual ~EJSONIteratorError() { }
	
};

#ifndef __aarch64__
#pragma pack(pop)
#endif /* not __aarch64__ */

//-- var, const, procedure ---------------------------------------------------
}	/* namespace Builders */
}	/* namespace Json */
}	/* namespace System */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON_BUILDERS)
using namespace System::Json::Builders;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM_JSON)
using namespace System::Json;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_SYSTEM)
using namespace System;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// System_Json_BuildersHPP
