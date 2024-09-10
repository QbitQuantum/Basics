UChar32 CaseFoldingUTextIterator::next() {
    UChar32  foldedC;
    UChar32  originalC;
    if (fFoldChars == NULL) {
        // We are not in a string folding of an earlier character.
        // Start handling the next char from the input UText.
        originalC = UTEXT_NEXT32(&fUText);
        if (originalC == U_SENTINEL) {
            return originalC;
        }
        fFoldLength = ucase_toFullFolding(fcsp, originalC, &fFoldChars, U_FOLD_CASE_DEFAULT);
        if (fFoldLength >= UCASE_MAX_STRING_LENGTH || fFoldLength < 0) {
            // input code point folds to a single code point, possibly itself.
            // See comment in ucase.h for explanation of return values from ucase_toFullFoldings.
            if (fFoldLength < 0) {
                fFoldLength = ~fFoldLength;
            }
            foldedC = (UChar32)fFoldLength;
            fFoldChars = NULL;
            return foldedC;
        }
        // String foldings fall through here.
        fFoldIndex = 0;
    }

    U16_NEXT(fFoldChars, fFoldIndex, fFoldLength, foldedC);
    if (fFoldIndex >= fFoldLength) {
        fFoldChars = NULL;
    }
    return foldedC;
}