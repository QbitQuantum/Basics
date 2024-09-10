 es_buffer& operator=(es_buffer const& other)
 {
   es_buffer tmp(other);
   swap(tmp);
   return *this;
 }