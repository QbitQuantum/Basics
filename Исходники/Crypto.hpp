 void decrypt(const char* in, std::size_t len, char* out)
 {
     decrypt(in, len, reinterpret_cast<byte*>(out));
 }