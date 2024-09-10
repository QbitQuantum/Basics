//----------------------------------------------------------------------------
//
//  main      for gencfu
//
//----------------------------------------------------------------------------
int  main(int argc, char **argv) {
    UErrorCode  status = U_ZERO_ERROR;
    const char *confFileName;
    const char *confWSFileName;
    const char *outFileName;
    const char *outDir = NULL;
    const char *copyright = NULL;

    //
    // Pick up and check the command line arguments,
    //    using the standard ICU tool utils option handling.
    //
    U_MAIN_INIT_ARGS(argc, argv);
    progName = argv[0];
    argc=u_parseArgs(argc, argv, sizeof(options)/sizeof(options[0]), options);
    if(argc<0) {
        // Unrecognized option
        fprintf(stderr, "error in command line argument \"%s\"\n", argv[-argc]);
        usageAndDie(U_ILLEGAL_ARGUMENT_ERROR);
    }

    if(options[0].doesOccur || options[1].doesOccur) {
        //  -? or -h for help.
        usageAndDie(0);
    }

    if (!(options[3].doesOccur && options[4].doesOccur && options[5].doesOccur)) {
        fprintf(stderr, "confusables file, whole script confusables file and output file must all be specified.\n");
        usageAndDie(U_ILLEGAL_ARGUMENT_ERROR);
    }
    confFileName   = options[3].value;
    confWSFileName = options[4].value;
    outFileName    = options[5].value;

    if (options[6].doesOccur) {
        u_setDataDirectory(options[6].value);
    }

    status = U_ZERO_ERROR;

    /* Combine the directory with the file name */
    if(options[7].doesOccur) {
        outDir = options[7].value;
    }
    if (options[8].doesOccur) {
        copyright = U_COPYRIGHT_STRING;
    }

#if UCONFIG_NO_REGULAR_EXPRESSIONS || UCONFIG_NO_NORMALIZATION || UCONFIG_NO_FILE_IO
    // spoof detection data file parsing is dependent on regular expressions.
    // TODO: have the tool return an error status.  Requires fixing the ICU data build
    //       so that it doesn't abort entirely on that error.

    UNewDataMemory *pData;
    char msg[1024];

    /* write message with just the name */
    sprintf(msg, "gencfu writes dummy %s because of UCONFIG_NO_REGULAR_EXPRESSIONS and/or UCONFIG_NO_NORMALIZATION and/or UCONFIG_NO_FILE_IO, see uconfig.h", outFileName);
    fprintf(stderr, "%s\n", msg);

    /* write the dummy data file */
    pData = udata_create(outDir, NULL, outFileName, &dummyDataInfo, NULL, &status);
    udata_writeBlock(pData, msg, strlen(msg));
    udata_finish(pData, &status);
    return (int)status;

#else
    /* Initialize ICU */
    u_init(&status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "%s: can not initialize ICU.  status = %s\n",
            argv[0], u_errorName(status));
        exit(1);
    }
    status = U_ZERO_ERROR;

    //  Read in the confusables source file

    int32_t      confusablesLen = 0;
    const char  *confusables = readFile(confFileName, &confusablesLen);
    if (confusables == NULL) {
        printf("gencfu: error reading file  \"%s\"\n", confFileName);
        exit(-1);
    }

    int32_t     wsConfusablesLen = 0;
    const char *wsConfsables =  readFile(confWSFileName, &wsConfusablesLen);
    if (wsConfsables == NULL) {
        printf("gencfu: error reading file  \"%s\"\n", confFileName);
        exit(-1);
    }

    //
    //  Create the Spoof Detector from the source confusables files.
    //     This will compile the data.
    //
    UParseError parseError;
    parseError.line = 0;
    parseError.offset = 0;
    int32_t errType;
    USpoofChecker *sc = uspoof_openFromSource(confusables, confusablesLen,
                                              wsConfsables, wsConfusablesLen,
                                              &errType, &parseError, &status);
    if (U_FAILURE(status)) {
        const char *errFile = 
            (errType == USPOOF_WHOLE_SCRIPT_CONFUSABLE)? confWSFileName : confFileName;
        fprintf(stderr, "gencfu: uspoof_openFromSource error \"%s\"  at file %s, line %d, column %d\n",
                u_errorName(status), errFile, (int)parseError.line, (int)parseError.offset);
        exit(status);
    };


    //
    //  Get the compiled rule data from the USpoofChecker.
    //
    uint32_t        outDataSize;
    uint8_t        *outData;
    outDataSize = uspoof_serialize(sc, NULL, 0, &status);
    if (status != U_BUFFER_OVERFLOW_ERROR) {
        fprintf(stderr, "gencfu: uspoof_serialize() returned %s\n", u_errorName(status));
        exit(status);
    }
    status = U_ZERO_ERROR;
    outData = new uint8_t[outDataSize];
    uspoof_serialize(sc, outData, outDataSize, &status);

    // Copy the data format version numbers from the spoof data header into the UDataMemory header.
    
    uprv_memcpy(dh.info.formatVersion, 
                reinterpret_cast<SpoofDataHeader *>(outData)->fFormatVersion,
                sizeof(dh.info.formatVersion));

    //
    //  Create the output file
    //
    size_t bytesWritten;
    UNewDataMemory *pData;
    pData = udata_create(outDir, NULL, outFileName, &(dh.info), copyright, &status);
    if(U_FAILURE(status)) {
        fprintf(stderr, "gencfu: Could not open output file \"%s\", \"%s\"\n", 
                         outFileName, u_errorName(status));
        exit(status);
    }


    //  Write the data itself.
    udata_writeBlock(pData, outData, outDataSize);
    // finish up 
    bytesWritten = udata_finish(pData, &status);
    if(U_FAILURE(status)) {
        fprintf(stderr, "gencfu: Error %d writing the output file\n", status);
        exit(status);
    }
    
    if (bytesWritten != outDataSize) {
        fprintf(stderr, "gencfu: Error writing to output file \"%s\"\n", outFileName);
        exit(-1);
    }

    uspoof_close(sc);
    delete [] outData;
    delete [] confusables;
    delete [] wsConfsables;
    u_cleanup();
    printf("gencfu: tool completed successfully.\n");
    return 0;
#endif   // UCONFIG_NO_REGULAR_EXPRESSIONS
}