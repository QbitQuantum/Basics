//
// Process Auto Config options:
// #1 search for '/noconfig'
// if not present and csc.cfg exists in EXE dir, inject after env var stuff
//
void ConsoleArgs::ProcessAutoConfig()
{
    bool fFoundNoConfig = false;

    // Scan the argument list for the "/noconfig" options. If present, just kill it and bail.
    for (WStrList * listArgCur = m_listArgs; listArgCur; listArgCur = listArgCur->next)
    {
        // Skip everything except options
        WCHAR * szArg = listArgCur->arg;
        if (szArg == NULL || (szArg[0] != '/' && szArg[0] != '-'))
            continue;

        if (_wcsicmp(szArg + 1, L"noconfig") == 0) {
            listArgCur->arg = NULL;
            VSFree(szArg);
            // We found it, empty it but keep checking in case they specified it twice
            fFoundNoConfig = true;
        }
    }

    if (fFoundNoConfig)
        return;

    // If we got here it means there was no '/noconfig'
    WCHAR szPath[MAX_PATH];
    if (W_IsUnicodeSystem()) {
        if(!GetModuleFileNameW(NULL, szPath, lengthof(szPath)))
            szPath[0] = 0;
    } else {
        CHAR szTemp[MAX_PATH];
        if (!GetModuleFileNameA(NULL, szTemp, lengthof(szTemp)) ||
            !MultiByteToWideChar( AreFileApisANSI() ? CP_ACP : CP_OEMCP,
                0, szTemp, -1, szPath, lengthof(szPath)))
            szPath[0] = 0;
    }
    if (*szPath && PathRemoveFileSpecW(szPath) &&
        PathAppendW(szPath, L"csc.rsp")) {

        if (W_Access( szPath, 4) == 0) { 
            // We know the file exists and that we have read access
            // so add into the list
            size_t cchLen = wcslen(szPath) + 2; // +2 for @ and terminator
            WCHAR * szPathCopy = (WCHAR*)VSAlloc( sizeof(WCHAR) * cchLen);
            if (!szPathCopy || FAILED(StringCchCopyW(szPathCopy + 1, cchLen, szPath))) {
                VSFAIL("The string changed size, or our pointers got messed up");
                m_output->ShowErrorId(FTL_NoMemory, ERROR_FATAL);
                return;
            }
            szPathCopy[0] = L'@';

            WStrList * listArgNew = new WStrList( szPathCopy, m_listArgs);
            if (!listArgNew) {
                VSFree(szPathCopy);
                m_output->ShowErrorId(FTL_NoMemory, ERROR_FATAL);
                return;
            }

            m_listArgs = listArgNew;
        }
    }
}