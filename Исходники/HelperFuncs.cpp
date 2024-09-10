inline wchar_t MyCharUpper(wchar_t c)
{ return (wchar_t)(unsigned int)(UINT_PTR)CharUpperW((LPWSTR)(UINT_PTR)(unsigned int)c); }