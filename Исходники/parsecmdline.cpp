UINT
WINAPI
SHExplorerParseCmdLine(ExplorerCommandLineParseResults * pInfo)
{
    WCHAR   strField[MAX_PATH];
    WCHAR   strDir[MAX_PATH];

    PCWSTR strCmdLine = GetCommandLineW();
    PCWSTR strFieldArray = PathGetArgsW(strCmdLine);

    if (!*strFieldArray)
    {
        pInfo->dwFlags = 9;
        pInfo->pidlPath = _GetDocumentsPidl();
        if (!pInfo->pidlPath)
        {
            GetWindowsDirectoryW(strDir, MAX_PATH);
            PathStripToRootW(strDir);
            pInfo->pidlPath = ILCreateFromPathW(strDir);
        }
        return (LONG) (pInfo->pidlPath);
    }

    PCWSTR strNextArg = _FindFirstField(strFieldArray);

    BOOL hasNext = TRUE;

    hasNext = _ReadNextArg(&strNextArg, strField, _countof(strField));
    while (TRUE)
    {
        // Basic flags-only params first
        if (!StrCmpIW(strField, L"/N"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_N | SH_EXPLORER_CMDLINE_FLAG_ONE;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"/S"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_S;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"/E"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_E;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"/SELECT"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_SELECT;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"/NOUI"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_NOUI;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"-embedding"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_EMBED;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"/SEPARATE"))
        {
            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_SEPARATE;
            TRACE("CmdLine Parser: Parsed %S flag. dwFlags=%08lx\n", strField, pInfo->dwFlags);
        }
        else if (!StrCmpIW(strField, L"/INPROC"))
        {
            // No idea what Inproc is supposed to do, but it gets a GUID, and parses it.

            TRACE("CmdLine Parser: Found %S flag\n", strField);

            if (!hasNext)
                return FALSE;

            hasNext = _ReadNextArg(&strNextArg, strField, _countof(strField));

            if (!GUIDFromStringW(strField, &(pInfo->guidInproc)))
                return FALSE;

            pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_INPROC;

            TRACE("CmdLine Parser: Parsed /INPROC flag. dwFlags=%08lx, guidInproc=%S\n", pInfo->dwFlags, strField);
        }
        else if (!StrCmpIW(strField, L"/ROOT"))
        {
            LPITEMIDLIST pidlRoot = NULL;

            // The window should be rooted

            TRACE("CmdLine Parser: Found %S flag\n", strField);

            if (!pInfo->pidlPath)
                return FALSE;

            if (!hasNext)
                return FALSE;

            hasNext = _ReadNextArg(&strNextArg, strField, _countof(strField));

            // Root may be a pidl
            if (!StrCmpIW(strField, L"/IDLIST"))
            {
                if (hasNext)
                {
                    hasNext = _ReadNextArg(&strNextArg, strField, _countof(strField));
                }
                pidlRoot = _ILReadFromSharedMemory(strField);
            }
            else
            {
                // Or just a path string
                _ParsePathToPidl(strField, &pidlRoot);
            }

            pInfo->pidlRoot = pidlRoot;

            // The root defaults to the desktop
            if (!pidlRoot)
            {
                if (FAILED(SHGetSpecialFolderLocation(0, CSIDL_DESKTOP, &(pInfo->pidlRoot))))
                    pInfo->pidlRoot = NULL;
            }

            // TODO: Create rooted PIDL from pInfo->pidlPath and pInfo->pidlRoot

            TRACE("CmdLine Parser: Parsed /ROOT flag. dwFlags=%08lx, pidlRoot=%p\n", pInfo->dwFlags, pInfo->pidlRoot);
        }
        else
        {
            // Anything else is part of the target path to browse to
            TRACE("CmdLine Parser: Found target path %S\n", strField);

            // Which can be a shared-memory itemidlist
            if (!StrCmpIW(strField, L"/IDLIST"))
            {
                LPITEMIDLIST pidlArg;

                if (!hasNext)
                    return FALSE;

                hasNext = _ReadNextArg(&strNextArg, strField, _countof(strField));
                pidlArg = _ILReadFromSharedMemory(strField);
                if (!pidlArg)
                    return FALSE;

                if (pInfo->pidlPath)
                    ILFree(pInfo->pidlPath);
                pInfo->pidlPath = pidlArg;

                TRACE("CmdLine Parser: Parsed target path. dwFlags=%08lx, pidlPath=%p\n", pInfo->dwFlags, pInfo->pidlPath);
            }
            else
            {
                // Or just a plain old string.

                WCHAR szPath[MAX_PATH];
                DWORD result = GetFullPathNameW(strField, _countof(szPath), szPath, NULL);

                if (result != 0 && result <= _countof(szPath) && PathFileExistsW(szPath))
                    StringCchCopyW(strField, _countof(strField), szPath);

                LPITEMIDLIST pidlPath = ILCreateFromPathW(strField);

                pInfo->pidlPath = pidlPath;

                if (pidlPath)
                {
                    pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_IDLIST;
                    TRACE("CmdLine Parser: Parsed target path. dwFlags=%08lx, pidlPath=%p\n", pInfo->dwFlags, pInfo->pidlPath);
                }
                else
                {
                    // The path could not be parsed into an ID List,
                    // so pass it on as a plain string.

                    PWSTR field = StrDupW(strField);
                    pInfo->strPath = field;
                    if (field)
                    {
                        pInfo->dwFlags |= SH_EXPLORER_CMDLINE_FLAG_STRING;
                        TRACE("CmdLine Parser: Parsed target path. dwFlags=%08lx, strPath=%S\n", pInfo->dwFlags, field);
                    }
                }

            }
        }

        if (!hasNext)
            break;
        hasNext = _ReadNextArg(&strNextArg, strField, _countof(strField));
    }

    return TRUE;
}