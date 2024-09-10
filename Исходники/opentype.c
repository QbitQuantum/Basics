static void get_name_record_locale(enum OPENTYPE_PLATFORM_ID platform, USHORT lang_id, WCHAR *locale, USHORT locale_len)
{
    static const WCHAR enusW[] = {'e','n','-','U','S',0};

    switch (platform) {
    case OPENTYPE_PLATFORM_MAC:
    {
        const char *locale_name = NULL;

        if (lang_id > TT_NAME_MAC_LANGID_AZER_ROMAN)
            ERR("invalid mac lang id %d\n", lang_id);
        else if (!name_mac_langid_to_locale[lang_id][0])
            FIXME("failed to map mac lang id %d to locale name\n", lang_id);
        else
            locale_name = name_mac_langid_to_locale[lang_id];

        if (locale_name)
            MultiByteToWideChar(CP_ACP, 0, name_mac_langid_to_locale[lang_id], -1, locale, locale_len);
        else
            strcpyW(locale, enusW);
        break;
    }
    case OPENTYPE_PLATFORM_WIN:
        if (!LCIDToLocaleName(MAKELCID(lang_id, SORT_DEFAULT), locale, locale_len, 0)) {
            FIXME("failed to get locale name for lcid=0x%08x\n", MAKELCID(lang_id, SORT_DEFAULT));
            strcpyW(locale, enusW);
        }
        break;
    default:
        FIXME("unknown platform %d\n", platform);
    }
}