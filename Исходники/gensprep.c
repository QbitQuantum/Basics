extern int
main(int argc, char* argv[]) {
#if !UCONFIG_NO_IDNA
    char* filename = NULL;
#endif
    const char *srcDir=NULL, *destDir=NULL, *icuUniDataDir=NULL;
    const char *bundleName=NULL, *inputFileName = NULL;
    char *basename=NULL;
    int32_t sprepOptions = 0;

    UErrorCode errorCode=U_ZERO_ERROR;

    U_MAIN_INIT_ARGS(argc, argv);

    /* preset then read command line options */
    options[DESTDIR].value=u_getDataDirectory();
    options[SOURCEDIR].value="";
    options[UNICODE_VERSION].value="0"; /* don't assume the unicode version */
    options[BUNDLE_NAME].value = DATA_NAME;
    options[NORMALIZE].value = "";

    argc=u_parseArgs(argc, argv, UPRV_LENGTHOF(options), options);

    /* error handling, printing usage message */
    if(argc<0) {
        fprintf(stderr,
            "error in command line argument \"%s\"\n",
            argv[-argc]);
    }
    if(argc<0 || options[HELP].doesOccur || options[HELP_QUESTION_MARK].doesOccur) {
        return printHelp(argc, argv);
        
    }

    /* get the options values */
    beVerbose=options[VERBOSE].doesOccur;
    haveCopyright=options[COPYRIGHT].doesOccur;
    srcDir=options[SOURCEDIR].value;
    destDir=options[DESTDIR].value;
    bundleName = options[BUNDLE_NAME].value;
    if(options[NORMALIZE].doesOccur) {
        icuUniDataDir = options[NORMALIZE].value;
    } else {
        icuUniDataDir = options[NORM_CORRECTION_DIR].value;
    }

    if(argc<2) {
        /* print the help message */
        return printHelp(argc, argv);
    } else {
        inputFileName = argv[1];
    }
    if(!options[UNICODE_VERSION].doesOccur){
        return printHelp(argc, argv);
    }
    if(options[ICUDATADIR].doesOccur) {
        u_setDataDirectory(options[ICUDATADIR].value);
    }
#if UCONFIG_NO_IDNA

    fprintf(stderr,
        "gensprep writes dummy " U_ICUDATA_NAME "_" DATA_NAME "." DATA_TYPE
        " because UCONFIG_NO_IDNA is set, \n"
        "see icu/source/common/unicode/uconfig.h\n");
    generateData(destDir, bundleName);

#else

    setUnicodeVersion(options[UNICODE_VERSION].value);
    filename = (char* ) uprv_malloc(uprv_strlen(srcDir) + 300); /* hopefully this should be enough */
   
    /* prepare the filename beginning with the source dir */
    if(uprv_strchr(srcDir,U_FILE_SEP_CHAR) == NULL && uprv_strchr(srcDir,U_FILE_ALT_SEP_CHAR) == NULL){
        filename[0] = '.';
        filename[1] = U_FILE_SEP_CHAR;
        uprv_strcpy(filename+2,srcDir);
    }else{
        uprv_strcpy(filename, srcDir);
    }
    
    basename=filename+uprv_strlen(filename);
    if(basename>filename && *(basename-1)!=U_FILE_SEP_CHAR) {
        *basename++=U_FILE_SEP_CHAR;
    }
    
    /* initialize */
    init();

    /* process the file */
    uprv_strcpy(basename,inputFileName);
    parseMappings(filename,FALSE, &errorCode);
    if(U_FAILURE(errorCode)) {
        fprintf(stderr, "Could not open file %s for reading. Error: %s \n", filename, u_errorName(errorCode));
        return errorCode;
    }
    
    if(options[NORMALIZE].doesOccur){ /* this option might be set by @normalize;; in the source file */
        /* set up directory for NormalizationCorrections.txt */
        uprv_strcpy(filename,icuUniDataDir);
        basename=filename+uprv_strlen(filename);
        if(basename>filename && *(basename-1)!=U_FILE_SEP_CHAR) {
            *basename++=U_FILE_SEP_CHAR;
        }

        *basename++=U_FILE_SEP_CHAR;
        uprv_strcpy(basename,NORM_CORRECTIONS_FILE_NAME);
    
        parseNormalizationCorrections(filename,&errorCode);
        if(U_FAILURE(errorCode)){
            fprintf(stderr,"Could not open file %s for reading \n", filename);
            return errorCode;
        }
        sprepOptions |= _SPREP_NORMALIZATION_ON;
    }
    
    if(options[CHECK_BIDI].doesOccur){ /* this option might be set by @check-bidi;; in the source file */
        sprepOptions |= _SPREP_CHECK_BIDI_ON;
    }

    setOptions(sprepOptions);

    /* process parsed data */
    if(U_SUCCESS(errorCode)) {
        /* write the data file */
        generateData(destDir, bundleName);

        cleanUpData();
    }

    uprv_free(filename);

    u_cleanup();

#endif

    return errorCode;
}