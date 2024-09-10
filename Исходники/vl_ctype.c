/*
 * Return the character-type bits for the given character.  There are several
 * cases.
 *
 * vile supports a 256-entry table for "character classes", which are used
 * mainly to support systems with single-byte encodings.  Some of those (no all
 * older systems) may have incorrect character types; that is the reason for
 * having the ability to change classes at runtime.
 *
 * If use_locale is TRUE, this uses the system's character type functions,
 * (wide if available) e.g., for Unicode.  However, we still allow the
 * character-classes to override.  The simple case is where the wide/narrow
 * encodings coincide (up to latin1_codes).
 *
 * A more complicated case is for narrow encodings such as ISO-8859-2, where
 * latin_codes is less than 256.  Then we have to check first if it corresponds
 * to the narrow encoding before using the system's character type functions.
 *
 * If use_locale is -TRUE (negative), then use the system's 8-bit character
 * tests to get the narrow locale information used as a starting point for the
 * character classes.  On some systems, this may give odd results, but that is
 * why it is configurable.
 *
 * If use_locale is FALSE, then use the 256-entry table of character classes.
 */
CHARTYPE
vl_ctype_bits(int ch, int use_locale GCC_UNUSED)
{
    CHARTYPE result = 0;

    if (ch < 0) {
        ;
    }
#if OPT_LOCALE
    else if (use_locale > 0) {
        int check;

        /* handle case where character-classes can be overridden */
        if (ch < latin1_codes) {
            result = vlCTYPE(ch);
            ch = -1;
        } else if (vl_ucs_to_8bit(&check, ch)) {
            result = vlCTYPE(check);
            ch = -1;
        }

        if (ch >= 0) {
            if (sys_isalpha(ch))
                result |= (vl_ident | vl_pathn | vl_qident);
            if (sys_iscntrl(ch))
                result |= (vl_cntrl);
            if (sys_isdigit(ch))
                result |= (vl_digit | vl_ident | vl_pathn | vl_qident);
            if (sys_islower(ch))
                result |= vl_lower;
            if (sys_isprint(ch) && ch != '\t')
                result |= vl_print;
            if (sys_ispunct(ch))
                result |= vl_punct;
            if (sys_isspace(ch))
                result |= vl_space;
            else
                result |= vl_nonspace;
            if (sys_isupper(ch))
                result |= vl_upper;
#ifdef vl_xdigit
            if (sys_isxdigit(ch))
                result |= vl_xdigit;
#endif
        }
    } else if (use_locale < 0) {
        if (isalpha(ch))
            result |= (vl_ident | vl_pathn | vl_qident);
        if (iscntrl(ch))
            result |= (vl_cntrl);
        if (isdigit(ch))
            result |= (vl_digit | vl_ident | vl_pathn | vl_qident);
        if (islower(ch))
            result |= vl_lower;
        if (isprint(ch) && ch != '\t')
            result |= vl_print;
        if (ispunct(ch))
            result |= vl_punct;
        if (isspace(ch))
            result |= vl_space;
        else
            result |= vl_nonspace;
        if (isupper(ch))
            result |= vl_upper;
#ifdef vl_xdigit
        if (isxdigit(ch))
            result |= vl_xdigit;
#endif
    } else
#endif /* OPT_LOCALE */
        if (ch < N_chars)
            result = vlCTYPE(ch);
    return result;
}