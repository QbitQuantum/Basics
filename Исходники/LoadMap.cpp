static void idaapi run(int /* arg */)
{
    static char mapFileName[_MAX_PATH] = { 0 };

    // If user press shift key, show options dialog
    if (GetAsyncKeyState(VK_SHIFT) & 0x8000)
    {
        ShowOptionsDlg();
    }

    ulong numOfSegs = (ulong) get_segm_qty();
    if (0 == numOfSegs)
    {
        warning("Not found any segments");
        return;
    }

    if ('\0' == mapFileName[0])
    {
        // First run
        strncpy(mapFileName, get_input_file_path(), sizeof(mapFileName));
        WIN32CHECK(PathRenameExtension(mapFileName, ".map"));
    }

    // Show open map file dialog
    char *fname = askfile_c(0, mapFileName, "Open MAP file");
    if (NULL == fname)
    {
        msg("LoadMap: User cancel\n");
        return;
    }

    // Open the map file
    LPSTR pMapStart = NULL;
    DWORD mapSize = INVALID_FILE_SIZE;
    MAP_OPEN_ERROR eRet = MapFileOpen(fname, pMapStart, mapSize);
    switch (eRet)
    {
        case WIN32_ERROR:
            warning("Could not open file '%s'.\nWin32 Error Code = 0x%08X",
                    fname, GetLastError());
            return;

        case FILE_EMPTY_ERROR:
            warning("File '%s' is empty, zero size", fname);
            return;

        case FILE_BINARY_ERROR:
            warning("File '%s' seem to be a binary or Unicode file", fname);
            return;

        case OPEN_NO_ERROR:
        default:
            break;
    }

    bool foundHdr = false;
    ulong validSyms = 0;
    ulong invalidSyms = 0;

    // The mark pointer to the end of memory map file
    // all below code must not read or write at and over it
    LPSTR pMapEnd = pMapStart + mapSize;

    show_wait_box("Parsing and applying symbols from the Map file '%s'", fname);

    __try
    {
        LPSTR pLine = pMapStart;
        LPSTR pEOL = pMapStart;
        while (pLine < pMapEnd)
        {
            // Skip the spaces, '\r', '\n' characters, blank lines, seek to the
            // non space character at the beginning of a non blank line
            pLine = SkipSpaces(pEOL, pMapEnd);

            // Find the EOL '\r' or '\n' characters
            pEOL = FindEOL(pLine, pMapEnd);

            size_t lineLen = (size_t) (pEOL - pLine);
            if (lineLen < g_minLineLen)
            {
                continue;
            }

            if (!foundHdr)
            {
                if ((0 == strnicmp(pLine, VC_HDR_START      , lineLen)) ||
                    (0 == strnicmp(pLine, BL_HDR_NAME_START , lineLen)) ||
                    (0 == strnicmp(pLine, BL_HDR_VALUE_START, lineLen)))
                {
                    foundHdr = true;
                }
            }
            else
            {
                ulong seg = SREG_NUM;
                ulong addr = BADADDR;
                char name[MAXNAMELEN + 1];
                char fmt[80];

                name[0] = '\0';
                fmt[0] = '\0';

                // Get segment number, address, name, by pass spaces at beginning,
                // between ':' character, between address and name
                int ret = _snscanf(pLine, min(lineLen, MAXNAMELEN + g_minLineLen),
                                   " %04X : %08X %s", &seg, &addr, name);
                if (3 != ret)
                {
                    // we have parsed to end of value/name symbols table or reached EOF
                    _snprintf(fmt, sizeof(fmt), "Parsing finished at line: '%%.%ds'.\n", lineLen);
                    ShowMsg(fmt, pLine);
                    break;
                }
                else if ((0 == seg) || (--seg >= numOfSegs) ||
                        (BADADDR == addr) || ('\0' == name[0]))
                {
                    sprintf(fmt, "Invalid map line: %%.%ds.\n", lineLen);
                    ShowMsg(fmt, pLine);

                    invalidSyms++;
                }
                else
                {
                    // Ensure name is NULL terminated
                    name[MAXNAMELEN] = '\0';

                    // Determine the DeDe map file
                    bool bNameApply = g_options.bNameApply;
                    char *pname = name;
                    if (('<' == pname[0]) && ('-' == pname[1]))
                    {
                        // Functions indicator symbol of DeDe map
                        pname += 2;
                        bNameApply = true;
                    }
                    else if ('*' == pname[0])
                    {
                        // VCL controls indicator symbol of DeDe map
                        pname++;
                        bNameApply = false;
                    }
                    else if (('-' == pname[0]) && ('>' == pname[1]))
                    {
                        // VCL methods indicator symbol of DeDe map
                        pname += 2;
                        bNameApply = false;
                    }

                    ulong la = addr + getnseg((int) seg)->startEA;
                    flags_t f = getFlags(la);

                    if (bNameApply) // Apply symbols for name
                    {
                        //  Add name if there's no meaningful name assigned.
                        if (g_options.bReplace ||
                            (!has_name(f) || has_dummy_name(f) || has_auto_name(f)))
                        {
                            if (set_name(la, pname, SN_NOWARN))
                            {
                                ShowMsg("%04X:%08X - Change name to '%s' successed\n",
                                        seg, la, pname);
                                validSyms++;
                            }
                            else
                            {
                                ShowMsg("%04X:%08X - Change name to '%s' failed\n",
                                        seg, la, pname);
                                invalidSyms++;
                            }
                        }
                    }
                    else if (g_options.bReplace || !has_cmt(f))
                    {
                        // Apply symbols for comment
                        if (set_cmt(la, pname, false))
                        {
                            ShowMsg("%04X:%08X - Change comment to '%s' successed\n",
                                    seg, la, pname);
                            validSyms++;
                        }
                        else
                        {
                            ShowMsg("%04X:%08X - Change comment to '%s' failed\n",
                                    seg, la, pname);
                            invalidSyms++;
                        }
                    }
                }
            }
        }
    }
    __finally
    {
        MapFileClose(pMapStart);
        hide_wait_box();
    }

    if (!foundHdr)
    {
        warning("File '%s' is not a valid Map file", fname);
    }
    else
    {
        // Save file name for next askfile_c dialog
        strncpy(mapFileName, fname, sizeof(mapFileName));

        // Show the result
        msg("Result of loading and parsing the Map file '%s'\n"
            "   Number of Symbols applied: %d\n"
            "   Number of Invalid Symbols: %d\n\n",
            fname, validSyms, invalidSyms);
    }
}