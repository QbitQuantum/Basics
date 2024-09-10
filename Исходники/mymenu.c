void MYMENU_HelpAbout()
{
    HINSTANCE hInstance = (HINSTANCE)GetWindowLongPtr( hwnd, GWLP_HINSTANCE );
    HICON icon = LoadImageW( hInstance, MAKEINTRESOURCEW(IDI_MYICON), IMAGE_ICON, 48, 48, LR_SHARED );
    static const WCHAR apptitle[] = {'O','x','y','g','e','n',' ','S','p','r','e','a','d','\0'};
    static const WCHAR extratext[] = L"(C) 2009 Ni Hui";
    ShellAboutW( hwnd, apptitle, extratext, icon );
}