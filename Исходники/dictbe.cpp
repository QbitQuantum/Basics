/*
 * @param text A UText representing the text
 * @param rangeStart The start of the range of dictionary characters
 * @param rangeEnd The end of the range of dictionary characters
 * @param foundBreaks Output of C array of int32_t break positions, or 0
 * @return The number of breaks found
 */
int32_t 
CjkBreakEngine::divideUpDictionaryRange( UText *text,
        int32_t rangeStart,
        int32_t rangeEnd,
        UStack &foundBreaks ) const {
    if (rangeStart >= rangeEnd) {
        return 0;
    }

    const size_t defaultInputLength = 80;
    size_t inputLength = rangeEnd - rangeStart;
    // TODO: Replace by UnicodeString.
    AutoBuffer<UChar, defaultInputLength> charString(inputLength);

    // Normalize the input string and put it in normalizedText.
    // The map from the indices of the normalized input to the raw
    // input is kept in charPositions.
    UErrorCode status = U_ZERO_ERROR;
    utext_extract(text, rangeStart, rangeEnd, charString.elems(), inputLength, &status);
    if (U_FAILURE(status)) {
        return 0;
    }

    UnicodeString inputString(charString.elems(), inputLength);
    // TODO: Use Normalizer2.
    UNormalizationMode norm_mode = UNORM_NFKC;
    UBool isNormalized =
        Normalizer::quickCheck(inputString, norm_mode, status) == UNORM_YES ||
        Normalizer::isNormalized(inputString, norm_mode, status);

    // TODO: Replace by UVector32.
    AutoBuffer<int32_t, defaultInputLength> charPositions(inputLength + 1);
    int numChars = 0;
    UText normalizedText = UTEXT_INITIALIZER;
    // Needs to be declared here because normalizedText holds onto its buffer.
    UnicodeString normalizedString;
    if (isNormalized) {
        int32_t index = 0;
        charPositions[0] = 0;
        while(index < inputString.length()) {
            index = inputString.moveIndex32(index, 1);
            charPositions[++numChars] = index;
        }
        utext_openUnicodeString(&normalizedText, &inputString, &status);
    }
    else {
        Normalizer::normalize(inputString, norm_mode, 0, normalizedString, status);
        if (U_FAILURE(status)) {
            return 0;
        }
        charPositions.resize(normalizedString.length() + 1);
        Normalizer normalizer(charString.elems(), inputLength, norm_mode);
        int32_t index = 0;
        charPositions[0] = 0;
        while(index < normalizer.endIndex()){
            /* UChar32 uc = */ normalizer.next();
            charPositions[++numChars] = index = normalizer.getIndex();
        }
        utext_openUnicodeString(&normalizedText, &normalizedString, &status);
    }

    if (U_FAILURE(status)) {
        return 0;
    }

    // From this point on, all the indices refer to the indices of
    // the normalized input string.

    // bestSnlp[i] is the snlp of the best segmentation of the first i
    // characters in the range to be matched.
    // TODO: Replace by UVector32.
    AutoBuffer<uint32_t, defaultInputLength> bestSnlp(numChars + 1);
    bestSnlp[0] = 0;
    for(int i = 1; i <= numChars; i++) {
        bestSnlp[i] = kuint32max;
    }

    // prev[i] is the index of the last CJK character in the previous word in 
    // the best segmentation of the first i characters.
    // TODO: Replace by UVector32.
    AutoBuffer<int, defaultInputLength> prev(numChars + 1);
    for(int i = 0; i <= numChars; i++){
        prev[i] = -1;
    }

    const size_t maxWordSize = 20;
    // TODO: Replace both with UVector32.
    AutoBuffer<int32_t, maxWordSize> values(numChars);
    AutoBuffer<int32_t, maxWordSize> lengths(numChars);

    // Dynamic programming to find the best segmentation.
    bool is_prev_katakana = false;
    for (int32_t i = 0; i < numChars; ++i) {
        //utext_setNativeIndex(text, rangeStart + i);
        utext_setNativeIndex(&normalizedText, i);
        if (bestSnlp[i] == kuint32max)
            continue;

        int32_t count;
        // limit maximum word length matched to size of current substring
        int32_t maxSearchLength = (i + maxWordSize < (size_t) numChars)? maxWordSize : (numChars - i);

        fDictionary->matches(&normalizedText, maxSearchLength, lengths.elems(), count, maxSearchLength, values.elems());

        // if there are no single character matches found in the dictionary 
        // starting with this charcter, treat character as a 1-character word 
        // with the highest value possible, i.e. the least likely to occur.
        // Exclude Korean characters from this treatment, as they should be left
        // together by default.
        if((count == 0 || lengths[0] != 1) &&
                !fHangulWordSet.contains(utext_current32(&normalizedText))) {
            values[count] = maxSnlp;
            lengths[count++] = 1;
        }

        for (int j = 0; j < count; j++) {
            uint32_t newSnlp = bestSnlp[i] + values[j];
            if (newSnlp < bestSnlp[lengths[j] + i]) {
                bestSnlp[lengths[j] + i] = newSnlp;
                prev[lengths[j] + i] = i;
            }
        }

        // In Japanese,
        // Katakana word in single character is pretty rare. So we apply
        // the following heuristic to Katakana: any continuous run of Katakana
        // characters is considered a candidate word with a default cost
        // specified in the katakanaCost table according to its length.
        //utext_setNativeIndex(text, rangeStart + i);
        utext_setNativeIndex(&normalizedText, i);
        bool is_katakana = isKatakana(utext_current32(&normalizedText));
        if (!is_prev_katakana && is_katakana) {
            int j = i + 1;
            utext_next32(&normalizedText);
            // Find the end of the continuous run of Katakana characters
            while (j < numChars && (j - i) < kMaxKatakanaGroupLength &&
                    isKatakana(utext_current32(&normalizedText))) {
                utext_next32(&normalizedText);
                ++j;
            }
            if ((j - i) < kMaxKatakanaGroupLength) {
                uint32_t newSnlp = bestSnlp[i] + getKatakanaCost(j - i);
                if (newSnlp < bestSnlp[j]) {
                    bestSnlp[j] = newSnlp;
                    prev[j] = i;
                }
            }
        }
        is_prev_katakana = is_katakana;
    }

    // Start pushing the optimal offset index into t_boundary (t for tentative).
    // prev[numChars] is guaranteed to be meaningful.
    // We'll first push in the reverse order, i.e.,
    // t_boundary[0] = numChars, and afterwards do a swap.
    // TODO: Replace by UVector32.
    AutoBuffer<int, maxWordSize> t_boundary(numChars + 1);

    int numBreaks = 0;
    // No segmentation found, set boundary to end of range
    if (bestSnlp[numChars] == kuint32max) {
        t_boundary[numBreaks++] = numChars;
    } else {
        for (int i = numChars; i > 0; i = prev[i]) {
            t_boundary[numBreaks++] = i;
        }
        U_ASSERT(prev[t_boundary[numBreaks - 1]] == 0);
    }

    // Reverse offset index in t_boundary.
    // Don't add a break for the start of the dictionary range if there is one
    // there already.
    if (foundBreaks.size() == 0 || foundBreaks.peeki() < rangeStart) {
        t_boundary[numBreaks++] = 0;
    }

    // Now that we're done, convert positions in t_bdry[] (indices in 
    // the normalized input string) back to indices in the raw input string
    // while reversing t_bdry and pushing values to foundBreaks.
    for (int i = numBreaks-1; i >= 0; i--) {
        foundBreaks.push(charPositions[t_boundary[i]] + rangeStart, status);
    }

    utext_close(&normalizedText);
    return numBreaks;
}