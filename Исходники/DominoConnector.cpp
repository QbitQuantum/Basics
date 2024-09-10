LPLOCKBYTES ReadFileIntoMemory(const std::wstring& fileName)
{
    HRESULT hr = S_OK;
    HANDLE file = INVALID_HANDLE_VALUE;

    file = ::CreateFileW(fileName.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
    if(INVALID_HANDLE_VALUE == file)
    {
        DWORD lastError = GetLastError();
        std::tostringstream msg;
        msg << _T("Failed to open [") << fileName << _T("] for reading its contents into memory, so we may read its custom properties") << std::ends;
        throw Workshare::System::SystemException(msg.str().c_str(), lastError);
    }

    try
    {
        unsigned long size = ::GetFileSize(file, NULL);
        HGLOBAL memory = GlobalAlloc(GPTR, size);
        if(NULL == memory)
        {
            DWORD lastError = GetLastError();
            std::tostringstream msg;
            msg << _T("Failed to allocate ") << size << _T(" bytes of memory for reading [") << fileName << _T("] into memory, so we may read its custom properties") << std::ends;
            throw Workshare::System::SystemException(msg.str().c_str(), lastError);
        }

        try
        {
            DWORD numberOfBytesRead = 0;
            BOOL ok = ::ReadFile(file, memory, size, &numberOfBytesRead, NULL);
            if(!ok)
            {
                DWORD lastError = GetLastError();
                std::tostringstream msg;
                msg << _T("Failed to read ") << size << _T(" bytes from [") << fileName << _T("] into a buffer that is ") << size << _T(" big, so we may read its custom properties") << std::ends;
                throw Workshare::System::SystemException(msg.str().c_str(), lastError);
            }

            if(size != numberOfBytesRead)
            {
                std::tostringstream msg;
                msg << _T("Failed to read all the ") << size << _T(" bytes from [") << fileName << _T("] into a buffer that is ") << size << _T(" big, so we may read its custom properties. Only ") << numberOfBytesRead << _T(" was read") << std::ends;
                throw Workshare::System::IO::IOException(msg.str().c_str());
            }

            LPLOCKBYTES lpBytes = NULL;
            hr = CreateILockBytesOnHGlobal(memory, TRUE, &lpBytes);
            if(FAILED(hr))
            {
                std::tostringstream msg;
                msg << _T("Failed to create an instance of ILockBytes from memory ") << size << _T(" bytes from [") << fileName << _T("] into a buffer that is ") << size << _T(" big, so we may read its custom properties. Only ") << numberOfBytesRead << _T(" was read") << std::ends;
                throw Workshare::System::IO::IOException(msg.str().c_str());
            }

            CloseHandle(file);
            return lpBytes;
        }
        catch(...)
        {
            GlobalFree(memory);
            throw;
        }
    }
    catch(...)
    {
        CloseHandle(file);
        throw;
    }
}