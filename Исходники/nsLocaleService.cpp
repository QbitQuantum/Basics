//
// nsLocaleService methods
//
nsLocaleService::nsLocaleService(void) 
{
#ifdef XP_WIN
    nsAutoString        xpLocale;
    //
    // get the system LCID
    //
    LCID win_lcid = GetSystemDefaultLCID();
    NS_ENSURE_TRUE_VOID(win_lcid);
    nsWin32Locale::GetXPLocale(win_lcid, xpLocale);
    nsresult rv = NewLocale(xpLocale, getter_AddRefs(mSystemLocale));
    NS_ENSURE_SUCCESS_VOID(rv);

    //
    // get the application LCID
    //
    win_lcid = GetUserDefaultLCID();
    NS_ENSURE_TRUE_VOID(win_lcid);
    nsWin32Locale::GetXPLocale(win_lcid, xpLocale);
    rv = NewLocale(xpLocale, getter_AddRefs(mApplicationLocale));
    NS_ENSURE_SUCCESS_VOID(rv);
#endif
#if defined(XP_UNIX) && !defined(XP_MACOSX)
    nsRefPtr<nsLocale> resultLocale(new nsLocale());
    NS_ENSURE_TRUE_VOID(resultLocale);

#ifdef MOZ_WIDGET_QT
    const char* lang = QLocale::system().name().toUtf8();
#else
    // Get system configuration
    const char* lang = getenv("LANG");
#endif

    nsAutoString xpLocale, platformLocale;
    nsAutoString category, category_platform;
    int i;

    for( i = 0; i < LocaleListLength; i++ ) {
        nsresult result;
        // setlocale( , "") evaluates LC_* and LANG
        char* lc_temp = setlocale(posix_locale_category[i], "");
        CopyASCIItoUTF16(LocaleList[i], category);
        category_platform = category;
        category_platform.AppendLiteral("##PLATFORM");
        if (lc_temp != nullptr) {
            result = nsPosixLocale::GetXPLocale(lc_temp, xpLocale);
            CopyASCIItoUTF16(lc_temp, platformLocale);
        } else {
            if ( lang == nullptr ) {
                platformLocale.AssignLiteral("en_US");
                result = nsPosixLocale::GetXPLocale("en-US", xpLocale);
            } else {
                CopyASCIItoUTF16(lang, platformLocale);
                result = nsPosixLocale::GetXPLocale(lang, xpLocale);
            }
        }
        if (NS_FAILED(result)) {
            return;
        }
        resultLocale->AddCategory(category, xpLocale);
        resultLocale->AddCategory(category_platform, platformLocale);
    }
    mSystemLocale = do_QueryInterface(resultLocale);
    mApplicationLocale = do_QueryInterface(resultLocale);
       
#endif // XP_UNIX

#ifdef XP_MACOSX
    // Get string representation of user's current locale
    CFLocaleRef userLocaleRef = ::CFLocaleCopyCurrent();
    CFStringRef userLocaleStr = ::CFLocaleGetIdentifier(userLocaleRef);
    ::CFRetain(userLocaleStr);

    nsAutoTArray<UniChar, 32> buffer;
    int size = ::CFStringGetLength(userLocaleStr);
    if (buffer.SetLength(size + 1))
    {
        CFRange range = ::CFRangeMake(0, size);
        ::CFStringGetCharacters(userLocaleStr, range, buffer.Elements());
        buffer[size] = 0;

        // Convert the locale string to the format that Mozilla expects
        nsAutoString xpLocale(buffer.Elements());
        xpLocale.ReplaceChar('_', '-');

        nsresult rv = NewLocale(xpLocale, getter_AddRefs(mSystemLocale));
        if (NS_SUCCEEDED(rv)) {
            mApplicationLocale = mSystemLocale;
        }
    }

    ::CFRelease(userLocaleStr);
    ::CFRelease(userLocaleRef);

    NS_ASSERTION(mApplicationLocale, "Failed to create locale objects");
#endif // XP_MACOSX
}