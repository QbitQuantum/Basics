bool KAppRes::PrepareRes()
{
    bool retval = false;
    KFilePath pathRes = KFilePath::GetFilePath(g_hInstance);
    HRSRC hResInfo = NULL;
    HGLOBAL hResDat = NULL;
    PVOID pResBuffer = NULL;
    DWORD dwResBuffer;
    wchar_t szTempPath[MAX_PATH] = { 0 };
    wchar_t szTempFilePath[MAX_PATH] = { 0 };
    //BOOL fRetCode;
    //DWORD dwWritten;

    pathRes.RemoveExtension();
    pathRes.AddExtension(L"kui");

    if (GetFileAttributesW(pathRes) != INVALID_FILE_ATTRIBUTES)
    {
        m_strResPackPath = pathRes.value();
    }
    else
    {
        hResInfo = FindResourceW(_ModulePtr->GetResourceInstance(), L"kuires.dat", L"SKIN");
        if (!hResInfo)
            goto clean0;
        
        hResDat = LoadResource(_ModulePtr->GetResourceInstance(), hResInfo);
        if (!hResDat)
            goto clean0;

        pResBuffer = LockResource(hResDat);
        if (!pResBuffer)
            goto clean0;

        dwResBuffer = SizeofResource(_ModulePtr->GetResourceInstance(), hResInfo);
		m_memZipRes.SetData(pResBuffer, dwResBuffer);

       /* GetTempPathW(MAX_PATH, szTempPath);
        GetTempFileNameW(szTempPath, L"kui", 0, szTempFilePath);
        m_hTempRes = CreateFileW(szTempFilePath, GENERIC_ALL, FILE_SHARE_READ, NULL, 
            CREATE_ALWAYS, FILE_ATTRIBUTE_TEMPORARY, NULL);
        if (INVALID_HANDLE_VALUE == m_hTempRes)
            goto clean0;

        fRetCode = WriteFile(m_hTempRes, pResBuffer, dwResBuffer, &dwWritten, NULL);
        if (!fRetCode)
            goto clean0;

        fRetCode = FlushFileBuffers(m_hTempRes);

        m_strResPackPath = szTempFilePath;*/
    }
    
    retval = true;

clean0:
    return retval;
}