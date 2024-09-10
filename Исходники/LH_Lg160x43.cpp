const char *LH_Lg160x43::userInit()
{
#ifdef Q_WS_WIN
    // make sure neither LCDMon.exe nor LCORE.EXE is running on Windows
    if( FindWindowA( "Logitech LCD Monitor Window", "LCDMon" ) ||
            FindWindowA( "QWidget", "LCore" ) )
        return "Logitech drivers are loaded";
#endif
    scan();
    return NULL;
}