void JsonOut::stringPart(const char *s)
{
    for (; *s; s++)
    {
        utf8_t c = (utf8_t) *s;
        switch (c)
        {
            case '\n':
                buf->writestring("\\n");
                break;

            case '\r':
                buf->writestring("\\r");
                break;

            case '\t':
                buf->writestring("\\t");
                break;

            case '\"':
                buf->writestring("\\\"");
                break;

            case '\\':
                buf->writestring("\\\\");
                break;

            case '\b':
                buf->writestring("\\b");
                break;

            case '\f':
                buf->writestring("\\f");
                break;

            default:
                if (c < 0x20)
                    buf->printf("\\u%04x", c);
                else
                    // Note that UTF-8 chars pass through here just fine
                    buf->writeByte(c);
                break;
        }
    }
}