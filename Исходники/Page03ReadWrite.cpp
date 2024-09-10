static int UpdateFileData(
    HWND hDlg,
    LPCSTR szDataToFill,
    size_t OffsetToFill,
    UINT FillPattern)
{
    TFileTestData * pData = GetDialogData(hDlg);
    LONGLONG ByteOffset;
    LPBYTE WritePattern = (LPBYTE)"BAADF00D";
    ULONG NewLength;
    ULONG i;
    size_t cchDataToFill = 0;
    HWND hWndChild = GetDlgItem(hDlg, IDC_FILE_DATA);

    // Get the byte offset
    DlgText2Hex64(hDlg, IDC_BYTE_OFFSET, &ByteOffset);
    DlgText2Hex32(hDlg, IDC_LENGTH, &NewLength);

    // Clear the file data from the data editor
    DataEditor_SetData(hWndChild, 0, NULL, 0);

    // Determine the new length of the data
    if(szDataToFill != NULL)
    {
        cchDataToFill = strlen(szDataToFill);
        NewLength = (ULONG)(OffsetToFill + cchDataToFill);
    }

    // If we need to increase the buffer size, do it
    if(NewLength > pData->cbFileDataMax)
    {
        pData->pbFileData = (LPBYTE)HeapReAlloc(g_hHeap, HEAP_ZERO_MEMORY, pData->pbFileData, NewLength);
        if(pData->pbFileData == NULL)
            return ERROR_NOT_ENOUGH_MEMORY;

        pData->cbFileDataMax = NewLength;
    }

    // If we shall fill the data with custom data, do it
    if(szDataToFill != NULL)
    {
        // Fill the gap after end of current data with zeros
        if(OffsetToFill > pData->cbFileData)
            memset(pData->pbFileData + pData->cbFileData, 0, OffsetToFill - pData->cbFileData);
        memcpy(pData->pbFileData + OffsetToFill, szDataToFill, cchDataToFill);
    }

    // If the caller required us to fill the data with pattern, do it
    else
    {
        // If the new pattern is zero, it means to fill the same pattern like before
        if(FillPattern == 0)
            FillPattern = pData->FillPattern;

        // If the pattern is the same like before, just fill the remaining part
        if(OffsetToFill < NewLength)
        {
            switch(FillPattern)
            {
            case IDC_FILL_DATA_ZEROS:
                memset(pData->pbFileData + OffsetToFill, 0, NewLength - OffsetToFill);
                break;

            case IDC_FILL_DATA_PATTERN:
                for(i = (ULONG)OffsetToFill; i < NewLength; i++)
                    pData->pbFileData[i] = WritePattern[i % 8];
                break;

            case IDC_FILL_DATA_RANDOM:
                srand(GetTickCount());
                for(i = (ULONG)OffsetToFill; i < NewLength; i++)
                    pData->pbFileData[i] = (BYTE)(rand() % 0x100);
                break;
            }
        }

        // Remember the current pattern
        pData->FillPattern = FillPattern;
    }

    // Remember the new data length
    if(NewLength != pData->cbFileData)
    {
        Hex2DlgText32(hDlg, IDC_LENGTH, NewLength);
        pData->cbFileData = NewLength;
    }

    // Apply the new file data
    DataEditor_SetData(hWndChild, ByteOffset, pData->pbFileData, pData->cbFileData);
    return ERROR_SUCCESS;
}