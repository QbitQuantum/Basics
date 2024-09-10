Void
CALLBACK
PackFiles(
    SPackFileInfo *pPackFileInfo,
    UInt32         uCount,
    PCWChar        pszOutput,
    PCWChar        pszFullInputPath,
    PCWChar        pszParam,
    FShowStatus    ShowStatus
)
{
    CMem    m;
    HANDLE  hFile, hFilePack;
    UInt32  BufferSize, CompressBufferSize;
    DWORD   dwRead;
    WChar   szPath[MAX_PATH];
    LPVoid  lpBuffer, lpCompressBuffer;
    Large_Integer liOffset;
    SPackFileInfo *pInfo;
    SMyPackIndex  *pIndex, *pPackIndex;

    hFilePack = CreateFileW(pszOutput, 
        GENERIC_READ|GENERIC_WRITE, 
        FILE_SHARE_READ|FILE_SHARE_WRITE, 
        NULL, 
        CREATE_ALWAYS, 
        FILE_ATTRIBUTE_NORMAL, 
        NULL);
    if (hFilePack == INVALID_HANDLE_VALUE)
        return;

    GetCurrentDirectoryW(countof(szPath), szPath);
    SetCurrentDirectoryW(pszFullInputPath);

    pIndex = (SMyPackIndex *)m.Alloc(uCount * sizeof(*pIndex), HEAP_ZERO_MEMORY);
    if (pIndex == NULL)
        return;

    static Char Sig[]  = "Amano Tooko";
    static Char Tag[]  = "FilePackVer3.0";
    static Char Seed[] = "8hr48uky,8ugi8ewra4g8d5vbf5hb5s6";
    UInt32 Key;
    SPackHeader PackHeader;

    ZeroMemory(&PackHeader, sizeof(PackHeader));
    memcpy(PackHeader.Seed, Seed, sizeof(PackHeader.Seed));
    memcpy(PackHeader.tag, Tag, sizeof(PackHeader.tag));

#if 1
    for (UInt32 i = 0, j = 1; i != sizeof(PackHeader.Data) / sizeof(i); ++i)
    {
//        j = _rotl(GetRandom32(), (Byte)j);
        j = GetRandom32();
        *((PUInt32)PackHeader.Data + i) = j;
//        j = _rotl(j, (Byte)HIBYTE(j));
        Sleep(1);
    }
/*
    for (UInt32 i = 0, j = 1; i != sizeof(PackHeader.arr) / sizeof(i); ++i)
    {
//        j = _rotl(GetRandom32(), (Byte)j);
        j = GetRandom32();
        *((PUInt32)PackHeader.arr + i) = j;
        Sleep(1);
//        j = _rotl(j, (Byte)HIBYTE(j));
    }
*/
    memcpy((PByte)&PackHeader.tag - sizeof(Sig) + 1, Sig, sizeof(Sig) - 1);

#else
    lstrcpyA(PackHeader.Data, "Amano Tooko");
#endif

    PackHeader.FileNum = uCount;

    Key = Hash(PackHeader.Data, sizeof(PackHeader.Data)) & 0x0FFFFFFF;
    Encrypt(PackHeader.Seed, sizeof(PackHeader.Seed), Key);

    BufferSize = 0x10000;
    CompressBufferSize = BufferSize;
    lpBuffer = m.Alloc(BufferSize);
    lpCompressBuffer = m.Alloc(CompressBufferSize);

    liOffset.QuadPart = 0;
    pInfo = pPackFileInfo;
    pPackIndex = pIndex;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex, ++pInfo)
    {
        lstrcpyW(pIndex->FileName, pInfo->pFileName);
        hFile = CreateFileW(pInfo->pFileName, 
                    GENERIC_READ, 
                    FILE_SHARE_READ, 
                    NULL, 
                    OPEN_EXISTING, 
                    FILE_ATTRIBUTE_NORMAL, 
                    NULL);
        if (hFile == INVALID_HANDLE_VALUE)
            continue;

        dwRead = GetFileSize(hFile, NULL);
        pIndex->DecompressSize = dwRead;
        pIndex->CompressedSize = dwRead;
        pIndex->bEncrypted     = True;
        if (dwRead > BufferSize)
        {
            BufferSize = dwRead;
            lpBuffer = m.ReAlloc(lpBuffer, BufferSize);
        }

        if (dwRead)
        {
            ReadFile(hFile, lpBuffer, dwRead, &dwRead, NULL);
        }
        CloseHandle(hFile);

        pIndex->Offset = liOffset;
        if (dwRead)
        {
#if 1
            ULong MaxCompressedSize;

            MaxCompressedSize = GetMaxCompressedSize(lpBuffer, dwRead);
            if (MaxCompressedSize > CompressBufferSize)
            {
                CompressBufferSize = MaxCompressedSize;
                lpCompressBuffer = m.ReAlloc(lpCompressBuffer, CompressBufferSize);
            }

            if (MaxCompressedSize > BufferSize)
            {
                BufferSize = MaxCompressedSize;
                lpBuffer = m.ReAlloc(lpBuffer, BufferSize);
            }

            MaxCompressedSize = QLIECompress(
                                    lpBuffer,
                                    dwRead,
                                    lpCompressBuffer,
                                    MaxCompressedSize);

            if (MaxCompressedSize != 0 && MaxCompressedSize < dwRead)
            {
                dwRead = MaxCompressedSize;
                memcpy(lpBuffer, lpCompressBuffer, dwRead);
                pIndex->bCompressed = True;
                pIndex->CompressedSize = dwRead;
            }

#endif
            Encrypt(lpBuffer, dwRead, Key);
            pIndex->Hash = Hash(lpBuffer, dwRead);
        }
        else
        {
            SPackEntryCompressedData *pData = (SPackEntryCompressedData *)lpBuffer;

            pData->Magic = QLIE_COMP_MAGIC;
            pData->Flag = 1;
            pData->DecompressSize = 0;
            *(PUInt32)pData->Data = 0xFFFE7FFE;
            *(PUInt16)&pData->Data[4] = 0;

            pIndex->bEncrypted = False;
            pIndex->bCompressed = True;
            dwRead = 0x12;
            pIndex->CompressedSize = dwRead;
            pIndex->Hash = Hash(lpBuffer, dwRead);
        }

        WriteFile(hFilePack, lpBuffer, dwRead, &dwRead, NULL);
        liOffset.QuadPart += dwRead;
        if (ShowStatus)
        {
            WChar buf[400];
            swprintf(buf, L"%u / %u : %s", i + 1, uCount, pIndex->FileName);
            ShowStatus(buf, (i + 1) * 100 / uCount);
        }
    }

    UInt32 CodePage;
    Char szFile[MAX_PATH];
    PWChar pCharMap;

    pCharMap = CreateCharMapW(NULL, 0);

    CodePage = CP_SHIFTJIS;
    if (pszParam)
    {
        if (!StrICompareW(pszParam, L"gb2312"))
            CodePage = CP_GB2312;
    }

    pIndex = pPackIndex;
    for (UInt32 i = 0; i != uCount; ++i, ++pIndex)
    {
        UInt32 Len;
        FilterStringWithConvertTable(pIndex->FileName, -1, pCharMap);
        Len = WideCharToMultiByte(CodePage, 0, pIndex->FileName, -1, szFile, sizeof(szFile), 0, 0);
        --Len;
        EncryptFileName(szFile, Len, Key);
        WriteFile(hFilePack, &Len, 2, &dwRead, NULL);
        WriteFile(hFilePack, szFile, Len, &dwRead, NULL);
        dwRead = sizeof(*pIndex) - sizeof(pIndex->FileName);
        WriteFile(hFilePack, &pIndex->Offset, dwRead, &dwRead, NULL);
    }

    const UInt32 SubTableNum = 256;
    pbool  pMask;
    PByte  pbBuffer;
    UInt32 HashTableSize;
    SPackHashTableHeader hashtbl, *pHashTable;
    static Char HashVer[] = "HashVer1.3";

    // calc maximum hash table size

    HashTableSize = sizeof(*pHashTable) - sizeof(pHashTable->Data);
    HashTableSize += FakeCompress(0, 0, 0, 0);      // compressed data header

    // Len + Name(MAX) + Offset + Crc + FileIndex

    HashTableSize += uCount * (2 + MAX_PATH + 8 + 4) + uCount * 2;

    pHashTable = (SPackHashTableHeader *)m.Alloc(HashTableSize);
    if (pHashTable == NULL)
    {
        MessageBoxW(0, L"Allocate memory for hash table failed", 0, 64);
        goto PACK_END;
    }
    pMask = (pbool)m.Alloc(uCount, HEAP_ZERO_MEMORY);
    if (pMask == NULL)
    {
        m.Free(pHashTable);
        MessageBoxW(0, L"Allocate memory for hash table masks failed", 0, 64);
        goto PACK_END;
    }

    // generate

    memcpy(pHashTable->HashVer, HashVer, sizeof(pHashTable->HashVer));
    pHashTable->SubTableNum = SubTableNum;
    pHashTable->FileNum = uCount;
    pHashTable->FileIndexSize = uCount * 2;

    pbBuffer = (PByte)&pHashTable->Data;
    for (UInt32 i = 0; i != SubTableNum; ++i)
    {
        PByte pbOutput;
        UInt32 Count;

        Count = 0;
        pbOutput = pbBuffer + 2;
        pIndex = pPackIndex;
        for (UInt32 j = 0; j != uCount; ++j, ++pIndex)
        {
            UInt32 Len;
            CONTINUE_IF(pMask[j]);

            Len = WideCharToMultiByte(CodePage, 0, pIndex->FileName, -1, szFile, sizeof(szFile), 0, 0) - 1;
            if(GetStringSubIndex(szFile, Len, SubTableNum) != i)
            {
                continue;
            }

            pMask[j] = true;
            ++Count;

            *(PUInt16)pbOutput = Len;       // name len
            pbOutput += 2;
            memcpy(pbOutput, szFile, Len);  // name
            pbOutput += Len;
            *(PUInt64)pbOutput = j * 2;     // offset
            pbOutput += 8;
            *(PUInt32)pbOutput = CRC(szFile, Len);
            pbOutput += 4;
        }

        *(PUInt16)pbBuffer = Count;
        pbBuffer = pbOutput;
    }

    for (UInt32 i = 0; i != uCount; ++i)
    {
        *(PUInt16)pbBuffer = i;
        pbBuffer += 2;
    }

    HashTableSize = pbBuffer - (PByte)&pHashTable->Data;

