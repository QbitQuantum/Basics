 void AppendFormat(const T *fmt, Args&&... args) {
   size_t l = length();
   StringFormat(data + l, MAX_SIZE - l, fmt, args...);
 }