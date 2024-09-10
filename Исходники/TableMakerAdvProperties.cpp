void
TableMakerAdvProperties::InitTableTypeValues()
{
    HWND        hwndcombo;
    wyInt32     index;
    wyString    strengine;
    wyWChar     *enginebuff, *tokpointer;

    GetTableEngineString(m_tunnel, m_mysql, strengine);

    enginebuff = AllocateBuffWChar(strengine.GetLength()+1);
    wcscpy(enginebuff, strengine.GetAsWideChar());
    VERIFY(hwndcombo = GetDlgItem(m_hwnd, IDC_TYPE));

    tokpointer = wcstok(enginebuff, L";");

    while(tokpointer != NULL)
    {
        VERIFY((SendMessage(hwndcombo, CB_ADDSTRING, 0, (LPARAM)tokpointer)) >= 0);

        tokpointer = wcstok(NULL, L";");
    }
    free(enginebuff);

    if((index = SendMessage(hwndcombo , CB_ADDSTRING, 0,(LPARAM)TEXT(STR_DEFAULT))) != CB_ERR)
        SendMessage(hwndcombo, CB_SELECTSTRING, index, (LPARAM)TEXT(STR_DEFAULT));

    return;
}