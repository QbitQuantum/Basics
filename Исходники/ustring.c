/* Parse a single escape sequence.  Although this method deals in
 * UChars, it does not use C++ or UnicodeString.  This allows it to
 * be used from C contexts. */
U_CAPI UChar32 U_EXPORT2
u_unescapeAt(UNESCAPE_CHAR_AT charAt,
             int32_t* offset,
             int32_t length,
             void* context) {

    int32_t start = *offset;
    UChar c;
    UChar32 result = 0;
    int8_t n = 0;
    int8_t minDig = 0;
    int8_t maxDig = 0;
    int8_t bitsPerDigit = 4;
    int8_t dig;
    int32_t i;
    UBool braces = FALSE;

    /* Check that offset is in range */
    if (*offset < 0 || *offset >= length) {
        goto err;
    }

    /* Fetch first UChar after '\\' */
    c = charAt((*offset)++, context);

    /* Convert hexadecimal and octal escapes */
    switch (c) {
        case 0x0075 /*'u'*/:
            minDig = maxDig = 4;
            break;
        case 0x0055 /*'U'*/:
            minDig = maxDig = 8;
            break;
        case 0x0078 /*'x'*/:
            minDig = 1;
            if (*offset < length && charAt(*offset, context) == 0x7B /*{*/) {
                ++(*offset);
                braces = TRUE;
                maxDig = 8;
            } else {
                maxDig = 2;
            }
            break;
        default:
            dig = _digit8(c);
            if (dig >= 0) {
                minDig = 1;
                maxDig = 3;
                n = 1; /* Already have first octal digit */
                bitsPerDigit = 3;
                result = dig;
            }
            break;
    }
    if (minDig != 0) {
        while (*offset < length && n < maxDig) {
            c = charAt(*offset, context);
            dig = (int8_t) ((bitsPerDigit == 3) ? _digit8(c) : _digit16(c));
            if (dig < 0) {
                break;
            }
            result = (result << bitsPerDigit) | dig;
            ++(*offset);
            ++n;
        }
        if (n < minDig) {
            goto err;
        }
        if (braces) {
            if (c != 0x7D /*}*/) {
                goto err;
            }
            ++(*offset);
        }
        if (result < 0 || result >= 0x110000) {
            goto err;
        }
        /* If an escape sequence specifies a lead surrogate, see if
         * there is a trail surrogate after it, either as an escape or
         * as a literal.  If so, join them up into a supplementary.
         */
        if (*offset < length && U16_IS_LEAD(result)) {
            int32_t ahead = *offset + 1;
            c = charAt(*offset, context);
            if (c == 0x5C /*'\\'*/ && ahead < length) {
                c = (UChar) u_unescapeAt(charAt, &ahead, length, context);
            }
            if (U16_IS_TRAIL(c)) {
                *offset = ahead;
                result = U16_GET_SUPPLEMENTARY(result, c);
            }
        }
        return result;
    }

    /* Convert C-style escapes in table */
    for (i = 0; i < UNESCAPE_MAP_LENGTH; i += 2) {
        if (c == UNESCAPE_MAP[i]) {
            return UNESCAPE_MAP[i + 1];
        } else if (c < UNESCAPE_MAP[i]) {
            break;
        }
    }

    /* Map \cX to control-X: X & 0x1F */
    if (c == 0x0063 /*'c'*/ && *offset < length) {
        c = charAt((*offset)++, context);
        if (UTF_IS_FIRST_SURROGATE(c) && *offset < length) {
            UChar c2 = charAt(*offset, context);
            if (UTF_IS_SECOND_SURROGATE(c2)) {
                ++(*offset);
                c = (UChar) UTF16_GET_PAIR_VALUE(c, c2); /* [sic] */
            }
        }
        return 0x1F & c;
    }

    /* If no special forms are recognized, then consider
     * the backslash to generically escape the next character.
     * Deal with surrogate pairs. */
    if (UTF_IS_FIRST_SURROGATE(c) && *offset < length) {
        UChar c2 = charAt(*offset, context);
        if (UTF_IS_SECOND_SURROGATE(c2)) {
            ++(*offset);
            return UTF16_GET_PAIR_VALUE(c, c2);
        }
    }
    return c;

    err:
    /* Invalid escape sequence */
    *offset = start; /* Reset to initial value */
    return (UChar32) 0xFFFFFFFF;
}