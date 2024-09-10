/** 
@ingroup utility_functions

Load the content of a text file into a buffer.  The
buffer is converted into Unicode using the default
engine codepage if it isn't already in Unicode

This code was borrowed from SAPI 5.1 sample CRecogDlgClass::GetTextFile
@param pszFileName - [in] source file name
@param ppwszCoMem - [out] the loaded text buffer
@param pcch - [out] size of text buffer
@return HRESULT hr 
**/
HRESULT GetTextFile(
    const TCHAR* pszFileName,
    WCHAR ** ppwszCoMem,
    ULONG * pcch)
{

    HRESULT hr = S_OK;
    HANDLE hf = INVALID_HANDLE_VALUE;
    DWORD cBytes;
    BOOL fUnicodeFile = FALSE;
    USHORT uTemp;
    WCHAR * pwszCoMem = 0;
    ULONG cch = 0;
    DWORD dwRead;

       

    if (SUCCEEDED(hr))
    {
        hf = CreateFile(pszFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

        hr = (hf != INVALID_HANDLE_VALUE) ? S_OK : HRESULT_FROM_WIN32(CommDlgExtendedError());
    }

    if (SUCCEEDED(hr))
    {
        cBytes = GetFileSize(hf, NULL); // 64K limit

        hr = (cBytes != -1) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
    }

    if (SUCCEEDED(hr))
    {
        hr = ReadFile(hf, &uTemp, 2, &dwRead, NULL) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
    }

    if (SUCCEEDED(hr))
    {
        fUnicodeFile = uTemp == 0xfeff;

        if (fUnicodeFile)
        {
            cBytes -= 2;

            pwszCoMem = (WCHAR *)CoTaskMemAlloc(cBytes);

            if (pwszCoMem)
            {
                hr = ReadFile(hf, pwszCoMem, cBytes, &dwRead, NULL) ? S_OK : HRESULT_FROM_WIN32(GetLastError());

                cch = cBytes / sizeof(WCHAR);
            }
            else
            {
                hr = E_OUTOFMEMORY;
            }
        }
        else
        {
            SPRECOGNIZERSTATUS stat;
            ZeroMemory(&stat, sizeof(stat));
            hr = S_OK;
            if (SUCCEEDED(hr))
            {
                UINT uiCodePage = SpCodePageFromLcid(MAKELCID(LANG_ENGLISH, SORT_DEFAULT));

                char * pszBuffer = (char *)malloc(cBytes);

                hr = pszBuffer ? S_OK : E_OUTOFMEMORY;

                if (SUCCEEDED(hr))
                {
                    SetFilePointer(hf, 0, NULL, FILE_BEGIN); // rewind
        
                    hr = ReadFile(hf, pszBuffer, cBytes, &dwRead, NULL) ? S_OK : HRESULT_FROM_WIN32(GetLastError());
                }

                if (SUCCEEDED(hr))
                {
                    cch = MultiByteToWideChar(uiCodePage, 0, pszBuffer, cBytes, NULL, NULL);

                    if (cch)
                    {
                        pwszCoMem = (WCHAR *)CoTaskMemAlloc(sizeof(WCHAR) * cch);
                    }
                    else
                    {
                        hr = E_FAIL;
                    }
                }

                if (SUCCEEDED(hr))
                {
                    MultiByteToWideChar(uiCodePage, 0, pszBuffer, cBytes, pwszCoMem, cch);
                }

                if (pszBuffer)
                {
                    free(pszBuffer);
                }
            }
        }
    }

    if (INVALID_HANDLE_VALUE != hf)
    {
        CloseHandle(hf);
    }

    *ppwszCoMem = pwszCoMem;
    *pcch = cch;
    
    return hr;
}