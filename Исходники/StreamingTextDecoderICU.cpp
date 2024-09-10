DeprecatedString StreamingTextDecoderICU::convertUsingICU(const unsigned char* chs, int len, bool flush)
{
    // Get a converter for the passed-in encoding.
    if (!m_converterICU) {
        createICUConverter();
        if (!m_converterICU)
            return DeprecatedString();
    }

    DeprecatedString result("");
    result.reserve(len);

    UChar buffer[ConversionBufferSize];
    const char* source = reinterpret_cast<const char*>(chs);
    const char* sourceLimit = source + len;
    int32_t* offsets = NULL;
    UErrorCode err;

    do {
        UChar* target = buffer;
        const UChar* targetLimit = target + ConversionBufferSize;
        err = U_ZERO_ERROR;
        ucnv_toUnicode(m_converterICU, &target, targetLimit, &source, sourceLimit, offsets, flush, &err);
        int count = target - buffer;
        appendOmittingBOM(result, reinterpret_cast<const UChar*>(buffer), count * sizeof(UChar));
    } while (err == U_BUFFER_OVERFLOW_ERROR);

    if (U_FAILURE(err)) {
        // flush the converter so it can be reused, and not be bothered by this error.
        do {
            UChar *target = buffer;
            const UChar *targetLimit = target + ConversionBufferSize;
            err = U_ZERO_ERROR;
            ucnv_toUnicode(m_converterICU, &target, targetLimit, &source, sourceLimit, offsets, true, &err);
        } while (source < sourceLimit);
        LOG_ERROR("ICU conversion error");
        return DeprecatedString();
    }

    return result;
}