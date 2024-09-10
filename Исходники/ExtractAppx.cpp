//
// Function to create a writable IStream over a file with the specified name
// under the specified path.  This function will also create intermediate
// subdirectories if necessary.  For simplicity, file names including path are
// assumed to be 200 characters or less.  A real application should be able to
// handle longer names and allocate the necessary buffer dynamically.
//
// Parameters:
// path - Path of the folder containing the file to be opened.  This should NOT
//        end with a slash ('\') character.
// fileName - Name, not including path, of the file to be opened
// stream - Output parameter pointing to the created instance of IStream over
//          the specified file when this function succeeds.
//
HRESULT GetOutputStream(
    _In_ LPCWSTR path,
    _In_ LPCWSTR fileName,
    _Outptr_ IStream** stream)
{
    HRESULT hr = S_OK;
    const int MaxFileNameLength = 200;
    WCHAR fullFileName[MaxFileNameLength + 1];

    // Create full file name by concatenating path and fileName
    hr = StringCchCopyW(fullFileName, MaxFileNameLength, path);

    if (SUCCEEDED(hr))
    {
        hr = StringCchCat(fullFileName, MaxFileNameLength, L"\\");
    }
    if (SUCCEEDED(hr))
    {
        hr = StringCchCat(fullFileName, MaxFileNameLength, fileName);
    }

    // Search through fullFileName for the '\' character which denotes
    // subdirectory and create each subdirectory in order of depth.
    for (int i = 0; SUCCEEDED(hr) && (i < MaxFileNameLength); i++)
    {
        if (fullFileName[i] == L'\0')
        {
            break;
        }
        else if (fullFileName[i] == L'\\')
        {
            // Temporarily set string to terminate at the '\' character
            // to obtain name of the subdirectory to create
            fullFileName[i] = L'\0';

            if (!CreateDirectory(fullFileName, NULL))
            {
                DWORD lastError = GetLastError();

                // It is normal for CreateDirectory to fail if the subdirectory
                // already exists.  Other errors should not be ignored.
                if (lastError != ERROR_ALREADY_EXISTS)
                {
                    hr = HRESULT_FROM_WIN32(lastError);
                }
            }

            // Restore original string
            fullFileName[i] = L'\\';
        }
    }

    // Create stream for writing the file
    if (SUCCEEDED(hr))
    {
        hr = SHCreateStreamOnFileEx(
                fullFileName,
                STGM_CREATE | STGM_WRITE | STGM_SHARE_EXCLUSIVE,
                0, // default file attributes
                TRUE, // create new file if it does not exist
                NULL, // no template
                stream);
    }
    return hr;
}