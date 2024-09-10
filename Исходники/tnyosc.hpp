 // float32
 void append(float v) {
   is_cached_ = false;
   types_.push_back('f');
   int32_t a = htonf(v);
   ByteArray b(4);
   memcpy(&b[0], (char*)&a, 4);
   data_.insert(data_.end(), b.begin(), b.end()); }