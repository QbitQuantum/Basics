static char*
convertToUtf8(UConverter* conv, const unsigned char* name, int len)
{
    char* buffer1 = NULL;
    char* buffer2 = NULL;
    int bufSize = -1;

    if (2 * (len + 1) > bufSize) {
        if (buffer1 != NULL) {
            delete[] buffer1;
            delete[] buffer2;
        }
        bufSize = 2 * len + 100;
        buffer1 = new char[bufSize];
        buffer2 = new char[bufSize];
    }

    UErrorCode status = U_ZERO_ERROR;
    len = ucnv_toUChars(conv, (UChar*)buffer1, bufSize, (const char*)name, len, &status);
    len = ucnv_fromUChars(utf8Conv, buffer2, bufSize, (UChar*)buffer1, len, &status);
    buffer2[len] = 0;

    delete[] buffer1;
    return buffer2;
}