 Local<Object> getBuffer(OutputBuffer *b) {
   return  NewBuffer(static_cast<char*>(buffer->data), buffer->length, FreeCallback, nullptr).ToLocalChecked();
 }