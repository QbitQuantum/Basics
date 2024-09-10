const gchar *
g_getenv (const gchar *variable)
{
  GQuark quark;
  gchar *value;
  wchar_t dummy[2], *wname, *wvalue;
  int len;

  g_return_val_if_fail (variable != NULL, NULL);
  g_return_val_if_fail (g_utf8_validate (variable, -1, NULL), NULL);

  /* On Windows NT, it is relatively typical that environment
   * variables contain references to other environment variables. If
   * so, use ExpandEnvironmentStrings(). (In an ideal world, such
   * environment variables would be stored in the Registry as
   * REG_EXPAND_SZ type values, and would then get automatically
   * expanded before a program sees them. But there is broken software
   * that stores environment variables as REG_SZ values even if they
   * contain references to other environment variables.)
   */

  wname = g_utf8_to_utf16 (variable, -1, NULL, NULL, NULL);

  len = GetEnvironmentVariableW (wname, dummy, 2);

  if (len == 0)
    {
      g_free (wname);
      return NULL;
    }
  else if (len == 1)
    len = 2;

  wvalue = g_new (wchar_t, len);

  if (GetEnvironmentVariableW (wname, wvalue, len) != len - 1)
    {
      g_free (wname);
      g_free (wvalue);
      return NULL;
    }

  if (wcschr (wvalue, L'%') != NULL)
    {
      wchar_t *tem = wvalue;

      len = ExpandEnvironmentStringsW (wvalue, dummy, 2);

      if (len > 0)
        {
          wvalue = g_new (wchar_t, len);

          if (ExpandEnvironmentStringsW (tem, wvalue, len) != len)
            {
              g_free (wvalue);
              wvalue = tem;
            }
          else
            g_free (tem);
        }