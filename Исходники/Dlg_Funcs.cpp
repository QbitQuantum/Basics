INT_PTR MainDlg::OnExecute( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    wchar_t path[MAX_PATH] = { 0 };
    char init[256] = { 0 };
    wchar_t arg[512] = { 0 };

    GetDlgItemTextW( hDlg, IDC_IMAGE_PATH, path, MAX_PATH );
    GetDlgItemTextA( hDlg, IDC_INIT_EXPORT, init, 256 );
    GetDlgItemTextW( hDlg, IDC_ARGUMENT, arg, 512 );

    DoInject( path, init, arg );

    return (INT_PTR)TRUE;
}