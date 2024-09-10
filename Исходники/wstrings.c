LPWSTR WINAPI CharLowerW(
    LPWSTR pwsz)
{
    /*
     * Early out for NULL string or '\0'
     */
    if (pwsz == NULL) {
        return pwsz;
    }

    if (!IS_PTR(pwsz)) {
        if (!LCMapStringW(
                 LOCALE_USER_DEFAULT,
                 LCMAP_LOWERCASE,
                 (LPWSTR)&pwsz,
                 1,
                 (LPWSTR)&pwsz,
                 1
                 )) {
            /*
             * We don't expect LCMapString to fail!  The caller is not expecting
             * failure, CharLowerW does not have a failure indicator, so we do
             * nothing.
             */
            RIPMSG1(RIP_WARNING, "CharLowerW(%#p): LCMapString failed\n", pwsz);
        }

        return pwsz;
    }

    /*
     * pwsz is a null-terminated string
     */
    CharLowerBuffW(pwsz, wcslen(pwsz)+1);
    return pwsz;
}