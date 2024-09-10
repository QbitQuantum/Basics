void CUIString::MakeUpper()
{
#ifdef WIN32
    wcsupr(m_pstr);
#else
    WCHAR *pstr = m_pstr;
    while(*pstr){
        *pstr = (WCHAR)toupper(*pstr);
        pstr ++;
    }
#endif // WIN32
}