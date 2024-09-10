 typename std::enable_if<std::is_same<CharT,char>::value,double>::type
 operator()(const CharT* s, size_t) const
 {
     CharT *end = nullptr;
     double val = _strtod_l(s, &end, locale_);
     if (s == end)
     {
         JSONCONS_THROW(json_runtime_error<std::invalid_argument>("Convert string to double failed"));
     }
     return val;
 }