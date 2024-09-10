int32_t CharsetMatch::getUChars(UChar *buf, int32_t cap, UErrorCode *status) const
{
    UConverter *conv = ucnv_open(getName(), status);
    int32_t result = ucnv_toUChars(conv, buf, cap, (const char *) textIn->fRawInput, textIn->fRawLength, status);

    ucnv_close(conv);

    return result;
}