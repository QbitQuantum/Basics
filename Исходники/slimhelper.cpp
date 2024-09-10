BOOL slimhelper::RecyclePath(const CString& strFilePath, BOOL bKeepRootDir)
{
    BOOL retval = FALSE;
    CString strOldSecurityDescriptor;
    HRESULT hr;
    int nRetCode;
    ULARGE_INTEGER tempSize;
    DWORD dwFileAttributes;
    BOOL bIsDir = FALSE;
    SHFILEOPSTRUCTW fileopt = { 0 };
    ULONGLONG qwFileSize = 0;
    TCHAR* szDelPath = new TCHAR[MAX_PATH * 2];
    CString strFlagFile;

    RtlZeroMemory(szDelPath, sizeof(TCHAR) * MAX_PATH * 2);
    StringCchCopy(szDelPath, MAX_PATH * 2, strFilePath);

    fileopt.pFrom = szDelPath;
    fileopt.wFunc = FO_DELETE;
    fileopt.fFlags = FOF_SILENT|FOF_NOCONFIRMATION|FOF_NOERRORUI|FOF_ALLOWUNDO;

    dwFileAttributes = ::GetFileAttributes(strFilePath);
    if (INVALID_FILE_ATTRIBUTES == dwFileAttributes)
        goto clean0;

    if (dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        bIsDir = TRUE;

    GrantFileAccess(strFilePath, strOldSecurityDescriptor, bIsDir);
    //if (!GrantFileAccess(strFilePath, strOldSecurityDescriptor))
    //    goto clean0;

    strFlagFile = strFilePath + _T("\\"); 
    strFlagFile += g_kSlimFlag;

    if (bIsDir)
    {
        ::DeleteFile(strFlagFile);
        nRetCode = SHFileOperationW(&fileopt);
        if (32 == nRetCode)
            goto clean0;

        if (0x78 == nRetCode || 5 == nRetCode)
        {
            GrantDirAccess(strFilePath);
            ::DeleteFile(strFlagFile);
            nRetCode = SHFileOperationW(&fileopt);;
        }

        if (!nRetCode)
        {
            if (bKeepRootDir)
            {
                ::CreateDirectory(strFilePath, NULL);
                // 创建瘦身后的标记文件
//                 CAtlFile file;
//                 file.Create(strFlagFile, 
//                     FILE_GENERIC_WRITE, 
//                     FILE_SHARE_READ|FILE_SHARE_WRITE,
//                     CREATE_ALWAYS);
            }
            retval = TRUE;
        }
        goto clean0;
    }

    if (dwFileAttributes & FILE_ATTRIBUTE_COMPRESSED
        || dwFileAttributes & FILE_ATTRIBUTE_SPARSE_FILE)
    {
        tempSize.LowPart = GetCompressedFileSize(strFilePath, &tempSize.HighPart);
        qwFileSize = tempSize.QuadPart;
    }
    else
    {
        CAtlFile file;
        hr = file.Create(strFilePath, 
                         FILE_GENERIC_READ, 
                         FILE_SHARE_READ|FILE_SHARE_WRITE|FILE_SHARE_DELETE,
                         OPEN_EXISTING);
        if (FAILED(hr))
            goto clean0;

        tempSize.LowPart = GetFileSize((HANDLE)file, &tempSize.HighPart);
        qwFileSize = tempSize.QuadPart;
    }

    qwFileSize = FileSizeConver::Instance().FileSizeOnDisk(qwFileSize);

    nRetCode = SHFileOperationW(&fileopt);
    if (nRetCode)
        goto clean0;

    retval = TRUE;

clean0:
    if (szDelPath)
    {
        delete[] szDelPath;
        szDelPath = NULL;
    }

    return retval;
}