__integer __INTERNAL_FUNC__ PrintDbgInfo_DebugerWriteLine(__char *pInfo) {
    __char szText[__PRINTDBGINFO_WRITECONSOLE_BUFFER_SIZE__] = {0};
    __integer iWritten = 0;
    __logic_strcpy__(szText, pInfo);
    __logic_strcat__(szText, "\n");
    if (g_hWriteConsole) {
        if (!WriteConsoleA(g_hWriteConsole, szText, __logic_strlen__(szText), &iWritten, NULL))
            return 0;
        return iWritten;
    }
    return 0;
}