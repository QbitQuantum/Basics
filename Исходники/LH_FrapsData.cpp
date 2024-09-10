void LH_FrapsData::pingFraps()
{
#ifdef Q_WS_WIN
    if( FindWindowA( "#32770", NULL ) != (HWND)NULL )
    {
        HWND hWndLH = FindWindowA( "QWidget" , "LCDHost" );
        if ( hWndLH != 0 )
        {
            HINSTANCE instance = (HINSTANCE)GetWindowLong(hWndLH, GWL_HINSTANCE);

            HWND hWnd = CreateWindowA("QWidget", "LCDHost",
                                       WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                       (HWND) NULL,(HMENU) NULL, instance, (LPVOID) NULL);
            DestroyWindow( hWnd );
        }
    }
#else
    return;
#endif
}