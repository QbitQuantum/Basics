static BOOL FillDriveList()
{
    DRIVE_INFO di;

    TCHAR chDrive = TEXT('A');
    DWORD dwDrives = GetLogicalDrives();

    // This failing is not fatal to this function
    // Make sure the partition table is up to date
    afs_status_t nStatus;
    int nResult = ReadPartitionTable(&nStatus);
    ASSERT(nResult);

    while (dwDrives) {
	if (dwDrives & 1) {
	    memset(&di, 0, sizeof(di));

	    if (GetDriveInfo(chDrive, di)) {
		FASTLISTADDITEM ai = { 0, di.nImage, IMAGE_NOIMAGE, di.szRootDir, di.bDisabled, di.dwFlags };
		HLISTITEM hItem = FastList_AddItem(m_hDriveList, &ai);
		FastList_SetItemText(m_hDriveList, hItem, 1, di.szVolName);
		FastList_SetItemText(m_hDriveList, hItem, 2, di.szSize);
	    }
	}

	chDrive++;
	dwDrives >>= 1;
    }

    return TRUE;
}