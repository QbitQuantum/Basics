static void TestSearchCollatorElements(void)
{
    const TSCEItem * tsceItemPtr;
    for (tsceItemPtr = tsceItems; tsceItemPtr->locale != NULL; tsceItemPtr++) {
        UErrorCode status = U_ZERO_ERROR;
        UCollator* ucol = ucol_open(tsceItemPtr->locale, &status);
        if ( U_SUCCESS(status) ) {
            UCollationElements * uce = ucol_openElements(ucol, tsceText, kLen_tsceText, &status);
            if ( U_SUCCESS(status) ) {
                int32_t offset, element;
                const int32_t * nextOffsetPtr;
                const int32_t * limitOffsetPtr;

                nextOffsetPtr = tsceItemPtr->offsets;
                limitOffsetPtr = tsceItemPtr->offsets + tsceItemPtr->offsetsLen;
                do {
                    offset = ucol_getOffset(uce);
                    element = ucol_next(uce, &status);
                    log_verbose("(%s) offset=%2d  ce=%08x\n", tsceItemPtr->locale, offset, element);
                    if ( element == 0 ) {
                        log_err("error, locale %s, ucol_next returned element 0\n", tsceItemPtr->locale );
                    }
                    if ( nextOffsetPtr < limitOffsetPtr ) {
                        if (offset != *nextOffsetPtr) {
                            log_err("error, locale %s, expected ucol_next -> ucol_getOffset %d, got %d\n",
                                                            tsceItemPtr->locale, *nextOffsetPtr, offset );
                            nextOffsetPtr = limitOffsetPtr;
                            break;
                        }
                        nextOffsetPtr++;
                    } else {
                        log_err("error, locale %s, ucol_next returned more elements than expected\n", tsceItemPtr->locale );
                    }
                } while ( U_SUCCESS(status) && element != UCOL_NULLORDER );
                if ( nextOffsetPtr < limitOffsetPtr ) {
                    log_err("error, locale %s, ucol_next returned fewer elements than expected\n", tsceItemPtr->locale );
                }

                ucol_setOffset(uce, kLen_tsceText, &status);
                status = U_ZERO_ERROR;
                nextOffsetPtr = tsceItemPtr->offsets + tsceItemPtr->offsetsLen;
                limitOffsetPtr = tsceItemPtr->offsets;
                do {
                    offset = ucol_getOffset(uce);
                    element = ucol_previous(uce, &status);
                    if ( element == 0 ) {
                        log_err("error, locale %s, ucol_previous returned element 0\n", tsceItemPtr->locale );
                    }
                    if ( nextOffsetPtr > limitOffsetPtr ) {
                        nextOffsetPtr--;
                        if (offset != *nextOffsetPtr) {
                            log_err("error, locale %s, expected ucol_previous -> ucol_getOffset %d, got %d\n",
                                                                tsceItemPtr->locale, *nextOffsetPtr, offset );
                            nextOffsetPtr = limitOffsetPtr;
                            break;
                        }
                   } else {
                        log_err("error, locale %s, ucol_previous returned more elements than expected\n", tsceItemPtr->locale );
                    }
                } while ( U_SUCCESS(status) && element != UCOL_NULLORDER );
                if ( nextOffsetPtr > limitOffsetPtr ) {
                    log_err("error, locale %s, ucol_previous returned fewer elements than expected\n", tsceItemPtr->locale );
                }

                ucol_closeElements(uce);
            } else {
                log_err("error, locale %s, ucol_openElements failed: %s\n", tsceItemPtr->locale, u_errorName(status) );
            }
            ucol_close(ucol);
        } else {
            log_data_err("error, locale %s, ucol_open failed: %s\n", tsceItemPtr->locale, u_errorName(status) );
        }
    }
}