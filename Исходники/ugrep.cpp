//------------------------------------------------------------------------------------------
//
//   main          for ugrep
//
//           Structurally, all use of the ICU Regular Expression API is in main(),
//           and all of the supporting stuff necessary to make a running program, but
//           not directly related to regular expressions, is factored out into these other
//           functions.
//
//------------------------------------------------------------------------------------------
int main(int argc, const char** argv) {
    UBool     matchFound = FALSE;

    //
    //  Process the commmand line options.
    //
    processOptions(argc, argv);

    //
    // Create a RegexPattern object from the user supplied pattern string.
    //
    UErrorCode status = U_ZERO_ERROR;   // All ICU operations report success or failure
                                        //   in a status variable.

    UParseError    parseErr;            // In the event of a syntax error in the regex pattern,
                                        //   this struct will contain the position of the
                                        //   error.

    RegexPattern  *rePat = RegexPattern::compile(pattern, parseErr, status);
                                        // Note that C++ is doing an automatic conversion
                                        //  of the (char *) pattern to a temporary
                                        //  UnicodeString object.
    if (U_FAILURE(status)) {
        fprintf(stderr, "ugrep:  error in pattern: \"%s\" at position %d\n",
            u_errorName(status), parseErr.offset);
        exit(-1);
    }

    //
    // Create a RegexMatcher from the newly created pattern.
    //
    UnicodeString empty;
    RegexMatcher *matcher = rePat->matcher(empty, status);
    if (U_FAILURE(status)) {
        fprintf(stderr, "ugrep:  error in creating RegexMatcher: \"%s\"\n",
            u_errorName(status));
        exit(-1);
    }

    //
    // Loop, processing each of the input files.
    //
    for (int fileNum=firstFileNum; fileNum < argc; fileNum++) {
        readFile(argv[fileNum]);

        //
        //  Loop through the lines of a file, trying to match the regex pattern on each.
        //
        for (nextLine(0); lineStart<fileLen; nextLine(lineEnd)) {
            UnicodeString s(FALSE, ucharBuf+lineStart, lineEnd-lineStart);
            matcher->reset(s);
            if (matcher->find()) {
                matchFound = TRUE;
                printMatch();
            }
        }
    }

    //
    //  Clean up
    //
    delete matcher;
    delete rePat;
    free(ucharBuf);
    free(charBuf);
    ucnv_close(outConverter);
    
    u_cleanup();       // shut down ICU, release any cached data it owns.

    return matchFound? 0: 1;
}