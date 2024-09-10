/*
 *  stress_wcscoll()
 *	stress on wcscoll
 */
static void stress_wcscoll(
    const char *name,
    wchar_t *str1,
    const size_t len1,
    wchar_t *str2,
    const size_t len2)
{
    register size_t i;

    (void)len2;

    for (i = 1; i < len1; i++) {
        WCSCHK(name, 0 == wcscoll(str1, str1));
        WCSCHK(name, 0 == wcscoll(str2, str2));

        WCSCHK(name, 0 != wcscoll(str2, str1));
        WCSCHK(name, 0 != wcscoll(str1, str2));

        WCSCHK(name, 0 != wcscoll(str1 + i, str1));
        WCSCHK(name, 0 != wcscoll(str1, str1 + i));
        WCSCHK(name, 0 == wcscoll(str1 + i, str1 + i));

        WCSCHK(name, 0 != wcscoll(str1 + i, str2));
        WCSCHK(name, 0 != wcscoll(str2, str1 + i));
    }
}