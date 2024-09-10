/******************************************************************
 *		doWinMain (HHCTRL.OCX.13)
 */
int WINAPI doWinMain(HINSTANCE hInstance, LPSTR szCmdLine)
{
    MSG msg;
    int len, buflen, mapid = -1;
    WCHAR *filename;
    char *endq = NULL;

    hh_process = TRUE;

    /* Parse command line option of the HTML Help command.
     *
     * Note: The only currently handled action is "mapid",
     *  which corresponds to opening a specific page.
     */
    while(*szCmdLine == '-')
    {
        LPSTR space, ptr;

        ptr = szCmdLine + 1;
        space = strchr(ptr, ' ');
        if(!strncmp(ptr, "mapid", space-ptr))
        {
            char idtxt[10];

            ptr += strlen("mapid")+1;
            space = strchr(ptr, ' ');
            /* command line ends without number */
            if (!space)
                return 0;
            memcpy(idtxt, ptr, space-ptr);
            idtxt[space-ptr] = '\0';
            mapid = atoi(idtxt);
            szCmdLine = space+1;
        }
        else
        {
            FIXME("Unhandled HTML Help command line parameter! (%.*s)\n", (int)(space-szCmdLine), szCmdLine);
            return 0;
        }
    }

    /* FIXME: Check szCmdLine for bad arguments */
    if (*szCmdLine == '\"')
        endq = strchr(++szCmdLine, '\"');

    if (endq)
        len = endq - szCmdLine;
    else
        len = strlen(szCmdLine);

    /* no filename given */
    if (!len)
        return 0;

    buflen = MultiByteToWideChar(CP_ACP, 0, szCmdLine, len, NULL, 0) + 1;
    filename = heap_alloc(buflen * sizeof(WCHAR));
    MultiByteToWideChar(CP_ACP, 0, szCmdLine, len, filename, buflen);
    filename[buflen-1] = 0;

    /* Open a specific help topic */
    if(mapid != -1)
        HtmlHelpW(GetDesktopWindow(), filename, HH_HELP_CONTEXT, mapid);
    else
        HtmlHelpW(GetDesktopWindow(), filename, HH_DISPLAY_TOPIC, 0);

    heap_free(filename);

    while (GetMessageW(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    return 0;
}