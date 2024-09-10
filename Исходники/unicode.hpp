 inline v8::Local<v8::String> utf8_to_v8_String(const char* cstring) {
     UErrorCode error_code = U_ZERO_ERROR;
     UChar dest[characters*2];
     int32_t dest_length;
     u_strFromUTF8(dest, characters*2, &dest_length, cstring, -1, &error_code);
     if (error_code != U_ZERO_ERROR) {
         throw UTF8_to_UTF16_Conversion_Error(error_code);
     }
     return v8::String::New(dest, dest_length);
 }