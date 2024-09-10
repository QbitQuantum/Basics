//.-.-.-.-.-.-.-.-.-.-.-.-.-.- DtOptException::DtOptException -.-.-.-.-.-.-.-.-.-.-.-.-.-.-
//
DtOptException::DtOptException(const wchar_t* pFormat, ...)
{
    va_list  ArgList;
    va_start(ArgList, pFormat);
    _vsnwprintf(m_ErrorMsg, sizeof(m_ErrorMsg)-1, pFormat, ArgList);
    va_end(ArgList);
};