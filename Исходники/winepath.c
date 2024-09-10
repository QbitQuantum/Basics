/*
 * Main function
 */
int wmain(int argc, WCHAR *argv[])
{
    LPSTR (*CDECL wine_get_unix_file_name_ptr)(LPCWSTR) = NULL;
    LPWSTR (*CDECL wine_get_dos_file_name_ptr)(LPCSTR) = NULL;
    WCHAR dos_pathW[MAX_PATH];
    char path[MAX_PATH];
    int outputformats;
    int i;

    outputformats = parse_options(argv);
    if (outputformats == 0)
        outputformats = UNIXFORMAT;

    if (outputformats & UNIXFORMAT) {
        wine_get_unix_file_name_ptr = (void*)
            GetProcAddress(GetModuleHandleA("KERNEL32"),
                           "wine_get_unix_file_name");
        if (wine_get_unix_file_name_ptr == NULL) {
            fprintf(stderr, "%s: cannot get the address of "
                            "'wine_get_unix_file_name'\n", progname);
            exit(3);
        }
    }

    if (outputformats & WINDOWSFORMAT) {
        wine_get_dos_file_name_ptr = (void*)
            GetProcAddress(GetModuleHandleA("KERNEL32"),
                           "wine_get_dos_file_name");
        if (wine_get_dos_file_name_ptr == NULL) {
            fprintf(stderr, "%s: cannot get the address of "
                            "'wine_get_dos_file_name'\n", progname);
            exit(3);
        }
    }

    for (i = 1; argv[i]; i++)
    {
        *path='\0';
        if (outputformats & LONGFORMAT) {
            if (GetLongPathNameW(argv[i], dos_pathW, MAX_PATH))
                WideCharToMultiByte(CP_UNIXCP, 0, dos_pathW, -1, path, MAX_PATH, NULL, NULL);
            printf("%s\n", path);
        }
        if (outputformats & SHORTFORMAT) {
            if (GetShortPathNameW(argv[i], dos_pathW, MAX_PATH))
                WideCharToMultiByte(CP_UNIXCP, 0, dos_pathW, -1, path, MAX_PATH, NULL, NULL);
            printf("%s\n", path);
        }
        if (outputformats & UNIXFORMAT) {
            WCHAR *ntpath, *tail;
            int ntpathlen=lstrlenW(argv[i]);
            ntpath=HeapAlloc(GetProcessHeap(), 0, sizeof(*ntpath)*(ntpathlen+1));
            lstrcpyW(ntpath, argv[i]);
            tail=NULL;
            while (1)
            {
                char *unix_name;
                WCHAR *slash, *c;

                unix_name = wine_get_unix_file_name_ptr(ntpath);
                if (unix_name)
                {
                    if (tail)
                    {
                        WideCharToMultiByte(CP_UNIXCP, 0, tail+1, -1, path, MAX_PATH, NULL, NULL);
                        printf("%s/%s\n", unix_name, path);
                    }
                    else
                    {
                        printf("%s\n", unix_name);
                    }
                    HeapFree( GetProcessHeap(), 0, unix_name );
                    break;
                }

                slash=(tail ? tail : ntpath+ntpathlen);
                while (slash != ntpath && *slash != '/' && *slash != '\\')
                    slash--;
                if (slash == ntpath)
                {
                    /* This is a complete path conversion failure.
                     * It would typically happen if ntpath == "".
                     */
                    printf("\n");
                    break;
                }
                c=slash+1;
                while (*c != '\0' && *c != '*' && *c != '?' &&
                       *c != '<' && *c != '>' && *c != '|' && *c != '"')
                    c++;
                if (*c != '\0')
                {
                    /* If this is not a valid NT path to start with,
                     * then obviously we cannot convert it.
                     */
                    printf("\n");
                    break;
                }
                if (tail)
                    *tail='/';
                tail=slash;
                *tail='\0';
            }
            HeapFree(GetProcessHeap(), 0, ntpath);
        }
        if (outputformats & WINDOWSFORMAT) {
            WCHAR* windows_name;
            char* unix_name;
            DWORD size;

            size=WideCharToMultiByte(CP_UNIXCP, 0, argv[i], -1, NULL, 0, NULL, NULL);
            unix_name=HeapAlloc(GetProcessHeap(), 0, size);
            WideCharToMultiByte(CP_UNIXCP, 0, argv[i], -1, unix_name, size, NULL, NULL);

            if ((windows_name = wine_get_dos_file_name_ptr(unix_name)))
            {
                WideCharToMultiByte(CP_UNIXCP, 0, windows_name, -1, path, MAX_PATH, NULL, NULL);
                printf("%s\n", path);
                HeapFree( GetProcessHeap(), 0, windows_name );
            }
            else printf( "\n" );
            HeapFree( GetProcessHeap(), 0, unix_name );
        }
    }

    exit(0);
}