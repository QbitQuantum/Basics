my_bool DSNDialog(HWND hwndParent,
                  WORD fRequest,
                  LPCSTR lpszDriver,
                  LPCSTR lpszAttributes,
                  MADB_Dsn *Dsn)
{
  MSG msg;
  BOOL ret;
  char *DsnName= NULL;
  my_bool DsnExists= FALSE;

  if (Dsn->isPrompt < 0 || Dsn->isPrompt > MAODBC_PROMPT_REQUIRED)
  {
    Dsn->isPrompt= MAODBC_CONFIG;
  }

  EffectiveDisabledPages=     DisabledPages[Dsn->isPrompt];
  EffectiveDisabledControls=  DisabledControls[Dsn->isPrompt];

  if (lpszAttributes)
    DsnName= strchr((char *)lpszAttributes, '=');
  
  if (lpszDriver)
    MADB_DriverGet((char *)lpszDriver);

  if (DsnName)
  {
    ++DsnName;
    /* In case of prompting we are supposed to show dialog even DSN name is incorrect */
    if (!Dsn->isPrompt && !SQLValidDSN(DsnName))
    {
      if (hwndParent)
        MessageBox(hwndParent, "Validation of data source name failed", "Error", MB_ICONERROR | MB_OK);
      return FALSE;
    }
  }

  if (!DsnName && Dsn && Dsn->DSNName)
  {
    DsnName= Dsn->DSNName;
  }
  else if (DsnName && Dsn)
  {
    /* Need to free current value in Dsn->DSNName */
    MADB_SUBSTITUTE(Dsn->DSNName, _strdup(DsnName));
  }

  /* Even if DsnName invalid(in case of prompt) - we should not have problem */
  DsnExists= MADB_DSN_Exists(DsnName);
 
  InitCommonControls();

  if (lpszDriver)
    Dsn->Driver= _strdup(lpszDriver);

  SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &Environment);
  SQLSetEnvAttr(Environment, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0);

  if (fRequest == ODBC_ADD_DSN)
  {
    if (DsnExists && hwndParent)
    {
      if (MessageBox(hwndParent, "Data source name already exists, do you want to replace it?", 
                      "Question", MB_ICONQUESTION | MB_YESNO) != IDYES)
        return FALSE;
    }
    Dsn->IsTcpIp= 1;
  }
  else
  {
    /* i.e. not a prompt */
    if (Dsn->isPrompt == MAODBC_CONFIG)
    {
      if (!DsnExists)
      {
        MessageBox(0, "Data source name not found", "Error", MB_ICONERROR | MB_OK);
        return FALSE;
      }
      else if (!MADB_ReadDSN(Dsn, (char *)lpszAttributes, TRUE))
      {
        SQLPostInstallerError(ODBC_ERROR_INVALID_DSN, Dsn->ErrorMsg);
        return FALSE;
      }
    }
  }

  notCanceled= TRUE;
  hwndMain= CreateDialogParam(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), 0, DialogProc, 0);
  SetWindowLongPtr(hwndMain, DWLP_USER, (LONG)Dsn);

  /* Setting first not disabled page */
  CurrentPage= -1;
  SetPage(hwndMain, 1);

  Edit_SetReadOnly(GetDlgItem(hwndTab[0], txtDsnName), 
                   (hwndParent && DsnName && fRequest == ODBC_ADD_DSN) ? TRUE : FALSE);

  SetDialogFields();
  CenterWindow(hwndMain);
  ShowWindow(hwndMain, SW_SHOW);

  while((ret = GetMessage(&msg, 0, 0, 0)) != 0) {
    if(ret == -1)
      break;

    if(!IsDialogMessage(hwndTab[CurrentPage], &msg)) {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
  }

  SQLFreeHandle(SQL_HANDLE_ENV, Environment);

  return notCanceled;
}