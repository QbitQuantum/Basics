std::vector<std::wstring> LanguageTranslator::CurrentLocale() {
    wchar_t buf[LOCALE_NAME_MAX_LENGTH];
    GetUserDefaultLocaleName(buf, LOCALE_NAME_MAX_LENGTH);
    CLOG(L"Locale: %s", buf);

    std::wstring locale(buf);

    /* Remove custom supplemental locales */
    int custom = locale.find(L"-x-");
    if (custom > 0) {
        locale.erase(custom, locale.size() - 1);
    }

    /* Split up parts of the locale string */
    std::vector<std::wstring> parts;
    std::wstring sub;
    std::wistringstream ss(locale);
    while (std::getline(ss, sub, L'-')) {
        parts.push_back(sub);
    }

    std::vector<std::wstring> finalLocale;
    for (std::wstring sub : parts) {
        /* Remove sort orders */
        int sort = sub.find(L"_");
        if (sort > 0) {
            sub.erase(sort, sub.size() - 1);
        }

        finalLocale.push_back(sub);
    }

    return finalLocale;
}