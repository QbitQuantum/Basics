lString8 SaveFileDialog( HWND hWndOwner )
{
    lString8 fn;
    OPENFILENAMEA ofn;
    char str[MAX_PATH] = "";
    memset( &ofn, 0, sizeof(ofn) );
    ofn.lStructSize = sizeof( ofn );
    ofn.hwndOwner = hWndOwner;
    ofn.lpstrFilter = "WOL files (*.wol)\0*.wol\0All Files (*.*)\0*.*\0\0";
    ofn.nFilterIndex = 1;
    ofn.lpstrFile = str;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Please select book to open";
    ofn.Flags = OFN_OVERWRITEPROMPT | OFN_PATHMUSTEXIST;
    ofn.lpstrDefExt = "wol";
//    ofn.FlagsEx = OFN_EX_NOPLACESBAR;
    if ( GetSaveFileNameA( &ofn ) )
    {
        fn = str;
    }
    return fn;
}