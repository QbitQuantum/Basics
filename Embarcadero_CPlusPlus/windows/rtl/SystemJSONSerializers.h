// -----------------------------------------------------------------------------------
// SystemJSONSerializers.h C++ Declarations of types from the System.JSON.Serializers unit
//
// $Rev: 99084 $
//
// Copyright(c) 2012 Embarcadero Technologies, Inc.
// -----------------------------------------------------------------------------------
#ifndef SystemJSONSerializers_H
#define SystemJSONSerializers_H

#if !defined(System_Json_SerializersHPP)
#error Do not include this file directly.  Include 'System.Json.Serializers.hpp'.
#endif

#include <memory>
#include <System.Rtti.hpp>

namespace System
{
namespace Json
{
namespace Serializers
{

  template<typename T>
  System::UnicodeString __fastcall TJsonSerializer::Serialize(const T AValue)
  {
    std::unique_ptr<System::Sysutils::TStringBuilder> StringBuilder(new System::Sysutils::TStringBuilder(0x7FFF));
    std::unique_ptr<System::Classes::TStringWriter> StringWriter(new System::Classes::TStringWriter(StringBuilder.get()));
    Serialize<T>(StringWriter.get(), AValue);
    return StringBuilder->ToString(true);
  }

  template<typename T>
  void __fastcall TJsonSerializer::Serialize(System::Classes::TTextWriter* const AWriter, const T AValue)
  {
    std::unique_ptr<System::Json::Writers::TJsonTextWriter> JsonWriter(new System::Json::Writers::TJsonTextWriter(AWriter));
    JsonWriter->FloatFormatHandling = FloatFormatHandling;
    JsonWriter->DateFormatHandling = DateFormatHandling;
    JsonWriter->DateTimeZoneHandling = DateTimeZoneHandling;
    JsonWriter->StringEscapeHandling = StringEscapeHandling;
    JsonWriter->Formatting = Formatting;
    Serialize<T>(JsonWriter.get(), AValue);
  }

  template<typename T>
  void __fastcall TJsonSerializer::Serialize(System::Json::Writers::TJsonWriter* const AWriter, const T AValue)
  {
    this->InternalSerialize(AWriter, System::Rtti::TValue::From<T>(AValue));
  }

  template<typename T>
  T __fastcall TJsonSerializer::Deserialize(const System::UnicodeString AJson)
  {
    std::unique_ptr<System::Classes::TStringReader> LStringReader(new System::Classes::TStringReader(AJson));
    return Deserialize<T>(LStringReader.get());
  }

  template<typename T>
  T __fastcall TJsonSerializer::Deserialize(System::Classes::TTextReader* const AReader)
  {
    std::unique_ptr<System::Json::Readers::TJsonTextReader> LJsonReader(new System::Json::Readers::TJsonTextReader(AReader));
    LJsonReader->DateTimeZoneHandling = DateTimeZoneHandling;
    LJsonReader->DateParseHandling = DateParseHandling;
    LJsonReader->MaxDepth = MaxDepth;
    return Deserialize<T>(LJsonReader.get());
  }

  template<typename T>
  T __fastcall TJsonSerializer::Deserialize(System::Json::Readers::TJsonReader* const AReader)
  {
    return this->InternalDeserialize(AReader, System::Rtti::_TValueRTTIHlpr<T>::get()).template AsType<T>();
  }

  template<typename T>
  void __fastcall TJsonSerializer::Populate(const System::UnicodeString AJson, /* var */ T &AValue)
  {
    std::unique_ptr<System::Classes::TStringReader> LStringReader(new System::Classes::TStringReader(AJson));
    return Populate<T>(LStringReader.get(), AValue);
  }

  template<typename T>
  void __fastcall TJsonSerializer::Populate(System::Classes::TTextReader* const AReader, /* var */ T &AValue)
  {
    std::unique_ptr<System::Json::Readers::TJsonTextReader> LJsonReader(new System::Json::Readers::TJsonTextReader(AReader));
    LJsonReader->DateTimeZoneHandling = DateTimeZoneHandling;
    LJsonReader->DateParseHandling = DateParseHandling;
    LJsonReader->MaxDepth = MaxDepth;
    return Populate<T>(LJsonReader.get(), AValue);
  }

  template<typename T>
  void __fastcall TJsonSerializer::Populate(System::Json::Readers::TJsonReader* const AReader, /* var */ T &AValue)
  {
    System::Rtti::TValue LValue = System::Rtti::TValue::From<T>(AValue);
    InternalPopulate(AReader, LValue);
    AValue = LValue.AsType<T>();
  }

}	/* namespace Serializers */
}	/* namespace Json */
}	/* namespace System */

#endif // SystemJSONSerializers_H