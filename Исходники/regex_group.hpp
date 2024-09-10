 self_type& operator()(const char* pattern, const char* substitution, const bool insensitive=false, const bool subst_all=false)
 {
   return operator()(std::string(pattern), std::string(substitution), insensitive, subst_all);
 }