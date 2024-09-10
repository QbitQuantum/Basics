void RegExpFunctionalTestCollector::outputEscapedUString(const UString& s, bool escapeSlash)
{
    int len = s.length();
    
    for (int i = 0; i < len; ++i) {
        UChar c = s[i];

        switch (c) {
        case '\0':
            fputs("\\0", m_file);
            break;
        case '\a':
            fputs("\\a", m_file);
            break;
        case '\b':
            fputs("\\b", m_file);
            break;
        case '\f':
            fputs("\\f", m_file);
            break;
        case '\n':
            fputs("\\n", m_file);
            break;
        case '\r':
            fputs("\\r", m_file);
            break;
        case '\t':
            fputs("\\t", m_file);
            break;
        case '\v':
            fputs("\\v", m_file);
            break;
        case '/':
            if (escapeSlash)
                fputs("\\/", m_file);
            else
                fputs("/", m_file);
            break;
        case '\"':
            fputs("\\\"", m_file);
            break;
        case '\\':
            fputs("\\\\", m_file);
            break;
        case '\?':
            fputs("\?", m_file);
            break;
        default:
            if (c > 0x7f)
                fprintf(m_file, "\\u%04x", c);
            else 
                fputc(c, m_file);
            break;
        }
    }
}