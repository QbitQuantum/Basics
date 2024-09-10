/*
 * This function is a temporary workaround for a broken glib version
 * 2.42.2 that is missing g_get_user_name_utf8 export. After glib
 * is fixed this needs to be removed and call to GlibGetUserName
 * replaced by g_get_user_name. See bug 1434059 for details.
 */
const char* GlibGetUserName()
{
#if !defined(_WIN32)
    return g_get_user_name();
#else
    wchar_t buffer[256] = { 0 };
    DWORD len = ARRAYSIZE(buffer);
    static char* user_name_utf8 = NULL;
    if (!user_name_utf8) {
        if (GetUserNameW(buffer, &len)) {
            user_name_utf8 = g_utf16_to_utf8(buffer, -1, NULL, NULL, NULL);
        }
    }
    return user_name_utf8;
#endif
}