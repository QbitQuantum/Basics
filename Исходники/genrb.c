int
main(int argc,
     char* argv[])
{
    UErrorCode  status    = U_ZERO_ERROR;
    const char *arg       = NULL;
    const char *outputDir = NULL; /* NULL = no output directory, use current */
    const char *inputDir  = NULL;
    const char *encoding  = "";
    int         i;

    U_MAIN_INIT_ARGS(argc, argv);

    argc = u_parseArgs(argc, argv, (int32_t)(sizeof(options)/sizeof(options[0])), options);

    /* error handling, printing usage message */
    if(argc<0) {
        fprintf(stderr, "%s: error in command line argument \"%s\"\n", argv[0], argv[-argc]);
    } else if(argc<2) {
        argc = -1;
    }

    if(options[VERSION].doesOccur) {
        fprintf(stderr,
                "%s version %s (ICU version %s).\n"
                "%s\n",
                argv[0], GENRB_VERSION, U_ICU_VERSION, U_COPYRIGHT_STRING);
        return U_ZERO_ERROR;
    }

    if(argc<0 || options[HELP1].doesOccur || options[HELP2].doesOccur) {
        /*
         * Broken into chucks because the C89 standard says the minimum
         * required supported string length is 509 bytes.
         */
        fprintf(stderr,
                "Usage: %s [OPTIONS] [FILES]\n"
                "\tReads the list of resource bundle source files and creates\n"
                "\tbinary version of reosurce bundles (.res files)\n",
                argv[0]);
        fprintf(stderr,
                "Options:\n"
                "\t-h or -? or --help       this usage text\n"
                "\t-q or --quiet            do not display warnings\n"
                "\t-v or --verbose          print extra information when processing files\n"
                "\t-V or --version          prints out version number and exits\n"
                "\t-c or --copyright        include copyright notice\n");
        fprintf(stderr,
                "\t-e or --encoding         encoding of source files\n"
                "\t-d of --destdir          destination directory, followed by the path, defaults to %s\n"
                "\t-s or --sourcedir        source directory for files followed by path, defaults to %s\n"
                "\t-i or --icudatadir       directory for locating any needed intermediate data files,\n"
                "\t                         followed by path, defaults to %s\n",
                u_getDataDirectory(), u_getDataDirectory(), u_getDataDirectory());
        fprintf(stderr,
                "\t-j or --write-java       write a Java ListResourceBundle for ICU4J, followed by optional encoding\n"
                "\t                         defaults to ASCII and \\uXXXX format.\n"
                "\t-p or --package-name     For ICU4J: package name for writing the ListResourceBundle for ICU4J,\n"
                "\t                         defaults to com.ibm.icu.impl.data\n");
        fprintf(stderr,
                "\t-b or --bundle-name      bundle name for writing the ListResourceBundle for ICU4J,\n"
                "\t                         defaults to LocaleElements\n"
                "\t-x or --write-xliff      write a XLIFF file for the resource bundle. Followed by an optional output file name.\n"
                "\t-k or --strict           use pedantic parsing of syntax\n"
                /*added by Jing*/
                "\t-l or --language         For XLIFF: language code compliant with ISO 639.\n");

        return argc < 0 ? U_ILLEGAL_ARGUMENT_ERROR : U_ZERO_ERROR;
    }

    if(options[VERBOSE].doesOccur) {
        setVerbose(TRUE);
    }

    if(options[QUIET].doesOccur) {
        setShowWarning(FALSE);
    }
    if(options[STRICT].doesOccur) {
        setStrict(TRUE);
    }
    if(options[COPYRIGHT].doesOccur){
        setIncludeCopyright(TRUE);
    }

    if(options[SOURCEDIR].doesOccur) {
        inputDir = options[SOURCEDIR].value;
    }

    if(options[DESTDIR].doesOccur) {
        outputDir = options[DESTDIR].value;
    }
    if(options[PACKAGE_NAME].doesOccur) {
        gPackageName = options[PACKAGE_NAME].value;
        if(!strcmp(gPackageName, "ICUDATA"))
        {
            gPackageName = U_ICUDATA_NAME;
        }
        if(gPackageName[0] == 0)
        {
            gPackageName = NULL;
        }
    }

    if(options[ENCODING].doesOccur) {
        encoding = options[ENCODING].value;
    }

    if(options[ICUDATADIR].doesOccur) {
        u_setDataDirectory(options[ICUDATADIR].value);
    }
    /* Initialize ICU */
    u_init(&status);
    if (U_FAILURE(status) && status != U_FILE_ACCESS_ERROR) {
        /* Note: u_init() will try to open ICU property data.
         *       failures here are expected when building ICU from scratch.
         *       ignore them.
        */
        fprintf(stderr, "%s: can not initialize ICU.  status = %s\n",
            argv[0], u_errorName(status));
        exit(1);
    }
    status = U_ZERO_ERROR;
    if(options[WRITE_JAVA].doesOccur) {
        write_java = TRUE;
        outputEnc = options[WRITE_JAVA].value;
    }

    if(options[BUNDLE_NAME].doesOccur) {
        bundleName = options[BUNDLE_NAME].value;
    }

    if(options[WRITE_XLIFF].doesOccur) {
        write_xliff = TRUE;
        if(options[WRITE_XLIFF].value != NULL){
            xliffOutputFileName = options[WRITE_XLIFF].value;
        }
    }

    if(options[NO_BINARY_COLLATION].doesOccur) {
      initParser(FALSE);
    } else {
      initParser(TRUE);
    }

    /*added by Jing*/
    if(options[LANGUAGE].doesOccur) {
        language = options[LANGUAGE].value;
    }

    /* generate the binary files */
    for(i = 1; i < argc; ++i) {
        status = U_ZERO_ERROR;
        arg    = getLongPathname(argv[i]);

        if (inputDir) {
            uprv_strcpy(theCurrentFileName, inputDir);
            uprv_strcat(theCurrentFileName, U_FILE_SEP_STRING);
        } else {
            *theCurrentFileName = 0;
        }
        uprv_strcat(theCurrentFileName, arg);

        if (isVerbose()) {
            printf("Processing file \"%s\"\n", theCurrentFileName);
        }
        processFile(arg, encoding, inputDir, outputDir, gPackageName, &status);
    }

    /* Dont return warnings as a failure */
    if (! U_FAILURE(status)) {
        return 0;
    }

    return status;
}