bool CMyFile::FWriteString(TCHAR *Buffer, UINT nLength)
{
    if((nLength == 0) || (Buffer == NULL))
        return false;

    if(this->_bOpen == false)
        return false;

    if(this->_bWrite == false)
        return false;

    if(this->_nMode == -1)
        return false;

    for(unsigned int i = 0; i < nLength; i++)
    {
        if(FWrite(Buffer[i]) == false)
            return false;
    }

    return true;
}