 size_t operator()(const std::basic_string<CharT> &key) const {
     return hash_(ToLower(key));
 }