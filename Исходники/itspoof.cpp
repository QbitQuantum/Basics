//  testConfData - Check each data item from the Unicode confusables.txt file,
//                 verify that it transforms correctly in a skeleton.
//
void IntlTestSpoof::testConfData() {
    UErrorCode status = U_ZERO_ERROR;

    const char *testDataDir = IntlTest::getSourceTestData(status);
    TEST_ASSERT_SUCCESS(status);
    char buffer[2000];
    uprv_strcpy(buffer, testDataDir);
    uprv_strcat(buffer, "confusables.txt");

    LocalStdioFilePointer f(fopen(buffer, "rb"));
    if (f.isNull()) {
        errln("Skipping test spoof/testConfData.  File confusables.txt not accessible.");
        return;
    }
    fseek(f.getAlias(), 0, SEEK_END);
    int32_t  fileSize = ftell(f.getAlias());
    LocalArray<char> fileBuf(new char[fileSize]);
    fseek(f.getAlias(), 0, SEEK_SET);
    int32_t amt_read = fread(fileBuf.getAlias(), 1, fileSize, f.getAlias());
    TEST_ASSERT_EQ(amt_read, fileSize);
    TEST_ASSERT(fileSize>0);
    if (amt_read != fileSize || fileSize <=0) {
        return;
    }
    UnicodeString confusablesTxt = UnicodeString::fromUTF8(StringPiece(fileBuf.getAlias(), fileSize));

    LocalUSpoofCheckerPointer sc(uspoof_open(&status));
    TEST_ASSERT_SUCCESS(status);

    // Parse lines from the confusables.txt file.  Example Line:
    // FF44 ;	0064 ;	SL	# ( d -> d ) FULLWIDTH ....
    // Three fields.  The hex fields can contain more than one character,
    //                and each character may be more than 4 digits (for supplemntals)
    // This regular expression matches lines and splits the fields into capture groups.
    RegexMatcher parseLine("(?m)^([0-9A-F]{4}[^#;]*?);([^#;]*?);([^#]*)", confusablesTxt, 0, status);
    TEST_ASSERT_SUCCESS(status);
    while (parseLine.find()) {
        UnicodeString from = parseHex(parseLine.group(1, status));
        if (!Normalizer::isNormalized(from, UNORM_NFD, status)) {
            // The source character was not NFD.
            // Skip this case; the first step in obtaining a skeleton is to NFD the input,
            //  so the mapping in this line of confusables.txt will never be applied.
            continue;
        }

        UnicodeString rawExpected = parseHex(parseLine.group(2, status));
        UnicodeString expected;
        Normalizer::decompose(rawExpected, FALSE /*NFD*/, 0, expected, status);
        TEST_ASSERT_SUCCESS(status);

        int32_t skeletonType = 0;
        UnicodeString tableType = parseLine.group(3, status);
        TEST_ASSERT_SUCCESS(status);
        if (tableType.indexOf("SL") >= 0) {
            skeletonType = USPOOF_SINGLE_SCRIPT_CONFUSABLE;
        } else if (tableType.indexOf("SA") >= 0) {
            skeletonType = USPOOF_SINGLE_SCRIPT_CONFUSABLE | USPOOF_ANY_CASE;
        } else if (tableType.indexOf("ML") >= 0) {
            skeletonType = 0;
        } else if (tableType.indexOf("MA") >= 0) {
            skeletonType = USPOOF_ANY_CASE;
        }

        UnicodeString actual;
        uspoof_getSkeletonUnicodeString(sc.getAlias(), skeletonType, from, actual, &status);
        TEST_ASSERT_SUCCESS(status);
        TEST_ASSERT(actual == expected);
        if (actual != expected) {
            errln(parseLine.group(0, status));
            UnicodeString line = "Actual: ";
            int i = 0;
            while (i < actual.length()) {
                appendHexUChar(line, actual.char32At(i));
                i = actual.moveIndex32(i, 1);
            }
            errln(line);
        }
        if (U_FAILURE(status)) {
            break;
        }
    }
}