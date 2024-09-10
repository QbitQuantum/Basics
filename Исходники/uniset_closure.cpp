UnicodeSet& UnicodeSet::closeOver(int32_t attribute) {
    if (isFrozen() || isBogus()) {
        return *this;
    }
    if (attribute & (USET_CASE_INSENSITIVE | USET_ADD_CASE_MAPPINGS)) {
        const UCaseProps *csp = ucase_getSingleton();
        {
            UnicodeSet foldSet(*this);
            UnicodeString str;
            USetAdder sa = {
                foldSet.toUSet(),
                _set_add,
                _set_addRange,
                _set_addString,
                NULL, // don't need remove()
                NULL // don't need removeRange()
            };

            // start with input set to guarantee inclusion
            // USET_CASE: remove strings because the strings will actually be reduced (folded);
            //            therefore, start with no strings and add only those needed
            if (attribute & USET_CASE_INSENSITIVE) {
                foldSet.strings->removeAllElements();
            }

            int32_t n = getRangeCount();
            UChar32 result;
            const UChar *full;
            int32_t locCache = 0;

            for (int32_t i=0; i<n; ++i) {
                UChar32 start = getRangeStart(i);
                UChar32 end   = getRangeEnd(i);

                if (attribute & USET_CASE_INSENSITIVE) {
                    // full case closure
                    for (UChar32 cp=start; cp<=end; ++cp) {
                        ucase_addCaseClosure(csp, cp, &sa);
                    }
                } else {
                    // add case mappings
                    // (does not add long s for regular s, or Kelvin for k, for example)
                    for (UChar32 cp=start; cp<=end; ++cp) {
                        result = ucase_toFullLower(csp, cp, NULL, NULL, &full, "", &locCache);
                        addCaseMapping(foldSet, result, full, str);

                        result = ucase_toFullTitle(csp, cp, NULL, NULL, &full, "", &locCache);
                        addCaseMapping(foldSet, result, full, str);

                        result = ucase_toFullUpper(csp, cp, NULL, NULL, &full, "", &locCache);
                        addCaseMapping(foldSet, result, full, str);

                        result = ucase_toFullFolding(csp, cp, &full, 0);
                        addCaseMapping(foldSet, result, full, str);
                    }
                }
            }
            if (strings != NULL && strings->size() > 0) {
                if (attribute & USET_CASE_INSENSITIVE) {
                    for (int32_t j=0; j<strings->size(); ++j) {
                        str = *(const UnicodeString *) strings->elementAt(j);
                        str.foldCase();
                        if(!ucase_addStringCaseClosure(csp, str.getBuffer(), str.length(), &sa)) {
                            foldSet.add(str); // does not map to code points: add the folded string itself
                        }
                    }
                } else {
                    Locale root("");
#if !UCONFIG_NO_BREAK_ITERATION
                    UErrorCode status = U_ZERO_ERROR;
                    BreakIterator *bi = BreakIterator::createWordInstance(root, status);
                    if (U_SUCCESS(status)) {
#endif
                        const UnicodeString *pStr;

                        for (int32_t j=0; j<strings->size(); ++j) {
                            pStr = (const UnicodeString *) strings->elementAt(j);
                            (str = *pStr).toLower(root);
                            foldSet.add(str);
#if !UCONFIG_NO_BREAK_ITERATION
                            (str = *pStr).toTitle(bi, root);
                            foldSet.add(str);
#endif
                            (str = *pStr).toUpper(root);
                            foldSet.add(str);
                            (str = *pStr).foldCase();
                            foldSet.add(str);
                        }
#if !UCONFIG_NO_BREAK_ITERATION
                    }
                    delete bi;
#endif
                }
            }
            *this = foldSet;
        }
    }
    return *this;
}