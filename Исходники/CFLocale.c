static bool __CFLocaleICUCurrencyName(const char *locale, const char *value, UCurrNameStyle style, CFStringRef *out) {
    size_t valLen = strlen(value);
    if (valLen != 3) // not a valid ISO code
        return false;
    UChar curr[4];
    UBool isChoice = FALSE;
    int32_t size = 0;
    UErrorCode icuStatus = U_ZERO_ERROR;
    u_charsToUChars(value, curr, (int32_t)valLen);
    curr[valLen] = '\0';
    const UChar *name;
    name = ucurr_getName(curr, locale, style, &isChoice, &size, &icuStatus);
    if (U_FAILURE(icuStatus) || icuStatus == U_USING_DEFAULT_WARNING)
        return false;
    UChar result[kMaxICUNameSize];
    if (isChoice)
    {
        UChar pattern[kMaxICUNameSize];
        CFStringRef patternRef = CFStringCreateWithFormat(kCFAllocatorSystemDefault, NULL, CFSTR("{0,choice,%S}"), name);
        CFIndex pattlen = CFStringGetLength(patternRef);
        CFStringGetCharacters(patternRef, CFRangeMake(0, pattlen), (UniChar *)pattern);
        CFRelease(patternRef);
        pattern[pattlen] = '\0';        // null terminate the pattern
        // Format the message assuming a large amount of the currency
        size = u_formatMessage("en_US", pattern, pattlen, result, kMaxICUNameSize, &icuStatus, 10.0);
        if (U_FAILURE(icuStatus))
            return false;
        name = result;
        
    }
    *out = CFStringCreateWithCharacters(kCFAllocatorSystemDefault, (UniChar *)name, size);
    return (*out != NULL);
}