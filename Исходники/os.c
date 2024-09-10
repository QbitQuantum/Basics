API_EXPORT(int) os_spawnve(int mode, const char *cmdname,
			   const char *const *argv, const char *const *envp)
{
    int n;
    char **aszArgs;
    const char *szArg;
    char *szCmd;
    char *s;
    
    szCmd = _alloca(strlen(cmdname)+1);
    strcpy(szCmd, cmdname);
    for (s = szCmd; *s; ++s) {
        if (*s == '/') {
            *s = '\\';
	}
    }
    
    for (n = 0; argv[n]; ++n)
        ;

    aszArgs = _alloca((n + 1)*sizeof(const char *));

    for (n = 0; szArg = argv[n]; ++n){
        if (strchr(szArg, ' ')) {
            int l = strlen(szArg);

            aszArgs[n] = _alloca(l + 2 + 1);
            aszArgs[n][0] = '"';
            strcpy(&aszArgs[n][1], szArg);
            aszArgs[n][l + 1] = '"';
            aszArgs[n][l + 2] = '\0';
        }
        else {
            aszArgs[n] = (char *)szArg;
        }
    }

    aszArgs[n] = NULL;

    return _spawnve(mode, szCmd, aszArgs, envp);
}