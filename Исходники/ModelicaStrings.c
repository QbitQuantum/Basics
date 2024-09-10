void ModelicaStrings_scanInteger(_In_z_ const char* string,
                                 int startIndex, int unsignedNumber,
                                 _Out_ int* nextIndex, _Out_ int* integerNumber) {
    int sign = 0;
    /* Number of characters used for sign. */

    int token_start = ModelicaStrings_skipWhiteSpace(string, startIndex);
    /* Index of first char of token, after ws. */

    if (string[token_start-1] == '+' || string[token_start-1] == '-') {
        sign = 1;
    }

    if (unsignedNumber==0 || (unsignedNumber==1 && sign==0)) {
        int number_length = MatchUnsignedInteger(string, token_start + sign);
        /* Number of characters in unsigned number. */

        if (number_length > 0 && sign + number_length < MAX_TOKEN_SIZE) {
            /* check if the scanned string is no Real number */
            int next = token_start + sign + number_length - 1;
            if ( string[next] == '\0' ||
                (string[next] != '.'  && string[next] != 'e'
                                      && string[next] != 'E') ) {
#if defined(NO_LOCALE)
#elif defined(_MSC_VER) && _MSC_VER >= 1400
                _locale_t loc = _create_locale(LC_NUMERIC, "C");
#elif defined(__GLIBC__) && defined(__GLIBC_MINOR__) && ((__GLIBC__ << 16) + __GLIBC_MINOR__ >= (2 << 16) + 3)
                locale_t loc = newlocale(LC_NUMERIC, "C", NULL);
#endif
                char buf[MAX_TOKEN_SIZE+1];
                /* Buffer for copying the part recognized as the number for passing to strtol(). */
                char* endptr;
                /* For error checking of strtol(). */
                int x;
                /* For receiving the result. */

                strncpy(buf, string+token_start-1, (size_t)(sign + number_length));
                buf[sign + number_length] = '\0';
#if !defined(NO_LOCALE) && (defined(_MSC_VER) && _MSC_VER >= 1400)
                x = (int)_strtol_l(buf, &endptr, 10, loc);
                _free_locale(loc);
#elif !defined(NO_LOCALE) && (defined(__GLIBC__) && defined(__GLIBC_MINOR__) && ((__GLIBC__ << 16) + __GLIBC_MINOR__ >= (2 << 16) + 3))
                x = (int)strtol_l(buf, &endptr, 10, loc);
                freelocale(loc);
#else
                x = (int)strtol(buf, &endptr, 10);
#endif
                if (*endptr == 0) {
                    *integerNumber = x;
                    *nextIndex = token_start + sign + number_length;
                    return;
                }
            }
        }
    }

    /* Token missing or cannot be converted to result type. */
    *nextIndex     = startIndex;
    *integerNumber = 0;
    return;
}