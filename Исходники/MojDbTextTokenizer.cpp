MojErr MojDbTextTokenizer::tokenize(const MojString& text, MojDbTextCollator* collator, KeySet& keysOut) const
{
    LOG_TRACE("Entering function %s", __FUNCTION__);
    MojAssert(m_ubrk.get());

    // convert to UChar from str
    MojDbTextUtils::UnicodeVec unicodeStr;
    MojErr err = MojDbTextUtils::strToUnicode(text, unicodeStr);
    MojErrCheck(err);

    // clone break iterator and set text
    MojByte buf[U_BRK_SAFECLONE_BUFFERSIZE];
    UErrorCode status = U_ZERO_ERROR;
    MojInt32 size = sizeof(buf);
    IterPtr ubrk(ubrk_safeClone(m_ubrk.get(), buf, &size, &status));
    MojUnicodeErrCheck(status);
    MojAssert(ubrk.get());
    ubrk_setText(ubrk.get(), unicodeStr.begin(), (MojInt32) unicodeStr.size(), &status);
    MojUnicodeErrCheck(status);

    MojInt32 tokBegin = -1;
    MojInt32 pos = ubrk_first(ubrk.get());
    while (pos != UBRK_DONE) {
        UWordBreak status = (UWordBreak) ubrk_getRuleStatus(ubrk.get());
        if (status != UBRK_WORD_NONE) {
            MojAssert(tokBegin != -1);
            MojDbKey key;
            const UChar* tokChars = unicodeStr.begin() + tokBegin;
            MojSize tokSize = (MojSize) (pos - tokBegin);
            if (collator) {
                err = collator->sortKey(tokChars, tokSize, key);
                MojErrCheck(err);
            } else {
                MojString tok;
                err = MojDbTextUtils::unicodeToStr(tokChars, tokSize, tok);
                MojErrCheck(err);
                err = key.assign(tok);
                MojErrCheck(err);
            }
            err = keysOut.put(key);
            MojErrCheck(err);
        }
        tokBegin = pos;
        pos = ubrk_next(ubrk.get());
    }
    return MojErrNone;
}