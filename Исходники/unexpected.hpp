 inline void unexpected(const std::string& what, const char* file, int line, const char* function) {
   unexpected(what.c_str(), file, line, function);
 }