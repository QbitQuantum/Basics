 static std::string::size_type find(const char* s, int s_length, const char* to_find, int to_find_length) {
   int n = s_length - to_find_length;
   std::string::size_type pos = 0;
   while(n-- >= 0) {
     if(memicmp(s, to_find, to_find_length) == 0) return pos;
     ++s; ++pos;
   }
   return std::string::npos;
 }