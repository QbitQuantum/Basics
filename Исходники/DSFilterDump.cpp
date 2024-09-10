//
// SetFileName
//
// Implemented for IFileSinkFilter support
//
STDMETHODIMP CDump::SetFileName(LPCOLESTR pszFileName,const AM_MEDIA_TYPE *pmt)
{
    // Is this a valid filename supplied

    CheckPointer(pszFileName,E_POINTER);
    if(wcslen(pszFileName) > MAX_PATH)
        return ERROR_FILENAME_EXCED_RANGE;

    // Take a copy of the filename

    size_t len = 1+lstrlenW(pszFileName);
    m_pFileName = new WCHAR[len];
    if (m_pFileName == 0)
        return E_OUTOFMEMORY;

    HRESULT hr = StringCchCopyW(m_pFileName, len, pszFileName);

    // Clear the global 'write error' flag that would be set
    // if we had encountered a problem writing the previous dump file.
    // (eg. running out of disk space).
    m_fWriteError = FALSE;

    // Create the file then close it

    hr = OpenFile();
    CloseFile();

    return hr;

} // SetFileName