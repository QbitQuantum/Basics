wstring s2ws(const string &s,const char *locale /*= ""*/)
{
	assert(locale);

    wstring result;

    _locale_t loc = _create_locale(LC_CTYPE,locale);  //使用指定的locale。
	//如果_create_locale返回空,返回空字符串。
    if(!loc)
    {
        return result;
    }

	const size_t len = s.size()+1;
	wchar_t *dest = new wchar_t[len];
	size_t numOfCharConverted = 0;
    errno_t err = _mbstowcs_s_l(&numOfCharConverted,dest,len,s.c_str(),_TRUNCATE,loc);
    _free_locale(loc);
    if(err == 0)
    {
        result = dest;
    }
    else if(err == STRUNCATE)
    {
		assert(!"dest buffer should be adequate");
        result = dest;
    }
    else
    {
		//转换失败。
    }
    delete []dest;
    return result;
}