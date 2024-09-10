U_CAPI int32_t U_EXPORT2
ucurr_forLocale(const char* locale,
                UChar* buff,
                int32_t buffCapacity,
                UErrorCode* ec)
{
    int32_t resLen = 0;
    const UChar* s = NULL;
    if (ec != NULL && U_SUCCESS(*ec)) {
        if ((buff && buffCapacity) || !buffCapacity) {
            UErrorCode localStatus = U_ZERO_ERROR;
            char id[ULOC_FULLNAME_CAPACITY];
            if ((resLen = uloc_getKeywordValue(locale, "currency", id, ULOC_FULLNAME_CAPACITY, &localStatus))) {
                // there is a currency keyword. Try to see if it's valid
                if(buffCapacity > resLen) {
                    u_charsToUChars(id, buff, resLen);
                }
            } else {
                // get country or country_variant in `id'
                uint32_t variantType = idForLocale(locale, id, sizeof(id), ec);

                if (U_FAILURE(*ec)) {
                    return 0;
                }

#if !UCONFIG_NO_SERVICE
                const UChar* result = CReg::get(id);
                if (result) {
                    if(buffCapacity > u_strlen(result)) {
                        u_strcpy(buff, result);
                    }
                    return u_strlen(result);
                }
#endif
                // Remove variants, which is only needed for registration.
                char *idDelim = strchr(id, VAR_DELIM);
                if (idDelim) {
                    idDelim[0] = 0;
                }

                // Look up the CurrencyMap element in the root bundle.
                UResourceBundle *rb = ures_openDirect(NULL, CURRENCY_DATA, &localStatus);
                UResourceBundle *cm = ures_getByKey(rb, CURRENCY_MAP, rb, &localStatus);
                UResourceBundle *countryArray = ures_getByKey(rb, id, cm, &localStatus);
                UResourceBundle *currencyReq = ures_getByIndex(countryArray, 0, NULL, &localStatus);
                s = ures_getStringByKey(currencyReq, "id", &resLen, &localStatus);

                /*
                Get the second item when PREEURO is requested, and this is a known Euro country.
                If the requested variant is PREEURO, and this isn't a Euro country, assume
                that the country changed over to the Euro in the future. This is probably
                an old version of ICU that hasn't been updated yet. The latest currency is
                probably correct.
                */
                if (U_SUCCESS(localStatus)) {
                    if ((variantType & VARIANT_IS_PREEURO) && u_strcmp(s, EUR_STR) == 0) {
                        currencyReq = ures_getByIndex(countryArray, 1, currencyReq, &localStatus);
                        s = ures_getStringByKey(currencyReq, "id", &resLen, &localStatus);
                    }
                    else if ((variantType & VARIANT_IS_EURO)) {
                        s = EUR_STR;
                    }
                }
                ures_close(countryArray);
                ures_close(currencyReq);

                if ((U_FAILURE(localStatus)) && strchr(id, '_') != 0)
                {
                    // We don't know about it.  Check to see if we support the variant.
                    uloc_getParent(locale, id, sizeof(id), ec);
                    *ec = U_USING_FALLBACK_WARNING;
                    return ucurr_forLocale(id, buff, buffCapacity, ec);
                }
                else if (*ec == U_ZERO_ERROR || localStatus != U_ZERO_ERROR) {
                    // There is nothing to fallback to. Report the failure/warning if possible.
                    *ec = localStatus;
                }
                if (U_SUCCESS(*ec)) {
                    if(buffCapacity > resLen) {
                        u_strcpy(buff, s);
                    }
                }
            }
            return u_terminateUChars(buff, buffCapacity, resLen, ec);
        } else {
            *ec = U_ILLEGAL_ARGUMENT_ERROR;
        }
    }
    return resLen;
}