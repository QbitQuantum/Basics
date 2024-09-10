ccLanguageType CCApplication::getCurrentLanguage()
{
    ccLanguageType ret = kLanguageEnglish;

    wchar_t localeName[LOCALE_NAME_MAX_LENGTH] = {0};

    if (GetUserDefaultLocaleName(localeName, LOCALE_NAME_MAX_LENGTH))
    {
        wchar_t* primary = NULL;
        wchar_t* sub = NULL;

        primary = wcstok(localeName, L"-");
        sub = wcstok(NULL, L"-");
        
        if (wcscmp(primary, L"zh") == 0)
        {
            ret = kLanguageChinese;
        }
        else if (wcscmp(primary, L"ja") == 0)
        {
            ret = kLanguageJapanese;
        }
        else if (wcscmp(primary, L"fr") == 0)
        {
            ret = kLanguageFrench;
        }
        else if (wcscmp(primary, L"it") == 0)
        {
            ret = kLanguageItalian;
        }
        else if (wcscmp(primary, L"de") == 0)
        {
            ret = kLanguageGerman;
        }
        else if (wcscmp(primary, L"es") == 0)
        {
            ret = kLanguageSpanish;
        }
        else if (wcscmp(primary, L"ru") == 0)
        {
            ret = kLanguageRussian;
        }
        else if (wcscmp(primary, L"hu") == 0)
        {
            ret = kLanguageHungarian;
        }
        else if (wcscmp(primary, L"pt") == 0)
        {
            ret = kLanguagePortuguese;
        }
        else if (wcscmp(primary, L"ko") == 0)
        {
            ret = kLanguageKorean;
        }
        else if (wcscmp(primary, L"ar") == 0)
        {
            ret = kLanguageArabic;
        } 
    }

    return ret;
}