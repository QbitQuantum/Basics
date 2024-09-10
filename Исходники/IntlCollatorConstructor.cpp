static Vector<String> sortLocaleData(const String& locale, const String& key)
{
    // 9.1 Internal slots of Service Constructors & 10.2.3 Internal slots (ECMA-402 2.0)
    Vector<String> keyLocaleData;
    if (key == "co") {
        // 10.2.3 "The first element of [[sortLocaleData]][locale].co and [[searchLocaleData]][locale].co must be null for all locale values."
        keyLocaleData.append(String());

        UErrorCode status = U_ZERO_ERROR;
        UEnumeration* enumeration = ucol_getKeywordValuesForLocale("collation", locale.utf8().data(), TRUE, &status);
        if (U_SUCCESS(status)) {
            const char* keywordValue;
            while ((keywordValue = uenum_next(enumeration, nullptr, &status)) && U_SUCCESS(status)) {
                String collation(keywordValue);

                // 10.2.3 "The values "standard" and "search" must not be used as elements in any [[sortLocaleData]][locale].co and [[searchLocaleData]][locale].co array."
                if (collation == "standard" || collation == "search")
                    continue;

                // Map keyword values to BCP 47 equivalents.
                if (collation == "dictionary")
                    collation = ASCIILiteral("dict");
                else if (collation == "gb2312han")
                    collation = ASCIILiteral("gb2312");
                else if (collation == "phonebook")
                    collation = ASCIILiteral("phonebk");
                else if (collation == "traditional")
                    collation = ASCIILiteral("trad");

                keyLocaleData.append(collation);
            }
            uenum_close(enumeration);
        }
    } else if (key == "kn") {
        keyLocaleData.append(ASCIILiteral("false"));
        keyLocaleData.append(ASCIILiteral("true"));
    } else
        ASSERT_NOT_REACHED();
    return keyLocaleData;
}