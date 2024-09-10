U_IO_API STD_OSTREAM & U_EXPORT2
operator<<(STD_OSTREAM& stream, const UnicodeString& str)
{
    if(str.length() > 0) {
        char buffer[200];
        UConverter *converter;
        UErrorCode errorCode = U_ZERO_ERROR;

        // use the default converter to convert chunks of text
        converter = u_getDefaultConverter(&errorCode);
        if(U_SUCCESS(errorCode)) {
            const UChar *us = str.getBuffer();
            const UChar *uLimit = us + str.length();
            char *s, *sLimit = buffer + (sizeof(buffer) - 1);
            do {
                errorCode = U_ZERO_ERROR;
                s = buffer;
                ucnv_fromUnicode(converter, &s, sLimit, &us, uLimit, 0, FALSE, &errorCode);
                *s = 0;

                // write this chunk
                if(s > buffer) {
                    stream << buffer;
                }
            } while(errorCode == U_BUFFER_OVERFLOW_ERROR);
            u_releaseDefaultConverter(converter);
        }
    }

/*    stream.flush();*/
    return stream;
}