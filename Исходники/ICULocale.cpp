PassOwnPtr<Vector<String> > ICULocale::createLabelVector(UDateFormatSymbolType type, int32_t startIndex, int32_t size)
{
    if (!m_shortDateFormat)
        return PassOwnPtr<Vector<String> >();
    if (udat_countSymbols(m_shortDateFormat, type) != startIndex + size)
        return PassOwnPtr<Vector<String> >();

    OwnPtr<Vector<String> > labels = adoptPtr(new Vector<String>());
    labels->reserveCapacity(size);
    for (int32_t i = 0; i < size; ++i) {
        UErrorCode status = U_ZERO_ERROR;
        int32_t length = udat_getSymbols(m_shortDateFormat, type, startIndex + i, 0, 0, &status);
        if (status != U_BUFFER_OVERFLOW_ERROR)
            return PassOwnPtr<Vector<String> >();
        Vector<UChar> buffer(length);
        status = U_ZERO_ERROR;
        udat_getSymbols(m_shortDateFormat, type, startIndex + i, buffer.data(), length, &status);
        if (U_FAILURE(status))
            return PassOwnPtr<Vector<String> >();
        labels->append(String::adopt(buffer));
    }
    return labels.release();
}