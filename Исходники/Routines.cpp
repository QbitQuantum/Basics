/// <summary>
/// Enumerate processes
/// </summary>
/// <returns>Error code</returns>
DWORD MainDlg::FillProcessList()
{
    PROCESSENTRY32W pe32 = { 0 };
    pe32.dwSize = sizeof(pe32);

    HWND hCombo = GetDlgItem( _hMainDlg, IDC_COMBO_PROC );

    ComboBox_ResetContent( hCombo );

    HANDLE hSnap = CreateToolhelp32Snapshot( TH32CS_SNAPPROCESS, 0 );
    if (hSnap == NULL)
        return GetLastError();

    for (BOOL res = Process32FirstW( hSnap, &pe32 ); res; res = Process32NextW( hSnap, &pe32 ))
    {
        wchar_t text[255] = { 0 };
        swprintf_s( text, L"%ls (%d)", pe32.szExeFile, pe32.th32ProcessID );

        int idx = ComboBox_AddString( hCombo, text );
        ComboBox_SetItemData( hCombo, idx, pe32.th32ProcessID );
    }

    CloseHandle( hSnap );

    return 0;
}