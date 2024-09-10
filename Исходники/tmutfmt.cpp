void 
TimeUnitFormat::parseObject(const UnicodeString& source, 
                            Formattable& result,
                            ParsePosition& pos) const {
    double resultNumber = -1; 
    UBool withNumberFormat = false;
    TimeUnit::UTimeUnitFields resultTimeUnit = TimeUnit::UTIMEUNIT_FIELD_COUNT;
    int32_t oldPos = pos.getIndex();
    int32_t newPos = -1;
    int32_t longestParseDistance = 0;
    UnicodeString* countOfLongestMatch = NULL;
#ifdef TMUTFMT_DEBUG
    char res[1000];
    source.extract(0, source.length(), res, "UTF-8");
    std::cout << "parse source: " << res << "\n";           
#endif
    // parse by iterating through all available patterns
    // and looking for the longest match.
    for (TimeUnit::UTimeUnitFields i = TimeUnit::UTIMEUNIT_YEAR;
         i < TimeUnit::UTIMEUNIT_FIELD_COUNT;
         i = (TimeUnit::UTimeUnitFields)(i+1)) {
        Hashtable* countToPatterns = fTimeUnitToCountToPatterns[i];
        int32_t elemPos = -1;
        const UHashElement* elem = NULL;
        while ((elem = countToPatterns->nextElement(elemPos)) != NULL){
            const UHashTok keyTok = elem->key;
            UnicodeString* count = (UnicodeString*)keyTok.pointer;
#ifdef TMUTFMT_DEBUG
            count->extract(0, count->length(), res, "UTF-8");
            std::cout << "parse plural count: " << res << "\n";           
#endif
            const UHashTok valueTok = elem->value;
            // the value is a pair of MessageFormat*
            MessageFormat** patterns = (MessageFormat**)valueTok.pointer;
            for (UTimeUnitFormatStyle style = UTMUTFMT_FULL_STYLE; style < UTMUTFMT_FORMAT_STYLE_COUNT;
                 style = (UTimeUnitFormatStyle)(style + 1)) {
                MessageFormat* pattern = patterns[style];
                pos.setErrorIndex(-1);
                pos.setIndex(oldPos);
                // see if we can parse
                Formattable parsed;
                pattern->parseObject(source, parsed, pos);
                if (pos.getErrorIndex() != -1 || pos.getIndex() == oldPos) {
                    continue;
                }
    #ifdef TMUTFMT_DEBUG
                std::cout << "parsed.getType: " << parsed.getType() << "\n";
    #endif
                double tmpNumber = 0;
                if (pattern->getArgTypeCount() != 0) {
                    // pattern with Number as beginning, such as "{0} d".
                    // check to make sure that the timeUnit is consistent
                    Formattable& temp = parsed[0];
                    if (temp.getType() == Formattable::kDouble) {
                        tmpNumber = temp.getDouble();
                    } else if (temp.getType() == Formattable::kLong) {
                        tmpNumber = temp.getLong();
                    } else {
                        continue;
                    }
                    UnicodeString select = fPluralRules->select(tmpNumber);
    #ifdef TMUTFMT_DEBUG
                    select.extract(0, select.length(), res, "UTF-8");
                    std::cout << "parse plural select count: " << res << "\n"; 
    #endif
                    if (*count != select) {
                        continue;
                    }
                }
                int32_t parseDistance = pos.getIndex() - oldPos;
                if (parseDistance > longestParseDistance) {
                    if (pattern->getArgTypeCount() != 0) {
                        resultNumber = tmpNumber;
                        withNumberFormat = true;
                    } else {
                        withNumberFormat = false;
                    }
                    resultTimeUnit = i;
                    newPos = pos.getIndex();
                    longestParseDistance = parseDistance;
                    countOfLongestMatch = count;
                }
            }
        }
    }
    /* After find the longest match, parse the number.
     * Result number could be null for the pattern without number pattern.
     * such as unit pattern in Arabic.
     * When result number is null, use plural rule to set the number.
     */
    if (withNumberFormat == false && longestParseDistance != 0) {
        // set the number using plurrual count
        if (0 == countOfLongestMatch->compare(PLURAL_COUNT_ZERO, 4)) {
            resultNumber = 0;
        } else if (0 == countOfLongestMatch->compare(PLURAL_COUNT_ONE, 3)) {
            resultNumber = 1;
        } else if (0 == countOfLongestMatch->compare(PLURAL_COUNT_TWO, 3)) {
            resultNumber = 2;
        } else {
            // should not happen.
            // TODO: how to handle?
            resultNumber = 3;
        }
    }
    if (longestParseDistance == 0) {
        pos.setIndex(oldPos);
        pos.setErrorIndex(0);
    } else {
        UErrorCode status = U_ZERO_ERROR;
        TimeUnitAmount* tmutamt = new TimeUnitAmount(resultNumber, resultTimeUnit, status);
        if (U_SUCCESS(status)) {
            result.adoptObject(tmutamt);
            pos.setIndex(newPos);
            pos.setErrorIndex(-1);
        } else {
            pos.setIndex(oldPos);
            pos.setErrorIndex(0);
        }
    }
}