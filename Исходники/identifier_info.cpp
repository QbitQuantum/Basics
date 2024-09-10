IdentifierInfo &IdentifierInfo::setIdentifier(const UnicodeString &identifier, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return *this;
    }
    *fIdentifier = identifier;
    clear();
    ScriptSet scriptsForCP;
    UChar32 cp;
    for (int32_t i = 0; i < identifier.length(); i += U16_LENGTH(cp)) {
        cp = identifier.char32At(i);
        // Store a representative character for each kind of decimal digit
        if (u_charType(cp) == U_DECIMAL_DIGIT_NUMBER) {
            // Just store the zero character as a representative for comparison. Unicode guarantees it is cp - value
            fNumerics->add(cp - (UChar32)u_getNumericValue(cp));
        }
        UScriptCode extensions[500];
        int32_t extensionsCount = uscript_getScriptExtensions(cp, extensions, UPRV_LENGTHOF(extensions), &status);
        if (U_FAILURE(status)) {
            return *this;
        }
        scriptsForCP.resetAll();
        for (int32_t j=0; j<extensionsCount; j++) {
            scriptsForCP.set(extensions[j], status);
        }
        scriptsForCP.reset(USCRIPT_COMMON, status);
        scriptsForCP.reset(USCRIPT_INHERITED, status);
        switch (scriptsForCP.countMembers()) {
          case 0: break;
          case 1:
            // Single script, record it.
            fRequiredScripts->Union(scriptsForCP);
            break;
          default:
            if (!fRequiredScripts->intersects(scriptsForCP) 
                    && !uhash_geti(fScriptSetSet, &scriptsForCP)) {
                // If the set hasn't been added already, add it
                //    (Add a copy, fScriptSetSet takes ownership of the copy.)
                uhash_puti(fScriptSetSet, new ScriptSet(scriptsForCP), 1, &status);
            }
            break;
        }
    }
    // Now make a final pass through ScriptSetSet to remove alternates that came before singles.
    // [Kana], [Kana Hira] => [Kana]
    // This is relatively infrequent, so doesn't have to be optimized.
    // We also compute any commonalities among the alternates.
    if (uhash_count(fScriptSetSet) > 0) {
        fCommonAmongAlternates->setAll();
        for (int32_t it = UHASH_FIRST;;) {
            const UHashElement *nextHashEl = uhash_nextElement(fScriptSetSet, &it);
            if (nextHashEl == NULL) {
                break;
            }
            ScriptSet *next = static_cast<ScriptSet *>(nextHashEl->key.pointer);
            // [Kana], [Kana Hira] => [Kana]
            if (fRequiredScripts->intersects(*next)) {
                uhash_removeElement(fScriptSetSet, nextHashEl);
            } else {
                fCommonAmongAlternates->intersect(*next);
                // [[Arab Syrc Thaa]; [Arab Syrc]] => [[Arab Syrc]]
                for (int32_t otherIt = UHASH_FIRST;;) {
                    const UHashElement *otherHashEl = uhash_nextElement(fScriptSetSet, &otherIt);
                    if (otherHashEl == NULL) {
                        break;
                    }
                    ScriptSet *other = static_cast<ScriptSet *>(otherHashEl->key.pointer);
                    if (next != other && next->contains(*other)) {
                        uhash_removeElement(fScriptSetSet, nextHashEl);
                        break;
                    }
                }
            }
        }
    }
    if (uhash_count(fScriptSetSet) == 0) {
        fCommonAmongAlternates->resetAll();
    }
    return *this;
}