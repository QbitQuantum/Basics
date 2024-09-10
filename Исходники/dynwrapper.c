void setPath(void) {
    LPTSTR *dir;
    LPTSTR path;
    int n;
    int len = 0;
    LPTSTR exePath, s;

    exePath = getModuleFileName();
    for(s = exePath; *s != '\0'; s++) {
        if (*s == '\\') {
            *s = '/';
        }
    }
    s = StrRChr(exePath, NULL, '/');
    if (s == NULL) {
        die("No directory separator in executable path: %s", exePath);
    }
    s[0] = '\0';
    n = s - exePath;

    for (dir = path_dirs; *dir != NULL; dir++) {
        len += n + lstrlen(*dir) + 1/* semicolon */;
    }
    len++; // NUL

    path = malloc(len);
    if (path == NULL) {
        die("Mallocing %d for PATH failed", len);
    }
    s = path;
    for (dir = path_dirs; *dir != NULL; dir++) {
        StrCpy(s, exePath);
        s += n;
        StrCpy(s, *dir);
        s += lstrlen(*dir);
        s[0] = ';';
        s++;
    }
    s[0] = '\0';
    free(exePath);

    if (! SetEnvironmentVariable(TEXT("PATH"), path)) {
        printf("SetEnvironmentVariable failed (%d)\n", GetLastError());
    }
    free(path);
}