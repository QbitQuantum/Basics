CString CCrypt::decrypt(CString str)
{
    USES_CONVERSION;

    LPCSTR lpszAscii=T2CA(str);
    int pos=(strlen(lpszAscii)/3)%strlen(m_key);
    CString ret;
    TCHAR tmp[2];
    tmp[1] = 0;
    for (unsigned int i=0; i<strlen(lpszAscii)/3; i++)
    {
        int digit;
        int number = 0;
        digit = lpszAscii[i * 3];
        if (digit < '0' || digit > '9')
            return _T("");
        number += (digit - '0') * 100;
        digit = lpszAscii[i * 3 + 1];
        if (digit < '0' || digit > '9')
            return _T("");
        number += (digit - '0') * 10;
        digit = lpszAscii[i * 3 + 2];
        if (digit < '0' || digit > '9')
            return _T("");
        number += digit - '0';
        tmp[0] = number^m_key[(i+pos)%strlen(m_key)];
        ret += tmp;
    }
    return ret;
}