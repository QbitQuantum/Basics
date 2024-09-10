 // Calculate the buffer length required to compress an integer.
 static inline size_t compressed_size(uint64_t ui64) {
   //TODO: something faster than this!
   unsigned char buffer[MAX_COMPRESSED_INT_SIZE];
   return compress(buffer, ui64) - buffer;
 }