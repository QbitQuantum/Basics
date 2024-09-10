/* {{{ MADB_SaveDSN */
my_bool MADB_SaveDSN(MADB_Dsn *Dsn)
{
  int i= 1;
  char Value[32];
  my_bool ret;
  DWORD ErrNum;

  if (!SQLValidDSN(Dsn->DSNName))
  {
    strcpy_s(Dsn->ErrorMsg, SQL_MAX_MESSAGE_LENGTH, "Invalid Data Source Name");
    return FALSE;
  }

  if (!SQLRemoveDSNFromIni(Dsn->DSNName))
  {
    SQLInstallerError(1,&ErrNum, Dsn->ErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL);
    return FALSE;
  }
  if (!SQLWriteDSNToIni(Dsn->DSNName, Dsn->Driver))
  {
    SQLInstallerError(1,&ErrNum, Dsn->ErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL);
    return FALSE;
  }

  while(DsnKeys[i].DsnKey)
  {
    ret= TRUE;
    switch(DsnKeys[i].Type){
    case DSN_TYPE_BOOL:
        ret= SQLWritePrivateProfileString(Dsn->DSNName, DsnKeys[i].DsnKey, 
        *(my_bool *)((char *)Dsn + DsnKeys[i].DsnOffset) ? "1" : "0", "ODBC.INI");
      break;
    case DSN_TYPE_INT:
      {
        my_snprintf(Value ,32, "%d", *(int *)((char *)Dsn + DsnKeys[i].DsnOffset));
        ret= SQLWritePrivateProfileString(Dsn->DSNName, DsnKeys[i].DsnKey, Value, "ODBC.INI");
      }
      break;
    case DSN_TYPE_STRING:
    case DSN_TYPE_COMBO:
      {
        char *Val= *(char **)((char *)Dsn + DsnKeys[i].DsnOffset);
        if (Val && Val[0])
          ret= SQLWritePrivateProfileString(Dsn->DSNName, DsnKeys[i].DsnKey, Val, "ODBC.INI");
      }
      break;
    }
    if (!ret)
    {
      SQLInstallerError(1,&ErrNum, Dsn->ErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL);
      return FALSE;
    }
    i++;
  }
  /* Save Options */
  my_snprintf(Value ,32, "%d", Dsn->Options);
  if (!(ret= SQLWritePrivateProfileString(Dsn->DSNName, "OPTIONS", Value, "ODBC.INI")))
  {
    SQLInstallerError(1,&ErrNum, Dsn->ErrorMsg, SQL_MAX_MESSAGE_LENGTH, NULL);
    return FALSE;
  }
  return TRUE;
}