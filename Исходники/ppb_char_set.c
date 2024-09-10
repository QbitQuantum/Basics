char *
ppb_char_set_utf16_to_char_set(PP_Instance instance, const uint16_t *utf16, uint32_t utf16_len,
                               const char *output_char_set,
                               enum PP_CharSet_ConversionError on_error, uint32_t *output_length)
{
    // each character could take up to 4 bytes in UTF-8; with additional zero-terminator byte
    const uint32_t output_buffer_length = (utf16_len + 1) * 4 + 1;
    char *output = ppb_memory_mem_alloc(output_buffer_length);

    if (!output) {
        trace_error("%s, can't allocate memory, %u bytes\n", __func__, output_buffer_length);
        goto err;
    }

    const char *charset = encoding_alias_get_canonical_name(output_char_set);

    const UChar subst = '?';
    UErrorCode st = U_ZERO_ERROR;
    UConverter *u = ucnv_open(charset, &st);
    if (!U_SUCCESS(st)) {
        trace_error("%s, wrong charset %s\n", __func__, output_char_set);
        goto err;
    }

    switch (on_error) {
    default:
    case PP_CHARSET_CONVERSIONERROR_FAIL:
        st = U_ZERO_ERROR;
        ucnv_setFromUCallBack(u, UCNV_FROM_U_CALLBACK_STOP, NULL, NULL, NULL, &st);
        break;

    case PP_CHARSET_CONVERSIONERROR_SKIP:
        st = U_ZERO_ERROR;
        ucnv_setFromUCallBack(u, UCNV_FROM_U_CALLBACK_SKIP, NULL, NULL, NULL, &st);
        break;

    case PP_CHARSET_CONVERSIONERROR_SUBSTITUTE:
        st = U_ZERO_ERROR;
        ucnv_setFromUCallBack(u, UCNV_FROM_U_CALLBACK_SUBSTITUTE, NULL, NULL, NULL, &st);

        st = U_ZERO_ERROR;
        ucnv_setSubstString(u, &subst, 1, &st);
        break;
    }

    *output_length = ucnv_fromUChars(u, output, output_buffer_length, utf16, utf16_len, &st);

    if (st != U_BUFFER_OVERFLOW_ERROR && !U_SUCCESS(st))
        goto err;

    ucnv_close(u);
    return output;

err:
    *output_length = 0;
    ppb_memory_mem_free(output);
    if (u)
        ucnv_close(u);
    return NULL;
}