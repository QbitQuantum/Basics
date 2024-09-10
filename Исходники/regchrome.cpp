void
TranslateResourceValue(const char* aProviderType,
                       const char* aProvider,
                       const char* aArc,
                       const char* aResourceValue,
                       nsACString& aResult)
{
    PRUint32 chopStart=0, chopEnd=0; // bytes to chop off the front/back of aResourceValue

    static const char localeUrn[] = "urn:mozilla:locale:";
    if ((strcmp(aArc, "selectedLocale") == 0) &&
        (strncmp(aResourceValue, localeUrn, sizeof(localeUrn)-1) == 0)) {
        
        chopStart = sizeof(localeUrn) - 1;
        chopEnd = strlen(aProvider) + 1;
    }

    static const char skinUrn[] = "urn:mozilla:skin:";
    if ((strcmp(aArc, "selectedSkin") == 0) &&
        (strncmp(aResourceValue, skinUrn, sizeof(skinUrn)-1) == 0)) {

        chopStart = sizeof(skinUrn) - 1;
        chopEnd = strlen(aProvider) + 1;
    }

    // strip off 'urn:mozilla:<foo>:' and ':<provider>'
    aResult = (aResourceValue + chopStart);
    aResult.Truncate(aResult.Length() - chopEnd);
        
}