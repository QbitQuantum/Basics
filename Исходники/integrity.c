/***********************************************************************
 *		ImageRemoveCertificate (IMAGEHLP.@)
 */
BOOL WINAPI ImageRemoveCertificate(HANDLE FileHandle, DWORD Index)
{
    DWORD size = 0, count = 0, sd_VirtualAddr = 0, offset = 0;
    DWORD data_size = 0, cert_size = 0, cert_size_padded = 0, ret = 0;
    LPVOID cert_data;
    BOOL r;

    TRACE("(%p, %d)\n", FileHandle, Index);

    r = ImageEnumerateCertificates(FileHandle, CERT_SECTION_TYPE_ANY, &count, NULL, 0);

    if ((!r) || (count == 0))
        return FALSE;

    if ((!IMAGEHLP_GetSecurityDirOffset(FileHandle, &sd_VirtualAddr, &size)) ||
        (!IMAGEHLP_GetCertificateOffset(FileHandle, Index, &offset, &cert_size)))
        return FALSE;

    /* Ignore any padding we have, too */
    if (cert_size % 8)
        cert_size_padded = cert_size + (8 - (cert_size % 8));
    else
        cert_size_padded = cert_size;

    data_size = size - (offset - sd_VirtualAddr) - cert_size_padded;

    if (data_size == 0)
    {
        ret = SetFilePointer(FileHandle, sd_VirtualAddr, NULL, FILE_BEGIN);

        if (ret == INVALID_SET_FILE_POINTER)
            return FALSE;
    }
    else
    {
        cert_data = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, data_size);

        if (!cert_data)
            return FALSE;

        ret = SetFilePointer(FileHandle, offset + cert_size_padded, NULL, FILE_BEGIN);

        if (ret == INVALID_SET_FILE_POINTER)
            goto error;

        /* Read any subsequent certificates */
        r = ReadFile(FileHandle, cert_data, data_size, &count, NULL);

        if ((!r) || (count != data_size))
            goto error;

        SetFilePointer(FileHandle, offset, NULL, FILE_BEGIN);

        /* Write them one index back */
        r = WriteFile(FileHandle, cert_data, data_size, &count, NULL);

        if ((!r) || (count != data_size))
            goto error;

        HeapFree(GetProcessHeap(), 0, cert_data);
    }

    /* If security directory is at end of file, trim the file */
    if (GetFileSize(FileHandle, NULL) == sd_VirtualAddr + size)
        SetEndOfFile(FileHandle);

    if (count == 1)
        r = IMAGEHLP_SetSecurityDirOffset(FileHandle, 0, 0);
    else
        r = IMAGEHLP_SetSecurityDirOffset(FileHandle, sd_VirtualAddr, size - cert_size_padded);

    if (!r)
        return FALSE;

    if (!IMAGEHLP_RecalculateChecksum(FileHandle))
        return FALSE;

    return TRUE;

error:
    HeapFree(GetProcessHeap(), 0, cert_data);
    return FALSE;
}