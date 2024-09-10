//-------------------------------------------------------------------------------
//      
//  Read a text data file, convert it from UTF-8 to UChars, and return the data
//    in one big UChar * buffer, which the caller must delete.
//
//    (Lightly modified version of a similar function in regextst.cpp)
//
//--------------------------------------------------------------------------------
UChar *DecimalFormatTest::ReadAndConvertFile(const char *fileName, int32_t &ulen,
                                     UErrorCode &status) {
    UChar       *retPtr  = NULL;
    char        *fileBuf = NULL;
    const char  *fileBufNoBOM = NULL;
    FILE        *f       = NULL;

    ulen = 0;
    if (U_FAILURE(status)) {
        return retPtr;
    }

    //
    //  Open the file.
    //
    f = fopen(fileName, "rb");
    if (f == 0) {
        dataerrln("Error opening test data file %s\n", fileName);
        status = U_FILE_ACCESS_ERROR;
        return NULL;
    }
    //
    //  Read it in
    //
    int32_t            fileSize;
    int32_t            amtRead;
    int32_t            amtReadNoBOM;

    fseek( f, 0, SEEK_END);
    fileSize = ftell(f);
    fileBuf = new char[fileSize];
    fseek(f, 0, SEEK_SET);
    amtRead = fread(fileBuf, 1, fileSize, f);
    if (amtRead != fileSize || fileSize <= 0) {
        errln("Error reading test data file.");
        goto cleanUpAndReturn;
    }

    //
    // Look for a UTF-8 BOM on the data just read.
    //    The test data file is UTF-8.
    //    The BOM needs to be there in the source file to keep the Windows & 
    //    EBCDIC machines happy, so force an error if it goes missing.  
    //    Many Linux editors will silently strip it.
    //
    fileBufNoBOM = fileBuf + 3;
    amtReadNoBOM = amtRead - 3;
    if (fileSize<3 || uprv_strncmp(fileBuf, "\xEF\xBB\xBF", 3) != 0) {
        // TODO:  restore this check.
        errln("Test data file %s is missing its BOM", fileName);
        fileBufNoBOM = fileBuf;
        amtReadNoBOM = amtRead;
    }

    //
    // Find the length of the input in UTF-16 UChars
    //  (by preflighting the conversion)
    //
    u_strFromUTF8(NULL, 0, &ulen, fileBufNoBOM, amtReadNoBOM, &status);

    //
    // Convert file contents from UTF-8 to UTF-16
    //
    if (status == U_BUFFER_OVERFLOW_ERROR) {
        // Buffer Overflow is expected from the preflight operation.
        status = U_ZERO_ERROR;
        retPtr = new UChar[ulen+1];
        u_strFromUTF8(retPtr, ulen+1, NULL, fileBufNoBOM, amtReadNoBOM, &status);
    }

cleanUpAndReturn:
    fclose(f);
    delete[] fileBuf;
    if (U_FAILURE(status)) {
        errln("ICU Error \"%s\"\n", u_errorName(status));
        delete retPtr;
        retPtr = NULL;
    };
    return retPtr;
}