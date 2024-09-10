HRESULT GetFusionInfo(CTransCache *pTC, LPWSTR pszAsmDir)
{
    HRESULT hr = S_OK;
    WCHAR   wzFilePath[MAX_PATH+1];
    DWORD  cbSize=0;
    PBYTE pMVID=NULL;
    DWORD dwAttrib;
    DWORD cb;
    IAssemblyName *pName=NULL;
    LPWSTR pszBuf=NULL;
    BOOL bMVIDFailed=FALSE;
    BOOL bCustomFailed=FALSE;
    BOOL bURLFailed=FALSE;
    BOOL bDispNameFailed=FALSE;
    HINI hIni=NULL;
    TRANSCACHEINFO *pTCInfo = NULL;

    ASSERT(pszAsmDir || (pTC && pTC->_pInfo->pwzPath));

    pszBuf = NEW(WCHAR[MAX_URL_LENGTH+1]);
    if (!pszBuf)
    {
        hr = E_OUTOFMEMORY;
        goto exit;
    }

    if(pTC && pTC->_pInfo->pwzPath)
    {  
        // if there is path is transprtCache obj use it. else use second param pszAsmDir
        wnsprintf(wzFilePath, MAX_PATH, L"%s", pTC->_pInfo->pwzPath);
    }
    else
    {
        wnsprintf(wzFilePath, MAX_PATH, L"%s", pszAsmDir);
    }

    if((dwAttrib = GetFileAttributes(wzFilePath)) == (DWORD) -1)
    {
        hr = E_FAIL;
        goto exit;
    }

    if(!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY))
    {
        // looks manifestFilePath is passed in. knock-off the filename.
        LPWSTR pszTemp = PathFindFileName(wzFilePath);
        if(pszTemp > wzFilePath)
        {
            *(pszTemp-1) = L'\0';
        }
    }
    // else we have assembly dir;

    wnsprintf(wzFilePath, MAX_PATH, L"%s\\%s", wzFilePath, g_FusionInfoFile);

    if ((hIni = PAL_IniCreate()) == NULL)
    {
        hr = FusionpHresultFromLastError();
        goto exit;
    }

    if (!PAL_IniLoad(hIni, wzFilePath))
    {
        hr = FusionpHresultFromLastError();
        goto exit;
    }

#define _ReadString(section, key, buf, size) PAL_IniReadString(hIni, section, key, buf, size)

    pTCInfo = (TRANSCACHEINFO*) pTC->_pInfo;

    cbSize = _ReadString(ASSEMBLY_INFO_STRING, MVID_KEY_STRING, pszBuf, MAX_URL_LENGTH);

    if(cbSize == MVID_LENGTH*2)
    {
        pMVID = NEW(BYTE[MVID_LENGTH]);
        if (!pMVID)
        {
            hr = E_OUTOFMEMORY;
            goto exit;
        }

        CParseUtils::UnicodeHexToBin(pszBuf, MVID_LENGTH*2, (LPBYTE) pMVID);

        SAFEDELETEARRAY(pTCInfo->blobMVID.pBlobData);
        pTCInfo->blobMVID.pBlobData = pMVID;
        pTCInfo->blobMVID.cbSize = MVID_LENGTH;
        pMVID = NULL;
    }
    else
        bMVIDFailed = TRUE;

    if(pTC->GetCacheType() & ASM_CACHE_ZAP)
    {
        cbSize = _ReadString(ASSEMBLY_INFO_STRING, CUSTOM_BLOB_STRING, pszBuf, MAX_URL_LENGTH);

        if(cbSize)
        {
            SAFEDELETEARRAY(pTCInfo->blobCustom.pBlobData);
            pTCInfo->blobCustom.pBlobData = (PBYTE) WSTRDupDynamic(pszBuf);
            if (!pTCInfo->blobCustom.pBlobData)
            {
                hr = E_OUTOFMEMORY;
                goto exit;
            }
            pTCInfo->blobCustom.cbSize = (cbSize + 1) * sizeof(WCHAR) ;
        }
        else
            bCustomFailed = TRUE;

    }
    else
    {
        cbSize = _ReadString(ASSEMBLY_INFO_STRING, URL_STRING, pszBuf, MAX_URL_LENGTH);

        if(cbSize)
        {
            SAFEDELETEARRAY(pTCInfo->pwzCodebaseURL);
            pTCInfo->pwzCodebaseURL = WSTRDupDynamic(pszBuf);

            if (!pTCInfo->pwzCodebaseURL)
            {
                hr = E_OUTOFMEMORY;
                goto exit;
            }
        }
        else
            bURLFailed = TRUE;

        if(pTC->GetCacheType() & ASM_CACHE_DOWNLOAD)
        {
            cbSize = _ReadString(ASSEMBLY_INFO_STRING, DISPLAY_NAME_STRING, pszBuf, MAX_URL_LENGTH);

            if(cbSize)
            {
                if (FAILED(hr = CreateAssemblyNameObject(&pName, pszBuf, CANOF_PARSE_DISPLAY_NAME, 0)))
                    goto exit;

                SAFEDELETEARRAY(pTCInfo->pwzName);

                if (FAILED(hr = NameObjGetWrapper(pName, ASM_NAME_NAME,
                        (LPBYTE*) &pTCInfo->pwzName, &(cb = 0))))
                    goto exit;

                // Version
                if(FAILED(hr = pName->GetVersion(&pTCInfo->dwVerHigh, &pTCInfo->dwVerLow)))
                    goto exit;

                SAFEDELETEARRAY(pTCInfo->pwzCulture);

                // Culture
                if(FAILED(hr = NameObjGetWrapper(pName, ASM_NAME_CULTURE,
                    (LPBYTE*) &pTCInfo->pwzCulture, &cb))
                        || (pTCInfo->pwzCulture && !_wcslwr(pTCInfo->pwzCulture)))
                    goto exit;

                SAFEDELETEARRAY(pTCInfo->blobPKT.pBlobData);

                // PublicKeyToken
                if(FAILED(hr = NameObjGetWrapper(pName, ASM_NAME_PUBLIC_KEY_TOKEN, 
                    &pTCInfo->blobPKT.pBlobData, &pTCInfo->blobPKT.cbSize)))
                    goto exit;
            }
            else
                bDispNameFailed = TRUE;
        }
    }

exit:

    SAFEDELETEARRAY(pszBuf);
    SAFEDELETEARRAY(pMVID);
    SAFERELEASE(pName);

    if(SUCCEEDED(hr))
    {
        if(bMVIDFailed || bCustomFailed)
            hr = E_FAIL;
        else if(bDispNameFailed || bURLFailed)
            hr = S_FALSE;
    }

    return hr;
}