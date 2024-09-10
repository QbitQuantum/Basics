static void fillComboBox(HWND hWnd) 
{
  HWND hWndCB = GetDlgItem(hWnd, ID_COMBO_DIR);
  HWND hWndTempLB = GetDlgItem(hWnd, ID_LISTTEMP_DIR);
  if(hWndCB == NULL)
    return;
  ComboBox_ResetContent(hWndCB);
  ListBox_ResetContent(hWndTempLB);
  ListBox_Dir(hWndTempLB, DDL_DRIVES|DDL_EXCLUSIVE, (LPSTR)"*");

  int iDriveCount = ListBox_GetCount(hWndTempLB);
  int iCurDrive=_getdrive() - 1;

  char szDrive[16];
  char szItem[80];

  for (int i = 0; i < iDriveCount;  i++) 
  {
    ListBox_GetText(hWndTempLB, i, szDrive);
    CharLower(szDrive);
    int iDrive = szDrive[2] - 'a';
    char szRoot[16];
    sprintf(szRoot, "%c:\\", szDrive[2]);

    int iType = DriveType(iDrive);

    if(iType < 2)
      continue;

    //Start the item string with the drive letter, colon, and two spaces
    sprintf(szItem, "%c%s", szDrive[2], ": ");

    if((iType == DRIVE_FIXED) || (iType == DRIVE_RAMDISK)) 
    { // get volume ID
      char szVolumeID[80];
      DWORD dwMaxLength;
      DWORD dwSysFlags;
      GetVolumeInformation(szRoot,             // address of root directory of the file system 
                           szVolumeID,         // address of name of the volume 
                           sizeof(szVolumeID), // length of lpVolumeNameBuffer 
                           NULL,               // address of volume serial number 
                           &dwMaxLength,       // address of system's maximum filename length
                           &dwSysFlags,        // address of file system flags 
                           NULL,               // address of name of file system 
                           NULL);              // length of lpFileSystemNameBuffer 

      CharLower(szVolumeID);
      lstrcat(szItem, szVolumeID);
    }

    //For network drives, go grab the \\server\share for it.
    if(DRIVE_REMOTE == iType) 
    {
      char szNet[64];
      szNet[0] = '\0';
      DWORD dwSizeOfszNet = sizeof(szNet);

      sprintf(szDrive, "%c:", szDrive[2]);
      CharUpper(szDrive);
      WNetGetConnection(szDrive, szNet, &dwSizeOfszNet);
      CharLower(szNet);
      lstrcat(szItem, szNet);
    }

    int index = ComboBox_AddString(hWndCB, szItem);
    ComboBox_SetItemData(hWndCB, index, MAKELONG(iDrive, iType));
    if(iDrive == iCurDrive)
      ComboBox_SetCurSel(hWndCB, index);
    if(szUNCRoot[0] != '\0')
      ComboBox_SetCurSel(hWndCB, -1);
  }
}