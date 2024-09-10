 static const char_type* 
 find(const char_type* __s, size_t __n, const char_type& __a)
 { return (char_type*)wmemchr((wchar_t*)__s, __a, __n); }