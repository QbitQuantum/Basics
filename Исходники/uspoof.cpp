U_CAPI int32_t U_EXPORT2
uspoof_checkUnicodeString(const USpoofChecker *sc,
                          const icu::UnicodeString &id, 
                          int32_t *position,
                          UErrorCode *status) {
    const SpoofImpl *This = SpoofImpl::validateThis(sc, *status);
    if (This == NULL) {
        return 0;
    }
    int32_t result = 0;

    IdentifierInfo *identifierInfo = NULL;
    if ((This->fChecks) & (USPOOF_RESTRICTION_LEVEL | USPOOF_MIXED_NUMBERS)) {
        identifierInfo = This->getIdentifierInfo(*status);
        if (U_FAILURE(*status)) {
            goto cleanupAndReturn;
        }
        identifierInfo->setIdentifier(id, *status);
        identifierInfo->setIdentifierProfile(*This->fAllowedCharsSet);
    }


    if ((This->fChecks) & USPOOF_RESTRICTION_LEVEL) {
        URestrictionLevel idRestrictionLevel = identifierInfo->getRestrictionLevel(*status);
        if (idRestrictionLevel > This->fRestrictionLevel) {
            result |= USPOOF_RESTRICTION_LEVEL;
        }
        if (This->fChecks & USPOOF_AUX_INFO) {
            result |= idRestrictionLevel;
        }
    }

    if ((This->fChecks) & USPOOF_MIXED_NUMBERS) {
        const UnicodeSet *numerics = identifierInfo->getNumerics();
        if (numerics->size() > 1) {
            result |= USPOOF_MIXED_NUMBERS;
        }

        // TODO: ICU4J returns the UnicodeSet of the numerics found in the identifier.
        //       We have no easy way to do the same in C.
        // if (checkResult != null) {
        //     checkResult.numerics = numerics;
        // }
    }


    if (This->fChecks & (USPOOF_CHAR_LIMIT)) {
        int32_t i;
        UChar32 c;
        int32_t length = id.length();
        for (i=0; i<length ;) {
            c = id.char32At(i);
            i += U16_LENGTH(c);
            if (!This->fAllowedCharsSet->contains(c)) {
                result |= USPOOF_CHAR_LIMIT;
                break;
            }
        }
    }

    if (This->fChecks & 
        (USPOOF_WHOLE_SCRIPT_CONFUSABLE | USPOOF_MIXED_SCRIPT_CONFUSABLE | USPOOF_INVISIBLE)) {
        // These are the checks that need to be done on NFD input
        UnicodeString nfdText;
        gNfdNormalizer->normalize(id, nfdText, *status);
        int32_t nfdLength = nfdText.length();

        if (This->fChecks & USPOOF_INVISIBLE) {
           
            // scan for more than one occurence of the same non-spacing mark
            // in a sequence of non-spacing marks.
            int32_t     i;
            UChar32     c;
            UChar32     firstNonspacingMark = 0;
            UBool       haveMultipleMarks = FALSE;  
            UnicodeSet  marksSeenSoFar;   // Set of combining marks in a single combining sequence.
            
            for (i=0; i<nfdLength ;) {
                c = nfdText.char32At(i);
                i += U16_LENGTH(c);
                if (u_charType(c) != U_NON_SPACING_MARK) {
                    firstNonspacingMark = 0;
                    if (haveMultipleMarks) {
                        marksSeenSoFar.clear();
                        haveMultipleMarks = FALSE;
                    }
                    continue;
                }
                if (firstNonspacingMark == 0) {
                    firstNonspacingMark = c;
                    continue;
                }
                if (!haveMultipleMarks) {
                    marksSeenSoFar.add(firstNonspacingMark);
                    haveMultipleMarks = TRUE;
                }
                if (marksSeenSoFar.contains(c)) {
                    // report the error, and stop scanning.
                    // No need to find more than the first failure.
                    result |= USPOOF_INVISIBLE;
                    break;
                }
                marksSeenSoFar.add(c);
            }
        }
       
        
        if (This->fChecks & (USPOOF_WHOLE_SCRIPT_CONFUSABLE | USPOOF_MIXED_SCRIPT_CONFUSABLE)) {
            // The basic test is the same for both whole and mixed script confusables.
            // Compute the set of scripts that every input character has a confusable in.
            // For this computation an input character is always considered to be
            // confusable with itself in its own script.
            //
            // If the number of such scripts is two or more, and the input consisted of
            // characters all from a single script, we have a whole script confusable.
            // (The two scripts will be the original script and the one that is confusable)
            //
            // If the number of such scripts >= one, and the original input contained characters from
            // more than one script, we have a mixed script confusable.  (We can transform
            // some of the characters, and end up with a visually similar string all in
            // one script.)

            if (identifierInfo == NULL) {
                identifierInfo = This->getIdentifierInfo(*status);
                if (U_FAILURE(*status)) {
                    goto cleanupAndReturn;
                }
                identifierInfo->setIdentifier(id, *status);
            }

            int32_t scriptCount = identifierInfo->getScriptCount();
            
            ScriptSet scripts;
            This->wholeScriptCheck(nfdText, &scripts, *status);
            int32_t confusableScriptCount = scripts.countMembers();
            //printf("confusableScriptCount = %d\n", confusableScriptCount);
            
            if ((This->fChecks & USPOOF_WHOLE_SCRIPT_CONFUSABLE) &&
                confusableScriptCount >= 2 &&
                scriptCount == 1) {
                result |= USPOOF_WHOLE_SCRIPT_CONFUSABLE;
            }
        
            if ((This->fChecks & USPOOF_MIXED_SCRIPT_CONFUSABLE) &&
                confusableScriptCount >= 1 &&
                scriptCount > 1) {
                result |= USPOOF_MIXED_SCRIPT_CONFUSABLE;
            }
        }
    }

cleanupAndReturn:
    This->releaseIdentifierInfo(identifierInfo);
    if (position != NULL) {
        *position = 0;
    }
    return result;
}