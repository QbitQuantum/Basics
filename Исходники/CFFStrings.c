static
BOOL
_findStrings
(
    HWND    hDlg,
    DWORD   minLength,
    BOOL    ascii,
    BOOL    unicode,
    BOOL    showOffset,
    BOOL    searchBoth
)
{

    PBYTE   fileptr     = g_object;
    PBYTE   fileend     = g_object;
    DWORD   filelen     = 0;
    CHAR    str[MAX_STRING_LEN] = { 0 };
    CHAR    strsfound[30] = { 0 };
    int     strlen      = 0;
    int     offset      = 0;
    int     index       = 0;
    DWORD   steplen     = 0;
    int     stepOffset  = 0;
    char    isUnicode   = 0;
    int     longestStr  = 0;
    BOOL    stop        = FALSE;
    BOOL    err         = FALSE;

    if (minLength < MIN_STRING_LEN)
    {
        minLength = MIN_STRING_LEN;
    }

    ResetEvent(g_event);

    filelen = CFFApi.eaGetObjectSize(hDlg);
    fileend += filelen;
    steplen = filelen / 100;

    if (searchBoth)
    {
        steplen *= 2;
    }


    while (fileptr + offset < fileend && !stop)
    {
        ZeroMemory(str, sizeof(str));
        strlen = string(fileptr, filelen, offset, unicode, str, sizeof(str) - 1, &isUnicode);
            
        if (strlen >= (int)minLength)
        {
            if (index < MAXINT16)
            {
                if (strlen > longestStr)
                {
                    longestStr = strlen;
                }

                if ((ascii && !isUnicode) || (unicode && isUnicode))
                {
                    _insertString(hDlg, str, strlen + 1, showOffset, offset, searchBoth, isUnicode, index);
                    index++;
                }
            }
            else
            {
                Edit_SetText(GetDlgItem(hDlg, IDC_STATUS), "ERROR: Exceeded string display limit (~32K strings). Increase min string length.");
                err = TRUE;
                break;
            }
        }

        offset += (strlen == 0) ? 1 : (isUnicode ? strlen * 2 : strlen);

        if (offset - stepOffset > (int)steplen)
        {
            SendDlgItemMessageA(hDlg, IDC_PROGRESS, PBM_STEPIT, 0, (LPARAM)0);
            stepOffset = offset;
        }
        if (WAIT_OBJECT_0 == WaitForSingleObject(g_event, 0))
        {
            stop = TRUE;
        }
    }
    ListView_SetColumnWidth(GetDlgItem(hDlg, IDC_STRINGLIST), showOffset + searchBoth, longestStr * PIXELS_PER_CHAR);

    if (!stop)
    {
        if (!err)
        {
            ZeroMemory(strsfound, sizeof(strsfound));
            _snprintf_s(strsfound, sizeof(strsfound), sizeof(strsfound), "Found %d strings.", index);
            Edit_SetText(GetDlgItem(hDlg, IDC_STATUS), strsfound);
        }
    }

    return stop || err;
}