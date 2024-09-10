extern int
testData(TestIDNA& test) {
    char *basename=NULL;
    UErrorCode errorCode=U_ZERO_ERROR;
    char *saveBasename =NULL;

    profile = usprep_openByType(USPREP_RFC3491_NAMEPREP, &errorCode);
    if(U_FAILURE(errorCode)){
        test.errcheckln(errorCode, "Failed to load IDNA data file. " + UnicodeString(u_errorName(errorCode)));
        return errorCode;
    }
    
    char* filename = (char*) malloc(strlen(IntlTest::pathToDataDirectory())*1024);
    //TODO get the srcDir dynamically 
    const char *srcDir=IntlTest::pathToDataDirectory();

    idnTrie     = &profile->sprepTrie;
    indexes     = profile->indexes;
    mappingData = profile->mappingData;

    //initialize
    pTestIDNA = &test;
    
    /* prepare the filename beginning with the source dir */
    if(uprv_strchr(srcDir,U_FILE_SEP_CHAR) == NULL){
        filename[0] = 0x2E;
        filename[1] = U_FILE_SEP_CHAR;
        uprv_strcpy(filename+2,srcDir);
    }else{
        uprv_strcpy(filename, srcDir);
    }
    basename=filename+uprv_strlen(filename);
    if(basename>filename && *(basename-1)!=U_FILE_SEP_CHAR) {
        *basename++=U_FILE_SEP_CHAR;
    }

    /* process unassigned */
    basename=filename+uprv_strlen(filename);
    if(basename>filename && *(basename-1)!=U_FILE_SEP_CHAR) {
        *basename++=U_FILE_SEP_CHAR;
    }
    
    /* first copy misc directory */
    saveBasename = basename;
    uprv_strcpy(basename,SPREP_DIR);
    basename = basename + uprv_strlen(SPREP_DIR);
    *basename++=U_FILE_SEP_CHAR;
    
    /* process unassigned */
    uprv_strcpy(basename,fileNames[0]);
    parseMappings(filename,TRUE, test,&errorCode);
    if(U_FAILURE(errorCode)) {
        test.errln( "Could not open file %s for reading \n", filename);
        return errorCode;
    }

    testAllCodepoints(test);

    usprep_close(profile);
    pTestIDNA = NULL;
    free(filename);
    return errorCode;
}