static UnicodeString &getWindowsFormat(int32_t lcid, UBool currency, UnicodeString &appendTo, const wchar_t *fmt, ...)
{
    wchar_t nStackBuffer[STACK_BUFFER_SIZE];
    wchar_t *nBuffer = nStackBuffer;
    va_list args;
    int result;

    nBuffer[0] = 0x0000;

    /* Due to the arguments causing a result to be <= 23 characters (+2 for NULL and minus),
    we don't need to reallocate the buffer. */
    va_start(args, fmt);
    result = _vsnwprintf(nBuffer, STACK_BUFFER_SIZE, fmt, args);
    va_end(args);

    /* Just to make sure of the above statement, we add this assert */
    U_ASSERT(result >=0);
    // The following code is not used because _vscwprintf isn't available on MinGW at the moment.
    /*if (result < 0) {
        int newLength;

        va_start(args, fmt);
        newLength = _vscwprintf(fmt, args);
        va_end(args);

        nBuffer = NEW_ARRAY(UChar, newLength + 1);

        va_start(args, fmt);
        result = _vsnwprintf(nBuffer, newLength + 1, fmt, args);
        va_end(args);
    }*/


    // vswprintf is sensitive to the locale set by setlocale. For some locales
    // it doesn't use "." as the decimal separator, which is what GetNumberFormatW
    // and GetCurrencyFormatW both expect to see.
    //
    // To fix this, we scan over the string and replace the first non-digits, except
    // for a leading "-", with a "."
    //
    // Note: (nBuffer[0] == L'-') will evaluate to 1 if there is a leading '-' in the
    // number, and 0 otherwise.
    for (wchar_t *p = &nBuffer[nBuffer[0] == L'-']; *p != L'\0'; p += 1) {
        if (*p < L'0' || *p > L'9') {
            *p = L'.';
            break;
        }
    }

    wchar_t stackBuffer[STACK_BUFFER_SIZE];
    wchar_t *buffer = stackBuffer;

    buffer[0] = 0x0000;

    if (currency) {
        result = GetCurrencyFormatW(lcid, 0, nBuffer, NULL, buffer, STACK_BUFFER_SIZE);

        if (result == 0) {
            DWORD lastError = GetLastError();

            if (lastError == ERROR_INSUFFICIENT_BUFFER) {
                int newLength = GetCurrencyFormatW(lcid, 0, nBuffer, NULL, NULL, 0);

                buffer = NEW_ARRAY(UChar, newLength);
                buffer[0] = 0x0000;
                GetCurrencyFormatW(lcid, 0, nBuffer, NULL, buffer, newLength);
            }
        }
    } else {
        result = GetNumberFormatW(lcid, 0, nBuffer, NULL, buffer, STACK_BUFFER_SIZE);

        if (result == 0) {
            DWORD lastError = GetLastError();

            if (lastError == ERROR_INSUFFICIENT_BUFFER) {
                int newLength = GetNumberFormatW(lcid, 0, nBuffer, NULL, NULL, 0);

                buffer = NEW_ARRAY(UChar, newLength);
                buffer[0] = 0x0000;
                GetNumberFormatW(lcid, 0, nBuffer, NULL, buffer, newLength);
            }
        }
    }

    appendTo.append(buffer, (int32_t) wcslen(buffer));

    if (buffer != stackBuffer) {
        DELETE_ARRAY(buffer);
    }

    /*if (nBuffer != nStackBuffer) {
        DELETE_ARRAY(nBuffer);
    }*/

    return appendTo;
}