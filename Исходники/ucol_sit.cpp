U_CAPI int32_t U_EXPORT2
ucol_getShortDefinitionString(const UCollator *coll,
                              const char *locale,
                              char *dst,
                              int32_t capacity,
                              UErrorCode *status)
{
    if(U_FAILURE(*status)) return 0;
    if(coll->delegate != NULL) {
      return ((icu::Collator*)coll->delegate)->internalGetShortDefinitionString(locale,dst,capacity,*status);
    }
    char buffer[internalBufferSize];
    uprv_memset(buffer, 0, internalBufferSize*sizeof(char));
    int32_t resultSize = 0;
    char tempbuff[internalBufferSize];
    char locBuff[internalBufferSize];
    uprv_memset(buffer, 0, internalBufferSize*sizeof(char));
    int32_t elementSize = 0;
    UBool isAvailable = 0;
    CollatorSpec s;
    ucol_sit_initCollatorSpecs(&s);

    if(!locale) {
        locale = ucol_getLocaleByType(coll, ULOC_VALID_LOCALE, status);
    }
    elementSize = ucol_getFunctionalEquivalent(locBuff, internalBufferSize, "collation", locale, &isAvailable, status);

    if(elementSize) {
        // we should probably canonicalize here...
        elementSize = uloc_getLanguage(locBuff, tempbuff, internalBufferSize, status);
        appendShortStringElement(tempbuff, elementSize, buffer, &resultSize, /*capacity*/internalBufferSize, languageArg);
        elementSize = uloc_getCountry(locBuff, tempbuff, internalBufferSize, status);
        appendShortStringElement(tempbuff, elementSize, buffer, &resultSize, /*capacity*/internalBufferSize, regionArg);
        elementSize = uloc_getScript(locBuff, tempbuff, internalBufferSize, status);
        appendShortStringElement(tempbuff, elementSize, buffer, &resultSize, /*capacity*/internalBufferSize, scriptArg);
        elementSize = uloc_getVariant(locBuff, tempbuff, internalBufferSize, status);
        appendShortStringElement(tempbuff, elementSize, buffer, &resultSize, /*capacity*/internalBufferSize, variantArg);
        elementSize = uloc_getKeywordValue(locBuff, "collation", tempbuff, internalBufferSize, status);
        appendShortStringElement(tempbuff, elementSize, buffer, &resultSize, /*capacity*/internalBufferSize, keywordArg);
    }

    int32_t i = 0;
    UColAttributeValue attribute = UCOL_DEFAULT;
    for(i = 0; i < UCOL_SIT_ITEMS_COUNT; i++) {
        if(options[i].action == _processCollatorOption) {
            attribute = ucol_getAttributeOrDefault(coll, (UColAttribute)options[i].attr, status);
            if(attribute != UCOL_DEFAULT) {
                char letter = ucol_sit_attributeValueToLetter(attribute, status);
                appendShortStringElement(&letter, 1,
                    buffer, &resultSize, /*capacity*/internalBufferSize, options[i].optionStart);
            }
        }
    }
    if(coll->variableTopValueisDefault == FALSE) {
        //s.variableTopValue = ucol_getVariableTop(coll, status);
        elementSize = T_CString_integerToString(tempbuff, coll->variableTopValue, 16);
        appendShortStringElement(tempbuff, elementSize, buffer, &resultSize, capacity, variableTopValArg);
    }

    UParseError parseError;
    return ucol_normalizeShortDefinitionString(buffer, dst, capacity, &parseError, status);
}