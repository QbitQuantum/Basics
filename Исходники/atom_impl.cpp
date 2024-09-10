double _wtof(const wchar_t* _Str)
    { return (double)wcstold(_Str, NULL);  /* radix is always 10 */ }