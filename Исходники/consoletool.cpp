//-----------------------------------------------------------------------------
// 設定視窗標題
void SetConsoleWindowTile(IN const nstring &szTitle, IN const nstring &szVer, IN const nstring &szFile)
{
    nstring szWindowTile;

    if(szTitle.empty() == false)
        szWindowTile += nsoutf(__T("{} ")) << szTitle;

    if(szVer.empty() == false)
        szWindowTile += nsoutf(__T("[Ver:{}]")) << szVer;

    if(szFile.empty() == false)
    {
        struct _stat sStat;
        struct tm sTMTime;
        TCHAR szTime[32];

        _tstat(szFile.c_str(), &sStat);
        localtime_s(&sTMTime, &sStat.st_mtime);
        _tasctime_s(szTime, _countof(szTime), &sTMTime);

        szWindowTile += nsoutf(__T("[FileTime:{}]")) << szTime;
    }//if

    szWindowTile += nsoutf(__T("[PID:{}]")) << _getpid();

    SetConsoleTitle(szWindowTile.c_str());
}