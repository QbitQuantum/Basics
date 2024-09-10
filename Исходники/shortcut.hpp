        static HRESULT _ExpandFullPathName( CString& strPathName )
        {
            DWORD dwLen = ::GetFullPathName(strPathName, 0, NULL, NULL);
            if (0 == dwLen)
                return GetLastError() ? AtlHresultFromLastError() : E_FAIL;

            assert(dwLen <= WIN_PATH_MAX_UNICODE_PATH);
            if (dwLen > WIN_PATH_MAX_UNICODE_PATH)
                return E_UNEXPECTED;

            CString strFullPathName;
            dwLen = ::GetFullPathName(strPathName, dwLen, strFullPathName.GetBuffer(dwLen), NULL);
            if (0 == dwLen)
            {
                strFullPathName.ReleaseBuffer(0);
                return GetLastError() ? AtlHresultFromLastError() : E_FAIL;
            }

            strFullPathName.ReleaseBuffer();
            strPathName = strFullPathName;
            return S_OK;
        }