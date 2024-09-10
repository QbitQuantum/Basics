static ULayoutType
_uloc_getOrientationHelper(const char* localeId,
                           const char* key,
                           UErrorCode *status)
{
    ULayoutType result = ULOC_LAYOUT_UNKNOWN;

    if (!U_FAILURE(*status)) {
        int32_t length = 0;
        char localeBuffer[ULOC_FULLNAME_CAPACITY];

        uloc_canonicalize(localeId, localeBuffer, sizeof(localeBuffer), status);

        if (!U_FAILURE(*status)) {
            const UChar* const value =
                uloc_getTableStringWithFallback(
                    NULL,
                    localeBuffer,
                    "layout",
                    NULL,
                    key,
                    &length,
                    status);

            if (!U_FAILURE(*status) && length != 0) {
                switch(value[0])
                {
                case 0x0062: /* 'b' */
                    result = ULOC_LAYOUT_BTT;
                    break;
                case 0x006C: /* 'l' */
                    result = ULOC_LAYOUT_LTR;
                    break;
                case 0x0072: /* 'r' */
                    result = ULOC_LAYOUT_RTL;
                    break;
                case 0x0074: /* 't' */
                    result = ULOC_LAYOUT_TTB;
                    break;
                default:
                    *status = U_INTERNAL_PROGRAM_ERROR;
                    break;
                }
            }
        }
    }

    return result;
}