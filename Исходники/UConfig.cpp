std::wstring UIniConfig::formatKey( std::wstring &key, va_list ap )
{
    //该函数返回格式化后的字符串长度，不包括0结束符。
    _locale_t loc = _create_locale(LC_ALL,"");
    const int len = _vscwprintf_p_l(key.c_str(),loc,ap)+1;
    wchar_t *buffer = new wchar_t[len];

    _vswprintf_p_l(buffer,len,key.c_str(),loc,ap);
    _free_locale(loc);

    wstring result = buffer;

    delete[] buffer;
    return result;
}