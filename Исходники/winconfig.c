/* Set the keyboard configuration */
Bool
winConfigKeyboard(DeviceIntPtr pDevice)
{
    char layoutName[KL_NAMELENGTH];
    unsigned char layoutFriendlyName[256];
    unsigned int layoutNum = 0;
    unsigned int deviceIdentifier = 0;
    int keyboardType;

#ifdef XWIN_XF86CONFIG
    XF86ConfInputPtr kbd = NULL;
    XF86ConfInputPtr input_list = NULL;
    MessageType kbdfrom = X_CONFIG;
#endif
    MessageType from = X_DEFAULT;
    char *s = NULL;

    /* Setup defaults */
    XkbGetRulesDflts(&g_winInfo.xkb);

    /*
     * Query the windows autorepeat settings and change the xserver defaults.
     */
    {
        int kbd_delay;
        DWORD kbd_speed;

        if (SystemParametersInfo(SPI_GETKEYBOARDDELAY, 0, &kbd_delay, 0) &&
            SystemParametersInfo(SPI_GETKEYBOARDSPEED, 0, &kbd_speed, 0)) {
            switch (kbd_delay) {
            case 0:
                g_winInfo.keyboard.delay = 250;
                break;
            case 1:
                g_winInfo.keyboard.delay = 500;
                break;
            case 2:
                g_winInfo.keyboard.delay = 750;
                break;
            default:
            case 3:
                g_winInfo.keyboard.delay = 1000;
                break;
            }
            g_winInfo.keyboard.rate = (kbd_speed > 0) ? kbd_speed : 1;
            winDebug("Setting autorepeat to delay=%ld, rate=%ld\n",
                   g_winInfo.keyboard.delay, g_winInfo.keyboard.rate);

        }
    }

    keyboardType = GetKeyboardType(0);
    if (keyboardType > 0 && GetKeyboardLayoutName(layoutName)) {
        WinKBLayoutPtr pLayout;
        Bool bfound = FALSE;
        int pass;

        layoutNum = strtoul(layoutName, (char **) NULL, 16);
        if ((layoutNum & 0xffff) == 0x411) {
            if (keyboardType == 7) {
                /* Japanese layouts have problems with key event messages
                   such as the lack of WM_KEYUP for Caps Lock key.
                   Loading US layout fixes this problem. */
                if (LoadKeyboardLayout("00000409", KLF_ACTIVATE) != NULL)
                    winDebug("Loading US keyboard layout.\n");
                else
                    ErrorF ("LoadKeyboardLayout failed.\n");
            }
        }

        /* Discover the friendly name of the current layout */
        {
            HKEY regkey = NULL;
            const char regtempl[] =
                "SYSTEM\\CurrentControlSet\\Control\\Keyboard Layouts\\";
            char *regpath;
            DWORD namesize = sizeof(layoutFriendlyName);

            regpath = malloc(sizeof(regtempl) + KL_NAMELENGTH + 1);
            strcpy(regpath, regtempl);
            strcat(regpath, layoutName);

            if (!RegOpenKey(HKEY_LOCAL_MACHINE, regpath, &regkey))
                RegQueryValueEx(regkey, "Layout Text", 0, NULL,
                                layoutFriendlyName, &namesize);

            /* Close registry key */
            if (regkey)
                RegCloseKey(regkey);
            free(regpath);
        }

        winDebug ("Windows keyboard layout: \"%s\" (%08x) \"%s\", type %d\n",
                  layoutName, layoutNum, layoutFriendlyName, keyboardType);

        deviceIdentifier = layoutNum >> 16;
        for (pass = 0; pass < 2; pass++) {
            /* If we didn't find an exact match for the input locale identifer,
               try to find an match on the language identifier part only  */
            if (pass == 1)
                layoutNum = (layoutNum & 0xffff);

            for (pLayout = winKBLayouts; pLayout->winlayout != -1; pLayout++) {
                if (pLayout->winlayout != layoutNum)
                    continue;
                if (pLayout->winkbtype > 0 && pLayout->winkbtype != keyboardType)
                    continue;

                bfound = TRUE;
                winDebug (
                       "Found matching XKB configuration \"%s\"\n",
                       pLayout->layoutname);

                winDebug(
                       "Model = \"%s\" Layout = \"%s\""
                       " Variant = \"%s\" Options = \"%s\"\n",
                       pLayout->xkbmodel ? pLayout->xkbmodel : "none",
                       pLayout->xkblayout ? pLayout->xkblayout : "none",
                       pLayout->xkbvariant ? pLayout->xkbvariant : "none",
                       pLayout->xkboptions ? pLayout->xkboptions : "none");

                g_winInfo.xkb.model = (char *)pLayout->xkbmodel;
                g_winInfo.xkb.layout = (char *)pLayout->xkblayout;
                g_winInfo.xkb.variant = (char *)pLayout->xkbvariant;
                g_winInfo.xkb.options = (char *)pLayout->xkboptions;

                if (deviceIdentifier == 0xa000) {
                    winDebug("Windows keyboard layout device identifier indicates Macintosh, setting Model = \"macintosh\"");
                    g_winInfo.xkb.model = "macintosh";
                }

                break;
            }

            if (bfound)
                break;
        }

        if (!bfound) {
            ErrorF ("Keyboardlayout \"%s\" (%s) is unknown, using X server default layout\n",
                   layoutFriendlyName, layoutName);
        }
    }