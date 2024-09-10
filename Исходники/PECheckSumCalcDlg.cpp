void CPECheckSumCalcDlg::OnBnProcessClicked()
{
    // Needs to open a file for reading & writing
    GetDlgItem(IDC_FILEPATHEDIT)->GetWindowText(m_strFileName);
    HANDLE hFile = CreateFile(m_strFileName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        return;
    }
    DWORD dwFileSize = GetFileSize(hFile, NULL);

    // the mapping is easiest way to calculate check sum and rewrite it
    HANDLE hFileMapping = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 0, NULL);
    if (hFileMapping == NULL) {
        CloseHandle(hFile);
        return;
    }

    DWORD dwHdrCheckSum, dwCheckSum;
    LPVOID pBaseAddr = MapViewOfFile(hFileMapping, FILE_MAP_WRITE, 0, 0, dwFileSize);
    if (pBaseAddr == NULL) {
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        return;
    }
    PIMAGE_NT_HEADERS pImageNTHdr = CheckSumMappedFile(pBaseAddr, dwFileSize, &dwHdrCheckSum, &dwCheckSum);
    if (pImageNTHdr == NULL) {
        UnmapViewOfFile(pBaseAddr);
        CloseHandle(hFileMapping);
        CloseHandle(hFile);
        return;
    }
    // Save the control check sum
    pImageNTHdr->OptionalHeader.CheckSum = dwCheckSum;
    UnmapViewOfFile(pBaseAddr);
    CloseHandle(hFileMapping);
    CloseHandle(hFile);
	EndDialog(0);
}