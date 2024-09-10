void 
ResourceBundle::constructForLocale(const UnicodeString& path,
                                   const Locale& locale,
                                   UErrorCode& error)
{
    if (path.isEmpty()) {
        fResource = ures_open(NULL, locale.getName(), &error);
    }
    else {
        UnicodeString nullTerminatedPath(path);
        nullTerminatedPath.append((UChar)0);
        fResource = ures_openU(nullTerminatedPath.getBuffer(), locale.getName(), &error);
    }
}