int32_t BytesDictionaryMatcher::matches(UText *text, int32_t maxLength, int32_t limit,
                            int32_t *lengths, int32_t *cpLengths, int32_t *values,
                            int32_t *prefix) const {
    BytesTrie bt(characters);
    int32_t startingTextIndex = (int32_t)utext_getNativeIndex(text);
    int32_t wordCount = 0;
    int32_t codePointsMatched = 0;

    for (UChar32 c = utext_next32(text); c >= 0; c=utext_next32(text)) {
        UStringTrieResult result = (codePointsMatched == 0) ? bt.first(transform(c)) : bt.next(transform(c));
        int32_t lengthMatched = (int32_t)utext_getNativeIndex(text) - startingTextIndex;
        codePointsMatched += 1;
        if (USTRINGTRIE_HAS_VALUE(result)) {
            if (wordCount < limit) {
                if (values != NULL) {
                    values[wordCount] = bt.getValue();
                }
                if (lengths != NULL) {
                    lengths[wordCount] = lengthMatched;
                }
                if (cpLengths != NULL) {
                    cpLengths[wordCount] = codePointsMatched;
                }
                ++wordCount;
            }
            if (result == USTRINGTRIE_FINAL_VALUE) {
                break;
            }
        }
        else if (result == USTRINGTRIE_NO_MATCH) {
            break;
        }
        if (lengthMatched >= maxLength) {
            break;
        }
    }

    if (prefix != NULL) {
        *prefix = codePointsMatched;
    }
    return wordCount;
}