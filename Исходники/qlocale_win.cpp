QVariant QSystemLocalePrivate::uiLanguages()
{
    if (QSysInfo::windowsVersion() >= QSysInfo::WV_VISTA) {
        typedef BOOL (WINAPI *GetUserPreferredUILanguagesFunc) (
                    DWORD dwFlags,
                    PULONG pulNumLanguages,
                    PWSTR pwszLanguagesBuffer,
                    PULONG pcchLanguagesBuffer);
        static GetUserPreferredUILanguagesFunc GetUserPreferredUILanguages_ptr = 0;
        if (!GetUserPreferredUILanguages_ptr) {
            QSystemLibrary lib(QLatin1String("kernel32"));
            if (lib.load())
                GetUserPreferredUILanguages_ptr = (GetUserPreferredUILanguagesFunc)lib.resolve("GetUserPreferredUILanguages");
        }
        if (GetUserPreferredUILanguages_ptr) {
            unsigned long cnt = 0;
            QVarLengthArray<wchar_t, 64> buf(64);
            unsigned long size = buf.size();
            if (!GetUserPreferredUILanguages_ptr(MUI_LANGUAGE_NAME, &cnt, buf.data(), &size)) {
                size = 0;
                if (GetLastError() == ERROR_INSUFFICIENT_BUFFER &&
                    GetUserPreferredUILanguages_ptr(MUI_LANGUAGE_NAME, &cnt, NULL, &size)) {
                    buf.resize(size);
                    if (!GetUserPreferredUILanguages_ptr(MUI_LANGUAGE_NAME, &cnt, buf.data(), &size))
                        return QStringList();
                }
            }
            QStringList result;
            result.reserve(cnt);
            const wchar_t *str = buf.constData();
            for (; cnt > 0; --cnt) {
                QString s = QString::fromWCharArray(str);
                if (s.isEmpty())
                    break; // something is wrong
                result.append(s);
                str += s.size()+1;
            }
            return result;
        }
    }

    // old Windows before Vista
    return QStringList(QString::fromLatin1(winLangCodeToIsoName(GetUserDefaultUILanguage())));
}