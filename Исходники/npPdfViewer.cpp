void SelectTranslation(const WCHAR *exePath=NULL)
{
    LANGID langId = GetUserDefaultUILanguage();
    int idx = GetLanguageIndex(langId);
    if (-1 == idx) {
        // try a neutral language if the specific sublanguage isn't available
        langId = MAKELANGID(PRIMARYLANGID(langId), SUBLANG_NEUTRAL);
        idx = GetLanguageIndex(langId);
    }
    if (-1 != idx) {
        gTranslationIdx = idx;
        plogf("sp: Detected language %s (%d)", gLanguages[idx / gTranslationsCount], idx);
    }

    // try to extract the language used by SumatraPDF
    ScopedMem<WCHAR> path;
    if (exePath) {
        path.Set(path::GetDir(exePath));
        path.Set(path::Join(path, PREFS_FILE_NAME));
    }
    if (!file::Exists(path)) {
        path.Set(GetSpecialFolder(CSIDL_APPDATA));
        path.Set(path::Join(path, L"SumatraPDF\\" PREFS_FILE_NAME));
    }
    if (!file::Exists(path))
        return;
    plogf("sp: Found preferences at %S", path);
    ScopedMem<char> prefsData(file::ReadAll(path, NULL));
    SquareTree sqt(prefsData);
    const char *langCode = sqt.root ? sqt.root->GetValue("UiLanguage") : NULL;
    if (langCode) {
        plogf("sp: UiLanguage from preferences: %s", langCode);
        for (int i = 0; gLanguages[i]; i++) {
            if (str::Eq(gLanguages[i], langCode)) {
                gTranslationIdx = i * gTranslationsCount;
                break;
            }
        }
    }
}