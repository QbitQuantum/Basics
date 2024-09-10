static bool getDayIntVector(JNIEnv* env, UResourceBundle* gregorian, int* values) {
    // get the First day of week and the minimal days in first week numbers
    UErrorCode status = U_ZERO_ERROR;
    ScopedResourceBundle gregorianElems(ures_getByKey(gregorian, "DateTimeElements", NULL, &status));
    if (U_FAILURE(status)) {
        return false;
    }

    int intVectSize;
    const int* result = ures_getIntVector(gregorianElems.get(), &intVectSize, &status);
    if (U_FAILURE(status) || intVectSize != 2) {
        return false;
    }

    values[0] = result[0];
    values[1] = result[1];
    return true;
}