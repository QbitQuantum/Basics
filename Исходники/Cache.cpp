// ---------------------------------------------------------------------------
// CCache::NameFromTransCacheEntry
// convert target assembly name from name res entry
//---------------------------------------------------------------------------
HRESULT CCache::NameFromTransCacheEntry(
    CTransCache         *pTransCache,   
    IAssemblyName      **ppName
)
{
    HRESULT hr;
    WORD wVerMajor, wVerMinor, wRevNo, wBldNo;
    TRANSCACHEINFO *pTCInfo = NULL;

    LPBYTE pbPublicKeyToken, pbCustom, pbMVID;
    DWORD  cbPublicKeyToken, cbCustom, cbMVID;


    // IAssemblyName target to be returned.
    IAssemblyName *pNameFinal = NULL;
    
    pTCInfo = (TRANSCACHEINFO*) pTransCache->_pInfo;

    // Mask target major, minor versions and rev#, build#
    wVerMajor = HIWORD(pTCInfo->dwVerHigh);
    wVerMinor = LOWORD(pTCInfo->dwVerHigh);
    wBldNo    = HIWORD(pTCInfo->dwVerLow);
    wRevNo    = LOWORD(pTCInfo->dwVerLow);

    // Currently this function is only called during enuming
    // the global cache so we expect an PublicKeyToken to be present.
    // BUT THIS IS NO LONGER TRUE - THE TRANSPORT CACHE CAN BE
    // INDEPENDENTLY ENUMERATED BUT AM LEAVING IN ASSERT AS COMMENT.
    // ASSERT(pTCInfo->blobPKT.cbSize);
    
    pbPublicKeyToken = pTCInfo->blobPKT.pBlobData;
    cbPublicKeyToken = pTCInfo->blobPKT.cbSize;

    pbCustom = pTCInfo->blobCustom.pBlobData;
    cbCustom = pTCInfo->blobCustom.cbSize;

    pbMVID = pTCInfo->blobMVID.pBlobData;
    cbMVID = pTCInfo->blobMVID.cbSize;


    // Create final name on text name and set properties.
    if (FAILED(hr = CreateAssemblyNameObject(&pNameFinal, pTCInfo->pwzName, NULL, 0)))
        goto exit;

    if(FAILED(hr = pNameFinal->SetProperty(cbPublicKeyToken ? 
        ASM_NAME_PUBLIC_KEY_TOKEN : ASM_NAME_NULL_PUBLIC_KEY_TOKEN,
        pbPublicKeyToken, cbPublicKeyToken)))
        goto exit;

    if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_MAJOR_VERSION, 
             &wVerMajor, sizeof(WORD))))
        goto exit;

    if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_MINOR_VERSION, 
             &wVerMinor, sizeof(WORD))))
        goto exit;

        // Build no.
    if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_BUILD_NUMBER, 
             &wBldNo, sizeof(WORD))))
        goto exit;

        // Revision no.
    if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_REVISION_NUMBER,
             &wRevNo, sizeof(WORD))))
        goto exit;

        // Culture
    if(pTCInfo->pwzCulture)
    {
        if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_CULTURE,
            pTCInfo->pwzCulture, (lstrlen(pTCInfo->pwzCulture) +1) * sizeof(TCHAR))))
            goto exit;
    }


        // Custom
    if(pbCustom)
    {
        if(FAILED(hr = pNameFinal->SetProperty(cbCustom ? 
            ASM_NAME_CUSTOM : ASM_NAME_NULL_CUSTOM, pbCustom, cbCustom)))
            goto exit;
    }

    if(pbMVID)
    {
        // MVID
        if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_MVID, pbMVID, cbMVID)))
            goto exit;
    }

    if(pTCInfo->pwzCodebaseURL)
    {
        // Codebase url
        if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_CODEBASE_URL,
             pTCInfo->pwzCodebaseURL, pTCInfo->pwzCodebaseURL ? 
                (DWORD)((lstrlen(pTCInfo->pwzCodebaseURL) +1) * sizeof(TCHAR)) : 0)))
            goto exit;
    }

    // Codebase url last modified filetime
    if(FAILED(hr = pNameFinal->SetProperty(ASM_NAME_CODEBASE_LASTMOD,
             &pTCInfo->ftLastModified, sizeof(FILETIME))))
        goto exit;

    // We're done and can hand out the target name.
    hr = S_OK;       

exit:
    if (SUCCEEDED(hr))
    {
        *ppName = pNameFinal;
    }
    else
    {
        SAFERELEASE(pNameFinal);
    }
    return hr;
}