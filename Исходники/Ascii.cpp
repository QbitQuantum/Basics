Ascii
Ascii::vformat(const Chr8* sFormat, va_list args)
{
    Size iLength = _vscprintf(sFormat, args);
    Chr8* pBuf = (Chr8*) NewBytes(iLength+1);
    vsprintf_s(pBuf, iLength + 1, sFormat, args);

    Ascii s;
    s.m_blob = Blob::own(pBuf,iLength+1);
    return s;
}