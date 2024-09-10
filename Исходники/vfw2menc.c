int main(int argc, char *argv[])
{
    char *driver = NULL;
    char *fourcc = NULL;
    char *filename = NULL;
    unsigned char mode = 0;
    DWORD dwFCC = 0;
    ICOPEN icopen;
    HRESULT coinit = S_FALSE;
    /* ICINFO icinfo; */

    wchar_t drvfile[MAX_PATH];
    HDRVR hDriver = NULL;
    int ret = 0;
    int c = -1, long_options_index = -1;

    if (argc < 2)
    {
        help(argv[0]);
        ret = -1;
        goto cleanup;
    }

    while ((c = getopt_long(argc, argv, "hd:f:s:c:v", long_options, &long_options_index)) != -1)
    {
        switch (c)
        {
            case 'h':
                help(argv[0]);
                ret = 0;
                goto cleanup;
            case 'd':
                driver = strdup(optarg);
                break;
            case 'f':
                fourcc = strdup(optarg);
                if (strlen(optarg) != 4) BAIL("Fourcc must be exactly 4 chars");
                break;
            case 's':
                if (mode != MODE_NONE) BAIL("Incompatible arguments");
                filename = strdup(optarg);
                mode = MODE_SAVE;
                break;
            case 'c':
                if (mode != MODE_NONE) BAIL("Incompatible arguments");
                filename = strdup(optarg);
                mode = MODE_CHECK;
                break;
            case 'v':
                if (mode != MODE_NONE) BAIL("Incompatible arguments");
                mode = MODE_VIEW;
                break;
            default:
                printf("Wrong arguments!\n");
                help(argv[0]);
                goto cleanup;
        }
    }

    if (!(argc == optind) && (mode != MODE_NONE) &&
        driver && (filename || (mode == MODE_VIEW)))
    {
        help(argv[0]);
        goto cleanup;
    }

    if (!MultiByteToWideChar(CP_ACP, 0, driver, -1, drvfile, MAX_PATH))
        BAIL("MultiByteToWideChar() failed\n");

    if (fourcc) memcpy(&dwFCC, fourcc, 4);
    memset(&icopen, 0, sizeof(icopen));

    icopen.dwSize = sizeof(icopen);
    icopen.fccType = ICTYPE_VIDEO; /* VIDC */
    icopen.fccHandler = dwFCC;
    icopen.dwVersion  = 0x00001000; /* FIXME */
    icopen.dwFlags = ICMODE_COMPRESS;
    icopen.dwError = 0;
    icopen.pV1Reserved = NULL;
    icopen.pV2Reserved = NULL;
    icopen.dnDevNode = -1; /* FIXME */

    coinit = CoInitialize(NULL);

    if (!(hDriver = OpenDriver(drvfile, NULL, (LPARAM) &icopen)))
        BAIL("OpenDriver() failed\n");

   /*
        memset(&icinfo, 0, sizeof(ICINFO));
        icinfo.dwSize = sizeof(ICINFO);
        SendDriverMessage(hDriver, ICM_GETINFO, (LPARAM) &icinfo, sizeof(ICINFO));
    */

    if (SendDriverMessage(hDriver, ICM_CONFIGURE, -1, 0) != ICERR_OK)
        BAIL("The driver doesn't provide a configure dialog");


    switch(mode)
    {
        case MODE_CHECK:
            if (load_settings(hDriver, filename))
                BAIL("Cannot load settings from file");
            if (SendDriverMessage(hDriver, ICM_CONFIGURE, 0, 0) != ICERR_OK)
                BAIL("ICM_CONFIGURE failed");
            break;
        case MODE_SAVE:
            if (SendDriverMessage(hDriver, ICM_CONFIGURE, 0, 0) != ICERR_OK)
                BAIL("ICM_CONFIGURE failed");
            if (save_settings(hDriver, filename))
                BAIL("Cannot save settings to file");
            break;
        case MODE_VIEW:
            {
                HWND hwnd = GetDesktopWindow();
                if (SendDriverMessage(hDriver, ICM_CONFIGURE, (LPARAM) hwnd, 0) != ICERR_OK)
                    BAIL("ICM_CONFIGURE failed");
            }
            break;
        default:
            BAIL("This should not happen :)");
    }

cleanup:
    if (driver) free(driver);
    if (fourcc) free(fourcc);
    if (filename) free(filename);
    if (hDriver) CloseDriver(hDriver, 0, 0);
    if (coinit == S_OK) CoUninitialize();
    return ret;
}