void get_unicode_info(const char* text, const icu::UnicodeString& us, Sqlite::Statement& insert) {
    bool allokay = true;
    for (const char* t = text; *t; ++t) {
        if (!(std::isalnum(*t) || *t == '_' || *t == ':' || *t == ' ' || *t == '.' || *t == '-')) {
            allokay = false;
            break;
        }
    }

    if (allokay) {
        return;
    }

    bool unusual = false;
    for (icu::StringCharacterIterator it(us); it.hasNext(); it.next()) {
        UChar32 codepoint = it.current32();
        int8_t chartype = u_charType(codepoint);
        if (! u_isprint(codepoint)) {
            unusual = true;
            break;
        }
        if (u_charDirection(codepoint) != 0) {
            unusual = true;
            break;
        }
        if (chartype !=  1 && // UPPERCASE_LETTER
            chartype !=  2 && // LOWERCASE_LETTER
            chartype !=  9 && // DECIMAL_DIGIT_NUMBER
            chartype != 12 && // SPACE_SEPARATOR
            chartype != 19 && // DASH_PUNCTUATION
            chartype != 22 && // CONNECTOR_PUNCTUATION
            chartype != 23) { // OTHER_PUNCTUATION
            unusual = true;
            break;
        }
    }

    if (unusual) {
        int num = 0;
        for (icu::StringCharacterIterator it(us); it.hasNext(); it.next(), ++num) {
            UChar32 codepoint = it.current32();

            int8_t chartype = u_charType(codepoint);

            char buffer[100];
            UErrorCode errorCode = U_ZERO_ERROR;
            u_charName(codepoint, U_UNICODE_CHAR_NAME, buffer, sizeof(buffer), &errorCode);

            UCharDirection direction = u_charDirection(codepoint);
            int32_t block = u_getIntPropertyValue(codepoint, UCHAR_BLOCK);

            icu::UnicodeString ustr(codepoint);
            std::string str;
            ustr.toUTF8String(str);

            char uplus[10];
            snprintf(uplus, 10, "U+%04x", codepoint);

            insert.
                bind_text(text).
                bind_int(num).
                bind_text(str.c_str()).
                bind_text(uplus).
                bind_int(block).
                bind_text(category_to_string(chartype)).
                bind_int(direction).
                bind_text(buffer).
                execute();
        }
    }
}