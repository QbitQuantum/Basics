extern int
main(int argc, char* argv[]) {
    UVersionInfo version;
    UBool store10Names=FALSE;
    UErrorCode errorCode = U_ZERO_ERROR;

    U_MAIN_INIT_ARGS(argc, argv);

    /* Initialize ICU */
    u_init(&errorCode);
    if (U_FAILURE(errorCode) && errorCode != U_FILE_ACCESS_ERROR) {
        /* Note: u_init() will try to open ICU property data.
         *       failures here are expected when building ICU from scratch.
         *       ignore them.
         */
        fprintf(stderr, "%s: can not initialize ICU.  errorCode = %s\n",
            argv[0], u_errorName(errorCode));
        exit(1);
    }

    /* preset then read command line options */
    options[5].value=u_getDataDirectory();
    options[6].value="4.1";
    argc=u_parseArgs(argc, argv, sizeof(options)/sizeof(options[0]), options);

    /* error handling, printing usage message */
    if(argc<0) {
        fprintf(stderr,
            "error in command line argument \"%s\"\n",
            argv[-argc]);
    } else if(argc<2) {
        argc=-1;
    }
    if(argc<0 || options[0].doesOccur || options[1].doesOccur) {
        /*
         * Broken into chucks because the C89 standard says the minimum
         * required supported string length is 509 bytes.
         */
        fprintf(stderr,
            "Usage: %s [-1[+|-]] [-v[+|-]] [-c[+|-]] filename\n"
            "\n"
            "Read the UnicodeData.txt file and \n"
            "create a binary file " DATA_NAME "." DATA_TYPE " with the character names\n"
            "\n"
            "\tfilename  absolute path/filename for the Unicode database text file\n"
            "\t\t(default: standard input)\n"
            "\n",
            argv[0]);
        fprintf(stderr,
            "Options:\n"
            "\t-h or -? or --help  this usage text\n"
            "\t-v or --verbose     verbose output\n"
            "\t-q or --quiet       no output\n"
            "\t-c or --copyright   include a copyright notice\n"
            "\t-d or --destdir     destination directory, followed by the path\n"
            "\t-u or --unicode     Unicode version, followed by the version like 3.0.0\n"
            "\t-1 or --unicode1-names  store Unicode 1.0 character names\n");
        return argc<0 ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR;
    }

    /* get the options values */
    beVerbose=options[2].doesOccur;
    beQuiet=options[3].doesOccur;
    haveCopyright=options[4].doesOccur;
    store10Names=options[7].doesOccur;

    /* set the Unicode version */
    u_versionFromString(version, options[6].value);
    uprv_memcpy(dataInfo.dataVersion, version, 4);
    ucdVersion=findUnicodeVersion(version);

    init();
    parseDB(argc>=2 ? argv[1] : "-", store10Names);
    compress();
    generateData(options[5].value);

    u_cleanup();
    return 0;
}