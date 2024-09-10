 inline Unicode
 decode(const Bytes& object) const
 {
   int state;
   size_t offset = 0;
   size_t declen = 0;
   unicode* decptr = NULL;
   size_t enclen = object.length();
   const bytechar* encptr = static_cast<const bytechar*>(object);
   state = u8_decode(encptr, enclen, decptr, declen, offset);
   if (state != UNICODE_STATE_SUCCESS)
     throw DecodeError(state, offset, "UTF-8");
   return Unicode(decptr, declen);
 }