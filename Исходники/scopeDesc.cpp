GrowableArray<ScopeValue*>* ScopeDesc::decode_object_values(int decode_offset) {
  if (decode_offset == DebugInformationRecorder::serialized_null) return NULL;
  GrowableArray<ScopeValue*>* result = new GrowableArray<ScopeValue*>();
  DebugInfoReadStream* stream = new DebugInfoReadStream(_code, decode_offset, result);
  int length = stream->read_int();
  for (int index = 0; index < length; index++) {
    // Objects values are pushed to 'result' array during read so that
    // object's fields could reference it (OBJECT_ID_CODE).
    (void)ScopeValue::read_from(stream);
  }
  assert(result->length() == length, "inconsistent debug information");
  return result;
}