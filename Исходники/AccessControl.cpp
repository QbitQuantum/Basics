PUBLIC_FUNCTION_END

PUBLIC_FUNCTION(IsUserTheAdministrator)
{
  TCHAR * name = (TCHAR *)LocalAlloc(LPTR, string_size*sizeof(TCHAR));
  TCHAR * sidstr = NULL;
  DWORD dwName = string_size;
  PSID pSid = NULL;
  DWORD sidLen = 0;
  DWORD domLen = 0;
  TCHAR * domain = NULL;
  SID_NAME_USE use;

  if (popstring(name))
    ABORT("Missing user name plug-in parameter.");

  if ((LookupAccountName(NULL, name, 
      NULL, &sidLen, NULL, &domLen, &use) ||
      ERROR_INSUFFICIENT_BUFFER == GetLastError()) &&
      NULL != (domain = (TCHAR *)LocalAlloc(LPTR, domLen*sizeof(TCHAR))) &&
    NULL != (pSid = (PSID)LocalAlloc(LPTR, sidLen)))
  {
    if (!LookupAccountName(NULL, name, 
      pSid, &sidLen, domain, &domLen, &use))
    {
      LocalFree(pSid);
      pSid = NULL;
      ABORT_d("Couldn't lookup current user name. Error code %d: ", GetLastError());
    }

    int uid;
    if (500 == (uid = *GetSidSubAuthority(pSid, *GetSidSubAuthorityCount(pSid) - 1)))
      pushstring(_T("yes"));
    else
      pushstring(_T("no"));

    sidstr = (TCHAR *)LocalAlloc(LPTR, string_size*sizeof(TCHAR));
    ConvertSidToStringSid(pSid, &sidstr);

    int len = lstrlen(sidstr);
    TCHAR * strend = sidstr + len - 1;
    TCHAR * strstart = sidstr;
    while (*strend != '-' && len >= 0)
    {
      strend--;
      len--;
    }
    *strend = '\0';
    lstrcat(strend, _T("-500"));

    pushstring(sidstr);
  }

cleanup:
  if (NULL != sidstr)
    LocalFree(sidstr);
  LocalFree(name);
}