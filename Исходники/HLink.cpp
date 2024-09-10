HINSTANCE CHLink::GotoURL(LPCTSTR url, int showcmd)
{
    TCHAR key[MAX_PATH + MAX_PATH];

    HINSTANCE result = ShellExecute(NULL, _T("open"), url, NULL,NULL, showcmd);

    if ((UINT)result <= HINSTANCE_ERROR) 
    {
        if (GetRegKey(HKEY_CLASSES_ROOT, _T(".htm"), key) == ERROR_SUCCESS) 
        {
            lstrcat(key, _T("\shell\open\command"));
            if (GetRegKey(HKEY_CLASSES_ROOT,key,key) == ERROR_SUCCESS)
            {

                TCHAR *pos;

                pos = _tcsstr(key, _T("%1"));

                if (pos == NULL)
                {
                    pos = strstr(key, _T("%1"));

                    if (pos == NULL)
                        pos = key+lstrlen(key)-1;
                    else
                        *pos = '0';
                }
                else
                    *pos = '0'; // Remove the parameter

                lstrcat(pos, _T(" "));
                lstrcat(pos, url);
                result = (HINSTANCE) WinExec(key,showcmd);
            }
        }
    }