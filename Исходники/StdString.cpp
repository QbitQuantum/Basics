std::wstring s2ws( const std::string& s )
{
#ifdef WIN_PLATFORM
	setlocale(LC_ALL, "chs"); 
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1;
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, "C");
	return result;
#endif 
//    wstring rt;
//    return rt;
    std::wstring val = L"";  

    if ( NULL == s.c_str() )
    {  
        return val;  
    }  
    //size_t size_of_ch = strlen(pc)*sizeof(char);  
    //size_t size_of_wc = get_wchar_size(pc); 

    size_t size_of_wc;  
    size_t destlen = mbstowcs(0,s.c_str(),0);  
    if (destlen ==(size_t)(-1))  
    {  
        return val;  
    }  
    size_of_wc = destlen+1;  
    wchar_t *pw  = new wchar_t[size_of_wc];  
    mbstowcs(pw,s.c_str(),size_of_wc);  
    val = pw;  
    delete pw;  
    return val;  

}