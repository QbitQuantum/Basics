BOOL DisplayPrinterDriverInfo (HWND hwnd)
{
  HANDLE        hPrinter;
  DWORD         dwBytesNeeded;
  DRIVER_INFO_1 *pDriverInfo1;
  DRIVER_INFO_2 *pDriverInfo2;
  char          buf[BUFSIZE];
  char          pEnvironment[BUFSIZE] = "";
  BOOL          bReturn = TRUE;

  //
  // open selected printer & alloc buffers & get sundry info, close printer
  //

  OpenPrinter (gszDeviceName, &hPrinter, NULL);

  if (!hPrinter)
  {
    char buf[BUFSIZE];

    _snprintf_s (buf, BUFSIZE, _TRUNCATE, GetStringRes(IDS_FMT_OPNPRTFAIL), gszDeviceName);
    ErrMsgBox ((LPCSTR) buf, ERR_MOD_NAME);
    bReturn  = FALSE;
    goto display_prt_drv_info_done1;
  }

  GetPrinterDriver (hPrinter, pEnvironment, 1, NULL, 0, &dwBytesNeeded);

  //
  // simple error checking, if these work assume rest will too
  //

  if (!(pDriverInfo1 = (DRIVER_INFO_1 *) LocalAlloc (LPTR, dwBytesNeeded)))
  {
    ErrMsgBox (GetStringRes(IDS_LALLOCFAIL), ERR_MOD_NAME);
    bReturn = FALSE;
    goto display_prt_drv_info_done1;
  }

  if (!GetPrinterDriver (hPrinter, pEnvironment, 1, (LPBYTE) pDriverInfo1,
                         dwBytesNeeded, &dwBytesNeeded))
  {
    ErrMsgBox (GetStringRes(IDS_GETPRTDRVFAIL), ERR_MOD_NAME);
    bReturn = FALSE;
    goto display_prt_drv_info_done2;
  }

  GetPrinterDriver (hPrinter, pEnvironment, 2, NULL, 0, &dwBytesNeeded);
  pDriverInfo2 = (DRIVER_INFO_2 *) LocalAlloc (LPTR, dwBytesNeeded);
  GetPrinterDriver (hPrinter, pEnvironment, 2, (LPBYTE) pDriverInfo2,
                    dwBytesNeeded, &dwBytesNeeded);

  ClosePrinter (hPrinter);

  //
  // shove info in listbox
  //

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[0]) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[1], pDriverInfo1->pName) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[2]) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[3], pDriverInfo2->cVersion) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[4], pDriverInfo2->pName) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[5], pDriverInfo2->pEnvironment) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[6], pDriverInfo2->pDriverPath) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[7], pDriverInfo2->pDataFile) > 0 )
	outstr();

  if ( _snprintf_s (buf, BUFSIZE, _TRUNCATE, gaDrvInfo[8], pDriverInfo2->pConfigFile) > 0 )
	outstr();

  LocalFree (LocalHandle (pDriverInfo2));

display_prt_drv_info_done2:

  LocalFree (LocalHandle (pDriverInfo1));

display_prt_drv_info_done1:

  return bReturn;
}