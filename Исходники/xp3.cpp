PBYTE uncompress_xp3_idx(HANDLE hFile, PDWORD idx_len, UNCOM unCom)
{
    DWORD ByteRead;
    xp3_file_header header;

    SetFilePointer(hFile, 11, NULL, FILE_BEGIN);
    ReadFile(hFile, &header.offset_lo, 4, &ByteRead, NULL);
    ReadFile(hFile, &header.offset_hi, 4, &ByteRead, NULL);

    if (header.offset_lo != 0x17)
        SetFilePointer(hFile, header.offset_lo, (PLONG)&header.offset_hi, FILE_BEGIN);
    else
    {
        ReadFile(hFile, &header.minor_version, 4, &ByteRead, NULL);
        ReadFile(hFile, &header.flag, 1, &ByteRead, NULL);
        ReadFile(hFile, &header.index_size_lo, 4, &ByteRead, NULL);
        ReadFile(hFile, &header.index_size_hi, 4, &ByteRead, NULL);
        ReadFile(hFile, &header.index_offset_lo, 4, &ByteRead, NULL);
        ReadFile(hFile, &header.index_offset_hi, 4, &ByteRead, NULL);

        SetFilePointer(hFile, header.index_offset_lo, (PLONG)&header.index_offset_hi, FILE_BEGIN);
    }

    BYTE  idx_flag;
    DWORD idx_size_lo;
    DWORD idx_size_hi;
    DWORD idx_uncom_lo;
    DWORD idx_uncom_hi;

    ReadFile(hFile,     &idx_flag, 1, &ByteRead, NULL);
    ReadFile(hFile,  &idx_size_lo, 4, &ByteRead, NULL);
    ReadFile(hFile,  &idx_size_hi, 4, &ByteRead, NULL);
    if (idx_flag)
    {
        ReadFile(hFile, &idx_uncom_lo, 4, &ByteRead, NULL);
        ReadFile(hFile, &idx_uncom_hi, 4, &ByteRead, NULL);
    }
    else
    {
        idx_uncom_lo = idx_size_lo;
        idx_uncom_hi = idx_size_hi;
    }

    PBYTE idx = (u8*)VirtualAlloc(NULL, idx_size_lo, MEM_COMMIT, PAGE_READWRITE);
    PBYTE idx_raw = (u8*)VirtualAlloc(NULL, idx_uncom_lo, MEM_COMMIT, PAGE_READWRITE);
    if (!idx || !idx_raw)
    {
        AppendMsg(L"内存分配失败！");
        return 0;
    }

    ReadFile(hFile, idx, idx_size_lo, &ByteRead, NULL);
    if (idx_flag)
        unCom((PBYTE)idx_raw, &idx_uncom_lo, (PBYTE)idx, idx_size_lo);
    else
        memcpy(idx_raw, idx, idx_size_lo);

    VirtualProtect(idx_raw, idx_uncom_lo, PAGE_READONLY, NULL);
    VirtualFree(idx, idx_size_lo, MEM_DECOMMIT);
    VirtualFree(idx, 0, MEM_RELEASE);

    *idx_len = idx_uncom_lo;
    return idx_raw;
}