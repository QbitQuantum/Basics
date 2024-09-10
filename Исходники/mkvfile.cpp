HRESULT MkvFile::Open(const wchar_t* strFileName)
{
    if (strFileName == 0)
        return E_INVALIDARG;

    if (m_hFile != INVALID_HANDLE_VALUE)
        return E_UNEXPECTED;

    m_hFile = CreateFile(
                strFileName,
                GENERIC_READ,
                FILE_SHARE_READ,
                0,  //security attributes
                OPEN_EXISTING,
                FILE_ATTRIBUTE_READONLY,
                0);

    if (m_hFile == INVALID_HANDLE_VALUE)
    {
        const DWORD e = GetLastError();
        return HRESULT_FROM_WIN32(e);
    }

    LARGE_INTEGER size;

    const BOOL b = GetFileSizeEx(m_hFile, &size);

    if (!b)
    {
        const DWORD e = GetLastError();
        Close();
        return HRESULT_FROM_WIN32(e);
    }

    m_length = size.QuadPart;
    assert(m_length >= 0);

    return S_OK;
}