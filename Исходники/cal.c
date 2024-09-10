static void get_symbols(const UDateFormat *fmt,
                        UDateFormatSymbolType type,
                        UChar *array[],
                        int32_t arrayLength,
                        int32_t lowestIndex,
                        int32_t firstIndex,
                        UErrorCode *status)
{
    int32_t count, i;

    if (U_FAILURE(*status)) {
        return;
    }

    count = udat_countSymbols(fmt, type);

    if(count != arrayLength + lowestIndex) {
        return;
    }

    for(i = 0; i < arrayLength; i++) {
        int32_t idx = (i + firstIndex) % arrayLength;
        int32_t size = 1 + udat_getSymbols(fmt, type, idx + lowestIndex, NULL, 0, status);

        array[idx] = (UChar *) malloc(sizeof(UChar) * size);

        *status = U_ZERO_ERROR;
        udat_getSymbols(fmt, type, idx + lowestIndex, array[idx], size, status);
    }
}