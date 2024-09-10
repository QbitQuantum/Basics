UErrorCode
detect_ICU(const text* buffer, text** encoding, text** lang, int32_t* confidence)
{
    const char* cbuffer = text_to_cstring(buffer);
    //int cbuffer_len = strlen(cbuffer);

    UCharsetDetector* csd;
    const UCharsetMatch* csm;
    UErrorCode status = U_ZERO_ERROR;

    csd = ucsdet_open(&status);

    // set text buffer
    // use -1 for string length since NUL terminated
    ucsdet_setText(csd, cbuffer, STRING_IS_NULL_TERMINATED, &status);
    //ucsdet_setText(csd, cbuffer, cbuffer_len, &status);

    // detect charset
    csm = ucsdet_detect(csd, &status);

    // charset match is NULL if no match
    if (NULL == csm)
    {
        ereport(WARNING,
            (errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
             errmsg("ICU error: No charset match for \"%s\" - assuming ISO-8859-1.", cbuffer)));

        *encoding = cstring_to_text("ISO-8859-1");
        *lang = NULL;
        *confidence = 0;

        ucsdet_close(csd);
        pfree((void *) cbuffer);
        return status;
    }
    else if (U_FAILURE(status))
    {
        ereport(WARNING,
            (errcode(ERRCODE_EXTERNAL_ROUTINE_EXCEPTION),
             errmsg("ICU error: %s\n", u_errorName(status))));

        *encoding = NULL;
        *lang = NULL;
        *confidence = 0;

        ucsdet_close(csd);
        pfree((void *) cbuffer);
        return status;
    }

    *encoding = cstring_to_text(ucsdet_getName(csm, &status));
    *lang = cstring_to_text(ucsdet_getLanguage(csm, &status));
    *confidence = ucsdet_getConfidence(csm, &status);

    // close charset detector
    // UCharsetMatch is owned by UCharsetDetector so its memory will be
    // freed when the char set detector is closed
    ucsdet_close(csd);
    pfree((void *) cbuffer);
    return status;
}