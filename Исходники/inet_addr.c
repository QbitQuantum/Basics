bool
inet_aton(const char *s, in_addr_t *addr)
{
    int i, val, radix, digit;
    unsigned long res = 0;
    bool first;
    char c;
    
    for (i = 0;  i < 4;  i++) {
        // Parse next digit string
        first = true;
        val = 0;
        radix = 10;
        while ((c = *s++) != '\0') {
            if (first && (c == '0') && (_tolower(*s) == 'x')) {
                radix = 16;
                s++;  // Skip over 0x
                c = *s++;
            }
            first = false;
            if (_is_hex(c) && ((digit = _from_hex(c)) < radix)) {
                // Valid digit
                val = (val * radix) + digit;
            } else if (c == '.' && i < 3) { // all but last terminate by '.'
                break;
            } else {
                return false;
            }
        }
        // merge result
#ifdef __LITTLE_ENDIAN__
        res |= val << ((3-i)*8);  // 24, 16, 8, 0
#else
        res = (res << 8) | val;
#endif
        if ('\0' == c) {
            if (0 == i) { // first field found end of string
                res = val; // no shifting, use it as the whole thing
                break; // permit entering a single number
            }
            if (3 > i) // we found end of string before getting 4 fields
                return false;
        }
        // after that we check that it was 0..255 only
        if (val &~0xff) return false;
    }
    addr->s_addr = htonl(res);
    return true;
}