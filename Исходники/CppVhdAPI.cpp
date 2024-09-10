// Expanding a virtual disk requires that the virtual disk be detached during 
// the operation.
BOOL OpenAndExpandVHD(PCWSTR pszVhdPath, ULONG newSizeMB)
{
    BOOL bRet = FALSE;
    DWORD ret;
    HANDLE hVhd = INVALID_HANDLE_VALUE;
    EXPAND_VIRTUAL_DISK_PARAMETERS xparams;
    VIRTUAL_STORAGE_TYPE            vst =
    {
        VIRTUAL_STORAGE_TYPE_DEVICE_VHD,
        VIRTUAL_STORAGE_TYPE_VENDOR_MICROSOFT
    };

    wprintf(L"OpenAndExpandVHD %s, new size (MB) %d\n", pszVhdPath, newSizeMB);

    ret = OpenVirtualDisk(&vst, pszVhdPath,
        VIRTUAL_DISK_ACCESS_METAOPS,
        OPEN_VIRTUAL_DISK_FLAG_NONE, NULL, &hVhd);

    if (ERROR_SUCCESS == ret) 
    {
        printf("success opening vdisk...\n");
        xparams.Version = EXPAND_VIRTUAL_DISK_VERSION_1;
        xparams.Version1.NewSize = newSizeMB * 1024 * 1024;

        ret = ExpandVirtualDisk(hVhd, EXPAND_VIRTUAL_DISK_FLAG_NONE, &xparams, 0);

        if (ERROR_SUCCESS == ret) 
        {
            printf("success expanding vdisk...\n");
        }
        else
        {
            printf("failed to expand vdisk... %d\n", ret);
            PrintErrorMessage(GetLastError());
            bRet = FALSE;
        }
    }
    else
    {
        printf("failed to open vdisk...err %d\n", ret);
        PrintErrorMessage(GetLastError());
        bRet = FALSE;
    }

    if (INVALID_HANDLE_VALUE != hVhd)
    {
        CloseHandle(hVhd);
    }

    return bRet;
}