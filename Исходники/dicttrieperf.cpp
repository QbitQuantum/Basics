// Closely imitate CompactTrieDictionary::matches().
// Note: CompactTrieDictionary::matches() is part of its trie implementation,
// and while it loops over the text, it knows the current state.
// By contrast, this implementation uses UCharsTrie API functions that have to
// check the trie state each time and load/store state in the object.
// (Whether it hasNext() and whether it is in the middle of a linear-match node.)
static int32_t
ucharsTrieMatches(UCharsTrie &trie,
                  UText *text, int32_t textLimit,
                  int32_t *lengths, int &count, int limit ) {
    UChar32 c=utext_next32(text);
    // Notes:
    // a) CompactTrieDictionary::matches() does not check for U_SENTINEL.
    // b) It also ignores non-BMP code points by casting to UChar!
    if(c<0) {
        return 0;
    }
    // Should be firstForCodePoint() but CompactTrieDictionary
    // handles only code units.
    UStringTrieResult result=trie.first(c);
    int32_t numChars=1;
    count=0;
    for(;;) {
        if(USTRINGTRIE_HAS_VALUE(result)) {
            if(count<limit) {
                // lengths[count++]=(int32_t)utext_getNativeIndex(text);
                lengths[count++]=numChars;  // CompactTrieDictionary just counts chars too.
            }
            if(result==USTRINGTRIE_FINAL_VALUE) {
                break;
            }
        } else if(result==USTRINGTRIE_NO_MATCH) {
            break;
        }
        if(numChars>=textLimit) {
            // Note: Why do we have both a text limit and a UText that knows its length?
            break;
        }
        UChar32 c=utext_next32(text);
        // Notes:
        // a) CompactTrieDictionary::matches() does not check for U_SENTINEL.
        // b) It also ignores non-BMP code points by casting to UChar!
        if(c<0) {
            break;
        }
        ++numChars;
        // Should be nextForCodePoint() but CompactTrieDictionary
        // handles only code units.
        result=trie.next(c);
    }
#if 0
    // Note: CompactTrieDictionary::matches() comments say that it leaves the UText
    // after the longest prefix match and returns the number of characters
    // that were matched.
    if(index!=lastMatch) {
        utext_setNativeIndex(text, lastMatch);
    }
    return lastMatch-start;
    // However, it does not do either of these, so I am not trying to
    // imitate it (or its docs) 100%.
#endif
    return numChars;
}