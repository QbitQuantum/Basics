// CodeGear C++Builder
// Copyright (c) 1995, 2021 by Embarcadero Technologies, Inc.
// All rights reserved

// (DO NOT EDIT: machine generated header) 'FireDAC.Comp.BatchMove.JSON.pas' rev: 34.00 (MacOS)

#ifndef Firedac_Comp_Batchmove_JsonHPP
#define Firedac_Comp_Batchmove_JsonHPP

#pragma delphiheader begin
#pragma option push
#pragma option -w-      // All warnings off
#pragma option -Vx      // Zero-length empty class member 
#pragma pack(push,8)
#include <System.hpp>
#include <SysInit.hpp>
#include <System.SysUtils.hpp>
#include <System.Classes.hpp>
#include <Data.DB.hpp>
#include <System.JSON.hpp>
#include <System.JSON.Writers.hpp>
#include <System.JSON.Types.hpp>
#include <System.JSON.BSON.hpp>
#include <FireDAC.Stan.Intf.hpp>
#include <FireDAC.Stan.Util.hpp>
#include <FireDAC.Comp.DataSet.hpp>
#include <FireDAC.Comp.BatchMove.hpp>

//-- user supplied -----------------------------------------------------------

namespace Firedac
{
namespace Comp
{
namespace Batchmove
{
namespace Json
{
//-- forward type declarations -----------------------------------------------
class DELPHICLASS TFDJsonField;
class DELPHICLASS TFDJsonFields;
class DELPHICLASS TFDJsonDataDef;
class DELPHICLASS TFDBatchMoveJSONWriter;
//-- type declarations -------------------------------------------------------
enum DECLSPEC_DENUM TFDJsonDataType : unsigned int { jtOther, jtString, jtInteger, jtNumber, jtBoolean, jtDateTime, jtGUID, jtBlob };

enum DECLSPEC_DENUM TFDJsonFormat : unsigned int { jfJSON, jfJSONP, jfBSON };

class PASCALIMPLEMENTATION TFDJsonField : public System::Classes::TCollectionItem
{
	typedef System::Classes::TCollectionItem inherited;
	
private:
	TFDJsonDataType FDataType;
	System::UnicodeString FFieldName;
	int FFieldSize;
	int FPrecision;
	System::Json::Types::TJsonBinaryType FBinaryType;
	System::Variant FValue;
	void __fastcall SetFieldName(const System::UnicodeString AValue);
	
protected:
	virtual System::UnicodeString __fastcall GetDisplayName();
	virtual void __fastcall AssignTo(System::Classes::TPersistent* ADest);
	
public:
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	void __fastcall Define(const System::UnicodeString AName, Firedac::Stan::Intf::TFDDataType ADataType, int ASize, int APrecision, int AScale);
	
__published:
	__property System::UnicodeString FieldName = {read=FFieldName, write=SetFieldName};
	__property TFDJsonDataType DataType = {read=FDataType, write=FDataType, default=0};
	__property int FieldSize = {read=FFieldSize, write=FFieldSize, default=0};
	__property int Precision = {read=FPrecision, write=FPrecision, default=0};
	__property System::Json::Types::TJsonBinaryType BinaryType = {read=FBinaryType, write=FBinaryType, default=0};
public:
	/* TCollectionItem.Create */ inline __fastcall virtual TFDJsonField(System::Classes::TCollection* Collection) : System::Classes::TCollectionItem(Collection) { }
	/* TCollectionItem.Destroy */ inline __fastcall virtual ~TFDJsonField() { }
	
};


#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDJsonFields : public System::Classes::TCollection
{
	typedef System::Classes::TCollection inherited;
	
public:
	TFDJsonField* operator[](int Index) { return this->Items[Index]; }
	
private:
	TFDJsonDataDef* FDef;
	HIDESBASE TFDJsonField* __fastcall GetItem(int AIndex);
	HIDESBASE void __fastcall SetItem(int AIndex, TFDJsonField* const AValue);
	void __fastcall CheckFieldName(TFDJsonField* AField, const System::UnicodeString ANewName);
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TFDJsonFields(TFDJsonDataDef* ADef);
	HIDESBASE TFDJsonField* __fastcall Add();
	void __fastcall AddAll();
	TFDJsonField* __fastcall FindField(const System::UnicodeString AName);
	TFDJsonField* __fastcall FieldByName(const System::UnicodeString AName);
	__property TFDJsonField* Items[int Index] = {read=GetItem, write=SetItem/*, default*/};
public:
	/* TCollection.Destroy */ inline __fastcall virtual ~TFDJsonFields() { }
	
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

#ifndef __x86_64__
#pragma pack(push,4)
#endif /* not __x86_64__ */
class PASCALIMPLEMENTATION TFDJsonDataDef : public System::Classes::TPersistent
{
	typedef System::Classes::TPersistent inherited;
	
private:
	TFDBatchMoveJSONWriter* FDriver;
	TFDJsonFields* FFields;
	System::Json::Types::TJsonEmptyValueHandling FEmptyValueHandling;
	System::Json::Types::TJsonDateTimeZoneHandling FDateTimeZoneHandling;
	Firedac::Stan::Intf::TFDTextEndOfLine FEndOfLine;
	System::Json::Types::TJsonExtendedJsonMode FExtendedJsonMode;
	System::Json::Types::TJsonFormatting FFormatting;
	System::Json::Types::TJsonDateFormatHandling FDateFormatHandling;
	bool FQuoteName;
	System::WideChar FIndentChar;
	System::Json::Types::TJsonStringEscapeHandling FStringEscapeHandling;
	int FIndentation;
	System::WideChar FQuoteChar;
	System::Json::Types::TJsonFloatFormatHandling FFloatFormatHandling;
	System::UnicodeString FCallbackName;
	bool FWriteNulls;
	void __fastcall SetFields(TFDJsonFields* const AValue);
	bool __fastcall IsCNS();
	
protected:
	DYNAMIC System::Classes::TPersistent* __fastcall GetOwner();
	
public:
	__fastcall TFDJsonDataDef(TFDBatchMoveJSONWriter* ADriver);
	__fastcall virtual ~TFDJsonDataDef();
	virtual void __fastcall Assign(System::Classes::TPersistent* ASource);
	__property TFDBatchMoveJSONWriter* Driver = {read=FDriver};
	
__published:
	__property TFDJsonFields* Fields = {read=FFields, write=SetFields};
	__property System::Json::Types::TJsonEmptyValueHandling EmptyValueHandling = {read=FEmptyValueHandling, write=FEmptyValueHandling, default=0};
	__property System::Json::Types::TJsonDateTimeZoneHandling DateTimeZoneHandling = {read=FDateTimeZoneHandling, write=FDateTimeZoneHandling, default=0};
	__property bool WriteNulls = {read=FWriteNulls, write=FWriteNulls, default=0};
	__property Firedac::Stan::Intf::TFDTextEndOfLine EndOfLine = {read=FEndOfLine, write=FEndOfLine, default=0};
	__property System::Json::Types::TJsonExtendedJsonMode ExtendedJsonMode = {read=FExtendedJsonMode, write=FExtendedJsonMode, default=0};
	__property int Indentation = {read=FIndentation, write=FIndentation, default=2};
	__property System::WideChar IndentChar = {read=FIndentChar, write=FIndentChar, default=32};
	__property System::WideChar QuoteChar = {read=FQuoteChar, write=FQuoteChar, default=34};
	__property bool QuoteName = {read=FQuoteName, write=FQuoteName, default=1};
	__property System::Json::Types::TJsonFormatting Formatting = {read=FFormatting, write=FFormatting, default=0};
	__property System::Json::Types::TJsonStringEscapeHandling StringEscapeHandling = {read=FStringEscapeHandling, write=FStringEscapeHandling, default=1};
	__property System::Json::Types::TJsonDateFormatHandling DateFormatHandling = {read=FDateFormatHandling, write=FDateFormatHandling, default=0};
	__property System::Json::Types::TJsonFloatFormatHandling FloatFormatHandling = {read=FFloatFormatHandling, write=FFloatFormatHandling, default=1};
	__property System::UnicodeString CallbackName = {read=FCallbackName, write=FCallbackName, stored=IsCNS};
};

#ifndef __x86_64__
#pragma pack(pop)
#endif /* not __x86_64__ */

class PASCALIMPLEMENTATION TFDBatchMoveJSONWriter : public Firedac::Comp::Batchmove::TFDBatchMoveDriver
{
	typedef Firedac::Comp::Batchmove::TFDBatchMoveDriver inherited;
	
private:
	System::UnicodeString FFileName;
	TFDJsonDataDef* FDataDef;
	TFDJsonFormat FJsonFormat;
	Firedac::Stan::Intf::TFDEncoding FEncoding;
	System::Sysutils::TEncoding* FEncoder;
	System::Classes::TStream* FStream;
	System::Json::Writers::TJsonWriter* FJsonWriter;
	System::Json::TJSONArray* FJsonArray;
	Firedac::Stan::Util::TFDEncoder* FFDEncoder;
	Firedac::Stan::Intf::_di_IFDStanStorage FFDStorage;
	Firedac::Comp::Dataset::TFDDataSet* FFDDataSet;
	System::Classes::TBufferedFileStream* FOutput;
	System::Classes::TStreamWriter* FText;
	System::Classes::TBinaryWriter* FBin;
	System::Json::Writers::TJsonWriter* FJson;
	bool FWrapIntoArray;
	bool FGenerateExtJSModel;
	System::UnicodeString __fastcall GetActualFileName();
	void __fastcall SetDataDef(TFDJsonDataDef* const AValue);
	void __fastcall SetJsonFormat(const TFDJsonFormat AValue);
	void __fastcall ClearSources();
	void __fastcall SetFileName(const System::UnicodeString AValue);
	void __fastcall SetStream(System::Classes::TStream* const AValue);
	void __fastcall SetJsonWriter(System::Json::Writers::TJsonWriter* const aValue);
	void __fastcall SetJsonArray(System::Json::TJSONArray* const AValue);
	void __fastcall OpenStream(System::Classes::TStream* AStream);
	bool __fastcall IsASCIIOutput();
	
protected:
	System::UnicodeString __fastcall GetCatalog();
	bool __fastcall GetIsUnicode();
	bool __fastcall GetIsOpen();
	int __fastcall GetFieldCount();
	System::UnicodeString __fastcall GetFieldName(int AIndex);
	bool __fastcall CheckDefined(bool ARaise);
	void __fastcall Open(bool AStartTx);
	void __fastcall Close(bool AStopTxError);
	void __fastcall Refresh();
	void __fastcall AbortJob();
	bool __fastcall AddAutoFields();
	void __fastcall DeleteAutoFields();
	int __fastcall GetFieldIndex(const System::UnicodeString AName, bool ACheck);
#ifndef __x86_64__
	System::TObject* __fastcall GetFieldInfo(int AIndex, Firedac::Stan::Intf::TFDDataType &AType, unsigned &ASize, int &APrec, int &AScale, bool &AInKey, bool &AIsIdentity);
#else /* __x86_64__ */
	System::TObject* __fastcall GetFieldInfo(int AIndex, Firedac::Stan::Intf::TFDDataType &AType, unsigned long &ASize, int &APrec, int &AScale, bool &AInKey, bool &AIsIdentity);
#endif /* __x86_64__ */
	void __fastcall CreateTable();
	void __fastcall StartTransaction();
	void __fastcall CommitTransaction();
	void __fastcall RollbackTransaction();
	void __fastcall Erase(bool ANoUndo);
	void __fastcall WriteHeader();
	void __fastcall SetFieldValue(System::TObject* AField, const System::Variant &AValue);
	bool __fastcall FindRecord();
	int __fastcall InsertRecord();
	int __fastcall UpdateRecord();
	int __fastcall DeleteRecord();
	int __fastcall FlushRecords();
	
public:
	__fastcall virtual TFDBatchMoveJSONWriter(System::Classes::TComponent* AOwner);
	__fastcall virtual ~TFDBatchMoveJSONWriter();
	void __fastcall GenerateExtJSModel(const System::UnicodeString AModelName, bool AWithTypes, System::Classes::TStrings* AOutput);
	__property System::Classes::TStream* Stream = {read=FStream, write=SetStream};
	__property System::Json::Writers::TJsonWriter* JsonWriter = {read=FJsonWriter, write=SetJsonWriter};
	__property System::Json::TJSONArray* JsonArray = {read=FJsonArray, write=SetJsonArray};
	__property System::Sysutils::TEncoding* Encoder = {read=FEncoder, write=FEncoder};
	__property System::UnicodeString ActualFileName = {read=GetActualFileName};
	
__published:
	__property System::UnicodeString FileName = {read=FFileName, write=SetFileName};
	__property TFDJsonDataDef* DataDef = {read=FDataDef, write=SetDataDef};
	__property TFDJsonFormat JsonFormat = {read=FJsonFormat, write=SetJsonFormat, default=0};
	__property Firedac::Stan::Intf::TFDEncoding Encoding = {read=FEncoding, write=FEncoding, default=0};
private:
	void *__IFDBatchMoveWriter;	// Firedac::Comp::Batchmove::IFDBatchMoveWriter 
	
public:
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2052}
	operator Firedac::Comp::Batchmove::_di_IFDBatchMoveWriter()
	{
		Firedac::Comp::Batchmove::_di_IFDBatchMoveWriter intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Comp::Batchmove::IFDBatchMoveWriter*(void) { return (Firedac::Comp::Batchmove::IFDBatchMoveWriter*)&__IFDBatchMoveWriter; }
	#endif
	#if defined(MANAGED_INTERFACE_OPERATORS)
	// {3E9B315B-F456-4175-A864-B2573C4A2050}
	operator Firedac::Comp::Batchmove::_di_IFDBatchMoveDriver()
	{
		Firedac::Comp::Batchmove::_di_IFDBatchMoveDriver intf;
		this->GetInterface(intf);
		return intf;
	}
	#else
	operator Firedac::Comp::Batchmove::IFDBatchMoveDriver*(void) { return (Firedac::Comp::Batchmove::IFDBatchMoveDriver*)&__IFDBatchMoveWriter; }
	#endif
	
};


//-- var, const, procedure ---------------------------------------------------
#define C_FD_DefCallbackName u"fdJson"
}	/* namespace Json */
}	/* namespace Batchmove */
}	/* namespace Comp */
}	/* namespace Firedac */
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP_BATCHMOVE_JSON)
using namespace Firedac::Comp::Batchmove::Json;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP_BATCHMOVE)
using namespace Firedac::Comp::Batchmove;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC_COMP)
using namespace Firedac::Comp;
#endif
#if !defined(DELPHIHEADER_NO_IMPLICIT_NAMESPACE_USE) && !defined(NO_USING_NAMESPACE_FIREDAC)
using namespace Firedac;
#endif
#pragma pack(pop)
#pragma option pop

#pragma delphiheader end.
//-- end unit ----------------------------------------------------------------
#endif	// Firedac_Comp_Batchmove_JsonHPP
