static LCID LCIDFromLocaleInternal(LCID userDefaultLCID, const String& userDefaultLanguageCode, String& locale)
{
    if (equalIgnoringASCIICase(extractLanguageCode(locale), userDefaultLanguageCode))
        return userDefaultLCID;
    return LocaleNameToLCID(locale.charactersWithNullTermination().data(), 0);
}