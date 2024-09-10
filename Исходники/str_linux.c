tchar_t* TcsToUpper(tchar_t* Out,size_t OutLen,const tchar_t* In)
{
    if (OutLen)
    {
        tcscpy_s(Out,OutLen,In);
        tcsupr(Out);  //todo: doesn't support multibyte
    }
    return Out;
}