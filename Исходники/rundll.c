void
WINAPI
RunDLL_SaveImageFile(HWND hWnd,
		     HINSTANCE hInst,
		     LPSTR lpszCmdLine,
		     int nCmdShow)
{
  WCHAR file_name[MAX_PATH + 1] = L"";
  WCHAR mount_point[] = L"\\\\.\\ :";
  HANDLE hDev;
  BOOL bIsCdRomType = FALSE;

  switch (GetDriveTypeA(lpszCmdLine))
    {
    case DRIVE_CDROM:
      bIsCdRomType = TRUE;
      break;

    case DRIVE_REMOTE:
      MsgBoxPrintF(hWnd, MB_ICONSTOP, L"ImDisk Virtual Disk Driver",
		   L"Unsupported drive type: '%1!hs!'", lpszCmdLine);
      return;
    }

  // If user right-clicked in Windows Explorer the drive we are dismounting is
  // the current directory in this process. Change to Windows directory.
  if (GetWindowsDirectory(file_name, sizeof(file_name) / sizeof(*file_name)))
    {
      file_name[(sizeof(file_name) / sizeof(*file_name)) - 1] = 0;
      SetCurrentDirectory(file_name);
    }
  file_name[0] = 0;

  if (strlen(lpszCmdLine) < 2 ? TRUE : lpszCmdLine[1] != L':')
    {
      MsgBoxPrintF(hWnd, MB_ICONSTOP, L"ImDisk Virtual Disk Driver",
		   L"Unsupported mount point: '%1!hs!'", lpszCmdLine);
      return;
    }

  mount_point[4] = lpszCmdLine[0];

  hDev = CreateFile(mount_point,
		    GENERIC_READ,
		    FILE_SHARE_READ | FILE_SHARE_WRITE,
		    NULL,
		    OPEN_EXISTING,
		    FILE_FLAG_NO_BUFFERING | FILE_FLAG_SEQUENTIAL_SCAN,
		    NULL);

  if (hDev == INVALID_HANDLE_VALUE)
    {
      MsgBoxLastError(hWnd, L"Cannot open drive for direct access:");
      return;
    }

  ImDiskSaveImageFileInteractive(hDev, hWnd, 0, bIsCdRomType);

  CloseHandle(hDev);
}