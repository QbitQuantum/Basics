/***
*void GetLcidFromLangCountry - get LCIDs from language and country strings
*
*Purpose:
*   Match the best LCIDs to the language and country string given.
*   After global variables are initialized, the LangCountryEnumProc
*   routine is registered as an EnumSystemLocalesA callback to actually
*   perform the matching as the LCIDs are enumerated.
*
*Entry:
*   pchLanguage     - language string
*   bAbbrevLanguage - language string is a three-letter abbreviation
*   pchCountry      - country string
*   bAbbrevCountry  - country string ia a three-letter abbreviation
*   iPrimaryLen     - length of language string with primary name
*
*Exit:
*   lcidLanguage - LCID of language string
*   lcidCountry  - LCID of country string
*
*Exceptions:
*
*******************************************************************************/
static void GetLcidFromLangCountry (void)
{
    //  initialize static variables for callback use
    bAbbrevLanguage = strlen(pchLanguage) == 3;
    bAbbrevCountry = strlen(pchCountry) == 3;
    lcidLanguage = 0;
    iPrimaryLen = bAbbrevLanguage ? 2 : GetPrimaryLen(pchLanguage);

    EnumSystemLocalesA(LangCountryEnumProc, LCID_INSTALLED);

    //  locale value is invalid if the language was not installed or the language
    //  was not available for the country specified
    if (!(iLcidState & __LCID_LANGUAGE) || !(iLcidState & __LCID_EXISTS) ||
                !(iLcidState & (__LCID_FULL | __LCID_PRIMARY | __LCID_DEFAULT)))
        iLcidState = 0;
}