int32_t SSearchTest::monkeyTestCase(UCollator *coll, const UnicodeString &testCase, const UnicodeString &pattern, const UnicodeString &altPattern,
                                    const char *name, const char *strength, uint32_t seed)
{
    UErrorCode status = U_ZERO_ERROR;
    int32_t actualStart = -1, actualEnd = -1;
  //int32_t expectedStart = prefix.length(), expectedEnd = prefix.length() + altPattern.length();
    int32_t expectedStart = -1, expectedEnd = -1;
    int32_t notFoundCount = 0;
    LocalUStringSearchPointer uss(usearch_openFromCollator(pattern.getBuffer(), pattern.length(),
                                                           testCase.getBuffer(), testCase.length(),
                                                           coll,
                                                           NULL,     // the break iterator
                                                           &status));

    // **** TODO: find *all* matches, not just first one ****
    simpleSearch(coll, testCase, 0, pattern, expectedStart, expectedEnd);

    usearch_search(uss.getAlias(), 0, &actualStart, &actualEnd, &status);

    if (expectedStart >= 0 && (actualStart != expectedStart || actualEnd != expectedEnd)) {
        errln("Search for <pattern> in <%s> failed: expected [%d, %d], got [%d, %d]\n"
              "    strength=%s seed=%d",
              name, expectedStart, expectedEnd, actualStart, actualEnd, strength, seed);
    }

    if (expectedStart == -1 && actualStart == -1) {
        notFoundCount += 1;
    }

    // **** TODO: find *all* matches, not just first one ****
    simpleSearch(coll, testCase, 0, altPattern, expectedStart, expectedEnd);

    usearch_setPattern(uss.getAlias(), altPattern.getBuffer(), altPattern.length(), &status);

    usearch_search(uss.getAlias(), 0, &actualStart, &actualEnd, &status);

    if (expectedStart >= 0 && (actualStart != expectedStart || actualEnd != expectedEnd)) {
        errln("Search for <alt_pattern> in <%s> failed: expected [%d, %d], got [%d, %d]\n"
              "    strength=%s seed=%d",
              name, expectedStart, expectedEnd, actualStart, actualEnd, strength, seed);
    }

    if (expectedStart == -1 && actualStart == -1) {
        notFoundCount += 1;
    }

    return notFoundCount;
}