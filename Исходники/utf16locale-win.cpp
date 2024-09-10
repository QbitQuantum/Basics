RTDECL(int) RTUtf16LocaleICmp(PCRTUTF16 pusz1, PCRTUTF16 pusz2)
{
    if (pusz1 == pusz2)
        return 0;
    if (pusz1 == NULL)
        return -1;
    if (pusz2 == NULL)
        return 1;

    return CompareStringW(LOCALE_USER_DEFAULT, NORM_IGNORECASE, pusz1, -1, pusz2, -1) - 2;
}