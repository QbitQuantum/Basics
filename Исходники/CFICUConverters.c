CF_PRIVATE CFStringEncoding __CFStringEncodingGetFromICUName(const char *icuName) {
    uint32_t codepage;
    char *endPtr;
    UErrorCode errorCode = U_ZERO_ERROR;

    if ((0 == strncasecmp_l(icuName, "windows-", strlen("windows-"), NULL)) && (0 != (codepage = strtol(icuName + strlen("windows-"), &endPtr, 10))) && (*endPtr == '\0')) return __CFStringEncodingGetFromWindowsCodePage(codepage);

    if (0 != ucnv_countAliases(icuName, &errorCode)) {
        CFStringEncoding encoding;
        const char *name;

        // Try WINDOWS platform
        name = ucnv_getStandardName(icuName, "WINDOWS", &errorCode);
        
        if (NULL != name) {
            if ((0 == strncasecmp_l(name, "windows-", strlen("windows-"), NULL)) && (0 != (codepage = strtol(name + strlen("windows-"), &endPtr, 10))) && (*endPtr == '\0')) return __CFStringEncodingGetFromWindowsCodePage(codepage);
            
            if (strncasecmp_l(icuName, name, strlen(name), NULL) && (kCFStringEncodingInvalidId != (encoding = __CFStringEncodingGetFromCanonicalName(name)))) return encoding;
        }

        // Try JAVA platform
        name = ucnv_getStandardName(icuName, "JAVA", &errorCode);
        if ((NULL != name) && strncasecmp_l(icuName, name, strlen(name), NULL) && (kCFStringEncodingInvalidId != (encoding = __CFStringEncodingGetFromCanonicalName(name)))) return encoding;

        // Try MIME platform
        name = ucnv_getStandardName(icuName, "MIME", &errorCode);
        if ((NULL != name) && strncasecmp_l(icuName, name, strlen(name), NULL) && (kCFStringEncodingInvalidId != (encoding = __CFStringEncodingGetFromCanonicalName(name)))) return encoding;
    }

    return kCFStringEncodingInvalidId;
}