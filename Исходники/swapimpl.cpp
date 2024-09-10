U_CAPI int32_t U_EXPORT2
udata_swap(const UDataSwapper *ds,
           const void *inData, int32_t length, void *outData,
           UErrorCode *pErrorCode) {
    char dataFormatChars[4];
    const UDataInfo *pInfo;
    int32_t i, swappedLength;

    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return 0;
    }

    /*
     * Preflight the header first; checks for illegal arguments, too.
     * Do not swap the header right away because the format-specific swapper
     * will swap it, get the headerSize again, and also use the header
     * information. Otherwise we would have to pass some of the information
     * and not be able to use the UDataSwapFn signature.
     */
    udata_swapDataHeader(ds, inData, -1, NULL, pErrorCode);

    /*
     * If we wanted udata_swap() to also handle non-loadable data like a UTrie,
     * then we could check here for further known magic values and structures.
     */
    if(U_FAILURE(*pErrorCode)) {
        return 0; /* the data format was not recognized */
    }

    pInfo=(const UDataInfo *)((const char *)inData+4);

    {
        /* convert the data format from ASCII to Unicode to the system charset */
        UChar u[4]={
             pInfo->dataFormat[0], pInfo->dataFormat[1],
             pInfo->dataFormat[2], pInfo->dataFormat[3]
        };

        if(uprv_isInvariantUString(u, 4)) {
            u_UCharsToChars(u, dataFormatChars, 4);
        } else {
            dataFormatChars[0]=dataFormatChars[1]=dataFormatChars[2]=dataFormatChars[3]='?';
        }
    }

    /* dispatch to the swap function for the dataFormat */
    for(i=0; i<UPRV_LENGTHOF(swapFns); ++i) {
        if(0==memcmp(swapFns[i].dataFormat, pInfo->dataFormat, 4)) {
            swappedLength=swapFns[i].swapFn(ds, inData, length, outData, pErrorCode);

            if(U_FAILURE(*pErrorCode)) {
                udata_printError(ds, "udata_swap(): failure swapping data format %02x.%02x.%02x.%02x (\"%c%c%c%c\") - %s\n",
                                 pInfo->dataFormat[0], pInfo->dataFormat[1],
                                 pInfo->dataFormat[2], pInfo->dataFormat[3],
                                 dataFormatChars[0], dataFormatChars[1],
                                 dataFormatChars[2], dataFormatChars[3],
                                 u_errorName(*pErrorCode));
            } else if(swappedLength<(length-15)) {
                /* swapped less than expected */
                udata_printError(ds, "udata_swap() warning: swapped only %d out of %d bytes - data format %02x.%02x.%02x.%02x (\"%c%c%c%c\")\n",
                                 swappedLength, length,
                                 pInfo->dataFormat[0], pInfo->dataFormat[1],
                                 pInfo->dataFormat[2], pInfo->dataFormat[3],
                                 dataFormatChars[0], dataFormatChars[1],
                                 dataFormatChars[2], dataFormatChars[3],
                                 u_errorName(*pErrorCode));
            }

            return swappedLength;
        }
    }

    /* the dataFormat was not recognized */
    udata_printError(ds, "udata_swap(): unknown data format %02x.%02x.%02x.%02x (\"%c%c%c%c\")\n",
                     pInfo->dataFormat[0], pInfo->dataFormat[1],
                     pInfo->dataFormat[2], pInfo->dataFormat[3],
                     dataFormatChars[0], dataFormatChars[1],
                     dataFormatChars[2], dataFormatChars[3]);

    *pErrorCode=U_UNSUPPORTED_ERROR;
    return 0;
}