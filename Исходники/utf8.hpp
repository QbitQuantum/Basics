 utf8_t(const utf8_t & s){
   unsigned length = _mbslen((unsigned char const *)s.buffer);
   buffer = new char[length + 1]();
   memcpy(buffer, s.buffer, length + 1);
 }