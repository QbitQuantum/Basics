uint32_t
FCDUTF8CollationIterator::handleNextCE32(UChar32 &c, UErrorCode &errorCode) {
    for(;;) {
        if(state == CHECK_FWD) {
            // Combination of UTF8CollationIterator::handleNextCE32() with FCD check fastpath.
            if(pos == length) {
                c = U_SENTINEL;
                return Collation::FALLBACK_CE32;
            }
            c = u8[pos++];
            if(c < 0xc0) {
                // ASCII 00..7F; trail bytes 80..BF map to error values.
                return trie->data32[c];
            }
            uint8_t t1, t2;
            if(c < 0xe0 && pos != length && (t1 = (u8[pos] - 0x80)) <= 0x3f) {
                // U+0080..U+07FF; 00..7F map to error values.
                uint32_t ce32 = trie->data32[trie->index[(UTRIE2_UTF8_2B_INDEX_2_OFFSET - 0xc0) + c] + t1];
                c = ((c & 0x1f) << 6) | t1;
                ++pos;
                if(CollationFCD::hasTccc(c) && pos != length && nextHasLccc()) {
                    pos -= 2;
                } else {
                    return ce32;
                }
            } else if(c <= 0xef &&
                      ((pos + 1) < length || length < 0) &&
                      (t1 = (u8[pos] - 0x80)) <= 0x3f && (c != 0xe0 || t1 >= 0x20) &&
                      (t2 = (u8[pos + 1] - 0x80)) <= 0x3f
            ) {
                // U+0800..U+FFFF; caller maps surrogates to error values.
                c = (UChar)((c << 12) | (t1 << 6) | t2);
                pos += 2;
                if(CollationFCD::hasTccc(c) &&
                        (CollationFCD::maybeTibetanCompositeVowel(c) ||
                            (pos != length && nextHasLccc()))) {
                    pos -= 3;
                } else {
                    break;  // return CE32(BMP)
                }
            } else {
                // Function call for supplementary code points and error cases.
                // Illegal byte sequences yield U+FFFD.
                c = utf8_nextCharSafeBody(u8, &pos, length, c, -3);
                if(c == 0xfffd) {
                    return Collation::FFFD_CE32;
                } else {
                    U_ASSERT(c > 0xffff);
                    if(CollationFCD::hasTccc(U16_LEAD(c)) && pos != length && nextHasLccc()) {
                        pos -= 4;
                    } else {
                        return data->getCE32FromSupplementary(c);
                    }
                }
            }
            if(!nextSegment(errorCode)) {
                c = U_SENTINEL;
                return Collation::FALLBACK_CE32;
            }
            continue;
        } else if(state == IN_FCD_SEGMENT && pos != limit) {
            return UTF8CollationIterator::handleNextCE32(c, errorCode);
        } else if(state == IN_NORMALIZED && pos != normalized.length()) {
            c = normalized[pos++];
            break;
        } else {
            switchToForward();
        }
    }
    return UTRIE2_GET32_FROM_U16_SINGLE_LEAD(trie, c);
}