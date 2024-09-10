//windows : find main DLL and extract path
//linux and macos : scilab script fill SCI env variable
char* computeTMPDIR()
{
#ifdef _MSC_VER
    wchar_t wcTmpDirDefault[PATH_MAX];

    if (!GetTempPathW(PATH_MAX, wcTmpDirDefault))
    {
        MessageBoxA(NULL, _("Cannot find Windows temporary directory (1)."), _("Error"), MB_ICONERROR);
        exit(1);
    }
    else
    {
        wchar_t wctmp_dir[PATH_MAX + FILENAME_MAX + 1];
        static wchar_t bufenv[PATH_MAX + 16];
        char *TmpDir = NULL;
        os_swprintf(wctmp_dir, PATH_MAX + FILENAME_MAX + 1, L"%lsSCI_TMP_%d_", wcTmpDirDefault, _getpid());
        if (CreateDirectoryW(wctmp_dir, NULL) == FALSE)
        {
            DWORD attribs = GetFileAttributesW(wctmp_dir);
            if (attribs & FILE_ATTRIBUTE_DIRECTORY)
            {
                /* Repertoire existant */
            }
            else
            {
#ifdef _DEBUG
                {
                    char MsgErr[1024];
                    wsprintfA(MsgErr, _("Impossible to create : %s"), wctmp_dir);
                    MessageBoxA(NULL, MsgErr, _("Error"), MB_ICONERROR);
                    exit(1);
                }
#else
                {
                    GetTempPathW(PATH_MAX, wcTmpDirDefault);
                    wcscpy(wctmp_dir, wcTmpDirDefault);
                    wctmp_dir[wcslen(wctmp_dir) - 1] = '\0'; /* Remove last \ */
                }
#endif
            }
        }

        os_swprintf(bufenv, PATH_MAX + 16, L"TMPDIR=%ls", wctmp_dir);
        _wputenv(bufenv);

        TmpDir = wide_string_to_UTF8(wctmp_dir);
        if (TmpDir)
        {
            return TmpDir;
        }
        else
        {
            return NULL;
        }
    }
    return NULL;
#else
    char *tmpdir;

    char* env_dir = (char*)MALLOC(sizeof(char) * (PATH_MAX + 16));
    /* If the env variable TMPDIR is set, honor this preference */
    tmpdir = getenv("TMPDIR");
    if (tmpdir != NULL && strlen(tmpdir) < (PATH_MAX) && strstr(tmpdir, "SCI_TMP_") == NULL)
    {
        strcpy(env_dir, tmpdir);
    }
    else
    {
        strcpy(env_dir, "/tmp");
    }

    /* XXXXXX will be randomized by mkdtemp */
    char *env_dir_strdup = os_strdup(env_dir); /* Copy to avoid to have the same buffer as input and output for sprintf */
    sprintf(env_dir, "%s/SCI_TMP_%d_XXXXXX", env_dir_strdup, (int)getpid());
    free(env_dir_strdup);

    if (mkdtemp(env_dir) == NULL)
    {
        fprintf(stderr, _("Error: Could not create %s: %s\n"), env_dir, strerror(errno));
    }

    setenvc("TMPDIR", env_dir);
    return env_dir;
#endif
}