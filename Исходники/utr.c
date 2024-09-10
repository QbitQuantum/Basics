int32_t grapheme_count(UBreakIterator *ubrk, const UString *ustr)
{
    int32_t i, count;
    UErrorCode status;

    count = 0;
    status = U_ZERO_ERROR;
    ubrk_setText(ubrk, ustr->ptr, ustr->len, &status);
    if (U_FAILURE(status)) {
        return -1;
    }
    if (UBRK_DONE != (i = ubrk_first(ubrk))) {
        while (UBRK_DONE != (i = ubrk_next(ubrk))) {
            ++count;
        }
    }
    ubrk_unbindText(ubrk);

    return count;
}