/*
 * Internal titlecasing function.
 */
static int32_t
_toTitle(UCaseMap *csm,
         uint8_t *dest, int32_t destCapacity,
         const uint8_t *src, UCaseContext *csc,
         int32_t srcLength,
         UErrorCode *pErrorCode) {
    UText utext=UTEXT_INITIALIZER;
    const UChar *s;
    UChar32 c;
    int32_t prev, titleStart, titleLimit, idx, destIndex, length;
    UBool isFirstIndex;

    utext_openUTF8(&utext, (const char *)src, srcLength, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }
    if(csm->iter==NULL) {
        csm->iter=ubrk_open(UBRK_WORD, csm->locale,
                            NULL, 0,
                            pErrorCode);
    }
    ubrk_setUText(csm->iter, &utext, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        utext_close(&utext);
        return 0;
    }

    /* set up local variables */
    destIndex=0;
    prev=0;
    isFirstIndex=TRUE;

    /* titlecasing loop */
    while(prev<srcLength) {
        /* find next index where to titlecase */
        if(isFirstIndex) {
            isFirstIndex=FALSE;
            idx=ubrk_first(csm->iter);
        } else {
            idx=ubrk_next(csm->iter);
        }
        if(idx==UBRK_DONE || idx>srcLength) {
            idx=srcLength;
        }

        /*
         * Unicode 4 & 5 section 3.13 Default Case Operations:
         *
         * R3  toTitlecase(X): Find the word boundaries based on Unicode Standard Annex
         * #29, "Text Boundaries." Between each pair of word boundaries, find the first
         * cased character F. If F exists, map F to default_title(F); then map each
         * subsequent character C to default_lower(C).
         *
         * In this implementation, segment [prev..index[ into 3 parts:
         * a) uncased characters (copy as-is) [prev..titleStart[
         * b) first case letter (titlecase)         [titleStart..titleLimit[
         * c) subsequent characters (lowercase)                 [titleLimit..index[
         */
        if(prev<idx) {
            /* find and copy uncased characters [prev..titleStart[ */
            titleStart=titleLimit=prev;
            U8_NEXT(src, titleLimit, idx, c);
            if((csm->options&U_TITLECASE_NO_BREAK_ADJUSTMENT)==0 && UCASE_NONE==ucase_getType(csm->csp, c)) {
                /* Adjust the titlecasing index (titleStart) to the next cased character. */
                for(;;) {
                    titleStart=titleLimit;
                    if(titleLimit==idx) {
                        /*
                         * only uncased characters in [prev..index[
                         * stop with titleStart==titleLimit==index
                         */
                        break;
                    }
                    U8_NEXT(src, titleLimit, idx, c);
                    if(UCASE_NONE!=ucase_getType(csm->csp, c)) {
                        break; /* cased letter at [titleStart..titleLimit[ */
                    }
                }
                length=titleStart-prev;
                if(length>0) {
                    if((destIndex+length)<=destCapacity) {
                        uprv_memcpy(dest+destIndex, src+prev, length);
                    }
                    destIndex+=length;
                }
            }

            if(titleStart<titleLimit) {
                /* titlecase c which is from [titleStart..titleLimit[ */
                csc->cpStart=titleStart;
                csc->cpLimit=titleLimit;
                c=ucase_toFullTitle(csm->csp, c, utf8_caseContextIterator, csc, &s, csm->locale, &csm->locCache);
                destIndex=appendResult(dest, destIndex, destCapacity, c, s);

                
                /* Special case Dutch IJ titlecasing */
                if ( titleStart+1 < idx && 
                     ucase_getCaseLocale(csm->locale,&csm->locCache) == UCASE_LOC_DUTCH &&
                     ( src[titleStart] == 0x0049 || src[titleStart] == 0x0069 ) &&
                     ( src[titleStart+1] == 0x004A || src[titleStart+1] == 0x006A )) { 
                            c=0x004A;
                            destIndex=appendResult(dest, destIndex, destCapacity, c, s);
                            titleLimit++;
                }
                /* lowercase [titleLimit..index[ */
                if(titleLimit<idx) {
                    if((csm->options&U_TITLECASE_NO_LOWERCASE)==0) {
                        /* Normal operation: Lowercase the rest of the word. */
                        destIndex+=
                            _caseMap(
                                csm, ucase_toFullLower,
                                dest+destIndex, destCapacity-destIndex,
                                src, csc,
                                titleLimit, idx,
                                pErrorCode);
                    } else {
                        /* Optionally just copy the rest of the word unchanged. */
                        length=idx-titleLimit;
                        if((destIndex+length)<=destCapacity) {
                            uprv_memcpy(dest+destIndex, src+titleLimit, length);
                        }
                        destIndex+=length;
                    }
                }
            }
        }

        prev=idx;
    }

    if(destIndex>destCapacity) {
        *pErrorCode=U_BUFFER_OVERFLOW_ERROR;
    }
    utext_close(&utext);
    return destIndex;
}