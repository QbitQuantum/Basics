_TCHAR* _WINAPI_ _AvpStrlwr(_TCHAR* str_)
{
#ifdef _MBCS
        _strlwr_s(str_, strlen(str_)+1);
		return str_;
#else
        if(str_)
        {
                _TCHAR* c=str_;
                while(*c){
                        *c|=0x20;
                        c++;
                }
        }
        return str_;
#endif
}