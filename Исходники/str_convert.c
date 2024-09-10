int str_convert_string(string_encoding_t from_charset, size_t from_length, uint8_t *from_string_p, size_t spare_bits,
                       string_encoding_t to_charset, size_t *to_length_p, uint8_t *to_string_p)
{
    CONVERTER_HANDLE from_conv;
    CONVERTER_HANDLE to_conv;
    bool from_7_bit = false;
    bool to_7_bit = false;
    size_t length;
    uint8_t *string_p;
    int converted = 0;
    int result;


    CN_LOG_D("from_charset=%d, from_length=%d, to_charset=%d, *to_length_p=%d",
             from_charset, from_length, to_charset, *to_length_p);

    if (from_charset == to_charset) {
        /* No conversion, adjust/copy length and strings, and return */
        if (*to_length_p > from_length) {
            *to_length_p = from_length;
        }

        memcpy(to_string_p, from_string_p, *to_length_p);
        to_string_p[*to_length_p] = '\0';
        return from_length;
    }

    /* GSM Default alphabet (7-bit packed) is not supported by the converters.
     * These strings must first be massaged from an array of septets to octets... */
    if (CHARSET_GSM_DEFAULT_7_BIT == from_charset) {
        from_charset = CHARSET_GSM_DEFAULT_8_BIT;
        from_7_bit = true;
    }

    /* or from an array of octets to septets. */
    if (CHARSET_GSM_DEFAULT_7_BIT == to_charset) {
        to_charset = CHARSET_GSM_DEFAULT_8_BIT;
        to_7_bit = true;
    }

    /* (Al)Locate converter(s) */
    result = str_convert_get_converter(from_charset, &from_conv, to_charset, &to_conv);

    if (result < 0) {
        CN_LOG_E("Unable to convert from character set %d to %d!", from_charset, to_charset);
        return result;
    }

    /* Run zeroth conversion */
    if (from_7_bit) {
        length = from_length + from_length / 7;
        string_p = (uint8_t *)alloca(length + 1);
        length = str_convert_septet_to_octet(from_length, from_string_p, spare_bits, length, string_p);
    } else {
        length = from_length;
        string_p = from_string_p;
    }

    /* Run first conversion */
#ifdef USE_ICONV
    int errnum;
    char *inbuf_p = string_p;
    size_t inbytesleft = (size_t)length;
    char *outbuf_p;
    char *outstr_p;
    size_t outbytesleft, outstr_length;
    size_t res;

    /* Allocate memory to hold result string and call ICONV to perform the conversion.
     * Assume worst case, 1 input character becomes 4 output characters. */
    outstr_length = outbytesleft = (length + 1) * sizeof(uint32_t);
    outstr_p = outbuf_p = (char *)alloca(outbytesleft);

    res = iconv(from_conv,
                &inbuf_p, &inbytesleft,
                &outbuf_p, &outbytesleft);

    /* Check for errors */
    if (res == (size_t) - 1) {
        errnum = errno;
        CN_LOG_E("iconv error %d (%s) !", errnum, strerror(errnum));
        return -1;
    }

    /* Find out how many bytes iconv actualy used for the converted string */
    outstr_length -= outbytesleft;

#elif USE_UCNV
    UChar *ustr_p;
    int32_t ustr_length;
    UErrorCode errcode = U_ZERO_ERROR;
    int32_t res;

    if (str_convert_is_utf_16(from_charset)) {
        /* From string is already UTF-16 encoded. Skip this conversion step */
        ustr_length = length;
        ustr_p = (UChar *)string_p;
    } else {
        /* Allocate memory to hold result string and call ICU to perform the conversion */
        ustr_length = length + 1;
        ustr_p = (UChar *)alloca((size_t)(ustr_length * sizeof(UChar)));

        res = ucnv_toUChars(from_conv,
                            ustr_p, ustr_length,
                            (const char *)string_p, length,
                            &errcode);

        if (res < 0) {
            CN_LOG_E("ucnv_toUChars res %d!", res);
            return -1;
        }

        /* Check for errors, ignore warnings */
        if (U_ZERO_ERROR != errcode && errcode > U_ERROR_WARNING_LIMIT) {
            CN_LOG_E("ucnv_toUChars error code %d!", errcode);
            return -1;
        }

#ifdef CN_DEBUG_ENABLED
        {
            char datastr[100] = { '\0' };
            char str[10];
            int i;

            for (i = 0; i < 30 && i < res; i++) {
                sprintf(str, "%02X ", *(ustr_p + i));
                strcat(datastr, str);
            }

            CN_LOG_D("ucnv_toUChars(conv=%p, charset=%d, ustr=\"%s\") = %d",
                     (void *)from_conv,
                     from_charset,
                     datastr,
                     res);
        }
#endif /* CN_DEBUG_ENABLED */

        ustr_length = res;
    }

#endif /* USE_UCNV */

    /* Run second conversion, unless it is the same converter as we ran before */
    if (to_conv == from_conv) {
        /* One step conversion, copy result to output parameters and return */
#ifdef USE_ICONV
        /* ICONV uses a one step conversion */

        if (*to_length_p > outstr_length) {
            *to_length_p = outstr_length;
        }

        memcpy(to_string_p, outstr_p, *to_length_p);
        to_string_p[*to_length_p] = '\0';
        converted = outstr_length;

#elif USE_UCNV

        if (*to_length_p > (size_t)ustr_length) {
            *to_length_p = (size_t)ustr_length;
        }

        memcpy(to_string_p, ustr_p, *to_length_p);
        to_string_p[*to_length_p] = '\0';
        converted = ustr_length;
#endif
    } else {
#ifdef USE_UCNV
        res = ucnv_fromUChars(to_conv,
                              (char *)to_string_p, (int32_t) * to_length_p,
                              ustr_p, ustr_length,
                              &errcode);

        /* Check for errors, ignore warnings */
        if (U_ZERO_ERROR != errcode && errcode > U_ERROR_WARNING_LIMIT) {
            CN_LOG_E("ucnv_fromUChars error code %d!", errcode);
            return -1;
        }

        if (*to_length_p > (size_t)res) {
            *to_length_p = (size_t)res;
        }

#ifdef CN_DEBUG_ENABLED
        {
            char datastr[100] = { '\0' };
            char str[10];
            int i;

            for (i = 0; i < 30 && i < res; i++) {
                sprintf(str, "%02X ", *(to_string_p + i));
                strcat(datastr, str);
            }

            CN_LOG_D("ucnv_fromUChars(conv=%p, charset=%d, str=\"%s\") = %d",
                     (void *)to_conv,
                     to_charset,
                     datastr,
                     res);
        }
#endif /* CN_DEBUG_ENABLED */

        converted = res;
#endif
    }

    /* Run final conversion, convert in-place */
    if (to_7_bit) {
        converted = str_convert_octet_to_septet(converted, to_string_p, converted, to_string_p);
    }

    return converted;
}