void KWQFindSentenceBoundary(const QChar *chars, int len, int position, int *start, int *end)
{
    int  startPos = 0;
    int  endPos = 0;

    UErrorCode status = U_ZERO_ERROR;
    UBreakIterator *boundary = ubrk_open(UBRK_SENTENCE, (const char*)currentTextBreakLocaleID().c_str(), const_cast<UChar *>(reinterpret_cast<const UChar *>(chars)), len, &status);
    if ( boundary && U_SUCCESS(status) ) {
        startPos = ubrk_preceding(boundary, position);
        if (startPos == UBRK_DONE) {
            startPos = 0;
        } 
        endPos = ubrk_following(boundary, startPos);
        if (endPos == UBRK_DONE)
            endPos = len;

        ubrk_close(boundary);
    }
    
    *start = startPos;
    *end = endPos;
}