/*
 * Check for the alias from the string or alias resource res.
 */
static void
checkAlias(const char *itemName,
           Resource res, const UChar *alias, int32_t length, UBool useResSuffix,
           CheckDependency check, void *context, UErrorCode *pErrorCode) {
    int32_t i;

    if(!uprv_isInvariantUString(alias, length)) {
        fprintf(stderr, "icupkg/ures_enumDependencies(%s res=%08x) alias string contains non-invariant characters\n",
                        itemName, res);
        *pErrorCode=U_INVALID_CHAR_FOUND;
        return;
    }

    // extract the locale ID from alias strings like
    // locale_ID/key1/key2/key3
    // locale_ID

    // search for the first slash
    for(i=0; i<length && alias[i]!=SLASH; ++i) {}

    if(res_getPublicType(res)==URES_ALIAS) {
        // ignore aliases with an initial slash:
        // /ICUDATA/... and /pkgname/... go to a different package
        // /LOCALE/... are for dynamic sideways fallbacks and don't go to a fixed bundle
        if(i==0) {
            return; // initial slash ('/')
        }

        // ignore the intra-bundle path starting from the first slash ('/')
        length=i;
    } else /* URES_STRING */ {
        // the whole string should only consist of a locale ID
        if(i!=length) {
            fprintf(stderr, "icupkg/ures_enumDependencies(%s res=%08x) %%ALIAS contains a '/'\n",
                            itemName, res);
            *pErrorCode=U_UNSUPPORTED_ERROR;
            return;
        }
    }

    // convert the Unicode string to char *
    char localeID[32];
    if(length>=(int32_t)sizeof(localeID)) {
        fprintf(stderr, "icupkg/ures_enumDependencies(%s res=%08x) alias locale ID length %ld too long\n",
                        itemName, res, (long)length);
        *pErrorCode=U_BUFFER_OVERFLOW_ERROR;
        return;
    }
    u_UCharsToChars(alias, localeID, length);
    localeID[length]=0;

    checkIDSuffix(itemName, localeID, -1, (useResSuffix ? ".res" : ""), check, context, pErrorCode);
}