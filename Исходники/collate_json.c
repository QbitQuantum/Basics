static int compareUnicodeSlow(const char* str1, size_t len1,
                              const char* str2, size_t len2)
{
    static UCollator* coll = NULL;
    UCharIterator iterA, iterB;
    int result;

    UErrorCode status = U_ZERO_ERROR;
    if (!coll) {
        coll = ucol_open("", &status);
        if (U_FAILURE(status)) {
            fprintf(stderr, "CouchStore CollateJSON: Couldn't initialize ICU (%d)\n", (int)status);
            return -1;
        }
    }

    uiter_setUTF8(&iterA, str1, (int)len1);
    uiter_setUTF8(&iterB, str2, (int)len2);

    result = ucol_strcollIter(coll, &iterA, &iterB, &status);

    if (U_FAILURE(status)) {
        fprintf(stderr, "CouchStore CollateJSON: ICU error %d\n", (int)status);
        return -1;
    }

    if (result < 0) {
        return -1;
    } else if (result > 0) {
        return 1;
    }

    return 0;
}