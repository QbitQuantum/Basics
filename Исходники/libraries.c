static void on_add_click(HWND dialog)
{
    static const char dotDll[] = ".dll";
    char buffer[1024], *ptr;

    ZeroMemory(buffer, sizeof(buffer));

    SendDlgItemMessageA(dialog, IDC_DLLCOMBO, WM_GETTEXT, sizeof(buffer), (LPARAM) buffer);
    if (lstrlenA(buffer) >= sizeof(dotDll))
    {
        ptr = buffer + lstrlenA(buffer) - sizeof(dotDll) + 1;
        if (!lstrcmpiA(ptr, dotDll))
        {
            WINE_TRACE("Stripping dll extension\n");
            *ptr = '\0';
        }
    }

    /* check if dll is in the builtin-only list */
    if (!(ptr = strrchr( buffer, '\\' )))
    {
        ptr = buffer;
        if (*ptr == '*') ptr++;
    }
    else ptr++;
    if (is_builtin_only( ptr ))
    {
        MSGBOXPARAMSA params;
        params.cbSize = sizeof(params);
        params.hwndOwner = dialog;
        params.hInstance = GetModuleHandleA( NULL );
        params.lpszText = MAKEINTRESOURCEA( IDS_DLL_WARNING );
        params.lpszCaption = MAKEINTRESOURCEA( IDS_DLL_WARNING_CAPTION );
        params.dwStyle = MB_ICONWARNING | MB_YESNO;
        params.lpszIcon = NULL;
        params.dwContextHelpId = 0;
        params.lpfnMsgBoxCallback = NULL;
        params.dwLanguageId = 0;
        if (MessageBoxIndirectA( &params ) != IDYES) return;
    }

    SendDlgItemMessageW(dialog, IDC_DLLCOMBO, WM_SETTEXT, 0, (LPARAM)emptyW);
    disable(IDC_DLLS_ADDDLL);
    SendMessageW(GetParent(dialog), DM_SETDEFID, IDOK, 0);

    WINE_TRACE("Adding %s as native, builtin\n", buffer);

    SendMessageW(GetParent(dialog), PSM_CHANGED, 0, 0);
    set_reg_key(config_key, keypath("DllOverrides"), buffer, "native,builtin");

    load_library_settings(dialog);

    SendDlgItemMessageA(dialog, IDC_DLLS_LIST, LB_SELECTSTRING, 0, (LPARAM) buffer);

    set_controls_from_selection(dialog);
}