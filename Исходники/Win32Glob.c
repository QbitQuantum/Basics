ArchGlob* archGlob(const char* pattern, int flags)
{
    char *p;
    char oldPath[MAX_PATH];
    char findPath[MAX_PATH];
    const char* filePattern;
    ArchGlob* glob;
    WIN32_FIND_DATAA wfd;
    HANDLE handle;

    strcpy(oldPath, archGetCurrentDirectory());

    while((p = strchr(pattern, '\\')) != NULL) {
        *p = '/';
    }

    filePattern = strrchr(pattern, '/');
    if (filePattern == NULL) {
        filePattern = pattern;
    }
    else {
        char relPath[MAX_PATH];
        strcpy(relPath, pattern);
        relPath[filePattern - pattern] = '\0';
        pattern = filePattern + 1;
        if( relPath[0] == '/' || relPath[1] == ':' ) {
            // absolute path already
            strcpy(oldPath, relPath);
        }else{
            strcat(oldPath, "/");
            strcat(oldPath, relPath);
        }
    }

    strcpy(findPath, oldPath);
    strcat(findPath, "/");
    strcat(findPath, pattern);
    handle = FindFirstFileA(findPath, &wfd);
    if (handle == INVALID_HANDLE_VALUE) {
        return NULL;
    }

    glob = (ArchGlob*)calloc(1, sizeof(ArchGlob));

    do {
        char *fullpath = (char*)malloc(MAX_PATH);
        DWORD fa;
        if (0 == strcmp(wfd.cFileName, ".") || 0 == strcmp(wfd.cFileName, "..")) {
            continue;
        }
        strcpy(fullpath, oldPath);
        strcat(fullpath, "/");
        strcat(fullpath, wfd.cFileName);
        fa = GetFileAttributesA(fullpath);
        if (((flags & ARCH_GLOB_DIRS) && (fa & FILE_ATTRIBUTE_DIRECTORY) != 0) ||
            ((flags & ARCH_GLOB_FILES) && (fa & FILE_ATTRIBUTE_DIRECTORY) == 0))
        {
            glob->count++;
            glob->pathVector = realloc(glob->pathVector, sizeof(char*) * glob->count);
            glob->pathVector[glob->count - 1] = fullpath;
        }else{
            free(fullpath);
        }
    } while (FindNextFileA(handle, &wfd));

    FindClose(handle);

    return glob;
}