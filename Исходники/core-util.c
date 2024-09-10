int pa_set_root(HANDLE handle) {
    char library_path[MAX_PATH + sizeof(PULSE_ROOTENV) + 1], *sep;

    strcpy(library_path, PULSE_ROOTENV "=");

    if (!GetModuleFileName(handle, library_path + sizeof(PULSE_ROOTENV), MAX_PATH))
        return 0;

    sep = strrchr(library_path, PA_PATH_SEP_CHAR);
    if (sep)
        *sep = '\0';

    if (_putenv(library_path) < 0)
        return 0;

    return 1;
}