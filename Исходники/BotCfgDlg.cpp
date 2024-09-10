void BotCfg_OnSave( HWND hDlg, BotCfgDlgSt *st )
{
    // change subdir to '.\configs'
    char curDir[256] = {0};
    char newDir[256] = {0};
    GetCurrentDirectoryA( 200, curDir );
    wsprintfA( newDir, "%s\\configs", curDir );
    SetCurrentDirectoryA( newDir );
    //
    char fileName[256] = {0};
    OPENFILENAMEA ofn;
    memset( &ofn, 0, sizeof(ofn) );
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hDlg;
    ofn.hInstance = g_hInst;
    ofn.lpstrFilter = "Config files\0*.config\0All files\0*.*\0\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = 255;
    ofn.lpstrTitle = "Куда сохранять?";
    ofn.lpstrInitialDir = newDir;
    ofn.Flags = OFN_ENABLESIZING | OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST;
    if( GetSaveFileNameA( &ofn ) )
    {
        if( strstr( fileName, ".config" ) == NULL ) strcat( fileName, ".config" );
        if( !st->myCfg.saveConfig( fileName ) )
        {
            MessageBox( hDlg, TEXT("Конфиг не сохранился!"), TEXT("Ашыпка!"), MB_ICONSTOP );
        }
    }
    // restore cur dir (required to load maps, for example)
    SetCurrentDirectoryA( curDir );
}