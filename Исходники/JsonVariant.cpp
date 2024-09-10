void JsonVariant::writeTo(JsonWriter &writer) const {
  if (_type == JSON_ARRAY)
    _content.asArray->writeTo(writer);

  else if (_type == JSON_OBJECT)
    _content.asObject->writeTo(writer);

  else if (_type == JSON_STRING)
    writer.writeString(_content.asString);

  else if (_type == JSON_UNPARSED)
    writer.writeRaw(_content.asString);

  else if (_type == JSON_INTEGER)
    writer.writeInteger(_content.asInteger);

  else if (_type == JSON_BOOLEAN)
    writer.writeBoolean(_content.asInteger != 0);

  else if (_type >= JSON_FLOAT_0_DECIMALS) {
    uint8_t decimals = static_cast<uint8_t>(_type - JSON_FLOAT_0_DECIMALS);
    writer.writeFloat(_content.asFloat, decimals);
  }
}