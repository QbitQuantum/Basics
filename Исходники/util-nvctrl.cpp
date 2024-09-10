int GetNvidiaRates(t_screenrate& screenmap)
{
#ifdef USING_XRANDR

    MythXDisplay *d = OpenMythXDisplay();
    if (!d)
    {
        return -1;
    }
    Display *dpy;
    bool ret;
    int screen, display_devices, mask, major, minor, len, j;
    char *str, *start;
    int nDisplayDevice;
    
    char *pMetaModes, *pModeLines[8], *tmp, *modeString;
    char *modeLine, *modeName;
    int MetaModeLen, ModeLineLen[8];
    int thisMask;
    int id;
    int twinview =  0;
    map<int, map<int,bool> > maprate;

    memset(pModeLines, 0, sizeof(pModeLines));
    memset(ModeLineLen, 0, sizeof(ModeLineLen));

    /*
     * Open a display connection, and make sure the NV-CONTROL X
     * extension is present on the screen we want to use.
     */

    dpy = d->GetDisplay();    
    screen = d->GetScreen();

    if (!XNVCTRLIsNvScreen(dpy, screen))
    {
        LOG(VB_PLAYBACK, LOG_INFO,
            QString("The NV-CONTROL X extension is not available on screen %1 "
                    "of '%2'.")
                .arg(screen) .arg(XDisplayName(NULL)));
        delete d;
        return -1;
    }

    ret = XNVCTRLQueryVersion(dpy, &major, &minor);
    if (ret != True)
    {
        LOG(VB_PLAYBACK, LOG_INFO,
            QString("The NV-CONTROL X extension does not exist on '%1'.")
                .arg(XDisplayName(NULL)));
        delete d;
        return -1;
    }

    ret = XNVCTRLQueryAttribute(dpy, screen, 0, NV_CTRL_DYNAMIC_TWINVIEW, &twinview);

    if (!ret)
    {
        LOG(VB_PLAYBACK, LOG_ERR,
             "Failed to query if Dynamic Twinview is enabled");
        XCloseDisplay(dpy);
        return -1;
    }
    if (!twinview)
    {
        LOG(VB_PLAYBACK, LOG_ERR, "Dynamic Twinview not enabled, ignoring");
        delete d;
        return 0;
    }

    /*
     * query the connected display devices on this X screen and print
     * basic information about each X screen
     */

    ret = XNVCTRLQueryAttribute(dpy, screen, 0,
                                NV_CTRL_CONNECTED_DISPLAYS, &display_devices);

    if (!ret)
    {
        LOG(VB_PLAYBACK, LOG_ERR,
            "Failed to query the enabled Display Devices.");
        delete d;
        return -1;
    }

    /* first, we query the MetaModes on this X screen */

    ret = XNVCTRLQueryBinaryData(dpy, screen, 0, // n/a
                           NV_CTRL_BINARY_DATA_METAMODES,
                           (unsigned char **)&pMetaModes, &MetaModeLen);
    if (!ret)
    {
        LOG(VB_PLAYBACK, LOG_ERR,
            "Failed to query the metamode on selected display device.");
        delete d;
        return -1;
    }

    /*
     * then, we query the ModeLines for each display device on
     * this X screen; we'll need these later
     */

    nDisplayDevice = 0;

    for (mask = 1; mask < (1 << 24); mask <<= 1)
    {
        if (!(display_devices & mask)) continue;

        ret = XNVCTRLQueryBinaryData(dpy, screen, mask,
                               NV_CTRL_BINARY_DATA_MODELINES,
                               (unsigned char **)&str, &len);
        if (!ret)
        {
            LOG(VB_PLAYBACK, LOG_ERR,
               "Unknown error. Failed to query the enabled Display Devices.");
            // Free Memory currently allocated
            for (j=0; j < nDisplayDevice; ++j)
            {
                free(pModeLines[j]);
            }
            delete d;
            return -1;
        }

        pModeLines[nDisplayDevice] = str;
        ModeLineLen[nDisplayDevice] = len;

        nDisplayDevice++;
    }

    /* now, parse each MetaMode */
    str = start = pMetaModes;

    for (j = 0; j < MetaModeLen - 1; ++j)
    {
        /*
         * if we found the end of a line, treat the string from
         * start to str[j] as a MetaMode
         */

        if ((str[j] == '\0') && (str[j+1] != '\0'))
        {
            id = extract_id_string(start);
            /*
             * the MetaMode may be preceded with "token=value"
             * pairs, separated by the main MetaMode with "::"; if
             * "::" exists in the string, skip past it
             */

            tmp = strstr(start, "::");
            if (tmp)
            {
                tmp += 2;
            }
            else
            {
                tmp = start;
            }

            /* split the MetaMode string by comma */

            char *strtok_state = NULL;
            for (modeString = strtok_r(tmp, ",", &strtok_state);
                 modeString;
                 modeString = strtok_r(NULL, ",", &strtok_state))
            {
                /*
                 * retrieve the modeName and display device mask
                 * for this segment of the Metamode
                 */

                parse_mode_string(modeString, &modeName, &thisMask);

                /* lookup the modeline that matches */
                nDisplayDevice = 0;
                if (thisMask)
                {
                    for (mask = 1; mask < (1 << 24); mask <<= 1)
                    {
                        if (!(display_devices & mask)) continue;
                        if (thisMask & mask) break;
                        nDisplayDevice++;
                    }
                }

                modeLine = find_modeline(modeName,
                                         pModeLines[nDisplayDevice],
                                         ModeLineLen[nDisplayDevice]);

                if (modeLine && !modeline_is_interlaced(modeLine))
                {
                    int w, h, vfl, hfl, i, irate;
                    double dcl, r;
                    char *buf[256];
                    uint64_t key, key2;

                    // skip name
                    tmp = strchr(modeLine, '"');
                    tmp = strchr(tmp+1, '"') +1 ;
                    while (*tmp == ' ')
                        tmp++;
                    i = 0;
                    for (modeString = strtok_r(tmp, " ", &strtok_state);
                         modeString;
                         modeString = strtok_r(NULL, " ", &strtok_state))
                    {
                        buf[i++] = modeString;
                    }
                    w = strtol(buf[1], NULL, 10);
                    h = strtol(buf[5], NULL, 10);
                    vfl = strtol(buf[8], NULL, 10);
                    hfl = strtol(buf[4], NULL, 10);
                    h = strtol(buf[5], NULL, 10);
                    istringstream istr(buf[0]);
                    istr.imbue(locale("C"));
                    istr >> dcl;
                    r = (dcl * 1000000.0) / (vfl * hfl);
                    irate = (int) round(r * 1000.0);
                    key = DisplayResScreen::CalcKey(w, h, (double) id);
                    key2 = DisplayResScreen::CalcKey(w, h, 0.0);
                    // We need to eliminate duplicates, giving priority to the first entries found
                    if (maprate.find(key2) == maprate.end())
                    {
                        // First time we see this resolution, create a map for it
                        maprate[key2] = map<int, bool>();
                    }
                    if ((maprate[key2].find(irate) == maprate[key2].end()) &&
                        (screenmap.find(key) == screenmap.end()))
                    {
                        screenmap[key] = r;
                        maprate[key2][irate] = true;
                    }
                }
                free(modeName);
            }

            /* move to the next MetaMode */
            start = &str[j+1];
        }