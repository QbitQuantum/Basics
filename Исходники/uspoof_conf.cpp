void ConfusabledataBuilder::build(const char * confusables, int32_t confusablesLen,
               UErrorCode &status) {

    // Convert the user input data from UTF-8 to UChar (UTF-16)
    int32_t inputLen = 0;
    if (U_FAILURE(status)) {
        return;
    }
    u_strFromUTF8(NULL, 0, &inputLen, confusables, confusablesLen, &status);
    if (status != U_BUFFER_OVERFLOW_ERROR) {
        return;
    }
    status = U_ZERO_ERROR;
    fInput = static_cast<UChar *>(uprv_malloc((inputLen+1) * sizeof(UChar)));
    if (fInput == NULL) {
        status = U_MEMORY_ALLOCATION_ERROR;
        return;
    }
    u_strFromUTF8(fInput, inputLen+1, NULL, confusables, confusablesLen, &status);


    // Regular Expression to parse a line from Confusables.txt.  The expression will match
    // any line.  What was matched is determined by examining which capture groups have a match.
    //   Capture Group 1:  the source char
    //   Capture Group 2:  the replacement chars
    //   Capture Group 3-6  the table type, SL, SA, ML, or MA (deprecated)
    //   Capture Group 7:  A blank or comment only line.
    //   Capture Group 8:  A syntactically invalid line.  Anything that didn't match before.
    // Example Line from the confusables.txt source file:
    //   "1D702 ;	006E 0329 ;	SL	# MATHEMATICAL ITALIC SMALL ETA ... "
    UnicodeString pattern(
        "(?m)^[ \\t]*([0-9A-Fa-f]+)[ \\t]+;"      // Match the source char
        "[ \\t]*([0-9A-Fa-f]+"                    // Match the replacement char(s)
           "(?:[ \\t]+[0-9A-Fa-f]+)*)[ \\t]*;"    //     (continued)
        "\\s*(?:(SL)|(SA)|(ML)|(MA))"             // Match the table type
        "[ \\t]*(?:#.*?)?$"                       // Match any trailing #comment
        "|^([ \\t]*(?:#.*?)?)$"       // OR match empty lines or lines with only a #comment
        "|^(.*?)$", -1, US_INV);      // OR match any line, which catches illegal lines.
    // TODO: Why are we using the regex C API here? C++ would just take UnicodeString...
    fParseLine = uregex_open(pattern.getBuffer(), pattern.length(), 0, NULL, &status);

    // Regular expression for parsing a hex number out of a space-separated list of them.
    //   Capture group 1 gets the number, with spaces removed.
    pattern = UNICODE_STRING_SIMPLE("\\s*([0-9A-F]+)");
    fParseHexNum = uregex_open(pattern.getBuffer(), pattern.length(), 0, NULL, &status);

    // Zap any Byte Order Mark at the start of input.  Changing it to a space is benign
    //   given the syntax of the input.
    if (*fInput == 0xfeff) {
        *fInput = 0x20;
    }

    // Parse the input, one line per iteration of this loop.
    uregex_setText(fParseLine, fInput, inputLen, &status);
    while (uregex_findNext(fParseLine, &status)) {
        fLineNum++;
        if (uregex_start(fParseLine, 7, &status) >= 0) {
            // this was a blank or comment line.
            continue;
        }
        if (uregex_start(fParseLine, 8, &status) >= 0) {
            // input file syntax error.
            status = U_PARSE_ERROR;
            return;
        }

        // We have a good input line.  Extract the key character and mapping string, and
        //    put them into the appropriate mapping table.
        UChar32 keyChar = SpoofImpl::ScanHex(fInput, uregex_start(fParseLine, 1, &status),
                          uregex_end(fParseLine, 1, &status), status);

        int32_t mapStringStart = uregex_start(fParseLine, 2, &status);
        int32_t mapStringLength = uregex_end(fParseLine, 2, &status) - mapStringStart;
        uregex_setText(fParseHexNum, &fInput[mapStringStart], mapStringLength, &status);

        UnicodeString  *mapString = new UnicodeString();
        if (mapString == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return;
        }
        while (uregex_findNext(fParseHexNum, &status)) {
            UChar32 c = SpoofImpl::ScanHex(&fInput[mapStringStart], uregex_start(fParseHexNum, 1, &status),
                                 uregex_end(fParseHexNum, 1, &status), status);
            mapString->append(c);
        }
        U_ASSERT(mapString->length() >= 1);

        // Put the map (value) string into the string pool
        // This a little like a Java intern() - any duplicates will be eliminated.
        SPUString *smapString = stringPool->addString(mapString, status);

        // Add the UChar32 -> string mapping to the table.
        // For Unicode 8, the SL, SA and ML tables have been discontinued.
        //                All input data from confusables.txt is tagged MA.
        uhash_iput(fTable, keyChar, smapString, &status);
        if (U_FAILURE(status)) { return; }
        fKeySet->add(keyChar);
    }

    // Input data is now all parsed and collected.
    // Now create the run-time binary form of the data.
    //
    // This is done in two steps.  First the data is assembled into vectors and strings,
    //   for ease of construction, then the contents of these collections are dumped
    //   into the actual raw-bytes data storage.

    // Build up the string array, and record the index of each string therein
    //  in the (build time only) string pool.
    // Strings of length one are not entered into the strings array.
    // (Strings in the table are sorted by length)
    stringPool->sort(status);
    fStringTable = new UnicodeString();
    int32_t poolSize = stringPool->size();
    int32_t i;
    for (i=0; i<poolSize; i++) {
        SPUString *s = stringPool->getByIndex(i);
        int32_t strLen = s->fStr->length();
        int32_t strIndex = fStringTable->length();
        if (strLen == 1) {
            // strings of length one do not get an entry in the string table.
            // Keep the single string character itself here, which is the same
            //  convention that is used in the final run-time string table index.
            s->fCharOrStrTableIndex = s->fStr->charAt(0);
        } else {
            s->fCharOrStrTableIndex = strIndex;
            fStringTable->append(*(s->fStr));
        }
    }

    // Construct the compile-time Key and Value tables
    //
    // For each key code point, check which mapping tables it applies to,
    //   and create the final data for the key & value structures.
    //
    //   The four logical mapping tables are conflated into one combined table.
    //   If multiple logical tables have the same mapping for some key, they
    //     share a single entry in the combined table.
    //   If more than one mapping exists for the same key code point, multiple
    //     entries will be created in the table

    for (int32_t range=0; range<fKeySet->getRangeCount(); range++) {
        // It is an oddity of the UnicodeSet API that simply enumerating the contained
        //   code points requires a nested loop.
        for (UChar32 keyChar=fKeySet->getRangeStart(range);
                keyChar <= fKeySet->getRangeEnd(range); keyChar++) {
            SPUString *targetMapping = static_cast<SPUString *>(uhash_iget(fTable, keyChar));
            U_ASSERT(targetMapping != NULL);

            // Set an error code if trying to consume a long string.  Otherwise,
            // codePointAndLengthToKey will abort on a U_ASSERT.
            if (targetMapping->fStr->length() > 256) {
                status = U_ILLEGAL_ARGUMENT_ERROR;
                return;
            }

            int32_t key = ConfusableDataUtils::codePointAndLengthToKey(keyChar,
                targetMapping->fStr->length());
            int32_t value = targetMapping->fCharOrStrTableIndex;

            fKeyVec->addElement(key, status);
            fValueVec->addElement(value, status);
        }
    }

    // Put the assembled data into the flat runtime array
    outputData(status);

    // All of the intermediate allocated data belongs to the ConfusabledataBuilder
    //  object  (this), and is deleted in the destructor.
    return;
}