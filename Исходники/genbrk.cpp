//----------------------------------------------------------------------------
//
//  main      for genbrk
//
//----------------------------------------------------------------------------
int  main(int argc, char **argv) {
    UErrorCode  status = U_ZERO_ERROR;
    const char *ruleFileName;
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

    if (!(options[3].doesOccur && options[4].doesOccur)) {
        fprintf(stderr, "rule file and output file must both be specified.\n");
        usageAndDie(U_ILLEGAL_ARGUMENT_ERROR);
    }
    ruleFileName = options[3].value;
    outFileName  = options[4].value;

    if (options[5].doesOccur) {
        u_setDataDirectory(options[5].value);
    }

    /* Initialize ICU */
    u_init(&status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "%s: can not initialize ICU.  status = %s\n",
            argv[0], u_errorName(status));
        exit(1);
    }
    status = U_ZERO_ERROR;

    /* Combine the directory with the file name */
    if(options[6].doesOccur) {
        outDir = options[6].value;
    }
    if (options[7].doesOccur) {
        copyright = U_COPYRIGHT_STRING;
    }

#if UCONFIG_NO_BREAK_ITERATION

    UNewDataMemory *pData;
    char msg[1024];

    /* write message with just the name */
    sprintf(msg, "genbrk writes dummy %s because of UCONFIG_NO_BREAK_ITERATION, see uconfig.h", outFileName);
    fprintf(stderr, "%s\n", msg);

    /* write the dummy data file */
    pData = udata_create(outDir, NULL, outFileName, &dummyDataInfo, NULL, &status);
    udata_writeBlock(pData, msg, strlen(msg));
    udata_finish(pData, &status);
    return (int)status;

#else

    //
    //  Read in the rule source file
    //
    long        result;
    long        ruleFileSize;
    FILE        *file;
    char        *ruleBufferC;

    file = fopen(ruleFileName, "rb");
    if( file == 0 ) {
        fprintf(stderr, "Could not open file \"%s\"\n", ruleFileName);
        exit(-1);
    }
    fseek(file, 0, SEEK_END);
    ruleFileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    ruleBufferC = new char[ruleFileSize+10];

    result = (long)fread(ruleBufferC, 1, ruleFileSize, file);
    if (result != ruleFileSize)  {
        fprintf(stderr, "Error reading file \"%s\"\n", ruleFileName);
        exit (-1);
    }
    ruleBufferC[ruleFileSize]=0;
    fclose(file);

    //
    // Look for a Unicode Signature (BOM) on the rule file
    //
    int32_t        signatureLength;
    const char *   ruleSourceC = ruleBufferC;
    const char*    encoding = ucnv_detectUnicodeSignature(
                           ruleSourceC, ruleFileSize, &signatureLength, &status);
    if (U_FAILURE(status)) {
        exit(status);
    }
    if(encoding!=NULL ){
        ruleSourceC  += signatureLength;
        ruleFileSize -= signatureLength;
    }

    //
    // Open a converter to take the rule file to UTF-16
    //
    UConverter* conv;
    conv = ucnv_open(encoding, &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "ucnv_open: ICU Error \"%s\"\n", u_errorName(status));
        exit(status);
    }

    //
    // Convert the rules to UChar.
    //  Preflight first to determine required buffer size.
    //
    uint32_t destCap = ucnv_toUChars(conv,
                       NULL,           //  dest,
                       0,              //  destCapacity,
                       ruleSourceC,
                       ruleFileSize,
                       &status);
    if (status != U_BUFFER_OVERFLOW_ERROR) {
        fprintf(stderr, "ucnv_toUChars: ICU Error \"%s\"\n", u_errorName(status));
        exit(status);
    };

    status = U_ZERO_ERROR;
    UChar *ruleSourceU = new UChar[destCap+1];
    ucnv_toUChars(conv,
                  ruleSourceU,     //  dest,
                  destCap+1,
                  ruleSourceC,
                  ruleFileSize,
                  &status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "ucnv_toUChars: ICU Error \"%s\"\n", u_errorName(status));
        exit(status);
    };
    ucnv_close(conv);


    //
    //  Put the source rules into a UnicodeString
    //
    UnicodeString ruleSourceS(FALSE, ruleSourceU, destCap);

    //
    //  Create the break iterator from the rules
    //     This will compile the rules.
    //
    UParseError parseError;
    parseError.line = 0;
    parseError.offset = 0;
    RuleBasedBreakIterator *bi = new RuleBasedBreakIterator(ruleSourceS, parseError, status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "createRuleBasedBreakIterator: ICU Error \"%s\"  at line %d, column %d\n",
                u_errorName(status), (int)parseError.line, (int)parseError.offset);
        exit(status);
    };


    //
    //  Get the compiled rule data from the break iterator.
    //
    uint32_t        outDataSize;
    const uint8_t  *outData;
    outData = bi->getBinaryRules(outDataSize);

    // Copy the data format version numbers from the RBBI data header into the UDataMemory header.
    uprv_memcpy(dh.info.formatVersion, ((RBBIDataHeader *)outData)->fFormatVersion, sizeof(dh.info.formatVersion));

    //
    //  Create the output file
    //
    size_t bytesWritten;
    UNewDataMemory *pData;
    pData = udata_create(outDir, NULL, outFileName, &(dh.info), copyright, &status);
    if(U_FAILURE(status)) {
        fprintf(stderr, "genbrk: Could not open output file \"%s\", \"%s\"\n", 
                         outFileName, u_errorName(status));
        exit(status);
    }


    //  Write the data itself.
    udata_writeBlock(pData, outData, outDataSize);
    // finish up 
    bytesWritten = udata_finish(pData, &status);
    if(U_FAILURE(status)) {
        fprintf(stderr, "genbrk: error %d writing the output file\n", status);
        exit(status);
    }
    
    if (bytesWritten != outDataSize) {
        fprintf(stderr, "Error writing to output file \"%s\"\n", outFileName);
        exit(-1);
    }

    delete bi;
    delete[] ruleSourceU;
    delete[] ruleBufferC;
    u_cleanup();


    printf("genbrk: tool completed successfully.\n");
    return 0;

#endif /* #if !UCONFIG_NO_BREAK_ITERATION */
}