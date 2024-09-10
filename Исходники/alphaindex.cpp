void AlphabeticIndex::getIndexExemplars(UnicodeSet  &dest, const Locale &locale, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return;
    }

    LocalULocaleDataPointer uld(ulocdata_open(locale.getName(), &status));
    UnicodeSet exemplars;
    ulocdata_getExemplarSet(uld.getAlias(), exemplars.toUSet(), 0, ULOCDATA_ES_INDEX, &status);
    if (U_SUCCESS(status)) {
        dest.addAll(exemplars);
        return;
    }
    status = U_ZERO_ERROR;  // Clear out U_MISSING_RESOURCE_ERROR

    // Locale data did not include explicit Index characters.
    // Synthesize a set of them from the locale's standard exemplar characters.

    ulocdata_getExemplarSet(uld.getAlias(), exemplars.toUSet(), 0, ULOCDATA_ES_STANDARD, &status);
    if (U_FAILURE(status)) {
        return;
    }

    // Upper-case any that aren't already so.
    //   (We only do this for synthesized index characters.)

    UnicodeSetIterator it(exemplars);
    UnicodeString upperC;
    UnicodeSet  lowersToRemove;
    UnicodeSet  uppersToAdd;
    while (it.next()) {
        const UnicodeString &exemplarC = it.getString();
        upperC = exemplarC;
        upperC.toUpper(locale);
        if (exemplarC != upperC) {
            lowersToRemove.add(exemplarC);
            uppersToAdd.add(upperC);
        }
    }
    exemplars.removeAll(lowersToRemove);
    exemplars.addAll(uppersToAdd);

    // get the exemplars, and handle special cases

    // question: should we add auxiliary exemplars?
    if (exemplars.containsSome(*CORE_LATIN)) {
        exemplars.addAll(*CORE_LATIN);
    }
    if (exemplars.containsSome(*HANGUL)) {
        // cut down to small list
        UnicodeSet BLOCK_HANGUL_SYLLABLES(UNICODE_STRING_SIMPLE("[:block=hangul_syllables:]"), status);
        exemplars.removeAll(BLOCK_HANGUL_SYLLABLES);
        exemplars.addAll(*HANGUL);
    }
    if (exemplars.containsSome(*ETHIOPIC)) {
        // cut down to small list
        // make use of the fact that Ethiopic is allocated in 8's, where
        // the base is 0 mod 8.
        UnicodeSetIterator  it(*ETHIOPIC);
        while (it.next() && !it.isString()) {
            if ((it.getCodepoint() & 0x7) != 0) {
                exemplars.remove(it.getCodepoint());
            }
        }
    }
    dest.addAll(exemplars);
}