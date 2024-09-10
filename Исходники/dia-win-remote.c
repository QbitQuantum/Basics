/* Find path to Dia in the registry and then launch it with the
   passed command line.*/
int LaunchDia(int nArgs, LPWSTR *szArglist, int start_at)
{
    HKEY hRegData;
    char szAppPath[_MAX_PATH];   /* path to exe */
	char szDiaKey[255*2]; /* just incase * 2 */
	char *uri_args = NULL;
	char *uri_args_cpy = NULL;
	char *filename_utf8 = NULL;
	char *filename_uri = NULL;
    DWORD dwSize;
    DWORD dwType = 0;
    DWORD dwDisp;
    int i, iRetCode=-1;
	GError *error = NULL;

    /* Read path to Dia */
    sprintf(szDiaKey, "Software\\Microsoft\\Windows\\CurrentVersion\\App Paths\\%s", 
            (gUseRegVal) ? gszDiaExe : __argv[1]);

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, szDiaKey, 0, KEY_READ, &hRegData) == ERROR_SUCCESS)
    {
        dwSize = sizeof(szAppPath);
        if (RegQueryValueEx(hRegData, "", 0, &dwType,
                            (PBYTE)szAppPath, (LPDWORD)&dwSize) == ERROR_SUCCESS)
        {
            /**
	     * Extract the path from where diaw.exe was launched. Could
             * use the path in registry, but you never know where in the
             * string it will be.
	     */
            char szPath[_MAX_PATH]={0};
            char *pEnd = strrchr(szAppPath, '\\');

            /* Could we find last slash? */
            if (pEnd != NULL)
            {
                int len = pEnd-szAppPath;
                
                /* just incase */
                if (len > 0 && len < _MAX_PATH)
                {
                    strncpy(szPath, szAppPath, len);
                }
            }
          
			/**
			 * Create commandline with URIs
			 */
			uri_args_cpy = g_strdup("");
			for(i = start_at; i<nArgs; i++)
			{
				if((0 == wcsncmp(szArglist[i], L"--", 2)) && !PathFileExistsW(szArglist[i]))
				{
					uri_args = g_strdup_printf("%s %s", uri_args_cpy, __argv[i]);
					g_free(uri_args_cpy);
					uri_args_cpy = uri_args;
				}
				else
				{
					filename_utf8 = g_utf16_to_utf8(szArglist[i], -1, NULL, NULL, &error);
					if(error) {
						MessageBox(NULL, "Error converting to UTF-8!", gszVersion, MB_ICONEXCLAMATION);
						g_free(filename_utf8);
						g_free(uri_args);
						g_free(uri_args_cpy);
						return -1;
					}
					
					filename_uri = g_filename_to_uri(filename_utf8, NULL, &error);
					if(error) {
						MessageBox(NULL, "Error converting to URI!", gszVersion, MB_ICONEXCLAMATION);
						g_free(filename_uri);
						g_free(uri_args);
						g_free(uri_args_cpy);					
						g_free(filename_utf8);
						return -1;
					}
					else
					{
						uri_args = g_strdup_printf("%s %s", uri_args_cpy, filename_uri);
						g_free(uri_args_cpy);
						g_free(filename_uri);
						uri_args_cpy = uri_args;
					}
					g_free(filename_utf8);
				}
			}
            /**
	     * Try launching Dia with the passed params.
	     */
            if (ShellExecute(NULL, "open", szAppPath,
                             uri_args, szPath, SW_SHOW) <= (HINSTANCE)32)
            {
                MessageBox(NULL, "Failed to launch Dia!", gszVersion, MB_ICONEXCLAMATION);
            }
            else
            {
                iRetCode = 0;
            }
			g_free(uri_args);
			g_free(uri_args_cpy);
        }
    }
    else
    {
        MessageBox(NULL, "Error reading registry!", gszVersion, MB_ICONSTOP);
    }

    /* close the key */
    RegCloseKey(hRegData);

    return iRetCode;
}