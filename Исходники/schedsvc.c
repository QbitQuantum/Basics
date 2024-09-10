static int detect_encoding(const void *buffer, DWORD size)
{
    if (size >= sizeof(bom_utf8) && !memcmp(buffer, bom_utf8, sizeof(bom_utf8)))
        return CP_UTF8;
    else
    {
        int flags = IS_TEXT_UNICODE_SIGNATURE |
                    IS_TEXT_UNICODE_REVERSE_SIGNATURE |
                    IS_TEXT_UNICODE_ODD_LENGTH;
        IsTextUnicode(buffer, size, &flags);
        if (flags & IS_TEXT_UNICODE_SIGNATURE)
            return -1;
        if (flags & IS_TEXT_UNICODE_REVERSE_SIGNATURE)
            return -2;
        return CP_ACP;
    }
}