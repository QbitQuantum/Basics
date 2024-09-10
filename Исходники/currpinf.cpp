void
CurrencyPluralInfo::setupCurrencyPluralPattern(const Locale& loc, UErrorCode& status) {
    if (U_FAILURE(status)) {
        return;
    }

    if (fPluralCountToCurrencyUnitPattern) {
        deleteHash(fPluralCountToCurrencyUnitPattern);
    }
    fPluralCountToCurrencyUnitPattern = initHash(status);
    if (U_FAILURE(status)) {
        return;
    }

    UErrorCode ec = U_ZERO_ERROR;
    UResourceBundle *rb = ures_open(NULL, loc.getName(), &ec);
    rb = ures_getByKey(rb, gNumberElementsTag, rb, &ec);
    rb = ures_getByKey(rb, gLatnTag, rb, &ec);
    rb = ures_getByKey(rb, gPatternsTag, rb, &ec);
    int32_t ptnLen;
    const UChar* numberStylePattern = ures_getStringByKeyWithFallback(rb, gDecimalFormatTag, &ptnLen, &ec);
    int32_t numberStylePatternLen = ptnLen;
    const UChar* negNumberStylePattern = NULL;
    int32_t negNumberStylePatternLen = 0;
    // TODO: Java
    // parse to check whether there is ";" separator in the numberStylePattern
    UBool hasSeparator = false;
    if (U_SUCCESS(ec)) {
        for (int32_t styleCharIndex = 0; styleCharIndex < ptnLen; ++styleCharIndex) {
            if (numberStylePattern[styleCharIndex] == gNumberPatternSeparator) {
                hasSeparator = true;
                // split the number style pattern into positive and negative
                negNumberStylePattern = numberStylePattern + styleCharIndex + 1;
                negNumberStylePatternLen = ptnLen - styleCharIndex - 1;
                numberStylePatternLen = styleCharIndex;
            }
        }
    }
    ures_close(rb);

    if (U_FAILURE(ec)) {
        return;
    }

    UResourceBundle *currRb = ures_open(U_ICUDATA_CURR, loc.getName(), &ec);
    UResourceBundle *currencyRes = ures_getByKeyWithFallback(currRb, gCurrUnitPtnTag, NULL, &ec);
    
#ifdef CURRENCY_PLURAL_INFO_DEBUG
    std::cout << "in set up\n";
#endif
    StringEnumeration* keywords = fPluralRules->getKeywords(ec);
    if (U_SUCCESS(ec)) {
        const char* pluralCount;
        while ((pluralCount = keywords->next(NULL, ec)) != NULL) {
            if ( U_SUCCESS(ec) ) {
                int32_t ptnLen;
                UErrorCode err = U_ZERO_ERROR;
                const UChar* patternChars = ures_getStringByKeyWithFallback(
                    currencyRes, pluralCount, &ptnLen, &err);
                if (U_SUCCESS(err) && ptnLen > 0) {
                    UnicodeString* pattern = new UnicodeString(patternChars, ptnLen);
#ifdef CURRENCY_PLURAL_INFO_DEBUG
                    char result_1[1000];
                    pattern->extract(0, pattern->length(), result_1, "UTF-8");
                    std::cout << "pluralCount: " << pluralCount << "; pattern: " << result_1 << "\n";
#endif
                    pattern->findAndReplace(gPart0, 
                      UnicodeString(numberStylePattern, numberStylePatternLen));
                    pattern->findAndReplace(gPart1, gTripleCurrencySign);

                    if (hasSeparator) {
                        UnicodeString negPattern(patternChars, ptnLen);
                        negPattern.findAndReplace(gPart0, 
                          UnicodeString(negNumberStylePattern, negNumberStylePatternLen));
                        negPattern.findAndReplace(gPart1, gTripleCurrencySign);
                        pattern->append(gNumberPatternSeparator);
                        pattern->append(negPattern);
                    }
#ifdef CURRENCY_PLURAL_INFO_DEBUG
                    pattern->extract(0, pattern->length(), result_1, "UTF-8");
                    std::cout << "pluralCount: " << pluralCount << "; pattern: " << result_1 << "\n";
#endif

                    fPluralCountToCurrencyUnitPattern->put(UnicodeString(pluralCount), pattern, status);
                }
            }
        }
    }
    delete keywords;
    ures_close(currencyRes);
    ures_close(currRb);
}