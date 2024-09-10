U_STABLE UConverter* U_EXPORT2
ucnv_open_emoji(const char *converterName, UErrorCode *err) {
    if (EmojiFont::IsAvailable()) {
        if (strcmp(converterName, "Shift_JIS") == 0)
            converterName = "docomo-emoji";
    }
    return ucnv_open(converterName, err);
}