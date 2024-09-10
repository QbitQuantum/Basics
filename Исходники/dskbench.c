BOOL
InitDialog (
    HWND hwnd,
    HWND hwndFocus,
    LPARAM lParam
    )
{
    BOOLEAN Found = FALSE;
    CHAR   buffer[34];
    DWORD  bytes;
    HWND   Drives = GetDlgItem (hwnd,DRV_BOX);
    PCHAR  lp;
    UINT   i = 0,
           NoDrives = 0;

    srand(GetTickCount());
    Button_Enable(GetDlgItem(hwnd,STOP_BUTTON), FALSE);


    //
    // Get attached drives, filter out non-disk drives, and fill drive box.
    //

    bytes = GetLogicalDriveStrings(0,NULL);

    DrvStrHandle = VirtualAlloc(NULL,bytes + 1,
                                MEM_COMMIT | MEM_RESERVE,
                                PAGE_READWRITE);

    GetLogicalDriveStrings( bytes, DrvStrHandle);
    for (lp = DrvStrHandle;*lp; ) {
        if (GetDriveType(lp) == DRIVE_FIXED) {
            ComboBox_AddString(Drives,lp);
            ++NoDrives;
        }
        while(*lp++);
    }

    //
    // Check for cmd line params passed in, and set the test drive to either
    // the specified drive, or to the first in the drive list.
    //

    ComboBox_SetCurSel (Drives,0);
    if (TestDrv[4] != '\0') {
        do {
            ComboBox_GetText(GetDlgItem(hwnd,DRV_BOX),buffer,4);
            if (buffer[0] == TestDrv[4]) {
                Found = TRUE;
            } else {
                if (++i >= NoDrives) {
                    Found = TRUE;
                } else {
                    ComboBox_SetCurSel (Drives,i);
                }
            }
        } while (!Found);
        if (i >= NoDrives) {

            //
            // Couldn't find the drive, exit with a message.
            //

            LogError("Incorrect Drive Letter in command line.",1,0);
            EndDialog(hwnd,0);
            return FALSE;
        }

    } else {
        ComboBox_SetCurSel (Drives,0);
    }

    //
    // Get the sector size for the default selection.
    //
    TestDrv[4] = '\0';
    ComboBox_GetText(GetDlgItem(hwnd,DRV_BOX),buffer, 4);
    strcat (TestDrv,buffer);
    TestDrv[6] = '\0';
    GetSectorSize(&SectorSize,TestDrv);

    //
    // If index is 0, use defaults, otherwise set the test according to
    // the cmdline passes in.
    //

    Button_SetCheck(GetDlgItem(hwnd,TEST_RAD_READ + (index >> 1)), TRUE);
    Button_SetCheck(GetDlgItem(hwnd,VAR_RAD_SEQ + (index & 0x01)),TRUE);

    //
    // Set buffer size.
    //

    if (BufferSize == 0) {

        BufferSize = 65536;
        NumberIOs = FILE_SIZE / BufferSize;

    } else {

        //
        // Verify that buffersize is a multiple of sector size, if not adjust it.
        //

        if (BufferSize % SectorSize) {
            BufferSize &= ~(SectorSize - 1);
        }

        NumberIOs = FILE_SIZE / BufferSize;

        //
        // Cmd line was present and has been used to config. the test. Send a message
        // to the start button to get things rolling.
        //

        SendMessage(hwnd,WM_COMMAND,(BN_CLICKED << 16) | START_BUTTON,(LPARAM)GetDlgItem(hwnd,START_BUTTON));
    }
    _ultoa(BufferSize,buffer,10);
    Static_SetText(GetDlgItem(hwnd,BUFFER_TEXT),buffer);

    return(TRUE);
}