/* Enumerates the subkeys of <hKey>/Software/mimerun/rules and looks for a rule that matches the values
 * from <mres>, <lpfile> and <einfo>->lpParameters
 * Once a matching rule is found, its handler is executed and the function returns without looking checking
 * any other rules.
 */
int handle_key (wchar_t *logfile, HKEY hKey, MimeResults *mres, LPSHELLEXECUTEINFOW einfo, wchar_t *lpfile, wchar_t *lpdir)
{
  wchar_t *handle_val = NULL;
  HKEY rules;
  wchar_t *matchstring = NULL;
  wchar_t **allkeys = NULL;
  wchar_t *handler = NULL;
  DWORD allkeys_len, maxkey_len;
  LONG res = 0;
  int ret = -4;
  DWORD matchlen = 0;
  DWORD i;
  DWORD len = 0;
  BOOL sorted;

  logtofilew (logfile, L">handle_key\n");

  matchlen = _scwprintf (MATCHSTRING_FORMAT_ARGS(mres, einfo, lpfile));
  if (matchlen <= 0)
  {
    logtofilew (logfile, L"match string length %d <= 0\n", matchlen);
    ret = -1;
    goto end;
  }
  res = RegOpenKeyExW (hKey, L"Software\\mimerun\\rules", 0, KEY_QUERY_VALUE | KEY_ENUMERATE_SUB_KEYS | KEY_WOW64_32KEY, &rules);
  if (res != ERROR_SUCCESS)
  {
    logtofilew (logfile, L"Failed to open %08X\\Software\\mimerun\\rules\n", hKey);
    ret = -2;
    goto end;
  }
  res = RegQueryInfoKeyW (rules, NULL, NULL, NULL, &allkeys_len, &maxkey_len, NULL, NULL, NULL, NULL, NULL, NULL);
  if (res != ERROR_SUCCESS || (allkeys_len <= 0 || maxkey_len <= 0))
  {
    logtofilew (logfile, L"Failed to query keys from %08X\\Software\\mimerun\\rules\n", hKey);
    ret = -3;
    goto end;
  }
  allkeys = (wchar_t **) malloc (sizeof (wchar_t *) * (allkeys_len + 1));
  if (allkeys == NULL)
  {
    logtofilew (logfile, L"Failed to allocate %d bytes for rule keys\n", sizeof (wchar_t *) * (allkeys_len + 1));
    ret = -4;
    goto end;
  }
  memset (allkeys, 0, sizeof (wchar_t *) * (allkeys_len + 1));
  for (i = 0; i < allkeys_len; i++)
  {
    allkeys[i] = (wchar_t *) malloc (sizeof (wchar_t) * (maxkey_len + 1));
    if (allkeys[i] == NULL)
    {
      logtofilew (logfile, L"Failed to allocate %d bytes for one of the rule keys\n", sizeof (wchar_t) * (maxkey_len + 1));
      ret = -5;
      goto end;
    }
  }
  allkeys[allkeys_len] = NULL;
  for (i = 0; res == ERROR_SUCCESS; i++)
  {
    len = maxkey_len + 1;
    res = RegEnumKeyExW (rules, i, allkeys[i], &len, NULL, NULL, NULL, NULL);
  }
  logtofilew (logfile, L"Enumerated %d rules\n", i - 1);
  sorted = FALSE;
  while (!sorted)
  {
    sorted = TRUE;
    for (i = 1; i < allkeys_len; i++)
    {
      if (wcscmp (allkeys[i - 1], allkeys[i]) > 0)
      {
        sorted = FALSE;
        wchar_t *tmp;
        tmp = allkeys[i - 1];
        allkeys[i - 1] = allkeys[i];
        allkeys[i] = tmp;
      }
    }
  }
  matchstring = (wchar_t *) malloc (sizeof (wchar_t) * (matchlen + 1));
  swprintf (matchstring, MATCHSTRING_FORMAT_ARGS(mres, einfo, lpfile));
  logtofilew (logfile, L"Matchstring: %s\n", matchstring);
  for (i = 0; i < allkeys_len; i++)
  {
    if ((ret = match_rule (logfile, rules, allkeys[i], matchstring)) == 0)
    {
      handler = NULL;
      DWORD executable = 0;
      DWORD fix_redir = 0;
      DWORD shebang_flags = 0;
      char shebang_interp[MAX_PATH + 1];
      char *shebang_args = NULL;
      if (get_dword_key (rules, allkeys[i], L"executable", &executable, KEY_WOW64_32KEY) != 0)
        executable = 1;
      if (get_dword_key (rules, allkeys[i], L"fix_wow64_redirection", &fix_redir, KEY_WOW64_32KEY) != 0)
        fix_redir = 0;
      if (get_dword_key (rules, allkeys[i], L"shebang", &shebang_flags, KEY_WOW64_32KEY) != 0)
        shebang_flags = 0;
      logtofilew (logfile, L"Found a handler, execuable is %d, fix_wow64_redirection is %d, shebang is %d\n", executable, fix_redir, shebang_flags);

      if (shebang_flags & MIMERUN_SHEBANG_LOOKFORIT)
      {
        logtofilew (logfile, L"Trying to get shebang... ");
        if (get_shebang (lpfile, shebang_interp, &shebang_args) < 0)
        {
          shebang_flags = 0;
          logtofilew (logfile, L"FAILURE\n");
        }
        else
        {
          logtofilew (logfile, L"%S %S\n", shebang_interp, shebang_args ? shebang_args : "");
        }
      }
      if (shebang_flags & MIMERUN_SHEBANG_LOOKFORIT && shebang_flags & MIMERUN_SHEBANG_TRYITFIRST)
      {
        wchar_t *tmp = dup_wprintf (NULL, L"%S%s%S %s", shebang_interp, shebang_args == NULL ? L"" : L" ", shebang_args == NULL ? "" : shebang_args, lpfile);
        if (tmp != NULL)
        {
          ret = run_handler (logfile, tmp, mres, einfo, lpfile, lpdir, 1, fix_redir);
          free (tmp);
          free (shebang_args);
          if (shebang_flags & MIMERUN_SHEBANG_BAILONIT || ret == 0)
          {
            logtofilew (logfile, L"Bailing out after shebang\n", ret);
            goto end;
          }
          else
            einfo->hInstApp = (HINSTANCE) 33;
        }
      }
      if (get_sz_key (rules, allkeys[i], L"handler", &handler, KEY_WOW64_32KEY) == 0 && handler != NULL)
      {
        ret = run_handler (logfile, handler, mres, einfo, lpfile, lpdir, executable, fix_redir);
        free (handler);
        handler = NULL;
        if (ret == 0)
        {
          logtofilew (logfile, L"Handled, returning\n");
          goto end;
        }
      }
      else
      {
        logtofilew (logfile, L"Failed to get handler value\n");
      }
      if (shebang_flags & MIMERUN_SHEBANG_LOOKFORIT && ~shebang_flags & MIMERUN_SHEBANG_TRYITFIRST)
      {
        wchar_t *tmp = dup_wprintf (NULL, L"%S%s%S %s", shebang_interp, shebang_args == NULL ? L"" : L" ", shebang_args == NULL ? "" : shebang_args, lpfile);
        if (tmp != NULL)
        {
          ret = run_handler (logfile, tmp, mres, einfo, lpfile, lpdir, 1, fix_redir);
          free (tmp);
          free (shebang_args);
          if (shebang_flags & MIMERUN_SHEBANG_BAILONIT || ret == 0)
          {
            logtofilew (logfile, L"Bailing out after shebang\n");
            goto end;
          }
        }
      }
      ret = -4;
    }
  }
end:
  logtofilew (logfile, L"Cleaning up handle_key\n");
  if (matchstring != NULL)
    free (matchstring);
  if (allkeys != NULL)
  {
    for (i = 0; allkeys[i] != NULL; i++)
      free (allkeys[i]);
    free (allkeys);
  }
  if (rules != NULL)
    RegCloseKey (rules);

  logtofilew (logfile, L"<handle_key %d\n", ret);
  return ret;
}