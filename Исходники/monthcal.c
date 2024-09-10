static WORD
MonthCalFirstDayOfWeek(VOID)
{
    WCHAR szBuf[2] = {0};
    WORD Ret = 0;

    if (GetLocaleInfoW(LOCALE_USER_DEFAULT,
                       LOCALE_IFIRSTDAYOFWEEK,
                       szBuf,
                       sizeof(szBuf) / sizeof(szBuf[0])) != 0)
    {
        Ret = (WORD)(szBuf[0] - TEXT('0'));
    }

    return Ret;
}