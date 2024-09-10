void Stringifier::appendQuotedString(UStringBuilder& builder, const UString& value)
{
    int length = value.length();

    // String length plus 2 for quote marks plus 8 so we can accomodate a few escaped characters.
    builder.reserveCapacity(builder.length() + length + 2 + 8);

    builder.append('"');

    const UChar* data = value.characters();
    for (int i = 0; i < length; ++i) {
        int start = i;
        while (i < length && (data[i] > 0x1F && data[i] != '"' && data[i] != '\\'))
            ++i;
        builder.append(data + start, i - start);
        if (i >= length)
            break;
        switch (data[i]) {
            case '\t':
                builder.append('\\');
                builder.append('t');
                break;
            case '\r':
                builder.append('\\');
                builder.append('r');
                break;
            case '\n':
                builder.append('\\');
                builder.append('n');
                break;
            case '\f':
                builder.append('\\');
                builder.append('f');
                break;
            case '\b':
                builder.append('\\');
                builder.append('b');
                break;
            case '"':
                builder.append('\\');
                builder.append('"');
                break;
            case '\\':
                builder.append('\\');
                builder.append('\\');
                break;
            default:
                static const char hexDigits[] = "0123456789abcdef";
                UChar ch = data[i];
                UChar hex[] = { '\\', 'u', hexDigits[(ch >> 12) & 0xF], hexDigits[(ch >> 8) & 0xF], hexDigits[(ch >> 4) & 0xF], hexDigits[ch & 0xF] };
                builder.append(hex, WTF_ARRAY_LENGTH(hex));
                break;
        }
    }