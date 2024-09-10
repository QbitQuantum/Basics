LRESULT PickList<C>::getValue(C *out, C def)
{
    int data = -1;

    LRESULT res = SendDlgItemMessage(hDlg,wId,CB_GETCURSEL,0,0);
    if (res != CB_ERR)
    {
        data = SendDlgItemMessage(hDlg,wId,CB_GETITEMDATA,(WPARAM)res,0);
        try {
            wchar_t buf[MAX_PATH];
            ::_snwprintf(buf, MAX_PATH, L"item[%d]/value", data);
            *out = valueSet->selectSingleNode(buf)->nodeTypedValue;
        } catch (...) {
            AtlTrace("Excepton tying to retrieve picklist value from XML fragment\n");
        }
    }
    else if (!fixed)
    {
        char s[MAX_PATH];
        GetDlgItemText(hDlg,wId, s, sizeof(s));
        (*pFromStr)(out, s);
    }
    else
        *out = def;

    return 1;
}