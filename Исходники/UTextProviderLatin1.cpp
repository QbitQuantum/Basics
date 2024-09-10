UText* openLatin1UTextProvider(UTextWithBuffer* utWithBuffer, const LChar* string, unsigned length, UErrorCode* status)
{
    if (U_FAILURE(*status))
        return nullptr;
    if (!string || length > static_cast<unsigned>(std::numeric_limits<int32_t>::max())) {
        *status = U_ILLEGAL_ARGUMENT_ERROR;
        return nullptr;
    }
    UText* text = utext_setup(&utWithBuffer->text, sizeof(utWithBuffer->buffer), status);
    if (U_FAILURE(*status)) {
        ASSERT(!text);
        return nullptr;
    }

    text->context = string;
    text->a = length;
    text->pFuncs = &uTextLatin1Funcs;
    text->chunkContents = (UChar*)text->pExtra;
    memset(const_cast<UChar*>(text->chunkContents), 0, sizeof(UChar) * UTextWithBufferInlineCapacity);

    return text;
}