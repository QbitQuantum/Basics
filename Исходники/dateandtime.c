static VOID
FillMonthsComboBox(HWND hCombo)
{
    SYSTEMTIME LocalDate = {0};
    WCHAR szBuf[64];
    INT i;
    UINT Month;

    GetLocalTime(&LocalDate);

    SendMessageW(hCombo,
                 CB_RESETCONTENT,
                 0,
                 0);

    for (Month = 1;
         Month <= 13;
         Month++)
    {
        i = GetLocaleInfoW(LOCALE_USER_DEFAULT,
                           ((Month < 13) ? LOCALE_SMONTHNAME1 + Month - 1 : LOCALE_SMONTHNAME13),
                           szBuf,
                           sizeof(szBuf) / sizeof(szBuf[0]));
        if (i > 1)
        {
            i = (INT)SendMessageW(hCombo,
                                  CB_ADDSTRING,
                                  0,
                                  (LPARAM)szBuf);
            if (i != CB_ERR)
            {
                SendMessageW(hCombo,
                             CB_SETITEMDATA,
                             (WPARAM)i,
                             Month);

                if (Month == (UINT)LocalDate.wMonth)
                {
                    SendMessageW(hCombo,
                                 CB_SETCURSEL,
                                 (WPARAM)i,
                                 0);
                }
            }
        }
    }
}