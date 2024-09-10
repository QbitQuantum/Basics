/**
 * generate path where to store settings.
 *
 * @note %APPDATA%/Kouets/
 *       --> C:\Users\nob-aoki\AppData\Roaming[WinVista/7/8]
 *       --> C:\Documents and Settings\nob-aoki\Application Data[Win2k/XP]
 *
 * @note ~/.Kouets/    on Linux & MacOS
 */
void KouetsApp::prepareAppDataPath()
{
#ifdef WINDOWS
    wchar_t appdatapath[0x1000];
    ExpandEnvironmentStringsW(L"%APPDATA%\\Kouets\\",
                              appdatapath, _countof(appdatapath));
    appDataPath_ = QString::fromWCharArray(appdatapath);
#else
    appDataPath_ = "~/.Kouets/";
#endif
}