 virtual size_t read(byte *buf, size_t max) {
   size_t n = std::min(s.available(), max);
   if (n>0) s.read_some(boost::asio::buffer(buf, n));
   return n;
 }