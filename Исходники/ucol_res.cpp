U_CAPI UBool U_EXPORT2
ucol_equals(const UCollator *source, const UCollator *target) {
    UErrorCode status = U_ZERO_ERROR;
    // if pointers are equal, collators are equal
    if(source == target) {
        return TRUE;
    }
    int32_t i = 0, j = 0;
    // if any of attributes are different, collators are not equal
    for(i = 0; i < UCOL_ATTRIBUTE_COUNT; i++) {
        if(ucol_getAttribute(source, (UColAttribute)i, &status) != ucol_getAttribute(target, (UColAttribute)i, &status) || U_FAILURE(status)) {
            return FALSE;
        }
    }

    int32_t sourceRulesLen = 0, targetRulesLen = 0;
    const UChar *sourceRules = ucol_getRules(source, &sourceRulesLen);
    const UChar *targetRules = ucol_getRules(target, &targetRulesLen);

    if(sourceRulesLen == targetRulesLen && u_strncmp(sourceRules, targetRules, sourceRulesLen) == 0) {
        // all the attributes are equal and the rules are equal - collators are equal
        return(TRUE);
    }
    // hard part, need to construct tree from rules and see if they yield the same tailoring
    UBool result = TRUE;
    UParseError parseError;
    UColTokenParser sourceParser, targetParser;
    int32_t sourceListLen = 0, targetListLen = 0;
    ucol_tok_initTokenList(&sourceParser, sourceRules, sourceRulesLen, source->UCA, &status);
    ucol_tok_initTokenList(&targetParser, targetRules, targetRulesLen, target->UCA, &status);
    sourceListLen = ucol_tok_assembleTokenList(&sourceParser, &parseError, &status);
    targetListLen = ucol_tok_assembleTokenList(&targetParser, &parseError, &status);

    if(sourceListLen != targetListLen) {
        // different number of resets
        result = FALSE;
    } else {
        UColToken *sourceReset = NULL, *targetReset = NULL;
        UChar *sourceResetString = NULL, *targetResetString = NULL;
        int32_t sourceStringLen = 0, targetStringLen = 0;
        for(i = 0; i < sourceListLen; i++) {
            sourceReset = sourceParser.lh[i].reset;
            sourceResetString = sourceParser.source+(sourceReset->source & 0xFFFFFF);
            sourceStringLen = sourceReset->source >> 24;
            for(j = 0; j < sourceListLen; j++) {
                targetReset = targetParser.lh[j].reset;
                targetResetString = targetParser.source+(targetReset->source & 0xFFFFFF);
                targetStringLen = targetReset->source >> 24;
                if(sourceStringLen == targetStringLen && (u_strncmp(sourceResetString, targetResetString, sourceStringLen) == 0)) {
                    sourceReset = sourceParser.lh[i].first;
                    targetReset = targetParser.lh[j].first;
                    while(sourceReset != NULL && targetReset != NULL) {
                        sourceResetString = sourceParser.source+(sourceReset->source & 0xFFFFFF);
                        sourceStringLen = sourceReset->source >> 24;
                        targetResetString = targetParser.source+(targetReset->source & 0xFFFFFF);
                        targetStringLen = targetReset->source >> 24;
                        if(sourceStringLen != targetStringLen || (u_strncmp(sourceResetString, targetResetString, sourceStringLen) != 0)) {
                            result = FALSE;
                            goto returnResult;
                        }
                        // probably also need to check the expansions
                        if(sourceReset->expansion) {
                            if(!targetReset->expansion) {
                                result = FALSE;
                                goto returnResult;
                            } else {
                                // compare expansions
                                sourceResetString = sourceParser.source+(sourceReset->expansion& 0xFFFFFF);
                                sourceStringLen = sourceReset->expansion >> 24;
                                targetResetString = targetParser.source+(targetReset->expansion & 0xFFFFFF);
                                targetStringLen = targetReset->expansion >> 24;
                                if(sourceStringLen != targetStringLen || (u_strncmp(sourceResetString, targetResetString, sourceStringLen) != 0)) {
                                    result = FALSE;
                                    goto returnResult;
                                }
                            }
                        } else {
                            if(targetReset->expansion) {
                                result = FALSE;
                                goto returnResult;
                            }
                        }
                        sourceReset = sourceReset->next;
                        targetReset = targetReset->next;
                    }
                    if(sourceReset != targetReset) { // at least one is not NULL
                        // there are more tailored elements in one list
                        result = FALSE;
                        goto returnResult;
                    }


                    break;
                }
            }
            // couldn't find the reset anchor, so the collators are not equal
            if(j == sourceListLen) {
                result = FALSE;
                goto returnResult;
            }
        }