#if 1
    ULong MaxCompressedSize;

    dwRead = HashTableSize;
    MaxCompressedSize = GetMaxCompressedSize(NULL, dwRead);
    if (MaxCompressedSize > CompressBufferSize)
    {
        CompressBufferSize = MaxCompressedSize;
        lpCompressBuffer = m.ReAlloc(lpCompressBuffer, CompressBufferSize);
    }

    MaxCompressedSize = QLIECompress(
                            &pHashTable->Data,
                            HashTableSize,
                            lpCompressBuffer,
                            CompressBufferSize);

    if (MaxCompressedSize == 0 || MaxCompressedSize >= dwRead)
    {
        dwRead = FakeCompress(
                     &pHashTable->Data,
                     HashTableSize,
                     lpCompressBuffer,
                     CompressBufferSize);
    }
    else
    {
        dwRead = MaxCompressedSize;
    }

#else
    dwRead = FakeCompress(0, HashTableSize, 0, 0);
    if (dwRead > CompressBufferSize)
    {
        CompressBufferSize = dwRead;
        lpCompressBuffer = m.ReAlloc(lpCompressBuffer, CompressBufferSize);
    }

    dwRead = FakeCompress(&pHashTable->Data, HashTableSize, lpCompressBuffer, CompressBufferSize);
#endif

    Encrypt(lpCompressBuffer, dwRead, 0x428);
    memcpy(&pHashTable->Data, lpCompressBuffer, dwRead);
    pHashTable->CompressedSize = dwRead;

    PackHeader.HashTableSize = sizeof(*pHashTable) - sizeof(pHashTable->Data) + dwRead;
    PackHeader.IndexOffset = liOffset;

    WriteFile(hFilePack, pHashTable, PackHeader.HashTableSize, &dwRead, NULL);
    WriteFile(hFilePack, &PackHeader, sizeof(PackHeader), &dwRead, NULL);

PACK_END:
    CloseHandle(hFilePack);

    FreeCharMap(pCharMap);
    m.Free(lpBuffer);
    m.Free(lpCompressBuffer);

    SetCurrentDirectoryW(szPath);

    ReleaseGlobalData();
}