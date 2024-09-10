/// Decode
///
/// @param pclArc Archive
///
BOOL CPaz::Decode(CArcFile* pclArc)
{
    if (pclArc->GetArcExten() != _T(".paz"))
        return FALSE;

    // Initialize decryption key
    InitDecodeKey(pclArc);

    // Initialize Table
    InitTable();

    // Decrypt table
    DecodeTable1();
    DecodeTable2();

    // Create output file
    SFileInfo* pstFileInfo = pclArc->GetOpenFileInfo();

    if (lstrcmpi(PathFindExtension(pstFileInfo->name), _T(".sc")) == 0)
    {
        pclArc->OpenScriptFile();
    }
    else
    {
        pclArc->OpenFile();
    }

    // Output

    if (pstFileInfo->format == _T("zlib"))
    {
        // ZLIB

        DWORD dwSrcSize = pstFileInfo->sizeCmp;
        DWORD dwDstSize = pstFileInfo->sizeOrg;

        YCMemory<BYTE> clmbtSrc(dwSrcSize);
        YCMemory<BYTE> clmbtDst(dwDstSize);

        // Decrypt
        pclArc->Read(&clmbtSrc[0], dwSrcSize);
        Decrypt(&clmbtSrc[0], dwSrcSize);
        DecodeData(&clmbtSrc[0], dwSrcSize);
        Decrypt2(&clmbtSrc[0], dwSrcSize);

        // Decompress
        CZlib clZlib;
        clZlib.Decompress(&clmbtDst[0], dwDstSize, &clmbtSrc[0], dwSrcSize);

        // Output
        pclArc->WriteFile(&clmbtDst[0], dwDstSize);
    }
    else
    {
        if (pclArc->GetArcName() == _T("mov.paz"))
        {
            // Movie
            DWORD dwBufferSize = GetMovieBufSize(pclArc);
            YCMemory<BYTE> clmbtBuffer(dwBufferSize);

            for (DWORD dwWriteTotal = 0; dwWriteTotal != pstFileInfo->sizeOrg; dwWriteTotal += dwBufferSize)
            {
                // Get buffer size
                pclArc->SetBufSize(&dwBufferSize, dwWriteTotal, pstFileInfo->dwSizeOrg2);

                // Read
                pclArc->Read(&clmbtBuffer[0], dwBufferSize);

                // Decrypt
                Decrypt(&clmbtBuffer[0], dwBufferSize);
                DecodeMovieData(&clmbtBuffer[0], dwBufferSize);
                Decrypt2(&clmbtBuffer[0], dwBufferSize);

                // Adjust buffer size
                pclArc->SetBufSize(&dwBufferSize, dwWriteTotal, pstFileInfo->sizeOrg);

                // Write
                pclArc->WriteFile(&clmbtBuffer[0], dwBufferSize);
            }
        }
        else
        {
            // Other data

            DWORD dwBufferSize = pclArc->GetBufSize();

            YCMemory<BYTE> clmbtBuffer(dwBufferSize);

            for (DWORD dwWriteTotal = 0; dwWriteTotal != pstFileInfo->sizeOrg; dwWriteTotal += dwBufferSize)
            {
                // Adjust buffer size
                pclArc->SetBufSize(&dwBufferSize, dwWriteTotal, pstFileInfo->dwSizeOrg2);

                // Read
                pclArc->Read(&clmbtBuffer[0], dwBufferSize);

                // Decrypt
                Decrypt(&clmbtBuffer[0], dwBufferSize);
                DecodeData(&clmbtBuffer[0], dwBufferSize);
                Decrypt2(&clmbtBuffer[0], dwBufferSize);

                // Adjust buffer size
                pclArc->SetBufSize(&dwBufferSize, dwWriteTotal, pstFileInfo->sizeOrg);

                // Write
                pclArc->WriteFile(&clmbtBuffer[0], dwBufferSize);
            }
        }
    }

    return TRUE;
}