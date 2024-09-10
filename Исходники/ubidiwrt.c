U_CAPI int32_t U_EXPORT2
ubidi_writeReordered(UBiDi *pBiDi,
                     UChar *dest, int32_t destSize,
                     uint16_t options,
                     UErrorCode *pErrorCode) {
    const UChar *text;
    UChar *saveDest;
    int32_t length, destCapacity;
    int32_t run, runCount, logicalStart, runLength;

    if(pErrorCode==NULL || U_FAILURE(*pErrorCode)) {
        return 0;
    }

    /* more error checking */
    if( pBiDi==NULL ||
        (text=pBiDi->text)==NULL || (length=pBiDi->length)<0 ||
        destSize<0 || (destSize>0 && dest==NULL))
    {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    /* do input and output overlap? */
    if( dest!=NULL &&
        ((text>=dest && text<dest+destSize) ||
         (dest>=text && dest<text+pBiDi->originalLength)))
    {
        *pErrorCode=U_ILLEGAL_ARGUMENT_ERROR;
        return 0;
    }

    if(length==0) {
        /* nothing to do */
        return u_terminateUChars(dest, destSize, 0, pErrorCode);
    }

    runCount=ubidi_countRuns(pBiDi, pErrorCode);
    if(U_FAILURE(*pErrorCode)) {
        return 0;
    }

    /* destSize shrinks, later destination length=destCapacity-destSize */
    saveDest=dest;
    destCapacity=destSize;

    /*
     * Option "insert marks" implies UBIDI_INSERT_LRM_FOR_NUMERIC if the
     * reordering mode (checked below) is appropriate.
     */
    if(pBiDi->reorderingOptions & UBIDI_OPTION_INSERT_MARKS) {
        options|=UBIDI_INSERT_LRM_FOR_NUMERIC;
        options&=~UBIDI_REMOVE_BIDI_CONTROLS;
    }
    /*
     * Option "remove controls" implies UBIDI_REMOVE_BIDI_CONTROLS
     * and cancels UBIDI_INSERT_LRM_FOR_NUMERIC.
     */
    if(pBiDi->reorderingOptions & UBIDI_OPTION_REMOVE_CONTROLS) {
        options|=UBIDI_REMOVE_BIDI_CONTROLS;
        options&=~UBIDI_INSERT_LRM_FOR_NUMERIC;
    }
    /*
     * If we do not perform the "inverse BiDi" algorithm, then we
     * don't need to insert any LRMs, and don't need to test for it.
     */
    if((pBiDi->reorderingMode != UBIDI_REORDER_INVERSE_NUMBERS_AS_L) &&
       (pBiDi->reorderingMode != UBIDI_REORDER_INVERSE_LIKE_DIRECT)  &&
       (pBiDi->reorderingMode != UBIDI_REORDER_INVERSE_FOR_NUMBERS_SPECIAL) &&
       (pBiDi->reorderingMode != UBIDI_REORDER_RUNS_ONLY)) {
        options&=~UBIDI_INSERT_LRM_FOR_NUMERIC;
    }
    /*
     * Iterate through all visual runs and copy the run text segments to
     * the destination, according to the options.
     *
     * The tests for where to insert LRMs ignore the fact that there may be
     * BN codes or non-BMP code points at the beginning and end of a run;
     * they may insert LRMs unnecessarily but the tests are faster this way
     * (this would have to be improved for UTF-8).
     *
     * Note that the only errors that are set by doWriteXY() are buffer overflow
     * errors. Ignore them until the end, and continue for preflighting.
     */
    if(!(options&UBIDI_OUTPUT_REVERSE)) {
        /* forward output */
        if(!(options&UBIDI_INSERT_LRM_FOR_NUMERIC)) {
            /* do not insert BiDi controls */
            for(run=0; run<runCount; ++run) {
                if(UBIDI_LTR==ubidi_getVisualRun(pBiDi, run, &logicalStart, &runLength)) {
                    runLength=doWriteForward(text+logicalStart, runLength,
                                             dest, destSize,
                                             (uint16_t)(options&~UBIDI_DO_MIRRORING), pErrorCode);
                } else {
                    runLength=doWriteReverse(text+logicalStart, runLength,
                                             dest, destSize,
                                             options, pErrorCode);
                }
                dest+=runLength;
                destSize-=runLength;
            }
        } else {
            /* insert BiDi controls for "inverse BiDi" */
            const DirProp *dirProps=pBiDi->dirProps;
            const UChar *src;
            UChar uc;
            UBiDiDirection dir;
            int32_t markFlag;

            for(run=0; run<runCount; ++run) {
                dir=ubidi_getVisualRun(pBiDi, run, &logicalStart, &runLength);
                src=text+logicalStart;
                /* check if something relevant in insertPoints */
                markFlag=pBiDi->runs[run].insertRemove;
                if(markFlag<0) {        /* BiDi controls count */
                    markFlag=0;
                }

                if(UBIDI_LTR==dir) {
                    if((pBiDi->isInverse) &&
                       (/*run>0 &&*/ dirProps[logicalStart]!=L)) {
                        markFlag |= LRM_BEFORE;
                    }
                    if (markFlag & LRM_BEFORE) {
                        uc=LRM_CHAR;
                    }
                    else if (markFlag & RLM_BEFORE) {
                        uc=RLM_CHAR;
                    }
                    else  uc=0;
                    if(uc) {
                        if(destSize>0) {
                            *dest++=uc;
                        }
                        --destSize;
                    }

                    runLength=doWriteForward(src, runLength,
                                             dest, destSize,
                                             (uint16_t)(options&~UBIDI_DO_MIRRORING), pErrorCode);
                    dest+=runLength;
                    destSize-=runLength;

                    if((pBiDi->isInverse) &&
                       (/*run<runCount-1 &&*/ dirProps[logicalStart+runLength-1]!=L)) {
                        markFlag |= LRM_AFTER;
                    }
                    if (markFlag & LRM_AFTER) {
                        uc=LRM_CHAR;
                    }
                    else if (markFlag & RLM_AFTER) {
                        uc=RLM_CHAR;
                    }
                    else  uc=0;
                    if(uc) {
                        if(destSize>0) {
                            *dest++=uc;
                        }
                        --destSize;
                    }
                } else {                /* RTL run */
                    if((pBiDi->isInverse) &&
                       (/*run>0 &&*/ !(MASK_R_AL&DIRPROP_FLAG(dirProps[logicalStart+runLength-1])))) {
                        markFlag |= RLM_BEFORE;
                    }
                    if (markFlag & LRM_BEFORE) {
                        uc=LRM_CHAR;
                    }
                    else if (markFlag & RLM_BEFORE) {
                        uc=RLM_CHAR;
                    }
                    else  uc=0;
                    if(uc) {
                        if(destSize>0) {
                            *dest++=uc;
                        }
                        --destSize;
                    }

                    runLength=doWriteReverse(src, runLength,
                                             dest, destSize,
                                             options, pErrorCode);
                    dest+=runLength;
                    destSize-=runLength;

                    if((pBiDi->isInverse) &&
                       (/*run<runCount-1 &&*/ !(MASK_R_AL&DIRPROP_FLAG(dirProps[logicalStart])))) {
                        markFlag |= RLM_AFTER;
                    }
                    if (markFlag & LRM_AFTER) {
                        uc=LRM_CHAR;
                    }
                    else if (markFlag & RLM_AFTER) {
                        uc=RLM_CHAR;
                    }
                    else  uc=0;
                    if(uc) {
                        if(destSize>0) {
                            *dest++=uc;
                        }
                        --destSize;
                    }
                }
            }
        }
    } else {
        /* reverse output */
        if(!(options&UBIDI_INSERT_LRM_FOR_NUMERIC)) {
            /* do not insert BiDi controls */
            for(run=runCount; --run>=0;) {
                if(UBIDI_LTR==ubidi_getVisualRun(pBiDi, run, &logicalStart, &runLength)) {
                    runLength=doWriteReverse(text+logicalStart, runLength,
                                             dest, destSize,
                                             (uint16_t)(options&~UBIDI_DO_MIRRORING), pErrorCode);
                } else {
                    runLength=doWriteForward(text+logicalStart, runLength,
                                             dest, destSize,
                                             options, pErrorCode);
                }
                dest+=runLength;
                destSize-=runLength;
            }
        } else {
            /* insert BiDi controls for "inverse BiDi" */
            const DirProp *dirProps=pBiDi->dirProps;
            const UChar *src;
            UBiDiDirection dir;

            for(run=runCount; --run>=0;) {
                /* reverse output */
                dir=ubidi_getVisualRun(pBiDi, run, &logicalStart, &runLength);
                src=text+logicalStart;

                if(UBIDI_LTR==dir) {
                    if(/*run<runCount-1 &&*/ dirProps[logicalStart+runLength-1]!=L) {
                        if(destSize>0) {
                            *dest++=LRM_CHAR;
                        }
                        --destSize;
                    }

                    runLength=doWriteReverse(src, runLength,
                                             dest, destSize,
                                             (uint16_t)(options&~UBIDI_DO_MIRRORING), pErrorCode);
                    dest+=runLength;
                    destSize-=runLength;

                    if(/*run>0 &&*/ dirProps[logicalStart]!=L) {
                        if(destSize>0) {
                            *dest++=LRM_CHAR;
                        }
                        --destSize;
                    }
                } else {
                    if(/*run<runCount-1 &&*/ !(MASK_R_AL&DIRPROP_FLAG(dirProps[logicalStart]))) {
                        if(destSize>0) {
                            *dest++=RLM_CHAR;
                        }
                        --destSize;
                    }

                    runLength=doWriteForward(src, runLength,
                                             dest, destSize,
                                             options, pErrorCode);
                    dest+=runLength;
                    destSize-=runLength;

                    if(/*run>0 &&*/ !(MASK_R_AL&DIRPROP_FLAG(dirProps[logicalStart+runLength-1]))) {
                        if(destSize>0) {
                            *dest++=RLM_CHAR;
                        }
                        --destSize;
                    }
                }
            }
        }
    }

    return u_terminateUChars(saveDest, destCapacity, destCapacity-destSize, pErrorCode);
}