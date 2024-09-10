//
// PathAddBackslashEx
//
// Checked version of PathAddBackslash which also handles quoted paths
//
// Return values:  S_OK          - backslash appended
//                 S_FALSE       - path already ended with a backslash
//                 E_OUTOFMEMORY - buffer too small
//                 E_FAIL        - other failure (invalid input string)
//
HRESULT PathAddBackslashExA(LPSTR pszPath, size_t cchPath)
{
    ASSERT(cchPath <= STRSAFE_MAX_CCH);
    ASSERT(nullptr != pszPath); ASSERT(0 != cchPath);

    HRESULT hr = E_FAIL;
    size_t cchCurrentLength = 0;

    if (SUCCEEDED(StringCchLengthA(pszPath, cchPath, &cchCurrentLength)))
    {
        bool bHasQuote = false;
        LPSTR ptzEnd = pszPath + cchCurrentLength;

        if ((ptzEnd > pszPath) && (*(ptzEnd-1) == _T('\"')))
        {
            --ptzEnd;
            bHasQuote = true;
        }

        if (ptzEnd > pszPath)
        {
            if (*(ptzEnd-1) != _T('\\'))
            {
                if (cchPath - cchCurrentLength > 1)
                {
                    if (bHasQuote)
                    {
                        *(ptzEnd+1) = *ptzEnd;
                    }

                    *ptzEnd = _T('\\');

                    if (bHasQuote)
                    {
                        ++ptzEnd;
                    }

                    ASSERT((size_t)(ptzEnd - pszPath) < cchPath);
                    *(ptzEnd+1) = _T('\0');

                    hr = S_OK;
                }
                else
                {
                    hr = E_OUTOFMEMORY;
                }
            }
            else
            {
                hr = S_FALSE;
            }
        }
    }

    return hr;
}