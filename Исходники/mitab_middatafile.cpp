void MIDDATAFile::WriteLine(const char *pszFormat,...)
{
    va_list args;

    if (m_eAccessMode == TABWrite  && m_fp)
    {
        va_start(args, pszFormat);
        CPLString osStr;
        osStr.vPrintf( pszFormat, args );
        VSIFWriteL( osStr.c_str(), 1, osStr.size(), m_fp);
        va_end(args);
    } 
    else
    {
        CPLAssert(FALSE);
    }
}